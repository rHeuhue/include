
public WC3_Admin_Menu(id, level, cid)
{
	if (!WC3_Check())
		return PLUGIN_HANDLED;

	if (!cmd_access(id, level, cid, 1))
		return PLUGIN_HANDLED;

	ToggleAdminMenu(id);

	return PLUGIN_HANDLED;
}

public ToggleAdminMenu(id)
{
	new iMenu = menu_create(fmt("\yWC3 Admin Menu\R"), "admin_menu_handler");
	
	menu_additem(iMenu, "Experience \d& \wLevel");
	menu_additem(iMenu, "Shop Items");
	menu_additem(iMenu, "Gold");
	
	menu_setprop(iMenu, MPROP_NUMBER_COLOR, "\y");
	menu_display(id, iMenu, 0);
	return PLUGIN_HANDLED;
	
}

public admin_menu_handler(id, iMenu, Item)
{
	switch(Item)
	{
		case MENU_EXIT:
		{
			menu_destroy(iMenu);
			return PLUGIN_HANDLED;
		}
		case 0: ToggleExperienceMenu(id);
		case 1: ToggleItemsMenu(id);
		case 2: ToggleGoldMenu(id);
	}
	
	menu_destroy(iMenu);
	return PLUGIN_HANDLED;
}

public ToggleExperienceMenu(id)
{
	new iMenu = menu_create("\yExperience & Level\R", "exp_menu_handler");

	menu_additem(iMenu, "Give Player Experience");
	menu_additem(iMenu, "Take Player Experience");
	menu_additem(iMenu, "Set Player Level");

	menu_setprop(iMenu, MPROP_NUMBER_COLOR, "\y");
	menu_setprop(iMenu, MPROP_EXITNAME, "\wBack to WC3 Admin Menu\d..");
	menu_display(id, iMenu, 0);
	return PLUGIN_HANDLED;
}

public exp_menu_handler(id, iMenu, Item)
{
	switch(Item)
	{
		case MENU_EXIT:
		{
			ToggleAdminMenu(id);
			return PLUGIN_HANDLED;
		}
		case 0: PlayerExpMenu(id, WC3_GIVEXP);
		case 1: PlayerExpMenu(id, WC3_TAKEXP);
		case 2: PlayerExpMenu(id, WC3_SETLEVEL);
	}
	menu_destroy(iMenu);
	return PLUGIN_HANDLED;
}

public PlayerExpMenu(id, eMENUS:iType)
{
	new szTitle[64];
	formatex(szTitle, charsmax(szTitle), "\yChose Player to \r%s \w%s\y\R", iType == WC3_GIVEXP ? "Give" : iType == WC3_TAKEXP ? "Take" : "Set", iType == WC3_SETLEVEL ? "Level" : "Experience");

	new iMenu = menu_create(szTitle, "player_exp_menu_handler");

	g_iMenuType[id] = iType;

	new iPlayers[MAX_PLAYERS], iNum, iPlayer;
	new szTempID[10];

	get_players(iPlayers, iNum);

	for(--iNum; iNum >= 0; iNum--)
	{
		iPlayer = iPlayers[iNum];

		if (!is_user_connected(iPlayer))
				continue;

		num_to_str(iPlayer, szTempID, charsmax(szTempID));
		menu_additem(iMenu, fmt("%n", iPlayer), szTempID);
	}	
	menu_setprop(iMenu, MPROP_NUMBER_COLOR, "\y");
	menu_setprop(iMenu, MPROP_EXITNAME, "\wBack to \rExperience & Level \wMenu\d..");
	menu_display(id, iMenu, 0);
	return PLUGIN_HANDLED;
}

