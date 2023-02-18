/*
*	Race: Priest (Жрец) Functions
*/

//Инициализация скилов Race: Priest (Жрец)
public clRacePriest::setPriestSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	// Set up the Skill Owners
	g_SkillOwner[SKILL_PRIEST_ENTRYINTOCHASM				]	= RACE_PRIEST;
	g_SkillOwner[SKILL_PRIEST_SACRED_FIRE					]	= RACE_PRIEST;
	g_SkillOwner[SKILL_PRIEST_SPIRITUAL_ACCURACY			]	= RACE_PRIEST;
	g_SkillOwner[ULTIMATE_PRIEST_DARKNESS_WORD_DEATH		]	= RACE_PRIEST;
	g_SkillOwner[PASS_PRIEST_MYSTICISM						]	= RACE_PRIEST;
	
	// Set up the skill types
	g_SkillType[SKILL_PRIEST_ENTRYINTOCHASM					]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_PRIEST_SACRED_FIRE					]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_PRIEST_SPIRITUAL_ACCURACY				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_PRIEST_DARKNESS_WORD_DEATH			]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_PRIEST_MYSTICISM						]	= SKILL_TYPE_PASSIVE;
	
	// Set up the skill order
	g_SkillOrder[SKILL_PRIEST_ENTRYINTOCHASM				]	= SKILL_POS_1;
	g_SkillOrder[SKILL_PRIEST_SACRED_FIRE					]	= SKILL_POS_2;
	g_SkillOrder[SKILL_PRIEST_SPIRITUAL_ACCURACY			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_PRIEST_DARKNESS_WORD_DEATH		]	= SKILL_POS_4;
	g_SkillOrder[PASS_PRIEST_MYSTICISM						]	= SKILL_POS_NONE;

}



// *******************************************************
// Скил 1 уровня - Entry into a chasm - Вхождение в бездну - защитный
// *******************************************************
public clRacePriest::skillEntryInChasm(idVictim,idAttacker)
{	
	if (!is_user_alive( idAttacker ) && !arrBoolData[idAttacker][PB_ISCONNECTED])
		return;

	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_PRIEST_ENTRYINTOCHASM);
	if(iSkillLevel > 0)
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_PRIEST_ENTRYINTOCHASM) == true)
			return;

		new Float:fEntryintochasm = ArrayGetCell(arrEntryintochasm,iSkillLevel-1);
		if (!arrBoolData[idAttacker][PB_HEXED] && 
			random_float(fPriestSkill1MinPercent,fPriestSkill1MaxPercent) <= fEntryintochasm && 
			arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
		{
			if(get_user_team(idVictim) != get_user_team(idAttacker) )
			{
				new iAttackerCurHealth = clHP:getUserHealth(idAttacker);
				new iVictimCurHealth = clHP:getUserHealth(idVictim);

				if(iVictimCurHealth > iAttackerCurHealth)
				{
					clHP:setUserHealth(idAttacker,iVictimCurHealth);
					clHP:setUserHealth(idVictim,iAttackerCurHealth);
				}
			}
			
		}
	}
}
// *******************************************************
// Скил 2 уровня - Sacred fire - Священный огонь - наступательный
// *******************************************************
public fwHamWeapPriAttack(idWeapon)
{
	if (!pev_valid(idWeapon))
		return HAM_IGNORED;

	static idOwner;
	idOwner = pev(idWeapon, pev_owner)

	if (!is_user_alive( idOwner ) && !arrBoolData[idOwner][PB_ISCONNECTED])
		return HAM_IGNORED;

	if (fm_get_weaponid(idWeapon) == CSW_KNIFE)
		return HAM_IGNORED;
	
	if (fm_get_weapon_ammo(idWeapon) > 0 && arrFireWeapon[idOwner] > 0 && arrIsWorkFireWeapon[idOwner] == true)
	{
		arrFireWeapon[idOwner] -= 1;
		arrIsWorkFireWeapon[idOwner] = false;
	}

	return HAM_IGNORED;
}

