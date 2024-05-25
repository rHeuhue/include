// ***************************************************************************
// Author: B. Josh Becker
// Description: This page contains defines as well as the variables used
// in this plugin
// ***************************************************************************

#define TASK_ITEMS			0		// Showing items in the HUD
#define TASK_SPAWN			32		// Respawning from revive
#define TASK_IMPALE			64		// Crypt Lord's Impale
#define TASK_BANISH			96		// Used to set the user's origin back to normal
#define TASK_SPAWNREMOVEGOD	128		// Gives the user godmode for a brief period after they respawn
#define TASK_EXPLOSION		160		// From Suicide Bomber
#define TASK_BEAMCYLINDER	192		// From Suicide Bomber
#define	TASK_GETINPUT		224		// Calls getuserinput function
#define TASK_COOLDOWN		256		// Ultimate Cooldown function
#define TASK_TRANSPORT		288		// Transport function for ITEM_MOLE
#define TASK_MOLE			320		// Used for mole + fan of knives
#define	TASK_WAVE			352		// Healing Wave
#define	TASK_AURA			112233	// Arcane Aura
#define	TASK_REINCARNATION	384		// Weapon Reincarnation
#define	TASK_GLOW			416		// Calls glow_change
#define	TASK_REMOVEBUYZONE	448		// This will remove a buyzone
#define	TASK_HEX			480		// Jumper task (goomba)
#define	TASK_RESETSPEED		512		// Reset maxspeed (bash)
#define	TASK_ITEM_GLOVES	544		// Nade timer (gloves)
#define	TASK_UNHOLYSPEED	576		// Unholyspeed timer
#define	TASK_RESETGOD		608		// Reset god mode
#define	TASK_BLINKCHECK		640		// Check to see if the player teleported into an invalid location
#define	TASK_BLINKSTUCK		672		// Checks to see if a user is stuck after blinking
#define	TASK_BIGBADATTACKER	704		// _SH_ResetBigBadAttacker
#define	TASK_TELEPORT		736		// For teleporting someone w00t
//#define	TASK_TELEPORT		768		// Teleports the player
//#define	TASK_TELEFADEIN		800		// Calls telefadein function
//#define	TASK_UNSTICK		832		// "Unsticks" a stuck teleported player
#define	TASK_SEARCHTARGET	864		// Used by some ultimates
//#define TASK_WALKER			896		// Walker process
#define	TASK_ENTANGLEWAIT	928		// Used for entangling roots
#define	TASK_LIGHTNING		960		// Used for chain lightning
//#define	TASK_LIGHTSEARCH	992		// Used for chain lightning
#define	TASK_LIGHTNINGNEXT	1024	// Used for chain lightning
#define TASK_SPAWNPLAYER	1056	// Used to spawn a player (final spawn call)
#define TASK_GIVEITEMS		1088	// Used to give a player his items after spawning
#define	TASK_ITEM_RING	1120	// Used with rings of regeneration
#define	TASK_SILENCEBURST	1152
//#define	TASK_ONFIRE			1184	// Used with flamethrower
//#define	TASK_HEALNOW		1226	// Used with Healing Waves
#define	TASK_HEALNEXT		1258	// Used with Healing Waves
#define	TASK_LIGHT			1290	// Used with serpant wards
#define	TASK_SHIELD			1322	// Used to check for shield
#define	TASK_FUNNELS		1354	// Used with Swarming Locusts
#define	TASK_HETHROWEVENT	1386	// Used for nade trails

#define TASK_TEMPENTITY		1460
#define TASK_ANKHGIVEITEMS	1492
#define TASK_HELM			1524
#define	TASK_REINCCHECK		1556
#define TASK_SAVE			1588	// Used for saving XP
//#define TASK_UDELAY			1620	// Ultimate Delay Function
//#define TASK_BURN           1652
#define TASK_BURNING		1684	// Used for Blood Mage Ultimate
#define TASK_FINDTARGET		1706	// Used for finding a target
#define TASK_ULTPING		1738	// Used to play the "ping" sound every second


#define TASK_BUYTIME		2000	// Checks for buytime
#define	TASK_CHECKVOTES		2002	// Used for checking the votes
#define	TASK_FTCONTROLLER	2003	// Used for automatic start/stop
#define	TASK_CHECKWAR3		2004
#define	TASK_EXECUTECONFIG	2005
#define	TASK_AFTERCONFIG	2006
#define	TASK_SETSQL			2007
//#define	TASK_SETLANGUAGE	2008
#define	TASK_SETVARIABLES	2009
#define	TASK_CLONETHINK		2010
//#define	TASK_CHECKMAP		2011
#define TASK_BOIDTHINK		2012
#define TASK_TARGETBOMBED	2013
//#define TASK_BOMBTIMER		2014
//#define TASK_WAR3CHECK		2015	// Checks the value of sv_warcraft3 every 5 seconds (better than checking it on every function call)
#define TASK_SIPHON			2016
#define TASK_ENDULTIMATE	2017
//#define TASK_BEFORE_ROUND_START		2018
#define TASK_MOLEFIX		3000
#define TASK_RESETSPAWNS	3001
#define TASK_UDELAY			3002		// Ultimate delay function
#define	TASK_CROWFORM		3567		// 
#define	TASK_FROSTBITE		4567		// Frostbite 	

// From ../multiplayer source/dlls/player.cpp
#define ARMOR_RATIO	 0.7	// Armor Takes 30% of the damage (was .2 in the SDK)
#define ARMOR_BONUS  0.5	// Each Point of Armor is work 1/x points of health

#define TE_BEAMPOINTS		0
#define TE_EXPLOSION		3
#define	TE_TAREXPLOSION		4
#define TE_SMOKE			5
#define TE_BEAMENTS			8
#define	TE_LAVASPLASH		10
#define	TE_TELEPORT			11
#define TE_IMPLOSION		14
#define TE_SPRITETRAIL		15
#define TE_SPRITE			17
#define TE_BEAMCYLINDER		21
#define TE_BEAMFOLLOW		22
#define TE_STREAK_SPLASH	25
#define TE_ELIGHT			28
#define TE_LARGEFUNNEL		100
#define TE_FIZZ				105		// create alpha sprites inside of entity, float upwards
#define TE_BUBBLES			113		// create alpha sprites inside of box, float upwards
#define TE_SPRAY			120
#define TE_PLAYERATTACHMENT 124

