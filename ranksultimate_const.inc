#if defined _ranksultimate_const_included
    #endinput
#endif

#define _ranksultimate_const_included
#include <reapi_stocks>

#define GetSkillRange(%0) (100.0 * (float(g_pPlayerData[%0][Kills]) / float(g_pPlayerData[%0][Kills] + g_pPlayerData[%0][Deaths])))
#define is_user_valid(%0) (0 < %0 && %0 < g_iMaxPlayers)

/*
 * Maxiumum names length.
 */
#define NAMES_LENGTH        28

/**
 * Maximum buffer length for queries.
 */ 
#define MAX_QUERY_LENGTH    1024

/**
 * Maximum buffer length for integers.
 */ 
#define MAX_INT_LENGTH      7

/**
 * Maximum buffer length for datas.
 */ 
#define MAX_DATA_LENGTH     512

/**
 * Maximum buffer length for items.
 */ 
#define MAX_ITEM_LENGTH     128

/**
 * Maximum buffer length for player info.
 */ 
#define MAX_INFO_LENGTH     35

/**
 * Maximum buffer length for nums.
 */ 
#define MAX_NUM_LENGTH      16

/**
 * Maximum weapons amount.
 */ 
#define MAX_WEAPONS_EX      26

/**
 * Maximum orders amount.
 */ 
#define MAX_ORDERS          9

/*
 * Task for HUD rank status.
 */
#define TASK_RANK           2465

/*
 * Task for XP HUD information.
 */
#define TASK_HUD            2475

/*
 * Task for reseting client XP.
 */
#define TASK_RESETXP        9546

/*
 * Task for reseting team XP.
 */
#define TASK_TEAM_XP        1453

/**
 * Weapon ID types.
 */
enum  
{
    WEAPON__KNIFE,        
    WEAPON__GLOCK18, 
    WEAPON__USP,      
    WEAPON__P228,         
    WEAPON__DEAGLE,   
    WEAPON__FIVESEVEN,    
    WEAPON__ELITE,        
    WEAPON__M3,       
    WEAPON__XM1014, 
    WEAPON__TMP,      
    WEAPON__MAC10,    
    WEAPON__MP5N,         
    WEAPON__UMP45,        
    WEAPON__P90,      
    WEAPON__M249,             
    WEAPON__GALIL,
    WEAPON__FAMAS,        
    WEAPON__AK47,         
    WEAPON__M4A1,         
    WEAPON__SG552,        
    WEAPON__AUG,  
    WEAPON__SCOUT,        
    WEAPON__AWP,      
    WEAPON__G3SG1,        
    WEAPON__SG550,
    WEAPON__GRENADE
}

/*
 * Weapons Names.
 */
new g_szWeapon[MAX_WEAPONS_EX][MAX_NAME_LENGTH] =
{
    "knife",
    "glock18",
    "usp",
    "p228",
    "deagle",
    "fiveseven",
    "elite",
    "m3",
    "xm1014",
    "tmp",
    "mac10",
    "mp5navy",
    "ump45",
    "p90",
    "m249",
    "galil",
    "famas",
    "ak47",
    "m4a1",
    "sg552",
    "aug",
    "scout",
    "awp",
    "g3sg1",
    "sg550",
    "grenade"
}

/**
 * Settings types.
 */
enum
{
    SECTION_NONE,
    SECTION_MYSQL,
    SECTION_RANKS,
    SECTION_SETTINGS,
    SECTION_REWARDS,
    SECTION_SKILLS,
    SECTION_COMMANDS
}

/**
 * Save types.
 */
enum
{
    SAVE_NAME,
    SAVE_IP,
    SAVE_STEAMID
}

/**
 * Mysql data types.
 */
enum
{
    MYSQL_SAVE,
    MYSQL_LOAD
}

/**
 * Level types.
 */
enum
{
    LEVEL_UP,
    LEVEL_DN
}

/**
 * MVP types.
 */
enum
{
    MOST_KILLS,
    BOMB_EXPLODE,
    BOMB_DEFUSE
}

/**
 * Reward types.
 */
enum
{
    XP_REWARD,
    XP_TEAM_REWARD
}

/**
 * Teams.
 */
enum
{
    TEAM_NONE,
    TEAM_T,
    TEAM_CT,
    TEAM_SPEC
}

/**
 * Types of orders.
 */
enum
{
    ORDER_XP,
    ORDER_KILLS,
    ORDER_MVPS,
    ORDER_ROUNDS_WON,
    ORDER_BOMBS_PLANTED,
    ORDER_BOMBS_EXPLODED,
    ORDER_BOMBS_DEFUSED,
    ORDER_PLAYED_TIME,
    ORDER_SKILL
}

/*
 * Player types.
 */
enum
{
    PLAYER,
    NICK
}

/*
 * Loaded types.
 */
enum
{
    LOAD_STATS,
    LOAD_KILLS
}

/*
 * Dates types.
 */
enum
{
    FIRST_LOGIN,
    LAST_LOGIN
}

/*
 * Setinfo types.
 */
