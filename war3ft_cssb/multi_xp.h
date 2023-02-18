//Дефайны
#define	ON 1	//Включить
#define	OFF 0	//Выключить
#define	MAX_HOUR 24	//Максимальное колличество часов (сутки)

#define TASK_MULTIXP 332576

//Переменные
new bool:bDoubleXPActive = false;	//Активация двойного опыта
new iMultiXPOnOff;			//Включение/выключение получения мульти опыта	
new iBonusFactorXP;			//Во сколько раз увеличивать даваемый опыт

new Array:arrIntMultiXPHourData;			//Массив часов


//#define	BONUS_DOUBLE_XP get_pcvar_num( CVAR_wc3_bonus_xp )	//Во сколько раз увеличивать даваемый опыт

//Массивы
//Массив часов
new const LIST_TIME[MAX_HOUR] = 
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23
};
/*
//Массив часов (вкючение опыта)
new const LIST_TIME_XP[MAX_HOUR] = 
{
	ON,		//	0
	ON,		//	1
	ON,		//	2
	OFF,	//	3
	OFF,	//	4
	OFF,	//	5
	OFF,	//	6
	OFF,	//	7
	OFF,	//	8
	OFF,	//	9
	ON,		//	10
	ON,		//	11
	ON,		//	12
	ON,		//	13
	ON,		//	14
	ON,		//	15
	ON,		//	16
	ON,		//	17
	ON,		//	18
	ON,		//	19
	ON,		//	20
	ON,		//	21
	ON,		//	22
	ON		//	23
};
*/


