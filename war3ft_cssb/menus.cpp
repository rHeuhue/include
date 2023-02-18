// ******************************************************************
// MENU_WAR3MENU = CSSB Warcraft 3 Frozen Throne Private Меню
// ******************************************************************
public MENU_War3Menu( idUser )
{
	
		static pos, szMenu[256], keys;
		keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<9);
		pos = 0;

		// Add the title
		pos += formatex( szMenu[pos], charsmax(szMenu)-pos, "%L^n^n", LANG_PLAYER, "MENU_WAR3MENU" );
		
		// Add the actual options to the menu
		pos += formatex( szMenu[pos], charsmax(szMenu)-pos, "\w1. %L^n", LANG_PLAYER, "SKILLS_MENU" );
		pos += formatex( szMenu[pos], charsmax(szMenu)-pos, "\w2. %L^n", LANG_PLAYER, "RACE_MENU" );
		pos += formatex( szMenu[pos], charsmax(szMenu)-pos, "\w3. %L^n", LANG_PLAYER, "ITEM_MENU" );
		pos += formatex( szMenu[pos], charsmax(szMenu)-pos, "\y4. %L^n", LANG_PLAYER, "HELP" );
		pos += formatex( szMenu[pos], charsmax(szMenu)-pos, "\r5. %L^n", LANG_PLAYER, "ADMIN_MENU_TITLE" );
		pos += formatex( szMenu[pos], charsmax(szMenu)-pos, "\w6. %L^n", LANG_PLAYER, "MENU_TALISMAN_MENU_NAME" );//Для talisman
		pos += formatex( szMenu[pos], charsmax(szMenu)-pos, "\w7. %L^n", LANG_PLAYER, "MENU_AUTOBUY_MENU_NAME" );//Для авто закупки предметов +
		pos += formatex( szMenu[pos], charsmax(szMenu)-pos, "^n\d0. %L", LANG_PLAYER, "WORD_EXIT" );

		// Display the menu
		show_menu( idUser, keys, szMenu, -1 );
	

	return;
}

public _MENU_War3Menu( idUser, key )
{
	
		if ( !WC3_Check() )
			return PLUGIN_HANDLED;

		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_MENU_CLICK], 1.0, ATTN_NORM, 0, PITCH_NORM ); 

		switch ( key )
		{
			case 0:	menu_Skill_Options( idUser );
			case 1:	menu_Race_Options( idUser );
			case 2:	menu_Item_Options( idUser );
			case 3:	clMotd::fShowMenuHelp(idUser,0);
			case 4:	menu_Admin_Options( idUser );
			case 5:	fShowMenuTalismans( idUser ); //Для talisman
			case 6:	fShowMenuAutoBuyBase(idUser); //Для авто закупки предметов
		}
	

	return PLUGIN_HANDLED;
}


// ******************************************************************
// SKILLS_MENU = Меню навыков
// ******************************************************************
public menu_Skill_Options( idUser )
{
	
		new pos = 0, menu_body[512]
		new keys = (1<<0)|(1<<1)|(1<<2)|(1<<8)|(1<<9)
		new szMenuItemSelectSkills[64];
		new szMenuItemSkillInfo[64];
		new szMenuItemReselectSkill[64];
		
		format(szMenuItemSelectSkills,charsmax(szMenuItemSelectSkills),"\w%L",LANG_PLAYER,"SELECT_SKILLS")
		format(szMenuItemSkillInfo,charsmax(szMenuItemSkillInfo),"\y%L",LANG_PLAYER,"SKILLS_INFORMATION")
		format(szMenuItemReselectSkill,charsmax(szMenuItemReselectSkill),"\r%L",LANG_PLAYER,"RESELECT_SKILLS")
		
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "%L^n^n",LANG_PLAYER,"MENU_SKILLS_OPTIONS")

		pos += format(menu_body[pos], charsmax(menu_body)-pos, "\w1. %s^n",szMenuItemSelectSkills)
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "\y2. %s^n",szMenuItemSkillInfo)
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "\r3. %s^n",szMenuItemReselectSkill)

		pos += format(menu_body[pos], charsmax(menu_body)-pos, "^n^n\d9. %L",LANG_PLAYER,"BACK_STRING")
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "^n\d0. %L",LANG_PLAYER,"WORD_EXIT")
		show_menu(idUser,keys,menu_body,-1)
	

	return PLUGIN_CONTINUE;
}

public _menu_Skill_Options(idUser,key){

	
		if ( !WC3_Check() )
			return PLUGIN_HANDLED;

		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_MENU_CLICK], 1.0, ATTN_NORM, 0, PITCH_NORM ); 

		switch (key)
		{
			case 0:	MENU_SelectSkill( idUser );
			case 1:	MOTD_SkillsInfo( idUser );
			case 2:	CMD_Handle(idUser,"resetskills");
			case 8: MENU_War3Menu(idUser)
			default: return PLUGIN_HANDLED;
		}
	

	return PLUGIN_HANDLED;
}

