#if defined _sql_table_included
    #endinput
#endif

#define _sql_table_included

#include <amxmodx>
#include <sqlx>

const TABLE_MAX_LEN = 2048

public Sql_CreateTable() {
	new table[32];	get_pcvar_string(g_Cvars[CVAR_SQL_TABLE], table, charsmax(table));

	new query[TABLE_MAX_LEN], len;
	
	len = formatex(query, charsmax(query), "CREATE TABLE IF NOT EXISTS `%s_players` (\
	`id` int(10) unsigned NOT NULL AUTO_INCREMENT,\
	`player_name`  varchar(32) NOT NULL,\
	`player_id` varchar(32) NOT NULL,\
	`player_ip` varchar(32) NOT NULL,\
	`player_total_time` int(16) NOT NULL,\
	`player_last_time` int(16) NOT NULL,\
	", table)

	len += formatex(query[len], charsmax(query)-len, "\
	`player_login` varchar(32) NOT NULL DEFAULT '',\
	`player_password` varchar(35) NOT NULL  DEFAULT '',\
	UNIQUE INDEX (`player_id`, `player_ip`),\
		PRIMARY KEY (`id`) )\
	ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=1;")
	
	SQL_ThreadQuery(g_SqlTuple, "QueryTemkOK", query)

	len = formatex(query, charsmax(query), "CREATE TABLE IF NOT EXISTS `%s_player_stats` (\
	`player` int(10) unsigned NOT NULL,\
	`exp` int(10) NOT NULL,\
	`exp_total` int(10) NOT NULL,\
	`medals` int(10) NOT NULL,\
	`cases` int(10) NOT NULL,\
	`cases_total` int(10) NOT NULL,", table);
	len += formatex(query[len], charsmax(query)-len, "\
	`keys` int(10) NOT NULL,\
	`keys_total` int(10) NOT NULL,\
	`coins` int(10) NOT NULL,\
	`coins_total` int(10) NOT NULL,\
	`golds` int(10) NOT NULL,\
	`golds_total` int(10) NOT NULL,\
	`check_time` int(16) NOT NULL,\
	`rewards` int(4) NOT NULL,\
	`stats` varchar(256) NOT NULL DEFAULT '', \
		PRIMARY KEY (`player`) )\
	ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=1;")

	SQL_ThreadQuery(g_SqlTuple, "QueryTemkOK", query)

	len = formatex(query, charsmax(query), "CREATE TABLE IF NOT EXISTS `%s_player_items` (\
	`id` int(10) unsigned NOT NULL AUTO_INCREMENT,\
	`player` int(10) unsigned NOT NULL,\
	`skin` int(10) NOT NULL,", table);
	len += formatex(query[len], charsmax(query)-len, "\
		PRIMARY KEY (`id`) )\
	ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=1;")

	SQL_ThreadQuery(g_SqlTuple, "QueryTemkOK", query)

	len = formatex(query, charsmax(query), "CREATE TABLE IF NOT EXISTS `%s_player_weapons` (\
	`id` int(10) unsigned NOT NULL AUTO_INCREMENT,\
	`player` int(10) unsigned NOT NULL,\
	`team` int(10) NOT NULL,\
	`weapon_id` int(10) NOT NULL,\
	`weapon_skin` int(10) NOT NULL,", table);
	len += formatex(query[len], charsmax(query)-len, "\
		PRIMARY KEY (`id`) )\
	ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=1;")

	SQL_ThreadQuery(g_SqlTuple, "QueryTemkOK", query)

}