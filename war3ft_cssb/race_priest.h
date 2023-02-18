/*
*	Race: Priest Constants
*/


//Класс (Race: Priest (Жрец) )
#define clRacePriest::		clRacePriest_

#define clRacePriest_setPriestSkillsInit		_setPriestSkillsInit
#define clRacePriest_skillEntryInChasm			_skillEntryInChasm
#define clRacePriest_skillSpAccuracy			_skillSpiritualAccuracy
#define clRacePriest_ultDarkWordDeath			_ultDarkWordDeath
#define clRacePriest_setTaskResetSPA			_setTaskResetSPA
#define clRacePriest_stBubbles					_stBubbles
#define clRacePriest_stGetPos					_stGetPos
#define clRacePriest_fStopUlt					_fStopUlt
#define clRacePriest_fSetFireAttack				_fSetFireAttack
#define clRacePriest_fCreateFireball			_fCreateFireball
#define clRacePriest_fBurning					_fBurning
#define clRacePriest_stScreenFadePriest			_stScreenFadePriest
#define clRacePriest_stShakeScreenPriest		_stShakeScreenPriest


#define FLAME_DURATION args[0]
#define FLAME_ATTACKER args[1]

const OFFSET_LINUX_WEAPONS = 4; // weapon offsets are only 4 steps higher on Linux
const OFFSET_iWeapId = 43;
const OFFSET_iClipAmmo = 51;

new const WEAPON_CLASSNAME[][] = { "", "weapon_p228", "", "weapon_scout", "", "weapon_xm1014", "", "weapon_mac10",
	"weapon_aug", "", "weapon_elite", "weapon_fiveseven", "weapon_ump45", "weapon_sg550", "weapon_galil", "weapon_famas",
	"weapon_usp", "weapon_glock18", "weapon_awp", "weapon_mp5navy", "weapon_m249", "weapon_m3", "weapon_m4a1",
	"weapon_tmp", "weapon_g3sg1", "", "weapon_deagle", "weapon_sg552", "weapon_ak47", "weapon_knife", "weapon_p90" }

new arrFireWeapon[33];				//Массив количества зарядов огненных пуль
new bool:arrIsWorkFireWeapon[33];	//Массив если сработал скилл,тогда удаляем один заряд
new bool:arrIsEffectBubble[33];		//Массив если сработал скилл Духовная меткость (Spiritual accuracy). Нужен для отрисоыки пузырьков


new Float:fEntryFrequency;
new Float:fFireDuration;
new Float:fFireDamage;
new Float:fFireSlowdown, iFireNumAmmo;
new Float:fBallExpRadius;
new iWordDeathDmg;
new Float:fBlockUltRadius;

//Задачи
#define	clRacePriest_tID_SP_ACCURACY		2457854		// Вскипание крови - Blood Boil
#define	clRacePriest_tID_FIRE_ATTACK		9654252		// Запуск clRacePriest::fSetFireAttack(taskParm[4])
#define	clRacePriest_tID_REMOVE_ATTACK		9542154		// Запуск clRacePriest::fStopUlt(idUser)
#define	clRacePriest_tID_SACRED_FIRE		8924576		// 


