// ******************************************************************
// Раса: Разбойник (Race: Rogue) Constants
// ******************************************************************


//Класс Разбойник (Race: Rogue )
#define clRogue::		clRogue_

//Функции
#define clRogue_setRogueSkillsInit		_Rogue_ID_1
#define clRogue_skillSinisterStrike		_Rogue_ID_2
#define clRogue_addSkillCharge			_Rogue_ID_3
#define clRogue_skillVanish				_Rogue_ID_4
#define clRogue_skillCripplingPoison	_Rogue_ID_5
#define clRogue_ultShurikenToss			_Rogue_ID_6
#define clRogue_setChargeNum			_Rogue_ID_7

//Задачи
#define	clRogue_tID_VANISH		952147		// Vanish - Исчезновение
#define	clRogue_tID_CP_SPEED	521748		// 

#define clRogue_taskResetVanish			_taskResetVanish
#define clRogue_taskResetCP_Speed		_taskResetCP_Speed


#define BALL_CLASSNAME "shuriken"
#define BEAM_CLASSNAME "shuriken_beam"


new Float:fShurikenDmg;				//ROGUE_SHURIKEN_DMG - Урон при взрыве сюрикена
new Float:fShurikenRadiusExp;		//ROGUE_SHURIKEN_RADIUS_EXP - Радиус урона при взрыве сюрикена
new Float:fShurikenBeamRadius;		//ROGUE_SHURIKEN_BEAM_RADIUS - Радиус поражения лучом от сюрикена
new Float:fShurikenBeamDmg;			//ROGUE_SHURIKEN_BEAM_DMG - Урон от луча сюрикена

//Max кол-во зарядов:
new	iRogueChargeMax_1;	//ROGUE_CHARGE_MAX_1 - (Скил 1 уровня - Sinister Strike - Коварный удар)
new	iRogueChargeMax_2;	//ROGUE_CHARGE_MAX_2 - (Скил 2 уровня - Vanish - Исчезновение)
new	iRogueChargeMax_3;	//ROGUE_CHARGE_MAX_3 - (Скил 3 уровня - Crippling Poison - Калечащий яд)
//Min кол-во зарядов зарядов:
new	iRogueChargeMin_1;	//ROGUE_CHARGE_MIN_1 - (Скил 1 уровня - Sinister Strike - Коварный удар)
new	iRogueChargeMin_2;	//ROGUE_CHARGE_MIN_2 - (Скил 2 уровня - Vanish - Исчезновение)
new	iRogueChargeMin_3;	//ROGUE_CHARGE_MIN_3 - (Скил 3 уровня - Crippling Poison - Калечащий яд)
//Отсчет времени в секундах, черезе сколько появится шанс получить заряд:
new	iRogueCount_1;		//ROGUE_COUNT_1 - (Скил 1 уровня - Sinister Strike - Коварный удар)
new	iRogueCount_2;		//ROGUE_COUNT_2 - (Скил 2 уровня - Vanish - Исчезновение)
new	iRogueCount_3;		//ROGUE_COUNT_3 - (Скил 3 уровня - Crippling Poison - Калечащий яд)

//Урон для Скила 1 уровня  (Sinister Strike - Коварный удар)
new iSStrike_Secondary;	//ROGUE_SSTRIKE_SECONDARY - урон с пистолета
new iSStrike_Primary;	//ROGUE_SSTRIKE_PRIMARY - урон с автомата
new iSStrike_Knife;		//ROGUE_SSTRIKE_KNIFE - урон с ножа
new iSStrike_Grenade;	//ROGUE_SSTRIKE_GRENADE - урон с гранаты