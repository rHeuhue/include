// ******************************************************************
// Раса: Друид (Race: Druid) Functions
// ******************************************************************


//Инициализация скилов Race: Druid (Друид)
public clDruid::setDruidSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	g_SkillOwner[SKILL_DRUID_1			]	= RACE_DRUID;
	g_SkillOwner[SKILL_DRUID_2			]	= RACE_DRUID;
	g_SkillOwner[SKILL_DRUID_3			]	= RACE_DRUID;
	g_SkillOwner[ULTIMATE_DRUID			]	= RACE_DRUID;
	g_SkillOwner[PASS_MANGLE_DRUID		]	= RACE_DRUID;

	g_SkillType[SKILL_DRUID_1			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_DRUID_2			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_DRUID_3			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_DRUID			]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_MANGLE_DRUID		]	= SKILL_TYPE_PASSIVE;

	g_SkillOrder[SKILL_DRUID_1			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_DRUID_2			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_DRUID_3			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_DRUID			]	= SKILL_POS_4;
	g_SkillOrder[PASS_MANGLE_DRUID		]	= SKILL_POS_NONE;


	//Максимальное количество зарядов
	arrSkillChargeMax[SKILL_DRUID_1			]	= iDruidChargeMax_1;
	arrSkillChargeMax[SKILL_DRUID_2			]	= iDruidChargeMax_2;
	arrSkillChargeMax[SKILL_DRUID_3			]	= iDruidChargeMax_3;

	//Минимальное количество зарядов
	arrSkillChargeMin[SKILL_DRUID_1			]	= iDruidChargeMin_1;
	arrSkillChargeMin[SKILL_DRUID_2			]	= iDruidChargeMin_2;
	arrSkillChargeMin[SKILL_DRUID_3			]	= iDruidChargeMin_3;

	//Счетчик через сколько шанс получить заряд
	arrSkillCount[SKILL_DRUID_1				]	= iDruidCount_1;
	arrSkillCount[SKILL_DRUID_2				]	= iDruidCount_2;
	arrSkillCount[SKILL_DRUID_3				]	= iDruidCount_3;
	
}

//Инициализация начального количества зарядов у игрока
public clDruid::setChargeNum(idUser)//добавлена в war3ft.cpp ( WC3_PlayerInit( idUser ) )
{
	arrSkillChargeNum[idUser][SKILL_DRUID_1] = iDruidChargeMin_1;
	arrSkillChargeNum[idUser][SKILL_DRUID_2] = iDruidChargeMin_2;
	arrSkillChargeNum[idUser][SKILL_DRUID_3] = iDruidChargeMin_3;

//	client_print(idUser,print_chat,"setChargeNum");
}

//Добавляем заряд скилу. Функция размещается в зависимости от того,
//каким способом будет даваться заряд (время,дамаг,убийство и тд)
clDruid::addSkillCharge(const iSkillID,const idUser,const iNumIncrement = 1)
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
		case SKILL_DRUID_1:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser,iSkillID);
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
				new Float:fWildEntanglement = ArrayGetCell(arrWildEntanglement,iSkillLevel-1);
				if (random_float(fDruidSkill1MinPercent,fDruidSkill1MaxPercent) <= fWildEntanglement )		
				{
					arrSkillChargeNum[idUser][iSkillID] += iNumIncrement;
					WC3_ShowBar(idUser);
				}
			}
		}
		case SKILL_DRUID_2:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser, iSkillID );
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
				new Float:fWildHealing = ArrayGetCell(arrWildHealing,iSkillLevel-1);
				if (random_float(fDruidSkill2MinPercent,fDruidSkill2MaxPercent) <= fWildHealing )		
				{
					arrSkillChargeNum[idUser][iSkillID] += iNumIncrement;
					WC3_ShowBar(idUser);
				}
			}
		}
		case SKILL_DRUID_3:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser, iSkillID );
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
			
				new Float:fWildExplode = ArrayGetCell(arrWildExplode,iSkillLevel-1);
				if (random_float(fDruidSkill3MinPercent,fDruidSkill3MaxPercent) <= fWildExplode )		
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
// Скил 1 уровня - Wild Mushroom: Entanglement - Дикий гриб: Запутывание
// **********************************************************************
clDruid::skillWildMush_Entangle(const idUser,const iSkillID)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;

	if(isDisabledSkillsOnMap(idUser,iSkillID) == true)
		return;

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idUser][iSkillID] <= 0)
		return;

	if(arrSkillChargeNum[idUser][iSkillID] < arrSkillChargeMin[iSkillID])
		return;

	clDruid::fCreateWildMushroom(idUser,fRadiusSpawnWild,0.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_ENTANGLE],0.2,
		0.0,fWildHpEnt,0.3,enWildMush:enWildMush_Entangle);
	clDruid::fCreateWildMushroom(idUser,fRadiusSpawnWild,120.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_ENTANGLE],0.2,
		0.0,fWildHpEnt,0.3,enWildMush:enWildMush_Entangle);
	clDruid::fCreateWildMushroom(idUser,fRadiusSpawnWild,240.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_ENTANGLE],0.2,
		0.0,fWildHpEnt,0.3,enWildMush:enWildMush_Entangle);

	emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_WISP_SPAWN], 1.0, ATTN_NORM, 0, PITCH_NORM );

	//Обнуляем заряды после срабатывания или списываем заряды
	if(arrSkillChargeNum[idUser][iSkillID] >= arrSkillChargeMin[iSkillID])
		arrSkillChargeNum[idUser][iSkillID] -= arrSkillChargeMin[iSkillID];
	else
		arrSkillChargeNum[idUser][iSkillID] = 0;

	WC3_ShowBar(idUser);
}

