// ******************************************************************
// Логирование
// ******************************************************************

#define MODE_LOG 0		//Включает режим при котором будет выводиться в чат различная информация

#define LOG_SKILL_CRITICALSTRIKE 0		//Critical Strike
#define LOG_SKILL_CRITICALGRENADE 0		//Critical Grenade

#define LOG_SKILL_THORNS 0				//Шипастая аура (Thorns Aura)
#define LOG_SKILL_TRUESHOT 0			//Аура правдивости (Trueshot Aura)
#define LOG_PASS_RESISTANTSKIN 0		//Шипованная кожа (Resistant Skin)
#define LOG_SKILL_SPIKEDCARAPACE 0		//Шипованная броня
#define LOG_SKILL_BLOOD_BOIL 0			//Unbreakable Armor - Несокрушимая броня
#define LOG_SKILL_DEATH_COIL 0			//Лик смерти




#if MODE_LOG

//Класс clLog
#define clLog:		clLog_

#define clLog_logMagicDamage				_Log_ID_1
#define clLog_logRaceUndead					_Log_ID_2
#define clLog_logRaceOrc					_Log_ID_3
#define clLog_logRaceElf					_Log_ID_4
#define clLog_logRaceBlood					_Log_ID_5
#define clLog_logRaceCrypt					_Log_ID_6
#define clLog_logRaceDeathKnight			_Log_ID_7
#define clLog_logRaceDeathKnight2			_Log_ID_8


#endif
