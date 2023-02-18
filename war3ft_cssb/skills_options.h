
new const WAR3FT_CUSTOM_FILE_SKILLS[] = "war3ft/options/skills.ini"

#define MAX_SKILLS 114	//Количество скилов


// Секции файла настроек skills_options.ini
enum
{
	SECTION_NONE = 0,
	SECTION_MAX_LEVELS,
	SECTION_MAX_SKILL_LEVEL,
	SECTION_UNDEAD_SKILL1,
	SECTION_UNDEAD_SKILL2,
	SECTION_UNDEAD_SKILL3,
	SECTION_HUMAN_SKILL1,
	SECTION_HUMAN_SKILL2,
	SECTION_HUMAN_SKILL3,
	SECTION_ORC_SKILL1,
	SECTION_ORC_SKILL2,
	SECTION_ORC_SKILL3,
	SECTION_ELF_SKILL1,
	SECTION_ELF_SKILL2,
	SECTION_ELF_SKILL3,
	SECTION_BLOOD_MAGE_SKILL1,
	SECTION_BLOOD_MAGE_SKILL2,
	SECTION_BLOOD_MAGE_SKILL3,
	SECTION_BLOOD_MAGE_SKILL4,
	SECTION_HUNTER_SKILL1,
	SECTION_HUNTER_SKILL2,
	SECTION_HUNTER_SKILL3,
	SECTION_HUNTER_SKILL4,
	SECTION_WARDEN_SKILL1,
	SECTION_WARDEN_SKILL2,
	SECTION_WARDEN_SKILL3,
	SECTION_WARDEN_SKILL4,
	SECTION_LORD_SKILL1,
	SECTION_LORD_SKILL2,
	SECTION_LORD_SKILL3,
	SECTION_LORD_SKILL4,
	SECTION_ICE_SKILL1,
	SECTION_ICE_SKILL2,
	SECTION_ICE_SKILL3,
	SECTION_KNIGHT_SKILL1,
	SECTION_KNIGHT_SKILL2,
	SECTION_KNIGHT_SKILL3,
	SECTION_BLACK_MAG_SKILL1,
	SECTION_BLACK_MAG_SKILL2,
	SECTION_BLACK_MAG_SKILL3,
	SECTION_ALCHEMIST_SKILL1,
	SECTION_ALCHEMIST_SKILL2,
	SECTION_ALCHEMIST_SKILL3,
	SECTION_ALCHEMIST_SKILL4,
	SECTION_PRIEST_SKILL1,
	SECTION_PRIEST_SKILL2,
	SECTION_PRIEST_SKILL3,
	SECTION_PRIEST_SKILL4,
	SECTION_ROGUE_SKILL1,
	SECTION_ROGUE_SKILL2,
	SECTION_ROGUE_SKILL3,
	SECTION_DRUID_SKILL1,
	SECTION_DRUID_SKILL2,
	SECTION_DRUID_SKILL3,
	SECTION_BLOODSEEKER_SKILL1,
	SECTION_BLOODSEEKER_SKILL2,
	SECTION_BLOODSEEKER_SKILL3,
	SECTION_JUGGERNAUT_SKILL1,
	SECTION_JUGGERNAUT_SKILL2,
	SECTION_JUGGERNAUT_SKILL3,
	SECTION_SNIPER_SKILL1,
	SECTION_SNIPER_SKILL2,
	SECTION_SNIPER_SKILL3,
	SECTION_DISRUPTOR_SKILL1,
	SECTION_DISRUPTOR_SKILL2,
	SECTION_DISRUPTOR_SKILL3,
	SECTION_RAZOR_SKILL1,
	SECTION_RAZOR_SKILL2,
	SECTION_RAZOR_SKILL3,
	SECTION_WARLOCK_SKILL1,
	SECTION_WARLOCK_SKILL2,
	SECTION_WARLOCK_SKILL3,
	SECTION_SHADOW_FIEND_SKILL1,
	SECTION_SHADOW_FIEND_SKILL2,
	SECTION_SHADOW_FIEND_SKILL3,

	SECTION_24_SKILL1,
	SECTION_24_SKILL2,
	SECTION_24_SKILL3,

	SECTION_25_SKILL1,
	SECTION_25_SKILL2,
	SECTION_25_SKILL3
};

//Переменные
new iMaxLevels;		//Количество уровней
new iMaxSkillLevel;	//Максимальный уровень прокачки скила