// **********************************************************************
// Скил 2 уровня - Wild Mushroom: Healing  - Дикий гриб: Исцеление
// **********************************************************************
clDruid::skillWildMush_Healing(const idUser,const iSkillID)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;

	if(isDisabledSkillsOnMap(idUser,iSkillID) == true)
		return;

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idUser][iSkillID] <= 0)
		return;

	if(arrSkillChargeNum[idUser][iSkillID] < arrSkillChargeMin[iSkillID])
		return;
		
	clDruid::fCreateWildMushroom(idUser,fRadiusSpawnWild,0.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_HEALING],0.2,
		fWildHealingHp,fWildHpHeal,0.5,enWildMush:enWildMush_Healing);
	clDruid::fCreateWildMushroom(idUser,fRadiusSpawnWild,120.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_HEALING],0.2,
		fWildHealingHp,fWildHpHeal,0.5,enWildMush:enWildMush_Healing);
	clDruid::fCreateWildMushroom(idUser,fRadiusSpawnWild,240.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_HEALING],0.2,
		fWildHealingHp,fWildHpHeal,0.5,enWildMush:enWildMush_Healing);

	emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_WISP_SPAWN], 1.0, ATTN_NORM, 0, PITCH_NORM );

	//Обнуляем заряды после срабатывания или списываем заряды
	if(arrSkillChargeNum[idUser][iSkillID] >= arrSkillChargeMin[iSkillID])
		arrSkillChargeNum[idUser][iSkillID] -= arrSkillChargeMin[iSkillID];
	else
		arrSkillChargeNum[idUser][iSkillID] = 0;

	WC3_ShowBar(idUser);
}

// **********************************************************************
// Скил 3 уровня - Wild Mushroom: Explode  - Дикий гриб: Удар
// **********************************************************************
clDruid::skillWildMush_Explode(const idUser,const iSkillID)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;

	if(isDisabledSkillsOnMap(idUser,iSkillID) == true)
		return;

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idUser][iSkillID] <= 0)
		return;

	if(arrSkillChargeNum[idUser][iSkillID] < arrSkillChargeMin[iSkillID])
		return;
	
	clDruid::fCreateWildMushroom(idUser,fRadiusSpawnWild,0.0, "Wild_Mushroom",arrIdSprites[SPR_ROGUE_SHURIKEN],0.2,
		fWildExplodeDmg,fWildHpExp,0.5,enWildMush:enWildMush_Explode);
	clDruid::fCreateWildMushroom(idUser,fRadiusSpawnWild,120.0, "Wild_Mushroom",arrIdSprites[SPR_ROGUE_SHURIKEN],0.2,
		fWildExplodeDmg,fWildHpExp,0.5,enWildMush:enWildMush_Explode);
	clDruid::fCreateWildMushroom(idUser,fRadiusSpawnWild,240.0, "Wild_Mushroom",arrIdSprites[SPR_ROGUE_SHURIKEN],0.2,
		fWildExplodeDmg,fWildHpExp,0.5,enWildMush:enWildMush_Explode);	

	emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_WISP_SPAWN], 1.0, ATTN_NORM, 0, PITCH_NORM );

	//Обнуляем заряды после срабатывания или списываем заряды
	if(arrSkillChargeNum[idUser][iSkillID] >= arrSkillChargeMin[iSkillID])
		arrSkillChargeNum[idUser][iSkillID] -= arrSkillChargeMin[iSkillID];
	else
		arrSkillChargeNum[idUser][iSkillID] = 0;

	WC3_ShowBar(idUser);
}

//Дополнение к скилу 1
//Гриб выращивается когда Друид стреляет в кого-то. На месте жертвы появляется
public clDruid::addWMStrikeEntangle(idAttacker,idVictim)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim)) 
		return;

	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_DRUID_1);

	if(iSkillLevel <= 0)
		return;

	if(isDisabledSkillsOnMap(idAttacker,SKILL_DRUID_1) == true)
		return;

	new Float:fWildEntanglement = ArrayGetCell(arrWildEntanglement,iSkillLevel-1);
	if (random_float(fDruidSkill1MinPercent,fDruidSkill1MaxPercent) <= fWildEntanglement)
	{
		new Float:ptOriginPlayer[3];
		pev(idVictim, pev_origin, ptOriginPlayer);

		clDruid::fCreateWildMushroom_2(idAttacker,ptOriginPlayer,fRadiusSpawnWild,0.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_ENTANGLE],0.2,
			0.0,fWildHpEnt,0.3,enWildMush:enWildMush_Entangle);
		clDruid::fCreateWildMushroom_2(idAttacker,ptOriginPlayer,fRadiusSpawnWild,120.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_ENTANGLE],0.2,
			0.0,fWildHpEnt,0.3,enWildMush:enWildMush_Entangle);
		clDruid::fCreateWildMushroom_2(idAttacker,ptOriginPlayer,fRadiusSpawnWild,240.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_ENTANGLE],0.2,
			0.0,fWildHpEnt,0.3,enWildMush:enWildMush_Entangle);

		emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_WISP_SPAWN], 1.0, ATTN_NORM, 0, PITCH_NORM );

	}

}

