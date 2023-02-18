// ******************************************************************
// Раса: Бладсикер (Race: Bloodseeker) Functions
// ******************************************************************


//Инициализация скилов Race: Bloodseeker (Бладсикер)
public clBloodseeker::setSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	g_SkillOwner[SKILL_BLOODSEEKER_1			]	= RACE_BLOODSEEKER;
	g_SkillOwner[SKILL_BLOODSEEKER_2			]	= RACE_BLOODSEEKER;
	g_SkillOwner[SKILL_BLOODSEEKER_3			]	= RACE_BLOODSEEKER;
	g_SkillOwner[ULTIMATE_BLOODSEEKER			]	= RACE_BLOODSEEKER;
	g_SkillOwner[PASS_BLOODSEEKER				]	= RACE_BLOODSEEKER;

	g_SkillType[SKILL_BLOODSEEKER_1				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_BLOODSEEKER_2				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_BLOODSEEKER_3				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_BLOODSEEKER			]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_BLOODSEEKER				]	= SKILL_TYPE_PASSIVE;

	g_SkillOrder[SKILL_BLOODSEEKER_1			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_BLOODSEEKER_2			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_BLOODSEEKER_3			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_BLOODSEEKER			]	= SKILL_POS_4;
	g_SkillOrder[PASS_BLOODSEEKER				]	= SKILL_POS_NONE;


	//Максимальное количество зарядов
	arrSkillChargeMax[SKILL_BLOODSEEKER_1			]	= iBloodseekerChargeMax_1;
	arrSkillChargeMax[SKILL_BLOODSEEKER_2			]	= iBloodseekerChargeMax_2;
	arrSkillChargeMax[SKILL_BLOODSEEKER_3			]	= iBloodseekerChargeMax_3;

	//Минимальное количество зарядов
	arrSkillChargeMin[SKILL_BLOODSEEKER_1			]	= iBloodseekerChargeMin_1;
	arrSkillChargeMin[SKILL_BLOODSEEKER_2			]	= iBloodseekerChargeMin_2;
	arrSkillChargeMin[SKILL_BLOODSEEKER_3			]	= iBloodseekerChargeMin_3;

	//Счетчик через сколько шанс получить заряд
	arrSkillCount[SKILL_BLOODSEEKER_1				]	= iBloodseekerCount_1;
	arrSkillCount[SKILL_BLOODSEEKER_2				]	= iBloodseekerCount_2;
	arrSkillCount[SKILL_BLOODSEEKER_3				]	= iBloodseekerCount_3;
	
}

//Инициализация начального количества зарядов у игрока
public clBloodseeker::setChargeNum(idUser)//добавлена в war3ft.cpp ( WC3_PlayerInit( idUser ) )
{
	arrSkillChargeNum[idUser][SKILL_BLOODSEEKER_1] = iBloodseekerChargeMin_1;
	arrSkillChargeNum[idUser][SKILL_BLOODSEEKER_2] = iBloodseekerChargeMin_2;
	arrSkillChargeNum[idUser][SKILL_BLOODSEEKER_3] = iBloodseekerChargeMin_3;

}

