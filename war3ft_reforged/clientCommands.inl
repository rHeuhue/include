// Search the target for 5 sec 
#define ULT_SEARCHTIME		50			

// This isn't actually called when they join spectator 
public cmd_Teamselect( id, key )
{
	p_data_b[id][PB_CHANGINGTEAM] = true;
}

public cmd_Jointeam( id )
{
	p_data_b[id][PB_CHANGINGTEAM] = true;
}

// This is here to prevent the user from forcing a ResetHUD event
public cmd_fullupdate()
{
	return PLUGIN_HANDLED;
}

// Called when the user buys a he grenade
public cmd_hegren( id )
{ 
	if ( !WC3_Check() )
	{
		return PLUGIN_CONTINUE;
	}

	// Make sure we even have grenade protection on
	if ( !get_pcvar_num( CVAR_wc3_grenade_protection ) )
	{
		return PLUGIN_CONTINUE;
	}

	// Then they shouldn't be buying a grenade anyway
	if ( !cs_get_user_buyzone( id ) )
	{
		return PLUGIN_HANDLED;
	}


	// User can only buy one grenade per round
	if ( p_data[id][P_HECOUNT] > 0 )
	{ 
		client_print( id, print_center, "Only one grenade per round !");

		return PLUGIN_HANDLED;
	}
	
	// Increment since they bought their grenade
	else
	{
		++p_data[id][P_HECOUNT];

		return PLUGIN_CONTINUE;
	}
	#if AMXX_VERSION_NUM < 183
	return PLUGIN_CONTINUE;
	#endif
} 

