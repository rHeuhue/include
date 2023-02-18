// ******************************************************************
// Раса: Варлок (Race: Warlock) Functions
// ******************************************************************


//Инициализация скилов Race: Warlock (Варлок)
public clWarlock::setSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	g_SkillOwner[SKILL_WARLOCK_1			]	= RACE_WARLOCK;
	g_SkillOwner[SKILL_WARLOCK_2			]	= RACE_WARLOCK;
	g_SkillOwner[SKILL_WARLOCK_3			]	= RACE_WARLOCK;
	g_SkillOwner[ULTIMATE_WARLOCK			]	= RACE_WARLOCK;
//	g_SkillOwner[PASS_WARLOCK				]	= RACE_WARLOCK;

	g_SkillType[SKILL_WARLOCK_1				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_WARLOCK_2				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_WARLOCK_3				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_WARLOCK			]	= SKILL_TYPE_ULTIMATE;
//	g_SkillType[PASS_WARLOCK				]	= SKILL_TYPE_PASSIVE;

	g_SkillOrder[SKILL_WARLOCK_1			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_WARLOCK_2			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_WARLOCK_3			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_WARLOCK			]	= SKILL_POS_4;
//	g_SkillOrder[PASS_WARLOCK				]	= SKILL_POS_NONE;
	
}

// **********************************************************************
// Скил 1 уровня - Fatal Bonds - Фатальная связь
// **********************************************************************
clWarlock::skillFatalBonds(const idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser))
		return;

	if(isDisabledSkillsOnMap(idUser,SKILL_WARLOCK_1) == true)
		return;

	new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_WARLOCK_1);
	if (iSkillLevel > 0)
	{			
		new Float:fFatalBonds = ArrayGetCell(arrFatalBonds,iSkillLevel-1);
		if (random_float(fFatalBondsSkill1MinPercent,fFatalBondsSkill1MaxPercent) <= fFatalBonds )		
			set_task(1.0, "_taskActiveFatalBonds", clWarlock::tID_FATAL_BONDS + idUser);
	}
	
}

public clWarlock::taskActiveFatalBonds(idUser)
{
	if (idUser >= clWarlock::tID_FATAL_BONDS)
		idUser -= clWarlock::tID_FATAL_BONDS;

	new Float:ptOriginPlayer[3];
	pev(idUser, pev_origin, ptOriginPlayer);
	Create_TE_BEAMDISK(ptOriginPlayer, 40, arrIdSprites[SPR_ROGUE_SHURIKEN], 0, 9, 5,   15,    3,    255, 255, 255,    255,  0, 0);
	
	//Поиск жертв
	new arrPlayers[32], iNumberOfPlayers;
	new iTeamCurrentUser = get_user_team(idUser);

	if(iTeamCurrentUser == TEAM_T)
		get_players(arrPlayers, iNumberOfPlayers, "e","CT");
	if(iTeamCurrentUser == TEAM_CT)
		get_players(arrPlayers, iNumberOfPlayers, "e","TERRORIST");
	
	new iRand = random_num(0,iNumberOfPlayers - 1);
	new idVictim = arrPlayers[iRand];

	if(!SHARED_ValidPlayer(idVictim))
		return;

	if(!is_user_alive(idVictim) || !is_user_connected(idVictim))
		return;

	new iTeamVictim = get_user_team(idVictim);

	new ptVictimOrigin[3];
	get_user_origin(idVictim, ptVictimOrigin);

	new Array:arrIdFindVictim;
	arrIdFindVictim = ArrayCreate(1, 1);
	
	new idOldFindNextVictim = idVictim;
	new idNewFindNextVictim = clDisruptor::getIdFindNextVictim(idVictim,arrPlayers,iNumberOfPlayers,iTeamVictim,ptVictimOrigin,arrIdFindVictim,iFatalBondsRadius);
					
	while(idNewFindNextVictim > 0)
	{				
		if(idNewFindNextVictim > 0)
		{						
			Create_TE_BEAMENTS(idOldFindNextVictim, idNewFindNextVictim, arrIdSprites[SPR_LIGHTNING], 0, 15, 5, 35, 1,  255,0,0,   255, 0);
			WC3_Damage(idNewFindNextVictim,idUser,iFatalBondsDmg, CSW_FATAL_BONDS, -1);

			emit_sound(idNewFindNextVictim,CHAN_STATIC, arrStrSounds[SOUND_FATAL_BONDS], 0.3, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			idOldFindNextVictim = idNewFindNextVictim;

		}

		idNewFindNextVictim = clDisruptor::getIdFindNextVictim(idVictim,arrPlayers,iNumberOfPlayers,iTeamVictim,ptVictimOrigin,arrIdFindVictim,iFatalBondsRadius);

	}		

}



// **********************************************************************
// Скил 2 уровня - Shadow Word  - Проклятье призрака
// **********************************************************************
public clWarlock::skillShadowWord(const idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser))
		return;

	if(arrIntData[idUser][PB_SHADOW_WORD_NUM] >= iShadowWordNum)
		return;

	if(isDisabledSkillsOnMap(idUser,SKILL_WARLOCK_2) == true)
		return;

	arrIntData[idUser][PB_SHADOW_WORD_TIME] += 1;

	new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_WARLOCK_2);
	if (iSkillLevel > 0 && arrIntData[idUser][PB_SHADOW_WORD_TIME] >= iShadowWordTime)
	{
		new Float:fShadowWord = ArrayGetCell(arrShadowWord,iSkillLevel-1);
		if (random_float(fShadowWordSkill2MinPercent,fShadowWordSkill2MaxPercent) <= fShadowWord )		
		{				
			arrIntData[idUser][PB_SHADOW_WORD_NUM] += 1;
			
			clWarlock::fActiveSkillShadowWord(idUser);

		}//if
		
		arrIntData[idUser][PB_SHADOW_WORD_TIME] = 0;

	}//if

}