//Добавляем заряд скилу. Функция размещается в зависимости от того,
//каким способом будет даваться заряд (время,дамаг,убийство и тд)
clBloodseeker::addSkillCharge(const iSkillID,const idUser,const iNumIncrement = 1)
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
		case SKILL_BLOODSEEKER_1:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser,iSkillID);
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
				new Float:fBloodRage = ArrayGetCell(arrBloodRage,iSkillLevel-1);
				if (random_float(fBloodseekerSkill1MinPercent,fBloodseekerSkill1MaxPercent) <= fBloodRage )		
				{
					arrSkillChargeNum[idUser][iSkillID] += iNumIncrement;
					WC3_ShowBar(idUser);
				}
			}
		}
		case SKILL_BLOODSEEKER_2:
		{
			new iSkillLevel = SM_GetSkillLevel(idUser, iSkillID );
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
				new Float:fBloodBath = ArrayGetCell(arrBloodBath,iSkillLevel-1);
				if (random_float(fBloodseekerSkill2MinPercent,fBloodseekerSkill2MaxPercent) <= fBloodBath)		
				{
					arrSkillChargeNum[idUser][iSkillID] += iNumIncrement;
					WC3_ShowBar(idUser);
				}
			}
		}
		case SKILL_BLOODSEEKER_3:
		{			
			new iSkillLevel = SM_GetSkillLevel(idUser, iSkillID );
			if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,iSkillID) == false)
			{
			
				new Float:fBloodRite = ArrayGetCell(arrBloodRite,iSkillLevel-1);
				if (random_float(fBloodseekerSkill3MinPercent,fBloodseekerSkill3MaxPercent) <= fBloodRite )		
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
// Скил 1 уровня - Blood Rage - Ярость крови
// **********************************************************************
clBloodseeker::skillBloodRage(const idAttacker,const idVictim,const iSkillID)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
		return;

	if(!is_user_alive(idVictim) || !is_user_connected(idVictim)) 
		return;

	if(isDisabledSkillsOnMap(idAttacker,iSkillID) == true)
		return;

	//Скил активен
	if(arrIsSkillChargeActive[idAttacker][iSkillID] == true)
	{
		WC3_Damage(idVictim,idAttacker,iBloodRageDmg, CSW_BLOOD_RAGE, 0 );

		SHARED_ResetMaxSpeed(idAttacker);
		arrBoolData[idAttacker][PB_BLOODRAGE] = true;
		SHARED_SetSpeed(idAttacker);

		return;
	}

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idAttacker][iSkillID] <= 0)
		return;

	if(arrSkillChargeNum[idAttacker][iSkillID] < arrSkillChargeMin[iSkillID])
		return;

	//Срабатывание
	arrIsSkillChargeActive[idAttacker][iSkillID] = true;

	new Float:fNumCharge = float(arrSkillChargeNum[idAttacker][iSkillID]);
	set_task(fNumCharge, "_taskResetBloodRage", clBloodseeker::tID_BLOODRAGE + idAttacker);

	SHARED_GlowShell(idAttacker, 252, 40, 2, 2.0, 50);
	Create_ScreenFade(idAttacker, (1<<10), (1<<10), (1<<12), 255, 0, 0, 100);
	emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_BLOODRAGE], 1.0, ATTN_NORM, 0, PITCH_NORM );
	
	SHARED_ResetMaxSpeed(idAttacker);
	arrBoolData[idAttacker][PB_BLOODRAGE] = true;
	SHARED_SetSpeed(idAttacker);

	//Обнуляем заряды после срабатывания или списываем заряды
	if(arrSkillChargeNum[idAttacker][iSkillID] >= arrSkillChargeMin[iSkillID])
		arrSkillChargeNum[idAttacker][iSkillID] -= arrSkillChargeMin[iSkillID];
	else
		arrSkillChargeNum[idAttacker][iSkillID] = 0;

	WC3_ShowBar(idAttacker);
}

public clBloodseeker::taskResetBloodRage(idUser)
{
	if (idUser >= clBloodseeker::tID_BLOODRAGE)
		idUser -= clBloodseeker::tID_BLOODRAGE;

	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;
	
	arrIsSkillChargeActive[idUser][SKILL_BLOODSEEKER_1] = false;

	SHARED_ResetMaxSpeed(idUser);
	arrBoolData[idUser][PB_BLOODRAGE] = false;
	SHARED_SetSpeed(idUser);

	new szSkillName[64];
	fGetSkillName(SKILL_BLOODSEEKER_1,szSkillName, charsmax(szSkillName));
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_DEACTIVE_SKILLS",szSkillName);
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

}

