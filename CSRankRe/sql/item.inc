#if defined _sql_item_included
    #endinput
#endif

#define _sql_item_included

#include <amxmodx>
#include <sqlx>

stock Sql_InsertItemToPlayer(id, item) {
	new query[256], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), " INSERT INTO `%s_player_items` (`player`, `skin` ) VALUES ( %d, %d)", \
		table, g_player_data[id][PD_ID], item);

	SQL_ThreadQuery(g_SqlTuple, "QueryTemkOK", query, Data, 1)
}

stock Sql_RemoveItemFromPlayer(id, item) {
	new query[256], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), "DELETE FROM `%s_player_items` WHERE ( `player` = %d AND `skin` = %d) LIMIT 1", \
		table, g_player_data[id][PD_ID], item);

	SQL_ThreadQuery(g_SqlTuple, "QueryTemkOK", query, Data, 1)
}

stock Sql_GetPlayerItems(id, function[], player = 0) {
	new query[256], Data[OperLoadItems];
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	if ( !player ) player = id

	formatex(query, charsmax(query), "\
		SELECT * FROM `%s_player_items`\
		WHERE `player` = '%d'", table, g_player_data[player][PD_ID]\
		)

	Data[OLI_PLAYER] = player;
	Data[OLI_ID] = id;
	copy(Data[OLI_FUNCTION], 31, function);
	SQL_ThreadQuery(g_SqlTuple, "QueryLoadPlayerItems", query, Data, sizeof Data)
}