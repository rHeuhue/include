/*
*	Race: Death knight Constants
*/

#define xs_1_neg(%1)				%1 = -%1
#define SURFACE_CHECK_NUM			5
#define ADDITIONAL_DIVIDER			2.0


//Класс (Race: Death knight (Рыцарь смерти) )
#define clRaceDeathKnight::		clRaceDeathKnight_

#define clRaceDeathKnight_setSkillsInit				_setSkillsInit
#define clRaceDeathKnight_skillDeathCoil			_skillDeathCoil
#define clRaceDeathKnight_skillUnbreakableArmor		_skillUnbreakableArmor
#define clRaceDeathKnight_setSurfaceEffect			_setSurfaceEffect
#define clRaceDeathKnight_getCorrectedOrigin		_getCorrectedOrigin
#define clRaceDeathKnight_checkWallInCycle			_checkWallInCycle
#define clRaceDeathKnight_checkWallInCycleDouble	_checkWallInCycleDouble
#define clRaceDeathKnight_checkWall					_checkWall
#define clRaceDeathKnight_getWallNormal				_getWallNormal
#define clRaceDeathKnight_getTraceToWall			_getTraceToWall
#define clRaceDeathKnight_skillBloodBoil			_skillBloodBoil
#define clRaceDeathKnight_setEffectDrawBloodBoil	_setEffectDrawBloodBoil
#define clRaceDeathKnight_ultBloodPresence			_ultBloodPresence
#define clRaceDeathKnight_setTaskRestoreBP			_setTaskRestoreBP
#define clRaceDeathKnight_setTaskBloodBoilSkill		_setTaskBloodBoilSkill

//Задачи
#define	clRaceDeathKnight_taskID_BLOOD_BOIL		96524		// Вскипание крови - Blood Boil
#define	clRaceDeathKnight_taskID_BLOOD_PRESENCE 894452		// Вскипание крови - Blood Boil

new bool:clRaceDeathKnight_bIsDamageBP[33];		// Если были нанесены повреждения здоровье и броня отниматься не будут
new bool:clRaceDeathKnight_bIsUnDamageBP[33];	// Получаемый урон от скилов врага уменьшается на 10%