//Дополнение к скилу 2
//Гриб выращивается когда Друид стреляет в кого-то. На месте жертвы появляется
public clDruid::addWMStrikeHealing(idAttacker,idVictim)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim)) 
		return;

	new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_DRUID_2);
	
	if(iSkillLevel <= 0)
		return;

	if(isDisabledSkillsOnMap(idVictim,SKILL_DRUID_2) == true)
		return;

	new Float:fWildHealing = ArrayGetCell(arrWildHealing,iSkillLevel-1);
	if (random_float(fDruidSkill2MinPercent,fDruidSkill2MaxPercent) <= fWildHealing)
	{
	
		clDruid::fCreateWildMushroom(idVictim,fRadiusSpawnWild,0.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_HEALING],0.2,
			fWildHealingHp,fWildHpHeal,0.5,enWildMush:enWildMush_Healing);
		clDruid::fCreateWildMushroom(idVictim,fRadiusSpawnWild,120.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_HEALING],0.2,
			fWildHealingHp,fWildHpHeal,0.5,enWildMush:enWildMush_Healing);
		clDruid::fCreateWildMushroom(idVictim,fRadiusSpawnWild,240.0, "Wild_Mushroom",arrIdSprites[SPR_DRUID_HEALING],0.2,
			fWildHealingHp,fWildHpHeal,0.5,enWildMush:enWildMush_Healing);

		emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_WISP_SPAWN], 1.0, ATTN_NORM, 0, PITCH_NORM );

	}

}

//Дополнение к скилу 3
//Гриб выращивается когда Друид стреляет в кого-то. На месте жертвы появляется
public clDruid::addWMStrikeExplode(idAttacker,idVictim)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim)) 
		return;

	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_DRUID_3);

	if(iSkillLevel <= 0)
		return;

	if(isDisabledSkillsOnMap(idAttacker,SKILL_DRUID_3) == true)
		return;

	new Float:fWildExplode = ArrayGetCell(arrWildExplode,iSkillLevel-1);
	if (random_float(fDruidSkill3MinPercent,fDruidSkill3MaxPercent) <= fWildExplode)
	{
		new Float:ptOriginPlayer[3];
		pev(idVictim, pev_origin, ptOriginPlayer);

		clDruid::fCreateWildMushroom_2(idAttacker,ptOriginPlayer,fRadiusSpawnWild,0.0, "Wild_Mushroom",arrIdSprites[SPR_ROGUE_SHURIKEN],0.2,
			fWildExplodeDmg,fWildHpExp,0.5,enWildMush:enWildMush_Explode);
		clDruid::fCreateWildMushroom_2(idAttacker,ptOriginPlayer,fRadiusSpawnWild,120.0, "Wild_Mushroom",arrIdSprites[SPR_ROGUE_SHURIKEN],0.2,
			fWildExplodeDmg,fWildHpExp,0.5,enWildMush:enWildMush_Explode);
		clDruid::fCreateWildMushroom_2(idAttacker,ptOriginPlayer,fRadiusSpawnWild,240.0, "Wild_Mushroom",arrIdSprites[SPR_ROGUE_SHURIKEN],0.2,
			fWildExplodeDmg,fWildHpExp,0.5,enWildMush:enWildMush_Explode);	

		emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_WISP_SPAWN], 1.0, ATTN_NORM, 0, PITCH_NORM );


	}

}