#define	EF_BRIGHTFIELD		1

#define TE_EXPLFLAG_NONE	0

#define MAX_NAME_LENGTH 32
#define MAX_VAR_LENGTH 64 
#define RACE_SKILL_LENGTH 64
#define RACE_SKILL_LENGTH_F 63
#define RACE_NAME_LENGTH 64
#define RACE_NAME_LENGTH_F 63
#define ITEM_NAME_LENGTH 64
#define ITEM_NAME_LENGTH_F 63
#define SHORT_RACE_NAME_LENGTH 16
#define SHORT_RACE_NAME_LENGTH_F 15
#define SHORT_ITEM_NAME_LENGTH 32
#define SHORT_ITEM_NAME_LENGTH_F 31

#define TELEPORT_RADIUS			50
#define LIGHTNING_RANGE			500
#define ORB_DAMAGE				20			// Damage done by Orb of Annihilation

// CS AmmoX Types
#define AMMOX_338MAGNUM			1     // AWP
#define AMMOX_762NATO			2     // AK47, SCOUT, G3SG1
#define AMMOX_556NATOBOX		3     // MG
#define AMMOX_556NATO			4     // SG552, GALI, FAMAS, M4A1, AUG, SG550
#define AMMOX_BUCKSHOT			5     // M3, XM1014
#define AMMOX_45ACP				6     // MAC10, UMP45, USP
#define AMMOX_57MM				7     // P90, FIVESEVEN
#define AMMOX_50AE				8     // DEAGLE
#define AMMOX_357SIG			9     // P228
#define AMMOX_9MM				10     // MP5NAVY, TMP, GLOCK18, ELITE
#define AMMOX_FLASHBANG			11     // Flashbang
#define AMMOX_HEGRENADE			12     // HE Grenade
#define AMMOX_SMOKEGRENADE		13     // Smoke Grenade


#define HITGROUP_GENERIC		0 // none
#define HITGROUP_HEAD			1 // 1 << 1 = 2
#define HITGROUP_CHEST			2 // 1 << 2 = 4
#define HITGROUP_STOMACH		3 // 8
#define HITGROUP_LEFTARM		4 // 16
#define HITGROUP_RIGHTARM		5 // 32
#define HITGROUP_LEFTLEG		6 // 64
#define HITGROUP_RIGHTLEG		7 // 128

/*	 Weapon IDs	 */
#define CSW_WORLDSPAWN			0 

#if !defined CSW_GALIL
	#define CSW_GALIL			14
#endif
#if !defined CSW_FAMAS
	#define CSW_FAMAS			15
#endif

#define CSW_WAR3_MIN			51

#define	CSW_LIGHTNING			51
#define	CSW_SUICIDE				52
#define	CSW_IMMOLATE			53
#define	CSW_LOCUSTS				54
#define	CSW_SERPENTWARD			55
#define CSW_SHADOW				56
#define	CSW_THORNS				57
#define	CSW_CARAPACE			58
#define CSW_CARRION				59
#define CSW_ORB					60
#define CSW_CONCOCTION			61
#define CSW_BANISH				62

#define CSW_WAR3_MAX			62

// Should be equal to (CSW_WAR3_MIN - CSW_WAR3_MAX) + 1
#define MAX_CSW_S				12

// Race numbers

#define MAX_RACES					11

#define RACE_NONE				0
#define RACE_UNDEAD				1
#define RACE_HUMAN				2
#define RACE_ORC				3
#define RACE_ELF				4
#define RACE_BLOOD				5
#define RACE_SHADOW				6
#define RACE_WARDEN				7
#define RACE_CRYPT				8
#define	RACE_CRYSTAL			9
#define	RACE_DRUID				10

#define RACE_CHAMELEON			11

// Language  
new const Lang_RaceName[][] =
{
	"No Race",
	"Undead",	
	"Human",	
	"Orc",	
	"Night Elf",	
	"Blood Elf",
	"Shaman",
	"Warden",
	"Nerubian",
	"Crystal",
	"Druid",
	"Polymorph"
}



// team ids 
#define UNASSIGNED 0 
#define TS 1 
#define CTS 2 
#define AUTO_TEAM 5 

// New team ID defines
#define TEAM_T		1
#define TEAM_CT		2

// To determine what game is running
#define GAME_CSTRIKE		1
#define GAME_CZERO			2


// Used with PB_SKINSWITCHED
#define SKIN_RESET					0
#define SKIN_SWITCH					1

#define KEY_1						0
#define KEY_2						1
#define KEY_3						2
#define KEY_4						3
#define KEY_5						4
#define KEY_6						5
#define KEY_7						6
#define KEY_8						7
#define KEY_9						8
#define KEY_0						9

#define XPOS						0
#define YPOS						1
#define ZPOS						2

#define DISPLAYLEVEL_NONE			0
#define DISPLAYLEVEL_SHOWRACE		1
#define DISPLAYLEVEL_SHOWGAINED		2
//#define DISPLAYLEVEL_SHOWBOTH		3
#define	DISPLAYLEVEL_SHOWRACECHAT	4



#define MAX_LEVELS					10

