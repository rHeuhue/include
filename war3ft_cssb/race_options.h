
//Количество рас
#define MAX_RACES				25


//Номерация рас
#define RACE_NONE				0
#define RACE_UNDEAD				1
#define RACE_HUMAN				2
#define RACE_ORC				3
#define RACE_ELF				4
#define RACE_BLOOD				5
#define RACE_SHADOW				6
#define RACE_WARDEN				7
#define RACE_CRYPT				8
#define RACE_CHAMELEON			9
#define RACE_FROST_MAGE			10
#define RACE_DEATH_KNIGHT		11
#define RACE_BLACK_MAGICIAN		12
#define RACE_ALCHEMIST			13
#define RACE_PRIEST				14
#define RACE_ROGUE				15
#define RACE_DRUID				16
#define RACE_BLOODSEEKER		17
#define RACE_JUGGERNAUT			18
#define RACE_SNIPER				19
#define RACE_DISRUPTOR			20
#define RACE_RAZOR				21
#define RACE_WARLOCK			22
#define RACE_SHADOW_FIEND		23
#define RACE_24					24
#define RACE_25					25

//******************************************************
// Информация о скилах
//******************************************************

#define SKILL_1						1
#define SKILL_2						2
#define SKILL_3						3
#define SKILL_ULTIMATE				4
#define SKILL_PASSIVE				5

#define MAX_PLAYER_SKILLS			6

// SKILL DEFINES
#define SKILL_NONE								-1

#define SKILL_VAMPIRICAURA						0
#define SKILL_UNHOLYAURA						1
#define SKILL_LEVITATION						2
#define ULTIMATE_SUICIDE						3

#define SKILL_INVISIBILITY						4
#define SKILL_DEVOTION							5
#define SKILL_BASH								6
#define ULTIMATE_BLINK							7

#define SKILL_CRITICALSTRIKE					8
#define SKILL_CRITICALGRENADE					9
#define SKILL_REINCARNATION						10
#define ULTIMATE_CHAINLIGHTNING					11

#define SKILL_EVASION							12
#define SKILL_THORNS							13
#define SKILL_TRUESHOT							14
#define ULTIMATE_ENTANGLE						15

#define SKILL_PHOENIX							16
#define SKILL_BANISH							17
#define SKILL_SIPHONMANA						18
#define ULTIMATE_IMMOLATE						19
#define PASS_RESISTANTSKIN						20

#define SKILL_HEALINGWAVE						21
#define SKILL_HEX								22
#define SKILL_SERPENTWARD						23
#define ULTIMATE_BIGBADVOODOO					24
#define PASS_UNSTABLECONCOCTION					25

#define SKILL_FANOFKNIVES						26
#define SKILL_BLINK								27
#define SKILL_SHADOWSTRIKE						28
#define ULTIMATE_VENGEANCE						29
#define PASS_HARDENEDSKIN						30

#define SKILL_IMPALE							31
#define SKILL_SPIKEDCARAPACE					32
#define SKILL_CARRIONBEETLES					33
#define ULTIMATE_LOCUSTSWARM					34
#define PASS_ORB								35

//Раса Ледяной Маг
#define SKILL_FROST_MAGE_ICE_SPLINTERS			36	//Ice splinters - Осколки льда
#define SKILL_FROST_MAGE_ICE_ARROW				37	//Ice Arrow - Ледяная стрела
#define SKILL_FROST_MAGE_CONE_OF_COLD			38	//Cone of Cold - Конус холода
#define ULTIMATE_FROST_MAGE_BLIZZARD			39	//Blizzard - Снежная буря

#define ULTIMATE_CHAM_FLAME_STRIKE				40	//Flame Strike - Супер навык для Хамелеона "паровоз"

