#if defined _csrank_included
	#endinput
#endif

#define _csrank_included

#include <amxmodx>

#define csr_is_valid_player(%0) (1<=%0<=32 && is_user_connected(%0))

enum
{
	CSR_VALUE_MEDALS = 0,

	CSR_VALUE_EXP,
	CSR_VALUE_COINS,
	CSR_VALUE_CASES,
	CSR_VALUE_KEYS,
	CSR_VALUE_LEVEL
}

/*
	Return a value for player
*/
native csr_get_value(id, type);

/*
	Set a value for player
*/
native csr_set_value(id, type, value);

/*
	Add item(skin) to player
*/
native csr_add_item(id, const item_id);

/*
	Remove item(skin) to player
*/
native csr_remove_item(id, const item_id);

// ###########################################################3

/*
	Add a value to player
*/
public csr_add_value(id, type, value)
{
	return csr_set_value(id, type, max(csr_get_value(id, type)+value,0));
}

/*
	Add a drop for player. If is_case: add skin, but not the keys, case
*/
native csr_give_drop(id, bool:is_case);