// ***************************************************************************
// The following section contains defines for the player_data array, it pretty much
// stores everything.  
//		P_ is within player_data
//		PB_ is within player_data_bool array
// ***************************************************************************
	// ***************************
	//		Start of info for player_data
	// ***************************

	#define P_RACE                  0		// Race
	//#define P_SKILL1                1		// Skill 1 level
	//#define P_SKILL2                2		// Skill 2 level
	//#define P_SKILL3                3		// Skill 4 level
	//#define P_ULTIMATE              4		// Ultimate level
	#define P_LEVEL					5		// Player Level
	#define P_XP                    6		// Current XP

	// Miscellaneous options
	#define P_SPECMODE				7		// Used to determine if the player is spectating or not
	#define P_SHOWRACEMENU			8		// Should we show the race menu when the player respawns?
	#define P_SHOWICONS				9		// Show player icons/levels for this player?
	#define P_CHANGERACE			10		// Holds the value of what race to change to when the following round starts

	// Used for weapon Reincarnation
	#define P_FLASHCOUNT			11		// Number of flash grenades bought that round
	#define	P_HECOUNT				12		// Number of HE's bought that round
	#define P_SMOKECOUNT			13		// Number of smoke grenades bought that round
	#define P_ARMORONDEATH			14		// Amount of armor the player had when he/she died
	#define P_LASTARMOR				15		// This will contain the previous value of P_ARMORONDEATH

	// Used by various ultimates/abilities
	#define P_TELEMENU				16		// Used by teleport
	#define P_TEAM					17		// Stores the player's team ID
	//#define P_SHADOWCOUNT			18		// Number of shadow strikes the player has left
	#define P_SERPENTCOUNT			19		// Number of serpent wards the player has left
	#define P_RINGS					20
	#define P_ULTIMATEDELAY			21
	#define P_RESPAWNBY				22		// Stores how the user is going to respawn

	

	#define P_LAST					24
	// ***************************
	//		End of info for player_data
	// ***************************


	// ***************************
	//		Start of info for player_data_bool
	// ***************************

	// Miscellaneous
	#define PB_SKINSWITCHED			0		// Set if the user's skin has been changed
	#define PB_RESETSKILLS			1		// Does the player want to reset their skills in the next round?
	#define PB_CHANGINGTEAM			2		// Is the user currently changing his/her team?
	#define PB_DIEDLASTROUND		3		// Did the user died during the previous round?

	// Used for weapon Reincarnation
	#define PB_DEFUSE				4		// Player had a defuse kit when he/she died?
	#define PB_SHIELD				5		// Player had a shield when he/she died?
	#define PB_NIGHTVISION			6		// Player had nightvision when he/she died?
	#define PB_USP_SILENCED			28		// USP silenced on death?
	#define PB_M4A1_SILENCED		29		// M4A1 silenced on death?
	#define PB_GLOCK_BURST			30		// Glock in burst mode on death?
	#define PB_FAMAS_BURST			31		// Famas in burst mode on death?


	// Used by various ultimates/abilities
	#define PB_GIVEITEMS			7		// Tells weapon controller function to give the player his items after respawning
	#define PB_NADEJUSTRECEIVED		8		// Used with flaming gloves... (removable?)
	#define PB_MOLE					9		// Is the player a mole?
	#define PB_PHOENIX				10		// Will this player have phoenix?
	#define PB_WARDENBLINK			11		// Does this player have blink enabled?
	#define PB_SUICIDEATTEMPT		12		// Has this player made a suicide attempt for undead's ultimate?
	#define PB_ISBURNING			13		// Is the player burning from the immolate ultimate?
	#define PB_STUNNED				14
	#define PB_SLOWED				15
	#define PB_ISSEARCHING			16
	#define PB_LIGHTNINGHIT			17
	#define PB_INVIS				18
	#define PB_HEXED				19		// Is the player hexed? (All abilities are disabled)
	#define PB_JUSTJOINED			20
	#define PB_ISCONNECTED			21
	#define PB_GODMODE				22

	#define PB_HAS_SPAWNED			23		// Has the player previously spawned this round?
	#define PB_CAN_RENDER			24

	#define PB_NO_DAMAGE			25
	#define PB_BIGBAD_ATTACKER		26		// This user is allowed to attack a user running big bad voodoo!

	#define PB_ISPLANTING			27		// Set to true if the user is planting the bomb

//	#define PB_CHAM_CONFIGURED		28		// Has chameleon been configured?

	#define PB_FIELDATTEMPT			32		// Has this player made a suicide attempt for undead's ultimate?

	#define PB_LAST					33
	
	// ***************************
	//		End of info for player_data_bool
	// ***************************
// ***************************************************************************
//	End player array information
// ***************************************************************************


// What is the user going to respawn by?
#define RESPAWN_ITEM			1
#define RESPAWN_PHOENIX			2
#define RESPAWN_VENGEANCE		3

// Enemies who have immunity w/in this radius will cause blink to fail 
#define IMMUNITY_RADIUS		500

#define SPAWN_DELAY			0.2

// ***************************************************************************
//  Start of variables
// ***************************************************************************



// This keeps track of which races were given "free" XP - we don't want to save this XP to the database
new bool:g_bGivenLevel10[33][MAX_RACES+1];	// Stores if we gave them level 10

new g_GlowLevel[33][4];

// Used for Chameleon
new g_ChamSkills[5];

new p_data[33][P_LAST]					// Contains player data
new bool:p_data_b[33][PB_LAST]			// Contains player data of type boolean



new MAXPLAYERS


new gmsgStatusText
new gmsgBarTime

// Used with SHARED_SetUserSpeed
new bool:g_bPlayerZoomed[33];

new szSpawnEnt[2][32];

/*  START - CSTRIKE VARIABLES */
new bool:g_freezeTime	= false;
new bool:g_buyTime

// Counter-Strike/Condition Zero Skins
new SKIN_CT[5][]		= { "sas"		, "gsg9"	, "urban"		, "gign"	, "spetsnaz" };
new SKIN_T[5][]			= { "arctic"	, "leet"	, "guerilla"	, "terror"	, "militia" };
	

new CsArmorType:g_ArmorType[33];

/*  END - CSTRIKE VARIABLES */



// Used to keep track of how much dmg one player does to another
new g_iDamageDealt[33][33];

// Used with helm
new Float:fLastShotFired[33];

// Used to determine if the ultimatedelay is valid
new g_iUltimateDelay;

// Captured Messages
new gmsgDeathMsg
new gmsgScreenFade
new gmsgScreenShake
new gmsgScoreInfo
new gmsgStatusIcon

new bool:g_GameRestarting = false;

new bool:bIgnoreArmorSet[33];

#define	GAME_NAME	">>"

#define FRAME 30
new currentFrame[33];


new bool:warcraft3 = true
new bool:g_EndRound

// Used to make sure a spawn point isn't used for another player
#define TOTAL_SPAWNS	64
new g_iSpawnReserved[TOTAL_SPAWNS];
new g_iSpawnInc = 0;

