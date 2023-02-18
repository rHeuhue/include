#if defined _mp_included
	#endinput
#endif

#define _mp_included

#include <amxmodx>
#include <sqlx>

#include <CSRankRe/marketplace/stock> 
#include <CSRankRe/marketplace/menu> 
new Market_MaxOffers = 0;

stock Market_init()
{
	g_marketplace_offers = ArrayCreate(mpArray);
}

stock Market_end() {
	ArrayDestroy(g_marketplace_offers)
}

stock Market_ResetPlayer(id, bool:hard = false)
{
	g_marketplace_item[id] 			= 0;
	g_marketplace_price[id] 		= 0;
	g_marketplace_for[id] 			= 0;
	g_marketplace_time[id] 			= 0;
	g_marketplace_offer_time[id] 	= 0;
	g_marketplace_type[id]			= 0;

	if (hard) {
		g_marketplace_count[id] 		= 0;
	}
}

stock Market_MainMenu(id) {
	if (!Market_MaxOffers) Market_MaxOffers = get_pcvar_num(g_Cvars[CVAR_MARKET_OFFERS])

	Market_ResetPlayer(id)

	new menu, title[196];

	formatex(title, charsmax(title),"%L",\
	 id, "CSRE_MARKETPLACE_TITLE")
	
	menu = menu_create(title, "HandleMarket_MainMenu")
	MenuSetProps(id, menu);

	
	formatex(title, charsmax(title),"%L \y[%d]", id, "CSRE_MARKETPLACE_VIEWALL", Market_CountAllOffers())
	menu_additem(menu, title, "1");
	
	formatex(title, charsmax(title),"%L \y[%d]^n", id, "CSRE_MARKETPLACE_VIEWME", Market_CountOffersFor(id))
	menu_additem(menu, title, "2");
	
	formatex(title, charsmax(title),"%L", id, "CSRE_MARKETPLACE_CREATE")
	menu_additem(menu, title, "3");
	
	formatex(title, charsmax(title),"%L^n", id, "CSRE_MARKETPLACE_CREATEFOR")
	menu_additem(menu, title, "4");
	
	formatex(title, charsmax(title),"%L \y[%d]\r[Max: %d]", id, "CSRE_MARKETPLACE_VIEWMY", g_marketplace_count[id], Market_MaxOffers)
	menu_additem(menu, title, "5");
	
	formatex(title, charsmax(title),"%L", id, "CSRE_MARKETPLACE_DELETEMY")
	menu_additem(menu, title, "6");

	return menu_display(id, menu, 0)
}

public HandleMarket_MainMenu(id, menu, item)
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
		 case 1: ViewAllOffers(id, 0);
		case 2: ViewAllOffers(id, 1);
		case 3: Sql_GetPlayerItems(id, "QueryLoadSkinsMarket")// OWN Skins;	
		case 4: {
			g_marketplace_for[id] = -1;
			Sql_GetPlayerItems(id, "QueryLoadSkinsMarket")// OWN Skins;	
		}	
		case 5: ViewMyOffers(id);
		case 6: RemoveAllOffer(id, true);
	}

	return menu_destroy(menu);
}

