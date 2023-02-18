// ******************************************************************
// Раса: Невермор (Race: Shadow Fiend) Functions
// ******************************************************************


//Инициализация скилов Race: Shadow Fiend (Невермор)
public clShadowFiend::setSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	g_SkillOwner[SKILL_SHADOW_FIEND_1			]	= RACE_SHADOW_FIEND;
	g_SkillOwner[SKILL_SHADOW_FIEND_2			]	= RACE_SHADOW_FIEND;
	g_SkillOwner[SKILL_SHADOW_FIEND_3			]	= RACE_SHADOW_FIEND;
	g_SkillOwner[ULTIMATE_SHADOW_FIEND			]	= RACE_SHADOW_FIEND;
//	g_SkillOwner[PASS_SHADOW_FIEND				]	= RACE_SHADOW_FIEND;

	g_SkillType[SKILL_SHADOW_FIEND_1			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_SHADOW_FIEND_2			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_SHADOW_FIEND_3			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_SHADOW_FIEND			]	= SKILL_TYPE_ULTIMATE;
//	g_SkillType[PASS_SHADOW_FIEND				]	= SKILL_TYPE_PASSIVE;

	g_SkillOrder[SKILL_SHADOW_FIEND_1			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_SHADOW_FIEND_2			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_SHADOW_FIEND_3			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_SHADOW_FIEND			]	= SKILL_POS_4;
//	g_SkillOrder[PASS_SHADOW_FIEND				]	= SKILL_POS_NONE;
	
}


// **********************************************************************
// Скил 1 уровня - Presence of the Dark Lord - Присутствие Темного Лорда
// **********************************************************************
public clShadowFiend::skillPresenceDL(const idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser))
		return;

	if(isDisabledSkillsOnMap(idUser,SKILL_SHADOW_FIEND_1) == true)
		return;

	if (task_exists(idUser + clShadowFiend::tID_PRESENCE_DL) == 0)
		clShadowFiend::taskActivePresDL(idUser);
	
}

public clShadowFiend::taskActivePresDL(idUser)
{
	if (idUser >= clShadowFiend::tID_PRESENCE_DL)
		idUser -= clShadowFiend::tID_PRESENCE_DL;

	if (!arrBoolData[idUser][PB_ISCONNECTED])
		return;

	new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_SHADOW_FIEND_1 );
	
	if (iSkillLevel <= 0)
		return;

	if (is_user_alive(idUser))
	{
		new Float:fPresence = ArrayGetCell(arrPresenceDarkLord,iSkillLevel-1);
		set_task(fPresence, "_taskActivePresDL", clShadowFiend::tID_PRESENCE_DL + idUser);
	}
	
	if (arrBoolData[idUser][PB_HEXED])
		return;

	new arrPlayers[32], iNumberOfPlayers, idTarget, ptTargetOrigin[3], ptOrigin[3];
	new iTeam = get_user_team( idUser );

	get_user_origin(idUser, ptOrigin);
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
			
				if (get_distance(ptOrigin, ptTargetOrigin) < iPresenceRadius )
				{						
					new CsArmorType:tArmor;
					new iCurrentArmor =  clAr:getUserArmor(idTarget,tArmor);
					
					if (iCurrentArmor > iPresenceArmor)
					{
						iCurrentArmor -= 1;

						clAr:setUserArmor(idTarget,iCurrentArmor);
					
					}
				}
			}
		}
	}

	return;
}
// **********************************************************************
// Скил 2 уровня - Requiem of Souls  - Реквием душ
// **********************************************************************
public clShadowFiend::skillRequiemSouls(const idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser))
		return;

	if(arrIntData[idUser][PB_REQUIEM_SOULS_NUM] >= iRequiemSoulsNum)
		return;

	if(isDisabledSkillsOnMap(idUser,SKILL_SHADOW_FIEND_2) == true)
		return;

	arrIntData[idUser][PB_REQUIEM_SOULS_TIME] += 1;

	new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_SHADOW_FIEND_2);
	if (iSkillLevel > 0 && arrIntData[idUser][PB_REQUIEM_SOULS_TIME] >= iRequiemSoulsTime)
	{
		new Float:fRequiemSouls = ArrayGetCell(arrRequiemSouls,iSkillLevel-1);
		if (random_float(fRequiemSoulsSkill2MinPercent,fRequiemSoulsSkill2MaxPercent) <= fRequiemSouls )		
		{	
			emit_sound(idUser,CHAN_STATIC, arrStrSounds[SOUND_REQUIEM_OF_SOULS], 0.9, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			arrIntData[idUser][PB_REQUIEM_SOULS_NUM] += 1;
			
			clShadowFiend::fActiveRequiemSouls(idUser);

		}//if
		
		arrIntData[idUser][PB_REQUIEM_SOULS_TIME] = 0;

	}//if

}

