
stock bool:bIsUserRace(idUser,iRaceId)
{
	if(arrIntData[idUser][P_RACE] == iRaceId)
		return true;

	return false;
}


stock get_user_actualhealth(idUser)
{

	new health = clHP:getUserHealth(idUser);

	// Player has god mode
	if ( health > 1500 )
		return health - 2048;

	// Player will evade the next shot
	if ( health > 500 )
		return health - 1024;

	return health;
}

// Функция проверяющая доступ к shopmenu4
public fVipShop4()
{
    new szFlags[24];
    get_pcvar_string(CVAR_wc3_shopmenu4_flag, szFlags, 23 );

    return ( read_flags( szFlags ) );
}

// Функция проверяющая доступ к расе [Vip Race]
public fVipRace(const szFlagVip[])
{
   return ( read_flags( szFlagVip ) );
}

// Функция проверяющая доступ к бонусу XP
public fBonusXP()
{
    new szFlags[24];
    get_pcvar_string(CVAR_wc3_bonus_xp_flag, szFlags, 23 );

    return ( read_flags( szFlags ) );
}

// Функция проверяющая доступ к низким ценам
public fBuyItemCost()
{
    new szFlags[24];
    get_pcvar_string(CVAR_wc3_cost_vip_flag, szFlags, 23 );

    return ( read_flags( szFlags ) );
}

//Для shopmenu4
stock set_entity_rendering( ent, iRenderFx, iR, iG, iB, iRenderType, iAmmount )
{
	entity_set_int( ent, EV_INT_renderfx, iRenderFx );

	new Float:fRGB[3];
	fRGB[0] = float( iR );
	fRGB[1] = float( iG );
	fRGB[2] = float( iB );

	entity_set_vector( ent, EV_VEC_rendercolor, fRGB );
	entity_set_int( ent, EV_INT_rendermode, iRenderType );

	new Float:fAmmount = float( iAmmount );

	entity_set_float( ent, EV_FL_renderamt, fAmmount );

	return ( 1 );
}

stock set_velocity_to_ent( ent1, ent2, Float:fSpeed )
{
	new Float:fOrigin[3], Float:fVelocity[3];

	entity_get_vector( ent2, EV_VEC_origin, fOrigin );
	get_velocity_to_origin( ent1, fOrigin, fSpeed, fVelocity );

	entity_set_vector( ent1, EV_VEC_velocity, fVelocity );

	return ( 1 );
}

stock get_velocity_to_origin( ent, Float:fOrigin[3], Float:fSpeed, Float:fVelocity[3] )
{
	new Float:fEntOrigin[3];
	entity_get_vector( ent, EV_VEC_origin, fEntOrigin );

	// Velocity = Distance / Time
	new Float:fDistance[3];
	fDistance[0] = fOrigin[0] - fEntOrigin[0];
	fDistance[1] = fOrigin[1] - fEntOrigin[1];
	fDistance[2] = fOrigin[2] - fEntOrigin[2];

	new Float:fTime = ( vector_distance( fEntOrigin,fOrigin ) / fSpeed );

	fVelocity[0] = fDistance[0] / fTime;
	fVelocity[1] = fDistance[1] / fTime;
	fVelocity[2] = fDistance[2] / fTime;

	return ( fVelocity[0] && fVelocity[1] && fVelocity[2] );
}


stock get_entity_velocity( ent, velocity[3] )
{
	new Float:fVelocity[3];
	entity_get_vector( ent, EV_VEC_velocity, fVelocity );

	velocity[0] = floatround( fVelocity[0] );
	velocity[1] = floatround( fVelocity[1] );
	velocity[2] = floatround( fVelocity[2] );

	return ( velocity[0] && velocity[1] && velocity[2] );
}

stock set_entity_velocity( ent, velocity[3] )
{
	new Float:fVelocity[3];

	fVelocity[0] = float( velocity[0] );
	fVelocity[1] = float( velocity[1] );
	fVelocity[2] = float( velocity[2] );

	entity_set_vector( ent, EV_VEC_velocity, fVelocity );

	return ( 1 );
}


