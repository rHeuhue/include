#if defined _menu_included 
	#endinput
#endif

#define _menu_included 

#include <amxmodx>

/** 
	Меню статистики
 */
ShowStatsMenu(id) {
	new menu, title[196];
	formatex(title, charsmax(title),"%L",\
	 id, "CSRE_MAINMENU_STATS")

	menu = menu_create(title, "HandleStatsMenu")
	MenuSetProps(id, menu);

	formatex(title, charsmax(title), "%L^n", id, "CSRE_TOP15")
	menu_additem(menu, title, "1");

	// Статистика игроков
	formatex(title, charsmax(title), "%L", id, "CSRE_MENU_INFO_PLAYER")
	menu_additem(menu, title, "2");

	// Статистика игроков
	formatex(title, charsmax(title), "%L", id, "CSRE_INFO_PLAYER_RANK")
	menu_additem(menu, title, "3");

	menu_display(id, menu, 0)
}

public HandleStatsMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	new uid = str_to_num(data);
	
	switch(uid)
	{
		case 1: Sql_QueryTop(id) // TOP 15
		case 2: ShowInfoMenu(id);
		case 3: {
			Print(id, "%L", id, "CSRE_INFO_PLAYER_RANK")
			client_cmd(id, "say /csrank")
		}
	}

	return menu_destroy(menu);
}

ShowInfoMenu(id)
{
	new menu, title[128];
	formatex(title, charsmax(title),"%L",\
	 id, "CSRE_MAINMENU_STATS")
	
	menu = menu_create(title, "HandleInfoMenu")
	MenuSetProps(id, menu);
	new pid[6], name[32];
	
	static maxplayers;
	if( !maxplayers) maxplayers = get_maxplayers();
	
	for(new player = 1; player< maxplayers; player++)
	{
		if(!is_user_connected(player))
			continue;
	
		num_to_str(player, pid, charsmax(pid))
		get_user_name(player, name, charsmax(name))
		
		menu_additem(menu, name, pid);
	}
	
	menu_display(id, menu, 0)
}

public HandleInfoMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	new pid = str_to_num(data);
	if(!is_user_connected(pid))	return menu_destroy(menu)

	ShowPlayerInfoMenu(id, pid)
	return menu_destroy(menu);
}

ShowPlayerInfoMenu(id, pid) {
	
	new name[32];
	get_user_name(pid, name, charsmax(name))

	new menu, title[128];
	formatex(title, charsmax(title),"%L: %s",\
	 id, "CSRE_MAINMENU_STATS", name)
	
	menu = menu_create(title, "HandlePlayerInfoMenu")
	MenuSetProps(id, menu);

	formatex(title, charsmax(title),"%L: %d | %d", id, "CSRE_CURRENCY_EXP", g_player_stats[pid][PS_EXP], g_player_stats[pid][PS_EXP_TOTAL])
	menu_additem(menu, title, "1");

	formatex(title, charsmax(title),"%L: %d", id, "CSRE_CURRENCY_MEDALS", g_player_stats[pid][PS_MEDALS])
	menu_additem(menu, title, "2");

	formatex(title, charsmax(title),"%L: %d | %d", id, "CSRE_CURRENCY_CASES", g_player_stats[pid][PS_CASES], g_player_stats[pid][PS_CASES_TOTAL])
	menu_additem(menu, title, "3");

	formatex(title, charsmax(title),"%L: %d | %d", id, "CSRE_CURRENCY_KEYS", g_player_stats[pid][PS_KEYS], g_player_stats[pid][PS_KEYS_TOTAL])
	menu_additem(menu, title, "4");

	formatex(title, charsmax(title),"%L: %d | %d", id, "CSRE_CURRENCY_COINS", g_player_stats[pid][PS_COINS],g_player_stats[pid][PS_COINS_TOTAL])
	menu_additem(menu, title, "5");

	// formatex(title, charsmax(title),"%L: %d | %d", id, "CSRE_CURRENCY_GOLDS", g_player_stats[pid][PS_GOLDS],g_player_stats[pid][PS_GOLDS_TOTAL])
	// menu_additem(menu, title, "6");

	new tmp[32];
	formatex(tmp, charsmax(tmp), "7 %d", pid)

	formatex(title, charsmax(title),"%L", id, "CSRE_INFO_PLAYER_SKINS")
	menu_additem(menu, title, tmp);
	
	menu_display(id, menu, 0)
}

public HandlePlayerInfoMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowStatsMenu(id)
		return menu_destroy(menu);
	}
	
	new data[12], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,11, _dummy, charsmax(_dummy), callback);

	new _data[6], _pid[6];
	parse(data, _data, charsmax(_data), _pid, charsmax(_pid))

	if (str_to_num(_data) == 7) {
		new pid = str_to_num(_pid);

		if ( is_user_connected(pid) ) Sql_GetPlayerItems(id, "QueryInfoPlayerSkins", pid)
		return menu_destroy(menu);
	}

	ShowStatsMenu(id)	
	return menu_destroy(menu);
}

public QueryInfoPlayerSkins(id, Array:playerItems, player) {
	if ( !ArraySize(playerItems) ) {
		ArrayDestroy(playerItems);
		return Print(id, "%L", id, "CSRE_INFO_PLAYER_SKINS_EMPTY")
	}
	
	new name[32];
	get_user_name(player, name, charsmax(name))

	new menu, title[256];
	formatex(title, charsmax(title),"%L %s",id, "CSRE_INFO_PLAYER_SKINS", name)
	menu = menu_create(title, "HandleInfoSkinMenu")

	MenuSetProps(id, menu);

	new size = ArraySize(playerItems), item;
	
	new index, wid;
	new data[Items]
	new array[WEAPON_SIZE][3];

	new skinStr[SKIN_STR_LEN];

	for(new i; i< size; i++) {
		item = ArrayGetCell(playerItems, i);

		index = search_array(item);

		if(index < 0) continue;

		ArrayGetArray(g_Items, index, data)
		wid = get_weapon_csw(data[ITEM_REPLACE]);

		if ( isWeaponSkinOnPlayer(player, RE_TEAM_T, wid, item) ) {
			array[wid][RE_TEAM_T] = item;
		}

		if ( isWeaponSkinOnPlayer(player, RE_TEAM_CT, wid, item) ) {
			array[wid][RE_TEAM_CT] = item;
		}

		skinClassStr(data, title, charsmax(title))

		formatex(title, charsmax(title),"%s %s%s", title,
		(isItemsEquals(array[wid][RE_TEAM_T], item)) ? "\r[T]\w" : "",
		(isItemsEquals(array[wid][RE_TEAM_CT], item)) ? "\r[CT]\w" : "");
		
		num_to_str(item, skinStr, SKIN_STR_LEN - 1)
		menu_additem(menu, title, skinStr)
	}

	ArrayDestroy(playerItems);
	return menu_display(id, menu, 0)
}
public HandleInfoSkinMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowInfoMenu(id)
		return menu_destroy(menu);
	}
	
	new data[SKIN_STR_LEN + 2], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data, charsmax(data), _dummy, charsmax(_dummy), callback);


	ShowInfoMenu(id)
	return menu_destroy(menu);
}


/**
	Магазин
 */