// ******************************************************************
// Создание и управление эффектами для 1,2,3 скилов
// ******************************************************************
//Первый способ
bool:clDruid::fCreateWildMushroom_2(const idUser,Float:ptOriginPlayer[3],
								    const Float:fRadius,const Float:fAngleRotate, const szClassname[],
								    const iModelIndex,const Float:fScale,
								    const Float:fDmg,
								    const Float:fHealth,
								    const Float:fUpdate,
									const iTypeWildMushroom)
{
	new Float:ptForward[3];
	ptForward = uFloatPointToFloat(ptOriginPlayer);
	ptForward = uPointRotate(fRadius,fAngleRotate,ptForward);

	new idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	
	if(!pev_valid(idEntity))
		return false;
	
	set_pev(idEntity, pev_classname, szClassname);								// Задаем класс создаваемой сущности
	set_pev(idEntity, pev_origin, ptForward);									// Задаем позицию сущности
	set_pev(idEntity, pev_fuser1, fAngleRotate);								// Сохраням угол
	set_pev(idEntity, pev_vuser1, ptOriginPlayer);								// Сохраняем точку респауна
	set_pev(idEntity, pev_iuser1, iTypeWildMushroom);							// Сохраняем тип сущности
	set_pev(idEntity, pev_fuser2, fUpdate);										// Через сколько будет срабатывать молния.
	set_pev(idEntity, pev_health, fHealth);										// Задаем запас здоровья сущности
	set_pev(idEntity,pev_team,get_user_team(idUser));							// Сохраняем команду игрока

	set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
	set_pev(idEntity, pev_modelindex, iModelIndex);								// Задаем индекс создаваемой сущности
	fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти
		

	set_pev(idEntity, pev_movetype, MOVETYPE_FLY);
	set_pev(idEntity, pev_solid, SOLID_BBOX);
	set_pev(idEntity, pev_scale, fScale);										// Задаем масштаб сущности
	set_pev(idEntity, pev_dmg, fDmg);											// Закладываем дамаг в сущность
	set_pev(idEntity, pev_dmgtime,get_gametime());								// Закладываем время через которое будет работать дамаг


	dllfunc(DLLFunc_Spawn, idEntity);											//Делаем респаун сущности

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);						//Запуск обработчика Think

	return true;

}

//Второй способ
bool:clDruid::fCreateWildMushroom(const idUser,const Float:fRadius,const Float:fAngleRotate, const szClassname[],
								  const iModelIndex,const Float:fScale,
								  const Float:fDmg,
								  const Float:fHealth,
								  const Float:fUpdate,const iTypeWildMushroom)
{

	new Float:ptOriginPlayer[3];
	pev(idUser, pev_origin, ptOriginPlayer);									// Координата игрока

	new Float:ptForward[3];
	ptForward = uFloatPointToFloat(ptOriginPlayer);
	ptForward = uPointRotate(fRadius,fAngleRotate,ptForward);

	new idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	
	if(!pev_valid(idEntity))
		return false;
	
	set_pev(idEntity, pev_classname, szClassname);								// Задаем класс создаваемой сущности
	set_pev(idEntity, pev_origin, ptForward);									// Задаем позицию сущности
	set_pev(idEntity, pev_fuser1, fAngleRotate);								// Сохраням угол
	set_pev(idEntity, pev_vuser1, ptOriginPlayer);								// Сохраняем точку респауна
	set_pev(idEntity, pev_iuser1, iTypeWildMushroom);							// Сохраняем тип сущности
	set_pev(idEntity, pev_fuser2, fUpdate);										// Через сколько будет срабатывать молния.
	set_pev(idEntity, pev_health, fHealth);										// Задаем запас здоровья сущности
	set_pev(idEntity,pev_team,get_user_team(idUser));							// Сохраняем команду игрока

	set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
	set_pev(idEntity, pev_modelindex, iModelIndex);								// Задаем индекс создаваемой сущности
	fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти
		

	set_pev(idEntity, pev_movetype, MOVETYPE_FLY);
	set_pev(idEntity, pev_solid, SOLID_BBOX);
	set_pev(idEntity, pev_scale, fScale);										// Задаем масштаб сущности
	set_pev(idEntity, pev_dmg, fDmg);											// Закладываем дамаг в сущность
	set_pev(idEntity, pev_dmgtime,get_gametime());								// Закладываем время через которое будет работать дамаг


	dllfunc(DLLFunc_Spawn, idEntity);											//Делаем респаун сущности

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);						//Запуск обработчика Think

	return true;

}