stock Remove_TE_BEAMFOLLOW(id)
{
	message_begin( MSG_ALL,SVC_TEMPENTITY );
	write_byte( TE_KILLBEAM );          // TE_KILLBEAM (99)
	write_short( id );                  // entity
	message_end();

	return PLUGIN_HANDLED;
}

// Sets maxspeed of an entity ( corrects issues with setting maxspeed on bots )
stock set_entity_maxspeed( ent, Float:fMaxSpeed ) 
{
	entity_set_float( ent, EV_FL_maxspeed, fMaxSpeed );
	return ( 1 );
}

stock fm_get_weaponid(entity)
{
	return get_pdata_int(entity, OFFSET_iWeapId, OFFSET_LINUX_WEAPONS);
}

stock fm_get_weapon_ammo(entity)
{
	return get_pdata_int(entity, OFFSET_iClipAmmo, OFFSET_LINUX_WEAPONS);
}

stock Float:tlx_distance_to_sky(id) // Получить координаты до неба от сущности (игрока)
{
	new Float:TraceEnd[3];
	pev(id, pev_origin, TraceEnd);

	new Float:f_dest[3];
	f_dest[0] = TraceEnd[0];
	f_dest[1] = TraceEnd[1];
	f_dest[2] = TraceEnd[2] + 8192.0;

	new res, Float:SkyOrigin[3];
	engfunc(EngFunc_TraceLine, TraceEnd, f_dest, IGNORE_MONSTERS + IGNORE_GLASS, id, res);
	get_tr2(res, TR_vecEndPos, SkyOrigin);

	return SkyOrigin;
}
//return distance above us to sky
stock Float:is_user_outside(id) 
{
	new Float:origin[3], Float:dist

	pev(id, pev_origin, origin)
	dist = origin[2]

	while(engfunc(EngFunc_PointContents, origin) == CONTENTS_EMPTY)
		origin[2] += 5.0 
	if(engfunc(EngFunc_PointContents, origin) == CONTENTS_SKY)
		return (origin[2] - dist)

	return 0.0
}

stock bool:is_user_steam(id)
{
	if(is_user_bot(id)) return false;
	static dp_pointer
	if(dp_pointer || (dp_pointer = get_cvar_pointer("dp_r_id_provider")))
	{
		server_cmd("dp_clientinfo %d", id)
		server_exec()
		return (get_pcvar_num(dp_pointer) == 2) ? true : false
	}
	
	new auth[60]
	get_user_authid(id, auth, charsmax(auth))
	return (containi(auth, "LAN") < 0)
}


//Брызги крови в лицо
stock stockTraceBlood(id, iScale)
{
	new Float:start[3], Float:view_ofs[3], Float:end[3]
	pev(id, pev_origin, start)
	pev(id, pev_view_ofs, view_ofs)
	xs_vec_add(start, view_ofs, start)
	
	pev(id, pev_v_angle, end)
	engfunc(EngFunc_MakeVectors, end)
	global_get(glb_v_forward, end)
	xs_vec_mul_scalar(end, 8120.0, end)
	xs_vec_add(start, end, end)
	new ptr = create_tr2();
	engfunc(EngFunc_TraceLine, start, end, DONT_IGNORE_MONSTERS, id, ptr)
	get_tr2(ptr, TR_vecEndPos, end)
	free_tr2(ptr)

	engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, end, 0);
	write_byte(TE_BLOODSPRITE)
	engfunc(EngFunc_WriteCoord,end[0])
	engfunc(EngFunc_WriteCoord,end[1])
	engfunc(EngFunc_WriteCoord,end[2])
	write_short(arrIdSprites[SPR_BLOODSPRAY])
	write_short(arrIdSprites[SPR_BLOODDROP])
	write_byte(75)
	write_byte(iScale)
	message_end()
}

stock stGetSphericalCoord(const Float:ent_origin[3], Float:redius, Float:level_angle, Float:vertical_angle, Float:origin[3])
{
	new Float:length
	length  = redius * floatcos(vertical_angle, degrees)
	origin[0] = ent_origin[0] + length * floatcos(level_angle, degrees)
	origin[1] = ent_origin[1] + length * floatsin(level_angle, degrees)
	origin[2] = ent_origin[2] + redius * floatsin(vertical_angle, degrees)
}