//Массивы
new Array:arrVampiricAura;
new Array:arrUnholyAura;
new Array:arrLevitation;
// Раса: Альянс Людей (Race: Human)
new Array:arrInvisibility;
new	iDevotionAura;
new Float:fHumanSkill3MinPercent;
new Float:fHumanSkill3MaxPercent;
new Array:arrBash;
// Раса: Орда Орков (Race: Orc)
new Array:arrCriticalStrike;
new Array:arrCriticalGrenade;
new Float:fOrcSkill3MinPercent;
new Float:fOrcSkill3MaxPercent;
new Array:arrEquipmentreincarnation;
//*******************************************************
// Раса: Ночные Эльфы (Race: Night Elf)
//*******************************************************
new Float:fElfSkill1MinPercent;
new Float:fElfSkill1MaxPercent;
new Array:arrEvasion;
new Array:arrThornsAura;
new Array:arrTrueshotAura;
//*******************************************************
// Раса: Кровавый Маг (Race: Blood Mage)
//*******************************************************
new Float:fBloodMageSkill1MinPercent;
new Float:fBloodMageSkill1MaxPercent;
new Array:arrPhoenix;
new Float:fBloodMageSkill2MinPercent;
new Float:fBloodMageSkill2MaxPercent;
new Array:arrBanish;
new Array:arrSiphonMana;
new Array:arrResistantSkin;
//*******************************************************
// Раса: Призрачный Охотник (Race: Shadow Hunter)
//*******************************************************
new Array:arrHealingWave;
new Float:fHunterSkill2MinPercent;
new Float:fHunterSkill2MaxPercent;
new Array:arrHex;
new Array:arrSerpentWard;
new Float:fHunterSkill4MinPercent;
new Float:fHunterSkill4MaxPercent;
new Array:arrUnstableConcoction;
//*******************************************************
// Раса: Шпион (Race: Warden)
//*******************************************************
new Float:fWardenSkill1MinPercent;
new Float:fWardenSkill1MaxPercent;
new Array:arrFanOfKnives;
new Float:fWardenSkill2MinPercent;
new Float:fWardenSkill2MaxPercent;
new Array:arrBlink;
new Float:fWardenSkill3MinPercent;
new Float:fWardenSkill3MaxPercent;
new Array:arrShadowStrike;
new Array:arrHardenedSkin;
//*******************************************************
// Раса: Лорд Мертвых (Race: Crypt Lord)
//*******************************************************
new Float:fLordSkill1MinPercent;
new Float:fLordSkill1MaxPercent;
new Array:arrImpale;
new Array:arrSpikedCarapace;
new Float:fLordSkill3MinPercent;
new Float:fLordSkill3MaxPercent;
new Array:arrCarrionBeetle;
new Float:fLordSkill4MinPercent;
new Float:fLordSkill4MaxPercent;
new Array:arrOrbOfAnnihilation;
//*******************************************************
// Раса: Ледяной маг (Race: Ice magician)
//*******************************************************
new Float:fIceSkill1MinPercent;
new Float:fIceSkill1MaxPercent;
new Array:arrIceSplinters;
new Float:fIceSkill2MinPercent;
new Float:fIceSkill2MaxPercent;
new Array:arrIceArrow;
new Float:fIceSkill3MinPercent;
new Float:fIceSkill3MaxPercent;
new Array:arrColdCone;
//*******************************************************
// Раса: Рыцарь смерти (Race: Death knight)
//*******************************************************
new Array:arrUnbreakableArmor;
new Array:arrBloodBoil;
new Array:arrDeathCoil;
//*******************************************************
// Раса: Черный маг (Race: Black Mag)
//*******************************************************
new Float:fBlackMagSkill1MinPercent;
new Float:fBlackMagSkill1MaxPercent;
new Array:arrBlackStrike;
new Float:fBlackMagSkill2MinPercent;
new Float:fBlackMagSkill2MaxPercent;
new Array:arrBlackShadow;
new Float:fBlackMagSkill3MinPercent;
new Float:fBlackMagSkill3MaxPercent;
new Array:arrBlackPower;
//*******************************************************
// Раса: Алхимик (Race: Alchemist)
//*******************************************************
new Float:fAlchemistSkill1MinPercent;
new Float:fAlchemistSkill1MaxPercent;
new Array:arrPoison;
new Float:fAlchemistSkill2MinPercent;
new Float:fAlchemistSkill2MaxPercent;
new Array:arrShock;
new Float:fAlchemistSkill3MinPercent;
new Float:fAlchemistSkill3MaxPercent;
new Array:arrFrost;
new Float:fAlchemistSkill4MinPercent;
new Float:fAlchemistSkill4MaxPercent;
new Array:arrPassHypnosis;
//*******************************************************
// Раса: Жрец (Race: Priest)
//*******************************************************
new Float:fPriestSkill1MinPercent;
new Float:fPriestSkill1MaxPercent;
new Array:arrEntryintochasm;
new Float:fPriestSkill2MinPercent;
new Float:fPriestSkill2MaxPercent;
new Array:arrSacredFire;
new Float:fPriestSkill3MinPercent;
new Float:fPriestSkill3MaxPercent;
new Array:arrSpiritualAccuracy;
new Array:arrMysticism;
//*******************************************************
// Раса: Разбойник (Race: Rogue)
//*******************************************************
new Float:fRogueSkill1MinPercent;
new Float:fRogueSkill1MaxPercent;
new Array:arrSinisterStrike;

new Float:fRogueSkill2MinPercent;
new Float:fRogueSkill2MaxPercent;
new Array:arrVanish;

