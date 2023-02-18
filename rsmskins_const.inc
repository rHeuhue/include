#if defined _rsmskins_const_included
	#endinput
#endif

#define _rsmskins_const_included
#include <reapi_stocks>

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
 * Maximum buffer length for queries.
 */ 
#define MAX_WEAPONS_EX  25

/*
 * Task for XP HUD information.
 */
#define TASK_UPDATE     2435

/*
 * No weapon string.
 */
#define WEAPON_NONE  	"n/a"

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
 * Vault types.
 */
enum
{
	VAULT_SAVE,
	VAULT_LOAD
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
 * Cvars.
 */
enum Cvars
{
	rsmskins_save_skins,
	rsmskins_save_type,
	rsmskins_flags[MAX_NUM_LENGTH],
	rsmskins_reopen,
	rsmskins_spawn
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
 * Weapons info types.
 */
enum _:WeaponsInfo
{
	WpnName[MAX_NUM_LENGTH],
	WpnSkinName[MAX_NAME_LENGTH],
	WpnSkinModel[MAX_RESOURCE_PATH_LENGTH],
	Level,
	Flags[MAX_NUM_LENGTH],
	Damage[MAX_NUM_LENGTH],
	Gravity,
	Float:Speed,
	SilentSteps,
	Health[HealthValues],
	Armor[ArmorValues],
	Money[MoneyValues],
	Glow[GlowValues]
}