// ******************************************************************
// RACE_MENU = Меню рас (сменить расу,показать уровень,сброс опыта)
// ******************************************************************
public menu_Race_Options(idUser)
{
	
		new pos = 0, menu_body[512]
		new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<8)|(1<<9)

		new szMenuItemChangeRace[64];
		new szMenuItemShowLevel[64];
		new szMenuItemResetXP[64];
		new szMenuItemShowPlayerSkills[64];

		format(szMenuItemChangeRace,charsmax(szMenuItemChangeRace),"\w%L",LANG_PLAYER,"CHANGE_RACE")
		format(szMenuItemShowLevel,charsmax(szMenuItemShowLevel),"\y%L",LANG_PLAYER,"SHOW_LEVEL")
		format(szMenuItemResetXP,charsmax(szMenuItemResetXP),"\y%L",LANG_PLAYER,"RESET_XP")
		format(szMenuItemShowPlayerSkills,charsmax(szMenuItemShowPlayerSkills),"\r%L",LANG_PLAYER,"SHOW_PLAYER_SKILLS")

		pos += format(menu_body[pos], charsmax(menu_body)-pos, "%L^n^n",LANG_PLAYER,"MENU_RACE_OPTIONS")
			
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "\w1. %s^n",szMenuItemChangeRace)
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "\y2. %s^n",szMenuItemShowLevel)
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "\y3. %s^n",szMenuItemResetXP)		
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "\r4. %s^n",szMenuItemShowPlayerSkills)		

		pos += format(menu_body[pos], charsmax(menu_body)-pos, "^n^n\d9. %L",LANG_PLAYER,"BACK_STRING")
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "^n\d0. %L",LANG_PLAYER,"WORD_EXIT")
		show_menu(idUser,keys,menu_body,-1)
	

	return PLUGIN_CONTINUE;
}

public _menu_Race_Options(idUser,key)
{
	
		if ( !WC3_Check() )
			return PLUGIN_HANDLED;

		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_MENU_CLICK], 1.0, ATTN_NORM, 0, PITCH_NORM ); 

		switch (key)
		{
			case 0:	WC3_ChangeRaceStart( idUser );
			case 1:	WC3_ShowRaceInfo( idUser );
			case 2:	MENU_ResetXP( idUser );
			case 3:	clMotd::fShowMotdPlayerRaces(idUser);
			case 8: MENU_War3Menu(idUser)
			default: return PLUGIN_HANDLED;
		}
	

	return PLUGIN_HANDLED;
}

// ******************************************************************
// ITEM_MENU = Меню магазинов (все что к магазинам относится)
// ******************************************************************
public menu_Item_Options(idUser)
{
	
		new pos = 0, menu_body[512]
		new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9)

		new szMenuItemShopOption1[64];
		new szMenuItemShopOption2[64];
		new szMenuItemShopOption3[64];
		new szMenuItemShopOption4[64];
		new szMenuItemShopInfo1[64];
		new szMenuItemShopInfo2[64];
		new szMenuItemShopInfo3[64];
		new szMenuItemShopInfo4[64];
		
		formatex(szMenuItemShopOption1,charsmax(szMenuItemShopOption1),"\r%L",LANG_PLAYER,"SHOPMENU1_OPTION")
		formatex(szMenuItemShopOption2,charsmax(szMenuItemShopOption2),"\r%L",LANG_PLAYER,"SHOPMENU2_OPTION")
		formatex(szMenuItemShopOption3,charsmax(szMenuItemShopOption3),"\r%L",LANG_PLAYER,"SHOPMENU3_OPTION")
		formatex(szMenuItemShopOption4,charsmax(szMenuItemShopOption4),"\r%L",LANG_PLAYER,"SHOPMENU4_OPTION")

		formatex(szMenuItemShopInfo1,charsmax(szMenuItemShopInfo1),"\y%L",LANG_PLAYER,"SHOW_SHOPMENU1_INFO")//Для shopmenu1
		formatex(szMenuItemShopInfo2,charsmax(szMenuItemShopInfo2),"\y%L",LANG_PLAYER,"SHOW_SHOPMENU2_INFO")//Для shopmenu2
		formatex(szMenuItemShopInfo3,charsmax(szMenuItemShopInfo3),"\y%L",LANG_PLAYER,"SHOW_SHOPMENU3_INFO")//Для shopmenu3
		formatex(szMenuItemShopInfo4,charsmax(szMenuItemShopInfo4),"\y%L",LANG_PLAYER,"SHOW_SHOPMENU4_INFO")//Для shopmenu4

		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "%L^n^n",LANG_PLAYER,"MENU_ITEM_OPTIONS")
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\r1. %s^n",szMenuItemShopOption1)
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\r2. %s^n",szMenuItemShopOption2)
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\r3. %s^n",szMenuItemShopOption3)
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\r4. %s^n",szMenuItemShopOption4)

		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\y5. %s^n",szMenuItemShopInfo1)
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\y6. %s^n",szMenuItemShopInfo2)
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\y7. %s^n",szMenuItemShopInfo3)
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\y8. %s^n",szMenuItemShopInfo4)

		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "^n^n\d9. %L",LANG_PLAYER,"BACK_STRING")
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "^n\d0. %L",LANG_PLAYER,"WORD_EXIT")
		show_menu(idUser,keys,menu_body,-1)
	

	return PLUGIN_CONTINUE;
}


