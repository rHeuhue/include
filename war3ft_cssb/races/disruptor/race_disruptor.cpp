// ******************************************************************
// Раса: Разрушитель (Race: Disruptor) Functions
// ******************************************************************


//Инициализация скилов Race: Disruptor (Разрушитель)
public clDisruptor::setSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	g_SkillOwner[SKILL_DISRUPTOR_1			]	= RACE_DISRUPTOR;
	g_SkillOwner[SKILL_DISRUPTOR_2			]	= RACE_DISRUPTOR;
	g_SkillOwner[SKILL_DISRUPTOR_3			]	= RACE_DISRUPTOR;
	g_SkillOwner[ULTIMATE_DISRUPTOR			]	= RACE_DISRUPTOR;
	g_SkillOwner[PASS_DISRUPTOR				]	= RACE_DISRUPTOR;

	g_SkillType[SKILL_DISRUPTOR_1			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_DISRUPTOR_2			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_DISRUPTOR_3			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_DISRUPTOR			]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_DISRUPTOR				]	= SKILL_TYPE_PASSIVE;

	g_SkillOrder[SKILL_DISRUPTOR_1			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_DISRUPTOR_2			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_DISRUPTOR_3			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_DISRUPTOR			]	= SKILL_POS_4;
	g_SkillOrder[PASS_DISRUPTOR				]	= SKILL_POS_NONE;
	
}

// **********************************************************************
// Скил 1 уровня - Glimpse - Призрачный взгляд
// **********************************************************************
clDisruptor::skillGlimpse(const idAttacker,const idVictim)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;

	if(!is_user_alive(idVictim) || !is_user_connected(idVictim))
		return;

	if(isDisabledSkillsOnMap(idVictim,SKILL_DISRUPTOR_1) == true)
		return;

	new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_DISRUPTOR_1 );
	if (iSkillLevel > 0)
	{
		new Float:fGlimpse = ArrayGetCell(arrGlimpse,iSkillLevel-1);
		if (random_float(fGlimpseSkill1MinPercent,fGlimpseSkill1MaxPercent) <= fGlimpse )		
		{	
			
			if (SHARED_ValidPlayer(idAttacker) && 
				( get_user_team(idVictim) != get_user_team(idAttacker) )
			   )
			{
				new iRespEntity;

				new iTeam = get_user_team(idAttacker);
				if (iTeam == TEAM_T )
					iRespEntity = CanTeleportOnBaseT();
				if (iTeam == TEAM_CT )
					iRespEntity = CanTeleportOnBaseCT();

				if(pev_valid(iRespEntity)) 
					ShurikenBall_Teleport(idAttacker, iRespEntity);
									
				WC3_Damage(idAttacker,idVictim,iDisruptorGlimpseDmg, CSW_GLIMPSE, -1);
						
			}

		}//if
		
	}//if

}

