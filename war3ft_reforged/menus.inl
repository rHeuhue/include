public ShowInfoMessage(id)
{
	//client_print_color(id, print_team_default, "^4%s ^3Press '^1M^3' to open ^4Warcraft3: Frozen Throne^3 Game Menu.", GAME_NAME);
	client_print_color(id, print_team_default, "^4%s ^3Press '^1%s^3' to open ^4Warcraft3: Frozen Throne^3 Game Menu.", GAME_NAME, random_num(0, 1) == 0 ? "M" : "N");
}
	

public ChooseTeam(id)
{
	if (bChooseTeamOverrideActive[id])
	{
		MENU_GameMainMenu(id);
		return PLUGIN_HANDLED;
	}
	
	bChooseTeamOverrideActive[id] = true;
	return PLUGIN_CONTINUE;
}

public MENU_GameMainMenu(id) 
{ 
	if(is_user_connected(id)) 
	{
		new Title[256];
		formatex(Title,sizeof(Title)-1,"\yWarcraft3: Frozen Throne \d2022^nPage:");
		
		Menu = menu_create(Title, "_MENU_GameMainMenu");
		
		
		new szItem1[256];
		formatex(szItem1,sizeof(szItem1)-1,"Account Information");
		menu_additem(Menu, szItem1, "1", 0); 
		
		new szItem2[256];
		formatex(szItem2,sizeof(szItem2)-1,"Change Team");
		menu_additem(Menu, szItem2, "2", 0); 
		
		new szItem3[256];
		formatex(szItem3,sizeof(szItem3)-1,"Change Race");
		menu_additem(Menu, szItem3, "3", 0); 
		
		new szItem4[256];
		formatex(szItem4,sizeof(szItem4)-1,"Race Information");
		menu_additem(Menu, szItem4, "4", 0); 
		
		new szItem5[256];
		formatex(szItem5,sizeof(szItem5)-1,"Race Reconfiguration");
		menu_additem(Menu, szItem5, "5", 0); 
		
		
		new szItem6[256];
		formatex(szItem6,sizeof(szItem6)-1,"Shop");
		menu_additem(Menu, szItem6, "6", 0); 
		
		new szItem7[256];
		formatex(szItem7,sizeof(szItem7)-1,"Shop Information");
		menu_additem(Menu, szItem7, "7", 0); 
		
		
		new szItem8[256];
		formatex(szItem8,sizeof(szItem8)-1,"%s", g_bExchange[id] ? "Exchange Gold: \yEnabled" : "Exchange Gold: \rDisabled");
		menu_additem(Menu, szItem8, "8", 0); 
		
		
		new szItem9[256];
		formatex(szItem9,sizeof(szItem9)-1,"Show Players Information");
		menu_additem(Menu, szItem9, "9", 0); 
		
	
		new szItem10[256];
		formatex(szItem10,sizeof(szItem10)-1,"Show Help Information");
		menu_additem(Menu, szItem10, "10", 0); 
		
		new szItem11[256];
		formatex(szItem11,sizeof(szItem11)-1,"Add Level from Bank:\y %d", get_user_levelbank(id));
		menu_additem(Menu, szItem11, "11", 0); 

		if (get_user_flags(id) & ADMIN_CVAR)
		{
			new szItem12[256];
			formatex(szItem12,sizeof(szItem12)-1,"WC3 Admin Menu");
			menu_additem(Menu, szItem12, "12", 0);
				
			menu_setprop(Menu, MPROP_NUMBER_COLOR, "\y") 
			menu_setprop(Menu, MPROP_EXIT, MEXIT_ALL);
			menu_display(id, Menu, 0);
		}
	}
}

public _MENU_GameMainMenu(id, menu, item) 
{
	
	if(item == MENU_EXIT) 
	{
		menu_destroy(menu);
		return PLUGIN_HANDLED;
	}
	new Data[6], Name[64];
	new Access, CallBack;
	menu_item_getinfo(menu, item, Access, Data,5, Name, 63, CallBack);
	new Key = str_to_num(Data);
	switch(Key)
	{
		case 1: MOTD_Account( id );
	
		case 2:
		{
			bChooseTeamOverrideActive[id] = false;
			client_cmd(id, "chooseteam");
		}
		
		case 3: WC3_ChangeRaceStart( id );
		
		case 4: MOTD_RaceInfo( id );
		
		case 5:
		{
			if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 )
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
		
		case 6: MENU_Shop( id );
		
		case 7: MOTD_ShopInfo( id );
		
		case 8: Exchange_Think(id);
		
		case 9: MOTD_PlayersInfo( id );
		
		case 10: MOTD_TutorialInfo( id );

		case 11: LevelBank( id );

		case 12:
		{
			if (~get_user_flags(id) & ADMIN_CVAR)
			{
				client_print_color(id, print_team_default, "^4%s ^3You don't have access to this menu.", GAME_NAME);
				return PLUGIN_HANDLED;
			}
			ToggleAdminMenu(id);
		}
		default: return PLUGIN_HANDLED;
	}
	
	menu_destroy(menu);
	return PLUGIN_HANDLED;
}


