#if defined _weapon_models_api_included
  #endinput
#endif
#define _weapon_models_api_included

#if AMXX_VERSION_NUM >= 175
	#pragma reqlib weapon_models_api
	#if !defined AMXMODX_NOAUTOLOAD
		#pragma loadlib weapon_models_api
	#endif
#else
	#pragma library weapon_models_api
#endif

enum
{
	ADD_BY_WEAPONBOX,
	ADD_BY_ARMORY_ENTITY,
	ADD_BY_BUYZONE
}

/**
 * Called when weapon deployed.
 * 
 * @param id					Player index.
 * @param weapon				Weapon entity index.
 * @param weaponid				CSW_ const.
 */
forward cs_weapon_deploy(id, weapon, weaponid);

/**
 * Called when weapon holstered.
 * 
 * @param id					Player index.
 * @param weapon				Weapon entity index.
 * @param weaponid				CSW_ const.
 */
forward cs_weapon_holster(id, weapon, weaponid);

/**
 * Called when weapon droped.
 * Forward should return 1 if weaponbox model changed
 * 
 * @param id					Player index.
 * @param weaponbox				Weaponbox entity index.
 * @param weapon				Weapon entity index.
 * @param weaponid				CSW_ const.
 */
forward cs_weapon_drop(id, weaponbox, weapon, weaponid);

/**
 * Called when weapon added to player.
 * 
 * @param id					Player index.
 * @param weapon				Weapon entity index.
 * @param weaponid				CSW_ const.
 * @param type					Add type.
 */
forward cs_weapon_add_to_player(id, weapon, weaponid, type);
