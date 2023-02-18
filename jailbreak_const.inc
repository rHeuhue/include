#if defined _jailbreak_const_included
	#endinput
#endif

#define _jailbreak_const_included

#define CONFIGS_PATH "addons/amxmodx/configs/jailbreak"

/* From LastRequest */

//Last requests
enum LastRequest
{
	LR_NONE = -1,
	LR_SHOT4SHOT,
	LR_SPRAY,
	LR_RACE,
	LR_WEAPONTOSS,
	LR_KNIFEBATTLE,
	LR_GRENADETOSS,
	LR_SHOTGUNBATTLE,
	LR_FREEDAY
};

//Last request players
enum LastRequestPlayer
{
	PRISONER,
	GUARD
};

/* From special days */

//Days
enum Days
{
	NORMAL_DAY,
	HIDENSEEK_DAY,
	SAMURAI_DAY,
	SPACE_DAY,
	KNIFE_DAY,
	SHARK_DAY,
	PRESIDENT_DAY,
	MARIO_DAY,
	AWP_DAY,
	ZOMBIE_DAY,
	
	TotalDays
}

/* Days of week */
enum _:DaysOfWeek
{
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
}

/* From Shop Main */
enum _:ShopReturnValues
{
	SHOP_IGNORE,
	SHOP_BLOCK
}