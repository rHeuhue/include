#if defined _stats_included 
	#endinput
#endif

#define _stats_included 

#include <amxmodx>

stock Stats_AddPlayerExp(id, value) {
	CoreExp_ExpUpdate(id, value, true, false)
}

stock Stats_AddPlayerMedals(id, value) {
	g_player_stats[id][PS_MEDALS] += value
}

stock Stats_AddPlayerCases(id, value) {
	g_player_stats[id][PS_CASES] += value;
	g_player_stats[id][PS_CASES_TOTAL] += value < 0 ? 0 : value;
}

stock Stats_AddPlayerKeys(id, value) {
	g_player_stats[id][PS_KEYS] += value;
	g_player_stats[id][PS_KEYS_TOTAL] += value < 0 ? 0 : value;
}

stock Stats_AddPlayerCoins(id, value) {
	g_player_stats[id][PS_COINS] += value;
	g_player_stats[id][PS_COINS_TOTAL] += value < 0 ? 0 : value;
}

stock Stats_AddPlayerGolds(id, value) {
	g_player_stats[id][PS_GOLDS] += value;
	g_player_stats[id][PS_GOLDS_TOTAL] += value < 0 ? 0 : value;
}


