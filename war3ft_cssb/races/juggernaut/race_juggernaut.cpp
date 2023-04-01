// ******************************************************************
// Раса: Джагернаут (Race: Juggernaut) Functions
// ******************************************************************


//Инициализация скилов Race: Juggernaut (Джагернаут)
public clJuggernaut::setSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	g_SkillOwner[SKILL_JUGGERNAUT_1			]	= RACE_JUGGERNAUT;
	g_SkillOwner[SKILL_JUGGERNAUT_2			]	= RACE_JUGGERNAUT;
	g_SkillOwner[SKILL_JUGGERNAUT_3			]	= RACE_JUGGERNAUT;
	g_SkillOwner[ULTIMATE_JUGGERNAUT		]	= RACE_JUGGERNAUT;
	g_SkillOwner[PASS_JUGGERNAUT			]	= RACE_JUGGERNAUT;

	g_SkillType[SKILL_JUGGERNAUT_1			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_JUGGERNAUT_2			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_JUGGERNAUT_3			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_JUGGERNAUT			]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_JUGGERNAUT				]	= SKILL_TYPE_PASSIVE;

	g_SkillOrder[SKILL_JUGGERNAUT_1			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_JUGGERNAUT_2			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_JUGGERNAUT_3			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_JUGGERNAUT		]	= SKILL_POS_4;
	g_SkillOrder[PASS_JUGGERNAUT			]	= SKILL_POS_NONE;


	//Максимальное количество зарядов
	arrSkillChargeMax[SKILL_JUGGERNAUT_1	]	= iJuggernautChargeMax_1;
	arrSkillChargeMax[SKILL_JUGGERNAUT_2	]	= iJuggernautChargeMax_2;
	arrSkillChargeMax[SKILL_JUGGERNAUT_3	]	= iJuggernautChargeMax_3;

	//Минимальное количество зарядов
	arrSkillChargeMin[SKILL_JUGGERNAUT_1	]	= iJuggernautChargeMin_1;
	arrSkillChargeMin[SKILL_JUGGERNAUT_2	]	= iJuggernautChargeMin_2;
	arrSkillChargeMin[SKILL_JUGGERNAUT_3	]	= iJuggernautChargeMin_3;

	//Счетчик через сколько шанс получить заряд
	arrSkillCount[SKILL_JUGGERNAUT_1		]	= iJuggernautCount_1;
	arrSkillCount[SKILL_JUGGERNAUT_2		]	= iJuggernautCount_2;
	arrSkillCount[SKILL_JUGGERNAUT_3		]	= iJuggernautCount_3;
	
}

//Инициализация начального количества зарядов у игрока
public clJuggernaut::setChargeNum(idUser)//добавлена в war3ft.cpp ( WC3_PlayerInit( idUser ) )
{
	arrSkillChargeNum[idUser][SKILL_JUGGERNAUT_1] = iJuggernautChargeMin_1;
	arrSkillChargeNum[idUser][SKILL_JUGGERNAUT_2] = iJuggernautChargeMin_2;
	arrSkillChargeNum[idUser][SKILL_JUGGERNAUT_3] = iJuggernautChargeMin_3;

//	client_print(idUser,print_chat,"setChargeNum");
}

