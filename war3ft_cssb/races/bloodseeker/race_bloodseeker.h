// ******************************************************************
// Раса: Бладсикер (Race: Bloodseeker) Constants
// ******************************************************************

//Класс Бладсикер (Race: Bloodseeker )
#define clBloodseeker::		clBloodseeker_


#define clBloodseeker_setSkillsInit					_Bloodseeker_ID_1
#define clBloodseeker_addSkillCharge				_Bloodseeker_ID_2
#define clBloodseeker_skillBloodRage				_Bloodseeker_ID_3
#define clBloodseeker_fShowMenuAbility				_Bloodseeker_ID_4
#define clBloodseeker_Callback_Menu					_Callback_Menu_Bloodseeker
#define clBloodseeker_skillBloodBath				_Bloodseeker_ID_5
#define clBloodseeker_skillBloodRite				_Bloodseeker_ID_6
#define clBloodseeker_skillVendetta					_Bloodseeker_ID_7
#define clBloodseeker_ultBloodyMadness				_Bloodseeker_ID_8




#define	clBloodseeker_tID_BLOODRAGE		8963245
#define clBloodseeker_taskResetBloodRage	_taskResetBloodRage

#define	clBloodseeker_tID_BLOODRITE_A		9632578
#define clBloodseeker_taskResetBloodRiteA	_taskResetBloodRiteA

#define	clBloodseeker_tID_BLOODRITE_V		78542001
#define clBloodseeker_taskResetBloodRiteV	_taskResetBloodRiteV


//Max кол-во зарядов:
new	iBloodseekerChargeMax_1;	//BLOODSEEKER_CHARGE_MAX_1
new	iBloodseekerChargeMax_2;	//BLOODSEEKER_CHARGE_MAX_2
new	iBloodseekerChargeMax_3;	//BLOODSEEKER_CHARGE_MAX_3
//Min кол-во зарядов зарядов:
new	iBloodseekerChargeMin_1;	//BLOODSEEKER_CHARGE_MIN_1
new	iBloodseekerChargeMin_2;	//BLOODSEEKER_CHARGE_MIN_2
new	iBloodseekerChargeMin_3;	//BLOODSEEKER_CHARGE_MIN_3
//Отсчет времени в секундах, черезе сколько появится шанс получить заряд:
new	iBloodseekerCount_1;		//BLOODSEEKER_COUNT_1
new	iBloodseekerCount_2;		//BLOODSEEKER_COUNT_2
new	iBloodseekerCount_3;		//BLOODSEEKER_COUNT_3


new iAmountVendettaDMG[33];

new iBloodRiteDmg;					//BLOODSEEKER_BLOOD_RITE_DMG - Дамаг наносимый скилом "Кровавый обряд"
new Float:fBloodyMadnessDmg;		//BLOODSEEKER_BLOODY_MADNESS_DMG - Дамаг наносимый ультом "Кровавое безумие"
new Float:fBloodyMadnessHp;			//BLOODSEEKER_BLOODY_MADNESS_HP - Здоровье ульта "Кровавое безумие" (1 сущности)
new iNumVendettaDMG;				//BLOODSEEKER_VENDETTA_DMG_NUM - Сумма дамага нанесенного герою. Необходима для срабатывания скила "Кровная месть"
new iVendettaDmg;					//BLOODSEEKER_VENDETTA_DMG - Дамаг от скила "Кровная месть"
new iBloodRageDmg;					//BLOODSEEKER_BLOOD_RAGE_DMG - Дамаг наносимый скилом "Ярость крови"
new Float:fBloodRageSpeedFactor;	//BLOODSEEKER_BLOOD_RAGE_SPEED_FACTOR - множитель скорости при активности "Ярость крови"
new Float:fBloodBathHpFactor;		//BLOODSEEKER_BLOOD_BATH_HP_FACTOR - множитель здоровья при активности "Кровавая баня"