// **********************************************************************
// Скил 2 уровня - Blood Bath  - Кровавая баня
// **********************************************************************
clBloodseeker::skillBloodBath(const idAttacker,const idVictim,const iSkillID)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
      return;

	if(isDisabledSkillsOnMap(idAttacker,iSkillID) == true)
		return;

	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idAttacker][iSkillID] <= 0)
		return;

	new iMaxHealth = clHP:getRaceMaxHealth(idVictim);
	new iCurrentHealth =  clHP:getUserHealth(idAttacker);

	new iBonusHp = iMaxHealth - floatround(iMaxHealth * fBloodBathHpFactor);
	
	if( (iCurrentHealth + iBonusHp) > iMaxHealth)
		clHP:setUserHealth(idAttacker,iMaxHealth);
	else
		clHP:setUserHealth(idAttacker,iCurrentHealth + iBonusHp);

	SHARED_GlowShell(idAttacker, 198, 252, 148, 0.5, 50);
	Create_ScreenFade(idAttacker, (1<<10), (1<<10), (1<<12), 198, 252, 148, 100);

	//Удаляем один заряд после срабатывания
	arrSkillChargeNum[idAttacker][iSkillID] -= 1;

	WC3_ShowBar(idAttacker);
}


// **********************************************************************
// Скил 3 уровня - Blood Rite  - Кровавый обряд
// **********************************************************************
clBloodseeker::skillBloodRite(const idAttacker,const idVictim,const iSkillID)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
      return;

	if(!is_user_alive(idVictim) || !is_user_connected(idVictim)) 
      return;

	if(isDisabledSkillsOnMap(idAttacker,iSkillID) == true)
		return;

	//Скил активен
	if(arrIsSkillChargeActive[idAttacker][iSkillID] == true)
		return;
	
	//Зарядов нет у атакующего
	if(arrSkillChargeNum[idAttacker][iSkillID] <= 0)
		return;

	if(arrSkillChargeNum[idAttacker][iSkillID] < arrSkillChargeMin[iSkillID])
		return;

	//Срабатывание
	arrIsSkillChargeActive[idAttacker][iSkillID] = true;

	WC3_Damage(idVictim,idAttacker, iBloodRiteDmg, CSW_BLOOD_RITE, 0 );

	new Float:fNumCharge = float(arrSkillChargeNum[idAttacker][iSkillID]);
	set_task(fNumCharge, "_taskResetBloodRiteA", clBloodseeker::tID_BLOODRITE_A + idAttacker);

	set_task(fNumCharge / 2.0, "_taskResetBloodRiteV", clBloodseeker::tID_BLOODRITE_V + idVictim);

	arrBoolData[idVictim][PB_BLOODRITE] = true;

	new ptOriginVictim[3];	
	get_user_origin(idVictim, ptOriginVictim);

	new vInitOrigin[3], vAxisOrigin[3];
	vInitOrigin[0] = ptOriginVictim[0];
	vInitOrigin[1] = ptOriginVictim[1];
	vInitOrigin[2] = ptOriginVictim[2] - 16;

	vAxisOrigin[0] = ptOriginVictim[0];
	vAxisOrigin[1] = ptOriginVictim[1];
	vAxisOrigin[2] = ptOriginVictim[2] + 30;
	
	Create_TE_BEAMCYLINDER( ptOriginVictim, vInitOrigin, vAxisOrigin, arrIdSprites[SPR_BLOODRITE], 0, 0, 5, 50, 0, 255, 255, 255, 255, 0 );

	emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_BLOODRITE], 1.0, ATTN_NORM, 0, PITCH_NORM );
	
	//Обнуляем заряды после срабатывания или списываем заряды
	if(arrSkillChargeNum[idAttacker][iSkillID] >= arrSkillChargeMin[iSkillID])
		arrSkillChargeNum[idAttacker][iSkillID] -= arrSkillChargeMin[iSkillID];
	else
		arrSkillChargeNum[idAttacker][iSkillID] = 0;

	WC3_ShowBar(idAttacker);
}

public clBloodseeker::taskResetBloodRiteA(idUser)
{
	if (idUser >= clBloodseeker::tID_BLOODRITE_A)
		idUser -= clBloodseeker::tID_BLOODRITE_A;

	arrIsSkillChargeActive[idUser][SKILL_BLOODSEEKER_3] = false;

	if(!is_user_connected(idUser))
      return;
	
	new szSkillName[64];
	fGetSkillName(SKILL_BLOODSEEKER_3,szSkillName, charsmax(szSkillName));
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_DEACTIVE_SKILLS",szSkillName);
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

}