public MENU_Shop(id) 
{ 
	if(is_user_connected(id)) 
	{
		new Title[256];
		formatex(Title,sizeof(Title)-1,"\yShop \RCo st $^nPage:");
		
		Menu = menu_create(Title, "_MENU_Shop");
		
		new i, szItem[256], szKey[256];
		
		for ( i = 0; i < MAX_SHOPMENU_ITEMS; i++ ) 
		{ 
				
			if(ITEM_CanBuyCheckSilent( id, i ))
			formatex(szItem,sizeof(szItem)-1,"%s \R%d $",Lang_ItemDatabase[i][0],ITEM_Cost( id, i ));
			else
			formatex(szItem,sizeof(szItem)-1,"\d%s \R%d $",Lang_ItemDatabase[i][0],ITEM_Cost( id, i )); 
				
			num_to_str(i+1,szKey,255);
			
			menu_additem(Menu, szItem, szKey, 0); 
		}
  
		menu_setprop(Menu, MPROP_NUMBER_COLOR, "\y") 
		menu_setprop(Menu, MPROP_EXIT, MEXIT_ALL);
		menu_display(id, Menu, 0);
	}
}

public _MENU_Shop(id, menu, item) 
{
	
	if(item == MENU_EXIT) 
	{
		menu_destroy(menu);
		return PLUGIN_HANDLED;
	}
	new Data[6], Name[64];
	new Access, CallBack;
	menu_item_getinfo(menu, item, Access, Data,5, Name, 63, CallBack);
	new Key = str_to_num(Data);
	switch(Key)
	{
		case 1: ITEM_Buy( id, 0 );
		case 2: ITEM_Buy( id, 1 );
		case 3: ITEM_Buy( id, 2 );
		case 4: ITEM_Buy( id, 3 );
		case 5: ITEM_Buy( id, 4 );
		case 6: ITEM_Buy( id, 5 );
		case 7: ITEM_Buy( id, 6 );	
		case 8: ITEM_Buy( id, 7 );
		case 9: ITEM_Buy( id, 8 );	
		case 10: ITEM_Buy( id, 9 );	
		case 11: ITEM_Buy( id, 10 );	
		case 12: ITEM_Buy( id, 11 );	
		case 13: ITEM_Buy( id, 12 );	
		case 14: ITEM_Buy( id, 13 );
		case 15: ITEM_Buy( id, 14 );	
		case 16: ITEM_Buy( id, 15 );
		case 17: ITEM_Buy( id, 16 );
		case 18: ITEM_Buy( id, 17 );
		case 19: ITEM_Buy( id, 18 );
			
		default: return PLUGIN_HANDLED;
	}
	
	menu_destroy(menu);
	return PLUGIN_HANDLED;
}


// Function will create and display the changerace menu 

