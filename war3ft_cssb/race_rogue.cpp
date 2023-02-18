// ******************************************************************
// Раса: Разбойник (Race: Rogue) Functions
// ******************************************************************


//Инициализация скилов Race: Rogue (Разбойник)
public clRogue::setRogueSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	g_SkillOwner[SKILL_ROGUE_1			]	= RACE_ROGUE;
	g_SkillOwner[SKILL_ROGUE_2			]	= RACE_ROGUE;
	g_SkillOwner[SKILL_ROGUE_3			]	= RACE_ROGUE;
	g_SkillOwner[ULTIMATE_ROGUE			]	= RACE_ROGUE;
	
	g_SkillType[SKILL_ROGUE_1			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_ROGUE_2			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_ROGUE_3			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_ROGUE			]	= SKILL_TYPE_ULTIMATE;
	
	g_SkillOrder[SKILL_ROGUE_1			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_ROGUE_2			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_ROGUE_3			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_ROGUE			]	= SKILL_POS_4;

	//Максимальное количество зарядов
	arrSkillChargeMax[SKILL_ROGUE_1			]	= iRogueChargeMax_1;
	arrSkillChargeMax[SKILL_ROGUE_2			]	= iRogueChargeMax_2;
	arrSkillChargeMax[SKILL_ROGUE_3			]	= iRogueChargeMax_3;

	//Минимальное количество зарядов
	arrSkillChargeMin[SKILL_ROGUE_1			]	= iRogueChargeMin_1;
	arrSkillChargeMin[SKILL_ROGUE_2			]	= iRogueChargeMin_2;
	arrSkillChargeMin[SKILL_ROGUE_3			]	= iRogueChargeMin_3;

	//Счетчик через сколько шанс получить заряд
	arrSkillCount[SKILL_ROGUE_1				]	= iRogueCount_1;
	arrSkillCount[SKILL_ROGUE_2				]	= iRogueCount_2;
	arrSkillCount[SKILL_ROGUE_3				]	= iRogueCount_3;
	
}
//Инициализация начального количества зарядов у игрока
public clRogue::setChargeNum(idUser)//добавлена в war3ft.cpp ( WC3_PlayerInit( idUser ) )
{
	arrSkillChargeNum[idUser][SKILL_ROGUE_1] = iRogueChargeMin_1;
	arrSkillChargeNum[idUser][SKILL_ROGUE_2] = iRogueChargeMin_2;
	arrSkillChargeNum[idUser][SKILL_ROGUE_3] = iRogueChargeMin_3;
}

//Добавляем заряд скилу. Функция размещается в зависимости от того,
//каким способом будет даваться заряд (время,дамаг,убийство и тд)
clRogue::addSkillCharge(const iSkillID,const idUser,const iNumIncrement = 1)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;

	//Если достигнут максимум зарядов
	if(arrSkillChargeNum[idUser][iSkillID] >= arrSkillChargeMax[iSkillID])
		return;				

	//Счетчик - время через которое появится шанс получить заряд
	arrSkillTimer[idUser][iSkillID] += 1;

	if(arrSkillTimer[idUser][iSkillID] <= arrSkillCount[iSkillID])
		return;

	//Прибавление заряда скилу
	switch(iSkillID)
	{
		case SKILL_ROGUE_1:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser, iSkillID );
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
			
				new Float:fSinisterStrike = ArrayGetCell(arrSinisterStrike,iSkillLevel-1);
				if (random_float(fRogueSkill1MinPercent,fRogueSkill1MaxPercent) <= fSinisterStrike )		
				{
					arrSkillChargeNum[idUser][iSkillID] += iNumIncrement;
					WC3_ShowBar(idUser);

				//	client_print(idUser,print_chat,"C: %d | T: %d | S: %d",arrSkillChargeNum[idUser][iSkillID],arrSkillTimer[idUser][iSkillID],arrSkillCount[iSkillID]);
				}
			}
		}
		case SKILL_ROGUE_2:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser, iSkillID );
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
			
				new Float:fVanish = ArrayGetCell(arrVanish,iSkillLevel-1);
				if (random_float(fRogueSkill2MinPercent,fRogueSkill2MaxPercent) <= fVanish )		
				{
					arrSkillChargeNum[idUser][iSkillID] += iNumIncrement;
					WC3_ShowBar(idUser);
				}
			}
		}
		case SKILL_ROGUE_3:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser, iSkillID );
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
			
				new Float:fCripplingPoison = ArrayGetCell(arrCripplingPoison,iSkillLevel-1);
				if (random_float(fRogueSkill3MinPercent,fRogueSkill3MaxPercent) <= fCripplingPoison )		
				{
					arrSkillChargeNum[idUser][iSkillID] += iNumIncrement;
					WC3_ShowBar(idUser);

				}
			}
		}

	}

	//Обнуляем таймер
	arrSkillTimer[idUser][iSkillID] = 0;
}

