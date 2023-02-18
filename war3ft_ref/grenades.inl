


public FW_SetModel_Nades(ent, const model[])
{
	if (!pev_valid(ent))
		return FMRES_IGNORED;

	new id = pev(ent, pev_owner);

	if (!SHARED_ValidPlayer(id))
		return FMRES_IGNORED;
	
	// w_flashbang  , w_hegrenade , w_smokegrenade 


	// Change model only for orc critical grenade only if the skill is allowed 
	static iSkillLevel; 
	iSkillLevel = SM_GetSkillLevel(id, SKILL_CRITICALGRENADE);
	if (iSkillLevel > 0 && OR_CriticalGrenadeAllowed(id))
	{
		if (equal(model, "models/w_hegrenade.mdl"))
		{
			engfunc(EngFunc_SetModel, ent, W_MODEL_HE);
			return FMRES_SUPERCEDE;
		}
	}

	// Change model for every smoke 
	if (equal(model, "models/w_smokegrenade.mdl"))
	{
		engfunc(EngFunc_SetModel, ent, W_MODEL_SM);

		set_pev(ent, pev_iuser2, FROST_CODE);		// Set code for frost nade type detection 

		// And trail here but we already did using csx grenade throw 

		return FMRES_SUPERCEDE;
	}

	return FMRES_IGNORED;
}


public FW_Item_Deploy_HE(weapon_ent)
{
	static id; 
	id = fm_cs_get_weapon_ent_owner(weapon_ent);

	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel(id, SKILL_CRITICALGRENADE);


	if (!pev_valid(id))
		return

		if (iSkillLevel > 0 && OR_CriticalGrenadeAllowed(id))
		{
			set_pev(id, pev_viewmodel2, V_MODEL_HE);
		}
		
}


public FW_Item_Deploy_SM(weapon_ent)
{
	static id; 
	id = fm_cs_get_weapon_ent_owner(weapon_ent);

		if (!pev_valid(id)) return

			set_pev(id, pev_viewmodel2, V_MODEL_SM);
}



public FW_Touch_Nades(pfn, ptd)
{
	if (!pev_valid(pfn))
		return

		static Classname[32]; pev(pfn, pev_classname, Classname, sizeof(Classname))
		if (equal(Classname, "grenade"))
		{
			if (pev(pfn, pev_iuser2) != FROST_CODE)
				return

				Think_Cube(pfn);

				set_pev(pfn, pev_iuser2, 0);

				engfunc(EngFunc_RemoveEntity, pfn)
		}
}


Think_Cube(ent)
{
		// Get origin
		static Float:originF[3], Owner
		pev(ent, pev_origin, originF)
		Owner = pev(ent, pev_owner)


		Create_Boom(originF);
		
		// Fire nade explode sound
		emit_sound(ent, CHAN_WEAPON, g_szSounds[SOUND_BITE], 1.0, ATTN_NORM, 0, PITCH_NORM );

		static Float:PlayerOrigin[3]
		for (new i = 0; i < get_maxplayers(); i++)
		{
			if (!is_user_alive(i))
				continue
				
				if (cs_get_user_team(i) == cs_get_user_team(Owner))
					continue
					
					pev(i, pev_origin, PlayerOrigin);
					
					if (get_distance_f(originF, PlayerOrigin) > FROST_RADIUS)
						continue

						if (!is_user_connected(Owner)) Owner = i
						
						static iSkillLevel;
						iSkillLevel = SM_GetSkillLevel( i, SKILL_HIDES );
						if ( iSkillLevel > 0 )
						{   
							if ( random_float( 0.0, 1.0 ) <= p_hides[iSkillLevel-1] )
								{
									
									client_print( i, print_chat, "%s You have blocked a grenade.", GAME_NAME );
									
								}
						}
						else
						{
						
							Frozen_Cube(i, 1);

							emit_sound(i, CHAN_BODY, g_szSounds[SOUND_IMPALE], 1.0, ATTN_NORM, 0, PITCH_NORM );

							Create_ScreenFade( i, (1<<10), (1<<10), (1<<12), 0, 100, 200, 150 );
							Create_ScreenShake( i, (1<<14), (1<<13), (1<<14) );
							
							set_task(FROST_DURATION, "Remove_Freeze", i)
						
						}					
		}
}


public Remove_Freeze(id)
{
	// Not alive or not frozen anymore
	if (!is_user_alive(id))
		return;
		
		Create_ScreenFade( id, (1<<10), (1<<10), (1<<12), 0, 100, 200, 150 );
		Create_ScreenShake( id, (1<<14), (1<<13), (1<<14) );

		Frozen_Cube(id, 0);

		// Broken glass sound
		emit_sound(id, CHAN_BODY, g_szSounds[SOUND_IMPALE], 1.0, ATTN_NORM, 0, PITCH_NORM );

		// Get player's origin
		static origin2[3]
		get_user_origin(id, origin2)

		// Glass Shatter
		message_begin(MSG_PVS, SVC_TEMPENTITY, origin2)
		write_byte(TE_BREAKMODEL) // TE id
		write_coord(origin2[0]) // x
		write_coord(origin2[1]) // y
		write_coord(origin2[2] + 25) // z
		write_coord(16) // size x
		write_coord(16) // size y
		write_coord(16) // size z
		write_coord(random_num(-50, 50)) // velocity x
		write_coord(random_num(-50, 50)) // velocity y
		write_coord(25) // velocity z
		write_byte(10) // random velocity
		write_short(GLASS_SPR) // model
		write_byte(10) // count
		write_byte(25) // life
		write_byte(0x01) // flags
		message_end()
}