public fwHamTraceAttackPriest(idVictim, idAttacker, Float:fDamage, Float:fDirection[3], tracehandle, damage_type)
{
	//client_print(idAttacker,print_chat,"FA: %d",arrFireWeapon[idAttacker]);

	if (!is_user_alive( idAttacker ))
		return HAM_HANDLED;

	if (!is_user_alive( idVictim ))
		return HAM_HANDLED;

	if (!is_user_alive( idAttacker ) && !arrBoolData[idAttacker][PB_ISCONNECTED])
		return HAM_HANDLED;

	if (!is_user_alive( idVictim ) && !arrBoolData[idVictim][PB_ISCONNECTED])
		return HAM_HANDLED;


	if ((get_user_weapon(idAttacker) == CSW_KNIFE))
		return HAM_IGNORED;

	if ( (idVictim == idAttacker) || !is_user_connected(idAttacker) ||
		 (get_user_team(idVictim) == get_user_team(idAttacker)) 
	   )
		return HAM_HANDLED;

	if(arrIsEffectBubble[idAttacker] == true)
		clRacePriest::stBubbles(idAttacker);

	new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_PRIEST_SPIRITUAL_ACCURACY);
	if (iSkillLevel > 0 && isDisabledSkillsOnMap(idVictim,SKILL_PRIEST_SPIRITUAL_ACCURACY) == false) 
	{
		new Float:fSpiritual = ArrayGetCell(arrSpiritualAccuracy,iSkillLevel-1);
		if (is_user_alive( idVictim ) && arrBoolData[idVictim][PB_ISCONNECTED]&&
				random_float(fPriestSkill3MinPercent,fPriestSkill3MaxPercent) <= fSpiritual && 	
				arrBoolData[idAttacker][PB_ISFROZENSKILL] == false &&
				arrIsEffectBubble[idAttacker] == false)
		{
			clRacePriest::skillSpAccuracy(idVictim,idAttacker);
		}
	}

	if (!arrFireWeapon[idAttacker])
		return HAM_HANDLED;

	if (!(damage_type & DMG_BULLET))
		return HAM_HANDLED;

	iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_PRIEST_SACRED_FIRE);
	if (iSkillLevel > 0 && isDisabledSkillsOnMap(idAttacker,SKILL_PRIEST_SACRED_FIRE) == false)
	{
		new Float:fSacredfire = ArrayGetCell(arrSacredFire,iSkillLevel-1);
		if (is_user_alive( idAttacker ) && arrBoolData[idAttacker][PB_ISCONNECTED]&&
				random_float(fPriestSkill2MinPercent,fPriestSkill2MaxPercent) <= fSacredfire 	&& 	
				arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
		{

			fStartFire(idVictim, idAttacker);
			arrIsWorkFireWeapon[idAttacker] = true;
		}
	}


	return HAM_IGNORED;
}

fStartFire(idVictim, idAttacker)
{
	static params[3];
	params[0] = floatround(fFireDuration * 5.0); // duration
	params[1] = idAttacker; // attacker
	params[2] = idVictim + clRacePriest::tID_SACRED_FIRE;

	if (task_exists(idVictim + clRacePriest::tID_SACRED_FIRE ))
		return;

	set_task(0.2, "fBurningFlame",params[2], params, sizeof params);


}