public clWarlock::fActiveSkillShadowWord(const idUser)
{

	new arrPlayers[32], iNumberOfPlayers;
	get_players(arrPlayers, iNumberOfPlayers, "a");

	new iTeamCurrentUser = get_user_team(idUser);

	new ptUserOrigin[3];
	get_user_origin(idUser, ptUserOrigin);

	new ptTargetOrigin[3];
	new idTarget;

	for (new i = 0; i < iNumberOfPlayers; i++ )
	{
		idTarget = arrPlayers[i];
		
		if (is_user_alive(idTarget) && arrBoolData[idTarget][PB_ISCONNECTED])
		{
			//если игрок своей команды
			if (get_user_team(idTarget) == iTeamCurrentUser)
			{				
				get_user_origin(idTarget, ptTargetOrigin);
									
				if (get_distance(ptUserOrigin, ptTargetOrigin) < iShadowWordRadius)
				{	
					new iMinHealth = clHP:getRaceMinHealth(idTarget);
					new iCurrentHealth =  clHP:getUserHealth(idTarget);
					new iBonusHp = iShadowWordHp;

					if (iCurrentHealth < iMinHealth)
					{
						if( (iCurrentHealth + iBonusHp) > iMinHealth )
							clHP:setUserHealth(idTarget,iMinHealth);
						else
							clHP:setUserHealth(idTarget,iCurrentHealth + iBonusHp);
					}

					Create_TE_IMPLOSION(ptTargetOrigin, 100, 8, 1);

					emit_sound(idTarget,CHAN_STATIC, arrStrSounds[SOUND_SHADOW_WORD], 0.5, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
									
				}//if
							
			}//if
			//если игрок - противник
			else if(get_user_team(idTarget) != iTeamCurrentUser)
			{
				WC3_Damage(idTarget,idUser,iShadowWordDmg, CSW_SHADOW_WORD, -1);

				emit_sound(idTarget,CHAN_STATIC, arrStrSounds[SOUND_SHADOW_WORD], 0.5, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
				
			}//if

		}//if

	}//for

	return 0;

}



// **********************************************************************
// Скил 3 уровня - Flaming Fists - Пылающий кулак
// **********************************************************************
public clWarlock::skillFlamingFists(const idVictim,const idAttacker)
{	
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim))
		return;

	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;

	if(isDisabledSkillsOnMap(idAttacker,SKILL_WARLOCK_3) == true)
		return;

	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_WARLOCK_3);
	if (iSkillLevel > 0)
	{
		new Float:fFlamingFists = ArrayGetCell(arrFlamingFists,iSkillLevel-1);
		if (random_float(fFlamingFistsSkill3MinPercent,fFlamingFistsSkill3MaxPercent) <= fFlamingFists )		
		{			
			emit_sound(idVictim,CHAN_STATIC, arrStrSounds[SOUND_FLAMING_FISTS], 0.8, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			new iCurrentArmor = clAr:getArmorNum(idVictim);

			if(iCurrentArmor > 0)
				clWarlock::fStartFlamingFists(idVictim, idAttacker,enTypeDmg:eArmor,3,arrIdSprites[SPR_FL_FISTS_ARMOR]);
			else
				clWarlock::fStartFlamingFists(idVictim, idAttacker,enTypeDmg:eDmg,iFflamingFistsNum,arrIdSprites[SPR_FL_FISTS_DMG]);
			
		}//if
		
	}//if
	
}