// Used with changerace menu and game menu M
new g_menuPosition[33] = 0; 
new bChooseTeamOverrideActive[33];

new g_PlayerWeapons[33][32];			// Stores player weapons after they have been purchased
new g_PlayerLastWeapons[33][32];		// Stores player weapons after they have been purchased

new g_MOD = 0;

// thanks twistedeuphoria - from objective proximity warning
#define MAX_OBJECTIVES			11
#define OBJENT_VIP_ESCAPE		0
#define OBJENT_HOSTAGE			1
#define OBJENT_BOMBSITE			2
#define OBJENT_HOSTAGE_ESCAPE	3

new g_iObjectiveEnt[MAX_OBJECTIVES];
new g_iObjectiveEntType[MAX_OBJECTIVES];
new Float:g_fObjectiveOrigin[MAX_OBJECTIVES][3]
new g_iTotalObjectiveEnts = 0;

new bool:g_bLevitation[33];


new bool:g_bOrcNadesDisabled = false;
new bool:g_bGlovesDisabled = false;

new Menu;

// ***************************
// Skill Information
// ***************************

#define SKILL_1						1
#define SKILL_2						2
#define SKILL_3						3
#define SKILL_ULTIMATE				4
#define SKILL_PASSIVE				5

#define MAX_PLAYER_SKILLS			6
#define MIN_ULT_LEVEL               6

// SKILL DEFINES
#define SKILL_NONE				-1

#define SKILL_VAMPIRICAURA		0
#define SKILL_UNHOLYAURA		1
#define SKILL_LEVITATION		2
#define ULTIMATE_SUICIDE		3

#define SKILL_INVISIBILITY		4
#define SKILL_DEVOTION			5
#define SKILL_BASH				6
#define ULTIMATE_BLINK			7

#define SKILL_CRITICALSTRIKE	8
#define SKILL_CRITICALGRENADE	9
#define SKILL_REINCARNATION		10
#define ULTIMATE_CHAINLIGHTNING	11

#define SKILL_EVASION			12
#define SKILL_THORNS			13
#define SKILL_TRUESHOT			14
#define ULTIMATE_ENTANGLE		15

#define SKILL_PHOENIX			16
#define SKILL_BANISH			17
#define SKILL_SIPHONMANA		18
#define ULTIMATE_IMMOLATE		19
#define PASS_RESISTANTSKIN		20

#define SKILL_HEALINGWAVE		21
#define SKILL_HEX				22
#define SKILL_SERPENTWARD		23
#define ULTIMATE_BIGBADVOODOO	24
#define PASS_UNSTABLECONCOCTION	25

#define SKILL_FANOFKNIVES		26
#define SKILL_BLINK				27
#define SKILL_SHADOWSTRIKE		28
#define ULTIMATE_VENGEANCE		29
#define PASS_HARDENEDSKIN		30

#define SKILL_IMPALE			31
#define SKILL_SPIKEDCARAPACE	32
#define SKILL_CARRIONBEETLES	33
#define ULTIMATE_LOCUSTSWARM	34
#define PASS_ORB				35

#define	SKILL_NOVA				36
#define	SKILL_BITE				37
#define	SKILL_ARCANE			38
#define	ULTIMATE_FIELD			39


#define	SKILL_ROAR				40
#define	SKILL_CYCLONE			41
#define	SKILL_HIDES				42
#define	ULTIMATE_CROW			43


#define MAX_SKILLS				44


#define MAX_RACE_SKILLS         3
#define MAX_SKILL_LEVEL			3
#define MAX_ULTIMATE_LEVEL		1

// Used with g_SkillType
#define SKILL_TYPE_TRAINABLE	1
#define SKILL_TYPE_PASSIVE		2
#define SKILL_TYPE_ULTIMATE		3

// Used with g_SkillOrder
#define SKILL_POS_NONE			-1
#define SKILL_POS_1				0
#define SKILL_POS_2				1
#define SKILL_POS_3				2
#define SKILL_POS_4				3

new g_SkillOwner[MAX_SKILLS	];	// For each skill, says who the owning race is
new g_SkillType[MAX_SKILLS	];	// For each skill, says what type of skill it is (trainable/ultimate/passive)
new g_SkillOrder[MAX_SKILLS	];	// For each skill, lists what order it should appear in /level and /selectskill (and how it should save)

// Used to store what level each skill is for the players
new g_PlayerSkillLevel[33][MAX_SKILLS];			// Stores what level each skill is
new bool:g_bPlayerSkills[33][MAX_SKILLS];		// Stores what skills the player has available (set on race selection)

// Constants for Abilities
new const Float:p_vampiric[3] =			{0.1,0.15,0.20}			// Vampiric Aura			(skill 1)
new Float:p_unholy[3] =					{265.0,285.0,300.0}		// Unholy Aura				(skill 2)
new const Float:p_levitation[3] =		{0.7,0.5,0.3}			// Levitation				(skill 3)

new const p_invisibility[3] =			{200,175,135}			// Invisibility				(skill 1)
new const p_devotion =					15						// Devotion Aura			(skill 2)
new const Float:p_bash[3] =				{0.05,0.1,0.15}			// Bash						(skill 3)

new const Float:p_critical[3] =			{0.25,0.50,0.75}		// Critical Strike			(skill 1)
new const Float:p_grenade[3] =			{2.0,3.0,4.0}			// Critical Grenade			(skill 2)
new const Float:p_ankh[3] =				{0.333,0.666,1.0}		// Equipment reincarnation	(skill 3)

new const Float:p_evasion[3] =			{0.1,0.15,0.20}			// Evasion					(skill 1)
new const Float:p_thorns[3] =			{0.05,0.1,0.15}			// Thorns Aura				(skill 2)
new const Float:p_trueshot[3] =			{0.1,0.2,0.3}			// Trueshot Aura			(skill 3)