// ******************************************************************
// Скил 1 уровня - Sinister Strike - Коварный удар - наступательный
// ******************************************************************
clRogue::skillSinisterStrike(const idAttacker, const idVictim, const iWeapon,const iSkillID)
{
	if(!is_user_connected(idVictim)) 
      return;

	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
      return;

	if(isDisabledSkillsOnMap(idAttacker,iSkillID) == true)
		return;

	//Активен ли скилл
	if(arrIsSkillChargeActive[idAttacker][iSkillID] == false)
		return;

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idAttacker][iSkillID] <= 0)
		return;

	//Работа скила
	new vVictimOrigin[3], vAttackerOrigin[3]
	get_user_origin(idVictim, vVictimOrigin );
	get_user_origin(idAttacker, vAttackerOrigin );
	
	Create_TE_SPRITETRAIL(vAttackerOrigin, vVictimOrigin, arrIdSprites[SPR_SINISTER_STRIKE],100, random_num(20,30),1, random_num(60,100), 100 )

	Create_TE_PARTICLEBURST(vVictimOrigin,200,0x00FF00,30);
	
	emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_SINISTER_STRIKE], 1.0, ATTN_NORM, 0, PITCH_NORM );

	if(SHARED_IsSecondaryWeapon(iWeapon))// пистолет
		WC3_Damage(idVictim, idAttacker, iSStrike_Secondary, iWeapon, 0);
	else if(SHARED_IsPrimaryWeapon(iWeapon))
		WC3_Damage(idVictim, idAttacker, iSStrike_Primary, iWeapon, 0);// автомат
	else if(SHARED_IsHoldingKnife(idAttacker))
		WC3_Damage(idVictim, idAttacker, iSStrike_Knife, iWeapon, 0); // нож
	else if(SHARED_IsGrenade(iWeapon))
		WC3_Damage(idVictim, idAttacker, iSStrike_Grenade, iWeapon, 0); // граната

	//Удаляем один заряд после срабатывания
	arrSkillChargeNum[idAttacker][iSkillID] -= 1;
}

// *******************************************************
// Скил 2 уровня - Vanish - Исчезновение - пассивный
// *******************************************************
clRogue::skillVanish(const idUser,const iSkillID)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
		return;

	if(isDisabledSkillsOnMap(idUser,iSkillID) == true)
		return;

	//Делаем полную невидимость
	fm_set_rendering(idUser,kRenderFxGlowShell,0,0,0,kRenderTransAlpha,0);

	new Float:fNumCharge = float(arrSkillChargeNum[idUser][iSkillID]);
	set_task(fNumCharge, "_taskResetVanish", clRogue::tID_VANISH + idUser);

	emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_VANISH], 1.0, ATTN_NORM, 0, PITCH_NORM );

	arrSkillChargeNum[idUser][iSkillID] = 0;
	WC3_ShowBar(idUser);

}

public clRogue::taskResetVanish(idUser)
{
	if (idUser >= clRogue::tID_VANISH)
		idUser -= clRogue::tID_VANISH;

	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;

	//Восстанавливаем нормальную невидимость
	fm_set_rendering(idUser);

	new szSkillName[64];
	fGetSkillName(SKILL_ROGUE_2,szSkillName, charsmax(szSkillName));
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_DEACTIVE_SKILLS",szSkillName);
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

}

