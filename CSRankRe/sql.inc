#if defined _sql_included
    #endinput
#endif

#define _sql_included

#include <CSRankRe/sql/connect>
#include <CSRankRe/sql/weapon_skin>
#include <CSRankRe/sql/item>
#include <CSRankRe/sql/table>
#include <CSRankRe/sql/player>

public SqlX() {
	SQL_SetAffinity("mysql");

	new host[32],user[32],pass[32],db[32]
		
	get_pcvar_string(g_Cvars[CVAR_SQL_HOST],host,31)
	get_pcvar_string(g_Cvars[CVAR_SQL_USER],user,31)
	get_pcvar_string(g_Cvars[CVAR_SQL_PASS],pass,31)
	get_pcvar_string(g_Cvars[CVAR_SQL_DB],db,31)

	g_SqlTuple = sqlInit(host,user,pass,db)

	Sql_CreateTable();
}

stock Sql_QueryTop(id) {
	new query[512], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), "SELECT * FROM `%s_players` JOIN `%s_player_stats` ON `%s_player_stats`.`player` = `%s_players`.`id` ORDER BY `%s_player_stats`.`exp_total` DESC",\
	table, table, table,table,table)
		
	SQL_ThreadQuery(g_SqlTuple, "QueryLoadTop", query, Data, 1)
}

stock Sql_MarketPlaceCheckItem(id, creatorID, skinCreator, skinID, offerID) {
	new query[512], Data[2]; Data[0] = id; Data[1] = offerID
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	new len = formatex(query, charsmax(query), " SELECT COUNT(*) as ccount FROM `%s_player_items` where \
		`id` = (SELECT `id` from `%s_player_items` where `player` = %d and `skin` = %d LIMIT 1)\
	", table, table, g_player_data[id][PD_ID], skinID)

	len += formatex(query[len], charsmax(query)-len, " OR\
		`id` = (SELECT `id` from `%s_player_items` where `player` = %d and `skin` = %d LIMIT 1)\
		", table, g_player_data[creatorID][PD_ID],skinCreator)

	SQL_ThreadQuery(g_SqlTuple, "QueryMarketEnd", query, Data, 2)
}

stock Sql_MarketPlaceCheckPrice(id, creatorID, skinCreator, offerID) {
	new query[256], Data[2]; Data[0] = id; Data[1] = offerID
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), " SELECT COUNT(*) as ccount FROM `%s_player_items` where \
		`id` = (SELECT `id` from `%s_player_items` where `player` = %d and `skin` = %d LIMIT 1)\
	", table, table, g_player_data[creatorID][PD_ID], skinCreator)
	
	SQL_ThreadQuery(g_SqlTuple, "QueryMarketEnd", query, Data, 2)
}

public QueryTemkOK(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	if(FailState)
		return SQL_Error(Query, Error, Errcode, FailState);

	return SQL_FreeHandle(Query)
}

public QueryTemkUnlock(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	if(FailState)
		return SQL_Error(Query, Error, Errcode, FailState);

	new id = Data[0];
	Operation_blockPlayer[id] = false;
	return SQL_FreeHandle(Query)
}