public MENU_ChangeRace( id, iRaceXP[MAX_RACES],iRaceLVL[MAX_RACES], pos )
{
	if(pos < 0)
	{
		g_menuPosition[id] = 0
		return
	}
	new szEXP[256], szLVL[1024];
	
	static start
	start = pos * 8
	
	static maxitem
	maxitem = MAX_RACES
	
	if(start >= maxitem)
		start = pos = g_menuPosition[id]
	
	static racemenu[65536], len
	len = formatex(racemenu, 65535, "\yChange Race");
	
	static end
	end = start + 8
	
	if(end > maxitem)
		end = maxitem
	
	static keys
	keys = MENU_KEY_0
	
	static a, b
	b = 0
	
	len += formatex(racemenu[len], 65535 - len, "\y\RExpe r ience               \RLeve l^nPage: %d/2^n^n", pos + 1  );
	//len += formatex(racemenu[len], 65535 - len, "\y\RExpe r ience               \RLeve l^n^n");	
	
	for(a = start; a < end; ++a)
	{
		num_to_str( iRaceXP[a], szEXP, 255 );
		formatex(szLVL, charsmax(szLVL), "%d",iRaceLVL[a]); 
		
	/*
		// Add a text somewhere in menu 
		if ( a == 4 )
		{
			len += formatex(racemenu[len], 65535 - len, "\ySelect Hero");
		}
		if ( a == 12 )
		{
			len += formatex(racemenu[len], 65535 - len, "\ySelect Hero");
		}
	*/
		
		// Current race
		if ( a == p_data[id][P_RACE] - 1 )
		{
			keys |= (1<<b)
			
			len += formatex(racemenu[len], 65535 - len, "\y%d. \d%s \R%s               \R%s^n", ++b, Lang_RaceName[a+1], szEXP, szLVL);
		
		}
		
		// Next race 
		else if ( a == p_data[id][P_CHANGERACE] - 1 )
		{
			keys |= (1<<b)
			
			len += formatex(racemenu[len], 65535 - len, "\y%d. %s \R%s               \R%s^n", ++b, Lang_RaceName[a+1], szEXP, szLVL);
		
		}
		
		// All other cases
		else
		{
			new bool:bAllowRace = true;
			
			// Check to see if the user can choose this race (are there too many of this race?)
			if ( bAllowRace )
			{
				keys |= (1<<b)
				
				len += formatex(racemenu[len], 65535 - len, "\y%d.\w %s \y\R%s               \R%s^n", ++b, Lang_RaceName[a+1], szEXP, szLVL);
			
			}
			
			// If not, display the race, but don't give them a key to press
			else
			{
				len += formatex(racemenu[len], 65535 - len, "\y%d. \d%s \R%s               \R%s^n", ++b, Lang_RaceName[a+1], szEXP, szLVL);
			}
		}
	}
	
	if(end != maxitem) 
	{
		formatex(racemenu[len], 65535 - len, "^n\y9.\w Next Page^n\y0.\w %s", pos ? "Previous Page" : "Exit")
		keys |= MENU_KEY_9
	}
	else	
		formatex(racemenu[len], 65535 - len, "^n\y0.\w %s", pos ? "Previous Page" : "Exit")
		
	
	show_menu(id, keys, racemenu, -1, "ChangeRace")
	
	return
}


public _MENU_ChangeRace(id, key) 
{	
	switch(key) 
	{
		case 8: 
		{
			// Make sure the user is on a team!
			if ( SHARED_IsOnTeam( id ) )
			{
				g_menuPosition[id]++
				
				DB_GetAllXP( id );
				
			}
			
			else
			{
				client_print( id, print_center, "Please join a team before selecting a race !" );
			}
		}
		case 9: 
		{
			// Make sure the user is on a team!
			if ( SHARED_IsOnTeam( id ) )
			{
				g_menuPosition[id]--
				
				DB_GetAllXP( id );
				
			}
			
			else
			{
				client_print( id, print_center, "Please join a team before selecting a race !" );
			}
		}

		default: 
		{
			
			// User pressed 0 (cancel)
			if ( MAX_RACES < 9 && key - 1 == MAX_RACES )
			{
				return PLUGIN_HANDLED;
			}
			
			// Save the current race data before we change
			DB_SaveXP( id, false );
			
			new iRace
			iRace = g_menuPosition[id] * 8 + key + 1;
		
		/*		
			if(iRace == RACE_CRYSTAL || iRace == RACE_DRUID) 
			{ 
				if(!is_user_vip(id)) 
				{   
					ColorChat( id,"!t%s !gThis race is only for!t VIP!g.",GAME_NAME);
					return PLUGIN_HANDLED; 
				}
			}
		*/
		
 		
 
			// User currently has a race
			if ( p_data[id][P_RACE] != 0 )
			{
				
				// Change the user's race at the start of next round
				if ( iRace != p_data[id][P_RACE] )
				{
					
					// Special message for csdm
					if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 )
					{
						client_print( id, print_center, "Your race will be changed when you respawn." );
						client_print_color( id, print_team_default, "^4%s ^3Your race will be changed when you respawn.", GAME_NAME );
					}	
					else
					{
						client_print( id, print_center, "Your race will be changed next round.");
						client_print_color( id, print_team_default, "^4%s ^3Your race will be changed next round.", GAME_NAME );
					}
					
					p_data[id][P_CHANGERACE] = iRace;
				}
				
				// Do nothing
				else
				{
					p_data[id][P_CHANGERACE] = 0;
				}
			}
			
			// User doesn't have a race so give it to him!!!
			else
			{
				WC3_SetRace( id, iRace );
			}
			return PLUGIN_HANDLED;
		}
	}
	return PLUGIN_HANDLED
}


