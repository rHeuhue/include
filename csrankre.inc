#if defined _csrankre_included
	#endinput
#endif

#define _csrankre_included

#if !defined MAX_CLIENTS
	#define MAX_CLIENTS 32
#endif

#include <amxmodx>

#define is_valid_player(%0) ( 1<=%0<= MAX_CLIENTS)
#define csr_is_valid_player(%0) (is_valid_player(%0) && is_user_connected(%0))

enum
{
	CSRE_VALUE_MEDALS = 0,

	CSRE_VALUE_EXPS,

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

/*
	Return a value for player
*/
native csre_get_value(id, type);

/*
	Set a value for player
*/
native csre_add_value(id, type, value);

// ###########################################################3

/*
	Add a drop for player. If is_need_container: remove 1 case from player, if player don't has container, nothing will be given
*/
native csre_give_drop(id, bool:is_need_container);

/*
	Example:
		new Array:array = csre_get_all_skins();

		new size = ArraySize(array), data[nSkins]
		//new skinMenuFormat[64], skinID[12];
		for(new i; i<size;i++) {
			// Get skin
			ArrayGetArray(array, i, data)
			server_print("ID: %d | Name: %s | Skin level: %d", data[SKIN_N_ID], data[SKIN_N_NAME], data[SKIN_N_LEVEL])

			// For menu
			//csre_format_skin(data, skinMenuFormat, charsmax(skinMenuFormat))
			// num_to_str(data[SKIN_N_ID], skinID, charsmax(skinID))
			//menu_additem(menu, skinMenuFormat, "")
		}

	@return Array that implements nSkins
*/
native Array:csre_get_all_skins();

native csre_format_skin(data[nSkins], str[], len);

/*
	Get API version

	@param version for string version ("1.0.0")
	@param len

	@return number version like 100 ("1.0.0")
*/
native csre_get_api_version(version[], len);

/**
	@param skin_id from SKIN_N_ID
 */
native csre_add_skin(id, skin_id)