public thinkWildMushroom(idEntity)
{
	if (!pev_valid(idEntity)) 
		return;

	//Анимация спрайта
	if (entity_get_float(idEntity, EV_FL_frame) > 6)
		entity_set_float(idEntity, EV_FL_frame, 0.0);
	else
		entity_set_float(idEntity, EV_FL_frame, entity_get_float(idEntity, EV_FL_frame) + 1.0);

	
	new idOwner = pev(idEntity, pev_owner);

	
	new Float:ptOriginEntity[3];
	if (pev_valid(idEntity))
		pev(idEntity, pev_vuser1, ptOriginEntity);

	//Разворачиваем сущность на заданный градус
	new Float:fAngle = float(pev(idEntity, pev_fuser1));
	ptOriginEntity = uPointRotate(fRadiusSpawnWild,fAngle,ptOriginEntity);

	if (pev_valid(idEntity))
	{
		set_pev(idEntity, pev_origin, ptOriginEntity);	
		set_pev(idEntity, pev_fuser1, fAngle + 3.0);
	}

	new Float:fDmg = float(pev(idEntity, pev_dmg));
	new Float:fDmgTimeGlowworm = float(pev(idEntity, pev_dmgtime));
	new Float:fUpdate = float(pev(idEntity, pev_fuser2));
	new iTypeWildMushroom = pev(idEntity, pev_iuser1);
	new iTeamOwner = pev(idEntity,pev_team);

	new Float:fHealth = float(pev(idEntity, pev_health));
	if(fDmg <= 0.0)
		fHealth -= 3.0;
	else
		fHealth -= fDmg;
		
	if(fHealth <= 0.0)
	{
		emit_sound(idEntity, CHAN_STATIC, arrStrSounds[SOUND_WISP_DEATH], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
		Create_TE_PARTICLEBURST(uFloatPointToInt(ptOriginEntity),30,0x13137F,5);

		engfunc(EngFunc_RemoveEntity, idEntity);
		return;
	}


	new idVictim;
	while ((idVictim = engfunc(EngFunc_FindEntityInSphere, idVictim, ptOriginEntity, fWildRadiusDmg)))
	{
		if (pev(idVictim, pev_takedamage) && is_visible(idVictim, idEntity))
		{
			new Float:ptOriginVictim[3]; 
			pev(idVictim, pev_origin, ptOriginVictim);

			new iTeamVictim = get_user_team(idVictim);

			if ((fDmgTimeGlowworm + fUpdate) > get_gametime())
				break;
			
			fDmgTimeGlowworm = get_gametime();
			set_pev(idEntity, pev_dmgtime,fDmgTimeGlowworm);
		
			switch(iTypeWildMushroom)
			{
				case enWildMush_Entangle:
				{
					if(iTeamOwner == iTeamVictim)
						break;

					ExecuteHamB(Ham_TakeDamage, idVictim, idEntity, idOwner,0.0, DMG_ENERGYBEAM );
					Create_TE_BEAMENTS(idEntity, idVictim, arrIdSprites[SPR_LIGHTNING], 0, 1, 1, 20, 30, 255,246,3,    255, 0 );

					if (pev_valid(idEntity)) 
						set_pev(idEntity,pev_health,fHealth);
					
				}
				case enWildMush_Healing:
				{
					if(iTeamOwner != iTeamVictim)
						break;

					new iBonusHp = floatround(fDmg);
					new iMinHealth = clHP:getRaceMinHealth(idVictim);
					new iCurrentHealth =  clHP:getUserHealth(idVictim);

					if(iCurrentHealth >= iMinHealth)
						break;

					if( (iCurrentHealth + iBonusHp) > iMinHealth)
						clHP:setUserHealth(idVictim,iMinHealth);
					else
						clHP:setUserHealth(idVictim,iCurrentHealth + iBonusHp);

					Create_TE_BEAMENTS(idEntity, idVictim, arrIdSprites[SPR_LIGHTNING], 0, 1, 1, 20, 30, 3,255,242,    255, 0 );
					
					if (pev_valid(idEntity))
						set_pev(idEntity,pev_health,fHealth);

				}
				case enWildMush_Explode:
				{
					if(iTeamOwner == iTeamVictim)
						break;

					ExecuteHamB(Ham_TakeDamage, idVictim, idEntity, idOwner,fDmg, DMG_FALL );
					Create_TE_BEAMENTS(idEntity, idVictim, arrIdSprites[SPR_LIGHTNING], 0, 1, 1, 20, 30, 255,0,0,    255, 0 );

					if (pev_valid(idEntity))
						set_pev(idEntity,pev_health,fHealth);
				}
				//Раса: Бладсикер (Race: Bloodseeker)
				//Супер навык - Кровавое безумие - Bloody madness
				case enWildMush_Blood:
				{
					if(iTeamOwner == iTeamVictim)
						break;

					new iBonusHp = floatround(fDmg);
					new iMinHealth = clHP:getRaceMinHealth(idOwner);
					new iCurrentHealth =  clHP:getUserHealth(idOwner);
					
					if((iCurrentHealth + iBonusHp) > iMinHealth)
						clHP:setUserHealth(idOwner, iMinHealth);
					else
						clHP:setUserHealth(idOwner,iCurrentHealth + iBonusHp);
					
					stockTraceBlood(idEntity, 8);

					Create_TE_BEAMENTS(idEntity, idVictim, arrIdSprites[SPR_LIGHTNING], 0, 1, 1, 30, 30,  255,0,0,   255, 0 );
					
					if(fDmg > 0.0)
						ExecuteHamB(Ham_TakeDamage, idVictim, idEntity, idOwner,fDmg,DMG_FALL);

					if (pev_valid(idEntity))
						set_pev(idEntity,pev_health,fHealth);
						
				}
			}
			
			
			
		}
	}

	if (pev_valid(idEntity))
		set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);
}

