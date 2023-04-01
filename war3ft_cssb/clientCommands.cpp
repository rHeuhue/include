#define ULT_SEARCHTIME		50			// Translates to 5 seconds

// This isn't actually called when they join spectator
public cmd_Teamselect( idUser, key )
{
	if ( !WC3_Check() )
		return;

	arrBoolData[idUser][PB_CHANGINGTEAM] = true;
}

public cmd_Jointeam( idUser )
{	

	if ( !WC3_Check() )
		return;

	arrBoolData[idUser][PB_CHANGINGTEAM] = true;
}

// This is here to prevent the user from forcing a ResetHUD event
public cmd_fullupdate()
{
	if ( !WC3_Check() )
		return PLUGIN_CONTINUE;

	return PLUGIN_HANDLED;
}

// Called when the user buys a he grenade
public cmd_hegren( idUser )
{ 
	if ( !WC3_Check() )
		return PLUGIN_CONTINUE;

	// Make sure we even have grenade protection on
	if ( !get_pcvar_num( CVAR_wc3_grenade_protection ) )
		return PLUGIN_CONTINUE;

	// Then they shouldn't be buying a grenade anyway
	if ( !cs_get_user_buyzone( idUser ) )
		return PLUGIN_HANDLED;

	// User can only buy one grenade per round
	if ( arrIntData[idUser][P_HECOUNT] > 0 )
	{ 
		client_print( idUser, print_center, "%L", LANG_PLAYER, "ONLY_ONE_GRENADE_PER_ROUND" );

		return PLUGIN_HANDLED;
	}
	
	// Increment since they bought their grenade
	else
	{
		++arrIntData[idUser][P_HECOUNT];

		return PLUGIN_CONTINUE;
	}
	#if AMXX_VERSION_NUM < 183
	return PLUGIN_CONTINUE;
	#endif
} 