public MENU_ReplaceItem(id) 
{ 
		new Title[256];
		formatex(Title,sizeof(Title)-1,"\yReplace Item");
		
		Menu = menu_create(Title, "_MENU_ReplaceItem");
		
		new szItem1[256];
		formatex(szItem1,sizeof(szItem1)-1,"%s",Lang_ItemDatabase[g_iShopMenuItems[id][ITEM_SLOT_ONE]][ITEM_NAME_LONG]);
		menu_additem(Menu, szItem1, "1", 0); 
		
		new szItem2[256];
		formatex(szItem2,sizeof(szItem2)-1,"%s",Lang_ItemDatabase[g_iShopMenuItems[id][ITEM_SLOT_TWO]][ITEM_NAME_LONG]);
		menu_additem(Menu, szItem2, "2", 0); 
		
		menu_setprop(Menu, MPROP_NUMBER_COLOR, "\y") 
		menu_setprop(Menu, MPROP_EXIT, MEXIT_ALL);
		menu_display(id, Menu, 0);
	
}

public _MENU_ReplaceItem(id, menu, item) 
{
	
	if(item == MENU_EXIT) 
	{
		menu_destroy(menu);
		return PLUGIN_HANDLED;
	}
	new Data[6], Name[64];
	new Access, CallBack;
	menu_item_getinfo(menu, item, Access, Data,5, Name, 63, CallBack);
	new Key = str_to_num(Data);
	switch(Key)
	{
		case 1: 
		{
			ITEM_Remove( id, ITEM_SLOT_ONE );
			ITEM_Buy( id, g_iFutureItem[id] );
			
		}
		
		case 2:  
		{
			ITEM_Remove( id, ITEM_SLOT_TWO );
			ITEM_Buy( id, g_iFutureItem[id] );
		}
			
		default: return PLUGIN_HANDLED;
	}
	
	menu_destroy(menu);
	return PLUGIN_HANDLED;
}

		
public MENU_SelectSkills( id )
{
	if ( p_data[id][P_RACE] == 0 )
	{
		WC3_StatusText( id, TXT_TOP_CENTER, "You need to select race before select skills !" );

		return;
	}
	else if ( p_data[id][P_RACE] == RACE_CHAMELEON && get_pcvar_num( CVAR_wc3_cham_random ) && !Polymorph_Player[id] )
	{
		CHAM_ConfigureSkills( id );				// Do not choose if chameleon is random 

		return;
	}

	new iSkillsUsed = SM_TotalSkillPointsUsed( id );
	if ( iSkillsUsed >= p_data[id][P_LEVEL] )
	{
		WC3_StatusText( id, TXT_TOP_CENTER, "No skill points left !" );

		return;
	}

	new Title[256];
	formatex(Title,sizeof(Title)-1,"\ySelect Skills");
		
	Menu = menu_create(Title, "_MENU_SelectSkills");
	
	new szSkillSelect[256], szKey[256];
	
	new iSkillCounter = 0, iSkillID = 0, iSkillLevel;

	iSkillID = SM_GetSkillByPos( id, iSkillCounter );

	while ( iSkillID != -1 )
	{
		iSkillLevel = SM_GetSkillLevel( id, iSkillID, 4 );

		if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_TRAINABLE )
		{
		
			if ( iSkillLevel >= MAX_SKILL_LEVEL || p_data[id][P_LEVEL] <= 2 * iSkillLevel )
			{
		
				formatex(szSkillSelect,sizeof(szSkillSelect)-1,"\d%s (Level %d)", Lang_SkillUltimateDatabase[iSkillID][0], iSkillLevel);	
			}
			else 
			{
				formatex(szSkillSelect,sizeof(szSkillSelect)-1,"\w%s (Level %d)", Lang_SkillUltimateDatabase[iSkillID][0], iSkillLevel);
			}
			
			num_to_str(iSkillCounter+1,szKey,255);
			
			menu_additem(Menu, szSkillSelect, szKey, 0);

		}
		
		else if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_ULTIMATE )
		{
		
			if ( iSkillLevel >= MAX_ULTIMATE_LEVEL || p_data[id][P_LEVEL] <= 5 )
			{
		
				formatex(szSkillSelect,sizeof(szSkillSelect)-1,"\dUltimate: %s", Lang_SkillUltimateDatabase[iSkillID][0]);	
			}
			else 
			{
				formatex(szSkillSelect,sizeof(szSkillSelect)-1,"\wUltimate: %s", Lang_SkillUltimateDatabase[iSkillID][0]);
			}
			
			num_to_str(iSkillCounter+1,szKey,255);
			
			menu_additem(Menu, szSkillSelect, szKey, 0);
			
		}

		iSkillCounter++;
		iSkillID = SM_GetSkillByPos( id, iSkillCounter );
	}

	menu_setprop(Menu, MPROP_NUMBER_COLOR, "\y") 
	menu_setprop(Menu, MPROP_EXIT, MEXIT_ALL);
	menu_display(id, Menu, 0);

	return;
}