// ********************************************************************
// Проверка установки грибов на респе врага,около заложников и около c4
// ********************************************************************
bool:clDruid::IsWildMushroomSetup(const idUser)
{
	new vPlayerOrigin[3];
 	get_user_origin( idUser, vPlayerOrigin );

	if (SHARED_NearObjective( vPlayerOrigin ) == OBJENT_HOSTAGE )
		return false;

	if (SHARED_NearObjective( vPlayerOrigin ) == OBJENT_BOMBSITE )
		return false;

	if(clDruid::IsWildMushroomResp(idUser) == true)
		return false;


	new Float:vEntOrigin[3];
 	new vEntityOrigin[3];
 	
 	new iEnt = find_ent_by_model( -1, "grenade", "models/w_c4.mdl" )
 	
	if (iEnt && is_valid_ent( iEnt ) ) 
	{
		
    	entity_get_vector( iEnt, EV_VEC_origin, vEntOrigin )
    
    	vEntityOrigin[0] = floatround( vEntOrigin[0] );
    	vEntityOrigin[1] = floatround( vEntOrigin[1] );
    	vEntityOrigin[2] = floatround( vEntOrigin[2] );
    	
    	if (get_distance( vPlayerOrigin, vEntityOrigin ) < (250.0 + fRadiusSpawnWild) )
    		return false;
	}
	
	return true;
}

bool:clDruid::IsWildMushroomResp(const idUser)
{
	new vPlayerOrigin[3];
	get_user_origin( idUser, vPlayerOrigin );

	new iSpawnID,vOrigin[3];
	new entInfoSpawn = -1;
	new Float:fSpawnOrigin[3];
	new bool:bFound = false;

	new iTeam = get_user_team( idUser );
	iTeam = ( ( iTeam == TEAM_CT ) ? TEAM_T : TEAM_CT );
	iSpawnID = ( ( iTeam == TEAM_CT ) ? 0 : 1 );

	do {
		entInfoSpawn = find_ent_by_class( entInfoSpawn, szSpawnEnt[iSpawnID] );

		if ( entInfoSpawn != 0 )
		{
			entity_get_vector( entInfoSpawn, EV_VEC_origin, fSpawnOrigin );

			FVecIVec( fSpawnOrigin, vOrigin );

			if (get_distance( vPlayerOrigin, vOrigin ) < (250.0 + fRadiusSpawnWild) )
			{
				bFound = true;

				break;
			}
		}
	}
	while ( entInfoSpawn && !bFound )

	return bFound;
}

// **********************************************************************
// Скил 4 уровня - Увечье - Mangle
// **********************************************************************
public clDruid::skillMangle(idAttacker,idVictim,iWeapon,iHitPlace)
{
	if (!arrBoolData[idVictim][PB_ISCONNECTED] || !arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;
	
	if(isDisabledSkillsOnMap(idAttacker,PASS_MANGLE_DRUID) == true)
		return;

	if (random_float(0.0,1.0) <= fShanceMangle)
	{
		new ptVictimOrigin[3], ptAttackerOrigin[3];
		get_user_origin(idVictim, ptVictimOrigin );
		get_user_origin(idAttacker, ptAttackerOrigin);

		Create_TE_SPRITETRAIL(ptAttackerOrigin, ptVictimOrigin, arrIdSprites[SPR_MANGLE], 25, 7, 1, 3, 10 );
		
		emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_MANGLE], 1.0, ATTN_NORM, 0, PITCH_NORM );

		WC3_Damage(idVictim, idAttacker, iShanceMangleDmg , iWeapon, iHitPlace );
			
		SHARED_GlowShell(idVictim, 180, 6, 254, 1.5, 50);

		Create_ScreenFade(idVictim, (1<<10), (1<<10), (1<<12), 255, 0, 0, 100);

	}

}