// ****************************************************************
// Скил 3 уровня - Crippling Poison - Калечащий яд - наступательный
// ****************************************************************
clRogue::skillCripplingPoison(const idAttacker, const idVictim,const iSkillID)
{
	if(!is_user_connected(idVictim)) 
      return;

	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
      return;

	if(isDisabledSkillsOnMap(idAttacker,iSkillID) == true)
		return;

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idAttacker][iSkillID] <= 0)
		return;

	if(arrSkillChargeNum[idAttacker][iSkillID] < arrSkillChargeMin[iSkillID])
		return;

	//Работа скила
	new vVictimOrigin[3];
	get_user_origin(idVictim, vVictimOrigin);
	
	Create_TE_LARGEFUNNEL(vVictimOrigin, arrIdSprites[SPR_MFLASH2_BLACK_MAG],1);

	Create_ScreenShake(idVictim, (1<<14), (1<<13), (1<<14) );
	
	emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_SINISTER_STRIKE], 1.0, ATTN_NORM, 0, PITCH_NORM );


	//Уменьшение здоровья жертве
	new iMinHealth_V = clHP:getRaceMinHealth(idVictim);
	new iCurrentHealth_V =  clHP:getUserHealth(idVictim);
	new iBonusHp_V = iCurrentHealth_V - floatround(iCurrentHealth_V * 0.3);
	
	if(iBonusHp_V < iMinHealth_V)
		clHP:setUserHealth(idVictim,iMinHealth_V);
	else
		clHP:setUserHealth(idVictim,iBonusHp_V);

	//Прибавление здоровья атакующему
	new iMaxHealth_A = clHP:getRaceMaxHealth(idAttacker);
	new iCurrentHealth_A =  clHP:getUserHealth(idAttacker);
	new iBonusHp_A = floatround(iBonusHp_V  * 0.3);
	
	if((iCurrentHealth_A + iBonusHp_A) > iMaxHealth_A)
		clHP:setUserHealth(idAttacker,iMaxHealth_A);
	else
		clHP:setUserHealth(idAttacker,iCurrentHealth_A + iBonusHp_A);


	//Замедляем скорость
	arrBoolData[idVictim][PB_SLOWED] = true;
	SHARED_SetSpeed(idVictim);

	if (!task_exists(clRogue::tID_CP_SPEED + idVictim))
	{
		new Float:fNumCharge = float(arrSkillChargeNum[idAttacker][iSkillID]) / 3;
		set_task(fNumCharge, "_taskResetCP_Speed", clRogue::tID_CP_SPEED + idVictim);
	}

	//Обнуляем заряды после срабатывания или списываем заряды
	if(arrSkillChargeNum[idAttacker][iSkillID] >= arrSkillChargeMin[iSkillID])
		arrSkillChargeNum[idAttacker][iSkillID] -= arrSkillChargeMin[iSkillID];
	else
		arrSkillChargeNum[idAttacker][iSkillID] = 0;

	WC3_ShowBar(idAttacker);
}

//Восстанавливаем скорость
public clRogue::taskResetCP_Speed(idUser)
{
	if (idUser >= clRogue::tID_CP_SPEED)
		idUser -= clRogue::tID_CP_SPEED;

	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;

	SHARED_ResetMaxSpeed(idUser);

	emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_HEX], 1.0, ATTN_NORM, 0, PITCH_NORM );
}

