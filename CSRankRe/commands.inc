#if defined _commands_included 
	#endinput
#endif

#define _commands_included 

#include <amxmodx>
#include <CSRankRe/commands/commandsMenu.inc>

public CSRAddFeature(id)
{
	if( id && !has_access(id, g_Cvars[CVAR_MAIN_FLAG]))
		return console_print(id, "[%s] Access denied", PLUGIN)
		
	new player[32], bonus[32], value[32];

	read_argv(1, player, sizeof(player) - 1);
	read_argv(2, bonus, sizeof(bonus) - 1);
	read_argv(3, value, sizeof(value) - 1);
	
	new target = cmd_target(id, player, CMDTARGET_NO_BOTS);
	if( !target ) return console_print(id, "[%s] Can't find player with '%s'", PLUGIN, player);
 
	static const args[][] = {
		"exp",
		"coin",
		"case",
		"key",
		"skin_id"
	}

	new type = -1;

	for(new i; i< sizeof(args); i++) {
		if ( equali( bonus, args[i]) ) {
			type = i;
			break;
		}
	}
	if( type < 0)
		return console_print(id, "[%s] Invalid argument <2>(type) '%s'", PLUGIN, bonus);

	new count = str_to_num(value);
	if( count < 0 && type != 4)
		return console_print(id, "[%s] Invalid argument <3>(count) '%s'", PLUGIN, value);
	
	if (type == 4) count = convert_skin_id(value, charsmax(value))

	switch (type) {
		case 0: Stats_AddPlayerExp(target, count);
		case 1: Stats_AddPlayerCoins(target, count)
		case 2: Stats_AddPlayerCases(target, count);
		case 3: Stats_AddPlayerKeys(target, count);
		case 4: Operation_AddPlayerItem(target, count)
	}

	new targetName[32];
	get_user_name(target, targetName, charsmax(targetName))

	new name[32];
	get_user_name(id, name, charsmax(name))

	Print(id, "You give %d %s to player %s", count, args[type], targetName)
	Print(id, "You get %d %s from player %s", count, args[type], name)

	return PLUGIN_HANDLED;
}

public ShowRank(id)
{
	Sql_GetPlayerRank(id)
	return PLUGIN_HANDLED;
}

public QueryLoadRank(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	if(FailState)
	{
		return SQL_Error(Query, Error, Errcode, FailState);
	}

	if(SQL_NumResults(Query) < 1)    
		return SQL_FreeHandle(Query);
	
	new id = Data[0];
	new rank = SQL_ReadResult(Query, 0) + 0;

	Print(id, "%L", id, "CSRE_CS_SHOW_RANK", rank, g_player_stats[id][PS_EXP], g_player_stats[id][PS_MEDALS])
	return SQL_FreeHandle(Query);
}