public player_exp_menu_handler(id, iMenu, Item)
{
	if (Item == MENU_EXIT)
	{
		menu_destroy(iMenu);
		ToggleExperienceMenu(id);
		g_iMenuType[id] = WC3_NONE;
		return PLUGIN_HANDLED;
	}

	new szData[6], iName[64], iAccess, iCallBack;
	menu_item_getinfo(iMenu, Item, iAccess, szData, charsmax(szData), iName, charsmax(iName), iCallBack);
	
	g_iPlayer[id] = str_to_num(szData);

	if (!is_user_connected(g_iPlayer[id]))
	{
		g_iPlayer[id] = 0;
		client_print_color(id, print_team_default, "^4%s ^3The player you chose is not in the server.", GAME_NAME);
		return PLUGIN_HANDLED;
	}

	client_print_color(id, print_team_default, "^4%s ^3Player ^1%s ^3is ^1Level %i ^3with ^4%i Experience^3.", GAME_NAME, iName, XP_GetLevelByXP(p_data[g_iPlayer[id]][P_XP]), p_data[g_iPlayer[id]][P_XP]);

	switch(g_iMenuType[id])
	{
		case WC3_GIVEXP: client_cmd(id, "messagemode XP_Amount");
		case WC3_TAKEXP: client_cmd(id, "messagemode XP_Amount");
		case WC3_SETLEVEL: client_cmd(id, "messagemode Set_Level");
	}
	menu_destroy(iMenu)
	return PLUGIN_HANDLED
}

public WC3_XP_Amount(id, level, cid)
{
	if (!cmd_access(id, level, cid, 1))
		return PLUGIN_HANDLED;
		
	if (!g_iPlayer[id])
		return PLUGIN_HANDLED;
		
	if (!is_user_connected(g_iPlayer[id]))
	{
		client_print_color(id, print_team_default, "^4%s ^3The player you chose is not in the server.", GAME_NAME);
		return PLUGIN_HANDLED;
	}
	
	new szArgs[12];
	read_argv(1, szArgs, charsmax(szArgs));
	
	new iXP = str_to_num(szArgs);
	
	switch (g_iMenuType[id])
	{
		case WC3_GIVEXP:
		{
			ADMIN_SetXP(g_iPlayer[id], p_data[g_iPlayer[id]][P_XP] + iXP);

			client_print_color(0, print_team_default, "^3ADMIN ^4%n^3: gave ^1%i Experience ^3to ^4%n^3.", id, iXP, g_iPlayer[id]);
		}
		case WC3_TAKEXP:
		{
			ADMIN_SetXP(g_iPlayer[id], p_data[g_iPlayer[id]][P_XP] - iXP);

			client_print_color(0, print_team_default, "^3ADMIN ^4%n^3: took ^1%i Experience ^3from ^4%n^3.", id, iXP, g_iPlayer[id]);
		}
	}
	g_iPlayer[id] = 0;
	g_iMenuType[id] = WC3_NONE;
	
	ToggleAdminMenu(id);
	
	return PLUGIN_HANDLED
}

public WC3_Level_Set(id, level, cid)
{
	if (!cmd_access(id, level, cid, 1))
		return PLUGIN_HANDLED;
		
	if (!g_iPlayer[id])
		return PLUGIN_HANDLED;
		
	if (!is_user_connected(g_iPlayer[id]))
	{
		client_print_color(id, print_team_default, "^4%s ^3The player you chose is not in the server.", GAME_NAME);
		return PLUGIN_HANDLED;
	}
	
	new szArgs[12];
	read_argv(1, szArgs, charsmax(szArgs));
	
	new iLevel = str_to_num(szArgs);
	
	if (iLevel < 0 || iLevel >= MAX_LEVELS+1)
	{
		client_print_color(id, print_team_default, "^4%s ^3You can set level in between 0 and %i only!", GAME_NAME, MAX_LEVELS);

		PlayerExpMenu(id, g_iMenuType[id])
		return PLUGIN_HANDLED;
	}

	new iXP = XP_GetByLevel(iLevel);

	ADMIN_SetXP(g_iPlayer[id], iXP);
	
	client_print_color(0, print_team_default, "^3ADMIN ^4%n^3: set ^1Level %i ^3to ^4%n", id, iLevel, g_iPlayer[id]);

	g_iPlayer[id] = 0;
	g_iMenuType[id] = WC3_NONE;
	
	ToggleAdminMenu(id);
	
	return PLUGIN_HANDLED;
}