// *******************************************************
// Супер навык - Бросок сюрикена - Shuriken Toss
// *******************************************************
public clRogue::ultShurikenToss(idUser)
{	
	//Блокировка супер навыка врагом
	new vOldLocation[3], vNewLocation[3]
	
	get_user_origin( idUser, vOldLocation );
	get_user_origin( idUser, vNewLocation, 3 );

	new iPlayerOldCheck = WC3_IsImmunePlayerNear( idUser, vOldLocation );
	new iPlayerNewCheck = WC3_IsImmunePlayerNear( idUser, vNewLocation );
	new iLosesCharge = 0;
	if ( iPlayerOldCheck > 0 )
		iLosesCharge = iPlayerOldCheck;
	else if ( iPlayerNewCheck > 0 )
		iLosesCharge = iPlayerNewCheck;

	if ( iLosesCharge > 0 )
	{
		ULT_RemoveCharge(iLosesCharge);

		fResetUltimateTimerDivider(idUser);

		ULT_Blocked( idUser );

		return 0;
	}

	//Создание модели
	new ent = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	
	if(!pev_valid(ent)) 
		return 0;
	
	set_pev(ent, pev_classname, BALL_CLASSNAME);
	
	new Float: origin[3];
	new Float: velocity[3];
	
	GetGunPosition(idUser, origin);
	
	set_pev(ent, pev_origin, origin);
	set_pev(ent, pev_owner, idUser);
	set_pev(ent, pev_dmg, fShurikenDmg);
	
	engfunc(EngFunc_SetModel, ent, arrStrSprites[SPR_ROGUE_SHURIKEN]);
	engfunc(EngFunc_SetSize, ent, Float:{0.0, 0.0, 0.0} , Float:{0.0, 0.0, 0.0});
	
	set_pev(ent, pev_effects, pev(ent, pev_effects) | TE_DLIGHT);
	set_rendering(ent, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);
	
	velocity_by_aim(idUser, 650, velocity);
	set_pev(ent, pev_velocity, velocity);
	
	dllfunc(DLLFunc_Spawn, ent);
	
	set_pev(ent, pev_movetype, MOVETYPE_FLY);
	set_pev(ent, pev_solid, SOLID_BBOX);
	set_pev(ent, pev_scale, 5);
	set_pev(ent, pev_nextthink, get_gametime() + 0.1);
	
	fResetUltimateTimerDivider(idUser);

	return ent;
}

public ShurikenBall_Think(ent)
{
	if (!pev_valid(ent)) 
		return;
	
	ShurikenBall_Animate(ent);
	
	if (pev(ent, pev_iuser4))
	{
		ShurikenBall_Remove(ent);
		return;
	}
	
	new Float:velocity[3];
	pev(ent, pev_velocity, velocity);
	
	if (!vector_length(velocity) || !IsInWorld(ent))
	{
		ShurikenBall_Explode(ent);
		return;
	}
		
	new ptr, i, idVictim, owner, beam;
	new Float: Dist;
	new Float: flFraction;
	new Float: origin[3];
	new Float: vecDir[3];
	new Float: vecEndPos[3];
	
	Dist = 1.00; ptr = create_tr2();

	pev(ent, pev_origin, origin);
	
	while ((idVictim = engfunc(EngFunc_FindEntityInSphere, idVictim, origin, fShurikenBeamRadius)))
	{
		if (pev(idVictim, pev_takedamage) && is_visible(idVictim, ent) && idVictim != (owner = pev(ent, pev_owner)))
		{
			new Float:target_origin[3]; 
			pev(idVictim, pev_origin, target_origin);
			
			ExecuteHamB(Ham_TakeDamage, idVictim, ent, owner, fShurikenBeamDmg, DMG_ENERGYBEAM );
			
			if ((beam = BeamCreate(idVictim, arrStrSprites[SPR_ROGUE_BEAM], arrIdSprites[SPR_ROGUE_BEAM], 65.0)))
			{
				RelinkBeam(beam, origin, target_origin);
				
				BeamSetColor(beam, 255.0, 0.0, 0.0);
				BeamSetNoise(beam, 45);
				BeamSetBrightness(beam, 255.0);
				BeamSetScrollRate(beam, 35.0);
				BeamLiveForTime(beam, 0.1);
			}
		}
	}
	
	for (i = 0; i < 7; i++)
	{
		vecDir[0] = random_float(-1.0, 1.0);
		vecDir[1] = random_float(-1.0, 1.0);
		vecDir[2] = random_float(-1.0, 1.0);
		
		VecNormilize(vecDir, vecDir);
		xs_vec_mul_scalar(vecDir, 1536.0 /* Радиус распространения "заземляющихся" лучей сферы в юнитах*/, vecDir);
		xs_vec_add(vecDir, origin, vecDir);
		
		engfunc(EngFunc_TraceLine, origin, vecDir, IGNORE_MONSTERS, ent, ptr);
		get_tr2(ptr, TR_flFraction, flFraction);
		
		if (Dist > flFraction)
		{  
			get_tr2(ptr, TR_vecEndPos, vecEndPos);
			Dist = flFraction;
		}
	}
	
	if (Dist < 1.0) 
	{
		if ((beam = BeamCreate(ent, arrStrSprites[SPR_ROGUE_BEAM], arrIdSprites[SPR_ROGUE_BEAM], 30.0)))
		{
			RelinkBeam(beam, vecEndPos, origin);
			
			BeamSetColor(beam, 242.0, 234.0, 21.0);
			BeamSetNoise(beam, 65);
			BeamSetBrightness(beam, 255.0);
			BeamSetScrollRate(beam, 35.0);
			BeamLiveForTime(beam, 1.0);
		}
	}
	
	set_pev(ent, pev_nextthink, get_gametime() + 0.1);
	free_tr2(ptr);
}