public cmd_Ultimate(idUser)
{
	if ( !WC3_Check( idUser ) )
		return PLUGIN_HANDLED;
	
	// User can't use ultimate when dead
	if ( !is_user_alive( idUser ) )
		return PLUGIN_HANDLED;

	//Блокировка использования заклинания Бладсикером
	if(arrBoolData[idUser][PB_BLOODRITE] == true)
	{
		new szSkillName[64];
		fGetSkillName(PASS_BLOODSEEKER,szSkillName, charsmax(szSkillName));
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_DISABLED_ULT_ABIL",szSkillName);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		return PLUGIN_HANDLED;
	}

	new iSkillID = SM_GetSkillOfType( idUser, SKILL_TYPE_ULTIMATE );
	new iSkillLevel = SM_GetSkillLevel( idUser, iSkillID);

	// User can't use their ultimate when they're hexed
	if ( arrBoolData[idUser][PB_HEXED] )
	{
		WC3_StatusText( idUser, TXT_ULTIMATE, "%L", LANG_PLAYER, "HEX_NO_ABILITY" );

		client_cmd( idUser, "speak %s", arrStrSounds[SOUND_ERROR] );

		return PLUGIN_HANDLED;
	}
	
	// User has no ultimate!
	else if ( iSkillLevel == 0 )
	{
		WC3_StatusText( idUser, TXT_ULTIMATE, "%L", LANG_PLAYER, "ULTIMATE_NOT_FOUND" );

		client_cmd( idUser, "speak %s", arrStrSounds[SOUND_ERROR] );

		return PLUGIN_HANDLED;
	}
	

	// Ultimate is used or not ready yet
	else if ( arrIntData[idUser][P_ULTIMATEDELAY] > 0 )
	{
		WC3_StatusText( idUser, TXT_ULTIMATE, "%L", LANG_PLAYER, "ULTIMATE_NOT_READY", arrIntData[idUser][P_ULTIMATEDELAY] );

		client_cmd( idUser, "speak %s", arrStrSounds[SOUND_ERROR] );

		return PLUGIN_HANDLED;
	}

	//Заблокирован ли супер навык на карте
	new szSkillName[64];
	if(isDisabledSkillsOnMap(idUser,iSkillID,szSkillName) == true)
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SKILL_DISABLED_ON_MAP",szSkillName);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		return PLUGIN_HANDLED;
	}

	// If we got here, then we can cast the user's ultimate
	switch ( iSkillID )
	{
		
		// UNDEAD - Suicide Bomber
		case ULTIMATE_SUICIDE:
		{
			// User has already had their warning - kill them!
			if ( arrBoolData[idUser][PB_SUICIDEATTEMPT] )
			{
				WC3_KillUser( idUser, 0, 0 );
			
				arrBoolData[idUser][PB_SUICIDEATTEMPT] = false
			}

			// Give the user his/her warning
			else
			{
				// Flash the user's ultimate icon
				ULT_Icon( idUser, ICON_FLASH );

				arrBoolData[idUser][PB_SUICIDEATTEMPT] = true

				WC3_StatusText( idUser, TXT_BLINK_CENTER, "%L", LANG_PLAYER, "SUICIDE_BOMB_ARMED" );
			}
		}

		// HUMAN ALLIANCE - Blink
		case ULTIMATE_BLINK:
		{
			HU_ULT_Blink( idUser );
		}
		
		// ORCISH HORDE - Chain Lightning
		case ULTIMATE_CHAINLIGHTNING:
		{
			if ( !arrBoolData[idUser][PB_ISSEARCHING] )
			{
				arrBoolData[idUser][PB_ISSEARCHING] = true;

				// Don't continue if task already exists...
				if ( !task_exists( TASK_ULTPING + idUser ) )
				{
					new parm[2];
					parm[0] = idUser;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}
		}

		// NIGHT ELF - Entangling Roots
		case ULTIMATE_ENTANGLE:
		{
			if ( !arrBoolData[idUser][PB_ISSEARCHING] )
			{
				arrBoolData[idUser][PB_ISSEARCHING] = true;

				// Don't continue if task already exists...
				if ( !task_exists( TASK_ULTPING + idUser ) )
				{
					new parm[2];
					parm[0] = idUser;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}
		}

		// BLOOD MAGE - Immolate
		case ULTIMATE_IMMOLATE:
		{
			arrBoolData[idUser][PB_ISSEARCHING] = true;

			// Don't continue if task already exists...
			if ( !task_exists( TASK_ULTPING + idUser ) )
			{
				new parm[2];
				parm[0] = idUser;
				parm[1] = 5;
				_ULT_Ping( parm );
			}
		}

		// SHADOW HUNTER - Big Bad Voodoo
		case ULTIMATE_BIGBADVOODOO:
		{
			SH_Ult_BigBadVoodoo( idUser );
		}

		// WARDEN - Vengeance
		case ULTIMATE_VENGEANCE:
		{
			WA_ULT_Vengeance( idUser );
		}

		// CRYPT LORD - Locust Swarm
		case ULTIMATE_LOCUSTSWARM:
		{

			if ( get_pcvar_num( CVAR_wc3_psychostats ) )
			{
				new WEAPON = CSW_LOCUSTS - CSW_WAR3_MIN;

				iStatsShots[idUser][WEAPON]++;
			}

			CL_ULT_LocustSwarm( idUser );
		}
		// Frost Mage - Blizzard - Снежная буря
		case ULTIMATE_FROST_MAGE_BLIZZARD:
		{
			arrBoolData[idUser][PB_ISSEARCHING] = true;

			// Don't continue if task already exists...
			if ( !task_exists( TASK_ULTPING + idUser ) )
			{
				new parm[2];
				parm[0] = idUser;
				parm[1] = 5;
				_ULT_Ping( parm );
			}
		}
		// Черный маг
		case ULTIMATE_BLACKLIGHTNING:
		{
			arrBoolData[idUser][PB_ISSEARCHING] = true;

			// Don't continue if task already exists...
			if ( !task_exists( TASK_ULTPING + idUser ) )
			{
				new parm[2];
				parm[0] = idUser;
				parm[1] = 5;
				_ULT_Ping( parm );
			}
		}
		// Chameleon - Flame Strike
		case ULTIMATE_CHAM_FLAME_STRIKE:
		{
			if(arrIntData[idUser][P_RACE] == RACE_CHAMELEON)
			{
				Ultimate_FlameStrike(idUser);
				arrIntData[idUser][P_FLAMECOUNT]++;
				if(arrIntData[idUser][P_FLAMECOUNT]>5)
				{
					ULT_Icon( idUser, ICON_HIDE );
					arrIntData[idUser][P_FLAMECOUNT]=0;

				}
			}
		}
		// Race: Death knight (Рыцарь смерти) - Власть крови - Blood Presence
		case ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE:
		{
			clRaceDeathKnight::ultBloodPresence(idUser);
		}
		// Alchemist - Eclipse
		case ULTIMATE_RADIATION:
		{
			arrBoolData[idUser][PB_ISSEARCHING] = true;

			// Don't continue if task already exists...
			if ( !task_exists( TASK_ULTPING + idUser ) )
			{
				new parm[2];
				parm[0] = idUser;
				parm[1] = 5;
				_ULT_Ping( parm );
			}
		}
		// *******************************************************
		// Супер навык - Слово Тьмы: Смерть - Darkness word: Death
		// *******************************************************
		case ULTIMATE_PRIEST_DARKNESS_WORD_DEATH:
		{
			if ( arrBoolData[idUser][PB_SUICIDEATTEMPT] )
			{
				clRacePriest::ultDarkWordDeath(idUser);

				arrBoolData[idUser][PB_SUICIDEATTEMPT] = false
			}
			else
			{
				// Flash the user's ultimate icon
				ULT_Icon( idUser, ICON_FLASH );

				arrBoolData[idUser][PB_SUICIDEATTEMPT] = true

				WC3_StatusText( idUser, TXT_BLINK_CENTER, "%L", LANG_PLAYER, "MSG_PRIEST_DARKNESS_WORD_DEATH" );
			}
		}

		// *******************************************************
		// Супер навык - Бросок сюрикена - Shuriken Toss
		// *******************************************************
		case ULTIMATE_ROGUE:
		{
			clRogue::ultShurikenToss(idUser);
		}
		// *******************************************************
		// Супер навык - Астральная буря - Astral Storm
		// *******************************************************
		case ULTIMATE_DRUID:
		{
			clDruid::ultAstralStorm(idUser);
		}
		// *******************************************************
		// Супер навык - Бладсикер
		// *******************************************************
		case ULTIMATE_BLOODSEEKER:
		{
			if ( !arrBoolData[idUser][PB_ISSEARCHING] )
			{
				arrBoolData[idUser][PB_ISSEARCHING] = true;

				// Don't continue if task already exists...
				if ( !task_exists( TASK_ULTPING + idUser ) )
				{
					new parm[2];
					parm[0] = idUser;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}
		}
		// *******************************************************
		// Супер навык - Раса Джагернаут
		// *******************************************************
		case ULTIMATE_JUGGERNAUT:
		{
			if ( !arrBoolData[idUser][PB_ISSEARCHING] )
			{
				arrBoolData[idUser][PB_ISSEARCHING] = true;
				
				if ( !task_exists( TASK_ULTPING + idUser ) )
				{
					new parm[2];
					parm[0] = idUser;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}
		}
		// *******************************************************
		// Супер навык - Раса Снайпер
		// *******************************************************
		case ULTIMATE_SNIPER:
		{			
			if ( !arrBoolData[idUser][PB_ISSEARCHING] )
			{
				arrBoolData[idUser][PB_ISSEARCHING] = true;
				
				if ( !task_exists( TASK_ULTPING + idUser ) )
				{
					new parm[2];
					parm[0] = idUser;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}

		}
		// *******************************************************
		// Супер навык - Раса Разрушитель
		// *******************************************************
		case ULTIMATE_DISRUPTOR:
		{
			if ( !arrBoolData[idUser][PB_ISSEARCHING] )
			{
				arrBoolData[idUser][PB_ISSEARCHING] = true;
				
				if ( !task_exists( TASK_ULTPING + idUser ) )
				{
					new parm[2];
					parm[0] = idUser;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}
		}
		// *******************************************************
		// Супер навык - Раса Блэйд
		// *******************************************************
		case ULTIMATE_RAZOR:
		{
			if (!arrBoolData[idUser][PB_ISSEARCHING])
			{
				arrBoolData[idUser][PB_ISSEARCHING] = true;
				
				if ( !task_exists( TASK_ULTPING + idUser ) )
				{
					new parm[2];
					parm[0] = idUser;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}
		}
		// *******************************************************
		// Супер навык - Раса Варлок
		// *******************************************************
		case ULTIMATE_WARLOCK:
		{			
			if (!arrBoolData[idUser][PB_ISSEARCHING])
			{
				arrBoolData[idUser][PB_ISSEARCHING] = true;
				
				if ( !task_exists( TASK_ULTPING + idUser ) )
				{
					new parm[2];
					parm[0] = idUser;
					parm[1] = 5;
					_ULT_Ping( parm );
				}
			}
		}
		// *******************************************************
		// Супер навык - Раса Невермор
		// *******************************************************
		case ULTIMATE_SHADOW_FIEND:
		{
			clShadowFiend::ultNecromastery(idUser);

		}
		// *******************************************************
		// Супер навык - Раса 24
		// *******************************************************
		case ULTIMATE_24:
		{
		}
		// *******************************************************
		// Супер навык - Раса 25
		// *******************************************************
		case ULTIMATE_25:
		{
		}
		
	}

	return PLUGIN_HANDLED;
}


public CMD_Handler( idUser )
{
	new szCmd[32];

	read_argv( 0, szCmd, 31 );

	CMD_Handle(idUser, szCmd);

	return PLUGIN_HANDLED;
}

public cmd_Say( idUser )
{
	new szSaid[32];
	read_args( szSaid, 31 );

	remove_quotes( szSaid );

	CMD_Handle(idUser, szSaid);

	return;
}

// Command handler
CMD_Handle(idUser, szCmd[])
{
	// Change the user's race
	if ( CMD_Equal( idUser,  szCmd, "changerace" ) )
	{
		if(clGl::isUserNoTeam(idUser))
			WC3_ChangeRaceStart(idUser);
	}
	
	// Display select skill menu
	else if ( CMD_Equal( idUser,  szCmd, "selectskills" ) || CMD_Equal( idUser,  szCmd, "selectskill" ) )
	{
		if(clGl::isUserNoTeam(idUser))
			MENU_SelectSkill( idUser );
	}

	else if ( CMD_Equal( idUser,  szCmd, "playerskills" ) )
	{
		if(clGl::isUserNoTeam(idUser))
			clMotd::fShowMotdPlayerRaces(idUser);
	}

	else if ( CMD_Equal( idUser,  szCmd, "ms" ) || CMD_Equal( idUser,  szCmd, "movespeed" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			format(szMessage, charsmax(szMessage), "%L %0.0f",LANG_PLAYER,"CLIENT_PRINT_MOVE_SPEED",get_user_maxspeed(idUser));
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}

	else if ( CMD_Equal( idUser,  szCmd, "skillsinfo" ) )
	{
		if(clGl::isUserNoTeam(idUser))
			MOTD_SkillsInfo( idUser );
	}

	else if ( CMD_Equal( idUser,  szCmd, "war3help" ) )
	{
		clMotd::fShowMenuHelp(idUser);
	}
	else if ( CMD_Equal( idUser, szCmd, "levitation" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			if ( SM_GetSkillLevel( idUser, SKILL_LEVITATION ) <= 0 )
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LEVITATION_0");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				

				return;
			}

			if ( g_bLevitation[idUser] )
			{
				g_bLevitation[idUser] = false;
			
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LEVITATION_1");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
			else
			{
				g_bLevitation[idUser] = true;
			
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LEVITATION_2");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}

			SHARED_SetGravity(idUser);
		}
	}

	else if ( CMD_Equal( idUser,  szCmd, "level" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			WC3_ShowRaceInfo( idUser );
			WC3_ShowBar( idUser );
		}
	}

	else if ( CMD_Equal( idUser,  szCmd, "shopmenu" ) )
	{
		if(clGl::isUserNoTeam(idUser))
			MENU_Shopmenu( idUser, 0 );
	}

	else if ( CMD_Equal( idUser,  szCmd, "resetxp" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			if((get_user_flags(idUser) & ADMIN_FLAG))
			{
				MENU_ResetXP( idUser );
			}
			else
			{
				format(szMessage, charsmax(szMessage), "%L%L%L %L",
				LANG_PLAYER,"WC3_BRACKET_LEFT",LANG_PLAYER,"WC3_MODCLIENT",LANG_PLAYER,"WC3_BRACKET_RIGHT",
				LANG_PLAYER,"YOU_HAVE_NO_ACCESS");		
				
				client_print( idUser, print_console,szMessage);
				
				return;
			}
		}
	}
	else if ( CMD_Equal( idUser,  szCmd, "war3menuitems" ) )
	{
		if(clGl::isUserNoTeam(idUser))
			menu_Item_Options(idUser);
	}
	else if ( CMD_Equal( idUser,  szCmd, "war3menu" ) )
	{
		if(clGl::isUserNoTeam(idUser))
			MENU_War3Menu( idUser );
	}
	else if ( CMD_Equal( idUser,  szCmd, "savexp" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SAVE_XP");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}

	else if ( CMD_Equal( idUser,  szCmd, "resetskills" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			// Special message for csdm
			if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 )
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_RESET_SKILLS");
				client_print( idUser, print_center,szMessage);
			}
			else
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"SKILLS_RESET_NEXT_ROUND");
				client_print( idUser, print_center,szMessage);
			}
			
			arrBoolData[idUser][PB_RESETSKILLS] = true;
		}
	}	
	// Ability to buy items through console commands
	else if ( CMD_Equal( idUser, szCmd, "ankh" ) )
	{
		
			if ( ITEM_MenuCanBuyCheck(idUser) )ITEM_Buy( idUser, ITEM_ANKH );
		
	}

	else if ( CMD_Equal( idUser, szCmd, "boots" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_BOOTS );
	}

	else if ( CMD_Equal( idUser, szCmd, "claws" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_CLAWS );
	}

	else if ( CMD_Equal( idUser, szCmd, "cloak" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_CLOAK );
	}

	else if ( CMD_Equal( idUser, szCmd, "mask" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_MASK );
	}

	else if ( CMD_Equal( idUser, szCmd, "necklace" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_NECKLACE );
	}

	else if ( CMD_Equal( idUser, szCmd, "frost" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_FROST );
	}

	else if ( CMD_Equal( idUser, szCmd, "health" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_HEALTH );
	}

	else if ( CMD_Equal( idUser, szCmd, "tome" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_TOME );
	}
	else if ( CMD_Equal( idUser, szCmd, "scroll" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_SCROLL );
	}
	else if ( CMD_Equal( idUser, szCmd, "molepr" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_PROTECTANT );
	}

	else if ( CMD_Equal( idUser, szCmd, "helm" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_HELM );
	}

	else if ( CMD_Equal( idUser, szCmd, "amulet" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_AMULET );
	}

	else if ( CMD_Equal( idUser, szCmd, "socks" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_SOCK );
	}

	else if ( CMD_Equal( idUser, szCmd, "gloves" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_GLOVES );
	}

	else if ( CMD_Equal( idUser,  szCmd, "rings" ))
	{
		
			if ( ITEM_MenuCanBuyCheck( idUser ) ) ITEM_BuyRings(idUser);
	}

	else if ( CMD_Equal(idUser, szCmd, "chameleon"))
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_CHAMELEON);
	}

	else if ( CMD_Equal(idUser, szCmd, "mole"))
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser,ITEM_MOLE);
	}

	else if ( CMD_Equal( idUser,  szCmd, "ability"))
	{
		if(clGl::isUserNoTeam(idUser) && g_EndRound == false)
		{
			
			{
				//Блокировка использования заклинания Бладсикером
				if(arrBoolData[idUser][PB_BLOODRITE] == true)
				{
					new szSkillName[64];
					fGetSkillName(PASS_BLOODSEEKER,szSkillName, charsmax(szSkillName));
					formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_DISABLED_ULT_ABIL",szSkillName);
					cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

					return;
				}

				switch(arrIntData[idUser][P_RACE])
				{
					case RACE_SHADOW:
						SH_PlaceSerpentWard(idUser);
					case RACE_BLACK_MAGICIAN:
						{
							if(isDisabledAbiltyOnMap(1000) == false)
								clRaceBlackMag::setAbilityBlast(idUser);
						}
					case RACE_ROGUE:
						fShowMenuActiveSkills(idUser);
					case RACE_DRUID:
						fShowMenuActiveSkills_Druid(idUser);
					case RACE_BLOODSEEKER:
						clBloodseeker::fShowMenuAbility(idUser);
					case RACE_JUGGERNAUT:
						{
							if(isDisabledAbiltyOnMap(1001) == false)
								clJuggernaut::skillHealingWard(idUser,SKILL_JUGGERNAUT_1);
						}
				}
			}
		}
	}

	else if ( CMD_Equal( idUser,  szCmd, "shopmenu2" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			
				MENU_Shopmenu( idUser, 9 );
		}
	}
	//Для shopmenu3
	else if ( CMD_Equal( idUser,  szCmd, "shopmenu3" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			
				MENU_Shopmenu( idUser, 18 );
		}
	}
	else if ( CMD_Equal( idUser, szCmd, "brain" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_INTELLECT );
	}
	else if ( CMD_Equal( idUser, szCmd, "nogren" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_GRENADE_PROTECTION );
	}
	else if ( CMD_Equal( idUser, szCmd, "mirror" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_MIRROR_SHIELD );
	}
	else if ( CMD_Equal( idUser, szCmd, "esp" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_ESP );
	}
	else if ( CMD_Equal( idUser, szCmd, "farmor" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_FROST_ARMOR );
	}
	else if ( CMD_Equal( idUser, szCmd, "deathtouch" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_DEATH_TOUCH );
	}
	else if ( CMD_Equal( idUser, szCmd, "hpp" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_HEALTH_POTION );
	}
	else if ( CMD_Equal( idUser, szCmd, "ulttimediv" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_ULTIMATE_TIMER_DIVIDER );
	}
	else if ( CMD_Equal( idUser, szCmd, "steelskin" ) )
	{
		
			if (ITEM_MenuCanBuyCheck(idUser)) ITEM_Buy( idUser, ITEM_STEEL_SKIN );
	}

	//Для shopmenu4
	else if ( CMD_Equal( idUser,  szCmd, "shopmenu4" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			
			{
			
				if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
				{
					if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
						MENU_Shopmenu( idUser, 27 );
					else if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) > 0 && (get_user_flags(idUser) & fVipShop4()))
						MENU_Shopmenu( idUser, 27 );
				}
				else
				{
					formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
					cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				}
			}
		}
	}
	else if ( CMD_Equal( idUser, szCmd, "devlight" ) )
	{
		
		{
			if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
			{
				if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_DEVOURER_LIGHT );
				}
				else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
				{
					if (ITEM_MenuCanBuyCheck(idUser))
						ITEM_Buy( idUser, ITEM_DEVOURER_LIGHT );
				}
			}
			else
			{
				formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		
	}
	else if ( CMD_Equal( idUser, szCmd, "iceblock" ) )
	{
		
		{
		
			if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
			{
				if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_ICE_BLOCK );
				}
				else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_ICE_BLOCK );
				}
			}
			else
			{
				formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		
	}
	else if ( CMD_Equal( idUser, szCmd, "thief" ) )
	{
		
		{
		
			if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
			{
				if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_THIEF );
				}
				else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_THIEF );
				}
			}
			else
			{
				formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
		}


	}
	else if ( CMD_Equal( idUser, szCmd, "mirrorult" ) )
	{
		
		{
		
			if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
			{
				if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_MIRROR_ULTIMATE );
				}
				else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_MIRROR_ULTIMATE );
				}
			}
			else
			{
				formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		
	}
	else if ( CMD_Equal( idUser, szCmd, "deathcoil" ) )
	{
		
		{
			if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
			{
				if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_DEATHCOIL );	
				}
				else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_DEATHCOIL );
				}
			}
			else
			{
				formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		
	}
	else if ( CMD_Equal( idUser, szCmd, "impale" ) )
	{
		
		{
			if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
			{
				if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_IMPALE );
				}
				else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_IMPALE );
				}
			}
			else
			{
				formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		
	}
	else if ( CMD_Equal( idUser, szCmd, "sleep" ) )
	{
		
		{
			if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
			{
				if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_SLEEP );
				}
				else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_SLEEP );
				}
			}
			else
			{
				formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		
	}
	else if ( CMD_Equal( idUser, szCmd, "skeletons" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			
			{
			
				if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
				{
					if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
					{
						if (ITEM_MenuCanBuyCheck(idUser)) 
							ITEM_Buy( idUser, ITEM_BOOK_DEAD );
					}
					else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
					{
						if (ITEM_MenuCanBuyCheck(idUser)) 
							ITEM_Buy( idUser, ITEM_BOOK_DEAD );
					}
				}
				else
				{
					formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
					cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				}
			}
		}
		
	}
	else if ( CMD_Equal( idUser, szCmd, "tranquility" ) )
	{
		
		{

			if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
			{
				if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_TRANQUILITY );
				}
				else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
				{
					if (ITEM_MenuCanBuyCheck(idUser)) 
						ITEM_Buy( idUser, ITEM_TRANQUILITY );
				}
			}
			else
			{
				formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
		}
	
	}
	//Для talisman +
	else if ( CMD_Equal( idUser, szCmd, "talisman" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			
				fShowMenuTalismans(idUser);
		}
	}
	//Для авто закупки предметов
	else if ( CMD_Equal( idUser, szCmd, "autobuyitems" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			
				fShowMenuAutoBuyBase(idUser);
		}
	}
	else if ( CMD_Equal(idUser, szCmd, "nomole" ) )
	{
		if(bNomole[idUser] == false) //Включение блокировки
		{
			bNomole[idUser] = true;

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_NOMOLE_BLOCK_ON");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		else//Отключение
		{
			bNomole[idUser] = false;

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_NOMOLE_BLOCK_OFF");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	else if ( CMD_Equal(idUser, szCmd, "silentheal" ) )
	{
		if(bSilentHeal[idUser] == false) //Включение блокировки
		{
			bSilentHeal[idUser] = true;

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SILENTHEAL_BLOCK_ON");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		else//Отключение
		{
			bSilentHeal[idUser] = false;

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SILENTHEAL_BLOCK_OFF");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	//Информация о моде
	else if ( CMD_Equal( idUser, szCmd, "cssb_version" ) )
	{
		
			clGl::fPrintInfoMod(idUser);
	}
	//VIP меню
	else if ( CMD_Equal( idUser, szCmd, "showvipmenu" ) )
	{
		if(clGl::isUserNoTeam(idUser))
		{
			
				clVIP:fShowVipMenu(idUser);
		}
	}
	
	
	
	return;
}

// Function will check if the first string is equal to the second (checks for NAME or /NAME)
CMD_Equal( idUser,  szCmd[], szCorrectCmd[] )
{
	new szTmp[64];
	formatex( szTmp, 63, "/%s", szCorrectCmd );

	new bool:bValid = equali( szCmd, szTmp ) || equali( szCmd, szCorrectCmd );
	
	if ( !WC3_Check() )
	{
		
		// Only print a message if the command was valid
		if ( bValid )
		{
			WC3_Check( idUser );
		}
	
		return false;
	}


	return bValid;
}