// Items Stuff
public ToggleItemsMenu(id)
{
	new iMenu = menu_create("\yShop Items\R", "shopitems_menu_handler");

	menu_additem(iMenu, "Give Player Item");
	menu_additem(iMenu, "Remove Player Item");

	menu_setprop(iMenu, MPROP_NUMBER_COLOR, "\y");
	menu_setprop(iMenu, MPROP_EXITNAME, "\wBack to WC3 Admin Menu\d..");
	menu_display(id, iMenu, 0);
	return PLUGIN_HANDLED;
}

public shopitems_menu_handler(id, iMenu, Item)
{
	switch(Item)
	{
		case MENU_EXIT:
		{
			ToggleAdminMenu(id);
			return PLUGIN_HANDLED;
		}
		case 0: PlayerItemMenu(id, WC3_GIVEITEM);
		case 1: PlayerItemMenu(id, WC3_REMOVEITEM);
	}

	menu_destroy(iMenu);
	return PLUGIN_HANDLED;
}

public PlayerItemMenu(id, eMENUS:iType)
{
	new szTitle[64];
	formatex(szTitle, charsmax(szTitle), "\yChose Player to \r%s \yItem\R", iType == WC3_GIVEITEM ? "Give" : "Remove");

	new iMenu = menu_create(szTitle, "player_item_menu_handler");

	g_iMenuType[id] = iType;

	new iPlayers[MAX_PLAYERS], iNum, iPlayer;
	new szTempID[10];

	get_players(iPlayers, iNum);

	for(--iNum; iNum >= 0; iNum--)
	{
		iPlayer = iPlayers[iNum];

		if (!is_user_connected(iPlayer))
				continue;

		num_to_str(iPlayer, szTempID, charsmax(szTempID));
		menu_additem(iMenu, fmt("%n", iPlayer), szTempID);
	}	

	menu_setprop(iMenu, MPROP_NUMBER_COLOR, "\y");
	menu_setprop(iMenu, MPROP_EXITNAME, "\wBack to \rShop Items \wMenu\d..");
	menu_display(id, iMenu, 0);
	return PLUGIN_HANDLED;
}

public player_item_menu_handler(id, iMenu, Item)
{
	if (Item == MENU_EXIT)
	{
		menu_destroy(iMenu);
		ToggleItemsMenu(id);
		g_iMenuType[id] = WC3_NONE;
		return PLUGIN_HANDLED;
	}

	new szData[6], iName[64], iAccess, iCallBack, iShopItem[2];
	menu_item_getinfo(iMenu, Item, iAccess, szData, charsmax(szData), iName, charsmax(iName), iCallBack);
	
	g_iPlayer[id] = str_to_num(szData);

	iShopItem[ITEM_SLOT_ONE] = -1;
	iShopItem[ITEM_SLOT_TWO] = -1;

	if (!is_user_connected(g_iPlayer[id]))
	{
		g_iPlayer[id] = 0;
		client_print_color(id, print_team_default, "^4%s ^3The player you chose is not in the server.", GAME_NAME);
		return PLUGIN_HANDLED;
	}

	for (new i = 0; i <= 18; i++)
	{
		if (g_iShopMenuItems[g_iPlayer[id]][ITEM_SLOT_ONE] == i)
			iShopItem[ITEM_SLOT_ONE] = i
		else if (g_iShopMenuItems[g_iPlayer[id]][ITEM_SLOT_TWO] == i)
			iShopItem[ITEM_SLOT_TWO] = i
	}

	if (iShopItem[ITEM_SLOT_ONE] != -1 && iShopItem[ITEM_SLOT_TWO] != -1)
	{
		client_print_color(id, print_team_default, "^4%s ^3Player ^1%s ^3has item ^1%s ^3and ^1%s", GAME_NAME, iName, Lang_ItemDatabase[iShopItem[ITEM_SLOT_ONE]][ITEM_NAME_LONG], Lang_ItemDatabase[iShopItem[ITEM_SLOT_TWO]][ITEM_NAME_LONG]);
		
		if (g_iMenuType[id] == WC3_GIVEITEM)
		{
			ToggleAdminMenu(id);
			client_print_color(id, print_team_default, "^4%s ^3First remove one item from ^1%s slot^3!", GAME_NAME, iName);
			return PLUGIN_HANDLED;
		}
	}
	else if (iShopItem[ITEM_SLOT_ONE] != -1 && iShopItem[ITEM_SLOT_TWO] == -1)
	{
		client_print_color(id, print_team_default, "^4%s ^3Player ^1%s ^3has item ^1%s ^3and free slot", GAME_NAME, iName, Lang_ItemDatabase[iShopItem[ITEM_SLOT_ONE]][ITEM_NAME_LONG]);
	}
	else
	{
		client_print_color(id, print_team_default, "^4%s ^3Player ^1%s ^3doesn't have any item", GAME_NAME, iName);
	}

	ShopItemsMenu(id);

	menu_destroy(iMenu);
	return PLUGIN_HANDLED;
}