public _menu_Item_Options(idUser,key)
{
	
		
		if ( !WC3_Check() )
			return PLUGIN_HANDLED;

		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_MENU_CLICK], 1.0, ATTN_NORM, 0, PITCH_NORM ); 

		switch (key)
		{
			case 0:	MENU_Shopmenu( idUser, 0 );
			case 1:	MENU_Shopmenu( idUser, 9 );
			case 2:	MENU_Shopmenu( idUser, 18 );
			case 3:	
				{
					if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
					{
						if(get_pcvar_num( CVAR_wc3_shopmenu4_vip ) == 0)
						{
							MENU_Shopmenu( idUser, 27 );
						}
						else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
						{
							MENU_Shopmenu( idUser, 27 );
						}
					}
					else
					{
						formatex(szMessage, charsmax(szMessage), "%L - !t%L!",LANG_PLAYER,"MOTD_TITLE_SHOPMENU4",LANG_PLAYER,"CLIENT_PRINT_OFF");
						cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
					}
				}
			case 4:	clMotd::fShowMotdItemsInfo(idUser,0);
			case 5:	clMotd::fShowMotdItemsInfo(idUser,9);
			case 6:	clMotd::fShowMotdItemsInfo(idUser,18);
			case 7:	clMotd::fShowMotdItemsInfo(idUser,27);
			case 8: MENU_War3Menu(idUser);
			default: return PLUGIN_HANDLED;
		}
	

	return PLUGIN_HANDLED;
}

// ******************************************************************
// ADMIN_MENU_TITLE = Меню админа (дать опыт игрокам)
// ******************************************************************
public menu_Admin_Options(idUser)
{
	
		if ( idUser && !( get_user_flags( idUser ) & XP_GetAdminFlag() ) )
		{
			format(szMessage, charsmax(szMessage), "%L%L%L %L",
					LANG_PLAYER,"WC3_BRACKET_LEFT",LANG_PLAYER,"WC3_MODCLIENT",LANG_PLAYER,"WC3_BRACKET_RIGHT",
					LANG_PLAYER,"YOU_HAVE_NO_ACCESS");	
					
			client_print( idUser, print_console, szMessage );
			
			return PLUGIN_HANDLED
		}

		new pos = 0, menu_body[512]
		new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<8)|(1<<9)

		new szMenuItemGiveIndXP[64];
		new szMenuItemGiveMultXP[64];
		new szMenuItemSaveAll[64];
		new szMenuItemGiveTalisman[64];
		
		format(szMenuItemGiveIndXP,charsmax(szMenuItemGiveIndXP),"\r%L",LANG_PLAYER,"GIVE_IND_XP")
		format(szMenuItemGiveMultXP,charsmax(szMenuItemGiveMultXP),"\r%L",LANG_PLAYER,"GIVE_MULT_XP")
		format(szMenuItemSaveAll,charsmax(szMenuItemSaveAll),"\y%L",LANG_PLAYER,"SAVE_ALL_XP")
		format(szMenuItemGiveTalisman,charsmax(szMenuItemGiveTalisman),"\r%L",LANG_PLAYER,"GIVE_TALISMAN")

		pos += format(menu_body[pos], charsmax(menu_body)-pos, "%L^n^n",LANG_PLAYER,"MENU_ADMIN_MENU")

		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\r1. %s^n",szMenuItemGiveIndXP);
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\r2. %s^n",szMenuItemGiveMultXP);
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\y3. %s^n",szMenuItemSaveAll);
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\r4. %s^n",szMenuItemGiveTalisman);

		pos += format(menu_body[pos], charsmax(menu_body)-pos, "^n^n\d9. %L",LANG_PLAYER,"BACK_STRING")
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "^n\d0. %L",LANG_PLAYER,"WORD_EXIT")
		show_menu(idUser,keys,menu_body,-1)
	

	return PLUGIN_CONTINUE;
}

public _menu_Admin_Options(idUser,key)
{
	
		if ( !WC3_Check() )
			return PLUGIN_HANDLED;

		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_MENU_CLICK], 1.0, ATTN_NORM, 0, PITCH_NORM ); 

		switch (key)
		{
			case 0:
			{
				g_menuOption[idUser] = 1
				g_menuSettings[idUser] = 500
				menu_PlayerXP_Options(idUser,g_menuPosition[idUser] = 0)
			}
			case 1:
			{
				g_menuOption[idUser] = 1
				g_menuSettings[idUser] = 500
				menu_TeamXP_Options(idUser)
			}
			case 2: DB_SaveAll( false );

			case 3: 
			{
				//функция вызова меню выдачи таликов
				menu_Players_Talisman(idUser,g_menuPosition[idUser] = 0);
			}

			case 8: MENU_War3Menu(idUser);
		}
	

	return PLUGIN_HANDLED;
}

