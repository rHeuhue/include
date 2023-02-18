#if defined _core_exp_included
	#endinput
#endif

#define _core_exp_included

#include <amxmodx>

enum _:CoreExpForwards 
{
	COREEXP_EXP_UP = 0,

	COREEXP_LEVEL_UP,
	COREEXP_MEDAL_UP
}

new g_coreExp_forwards[CoreExpForwards];
new Array:g_coreExp_level_array;

stock CoreExp_Init() {

	/** id | exp_to_add */
	g_coreExp_forwards[COREEXP_EXP_UP] = CreateMultiForward("csrank_coreexp_exp_up", ET_CONTINUE, FP_CELL, FP_CELL)

	/** id | current_level | max_level */
	g_coreExp_forwards[COREEXP_LEVEL_UP] = CreateMultiForward("csrank_coreexp_level_up", ET_CONTINUE, FP_CELL, FP_CELL, FP_CELL)

	/** id | current_medal(s) */
	g_coreExp_forwards[COREEXP_MEDAL_UP] = CreateMultiForward("csrank_coreexp_medal_up", ET_CONTINUE, FP_CELL, FP_CELL)

	g_coreExp_level_array = ArrayCreate();
	CoreExp_ReadLevelsFromCvars()

}
stock CoreExp_end() {
	ArrayDestroy(g_coreExp_level_array)
}

/**
    При убийстве
 */
stock CoreExp_kill(iKiller, bool:hs = false)
{
	static expgive_kill = 0; 	CoreExp_get_num_cvar(expgive_kill, 	g_Cvars[CVAR_EXP_KILL]);
	static expgive_vip = 0;		CoreExp_get_num_cvar(expgive_vip, 	g_Cvars[CVAR_VIP_EXP]);
	static expgive_head = 0;	CoreExp_get_num_cvar(expgive_head, 	g_Cvars[CVAR_EXP_HEAD]);

	// Для вывода инфы о том, сколько игрок убил до своей смерти
	g_user_kills[iKiller] += 1;
	
	// Добавляем опыт
	new exp_to_give = expgive_kill;

	new name[33]; get_user_name(iKiller, name, 32);

	if( check_player_vip(iKiller) )			exp_to_give += expgive_vip;
	if(hs)							exp_to_give += expgive_head;		

	// Обновляем опыт игрока
	CoreExp_ExpUpdate( iKiller, exp_to_give, true, false)
}

/** 
	@desc Read Level Array from cfg
	@option csrank_level_exp | cvar_name
	@option 100 200 400 700 1000 1500 2100 2800 3600 4500 | default values

	@return void
 */
public CoreExp_ReadLevelsFromCvars( ) {
	new sLevel[256];
	get_pcvar_string(g_Cvars[CVAR_LEVEL_EXP], sLevel, charsmax(sLevel))
	
	new expPerLevel[16];
	while( strlen(sLevel) > 0 )
	{
		argbreak(sLevel, expPerLevel, charsmax(expPerLevel), sLevel, charsmax(sLevel))
		ArrayPushCell(g_coreExp_level_array, str_to_num(expPerLevel));
	}
	
	PrintMessage("Load %d level(s) from config", ArraySize(g_coreExp_level_array)-1);
}

/**
	@param bool set | set for current value
 */
public CoreExp_ExpUpdate(id, exp, bool:sound, bool:set) {

	if (set) {
		return CoreExp_set_player_exp(id, exp)
	}

	new ret;
	ExecuteForward(g_coreExp_forwards[COREEXP_EXP_UP], ret, id, exp)

	// Если exp = 0, то мы п
	if (exp && ret) {
		exp += ret
	}

	CoreExp_set_player_exp(id, CoreExp_get_player_exp(id) + exp);
	g_player_stats[id][PS_EXP_TOTAL] += exp

	return CoreExp_LevelUpdate(id, sound);
}

public CoreExp_LevelUpdate( id, bool:sound ) {

	new curr_level = g_player_stats[id][PS_LEVEL];
	new size = ArraySize(g_coreExp_level_array) - 1;

	while( CoreExp_get_player_exp(id) >= ArrayGetCell(g_coreExp_level_array, curr_level) && curr_level < size  )
	{
		curr_level++;
		
		if(sound)
		{
			Print(id, "%L", id, "CSRE_LEVEL_UP", curr_level)
			GiveItem(id, false, false)

			emit_sound(id, CHAN_AUTO, g_szSoundLevelUp, VOL_NORM, ATTN_NORM, 0, PITCH_NORM);

			// Forward for level up
			new ret;
			ExecuteForward(g_coreExp_forwards[COREEXP_LEVEL_UP], ret, id, curr_level, size)
		}
	}

	// Уровень обновляется здесь
	g_player_stats[id][PS_LEVEL] = curr_level;
	return CoreExp_MedalUpdate(id, curr_level)
}

public CoreExp_MedalUpdate(id, curr_level) {
	new size = ArraySize(g_coreExp_level_array) - 1;
	
	if ( CoreExp_get_player_exp(id) < ArrayGetCell(g_coreExp_level_array, size)) {
		// Если нехватает опыта до медали
		return 1;
	}

	// обнуляем опыт игрока, без вызова других update
	const EMPTY_EXP = 0
	CoreExp_ExpUpdate(id, EMPTY_EXP, false, true)

	g_player_stats[id][PS_LEVEL] = 0;
	Stats_AddPlayerMedals(id, 1)

	new keys = get_pcvar_num(g_Cvars[CVAR_MEDAL_KEYS])

	if (keys > 0) Stats_AddPlayerKeys(id, keys)

	emit_sound(id, CHAN_AUTO, g_szSoundMedalUp, VOL_NORM, ATTN_NORM, 0, PITCH_NORM);
		
	// Forward for take medal
	new ret;
	ExecuteForward(g_coreExp_forwards[COREEXP_MEDAL_UP], ret, id, g_player_stats[id][PS_MEDALS])
	return 1;
}


stock CoreExp_get_num_cvar( &var, cvar_id) {
	if ( !var )	var = get_pcvar_num(cvar_id)

	return var
}

/** return current exp of player */
public CoreExp_get_player_exp(id) {
	return g_player_stats[id][PS_EXP];
}

/** Set current exp for player */
public CoreExp_set_player_exp(id, exp) {
	g_player_stats[id][PS_EXP] = exp;
	return 1;
}

/** Возвращает максимальный уровень */
public CoreExp_get_max_level() { 
	static size = 0; 
	
	if ( !size )
		size = ArraySize(g_coreExp_level_array);

	return size;
}

public CoreExp_set_level_from_exp(id) {
	return CoreExp_LevelUpdate(id, false)
}

public CoreExp_get_next_level(exp)
{
	new iExp = 0;
	new size = CoreExp_get_max_level()
	for(new iLevel = 0; iLevel < size; iLevel++) {
		iExp = ArrayGetCell(g_coreExp_level_array, iLevel);

		if ( exp < iExp) break;
	}
	
	return iExp;
}