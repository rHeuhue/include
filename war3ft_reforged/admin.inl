/*
*	Admin Functions
*/

// Admin Commands Added by Huehue

public WC3_Give_Exp(id, level, cid)
{
	// Make sure WC3 is loaded
	if (!WC3_Check())
		return PLUGIN_HANDLED;

	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED

	new szArgs[32], szArgsExp[10], szTarget[32];
	read_argv(1, szArgs, charsmax(szArgs));
	read_argv(2, szArgsExp, charsmax(szArgsExp));

	new iAddXp = str_to_num(szArgsExp);

	new iPlayers[MAX_PLAYERS], iNum = cmd_targetex(id, szArgs, iPlayers, szTarget, charsmax(szTarget), TARGETEX_NONE);

	if (!iNum)
		return PLUGIN_HANDLED;

	for(--iNum; iNum >= 0; iNum--)
	{
		ADMIN_SetXP(iPlayers[iNum], p_data[iPlayers[iNum]][P_XP] + iAddXp);
	}

	client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: gave ^1%i Experience ^4to ^3%s^4.", id, iAddXp, szTarget);

	return PLUGIN_HANDLED;
}

public WC3_Take_Exp(id, level, cid)
{
	// Make sure WC3 is loaded
	if (!WC3_Check())
		return PLUGIN_HANDLED;

	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED

	new szArgs[32], szArgsExp[10], szTarget[32];
	read_argv(1, szArgs, charsmax(szArgs));
	read_argv(2, szArgsExp, charsmax(szArgsExp));

	new iRemoveXp = str_to_num(szArgsExp);

	new iPlayers[MAX_PLAYERS], iNum = cmd_targetex(id, szArgs, iPlayers, szTarget, charsmax(szTarget), TARGETEX_NONE);

	if (!iNum)
		return PLUGIN_HANDLED;

	for(--iNum; iNum >= 0; iNum--)
	{
		ADMIN_SetXP(iPlayers[iNum], p_data[iPlayers[iNum]][P_XP] - iRemoveXp);

		if (p_data[iPlayers[iNum]][P_XP] < 0)
			ADMIN_SetXP(iPlayers[iNum], 0);
	}

	client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: took ^1%i Experience ^4from ^3%s^4.", id, iRemoveXp, szTarget);

	return PLUGIN_HANDLED;
}

public WC3_Give_Item(id, level, cid)
{
	// Make sure WC3 is loaded
	if (!WC3_Check())
		return PLUGIN_HANDLED;

	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED

	new szArgs[32], szArgsItem[10], szTarget[32], iItemID;
	read_argv(1, szArgs, charsmax(szArgs));
	read_argv(2, szArgsItem, charsmax(szArgsItem));

	ucfirst(szArgsItem);

	if (!is_str_num(szArgsItem))
	{
		for (new i = 0; i <= 18; i++)
		{
			if (equal(szArgsItem, Lang_ItemDatabase[i][ITEM_NAME_SHORT]))
				iItemID = i;
		}
	}
	else
	{
		if (is_str_num(szArgsItem))
		{
			iItemID = str_to_num(szArgsItem);
		}
	}

	if (iItemID > 18 || iItemID < 0)
	{
		ADMIN_Print(id, "Item ID must be in between 0 and 18.");
		return PLUGIN_HANDLED;
	}

	new iPlayers[MAX_PLAYERS], iNum = cmd_targetex(id, szArgs, iPlayers, szTarget, charsmax(szTarget), TARGETEX_NONE);

	if (!iNum)
		return PLUGIN_HANDLED;

	for(--iNum; iNum >= 0; iNum--)
	{
		ITEM_GiveItem(iPlayers[iNum], iItemID);
	}

	client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: gave item ^1%s ^4to ^3%s^4.", id, Lang_ItemDatabase[iItemID][ITEM_NAME_LONG], szTarget);

	return PLUGIN_HANDLED;
}

