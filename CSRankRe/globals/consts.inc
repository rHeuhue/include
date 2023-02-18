#if defined _globals_consts_included
	#endinput
#endif

#define _globals_consts_included 

#if !defined MAX_CLIENTS
	#define MAX_CLIENTS 32
#endif

#define is_valid_player(%0) ( 1<=%0<= MAX_CLIENTS)

#define csr_is_valid_player(%0) (is_valid_player(%0) && is_user_connected(%0))

#define get_weapon_skin(%0) pev(%0, pev_iuser4)
#define set_weapon_skin(%0,%1) set_pev(%0, pev_iuser4, %1)

#define get_weapon_owner(%0,%1,%2) pev(%0, pev_noise3, %1, %2)
#define set_weapon_owner(%0,%1) set_pev(%0, pev_noise3, %1)

#define get_weapon_track(%0) pev(%0, pev_iuser3)
#define set_weapon_track(%0,%1) set_pev(%0, pev_iuser3, %1)


#define LOG_PREFIX PLUGIN
#define MAIN_CONFIG "CSRankRe.cfg"

#define LOG_FILE_ITEM_RARE "addons/amxmodx/logs/CSRank_take_items.log"

const WEAPON_SIZE = 31;
const PEV_SPEC_TARGET = pev_iuser2

new const ITEM_CLASS_NAME [][] = 
{
	"CSRE_ITEM_NORMAL",
	"CSRE_ITEM_RARE",
	"CSRE_ITEM_LEGENDARY"
}

const SKINS_ID_MAX_LEN = 12
const SKINS_RARITY_MAX_LEN = 12

const SKIN_STR_LEN = 22
const ZERO_SKIN_INT = -1337

enum _:ItemClass {
	ITEM_CLASS_NORMAl = 1,
	ITEM_CLASS_RARE = 2,

	ITEM_CLASS_LEGENDARY = 3,
}

new const g_szSoundLevelUp[] = "CSRankRe/level_up.wav"
new const g_szSoundMedalUp[] = "CSRankRe/medal_up.wav"