// *******************************************************
// Супер навык - Астральная буря - Astral Storm
// *******************************************************
public clDruid::ultAstralStorm(idUser)
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
		return;
	}

	//Создание эффектов
	new Float:ptOriginPlayer[3];
	new Float:vViewOfs[3];
	new Float:ptOriginSpawn[3];
	new Float:fPunchAngle[3];

	pev(idUser, pev_origin, ptOriginPlayer);					// Координата игрока
	pev(idUser, pev_view_ofs, vViewOfs);						// Получить смещение глаз игрока
	xs_vec_add(ptOriginPlayer, vViewOfs, ptOriginPlayer);		// Складываем смещение глаз и координаты игрока - получаем координаты его глаз
	pev(idUser, pev_v_angle, ptOriginSpawn);					// Получаем угол куда смотрит игрок
	pev(idUser, pev_punchangle, fPunchAngle);					// Это так сказать "искажение" угла взора игрока
	xs_vec_add(ptOriginSpawn, fPunchAngle, ptOriginSpawn);		// Складываем и получаем настоящий угол
	engfunc(EngFunc_MakeVectors, ptOriginSpawn);				// Делаем из угла единичный вектор
	global_get(glb_v_forward, ptOriginSpawn);					// Получаем этот вектор
	xs_vec_mul_scalar(ptOriginSpawn, 4048.0, ptOriginSpawn);	// Умножаем его
	xs_vec_add(ptOriginSpawn, ptOriginPlayer, ptOriginSpawn);	// Прибавляем к координатам игрока, чтобы получить вектор от координат игрока, направленный по его взору

	new tr;
	engfunc(EngFunc_TraceLine,ptOriginPlayer, ptOriginSpawn, 0, idUser, tr);	// Трассируем линию от координат до конца вектора
	get_tr2(tr, TR_vecEndPos, ptOriginSpawn);									// Получаем конечную точку
	free_tr2(tr);																// Освобождаем "указатель" трассирования (После этого начальная позиция пули в origin, конечная в angle)
	

	Create_TE_DLIGHT(uFloatPointToInt(ptOriginSpawn), 25, 222,228, 223, 7, 10 );
	
	
	emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_ASTRAL_STORM], 1.0, ATTN_NORM, 0, PITCH_NORM );

	new idVictim;
	while ((idVictim = engfunc(EngFunc_FindEntityInSphere, idVictim, ptOriginSpawn, fAStormRadiusDmg)))
	{
		if(get_user_team(idVictim) != get_user_team(idUser) && is_user_alive(idVictim))
		{
			ExecuteHamB(Ham_TakeDamage, idVictim ,0, idUser,fAStormDmg, DMG_NERVEGAS);

			Create_ScreenShake(idVictim, (1<<14), (1<<12)*8, (2<<12)*7);
		
			Create_ScreenFade(idVictim, (6<<8), (6<<10), (1<<1), 255, 155, 55, 255 );
			
		}//if

	}//while

	
	//Создание осколков	
	for (new i; i < random_num(20,40); i++)
	{
		
		new idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target")); // Создаем энтити
	
		if(!pev_valid(idEntity))
			continue;

		set_pev(idEntity, pev_classname, "AstralStorm");							// Задаем класс создаваемой сущности
		set_pev(idEntity,pev_team,get_user_team(idUser));							// Сохраняем команду игрока
		set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
		set_pev(idEntity, pev_origin, ptOriginSpawn);								// Задаем позицию сущности

		set_pev(idEntity, pev_modelindex, arrIdSprites[SPR_ASTRAL_STORM]);			// Задаем индекс создаваемой сущности
		fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти

		set_pev(idEntity, pev_movetype, MOVETYPE_BOUNCE);
		set_pev(idEntity, pev_solid, SOLID_BBOX);

		set_pev(idEntity, pev_scale, 0.5);											// Задаем масштаб сущности
		set_pev(idEntity, pev_dmg, fAstormSmallDmg);								// Закладываем дамаг в сущность
		
		// Работа с разбросом, будет рандомная в пределе лимита.
		new Float:fVelocity[3];
		fVelocity[0] = random_float(-250.0,350.0);
		fVelocity[1] = random_float(-250.0,350.0);	
		fVelocity[2] = random_float(-250.0, 700.0);
		
		// Устанавливаем силу разлета осколок
		set_pev(idEntity, pev_velocity, fVelocity);
		new Float:Angles[3];
		Angles[1] = 360.0;//random_float(0.0,360.0)
		set_pev(idEntity,pev_angles,Angles);

		Create_TE_BEAMFOLLOW(idEntity, arrIdSprites[SPR_ICE_ARROW_TRAIL], 6, 6, 10, 252, 51, 255 );

	}//for

	
	//Сброс счетчика
	fResetUltimateTimerDivider(idUser);

	return;
	
}


// ******************************************************************
// Создание и управление эффектами для супер навыка
// ******************************************************************
public touchAstralStorm(idEntity, idWorldPlayer)
{
	if (!pev_valid( idEntity ))
		return;

	new Float:ptOriginSpawn[3];
	pev(idEntity, pev_origin, ptOriginSpawn);
	new idOwner = pev(idEntity, pev_owner);
	new Float:fDmgAStorm = float(pev(idEntity, pev_dmg));

	clDruid::efBeamCylinder(ptOriginSpawn,20,40);
	clDruid::efBeamCylinder(ptOriginSpawn,40,20);

	Create_TE_DLIGHT(uFloatPointToInt(ptOriginSpawn), 15, 222,228, 223, 7, 10 );
	
	new idVictim;
	while ((idVictim = engfunc(EngFunc_FindEntityInSphere, idVictim, ptOriginSpawn, fAstormSmallRadDmg)))
	{
		if (get_user_team(idVictim) != get_user_team(idOwner) && is_user_alive(idVictim))
		{
			ExecuteHamB(Ham_TakeDamage, idVictim , idEntity, idOwner, fDmgAStorm , DMG_BULLET | DMG_NEVERGIB);
			
			Create_ScreenShake(idVictim, (1<<14), (1<<12)*8, (2<<12)*7);
		
			Create_ScreenFade(idVictim, (6<<8), (6<<10), (1<<1), 255, 155, 55, 255 );
			
		}//if

	}//while

	// Удаляем осколок
	remove_entity(idEntity);
}