/*
//Проверка если игрок сзади (нужно проверить)
stock Stock_Check_Back(iEnemy,id)
{
	new Float:anglea[3], Float:anglev[3]
	pev(iEnemy, pev_v_angle, anglea)
	pev(id, pev_v_angle, anglev)
	new Float:angle = anglea[1] - anglev[1] 
	if(angle < -180.0) angle += 360.0
	if(angle <= 60.0 && angle >= -60.0) return 1
	return 0
}

//Обычный разлет крови
stock Stock_TraceBlood2(id, id2, iScale)
{
	new Float:v1[3],Float:v2[3]
	pev(id,pev_origin,v1)
	pev(id2,pev_origin,v2)

	new Float:end[3]
	new ptr = create_tr2();
	engfunc(EngFunc_TraceLine, v1, v2, 1, -1, ptr)	
	get_tr2(ptr, TR_vecEndPos, end)

	engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, end, 0);
	write_byte(TE_BLOODSPRITE)
	engfunc(EngFunc_WriteCoord,end[0])
	engfunc(EngFunc_WriteCoord,end[1])
	engfunc(EngFunc_WriteCoord,end[2])
	write_short(arrIdSprites[SPR_BLOODSPRAY])
	write_short(arrIdSprites[SPR_BLOODDROP])
	write_byte(75)
	write_byte(iScale)
	message_end()
}



stock Stock_Set_Kvd(entity, const key[], const value[], const classname[])
{
	set_kvd(0, KV_ClassName, classname)
	set_kvd(0, KV_KeyName, key)
	set_kvd(0, KV_Value, value)
	set_kvd(0, KV_fHandled, 0)

	dllfunc(DLLFunc_KeyValue, entity, 0)
}

//Отличный взрыв салюта
stock Stock_FgLauncher_Effect(Float:vEntOrigin[3])
{
	static Float:vColor[5][3]
	new iEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "env_sprite"))
	
	new Float:vOrigin[3]	
	vOrigin[0] = vEntOrigin[0] + random_float(-35.0,35.0)
	vOrigin[1] = vEntOrigin[1] + random_float(-35.0,35.0)
	vOrigin[2] = vEntOrigin[2] + random_float(30.0,120.0)
	

	Stock_Set_Kvd(iEntity,"model","sprites/spark2.spr","cycle_sprite")
	Stock_Set_Kvd(iEntity,"framerate","29.0","cycle_sprite")
	set_pev(iEntity,pev_spawnflags,SF_SPRITE_ONCE)
	dllfunc(DLLFunc_Spawn,iEntity)

	set_pev(iEntity,pev_scale,0.9)
	//vColor[0] = vColor[1] = vColor[2] = 255.0
	
	vColor[0][0] = 92.0
	vColor[0][1] = 35.0
	vColor[0][2] = 78.0
	
	vColor[1][0] = 73.0
	vColor[1][1] = 101.0
	vColor[1][2] = 164.0
	
	vColor[2][0] = 30.0
	vColor[2][1] = 71.0
	vColor[2][2] = 31.0
	
	vColor[3][0] = 179.0
	vColor[3][1] = 63.0
	vColor[3][2] = 64.0
	
	vColor[4][0] = 229.0
	vColor[4][1] = 210.0
	vColor[4][2] = 118.0
	
	set_pev(iEntity,pev_rendercolor,vColor[random_num(0,4)])
	set_pev(iEntity, pev_rendermode, kRenderTransAdd)
	set_pev(iEntity, pev_renderamt, 254.0)
	set_pev(iEntity,pev_origin,vOrigin)	
	
	
	engfunc(EngFunc_RemoveEntity, iEntity)
	
	
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY)
	write_byte(TE_EXPLOSION)
	engfunc(EngFunc_WriteCoord, vOrigin[0])
	engfunc(EngFunc_WriteCoord, vOrigin[1])
	engfunc(EngFunc_WriteCoord, vOrigin[2])
	write_short(g_cache_fg_exp)
	write_byte(9)
	write_byte(29)
	write_byte(TE_EXPLFLAG_NOSOUND + TE_EXPLFLAG_NODLIGHTS)
	message_end()

}


stock GetDamageBody(body, Float:damage)
{
	switch (body)
	{
		case HIT_HEAD: damage *= 4.14
		case HIT_STOMACH: damage *= 1.25
		case HIT_LEFTLEG: damage *= 0.75
		case HIT_RIGHTLEG: damage *= 0.75
		default: damage *= 1.0
	}
	
	return floatround(damage);
}

stock Stock_Off_FlashLight(id)
{
	// Restore batteries for the next use
	set_pdata_int(id, OFFSET_FLASHLIGHT_BATTERY, 100, OFFSET_LINUX)
	
	// Check if flashlight is on
	if (pev(id, pev_effects) & EF_DIMLIGHT)
	{
		// Turn it off
		set_pev(id, pev_impulse, IMPULSE_FLASHLIGHT)
	}
	else
	{
		// Clear any stored flashlight impulse (bugfix)
		set_pev(id, pev_impulse, 0)
	}
	
	// Update flashlight HUD
	message_begin(MSG_ONE, get_user_msgid("Flashlight"), _, id)
	write_byte(0) // toggle
	write_byte(100) // battery
	message_end()
}

stock Str_Count(const str[], searchchar)
{
	new count, i, len = strlen(str)
	for (i = 0; i <= len; i++)
	{
		if(str[i] == searchchar)
			count++
	}
	return count
}


*/


