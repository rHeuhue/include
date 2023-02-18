#if defined _player_included 
	#endinput
#endif

#define _player_included

#include <amxmodx>
#include <sqlx>

stock Player_Reset(id) {
	g_user_kills[id] = 0;

	for(new i; i< PlayerData; i++) {
		g_player_data[id][i] = _:0;
	}

	for(new i; i < PlayerStats; i++)
	{
		g_player_stats[id][i] = _:0;
	}

	Player_ResetSkins(id);

	Operation_blockPlayer[id] = false;
	g_isTeamChanged[id] = 0;
	g_take_item[id] = false;
	g_player_weapons_load[id] = false;

	Market_ResetPlayer(id, true)
}

stock Player_ResetSkins(id) {
	Operation_ResetPlayerWeapon(id, false)
}

public QueryLoadPlayer(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	if(FailState)
	{
		return SQL_Error(Query, Error, Errcode, FailState);
	}
	
	new id = Data[0];
	
	if(SQL_NumResults(Query) <= 0) {
		Sql_InsertNewPlayer(id)
		return SQL_FreeHandle(Query);
	}
		

	g_player_data[id][PD_LOAD] = true;

	g_player_data[id][PD_LAST_TIME] = get_systime(0);
	g_player_data[id][PD_CHECK_TIME] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"check_time"));

	g_player_data[id][PD_ID] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"player"));

	g_player_stats[id][PS_PLAYER] = g_player_data[id][PD_ID]
	g_player_stats[id][PS_EXP] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"exp"));
	g_player_stats[id][PS_EXP_TOTAL] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"exp_total"));
	g_player_stats[id][PS_MEDALS] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"medals"));

	g_player_stats[id][PS_CASES] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"cases"));
	g_player_stats[id][PS_CASES_TOTAL] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"cases_total"));

	g_player_stats[id][PS_KEYS] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"keys"));
	g_player_stats[id][PS_KEYS_TOTAL] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"keys_total"));

	g_player_stats[id][PS_COINS] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"coins"));
	g_player_stats[id][PS_COINS_TOTAL] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"coins_total"));

	g_player_stats[id][PS_GOLDS] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"golds"));
	g_player_stats[id][PS_GOLDS_TOTAL] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"golds_total"));
	g_player_stats[id][PS_REWARDS] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"rewards"));

	CoreExp_set_level_from_exp(id)

	Sql_GetPlayerWeapons(id, g_player_stats[id][PS_PLAYER])
	return SQL_FreeHandle(Query);
}

public QueryLoadPlayerWeapons(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	if(FailState)
	{
		return SQL_Error(Query, Error, Errcode, FailState);
	}
	
	new id = Data[0];
	g_player_weapons_load[id] = true;

	if(SQL_NumResults(Query) <= 0)
		return SQL_FreeHandle(Query);

	new team, weapon_id, weapon_skin;
	new item;
	
	while (SQL_MoreResults(Query)) {
		// COde
		team = SQL_ReadResult(Query, SQL_FieldNameToNum(Query, "team"));
		weapon_id = SQL_ReadResult(Query, SQL_FieldNameToNum(Query, "weapon_id"));
		weapon_skin = SQL_ReadResult(Query, SQL_FieldNameToNum(Query, "weapon_skin"));

		item = weapon_skin;

		set_player_weapon_skin(id, team, weapon_id, item);
		
		SQL_NextRow(Query)
	}

	Sql_GetPlayerItems(id, "QueryHandlePlayerItems")
	return SQL_FreeHandle(Query);
}

/**
	Проверяем есть ли у игрока несуществующие скины
*/
public QueryHandlePlayerItems(id, Array:playerItems, player) {
	if (player == id) player = id;
	
	if ( !ArraySize(playerItems) ) {
		new bool:find = false;
		for(new i; i< WEAPON_SIZE + 1; i++)
			for(new j; j< ReTeams; j++)
				if ( get_player_weapon_skin(id, j, i) ) find = true;

		Operation_ResetPlayerWeapon(id, find)
		return ArrayDestroy(playerItems);
	 }

	new skin = 0;
	for(new i; i< WEAPON_SIZE + 1; i++) {

		for(new j; j< ReTeams; j++) {
			skin = get_player_weapon_skin(id, j, i)

			if ( !skin) continue;

			if ( search_array(skin) < 0 || !isPlayerHasItem( skin, playerItems) )
				Operation_ResetPlayerWeaponSkin(id, i, j)

		}
	}

	return ArrayDestroy(playerItems);
}

stock bool:isPlayerHasItem(search, Array: playerItems) {
	new size = ArraySize(playerItems), item;
	for(new i; i< size; i++) {
		item = ArrayGetCell(playerItems, i);

		if (item == search) return true;
	}

	return false;
}

stock Player_Save(id) {
	if(is_user_bot(id) || is_user_hltv(id) || !is_user_connected(id))
		return;

	if ( !g_player_data[id][PD_LOAD] ) {
		return;
	}
	
	Sql_SavePlayerStats(id)
}

public QueryInsertPlayer(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	if(FailState)
	{
		return SQL_Error(Query, Error, Errcode, FailState);
	}
	
	new id = Data[0];
	Sql_GetPlayerID( id, g_player_data[id][PD_AUTHID],  g_player_data[id][PD_IP])
	return SQL_FreeHandle(Query);
}

public QueryLoadPlayerID(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	if(FailState)
	{
		return SQL_Error(Query, Error, Errcode, FailState);
	}
	
	new id = Data[0];

	if(SQL_NumResults(Query) <= 0)
		return SQL_FreeHandle(Query);

	g_player_data[id][PD_LOAD] = true;
	g_player_data[id][PD_LAST_TIME] = get_systime(0);

	g_player_data[id][PD_ID] = SQL_ReadResult(Query, SQL_FieldNameToNum(Query,"id"));
	return SQL_FreeHandle(Query);
}




