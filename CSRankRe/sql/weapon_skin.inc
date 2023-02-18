#if defined _sql_ws_included
    #endinput
#endif

#define _sql_ws_included

#include <amxmodx>
#include <sqlx>


stock Sql_GetPlayerWeapons(id, player_id) {
	new query[256], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), "\
		SELECT * FROM `%s_player_weapons`\
		WHERE `player` = '%d'", table, player_id\
		)
	SQL_ThreadQuery(g_SqlTuple, "QueryLoadPlayerWeapons", query, Data, 1)
}

stock Sql_InsertWeaponSkin(id, weaponid, reTeam, item) {
	new query[256], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), " INSERT INTO `%s_player_weapons`\
	 	(`player`, `team`, `weapon_id`, `weapon_skin`) VALUES ( %d, %d, %d, %d )", \
		table, g_player_data[id][PD_ID], _:reTeam, weaponid, item);

	SQL_ThreadQuery(g_SqlTuple, "QueryTemkUnlock", query, Data, 1)
}

stock Sql_UpdateWeaponSkin(id, weaponid, reTeam, oldItem, item) {
	new query[256], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), " UPDATE `%s_player_weapons`  SET `weapon_skin` = %d WHERE (\
		`player` = %d AND\
		`team` = %d AND\
		`weapon_id` = %d AND\
		`weapon_skin` = %d\
		)\
	", \
		table, item, g_player_data[id][PD_ID], _:reTeam, weaponid, oldItem);

	SQL_ThreadQuery(g_SqlTuple, "QueryTemkUnlock", query, Data, 1)
}

stock Sql_RemoveWeaponSkin(id, reTeam, weaponid) {
	new query[256], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), "DELETE FROM `%s_player_weapons` WHERE (\
		`player` = %d AND\
		`team` = %d AND\
		`weapon_id` = %d) LIMIT 1", table, g_player_data[id][PD_ID], _:reTeam, weaponid);

	server_print(query)
	SQL_ThreadQuery(g_SqlTuple, "QueryTemkUnlock", query, Data, 1)
}

stock SQL_ResetWeapons(id) {
	new query[256], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), "DELETE FROM `%s_player_weapons` WHERE (\
		`player` = %d)", table, g_player_data[id][PD_ID]);

	SQL_ThreadQuery(g_SqlTuple, "QueryTemkUnlock", query, Data, 1)
}