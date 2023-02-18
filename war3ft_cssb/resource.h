
// SOUNDS - Звуки
#define MAX_SOUNDS	92

new arrStrSounds[MAX_SOUNDS][64];

#define SOUND_VENGEANCE				0
#define SOUND_SUICIDE				1
#define SOUND_BANISH				2
#define SOUND_LOCUSTSWARM			3
#define SOUND_SHADOWSTRIKE			4
#define SOUND_CARRION				5
#define SOUND_IMPALE				6
#define SOUND_VOODOO				7
#define SOUND_FLAMESTRIKE			8
#define SOUND_ENTANGLING			9
#define SOUND_LIGHTNING				10
#define SOUND_TELEPORT				11
#define SOUND_BLINK					12
#define SOUND_ANNIHILATION			13
#define SOUND_CONCOCTION_CAST		14
#define SOUND_CONCOCTION_HIT		15
#define SOUND_HEX					16
#define SOUND_IMMOLATE				17
#define SOUND_IMMOLATE_BURNING		18
#define SOUND_LEVELUP				19
#define SOUND_PICKUPITEM			20
#define SOUND_TOME					21
#define SOUND_ULTIMATESCAN			22
#define SOUND_ULTIMATEREADY			23
#define SOUND_REINCARNATION			24
#define SOUND_ANTEND				25
#define SOUND_ERROR					26
#define SOUND_DISPELL				27
#define SOUND_SPELLSHIELD			28
#define SOUND_DEATH_TOUCH			29
#define SOUND_HEALTH_POTION			30
#define SOUND_STEEL_SKIN			31
#define SOUND_BLIZZARD				32
#define SOUND_ICE_SPLINTERS			33
#define SOUND_ICE_ARROW_MISSILE		34
#define SOUND_ICE_EXPLODE			35
#define SOUND_COLD_CONE_S			36
#define SOUND_COLD_CONE_E			37
#define SOUND_ICE_BLOCK_EXPLODE		38		//Взрыв Ледяной глыбы
#define SOUND_ICE_BLOCK_FROZEN		39		//Заморозка Ледяной глыбы
#define SOUND_ICE_BLOCK_UNFROZEN	40		//Разморозка Ледяной глыбы
#define SOUND_ICE_BLOCK_CHILLED		41		//Заморожен Ледяной глыбой
#define SOUND_MIRROR_ULTIMATE_BLOCK	42		//Блокировка отражателя супер навыка
#define SOUND_DEATHCOIL				43		//Лик смерти
#define SOUND_DEATHCOIL_MISSILE		44		//Срабатывание Лик смерти
#define SOUND_SLEEP					45		//Сонная аура
#define SOUND_BOOK_DEAD_RAISE		46		//Вызов мертвецов хозяином
#define SOUND_BOOK_DEAD_WARLOCK		47		//Звук для ожившего мертвеца
#define SOUND_TRANQUILITY			48		//Спокойствие
#define SOUND_PRECAST_HOLY			49
#define SOUND_CAST_HOLY				50
#define SOUND_NO_GOLD				51
#define SOUND_DK_UNARMOR			52
#define SOUND_POISON				53
#define SOUND_FROST					54
#define SOUND_RADIATION				55
#define SOUND_FIREBALL_EXP_PRIEST	56
#define SOUND_FIREBALL_PRIEST		57
#define SOUND_MENU_CLICK			58
#define SOUND_SINISTER_STRIKE		59
#define SOUND_VANISH				60
#define SOUND_SHURIKEN_TOSS_EXP		61
#define SOUND_WISP_SPAWN			62
#define SOUND_WISP_DEATH			63
#define SOUND_ASTRAL_STORM			64
#define SOUND_MANGLE				65
#define SOUND_BLOODRAGE				66
#define SOUND_BLOODRITE				67
#define SOUND_HEALING_WARD			68
#define SOUND_HEADSHOT				69
#define SOUND_SHRAPNEL_FIRE			70
#define SOUND_SHRAPNEL_DAMAGE		71
#define SOUND_SHRAPNEL_EXPLODE		72
#define	SOUND_EYE_STORM				73
#define	SOUND_STATIC_LINK			74
#define	SOUND_UNSTABLE_CURRENT		75
#define	SOUND_PLASMA_FIELD			76
#define	SOUND_FATAL_BONDS 			77
#define	SOUND_SHADOW_WORD			78
#define	SOUND_FLAMING_FISTS			79
#define	SOUND_PERM_IMMOL			80
#define	SOUND_CRY_HEART				81
#define	SOUND_NECROMASTERY			82
#define	SOUND_NECROMASTERY_HP		83
#define	SOUND_REQUIEM_OF_SOULS		84
#define	SOUND_REQUIEM_OF_SOULS_DMG	85
#define	SOUND_BUY_ITEMS				86
#define	SOUND_BLADE_FURY			87
#define	SOUND_DEMON_BLADE			88
#define	SOUND_CRITICAL_BLADE		89
#define	SOUND_TOMES					90
#define	SOUND_THUNDER_CLAP			91

