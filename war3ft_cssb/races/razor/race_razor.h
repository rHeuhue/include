// ******************************************************************
// Раса: Блэйд (Race: Razor) Constants
// ******************************************************************

//Класс Блэйд (Race: Razor )
#define clRazor::		clRazor_


#define clRazor_setSkillsInit					_Razor_ID_1
#define clRazor_skillEyeOfTheStorm				_Razor_ID_2
#define clRazor_fCreateSmokeGroup				_Razor_ID_3
#define clRazor_ultPlasmaField					_Razor_ID_4
#define clRazor_fCreatePlasmaField				_Razor_ID_5
#define clRazor_skillStaticLink					_Razor_ID_6
#define clRazor_skillUnstableCurrent			_Razor_ID_7
#define clRazor_skillManna						_Razor_ID_8


#define PLASMA_FIELD_RAZOR_CLASSNAME "r_plasma_field"

#define	clRazor_tID_MANNA			8963247
#define clRazor_taskActiveManna		_taskActiveManna

new iUnstableCurrentDmg;		//RAZOR_UNSTABLE_CURRENT_DMG - Дамаг от скила "Неустойчивый поток"
new Float:fManaChance;			//RAZOR_MANA_CHANCE - Шанс срабатывания скила "Манна небесная"
new iManaRadius;				//RAZOR_MANA_RADIUS - Радиус в котором игроку дается бонус от скила "Манна небесная"
new iManaHP;					//RAZOR_MANA_HP - Бонус здоровья от скила "Манна небесная"
new iPlasmaFieldNumTouch;		//RAZOR_PLASMA_FIELD_NUM_TOUCH - Количество отскоков от стен, прежде чем исчезнет объект, созданный супер навыком
new Float:fPlasmaFieldRadius;	//RAZOR_PLASMA_FIELD_RADIUS - Радиус поражения супер навыком "Плазменное поле"
new iPlasmaFieldDmg;			//RAZOR_PLASMA_FIELD_DMG - Дамаг от супер навыка "Плазменное поле"