stock Frozen_Cube(id, status)
{
	if (status)
	{
		static ent, Float:o[3]
			if (!is_user_alive(id))
			{
				Frozen_Cube(id, 0)
					return
			}

		if (is_valid_ent(IceBlockEnt[id]))
		{
			if (pev(IceBlockEnt[id], pev_iuser3) != id)
			{
				if (pev(IceBlockEnt[id], pev_team) == 6969) remove_entity(IceBlockEnt[id])
			}
			else
			{
				pev(id, pev_origin, o)
					if (pev(id, pev_flags) & FL_DUCKING) o[2] -= 15.0
					else o[2] -= 35.0
						entity_set_origin(IceBlockEnt[id], o)
						return
			}
		}

		pev(id, pev_origin, o)
			if (pev(id, pev_flags) & FL_DUCKING) o[2] -= 15.0
			else o[2] -= 35.0
				ent = create_entity("info_target")
				set_pev(ent, pev_classname, "FrozenCube")

				entity_set_model(ent, FROST_BLOCK_MODEL)
				dllfunc(DLLFunc_Spawn, ent)
				set_pev(ent, pev_solid, SOLID_BBOX)
				set_pev(ent, pev_movetype, MOVETYPE_FLY)
				entity_set_origin(ent, o)
				
				new Float:mins[3] = { -3.0, -3.0, -3.0 };
				new Float:maxs[3] = { 3.0, 3.0, 3.0 };
				entity_set_size(ent,mins,maxs)
				
				//entity_set_size(ent, Float:mins{ -3.0, -3.0, -3.0 }, Float : { 3.0, 3.0, 3.0 })
				set_pev(ent, pev_iuser3, id)
				set_pev(ent, pev_team, 6969)
				set_rendering(ent, kRenderFxNone, 0, 100, 200, kRenderTransAdd, 200)
				IceBlockEnt[id] = ent
	}
	else
	{
		if (is_valid_ent(IceBlockEnt[id]))
		{
			if (pev(IceBlockEnt[id], pev_team) == 6969) remove_entity(IceBlockEnt[id])
				IceBlockEnt[id] = -1
		}
	}
}



stock fm_cs_get_weapon_ent_owner(ent)
{
	if (pev_valid(ent) != 2)
		return -1

		return get_pdata_cbase(ent, 41, 4)
}



Create_Boom(const Float:originF[3])
{
    engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, originF, 0)
    write_byte(TE_BEAMCYLINDER) // TE id
    engfunc(EngFunc_WriteCoord, originF[0]) // x
    engfunc(EngFunc_WriteCoord, originF[1]) // y
    engfunc(EngFunc_WriteCoord, originF[2]) // z
    engfunc(EngFunc_WriteCoord, originF[0]) // x axis
    engfunc(EngFunc_WriteCoord, originF[1]) // y axis
    engfunc(EngFunc_WriteCoord, originF[2]+FROST_RADIUS) // z axis
    write_short(g_iSprites[SPR_NEW_TRAIL]) // sprite
    write_byte(0) // startframe
    write_byte(0) // framerate
    write_byte(10) // life
    write_byte(60) // width
    write_byte(0) // noise
    write_byte(0) // red
    write_byte(100) // green
    write_byte(200) // blue
    write_byte(200) // brightness
    write_byte(0) // speed
    message_end()
    
    engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, originF, 0)
    write_byte(TE_DLIGHT) // TE id
    engfunc(EngFunc_WriteCoord, originF[0]) // x
    engfunc(EngFunc_WriteCoord, originF[1]) // y
    engfunc(EngFunc_WriteCoord, originF[2]) // z
    write_byte(50) // radio
    write_byte(0) // red
    write_byte(100) // green
    write_byte(200) // blue
    write_byte(30) // 
    write_byte(30) // 
    message_end()

    engfunc(EngFunc_MessageBegin, MSG_BROADCAST,SVC_TEMPENTITY, originF, 0)
    write_byte(TE_EXPLOSION)
    engfunc(EngFunc_WriteCoord, originF[0]) // x axis
    engfunc(EngFunc_WriteCoord, originF[1]) // y axis
    engfunc(EngFunc_WriteCoord, originF[2]+50) // z axis
    write_short(g_iSprites[SPR_FROSTEXP])
    write_byte(17)
    write_byte(15)
    write_byte(TE_EXPLFLAG_NOSOUND)
    message_end();
    
 
}

