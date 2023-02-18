/*
*	Race: Death knight (Рыцарь смерти) Functions
*/

//-----------------Базовые функции------------------------------------BEGIN {

/*
// - Shadow Strike ---------------------------------------- //

#define SHADOWSTRIKE_DURATION                         10    // (integer) duration of damage over time
#define SHADOWSTRIKE_DAMAGE                           35    // (integer) initial damage
#define SHADOWSTRIKE_ARMOR                            15    // (integer) amount of armor to remove from target
#define SHADOWSTRIKE_DOT                              20    // (integer) damage to apply over SHADOWSTRIKE_DURATION
#define SHADOWSTRIKE_SPEED                         120.0    // (  float) speed to set player to when struck
#define TASK_SHADOWSTRIKE            608

// ------------------------------------------------- End. - //
*/

//=============================================================================
//=============================================================================
//=============================================================================
//-----------------Базовые функции-----------------------------------------------END }
//Инициализация скилов
public clRaceDeathKnight::setSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	// Set up the Skill Owners
	g_SkillOwner[SKILL_DEATH_KNIGHT_UNARMOR					]	= RACE_DEATH_KNIGHT;
	g_SkillOwner[SKILL_DEATH_KNIGHT_BLOOD_BOIL				]	= RACE_DEATH_KNIGHT;
	g_SkillOwner[SKILL_DEATH_KNIGHT_DEATH_COIL				]	= RACE_DEATH_KNIGHT;
	g_SkillOwner[ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE		]	= RACE_DEATH_KNIGHT;
	g_SkillOwner[PASS_DEATH_KNIGHT_CONTROL_UNDEAD			]	= RACE_DEATH_KNIGHT;
	
	// Set up the skill types
	g_SkillType[SKILL_DEATH_KNIGHT_UNARMOR					]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_DEATH_KNIGHT_BLOOD_BOIL				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_DEATH_KNIGHT_DEATH_COIL				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE		]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_DEATH_KNIGHT_CONTROL_UNDEAD			]	= SKILL_TYPE_PASSIVE;
	
	// Set up the skill order
	g_SkillOrder[SKILL_DEATH_KNIGHT_UNARMOR					]	= SKILL_POS_1;
	g_SkillOrder[SKILL_DEATH_KNIGHT_BLOOD_BOIL				]	= SKILL_POS_2;
	g_SkillOrder[SKILL_DEATH_KNIGHT_DEATH_COIL				]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE		]	= SKILL_POS_4;
	g_SkillOrder[PASS_DEATH_KNIGHT_CONTROL_UNDEAD			]	= SKILL_POS_NONE;

}



// *******************************************************
// Скил 1 уровня - Unbreakable Armor - Несокрушимая броня - защитный 
// *******************************************************
Float:clRaceDeathKnight::skillUnbreakableArmor(idAttacker,idVictim, Float:fDamage )//добавлена в events.cpp ( public EVENT_TakeDamage( idVictim, iWeapon, idAttacker, Float:f_Damage, damagetype ) )
{
	new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_DEATH_KNIGHT_UNARMOR);
	if (iSkillLevel > 0 && arrBoolData[idVictim][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idVictim,SKILL_DEATH_KNIGHT_UNARMOR) == false)
	{
		if (random_float(0.0, 1.0 ) <= fUnarmorChance)
		{
			new Float:fOrigin[3], Float:fNormal[3], Float:fMins[3], Float:fMaxs[3]
			if(!clRaceDeathKnight::getCorrectedOrigin(idAttacker, fOrigin, fNormal, fMins, fMaxs))
			{
				clRaceDeathKnight::setSurfaceEffect(fOrigin, fNormal, arrIdSprites[SPR_DK_UNARMOR]);
				
				emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_DK_UNARMOR], 1.0, ATTN_NORM, 0, PITCH_NORM );

				new Float:fUnarmor = ArrayGetCell(arrUnbreakableArmor,iSkillLevel-1);
				new Float:fBonus = (fDamage - (fDamage * fUnarmor));
				

				#if MODE_LOG
					#if LOG_SKILL_BLOOD_BOIL > 0
						clLog:logRaceDeathKnight(idAttacker,fUnarmor,fDamage,fBonus);
					#endif
				#endif

				fDamage = fBonus;

				if(fDamage < 0.0)
					fDamage = 0.0;

				return fDamage;
			}

		}
	}

	return fDamage;
}