public _MENU_SelectSkills(id, menu, item) 
{
	
	if(item == MENU_EXIT) 
	{
		menu_destroy(menu);
		return PLUGIN_HANDLED;
	}
	
	new Data[6], Name[64];
	new Access, CallBack;
	menu_item_getinfo(menu, item, Access, Data,5, Name, 63, CallBack);
	new Key = str_to_num(Data);
	switch(Key)
	{
		case 1: _MENU_SelectSkills_Think( id, SKILL_POS_1 );
		case 2: _MENU_SelectSkills_Think( id, SKILL_POS_2 );
		case 3: _MENU_SelectSkills_Think( id, SKILL_POS_3 );
		case 4: _MENU_SelectSkills_Think( id, SKILL_POS_4 );
			
		default: return PLUGIN_HANDLED;
	}
	
	menu_destroy(menu);
	return PLUGIN_HANDLED;
}

public _MENU_SelectSkills_Think( id, iKey )
{
	new iSkillID = SM_GetSkillByPos( id, iKey );
	SM_SetSkill( id, iSkillID );
	
	new iSkillsUsed = SM_TotalSkillPointsUsed( id );
	
	if ( iSkillsUsed < p_data[id][P_LEVEL] )
	{
		MENU_SelectSkills( id );
	}
	else
	{
		WC3_ShowBar( id );
	}

}



// Display the current race information 

public MOTD_RaceInfo( id )
{
	static iSkillID, bool:bHeaderShown;
	new szTitle[128], szContent[2048];
	new iPos = 0;
		
	switch(SELECT_DESIGN) 
	{
		case 1: iPos = format(szContent, 2047, DESIGN1_STYLE)
		case 2: iPos = format(szContent, 2047, DESIGN2_STYLE)
		case 3: iPos = format(szContent, 2047, DESIGN3_STYLE)
		case 4: iPos = format(szContent, 2047, DESIGN4_STYLE)
		case 5: iPos = format(szContent, 2047, DESIGN5_STYLE)
		case 6: iPos = format(szContent, 2047, DESIGN6_STYLE)
		case 7: iPos = format(szContent, 2047, DESIGN7_STYLE)
		case 8: iPos = format(szContent, 2047, DESIGN8_STYLE)
		case 9: iPos = format(szContent, 2047, DESIGN9_STYLE)
		case 10: iPos = format(szContent, 2047, DESIGN10_STYLE)
		case 11: iPos = format(szContent, 2047, DESIGN11_STYLE)
		case 12: iPos = format(szContent, 2047, DESIGN12_STYLE)
		case 13: iPos = format(szContent, 2047, DESIGN13_STYLE)
		default: iPos = format(szContent, 2047, DEFAULT_STYLE)
	}
			
	if ( SM_IsValidRace( p_data[id][P_RACE] ) )
	{
		formatex( szTitle, 127, "%s Information", Lang_RaceName[p_data[id][P_RACE]]);
	}
	else
	{
		formatex( szTitle, 127, "No Race" );
		iPos += format(szContent[iPos], 2047 - iPos, "<body><center><table border=0 width=75%%><th>You have no race please use /changerace")
	}

	bHeaderShown = false;
	iSkillID = SM_GetSkillOfType( id, SKILL_TYPE_TRAINABLE );
	while ( iSkillID != -1 )
	{
		if ( !bHeaderShown )
		{
			iPos += format(szContent[iPos], 2047 - iPos, "<body><center><table border=0 width=75%%><th>Type<th>Name<th>Description")
			bHeaderShown = true;
		}

		iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Skill<td>%s<td>%s", Lang_SkillUltimateDatabase[iSkillID][0], Lang_SkillUltimateDatabase[iSkillID][1])

		iSkillID = SM_GetSkillOfType( id, SKILL_TYPE_TRAINABLE, iSkillID + 1 );
	}

	iSkillID = SM_GetSkillOfType( id, SKILL_TYPE_ULTIMATE );
	while ( iSkillID != -1 )
	{
	
		iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Ultimate<td>%s<td>%s", Lang_SkillUltimateDatabase[iSkillID][0], Lang_SkillUltimateDatabase[iSkillID][1])

		iSkillID = SM_GetSkillOfType( id, SKILL_TYPE_ULTIMATE, iSkillID + 1 );
	}
	
	iSkillID = SM_GetSkillOfType( id, SKILL_TYPE_PASSIVE );
	while ( iSkillID != -1 )
	{
		
		iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Passive<td>%s<td>%s", Lang_SkillUltimateDatabase[iSkillID][0], Lang_SkillUltimateDatabase[iSkillID][1])

		iSkillID = SM_GetSkillOfType( id, SKILL_TYPE_PASSIVE, iSkillID + 1 );
	}

	show_motd( id, szContent, szTitle );

	return;
}