public ShopItemsMenu(id)
{
	new iMenu = menu_create(fmt("\yChoose to \r%s \yShop Item\R", g_iMenuType[id] == WC3_GIVEITEM ? "Give" : "Remove"), "shop_items_handler");
	
	new szTempID[10]
	
	for(new i = 0; i <= 18; i++)
	{
		num_to_str(i, szTempID, charsmax(szTempID));
		menu_additem(iMenu, Lang_ItemDatabase[i][ITEM_NAME_LONG], szTempID);
	}
	menu_setprop(iMenu, MPROP_NUMBER_COLOR, "\y");
	menu_setprop(iMenu, MPROP_EXITNAME, "\wBack to \rShop Items \wMenu\d..");
	menu_display(id, iMenu, 0);
	return PLUGIN_HANDLED;
}

public shop_items_handler(id, iMenu, Item)
{
	if (Item == MENU_EXIT)
	{
		ToggleItemsMenu(id);
		return PLUGIN_HANDLED;
	}
	
	new szData[6], iAccess, iCallBack;
	menu_item_getinfo(iMenu, Item, iAccess, szData, charsmax(szData), _, _, iCallBack);
	
	new iItemID = str_to_num(szData);

	switch (g_iMenuType[id])
	{
		case WC3_GIVEITEM:
		{
			ITEM_GiveItem(g_iPlayer[id], iItemID);
			client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: gave item ^1%s ^4to ^3%n^4.", id, Lang_ItemDatabase[iItemID][ITEM_NAME_LONG], g_iPlayer[id]);
		}
		case WC3_REMOVEITEM:
		{
			ITEM_RemoveID(g_iPlayer[id], iItemID);
			client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: remove item ^1%s ^4from ^3%n^4.", id, Lang_ItemDatabase[iItemID][ITEM_NAME_LONG], g_iPlayer[id]);
		}
	}
	
	g_iPlayer[id] = 0;
	g_iMenuType[id] = WC3_NONE;
	
	ToggleAdminMenu(id);
	
	menu_destroy(iMenu);
	return PLUGIN_HANDLED;
}

// Gold stuff
public ToggleGoldMenu(id)
{
	new iMenu = menu_create("\yGold\R", "gold_menu_handler");

	menu_additem(iMenu, "Give Player Gold");
	menu_additem(iMenu, "Take Player Gold");
	menu_additem(iMenu, "Reset Player Gold");

	menu_setprop(iMenu, MPROP_NUMBER_COLOR, "\y");
	menu_setprop(iMenu, MPROP_EXITNAME, "\wBack to WC3 Admin Menu\d..");
	menu_display(id, iMenu, 0);
	return PLUGIN_HANDLED;
}

public gold_menu_handler(id, iMenu, Item)
{
	switch(Item)
	{
		case MENU_EXIT:
		{
			ToggleAdminMenu(id);
			return PLUGIN_HANDLED;
		}
		case 0: PlayerGoldMenu(id, WC3_GIVEGOLD);
		case 1: PlayerGoldMenu(id, WC3_TAKEGOLD);
		case 2: PlayerGoldMenu(id, WC3_RESETGOLD);
	}

	menu_destroy(iMenu);
	return PLUGIN_HANDLED;
}