enum
{
    SETINFO_HUD,
    SETINFO_RANK
}

/*
 * HUD types.
 */
enum
{
    RANK_HUD,
    XP_HUD,
    XP_TEAM_HUD
}

/**
 * Steam data types.
 */
enum _:SteamData
{
    STEAM_AVATAR,
    STEAM_PROFILE
}

/*
 * Win data types.
 */
enum _:eWinData
{
    TERR_WIN, CTs_WIN, 
    ROUND_DRAW,
    TERR_LOSE, CTs_LOSE
}

/*
 * Player data for a single map.
 */
enum _:MapData
{
    MAP_MVP,
    MAP_XP
}

/**
 * Assist types.
 */
enum _:AssistValues
{
    ASSIST_MIN_DMG,
    ASSIST_MONEY,
    ASSIST_FRAG
}

/*
 * Player data information.
 */
enum _:PlayerData
{
    IP[MAX_IP_LENGTH],
    RankID,
    Level,
    Xp,
    Kills,
    Deaths,
    Headshots,
    Assists,
    Shots,
    Hits,
    Damage,
    Planted,
    Exploded,
    Defused,
    MVP,
    RoundsWon,
    PlayedTime,
    FirstLogin[MAX_INFO_LENGTH],
    LastLogin[MAX_INFO_LENGTH],
    Flags[MAX_NAME_LENGTH],
    Steam
}

/*
 * Assist data information.
 */
enum _:AssistData
{
    AssistName[MAX_NAME_LENGTH],
    AssistDamage[MAX_PLAYERS + 1],
    Float:AssistDamageOnTime[MAX_PLAYERS + 1],
    bool:IsFlashed[MAX_PLAYERS + 1]
}

/*
 * Ranks information.
 */
enum _:RankInfo
{
    RankName[MAX_NAME_LENGTH],
    RankXp
}

/*
 * Skills information.
 */
enum _:SkillInfo
{
    SkillName[MAX_NUM_LENGTH],
    Float:SkillRange
}

/*
 * HUD values.
 */
enum _:HudValues
{
    Float:HUD_COLOR1,
    Float:HUD_COLOR2,
    Float:HUD_COLOR3,
    Float:HUD_POS_X,
    Float:HUD_POS_Y,
    Float:HUD_EFFECT,
    Float:HUD_HOLD_TIME
}

/*
 * Screen values.
 */
enum _:ScreenValues
{
    Float:SCREEN_COLOR1,
    Float:SCREEN_COLOR2,
    Float:SCREEN_COLOR3,
    Float:SCREEN_ALPHA,
    Float:SCREEN_HOLD_TIME
}

/*
 * Settings.
 */
enum _:Settings
{
    MYSQL_HOST[MAX_NAME_LENGTH],
    MYSQL_USER[MAX_NAME_LENGTH],
    MYSQL_PASSWORD[MAX_NAME_LENGTH],
    MYSQL_DATABASE[MAX_NAME_LENGTH],
    MYSQL_TABLE[MAX_NAME_LENGTH],
    MYSQL_TABLE2[MAX_NAME_LENGTH],
    MYSQL_TABLE3[MAX_NAME_LENGTH],
    MYSQL_REALTIME,
    WEBSITE_LINK[MAX_USER_INFO_LENGTH],
    STEAM_API_KEY[MAX_USER_INFO_LENGTH],
    SAVE_TYPE,
    CHAT_PREFIX[MAX_NAME_LENGTH],
    RANK_INFO,
    RANK_BOTS,
    TIME_NEW,
    DEFAULT_ORDER,
    MINIMUM_PLAYERS,
    TEAM_SET,
    HUD_ENABLE,
    HUD_TYPE,
    HUD_INFO[MAX_DATA_LENGTH],
    HUD_INFO_MAX[MAX_DATA_LENGTH],
    Float:HUD_VALUES[HudValues - 2],
    LEVEL_MESSAGE_TYPE,
    Float:LEVELUP_EFFECTS[ScreenValues],
    LEVELUP_SOUND[MAX_RESOURCE_PATH_LENGTH],
    Float:LEVELDN_EFFECTS[ScreenValues],
    LEVELDN_SOUND[MAX_RESOURCE_PATH_LENGTH],
    ASSIST_VALUES[AssistValues],
    XP_HUD_ENABLE,
    XP_HUD_TEAM_ENABLE,
    XP_HUD_TYPE,
    XP_HUD_TEAM_TYPE,
    XP_HUD_GET[MAX_ITEM_LENGTH],
    XP_HUD_TEAM_GET[MAX_ITEM_LENGTH],
    XP_HUD_LOSE[MAX_ITEM_LENGTH],
    XP_HUD_TEAM_LOSE[MAX_ITEM_LENGTH],
    Float:XP_HUD_VALUES[HudValues],
    Float:XP_HUD_TEAM_VALUES[HudValues],
    MVP_HUD_ENABLE,
    MVP_HUD_TYPE,
    Float:MVP_HUD_VALUES[HudValues - 2],
    VIP_FLAGS[MAX_NUM_LENGTH]
}