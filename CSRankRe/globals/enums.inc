#if defined _globals_enums_included
	#endinput
#endif

#define _globals_enums_included 

enum _:Items
{
	ITEM_ID = 0,
	ITEM_REPLACE[32],
	ITEM_NAME[64],
	ITEM_MODEL_V[64],
	ITEM_MODEL_P[64],
	ITEM_MODEL_W[64],
	ITEM_CLASS,
	bool:ITEM_GET_FROM_CONTAINER,
	ITEM_EVENT
}


enum _:PlayerData
{
	bool:PD_LOAD,
	PD_ID,
	PD_NAME[32],
	PD_AUTHID[26],
	PD_IP[26],
	PD_PASSWORD,
	PD_TOTAL_TIME,
	PD_LAST_TIME,
	PD_CHECK_TIME
}

enum _:PlayerStats
{
	PS_PLAYER = 0,
	PS_EXP,
	PS_EXP_TOTAL,
	PS_LEVEL,
	PS_MEDALS,
	PS_CASES,
	PS_CASES_TOTAL,
	PS_KEYS,
	PS_KEYS_TOTAL,
	PS_COINS,
	PS_COINS_TOTAL,
	PS_GOLDS,
	PS_GOLDS_TOTAL,
	PS_REWARDS
}

enum _:ReTeams {
	RE_TEAM_UNKOWN = 0,
	RE_TEAM_T = 1,
	RE_TEAM_CT = 2,
	RE_TEAM_SPECTATOR = 3
}

enum _:OperLoadItems {
	OLI_PLAYER,
	OLI_ID,
	OLI_FUNCTION[32]
}

enum any:mpArray
{
	MP_ID, // offers creator
	MP_ITEM, // item_id
	MP_PRICE, // 
	MP_TYPE, // 
	MP_FOR,
	MP_STATUS
}


enum _:RewardsArray
{
	RA_TYPE,
	RA_COUNT
}