// ****************************************************************************
// Меню админа -> Дать талисман игроку (список игроков для выдачи талика)
// ****************************************************************************
public menu_Players_Talisman(idUser,pos)
{
	
		if (pos < 0)
		{
			menu_Admin_Options(idUser);
			return PLUGIN_CONTINUE;
		}

		idPlayerGiveTalisman = 0;

		get_players(g_menuPlayers[idUser],g_menuPlayersNum[idUser])
		new menuBody[512]
		new b = 0
		new i
		new name[32], team[4], title[128], back[16], exitstring[16]
		new start = pos * 8
		if (start >= g_menuPlayersNum[idUser])
			start = pos = g_menuPosition[idUser] = 0
			
		format(title,127,"%L",LANG_PLAYER,"MENU_PLAYERS_TALISMAN")
		new len = format(menuBody,charsmax(menuBody), "%s\R%d/%d^n\w^n",title,pos+1,(g_menuPlayersNum[idUser] / 8 + ((g_menuPlayersNum[idUser] % 8) ? 1 : 0 )))
		new end = start + 8
		new keys = (1<<8)|(1<<9)

		if (end > g_menuPlayersNum[idUser])
			end = g_menuPlayersNum[idUser]

		for(new a = start; a < end; ++a)
		{
			i = g_menuPlayers[idUser][a]
			get_user_name(i,name,31)
			get_user_team(i,team,3)
			keys |= (1<<b)
			len += format(menuBody[len],charsmax(menuBody)-len,"\w%d. %s^n\w",++b,name)
		}

		format(back,15,"%L",LANG_PLAYER,"BACK_STRING")

		if (end != g_menuPlayersNum[idUser])
		{
			format(menuBody[len],charsmax(menuBody)-len,"^n9. %L...^n0. %s", LANG_PLAYER,"MORE_STRING", pos ? back : back)
			keys |= (1<<8)
		}
		else
		{
			format(exitstring,charsmax(exitstring),"%L",LANG_PLAYER,"WORD_EXIT")
			format(menuBody[len],charsmax(menuBody)-len,"^n0. %s", pos ? back : exitstring)
		}

		show_menu(idUser,keys,menuBody,-1)
	

	return PLUGIN_CONTINUE;

}

public _menu_Players_Talisman(idUser,key)
{
	
		if ( !WC3_Check() )
			return PLUGIN_HANDLED;

		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_MENU_CLICK], 1.0, ATTN_NORM, 0, PITCH_NORM ); 

		switch(key)
		{
			case 8: menu_Players_Talisman(idUser,++g_menuPosition[idUser])
			case 9:
			{
				if(g_menuPosition[idUser] > 0)
					menu_Players_Talisman(idUser,g_menuPosition[idUser] = 0);
				else
					menu_Admin_Options(idUser);
			}
			default:
			{
				idPlayerGiveTalisman = g_menuPlayers[idUser][g_menuPosition[idUser] * 8 + key];
			
				fShowMenuGiveTalisman(idUser,0);
			}
		}
	

	return PLUGIN_HANDLED;
}

// ****************************************************************************
// Меню админа -> Список выдаваемых талисманов
// ****************************************************************************
fShowMenuGiveTalisman(idUser, iPage = 0)
{
	

	new idMenu,szNumber[64],szMenuData[256],szTalismanData[256];
	
	//Название главного меню
	formatex(szMenuData, charsmax(szMenuData), "\y%L", LANG_PLAYER, "MENU_GIVE_TALISMAN");
	idMenu = menu_create(szMenuData, "_Callback_MENU_GiveTalisman");

	// Добавление пунктов в меню
	for(new i = 0; i < MAX_TALISMANS; i++)
	{
		new szItemName[32];
		LANG_GetItemName(LIST_TALISMANS[i], idUser, szItemName, 31, true );
		
		formatex(szTalismanData, charsmax(szTalismanData), "%L '\y%s'",LANG_PLAYER,"WC3_KEY_TALISMAN", szItemName);
		formatex(szNumber, charsmax(szNumber), "%d", LIST_TALISMANS[i]);

		menu_additem(idMenu,szTalismanData, szNumber,0,-1);
	}
	
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
	
	menu_display(idUser, idMenu, iPage);
}

public _Callback_MENU_GiveTalisman(idUser, idMenu, idItem)
{
	
	if (!WC3_Check())
		return PLUGIN_HANDLED;

	// Возврат в главное меню
	if (idItem == MENU_EXIT || idPlayerGiveTalisman == 0)
	{
		menu_Players_Talisman(idUser,g_menuPosition[idUser] = 0);

		menu_destroy(idMenu);
		return PLUGIN_HANDLED;
	}
	
	static _access, szInfoMenu[8], callback;
	menu_item_getinfo(idMenu, idItem, _access, szInfoMenu, sizeof(szInfoMenu) - 1, _, _, callback);
	
	new iNumberTalisman = str_to_num(szInfoMenu);
//	client_print(0,print_chat,"iNumberTalisman: %d |idItem: %d",iNumberTalisman,idItem);

	new szTalismanName[32];
	LANG_GetItemName(iNumberTalisman, idUser, szTalismanName, 31, true );

//Распечатка игроку,которому выдали талик
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_GIVE_TALISMAN",szTalismanName);
	cssbChatColor(idPlayerGiveTalisman,"%s%s",fTagWar3ft(),szMessage);

//Выдача талика
	ADMIN_Talisman_Buy(idPlayerGiveTalisman,iNumberTalisman);

//Лог выдачи талика
	new szUserName[32];
	get_user_name(idPlayerGiveTalisman, szUserName, 31 );		
	ADMIN_Log(idUser, "Give Talisman","%s %s",szTalismanName,szUserName);

//Распечатка для админа кому и что дал
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_GIVE_PLAYER_TALISMAN",szTalismanName,szUserName);
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

	menu_destroy(idMenu);

	fShowMenuGiveTalisman(idUser,floatround(float(idItem / 7)));


	return PLUGIN_HANDLED;
}

