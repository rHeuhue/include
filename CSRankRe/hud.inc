#if defined _hud_included
	#endinput
#endif

#define _hud_included

#include <amxmodx>

HudShow( const id, const player )
{
	new Float:x = get_pcvar_float(g_Cvars[CVAR_INFORMER_X])
	new Float:y = get_pcvar_float(g_Cvars[CVAR_INFORMER_Y])
	
	new text[512];
	get_pcvar_string(g_Cvars[CVAR_INFORMER_TEXT], text, charsmax(text))
	
	replace_all(text, charsmax(text), "%n%", "^n")

	new name[32]
	get_user_name(id, name, charsmax(name))
	
	new max_level[4];
	new cur_level[4];
	
	num_to_str(g_player_stats[id][PS_LEVEL], cur_level, charsmax(cur_level));
	num_to_str( CoreExp_get_max_level(), max_level, charsmax(max_level));
	
	new exp[6];
	new exp_next[6];
	
	num_to_str(g_player_stats[id][PS_EXP], exp, charsmax(exp));
	num_to_str(CoreExp_get_next_level(g_player_stats[id][PS_EXP]), exp_next, charsmax(exp_next));
	
	new cases[6];
	new coins[6];
	
	num_to_str(g_player_stats[id][PS_CASES], cases, charsmax(cases));
	num_to_str(g_player_stats[id][PS_COINS], coins, charsmax(coins));
	
	new medal[6];
	num_to_str(g_player_stats[id][PS_MEDALS], medal, charsmax(medal));

	new max_coins[6];
	num_to_str(g_player_stats[id][PS_COINS_TOTAL], max_coins, charsmax(coins));

	replace_all(text, charsmax(text), "%name%", name)
	replace_all(text, charsmax(text), "%exp%", exp)
	replace_all(text, charsmax(text), "%exp_next%", exp_next)
	
	replace_all(text, charsmax(text), "%level%", cur_level)
	
	replace_all(text, charsmax(text), "%max_level%", max_level)
	replace_all(text, charsmax(text), "%max_coins%", max_coins)
	
	replace_all(text, charsmax(text), "%cases%", cases)
	replace_all(text, charsmax(text), "%coins%", coins)
	replace_all(text, charsmax(text), "%medal%", medal)
	
	set_hudmessage(150, 150, 150, x, y, 0, 6.0, 2.0, _, _, 1)
	show_hudmessage(player, "%s", text)
}
