/*
#if defined _cs_player_models_api_included
  #endinput
#endif
#define _cs_player_models_api_included

#if AMXX_VERSION_NUM >= 175
	#pragma reqlib cs_player_models_api
	#if !defined AMXMODX_NOAUTOLOAD
		#pragma loadlib cs_player_models_api
	#endif
#else
	#pragma library cs_player_models_api
#endif
*/


// Delay between model changes (increase if getting SVC_BAD kicks)
#define MODELCHANGE_DELAY 0.2

// Delay after roundstart (increase if getting kicks at round start)
#define ROUNDSTART_DELAY 2.0

// Enable custom hitboxes (experimental, might lag your server badly with some models)
//#define SET_MODELINDEX_OFFSET

#define MAX_PLAYERS 32
#define MODELNAME_MAXLENGTH 32

#define TASK_MODELCHANGE 100
#define ID_MODELCHANGE (idTask - TASK_MODELCHANGE)

//new const DEFAULT_MODELINDEX_T[] = "models/player/terror/terror.mdl"
//new const DEFAULT_MODELINDEX_CT[] = "models/player/urban/urban.mdl"

// CS Player PData Offsets (win32)
#define PDATA_SAFE 2
#define OFFSET_CSTEAMS 114
#define OFFSET_MODELINDEX 491 // Orangutanz

#define flag_get(%1,%2)		(%1 & (1 << (%2 & 31)))
#define flag_set(%1,%2)		(%1 |= (1 << (%2 & 31)))
#define flag_unset(%1,%2)	(%1 &= ~(1 << (%2 & 31)))

new iHasCustomModel;
new Float:fModelChangeTargetTime;
new arrCustomPlayerModel[MAX_PLAYERS+1][MODELNAME_MAXLENGTH];

/*
#if defined SET_MODELINDEX_OFFSET
new arrCustomModelIndex[MAX_PLAYERS+1]
#endif
*/


/**
 * Установка игроку модели.
 *
 * @param id			Идентификатор игрока
 * @param model			Устанавливливаемая модель игрока по короткому названию файла 
 */
native cssbSetPlayerModel(idUser, const szNewModel[])

/**
 * Сброс модели игрока, которая идет по умолчанию.
 *
 * @param id		Идентификатор игрока
 */
native cssbResetPlayerModel(idUser)


//precache_model("models/player/cr0w/cr0w.mdl")
//cs_set_player_model(id, "cr0w")  