public ShurikenBeam_Think(ent)
{
	if (pev_valid(ent))
	{
		remove_entity(ent);
	}
}

public ShurikenBall_Explode_Touch(ent, other)
{
	if (pev_valid(ent))
	{
		ShurikenBall_Explode(ent, other);
	}
}

ShurikenBall_Explode(ent, idUser = 0)
{	
	if (!pev(ent, pev_iuser3))
	{
		new Float: origin[3];
		pev(ent, pev_origin, origin);
		set_pev(ent, pev_iuser3, 1);
		
		UTIL_MakeBeamCylinder(origin, arrIdSprites[SPR_ROGUE_RING]) ;
	}
	
	if (SHARED_ValidPlayer(idUser))
	{
		new resp_ent;

		new iTeam = get_user_team(idUser);
		if (iTeam == TEAM_T )
			resp_ent = CanTeleportOnBaseCT();
		if (iTeam == TEAM_CT )
			resp_ent = CanTeleportOnBaseT();

		if(pev_valid(resp_ent)) 
			ShurikenBall_Teleport(idUser, resp_ent);
	}
	
	set_pev(ent, pev_velocity, Float:{0.0, 0.0, 0.0});
	set_pev(ent, pev_iuser4, 1);
	set_pev(ent, pev_nextthink, get_gametime() + 0.6);
}
//Телепорт на базу террористов
CanTeleportOnBaseT()
{
	new ent, alert, i;
	do
	{	
		for (i = random_num(1, 10); i > 0; i-- )
			ent = engfunc(EngFunc_FindEntityByString, ent, "classname", "info_player_deathmatch");
		
		if (alert++ > 10)
			return 0;
	}
	while (!IsSpawnPointValid(ent));

	return ent;
}
//Телепорт на базу контров
CanTeleportOnBaseCT()
{
	new ent, alert, i;
	do
	{	
		for (i = random_num(1, 10); i > 0; i-- )
			ent = engfunc(EngFunc_FindEntityByString, ent, "classname", "info_player_start");
		
		if (alert++ > 10)
			return 0;
	}
	while (!IsSpawnPointValid(ent));

	return ent;
}

ShurikenBall_Teleport(idUser, resp_ent)
{
	new Float: origin[3], Float: angles[3];
	
	if(!pev_valid(resp_ent)) 
		return;

	pev(resp_ent, pev_origin, origin);
	pev(resp_ent, pev_angles, angles);
	
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_SPRITE);
	engfunc(EngFunc_WriteCoord, origin[0]);
	engfunc(EngFunc_WriteCoord, origin[1]);
	engfunc(EngFunc_WriteCoord, origin[2]);
	write_short(arrIdSprites[SPR_ROGUE_SHURIKEN]);
	write_byte(10);
	write_byte(128);
	message_end();
	
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_DLIGHT);
	engfunc(EngFunc_WriteCoord, origin[0]);
	engfunc(EngFunc_WriteCoord, origin[1]);
	engfunc(EngFunc_WriteCoord, origin[2]);
	write_byte(20) ;
	write_byte(90); // red
	write_byte(170); // green
	write_byte(16); // blue
	write_byte(255);
	write_byte(5);
	write_byte(1);
	message_end();
	
	emit_sound(resp_ent, CHAN_WEAPON, arrStrSounds[SOUND_TELEPORT], 1.0, ATTN_NORM, 0, PITCH_NORM);
	
	set_pev(idUser, pev_velocity, Float:{0.0, 0.0, 0.0});
	set_pev(idUser, pev_basevelocity, Float:{0.0, 0.0, 0.0});
	
	set_pev(idUser, pev_origin, origin);
	set_pev(idUser, pev_angles, angles);
	set_pev(idUser, pev_fixangle, true);
}