// Display the all players information

public MOTD_PlayersInfo(id)
{
	new szContent[2048], szName[64], szPlayersName[64];
	new iPos = 0;
		
	get_user_name(id, szName, 63);
		
	switch(SELECT_DESIGN) 
	{
		case 1: iPos = format(szContent, 2047, DESIGN1_STYLE)
		case 2: iPos = format(szContent, 2047, DESIGN2_STYLE)
		case 3: iPos = format(szContent, 2047, DESIGN3_STYLE)
		case 4: iPos = format(szContent, 2047, DESIGN4_STYLE)
		case 5: iPos = format(szContent, 2047, DESIGN5_STYLE)
		case 6: iPos = format(szContent, 2047, DESIGN6_STYLE)
		case 7: iPos = format(szContent, 2047, DESIGN7_STYLE)
		case 8: iPos = format(szContent, 2047, DESIGN8_STYLE)
		case 9: iPos = format(szContent, 2047, DESIGN9_STYLE)
		case 10: iPos = format(szContent, 2047, DESIGN10_STYLE)
		case 11: iPos = format(szContent, 2047, DESIGN11_STYLE)
		case 12: iPos = format(szContent, 2047, DESIGN12_STYLE)
		case 13: iPos = format(szContent, 2047, DESIGN13_STYLE)
		default: iPos = format(szContent, 2047, DEFAULT_STYLE)
	}
		
	iPos += format(szContent[iPos], 2047 - iPos, "<body><center><table border=0 width=75%%><th>Name<th>Account<th>Race<th>Level<th>Gold")
		
	for(new i = 1; i < get_maxplayers(); i++)
	{	
		if(is_user_connected(i))
		{
			get_user_name(i, szPlayersName, 63);
				
			if(equal(szName, szPlayersName)) 
				iPos += format(szContent[iPos], 2047 - iPos, "<tr id=c><td>%s<td>%s<td>%s<td>%d<td>%i", szPlayersName, is_user_vip(i) ? "VIP" : " ", Lang_RaceName[p_data[i][P_RACE]], p_data[i][P_LEVEL], get_user_gold(i))
			else 
				iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>%s<td>%s<td>%s<td>%d<td>%i", szPlayersName, is_user_vip(i) ? "VIP" : " ", Lang_RaceName[p_data[i][P_RACE]], p_data[i][P_LEVEL], get_user_gold(i))
				
		}		
	}
		
	show_motd(id, szContent, "Players Information");
}	

// Display the shop information

public MOTD_ShopInfo(id)
{
	new szContent[2048];
	new iPos = 0;
		
	switch(SELECT_DESIGN) 
	{
		case 1: iPos = format(szContent, 2047, DESIGN1_STYLE)
		case 2: iPos = format(szContent, 2047, DESIGN2_STYLE)
		case 3: iPos = format(szContent, 2047, DESIGN3_STYLE)	
		case 4: iPos = format(szContent, 2047, DESIGN4_STYLE)	
		case 5: iPos = format(szContent, 2047, DESIGN5_STYLE)	
		case 6: iPos = format(szContent, 2047, DESIGN6_STYLE)	
		case 7: iPos = format(szContent, 2047, DESIGN7_STYLE)	
		case 8: iPos = format(szContent, 2047, DESIGN8_STYLE)	
		case 9: iPos = format(szContent, 2047, DESIGN9_STYLE)
		case 10: iPos = format(szContent, 2047, DESIGN10_STYLE)
		case 11: iPos = format(szContent, 2047, DESIGN11_STYLE)
		case 12: iPos = format(szContent, 2047, DESIGN12_STYLE)
		case 13: iPos = format(szContent, 2047, DESIGN13_STYLE)	
		default: iPos = format(szContent, 2047, DEFAULT_STYLE)
	}
		
	iPos += format(szContent[iPos], 2047 - iPos, "<body><center><table border=0 width=75%%><th>Name<th>Short<th>Description")
		
	for(new i = 0; i < MAX_SHOPMENU_ITEMS; i++)
	{	
		iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>%s<td>%s<td>%s", Lang_ItemDatabase[i][0], Lang_ItemDatabase[i][1], Lang_ItemDatabase[i][2])		
	}
		
	show_motd(id, szContent, "Shop Information");	
}	