public WC3_Remove_Item(id, level, cid)
{
	// Make sure WC3 is loaded
	if (!WC3_Check())
		return PLUGIN_HANDLED;

	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED

	new szArgs[32], szArgsItem[10], szTarget[32], iItemID;
	read_argv(1, szArgs, charsmax(szArgs));
	read_argv(2, szArgsItem, charsmax(szArgsItem));

	ucfirst(szArgsItem);

	if (!is_str_num(szArgsItem))
	{
		for (new i = 0; i <= 18; i++)
		{
			if (equal(szArgsItem, Lang_ItemDatabase[i][ITEM_NAME_SHORT]))
				iItemID = i;
		}
	}
	else
	{
		if (is_str_num(szArgsItem))
		{
			iItemID = str_to_num(szArgsItem);
		}
	}

	if (iItemID > 18 || iItemID < 0)
	{
		ADMIN_Print(id, "Item ID must be in between 0 and 18.");
		return PLUGIN_HANDLED;
	}

	new iPlayers[MAX_PLAYERS], iNum = cmd_targetex(id, szArgs, iPlayers, szTarget, charsmax(szTarget), TARGETEX_NONE);

	if (!iNum)
		return PLUGIN_HANDLED;

	for(--iNum; iNum >= 0; iNum--)
	{
		ITEM_RemoveID(iPlayers[iNum], iItemID);
	}

	client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: remove item ^1%s ^4from ^3%s^4.", id, Lang_ItemDatabase[iItemID][ITEM_NAME_LONG], szTarget);

	return PLUGIN_HANDLED;
}

public WC3_Set_Level(id, level, cid)
{
	// Make sure WC3 is loaded
	if (!WC3_Check())
		return PLUGIN_HANDLED;

	if (!cmd_access(id, level, cid, 2))
		return PLUGIN_HANDLED

	new szArgs[32], szArgsExp[10], szTarget[32];
	read_argv(1, szArgs, charsmax(szArgs));
	read_argv(2, szArgsExp, charsmax(szArgsExp));

	new iLevel = str_to_num(szArgsExp);

	if (iLevel < 0 || iLevel >= 11)
	{
		ADMIN_Print(id, "Level must be in between 0 and 10.");
		return PLUGIN_HANDLED;
	}

	new iXP = XP_GetByLevel(iLevel);

	new iPlayers[MAX_PLAYERS], iNum = cmd_targetex(id, szArgs, iPlayers, szTarget, charsmax(szTarget), TARGETEX_NONE);

	if (!iNum)
		return PLUGIN_HANDLED;

	for(--iNum; iNum >= 0; iNum--)
	{
		ADMIN_SetXP(iPlayers[iNum], iXP);
	}

	client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: set ^1%i Level ^4to ^3%s^4.", id, iLevel, szTarget);

	return PLUGIN_HANDLED;
}

// Actually set the user's XP
ADMIN_SetXP( id, iXP )
{
	if ( iXP < 0 )
	{
		iXP = 0;
	}

	p_data[id][P_XP] = iXP;

	XP_Check( id );

	set_task( 0.3, "WC3_GetUserInput", TASK_GETINPUT + id );
}


// Function will print to server console or client console based on the ID number
ADMIN_Print( id, text[], {Float,_}:...)
{    
	// format the text as needed

	new szFormattedText[128];
	format_args( szFormattedText, 127, 1 );

	if ( id == 0 )
	{
		server_print( szFormattedText );
	}
	else
	{
		client_print( id, print_console, szFormattedText );
	}

	// Gets rid of compiler warning
	if ( text[0] == 0 )
	{
		return;
	}
}  

/*
// Adapted from war3x's log file (I was lazy)
ADMIN_Log( id, szCommand[], {Float,_}:... )
{

	new szLogFile[128];
	get_configsdir( szLogFile, 127 );
	formatex( szLogFile, 127, "%s/war3ft/wc3_admin.log", szLogFile );

	new szFormattedText[128];
	format_args( szFormattedText, 127, 2 );

	if ( !file_exists( szLogFile ) )
	{
		write_file( szLogFile, "WC3 : Frozen Throne", -1 );
		write_file( szLogFile, "Logging of admin commands", -1 );
		write_file( szLogFile, " ", -1 );
	}

	new szAdminName[32], szSteamID[32], szTeam[13];
	if ( id > 0 )
	{
		get_user_name( id, szAdminName, 31 );
		get_user_authid( id, szSteamID, 31 );
		get_user_team( id, szTeam, 12 );
	}
	else
	{
		copy( szAdminName, 31, "SERVER" );
		copy( szSteamID, 31, "SERVER" );
	}

	new szCurrentTime[32];
	get_time( "L %m/%d/%Y %H:%M:%:", szCurrentTime, 31 );

	new szLogEntry[256];
	formatex( szLogEntry, 255, "%s Cmd: ^"%s<%d><%s><%s>^" '%s %s'", szCurrentTime, szAdminName, get_user_userid( id ), szSteamID, szTeam, szCommand, szFormattedText );

	write_file( szLogFile, szLogEntry, -1 );

	// Gets rid of compiler warning
	if ( szCommand[0] == 0 )
	{
		return;
	}
}
*/