public clBloodseeker::taskResetBloodRiteV(idUser)
{
	if (idUser >= clBloodseeker::tID_BLOODRITE_V)
		idUser -= clBloodseeker::tID_BLOODRITE_V;

	if(!is_user_connected(idUser)) 
      return;
	
	arrBoolData[idUser][PB_BLOODRITE] = false;
}


// **********************************************************************
// Скил 4 уровня - Кровная месть - Vendetta
// **********************************************************************
public clBloodseeker::skillVendetta(idAttacker,idVictim,iWeapon,iHitPlace)
{
	if (!arrBoolData[idVictim][PB_ISCONNECTED] || !arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;
	
	if(isDisabledSkillsOnMap(idAttacker,PASS_BLOODSEEKER) == true)
		return;

//	Отрисовка кровяных пятен при попаданиях
	static Float:vecStart[3], Float:vecTarget[3],Float:vecViewOfs[3],
	Float:vecVictim[3],trRes,Float:vAngle[3],Float:vForw[3];
		 
	pev(idAttacker, pev_origin, vecStart);
	pev(idAttacker, pev_view_ofs, vecViewOfs); 
	xs_vec_add(vecStart, vecViewOfs, vecStart); 
	pev(idVictim, pev_origin, vecVictim);
		
	pev(idAttacker,pev_v_angle,vAngle);
	engfunc(EngFunc_MakeVectors,vAngle);
	global_get(glb_v_forward,vForw);
	xs_vec_mul_scalar(vForw,9999.0,vForw);
	xs_vec_add(vecStart, vForw, vecTarget);
	engfunc(EngFunc_TraceLine, vecStart, vecTarget, 0, idAttacker, trRes);
					
	Stock_TraceBleed(idVictim,24.0,vecTarget);
	Stock_BloodEffect(vecTarget, 7);

	//Срабатывает в зависимости от кол-ва нанесенного дамага		
	if(iAmountVendettaDMG[idAttacker] > iNumVendettaDMG)
	{
		new ptVictimOrigin[3], ptAttackerOrigin[3];
		get_user_origin(idVictim, ptVictimOrigin );
		get_user_origin(idAttacker, ptAttackerOrigin );
		
		Create_TE_SPRITETRAIL(ptAttackerOrigin, ptVictimOrigin, arrIdSprites[SPR_ROGUE_SHURIKEN], 10, 5, 1, 5, 12 );

		emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_MANGLE], 1.0, ATTN_NORM, 0, PITCH_NORM );

		WC3_Damage(idVictim, idAttacker, iVendettaDmg , iWeapon, iHitPlace);
			
		SHARED_GlowShell(idVictim, 255, 0, 0, 1.5, 30);

		Create_ScreenFade(idVictim, (1<<10), (1<<10), (1<<12), 0, 0, 255, 100);

		iAmountVendettaDMG[idAttacker] = 0;
	}

}


// *******************************************************
// Супер навык - Кровавое безумие - Bloody madness
// *******************************************************
public clBloodseeker::ultBloodyMadness(idAttacker,idVictim)
{		
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim)) 
		return;
	
	new Float:ptOriginPlayer[3];
	pev(idVictim, pev_origin, ptOriginPlayer);

	clDruid::fCreateWildMushroom_2(idAttacker,ptOriginPlayer,fRadiusSpawnWild,0.0, "Wild_Mushroom",arrIdSprites[SPR_SINISTER_STRIKE],0.5,
		fBloodyMadnessDmg, fBloodyMadnessHp,0.3,enWildMush:enWildMush_Blood);
	clDruid::fCreateWildMushroom_2(idAttacker,ptOriginPlayer,fRadiusSpawnWild,120.0, "Wild_Mushroom",arrIdSprites[SPR_SINISTER_STRIKE],0.5,
		fBloodyMadnessDmg, fBloodyMadnessHp,0.3,enWildMush:enWildMush_Blood);
	clDruid::fCreateWildMushroom_2(idAttacker,ptOriginPlayer,fRadiusSpawnWild,240.0, "Wild_Mushroom",arrIdSprites[SPR_SINISTER_STRIKE],0.5,
		fBloodyMadnessDmg, fBloodyMadnessHp,0.3,enWildMush:enWildMush_Blood);

	emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_FIREBALL_PRIEST], 1.0, ATTN_NORM, 0, PITCH_NORM );

}

