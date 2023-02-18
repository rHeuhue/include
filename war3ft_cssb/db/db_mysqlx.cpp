/*
*	MYSQL
*/
// **********************************************************************
// �������� � ���������� ������ (������� � ��������)
// **********************************************************************

#define TOTAL_TABLES		5

new const szTables[TOTAL_TABLES][] = 
{
	//������ ���� ��� ������ MYSQL 5.5 � ����
	"CREATE TABLE IF NOT EXISTS `cssb_player` ( `player_id` int(8) unsigned NOT NULL auto_increment, `player_steamid` varchar(25) NOT NULL default '', `player_ip` varchar(20) NOT NULL default '', `player_name` varchar(35) NOT NULL default '', `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, PRIMARY KEY  (`player_id`), KEY `player_name` (`player_name`), KEY `player_ip` (`player_ip`), KEY `player_steamid` (`player_steamid`) ) ENGINE=MyISAM;",
	"CREATE TABLE IF NOT EXISTS `cssb_player_race` ( `player_id` int(8) unsigned NOT NULL default '0', `race_id` tinyint(4) unsigned NOT NULL default '0', `race_xp` int(8) default NULL, PRIMARY KEY  (`player_id`,`race_id`) ) ENGINE=MyISAM;",
	"CREATE TABLE IF NOT EXISTS `cssb_player_skill` ( `player_id` int(8) unsigned NOT NULL default '0', `skill_id` tinyint(4) unsigned NOT NULL default '0', `skill_level` tinyint(4) unsigned NOT NULL default '0', PRIMARY KEY  (`player_id`,`skill_id`) ) ENGINE=MyISAM;",
	//��� talisman +
	"CREATE TABLE IF NOT EXISTS `cssb_player_talisman` ( `player_id` int(8) unsigned NOT NULL default '0', `talisman_id` tinyint(4) unsigned NOT NULL default '0', PRIMARY KEY  (`player_id`,`talisman_id`) ) ENGINE=MyISAM;",
	"CREATE TABLE IF NOT EXISTS `cssb_num_talisman` ( `player_id` int(8) unsigned NOT NULL default '0', `talisman_num` tinyint(4) unsigned NOT NULL default '0', PRIMARY KEY  (`player_id`,`talisman_num`) ) ENGINE=MyISAM;"
};


// ������������� ����������� � ���� ������ MySQL
MYSQLX_Init()
{
		// ������ ��� ����������� � ����
		new szHost[64], szUser[32], szPass[32], szDB[128], szError[256], iErrNum;

		get_pcvar_string( CVAR_wc3_sql_dbhost, szHost,charsmax(szHost));
		get_pcvar_string( CVAR_wc3_sql_dbuser, szUser,charsmax(szUser));
		get_pcvar_string( CVAR_wc3_sql_dbpass, szPass,charsmax(szPass));
		get_pcvar_string( CVAR_wc3_sql_dbname, szDB,charsmax(szDB));

		// ���������� � ���������� � ����� ������
		g_DBTuple = SQL_MakeDbTuple( szHost, szUser, szPass, szDB );

		// ������������ � ����
		g_DBConn = SQL_Connect(g_DBTuple, iErrNum, szError, charsmax(szError));

		if (g_DBConn == Empty_Handle)//���� ��� ����������
		{
			WC3_Log(true, "[MYSQL] Database Connection Failed: [%d] %s", iErrNum, szError );
			return;
		}

		server_print( "[WAR3FT] MySQL database connection successful!!!" );

		bDBAvailable = true;

		MYSQLX_CreateTables();
	
}

// �������� �� �������� ����������� � ���� ������
bool:MYSQLX_Connection_Available()
{
	if ( !bDBAvailable || !g_DBConn )
		return false;

	return true;
}

// �������� ���� ������ ���� �� ���
MYSQLX_CreateTables()
{
	

	new Handle:hQuery;
	for ( new i = 0; i < TOTAL_TABLES; i++ )
	{
		hQuery = SQL_PrepareQuery( g_DBConn, szTables[i] );

		if (!SQL_Execute( hQuery ) )
		{
			MYSQLX_Error( hQuery, szTables[i], 1 );
			return;
		}

		SQL_FreeHandle( hQuery );
	}
}

