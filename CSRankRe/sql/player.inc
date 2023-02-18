#if defined _sql_player_included
    #endinput
#endif

#define _sql_player_included

#include <amxmodx>
#include <sqlx>

stock Sql_GetPlayer(id, authid[], ip[]) {
	new query[512], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), "\
		SELECT * FROM `%s_players`\
		JOIN `%s_player_stats` ON `%s_player_stats`.`player` = `%s_players`.`id`\
		WHERE (`%s_players`.`player_id` = '%s' OR `%s_players`.`player_ip` = '%s')", table, table, table, table, table, authid, table, ip\
		)
	SQL_ThreadQuery(g_SqlTuple, "QueryLoadPlayer", query, Data, 1)
}

stock Sql_GetPlayerID(id, authid[], ip[]) {
	new query[256], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), "\
		SELECT * FROM `%s_players`\
		WHERE (`%s_players`.`player_id` = '%s' OR `%s_players`.`player_ip` = '%s')", table, table, authid, table, ip\
		)
	SQL_ThreadQuery(g_SqlTuple, "QueryLoadPlayerID", query, Data, 1)
}

stock Sql_InsertNewPlayer(id) {
	new query[512], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	SQL_SafeString(g_player_data[id][PD_NAME], 31)

	new len = formatex(query, charsmax(query), " INSERT INTO `%s_players` (`player_name`, `player_id`, `player_ip`, `player_total_time`, `player_last_time`) VALUES ( '%s', '%s', '%s', 0, 0 ) ", \
		table, g_player_data[id][PD_NAME], g_player_data[id][PD_AUTHID], g_player_data[id][PD_IP]);

	len +=formatex(query[len], charsmax(query)-len, "\
		ON DUPLICATE KEY UPDATE  \
		`player_name` = '%s',\
		`player_total_time` = `player_total_time` + %d,\
		`player_last_time` = %d\
		", g_player_data[id][PD_NAME], get_user_time(id), get_systime(0))

	SQL_ThreadQuery(g_SqlTuple, "QueryInsertPlayer", query, Data, 1)
}

stock Sql_SavePlayerStats(id) {
	new query[2048], len;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	len = formatex(query, charsmax(query), " INSERT INTO `%s_player_stats` (\
		`player`,\
		 `exp`,\
		 `exp_total`,\
		 `medals`,\
		 `cases`,\
		 `cases_total`,\
		 `keys`,\
		 `keys_total`,\
		 `coins`,\
		 `coins_total`,\
		 `golds`,\
		 `golds_total`,\
		 `check_time`,\
		 ", table);

	len +=formatex(query[len], charsmax(query)-len, "\
		`rewards`\
		)")

	new total_exp = (g_player_stats[id][PS_EXP_TOTAL] < g_player_stats[id][PS_EXP]) ? (g_player_stats[id][PS_EXP] + g_player_stats[id][PS_EXP_TOTAL]) : g_player_stats[id][PS_EXP_TOTAL];
	len += formatex(query[len], charsmax(query)-len, " VALUES (\
		%d,\
		%d,\
		%d,\
		%d,\
		%d,\
		%d,\
		%d,\
		%d,\
		%d,\
		%d,\
		%d,\
		%d,\
		%d,\
		%d\
	) ON DUPLICATE KEY UPDATE ", g_player_data[id][PD_ID], g_player_stats[id][PS_EXP], total_exp, g_player_stats[id][PS_MEDALS], 
	g_player_stats[id][PS_CASES], g_player_stats[id][PS_CASES_TOTAL], g_player_stats[id][PS_KEYS], g_player_stats[id][PS_KEYS_TOTAL], g_player_stats[id][PS_COINS],
	g_player_stats[id][PS_COINS_TOTAL], g_player_stats[id][PS_GOLDS], g_player_stats[id][PS_GOLDS_TOTAL], g_player_data[id][PD_CHECK_TIME], g_player_stats[id][PS_REWARDS])

	len += formatex(query[len], charsmax(query)-len, "\
		`exp` = %d,\
		`exp_total` = %d,\
		`medals` = %d,\
		`cases` = %d,\
		`cases_total` = %d,\
		`keys` = %d,\
		`keys_total` = %d,\
		`coins` = %d,\
		`coins_total` = %d,\
		`golds` = %d,\
		`golds_total` = %d,\
		`check_time` = %d,\
		`rewards` = %d\
	",  g_player_stats[id][PS_EXP], total_exp, g_player_stats[id][PS_MEDALS], 
	g_player_stats[id][PS_CASES], g_player_stats[id][PS_CASES_TOTAL], g_player_stats[id][PS_KEYS], g_player_stats[id][PS_KEYS_TOTAL], g_player_stats[id][PS_COINS],
	g_player_stats[id][PS_COINS_TOTAL], g_player_stats[id][PS_GOLDS], g_player_stats[id][PS_GOLDS_TOTAL], g_player_data[id][PD_CHECK_TIME], g_player_stats[id][PS_REWARDS])

	SQL_ThreadQuery(g_SqlTuple, "QueryTemkOK", query)
}

stock Sql_GetPlayerRank(id) {
	new query[512], Data[1]; Data[0] = id;
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	formatex(query, charsmax(query), "SELECT dummy1.row_number FROM ( SELECT @id := @id + 1 AS row_number, `%s_player_stats`.* FROM `%s_player_stats`, (SELECT @id := 0) AS dummy0 ORDER BY `%s_player_stats`.`exp_total` DESC ) AS dummy1 WHERE (dummy1.`player` = '%d')",
		table,table,table,g_player_data[id][PD_ID])

	SQL_ThreadQuery(g_SqlTuple, "QueryLoadRank", query, Data, 1)
}