new Float:fRogueSkill3MinPercent;
new Float:fRogueSkill3MaxPercent;
new Array:arrCripplingPoison;
//*******************************************************
// Раса: Друид (Race: Druid)
//*******************************************************
new Float:fDruidSkill1MinPercent;
new Float:fDruidSkill1MaxPercent;
new Array:arrWildEntanglement;

new Float:fDruidSkill2MinPercent;
new Float:fDruidSkill2MaxPercent;
new Array:arrWildHealing;

new Float:fDruidSkill3MinPercent;
new Float:fDruidSkill3MaxPercent;
new Array:arrWildExplode;

//*******************************************************
// Раса: (Бладсикер) Кровавый искатель (Race: Bloodseeker)
//*******************************************************
new Float:fBloodseekerSkill1MinPercent;
new Float:fBloodseekerSkill1MaxPercent;
new Array:arrBloodRage;

new Float:fBloodseekerSkill2MinPercent;
new Float:fBloodseekerSkill2MaxPercent;
new Array:arrBloodBath;

new Float:fBloodseekerSkill3MinPercent;
new Float:fBloodseekerSkill3MaxPercent;
new Array:arrBloodRite;

//*******************************************************
// Раса: Джагернаут (Race: Juggernaut)
//*******************************************************
new Float:fJuggernautSkill1MinPercent;
new Float:fJuggernautSkill1MaxPercent;
new Array:arrHealingWard;

new Float:fJuggernautSkill2MinPercent;
new Float:fJuggernautSkill2MaxPercent;
new Array:arrCriticalBlade;

new Float:fJuggernautSkill3MinPercent;
new Float:fJuggernautSkill3MaxPercent;
new Array:arrDemonBlade;

//*******************************************************
// Раса: Снайпер (Race: Sniper)
//*******************************************************
new Float:fHeadshotSkill1MinPercent;
new Float:fHeadshotSkill1MaxPercent;
new Array:arrHeadshot;
new Array:arrPhaseBoots;
new Array:arrSkillShrapnelCharge;

//*******************************************************
// Раса: Разрушитель (Race: Disruptor)
//*******************************************************
new Float:fGlimpseSkill1MinPercent;
new Float:fGlimpseSkill1MaxPercent;
new Array:arrGlimpse;

new Float:fThunderStrikeSkill2MinPercent;
new Float:fThunderStrikeSkill2MaxPercent;
new Array:arrThunderStrike;

new Float:fKineticFieldSkill3MinPercent;
new Float:fKineticFieldSkill3MaxPercent;
new Array:arrKineticField;
//*******************************************************
// Раса: Блэйд (Race: Razor)
//*******************************************************
new Float:fEyeOfTheStormSkill1MinPercent;
new Float:fEyeOfTheStormSkill1MaxPercent;
new Array:arrEyeOfTheStorm;

new Float:fStaticLinkSkill2MinPercent;
new Float:fStaticLinkSkill2MaxPercent;
new Array:arrStaticLink;

new Float:fUnstableCurSkill3MinPercent;
new Float:fUnstableCurSkill3MaxPercent;
new Array:arrUnstableCurrent;
//*******************************************************
// Раса: Варлок (Колдун) (Race: Warlock)
//*******************************************************
new Float:fFatalBondsSkill1MinPercent;
new Float:fFatalBondsSkill1MaxPercent;
new Array:arrFatalBonds;

new Float:fShadowWordSkill2MinPercent;
new Float:fShadowWordSkill2MaxPercent;
new Array:arrShadowWord;

new Float:fFlamingFistsSkill3MinPercent;
new Float:fFlamingFistsSkill3MaxPercent;
new Array:arrFlamingFists;
//*******************************************************
// Раса: Невермор (Race: Shadow Fiend)
//*******************************************************
new Array:arrPresenceDarkLord;

new Float:fRequiemSoulsSkill2MinPercent;
new Float:fRequiemSoulsSkill2MaxPercent;
new Array:arrRequiemSouls;

new Float:fCryHeartSkill3MinPercent;
new Float:fCryHeartSkill3MaxPercent;
new Array:arrCryHeart;

//*******************************************************
// Раса: 24 (Race: 24)
//*******************************************************
/*new Float:f24Skill1MinPercent;
new Float:f24Skill1MaxPercent;
new Array:arrSkill_1_24;

new Float:f24Skill2MinPercent;
new Float:f24Skill2MaxPercent;
new Array:arrSkill_2_24;

new Float:f24Skill3MinPercent;
new Float:f24Skill3MaxPercent;
new Array:arrSkill_3_24;
*/
//*******************************************************
// Раса: 25 (Race: 25)
//*******************************************************
/*new Float:f25Skill1MinPercent;
new Float:f25Skill1MaxPercent;
new Array:arrSkill_1_25;

new Float:f25Skill2MinPercent;
new Float:f25Skill2MaxPercent;
new Array:arrSkill_2_25;

new Float:f25Skill3MinPercent;
new Float:f25Skill3MaxPercent;
new Array:arrSkill_3_25;
*/