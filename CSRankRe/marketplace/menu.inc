#if defined _mk_menu_included 
	#endinput
#endif

#define _mk_stock_included 

#include <amxmodx>

stock ViewAllOffers(id, type = 0)
{
	new menu, title[196];

	formatex(title, charsmax(title),"%L",\
	 id, "CSRE_MARKETPLACE_TITLE")
	
	menu = menu_create(title, "HandleAllOffers")
	
	new data[mpArray], _data[Items], __data[Items];
	new size = ArraySize(g_marketplace_offers);

	if (size <= 0)
		return Print(id, "%L", id, "CSRE_MARKETPLACE_CLEAR")

	new index = 0;
	
	switch(type)
	{
		case 1: index = id;
		default: index = 0;
	}

	new text[64], str[12];
	new name[32];

	new skinClassColor[2][32];

	for(new i = 0; i< size; i++)
	{
		ArrayGetArray(g_marketplace_offers, i, data)
		
		if (data[MP_FOR] == index && data[MP_STATUS] == 1)
		{
			get_user_name(data[MP_ID], name, charsmax(name))
			ArrayGetArray(g_Items, search_array(data[MP_ITEM]), _data)

			skinClassStr(_data, skinClassColor[0], charsmax(skinClassColor[]))

			if (data[MP_TYPE] == 1) {
				ArrayGetArray(g_Items, search_array(data[MP_PRICE]), __data)
				skinClassStr(__data, skinClassColor[1], charsmax(skinClassColor[]))

				formatex(text, charsmax(text), "%s: <%s\w> -> <%s\w>", name, skinClassColor[0], skinClassColor[1])
			} else formatex(text, charsmax(text), "%s: <%s\w> -> <%d>", name, skinClassColor[0], data[MP_PRICE])
		
			
			formatex(str, charsmax(str), "%d %d", i, data[MP_ITEM])
		
			menu_additem(menu, text, str)
		}
	}

	menu_setprop(menu, MPROP_PERPAGE, 4)
	return menu_display(id, menu, 0)
}
public HandleAllOffers(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		Market_MainMenu(id)
		return menu_destroy(menu);
	}
	
	new _data[12], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, _data,11, _dummy, charsmax(_dummy), callback);

	new _uid[5], _check[5];
	parse(_data, _uid, charsmax(_uid), _check, charsmax(_check))
	
	new uid = str_to_num(_uid);
	
	if( uid >= ArraySize(g_marketplace_offers) )
		return Print(id, "%L", id, "CSRE_MARKETPLACE_ERROR")

	ViewOfferMenu(id, uid)
	return menu_destroy(menu);
}

stock ChoosePlayerFor(id)
{
	new menu, title[196];
	formatex(title, charsmax(title),"%L",
	 id, "CSRE_MARKETPLACE_TITLE")
	
	menu = menu_create(title, "HandleChooseForMenu")
	new pid[6], name[32];
	
	static maxplayers;
	if( !maxplayers) maxplayers = get_maxplayers();
	
	for(new player = 1; player<= maxplayers; player++)
	{
		if(!is_user_connected(player))
			continue;
	
		num_to_str(player, pid, charsmax(pid))
		get_user_name(player, name, charsmax(name))
		
		menu_additem(menu, name, pid);
	}
	
	menu_display(id, menu, 0)
}
public HandleChooseForMenu(id, menu, item)
{
	if(item == MENU_EXIT)
		return menu_destroy(menu);
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	new pid = str_to_num(data);
	
	if(!is_user_connected(pid))
		return menu_destroy(menu);
		
	g_marketplace_for[id] = pid;

	switch (g_marketplace_type[id]) {
		case 1: Market_AllSkinMenu(id)
		default: {
			Print(id, "%L",id, "CSRE_MARKETPLACE_ENTERCOST")
			client_cmd(id, "messagemode CSR_SetMoney")
		}
	}
	
	
	return menu_destroy(menu);
}

public QueryLoadSkinsMarket(id, Array:playerItems, player) {
	if (player == id) player = id;

	if ( !ArraySize(playerItems) ) {
		ArrayDestroy(playerItems);
		return Print(id, "%L", id, "CSRE_INFO_PLAYER_SKINS_EMPTY")
	}

	new menu, title[128];
	formatex(title, charsmax(title),"%L",id, "CSRE_MARKETPLACE_TITLE")
	menu = menu_create(title, "HandleMarketSkinMenu")

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

		if ( isWeaponSkinOnPlayer(id, RE_TEAM_T, wid, item) ) {
			array[wid][RE_TEAM_T] = item;
		}

		if ( isWeaponSkinOnPlayer(id, RE_TEAM_CT, wid, item) ) {
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
public HandleMarketSkinMenu(id, menu, item)
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
	g_marketplace_item[id] = item;

	Market_ChooseType(id);
	return menu_destroy(menu);
}

public Market_ChooseType(id) {
	new menu, title[128];
	formatex(title, charsmax(title),"%L",id, "CSRE_MARKETPLACE_TYPE_TITLE")
	menu = menu_create(title, "HandleMarketTypeMenu")

	MenuSetProps(id, menu);

	formatex(title, charsmax(title),"%L", id, "CSRE_MARKETPLACE_TYPE_COINS")
	menu_additem(menu, title, "0");

	formatex(title, charsmax(title),"%L", id, "CSRE_MARKETPLACE_TYPE_ITEM")
	menu_additem(menu, title, "1");

	menu_display(id, menu, 0)
}
public HandleMarketTypeMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		ShowMainMenu(id)
		return menu_destroy(menu);
	}
	
	new data[SKIN_STR_LEN + 2], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data, charsmax(data), _dummy, charsmax(_dummy), callback);

	g_marketplace_type[id] = str_to_num(data);

	switch (g_marketplace_type[id]) {
		case 1:	{

			if (g_marketplace_for[id] == -1) {
				ChoosePlayerFor(id)
			} else {
				Market_AllSkinMenu(id)
			}

		}
		default: {

			if (g_marketplace_for[id] == -1) {
				ChoosePlayerFor(id)
			} else {
				Print(id, "%L",id, "CSRE_MARKETPLACE_ENTERCOST") 
				client_cmd(id, "messagemode CSR_SetMoney")	
			}
		
		}
	}
	return menu_destroy(menu);
}

stock Market_AllSkinMenu(id) {
	new menu, title[128];
	formatex(title, charsmax(title),"%L",\
	 id, "CSRE_MARKETPLACE_TYPE_ITEM_TITLE")
	
	menu = menu_create(title, "HandleMarketAllSkinMenu")
	
	new data[Items], pid[10], temp[128];
	new size = ArraySize(g_Items)
	for(new i = 0; i < size; i++)
	{
		ArrayGetArray(g_Items, i, data)
		num_to_str(data[ITEM_ID], pid, charsmax(pid))
	
		formatex(temp, charsmax(temp), "%s%s", (data[ITEM_CLASS] == 3) ? "\y" : data[ITEM_CLASS] == 2 ? "\r" : "\w",data[ITEM_NAME])
		menu_additem(menu, temp, pid);
	}
	
	MenuSetProps(id, menu);
	menu_display(id, menu, 0)
}

public HandleMarketAllSkinMenu(id, menu, item)
{
	if(item == MENU_EXIT)
		return menu_destroy(menu);
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	new pid = str_to_num(data);
	g_marketplace_price[id] = pid;

	AddToMarketplace(id);
	return menu_destroy(menu);
}