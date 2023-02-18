// ******************************************************************
// Раса: Блэйд (Race: Razor) Functions
// ******************************************************************


//Инициализация скилов Race: Razor (Блэйд)
public clRazor::setSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	g_SkillOwner[SKILL_RAZOR_1			]	= RACE_RAZOR;
	g_SkillOwner[SKILL_RAZOR_2			]	= RACE_RAZOR;
	g_SkillOwner[SKILL_RAZOR_3			]	= RACE_RAZOR;
	g_SkillOwner[ULTIMATE_RAZOR			]	= RACE_RAZOR;
	g_SkillOwner[PASS_RAZOR				]	= RACE_RAZOR;

	g_SkillType[SKILL_RAZOR_1			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_RAZOR_2			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_RAZOR_3			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_RAZOR			]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_RAZOR				]	= SKILL_TYPE_PASSIVE;

	g_SkillOrder[SKILL_RAZOR_1			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_RAZOR_2			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_RAZOR_3			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_RAZOR			]	= SKILL_POS_4;
	g_SkillOrder[PASS_RAZOR				]	= SKILL_POS_NONE;
	
}

// **********************************************************************
// Скил 1 уровня - Eye of the Storm - Око бури
// **********************************************************************
clRazor::skillEyeOfTheStorm(const idAttacker,const idVictim)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;

	if(!is_user_alive(idVictim) || !is_user_connected(idVictim))
		return;

	if(isDisabledSkillsOnMap(idVictim,SKILL_RAZOR_1) == true)
		return;

	new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_RAZOR_1);
	if (iSkillLevel > 0)
	{
		new Float:fEyeOfTheStorm = ArrayGetCell(arrEyeOfTheStorm,iSkillLevel-1);
		if (random_float(fEyeOfTheStormSkill1MinPercent,fEyeOfTheStormSkill1MaxPercent) <= fEyeOfTheStorm )		
		{				
			if( SHARED_ValidPlayer(idAttacker) && (get_user_team(idVictim) != get_user_team(idAttacker)) )
			{	
				emit_sound(idAttacker,CHAN_STATIC, arrStrSounds[SOUND_EYE_STORM], 0.3, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

				new Float:ptOriginPlayer[3];
				pev(idAttacker, pev_origin, ptOriginPlayer);

				clRazor::fCreateSmokeGroup(ptOriginPlayer);

				//new iWeapon, iClip, iAmmo;
				//iWeapon = get_user_weapon(idAttacker, iClip, iAmmo );

				//if (iWeapon != CSW_KNIFE)
				//	engclient_cmd(idAttacker,"weapon_knife");
			}

		}//if
		
	}//if

}

stock clRazor::fCreateSmokeGroup(Float:fPointPosition[3])
{
	new Float:fPointOrigin[12][3];
	stGetSphericalCoord(fPointPosition, 40.0, 0.0, 0.0, fPointOrigin[0]);
	stGetSphericalCoord(fPointPosition, 40.0, 90.0, 0.0, fPointOrigin[1]);
	stGetSphericalCoord(fPointPosition, 40.0, 180.0, 0.0, fPointOrigin[2]);
	stGetSphericalCoord(fPointPosition, 40.0, 270.0, 0.0, fPointOrigin[3]);
	stGetSphericalCoord(fPointPosition, 100.0, 0.0, 0.0, fPointOrigin[4]);
	
	for (new i = 0; i < 4; i++)
		clRazor::fCreateSmoke(fPointOrigin[i],arrIdSprites[SPR_SMOKE_PRIEST], 100, 0);
}

stock clRazor::fCreateSmoke(const Float:fPointPosition[3], idSpriteIndex, iLife, iFrameRate)
{
	// Alphablend sprite, move vertically 30 pps
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_SMOKE); // TE_SMOKE (5)
	engfunc(EngFunc_WriteCoord, fPointPosition[0]); // position.x
	engfunc(EngFunc_WriteCoord, fPointPosition[1]); // position.y
	engfunc(EngFunc_WriteCoord, fPointPosition[2]); // position.z
	write_short(idSpriteIndex); // sprite index
	write_byte(iLife); // scale in 0.1's
	write_byte(iFrameRate); // framerate
	message_end();
}