bool:IsSpawnPointValid(const resp_ent)
{
	new ent = FM_NULLENT; 
	new Float: origin[3];
	pev(resp_ent, pev_origin, origin);
	
	while((ent= engfunc(EngFunc_FindEntityInSphere, ent, origin, 10.0)))
	{
		return SHARED_ValidPlayer(ent) ? false : true;
	}
	return false;
}

ShurikenBall_Remove(const ent)
{	
	new Float: origin[3]; 
	pev(ent, pev_origin, origin);

	UTIL_RadiusDamage(origin, ent, pev(ent, pev_owner), float(pev(ent, pev_dmg)), fShurikenRadiusExp, 0, DMG_RADIATION);
	
	emit_sound(ent, CHAN_VOICE,arrStrSounds[SOUND_SHURIKEN_TOSS_EXP], 0.9, ATTN_NORM, 0, PITCH_NORM);
	
	remove_entity(ent);
}

ShurikenBall_Animate(const ent)
{
	entity_set_float(ent, EV_FL_frame, entity_get_float(ent, EV_FL_frame) + 10.0);
		
	if (entity_get_float(ent, EV_FL_frame) > 24)
		entity_set_float(ent, EV_FL_frame, 0.0);
}

stock GetGunPosition(const idUser, Float:origin[3] )
{
	new Float:viewOfs[3];
	
	pev(idUser, pev_origin, origin);
	pev(idUser, pev_view_ofs, viewOfs);

	xs_vec_add( origin, viewOfs, origin);
}

stock VecNormilize(Float: in[3], Float: out[3])
{
	new Float:vlen;
	
	vlen = vector_length(in);
	vlen = 1/vlen;
	
	out[0] *= vlen;
	out[1] *= vlen;
	out[2] *= vlen;
}

stock UTIL_MakeBeamCylinder(const Float:origin[3], const m_Sprite) 
{
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_BEAMCYLINDER);
	engfunc(EngFunc_WriteCoord, origin[0]);
	engfunc(EngFunc_WriteCoord, origin[1]);
	engfunc(EngFunc_WriteCoord, origin[2]);
	engfunc(EngFunc_WriteCoord, origin[0]);
	engfunc(EngFunc_WriteCoord, origin[1]);
	engfunc(EngFunc_WriteCoord, origin[2] + 800.0) ;
	write_short(m_Sprite) ;
	write_byte(0);
	write_byte(10);
	write_byte(3); 
	write_byte(20); 
	write_byte(0); 
	write_byte(255);
	write_byte(255);
	write_byte(255);
	write_byte(255);
	write_byte(0);
	message_end();
}

stock UTIL_RadiusDamage(Float:vecSrc[3], entShuriken, idAttacker=0, Float:flDamage, Float:flRadius=0.0, iClassIgnore = 0, bitsDamageType)
{
	if (!idAttacker)
		return;

	new idVictim = FM_NULLENT;
	new bool: bInWater = (engfunc(EngFunc_PointContents, vecSrc) == CONTENTS_WATER);

	new Float:flTakeDamage;
	while ((idVictim = engfunc(EngFunc_FindEntityInSphere, idVictim, vecSrc, flRadius)) )
	{
		if (!is_visible(idVictim, entShuriken))
			continue;
		
		pev(idVictim, pev_takedamage, flTakeDamage);

		if ( flTakeDamage != DAMAGE_NO )
		{
			if ( iClassIgnore != 0 && ExecuteHamB(Ham_Classify, idVictim) == iClassIgnore )
				continue;

			if( bInWater )
			{
				if( !pev(idVictim, pev_waterlevel) )
					continue;
			}
			else if( pev(idVictim, pev_waterlevel) == 3 )
			{
				continue;
			}

			if(idVictim == idAttacker)
				continue;
			
			ExecuteHamB(Ham_TakeDamage, idVictim, entShuriken, idAttacker, flDamage, bitsDamageType);
		}
	}


}