public PlayerGoldMenu(id, eMENUS:iType)
{
	new szTitle[64];
	formatex(szTitle, charsmax(szTitle), "\yChose Player to \r%s \yGold\R", iType == WC3_GIVEGOLD ? "Give" : iType == WC3_TAKEGOLD ? "Take" : "Reset");

	new iMenu = menu_create(szTitle, "player_gold_menu_handler");

	g_iMenuType[id] = iType;

	new iPlayers[MAX_PLAYERS], iNum, iPlayer;
	new szTempID[10];

	get_players(iPlayers, iNum);

	for(--iNum; iNum >= 0; iNum--)
	{
		iPlayer = iPlayers[iNum];

		if (!is_user_connected(iPlayer))
				continue;

		num_to_str(iPlayer, szTempID, charsmax(szTempID));
		menu_additem(iMenu, fmt("%n", iPlayer), szTempID);
	}	

	menu_setprop(iMenu, MPROP_NUMBER_COLOR, "\y");
	menu_setprop(iMenu, MPROP_EXITNAME, "\wBack to Gold Menu\d..");
	menu_display(id, iMenu, 0);
	return PLUGIN_HANDLED;
}

public player_gold_menu_handler(id, iMenu, Item)
{
	if (Item == MENU_EXIT)
	{
		menu_destroy(iMenu);
		ToggleGoldMenu(id);
		g_iMenuType[id] = WC3_NONE;
		return PLUGIN_HANDLED;
	}

	new szData[6], iName[64], iAccess, iCallBack;
	menu_item_getinfo(iMenu, Item, iAccess, szData, charsmax(szData), iName, charsmax(iName), iCallBack);
	
	g_iPlayer[id] = str_to_num(szData);

	if (!is_user_connected(g_iPlayer[id]))
	{
		g_iPlayer[id] = 0;
		client_print_color(id, print_team_default, "^4%s ^3The player you chose is not in the server.", GAME_NAME);
		return PLUGIN_HANDLED;
	}

	client_print_color(id, print_team_default, "^4%s ^3Player ^1%s ^3has ^1%i Gold^3.", GAME_NAME, iName, get_user_gold(g_iPlayer[id]));

	switch(g_iMenuType[id])
	{
		case WC3_GIVEGOLD: client_cmd(id, "messagemode Gold_Amount");
		case WC3_TAKEGOLD: client_cmd(id, "messagemode Gold_Amount");
		case WC3_RESETGOLD: ResetPlayerGold(id, g_iPlayer[id]);
	}
	menu_destroy(iMenu)
	return PLUGIN_HANDLED
}

public WC3_Gold_Amount(id, level, cid)
{
	if (!cmd_access(id, level, cid, 1))
		return PLUGIN_HANDLED;
		
	if (!g_iPlayer[id])
		return PLUGIN_HANDLED;
		
	if (!is_user_connected(g_iPlayer[id]))
	{
		client_print_color(id, print_team_default, "^4%s ^3The player you chose is not in the server.", GAME_NAME);
		return PLUGIN_HANDLED;
	}
	
	new szArgs[12];
	read_argv(1, szArgs, charsmax(szArgs));
	
	new iGold = str_to_num(szArgs);
	
	switch (g_iMenuType[id])
	{
		case WC3_GIVEGOLD:
		{
			set_user_gold(g_iPlayer[id], get_user_gold(g_iPlayer[id]) + iGold);

			client_print_color(0, print_team_default, "^3ADMIN ^4%n^3: gave ^1%i Gold ^3to ^4%n^3.", id, iGold, g_iPlayer[id]);
		}
		case WC3_TAKEGOLD:
		{
			set_user_gold(g_iPlayer[id], get_user_gold(g_iPlayer[id]) - iGold);

			client_print_color(0, print_team_default, "^3ADMIN ^4%n^3: took ^1%i Gold ^3from ^4%n^3.", id, iGold, g_iPlayer[id]);
		}
	}
	g_iPlayer[id] = 0;
	g_iMenuType[id] = WC3_NONE;
	
	ToggleAdminMenu(id);
	
	return PLUGIN_HANDLED
}

public ResetPlayerGold(id, iPlayer)
{
	if (!is_user_connected(id) || !is_user_connected(iPlayer))
		return PLUGIN_HANDLED;

	set_user_gold(iPlayer, 0);
	client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: reset ^1Gold ^4to ^3%n^4.", id, iPlayer);

	g_iPlayer[id] = 0;
	g_iMenuType[id] = WC3_NONE;
	ToggleAdminMenu(id);
	return PLUGIN_HANDLED;
}