// Display user account information 

public MOTD_Account(id)
{
	new szContent[2048];
	new iPos = 0;
		
	switch(SELECT_DESIGN) 
	{
		case 1: iPos = format(szContent, 2047, DESIGN1_STYLE)
		case 2: iPos = format(szContent, 2047, DESIGN2_STYLE)
		case 3: iPos = format(szContent, 2047, DESIGN3_STYLE)	
		case 4: iPos = format(szContent, 2047, DESIGN4_STYLE)	
		case 5: iPos = format(szContent, 2047, DESIGN5_STYLE)	
		case 6: iPos = format(szContent, 2047, DESIGN6_STYLE)	
		case 7: iPos = format(szContent, 2047, DESIGN7_STYLE)	
		case 8: iPos = format(szContent, 2047, DESIGN8_STYLE)	
		case 9: iPos = format(szContent, 2047, DESIGN9_STYLE)
		case 10: iPos = format(szContent, 2047, DESIGN10_STYLE)
		case 11: iPos = format(szContent, 2047, DESIGN11_STYLE)
		case 12: iPos = format(szContent, 2047, DESIGN12_STYLE)
		case 13: iPos = format(szContent, 2047, DESIGN13_STYLE)	
		default: iPos = format(szContent, 2047, DEFAULT_STYLE)
	}
		
		
	new szName[32];
	get_user_name( id, szName, 31 );
		
	new iGold = 0; 
	iGold = get_user_gold(id);
		
	new iGold_Value = 0;
	iGold_Value = iGold * VALUE_GOLD;
		
	new szLevel[256], iPosLevel = 0;
	if(p_data[id][P_LEVEL]<MAX_LEVELS)
	{
		iPosLevel += formatex( szLevel[iPosLevel], 255, "%d/%d", p_data[id][P_LEVEL], MAX_LEVELS );
	}
	else
	{
		iPosLevel += formatex( szLevel[iPosLevel], 255, "%d", p_data[id][P_LEVEL]);
	}
		
		
	new szXP[256], iPosXP = 0;
	if(p_data[id][P_LEVEL]<MAX_LEVELS)
	{
		iPosXP += formatex( szXP[iPosXP], 255, "%d/%d", p_data[id][P_XP], XP_GetByLevel( p_data[id][P_LEVEL]+1) );
	}
	else
	{
		iPosXP += formatex( szXP[iPosXP], 255, "%d", p_data[id][P_XP]);
	}
		
		
	new szItems[256], iPosItems = 0;
		
	new bool:ItemSlotOne = false;
	
	if( g_iShopMenuItems[id][ITEM_SLOT_ONE] <= ITEM_NONE && g_iShopMenuItems[id][ITEM_SLOT_TWO] <= ITEM_NONE)
	{
		iPosItems += formatex( szItems[iPosItems], 255, "None" );
	}
	else 
	{
		if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] > ITEM_NONE )
		{
			iPosItems += formatex( szItems[iPosItems], 255, "%s", Lang_ItemDatabase[g_iShopMenuItems[id][ITEM_SLOT_ONE]][ITEM_NAME_SHORT] );
			ItemSlotOne = true;
		}
			
		if ( g_iShopMenuItems[id][ITEM_SLOT_TWO] > ITEM_NONE )
		{
			
			if ( ItemSlotOne )
			{
				iPosItems += formatex( szItems[iPosItems], 255, ", %s", Lang_ItemDatabase[g_iShopMenuItems[id][ITEM_SLOT_TWO]][ITEM_NAME_SHORT] );
			}
			else
			{
				iPosItems += formatex( szItems[iPosItems], 255, "%s", Lang_ItemDatabase[g_iShopMenuItems[id][ITEM_SLOT_TWO]][ITEM_NAME_SHORT] );
			}
				
		}
	}	
		
		
		
		
	iPos += format(szContent[iPos], 2047 - iPos, "<body><center><table border=0 width=75%%><th>Account<th>Information")
		
	iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Name<td>%s", szName)
	iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Account<td>%s", is_user_vip(id) ? "VIP" : "Player")
	iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Gold<td>%i",iGold)
	iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Gold Value<td>%i $", iGold_Value)
	iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Race<td>%s", Lang_RaceName[p_data[id][P_RACE]])
	iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Level<td>%s", szLevel)
	iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>XP<td>%s", szXP)
	iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>Items<td>%s", szItems)
		
		
	show_motd(id, szContent, "Account Information");	
}	