//Добавляем заряд скилу. Функция размещается в зависимости от того,
//каким способом будет даваться заряд (время,дамаг,убийство и тд)
clJuggernaut::addSkillCharge(const iSkillID,const idUser,const iNumIncrement = 1)
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
		case SKILL_JUGGERNAUT_1:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser,iSkillID);
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
				new Float:fSkillChance = ArrayGetCell(arrHealingWard,iSkillLevel-1);
				if (random_float(fJuggernautSkill1MinPercent,fJuggernautSkill1MaxPercent) <= fSkillChance )		
				{
					arrSkillChargeNum[idUser][iSkillID] += iNumIncrement;
					WC3_ShowBar(idUser);
				}
			}
		}
		case SKILL_JUGGERNAUT_2:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser, iSkillID );
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
				new Float:fSkillChance = ArrayGetCell(arrCriticalBlade,iSkillLevel-1);
				if (random_float(fJuggernautSkill2MinPercent,fJuggernautSkill2MaxPercent) <= fSkillChance)		
				{
					arrSkillChargeNum[idUser][iSkillID] += iNumIncrement;
					WC3_ShowBar(idUser);
				}
			}
		}
		case SKILL_JUGGERNAUT_3:
		{			
			new iSkillLevel = SM_GetSkillLevel(idUser, iSkillID );
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
			
				new Float:fSkillChance = ArrayGetCell(arrDemonBlade,iSkillLevel-1);
				if (random_float(fJuggernautSkill3MinPercent,fJuggernautSkill3MaxPercent) <= fSkillChance )		
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

// **********************************************************************
// Скил 1 уровня - Healing Ward - Исцеляющий идол
// **********************************************************************
clJuggernaut::skillHealingWard(const idUser,const iSkillID)
{
	
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
		return;

	if(isDisabledSkillsOnMap(idUser,iSkillID) == true)
		return;

	new szSkillName[64];
	fGetSkillName(iSkillID,szSkillName, charsmax(szSkillName));

	if(isEntUserOwner(HEALING_WARD_CLASSNAME,idUser))
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ACTIVE_SKILLS",szSkillName);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		return;
	}

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idUser][iSkillID] <= 0)
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MIN_CHARGE",arrSkillChargeMin[iSkillID]);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		return;
	}

	if(arrSkillChargeNum[idUser][iSkillID] < arrSkillChargeMin[iSkillID])
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MIN_CHARGE",arrSkillChargeMin[iSkillID]);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		return;
	}
	
	new Float:ptOriginPlayer[3];
	pev(idUser, pev_origin, ptOriginPlayer);
    
	new Float:fAngles[3];
	pev(idUser, pev_v_angle, fAngles);
	engfunc(EngFunc_MakeVectors, fAngles);
	global_get(glb_v_forward, fAngles);
	xs_vec_mul_scalar(fAngles, 64.0, fAngles);
	xs_vec_add(ptOriginPlayer, fAngles, ptOriginPlayer);

	new bool:bIsHullVacant = uIsHullVacant(ptOriginPlayer,HULL_LARGE);
	
	if(bIsHullVacant == false)//нельзя создать сущность т.к. мешает стена,пол...
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_NO_SPAWN_IDOL");
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		return;
	}

	emit_sound(idUser,CHAN_STATIC, arrStrSounds[SOUND_HEALING_WARD], 0.9, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);


	new idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
    
	if(!pev_valid(idEntity))
		return;

	set_pev(idEntity, pev_classname, HEALING_WARD_CLASSNAME);
	engfunc(EngFunc_SetModel, idEntity, arrStrModels[MDL_HEALINGWARD]);
	set_pev(idEntity, pev_solid, SOLID_TRIGGER);
	set_pev(idEntity, pev_movetype, MOVETYPE_TOSS);
	set_pev(idEntity, pev_sequence, 1);
	set_pev(idEntity, pev_animtime, 1.0);
	set_pev(idEntity, pev_framerate, 1.0);
	    
	new Float:fMinSizeBox[3] =  {-13.490000, -0.540000, -7.150000};
	new Float:fMaxSizeBx[3] =  {16.660000, 85.169998, 3.350000};
	
	set_pev(idEntity, pev_mins, fMinSizeBox);
	set_pev(idEntity, pev_maxs, fMaxSizeBx);
	engfunc(EngFunc_SetSize, idEntity, fMinSizeBox, fMaxSizeBx);

	set_pev(idEntity, pev_vuser1, ptOriginPlayer);								// Сохраняем точку респауна
	set_pev(idEntity, pev_health, fWardHp);
	set_pev(idEntity, pev_takedamage, DAMAGE_YES);
	set_pev(idEntity,pev_flags, FL_MONSTER);

	set_pev(idEntity, pev_owner, idUser);
	set_pev(idEntity,pev_team,get_user_team(idUser));							// Сохраняем команду игрока
	
	set_pev(idEntity, pev_effects, pev(idEntity, pev_effects) | EF_BRIGHTFIELD);	//Частицы
	set_pev(idEntity, pev_effects, pev(idEntity, pev_effects) | EF_DIMLIGHT);	//Маленькое Освещение
	
	new iTeam = get_user_team(idUser);
	if(iTeam == TEAM_CT)
		fm_set_rendering(idEntity,kRenderFxGlowShell,0,0,255,kRenderNormal, 16);
	else if(iTeam == TEAM_T)
		fm_set_rendering(idEntity,kRenderFxGlowShell,255,0,0,kRenderNormal, 16);
	
	engfunc(EngFunc_SetOrigin, idEntity, ptOriginPlayer);

	dllfunc(DLLFunc_Spawn, idEntity);											//Делаем респаун сущности

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);						//Запуск обработчика Think


	//Обнуляем заряды после срабатывания или списываем заряды
	if(arrSkillChargeNum[idUser][iSkillID] >= arrSkillChargeMin[iSkillID])
		arrSkillChargeNum[idUser][iSkillID] -= arrSkillChargeMin[iSkillID];
	else
		arrSkillChargeNum[idUser][iSkillID] = 0;

	WC3_ShowBar(idUser);
}