// ****************************************************************************
// Меню админа -> Дать XP игроку
// ****************************************************************************
public menu_PlayerXP_Options(idUser,pos)
{
	

		if (pos < 0)
		{
			menu_Admin_Options(idUser)
			return PLUGIN_CONTINUE;
		}

		get_players(g_menuPlayers[idUser],g_menuPlayersNum[idUser])
		new menuBody[512]
		new b = 0
		new i
		new name[32], team[4], title[128], back[16], exitstring[16]
		new start = pos * 7
		if (start >= g_menuPlayersNum[idUser])
			start = pos = g_menuPosition[idUser] = 0
			
		format(title,127,"%L",LANG_PLAYER,"MENU_GIVE_PLAYERS_XP")
		new len = format(menuBody,charsmax(menuBody), "%s\R%d/%d^n\w^n",title,pos+1,(g_menuPlayersNum[idUser] / 7 + ((g_menuPlayersNum[idUser] % 7) ? 1 : 0 )))
		new end = start + 7
		new keys = (1<<7)|(1<<9)

		if (end > g_menuPlayersNum[idUser])
			end = g_menuPlayersNum[idUser]

		for(new a = start; a < end; ++a)
		{
			i = g_menuPlayers[idUser][a]
			get_user_name(i,name,31)
			get_user_team(i,team,3)
			keys |= (1<<b)
			len += format(menuBody[len],charsmax(menuBody)-len,"\w%d. %s^n\w",++b,name)
		}

		format(title,charsmax(title),"%L",LANG_PLAYER,"GIVE")
		len += format(menuBody[len],charsmax(menuBody)-len,"^n8. %s  %d XP^n",title,g_menuSettings[idUser])

		format(back,15,"%L",LANG_PLAYER,"BACK_STRING")

		if (end != g_menuPlayersNum[idUser])
		{
			format(menuBody[len],charsmax(menuBody)-len,"^n9. %L...^n0. %s", LANG_PLAYER,"MORE_STRING", pos ? back : back)
			keys |= (1<<8)
		}
		else
		{
			format(exitstring,charsmax(exitstring),"%L",LANG_PLAYER,"WORD_EXIT")
			format(menuBody[len],charsmax(menuBody)-len,"^n0. %s", pos ? back : exitstring)
		}

		show_menu(idUser,keys,menuBody,-1)
	

	return PLUGIN_CONTINUE;

}

public _menu_PlayerXP_Options(idUser,key)
{
	
		if ( !WC3_Check() )
			return PLUGIN_HANDLED;

		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_MENU_CLICK], 1.0, ATTN_NORM, 0, PITCH_NORM ); 

		switch(key)
		{
			case 7:
			{
				++g_menuOption[idUser]
				if (g_menuOption[idUser]>6)
				{
					g_menuOption[idUser]=1
				}
				switch(g_menuOption[idUser])
				{
					case 1: g_menuSettings[idUser] = 500
					case 2: g_menuSettings[idUser] = 1000
					case 3: g_menuSettings[idUser] = 5000
					case 4: g_menuSettings[idUser] = 10000
					case 5: g_menuSettings[idUser] = 50000
					case 6: g_menuSettings[idUser] = 100000
				}

				menu_PlayerXP_Options(idUser,g_menuPosition[idUser])
			}
			case 8: menu_PlayerXP_Options(idUser,++g_menuPosition[idUser])
			case 9: 
			{
				if(g_menuPosition[idUser] > 0)
					menu_PlayerXP_Options(idUser,g_menuPosition[idUser] = 0);
				else
					menu_Admin_Options(idUser);
			}
			default:
			{
				new idPlayer = g_menuPlayers[idUser][g_menuPosition[idUser] * 7 + key];
		
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_GIVE_XP",g_menuSettings[idUser]);
				cssbChatColor(idPlayer,"%s%s",fTagWar3ft(),szMessage);
					
				arrIntData[idPlayer][P_XP] += g_menuSettings[idUser];

				XP_Check( idPlayer );

				menu_PlayerXP_Options(idUser,g_menuPosition[idUser]);
				
				new szUserName[32];
				get_user_name(idPlayer, szUserName, 31 );		
				ADMIN_Log(idUser, "Give XP","%d %s", g_menuSettings[idUser],szUserName);

			}
		}
	

	return PLUGIN_HANDLED;
}

// *****************************************************************************************************
// Меню админа -> Дать XP игрокам
// *****************************************************************************************************
public menu_TeamXP_Options(idUser)
{
	
		new pos = 0, menu_body[512], give[16]
		new keys = (1<<0)|(1<<1)|(1<<2)|(1<<7)|(1<<8)|(1<<9)

		new szMenuItemTerrorist[64];
		new szMenuItemCT[64];
		new szMenuItemEveryone[64];
		
		format(szMenuItemTerrorist,charsmax(szMenuItemTerrorist),"\y%L",LANG_PLAYER,"TERRORISTS")
		format(szMenuItemCT,charsmax(szMenuItemCT),"\y%L",LANG_PLAYER,"CT")
		format(szMenuItemEveryone,charsmax(szMenuItemEveryone),"\r%L",LANG_PLAYER,"EVERYONE")

		pos += format(menu_body[pos], charsmax(menu_body)-pos, "%L^n^n",LANG_PLAYER,"MENU_TEAM_XP")

		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\y1. %s^n",szMenuItemTerrorist)
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\y2. %s^n",szMenuItemCT)
		pos += formatex(menu_body[pos], charsmax(menu_body)-pos, "\r3. %s^n",szMenuItemEveryone)				

		format(give,charsmax(give),"\w%L",LANG_PLAYER,"GIVE")
		pos += format(menu_body[pos], charsmax(menu_body)-pos,"^n\w8. %s  %d XP^n",give,g_menuSettings[idUser])
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "^n^n\d9. %L",LANG_PLAYER,"BACK_STRING")
		pos += format(menu_body[pos], charsmax(menu_body)-pos, "^n\d0. %L",LANG_PLAYER,"WORD_EXIT")
		show_menu(idUser,keys,menu_body,-1)
	

	return PLUGIN_CONTINUE;
}

