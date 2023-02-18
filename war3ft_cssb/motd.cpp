// ******************************************************************
// Motd Functions
// ******************************************************************


// ******************************************************************
// MOTD окна описания предметов из магазинов
// ******************************************************************
clMotd::fShowMotdItemsInfo(idUser,iNumItems)
{
	new szNameVersionMod[256],szSiteMod[256];
	formatex(szNameVersionMod, charsmax(szNameVersionMod), "%L %s",LANG_PLAYER,"CLIENT_PRINT_MOD_VERSION",WC3_NAME,WC3_VERSION);
	formatex(szSiteMod, charsmax(szSiteMod), "%L",LANG_PLAYER,"CLIENT_PRINT_AUTHOR_SITE","<a href=^"http://perfect-soft.su^">PERFECT-SOFT.SU</a>");

	new iPos = 0;
	new szItemInfo[256], szItemName[256];
	
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<meta charset=^"utf-8^">");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<link rel=^"stylesheet^" href=^"http://perfect-soft.su/css/cssb.css^" type=^"text/css^">");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</head>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h1>");
	if ( iNumItems == 0 )//shopmenu1
		iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER,"MOTD_TITLE_SHOPMENU");
	if ( iNumItems == 9 )//shopmenu2
		iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER,"MOTD_TITLE_SHOPMENU2");
	if ( iNumItems == 18 )//shopmenu3
		iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER,"MOTD_TITLE_SHOPMENU3");
	if ( iNumItems == 27 )//shopmenu4
		iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h1>");

	for (new i = iNumItems; i < MAX_ITEMS_PAGE + iNumItems; i++ )
	{
		LANG_GetItemInfo(i, idUser, szItemInfo, charsmax(szItemInfo));
		LANG_GetItemName(i, idUser, szItemName, charsmax(szItemName));
		iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<dt>%s</dt><dd>%s</dd>", szItemInfo, szItemName );
	}

	if ( iNumItems == 0 )//shopmenu1
		formatex(szItemInfo, charsmax(szItemInfo), "%L", LANG_PLAYER, "MOTD_TITLE_SHOPMENU" );
	if ( iNumItems == 9 )//shopmenu2
		formatex(szItemInfo, charsmax(szItemInfo), "%L", LANG_PLAYER, "MOTD_TITLE_SHOPMENU2" );
	if ( iNumItems == 18 )//shopmenu3
		formatex(szItemInfo, charsmax(szItemInfo), "%L", LANG_PLAYER, "MOTD_TITLE_SHOPMENU3" );
	if ( iNumItems == 27 )//shopmenu4
		formatex(szItemInfo, charsmax(szItemInfo), "%L", LANG_PLAYER, "MOTD_TITLE_SHOPMENU4" );
	
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<hr>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h2>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szNameVersionMod);
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<br>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szSiteMod);
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h2>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");

	formatex(szTitle, charsmax(szTitle), "%L", LANG_PLAYER, "WAR3HELP_TITLE" );
	show_motd( idUser, szTmpMsg, szTitle );

	menu_Item_Options(idUser);
}