// **********************************************************************
// Скил 2 уровня - Static Link  - Статическая помеха
// **********************************************************************
bool:clRazor::skillStaticLink(const idVictim)
{
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim))
		return false;

	if(isDisabledSkillsOnMap(idVictim,SKILL_RAZOR_2) == true)
		return false;

	new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_RAZOR_2);
	if (iSkillLevel > 0)
	{
		new Float:fStaticLink = ArrayGetCell(arrStaticLink,iSkillLevel-1);
		if (random_float(fStaticLinkSkill2MinPercent,fStaticLinkSkill2MaxPercent) <= fStaticLink )		
		{	

			emit_sound(idVictim,CHAN_STATIC, arrStrSounds[SOUND_STATIC_LINK], 0.3, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			new Float:ptOriginVictim[3];
			pev(idVictim, pev_origin, ptOriginVictim);

			engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, ptOriginVictim, 0);
			write_byte(TE_BEAMCYLINDER); 
			engfunc(EngFunc_WriteCoord, ptOriginVictim[0]); 
			engfunc(EngFunc_WriteCoord, ptOriginVictim[1]); 
			engfunc(EngFunc_WriteCoord, ptOriginVictim[2])
			engfunc(EngFunc_WriteCoord, ptOriginVictim[0]);
			engfunc(EngFunc_WriteCoord, ptOriginVictim[1]);
			engfunc(EngFunc_WriteCoord, ptOriginVictim[2] + 100.0);
			write_short(arrIdSprites[SPR_DRUID_ENTANGLE]);
			write_byte(0);
			write_byte(0);
			write_byte(4);
			write_byte(60);
			write_byte(0);
			write_byte(41); 
			write_byte(138); 
			write_byte(255);
			write_byte(200);
			write_byte(0);
			message_end();

			return true;

		}//if
		
	}//if

	return false;

}

// **********************************************************************
// Скил 3 уровня - Unstable Current - Неустойчивый поток
// **********************************************************************
bool:clRazor::skillUnstableCurrent(const idVictim,const idAttacker)
{
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim))
		return false;

	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return false;

	if(isDisabledSkillsOnMap(idVictim,SKILL_RAZOR_3) == true)
		return false;

	new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_RAZOR_3);
	if (iSkillLevel > 0)
	{
		new Float:fUnstableCurrent = ArrayGetCell(arrUnstableCurrent,iSkillLevel-1);
		if (random_float(fUnstableCurSkill3MinPercent,fUnstableCurSkill3MaxPercent) <= fUnstableCurrent )		
		{			
			emit_sound(idAttacker,CHAN_STATIC, arrStrSounds[SOUND_UNSTABLE_CURRENT], 0.5, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
			
			Create_TE_BEAMENTS(idVictim, idAttacker, arrIdSprites[SPR_LIGHTNING], 0, 15, 5, 75, 1,  211,233,19,   255, 50 );

			WC3_Damage(idAttacker,idVictim,iUnstableCurrentDmg, CSW_UNSTABLE_CURRENT, -1);

			return true;

		}//if
		
	}//if

	return false;

}

// **********************************************************************
// Скил 4 уровня - Манна небесная - Manna
// **********************************************************************
public clRazor::skillManna(idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser))
		return;

	if(isDisabledSkillsOnMap(idUser,PASS_RAZOR) == true)
		return;

	if (random_float(0.0,1.0) <= fManaChance)
		set_task(0.4, "_taskActiveManna", clRazor::tID_MANNA + idUser);
	
}

