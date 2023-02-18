#if defined _chance_included 
	#endinput
#endif

#define _chance_included 

#include <amxmodx>

const CHANCE_CLASS_LEGENDARY = 3;
const CHANCE_CLASS_RARE = 2;
const CHANCE_CLASS_NORMAL = 1;

const CHANCE_DROP_COINS = 0;
const CHANCE_DROP_CASE = 1;
const CHANCE_DROP_KEY = 2;

/**
	Генерирует шанс на выпадения опеределенного класса оружия
 */
stock Chance_GenerateSkin(&chance) {
	new legendaryChance = get_pcvar_num(g_Cvars[CVAR_CHANCE_LEGENDARY]);
	new RareChance = get_pcvar_num(g_Cvars[CVAR_CHANCE_RARE]);

	chance = random_num(1, 100);

	if ( chance <= random_num(1, legendaryChance) ) {
		return CHANCE_CLASS_LEGENDARY;
	}

	if ( chance <= random_num(1, RareChance) ) {
		return CHANCE_CLASS_RARE;
	}

	return CHANCE_CLASS_NORMAL;
}

/**
	Генерирует шанс на дроп по времени
 */
stock Chance_GenerateDrop( &chance ) {
	chance = random_num(1, 100);

	if ( chance <= get_pcvar_num(g_Cvars[CVAR_CHANCE_DROP_KEY]) ) {
		return CHANCE_DROP_KEY;
	}

	if ( chance <= get_pcvar_num(g_Cvars[CVAR_CHANCE_DROP_CASE]) ) {
		return CHANCE_DROP_CASE;
	}

	return CHANCE_DROP_COINS;
}

stock CalculateDropTimeChance() {
	return random_num( 1, get_pcvar_num(g_Cvars[CVAR_CHANCE_ITEM_TIME]));
}
