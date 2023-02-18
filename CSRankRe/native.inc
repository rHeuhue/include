#if defined _native_included
	#endinput
#endif

#define _native_included

#include <amxmodx>

enum
{
	CSRE_VALUE_MEDALS = 0,

	CSRE_VALUE_EXPS,

    //
	CSRE_VALUE_COINS,
	CSRE_VALUE_CASES,
	CSRE_VALUE_KEYS,
    CSRE_VALUE_GOLDS,
	CSRE_VALUE_LEVEL
}

enum _:nSkins {
	SKIN_N_ID,
	SKIN_N_NAME[64],
	SKIN_N_LEVEL
}

public plugin_natives()
{
	register_library("csrankre")

	register_native("csre_get_api_version", "_getApiVersion", 1)
	
	register_native("csre_get_value", "_get_value", 1)
	register_native("csre_add_value", "_add_value", 1)
	
	register_native("csre_give_drop", "GiveItem", 1)

	register_native("csre_get_all_skins", "_getAllSkins", 1)
	register_native("csre_format_skin", "_formatSkin", 1)

	register_native("csre_add_skin", "_addSkin", 1)
}

public _addSkin(id, skin_id) {
	new index = search_array(skin_id);

	if (index < 0) return 0;

	return Operation_AddPlayerItem(id, skin_id);
}

public _getApiVersion(version[], len) {
	formatex(version, len, "%s", API_VERSION)
	return API_VERSION_NUM
}

public Array:_getAllSkins() {
	new Array:skins = ArrayCreate(nSkins);
	new size = ArraySize(g_Items)

	new data[Items]
	new _data[nSkins]
	for(new i = 0; i < size; i++)
	{
		ArrayGetArray(g_Items, i, data)

		_data[SKIN_N_ID] = data[ITEM_ID]
		_data[SKIN_N_LEVEL] = data[ITEM_CLASS]
		copy(_data[SKIN_N_NAME], 63, data[ITEM_NAME])

		ArrayPushArray(skins, _data)
	}

	return skins;
}

public _formatSkin(data[nSkins], str[], len) {
    new itemColor[] = "\w";

    switch (data[SKIN_N_LEVEL]) {
        case 3: formatex(itemColor, charsmax(itemColor), "\y");
        case 2: formatex(itemColor, charsmax(itemColor), "\r");
        case 1: formatex(itemColor, charsmax(itemColor), "\w");
    }

    return formatex(str, len, "%s%s", itemColor, data[SKIN_N_NAME])
}

public _get_value(id, type)
{
	if(!csr_is_valid_player(id))
		return -1;

	new value = -2;

	switch (type)
	{
		case CSRE_VALUE_MEDALS: value = g_player_stats[id][PS_MEDALS];
		case CSRE_VALUE_EXPS: 	value = g_player_stats[id][PS_EXP];
		case CSRE_VALUE_COINS: 	value = g_player_stats[id][PS_COINS];
		case CSRE_VALUE_CASES: 	value = g_player_stats[id][PS_CASES];
		case CSRE_VALUE_KEYS: 	value = g_player_stats[id][PS_KEYS];
        case CSRE_VALUE_GOLDS:  value = g_player_stats[id][PS_GOLDS];
		case CSRE_VALUE_LEVEL:	value = g_player_stats[id][PS_LEVEL];
	}

	return value;
}
public _add_value(id, type, value)
{
	if(!csr_is_valid_player(id))
		return 0;

	switch (type)
	{
		case CSRE_VALUE_MEDALS: Stats_AddPlayerMedals(id, value);
		case CSRE_VALUE_EXPS: 	Stats_AddPlayerExp(id, value);
		case CSRE_VALUE_COINS: 	Stats_AddPlayerCoins(id, value);
		case CSRE_VALUE_CASES: 	Stats_AddPlayerCases(id, value);
		case CSRE_VALUE_KEYS: 	Stats_AddPlayerKeys(id, value);
        case CSRE_VALUE_GOLDS:  Stats_AddPlayerGolds(id, value);
	}
	
	return 1;
}