public thinkHealingWard(idEntity)
{
	if (!pev_valid(idEntity)) 
		return;

	new Float:ptOriginEntity[3];
	if (pev_valid(idEntity))
		pev(idEntity, pev_vuser1, ptOriginEntity);
	
	new iTeamOwner = pev(idEntity,pev_team);

	new idOwner = pev(idEntity, pev_owner);

	new idVictim;
	while ((idVictim = engfunc(EngFunc_FindEntityInSphere, idVictim, ptOriginEntity, fHealingWardRadius)))
	{
		if (pev(idVictim, pev_takedamage) && is_visible(idVictim, idEntity))
		{
			new Float:ptOriginVictim[3]; 
			pev(idVictim, pev_origin, ptOriginVictim);

			new iTeamVictim = get_user_team(idVictim);

			if(!SHARED_ValidPlayer(idVictim))
				continue;

			if(iTeamOwner != iTeamVictim)
			{
				Create_ScreenFade(idVictim, (1<<15), (1<<10), (1<<12), 255, 255, 255, 255 );
				Create_ScreenFade(idOwner, (1<<10), (1<<10), (1<<12), 8, 250, 246, 32 );
			}
			else
			{					
				new iMinHealth = clHP:getRaceMinHealth(idVictim);
				new iCurrentHealth =  clHP:getUserHealth(idVictim);
				new iBonusHp = iHealingWardNumHealth;

				if(iCurrentHealth < iMinHealth)
				{
					if((iCurrentHealth + iBonusHp) > iMinHealth)
						clHP:setUserHealth(idVictim,iMinHealth);
					else
						clHP:setUserHealth(idVictim,iCurrentHealth + iBonusHp);
					

					Create_TE_BEAMENTS(idEntity, idVictim, arrIdSprites[SPR_BEAM], 0, 1, 1, 20, 30, 3,255,242,255, 0 );
				}
			}		
			
		}
	}

	if (pev_valid(idEntity))
		set_pev(idEntity, pev_nextthink, get_gametime() + fHealingWardFrequency);
}


// **********************************************************************
// Скил 2 уровня - Critical Blade  - Критический клинок
// **********************************************************************
clJuggernaut::skillCriticalBlade(const idAttacker,const iSkillID)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
		return;
	
	if(isDisabledSkillsOnMap(idAttacker,iSkillID) == true)
		return;

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idAttacker][iSkillID] <= 0)
		return;

	if(arrSkillChargeNum[idAttacker][iSkillID] < arrSkillChargeMin[iSkillID])
		return;

	emit_sound(idAttacker,CHAN_STATIC, arrStrSounds[SOUND_DEMON_BLADE], 0.7, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,100.0,arrStrModels[MDL_JKNIFE],1000,fBladeCriticalDmg,0.0,0,0.0,enBlade:enBlade_Critical);

	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,40.0,arrStrModels[MDL_JKNIFE],1000,0.0,30.0,2,0.0,enBlade:enBlade_Demon);
	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,40.0,arrStrModels[MDL_JKNIFE],1000,0.0,-15.0,2,0.0,enBlade:enBlade_Demon);

	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,40.0,arrStrModels[MDL_JKNIFE],1000,0.0,0.0,1,45.0,enBlade:enBlade_Demon);
	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,40.0,arrStrModels[MDL_JKNIFE],1000,0.0,0.0,1,-315.0,enBlade:enBlade_Demon);

	//Обнуляем заряды после срабатывания или списываем заряды
	if(arrSkillChargeNum[idAttacker][iSkillID] >= arrSkillChargeMin[iSkillID])
		arrSkillChargeNum[idAttacker][iSkillID] -= arrSkillChargeMin[iSkillID];
	else
		arrSkillChargeNum[idAttacker][iSkillID] = 0;

	WC3_ShowBar(idAttacker);
}