//*************************************
// Создание луча
//*************************************
BeamCreate(const endIndex, const pSpriteName[], const spriteIndex, const Float: width)
{
	new ent = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "beam"));
	
	if(!pev_valid(ent)) 
		return 0;
		
	set_pev(ent, pev_classname, BEAM_CLASSNAME);	
	
	set_pev(ent, pev_flags, pev(ent, pev_flags) | FL_CUSTOMENTITY);
	
	BeamSetFrame(ent, 0);
	
	set_pev(ent, pev_model, pSpriteName);
	
	BeamSetTexture(ent, spriteIndex);
	BeamSetWidth(ent, width);
	
	set_pev(ent, pev_skin, endIndex);
	set_pev(ent, pev_sequence, 0);
	set_pev(ent, pev_rendermode, 1);
	
	DispatchSpawn(ent);
	
	return ent;
}

RelinkBeam(const beam, const Float: startPos[3], const Float: endPos[3])
{
	new Float:mins[3], Float:maxs[3];
	
	mins[0] = floatmin(startPos[0], endPos[0]);
	mins[1] = floatmin(startPos[1], endPos[1]);
	mins[2] = floatmin(startPos[2], endPos[2]);
	
	maxs[0] = floatmax(startPos[0], endPos[0]);
	maxs[1] = floatmax(startPos[1], endPos[1]);
	maxs[2] = floatmax(startPos[2], endPos[2]);
	
	xs_vec_sub(mins, startPos, mins);
	xs_vec_sub(maxs, startPos, maxs);
	
	set_pev(beam, pev_mins, mins);
	set_pev(beam, pev_maxs, maxs);
	
	engfunc(EngFunc_SetSize, beam, mins, maxs);
	engfunc(EngFunc_SetOrigin, beam, startPos);
}

BeamLiveForTime(const ent, const Float: time)
{
	set_pev(ent, pev_nextthink, halflife_time() + time);
}

BeamSetColor(const ent, const Float: red, const Float: green, const Float: blue)
{
	new Float: rgb[3];
	
	rgb[0] = red;
	rgb[1] = green;
	rgb[2] = blue;
	
	set_pev(ent, pev_rendercolor, rgb);
}

BeamSetBrightness(const ent, const Float: brightness)
{
	set_pev(ent, pev_renderamt, brightness);
}

BeamSetNoise(const ent, const noise)
{
	set_pev(ent, pev_body, noise);
}

BeamSetFrame(const ent, const frame)
{
	set_pev(ent, pev_frame, frame);
}

BeamSetScrollRate(const ent, const Float: speed)
{
	set_pev(ent, pev_animtime, speed);
}

BeamSetTexture(const ent, const spriteIndex)
{
	set_pev(ent, pev_modelindex, spriteIndex);
}

BeamSetWidth(const ent, const Float: width)
{
	set_pev(ent, pev_scale, width);
}


// ******************************************************************
// Меню
// ******************************************************************

