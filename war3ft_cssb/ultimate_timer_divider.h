


new const WAR3FT_ULTIMATE_RACES_FILE[] = "war3ft/ultimate/ultimate_races.ini"

// Секции файла настроек ultimate_races.ini
enum
{
	SECTION_NONE = 0,
	SECTION_ULTIMATE_RACES
}


#define RESET_ULTIMATE_TIMER get_pcvar_num( CVAR_wc3_reset_ultimate_timer )	//Во сколько раз супер навык будет заряжаться быстрее

new Array:arrIntUltimateTimer;

