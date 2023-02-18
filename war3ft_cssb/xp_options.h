
new const WAR3FT_CUSTOM_FILE_XP[] = "war3ft/options/xp.ini"

// Секции файла настроек xp.ini
enum
{
	SECTION_NONE = 0,
	SECTION_XP_AWARDED,
	SECTION_XP_SAVE,
	SECTION_XP_KILL_SAVE
};

//Переменные
//Опыт за начало разминирования бомбы (XP awarded when the user starts to defuse the bomb)
new iDefusingBomb;
//Опыт за разминирование бомбы (XP awarded when the user defuses the bomb)
new iDefusedBomb;
//Опыт за начало установки бомбы (XP awarded when the user starts planting the bomb)
new iPlantingBomb;
//Опыт за установку бомбы (XP awarded when the user plants the bomb)
new iPlantBomb;
//Опыт за респ с бомбой (XP awarded when the user spawns with the bomb)
new iSpawnBomb;
//Опыт за подбор бомбы (XP awarded when the user picks up the bomb)
new iBombPickup;
//Опыт за прикосновение к заложнику ( XP awarded when the user touches a hostage)
new iTouchHostage;
//Опыт за спасение заложника (XP awarded when the user rescues the hostage)
new iRescueHostage;
//Отнимаемый опыт за убийство заложника (XP lost when killing a hostage)
new iKillHostage;
//Опыт за респ как VIP (XP awarded for spawning as the VIP)
new iSpawnVip;
//Опыт за побег как VIP ( XP awarded for escaping as the VIP)
new iEscapeVip;
//Опыт за убийство в голову (XP awarded for getting a headshot)
new iKillHeadshot;
//Опыт за убийство сопровождающего заложников (XP awarded for killing the hostage saver)
new iKillHostageSaver;
//Опыт за убийство сапера (XP awarded for killing the defuser)
new iKillDefuser;
//Опыт за убийство минера ( XP awarded for killing the planter)
new iKillPlanter;
//Опыт за убийство несущего бомбу (XP awarded for killing the bomb carrier)
new iKillBombCarrier;
//Опыт за убийство VIP (XP awarded for killing the VIP)
new iKillVip;
//Опыт за победу в раунде (XP awarded for winning the round)
new iWinRound;

//Массивы
//*******************************************************
//  Настройка опыта
//*******************************************************
new Array:arrXpSave;
new Array:arrXpKillSave;