stock Stock_TraceBleed(iPlayer, Float:fDamage, Float:vecDir[3])
{
	//if (ExecuteHam(Ham_BloodColor, iPlayer) == DONT_BLEED)
		//return
	
	if (fDamage == 0)
		return
	
	new Float:vecTraceDir[3]
	new Float:fNoise
	new iCount, iBloodTr

	if (fDamage < 10)
	{
		fNoise = 0.1
		iCount = 1
	}
	else if (fDamage < 25)
	{
		fNoise = 0.2
		iCount = 2
	}
	else
	{
		fNoise = 0.3
		iCount = 4
	}

	new iTr;
	for (new i = 0; i < iCount; i++)
	{		
		xs_vec_mul_scalar(vecDir, -1.0, vecTraceDir)

		vecTraceDir[0] += random_float(-fNoise, fNoise)
		vecTraceDir[1] += random_float(-fNoise, fNoise)
		vecTraceDir[2] += random_float(-fNoise, fNoise)

		static Float:vecEndPos[3]
		get_tr2(iTr, TR_vecEndPos, vecEndPos)
		xs_vec_mul_scalar(vecTraceDir, -0.5, vecTraceDir)
		xs_vec_add(vecTraceDir, vecEndPos, vecTraceDir)
		engfunc(EngFunc_TraceLine, vecEndPos, vecTraceDir, IGNORE_MONSTERS, iPlayer, iBloodTr)

		static Float:flFraction
		get_tr2(iBloodTr, TR_flFraction, flFraction)
		
		if (flFraction != -1.0)
			Stock_BloodDecalTrace(iBloodTr/*, ExecuteHam(Ham_BloodColor, iPlayer)*/)
	}
}
stock Stock_BloodDecalTrace(iTrace/*, iBloodColor*/)
{

	//client_print(0,print_chat,"Stock_BloodDecalTrace");

	switch (random_num(0, 5))
	{
		case 0: 
			Stock_DecalTrace(iTrace, engfunc(EngFunc_DecalIndex, "{blood1"))
		case 1: 
			Stock_DecalTrace(iTrace, engfunc(EngFunc_DecalIndex, "{blood2"))
		case 2: 
			Stock_DecalTrace(iTrace, engfunc(EngFunc_DecalIndex, "{blood3"))
		case 3: 
			Stock_DecalTrace(iTrace, engfunc(EngFunc_DecalIndex, "{blood4"))
		case 4: 
			Stock_DecalTrace(iTrace, engfunc(EngFunc_DecalIndex, "{blood5"))
		case 5: 
			Stock_DecalTrace(iTrace, engfunc(EngFunc_DecalIndex, "{blood6"))
	}
}
stock Stock_DecalTrace(iTrace, iDecalNumber)
{
	if (iDecalNumber < 0)
		return

	static Float:flFraction
	get_tr2(iTrace, TR_flFraction, flFraction)
	
	if (flFraction == 1.0)
		return

	new iHit = get_tr2(iTrace, TR_pHit)
	
	if (pev_valid(iHit))
	{
		if ((pev(iHit, pev_solid) != SOLID_BSP && pev(iHit, pev_movetype) != MOVETYPE_PUSHSTEP))
			return	
	}
	else 
		iHit = 0

	new iMessage = TE_DECAL
	if (iHit != 0)
	{
		if (iDecalNumber > 255)
		{
			iDecalNumber -= 256
			iMessage = TE_DECALHIGH
		}
	}
	else
	{
		iMessage = TE_WORLDDECAL
		if (iDecalNumber > 255)
		{
			iDecalNumber -= 256
			iMessage= TE_WORLDDECALHIGH
		}
	}
	
	static Float:vecEndPos[3]
	get_tr2(iTrace, TR_vecEndPos, vecEndPos)
	
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
	write_byte(iMessage)
	engfunc(EngFunc_WriteCoord, vecEndPos[0])
	engfunc(EngFunc_WriteCoord, vecEndPos[1])
	engfunc(EngFunc_WriteCoord, vecEndPos[2])
	write_byte(iDecalNumber)
	if (iHit) write_short(iHit)
	message_end()
	
}