new const Float:p_phoenix[3] =			{0.333,0.666,1.0}		// Phoenix					(skill 1)
new const Float:p_banish[3] =			{0.05,0.10,0.15}		// Banish					(skill 2)
new const Float:p_mana[3] =				{0.02,0.04,0.08}		// Siphon Mana				(skill 3)
new const Float:p_resistant[11] =		{0.02, 0.04, 0.06, 0.8, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22}	// Resistant Skin		(Skill 4)

new const Float:p_heal[3] =				{3.0,2.0,1.0}			// Healing Wave				(skill 1)
new const Float:p_hex[3] =				{0.05,0.10,0.15}		// Hex						(skill 2)
new const p_serpent[3] =				{1,3,5}					// Serpent Ward				(skill 3) // Old Values {3,6,9}
new const Float:p_concoction[11] =		{0.02, 0.04, 0.06, 0.8, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22}	// Unstable Concoction	(Skill 4)

new const Float:p_fan[3] =				{0.05,0.10,0.15}		// Fan of Knives			(skill 1)
new const Float:p_blink[3] =			{0.333,0.666,1.0}		// Blink					(skill 2)
new const Float:p_shadow[3] =			{0.05,0.10,0.15}		// Shadow Strike			(skill 3)
new const Float:p_harden[11] =			{0.02, 0.04, 0.06, 0.8, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22}	// Hardened Skin		(Skill 4)

new const Float:p_impale[3] =			{0.05,0.1,0.15}		    // Impale					(skill 1)
new const Float:p_spiked[3] =			{0.05,0.1,0.15}			// Spiked Carapace			(skill 2)
new const Float:p_carrion[3] =			{0.05,0.10,0.15}		// Carrion Beetle			(skill 3)
new const Float:p_orb[11] =				{0.02, 0.04, 0.06, 0.8, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22}	// Orb of Annihilation	(Skill 4)

new const Float:p_nova[3] =				{0.05,0.10,0.15}		// Crystal Nova				(skill 1)
new const p_frostbite[3] =				{30,20,10}				// Frostbite				(skill 2)
new const p_arcane[3] =					{50,100,150}			// Arcane Aura				(skill 3)


new const Float:p_roar[3] =				{0.10,0.20,0.30}		 // Roar						(skill 1)
new const p_cyclone[3] =				{25,50,75}				 // Cyclone						(skill 2)
new const Float:p_hides[3] =			{0.333,0.666,1.0}		 // Hides						(skill 3)

// SOUNDS

#define MAX_SOUNDS	37

new g_szSounds[MAX_SOUNDS][64];



#define SOUND_VENGEANCE			0
#define SOUND_SUICIDE			1
#define SOUND_BANISH			2
#define SOUND_LOCUSTSWARM		3
#define SOUND_SHADOWSTRIKE		4
#define SOUND_CARRION			5
#define SOUND_IMPALE			6
#define SOUND_VOODOO			7
#define SOUND_FLAMESTRIKE		8
#define SOUND_ENTANGLING		9
#define SOUND_LIGHTNING			10
#define SOUND_TELEPORT			11
#define SOUND_BLINK				12
#define SOUND_ANNIHILATION		13
#define SOUND_CONCOCTION_CAST	14
#define SOUND_CONCOCTION_HIT	15
#define SOUND_HEX				16
#define SOUND_IMMOLATE			17
#define SOUND_IMMOLATE_BURNING	18
#define SOUND_LEVELUP			19
#define SOUND_PICKUPITEM		20
#define SOUND_TOME				21
#define SOUND_ULTIMATESCAN		22
#define SOUND_ULTIMATEREADY		23
#define SOUND_REINCARNATION		24
#define SOUND_ANTEND			25
#define SOUND_ERROR				26
#define SOUND_DISPELL			27
#define SOUND_SPELLSHIELD		28
#define SOUND_HEORC				29
#define SOUND_NOVA				30
#define	SOUND_FIELD				31
#define	SOUND_BITE				32
#define	SOUND_ICE				33
#define	SOUND_BUY				34
#define	SOUND_ROAR				35
#define	SOUND_BEAP				36


// SPRITES
#define MAX_SPRITES	19

new g_szSprites[MAX_SPRITES][64];
new g_szRaceSprites[MAX_RACES + 1][64];
new g_szLevelSprites[MAX_LEVELS + 1][64];

new g_iRaceSprites[MAX_RACES + 1];
new g_iLevelSprites[MAX_LEVELS + 1];
new g_iSprites[MAX_SPRITES] = {0};

new bool:g_bExtraSpritesEnabled = false

#define SPR_BANISH			0
#define SPR_SHADOWSTRIKE	1
#define SPR_SNOW			2
#define SPR_FIRE			3
#define SPR_BURNING			4
#define SPR_BEETLE			5
#define SPR_FIREBALL		6
#define SPR_BEAM			7
#define SPR_TRAIL			8
#define SPR_SHOCKWAVE		9
#define SPR_LIGHTNING		10
#define SPR_FLARE			11
#define SPR_WAVE			12
#define SPR_SMOKE			13
#define SPR_IMMOLATE		14
#define SPR_NOVA			15
#define	SPR_FIELD			16
#define	SPR_FROSTEXP		17
#define	SPR_NEW_TRAIL		18

// HUD Channels
#define HUD_SPEC_INFO			1	// Info displayed in bottom corner of player being spectated
#define HUD_SHOWSTATUS			4	// Information shown on enemies/teammates when looking at them

#define HUD_RACE_INFO			2	// /level command
#define HUD_ULTIMATE			1	// Ultimate messages (i.e. you have _ seconds remaining)
#define HUD_SKILL				3	// i.e. "you have evaded a shot"
#define HUD_XP					3	// Used to show the user their xp/items when dead
#define HUD_AUTO				-1	// Automatically choose one!
#define HUD_TIMER				1	// Timer

#define FADE_OUT                0x0000          // Fade out from max alpha
#define FADE_IN                 0x0001          // Fade in to max alpha
#define FADE_MODULATE_OUT       0x0002          // Modulate, fade out from max alpha
#define FADE_MODULATE_IN        0x0003      // Modulate, fade in to max alpha
#define FADE_ONLYONE_OUT        0x0004      // Start at max Alpha, no fade out
#define FADE_ONLYONE_IN         0x0005      // Fade in to max Alpha, no fade out
#define FADE_MODONE_OUT         0x0006      // Modulate, Start at max Alpha, no fade
#define FADE_MODONE_IN          0x0007      // Modulate, Fade in to max Alpha, no fade out

