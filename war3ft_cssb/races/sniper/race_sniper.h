// ******************************************************************
// Раса: Снайпер (Race: Sniper) Constants
// ******************************************************************

//Класс Снайпер (Race: Sniper )
#define clSniper::		clSniper_


#define clSniper_setSkillsInit					_Sniper_ID_1
#define clSniper_skillHeadshot					_Sniper_ID_2
#define clSniper_skillElephantGun				_Sniper_ID_3
#define clSniper_fShowMenuAWP					_Sniper_ID_4
#define clSniper_fStripGuns						_Sniper_ID_5
#define clSniper_skillPhaseBoots				_Sniper_ID_6
#define clSniper_ultShrapnel					_Sniper_ID_7
#define clSniper_fCreateShrapnel				_Sniper_ID_8


#define SHRAPNEL_SNIPER_CLASSNAME "s_shrapnel"



new iSniperHeadshotRadius;			//SNIPER_HEADSHOT_RADIUS - Радиус поражения при срабатывании скила "Выстрел в голову"
new iSniperHeadshotDmg;				//SNIPER_HEADSHOT_DMG - Дамаг при срабатывании скила "Выстрел в голову"
new iShrapnelDmg;					//SNIPER_SHRAPNEL_DMG - Дамаг от шрапнели при попадании по врагу
new iShrapnelDmgExp;				//SNIPER_SHRAPNEL_DMG_EXP - Дамаг от шрапнели при взрыве
new Float:fShrapnelExpRadius;		//SNIPER_SHRAPNEL_EXP_RADIUS - Радиус взрыва шрапнели
new iShrapnelNumJump;				//SNIPER_SHRAPNEL_NUM_JUMP - Количество отскоков шрапнели от поверхности,после чего взрывается
new iRoundCountAwp;					//SNIPER_ROUNDCOUNT_AWP - Раунд после которого возможность получить AWP
