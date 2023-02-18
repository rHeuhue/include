/*
*	Admin Functions
*/

// Advanced Swear Filter and Punishment plugin uses this function
public ADMIN_ServerHandler()
{
	// Make sure WC3 is loaded
	if ( !WC3_Check() )
	{
		return PLUGIN_HANDLED;
	}

	new szCmd[32], szArg1[32], szArg2[32];
	read_argv( 0, szCmd, 31 );
	read_argv( 1, szArg1, 31 );
	read_argv( 2, szArg2, 31 );
	
	new id	= str_to_num( szArg1 );
	new iXP = str_to_num( szArg2 );

	if ( equal( szCmd, "amx_takexp" ) )
	{
		iXP *= -1;

		iXP += p_data[id][P_XP];
	}

	else if ( equal( szCmd, "changexp" ) )
	{
		iXP += p_data[id][P_XP];
	}

	ADMIN_SetXP( id, iXP );

	return PLUGIN_HANDLED;
}

// This will handle every admin client command
public ADMIN_Handler( id )
{
	new szCmd[32];
	read_argv( 0, szCmd, 31 );

	
	// Make sure the user is an admin
    if ( !( get_user_flags( id ) & XP_GetAdminFlag() ) )
	{
		client_print( id, print_console, "%s You have no access.", GAME_NAME );

		return PLUGIN_HANDLED;
	}

	// OK we're free to go!!!


	new szArg1[32], szArg2[32];
	read_argv( 1, szArg1, 31 );
	read_argv( 2, szArg2, 31 );

	// Give the user XP
	if ( equal( szCmd, "wc3_givexp" ) || equal( szCmd, "amx_givexp" ) )
	{
		if ( read_argc() < 3 )
		{
			ADMIN_Print( id, "Format: %s <name|#id|auth|@TEAM|@ALL> <xp>", szCmd );

			return PLUGIN_HANDLED;
		}

		ADMIN_GiveXP( id, szArg1, str_to_num( szArg2 ) );
	}

	// Set the level of a user's race
	else if ( equal( szCmd, "wc3_setlevel" ) )
	{
		if ( read_argc() < 3 )
		{
			ADMIN_Print( id, "Format: %s <name|#id|auth|@TEAM|@ALL> <level>", szCmd );

			return PLUGIN_HANDLED;
		}
		
		new iLevel = str_to_num( szArg2 );

		if ( iLevel < 0 || iLevel >= 11 )
		{
			ADMIN_Print( id, "%s Level must be in between 0 and 10.", GAME_NAME );

			return PLUGIN_HANDLED;
		}

		ADMIN_SetLevel( id, szArg1, iLevel );
	}

	// Give the user an item
	else if ( equal( szCmd, "wc3_giveitem" ) )
	{
		if ( read_argc() < 3 )
		{
			ADMIN_Print( id, "Format: %s <name|#id|auth|@TEAM|@ALL> <item id or name>", szCmd );

			return PLUGIN_HANDLED;
		}

		new iItemID;
		if ( is_str_num( szArg2 ) )
		{
			iItemID = str_to_num( szArg2 );
			if ( iItemID > 17 || iItemID < 0 )
			{
				ADMIN_Print( id, "%s Item ID must be in between 0 and 17.", GAME_NAME );

				return PLUGIN_HANDLED;
			}
		}

		ADMIN_GiveItem( id, szArg1, iItemID );
	}

	


	
	new szArgs[128];
	read_args( szArgs, 127 );

	ADMIN_Log( id, szCmd, "%s", szArgs );

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

// Set the user's level
ADMIN_SetLevel( id, szTarget[], iLevel )
{

	new iXP = XP_GetByLevel( iLevel );

	new iTarget = 0, bool:bTargetFound = false;

	// Do this while we continue having a target!
	while ( ( iTarget = FindTarget( iTarget, szTarget ) ) > 0 )
	{
		ADMIN_SetXP( iTarget, iXP );

		client_print( iTarget, print_chat, "%s The admin has set your level to %d.", GAME_NAME, iLevel );

		bTargetFound = true;
	}
	
	// No target found :/
	if ( !bTargetFound )
	{
		ADMIN_NoTargetFound( id, szTarget, ( iTarget == -2 ) );
	}
}

// Give the user some XP
ADMIN_GiveXP( id, szTarget[], iXP )
{
	new iTarget = 0, bool:bTargetFound = false;
	
	// Do this while we continue having a target!
	while ( ( iTarget = FindTarget( iTarget, szTarget ) ) > 0 )
	{
		ADMIN_SetXP( iTarget, p_data[iTarget][P_XP] + iXP );

		client_print( iTarget, print_chat, "%s The admin gave you %d experience.", GAME_NAME, iXP );

		bTargetFound = true;
	}

	// No target found :/
	if ( !bTargetFound )
	{
		ADMIN_NoTargetFound( id, szTarget, ( iTarget == -2 ) );
	}
}

// Give the user an item
ADMIN_GiveItem( id, szTarget[], iItemID )
{
	
	new iTarget = 0, bool:bTargetFound = false;

	// Do this while we continue having a target!
	while ( ( iTarget = FindTarget( iTarget, szTarget ) ) > 0 )
	{
		client_print( iTarget, print_chat, "%s The admin has given you the item %s.", GAME_NAME, Lang_ItemDatabase[iItemID][ITEM_NAME_LONG] );
		
		ITEM_GiveItem( iTarget, iItemID );

		bTargetFound = true;
	}

	// No target found :/
	if ( !bTargetFound )
	{
		ADMIN_NoTargetFound( id, szTarget, ( iTarget == -2 ) );
	}
}

// Find a user based on szTarget
FindTarget( iLastID, szTarget[] )
{
	
	new iTarget = -1;

	// Then we want to basically return everyone!
	if ( equali( szTarget, "@ALL" ) )
	{
		new players[32], iTotalPlayers, i;
		get_players( players, iTotalPlayers );
		
		// Loop through and search for the next target
		for ( i = 0; i < iTotalPlayers; i++ )
		{
			// Target found, so lets return the next one (if possible)!!
			if ( players[i] == iLastID && i + 1 != iTotalPlayers )
			{
				iTarget = players[i+1];
			}
		}

		// No target was found so return the first one
		if ( iTotalPlayers > 0 && iLastID == 0 )
		{
			iTarget = players[0];
		}
	}

	// Find a target based on the team
	else if ( szTarget[0] == '@' )
	{
		new iTeam = -1;
		
		// Counter-Strike and Condition Zero Checks
		if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
		{
			if ( equali( szTarget, "@T" ) )
			{
				iTeam = TEAM_T;
			}
			else if ( equali( szTarget, "@CT" ) )
			{
				iTeam = TEAM_CT;
			}
		}
		
		

		// Make sure a team was found
		if ( iTeam != -1 )
		{
			new players[32], iTotalPlayers, i, iFirstPlayer = -1, bool:bSaveNext = false;
			get_players( players, iTotalPlayers );

			// Loop through and search for the next target
			for ( i = 0; i < iTotalPlayers; i++ )
			{			
				// Make sure they're on the same team
				if ( iTeam == get_user_team( players[i] ) )
				{
					
					// This is the next available player
					if ( bSaveNext )
					{
						iTarget = players[i];
						break;
					}

					// If this is the previous target, we need to get the next one!
					if ( players[i] == iLastID )
					{
						bSaveNext = true;
					}
					
					// Save the FIRST player on this team
					if ( iFirstPlayer == -1 )
					{
						iFirstPlayer = players[i];
					}
				}
			}

			// No target was found so return the first one that matches the team (the target could still be -1 if iFirstPlayer wasn't found)
			if ( iLastID == 0 )
			{
				iTarget = iFirstPlayer;
			}
		}
	}

	// Otherwise search for a player
	else
	{
		// Initial search is by player name
		new iPlayer = find_player( "a", szTarget );
		
		// If not found, search by partial match
		if ( !iPlayer )
		{
			iPlayer = find_player( "bl", szTarget );

			if ( iPlayer )
			{

				// Then Multiple clients found
				if ( iPlayer != find_player( "blj", szTarget ) )
				{
					return -2;
				}
			}
		}

		// If not found, search by auth id
		if ( !iPlayer )
		{
			iPlayer = find_player( "c" , szTarget );
		}

		// If not found, search by user id
		if ( !iPlayer )
		{
			// Make sure we have a user id
			if ( szTarget[0] == '#' && szTarget[1] )
			{
				iPlayer = find_player( "k", str_to_num( szTarget[1] ) )
			}
		}
		
		// Yay we have a match!!!
		if ( iPlayer && iLastID != iPlayer )
		{
			iTarget = iPlayer;
		}
	}

	return iTarget;
}

ADMIN_NoTargetFound( id, szTarget[], bool:bMulti )
{
	// Multiple clients found
	if ( bMulti )
	{
		ADMIN_Print( id, "%s There is more than one client matching %s.", GAME_NAME, szTarget );
	}

	else
	{
		ADMIN_Print( id, "%s Unable to find target %s.", GAME_NAME, szTarget );
	}

	// List what the available targets are
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		ADMIN_Print( id, "%s Available targets are: @ALL, @CT, @T or Name/Auth/#id.", GAME_NAME );
	}

	
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