// Display the tutorial info 

public MOTD_TutorialInfo(id)
{
	new szContent[2048];
	new iPos = 0;
		
	switch(SELECT_DESIGN) 
	{
		case 1: iPos = format(szContent, 2047, DESIGN1_STYLE)
		case 2: iPos = format(szContent, 2047, DESIGN2_STYLE)
		case 3: iPos = format(szContent, 2047, DESIGN3_STYLE)	
		case 4: iPos = format(szContent, 2047, DESIGN4_STYLE)	
		case 5: iPos = format(szContent, 2047, DESIGN5_STYLE)	
		case 6: iPos = format(szContent, 2047, DESIGN6_STYLE)	
		case 7: iPos = format(szContent, 2047, DESIGN7_STYLE)	
		case 8: iPos = format(szContent, 2047, DESIGN8_STYLE)	
		case 9: iPos = format(szContent, 2047, DESIGN9_STYLE)
		case 10: iPos = format(szContent, 2047, DESIGN10_STYLE)
		case 11: iPos = format(szContent, 2047, DESIGN11_STYLE)
		case 12: iPos = format(szContent, 2047, DESIGN12_STYLE)
		case 13: iPos = format(szContent, 2047, DESIGN13_STYLE)	
		default: iPos = format(szContent, 2047, DEFAULT_STYLE)
	}
	
	iPos += format(szContent[iPos], 2047 - iPos, "<body><center><table border=0 width=75%%><th>About<th>Description")
		
	for(new i = 0; i < MAX_HELP; i++)
	{	
		iPos += format(szContent[iPos], 2047 - iPos, "<tr><td>%s<td>%s", Lang_TutorialDatabase[i][0], Lang_TutorialDatabase[i][1])		
	}
		
	show_motd(id, szContent, "Help Information");	

}

// Exchange 

public Exchange_Think(id)
{
	if(g_bExchange[id])
	{
		g_bExchange[id] = false;
		client_print( id, print_center, "Exchange has been Disabled." );
		client_print_color( id, print_team_default, "^4%s ^3Exchange has been Disabled.", GAME_NAME );
	}
	else 
	{
		g_bExchange[id] = true;
		client_print( id, print_center, "Exchange has been Enabled." );
		client_print_color( id, print_team_default, "^4%s ^3Exchange has been Enabled.", GAME_NAME );
	}

}


// Level Bank 

public LevelBank(id)
{

	if(p_data[id][P_RACE] == RACE_NONE)
	{
		client_print( id, print_center, "You have no race." );
		client_print_color( id, print_team_default, "^4%s ^3You have no race.", GAME_NAME );
		
		return; 
	}
	
	if(p_data[id][P_LEVEL] >= MAX_LEVELS)
	{
		client_print( id, print_center, "You have max level." );
		client_print_color( id, print_team_default, "^4%s ^3You have max level.", GAME_NAME );
		
		return; 
	
	}
	
	if(get_user_levelbank(id) <= 0)
	{
		client_print( id, print_center, "You have no levels in bank." );
		client_print_color( id, print_team_default, "^4%s ^3You have no levels in bank.", GAME_NAME );
		
		return; 
	
	}
	
	if(get_user_levelbank(id) > 0)
	{
		client_print( id, print_center, "Your level is now increased." );
		client_print_color( id, print_team_default, "^4%s ^3Your level is now increased.", GAME_NAME );
		
		new iXP = XP_GetByLevel( p_data[id][P_LEVEL] + 1 );
		
		ADMIN_SetXP( id, iXP );
		
		set_user_levelbank(id, get_user_levelbank(id) - 1)
		
		return; 
	
	}
	
	
	


}