public _menu_TeamXP_Options(idUser,key)
{
	
	
		if ( !WC3_Check() )
			return PLUGIN_HANDLED;

		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_MENU_CLICK], 1.0, ATTN_NORM, 0, PITCH_NORM ); 

		switch(key)
		{
			case 0:
			{
				ADMIN_GiveXP( idUser, "@T", g_menuSettings[idUser] );
				ADMIN_Log(idUser, "Give XP @T","%d", g_menuSettings[idUser]);
				menu_TeamXP_Options(idUser)
			}
			case 1:
			{
				ADMIN_GiveXP( idUser, "@CT", g_menuSettings[idUser] );
				ADMIN_Log(idUser, "Give XP @CT","%d", g_menuSettings[idUser]);
				menu_TeamXP_Options(idUser)
			}
			case 2:
			{
				ADMIN_GiveXP( idUser, "@ALL", g_menuSettings[idUser] );
				ADMIN_Log(idUser, "Give XP @ALL","%d", g_menuSettings[idUser]);
				menu_TeamXP_Options(idUser)
			}
			case 7:
			{
				++g_menuOption[idUser]
				if (g_menuOption[idUser]>6)
				{
					g_menuOption[idUser]=1
				}
				switch(g_menuOption[idUser])
				{
					case 1: g_menuSettings[idUser] = 500
					case 2: g_menuSettings[idUser] = 1000
					case 3: g_menuSettings[idUser] = 5000
					case 4: g_menuSettings[idUser] = 10000
					case 5: g_menuSettings[idUser] = 50000
					case 6: g_menuSettings[idUser] = 100000
				}
				menu_TeamXP_Options(idUser)
			}
			case 8: menu_Admin_Options(idUser)
		}
	

	return PLUGIN_HANDLED;
}

public MENU_ResetXP(idUser)
{
	
		if(!(get_user_flags(idUser) & ADMIN_FLAG))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"YOU_HAVE_NO_ACCESS");		
			client_print(idUser, print_console,szMessage);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

			return;
		}

		static szMenu[128];
		new keys = (1<<0)|(1<<1)|(1<<9);

		formatex(szMenu, sizeof(szMenu) - 1, "%L^n^n\w1. %L^n\w2. %L",
		LANG_PLAYER,"MENU_RESET_XP",
		LANG_PLAYER,"WC3_YES",
		LANG_PLAYER,"WC3_NO");
		
		show_menu( idUser, keys, szMenu, -1 );

	

	return;
}

public _MENU_ResetXP( idUser, key )
{
	

		if ( !WC3_Check() )
			return PLUGIN_HANDLED;

		// User selected yes
		if ( key == 0 )
		{
			XP_Reset( idUser );
		}

	
	
	return PLUGIN_HANDLED;
}



public MENU_ReplaceItem( idUser )
{

	
		new szMenu[512] = "", pos = 0;
		new iKeys = (1<<9)|(1<<0)|(1<<1)|(1<<2);

		// Add the menu header
		pos += format( szMenu[pos], charsmax(szMenu)-pos, "%L^n^n", LANG_PLAYER, "MENU_REPLACE_ITEM" );

		new szItemName[64], szItemName2[64],szItemName3[64];
		LANG_GetItemName( g_iShopMenuItems[idUser][ITEM_SLOT_ONE], idUser, szItemName, charsmax(szItemName) );
		LANG_GetItemName( g_iShopMenuItems[idUser][ITEM_SLOT_TWO], idUser, szItemName2, charsmax(szItemName2) );
		LANG_GetItemName( g_iShopMenuItems[idUser][ITEM_SLOT_THREE], idUser, szItemName3, charsmax(szItemName3) );

		// Add the items
		pos += format( szMenu[pos], charsmax(szMenu)-pos, "\y1. %s^n", szItemName );
		pos += format( szMenu[pos], charsmax(szMenu)-pos, "\y2. %s^n", szItemName2 );
		pos += format( szMenu[pos], charsmax(szMenu)-pos, "\y3. %s^n", szItemName3 );

		// Add the exit option
		pos += format( szMenu[pos], charsmax(szMenu)-pos, "^n\d0. %L", LANG_PLAYER, "WORD_EXIT" );

		// Show the menu
		show_menu( idUser, iKeys, szMenu, -1 );

	

	return;
}