//Вызов отображения меню для активации скилов
fShowMenuActiveSkills(idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;

	new idMenu,szNumber[64],szMenuData[256];
	
	//Название главного меню
	formatex(szMenuData, charsmax(szMenuData), "\y%L", LANG_PLAYER, "MENU_ID_ACTIVE_SKILLS");
	idMenu = menu_create(szMenuData, "_Callback_MENU_ActiveSkills");

	new szSkillName[64],szSkillFull[255];
	fGetSkillName(SKILL_ROGUE_1,szSkillName, charsmax(szSkillName));
	formatex(szNumber, charsmax(szNumber), "%d", SKILL_ROGUE_1);
	formatex(szSkillFull, charsmax(szSkillFull), "%s: \w%d | min \y%d \w| max \r%d", szSkillName,arrSkillChargeNum[idUser][SKILL_ROGUE_1],arrSkillChargeMin[SKILL_ROGUE_1],arrSkillChargeMax[SKILL_ROGUE_1]);
	menu_additem(idMenu,szSkillFull,szNumber,0,-1);

	fGetSkillName(SKILL_ROGUE_2,szSkillName, charsmax(szSkillName));
	formatex(szNumber, charsmax(szNumber), "%d", SKILL_ROGUE_2);
	formatex(szSkillFull, charsmax(szSkillFull), "%s: \w%d | min \y%d \w| max \r%d", szSkillName,arrSkillChargeNum[idUser][SKILL_ROGUE_2],arrSkillChargeMin[SKILL_ROGUE_2],arrSkillChargeMax[SKILL_ROGUE_2]);
	menu_additem(idMenu,szSkillFull,szNumber,0,-1);

	// Если нет пунктов в меню
	if (menu_items(idMenu) <= 0)
	{
		menu_destroy(idMenu);
		return;
	}
		
	formatex(szMenuData, charsmax(szMenuData), "\w%L", LANG_PLAYER, "WORD_EXIT");
	menu_setprop(idMenu, MPROP_EXITNAME, szMenuData);
	menu_setprop(idMenu, MPROP_NUMBER_COLOR, "\y");
	menu_display(idUser, idMenu, 0);
}

//Функция выбора пунктов в под меню Добавления предметов
public _Callback_MENU_ActiveSkills(idUser, idMenu, iItemMenu)
{
	if (!WC3_Check())
		return PLUGIN_HANDLED;

	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return PLUGIN_HANDLED;

	// Возврат в главное меню
	if (iItemMenu == MENU_EXIT)
	{
		menu_destroy(idMenu);
		return PLUGIN_HANDLED;
	}
	
	new _access, szInfoMenu[8], callback;
	menu_item_getinfo(idMenu,iItemMenu, _access, szInfoMenu, sizeof(szInfoMenu) - 1, _, _, callback);
	
	new iSkillID = str_to_num(szInfoMenu);
		
	new szSkillName[64];
	fGetSkillName(iSkillID,szSkillName, charsmax(szSkillName));

	switch(iSkillID)
	{
		case SKILL_ROGUE_1:
		{
			//Заблокирован ли супер навык на карте
			new szSkillName[64];
			if(isDisabledSkillsOnMap(idUser,SKILL_ROGUE_1,szSkillName) == true)
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SKILL_DISABLED_ON_MAP",szSkillName);
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				menu_destroy(idMenu);
				return PLUGIN_HANDLED;
			}

			if(arrIsSkillChargeActive[idUser][iSkillID] == false)
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ACTIVE_SKILLS",szSkillName);
				arrIsSkillChargeActive[idUser][iSkillID] = true;
			}
			else
			{

				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_DEACTIVE_SKILLS",szSkillName);
				arrIsSkillChargeActive[idUser][iSkillID] = false;
			}

			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case SKILL_ROGUE_2:
		{
			//Заблокирован ли супер навык на карте
			new szSkillName[64];
			if(isDisabledSkillsOnMap(idUser,SKILL_ROGUE_2,szSkillName) == true)
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SKILL_DISABLED_ON_MAP",szSkillName);
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				menu_destroy(idMenu);
				return PLUGIN_HANDLED;
			}


			//Если скил активен
			if (task_exists(clRogue::tID_VANISH + idUser))
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_IS_ACTIVE",szSkillName);
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				menu_destroy(idMenu);
				return PLUGIN_HANDLED;
			}

			if(arrSkillChargeNum[idUser][iSkillID] < arrSkillChargeMin[iSkillID])
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MIN_CHARGE",arrSkillChargeMin[iSkillID]);
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				menu_destroy(idMenu);
				return PLUGIN_HANDLED;
			}

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ACTIVE_SKILLS",szSkillName);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

			clRogue::skillVanish(idUser,iSkillID);
		}
	}

	menu_destroy(idMenu);

	//client_print(idUser,print_chat,"iNumberItem: %d |iSkillID: %d",iNumberItem,iItemMenu);	

	return PLUGIN_HANDLED;
}