public clRazor::taskActiveManna(idUser)
{
	if (idUser >= clRazor::tID_MANNA)
		idUser -= clRazor::tID_MANNA;

	new Float:ptOriginPlayer[3];
	pev(idUser, pev_origin, ptOriginPlayer);
	//Create_TE_BEAMDISK(ptOriginPlayer, 100 , arrIdSprites[SPR_DRUID_ENTANGLE], 0, 9, 5,   15,    3,    255, 255, 255,    255,  0, 0);
	Create_TE_BEAMTORUS(ptOriginPlayer,100, arrIdSprites[SPR_DRUID_HEALING], 0, 9, 5,   15,    3,    255, 255, 255,    255,  0, 0);

	new arrPlayers[32], iNumberOfPlayers, idTarget, ptTargetOrigin[3], ptOrigin[3];
	new iTeam = get_user_team(idUser);

	get_user_origin(idUser, ptOrigin);
	get_players(arrPlayers, iNumberOfPlayers, "a" );
	
	for ( new i = 0; i < iNumberOfPlayers; i++ )
	{
		idTarget = arrPlayers[i];			
		
		if (get_user_team(idTarget) == iTeam)
		{
			if (is_user_alive(idTarget))
			{
				get_user_origin(idTarget, ptTargetOrigin);
								
				if (get_distance(ptOrigin, ptTargetOrigin) < iManaRadius)
				{
					get_user_origin(idTarget,ptOrigin);
									

					new iMaxHealth = clHP:getRaceMaxHealth(idTarget);
					new iCurrentHealth =  clHP:getUserHealth(idTarget);
					new iBonusHp = iManaHP;

					if (iCurrentHealth < iMaxHealth)
					{
						if( (iCurrentHealth + iBonusHp) > iMaxHealth )
							clHP:setUserHealth(idTarget,iMaxHealth);
						else
							clHP:setUserHealth(idTarget,iCurrentHealth + iBonusHp);

						Create_TE_IMPLOSION(ptTargetOrigin, 100, 8, 1);
					}					
				}//if
			}//if
		}//if

	}//for

//	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MANNA");
//	cssbChatColor(idTarget,"%s%s",fTagWar3ft(),szMessage);
}


// *******************************************************
// Супер навык - Плазменное поле - Plasma Field
// *******************************************************
public clRazor::ultPlasmaField(const idAttacker, const idVictim)
{		
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
		return;
	
	emit_sound(idVictim,CHAN_STATIC, arrStrSounds[SOUND_PLASMA_FIELD], 0.7, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
	emit_sound(idAttacker,CHAN_STATIC, arrStrSounds[SOUND_PLASMA_FIELD], 0.07, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

	clRazor::fCreatePlasmaField(PLASMA_FIELD_RAZOR_CLASSNAME,idAttacker,idVictim,50.0,arrIdSprites[SPR_PLASMA_FIELD],0, 0.0, 0.0);
	clRazor::fCreatePlasmaField(PLASMA_FIELD_RAZOR_CLASSNAME,idAttacker,idVictim,50.0,arrIdSprites[SPR_PLASMA_FIELD],0, 0.0, 0.78539816339745);//45
	clRazor::fCreatePlasmaField(PLASMA_FIELD_RAZOR_CLASSNAME,idAttacker,idVictim,50.0,arrIdSprites[SPR_PLASMA_FIELD],0, 0.0, 1.5707963267949);//90
	clRazor::fCreatePlasmaField(PLASMA_FIELD_RAZOR_CLASSNAME,idAttacker,idVictim,50.0,arrIdSprites[SPR_PLASMA_FIELD],0, 0.0, 2.3561944901923);//135
	clRazor::fCreatePlasmaField(PLASMA_FIELD_RAZOR_CLASSNAME,idAttacker,idVictim,50.0,arrIdSprites[SPR_PLASMA_FIELD],0, 0.0, 3.1415926535898);//180
	clRazor::fCreatePlasmaField(PLASMA_FIELD_RAZOR_CLASSNAME,idAttacker,idVictim,50.0,arrIdSprites[SPR_PLASMA_FIELD],0, 0.0, 3.9269908169872);//225
	clRazor::fCreatePlasmaField(PLASMA_FIELD_RAZOR_CLASSNAME,idAttacker,idVictim,50.0,arrIdSprites[SPR_PLASMA_FIELD],0, 0.0, 4.7123889803847);//270
	clRazor::fCreatePlasmaField(PLASMA_FIELD_RAZOR_CLASSNAME,idAttacker,idVictim,50.0,arrIdSprites[SPR_PLASMA_FIELD],0, 0.0, 5.4977871437821);//315
	
	//Сброс счетчика
	fResetUltimateTimerDivider(idAttacker);

}

bool:clRazor::fCreatePlasmaField(const szClassname[],const idUser,const idVictim,const Float:fRadiusSpawn,
							     const iModelIndex,const iVelocityAux,
							     const Float:fOriginOffsetZ,
							     const Float:fAngleRotate)
{	
	new Float:ptOriginPlayer[3];
	pev(idVictim, pev_origin, ptOriginPlayer);
  	
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

	set_pev(idEntity, pev_movetype, MOVETYPE_BOUNCE);
	set_pev(idEntity, pev_solid, SOLID_BBOX);
		
	set_pev(idEntity, pev_gravity, 0.8);
	set_pev(idEntity,pev_iuser1,iPlasmaFieldNumTouch);		// Количество отскоков от стен
	
	set_pev(idEntity, pev_scale, 0.09);
	set_pev(idEntity, pev_health, 100.0);
	set_pev(idEntity, pev_takedamage, DAMAGE_YES);
	
	new Float:fVelocityAim[3];
	velocity_by_aim(idUser, iVelocityAux, fVelocityAim);
	set_pev(idEntity, pev_velocity, fVelocityAim);//Скорость движения сущности (вперед летит)

	new Float:fAnglesV[3];
	pev(idUser, pev_angles, fAnglesV);
	set_pev(idEntity, pev_angles, fAnglesV);//Задание сущности угла поворота
	set_pev(idEntity, pev_fixangle, 1);

	ptOriginPlayer[2] += fOriginOffsetZ;
	
	set_pev(idEntity, pev_origin, ptOriginPlayer);

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);						//Запуск обработчика Think

	return true;

}

// ******************************************************************
// Создание и управление эффектами для скила
// ******************************************************************
public thinkPlasmaField(idEntity)
{
	//log_amx("idEntity: %d",idEntity);

	if (!pev_valid(idEntity))
		return;

	//Анимация спрайта
	if (entity_get_float(idEntity, EV_FL_frame) > 2)
		entity_set_float(idEntity, EV_FL_frame, 0.0);
	else
		entity_set_float(idEntity, EV_FL_frame, entity_get_float(idEntity, EV_FL_frame) + 1.0);

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);
}