public clWarlock::fStartFlamingFists(const idVictim, const idAttacker,const iTypeDmg, const iCountFire, const iIndexSpriteFire)
{
	new arrParams[5];
	arrParams[0] = iCountFire; // начальный счетчик горения
	arrParams[1] = idAttacker; // ID атакующего
	arrParams[2] = idVictim + clWarlock::tID_FLAMING_FIRST;
	arrParams[3] = iTypeDmg;	//тип урона
	arrParams[4] = iIndexSpriteFire;	//индекс спрайта

	if (task_exists(arrParams[2]))
		return;

	set_task(0.1, "_taskFlamingFists",arrParams[2], arrParams, sizeof arrParams);

}

public clWarlock::taskFlamingFists(arrParams[5])
{
	new idAttacker = arrParams[1];
	new idVictim = arrParams[2];
	new iTypeDmg = arrParams[3];
	new iIndexSpriteFire = arrParams[4];

	if (idVictim >= clWarlock::tID_FLAMING_FIRST )
		idVictim -= clWarlock::tID_FLAMING_FIRST;

	if (!is_user_alive(idVictim))
		return;

	new Float:ptOriginUser[3];
	pev(idVictim, pev_origin, ptOriginUser);

	//Если игрок находится в воде или закончился таймер горения, вырубаем огонь
	if ((pev(idVictim, pev_flags) & FL_INWATER) || WARLOCK_FLAME_DURATION <= 0)
	{
		// Отрисовка дыма
		engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, ptOriginUser, 0);
		write_byte(TE_SMOKE); // TE id
		engfunc(EngFunc_WriteCoord, ptOriginUser[0]); // x
		engfunc(EngFunc_WriteCoord, ptOriginUser[1]); // y
		engfunc(EngFunc_WriteCoord, ptOriginUser[2]-50.0); // z
		write_short(arrIdSprites[SPR_SMOKE_PRIEST]); // sprite
		write_byte(random_num(15, 20)); // scale
		write_byte(random_num(10, 20)); // framerate
		message_end();
		
		return;
	}

	switch(iTypeDmg)
	{
		case eArmor:
		{
			clAr:setUserArmor(idVictim, 0);
			WARLOCK_FLAME_DURATION = 0;
		
		}
		case eDmg:
		{
			WC3_Damage(idVictim,idAttacker,iFlamingFistsDmg, CSW_FLAMING_FISTS, -1);
		}
	}	
	
	//Отрисовка огня
	engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, ptOriginUser, 0);
	write_byte(TE_SPRITE); // TE id
	engfunc(EngFunc_WriteCoord, ptOriginUser[0] + random_float(-5.0, 5.0)); // x
	engfunc(EngFunc_WriteCoord, ptOriginUser[1] + random_float(-5.0, 5.0)); // y
	engfunc(EngFunc_WriteCoord, ptOriginUser[2] + random_float(-10.0, 10.0)); // z
	write_short(iIndexSpriteFire); // sprite
	write_byte(random_num(5, 10)); // scale
	write_byte(200); // brightness
	message_end();
	
	//Убавляем счетчик на единицу
	WARLOCK_FLAME_DURATION -= 1;

	set_task(0.5, "_taskFlamingFists", arrParams[2], arrParams, sizeof arrParams);
}