// **********************************************************************
// Скил 3 уровня - Demon Blade  - Демонический клинок
// **********************************************************************
clJuggernaut::skillDemonBlade(const idAttacker,const iSkillID)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
		return;
	
	if(isDisabledSkillsOnMap(idAttacker,iSkillID) == true)
		return;

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idAttacker][iSkillID] <= 0)
		return;

	if (random_float(0.0, 1.0 ) <= fChanseDemonBlade)
	{
		emit_sound(idAttacker,CHAN_STATIC, arrStrSounds[SOUND_DEMON_BLADE], 0.7, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

		clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,150.0,arrStrModels[MDL_JKNIFE],1000,0.0,0.0,0,0.0,enBlade:enBlade_Demon);

		clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,70.0,arrStrModels[MDL_JKNIFE],900,0.0,30.0,2,0.0,enBlade:enBlade_HP);
		clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,70.0,arrStrModels[MDL_JKNIFE],900,0.0,0.0,2,0.0,enBlade:enBlade_HP);

		clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,70.0,arrStrModels[MDL_JKNIFE],900,0.0,0.0,1,30.0,enBlade:enBlade_HP);
		clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,70.0,arrStrModels[MDL_JKNIFE],900,0.0,0.0,1,-30.0,enBlade:enBlade_HP);

		//Удаляем один заряд после срабатывания
		arrSkillChargeNum[idAttacker][iSkillID] -= 1;

		WC3_ShowBar(idAttacker);
	}

}


bool:clJuggernaut::fCreateBlade(const szClassname[],const idUser,const Float:fRadiusSpawn,
							    const szModel[],const iVelocityAux,
							    const Float:fDmg,
							    const Float:fOriginOffset,
							    const iAxis,
								const Float:fAngleRotate,
								const iTypeBlade)
{

	//client_print(idUser,print_chat,"szClassname: %s",szClassname);

	new Float:ptOriginPlayer[3];
	pev(idUser, pev_origin, ptOriginPlayer);
  	
	new Float:fAngles[3];
	pev(idUser, pev_v_angle, fAngles);
	engfunc(EngFunc_MakeVectors, fAngles);
	global_get(glb_v_forward, fAngles);
	xs_vec_mul_scalar(fAngles, fRadiusSpawn, fAngles);
	fAngles = uRotate(fAngleRotate,fAngles);
	xs_vec_add(ptOriginPlayer, fAngles, ptOriginPlayer);


	new idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	
	if(!pev_valid(idEntity)) 
		return false;
	
	set_pev(idEntity, pev_classname, szClassname);
	engfunc(EngFunc_SetModel, idEntity, szModel);
	
	set_pev(idEntity, pev_solid, SOLID_TRIGGER);
	set_pev(idEntity, pev_movetype, MOVETYPE_FLY);

	new Float:fMinSizeBox[3] =  {-0.600000, -2.390000, -10.270000};
	new Float:fMaxSizeBx[3] =  {0.540000, 2.450000, 10.270000};
	
	set_pev(idEntity, pev_mins, fMinSizeBox);
	set_pev(idEntity, pev_maxs, fMaxSizeBx);
	engfunc(EngFunc_SetSize, idEntity, fMinSizeBox, fMaxSizeBx);

	set_pev(idEntity, pev_health, 1.0);
	set_pev(idEntity, pev_takedamage, DAMAGE_YES);
	set_pev(idEntity,pev_flags, FL_MONSTER);
	set_pev(idEntity, pev_owner, idUser);
	set_pev(idEntity, pev_dmg, fDmg);

	//Анимация модели
	set_pev(idEntity,pev_animtime,0.0);	//время анимации
	set_pev(idEntity,pev_framerate,1.0);//частота кадров
	set_pev(idEntity,pev_sequence,1);	//номер анимации
	set_pev(idEntity,pev_gaitsequence,1);//номер анимации
	set_pev(idEntity,pev_frame,0.0);

	new Float:fVelocityAim[3];
	velocity_by_aim(idUser, iVelocityAux, fVelocityAim);
	set_pev(idEntity, pev_velocity, fVelocityAim);//Скорость движения сущности (вперед летит)

	set_pev(idEntity, pev_avelocity, Float:{0.0, 0.0, 0.0});//Задает скорость вращения вокруг своей оси

	new Float:fAnglesV[3];
	pev(idUser, pev_angles, fAnglesV);
	set_pev(idEntity, pev_angles, fAnglesV);//Задание сущности угла поворота
	set_pev(idEntity, pev_fixangle, 1);

	ptOriginPlayer[iAxis] += fOriginOffset;
	
	set_pev(idEntity, pev_iuser1, iTypeBlade);	// Сохраняем тип сущности

	new iTeam = get_user_team(idUser);
	if(iTeam == TEAM_CT)
		fm_set_rendering(idEntity,kRenderFxGlowShell,0,0,255,kRenderNormal, 16);
	else if(iTeam == TEAM_T)
		fm_set_rendering(idEntity,kRenderFxGlowShell,255,0,0,kRenderNormal, 16);


	switch(iTypeBlade)
	{
		case enBlade_Critical:
		{
			//fm_set_rendering(idEntity,kRenderFxGlowShell,255,0,0,kRenderNormal, 16);
			set_pev(idEntity, pev_effects, pev(idEntity, pev_effects) | EF_LIGHT);
		}
		case enBlade_Demon:
		{
			fm_set_rendering(idEntity,kRenderFxGlowShell,255,0,0,kRenderNormal, 16);
		}
		case enBlade_HP:
		{
			fm_set_rendering(idEntity,kRenderFxGlowShell,0,255,0,kRenderNormal, 16);
			
		}
		
	}

	set_pev(idEntity, pev_origin, ptOriginPlayer);

	return true;

}