stock ViewOfferMenu(id, offer)
{
	new data[mpArray];
	ArrayGetArray(g_marketplace_offers, offer, data)

	new menu, title[196];

	formatex(title, charsmax(title),"%L",\
	 id, "CSRE_MARKETPLACE_TITLE")
	
	menu = menu_create(title, "HandleOfferMenu")
	MenuSetProps(id, menu);

	new name[32]; get_user_name(data[MP_ID], name, charsmax(name));

	formatex(title, charsmax(title),"%L", id, "CSRE_MARKETPLACE_DATA_ID", name)
	menu_additem(menu, title, "1");

	new _data[Items];
	ArrayGetArray(g_Items, search_array(data[MP_ITEM]), _data)

	new skinClassColor[16]
	skinClassStr(_data, skinClassColor, charsmax(skinClassColor))

	formatex(title, charsmax(title),"%L", id, "CSRE_MARKETPLACE_DATA_ITEM", skinClassColor)
	menu_additem(menu, title, "2");

	switch(data[MP_TYPE]) {
		case 1: {
			new __data[Items];
			ArrayGetArray(g_Items, search_array(data[MP_PRICE]), __data)
			skinClassStr(__data, skinClassColor, charsmax(skinClassColor))

			formatex(title, charsmax(title),"%L %s", id, "CSRE_MARKETPLACE_DATA_ITEM_TYPE", skinClassColor)
		}
		default: formatex(title, charsmax(title),"%L %d coin(s)", id, "CSRE_MARKETPLACE_DATA_ITEM_TYPE", data[MP_PRICE])
	}

	menu_additem(menu, title, "3");

	if (data[MP_FOR]) {
		get_user_name(data[MP_ID], name, charsmax(name));
	} formatex(name, charsmax(name), "%L", id, "CSRE_MARKETPLACE_DATA_FOR_ALL")
	

	formatex(title, charsmax(title),"%L", id, "CSRE_MARKETPLACE_DATA_FOR", name)
	menu_additem(menu, title, "4");

	switch(data[MP_STATUS]) {
		case 1: formatex(name, charsmax(name),"%L", id, "CSRE_MARKETPLACE_DATA_STATUS_ON");
		default: formatex(name, charsmax(name),"%L", id, "CSRE_MARKETPLACE_DATA_STATUS_OFF")
	}

	formatex(title, charsmax(title),"%L^n", id, "CSRE_MARKETPLACE_DATA_STATUS", name)
	menu_additem(menu, title, "5");

	new color[3];
	formatex(color, charsmax(color), "\d")

	if ( (	data[MP_FOR] == id || data[MP_FOR] == 0) &&
			data[MP_STATUS] &&
			is_user_connected(data[MP_ID])
	)
		formatex(color, charsmax(color), "\y")

	formatex(title, charsmax(title),"%s%L", color, id, "CSRE_MARKETPLACE_DATA_ACCEPT")
	formatex(name, charsmax(name),"6 %d", offer);
	menu_additem(menu, title, name);

	menu_display(id, menu, 0)
}

public HandleOfferMenu(id, menu, item)
{
	if(item == MENU_EXIT)
	{
		Market_MainMenu(id)
		return menu_destroy(menu);
	}
	
	new _data[12], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, _data,11, _dummy, charsmax(_dummy), callback);


	if (_data[0] != '6') {
		Market_MainMenu(id)
		return menu_destroy(menu);
	}

	new _uid[6]
	parse(_data, _dummy, charsmax(_dummy), _uid, charsmax(_uid))

	new offer = str_to_num(_uid)

	new data[mpArray];
	ArrayGetArray(g_marketplace_offers, offer, data);

	if(data[MP_FOR] != id && data[MP_FOR] != 0)
	{
		new name[33];
		get_user_name(id, name, 32)
		PrintMessage("[CSRErr] Oops, offer for %d, but %s(%d)", data[MP_FOR], name, id)
		return Print(id, "%L", id, "CSRE_MARKETPLACE_ERROR")
	}

	switch(data[MP_TYPE]) {
		case 1: Sql_MarketPlaceCheckItem(id, data[MP_ID], data[MP_ITEM], data[MP_PRICE], offer)
		default: Sql_MarketPlaceCheckPrice(id, data[MP_ID], data[MP_ITEM], offer)
	}

	return menu_destroy(menu);
}