//���������� ����������� �������������� ������
MYSQLX_FetchUniqueID( idUser )
{
	

	if (!MYSQLX_Connection_Available() )
		return;

	// ��� ����������
	g_iDBPlayerSavedBy[idUser] = get_pcvar_num( CVAR_wc3_save_by );

	new szKey[66], szKeyName[32];
	DB_GetKey(idUser, szKey, charsmax(szKey));
	DB_GetKeyName(szKeyName, charsmax(szKeyName));

	new szQuery[512];
	format(szQuery, charsmax(szQuery), "SELECT `player_id` FROM `cssb_player` WHERE `%s` = '%s';", szKeyName, szKey );
	
	new Handle:hQuery;
	hQuery = SQL_PrepareQuery( g_DBConn, szQuery );

	if (!SQL_Execute( hQuery ) )
	{
		MYSQLX_Error( hQuery, szQuery, 2 );
		return;
	}

	// ���� ��� ������� �� ������ ������� � ������,�� ��������� ����� � ����� ������
	if (SQL_NumResults( hQuery ) == 0 )
	{
		SQL_FreeHandle( hQuery );

		// ������� ������
		new szQueryCssbPlayer[512];
		format(szQueryCssbPlayer, charsmax(szQueryCssbPlayer), "INSERT INTO `cssb_player` ( `player_id` , `%s` , `time` ) VALUES ( NULL , '%s', NOW() );", szKeyName, szKey );
		new Handle:hQueryCssbPlayer;
		hQueryCssbPlayer = SQL_PrepareQuery( g_DBConn, szQueryCssbPlayer );

		if (!SQL_Execute( hQueryCssbPlayer ) )
		{
			MYSQLX_Error( hQueryCssbPlayer, szQueryCssbPlayer, 3 );
			return;
		}

		SQL_FreeHandle( hQueryCssbPlayer );
	}
	else//���������� ���������� ID ���� ������ ��� �������
	{
		g_iDBPlayerUniqueID[idUser] = SQL_ReadResult( hQuery, 0 );
		SQL_FreeHandle( hQuery );
	}

	
}

MYSQLX_Save(idUser)
{
	
		if (!MYSQLX_Connection_Available())
			return;

		new iUniqueID = DB_GetUniqueID( idUser );

		// ���� ���������� ID �� �������� ������������� ��������� ��� ������ � �������� ������ � ���������
		if ( iUniqueID <= 0 )
		{
			new szName[128];
			get_user_name( idUser, szName, charsmax(szName) );
			WC3_Log( true, "Unable to save XP for user '%s', unique ID: %d", szName, iUniqueID );
			return;
		}

		// ���������� ����� XP
		new szQueryXP[512];
		new Handle:hQueryXP;
		format(szQueryXP, charsmax(szQueryXP), "REPLACE INTO `cssb_player_race` ( `player_id` , `race_id` , `race_xp` ) VALUES ( '%d', '%d', '%d');", iUniqueID, arrIntData[idUser][P_RACE], arrIntData[idUser][P_XP] );
		hQueryXP = SQL_PrepareQuery(g_DBConn, szQueryXP);

		if (!SQL_Execute(hQueryXP))
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MYSQL_ERR_SAVE");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			MYSQLX_Error(hQueryXP, szQueryXP, 4 );
			return;
		}

		SQL_FreeHandle(hQueryXP);//+


		
		if (arrIntData[idUser][P_RACE] != RACE_CHAMELEON )
		{
			for (new iSkillID = 0; iSkillID < MAX_SKILLS; iSkillID++ )
			{
				if (g_SkillType[iSkillID] != SKILL_TYPE_PASSIVE )
				{
					new iCurrentLevel = SM_GetSkillLevel(idUser, iSkillID);
		
					if (iCurrentLevel >= 0 && g_iDBPlayerSkillStore[idUser][iSkillID] != iCurrentLevel )
					{
						new szQuerySkill[512];
						new Handle:hQuerySkill;
						g_iDBPlayerSkillStore[idUser][iSkillID] = iCurrentLevel;
						format(szQuerySkill, charsmax(szQuerySkill), "REPLACE INTO `cssb_player_skill` ( `player_id` , `skill_id` , `skill_level` ) VALUES ( '%d', '%d', '%d' );", iUniqueID, iSkillID, iCurrentLevel );
						hQuerySkill = SQL_PrepareQuery( g_DBConn, szQuerySkill );
		
						if (!SQL_Execute(hQuerySkill))
						{
							formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MYSQL_ERR_SAVE");	
							cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

							MYSQLX_Error(hQuerySkill, szQuerySkill, 5 );
							return;

						}//if

						SQL_FreeHandle(hQuerySkill);//+

					}//if
				}//if
			}//for
		}//if

		//���������� ����������
		if(MAX_MODE_TALISMAN == 1)
			fTalisman_MYSQLX_Save( idUser,iUniqueID );
	

	return;
}

