// ******************************************************************
// Глобальные функции настройки брони
// ******************************************************************

//Класс общих функций для игроков
#define clAr:		clAr_

//Функции
#define clAr_getRaceMinArmor			_AR_ID_1
#define clAr_getRaceMaxArmor			_AR_ID_2
#define clAr_getUserArmor				_AR_ID_3
#define clAr_setUserArmor				_AR_ID_4
#define clAr_cfLoadArmorFile			_AR_ID_5
#define clAr_setCurRespawnRaceArmor		_AR_ID_6
#define clAr_setUserArmorOnType			_AR_ID_7



new const WAR3FT_ARMOR_FILE[] = "war3ft/armor/armor_races.ini"

// Секции файла настроек armor_races.ini
enum
{
	SECTION_NONE = 0,
	SECTION_ARMOR_OPTIONS
	
}

new Array:arrIntMinArmor;		//Массив минимального брони
new Array:arrIntMaxArmor;		//Массив максимального брони

new arrArmorRace[2];

new iArmorItemRace;				//ARMOR_ITEM - Количество брони прибавляемое при использовании предмета "Стальная кожа"