public cmd_Ultimate(id)
{

	

	// User can't use ultimate when dead
	if ( !is_user_alive( id ) )
	{
		return PLUGIN_HANDLED;
	}

	new iSkillID = SM_GetSkillOfType( id, SKILL_TYPE_ULTIMATE );
	new iSkillLevel = SM_GetSkillLevel( id, iSkillID, 3 );

	// User can't use their ultimate when they're hexed
	if ( p_data_b[id][PB_HEXED] )
	{
		WC3_StatusText( id, TXT_ULTIMATE, "You have no ability because HEX.");

		client_cmd( id, "speak %s", g_szSounds[SOUND_ERROR] );

		return PLUGIN_HANDLED;
	}
	
	// User has no ultimate!
	else if ( iSkillLevel == 0 )
	{
		WC3_StatusText( id, TXT_ULTIMATE, "Ultimate not found." );

		client_cmd( id, "speak %s", g_szSounds[SOUND_ERROR] );

		return PLUGIN_HANDLED;
	}
	
	// We're still in the global delay :/
	else if ( g_iUltimateDelay > 0 )
	{
		WC3_StatusText( id, TXT_ULTIMATE, "Ultimate Cooldown: %d Seconds", g_iUltimateDelay );
		
		client_cmd( id, "speak %s", g_szSounds[SOUND_ERROR] );

		return PLUGIN_HANDLED;
	}

	// Ultimate is used or not ready yet
	else if ( p_data[id][P_ULTIMATEDELAY] > 0 )
	{
		WC3_StatusText( id, TXT_ULTIMATE, "Ultimate Cooldown: %d Seconds", p_data[id][P_ULTIMATEDELAY] );

		client_cmd( id, "speak %s", g_szSounds[SOUND_ERROR] );

		return PLUGIN_HANDLED;
	}

	// If we got here, then we can cast the user's ultimate
	switch ( iSkillID )
	{
		
		// UNDEAD - Suicide Bomber
		case ULTIMATE_SUICIDE:
		{
			// User has already had their warning - kill them!
			if ( p_data_b[id][PB_SUICIDEATTEMPT] )
			{
				WC3_KillUser( id, 0, 0 );
			
				p_data_b[id][PB_SUICIDEATTEMPT] = false
			}

			// Give the user his/her warning
			else
			{
				// Flash the user's ultimate icon
				ULT_Icon( id, ICON_FLASH );

				p_data_b[id][PB_SUICIDEATTEMPT] = true

				WC3_StatusText( id, TXT_BLINK_CENTER, "Ready to Suicide ? ^nPress again and detonate !");
			}
		}

		// HUMAN ALLIANCE - Blink
		case ULTIMATE_BLINK:
		{
			HU_ULT_Blink( id );
		}

		// ORCISH HORDE - Chain Lightning
		case ULTIMATE_CHAINLIGHTNING:
		{
			if ( !p_data_b[id][PB_ISSEARCHING] )
			{
				p_data_b[id][PB_ISSEARCHING] = true;

				// Don't continue if task already exists...
				if ( !task_exists( TASK_ULTPING + id ) )
				{
					new parm[2];
					parm[0] = id;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}
		}

		// NIGHT ELF - Entangling Roots
		case ULTIMATE_ENTANGLE:
		{
			if ( !p_data_b[id][PB_ISSEARCHING] )
			{
				p_data_b[id][PB_ISSEARCHING] = true;

				// Don't continue if task already exists...
				if ( !task_exists( TASK_ULTPING + id ) )
				{
					new parm[2];
					parm[0] = id;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}
		}

		// BLOOD MAGE - Immolate
		case ULTIMATE_IMMOLATE:
		{
			p_data_b[id][PB_ISSEARCHING] = true;

			// Don't continue if task already exists...
			if ( !task_exists( TASK_ULTPING + id ) )
			{
				new parm[2];
				parm[0] = id;
				parm[1] = 5;
				_ULT_Ping( parm );
			}
		}

		// SHADOW HUNTER - Big Bad Voodoo
		case ULTIMATE_BIGBADVOODOO:
		{
			SH_Ult_BigBadVoodoo( id );
		}

		// WARDEN - Vengeance
		case ULTIMATE_VENGEANCE:
		{
			WA_ULT_Vengeance( id );
		}

		// CRYPT LORD - Locust Swarm
		case ULTIMATE_LOCUSTSWARM:
		{
			CL_ULT_LocustSwarm( id );
		}
		
		// CRYSTAL  
		case ULTIMATE_FIELD:
		{

			if ( p_data_b[id][PB_FIELDATTEMPT] )
			{
				CM_ULT_Field( id );
			
				p_data_b[id][PB_FIELDATTEMPT] = false
			}

			// Give the user his/her warning
			else
			{
				// Flash the user's ultimate icon
				ULT_Icon( id, ICON_FLASH );

				p_data_b[id][PB_FIELDATTEMPT] = true

				WC3_StatusText( id, TXT_BLINK_CENTER, "Ready to Field ? ^nPress again to cast !");
			}
			
		}
		
		// DRUID - Crow Form
		case ULTIMATE_CROW:
		{
			DR_ULT_Crow( id );
		}

		
	}

	return PLUGIN_HANDLED;
}


public CMD_Handler( id )
{
	new szCmd[32];

	read_argv( 0, szCmd, 31 );

	CMD_Handle( id, szCmd);

	return PLUGIN_HANDLED;
}

public cmd_Say( id )
{	
	new szSaid[32];
	read_args( szSaid, 31 );
	remove_quotes( szSaid );

	// Hotfix Remove the commands itself in chat.. annoying for me
	for (new i = 1; i < sizeof g_szCommands; i++)
	{
		if (CMD_Equal(id, szSaid, g_szCommands[i]))
		{
			CMD_Handle(id, szSaid);
			return PLUGIN_HANDLED;
		}
	}

	// Hotfix Remove the commands itself in chat.. annoying for me
	return PLUGIN_CONTINUE;
	//return PLUGIN_HANDLED_MAIN; // buggy af as borislaw said
}

// Command handler
CMD_Handle( id, szCmd[])
{

	if ( CMD_Equal( id,  szCmd, "changerace" ) )
	{
		WC3_ChangeRaceStart( id );
	}
	else if ( CMD_Equal( id,  szCmd, "selectskills" ) || CMD_Equal( id,  szCmd, "selectskill" ) )
	{
		MENU_SelectSkills( id );
	}
	else if ( CMD_Equal( id,  szCmd, "playerskill" ) || CMD_Equal( id,  szCmd, "playerskills" ) || CMD_Equal( id,  szCmd, "playersinfo" ))
	{
		MOTD_PlayersInfo( id );
	}
	else if ( CMD_Equal( id,  szCmd, "war3menu" ) || CMD_Equal( id,  szCmd, "menu" ) || CMD_Equal( id,  szCmd, "gamemenu" ) )
	{
		MENU_GameMainMenu( id );
	}
	else if ( CMD_Equal( id,  szCmd, "skillsinfo" ) || CMD_Equal( id,  szCmd, "raceinfo" ) )
	{
		MOTD_RaceInfo( id );
	}
	else if ( CMD_Equal( id,  szCmd, "war3help" ) )
	{
		MOTD_TutorialInfo( id );
	}
	else if ( CMD_Equal( id,  szCmd, "account" ) )
	{
		MOTD_Account(id);
	}
	else if ( CMD_Equal( id,  szCmd, "level" ) )
	{
		WC3_ShowRaceInfo( id );
		WC3_ShowBar( id );
	}

	else if ( CMD_Equal( id,  szCmd, "shopmenu" ) || CMD_Equal( id,  szCmd, "shop" ) )
	{
		MENU_Shop( id );
	}
	
	else if ( CMD_Equal( id,  szCmd, "shopmenuinfo" ) || CMD_Equal( id,  szCmd, "shopinfo" ) || CMD_Equal( id,  szCmd, "iteminfo" ) || CMD_Equal( id,  szCmd, "itemsinfo" ) )
	{
		MOTD_ShopInfo( id );
	}


	else if ( CMD_Equal( id,  szCmd, "resetskills" ) )
	{
		// Special message for csdm
		if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 || CVAR_hws_active > 0 && get_pcvar_num( CVAR_hws_active ) == 1)
		{
			client_print( id, print_center, "Your skills will be reset when you respawn." );
			client_print_color( id, print_team_default, "^4%s ^3Your skills will be reset when you respawn.", GAME_NAME );
		}
		else
		{
			client_print( id, print_center, "Your skills will be reset next round.");
			client_print_color( id, print_team_default, "^4%s ^3Your skills will be reset next round.", GAME_NAME );
		}
		
		p_data_b[id][PB_RESETSKILLS] = true;
	}

	else if ( CMD_Equal( id,  szCmd, "exchange" ) || CMD_Equal( id,  szCmd, "gold" ) || CMD_Equal( id,  szCmd, "trade" ) )
	{
		Exchange_Think(id);
	}
	else if ( CMD_Equal( id,  szCmd, "levelbank" ) )
	{
		LevelBank(id);
	}
	
	// Ability to buy items through console commands
	else if ( CMD_Equal( id, szCmd, "ankh" ) )
	{
		if ( ITEM_MenuCanBuyCheck(id) )ITEM_Buy( id, ITEM_ANKH );
	}

	else if ( CMD_Equal( id, szCmd, "boots" ) )
	{
		if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_BOOTS );
	}

	else if ( CMD_Equal( id, szCmd, "claws" ) || CMD_Equal( id, szCmd, "claw" ) )
	{
		if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_CLAWS );
	}
	
	else if ( CMD_Equal( id, szCmd, "protectant" ) || CMD_Equal( id,  szCmd, "gem" )  )
	{
		if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_PROTECTANT );
	}

	else if ( CMD_Equal( id, szCmd, "cloak" ) )
	{
		if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_CLOAK );
	}

	else if ( CMD_Equal( id, szCmd, "mask" ) )
	{
		if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_MASK );
	}

	else if ( CMD_Equal( id, szCmd, "necklace" ) || CMD_Equal( id,  szCmd, "neck" )  || CMD_Equal( id,  szCmd, "wand" )  )
	{
		if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_NECKLACE );
	}

	else if ( CMD_Equal( id, szCmd, "frost" ) )
	{
		if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_FROST );
	}

	else if ( CMD_Equal( id, szCmd, "health" ) )
	{
		if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_HEALTH );
	}

	else if ( CMD_Equal( id, szCmd, "tome" ) )
	{
		if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_TOME );
	}

		else if ( CMD_Equal( id, szCmd, "scroll" ) )
		{
			if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_SCROLL );
		}

		else if ( CMD_Equal( id, szCmd, "helm" ) )
		{
			if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_HELM );
		}

		else if ( CMD_Equal( id, szCmd, "amulet" ) )
		{
			if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_AMULET );
		}

		else if ( CMD_Equal( id, szCmd, "socks" ) || CMD_Equal( id,  szCmd, "sock" )  )
		{
			if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_SOCK );
		}

		else if ( CMD_Equal( id, szCmd, "gloves" ) || CMD_Equal( id,  szCmd, "glove" ) )
		{
			if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_GLOVES );
		}

		else if ( CMD_Equal( id,  szCmd, "rings" ) || CMD_Equal( id,  szCmd, "ring" )  )
		{
			if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_RING );
		}

		else if ( CMD_Equal( id, szCmd, "chameleon" ) )
		{
			if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_CHAMELEON );
		}
		
		else if ( CMD_Equal( id, szCmd, "mine" ) )
		{
			if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_MINE );
		}

		else if ( CMD_Equal( id, szCmd, "mole" ) )
		{
			if (ITEM_MenuCanBuyCheck(id)) ITEM_Buy( id, ITEM_MOLE );
		}

		else if ( CMD_Equal( id,  szCmd, "ability" ) )
		{
			SH_PlaceSerpentWard( id );
		}
	
	return;
}

// Function will check if the first string is equal to the second (checks for NAME or /NAME)
CMD_Equal( id,  szCmd[], szCorrectCmd[] )
{

	new szTmp[64];
	formatex( szTmp, 63, "/%s", szCorrectCmd );

	new bool:bValid = equali( szCmd, szTmp ) || equali( szCmd, szCorrectCmd );
	
	if ( !WC3_Check() )
	{
		
		// Only print a message if the command was valid
		if ( bValid )
		{
			WC3_Check( id );
		}
	
		return false;
	}


	return bValid;
}