//���������� � ������ ������
MYSQLX_Save_T(idUser)
{
	
		if (!MYSQLX_Connection_Available() )
			return;

		new iUniqueID = DB_GetUniqueID( idUser );
		if ( iUniqueID <= 0 )
		{
			new szName[128];
			get_user_name( idUser, szName, charsmax(szName) );
			WC3_Log( true, "Unable to save XP for user '%s', unique ID: %d", szName, iUniqueID );
			return;
		}

		new szQueryXP[512];
		format(szQueryXP, charsmax(szQueryXP), "REPLACE INTO `cssb_player_race` ( `player_id` , `race_id` , `race_xp` ) VALUES ( '%d', '%d', '%d');", iUniqueID, arrIntData[idUser][P_RACE], arrIntData[idUser][P_XP] );
		SQL_ThreadQuery(g_DBTuple, "_MYSQLX_Save_T",szQueryXP);

		if (arrIntData[idUser][P_RACE] != RACE_CHAMELEON)
		{
			for (new iSkillID = 0; iSkillID < MAX_SKILLS; iSkillID++ )
			{
				if (g_SkillType[iSkillID] != SKILL_TYPE_PASSIVE )
				{
					new iCurrentLevel = SM_GetSkillLevel(idUser, iSkillID);
					if (iCurrentLevel >= 0 && g_iDBPlayerSkillStore[idUser][iSkillID] != iCurrentLevel )
					{
						new szQuerySkill[512];
						g_iDBPlayerSkillStore[idUser][iSkillID] = iCurrentLevel;
						format(szQuerySkill, charsmax(szQuerySkill), "REPLACE INTO `cssb_player_skill` ( `player_id` , `skill_id` , `skill_level` ) VALUES ( '%d', '%d', '%d' );", iUniqueID, iSkillID, iCurrentLevel );
						SQL_ThreadQuery(g_DBTuple, "_MYSQLX_Save_T", szQuerySkill);
					}//if
				}//if
			}//for
		}//if
		
		//��� talisman +
		if(MAX_MODE_TALISMAN == 1)
			fTalisman_MYSQLX_Save_T( idUser,iUniqueID );

	

	return;
}

public _MYSQLX_Save_T( iFailState, Handle:hQuery, szError[], iErrNum, szData[], iSize )
{
	

    if(iFailState != TQUERY_SUCCESS)
    {
		new szQuery[256];
		SQL_GetQueryString(hQuery, szQuery, charsmax(szQuery));
		
		MYSQLX_ThreadError(hQuery, szQuery, szError, iErrNum, iFailState, 1 );
    }
}

MYSQLX_GetAllXP(idUser,iSelectIdMenu)
{
	
		if ( !MYSQLX_Connection_Available() )
			return;
		
		new iUniqueID = DB_GetUniqueID( idUser );
		if (iUniqueID <= 0 )
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MYSQL_UN_RET_XP");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			WC3_Log( true, "[ERROR] Unable to retreive user's Unique ID" );
			return;
		}

		new szQueryXP[256];
		format(szQueryXP, charsmax(szQueryXP), "SELECT `race_id`, `race_xp` FROM `cssb_player_race` WHERE ( `player_id` = '%d' );", iUniqueID );
		new Handle:hQueryXP = SQL_PrepareQuery( g_DBConn, szQueryXP );

		if (!SQL_Execute(hQueryXP))
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MYSQL_ERR_UN_RET_XP");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			MYSQLX_Error(hQueryXP, szQueryXP, 6 );
			return;
		}

		//��������� ������� ����� ����� ����������� �� ���� ������
		for ( new i = 0; i < MAX_RACES; i++ )
		{
			g_iDBPlayerXPInfoStore[idUser][i] = 0;
			arrPlayerLevelsInfo[idUser][i] = 0;
		}

		//��������� XP �� ���� ������
		new iXP, iRace;
		while (SQL_MoreResults(hQueryXP))
		{
			iRace	= SQL_ReadResult(hQueryXP, 0 );
			iXP		= SQL_ReadResult(hQueryXP, 1 );
			
			if (iRace > 0 && iRace < MAX_RACES + 1 )
			{
				g_iDBPlayerXPInfoStore[idUser][iRace-1] = iXP;
				arrPlayerLevelsInfo[idUser][iRace-1] = XP_GetLevelByXP( iXP ); 
			}

			SQL_NextRow( hQueryXP );
		}

		SQL_FreeHandle( hQueryXP );


		// ����� ���� � ������� ��� ����� ���������� ����� �� ���� ������
		WC3_ChangeRaceShowMenu(idUser, g_iDBPlayerXPInfoStore[idUser],arrPlayerLevelsInfo[idUser],iSelectIdMenu );
	

	return;
}