stock clDruid::efBeamCylinder(Float:ptfOrigin[3],iSize,iWidth)
{

	engfunc(EngFunc_MessageBegin, MSG_PVS, SVC_TEMPENTITY, ptfOrigin, 0);
	write_byte(TE_BEAMCYLINDER);		// TE id
	engfunc(EngFunc_WriteCoord, ptfOrigin[0]);		// x
	engfunc(EngFunc_WriteCoord, ptfOrigin[1]);		// y
	engfunc(EngFunc_WriteCoord, ptfOrigin[2]);		// z
	engfunc(EngFunc_WriteCoord, ptfOrigin[0]);		// x axis
	engfunc(EngFunc_WriteCoord, ptfOrigin[1]);		// y axis
	engfunc(EngFunc_WriteCoord, ptfOrigin[2] + iSize);	// z axis
	write_short(arrIdSprites[SPR_SHOCKWAVE]); 	// sprite
	write_byte(1); 		// startframe
	write_byte(1); 		// framerate
	write_byte(10); 		// life
	write_byte(iWidth); 	// width
	write_byte(0); 		// noise
	write_byte(175); 		// red
	write_byte(206); 		// green
	write_byte(180); 		// blue
	write_byte(255); 		// brightness
	write_byte(5); 		// speed
	message_end();
}


// ******************************************************************
// Меню
// ******************************************************************
//Вызов отображения меню для активации скилов
fShowMenuActiveSkills_Druid(idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;

	new idMenu,szNumber[64],szMenuData[256];
	
	//Название главного меню
	formatex(szMenuData, charsmax(szMenuData), "\y%L", LANG_PLAYER, "MENU_ID_ACTIVE_SKILLS");
	idMenu = menu_create(szMenuData, "_Callback_ActiveSkills_Druid");

	new szSkillName[64],szSkillFull[255];
	fGetSkillName(SKILL_DRUID_1,szSkillName, charsmax(szSkillName));
	formatex(szNumber, charsmax(szNumber), "%d", SKILL_DRUID_1);
	formatex(szSkillFull, charsmax(szSkillFull), "%s: \w%d | min \y%d \w| max \r%d", szSkillName,arrSkillChargeNum[idUser][SKILL_DRUID_1],arrSkillChargeMin[SKILL_DRUID_1],arrSkillChargeMax[SKILL_DRUID_1]);
	menu_additem(idMenu,szSkillFull,szNumber,0,-1);

	fGetSkillName(SKILL_DRUID_2,szSkillName, charsmax(szSkillName));
	formatex(szNumber, charsmax(szNumber), "%d", SKILL_DRUID_2);
	formatex(szSkillFull, charsmax(szSkillFull), "%s: \w%d | min \y%d \w| max \r%d", szSkillName,arrSkillChargeNum[idUser][SKILL_DRUID_2],arrSkillChargeMin[SKILL_DRUID_2],arrSkillChargeMax[SKILL_DRUID_2]);
	menu_additem(idMenu,szSkillFull,szNumber,0,-1);

	fGetSkillName(SKILL_DRUID_3,szSkillName, charsmax(szSkillName));
	formatex(szNumber, charsmax(szNumber), "%d", SKILL_DRUID_3);
	formatex(szSkillFull, charsmax(szSkillFull), "%s: \w%d | min \y%d \w| max \r%d", szSkillName,arrSkillChargeNum[idUser][SKILL_DRUID_3],arrSkillChargeMin[SKILL_DRUID_3],arrSkillChargeMax[SKILL_DRUID_3]);
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
public _Callback_ActiveSkills_Druid(idUser, idMenu, iItemMenu)
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
		case SKILL_DRUID_1:
		{
			//Заблокирован ли супер навык на карте
			new szSkillName[64];
			if(isDisabledSkillsOnMap(idUser,SKILL_DRUID_1,szSkillName) == true)
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SKILL_DISABLED_ON_MAP",szSkillName);
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

			if(clDruid::IsWildMushroomSetup(idUser) == false)
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WILDMUSHROOM");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				menu_destroy(idMenu);
				return PLUGIN_HANDLED;
			}

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ACTIVE_SKILLS",szSkillName);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

			clDruid::skillWildMush_Entangle(idUser,iSkillID);

		}
		case SKILL_DRUID_2:
		{
			//Заблокирован ли супер навык на карте
			new szSkillName[64];
			if(isDisabledSkillsOnMap(idUser,SKILL_DRUID_2,szSkillName) == true)
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SKILL_DISABLED_ON_MAP",szSkillName);
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

			if(clDruid::IsWildMushroomSetup(idUser) == false)
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WILDMUSHROOM");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				menu_destroy(idMenu);
				return PLUGIN_HANDLED;
			}

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ACTIVE_SKILLS",szSkillName);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

			clDruid::skillWildMush_Healing(idUser,iSkillID);
		}
		case SKILL_DRUID_3:
		{
			//Заблокирован ли супер навык на карте
			new szSkillName[64];
			if(isDisabledSkillsOnMap(idUser,SKILL_DRUID_3,szSkillName) == true)
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SKILL_DISABLED_ON_MAP",szSkillName);
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

			if(clDruid::IsWildMushroomSetup(idUser) == false)
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WILDMUSHROOM");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				menu_destroy(idMenu);
				return PLUGIN_HANDLED;
			}

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ACTIVE_SKILLS",szSkillName);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

			clDruid::skillWildMush_Explode(idUser,iSkillID);			
		}
	}

	menu_destroy(idMenu);

	//client_print(idUser,print_chat,"iNumberItem: %d |iSkillID: %d",iNumberItem,iItemMenu);	

	return PLUGIN_HANDLED;
}