public fBurningFlame(args[3])
{
	//client_print(0,print_chat,"fBurningFlame");

	new idUser = args[2];
	if (args[2] >= clRacePriest::tID_SACRED_FIRE )
		idUser -= clRacePriest::tID_SACRED_FIRE;

	if (!is_user_alive(idUser))
		return;

	static Float:originF[3]
	pev(idUser, pev_origin, originF)

	if ((pev(idUser, pev_flags) & FL_INWATER) || FLAME_DURATION < 1)
	{
		// Smoke sprite
		engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, originF, 0);
		write_byte(TE_SMOKE); // TE id
		engfunc(EngFunc_WriteCoord, originF[0]); // x
		engfunc(EngFunc_WriteCoord, originF[1]); // y
		engfunc(EngFunc_WriteCoord, originF[2]-50.0); // z
		write_short(arrIdSprites[SPR_SMOKE_PRIEST]); // sprite
		write_byte(random_num(15, 20)); // scale
		write_byte(random_num(10, 20)); // framerate
		message_end()
		
		return;
	}

	if ((pev(idUser, pev_flags) & FL_ONGROUND) && fFireSlowdown > 0.0)
	{
		static Float:velocity[3];
		pev(idUser, pev_velocity, velocity);
		xs_vec_mul_scalar(velocity, fFireSlowdown, velocity);
		set_pev(idUser, pev_velocity, velocity);
	}

	new health = clHP:getUserHealth(idUser);

	if (health > fFireDamage)
		clHP:setUserHealth(idUser,health - floatround(fFireDamage));
	else
		ExecuteHamB(Ham_Killed, idUser, FLAME_ATTACKER, 0);

	engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, originF, 0);
	write_byte(TE_SPRITE); // TE id
	engfunc(EngFunc_WriteCoord, originF[0]+random_float(-5.0, 5.0)); // x
	engfunc(EngFunc_WriteCoord, originF[1]+random_float(-5.0, 5.0)); // y
	engfunc(EngFunc_WriteCoord, originF[2]+random_float(-10.0, 10.0)); // z
	write_short(arrIdSprites[SPR_FIRE_PRIEST]); // sprite
	write_byte(random_num(5, 10)); // scale
	write_byte(200); // brightness
	message_end();
	
	// Decrease burning duration counter
	FLAME_DURATION -= 1;

	new Float:firl_time
	if (0.2 > fFireDuration)
		firl_time = fFireDuration - 0.1;
	else
		firl_time = 0.2;

	set_task(firl_time, "fBurningFlame", args[2], args, sizeof args);
}

// *******************************************************
// Скил 3 уровня - Духовная меткость - Spiritual accuracy - защитный
// *******************************************************
public clRacePriest::skillSpAccuracy(idVictim,idAttacker)
{	
	if(!arrBoolData[idAttacker][PB_ISCONNECTED])
		return 0;

	clRacePriest::stBubbles(idAttacker);
	
	if (task_exists(idAttacker + clRacePriest::tID_SP_ACCURACY ) == 0 )
	{
		set_user_hitzones(idAttacker, 0, 0); //Делаем холостые выстрелы

		arrIsEffectBubble[idAttacker] = true;

		set_task(0.7, "_setTaskResetSPA", clRacePriest::tID_SP_ACCURACY + idAttacker );
	}

	return 0;
}

public clRacePriest::setTaskResetSPA(idAttacker)
{
	if (idAttacker >= clRacePriest::tID_SP_ACCURACY )
		idAttacker -= clRacePriest::tID_SP_ACCURACY;

	if(!arrBoolData[idAttacker][PB_ISCONNECTED])
		return;

	set_user_hitzones(idAttacker, 0, 255);	// Восстанавливаем нормальный режим стрельбы
	arrIsEffectBubble[idAttacker] = false;
}

stock clRacePriest::stBubbles(idAttacker)
{
	new ptPlayerOrigin[3], ptBulletOrigin[3];
	get_user_origin(idAttacker, ptPlayerOrigin, 1);
	get_user_origin(idAttacker, ptBulletOrigin, 4);

	message_begin(MSG_BROADCAST, SVC_TEMPENTITY, ptBulletOrigin);
	write_byte(114);
	write_coord(ptPlayerOrigin[0]);
	write_coord(ptPlayerOrigin[1]);
	write_coord(ptPlayerOrigin[2]);
	write_coord(ptBulletOrigin[0]);
	write_coord(ptBulletOrigin[1]); 
	write_coord(ptBulletOrigin[2]); 
	write_coord(40);
	write_short(arrIdSprites[SPR_BUBBLE_PRIEST]);
	write_byte(10); 
	write_coord(40);
	message_end();
}