public clShadowFiend::fActiveRequiemSouls(const idUser)
{

	//Поиск жертв
	new arrPlayers[32], iNumberOfPlayers;
	new iTeamCurrentUser = get_user_team(idUser);

	if(iTeamCurrentUser == TEAM_T)
		get_players(arrPlayers, iNumberOfPlayers, "e","CT");
	if(iTeamCurrentUser == TEAM_CT)
		get_players(arrPlayers, iNumberOfPlayers, "e","TERRORIST");
	
	new Array:arrIdFindVictim;
	arrIdFindVictim = ArrayCreate(1, 1);

	for(new i  = 0; i < iNumberOfPlayers; i++)
	{
		new iRand = random_num(0,iNumberOfPlayers - 1);
		new idVictim = arrPlayers[iRand];

		if(!SHARED_ValidPlayer(idVictim))
			continue;

		if(!is_user_alive(idVictim) || !is_user_connected(idVictim))
			continue;

		new bool:bIsFindCopyID = false;
		for(new iFV = 0; iFV < ArraySize(arrIdFindVictim); iFV++)
		{						
			new iIdCurVictim = ArrayGetCell(arrIdFindVictim,iFV);

			if(iIdCurVictim == idVictim)
			{
				bIsFindCopyID = true;
				break;
			}
		}//for
			
		if(bIsFindCopyID == false)
			ArrayPushCell(arrIdFindVictim,idVictim);
		
	}				

	for(new iAFV  = 0; iAFV < ArraySize(arrIdFindVictim); iAFV++)
	{
		if(iAFV > 3)
			break;

		new iIdCurVictim = ArrayGetCell(arrIdFindVictim,iAFV);

		switch(iAFV)
		{
			case 0: clShadowFiend::fCreateRequiemSouls(NECROMASTERY_SHADOW_FIEND_CLASSNAME,idUser,iIdCurVictim,50.0,arrIdSprites[SPR_NECROMASTERY],0.0);
			case 1: clShadowFiend::fCreateRequiemSouls(NECROMASTERY_SHADOW_FIEND_CLASSNAME,idUser,iIdCurVictim,50.0,arrIdSprites[SPR_NECROMASTERY],1.5707963267949);//90
			case 2: clShadowFiend::fCreateRequiemSouls(NECROMASTERY_SHADOW_FIEND_CLASSNAME,idUser,iIdCurVictim,50.0,arrIdSprites[SPR_NECROMASTERY],3.1415926535898);//180
			case 3: clShadowFiend::fCreateRequiemSouls(NECROMASTERY_SHADOW_FIEND_CLASSNAME,idUser,iIdCurVictim,50.0,arrIdSprites[SPR_NECROMASTERY],4.7123889803847);//270
		}
	}
	
}

bool:clShadowFiend::fCreateRequiemSouls(const szClassname[],const idUser,const idVictim,const Float:fRadiusSpawn,const iModelIndex,const Float:fAngleRotate)
{	
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
		
	set_pev(idEntity, pev_classname, szClassname);								// Задаем класс создаваемой сущности
	set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
	set_pev(idEntity, pev_modelindex, iModelIndex);								// Задаем индекс создаваемой сущности
	fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти
	

	set_pev(idEntity, pev_movetype, MOVETYPE_NOCLIP);
	set_pev(idEntity, pev_solid, SOLID_TRIGGER);
			
	set_pev(idEntity, pev_scale, 0.2);
	set_pev(idEntity, pev_health, 100.0);
	set_pev(idEntity, pev_takedamage, DAMAGE_YES);
		
	set_pev(idEntity,pev_iuser2,enTypeEntShadowFiend:eRequiemSouls);		// Тип сущности

	set_pev(idEntity, pev_origin, ptOriginPlayer);

	Create_TE_BEAMFOLLOW(idEntity, arrIdSprites[SPR_TRAIL], 50, 5,  244, 19, 86,  160 );

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);


	new arrParams[3];
	arrParams[1] = idEntity + clShadowFiend::tID_REQUIEM_SOULS;
	arrParams[2] = idVictim;

	if (task_exists(arrParams[1]))
		return false;

	set_task(0.5, "_taskRequiemSouls",arrParams[1], arrParams, sizeof arrParams);

	return true;

}