public _menu_ReplaceItem( idUser, iKey )
{
	
	
		if ( !WC3_Check() || iKey == 9 )
			return PLUGIN_HANDLED;

		// Remove item from item slot one
		if ( iKey == 0 )
		{
			ITEM_Remove( idUser, ITEM_SLOT_ONE )
		}

		// Remove item from itemslot two
		if ( iKey == 1 )
		{
			ITEM_Remove( idUser, ITEM_SLOT_TWO )
		}
		// Remove item from itemslot two
		if ( iKey == 2 )
		{
			ITEM_Remove( idUser, ITEM_SLOT_THREE )
		}

		// Then the user typed "rings"
		if ( g_iFutureItem[idUser] == -3 )
		{
			ITEM_BuyRings( idUser );
		}
		else
		{
			ITEM_Buy( idUser, g_iFutureItem[idUser] );
		}
	

	return PLUGIN_HANDLED;
}

//Меню магазинов
public MENU_Shopmenu( idUser, iStart )
{
	
		if ( !ITEM_MenuCanBuyCheck( idUser ) )
			return;

		// Shopmenu2 can't display if we don't have the correct number of races!
		if ( iStart == MAX_PAGE_ITEMS && MAX_RACES <= 4 )
		{
			return;
		}

		new szMenu[512], szItemName[64], pos = 0, i, iItemID;
		new iKeys = (1<<9);

		// Add the header
		if ( iStart == 0 )
		{
			pos += format( szMenu[pos], charsmax(szMenu)-pos, "%L", LANG_PLAYER, "MENU_BUY_ITEM" );
		}

		// "Shopmenu 2"
		if ( iStart == MAX_PAGE_ITEMS )
		{
			pos += format( szMenu[pos], charsmax(szMenu)-pos, "%L", LANG_PLAYER, "MENU_BUY_ITEM2" );
		}
		// "Shopmenu 3"
		if ( iStart == 18 )
		{
			pos += format( szMenu[pos], charsmax(szMenu)-pos, "%L", LANG_PLAYER, "MENU_BUY_ITEM3" );
		}
		//Для shopmenu4
		if ( iStart == 27 )
		{
			pos += format( szMenu[pos], charsmax(szMenu)-pos, "%L", LANG_PLAYER, "MENU_BUY_ITEM4" );
		}
		
		// Lets add the items to the menu!
		for ( i = 0; i < MAX_PAGE_ITEMS; i++ )
		{
			iItemID = iStart + i;

			LANG_GetItemName( iItemID, idUser, szItemName,charsmax(szItemName));

			new iItemMoney = ITEM_Cost( idUser, iItemID );
			new iUserMoney = SHARED_GetUserMoney( idUser );

			if(iUserMoney < iItemMoney)
				pos += format( szMenu[pos], charsmax(szMenu)-pos, "\d%d. %s\R%d^n", i + 1, szItemName, ITEM_Cost( idUser, iItemID ) );
			else
				pos += format( szMenu[pos], charsmax(szMenu)-pos, "\y%d. %s\r\R%d^n", i + 1, szItemName, ITEM_Cost( idUser, iItemID ) );

			iKeys |= (1<<i);
		}

		pos += format( szMenu[pos], charsmax(szMenu)-pos, "^n\d0. %L", LANG_PLAYER, "WORD_EXIT" );

		show_menu( idUser, iKeys, szMenu, -1 );
	

}
//Для shopmenu1
public _MENU_Shopmenu1( idUser, iKey )
{
	
		if ( !WC3_Check() || iKey == 9 )
			return PLUGIN_HANDLED;

		new iItemMoney = ITEM_Cost( idUser, iKey );
		new iUserMoney = SHARED_GetUserMoney( idUser );

		if(iUserMoney < iItemMoney)
			MENU_Shopmenu( idUser, 0 );


		ITEM_Buy( idUser, iKey );
	

	return PLUGIN_HANDLED;
}
//Для shopmenu2
public _MENU_Shopmenu2( idUser, iKey )
{
	
		if ( !WC3_Check() || iKey == 9 )
			return PLUGIN_HANDLED;

		iKey += MAX_PAGE_ITEMS;
		
		new iItemMoney = ITEM_Cost( idUser, iKey );
		new iUserMoney = SHARED_GetUserMoney( idUser );

		if(iUserMoney < iItemMoney)
			MENU_Shopmenu( idUser, 9 );


		ITEM_Buy( idUser, iKey );
	

	return PLUGIN_HANDLED;
}

//Для shopmenu3
public _MENU_Shopmenu3( idUser, iKey )
{
	
		if ( !WC3_Check() || iKey == 9 )
			return PLUGIN_HANDLED;

		iKey += 18;
		
		new iItemMoney = ITEM_Cost( idUser, iKey );
		new iUserMoney = SHARED_GetUserMoney( idUser );

		if(iUserMoney < iItemMoney)
			MENU_Shopmenu( idUser, 18 );


		ITEM_Buy( idUser, iKey );
	

	return PLUGIN_HANDLED;
}

//Для shopmenu4
public _MENU_Shopmenu4( idUser, iKey )
{
	
		if ( !WC3_Check() || iKey == 9 )
			return PLUGIN_HANDLED;

		iKey += 27;

		new iItemMoney = ITEM_Cost( idUser, iKey );
		new iUserMoney = SHARED_GetUserMoney( idUser );

		if(iUserMoney < iItemMoney)
			MENU_Shopmenu( idUser, 27 );


		ITEM_Buy( idUser, iKey );
	

	return PLUGIN_HANDLED;
}