// *******************************************************
// Супер навык - Слово Тьмы - Смерть - Darkness word: Death
// *******************************************************
public clRacePriest::ultDarkWordDeath(idVictim)
{
	if ( !ULT_Available( idVictim ) )
		return;

	if ( arrBoolData[idVictim][PB_CHANGINGTEAM] )
		return;

	//Блокировка супер навыка если у игрока Ожерелье {
	new Float:ptVictim[3]
	pev(idVictim, pev_origin, ptVictim);

	new arrPlayers[32], iNumPlayers;
	get_players(arrPlayers, iNumPlayers, "a" );

	new iTargetID;
	new iTeam = get_user_team( idVictim );

	for(new i = 0; i < iNumPlayers; i++)
	{
		iTargetID = arrPlayers[i];

		if(iTargetID == idVictim)
			continue;

		if(is_user_alive(iTargetID))
		{
			new Float:ptOriginTarget[3], Float:fDistance;
			pev(iTargetID, pev_origin, ptOriginTarget);
			fDistance = get_distance_f(ptVictim, ptOriginTarget);
	
			//client_print(idVictim,print_chat,"fDistance: %.1f",fDistance);

			if(fDistance <= fBlockUltRadius && iTeam != get_user_team(iTargetID))
			{
				if (ULT_CanUserBlockUlt(iTargetID,idVictim))
				{
					ULT_RemoveCharge(iTargetID);

					ULT_Blocked(idVictim);
					
					fResetUltimateTimerDivider(idVictim);

					return;
				}
			}
		}
	}
	//Блокировка супер навыка если у игрока Ожерелье }

	set_pev(idVictim, pev_sequence, 12);
    set_pev(idVictim, pev_animtime, halflife_time());
    set_pev(idVictim, pev_framerate, 1.0);
	set_pev(idVictim, pev_movetype, MOVETYPE_NONE);
	
	new Float:ptOrigin[3];
	pev(idVictim, pev_origin, ptOrigin);
	clRacePriest::stGetPos(idVictim, 150.0, 0.0, 0.0, ptOrigin);

	emit_sound(idVictim,CHAN_STATIC, arrStrSounds[SOUND_FIREBALL_PRIEST], 0.5, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

	new taskParm[4]
	taskParm[0] = idVictim;
	taskParm[1] = floatround(ptOrigin[0]);
	taskParm[2] = floatround(ptOrigin[1]);
	taskParm[3] = floatround(ptOrigin[2]);

	set_task(0.5, "_fSetFireAttack", idVictim + clRacePriest::tID_FIRE_ATTACK, taskParm, 4 );
	set_task(3.0, "_fStopUlt", idVictim + clRacePriest::tID_REMOVE_ATTACK);
	
	fResetUltimateTimerDivider(idVictim);

}

public clRacePriest::fSetFireAttack(taskParm[4])
{
	new idVictim = taskParm[0];
	
	new Float:ptSkyOrigin[3];
	ptSkyOrigin[0] = float(taskParm[1]);
	ptSkyOrigin[1] = float(taskParm[2]);
	ptSkyOrigin[2] = float(taskParm[3]);
	
	new Float:ptExplosion[24][3], Float:ptBall[24][3]	
	ptExplosion[0][0] = 200.0;
	ptExplosion[0][1] = 0.0;
	ptExplosion[0][2] = ptSkyOrigin[2];
	
	ptExplosion[1][0] = 400.0;
	ptExplosion[1][1] = 0.0;
	ptExplosion[1][2] = ptSkyOrigin[2];
	
	ptExplosion[2][0] = -200.0;
	ptExplosion[2][1] = 0.0;
	ptExplosion[2][2] = ptSkyOrigin[2];
	
	ptExplosion[3][0] = -400.0;
	ptExplosion[3][1] = 0.0;
	ptExplosion[3][2] = ptSkyOrigin[2];
	
	ptExplosion[4][0] = 0.0;
	ptExplosion[4][1] = 200.0;
	ptExplosion[4][2] = ptSkyOrigin[2];
	
	ptExplosion[5][0] = 0.0;
	ptExplosion[5][1] = 400.0;
	ptExplosion[5][2] = ptSkyOrigin[2];
	
	ptExplosion[6][0] = 0.0;
	ptExplosion[6][1] = -200.0;
	ptExplosion[6][2] = ptSkyOrigin[2];
	
	ptExplosion[7][0] = 0.0;
	ptExplosion[7][1] = -400.0;
	ptExplosion[7][2] = ptSkyOrigin[2];
	
	ptExplosion[8][0] = 200.0;
	ptExplosion[8][1] = 200.0;
	ptExplosion[8][2] = ptSkyOrigin[2];
	
	ptExplosion[9][0] = 400.0;
	ptExplosion[9][1] = 400.0;
	ptExplosion[9][2] = ptSkyOrigin[2];
	
	ptExplosion[10][0] = 200.0;
	ptExplosion[10][1] = 400.0;
	ptExplosion[10][2] = ptSkyOrigin[2];
	
	ptExplosion[11][0] = 400.0;
	ptExplosion[11][1] = 200.0;
	ptExplosion[11][2] = ptSkyOrigin[2];
	
	ptExplosion[12][0] = -200.0;
	ptExplosion[12][1] = 200.0;
	ptExplosion[12][2] = ptSkyOrigin[2];
	
	ptExplosion[13][0] = -400.0;
	ptExplosion[13][1] = 400.0;
	ptExplosion[13][2] = ptSkyOrigin[2];
	
	ptExplosion[14][0] = -200.0
	ptExplosion[14][1] = 400.0
	ptExplosion[14][2] = ptSkyOrigin[2];
	
	ptExplosion[15][0] = -400.0;
	ptExplosion[15][1] = 200.0;
	ptExplosion[15][2] = ptSkyOrigin[2];
	
	ptExplosion[16][0] = -200.0;
	ptExplosion[16][1] = -200.0;
	ptExplosion[17][2] = ptSkyOrigin[2];
	
	ptExplosion[17][0] = -200.0;
	ptExplosion[17][1] = -200.0;
	ptExplosion[17][2] = ptSkyOrigin[2];
	
	ptExplosion[18][0] = -200.0;
	ptExplosion[18][1] = -400.0;
	ptExplosion[18][2] = ptSkyOrigin[2];
	
	ptExplosion[19][0] = -400.0;
	ptExplosion[19][1] = -200.0;
	ptExplosion[19][2] = ptSkyOrigin[2];
	
	ptExplosion[20][0] = 200.0;
	ptExplosion[20][1] = -200.0;
	ptExplosion[20][2] = ptSkyOrigin[2];
	
	ptExplosion[21][0] = 400.0;
	ptExplosion[21][1] = -400.0;
	ptExplosion[21][2] = ptSkyOrigin[2];
	
	ptExplosion[22][0] = 200.0;
	ptExplosion[22][1] = -400.0;
	ptExplosion[22][2] = ptSkyOrigin[2];
	
	ptExplosion[23][0] = 400.0;
	ptExplosion[23][1] = -200.0;
	ptExplosion[23][2] = ptSkyOrigin[2];
	
	
	for(new i = 0; i < sizeof(ptExplosion); i++)
	{
		ptBall[i][0] = float(taskParm[1]);
		ptBall[i][1] = float(taskParm[2]);
		ptBall[i][2] = float(taskParm[3]);

		clRacePriest::stGetPos(idVictim, ptExplosion[i][0], ptExplosion[i][1], ptExplosion[i][2], ptBall[i])
		clRacePriest::fCreateFireball(idVictim, ptBall[i])
	}

	set_task(1.0, "_fSetFireAttack", idVictim + clRacePriest::tID_FIRE_ATTACK, taskParm, 4 );
}

stock clRacePriest::stGetPos(idUser, Float:fForward, Float:fRight, Float:fUp, Float:fVecStart[])
{
	new Float:fVecAngle[3], Float:fVecForward[3], Float:fVecRight[3], Float:fViewOfs[3];
	
	pev(idUser, pev_view_ofs,fViewOfs);
	xs_vec_add(fVecStart,fViewOfs,fVecStart)
	pev(idUser, pev_v_angle, fVecAngle);
	fVecAngle[0] = 0.0;
	angle_vector(fVecAngle,ANGLEVECTOR_FORWARD,fVecForward);
	angle_vector(fVecAngle,ANGLEVECTOR_RIGHT,fVecRight);
	angle_vector(fVecAngle,ANGLEVECTOR_UP,fViewOfs);
	fVecStart[0] = fVecStart[0] + fVecForward[0] * fForward + fVecRight[0] * fRight + fViewOfs[0] * fUp;
	fVecStart[1] = fVecStart[1] + fVecForward[1] * fForward + fVecRight[1] * fRight + fViewOfs[1] * fUp;
	fVecStart[2] = fVecStart[2] + fVecForward[2];
}

public clRacePriest::fCreateFireball(idUser, Float:ptOrigin[3])
{
	new entBall = create_entity("info_target");

	static Float:fAngles[3];
	pev(idUser, pev_angles, fAngles);

	entity_set_origin(entBall, ptOrigin);
	fAngles[0] = -100.0;
	entity_set_vector(entBall, EV_VEC_angles, fAngles);
	fAngles[0] = 100.0;
	entity_set_vector(entBall, EV_VEC_v_angle, fAngles);
	entity_set_string(entBall, EV_SZ_classname, "entBallFire");
	entity_set_model(entBall, arrStrModels[MDL_FIREBALL]);
	entity_set_int(entBall, EV_INT_solid, 2);
	entity_set_int(entBall, EV_INT_movetype, MOVETYPE_FLY);
	
	new Float:fMaxsSize[3] = {15.0, 15.0, 15.0};
	new Float:fMinSize[3] = {-15.0, -15.0, -15.0};
	entity_set_size(entBall, fMinSize, fMaxsSize);
	
	set_pev(entBall, pev_owner, idUser);
	
	static Float:fVelocity[3];
	VelocityByAim(entBall, random_num(250, 1000), fVelocity);
	set_pev(entBall, pev_light_level, 180);
	set_pev(entBall, pev_rendermode, kRenderTransAdd);
	set_pev(entBall, pev_renderamt, 255.0);
	entity_set_vector(entBall, EV_VEC_velocity, fVelocity);
	
	clRacePriest::fBurning(entBall, 0.5);
}

public clRacePriest::fStopUlt(idUser)//Остановка работающей ульты Жреца
{
	if (idUser >= clRacePriest::tID_REMOVE_ATTACK)
		idUser -= clRacePriest::tID_REMOVE_ATTACK;

	remove_task(idUser + clRacePriest::tID_FIRE_ATTACK);
}

public clRacePriest::fBurning(entBall, Float:fSize)
{
	static entEnvSprite;
	entEnvSprite = create_entity("env_sprite");
	set_pev(entEnvSprite, pev_takedamage, 0.0);
	set_pev(entEnvSprite, pev_solid, SOLID_NOT);
	set_pev(entEnvSprite, pev_movetype, MOVETYPE_NONE);
	set_pev(entEnvSprite, pev_classname, "_entBallFire");
	engfunc(EngFunc_SetModel, entEnvSprite, arrStrSprites[SPR_FLAME_PRIEST]);
	set_pev(entEnvSprite, pev_rendermode, kRenderTransAdd);
	set_pev(entEnvSprite, pev_renderamt, 255.0);
	set_pev(entEnvSprite, pev_light_level, 180);
	set_pev(entEnvSprite, pev_scale, fSize);
	set_pev(entEnvSprite, pev_owner, entBall);
	set_pev(entEnvSprite, pev_animtime, get_gametime());
	set_pev(entEnvSprite, pev_framerate, 8.0);
	set_pev(entEnvSprite, pev_frame, 0.1);
	set_pev(entEnvSprite, pev_spawnflags, SF_SPRITE_STARTON);
	dllfunc(DLLFunc_Spawn, entEnvSprite);

	thinkBallFire(entEnvSprite);
	set_pev(entEnvSprite, pev_nextthink, get_gametime() + 0.01);

	return entEnvSprite;
}

public thinkBallFire(entBallFire)
{
	if(!pev_valid(entBallFire))
		return;

	if(!pev_valid(pev(entBallFire, pev_owner)))
	{
		remove_entity(entBallFire);
		return;
	}
	static idOwner;
	idOwner = pev(entBallFire, pev_owner);
	static Float:ptOrigin[3];

	pev(idOwner, pev_origin, ptOrigin);
	ptOrigin[2] += 25.0;
	entity_set_origin(entBallFire, ptOrigin);
	set_pev(entBallFire, pev_nextthink, get_gametime() + 0.01);
	
}

public touchBallFire(entBallFire, idUserTouch)
{
	if(!pev_valid(entBallFire))
		return;

	static Float:ptOrigin[3]
	pev(entBallFire, pev_origin, ptOrigin);

	new idOwner = pev(entBallFire, pev_owner);

	message_begin(MSG_BROADCAST ,SVC_TEMPENTITY);
	write_byte(TE_EXPLOSION);
	engfunc(EngFunc_WriteCoord, ptOrigin[0]);
	engfunc(EngFunc_WriteCoord, ptOrigin[1]);
	engfunc(EngFunc_WriteCoord, ptOrigin[2]);
	write_short(arrIdSprites[SPR_ZEXPLODE_PRIEST]);
	write_byte(10);
	write_byte(30);
	write_byte(4);
	message_end();	

	emit_sound(entBallFire,CHAN_STATIC, arrStrSounds[SOUND_FIREBALL_EXP_PRIEST], 0.07, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

	new arrPlayers[32], iNumPlayers;
	get_players(arrPlayers, iNumPlayers, "a" );

	new iTargetID;
	new iTeam = get_user_team( idOwner );

	for(new i = 0; i < iNumPlayers; i++)
	{
		iTargetID = arrPlayers[i];

		if(is_user_alive(iTargetID))
		{
			new Float:ptOriginTarget[3], Float:fDistance;
			pev(iTargetID, pev_origin, ptOriginTarget);
			fDistance = get_distance_f(ptOrigin, ptOriginTarget);
	
			if(fDistance <= fBallExpRadius && iTeam != get_user_team(iTargetID))
			{
				clRacePriest::stShakeScreenPriest(iTargetID);

				WC3_Damage(iTargetID,idOwner,iWordDeathDmg,CSW_WORDDEATH, -1 ); 

				clRacePriest::stScreenFadePriest(iTargetID, 3, {255, 0, 0}, 120);

			}
		}

		
	}

	remove_entity(entBallFire);
}

stock clRacePriest::stScreenFadePriest(idUser, Timer, Colors[3], Alpha) 
{	
	message_begin(MSG_ONE_UNRELIABLE,gmsgScreenFade,_, idUser);
	write_short((1<<12) * Timer);
	write_short(1<<12);
	write_short(0);
	write_byte(Colors[0]);
	write_byte(Colors[1]);
	write_byte(Colors[2]);
	write_byte(Alpha);
	message_end();
}
stock clRacePriest::stShakeScreenPriest(idUser)
{
	message_begin(MSG_ONE_UNRELIABLE,gmsgScreenShake,{0,0,0}, idUser);
	write_short(1<<14);
	write_short(1<<13);
	write_short(1<<13);
	message_end();
}