public clRaceDeathKnight::setSurfaceEffect(Float:fOrigin[3], Float:fNormal[3],iSpriteIndex)
{
	new Float:fStart[3], Float:fEnd[3];
	xs_vec_mul_scalar(fNormal, 7.0, fStart);
	xs_vec_add(fOrigin, fStart, fStart);
	xs_vec_mul_scalar(fNormal, 20.0, fEnd);
	xs_vec_add(fOrigin, fEnd, fEnd);
	
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_SPRITETRAIL);
	engfunc(EngFunc_WriteCoord, fStart[0]);
	engfunc(EngFunc_WriteCoord, fStart[1]);
	engfunc(EngFunc_WriteCoord, fStart[2]);
	engfunc(EngFunc_WriteCoord, fEnd[0]);
	engfunc(EngFunc_WriteCoord, fEnd[1]);
	engfunc(EngFunc_WriteCoord, fEnd[2]);
	write_short(iSpriteIndex);
	write_byte(25);
	write_byte(1);
	write_byte(1);
	write_byte(20);
	write_byte(14);
	message_end();
}

public clRaceDeathKnight::getCorrectedOrigin(id, Float:fOutPointFSet[3], Float:fOrigWallNormal[3], Float:fMinsO[3], Float:fMaxsO[3])
{
	new Float:fWallNormal[3]
	clRaceDeathKnight::getWallNormal(id, fWallNormal)
	xs_vec_copy(fWallNormal, fOrigWallNormal)
	
	new Float:fWallAngles[3]
	vector_to_angle(fWallNormal, fWallAngles)
	
	new Float:fUpNormal[3], Float:fRightNormal[3]
	angle_vector(fWallAngles, ANGLEVECTOR_UP, fUpNormal)
	angle_vector(fWallAngles, ANGLEVECTOR_RIGHT, fRightNormal)
	
	new Float:fAimOrigin[3]
	fm_get_aim_origin(id, fAimOrigin)
	xs_vec_copy(fAimOrigin, fOutPointFSet)
	
	new Float:fAddUnits[3]
	xs_vec_mul_scalar(fOrigWallNormal, 1.0, fAddUnits)
	xs_vec_add(fAddUnits, fAimOrigin, fAimOrigin)
	
	xs_1_neg(fUpNormal[2])
	
	new Float:fUpLeftPoint[3], Float:fUpRightPoint[3], Float:fDownLeftPoint[3], Float:fDownRightPoint[3]
	xs_vec_mul_scalar(fUpNormal, 65.0/2, fUpNormal)
	xs_vec_mul_scalar(fRightNormal, 45.0/2, fRightNormal)
	
	//1
	xs_vec_add(fUpNormal, fRightNormal, fUpRightPoint)
	xs_vec_add(fUpRightPoint, fAimOrigin, fUpRightPoint)
	
	//2
	xs_vec_neg(fRightNormal, fRightNormal)
	xs_vec_add(fUpNormal, fRightNormal, fUpLeftPoint)
	xs_vec_add(fUpLeftPoint, fAimOrigin, fUpLeftPoint)
	
	//3
	xs_vec_neg(fUpNormal, fUpNormal)
	xs_vec_add(fUpNormal, fRightNormal, fDownLeftPoint)
	xs_vec_add(fDownLeftPoint, fAimOrigin, fDownLeftPoint)
	
	//4
	xs_vec_neg(fRightNormal, fRightNormal)
	xs_vec_add(fUpNormal, fRightNormal, fDownRightPoint)
	xs_vec_add(fDownRightPoint, fAimOrigin, fDownRightPoint)
	//
	
	xs_vec_neg(fWallNormal, fWallNormal)
	
	new isUpRightPoint, isUpLeftPoint, isDownLeftPoint, isDownRightPoint
	isUpRightPoint = clRaceDeathKnight::getTraceToWall(fUpRightPoint, fWallNormal)
	isUpLeftPoint = clRaceDeathKnight::getTraceToWall(fUpLeftPoint, fWallNormal)
	isDownLeftPoint = clRaceDeathKnight::getTraceToWall(fDownLeftPoint, fWallNormal)
	isDownRightPoint = clRaceDeathKnight::getTraceToWall(fDownRightPoint, fWallNormal)
	
	if(isUpRightPoint && isUpLeftPoint && isDownLeftPoint && isDownRightPoint){	}
	else if(isUpRightPoint && isUpLeftPoint && !isDownLeftPoint && !isDownRightPoint)
	{
		new Float:check_step = (65.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		xs_vec_normalize(fUpNormal, fUpNormal)	// down
		xs_vec_neg(fUpNormal, fUpNormal)		// up
		
		if(!clRaceDeathKnight::checkWallInCycle(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fUpNormal, fWallNormal, check_step))
			return 0
	}
	else if(!isUpRightPoint && !isUpLeftPoint && isDownLeftPoint && isDownRightPoint)
	{
		new Float:check_step = (65.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		xs_vec_normalize(fUpNormal, fUpNormal)	// down
		
		if(!clRaceDeathKnight::checkWallInCycle(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fUpNormal, fWallNormal, check_step))
			return 0
	}
	else if(isUpRightPoint && isDownRightPoint && !isUpLeftPoint && !isDownLeftPoint)
	{
		new Float:check_step = (45.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		xs_vec_normalize(fRightNormal, fRightNormal)	// right
		
		if(!clRaceDeathKnight::checkWallInCycle(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fRightNormal, fWallNormal, check_step))
			return 0
	}
	else if(!isUpRightPoint && !isDownRightPoint && isUpLeftPoint && isDownLeftPoint)
	{
		new Float:check_step = (45.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		xs_vec_normalize(fRightNormal, fRightNormal)	// right
		xs_vec_neg(fRightNormal, fRightNormal)			// left
		
		clRaceDeathKnight::checkWallInCycle(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fRightNormal, fWallNormal, check_step)
	}
	else if((!isUpRightPoint && isDownRightPoint && !isUpLeftPoint && !isDownLeftPoint) ||
			(isUpRightPoint && isDownRightPoint && !isUpLeftPoint && isDownLeftPoint))
	{
		new Float:check_step_n1 = (45.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		new Float:check_step_n2 = (65.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		
		xs_vec_normalize(fRightNormal, fRightNormal)	// right
		xs_vec_normalize(fUpNormal, fUpNormal)			// down
		
		if(!clRaceDeathKnight::checkWallInCycleDouble(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fRightNormal, fUpNormal, fWallNormal, check_step_n1, check_step_n2))
			return 0
	}
	else if((!isUpRightPoint && !isDownRightPoint && !isUpLeftPoint && isDownLeftPoint) ||
			(!isUpRightPoint && isDownRightPoint && isUpLeftPoint && isDownLeftPoint))
	{
		new Float:check_step_n1 = (45.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		new Float:check_step_n2 = (65.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		
		xs_vec_normalize(fRightNormal, fRightNormal)	// right
		xs_vec_neg(fRightNormal, fRightNormal)			// left
		xs_vec_normalize(fUpNormal, fUpNormal)			// down
		
		if(!clRaceDeathKnight::checkWallInCycleDouble(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fRightNormal, fUpNormal, fWallNormal, check_step_n1, check_step_n2))
			return 0
	}
	else if((!isUpRightPoint && !isDownRightPoint && isUpLeftPoint && !isDownLeftPoint) ||
			(isUpRightPoint && !isDownRightPoint && isUpLeftPoint && isDownLeftPoint))
	{
		new Float:check_step_n1 = (45.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		new Float:check_step_n2 = (65.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		
		xs_vec_normalize(fRightNormal, fRightNormal)	// right
		xs_vec_neg(fRightNormal, fRightNormal)			// left
		xs_vec_normalize(fUpNormal, fUpNormal)			// down
		xs_vec_neg(fUpNormal, fUpNormal)				// up
		
		if(!clRaceDeathKnight::checkWallInCycleDouble(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fRightNormal, fUpNormal, fWallNormal, check_step_n1, check_step_n2))
			return 0
	}
	else if((isUpRightPoint && !isDownRightPoint && !isUpLeftPoint && !isDownLeftPoint) ||
			(isUpRightPoint && isDownRightPoint && isUpLeftPoint && !isDownLeftPoint))
	{
		new Float:check_step_n1 = (45.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		new Float:check_step_n2 = (65.0/ADDITIONAL_DIVIDER)/SURFACE_CHECK_NUM
		
		xs_vec_normalize(fRightNormal, fRightNormal)	// right
		xs_vec_normalize(fUpNormal, fUpNormal)			// down
		xs_vec_neg(fUpNormal, fUpNormal)				// up
		
	if(!clRaceDeathKnight::checkWallInCycleDouble(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fRightNormal, fUpNormal, fWallNormal, check_step_n1, check_step_n2))
			return 0
	}
	else return 0
	
		angle_vector(fWallAngles, ANGLEVECTOR_UP, fUpNormal)
	angle_vector(fWallAngles, ANGLEVECTOR_RIGHT, fRightNormal)
	
	xs_1_neg(fUpNormal[2])
	
	xs_vec_mul_scalar(fRightNormal, 45.0/2, fRightNormal)
	xs_vec_mul_scalar(fUpNormal, 65.0/2, fUpNormal)
	
	new Float:fTmpVec[3]
	xs_vec_add(fDownLeftPoint, fRightNormal, fTmpVec)
	xs_vec_add(fTmpVec, fUpNormal, fOutPointFSet)
	
	xs_vec_mul_scalar(fOrigWallNormal, 50.0, fTmpVec)
	xs_vec_add(fTmpVec, fOutPointFSet, fTmpVec)
	
	return 1
}

clRaceDeathKnight::checkWallInCycle(Float:fUpRightPoint[3], Float:fUpLeftPoint[3], Float:fDownLeftPoint[3], 
									Float:fDownRightPoint[3],Float:fNormal[3], Float:fWallNormal[3], Float:check_step)
{
	new Float:fTmpVec[3]
	xs_vec_mul_scalar(fNormal, check_step, fTmpVec)
	
	for(new i=1; i<=SURFACE_CHECK_NUM; i++)
	{
		xs_vec_add(fUpRightPoint, fTmpVec, fUpRightPoint)
		xs_vec_add(fUpLeftPoint, fTmpVec, fUpLeftPoint)
		xs_vec_add(fDownLeftPoint, fTmpVec, fDownLeftPoint)
		xs_vec_add(fDownRightPoint, fTmpVec, fDownRightPoint)
		
		if(clRaceDeathKnight::checkWall(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fWallNormal))
			return 1
	}
	
	return 0
}

clRaceDeathKnight::checkWallInCycleDouble(Float:fUpRightPoint[3], Float:fUpLeftPoint[3], Float:fDownLeftPoint[3], Float:fDownRightPoint[3],
										  Float:fNormal1[3], Float:fNormal2[3], Float:fWallNormal[3], Float:check_step1, Float:check_step2)
{
	new Float:fTmpVec1[3]
	xs_vec_mul_scalar(fNormal1, check_step1, fTmpVec1)
	
	new Float:fTmpVec2[3]
	xs_vec_mul_scalar(fNormal2, check_step2, fTmpVec2)
	
	for(new i=1; i<=SURFACE_CHECK_NUM; i++)
	{
		xs_vec_add(fUpRightPoint, fTmpVec1, fUpRightPoint)
		xs_vec_add(fUpRightPoint, fTmpVec2, fUpRightPoint)
		xs_vec_add(fUpLeftPoint, fTmpVec1, fUpLeftPoint)
		xs_vec_add(fUpLeftPoint, fTmpVec2, fUpLeftPoint)
		xs_vec_add(fDownLeftPoint, fTmpVec1, fDownLeftPoint)
		xs_vec_add(fDownLeftPoint, fTmpVec2, fDownLeftPoint)
		xs_vec_add(fDownRightPoint, fTmpVec1, fDownRightPoint)
		xs_vec_add(fDownRightPoint, fTmpVec2, fDownRightPoint)
		
		if(clRaceDeathKnight::checkWall(fUpRightPoint, fUpLeftPoint, fDownLeftPoint, fDownRightPoint, fWallNormal))
			return 1

	}
	
	return 0
}

clRaceDeathKnight::checkWall(Float:fUpRightPoint[3], Float:fUpLeftPoint[3], Float:fDownLeftPoint[3], Float:fDownRightPoint[3], Float:fWallNormal[3])
{
	if(
	clRaceDeathKnight::getTraceToWall(fUpRightPoint, fWallNormal)	&&
	clRaceDeathKnight::getTraceToWall(fUpLeftPoint, fWallNormal)	&&
	clRaceDeathKnight::getTraceToWall(fDownLeftPoint, fWallNormal)	&&
	clRaceDeathKnight::getTraceToWall(fDownRightPoint, fWallNormal)) 
	return 1;
	
	return 0;
}

clRaceDeathKnight::getWallNormal(id, Float:fNormal[3])
{
	new Float:fOrigin[3]
	pev(id, pev_origin, fOrigin)
	
	new Float:fAngles[3]
	pev(id, pev_v_angle, fAngles)
	angle_vector(fAngles, ANGLEVECTOR_FORWARD, fAngles)
	xs_vec_mul_scalar(fAngles, 9999.0, fAngles)
	
	new Float:fEndPos[3]
	xs_vec_add(fAngles, fOrigin, fEndPos)
	
	new ptr = create_tr2()	
	engfunc(EngFunc_TraceLine, fOrigin, fEndPos, IGNORE_MISSILE | IGNORE_MONSTERS | IGNORE_GLASS, id, ptr)
	
	new Float:vfNormal[3]
	get_tr2(ptr, TR_vecPlaneNormal, vfNormal)
	
	xs_vec_copy(vfNormal, fNormal)

	free_tr2(ptr);
}

clRaceDeathKnight::getTraceToWall(Float:fOrigin[3], Float:fVec[3])
{
	new Float:fOrigin2[3]
	xs_vec_mul_scalar(fVec, 1.0, fOrigin2)
	xs_vec_add(fOrigin2, fOrigin, fOrigin2)
	xs_vec_add(fOrigin2, fVec, fOrigin2)
	
	new ptr = create_tr2()
	engfunc(EngFunc_TraceLine, fOrigin, fOrigin2, IGNORE_MISSILE | IGNORE_MONSTERS | IGNORE_GLASS, 0, ptr)
	
	new Float:fFrac
	get_tr2(ptr, TR_flFraction, fFrac)
	
	free_tr2(ptr)
	
	if(fFrac == 1.0)
		return 0
	
	return 1
}

// *******************************************************
// Скил 2 уровня - Blood Boil - Вскипание крови - наступательный
// *******************************************************
public clRaceDeathKnight::skillBloodBoil(idUser)
{
	if (task_exists(idUser + clRaceDeathKnight::taskID_BLOOD_BOIL) == 0 )
	{
		clRaceDeathKnight::setTaskBloodBoilSkill(idUser);
	}
}

public clRaceDeathKnight::setTaskBloodBoilSkill( idUser )
{
	if (idUser >= clRaceDeathKnight::taskID_BLOOD_BOIL)
		idUser -= clRaceDeathKnight::taskID_BLOOD_BOIL;

	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return;
	
	new iSkillLevel = SM_GetSkillLevel( idUser, SKILL_DEATH_KNIGHT_BLOOD_BOIL );
	if (iSkillLevel <= 0 || arrBoolData[idUser][PB_ISFROZENSKILL] == true || isDisabledSkillsOnMap(idUser,SKILL_DEATH_KNIGHT_BLOOD_BOIL) == true)
		return;

	if (is_user_alive(idUser))
	{
		new Float:fBloodboil = ArrayGetCell(arrBloodBoil,iSkillLevel-1);
		set_task(fBloodboil, "_setTaskBloodBoilSkill", clRaceDeathKnight::taskID_BLOOD_BOIL + idUser);
	}
	
	if ( arrBoolData[idUser][PB_HEXED] )
		return;

	new arrPlayers[32], iNumberOfPlayers, idTarget, ptTargetOrigin[3], ptOrigin[3];
	new iTeam = get_user_team( idUser );

	get_user_origin( idUser, ptOrigin );
	get_players(arrPlayers, iNumberOfPlayers, "a" );
	
	for ( new i = 0; i < iNumberOfPlayers; i++ )
	{
		idTarget = arrPlayers[i];
		
		if(idUser == idTarget)
			continue;

		if ( arrBoolData[idTarget][PB_ISCONNECTED] && get_user_team(idTarget) != iTeam)
		{
			if (is_user_alive(idTarget))
			{
				get_user_origin(idTarget, ptTargetOrigin );
			
				if (get_distance(ptOrigin, ptTargetOrigin) < 250 )
				{
					//get_user_origin(idTarget, ptOrigin);
			
					if (clHP:getUserHealth(idTarget) > iMaxHPVictim )
					{
						new iColorIndex = 70;

						/*
						new iRaceID = arrIntData[idTarget][P_RACE];

						switch (iRaceID)
						{
							case RACE_NONE:			iColorIndex = 70;		// Нет расы
							case RACE_UNDEAD:		iColorIndex = 128;		// Undead
							case RACE_HUMAN:		iColorIndex = 70;		// Human
							case RACE_ORC:			iColorIndex = 110;		// Orc
							case RACE_ELF:			iColorIndex = 110;		// Night Elf
							case RACE_BLOOD:		iColorIndex = 110;		// Blood Mage
							case RACE_SHADOW:		iColorIndex = 144;		// Shadow Hunter
							case RACE_WARDEN:		iColorIndex = 144;		// Warden
							case RACE_CRYPT:		iColorIndex = 128;		// Crypt Lord
							case RACE_CHAMELEON:	iColorIndex = 70;		// Chameleon
							case RACE_FROST_MAGE:	iColorIndex = 244;		// Frost Mage
							case RACE_DEATH_KNIGHT:	iColorIndex = 128;		// Death knight
						}
						*/

						clRaceDeathKnight::setEffectDrawBloodBoil(ptTargetOrigin,iColorIndex);

						WC3_Damage(idTarget, idUser, /*дамаг*/ 1, CSW_BLOODBOIL, -1 ); 
					}
				}
			}
		}
	}

	return;
}
//Отрисовка крови
clRaceDeathKnight::setEffectDrawBloodBoil(ptOrigin[3],iColorIndex)
{
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(TE_BLOODSTREAM);
	write_coord(ptOrigin[0]);
	write_coord(ptOrigin[1]);
	write_coord(ptOrigin[2]+10);
	write_coord(random_num(-360,360)); // x
	write_coord(random_num(-360,360)); // y
	write_coord(-10); // z
	write_byte(iColorIndex); // Цвет
	write_byte(random_num(50,100)); // Скорость
	message_end();
}

//			client_print(idVictim,print_chat,"Damage: %.1f health:%d",fDamage,clHP:getUserHealth(idVictim))


// *******************************************************
// Скил 3 уровня - Лик смерти - Death Coil - защитный
// *******************************************************
public clRaceDeathKnight::skillDeathCoil(idVictim,idAttacker)
{	
	new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_DEATH_KNIGHT_DEATH_COIL);
	if (iSkillLevel > 0 && is_user_alive( idAttacker ) && arrBoolData[idAttacker][PB_ISCONNECTED])
	{
		if(isDisabledSkillsOnMap(idVictim,SKILL_DEATH_KNIGHT_DEATH_COIL) == true)
			return;

		if(get_user_team(idVictim) != get_user_team(idAttacker) )
		{
			new iTypeDC = random_num(1,2);

			switch(iTypeDC)
			{
				case eDcHP:
				{
					InitDeathCoil(idVictim,idAttacker,eDcHP);
				}
				case eDcArmor:
				{
					InitDeathCoil(idVictim,idAttacker,eDcArmor);
				}
			}
		}
		
	}
}


// *******************************************************
// Супер навык - Власть крови - Blood Presence
// *******************************************************
public clRaceDeathKnight::ultBloodPresence(idUser)
{
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

	if (iLosesCharge > 0)
	{
		ULT_RemoveCharge(iLosesCharge);

		fResetUltimateTimerDivider(idUser);

		ULT_Blocked( idUser );

		return;
	}

	EffectRestoreHealth(idUser);
	
	Create_ScreenFade(idUser, (1<<10), (1<<10), (1<<12), 0, 255, 0, 255 );

	emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_HEALTH_POTION], 1.0, ATTN_NORM, 0, PITCH_NORM );

	//fPercentHP	- Выносливость повышается на 30%
	new iMaxHealth = clHP:getRaceMaxHealth(idUser);
	new iCurrentHealth =  clHP:getUserHealth(idUser);
	new iBonusHp = floatround(iCurrentHealth * fPercentHP);
	
	if((iCurrentHealth + iBonusHp) > iMaxHealth)
		clHP:setUserHealth(idUser,iMaxHealth);
	else
		clHP:setUserHealth(idUser,iCurrentHealth + iBonusHp);


	//fPercentArmor	- Показатель брони повышается на 55%
	new iMaxArmor = clAr:getRaceMaxArmor(idUser);
	new CsArmorType:tArmor;
	new iCurrentArmor =  clAr:getUserArmor(idUser,tArmor);
	new iBonusArmor = floatround(iCurrentArmor * fPercentArmor);
	
	if((iCurrentArmor + iBonusArmor) > iMaxArmor)
		clAr:setUserArmor(idUser,iMaxArmor);
	else
		clAr:setUserArmor(idUser,iCurrentArmor + iBonusArmor);


	fResetUltimateTimerDivider(idUser);

	//Сброс активности дамага
	clRaceDeathKnight::bIsDamageBP[idUser] = false;
	clRaceDeathKnight::bIsUnDamageBP[idUser] = true;

	//Восстановление предыдущих параметров
	new arrParameters[4];

	arrParameters[0] = iCurrentHealth;
	arrParameters[1] = iCurrentArmor;
	arrParameters[2] = idUser;
	arrParameters[3] = clRaceDeathKnight::taskID_BLOOD_PRESENCE + idUser;

	new Float:fTimeBP = float(ArrayGetCell(arrIntUltimateTimer,RACE_DEATH_KNIGHT)) / 2.0;
	set_task(fTimeBP,"_setTaskRestoreBP", clRaceDeathKnight::taskID_BLOOD_PRESENCE + idUser,arrParameters,4);

	return;

}

public clRaceDeathKnight::setTaskRestoreBP(arrParametersAux[4])
{
	new idUser = arrParametersAux[2];

	if (!arrBoolData[idUser][PB_ISCONNECTED] && !is_user_alive(idUser))
		return;

	clRaceDeathKnight::bIsUnDamageBP[idUser] = false;

	if(clRaceDeathKnight::bIsDamageBP[idUser] == true)
		return;

	new iUserOldHealth = arrParametersAux[0];
	new iUserOldArmor = arrParametersAux[1];

	new iUserBonusHealth = floatround(iUserOldHealth * fPercentHP );
	new iUserBonusArmor = floatround(iUserOldArmor * fPercentArmor);

	//Восстановление здоровья
	new iMinHealth = clHP:getRaceMinHealth(idUser);
	new iCurrentHealth =  clHP:getUserHealth(idUser);
	new iUserNewHealth = iCurrentHealth - iUserBonusHealth;

	if(iUserNewHealth <= iMinHealth)
		clHP:setUserHealth(idUser,iMinHealth);
	else
		clHP:setUserHealth(idUser,iUserNewHealth);


	//Восстановление брони
	new iMinArmor = clAr:getRaceMinArmor(idUser);
	new CsArmorType:tArmor;
	new iCurrentArmor =  clAr:getUserArmor(idUser,tArmor);
	new iUserNewArmor = iCurrentArmor - iUserBonusArmor;
	
	if(iUserNewArmor <= iMinArmor)
		clAr:setUserArmor(idUser,iMinArmor);
	else
		clAr:setUserArmor(idUser,iUserNewArmor);
}