public clShadowFiend::taskRequiemSouls(arrParams[3])
{
	new idEntity = arrParams[1];
	new idVictim = arrParams[2];
	
	if (idEntity >= clShadowFiend::tID_REQUIEM_SOULS)
		idEntity -= clShadowFiend::tID_REQUIEM_SOULS;
		
	if(!pev_valid(idEntity)) 
	{
		Create_TE_KILLBEAM(idEntity);
		remove_entity(idEntity);
		return;
	}		
	if (!is_user_alive(idVictim))
	{
		Create_TE_KILLBEAM(idEntity);
		remove_entity(idEntity);
		return;
	}

	set_velocity_to_ent(idEntity,idVictim, 800.0);
	
	set_task(0.1, "_taskRequiemSouls", arrParams[1], arrParams, sizeof arrParams);
}


// **********************************************************************
// Скил 3 уровня - Cry from the heart - Крик души
// **********************************************************************
public clShadowFiend::skillCryHeart(const idVictim,const idAttacker)
{	
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim))
		return;

	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;

	if(isDisabledSkillsOnMap(idAttacker,SKILL_SHADOW_FIEND_3) == true)
		return;

	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_SHADOW_FIEND_3);
	if (iSkillLevel > 0)
	{
		new Float:fCryHeart = ArrayGetCell(arrCryHeart,iSkillLevel-1);
		if (random_float(fCryHeartSkill3MinPercent,fCryHeartSkill3MaxPercent) <= fCryHeart )		
		{			
			emit_sound(idAttacker,CHAN_STATIC, arrStrSounds[SOUND_CRY_HEART], 0.8, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
			
			clShadowFiend::fCreateCryHeart(NECROMASTERY_SHADOW_FIEND_CLASSNAME,idAttacker,idVictim,30.0,arrIdSprites[SPR_NECROMASTERY],0.0);

			
		}//if
		
	}//if
	
}

bool:clShadowFiend::fCreateCryHeart(const szClassname[],const idUser,const idVictim,const Float:fRadiusSpawn,const iModelIndex,const Float:fAngleRotate)
{	
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
		
	set_pev(idEntity, pev_classname, szClassname);								// Задаем класс создаваемой сущности
	set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
	set_pev(idEntity, pev_modelindex, iModelIndex);								// Задаем индекс создаваемой сущности
	fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти
	
	set_pev(idEntity, pev_movetype, MOVETYPE_NOCLIP);
	set_pev(idEntity, pev_solid, SOLID_TRIGGER);
			
	set_pev(idEntity, pev_scale, 0.2);
	set_pev(idEntity, pev_health, 100.0);
	set_pev(idEntity, pev_takedamage, DAMAGE_YES);
		
	set_pev(idEntity,pev_iuser2,enTypeEntShadowFiend:eCryHeart);		// Тип сущности

	set_pev(idEntity, pev_origin, ptOriginPlayer);

	Create_TE_BEAMFOLLOW(idEntity, arrIdSprites[SPR_TRAIL], 50, 2,  11, 205, 230,  160 );

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);


	new arrParams[3];
	arrParams[1] = idEntity + clShadowFiend::tID_CRY_HEART;
	arrParams[2] = idVictim;

	if (task_exists(arrParams[1]))
		return false;

	set_task(0.1, "_taskActiveCryHeart",arrParams[1], arrParams, sizeof arrParams);

	return true;

}

public clShadowFiend::taskActiveCryHeart(arrParams[3])
{
	new idEntity = arrParams[1];
	new idVictim = arrParams[2];
	
	if (idEntity >= clShadowFiend::tID_CRY_HEART)
		idEntity -= clShadowFiend::tID_CRY_HEART;
		
	if(!pev_valid(idEntity)) 
	{
		Create_TE_KILLBEAM(idEntity);
		remove_entity(idEntity);
		return;
	}
			
	if (!is_user_alive(idVictim))
	{
		Create_TE_KILLBEAM(idEntity);
		remove_entity(idEntity);
		return;
	}

	set_velocity_to_ent(idEntity,idVictim, 1000.0);
	
	set_task(0.1, "_taskActiveCryHeart", arrParams[1], arrParams, sizeof arrParams);
}


// **********************************************************************
// Скил 4 уровня - xxx - xxx
// **********************************************************************
//SKILL_103 = Скил 103 (не используется)