MYSQLX_SetDataForRace(idUser)
{
	
		if (!MYSQLX_Connection_Available() )
			return;

		new szQuerySkillLevel[256];
		format(szQuerySkillLevel, charsmax(szQuerySkillLevel), "SELECT `skill_id`, `skill_level` FROM `cssb_player_skill` WHERE `player_id` = '%d';", DB_GetUniqueID( idUser ) );
		new Handle:hQuerySkillLevel = SQL_PrepareQuery( g_DBConn, szQuerySkillLevel );

		if (!SQL_Execute( hQuerySkillLevel ) )
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MYSQL_ERR_UN_RET_XP");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			MYSQLX_Error( hQuerySkillLevel, szQuerySkillLevel, 21 );
			return;
		}

		// ������������� ���� ������
		arrIntData[idUser][P_XP] = g_iDBPlayerXPInfoStore[idUser][arrIntData[idUser][P_RACE]-1];

		// �������� ��� ������ ����� ����������� �� ���� ������
		for (new iSkillID = 0; iSkillID < MAX_SKILLS; iSkillID++ )
		{
			if (g_SkillType[iSkillID] != SKILL_TYPE_PASSIVE )
				SM_SetSkillLevel( idUser, iSkillID, 0, 2 );
		}
		
		new iSkillID, iSkillLevel;
		while ( SQL_MoreResults( hQuerySkillLevel ) )
		{
			iSkillID = SQL_ReadResult( hQuerySkillLevel, 0 );
			iSkillLevel = SQL_ReadResult( hQuerySkillLevel, 1 );
			
			SM_SetSkillLevel( idUser, iSkillID, iSkillLevel, 3 );
			g_iDBPlayerSkillStore[idUser][iSkillID] = iSkillLevel;

			SQL_NextRow( hQuerySkillLevel );
		}

		SQL_FreeHandle( hQuerySkillLevel );
		

		WC3_SetRaceUp( idUser );

		// This user's XP has been set + retrieved! We can save now
		bDBXPRetrieved[idUser] = true;

	

	return;
}

MYSQLX_Close()
{
	
	if (g_DBTuple)
		SQL_FreeHandle(g_DBTuple);

	if (g_DBConn)
		SQL_FreeHandle(g_DBConn);

	bDBAvailable = false;
}

// **********************************************************************
// ���������� ������� time. ����������� �������� �������
// **********************************************************************
MYSQLX_UpdateTimestamp(idUser)
{
	
	if (!MYSQLX_Connection_Available())
		return;

	new szKey[66];
	DB_GetKey(idUser, szKey, charsmax(szKey));

	new iUniqueID = DB_GetUniqueID(idUser);
	if (iUniqueID <= 0)
		return;

	new szQuery[256];
	format(szQuery, charsmax(szQuery), "UPDATE `cssb_player` SET time = NOW() WHERE ( `player_id` = '%d' );", iUniqueID);

	SQL_ThreadQuery( g_DBTuple, "_MYSQLX_UpdateTimestamp", szQuery );	
}

public _MYSQLX_UpdateTimestamp( iFailState, Handle:hQuery, szError[], iErrNum, szData[], iSize )
{
	
    if(iFailState != TQUERY_SUCCESS)
    {
		new szQuery[256];
		SQL_GetQueryString(hQuery, szQuery, charsmax(szQuery));
		
		MYSQLX_ThreadError(hQuery, szQuery, szError, iErrNum, iFailState, 1 );
    }
	else// �.� ������ ����� �� ������ ������ � �� �������,����� ��������
	{
		SQL_FreeHandle( hQuery );
	}
}