public touchPlasmaField(idEntity, idWorldPlayer)
{
	//client_print(0,print_chat,"idEntity: %d | idWorldPlayer: %d",idEntity,idWorldPlayer);
	//log_amx("idEntity: %d | idWorldPlayer: %d",idEntity,idWorldPlayer);

	if (!pev_valid(idEntity))
		return PLUGIN_HANDLED;

	new idOwner = pev(idEntity, pev_owner);
	
	new iJumpNumPlasmaField = pev(idEntity, pev_iuser1);	

	if(iJumpNumPlasmaField <= 0)
	{
		remove_entity(idEntity);

		return PLUGIN_HANDLED;
	}
		
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
	engfunc(EngFunc_WriteCoord, ptOriginEntity[2] + fPlasmaFieldRadius);// axis and radius (Z)
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

	new idFindPlayer;
	while ((idFindPlayer = engfunc(EngFunc_FindEntityInSphere, idFindPlayer, ptOriginEntity, fPlasmaFieldRadius)))
	{
		if(!SHARED_ValidPlayer(idFindPlayer))
			continue;

		if (get_user_team(idFindPlayer) != get_user_team(idOwner) && is_user_alive(idFindPlayer))
		{
			WC3_Damage(idFindPlayer,idOwner,iPlasmaFieldDmg, CSW_PLASMA_FIELD, -1);
			ExecuteHamB(Ham_TakeDamage, idFindPlayer, idEntity, idOwner, 0.0, DMG_BULLET);
														
			Create_ScreenFade(idFindPlayer, (1<<12), (1<<12), (1<<6),  211,233,19,  255 );
			
			emit_sound(idEntity,CHAN_STATIC, arrStrSounds[SOUND_SHRAPNEL_DAMAGE], 0.015, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

			break;
		}//if

	}//while
	
	iJumpNumPlasmaField -= 1;
	set_pev(idEntity, pev_iuser1,iJumpNumPlasmaField);	// Счетчик через сколько изменить свойство

	return PLUGIN_CONTINUE;
}
