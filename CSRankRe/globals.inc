#if defined _global_vars_included 
	#endinput
#endif

#define _global_vars_included 

#include <CSRankRe/globals/consts>
#include <CSRankRe/globals/enums>
#include <CSRankRe/globals/cvars>

new g_HudSync;
new g_Cvars[Cvars];

new Handle: g_SqlTuple;
new Array: g_Items;
new Trie: g_ItemsTrie;

new g_player_data[MAX_CLIENTS + 1][PlayerData]
new g_player_stats[MAX_CLIENTS + 1][PlayerStats]

new g_player_weapons[MAX_CLIENTS + 1][ReTeams][WEAPON_SIZE + 1];

new bool:g_player_weapons_load[MAX_CLIENTS + 1];
new g_user_kills[MAX_CLIENTS + 1];
new g_isTeamChanged[MAX_CLIENTS + 1];
new bool:g_take_item[MAX_CLIENTS + 1]

//MarketPlace
new Array:g_marketplace_offers;

new g_marketplace_count[33];
new g_marketplace_item[33];
new g_marketplace_price[33];
new g_marketplace_for[33];
new g_marketplace_time[33];

new g_marketplace_offer_time[33];
new g_marketplace_type[33];


// Rewards
new Array: g_rewards;

// Event
new g_Event;

// Vip
new bool:g_vip[33]