// *******************************************************
// Супер навык - Воровство душ - Necromastery
// *******************************************************
public clShadowFiend::ultNecromastery(const idUser)
{		
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
		return;
	
	if(!clShadowFiend::fStartNecromastery(idUser))
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_NECROMASTERY");
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		emit_sound(idUser,CHAN_STATIC, arrStrSounds[SOUND_ERROR], 0.8, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

		return;
	}

	emit_sound(idUser,CHAN_STATIC, arrStrSounds[SOUND_NECROMASTERY], 1.0, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
	
	fResetUltimateTimerDivider(idUser);

}

bool:clShadowFiend::fStartNecromastery(const idUser)
{
	new iOriginCorpseLength = ArraySize(arrOriginCorpse_X);

	if(iOriginCorpseLength <= 0)
		return false;
	
	for(new i = 0; i < iOriginCorpseLength; i++)
	{
		if(i == iNecromasteryNum)
			break;
				
		new iRandIndex = random_num(0,iOriginCorpseLength - 1);

		new Float:ptOriginCorpse[3];
		ptOriginCorpse[0] = ArrayGetCell(arrOriginCorpse_X,iRandIndex);
		ptOriginCorpse[1] = ArrayGetCell(arrOriginCorpse_Y,iRandIndex);
		ptOriginCorpse[2] = ArrayGetCell(arrOriginCorpse_Z,iRandIndex);
		
		new idEntity;
		clShadowFiend::fCreateNecromastery(NECROMASTERY_SHADOW_FIEND_CLASSNAME,idUser,arrIdSprites[SPR_NECROMASTERY],ptOriginCorpse,idEntity);
				
		clShadowFiend::fUpNecromastery(idEntity);

		new arrParams[2];
		arrParams[1] = idEntity + clShadowFiend::tID_NECROMASTERY;

		if (task_exists(arrParams[1]))
			return false;
	
		set_task(2.0, "_taskNecromastery",arrParams[1], arrParams, sizeof arrParams);
	}
	
	return true;
}

//Поднятие вверх
public clShadowFiend::fUpNecromastery(&idEntity)
{
	if(!is_valid_ent(idEntity))
		return;
		
	set_pev(idEntity, pev_movetype, MOVETYPE_FLY);
	set_pev(idEntity, pev_velocity, Float:{0.0, 0.0, 20.0});//Скорость движения сущности
}

public clShadowFiend::taskNecromastery(arrParams[2])
{
	new idEntity = arrParams[1];
	
	if (idEntity >= clShadowFiend::tID_NECROMASTERY)
		idEntity -= clShadowFiend::tID_NECROMASTERY;
		
	if(!pev_valid(idEntity)) 
	{
		Create_TE_KILLBEAM(idEntity);
		remove_entity(idEntity);
		return;
	}

	set_pev(idEntity, pev_movetype, MOVETYPE_NOCLIP);
		
	new idOwner = pev(idEntity, pev_owner);
	
	if (!is_user_alive(idOwner))
	{
		Create_TE_KILLBEAM(idEntity);
		remove_entity(idEntity);
		return;
	}

	set_velocity_to_ent(idEntity,idOwner, 800.0);
	
	set_task(0.1, "_taskNecromastery", arrParams[1], arrParams, sizeof arrParams);
}

bool:clShadowFiend::fCreateNecromastery(const szClassname[],const idUser,const iModelIndex, const Float:ptOriginCorpse[3], &idEntity)
{	
	
	idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	
	if(!pev_valid(idEntity)) 
		return false;
		
	set_pev(idEntity, pev_classname, szClassname);								// Задаем класс создаваемой сущности
	set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
	set_pev(idEntity, pev_modelindex, iModelIndex);								// Задаем индекс создаваемой сущности
	fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти

	set_pev(idEntity, pev_movetype, MOVETYPE_NOCLIP);
	set_pev(idEntity, pev_solid, SOLID_TRIGGER);
			
	set_pev(idEntity, pev_scale, 0.3);
	set_pev(idEntity, pev_health, 100.0);
	set_pev(idEntity, pev_takedamage, DAMAGE_YES);
		
	set_pev(idEntity,pev_iuser2,enTypeEntShadowFiend:eNecromastery);		// Тип сущности

	set_pev(idEntity, pev_origin, ptOriginCorpse);

	Create_TE_BEAMFOLLOW(idEntity, arrIdSprites[SPR_TRAIL], 50, 5, 227, 252, 48, 160 );

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);

	return true;

}


