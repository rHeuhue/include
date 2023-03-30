/* Sublime AMXX Editor v3.0.0-beta */

#if defined _lj_const_included
	#endinput
#endif
#define _lj_const_included

/* Load custom module ?

#pragma reqlib LIBRARY_NAME
#if !defined AMXMODX_NOAUTOLOAD
	#pragma loadlib LIBRARY_NAME
#endif

*/

new const LJ_VERSION[] = "1.0.1"

new const g_szChatPrefix[] = "^4[LJ Training]^3"

native lj_get_user_level(id)

native get_user_boost(id)
native set_user_boost(id, bool:IsBoost)

native give_costumes(id)

native is_user_spec_list(id)
native is_user_spec_hide(id)
native set_user_spec_list(id, bool:bSpecList)
native set_user_spec_hide(id, bool:bSpecHide)

native is_user_show_keys(id)
native set_user_show_keys(id, bool:bShowKeys)

native is_user_stucked(id)
native set_user_unstuck(id)

new const g_szVIP_Players[][] =
{
	"Huehue", "mandiX", "chop"
}

enum _:eWeaponsData
{
	WeaponId[32],
	WeaponName[32],
	WeaponSpeed[32]
}

new const g_szWeapons[][eWeaponsData] =
{
	{ "", "All Weapons", 			"^n                    \rSpeed" },
	{ "weapon_scout", 		"Scout", 						"         \d[\y260\d]" },
	{ "weapon_flashbang", 	"Flashbang", 					"    \d[\yNormal\d]" },
	{ "weapon_awp", 		"AWP", 							"          \d[\y210\d]" },
	{ "weapon_m4a1", 		"M4A1", 						"        \d[\y230\d]" },
	{ "weapon_p90", 		"P90", 							"           \d[\y245\d]" },
	{ "weapon_famas", 		"Famas", 						"       \d[\y240\d]" },
	{ "weapon_ak47", 		"AK-47", 						"           \d[\y221\d]" },
	{ "weapon_m249", 		"M249 \d(Para)", 				" \d[\y220\d]" },
}

enum eKnifeItems
{
	HANDS = 0,
	KUNAI,
	MOON,
	OWL,
	RULER,
	WINDFAN,
	TRON,
	DEFAULT_KNIFE
}

enum _:eKnifeData
{
	KnifePath[128],
	KnifeName[64],
	KnifeLevel
}

new const g_szKnifeModels[][eKnifeData] =
{
	{ "models/lj_knives/v_hands.mdl", 	"Bare Hands", 		1 	},
	{ "models/lj_knives/v_kunai.mdl", 	"Kunai", 			5 	},
	{ "models/lj_knives/v_moon.mdl", 	"Moon Knight", 		8 	},
	{ "models/lj_knives/v_owl.mdl", 	"Owl", 				12 	},
	{ "models/lj_knives/v_ruler.mdl", 	"Ruler", 			15 	},
	{ "models/lj_knives/v_windfan.mdl", "Wind Fan", 		20 	},
	{ "models/lj_knives/v_tron.mdl", 	"Tron", 			25 	},
	{ "models/v_knife.mdl", 			"Default Knife", 	0 	}
}

enum eModelItems
{
	BELKAGIRL = 0,
	JOKER,
	MASK,
	SURVIVOR,
	VECTOR,
	DEFAULT_PLAYER
}

enum _:eModelsData
{
	PlayerModel_Path[64],
	PlayerModel_Name[64],
	PlayerModel_Level
}

new const g_szPlayerModels[][eModelsData] =
{
	{ "lj_belka", 				"Belka Girl", 							4 	},
	{ "lj_joker", 				"Joker", 								7 	},
	{ "lj_mask", 				"Mask", 								13 	},
	{ "lj_survivor", 			"Survivor", 							20 	},
	{ "lj_vector", 				"Vector", 								25 	},
	{ "lj_default", 			"Default Model \d[\yRan\rdom \yCo\rlor\d]^n", 0 	},
}

new g_iLJ_TrainingMenu;

enum _:ePlayerData
{
	bool:GodMode,
	bool:NoClip,
	Knife,
	Player_Model,
	bool:Camera,
	bool:CameraSolid,
	bool:KnifeHidden,
	bool:JumpTrail,
	bool:HudInfo,
	CustomChannel
}

new g_iPlayerData[MAX_CLIENTS + 1][ePlayerData]

enum _:ePlayerGC
{
	CheckPoint,
	CPs,
	GCs,
	CheckPointPos[XYZ],
	CheckPointAngle[XYZ],
	LastCheckPointPos[XYZ],
	LastCheckPointAngle[XYZ]
}

new g_iPlayerGC[MAX_CLIENTS + 1][ePlayerGC]

