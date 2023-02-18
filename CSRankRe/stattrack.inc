#if defined _stattrack_included 
	#endinput
#endif

#define _stattrack_included 

#include <amxmodx>

/** Can we add kill to statrack */
stock bool:is_add_to_strack(id, csw) {
	new name[2][33];
	new wp_id = get_pdata_cbase(id, 373, 5);

	new item[ItemProperty], team = get_user_team2(id);
	get_player_weapon_skin(id, team, csw, item);

	if ( !csw ||
	 	!item[IP_ID] ||
		!get_player_strack(id, csw)) {
			return false;
	}

	get_user_name(id, name[0], 32);
	get_weapon_owner( wp_id, name[1], 32);

	if (!equali(name[0], name[1]) && strlen(name[1]) >= 2) {
		return false;
	}

	return true
}

stock get_player_strack(id, weaponid) {
	new item[ItemProperty], team = get_user_team2(id);
	get_player_weapon_skin(id, team, weaponid, item);

	return item[IP_STATTRACK];
}

stock add_player_strack(id, weapon_id) {
	new item[ItemProperty], team = get_user_team2(id);
	get_player_weapon_skin(id, team, weapon_id, item);

	item[IP_STATTRACK] ++;
	set_player_weapon_skin(id, team, weapon_id, item);
}