#define HUDMESSAGE_FX_FADEIN    0           // hudmessage effect types
#define HUDMESSAGE_FX_FLICKER   1
#define HUDMESSAGE_FX_WRITEOUT  2

// Used for spectating info
#define SPEC_HOLDTIME		10.0
new g_iSpectatingID[33];
new Float:g_fLastSpecDisplay[33];

// Lets keep track of what team the player is on!
new g_iPlayerTeam[33];

#define BOT_CAST_ULT_CHANCE		0.10

new bool:g_bCZBotRegisterHam

#define VIP_LEVEL		ADMIN_LEVEL_H

// MOTD DESIGN

#define SELECT_DESIGN		10

#define DESIGN1_STYLE "<meta charset=UTF-8><style>body{background:#112233;font-family:Arial}th{background:#558866;color:#FFF;padding:10px 2px;text-align:left}td{padding:4px 3px}table{background:#EEEECC;font-size:12px;font-family:Arial}h2,h3{color:#FFF;font-family:Verdana}#c{background:#E2E2BC}img{height:10px;background:#09F;margin:0 3px}#r{height:10px;background:#B6423C}#clr{background:none;color:#FFF;font-size:20px}</style>"
#define DESIGN2_STYLE "<meta charset=UTF-8><style>body{font-family:Arial}th{background:#575757;color:#FFF;padding:5px;border-bottom:2px #BCE27F solid;text-align:left}td{padding:3px;border-bottom:1px #E7F0D0 solid}table{color:#3C9B4A;background:#FFF;font-size:12px}h2,h3{color:#333;font-family:Verdana}#c{background:#F0F7E2}img{height:10px;background:#62B054;margin:0 3px}#r{height:10px;background:#717171}#clr{background:none;color:#575757;font-size:20px}</style>"
#define DESIGN3_STYLE "<meta charset=UTF-8><style>body{background:#E6E6E6;font-family:Verdana}th{background:#F5F5F5;color:#A70000;padding:6px;text-align:left}td{padding:2px 6px}table{color:#333;background:#E6E6E6;font-size:10px;font-family:Georgia;border:2px solid #D9D9D9}h2,h3{color:#333;}#c{background:#FFF}img{height:10px;background:#14CC00;margin:0 3px}#r{height:10px;background:#CC8A00}#clr{background:none;color:#A70000;font-size:20px;border:0}</style>"
#define DESIGN4_STYLE "<meta charset=UTF-8><style>body{background:#E8EEF7;margin:2px;font-family:Tahoma}th{color:#0000CC;padding:3px}tr{text-align:left;background:#E8EEF7}td{padding:3px}table{background:#CCC;font-size:11px}h2,h3{font-family:Verdana}img{height:10px;background:#09F;margin:0 3px}#r{height:10px;background:#B6423C}#clr{background:none;color:#000;font-size:20px}</style>"
#define DESIGN5_STYLE "<meta charset=UTF-8><style>body{background:#555;font-family:Arial}th{border-left:1px solid #ADADAD;border-top:1px solid #ADADAD}table{background:#3C3C3C;font-size:11px;color:#FFF;border-right:1px solid #ADADAD;border-bottom:1px solid #ADADAD;padding:3px}h2,h3{color:#FFF}#c{background:#FF9B00;color:#000}img{height:10px;background:#00E930;margin:0 3px}#r{height:10px;background:#B6423C}#clr{background:none;color:#FFF;font-size:20px;border:0}</style>"
#define DESIGN6_STYLE "<meta charset=UTF-8><style>body{background:#FFF;font-family:Tahoma}th{background:#303B4A;color:#FFF}table{padding:6px 2px;background:#EFF1F3;font-size:12px;color:#222;border:1px solid #CCC}h2,h3{color:#222}#c{background:#E9EBEE}img{height:7px;background:#F8931F;margin:0 3px}#r{height:7px;background:#D2232A}#clr{background:none;color:#303B4A;font-size:20px;border:0}</style>"
#define DESIGN7_STYLE "<meta charset=UTF-8><style>body{background:#FFF;font-family:Verdana}th{background:#2E2E2E;color:#FFF;text-align:left}table{padding:6px 2px;background:#FFF;font-size:11px;color:#333;border:1px solid #CCC}h2,h3{color:#333}#c{background:#F0F0F0}img{height:7px;background:#444;margin:0 3px}#r{height:7px;background:#999}#clr{background:none;color:#2E2E2E;font-size:20px;border:0}</style>"
#define DESIGN8_STYLE "<meta charset=UTF-8><style>body{background:#242424;margin:20px;font-family:Tahoma}th{background:#2F3034;color:#BDB670;text-align:left} table{padding:4px;background:#4A4945;font-size:10px;color:#FFF}h2,h3{color:#D2D1CF}#c{background:#3B3C37}img{height:12px;background:#99CC00;margin:0 3px}#r{height:12px;background:#999900}#clr{background:none;color:#FFF;font-size:20px}</style>"
#define DESIGN9_STYLE "<meta charset=UTF-8><style>body{background:#FFF;font-family:Tahoma}th{background:#056B9E;color:#FFF;padding:3px;text-align:left;border-top:4px solid #3986AC}td{padding:2px 6px}table{color:#006699;background:#FFF;font-size:12px;border:2px solid #006699}h2,h3{color:#F69F1C;}#c{background:#EFEFEF}img{height:5px;background:#1578D3;margin:0 3px}#r{height:5px;background:#F49F1E}#clr{background:none;color:#056B9E;font-size:20px;border:0}</style>"
#define DESIGN10_STYLE "<meta charset=UTF-8><style>body{background:#4C5844;font-family:Tahoma}th{background:#1E1E1E;color:#C0C0C0;padding:2px;text-align:left;}td{padding:2px 10px}table{color:#AAC0AA;background:#424242;font-size:13px}h2,h3{color:#C2C2C2;font-family:Tahoma}#c{background:#323232}img{height:3px;background:#B4DA45;margin:0 3px}#r{height:3px;background:#6F9FC8}#clr{background:none;color:#FFF;font-size:20px}</style>"
#define DESIGN11_STYLE "<meta charset=UTF-8><style>body{background:#F2F2F2;font-family:Arial}th{background:#175D8B;color:#FFF;padding:7px;text-align:left}td{padding:3px;border-bottom:1px #BFBDBD solid}table{color:#153B7C;background:#F4F4F4;font-size:11px;border:1px solid #BFBDBD}h2,h3{color:#153B7C}#c{background:#ECECEC}img{height:8px;background:#54D143;margin:0 3px}#r{height:8px;background:#C80B0F}#clr{background:none;color:#175D8B;font-size:20px;border:0}</style>"
#define DESIGN12_STYLE "<meta charset=UTF-8><style>body{background:#283136;font-family:Arial}th{background:#323B40;color:#6ED5FF;padding:10px 2px;text-align:left}td{padding:4px 3px;border-bottom:1px solid #DCDCDC}table{background:#EDF1F2;font-size:10px;border:2px solid #505A62}h2,h3{color:#FFF}img{height:10px;background:#A7CC00;margin:0 3px}#r{height:10px;background:#CC3D00}#clr{background:none;color:#6ED5FF;font-size:20px;border:0}</style>"
#define DESIGN13_STYLE "<meta charset=UTF-8><style>body{background:#220000;font-family:Tahoma}th{background:#3E0909;color:#FFF;padding:5px 2px;text-align:left;border-bottom:1px solid #DEDEDE}td{padding:2px 2px;}table{background:#FFF;font-size:11px;border:1px solid #791616}h2,h3{color:#FFF}#c{background:#F4F4F4;color:#7B0000}img{height:7px;background:#a00000;margin:0 3px}#r{height:7px;background:#181818}#clr{background:none;color:#CFCFCF;font-size:20px;border:0}</style>"
#define DEFAULT_STYLE "<meta charset=UTF-8><style>body{background:#000}tr{text-align:left}table{font-size:13px;color:#FFB000;padding:2px}h2,h3{color:#FFF;font-family:Verdana}img{height:5px;background:#0000FF;margin:0 3px}#r{height:5px;background:#FF0000}</style>"