const TASKID_TRAIL = 100
new Float:g_flTrailTime[MAX_CLIENTS + 1], g_pSpriteTrail

new const g_szCheckPointCmds[][] = { "say /cp", "say /checkpoint", "/cp", "cp" }
new const g_szGoCheckCmds[][] = { "say /gc", "say /gocheck", "/gc", "gc"  }

new g_iSyncObject

Base_Commands_Init()
{
	register_clcmd("chooseteam", "Toggle_TrainingMenu")
	register_clcmd("say /menu", "Toggle_TrainingMenu")
	register_clcmd("say /training", "Toggle_TrainingMenu")

	register_concmd("Custom_Channel", "Channel_TypeIn")

	register_clcmd("buy", 				"@Block_BuyCMD")
	register_clcmd("buyammo1", 			"@Block_BuyCMD")
	register_clcmd("buyammo2", 			"@Block_BuyCMD")
	register_clcmd("autobuy", 			"@Block_BuyCMD")
	register_clcmd("drop", 				"@Block_BuyCMD")

	static i

	for (i = 0; i < sizeof g_szCheckPointCmds; i++)
		register_clcmd(g_szCheckPointCmds[i], "Toggle_CheckPoint")

	for (i = 0; i < sizeof g_szGoCheckCmds; i++)
		register_clcmd(g_szGoCheckCmds[i], "Toggle_GoCheckPoint")
}

ReAPI_Init()
{
	RegisterHookChain(RG_CBasePlayer_Spawn, "CBasePlayer_Spawn", true)
	RegisterHookChain(RG_CBasePlayerWeapon_DefaultDeploy, "CBasePlayerWeapon_DefaultDeploy", false)
	//RegisterHookChain(RG_PlayerBlind, "PlayerBlind", false)

	RegisterHookChain(RG_CBasePlayer_Jump, "CBasePlayer_Jump", true)

	RegisterHookChain(RG_CBasePlayer_HintMessageEx, "CBasePlayer_HintMessageEx") // Hint_you_are_the_vip

	rg_map_buy_status(true)
}

Fakemeta_Init()
{
	register_forward(FM_AddToFullPack, "Camera_AddToFullPack", 1)
	register_forward(FM_AddToFullPack, "Channel_AddToFullPack", 0)
}

Engine_Init()
{
	g_iSyncObject = CreateHudSyncObj()
	
	new iEnt = create_entity("info_target")
	
	if(iEnt)
	{
		entity_set_string(iEnt, EV_SZ_classname, "ThinkEntity")
		entity_set_float(iEnt, EV_FL_nextthink, get_gametime() + 1.0)
		
		register_think("ThinkEntity", "Information_Hud")
	}
}

Menu_Create_Init()
{
	g_iLJ_TrainingMenu = register_menuid("Training Menu");
	register_menucmd(g_iLJ_TrainingMenu, 1023, "handleTrainingMenu");
}

Precache_Resources()
{
	precache_model("models/rpgrocket.mdl")

	g_pSpriteTrail = precache_model("sprites/zbeam5.spr");

	static i
		
	for (i = 0; i < sizeof g_szKnifeModels; i++)
		precache_model(g_szKnifeModels[i][KnifePath])

	for (i = 0; i < sizeof g_szPlayerModels; i++)
		try_precache_player_model(g_szPlayerModels[i][PlayerModel_Path])
}

Configurate_Cvars()
{
	set_cvar_num("mp_item_staytime", 0)
	set_cvar_num("mp_round_infinite", 1)
	set_cvar_num("mp_auto_join_team", 1)
	set_cvar_string("humans_join_team", "CT")
	set_cvar_float("mp_forcerespawn", 0.1)
}

@CBasePlayer_MakeVIP(id)
{
	for (new i = 0; i < sizeof g_szVIP_Players; i++)
	{
		if (equal(fmt("%n", id), g_szVIP_Players[i]))
		{
			// Set the m_bIsVIP to true & respawn player to show DirectHUD Message
			set_member(id, m_bIsVIP, true)
			rg_round_respawn(id)

			// Update the ScoreBoard Information
			message_begin(MSG_ALL, get_user_msgid("ScoreAttrib")) 
			write_byte(id) 
			write_byte(4) 
			message_end()

			// Then set the m_bIsVIP to false bcuz VIPs can't use Weapons!
			set_member(id, m_bIsVIP, false)

			if (is_user_alive(id))
			{
				set_task(1.0, "Vip_Infomation_Start", id)
				set_task(7.0, "Vip_Infomation_Stop", id)
			}
		}
	}
}

@Block_BuyCMD(id)
{
	return PLUGIN_HANDLED
}