public MENU_SelectSkill( idUser )
{
	

		// User has no race, how can we select skills?!?
		if ( arrIntData[idUser][P_RACE] == 0 )
		{
			//set_hudmessage(200, 100, 0, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 2)
			WC3_StatusText( idUser, TXT_TOP_CENTER, "%L", LANG_PLAYER, "SELECT_RACE_BEFORE_SKILLS" );

			return;
		}

		// They don't choose skills when it's random
		else if ( arrIntData[idUser][P_RACE] == RACE_CHAMELEON && get_pcvar_num( CVAR_wc3_cham_random ) )
		{
			//WC3_StatusText( idUser, TXT_TOP_CENTER, "%s", "Chameleons can't select skills!" );
			CHAM_ConfigureSkills( idUser );

			return;
		}

		// Lets make sure the user has some available skill points
		new iSkillsUsed = SM_TotalSkillPointsUsed( idUser );
		if ( iSkillsUsed >= arrIntData[idUser][P_LEVEL] )
		{

			//set_hudmessage(200, 100, 0, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 2)
			WC3_StatusText( idUser, TXT_TOP_CENTER, "%L", LANG_PLAYER, "ALREADY_SELECTED_SKILL_POINTS" );

			return;
		}


	//-----------------------------------------------------------------------

		//Автопрокачка скилов Хамелеона
		// Bots don't need a menu now do they??
		if ( arrIntData[idUser][P_RACE] == RACE_CHAMELEON && get_pcvar_num( CVAR_wc3_cham_random ) || is_user_bot( idUser ))
		{
			// No race has been selected yet!!
			if (!SM_SkillAvailable(idUser))
				return;
			
			// Keep giving the bot a random ID until we are full!
			while (iSkillsUsed < arrIntData[idUser][P_LEVEL])
			{
				SM_GiveRandomSkillPoint( idUser );

				iSkillsUsed = SM_TotalSkillPointsUsed( idUser );
			}

			return;
		}

	//--------------------------------------------------------------------------
		// OK set up a menu!!!

		new szMsg[512], pos = 0, szSkillName[64];
		new iSkillCounter = 0, iSkillID = 0, iKeys = (1<<9), iSkillLevel;

		
		// Add the menu header
		pos += formatex( szMsg[pos], charsmax(szMsg)-pos, "%L", LANG_PLAYER, "MENU_SELECT_SKILL" );

		iSkillID = SM_GetSkillByPos( idUser, iSkillCounter );

		while ( iSkillID != -1 )
		{
			iSkillLevel = SM_GetSkillLevel( idUser, iSkillID);

			LANG_GetSkillName( iSkillID , idUser, szSkillName, 63, 1 );
			
			// Add the trainable skills to the menu
			if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_TRAINABLE )
			{

				// Only add it to the menu if they don't have level 3 already!
				if ( iSkillLevel < iMaxSkillLevel )
				{

					// User isn't high enough of a level to select this skill yet
					if ( arrIntData[idUser][P_LEVEL] <= 2 * iSkillLevel )
					{
						pos += formatex( szMsg[pos], charsmax(szMsg)-pos, "\d" );
					}

					// Then the user can choose it!
					else
					{
						iKeys |= (1<<iSkillCounter);
					}

					pos += formatex( szMsg[pos], charsmax(szMsg)-pos, "^n%d. %s %L %d\w", iSkillCounter+1, szSkillName, LANG_PLAYER, "WORD_LEVEL", iSkillLevel + 1 );
				}
			}
			
			// Add the ultimate to the menu
			else if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_ULTIMATE )
			{

				if (iSkillLevel < MAX_ULTIMATE_LEVEL)
				{
					// User can't choose ultimate yet :/
					if ( arrIntData[idUser][P_LEVEL] <= (iMinUltLevel-1) )
					{
						pos += formatex( szMsg[pos], charsmax(szMsg)-pos, "\d" );
					}

					// Then the user is level 6 or above and can select their ultimate!
					else
					{
						iKeys |= (1<<iSkillCounter);
					}

					pos += formatex( szMsg[pos], charsmax(szMsg)-pos, "^n%d. %L: %s\w", iSkillCounter+1, LANG_PLAYER, "WORD_ULTIMATE", szSkillName );
				}
			}

			iSkillCounter++;
			iSkillID = SM_GetSkillByPos( idUser, iSkillCounter );
		}

		// Add the cancel button to the menu
		pos += formatex( szMsg[pos], charsmax(szMsg)-pos, "^n^n\d0. %L", LANG_PLAYER, "WORD_CANCEL" );

		// Show the menu!
		show_menu( idUser, iKeys, szMsg, -1 );
	

	return;
}

public _MENU_SelectSkill( idUser, iKey )
{
	

		if ( !WC3_Check() || iKey == 9 )
			return PLUGIN_HANDLED;

		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_MENU_CLICK], 1.0, ATTN_NORM, 0, PITCH_NORM ); 

		// Determine which key was just selected
		new iSkillID = SM_GetSkillByPos( idUser, iKey );

		// Set up the skill!
		SM_SetSkill( idUser, iSkillID );
		
		new iSkillsUsed = SM_TotalSkillPointsUsed( idUser );
		
		// Then they have another skill to select!!
		if ( iSkillsUsed < arrIntData[idUser][P_LEVEL] )
		{
			MENU_SelectSkill( idUser );
		}

		// No more, lets show them their latest level/XP
		else
		{
			WC3_ShowBar( idUser );
		}

	

	return PLUGIN_HANDLED;
}