// **********************************************************************
// Скил 4 уровня - xxx - xxx
// **********************************************************************
//SKILL_I_98 = Описание скила 98(не используется)


// *******************************************************
// Супер навык - Жертвоприношение - Permanent Immolation
// *******************************************************
public clWarlock::ultPermanentImmolation(const idAttacker, const idVictim)
{		
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
		return;

	if(!is_user_alive(idVictim) || !is_user_connected(idVictim)) 
		return;

	emit_sound(idAttacker,CHAN_STATIC, arrStrSounds[SOUND_PERM_IMMOL], 1.0, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

	clWarlock::fStartPermImmolation(idAttacker,idVictim);

	//Сброс счетчика
	fResetUltimateTimerDivider(idAttacker);

}

public clWarlock::fStartPermImmolation(const idUser,const idVictim)
{
	new arrParamsPI[5];
	arrParamsPI[0] = 5; // начальный счетчик
	arrParamsPI[1] = idUser + clWarlock::tID_PERM_IMMOLATION;
	arrParamsPI[2] = idVictim;
	
	pev(idUser, pev_origin, ptOriginWarlock[idUser]);

	pev(idUser, pev_v_angle, fAnglesWarlock[idUser]);
	engfunc(EngFunc_MakeVectors, fAnglesWarlock[idUser]);
	global_get(glb_v_forward, fAnglesWarlock[idUser]);

	new Float:ptOriginVictim[3];
	pev(idVictim, pev_origin, ptOriginVictim);

	new Float:fDistMin = (get_distance_f(ptOriginWarlock[idUser], ptOriginVictim) * 1.7) / 5;

	arrParamsPI[3] = floatround(fDistMin);
	arrParamsPI[4] = 0;

	if (task_exists(arrParamsPI[1]))
		return;

	set_task(0.1, "_taskPermImmolation",arrParamsPI[1], arrParamsPI, sizeof arrParamsPI);

}

public clWarlock::taskPermImmolation(arrParamsPI[5])
{
	new idUser = arrParamsPI[1];
	
	if (idUser >= clWarlock::tID_PERM_IMMOLATION )
		idUser -= clWarlock::tID_PERM_IMMOLATION;

	if (!is_user_alive(idUser))
		return;

	arrParamsPI[4] += arrParamsPI[3]; //Расстояние на сколько строить друг от друга

	//Если счетчик доходит до нуля, вырубаем
	if (WARLOCK_PERM_IMMOLATION <= 0)
		return;
	
	new Float:fDistMin = float(arrParamsPI[4]);

	//Создание сущности
	clWarlock::fCreatePermImmolation(PERM_IMMOL_WARLOCK_CLASSNAME,idUser,fDistMin,arrIdSprites[SPR_FL_FISTS_ARMOR],0.087266462599716);//5 - Левый
	clWarlock::fCreatePermImmolation(PERM_IMMOL_WARLOCK_CLASSNAME,idUser,fDistMin,arrIdSprites[SPR_FL_FISTS_DMG],0.0); // Средний
	clWarlock::fCreatePermImmolation(PERM_IMMOL_WARLOCK_CLASSNAME,idUser,fDistMin,arrIdSprites[SPR_FL_FISTS_ARMOR],6.1959188445799);//355 - Правый
	
	//Убавляем счетчик на единицу
	WARLOCK_PERM_IMMOLATION -= 1;

	set_task(0.1, "_taskPermImmolation", arrParamsPI[1], arrParamsPI, sizeof arrParamsPI);
}

bool:clWarlock::fCreatePermImmolation(const szClassname[],const idUser,const Float:fRadiusSpawn,
									  const iModelIndex,const Float:fAngleRotate)
{	
	new Float:fAngles[3];
	fAngles = uFloatPointToFloat(fAnglesWarlock[idUser]);

	new Float:ptOriginPlayer[3];
	ptOriginPlayer = uFloatPointToFloat(ptOriginWarlock[idUser]);

	xs_vec_mul_scalar(fAngles, fRadiusSpawn, fAngles);
	fAngles = uRotate(fAngleRotate,fAngles);
	xs_vec_add(ptOriginPlayer, fAngles, ptOriginPlayer);

	new idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	
	if(!pev_valid(idEntity)) 
		return false;
		
	set_pev(idEntity, pev_classname, szClassname);								// Задаем класс создаваемой сущности
	set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
	set_pev(idEntity, pev_modelindex, iModelIndex);								// Задаем индекс создаваемой сущности
	fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти

	set_pev(idEntity, pev_movetype, MOVETYPE_TOSS);
	set_pev(idEntity, pev_solid, SOLID_BBOX);
		
	set_pev(idEntity, pev_gravity, 0.8);
	set_pev(idEntity,pev_iuser1,iPlasmaFieldNumTouch);		// Количество отскоков от стен
	
	set_pev(idEntity, pev_scale, 0.1);
	set_pev(idEntity, pev_health, 100.0);
	set_pev(idEntity, pev_takedamage, DAMAGE_YES);
		
	set_pev(idEntity, pev_origin, ptOriginPlayer);

	return true;

}


// ******************************************************************
// Создание и управление эффектами для скила
// ******************************************************************
public touchPermImmolation(idEntity, idWorldPlayer)
{
	//client_print(0,print_chat,"idEntity: %d | idWorldPlayer: %d",idEntity,idWorldPlayer);
	//log_amx("idEntity: %d | idWorldPlayer: %d",idEntity,idWorldPlayer);

	if (!pev_valid(idEntity))
		return PLUGIN_HANDLED;

	new idOwner = pev(idEntity, pev_owner);
			
	new Float:ptOriginEntity[3];
	pev(idEntity, pev_origin, ptOriginEntity);

	new Float:ptOriginOwner[3];
	pev(idOwner, pev_origin, ptOriginOwner);

/*
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_BEAMCYLINDER);
	engfunc(EngFunc_WriteCoord, ptOriginEntity[0]);// center position (X)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[1]);// center position (Y)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[2]);// center position (Z)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[0]);// axis and radius (X)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[1]);// axis and radius (Y)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[2] + 75.0);// axis and radius (Z)
	write_short(arrIdSprites[SPR_PLASMA_FIELD]) ;
	write_byte(0);// starting frame
	write_byte(10);// frame rate in 0.1's
	write_byte(3); // life in 0.1's
	write_byte(20); // line width in 0.1's
	write_byte(0); // noise amplitude in 0.01's
	write_byte(211);// color (red)
	write_byte(233);// color (green)
	write_byte(19);// color (blue)
	write_byte(255);// brightness
	write_byte(0);// scroll speed in 0.1's
	message_end();
*/

	//Create_TE_SPRITETRAIL(start[3], end[3], iSprite, count, life, scale, velocity, random )
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_SPRITETRAIL);
	engfunc(EngFunc_WriteCoord, ptOriginEntity[0]);
	engfunc(EngFunc_WriteCoord, ptOriginEntity[1]);
	engfunc(EngFunc_WriteCoord, ptOriginEntity[2]);
	engfunc(EngFunc_WriteCoord, ptOriginEntity[0]);
	engfunc(EngFunc_WriteCoord, ptOriginEntity[1]);
	engfunc(EngFunc_WriteCoord, ptOriginEntity[2] + 5);
	write_short(arrIdSprites[SPR_PERM_IMMOL]);
	write_byte(10);
	write_byte(1);
	write_byte(1);
	write_byte(20);
	write_byte(14);
	message_end();

	

	new idFindPlayer;
	while ((idFindPlayer = engfunc(EngFunc_FindEntityInSphere, idFindPlayer, ptOriginEntity, fPermImmolationRadius)))
	{
		if(!SHARED_ValidPlayer(idFindPlayer))
			continue;

		if (get_user_team(idFindPlayer) != get_user_team(idOwner) && is_user_alive(idFindPlayer))
		{
			WC3_Damage(idFindPlayer,idOwner,iPermImmolationDmg, CSW_PERM_IMMOLATION, -1);
			ExecuteHamB(Ham_TakeDamage, idFindPlayer, idEntity, idOwner, 0.0, DMG_BURN);
						
			emit_sound(idEntity,CHAN_STATIC, arrStrSounds[SOUND_SHRAPNEL_DAMAGE], 0.1, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			break;
		}//if

	}//while
	
	remove_entity(idEntity);

	return PLUGIN_CONTINUE;
}