// ******************************************************************
// Создание и управление эффектами для скила 2 и 3
// ******************************************************************
public touchCriticalBlade(idEntity, idWorldPlayer)
{
//	client_print(0,print_chat,"idEntity: %d | idWorldPlayer: %d",idEntity,idWorldPlayer);

	if (!pev_valid(idEntity))
		return PLUGIN_HANDLED;

	new idOwner = pev(idEntity, pev_owner);
	
	new Float:ptOriginEntity[3];
	pev(idEntity, pev_origin, ptOriginEntity);

	new Float:ptOriginOwner[3];
	pev(idOwner, pev_origin, ptOriginOwner);

	//Соприкосновение с миром (стены,пол...)
	if(idWorldPlayer == 0)
	{	
		message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
		write_byte(TE_SPRITETRAIL);
		engfunc(EngFunc_WriteCoord, ptOriginEntity[0]);
		engfunc(EngFunc_WriteCoord, ptOriginEntity[1]);
		engfunc(EngFunc_WriteCoord, ptOriginEntity[2]);
		engfunc(EngFunc_WriteCoord, ptOriginOwner[0]);
		engfunc(EngFunc_WriteCoord, ptOriginOwner[1]);
		engfunc(EngFunc_WriteCoord, ptOriginOwner[2]);
		write_short(arrIdSprites[SPR_DK_UNARMOR]);
		write_byte(15);
		write_byte(1);
		write_byte(1);
		write_byte(20);
		write_byte(14);
		message_end();

		emit_sound(idOwner,CHAN_STATIC, arrStrSounds[SOUND_DK_UNARMOR], 0.3, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
	
	}
	else
	{
		if(!SHARED_ValidPlayer(idWorldPlayer) || !SHARED_ValidPlayer(idOwner))
		{
			remove_entity(idEntity);
			return PLUGIN_HANDLED;
		}

		new iTypeBlade = pev(idEntity, pev_iuser1);		// тип сущности
		new Float:fDmg = float(pev(idEntity, pev_dmg));	//дамаг	

		switch(iTypeBlade)
		{
			case enBlade_Critical:
			{
				
				new idFindPlayer;
				while ((idFindPlayer = engfunc(EngFunc_FindEntityInSphere, idFindPlayer, ptOriginEntity, 350.0)))
				{
					if(!SHARED_ValidPlayer(idFindPlayer))
						continue;

					if (get_user_team(idFindPlayer) != get_user_team(idOwner) && is_user_alive(idFindPlayer))
					{
						ExecuteHamB(Ham_TakeDamage, idFindPlayer, idEntity, idOwner, fDmg, DMG_BULLET | DMG_NEVERGIB);
																	
						Create_ScreenFade(idFindPlayer, (6<<8), (6<<10), (1<<1), 0, 0, 0, 255 );
						
						emit_sound(idFindPlayer,CHAN_STATIC, arrStrSounds[SOUND_CRITICAL_BLADE], 0.45, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
						
					}//if

				}//while	
			}
			case enBlade_Demon:
			{
				if (get_user_team(idWorldPlayer) != get_user_team(idOwner) && is_user_alive(idWorldPlayer))
				{
					new CsArmorType:tArmor;
					new iCurrentArmor =  clAr:getUserArmor(idWorldPlayer,tArmor);
					new iBonusArmor = iBladeDemonArmor;
					
					if((iCurrentArmor + iBonusArmor) < 0)
						clAr:setUserArmor(idWorldPlayer,0);
					else
						clAr:setUserArmor(idWorldPlayer,iCurrentArmor + iBonusArmor);


					Create_ScreenShake(idWorldPlayer, (1<<14), (1<<12)*8, (2<<12)*7);
					
					emit_sound(idWorldPlayer,CHAN_STATIC, arrStrSounds[SOUND_CRITICAL_BLADE], 0.45, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

				}
			}
			case enBlade_HP:
			{
				if (get_user_team(idWorldPlayer) != get_user_team(idOwner) && is_user_alive(idWorldPlayer))
				{
					new iMaxHealth = clHP:getRaceMaxHealth(idOwner);
					new iCurrentHealth =  clHP:getUserHealth(idOwner);
					new iBonusHp = iBladeDemonHP;
					
					if((iCurrentHealth + iBonusHp) > iMaxHealth)
						clHP:setUserHealth(idOwner,iMaxHealth);
					else
						clHP:setUserHealth(idOwner,iCurrentHealth + iBonusHp);
				
					Create_ScreenFade(idOwner, (6<<8), (6<<10), (1<<1), 0, 255, 0, 120 );

					emit_sound(idWorldPlayer,CHAN_STATIC, arrStrSounds[SOUND_CRITICAL_BLADE], 0.45, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

				}
			}
		}

	}

	// Удаляем нож
	remove_entity(idEntity);
	
	return PLUGIN_CONTINUE;
}


// **********************************************************************
// Скил 4 уровня - Танец лезвий - Blade Dance
// **********************************************************************
public clJuggernaut::skillBladeDance(idAttacker,idVictim,iDamage,iWeapon,iHitPlace)
{
	if (!arrBoolData[idVictim][PB_ISCONNECTED] || !arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;
	
	if(isDisabledSkillsOnMap(idAttacker,PASS_JUGGERNAUT) == true)
		return;

	if (random_float(0.0, 1.0 ) <= fChanseBladeDance )
	{

		new iSkillLevel = SM_GetSkillLevel( idAttacker, PASS_JUGGERNAUT );
		if (iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false
			&& ((get_user_team( idAttacker ) != get_user_team( idVictim ))))
		{
			new iNewDamage = floatround(iDamage * float(iBladeDancePercentDmg / 100));
			WC3_Damage(idVictim, idAttacker, iNewDamage , iWeapon, iHitPlace);
				
			Create_ScreenFade(idVictim, (1<<10), (1<<10), (1<<12), 255, 0, 0, 255);

		}
	}
}


// *******************************************************
// Супер навык - Сокрушительный вихрь - Blade Fury
// *******************************************************
public clJuggernaut::ultBladeFury(idAttacker)
{		
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
		return;

	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,150.0,arrStrModels[MDL_JKNIFE],1500,fBladeCriticalDmg, 20.0,2,30.0,enBlade:enBlade_Critical);
	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,150.0,arrStrModels[MDL_JKNIFE],1500,fBladeCriticalDmg, 20.0,2,0.0,enBlade:enBlade_Critical);
	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,150.0,arrStrModels[MDL_JKNIFE],1500,fBladeCriticalDmg, 20.0,2,-30.0,enBlade:enBlade_Critical);

	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,100.0,arrStrModels[MDL_JKNIFE],1500,fBladeCriticalDmg, -10.0,2,45.0,enBlade:enBlade_Critical);
	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,100.0,arrStrModels[MDL_JKNIFE],1500,fBladeCriticalDmg, -10.0,2,0.0,enBlade:enBlade_Critical);
	clJuggernaut::fCreateBlade(CRITICAL_BLADE_CLASSNAME,idAttacker,100.0,arrStrModels[MDL_JKNIFE],1500,fBladeCriticalDmg, -10.0,2,-45.0,enBlade:enBlade_Critical);

	emit_sound(idAttacker,CHAN_STATIC, arrStrSounds[SOUND_BLADE_FURY], 1.0, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);


	//Сброс счетчика
	fResetUltimateTimerDivider(idAttacker);

}
