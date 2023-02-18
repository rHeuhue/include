// ******************************************************************
// Раса: Джагернаут (Race: Juggernaut) Constants
// ******************************************************************

//Класс Джагернаут (Race: Juggernaut )
#define clJuggernaut::		clJuggernaut_


#define clJuggernaut_setSkillsInit					_Juggernaut_ID_1
#define clJuggernaut_addSkillCharge					_Juggernaut_ID_2
#define clJuggernaut_skillHealingWard				_Juggernaut_ID_4
#define clJuggernaut_setChargeNum					_Juggernaut_ID_5
#define clJuggernaut_skillCriticalBlade				_Juggernaut_ID_6
#define clJuggernaut_fCreateBlade					_Juggernaut_ID_7
#define clJuggernaut_skillDemonBlade				_Juggernaut_ID_8
#define clJuggernaut_ultBladeFury					_Juggernaut_ID_9
#define clJuggernaut_skillBladeDance				_Juggernaut_ID_10

#define HEALING_WARD_CLASSNAME "j_healing_ward"
#define CRITICAL_BLADE_CLASSNAME "j_knife_cb"



enum enBlade
{
	enBlade_Critical,
	enBlade_Demon,
	enBlade_HP
};


//Max кол-во зарядов:
new	iJuggernautChargeMax_1;	//JUGGERNAUT_CHARGE_MAX_1
new	iJuggernautChargeMax_2;	//JUGGERNAUT_CHARGE_MAX_2
new	iJuggernautChargeMax_3;	//JUGGERNAUT_CHARGE_MAX_3
//Min кол-во зарядов зарядов:
new	iJuggernautChargeMin_1;	//JUGGERNAUT_CHARGE_MIN_1
new	iJuggernautChargeMin_2;	//JUGGERNAUT_CHARGE_MIN_2
new	iJuggernautChargeMin_3;	//JUGGERNAUT_CHARGE_MIN_3
//Отсчет времени в секундах, черезе сколько появится шанс получить заряд:
new	iJuggernautCount_1;		//JUGGERNAUT_COUNT_1
new	iJuggernautCount_2;		//JUGGERNAUT_COUNT_2
new	iJuggernautCount_3;		//JUGGERNAUT_COUNT_3

new Float:fHealingWardRadius;		//JUGGERNAUT_HEALING_WARD_RADIUS - Радиус лечения скилом "Исцеляющий идол"
new iHealingWardNumHealth;			//JUGGERNAUT_HEALING_WARD_NUM_HEALTH - Сколько за раз лечит "Исцеляющий идол"
new Float:fHealingWardFrequency;	//JUGGERNAUT_HEALING_WARD_FREQUENCY - Частота лечения "Исцеляющий идол"
new Float:fBladeCriticalDmg;		//JUGGERNAUT_BLADE_CRITICAL_DMG - Дамаг от "Критический клинок"
new Float:fChanseDemonBlade;		//JUGGERNAUT_CHANSE_DEMON_BLADE - Шанс срабатывания "Демонический клинок"
new iBladeDemonArmor;				//JUGGERNAUT_BLADE_DEMON_ARMOR - Кол-во снимаемой брони от "Демонический клинок"
new iBladeDemonHP;					//JUGGERNAUT_BLADE_DEMON_HP - Кол-во даваемого HP от "Демонический клинок"
new Float:fChanseBladeDance;		//JUGGERNAUT_CHANSE_DEMON_BLADE - Шанс срабатывания "Танец лезвий"
new iBladeDancePercentDmg;			//JUGGERNAUT_PERCENT_DMG_BLADE_DANCE - Процент увеличиваемый дамаг "Танец лезвий"
new Float:fWardHp;					//JUGGERNAUT_WARD_HP - Здоровье исцеляющего идола