// SPRITES - Спрайты
#define MAX_SPRITES	62

new arrStrSprites[MAX_SPRITES][64];
new arrIdSprites[MAX_SPRITES] = {0};

#define SPR_BANISH				0
#define SPR_SHADOWSTRIKE		1
#define SPR_SNOW				2
#define SPR_FIRE				3
#define SPR_BURNING				4
#define SPR_BEETLE				5
#define SPR_FIREBALL			6
#define SPR_BEAM				7
#define SPR_TRAIL				8
#define SPR_SHOCKWAVE			9
#define SPR_LIGHTNING			10
#define SPR_FLARE				11
#define SPR_WAVE				12
#define SPR_SMOKE				13
#define SPR_IMMOLATE			14
#define SPR_DEATH_TOUCH			15
#define SPR_HEALTH_POTION		16	// Health Potion
#define SPR_STEEL_SKIN			17	// Steel Skin
#define SPR_BLUE_LIGHTNING		18
#define SPR_ICE_FROSTBOLT		19
#define SPR_ICE_SPLINTERS		20	//Ice splinters
#define SPR_ICE_ARROW_TRAIL		21	//Ice arrow
#define SPR_ICE_ARROW			22	//Ice arrow
#define SPR_ICE_EXPLODE			23	//Ice arrow
//Спрайты Для shopmenu4
#define SPR_ICE_BLOCK_TRAIL		24	//"Хвост" Ледяной глыбы
#define SPR_MIRROR_ULTIMATE		25	//Срабатывание отражателя супер навыка
#define SPR_DEATHCOIL			26	//Лик смерти
#define SPR_BLOODSPRAY			27	//Impale
#define SPR_BLOODDROP			28	//Impale 2 
#define SPR_SLEEP				29	//Сонная аура
#define SPR_DK_UNARMOR			30
#define SPR_BLACKSTRIKE			31
#define SPR_BLACKFIRE			32
#define SPR_BURNFIRE			33
#define SPR_POISON				34
#define SPR_ECLIPSE				35
#define SPR_FIRE_PRIEST			36
#define SPR_SMOKE_PRIEST		37
#define SPR_FLAME_PRIEST		38
#define SPR_ZEXPLODE_PRIEST		39
#define SPR_BUBBLE_PRIEST		40
#define SPR_ICON_TALISMAN		41
#define SPR_MFLASH2_BLACK_MAG	42
#define SPR_SINISTER_STRIKE		43
#define SPR_ROGUE_BEAM			44
#define SPR_ROGUE_RING			45
#define SPR_ROGUE_SHURIKEN		46
#define SPR_DRUID_ENTANGLE		47
#define SPR_DRUID_HEALING		48
#define SPR_ASTRAL_STORM		49
#define SPR_MANGLE				50
#define SPR_BLOODRITE			51
#define SPR_HEADSHOT			52
#define SPR_SHRAPNEL			53
#define SPR_SHRAPNEL_EXPLODE	54
#define SPR_STATIC_STORM		55
#define SPR_PLASMA_FIELD		56
#define SPR_FL_FISTS_ARMOR		57
#define SPR_FL_FISTS_DMG		58
#define SPR_PERM_IMMOL			59
#define SPR_NECROMASTERY		60
#define SPR_NECROMASTERY_EXP    61


// MODELS - Модели
#define MAX_MODELS	8

new arrStrModels[MAX_MODELS][64];
new arrIdModels[MAX_MODELS] = {0};

#define MDL_FIREBALL			0
#define MDL_FRIEZADISC			1
#define MDL_FUN_SUPPLYBOX		2
#define MDL_GLASSGIBS			3
#define MDL_BSKULL				4
#define MDL_TENTACLE			5
#define MDL_HEALINGWARD			6
#define MDL_JKNIFE				7
//#define MDL_DKINETIC_FIELD		8