public QueryMarketEnd(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	if(FailState)
	{
		return SQL_Error(Query, Error, Errcode, FailState);
	}
	
	new id = Data[0];
	new uid = Data[1];

	if(SQL_NumResults(Query) <= 0)
		return SQL_FreeHandle(Query);


	new data[mpArray];
	ArrayGetArray(g_marketplace_offers, uid, data);

	new name[32]; get_user_name(id, name, charsmax(name))
	
	// if( data[MP_ID] == id )
	// {
	// 	PrintMessage("[CSRErr] %s use own offer", name)
	// 	Print(id, "%L", id, "CSRE_MARKETPLACE_ERROR")
	// 	return SQL_FreeHandle(Query);
	// }

	if (!is_user_connected(data[MP_ID]) || data[MP_STATUS] != 1 
		//|| equali( g_player_data[id][PD_IP], g_player_data[data[MP_ID]][PD_IP])
		)
	{
		if(!is_user_connected(data[MP_ID]))	PrintMessage("Player %s offer creator not online", name)
		if(data[MP_STATUS] != 1)			PrintMessage("Player %s problem with status %d", name, data[MP_STATUS])
		//if (equali( g_player_data[id][PD_IP], g_player_data[data[MP_ID]][PD_IP])) PrintMessage("Player %s has equal ip", name)
		
		if( data[MP_STATUS] != 1) {
			Print(id, "%L", id, "CSRE_MARKETPLACE_ERROR_STATUS") 
			return SQL_FreeHandle(Query);
		}

		Print(id, "%L", id, "CSRE_MARKETPLACE_ERROR")
		return SQL_FreeHandle(Query);
		
	}

	new check = SQL_ReadResult( Query, SQL_FieldNameToNum(Query, "ccount"));

	PrintMessage("Check: %d | Type: %d", check, data[MP_TYPE])
	if ( !checkOfferByType(id, data[MP_TYPE], check, g_player_stats[id][PS_COINS], data[MP_PRICE])) {
		data[MP_STATUS] = 0;
		ArraySetArray(g_marketplace_offers, uid, data)

		return SQL_FreeHandle(Query);
	}

	Operation_RemovePlayerItem(data[MP_ID], data[MP_ITEM])
	Operation_AddPlayerItem(id, data[MP_ITEM])

	if (data[MP_TYPE]) {
		Operation_RemovePlayerItem(id, data[MP_PRICE])
		Operation_AddPlayerItem(data[MP_ID], data[MP_PRICE])
	} else {
		Stats_AddPlayerCoins(data[MP_ID], data[MP_PRICE]);
		Stats_AddPlayerCoins(id, (-1) * data[MP_PRICE]);
	}
	
	data[MP_STATUS] = 0;
	ArraySetArray(g_marketplace_offers, uid, data)

	g_marketplace_count[data[MP_ID]] --;
	
	Print(id, "%L", id, "CSRE_MARKETPLACE_SUCEESS")
	Print(data[MP_ID], "%L", data[MP_ID], "CSRE_MARKETPLACE_SUCEESS")

	new sname[32];
	get_user_name(data[MP_ID], sname, charsmax(sname))
	
	PrintMessage("[Market] %s accepted the offer | Creator %s | Item [%d] | Cost [%d] | For [%d]", name, sname, data[MP_ITEM], data[MP_PRICE], data[MP_FOR])
	
	//checkSetStatus(id)
	//checkSetStatus(data[MP_ID])
	
	return SQL_FreeHandle(Query);
}