ShowShopMenu(id)
{
	new menu, title[128];
	formatex(title, charsmax(title),"%L^n%L",\
	 id, "CSRE_MAINMENU_SHOP", id, "CSRE_SHOPMENU_COINS", g_player_stats[id][PS_COINS], g_player_stats[id][PS_COINS_TOTAL])
	
	menu = menu_create(title, "HandleShopMenu")
	MenuSetProps(id, menu);

	new containerCost = get_pcvar_num(g_Cvars[CVAR_CASE_PRICE]);
	
	formatex(title, charsmax(title), "%s%L", g_player_stats[id][PS_COINS] >= containerCost ? "\w" : "\d", id, "CSRE_SHOPMENU_BUY_CASE", containerCost)
	menu_additem(menu, title, "1");

	formatex(title, charsmax(title), "%s%L^n", g_player_stats[id][PS_COINS] >= containerCost * 5 ? "\y" : "\d", id, "CSRE_SHOPMENU_BUY_CASE", containerCost * 5)
	menu_additem(menu, title, "2");

	formatex(title, charsmax(title),"%L", id, "CSRE_SHOPMENU_RESET_PLAYER")
	menu_additem(menu, title, "3")

	formatex(title, charsmax(title), "%L^n", id, "CSRE_SHOPMENU_SALE")
	menu_additem(menu, title, "4")

	formatex(title, charsmax(title), "%L [ \r%d|%d \w]", id, "CSRE_REWARDS_MENU_TITLE", g_player_stats[id][PS_REWARDS], ArraySize(g_rewards))
	menu_additem(menu, title, "5")

	menu_display(id, menu, 0)
}
public HandleShopMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	new uid = str_to_num(data);
	
	switch(uid)
	{
		case 1: {
			new containerCost = get_pcvar_num(g_Cvars[CVAR_CASE_PRICE]);
			if (g_player_stats[id][PS_COINS] >= containerCost) {
				Stats_AddPlayerCoins(id, containerCost * (-1))
				Stats_AddPlayerCases(id, 1)

				Print(id, "%L", id, "CSRE_BUY_CASE", containerCost, 1)
			} else Print(id, "%L", id, "CSRE_BUY_CASE_FAIL", containerCost)

			ShowShopMenu(id)
		}
		case 2: {
			new containerCost = get_pcvar_num(g_Cvars[CVAR_CASE_PRICE]) * 5;
			if (g_player_stats[id][PS_COINS] >= containerCost) {
				Stats_AddPlayerCoins(id, containerCost * (-1))
				Stats_AddPlayerCases(id, 5)

				Print(id, "%L", id, "CSRE_BUY_CASE", containerCost, 5)
			} else Print(id, "%L", id, "CSRE_BUY_CASE_FAIL", containerCost)

			ShowShopMenu(id)
		}
		case 3: {
			Print(id, "%L", id, "CSRE_RESET_SKINS")
			Operation_ResetPlayerWeapon(id, true)
		}

		case 4: Sql_GetPlayerItems(id, "QuerySaleSkins")// OWN Skins
		case 5: ShowRewardsMenu(id)
		// case 1: item_create_menu(id, "SaleMenu");
		// case 2: ShowBuyMenu(id);

		// case 3: scase_create_case_menu(id, "SaleScaseMenu")
		// case 4: ShowBuyCaseMenu(id);

		// case 5: ResetSkins(id);
		//case 6: ShowWishesMenu(id);
	}

	return menu_destroy(menu);
}