// **********************************************************************
// Скил 2 уровня - Thunder Strike  - Удар грома
// **********************************************************************
clDisruptor::skillThunderStrike(const idAttacker,const idVictim)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;

	if(!is_user_alive(idVictim) || !is_user_connected(idVictim))
		return;

	if(isDisabledSkillsOnMap(idAttacker,SKILL_DISRUPTOR_2) == true)
		return;

	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_DISRUPTOR_2);
	if (iSkillLevel > 0)
	{
		new Float:fThunderStrike = ArrayGetCell(arrThunderStrike,iSkillLevel-1);
		if (random_float(fThunderStrikeSkill2MinPercent,fThunderStrikeSkill2MaxPercent) <= fThunderStrike )		
		{	
			
			if (SHARED_ValidPlayer(idAttacker) && 
				( get_user_team(idVictim) != get_user_team(idAttacker) )
			   )
			{
				
				Create_TE_BEAMENTS(idAttacker, idVictim, arrIdSprites[SPR_LIGHTNING], 0, 15, 5, 50, 10,  random_num(0,255),random_num(0,255),random_num(0,255),   255,0 );
				emit_sound(idAttacker,CHAN_STATIC, arrStrSounds[SOUND_LIGHTNING], 0.25, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
				emit_sound(idVictim,CHAN_STATIC, arrStrSounds[SOUND_LIGHTNING], 0.25, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
				WC3_Damage(idVictim,idAttacker,iDisruptorThunderStrikeDmg_1, CSW_THUNDER_STRIKE, -1);

				new arrPlayers[32], iNumberOfPlayers;
				new iTeamVictim = get_user_team(idVictim);
				get_players(arrPlayers, iNumberOfPlayers, "a");
				
				new ptVictimOrigin[3];
				get_user_origin(idVictim, ptVictimOrigin);

				new Array:arrIdFindVictim;
				arrIdFindVictim = ArrayCreate(1, 1);
				
				new idOldFindNextVictim = idVictim;
				new idNewFindNextVictim = clDisruptor::getIdFindNextVictim(idVictim,arrPlayers,iNumberOfPlayers,iTeamVictim,ptVictimOrigin,arrIdFindVictim,iDisruptorThunderStrikeRadius);
								
				while(idNewFindNextVictim > 0)
				{				
					if(idNewFindNextVictim > 0)
					{						
						Create_TE_BEAMENTS(idOldFindNextVictim, idNewFindNextVictim, arrIdSprites[SPR_LIGHTNING], 0, 15, 5, 25, 10,  random_num(0,255),random_num(0,255),random_num(0,255),   255,0 );
						emit_sound(idNewFindNextVictim,CHAN_STATIC, arrStrSounds[SOUND_LIGHTNING], 0.025, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
						WC3_Damage(idNewFindNextVictim,idAttacker,iDisruptorThunderStrikeDmg_2, CSW_THUNDER_STRIKE, -1);

						idOldFindNextVictim = idNewFindNextVictim;

					}

					idNewFindNextVictim = clDisruptor::getIdFindNextVictim(idVictim,arrPlayers,iNumberOfPlayers,iTeamVictim,ptVictimOrigin,arrIdFindVictim,iDisruptorThunderStrikeRadius);

				}						
			}

		}//if
		
	}//if

}

stock clDisruptor::getIdFindNextVictim(const idVictim,const arrPlayers[32],const iNumberOfPlayers,const iTeamVictim,const ptVictimOrigin[3],&Array:arrIdFindVictim, const iRadiusNextTarget)
{

	new ptTargetOrigin[3];

	new idTarget;

	for (new i = 0; i < iNumberOfPlayers; i++ )
	{
		idTarget = arrPlayers[i];
		
		if(idTarget == idVictim)
			continue;

		if ( arrBoolData[idTarget][PB_ISCONNECTED] && get_user_team(idTarget) == iTeamVictim)
		{
			if (is_user_alive(idTarget))
			{
				get_user_origin(idTarget, ptTargetOrigin);
									
				if (get_distance(ptVictimOrigin, ptTargetOrigin) < iRadiusNextTarget)
				{
					new bool:bIsFindCopyID = false;
					for(new i = 0; i < ArraySize(arrIdFindVictim); i++)
					{						
						new iIdCurVictim = ArrayGetCell(arrIdFindVictim,i);

						if(iIdCurVictim == idTarget)
						{
							bIsFindCopyID = true;
							break;
						}
					}//for
						
					if(bIsFindCopyID == false)
					{
						ArrayPushCell(arrIdFindVictim,idTarget);
						return idTarget;
					}
				
				}
			}
		}
	}

	return 0;

}

// **********************************************************************
// Скил 3 уровня - Kinetic Field - Кинетическое поле
// **********************************************************************
public clDisruptor::skillKineticField(idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser))
		return;

	if(isDisabledSkillsOnMap(idUser,SKILL_DISRUPTOR_3) == true)
		return;

	new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_DISRUPTOR_3);
	if (iSkillLevel > 0)
	{		
		if (arrBoolData[idUser][PB_KINETIC_FIELD])
			return;

		new Float:fKineticField = ArrayGetCell(arrKineticField,iSkillLevel-1);
		if (random_float(fKineticFieldSkill3MinPercent,fKineticFieldSkill3MaxPercent) <= fKineticField )		
			set_task(0.5, "_taskActiveKineticField", clDisruptor::tID_KINETIC_FIELD + idUser);
		
	}
	else
	{
		arrBoolData[idUser][PB_KINETIC_FIELD] = false;
	}
	
}