stock AddToMarketplace(id)
{
	if( g_marketplace_count[id] >= Market_MaxOffers )
		return Print(id,"%L", id, "CSRE_MARKETPLACE_ERROR")

	new data[mpArray];
	
	data[MP_ID] = id;
	data[MP_ITEM] = g_marketplace_item[id];
	data[MP_PRICE] = g_marketplace_price[id];
	data[MP_STATUS] = 1;
	data[MP_TYPE] = g_marketplace_type[id];
	
	data[MP_FOR] = g_marketplace_for[id];
	
	new fromName[32]; get_user_name(id, fromName, charsmax(fromName));
	new name[32]; get_user_name(data[MP_FOR], name, 31)

	if (is_user_connected(data[MP_FOR])) {
		new name[32];
		get_user_name(id, name, charsmax(name))

		CmdScreenFade(data[MP_FOR], 3, {25, 150, 25}, 100)
		Print(data[MP_FOR], "%L", data[MP_FOR], "CSRE_MARKETPLACE_INFOME",name)
	}
		
	
	ArrayPushArray(g_marketplace_offers, data);
	g_marketplace_count[id] ++;
	
	Print(id, "%L", id, "CSRE_MARKETPLACE_ADD")
	
	PrintMessage("[Market] %s [Offers:%d][Max:%d] create offer | Item [%d] | Cost [%d]  | For [%d][%s]", fromName, g_marketplace_count[id],Market_MaxOffers,data[MP_ITEM], data[MP_PRICE], data[MP_FOR], data[MP_FOR] > 0 ? name : "All")
	return Market_MainMenu(id)
}
stock RemoveAllOffer(id, bool:type = false)
{
	new size = ArraySize(g_marketplace_offers);

	if (size <= 0)
		return;

	new data[mpArray];
	
	new count = 0;
	for(new i = 0; i< size; i++)
	{
		ArrayGetArray(g_marketplace_offers, i, data)
		
		if (data[MP_ID] != id) continue;
		
		switch (type)
		{
			case true:
			{
				data[MP_STATUS] = 0;
				ArraySetArray(g_marketplace_offers, i, data);
			}
			default: ArrayDeleteItem(g_marketplace_offers, i);
		}

		g_marketplace_count[id] --;
		count ++;
	}
	
	if (g_marketplace_count[id] < 0 )	g_marketplace_count[id] = 0;

	if (is_user_connected(id)) {
		Print(id, "%L", id, "CSRE_MARKETPLACE_CLEARALL", count)
		Market_MainMenu(id)
	}
	
}


ViewMyOffers(id)
{
	new data[mpArray], _data[Items];
	new size = ArraySize(g_marketplace_offers);

	if (size <= 0)
		return Print(id, "%L", id, "CSRE_MARKETPLACE_CLEAR")

	new count = 0;

	new __data[Items];
	for(new i = 0; i< size; i++)
	{
		ArrayGetArray(g_marketplace_offers, i, data)
		
		if (data[MP_ID] != id || !data[MP_STATUS])	continue;

		ArrayGetArray(g_Items, search_array(data[MP_ITEM]), _data)

		if (data[MP_TYPE]) {
			ArrayGetArray(g_Items, search_array(data[MP_PRICE]), __data)
			Print(id, "[%d] ^3%s^1 --> ^4%s", count,  _data[ITEM_NAME], __data[ITEM_NAME])

		} else Print(id, "[%d] ^3%s^1 --> ^4%d", count,  _data[ITEM_NAME], data[MP_PRICE])
		
		++count;
	}
	
	Market_MainMenu(id)
	return PLUGIN_CONTINUE;
}


public SetMPMoney(id)
{
	static arg[33];
	read_argv(1, arg, charsmax(arg));
	
	if ( !strlen(arg) )
	{
		Print(id, "%L", id, "CSRE_MARKETPLACE_ENTERCOST")
		
		client_cmd(id,"messagemode CSR_SetMoney");
		return PLUGIN_HANDLED;
	}
	else if ( !IsStrFloat(arg) )
	{
		Print(id, "%L", id, "CSRE_MARKETPLACE_ENTERCOST")
		
		client_cmd(id,"messagemode CSR_SetMoney");
		return PLUGIN_HANDLED;
	}
	new check = str_to_num(arg);
	if(check < 0)
	{
		Print(id, "%L", id, "CSRE_MARKETPLACE_ENTERCOST")
		
		client_cmd(id,"messagemode CSR_SetMoney");
		return PLUGIN_HANDLED;
	}
	
	g_marketplace_price[id] = check;
	AddToMarketplace(id);
	
	
	return PLUGIN_CONTINUE;
}