public QuerySaleSkins(id, Array:playerItems, player) {
	if (player == id) player = id;
	
	if ( !ArraySize(playerItems) ) {
		ArrayDestroy(playerItems);
		return Print(id, "%L", id, "CSRE_MENU_EMPTY_SKINS")
	}

	new menu, title[256];
	formatex(title, charsmax(title),"%L",id, "CSRE_SHOPMENU_SALE")
	menu = menu_create(title, "HandleSaleSkinMenu")

	MenuSetProps(id, menu);

	new size = ArraySize(playerItems), item;
	
	new index, wid;
	new data[Items]
	new array[WEAPON_SIZE][3];

	new skinStr[SKIN_STR_LEN];

	for(new i; i< size; i++) {
		item = ArrayGetCell(playerItems, i)
		index = search_array(item);

		if(index < 0) continue;

		ArrayGetArray(g_Items, index, data)
		wid = get_weapon_csw(data[ITEM_REPLACE]);

		if ( isWeaponSkinOnPlayer(id, RE_TEAM_T, wid, item) ) {
			array[wid][RE_TEAM_T] = item;
		}

		if ( isWeaponSkinOnPlayer(id, RE_TEAM_CT, wid, item) ) {
			array[wid][RE_TEAM_CT] = item;
		}

		skinClassStr(data, title, charsmax(title))

		formatex(title, charsmax(title),"%s [%d] %s%s", title, get_sale_price(data[ITEM_CLASS]),
		(isItemsEquals(array[wid][RE_TEAM_T], item)) ? "\r[T]\w" : "",
		(isItemsEquals(array[wid][RE_TEAM_CT], item)) ? "\r[CT]\w" : "");
		
		num_to_str(item, skinStr, SKIN_STR_LEN - 1)
		menu_additem(menu, title, skinStr)
	}

	ArrayDestroy(playerItems);
	return menu_display(id, menu, 0)
}
public HandleSaleSkinMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[SKIN_STR_LEN + 2], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data, charsmax(data), _dummy, charsmax(_dummy), callback);

	new item = str_to_num(data)

	new _data[Items];
	ArrayGetArray(g_Items, search_array(item), _data)

	if ( Operation_RemovePlayerItem(id, item) ) {
		new price = get_sale_price(_data[ITEM_CLASS]);
		Stats_AddPlayerCoins(id, price)

		Print(id, "%L", id, "CSRE_SALE_SKIN", _data[ITEM_NAME], price)
	} else {
		Print(id, "[^3Error^1]Something was wrong...")
	}

	ShowShopMenu(id);
	return menu_destroy(menu);
}

ShowRewardsMenu(id) {
	if ( !Rewards_isEnabled() ) {
		return Print(id, "%L", id, "CSRE_REWARDS_DISABLED")
	}

	new time[32];
	format_time(time, charsmax(time), "%H[H]:%M[M]:%S[S]", g_player_data[id][PD_CHECK_TIME] - get_systime(0))

	new menu, title[128], str[16];
	formatex(title, charsmax(title),"%L^n%s", id, "CSRE_REWARDS_MENU_TITLE", time)
	
	menu = menu_create(title, "HandleRewardsMenu")
	MenuSetProps(id, menu);

	new size = ArraySize(g_rewards), data[RewardsArray], rewards = g_player_stats[id][PS_REWARDS] ? (g_player_stats[id][PS_REWARDS] -1) : 0;
	for(new i; i< size; i++) {
		ArrayGetArray(g_rewards, i, data)

		Rewards_getReward(id, data[RA_TYPE], data[RA_COUNT], title, charsmax(title))
		num_to_str(i, str, charsmax(str))

		format(title, charsmax(title), "%s%s", rewards > i ? "\d" : (rewards == i ? "\y" : "\w"), title)
		menu_additem(menu, title, str)
	}

	return menu_display(id, menu, 0)
}

public HandleRewardsMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[SKIN_STR_LEN + 2], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data, charsmax(data), _dummy, charsmax(_dummy), callback);

	ShowRewardsMenu(id)
	return menu_destroy(menu);
}

ShowMainEventsMenu(id) {
	new eventName[32];
	formatex(eventName, charsmax(eventName), "%L", id, "CSRE_EVENT_EMPTY")

	if ( g_Event > 0 ) {
		new event[Events]
		event = Events_getEventInfo(g_Event)
		formatex(eventName, charsmax(eventName), "%s", event[EVENT_NAME])
	}
	
	new menu, title[192];
	formatex(title, charsmax(title),"%L^n%L",\
	 id, "CSRE_EVENT_MAIN_TITLE", id, "CSRE_EVENT_CURRENT_TITLE", eventName)

	menu = menu_create(title, "HandleMainEventsMenu")
	MenuSetProps(id, menu);

	formatex(title, charsmax(title), "%L \y[%d]^n", id, "CSRE_EVENT_MENU_ALL", ArraySize(g_events))
	menu_additem(menu, title, "1");

	// Информация о текущем эвенте
	formatex(title, charsmax(title), "%L", id, "CSRE_EVENT_MENU_CURRENT_INFO")
	menu_additem(menu, title, "2");

	menu_display(id, menu, 0)
}

public HandleMainEventsMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	new uid = str_to_num(data);
	
	switch(uid)
	{
		case 1: ShowAllEventsMenu(id)
		case 2: if (g_Event) ShowEventInfoMenu(id, g_Event);
	}

	return menu_destroy(menu);
}

ShowAllEventsMenu(id) {
	new menu, title[192];
	formatex(title, charsmax(title),"%L",\
	 id, "CSRE_EVENT_MENU_ALL")

	menu = menu_create(title, "HandleAllEventsMenu")
	MenuSetProps(id, menu);

	new data[Events], szCount[6], eventsSize = ArraySize(g_events);
	for(new i; i< eventsSize; i++) {
		ArrayGetArray(g_events, i, data);

		num_to_str(data[EVENT_ID], szCount, charsmax(szCount))
		formatex(title, charsmax(title), "%s", data[EVENT_NAME])
		menu_additem(menu, title, szCount);
	}

	menu_display(id, menu, 0)
}

public HandleAllEventsMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	new event_id = str_to_num(data);

	ShowEventInfoMenu(id, event_id)
	return menu_destroy(menu);
}

ShowEventInfoMenu(id, event_id) {
	new data[Events];
	data = Events_getEventInfo(event_id);

	new menu, title[192];
	formatex(title, charsmax(title),"%L",
	 id, "CSRE_EVENT_MENU_CURRENT_INFO")

	menu = menu_create(title, "HandleEventInfoMenu")
	MenuSetProps(id, menu);

	formatex(title, charsmax(title), "%s", data[EVENT_NAME])
	menu_additem(menu, title, "1");

	new startDate[22], endDate[22];
	getEventDate(data, startDate, charsmax(startDate), endDate, charsmax(endDate))

	formatex(title, charsmax(title), "%L", id, "CSRE_EVENT_INFO_START", startDate)
	menu_additem(menu, title, "2");

	formatex(title, charsmax(title), "%L^n", id, "CSRE_EVENT_INFO_END", endDate)
	menu_additem(menu, title, "3");

	if (data[EVENT_ITEMS] && ArraySize(data[EVENT_ITEMS])) {
		new size = ArraySize(data[EVENT_ITEMS])

		new _data[Items];
		new pid[10]
		for(new i; i<size; i++) {
			num_to_str(i + 4, pid, charsmax(pid))
			new cell = ArrayGetCell(data[EVENT_ITEMS], i);
			server_print("Cell: %d | %d", cell, search_array(cell))
			ArrayGetArray(g_Items, search_array(cell), _data);

			skinClassStr(_data, title, charsmax(title))

			formatex(title, charsmax(title),"%s", title);
			menu_additem(menu, title, pid);
		}
	}

	menu_display(id, menu, 0)
}

public HandleEventInfoMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	ShowMainEventsMenu(id)
	return menu_destroy(menu);
}

stock ShowContainerMenu(id) {
	new menu, title[192];
	formatex(title, charsmax(title),"%L",\
	 id, "CSRE_CONTAINER_MENU_TITLE")

	menu = menu_create(title, "HandleContainerMenu")
	MenuSetProps(id, menu);

	formatex(title, charsmax(title), "%L^n", id, "CSRE_OPEN_MENU", g_player_stats[id][PS_CASES])
	menu_additem(menu, title, "1");

	if (g_Event) {
		new data[Events];
		data = Events_getEventInfo(g_Event);

		formatex(title, charsmax(title), "%L \y'%s' \r[%d]", id, "CSRE_CONTAINER_TEXT", data[EVENT_NAME], g_player_stats[id][PS_KEYS])
		menu_additem(menu, title, "2");
	}

	menu_display(id, menu, 0)
}

public HandleContainerMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	new uid = str_to_num(data)

	switch(uid) {
		case 1: {
			GiveItem(id, true, false)
			ShowContainerMenu(id)
		}
		case 2: {
			if (!g_Event)
				return menu_destroy(menu)

			GiveItem(id, true, true)
			ShowContainerMenu(id)
		}
	}
	return menu_destroy(menu);
}