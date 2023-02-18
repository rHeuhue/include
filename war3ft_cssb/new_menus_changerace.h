//Общее количество менюшек
#define	MAX_NUM_MENUS 7

//Заголовки менюшек
new const MENU_TITLES[MAX_NUM_MENUS][] = 
{
	"MENU_SELECT_RACE",
	"MENU_ID_RACE_1",
	"MENU_ID_RACE_2",
	"MENU_ID_RACE_3",
	"MENU_ID_RACE_4",
	"MENU_ID_RACE_5",
	"MENU_ID_RACE_6"
};
//Функции выбора пунктов в меню
new const MENU_CALLBACK_ALL[MAX_NUM_MENUS][] = 
{
	"_Callback_MENU_SelectRace",
	"_Callback_SUB_MENU_ID_1",
	"_Callback_SUB_MENU_ID_2",
	"_Callback_SUB_MENU_ID_3",
	"_Callback_SUB_MENU_ID_4",
	"_Callback_SUB_MENU_ID_5",
	"_Callback_SUB_MENU_ID_6"
};

//Идентификаторы под меню
#define	MENU_ID_DEFAULT	100
#define	MENU_ID_RACE_1	101
#define	MENU_ID_RACE_2	102
#define	MENU_ID_RACE_3	103
#define	MENU_ID_RACE_4	104
#define	MENU_ID_RACE_5	105
#define	MENU_ID_RACE_6	106
/*
//Список пунктов меню Выбора рас (главного меню)
#define	MAX_ITEM_LIST_ITEM_SELECT_RACE 6
new const LIST_ITEM_SELECT_RACE[MAX_ITEM_LIST_ITEM_SELECT_RACE] = 
{
	MENU_ID_RACE_1,		//"Гильдия Нежити"
	MENU_ID_RACE_2,		//"Гильдия Магов"
	MENU_ID_RACE_3,		//"Гильдия Альянса"
	MENU_ID_RACE_4,		//"Гильдия Убийц"
	MENU_ID_RACE_5,		//"Гильдия Света"
	MENU_ID_RACE_6		//"Гильдия Тьмы"
	
};


//Список пунктов меню "Гильдия Нежити"
#define	MAX_ITEM_LIST_1 4
new const LIST_ITEM_RACE_1[MAX_ITEM_LIST_1] = 
{
	RACE_UNDEAD,
	RACE_DEATH_KNIGHT,
	RACE_CRYPT,
	RACE_PRIEST
};

//Список пунктов меню "Гильдия Магов"
#define	MAX_ITEM_LIST_2 4
new const LIST_ITEM_RACE_2[MAX_ITEM_LIST_2] = 
{
	RACE_BLOOD,
	RACE_BLACK_MAGICIAN,
	RACE_FROST_MAGE,
	RACE_DRUID
};

//Список пунктов меню "Гильдия Альянса"
#define	MAX_ITEM_LIST_3 3
new const LIST_ITEM_RACE_3[MAX_ITEM_LIST_3] = 
{
	RACE_HUMAN,
	RACE_SHADOW,
	RACE_CHAMELEON
};

//Список пунктов меню "Гильдия Убийц"
#define	MAX_ITEM_LIST_4 4
new const LIST_ITEM_RACE_4[MAX_ITEM_LIST_4] = 
{
	RACE_ORC,
	RACE_ELF,
	RACE_WARDEN,
	RACE_ROGUE
};


//Для текущей версии менюшки (потом удалить)
//Список пунктов меню "Армия Света"
#define	MAX_ITEM_LIST_5 3
new const LIST_ITEM_RACE_5[MAX_ITEM_LIST_5] = 
{
	RACE_BLOODSEEKER,
	RACE_JUGGERNAUT	
};

//Список пунктов меню "Армия Тьмы"
#define	MAX_ITEM_LIST_6 2
new const LIST_ITEM_RACE_6[MAX_ITEM_LIST_6] = 
{
	RACE_ALCHEMIST,
	RACE_SNIPER
	
};
*/

//Переменые
new arrRaceXP[MAX_RACES]; //массив XP

//Сброс выбора расы если игрок выбрал ее (ограничение уровня)
new bool:arrResetRace[33];
#define TASKID_RESETRACE	43645

new const WAR3FT_MENU_FILE[] = "war3ft/menu/war3ftmenu.ini"

// Секции файла настроек war3ftmenu.ini
enum enWar3ftMenu
{
	SECTION_NONE = 0,
	SECTION_BASE_MENU,
	SECTION_BASE_MENU_SUB_1,
	SECTION_BASE_MENU_SUB_2,
	SECTION_BASE_MENU_SUB_3,
	SECTION_BASE_MENU_SUB_4,
	SECTION_BASE_MENU_SUB_5,
	SECTION_BASE_MENU_SUB_6,
	SECTION_OPTIONS_MENU
	
}


new Array:arrIntBaseMenuData;			//Массив главного меню
new Array:arrIntBaseMenuDataSub_1		//Массив подменю 1 "Гильдия Нежити"
new Array:arrIntBaseMenuDataSub_2		//Массив подменю 2 "Гильдия Магов"
new Array:arrIntBaseMenuDataSub_3		//Массив подменю 3 "Гильдия Альянса"
new Array:arrIntBaseMenuDataSub_4		//Массив подменю 4 "Гильдия Убийц"
new Array:arrIntBaseMenuDataSub_5		//Массив подменю 5 "Гильдия Света"
new Array:arrIntBaseMenuDataSub_6		//Массив подменю 6 "Гильдия Тьмы"

new szColorNumber[16];			//MENU_COLOR_NUMBER - Цвет номера в меню
new szColorRace[16];			//MENU_COLOR_RACE - Цвет названия расы или героя
new szColorXP_Level[16];		//MENU_COLOR_XP_LEVEL - Цвет количества опыта,уровней
new szColorWordXP_Level[16];	//MENU_COLOR_WORD_XP_LEVEL - Цвет отображения слов Опыт и Уровень
new szColorVS[16];				//MENU_COLOR_VS - Цвет ( ... vs ... )
new szColorVsNum[16];			//MENU_COLOR_VS_NUMBER - Цвет значений в ( ... vs  ... )
new iShortNameRace;				//MENU_SHORT_NAME_RACE - короткое или длинное название расы берущееся из cssbWar3ftMod.txt (0 - используются ключи RACE_, 1 - используются ключи RACE_S )