//Раса Рыцарь смерти
#define SKILL_DEATH_KNIGHT_UNARMOR				41	//Unbreakable Armor - Несокрушимая броня 
#define SKILL_DEATH_KNIGHT_BLOOD_BOIL			42	//Blood Boil - Вскипание крови
#define SKILL_DEATH_KNIGHT_DEATH_COIL			43	//Death Coil - Лик смерти
#define ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE	44	//Власть крови - Blood Presence
#define PASS_DEATH_KNIGHT_CONTROL_UNDEAD		45  //Control Undead - Порабощение нежити
//Раса Черный Маг
#define SKILL_BLACKSTRIKE						46
#define SKILL_BLACKSHADOW						47
#define SKILL_BLACKPOWER						48
#define ULTIMATE_BLACKLIGHTNING					49
//Алхимик
#define SKILL_POISON							50
#define SKILL_SHOCK								51
#define SKILL_FROST								52
#define ULTIMATE_RADIATION						53
#define PASS_HYPNOSIS							54
//Раса Жрец
#define SKILL_PRIEST_ENTRYINTOCHASM				55
#define SKILL_PRIEST_SACRED_FIRE				56
#define SKILL_PRIEST_SPIRITUAL_ACCURACY			57
#define ULTIMATE_PRIEST_DARKNESS_WORD_DEATH		58
#define PASS_PRIEST_MYSTICISM					59
//Раса Разбойник
#define SKILL_ROGUE_1							60
#define SKILL_ROGUE_2							61
#define SKILL_ROGUE_3							62
#define ULTIMATE_ROGUE							63
//Раса Друид
#define SKILL_DRUID_1							64
#define SKILL_DRUID_2							65
#define SKILL_DRUID_3							66
#define ULTIMATE_DRUID							67
#define PASS_MANGLE_DRUID						68
//Бладсикер
#define SKILL_BLOODSEEKER_1						69
#define SKILL_BLOODSEEKER_2						70
#define SKILL_BLOODSEEKER_3						71
#define ULTIMATE_BLOODSEEKER					72
#define PASS_BLOODSEEKER						73
//Раса Джагернаут
#define SKILL_JUGGERNAUT_1						74
#define SKILL_JUGGERNAUT_2						75
#define SKILL_JUGGERNAUT_3						76
#define ULTIMATE_JUGGERNAUT						77
#define PASS_JUGGERNAUT							78
//Раса Снайпер
#define SKILL_SNIPER_1							79
#define SKILL_SNIPER_2							80
#define SKILL_SNIPER_3							81
#define ULTIMATE_SNIPER							82
#define PASS_SNIPER								83
//Раса Разрушитель
#define SKILL_DISRUPTOR_1						84
#define SKILL_DISRUPTOR_2						85
#define SKILL_DISRUPTOR_3						86
#define ULTIMATE_DISRUPTOR						87
#define PASS_DISRUPTOR							88
//Раса Блэйд
#define SKILL_RAZOR_1							89
#define SKILL_RAZOR_2							90
#define SKILL_RAZOR_3							91
#define ULTIMATE_RAZOR							92
#define PASS_RAZOR								93
//Раса Варлок
#define SKILL_WARLOCK_1							94
#define SKILL_WARLOCK_2							95
#define SKILL_WARLOCK_3							96
#define ULTIMATE_WARLOCK						97
#define PASS_WARLOCK							98
//Раса Невермор
#define SKILL_SHADOW_FIEND_1					99
#define SKILL_SHADOW_FIEND_2					100
#define SKILL_SHADOW_FIEND_3					101
#define ULTIMATE_SHADOW_FIEND					102
#define PASS_SHADOW_FIEND						103
//Раса 24
#define SKILL_24_1								104
#define SKILL_24_2								105
#define SKILL_24_3								106
#define ULTIMATE_24								107
#define PASS_24									108
//Раса 25
#define SKILL_25_1								109
#define SKILL_25_2								110
#define SKILL_25_3								111
#define ULTIMATE_25								112
#define PASS_25									113


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
#define CSW_BLIZZARD			63
#define CSW_ICE_SPLINTERS		64
#define CSW_CHAM_FLAME_STRIKE	65
#define CSW_DEATHCOIL			66
#define CSW_IMPALE				67
#define CSW_BLOODBOIL			68
#define CSW_BLACKPOWER			69
#define CSW_POISON				70
#define CSW_RADIATION			71
#define CSW_WORDDEATH			72
#define CSW_BLOOD_RAGE			73
#define CSW_BLOOD_RITE			74
#define CSW_HEADSHOT			75
#define CSW_SHRAPNEL			76
#define CSW_GLIMPSE				77
#define CSW_STATIC_STORM		78
#define CSW_THUNDER_STRIKE		79
#define CSW_PLASMA_FIELD		80
#define CSW_UNSTABLE_CURRENT	81
#define CSW_FATAL_BONDS			82
#define CSW_SHADOW_WORD			83
#define CSW_FLAMING_FISTS		84
#define CSW_PERM_IMMOLATION		85
#define CSW_CRY_HEART			86
#define CSW_REQUIEM_SOULS		87


#define CSW_WAR3_MAX			87

// MAX_CSW_S == (CSW_WAR3_MAX - CSW_WAR3_MIN) + 1
#define MAX_CSW_S				37




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

new arrSkillChargeNum[33][MAX_SKILLS];				// Количество зарядов скила
new arrSkillChargeMax[MAX_SKILLS];					// Максимальное количество зарядов скила
new arrSkillChargeMin[MAX_SKILLS];					// Минимальное количество зарядов скила
new bool:arrIsSkillChargeActive[33][MAX_SKILLS];	// Активация зарядов скила
new arrSkillCount[MAX_SKILLS];						// Через какое время срабатывает шанс получения заряда.
new arrSkillTimer[33][MAX_SKILLS];					// Счетчик который будет отсчитывать время

forward InitDeathCoil( idAttacker,idVictim,iTypeDC);