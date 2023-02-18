// ******************************************************************
// Раса: Друид (Race: Druid) Constants
// ******************************************************************

//Класс Друид (Race: Druid )
#define clDruid::		clDruid_


#define clDruid_setDruidSkillsInit		_Druid_ID_1
#define clDruid_addSkillCharge			_Druid_ID_2
#define clDruid_skillWildMush_Entangle  _Druid_ID_3
#define clDruid_skillWildMush_Healing	_Druid_ID_4
#define clDruid_skillWildMush_Explode	_Druid_ID_5
#define clDruid_fCreateWildMushroom		_Druid_ID_6
#define clDruid_ultAstralStorm			_Druid_ID_7
#define clDruid_efBeamCylinder			_Druid_ID_8
#define clDruid_setChargeNum			_Druid_ID_9
#define clDruid_skillMangle				_Druid_ID_10
#define clDruid_IsWildMushroomSetup		_Druid_ID_11
#define clDruid_IsWildMushroomResp		_Druid_ID_12
#define clDruid_fCreateWildMushroom_2	_Druid_ID_13
#define clDruid_addWMStrikeExplode		_Druid_ID_14
#define clDruid_addWMStrikeEntangle		_Druid_ID_15
#define clDruid_addWMStrikeHealing		_Druid_ID_16





enum enWildMush
{
	enWildMush_Entangle,
	enWildMush_Healing,
	enWildMush_Explode,
	enWildMush_Blood
};


//Max кол-во зарядов:
new	iDruidChargeMax_1;	//DRUID_CHARGE_MAX_1
new	iDruidChargeMax_2;	//DRUID_CHARGE_MAX_2
new	iDruidChargeMax_3;	//DRUID_CHARGE_MAX_3
//Min кол-во зарядов зарядов:
new	iDruidChargeMin_1;	//DRUID_CHARGE_MIN_1
new	iDruidChargeMin_2;	//DRUID_CHARGE_MIN_2
new	iDruidChargeMin_3;	//DRUID_CHARGE_MIN_3
//Отсчет времени в секундах, черезе сколько появится шанс получить заряд:
new	iDruidCount_1;		//DRUID_COUNT_1
new	iDruidCount_2;		//DRUID_COUNT_2
new	iDruidCount_3;		//DRUID_COUNT_3

new Float:fRadiusSpawnWild;		//DRUID_RADIUS_SPAWN_WILD - Радиус на котором находится выращенный гриб от точки респауна
new Float:fWildHpEnt;			//DRUID_WILD_HEALTH_ENT  - Здоровье Дикий гриб: Запутывание
new Float:fWildHpHeal;			//DRUID_WILD_HEALTH_HEAL - Здоровье Дикий гриб: Исцеление
new Float:fWildHpExp;			//DRUID_WILD_HEALTH_EXP - Здоровье Дикий гриб: Удар
new Float:fWildExplodeDmg;		//DRUID_WILD_EXPLODE_DMG - Дамаг (Скил 3 - Дикий гриб: Удар)
new Float:fWildHealingHp;		//DRUID_WILD_HEALING_HP - Здоровье (Скил 2 - Дикий гриб: Исцеление)
new Float:fWildRadiusDmg;		//DRUID_WILD_RADIUS_DMG - Радиус в котором должен находиться игрок чтобы cработал гриб
new Float:fAStormDmg;			//DRUID_ASTRAL_STORM_DMG - Дамаг от супер навыка Астральный шторм
new Float:fAStormRadiusDmg;		//DRUID_ASTRAL_STORM_RADIUS_DMG - Радиус поражения супер навыком Астральный шторм
new Float:fAstormSmallDmg;		//DRUID_ASTORM_SMALL_DMG - Дамаг от частей супер навыка Астральный шторм
new Float:fAstormSmallRadDmg;	//DRUID_ASTORM_SMALL_RADIUS_DMG - Радиус поражения от частей супер навыком Астральный шторм
new Float:fShanceMangle;		//DRUID_SHANCEMANGLE - Шанс срабатывания скила Увечье
new iShanceMangleDmg;			//DRUID_SHANCEMANGLEDMG - Дамаг от скила Увечье