// ******************************************************************
// MOTD окно показывающее кто и за какую расу играет
// ******************************************************************
clMotd::fShowMotdPlayerRaces(idUser)
{
	new iPlayers[32], iNumPlayers;
	get_players( iPlayers, iNumPlayers );

	// Lets find out what races are in use
	new bool:bRaceUsed[MAX_RACES+1] = {false}, iRaceID, iTargetID;
	for (new i = 0; i < iNumPlayers; i++ )
	{
		new iID	= iPlayers[i];
		new iRace	= arrIntData[iID][P_RACE];
		
		bRaceUsed[iRace] = true;
	}
	
	new iPos = 0, iTeam, szTeamColor[2];
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<meta charset=^"utf-8^">");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<link rel=^"stylesheet^" href=^"http://perfect-soft.su/css/cssb.css^" type=^"text/css^">");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</head>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");

	new szTmpName[64], szTeamName[32];
	// Loop through each race
	for ( iRaceID = 1; iRaceID < MAX_RACES + 1; iRaceID++ )
	{
		// Make sure this race was used somewhere!
		if ( bRaceUsed[iRaceID] )
		{
			Lang_GetRaceName ( iRaceID, idUser, szTmpName, charsmax(szTmpName) );
			iPos += formatex( szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<b>%s</b><ul>", szTmpName );

			// Lets show them per team, T, then CT, then Spectators
			for ( iTeam = TEAM_T; iTeam <= TEAM_CT + 1; iTeam++ )
			{
				// Default color
				formatex( szTeamColor, 1, "p" );

				if ( iTeam == TEAM_T )
					formatex( szTeamColor, 1, "t" );
				else if ( iTeam == TEAM_CT )
					formatex( szTeamColor, 1, "c" );
				
				// Loop through all players
				for (new k = 0; k < iNumPlayers; k++ )
				{
					iTargetID = iPlayers[k];
					
					// Make sure the user has this race and is on the proper team
					if (arrIntData[iTargetID][P_RACE] == iRaceID && get_user_team( iTargetID ) == iTeam)
					{
						get_user_name( iTargetID, szTmpName, charsmax(szTmpName) );
						get_user_team( iTargetID, szTeamName, charsmax(szTeamName) );
						
						iPos += formatex( szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<li id='%s'>(%d) %s</li>", szTeamColor, arrIntData[iTargetID][P_LEVEL], szTmpName );

					}
				}//end player loop
			}//end team loop

			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</ul>" );
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");
		}

	}//end race loop


	formatex(szTitle,charsmax(szTitle), "%L", LANG_PLAYER, "PLAYER_SKILLS" );
	show_motd(idUser, szTmpMsg, szTitle );
	
	return;
}

public MOTD_SkillsInfo(idUser)
{
	new szNameVersionMod[256],szSiteMod[256];
	formatex(szNameVersionMod, charsmax(szNameVersionMod), "%L %s",LANG_PLAYER,"CLIENT_PRINT_MOD_VERSION",WC3_NAME,WC3_VERSION);
	formatex(szSiteMod, charsmax(szSiteMod), "%L",LANG_PLAYER,"CLIENT_PRINT_AUTHOR_SITE","<a href=^"http://perfect-soft.su^">PERFECT-SOFT.SU</a>");

	new iSkillID, bool:bHeaderShown;
	new szTmpDesc[256], szSkillName[128], szRaceName[64];
	new iPos = 0;

	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<meta charset=^"utf-8^">");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<link rel=^"stylesheet^" href=^"http://perfect-soft.su/css/cssb.css^" type=^"text/css^">");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</head>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");

	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h1>");
	if (SM_IsValidRace(arrIntData[idUser][P_RACE])) // Если игрок выбрал расу
	{
		Lang_GetRaceName( arrIntData[idUser][P_RACE], idUser, szRaceName, 63 );
		iPos += formatex( szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s", szRaceName);
	}
	else // Не выбрана раса
	{
		iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER,"WC3_NO_RACE_SELECT");
	}
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h1>");


	// Скилы 1, 2, 3
	bHeaderShown = false;
	iSkillID = SM_GetSkillOfType( idUser, SKILL_TYPE_TRAINABLE );

	while ( iSkillID != -1 )
	{
		if (!bHeaderShown)
		{
			iPos += formatex( szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h3>%L</h3>", LANG_PLAYER, "WORD_TRAINABLE_SKILLS" );

			bHeaderShown = true;
		}

		LANG_GetSkillName( iSkillID, idUser, szSkillName, charsmax(szSkillName), 2 )
		LANG_GetSkillInfo( iSkillID, idUser, szTmpDesc, charsmax(szTmpDesc) );

		iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<dt>%s</dt><dd>%s</dd>", szSkillName, szTmpDesc );

		iSkillID = SM_GetSkillOfType( idUser, SKILL_TYPE_TRAINABLE, iSkillID + 1 );
	}

	// Супер навык - ultimate
	bHeaderShown = false;
	iSkillID = SM_GetSkillOfType( idUser, SKILL_TYPE_ULTIMATE );
	while ( iSkillID != -1 )
	{
		if ( !bHeaderShown )
		{
			iPos += formatex( szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h3>%L</h3>", LANG_PLAYER, "WORD_ULTIMATE" );

			bHeaderShown = true;
		}

		LANG_GetSkillName( iSkillID, idUser, szSkillName, charsmax(szSkillName), 3 )
		LANG_GetSkillInfo( iSkillID, idUser, szTmpDesc, charsmax(szTmpDesc) );

		iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<dt>%s</dt><dd>%s</dd>", szSkillName, szTmpDesc );

		iSkillID = SM_GetSkillOfType( idUser, SKILL_TYPE_ULTIMATE, iSkillID + 1 );
	}

	// Пассивный навык - ability
	bHeaderShown = false;
	iSkillID = SM_GetSkillOfType( idUser, SKILL_TYPE_PASSIVE );
	while ( iSkillID != -1 )
	{
		if ( !bHeaderShown )
		{
			iPos += formatex( szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h3>%L</h3>", LANG_PLAYER, "WORD_HERO_ABILITY" );

			bHeaderShown = true;
		}

		LANG_GetSkillName( iSkillID, idUser, szSkillName, charsmax(szSkillName), 4 )
		LANG_GetSkillInfo( iSkillID, idUser, szTmpDesc, charsmax(szTmpDesc) );

		iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<dt>%s</dt><dd>%s</dd>", szSkillName, szTmpDesc );

		iSkillID = SM_GetSkillOfType( idUser, SKILL_TYPE_PASSIVE, iSkillID + 1 );
	}


	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<hr>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h2>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szNameVersionMod);
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<br>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szSiteMod);
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h2>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
	iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");

	formatex(szTitle, charsmax(szTitle), "%L", LANG_PLAYER, "WAR3HELP_TITLE" );
	show_motd( idUser, szTmpMsg, szTitle );

	
	return;
}

// ******************************************************************
// Меню
// ******************************************************************
clMotd::fShowMenuHelp(idUser, iPage = 0)
{
	new idMenu,szNumber[64],szMenuData[256];
	
	//Название главного меню
	formatex(szMenuData, charsmax(szMenuData), "\y%L", LANG_PLAYER, "MOTD_MENU_ID_HELP");
	idMenu = menu_create(szMenuData, "_Callback_MENU_Help");

	new szNameItemMenu[256];
	formatex(szNumber, charsmax(szNumber), "%d", enItem:enBaseCmd);
	formatex(szNameItemMenu, charsmax(szNameItemMenu), "%L",LANG_PLAYER,"MOTD_ID_ITEM_MOD");
	menu_additem(idMenu,szNameItemMenu,szNumber,0,-1);

	formatex(szNumber, charsmax(szNumber), "%d", enItem:enSecondaryCmd);
	formatex(szNameItemMenu, charsmax(szNameItemMenu), "%L",LANG_PLAYER,"MOTD_ID_ITEM_MOD_2");
	menu_additem(idMenu,szNameItemMenu,szNumber,0,-1);

	formatex(szNumber, charsmax(szNumber), "%d", enItem:enBindCmd);
	formatex(szNameItemMenu, charsmax(szNameItemMenu), "%L",LANG_PLAYER,"MOTD_ID_ITEM_MOD_3");
	menu_additem(idMenu,szNameItemMenu,szNumber,0,-1);

	formatex(szNumber, charsmax(szNumber), "%d", enItem:enShop_1);
	formatex(szNameItemMenu, charsmax(szNameItemMenu), "%L \y^"%L^"",LANG_PLAYER,"MOTD_ID_ITEM_SHOPMENU",LANG_PLAYER,"MOTD_TITLE_SHOPMENU");
	menu_additem(idMenu,szNameItemMenu,szNumber,0,-1);

	formatex(szNumber, charsmax(szNumber), "%d", enItem:enShop_2);
	formatex(szNameItemMenu, charsmax(szNameItemMenu), "%L \y^"%L^"",LANG_PLAYER,"MOTD_ID_ITEM_SHOPMENU",LANG_PLAYER,"MOTD_TITLE_SHOPMENU2");
	menu_additem(idMenu,szNameItemMenu,szNumber,0,-1);

	formatex(szNumber, charsmax(szNumber), "%d", enItem:enShop_3);
	formatex(szNameItemMenu, charsmax(szNameItemMenu), "%L \y^"%L^"",LANG_PLAYER,"MOTD_ID_ITEM_SHOPMENU",LANG_PLAYER,"MOTD_TITLE_SHOPMENU3");
	menu_additem(idMenu,szNameItemMenu,szNumber,0,-1);

	formatex(szNumber, charsmax(szNumber), "%d", enItem:enShop_4);
	formatex(szNameItemMenu, charsmax(szNameItemMenu), "%L \y^"%L^"",LANG_PLAYER,"MOTD_ID_ITEM_SHOPMENU",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4");
	menu_additem(idMenu,szNameItemMenu,szNumber,0,-1);
	
	// Если нет предметов в меню
	if (menu_items(idMenu) <= 0)
	{
		menu_destroy(idMenu);
		return;
	}
			
	//Пункты меню (назад - следующий - выход)
	formatex(szMenuData, charsmax(szMenuData), "\w%L", LANG_PLAYER, "WC3_MENU_BACK");
	menu_setprop(idMenu, MPROP_BACKNAME, szMenuData);
	formatex(szMenuData, charsmax(szMenuData), "\w%L", LANG_PLAYER, "WC3_MENU_NEXT");
	menu_setprop(idMenu, MPROP_NEXTNAME, szMenuData);
	formatex(szMenuData, charsmax(szMenuData), "\r%L", LANG_PLAYER, "WC3_MENU_EXIT");
	menu_setprop(idMenu, MPROP_EXITNAME, szMenuData);
	
	menu_setprop(idMenu, MPROP_NUMBER_COLOR, "\y");
	menu_display(idUser, idMenu, iPage);
}

//Функция выбора пунктов в под меню Добавления предметов
public _Callback_MENU_Help(idUser, idMenu, idItem)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

	if (idItem == MENU_EXIT)
	{
		menu_destroy(idMenu);
		return PLUGIN_HANDLED;
	}
	
	static _access, szInfoMenu[8], callback;
	menu_item_getinfo(idMenu, idItem, _access, szInfoMenu, sizeof(szInfoMenu) - 1, _, _, callback);
	
	new iNumberItem = str_to_num(szInfoMenu);

	new szNameVersionMod[256],szSiteMod[256];
	formatex(szNameVersionMod, charsmax(szNameVersionMod), "%L %s",LANG_PLAYER,"CLIENT_PRINT_MOD_VERSION",WC3_NAME,WC3_VERSION);
	formatex(szSiteMod, charsmax(szSiteMod), "%L",LANG_PLAYER,"CLIENT_PRINT_AUTHOR_SITE","<a href=^"http://perfect-soft.su^">PERFECT-SOFT.SU</a>");

	new iPos = 0;

	switch(iNumberItem)
	{
		case enBaseCmd:
		{
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head><meta charset=^"utf-8^"></head>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<style type=^"text/css^">");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h1{font-size: 20px;font-family: Arial; color: #60BAF6;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h2{font-size: 12px;font-family: Arial; color: #FFAB00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "body {background: black; color: white}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dt{font: 17px serif; font-family: Arial; color: #69F902;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dd{font: italic 14px; font-family: Arial; color: #FFFC00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</style>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER,"MOTD_ID_ITEM_MOD");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h1>");
	
			//
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER, "MOTD_HELP_BASE_MOD");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szNameVersionMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<br>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szSiteMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");
						
			formatex(szTitle, charsmax(szTitle), "%L", LANG_PLAYER, "WAR3HELP_TITLE" );
			show_motd( idUser, szTmpMsg, szTitle );
		}
		case enSecondaryCmd:
		{
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head><meta charset=^"utf-8^"></head>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<style type=^"text/css^">");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h1{font-size: 20px;font-family: Arial; color: #60BAF6;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h2{font-size: 12px;font-family: Arial; color: #FFAB00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "body {background: black; color: white}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dt{font: 17px serif; font-family: Arial; color: #69F902;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dd{font: italic 14px; font-family: Arial; color: #FFFC00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</style>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER,"MOTD_ID_ITEM_MOD_2");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER, "MOTD_HELP_SECONDARY_MOD");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szNameVersionMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<br>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szSiteMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");
						
			formatex(szTitle, charsmax(szTitle), "%L", LANG_PLAYER, "WAR3HELP_TITLE" );
			show_motd( idUser, szTmpMsg, szTitle );
		}
		case enBindCmd:
		{
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head><meta charset=^"utf-8^"></head>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<style type=^"text/css^">");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h1{font-size: 20px;font-family: Arial; color: #60BAF6;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h2{font-size: 12px;font-family: Arial; color: #FFAB00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "body {background: black; color: white}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dt{font: 17px serif; font-family: Arial; color: #69F902;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dd{font: italic 14px; font-family: Arial; color: #FFFC00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</style>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER,"MOTD_ID_ITEM_MOD_3");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER, "MOTD_HELP_BIND_MOD");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szNameVersionMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<br>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szSiteMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");
						
			formatex(szTitle, charsmax(szTitle), "%L", LANG_PLAYER, "WAR3HELP_TITLE" );
			show_motd( idUser, szTmpMsg, szTitle );
		}
		case enShop_1:
		{
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head><meta charset=^"utf-8^"></head>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<style type=^"text/css^">");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h1{font-size: 20px;font-family: Arial; color: #60BAF6;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h2{font-size: 12px;font-family: Arial; color: #FFAB00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "body {background: black; color: white}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dt{font: 17px serif; font-family: Arial; color: #69F902;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dd{font: italic 14px; font-family: Arial; color: #FFFC00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</style>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L ^"%L^"",LANG_PLAYER,"MOTD_ID_ITEM_SHOPMENU",LANG_PLAYER,"MOTD_TITLE_SHOPMENU");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dl>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_0");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /ankh</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_1");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /boots</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_2");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /claws</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_3");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /cloak</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_4");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /mask</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_5");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /necklace</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_6");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /frost</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_7");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /health</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_8");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /tome</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"</dl>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER, "MOTD_HELP_SHOPMENU");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szNameVersionMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<br>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szSiteMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");
						
			formatex(szTitle, charsmax(szTitle), "%L", LANG_PLAYER, "WAR3HELP_TITLE" );
			show_motd( idUser, szTmpMsg, szTitle );
			
		}
		case enShop_2:
		{
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head><meta charset=^"utf-8^"></head>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<style type=^"text/css^">");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h1{font-size: 20px;font-family: Arial; color: #60BAF6;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h2{font-size: 12px;font-family: Arial; color: #FFAB00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "body {background: black; color: white}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dt{font: 17px serif; font-family: Arial; color: #69F902;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dd{font: italic 14px; font-family: Arial; color: #FFFC00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</style>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L ^"%L^"",LANG_PLAYER,"MOTD_ID_ITEM_SHOPMENU",LANG_PLAYER,"MOTD_TITLE_SHOPMENU2");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dl>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_9");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /scroll</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_10");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /molepr</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_11");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /helm</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_12");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /amulet</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_13");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /socks</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_14");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /gloves</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_15");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /rings</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_16");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /chameleon</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_17");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /mole</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"</dl>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER, "MOTD_HELP_SHOPMENU" );
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szNameVersionMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<br>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szSiteMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");
						
			formatex(szTitle, charsmax(szTitle), "%L", LANG_PLAYER, "WAR3HELP_TITLE" );
			show_motd( idUser, szTmpMsg, szTitle );
			
		}
		case enShop_3:
		{
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head><meta charset=^"utf-8^"></head>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<style type=^"text/css^">");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h1{font-size: 20px;font-family: Arial; color: #60BAF6;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h2{font-size: 12px;font-family: Arial; color: #FFAB00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "body {background: black; color: white}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dt{font: 17px serif; font-family: Arial; color: #69F902;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dd{font: italic 14px; font-family: Arial; color: #FFFC00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</style>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L ^"%L^"",LANG_PLAYER,"MOTD_ID_ITEM_SHOPMENU",LANG_PLAYER,"MOTD_TITLE_SHOPMENU3");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dl>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_18");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /brain</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_19");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /nogren</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_20");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /mirror</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_21");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /esp</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_22");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /farmor</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_23");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /deathtouch</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_24");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /hpp</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_25");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /ulttimediv</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_26");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /steelskin</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"</dl>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER, "MOTD_HELP_SHOPMENU" );
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szNameVersionMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<br>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szSiteMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");
						
			formatex(szTitle, charsmax(szTitle), "%L", LANG_PLAYER, "WAR3HELP_TITLE" );
			show_motd( idUser, szTmpMsg, szTitle );
			
		}
		case enShop_4:
		{
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<html>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<head><meta charset=^"utf-8^"></head>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<style type=^"text/css^">");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h1{font-size: 20px;font-family: Arial; color: #60BAF6;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "h2{font-size: 12px;font-family: Arial; color: #FFAB00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "body {background: black; color: white}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dt{font: 17px serif; font-family: Arial; color: #69F902;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "dd{font: italic 14px; font-family: Arial; color: #FFFC00;}");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</style>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L ^"%L^"",LANG_PLAYER,"MOTD_ID_ITEM_SHOPMENU",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h1>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dl>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_27");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /devlight</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_28");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /iceblock</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_29");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /thief</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_30");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /mirrorult</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_31");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /deathcoil</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_32");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /impale</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_33");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /sleep</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_34");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /skeletons</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dt>%L</dt>",LANG_PLAYER,"ITEM_35");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"<dd>say /tranquility</dd>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos,"</dl>");	
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%L",LANG_PLAYER, "MOTD_HELP_SHOPMENU" );
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szNameVersionMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "<br>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "%s",szSiteMod);
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</h2>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</body>");
			iPos += formatex(szTmpMsg[iPos], charsmax(szTmpMsg)-iPos, "</html>");
						
			formatex(szTitle, charsmax(szTitle), "%L", LANG_PLAYER, "WAR3HELP_TITLE" );
			show_motd( idUser, szTmpMsg, szTitle );
			
		}


	}

	menu_destroy(idMenu);

	clMotd::fShowMenuHelp(idUser,floatround( float(iNumberItem / 7)) );

	//client_print(0,print_chat,"iNumberItem: %d |idItem: %d",iNumberItem,idItem);	

	return PLUGIN_HANDLED;
}