public clDisruptor::taskActiveKineticField(idUser)
{
	if (idUser >= clDisruptor::tID_KINETIC_FIELD)
		idUser -= clDisruptor::tID_KINETIC_FIELD;

	if (arrBoolData[idUser][PB_KINETIC_FIELD])
		return;

	new Float:ptOriginPlayer[3];
	pev(idUser, pev_origin, ptOriginPlayer);
	Create_TE_BEAMDISK(ptOriginPlayer, 100 , arrIdSprites[SPR_DRUID_ENTANGLE], 0, 9, 5,   15,    3,    255, 255, 255,    255,  0, 0);
	
	//Тоже ничего
	//	Create_TE_BEAMTORUS(ptOriginPlayer, 40 , arrIdSprites[SPR_DRUID_ENTANGLE], 0, 9, 5,   15,    3,    255, 255, 255,    255,  0, 0);

	arrBoolData[idUser][PB_KINETIC_FIELD] = true;

	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_KINETIC_FIELD");
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
}

// *******************************************************
// Супер навык - Статический шторм - Static Storm
// *******************************************************
public clDisruptor::ultStaticStorm(idAttacker,idVictim)
{		
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
		return;
	
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim)) 
		return;

	for(new i = 0; i < 25; i++)
	{
		clDisruptor::fCreateStaticStorm(STATIC_STORM_DISRUPTOR_CLASSNAME,idAttacker,idVictim,arrIdSprites[SPR_STATIC_STORM],
										random_float(0.0,250.0), // ширина
										random_float(100.0,200.0), //высота
										random_float(0.0,360.0)); //угол поворота
		}

	fResetUltimateTimerDivider(idAttacker);

}

bool:clDisruptor::fCreateStaticStorm(const szClassname[],const idUser,const idVictim,const iModelIndex,
									 const Float:fOriginOffsetX,
									 const Float:fOriginOffsetZ,
									 const Float:fAngleRotate)
{
	new Float:ptOriginPlayer[3];
	pev(idVictim, pev_origin, ptOriginPlayer);

	new Float:ptNewPositionEnt[3];
	ptNewPositionEnt = uFloatPointToFloat(ptOriginPlayer);
	ptNewPositionEnt = uPointRotate(fOriginOffsetX,fAngleRotate,ptNewPositionEnt);
  
	new idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	
	if(!pev_valid(idEntity)) 
		return false;
		
	set_pev(idEntity, pev_classname, szClassname);								// Задаем класс создаваемой сущности
	set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
	set_pev(idEntity, pev_modelindex, iModelIndex);								// Задаем индекс создаваемой сущности
	fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти

	set_pev(idEntity, pev_movetype, MOVETYPE_FLY);
	set_pev(idEntity, pev_solid, SOLID_BBOX);
		
	set_pev(idEntity,pev_iuser1,0);		// Счетчик через сколько изменить свойство

	set_pev(idEntity, pev_scale,0.3);
	set_pev(idEntity, pev_health, 100.0);
	set_pev(idEntity, pev_takedamage, DAMAGE_YES);
	
	ptNewPositionEnt[2] += fOriginOffsetZ;
	
	set_pev(idEntity, pev_origin, ptNewPositionEnt);

	set_pev(idEntity,pev_fuser1,ptOriginPlayer[2]);		// Сохраняем Z координаты жертвы

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);						//Запуск обработчика Think

	return true;

}