stock Stock_BloodEffect(Float:vecOri[3], scale)
{
	//if(!get_pcvar_num(cvar_friendlyfire)) return
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY) 
	write_byte(TE_BLOODSPRITE)
	engfunc(EngFunc_WriteCoord,vecOri[0])
	engfunc(EngFunc_WriteCoord,vecOri[1])
	engfunc(EngFunc_WriteCoord,vecOri[2])
	write_short(arrIdSprites[SPR_BLOODSPRAY])
	write_short(arrIdSprites[SPR_BLOODDROP])
	write_byte(75)
	write_byte(scale)
	message_end()
}


// ******************************************************************
// Меню
// ******************************************************************
//Вызов отображения меню для активации скилов
public clBloodseeker::fShowMenuAbility(idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return;

	new idMenu,szNumber[64],szMenuData[256];
	
	//Название главного меню
	formatex(szMenuData, charsmax(szMenuData), "\y%L", LANG_PLAYER, "MENU_ID_ACTIVE_SKILLS");
	idMenu = menu_create(szMenuData, "_Callback_Menu_Bloodseeker");

	new szSkillName[64],szSkillFull[255];
	fGetSkillName(SKILL_BLOODSEEKER_1,szSkillName, charsmax(szSkillName));
	formatex(szNumber, charsmax(szNumber), "%d", SKILL_BLOODSEEKER_1);
	formatex(szSkillFull, charsmax(szSkillFull), "%s: \w%d | min \y%d \w| max \r%d", szSkillName,arrSkillChargeNum[idUser][SKILL_BLOODSEEKER_1],arrSkillChargeMin[SKILL_BLOODSEEKER_1],arrSkillChargeMax[SKILL_BLOODSEEKER_1]);
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

//Функция выбора пунктов в меню
public clBloodseeker::Callback_Menu(idUser, idMenu, iItemMenu)
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
		case SKILL_BLOODSEEKER_1:
		{
			//Заблокирован ли супер навык на карте
			new szSkillName[64];
			if(isDisabledSkillsOnMap(idUser,SKILL_BLOODSEEKER_1,szSkillName) == true)
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

			//Если скил активен
			if (task_exists(clBloodseeker::tID_BLOODRAGE + idUser))
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_IS_ACTIVE",szSkillName);
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				menu_destroy(idMenu);
				return PLUGIN_HANDLED;
			}
			else
			{
				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ACTIVE_SKILLS",szSkillName);
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
				arrIsSkillChargeActive[idUser][iSkillID] = true;

				new Float:fNumCharge = float(arrSkillChargeNum[idUser][iSkillID]);
				set_task(fNumCharge, "_taskResetBloodRage", clBloodseeker::tID_BLOODRAGE + idUser);
				
				SHARED_GlowShell(idUser, 252, 40, 2, 2.0, 50);
				Create_ScreenFade(idUser, (1<<10), (1<<10), (1<<12), 255, 0, 0, 100);
				emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_BLOODRAGE], 1.0, ATTN_NORM, 0, PITCH_NORM );
				
				SHARED_ResetMaxSpeed(idUser);
				arrBoolData[idUser][PB_BLOODRAGE] = true;
				SHARED_SetSpeed(idUser);
				

				//Обнуляем заряды после срабатывания или списываем заряды
				if(arrSkillChargeNum[idUser][iSkillID] >= arrSkillChargeMin[iSkillID])
					arrSkillChargeNum[idUser][iSkillID] -= arrSkillChargeMin[iSkillID];
				else
					arrSkillChargeNum[idUser][iSkillID] = 0;
			}
		}
		
	}

	menu_destroy(idMenu);

	//client_print(idUser,print_chat,"iNumberItem: %d |iSkillID: %d",iNumberItem,iItemMenu);	

	return PLUGIN_HANDLED;
}