// Druid Crow Check 

new CrowLastPosition[33][3];
new CrowStartPosition[33][3];


// Ice and Orc nade 


// Settings for frost nade 
#define	FROST_RADIUS		250.0
#define FROST_DURATION 		5.0

#define FROST_CODE 3245879	// So we can know the type of nade 

#define	FROST_BLOCK_MODEL	"models/warcraft3/iceblock.mdl"

new IceBlockEnt[33];

new GLASS_SPR;

new g_iBiteTimer[33];								// Keeps track of how much time is left to give a user a smoke grenade

// Models for nades 

// HE ORC NADE
#define	V_MODEL_HE	"models/warcraft3/v_holybomb_red.mdl"
#define	W_MODEL_HE	"models/warcraft3/w_holybomb_red.mdl"
//#define	P_MODEL_HE	"models/warcraft3/p_holybomb_red.mdl"

// SM FROST NADE 
#define	V_MODEL_SM	"models/warcraft3/v_holybomb_blue.mdl"
#define	W_MODEL_SM	"models/warcraft3/w_holybomb_blue.mdl"
//#define	P_MODEL_SM	"models/warcraft3/p_holybomb_blue.mdl"


// 	fm_give_item(id, "weapon_smokegrenade")



// Lasermine 


#define MAXMINES		3
#define MINE_DAMAGE		50
#define MINE_HEALTH		1000
#define MINE_INT_TEAM		EV_INT_iuser1
#define MINE_OWNER		EV_INT_iuser3
#define DMG_BULLET		(1<<1)

new Float:Delay[33]
new boom, beam


// Polymorph
new PolymorphFile[128];
new bool:Polymorph_Player[33];

new Polymorph_Skill_1[33]; 
new Polymorph_Skill_2[33]; 
new Polymorph_Skill_3[33]; 
new Polymorph_Ultimate[33]; 
new Polymorph_Passive[33]; 
			

// Game Message Freq

#define	INFO_FREQ					180.0


// Radar Constants 

	#define RADAR_DELAY	1.0
	
	
	new g_iMaxPlayers;
	new Float:g_fCurrentTime;
	new Float:g_fNextRadarTime[ 33 ];
	
	new g_iMsgIdHostageK;
	new g_iMsgIdHostagePos;
	

// Auto Buy 

new g_bAutoBuy[33];
new g_iAutobuySlot1[33];
new g_iAutobuySlot2[33];

// Gold Settings 

new PlayerGold[33];
new GoldFile[128];	

// Level Bank 

#define LEVEL_BANK	30
new LevelBankBonus[33]; 
new LevelBankFile[128];


new bool:g_bExchange[33];

#define	CONVERTOR_THINK_FREQ		0.2

#define	MAX_MONEY					10000			//	$
#define	MAX_XP						103000			// 	XP

#define	MAX_GOLD_PLAYER				1000			//	Gold
#define	MAX_GOLD_VIP				99999			// 	Gold
#define	VIP_BONUS					2	

#define	VALUE_GOLD					100				// 	$
#define VALUE_GOLD_XP				10				//	XP



// Wall Icon 
#define WALL_ICON_SIZE		2
#define WALL_ICON_LIGHT		100
#define WALL_ICON_DELAY		0.5  		// 0.03 

new Float:g_icon_delay[33];
new g_supplybox_icon_id;
new const supplybox_icon_spr[] = "sprites/warcraft3/icon_supplybox.spr"

// FPS 

new bool:IsUserConnected[33];
new Float:GameTime[ 33 ]; 
new FramesPer[33];
new CurFps[33];
new Fps[33];



// Use items id as order in items.h 


#define ITEM_NAME_LONG			0
#define	ITEM_NAME_SHORT			1
#define	ITEM_DESCRIPTION		2