stock ham_strip_weapon(id,weapon[])
{
	if(!equal(weapon,"weapon_",7) ) 
		return 0;
	
	new wId = get_weaponid(weapon)

	if(!wId) 
		return 0;
	
	new wEnt
	while( (wEnt = engfunc(EngFunc_FindEntityByString,wEnt,"classname",weapon) ) && pev(wEnt,pev_owner) != id)
	{}

	if(!wEnt) 
		return 0;
	
	if(get_user_weapon(id) == wId) 
		ExecuteHamB(Ham_Weapon_RetireWeapon,wEnt);
	
	if(!ExecuteHamB(Ham_RemovePlayerItem,id,wEnt) ) 
		return 0;

	ExecuteHamB(Ham_Item_Kill,wEnt);
	
	set_pev(id,pev_weapons,pev(id,pev_weapons) & ~(1<<wId) )
	
	return 1
}
/*
// Strip user weapons (from fakemeta_util)
stock fm_strip_user_weapons(id)
{
	static ent
	ent = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "player_weaponstrip"))
	if (!pev_valid(ent)) return;
	
	dllfunc(DLLFunc_Spawn, ent)
	dllfunc(DLLFunc_Use, ent, id)
	engfunc(EngFunc_RemoveEntity, ent)
}*/

// Drop primary/secondary weapons
stock drop_weapons(id, dropwhat)
{
	// Get user weapons
	static weapons[32], num, i, weaponid
	num = 0 // reset passed weapons count (bugfix)
	get_user_weapons(id, weapons, num)
	
	// Loop through them and drop primaries or secondaries
	for (i = 0; i < num; i++)
	{
		// Prevent re-indexing the array
		weaponid = weapons[i]
		
		if ((dropwhat == 1 && ((1<<weaponid) & PRIMARY_WEAPONS_BIT_SUM))|| 
			(dropwhat == 2 && ((1<<weaponid) & SECONDARY_WEAPONS_BIT_SUM)))
		{
			// Get weapon entity
			static wname[32], weapon_ent
			get_weaponname(weaponid, wname, charsmax(wname))
			weapon_ent = fm_find_ent_by_owner(-1, wname, id)
			
			// Hack: store weapon bpammo on PEV_ADDITIONAL_AMMO
			set_pev(weapon_ent, PEV_ADDITIONAL_AMMO, cs_get_user_bpammo(id, weaponid))

			// log_amx("Weapon drop: %s",wname);

			engclient_cmd(id, "drop", wname);

			if(pev_valid(weaponid) && weaponid != 29) 
				cs_set_user_bpammo(id, weaponid, 0)
		}
	}
}