// ******************************************************************
// Создание и управление эффектами для скила
// ******************************************************************
public thinkNecromastery(idEntity)
{
	if (!pev_valid(idEntity)) 
		return;

	//Анимация спрайта
	if (entity_get_float(idEntity, EV_FL_frame) > 20.0)
		entity_set_float(idEntity, EV_FL_frame, 0.0);
	else
		entity_set_float(idEntity, EV_FL_frame, entity_get_float(idEntity, EV_FL_frame) + 1.0);

	if (pev_valid(idEntity))
		set_pev(idEntity, pev_nextthink, get_gametime() + 0.5);
}

public touchNecromastery(idEntity, idWorldPlayer)
{	
	if (!pev_valid(idEntity))
		return PLUGIN_HANDLED;

	if(!is_user_alive(idWorldPlayer) || !is_user_connected(idWorldPlayer)) 
		return PLUGIN_HANDLED;

	new idOwner = pev(idEntity, pev_owner);

	if(!is_user_alive(idOwner) || !is_user_connected(idOwner)) 
		return PLUGIN_HANDLED;

	new Float:ptOriginEntity[3];
	pev(idEntity, pev_origin, ptOriginEntity);

	new Float:ptOriginOwner[3];
	pev(idOwner, pev_origin, ptOriginOwner);

	new iTypeEnt = pev(idEntity,pev_iuser2);		// Тип сущности

	switch(iTypeEnt)
	{
		case eNecromastery:
		{
			if(idOwner != idWorldPlayer)
				return PLUGIN_HANDLED;

			emit_sound(idOwner,CHAN_STATIC, arrStrSounds[SOUND_NECROMASTERY_HP], 0.5, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			new Origin[3];
			get_user_origin(idOwner, Origin);

			Create_ScreenFade(idOwner, (1<<10), (1<<10), FADE_OUT, 227, 252, 48, 160 );
			Create_TE_ELIGHT(idOwner, Origin, 100, 227, 252, 48, 10, 0 );
			
			Create_TE_EXPLOSION(Origin, Origin, arrIdSprites[SPR_NECROMASTERY_EXP], 10, 24, 4 );
			
			new iMaxHealth = clHP:getRaceMaxHealth(idOwner);
			new iCurrentHealth =  clHP:getUserHealth(idOwner);
			new iBonusHp = iNecromasteryHP;
			
			if((iCurrentHealth + iBonusHp) > iMaxHealth)
				clHP:setUserHealth(idOwner,iMaxHealth);
			else
				clHP:setUserHealth(idOwner,iCurrentHealth + iBonusHp);

		
		}
		case eRequiemSouls:
		{
			if(get_user_team(idOwner) == get_user_team(idWorldPlayer))
				return PLUGIN_HANDLED;

			emit_sound(idWorldPlayer,CHAN_STATIC, arrStrSounds[SOUND_REQUIEM_OF_SOULS_DMG], 0.8, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			new Origin[3];
			get_user_origin(idWorldPlayer, Origin);

			Create_ScreenFade(idWorldPlayer, (1<<10), (1<<10), FADE_OUT,  244, 19, 86,  160 );
			Create_TE_ELIGHT(idWorldPlayer, Origin, 100,  244, 19, 86,  10, 0 );
			
			Create_TE_EXPLOSION(Origin, Origin, arrIdSprites[SPR_NECROMASTERY_EXP], 10, 24, 4 );

			WC3_Damage(idWorldPlayer,idOwner,iRequiemSoulsDmg, CSW_REQUIEM_SOULS, -1);

		}
		case eCryHeart:
		{
			if(get_user_team(idOwner) == get_user_team(idWorldPlayer))
				return PLUGIN_HANDLED;
			
			emit_sound(idWorldPlayer,CHAN_STATIC, arrStrSounds[SOUND_CRY_HEART], 0.8, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			new Origin[3];
			get_user_origin(idWorldPlayer, Origin);

			Create_ScreenFade(idWorldPlayer, (1<<10), (1<<10), FADE_OUT,  11, 205, 230,  160 );
			Create_TE_ELIGHT(idWorldPlayer, Origin, 100,  11, 205, 230,  10, 0 );
			
			WC3_Damage(idWorldPlayer,idOwner,iCryHeartDmg, CSW_CRY_HEART, -1);

			
		}
	}
	
	Create_TE_KILLBEAM(idEntity);

	remove_entity(idEntity);

	return PLUGIN_CONTINUE;
}
