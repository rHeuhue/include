#if defined _rsmskins_const_included
	#endinput
#endif

#define _rsmskins_const_included
#include <reapi_stocks>

/**
 * Maximum buffer length for queries.
 */ 
#define MAX_QUERY_LENGTH    1024

/**
 * Maximum buffer length for queries.
 */ 
#define MAX_DATA_LENGTH 512

/**
 * Maximum buffer length for queries.
 */ 
#define MAX_ITEM_LENGTH 128

/**
 * Maximum buffer length for queries.
 */ 
#define MAX_INFO_LENGTH 35

/**
 * Maximum buffer length for queries.
 */ 
#define MAX_NUM_LENGTH  16

/**
 * Maximum buffer length for integers.
 */ 
#define MAX_INT_LENGTH      7

/**
 * Maximum buffer length for queries.
 */ 
#define MAX_WEAPONS_EX  25

/*
 * Task for menu status update.
 */
#define TASK_UPDATE     2435

/*
 * Task for regeneration.
 */
#define TASK_REGEN      5432

/*
 * No weapon string.
 */
#define WEAPON_NONE  	"n/a"

 /*
 * Default gravity amount.
 */
 #define DEFAULT_GRAVITY_AMOUNT 800

/*
 * Default max amounts for health, armor and money on kill.
 */
#define DEFAULT_MAX_AMOUNT 100

/*
 * Default FX rendering amount.
 */
#define DEFAULT_FX_AMOUNT 19

/*
 * Default brightness rendering amount.
 */
#define DEFAULT_BRIGHTNESS_AMOUNT 40

/**
 * Weapon ID types.
 */
enum  
{
	WEAPON_KNIFE_EX, 		
	WEAPON_GLOCK18_EX, 
	WEAPON_USP_EX, 		
	WEAPON_P228_EX, 		
	WEAPON_DEAGLE_EX, 	
	WEAPON_FIVESEVEN_EX, 	
	WEAPON_ELITE_EX, 		
	WEAPON_M3_EX, 		
	WEAPON_XM1014_EX, 
	WEAPON_TMP_EX, 		
	WEAPON_MAC10_EX, 	
	WEAPON_MP5N_EX, 		
	WEAPON_UMP45_EX, 		
	WEAPON_P90_EX, 		
	WEAPON_M249_EX, 			
	WEAPON_GALIL_EX,
	WEAPON_FAMAS_EX, 		
	WEAPON_AK47_EX, 		
	WEAPON_M4A1_EX, 		
	WEAPON_SG552_EX, 		
	WEAPON_AUG_EX, 	
	WEAPON_SCOUT_EX, 		
	WEAPON_AWP_EX, 		
	WEAPON_G3SG1_EX, 		
	WEAPON_SG550_EX
}

/** 
 * Safe types.
 */
enum
{
	SAVE_NONE,
	SAVE_NVAULT,
	SAVE_SQLITE
}

/**
 * Vault types.
 */
enum
{
	VAULT_SAVE,
	VAULT_LOAD
}

/**
 * SQLite data types.
 */
enum
{
	SQLITE_SAVE,
	SQLITE_LOAD
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
 * Check types.
 */
enum
{
	CHECK_NAME,
	CHECK_ATRIBUTES,
	CHECK_ACCESS
}

/**
 * Cvars.
 */
enum _:Settings
{
	SAVE_SKINS,
	SAVE_TYPE,
	MENU_FLAGS[MAX_NUM_LENGTH],
	MENU_REOPEN,
	SPAWN_ONLY,
	CHAT_PREFIX[MAX_NAME_LENGTH]
}

/**
 * Weapon list types.
 */
enum _:WeaponsList
{
	WeaponId,
	WeaponName[MAX_NAME_LENGTH]
}

/**
 * Model types.
 */
enum _:ModelType 
{
	V_MODEL,
	P_MODEL
}

/**
 * Health values.
 */
enum _:HealthValues
{
	HEALTH_AMOUNT,
	HEALTH_MAX
}

/**
 * Armor values.
 */
enum _:ArmorValues
{
	ARMOR_AMOUNT,
	ARMOR_MAX
}

/**
 * Money values.
 */
enum _:MoneyValues
{
	MONEY_AMOUNT,
	MONEY_MAX
}

/**
 * Glow values.
 */
enum _:GlowValues
{
	GLOW_RED,
	GLOW_GREEN,
	GLOW_BLUE,
	GLOW_BRIGHTNESS,
	GLOW_FX,
	GLOW_RENDER
}

/**
 * Knockback values.
 */
enum _:KnockValues
{
	KNOCK_POWER,
	KNOCK_VELOCITY
}

/**
 * Regeneration values.
 */
enum _:RegenValues
{
	REGEN_HEALTH,
	REGEN_MAXHEALTH,
	REGEN_INTERVAL
}

/**
 * Weapons info types.
 */
enum _:WeaponsInfo
{
	WpnName[MAX_RESOURCE_PATH_LENGTH],
	WpnSkinName[MAX_USER_INFO_LENGTH],
	WpnSkinModel[MAX_RESOURCE_PATH_LENGTH],
	Description[MAX_USER_INFO_LENGTH],
	Level,
	Flags[MAX_NUM_LENGTH],
	Damage[MAX_NUM_LENGTH],
	Gravity,
	Float:Speed,
	SilentSteps,
	Protection[MAX_NUM_LENGTH],
	Health[HealthValues],
	Armor[ArmorValues],
	Money[MoneyValues],
	Glow[GlowValues],
	Knockback[KnockValues],
	Regeneration[RegenValues]
}