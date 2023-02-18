// ******************************************************************
// Раса: Разрушитель (Race: Disruptor) Constants
// ******************************************************************

//Класс Разрушитель (Race: Disruptor )
#define clDisruptor::		clDisruptor_


#define clDisruptor_setSkillsInit					_Disruptor_ID_1
#define clDisruptor_skillGlimpse					_Disruptor_ID_2
#define clDisruptor_skillThunderStrike				_Disruptor_ID_3
#define clDisruptor_getIdFindNextVictim				_Disruptor_ID_4
#define clDisruptor_skillKineticField				_Disruptor_ID_5
//#define clDisruptor_fCreateKineticField				_Disruptor_ID_6
#define clDisruptor_ultStaticStorm					_Disruptor_ID_7
#define clDisruptor_fCreateStaticStorm				_Disruptor_ID_8


#define STATIC_STORM_DISRUPTOR_CLASSNAME "d_static_storm"
#define KINETIC_FIELD_DISRUPTOR_CLASSNAME "d_kinetic_field"

#define	clDisruptor_tID_KINETIC_FIELD		8963241
#define clDisruptor_taskActiveKineticField	_taskActiveKineticField

new iDisruptorGlimpseDmg;				//DISRUPTOR_GLIMPSE_DMG - Дамаг от скила "Призрачный взгляд"
new iDisruptorThunderStrikeDmg_1;		//DISRUPTOR_THUNDERSTRIKE_DMG_1 - Дамаг первой цели от скила "Удар грома"
new iDisruptorThunderStrikeDmg_2;		//DISRUPTOR_THUNDERSTRIKE_DMG_2 - Дамаг второстепенной цели от скила "Удар грома"
new iDisruptorThunderStrikeRadius;		//DISRUPTOR_THUNDERSTRIKE_RADIUS - Радиус поражения второстепенной цели от скила "Удар грома"
new iDisruptorStaticStormDmg;			//DISRUPTOR_STATIC_STORM_DMG - Дамаг от супер навыка
new Float:fDisruptorStaticStormRadius;	//DISRUPTOR_STATIC_STORM_RADIUS - Радиус поражения от супер навыка взрывающимися осколками