stock getIdWeaponFromModels(const sxModelWpnBox[])
{
	//Нож
//	return CSW_KNIFE;

	//Пистолеты
	if(equal(sxModelWpnBox, "models/w_p228.mdl"))
		return CSW_P228;
	else if(equal(sxModelWpnBox, "models/w_elite.mdl"))
		return CSW_ELITE;
	else if(equal(sxModelWpnBox, "models/w_fiveseven.mdl"))
		return CSW_FIVESEVEN;
	else if(equal(sxModelWpnBox, "models/w_usp.mdl"))
		return CSW_USP;
	else if(equal(sxModelWpnBox, "models/w_glock18.mdl"))
		return CSW_GLOCK18;
	else if(equal(sxModelWpnBox, "models/w_deagle.mdl"))
		return CSW_DEAGLE;

	//Штурмовые винтовки (автоматы)
	else if(equal(sxModelWpnBox, "models/w_aug.mdl"))
		return CSW_AUG;
	else if(equal(sxModelWpnBox, "models/w_sg550.mdl"))
		return CSW_SG550;
	else if(equal(sxModelWpnBox, "models/w_galil.mdl"))
		return CSW_GALIL;
	else if(equal(sxModelWpnBox, "models/w_famas.mdl"))
		return CSW_FAMAS;
	else if(equal(sxModelWpnBox, "models/w_m4a1.mdl"))
		return CSW_M4A1;
	else if(equal(sxModelWpnBox, "models/w_ak47.mdl"))
		return CSW_AK47;

	//Пистолет-пулемет
	else if(equal(sxModelWpnBox, "models/w_mac10.mdl"))
		return CSW_MAC10;
	else if(equal(sxModelWpnBox, "models/w_ump45.mdl"))
		return CSW_UMP45;
	else if(equal(sxModelWpnBox, "models/w_tmp.mdl"))
		return CSW_TMP;
	else if(equal(sxModelWpnBox, "models/w_p90.mdl"))
		return CSW_P90;
	else if(equal(sxModelWpnBox, "models/w_mp5.mdl"))
		return CSW_MP5NAVY;

	//Пулемет
	else if(equal(sxModelWpnBox, "models/w_m249.mdl"))
		return CSW_M249;

	//Ружья
	else if(equal(sxModelWpnBox, "models/w_xm1014.mdl"))
		return CSW_XM1014;
	else if(equal(sxModelWpnBox, "models/w_m3.mdl"))
		return CSW_M3;

	//Снайперские винтовки
	else if(equal(sxModelWpnBox, "models/w_scout.mdl"))
		return CSW_SCOUT;
	else if(equal(sxModelWpnBox, "models/w_awp.mdl"))
		return CSW_AWP;
	else if(equal(sxModelWpnBox, "models/w_g3sg1.mdl"))
		return CSW_G3SG1;
	else if(equal(sxModelWpnBox, "models/w_sg552.mdl"))
		return CSW_SG552;

	//Гранаты
	//return CSW_HEGRENADE;
	//return CSW_SMOKEGRENADE;
	//return CSW_FLASHBANG;

	//Броня
	//if(equal(sxModelWpnBox, "models/w_shield.mdl"))
	//return CSW_VEST;
	//return CSW_VESTHELM;

	//C4 - бомба
	else if(equal(sxModelWpnBox, "models/w_backpack.mdl"))
		return CSW_C4;
	
	return -1;
}

// Удаление конкретного оружия у игрока по индексу или названию.
stock bool:stStripUserGun(idUser, idWeapon = 0, const szWeaponName[] = "") 
{
	new szEntWeaponClass[32];

	if (!idWeapon && szWeaponName[0])
		copy(szEntWeaponClass, charsmax(szEntWeaponClass), szWeaponName);
	else
	{
		new idCurrentWeaponUser = idWeapon, iClip, iAmmo;

		if (!idCurrentWeaponUser && !(idCurrentWeaponUser = get_user_weapon(idUser, iClip, iAmmo)))
			return false;
		
		get_weaponname(idCurrentWeaponUser, szEntWeaponClass, charsmax(szEntWeaponClass) );
	}

	new entFindWeapon = fm_find_ent_by_owner(-1, szEntWeaponClass, idUser);

	if (!entFindWeapon)
		return false;

	engclient_cmd(idUser, "drop", szEntWeaponClass);

	new entOwnerWeapon = pev(entFindWeapon, pev_owner);

	if (!entOwnerWeapon || entOwnerWeapon == idUser)
		return false;

	dllfunc(DLLFunc_Think, entOwnerWeapon);

	return true;
}