#if defined _skins_included 
	#endinput
#endif

#define _skins_included 

#include <CSRankRe/skins/load>

#include <amxmodx>

stock Skins_end() {
	ArrayDestroy(g_Items);	
}

public GiveItem(id, bool:is_need_container, bool:event) {

	// EVENT
	if (event) {
		if (is_need_container) {
			if ( !g_player_stats[id][PS_KEYS] ) {
				return Print( id, "%L", id, "CSRE_ENOUGH_CASES")
			}

			Stats_AddPlayerKeys(id, -1);
		}

		return Skins_GenerateContainer(id, 0, true);
	}
	////////////////////////////////////

	if ( is_need_container) {

		if ( !g_player_stats[id][PS_CASES] ) {
			return Print( id, "%L", id, "CSRE_ENOUGH_CASES")
		}

		Stats_AddPlayerCases(id, -1);
	}


	return Skins_GenerateContainer(id);
}

stock Skins_GenerateContainer( id, item_level = 0, bool:event = false ) {
	new name[32];get_user_name(id, name, 31)

	new chance;
	new itemLevel = Chance_GenerateSkin(chance);

	if (item_level) {
		itemLevel = item_level
	}

	new itemID = calc_items(itemLevel, event);
	new item;

	new data[Items];
	ArrayGetArray(g_Items, itemID, data)
	item = data[ITEM_ID];

	Operation_AddPlayerItem(id, item)

	if ( itemLevel <= 1) 
		return Print(id, "%L", id, "CSRE_ADD_SKIN", name, data[ITEM_NAME]);

	new const screenFade[3][3] = {
		{0, 0, 0},
		{200, 50, 0},
		{ 255, 255, 50}
	}

	log_to_file( LOG_FILE_ITEM_RARE, " %s take %s [ItemClass: %d]", name, data[ITEM_NAME], data[ITEM_CLASS]);
	CmdScreenFade(id, 4, screenFade[itemLevel-1], 150)
			
	set_dhudmessage(screenFade[itemLevel-1][0],screenFade[itemLevel-1][1],screenFade[itemLevel-1][2],-1.0,0.3, 1 ,0.1, 10.0,0.1,0.1)
	show_dhudmessage(0, "%L", LANG_PLAYER, "CSRE_SKIN_GREAT", name, data[ITEM_NAME], chance)
			
	return Print(0, "%L", id, "CSRE_ADD_SKIN", name, data[ITEM_NAME])
}

stock calc_items( const item_class, bool:event = false )
{
	new Array: arr = ArrayCreate(1);
			
	new data[Items]
	for(new i = 1; i< ArraySize(g_Items); i++)
	{
		ArrayGetArray(g_Items, i, data)
		
		if(data[ITEM_CLASS] == item_class && data[ITEM_GET_FROM_CONTAINER]) {
			if (event && data[ITEM_EVENT] && data[ITEM_EVENT] == g_Event) {
				ArrayPushCell(arr, i);
			}

			if (!data[ITEM_EVENT]) ArrayPushCell(arr, i);
		}
	}
			
	new rnd = ArrayGetCell(arr,random_num(0, ArraySize(arr) - 1));
	
	ArrayDestroy(arr)
	return rnd;
}