// **********************************************************************
// ������� ���� ������ �� ������ �������
// **********************************************************************
#define MYSQL_TOTAL_PRUNE_QUERY 4
// Prune the MySQL database
MYSQLX_Prune()
{
		

	if (!MYSQLX_Connection_Available() )
		return;

	new const szPruneQuery[MYSQL_TOTAL_PRUNE_QUERY][] = 
	{
		"DELETE FROM cssb_player_race  WHERE player_id IN ( SELECT `player_id` FROM `cssb_player` WHERE ( DATE_SUB(CURDATE(), INTERVAL %d DAY) > time ) )",
		"DELETE FROM cssb_player_skill WHERE player_id IN ( SELECT `player_id` FROM `cssb_player` WHERE ( DATE_SUB(CURDATE(), INTERVAL %d DAY) > time ) );",
		"DELETE FROM cssb_player_talisman WHERE player_id IN ( SELECT `player_id` FROM `cssb_player` WHERE ( DATE_SUB(CURDATE(), INTERVAL %d DAY) > time ) );",
		"DELETE FROM cssb_num_talisman WHERE player_id IN ( SELECT `player_id` FROM `cssb_player` WHERE ( DATE_SUB(CURDATE(), INTERVAL %d DAY) > time ) );"
	};

	new szQuery[512];
	for (new i = 0; i < MYSQL_TOTAL_PRUNE_QUERY; i++ )
	{
		formatex( szQuery, charsmax(szQuery), szPruneQuery[i], get_pcvar_num( CVAR_wc3_days_before_delete ) );

		new Handle:hQuery = SQL_PrepareQuery(g_DBConn, szQuery);

		if (!SQL_Execute( hQuery ) )
		{
			MYSQLX_Error( hQuery, szQuery, 11 );
			return;
		}

		SQL_FreeHandle( hQuery );//+
	}


	new bool:bFound = false;
	do 
	{
		//���������� ����������� ID ������ �� �������,����� �� ���� ������� ������ �� ����� �������
		new szQuerySelectID[512];
		format(szQuerySelectID, charsmax(szQuerySelectID), "SELECT `player_id` FROM `cssb_player` WHERE (DATE_SUB(CURDATE(), INTERVAL %d DAY) > TIME);",get_pcvar_num(CVAR_wc3_days_before_delete));
		
		new Handle:hQuerySelectID;
		hQuerySelectID = SQL_PrepareQuery(g_DBConn, szQuerySelectID );

		if (!SQL_Execute(hQuerySelectID) )
		{
			MYSQLX_Error( hQuerySelectID, szQuerySelectID, 25 );
			return;
		}

		if (SQL_NumResults(hQuerySelectID) == 0 ) //������ ��� ������� ��� �� ������� ������� �� ���������
		{
			bFound = true;
			SQL_FreeHandle( hQuerySelectID );
			break;
		}
		else//���� ������ �������� (������ ��������)
		{
			new iUniqueID = SQL_ReadResult( hQuerySelectID, 0 );
			SQL_FreeHandle( hQuerySelectID );

			if(iUniqueID <= 0)
				break;

			//�������� ����� ������ �� ����������� ID
			new szQueryDelete[256];
			format(szQueryDelete, charsmax(szQueryDelete), "DELETE FROM `cssb_player` WHERE (`player_id` = '%d' );",iUniqueID);
			new Handle:hQueryDelete = SQL_PrepareQuery(g_DBConn, szQueryDelete );

			if (!SQL_Execute(hQueryDelete))
			{
				MYSQLX_Error(hQueryDelete, szQueryDelete, 26 );
				return;
			}
			SQL_FreeHandle( hQueryDelete );
			
		}
	}
	while (bFound == false)

}


// **********************************************************************
// ����
// **********************************************************************
// The idUser should be a unique number, so we know what function called it (useful for debugging)
MYSQLX_Error( Handle:query, szQuery[], idUser )
{
		

	new szError[256];
	new iErrNum = SQL_QueryError( query, szError, 255 );

	WC3_Log( true, "[MYSQL] Error in querying database, location: %d", idUser);
	WC3_Log( true, "[MYSQL] Message: %s (%d)", szError, iErrNum );
	WC3_Log( true, "[MYSQL] Query statement: %s ", szQuery );

	// Free the handle
	SQL_FreeHandle( query );

	// MySQL server has gone away (2006)
	if ( iErrNum == 2006 )
	{
		WC3_Log( true, "[MYSQL] Attempting to re-establish connection to MySQL server" );
		// Close the connection
		MYSQLX_Close();

		// Re-open the connection
		MYSQLX_Init();
	}
}

MYSQLX_ThreadError(Handle:hQuery, szQuery[], szError[], iErrNum, iFailState, idError )
{
	
	WC3_Log(true, "[MYSQL] Threaded query error, location: %d", idError);
	WC3_Log(true, "[MYSQL] Message: %s (%d)", szError, iErrNum );
	WC3_Log(true, "[MYSQL] Query statement: %s ", szQuery );
	
	if (iFailState == TQUERY_CONNECT_FAILED )		// �������� � �����������
		WC3_Log(true, "[MYSQL] Fail state: Connection Failed" );
	else if (iFailState == TQUERY_QUERY_FAILED )	// �������� � ��������
		WC3_Log(true, "[MYSQL] Fail state: Query Failed" );

	SQL_FreeHandle(hQuery);
}