// ******************************************************************
// Создание и управление эффектами для скила
// ******************************************************************
public thinkStaticStorm(idEntity)
{
	//log_amx("idEntity: %d",idEntity);

	if (!pev_valid(idEntity)) 
		return;

	//Анимация спрайта
	if (entity_get_float(idEntity, EV_FL_frame) > 2)
		entity_set_float(idEntity, EV_FL_frame, 0.0);
	else
		entity_set_float(idEntity, EV_FL_frame, entity_get_float(idEntity, EV_FL_frame) + 1.0);

	new Float:ptOriginEntity[3];
	pev(idEntity, pev_origin, ptOriginEntity);

	new iLightningNum = pev(idEntity, pev_iuser1);	
	if(iLightningNum > 1)
		return;
	
	if(iLightningNum == 1)
	{
		set_pev(idEntity, pev_movetype, MOVETYPE_BOUNCE);
		set_pev(idEntity, pev_solid, SOLID_BBOX);
		set_pev(idEntity, pev_gravity, 1.0);
		return;
	}
	
	new Float:fZvictim = float(pev(idEntity,pev_fuser1));		// Сохраняем Z координаты жертвы

	new ptStartEnt[3], ptEndEnt[3];

	ptStartEnt = uFloatPointToInt(ptOriginEntity);
	ptEndEnt = uFloatPointToInt(ptOriginEntity);
	ptEndEnt[2] = floatround(fZvictim);	

	if(random_float(0.0, 1.0) > 0.25 )
	{
		Create_TE_BEAMPOINTS(ptStartEnt, ptEndEnt, arrIdSprites[SPR_LIGHTNING], 0, 15, 5, 25, 10,  random_num(0,255),random_num(0,255),random_num(0,255),   255,0 );
		emit_sound(idEntity,CHAN_STATIC, arrStrSounds[SOUND_LIGHTNING], 0.03, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
	}

	//Кусок кода для поиска сущности. (оставлен для будущих работ)
	/*
	new idFindEntity;
	while ((idFindEntity = engfunc(EngFunc_FindEntityInSphere, idFindEntity, ptOriginEntity, 500.0)))
	{		
		if (is_visible(idFindEntity, idEntity) && pev_valid(idFindEntity))
		{
			new szClassnameFindEntity[128];
			pev(idFindEntity, pev_classname, szClassnameFindEntity,charsmax(szClassnameFindEntity));
				
			if (equal(szClassnameFindEntity,STATIC_STORM_DISRUPTOR_CLASSNAME))
			{
				new Float:ptOriginFindEntity[3];
				pev(idFindEntity, pev_origin, ptOriginFindEntity);

				if (get_distance_f(ptOriginFindEntity, ptOriginEntity) > random_float(10.0, 150.0) )
				{
					Create_TE_BEAMENTS(idEntity, idFindEntity, arrIdSprites[SPR_LIGHTNING], 0, 15, 1, 11, 10,  14,200,238,   255,0 );
					
					emit_sound(idEntity,CHAN_STATIC, arrStrSounds[SOUND_LIGHTNING], 0.025, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
					
				}//if
	
				break;

			}//if
			
		}//if

	}//while
	*/


	if (pev_valid(idEntity))
	{
		iLightningNum += 1;
		set_pev(idEntity, pev_iuser1,iLightningNum);	// Счетчик через сколько изменить свойство

		set_pev(idEntity, pev_nextthink, get_gametime() + 1.0);
	}
}


public touchStaticStorm(idEntity, idWorldPlayer)
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

	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_BEAMCYLINDER);
	engfunc(EngFunc_WriteCoord, ptOriginEntity[0]);// center position (X)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[1]);// center position (Y)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[2]);// center position (Z)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[0]);// axis and radius (X)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[1]);// axis and radius (Y)
	engfunc(EngFunc_WriteCoord, ptOriginEntity[2] + 75.0);// axis and radius (Z)
	write_short(arrIdSprites[SPR_STATIC_STORM]) ;
	write_byte(0);// starting frame
	write_byte(10);// frame rate in 0.1's
	write_byte(3); // life in 0.1's
	write_byte(20); // line width in 0.1's
	write_byte(0); // noise amplitude in 0.01's
	write_byte(255);// color (red)
	write_byte(255);// color (green)
	write_byte(255);// color (blue)
	write_byte(255);// brightness
	write_byte(0);// scroll speed in 0.1's
	message_end();

	new idFindPlayer;
	while ((idFindPlayer = engfunc(EngFunc_FindEntityInSphere, idFindPlayer, ptOriginEntity, fDisruptorStaticStormRadius)))
	{
		if(!SHARED_ValidPlayer(idFindPlayer))
			continue;

		if (get_user_team(idFindPlayer) != get_user_team(idOwner) && is_user_alive(idFindPlayer))
		{
			WC3_Damage(idFindPlayer,idOwner,iDisruptorStaticStormDmg, CSW_STATIC_STORM, -1);
			ExecuteHamB(Ham_TakeDamage, idFindPlayer, idEntity, idOwner, 0.0, DMG_BULLET);
														
			Create_ScreenFade(idFindPlayer, (1<<12), (1<<12), (1<<6),  14,200,238,  255 );
			
			emit_sound(idEntity,CHAN_STATIC, arrStrSounds[SOUND_SHRAPNEL_DAMAGE], 0.025, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			break;
		}//if

	}//while	

	remove_entity(idEntity);
		
	return PLUGIN_CONTINUE;
}