new Lang_ItemDatabase[][][] =
{
	{"Ankh of Reincarnation",		"Ankh",						"Equipment Recovery"						},	//	0
	{"Boots of Speed",				"Boots", 					"Increase Speed"							},	//	1
	{"Claws of Attack",				"Claws",					"Increase Damage"							},	//	2
	{"Cloak of Shadows",			"Cloak",					"Invisibility with Knife"					},	//	3
	{"Mask of Death",				"Mask", 					"Healing on Attack"							},	//	4
	{"Wand of Neutralization",		"Wand",						"Block Ultimate"							},	//	5
	{"Orb of Frost",				"Frost",					"Slow Enemy"								},	//	6
	{"Health Stone",				"Health", 					"Increase Health Capacity"					},	//	7
	{"Tome of Experience",			"Tome",						"Instant Experience Bonus"					},	//	8
	{"Scroll of Resurrection",		"Scroll",					"Instant Respawn"							},	//	9
	{"Gem of True Sight",			"Gem", 						"Detect Invisibility and Chameleons"		},	//	10
	{"Helm of Excellence",			"Helm",						"Block HeadShots"							},	//	11
	{"Amulet of the Wild",			"Amulet",					"Silent Steps"								},	//	12
	{"Sock of the Feather",			"Sock", 					"Decrease Gravity"							},	//	13
	{"Gloves of Haste",				"Gloves",					"Grenade Recovery"							},	//	14
	{"Ring of Regeneration",		"Ring",						"Health Regeneration"						},	//	15
	{"Chameleon",					"Chameleon", 				"Enemy Skin"								},	//	16
	{"Mole",						"Mole",						"Teleport to Enemy Spawn at Start"			},	//	17
	{"Goblin Land Mine",			"Mine",						"Explosive Mine on Wall"					}	//	18
							
	
}

// Use skills and ultimate id as order 

#define	SKILL_NAME			0
#define	SKILL_DESCRIPTION	1

new Lang_SkillUltimateDatabase[][][] =
{
	{"Vampiric Aura",				"Healing on Attack"										},	//	0
	{"Unholy Aura",					"Increase Speed"										},	//	1
	{"Levitation",					"Decrease Gravity"										},	//	2
	{"Death and Decay",				"Explosion Area on Death" 								},	//	3
	{"Invisibility",				"Invisibility with Knife"								},	//	4
	{"Devotion Aura",				"Increase Health Capacity"								},	//	5
	{"Bash",						"Stun Enemy"											},	//	6
	{"Teleport",					"Teleport on Target"									},	//	7
	{"Critical Strike",				"Chance to Increase Damage"								},	//	8
	{"Critical Grenade",			"Increase Grenade Damage"								},	//	9
	{"Equipment Reincarnation",		"Equipment Recovery"									},	//	10
	{"Chain Lightning",				"Lightning Bolt with Damage"							},	//	11
	{"Evasion",						"Chance to Evade Shoots"								},	//	12
	{"Thorns Aura",					"Mirror Damage to Attacker"								},	//	13
	{"Trueshot Aura",				"Increase Damage"										},	//	14
	{"Entangle Roots",				"Stun and Weapon Drop"									},	//	15
	{"Phoenix",						"Chance to Instant Respawn"								},	//	16
	{"Banish",						"Chance to Black Hole the Attacker"						},	//	17	
	{"Siphon Mana",					"Steal Money on Attack"									},	//	18
	{"Immolate",					"Burn Over Time"										},	//	19
	{"Resistant Skin",				"Reduce Damage"											},	//	20
	{"Healing Wave",				"Regenerate Team Health" 								},	//	21
	{"Hex",							"Chance to Block Ability and Slow"						},	//	22
	{"Serpent Ward",				"Plant Serpent Wards /ability"							},	//	23
	{"Big Bad Voodoo",				"Invincibility Over Time"								},	//	24
	{"Unstable Concoction",			"Chance to Damage Around"								},	//	25
	{"Fan of Knives",				"Chance to Become Mole"									},	//	26
	{"Blink",						"Chance to Block Ultimate"								},	//	27
	{"Shadow Strike",				"Chance to Extra Damage"								},	//	28
	{"Vengeance",					"Respawn or Teleport at Spawn"							},	//	29
	{"Hardened Skin",				"Chance to Reduce Damage"								},	//	30
	{"Impale",						"Chance to Throw Enemy"									},	//	31
	{"Spiked Carapace",				"Mirror Damage and Armor Bonus"							},	//	32
	{"Carrion Beetles",				"Chance to Extra Damage"								},	//	33
	{"Locust Swarm",				"Swarm of Locusts Attack the Enemy"						},	//	34
	{"Orb of Annihilation",			"Chance to Extra Damage"								},	//	35
	{"Crystal Nova",				"Chance to Extra Damage"								},	//	36
	{"Frostbite",					"Frozen Grenade Recovery"								},	//	37
	{"Arcane Aura",					"Regenerate Team Money"									},	//	38
	{"Freezing Field",				"Area Damage"											},	//	39
	{"Roar",						"Chance to Blind Attacker"								},	//	40
	{"Cyclone",						"See Low Enemy on Wall"									},	//	41
	{"Reinforced Hides",			"Chance to Block Grenade"								},	//	42
	{"Crow Form",					"Walk through Wall"										}	//	43
							
}

#define MAX_HELP	13

new Lang_TutorialDatabase[][][] =
{
	{"Race",						"Each race has separate level and different powers"							},	//	0
	{"Level",						"Each level upgrades the race powers"										},	//	1
	{"XP",							"Earn xp to increase level with wins, kills, objectives"					},	//	2
	{"Skill Powers",				"Auto activation or manual: bind v ability" 								},	//	3
	{"Ultimate Powers",				"Manual activation: bind f ultimate"										},	//	4
	{"Passive Powers",				"Auto activation & Always active"											},	//	5
	{"Items",						"Improve race powers or give other powers"									},	//	6
	{"Exchange Gold",				"Auto convert gold to money /exchange"										},	//	7
	{"Treasure Box",				"Items, Gold, HP, AP, XP, $"												},	//	8
	{" ",							" "																			},	//	9
	{" ",							" "																			},	//	10
	{" ",							" "																			},	//	11
	{"Questions ?",					"Discord: Ivaylo#1914"														}	//	12

							
}



