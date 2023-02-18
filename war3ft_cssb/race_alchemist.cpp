/*
*	Race: Alchemist Functions
*/

#define RADIATION_MAX_DAMAGE 50
#define RADIATION_RANGE 300
#define RADIATION_BLAST_RADIUS 250


//Инициализация скилов
public setALSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	// Set up the Skill Owners		  	
	g_SkillOwner[SKILL_POISON]			= RACE_ALCHEMIST;
	g_SkillOwner[SKILL_SHOCK]			= RACE_ALCHEMIST;
	g_SkillOwner[SKILL_FROST]			= RACE_ALCHEMIST;
	g_SkillOwner[ULTIMATE_RADIATION]	= RACE_ALCHEMIST;
	g_SkillOwner[PASS_HYPNOSIS]			= RACE_ALCHEMIST;
	
	// Set up the skill types
	g_SkillType[SKILL_POISON]			= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_SHOCK]			= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_FROST]			= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_RADIATION]		= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_HYPNOSIS]			= SKILL_TYPE_PASSIVE;
	
	// Set up the skill order
	g_SkillOrder[SKILL_POISON]			= SKILL_POS_1;
	g_SkillOrder[SKILL_SHOCK]			= SKILL_POS_2;
	g_SkillOrder[SKILL_FROST]			= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_RADIATION]	= SKILL_POS_4;
	g_SkillOrder[PASS_HYPNOSIS]			= SKILL_POS_NONE;

}

// Скил первого уровня - Отрава(Poison)
AC_SkillsOffensive( idAttacker, idVictim, iHitPlace )
{
	if ( !arrBoolData[idVictim][PB_ISCONNECTED] || !arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;

	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_POISON );
	if ( iSkillLevel > 0 && isDisabledSkillsOnMap(idAttacker,SKILL_POISON) == false)
	{
		new Float:fPoison = ArrayGetCell(arrPoison,iSkillLevel-1);
		if (random_float(fAlchemistSkill1MinPercent,fAlchemistSkill1MaxPercent) <= fPoison )
		{
			emit_sound( idVictim, CHAN_STATIC, arrStrSounds[SOUND_POISON], 1.0, ATTN_NORM, 0, PITCH_NORM );

			new FunctionSkill[4];
			FunctionSkill[0] = idAttacker;
			FunctionSkill[1] = idVictim;
			FunctionSkill[2] = 1;
			FunctionSkill[3] = iHitPlace;

			new TaskId = TASK_POISON + idVictim;
			set_task(fAlPoisonTime, "AC_SkillsOffensivePoison", TaskId, FunctionSkill, 32 );
		}
	}

	// Пассивка - Потеря ориентации(Disorientation)
	new iSkillLevelPass = SM_GetSkillLevel(idAttacker, PASS_HYPNOSIS);
	if ( iSkillLevelPass > 0 )
	{
		if(isDisabledSkillsOnMap(idAttacker,PASS_HYPNOSIS) == true)
			return;

		new Float:fHypnosis = ArrayGetCell(arrPassHypnosis,iSkillLevelPass-1);
		if (random_float(fAlchemistSkill4MinPercent,fAlchemistSkill4MaxPercent) <= fHypnosis )
		{
			new players[32], numberofplayers, targetid, targetorigin[3], origin[3];
			new iTeam = get_user_team(idVictim);

			get_user_origin( idVictim, origin );
			get_players( players, numberofplayers, "a" );

			for ( new i = 0; i < numberofplayers; i++ )
			{
				targetid = players[i];

				if ( arrBoolData[targetid][PB_ISCONNECTED] && get_user_team( targetid ) == iTeam )
				{
					if ( is_user_alive( targetid ) )
					{
						get_user_origin( targetid, targetorigin );

						if ( get_distance(origin, targetorigin) < 120 )
						{
							Create_ScreenFade( targetid, (1<<15), (1<<10), (1<<12), 0, 0, 0, 255 );
							SHARED_Glow( targetid, 0, 0, 0, 100 );
						}
					}
				}
			}
		}
	}
}

public AC_SkillsOffensivePoison( FunctionSkill[4] )
{
	new idAttacker = FunctionSkill[0];
	new idVictim = FunctionSkill[1];
	new iCounter = FunctionSkill[2];
	new iHitPlace = FunctionSkill[3];

	if ( iCounter > iAlPoisonNumber ) 
	{
		AC_SkillsOffensiveRemove( idVictim );
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive( idVictim ) )
	{
 		if (is_user_alive( idVictim ))
 		{
			new vVictimOrigin[3];

			// Получение координат игрока
			get_user_origin( idVictim, vVictimOrigin );
		
			// Отображение спрайта
			Create_TE_SPRITE( vVictimOrigin, arrIdSprites[SPR_POISON], 10, 200 );

 			WC3_Damage( idVictim, idAttacker, iAlPoisonDamage, CSW_POISON, iHitPlace );

	 		FunctionSkill[2]++;

			set_task(fAlPoisonTime, "AC_SkillsOffensivePoison", TASK_POISON + idVictim, FunctionSkill, 32 );
 		}
 		else if ( get_pcvar_num( CVAR_wc3_psychostats ) )
 		{
 			new WEAPON = CSW_POISON - CSW_WAR3_MIN;
 	
 			iStatsShots[idAttacker][WEAPON]++;
 		}
	}

	return PLUGIN_HANDLED;
}

AC_SkillsOffensiveRemove( idVictim ) 
{
	new TaskId = TASK_POISON + idVictim;
	remove_task( TaskId, 0 );

	return PLUGIN_HANDLED;
}

// Защитные скилы
AC_SkillsDefensive( idAttacker, idVictim )
{
	static iSkillLevel;

	// Скил второго уровня - Сотрясение (Shock)
	iSkillLevel = SM_GetSkillLevel( idVictim, SKILL_SHOCK );
	if ( iSkillLevel > 0 && is_user_alive( idAttacker ) && isDisabledSkillsOnMap(idVictim,SKILL_SHOCK) == false)
	{
		new Float:fShock = ArrayGetCell(arrShock,iSkillLevel-1);
		if (random_float(fAlchemistSkill2MinPercent,fAlchemistSkill2MaxPercent) <= fShock )
		{
			// Функция тряски экрана
			Create_ScreenShake( idAttacker, (10<<12), (2<<12), (5<<12) );
		}
	}

	// Скил третего уровня - Ледяное дыхание (Frost)
	iSkillLevel = SM_GetSkillLevel( idVictim, SKILL_FROST );
	if ( iSkillLevel > 0 && is_user_alive( idAttacker ) )
	{
		if(isDisabledSkillsOnMap(idVictim,SKILL_FROST) == true)
			return;

		new Float:fFrost = ArrayGetCell(arrFrost,iSkillLevel-1);
		if (random_float(fAlchemistSkill3MinPercent,fAlchemistSkill3MaxPercent) <= fFrost )
		{
			// Проигрование звука
			emit_sound( idAttacker, CHAN_STATIC, arrStrSounds[SOUND_FROST], 1.0, ATTN_NORM, 0, PITCH_NORM );

			arrBoolData[idAttacker][PB_FROST] = true;
			SHARED_SetSpeed(idAttacker);
			
			set_task(fAlFrostHoldTime, "SHARED_ResetMaxSpeed", TASK_RESETSPEED + idAttacker );
		}
	}
}

// Ультиматум - Настойка затмения
public AC_ULT_Eclipse(iCaster, iTarget)
{
	//Определение какие предметы были у жертвы
	new iItemVictimShop1 = bIsItemUserSlot(iTarget,ITEM_SLOT_ONE);
	new iItemVictimShop2 = bIsItemUserSlot(iTarget,ITEM_SLOT_TWO);
	new iItemVictimShop3 = bIsItemUserSlot(iTarget,ITEM_SLOT_THREE);

	//Проверка на наличие вещей
	new bIsDropItems = fIsDropItems(iItemVictimShop1,iItemVictimShop2,iItemVictimShop3);

	//new iItem = ITEM_NONE;
	new iItem = random_num(0,MAX_SHOPMENU_ITEMS-1);//Дается любой предмет не зависимо есть ли у противника
	if(iItemVictimShop1 != ITEM_NONE)
		iItem = iItemVictimShop1;
	else if (iItemVictimShop2 != ITEM_NONE)
		iItem = iItemVictimShop2;
	else if (iItemVictimShop3 != ITEM_NONE)
		iItem = iItemVictimShop3;

	if (iItem > ITEM_NONE)
	{
		new szItemName[64];

		new vVictimOrigin[3];
		get_user_origin( iTarget, vVictimOrigin );
		vVictimOrigin[2] += 10;
		Create_TE_SPRITE( vVictimOrigin, arrIdSprites[SPR_ECLIPSE], 10, 200 );

		// Проигрование звука
		emit_sound( iTarget, CHAN_STATIC, arrStrSounds[SOUND_RADIATION], 1.0, ATTN_NORM, 0, PITCH_NORM );

		//Получение названия предмета
		LANG_GetItemName( iItem, iTarget, szItemName, charsmax(szItemName) );

		if(bIsDropItems != 0)//Если были предметы у противника выводим сообщение
		{
			format(szMessage, charsmax(szMessage), "^x01%L",LANG_PLAYER,"CLIENT_PRINT_ECLIPSE",szItemName);
			cssbChatColor(iCaster,"%s%s",fTagWar3ft(),szMessage);
		}

		if ( ITEM_GetSlot( iCaster ) != ITEM_SLOT_FULL )
		{
			if ( ITEM_HasItem( iCaster, iItem ) != iItem)
			{
				// Выдаем предмет игроку
				ITEM_GiveItem( iCaster, iItem);

				if(bIsDropItems == 0)
				{
					format(szMessage, charsmax(szMessage), "^x01%L",LANG_PLAYER,"CLIENT_PRINT_ITEM_CREATED",szItemName);
					cssbChatColor(iCaster,"%s%s",fTagWar3ft(),szMessage);
				}
			}
			else
			{
				// Продаем предмет если уже есть такой предмет
				new iNewMoney = SHARED_GetUserMoney( iCaster ) + ITEM_Cost( iCaster, iItem );
				SHARED_SetUserMoney( iCaster, iNewMoney );

				new iItemMoney = ITEM_Cost( iCaster, iItem );

				new szShowMessageLoot[256];
				format(szShowMessageLoot, charsmax(szShowMessageLoot), "+$: %d",iItemMoney);
				fShowMessagePickUpItem(iCaster,szShowMessageLoot,205,92,92,enMoney);

				if(bIsDropItems == 0)
				{
					format(szMessage, charsmax(szMessage), "^x01%L",LANG_PLAYER,"CLIENT_PRINT_ITEM_CREATED",szItemName);
					cssbChatColor(iCaster,"%s%s",fTagWar3ft(),szMessage);
				}

				
			}
		}
		// Если у вас заняты все слоты
		else
		{
			// Продаем предмет если заняты все слоты
			new iNewMoney = SHARED_GetUserMoney( iCaster ) + ITEM_Cost( iCaster, iItem );
			SHARED_SetUserMoney( iCaster, iNewMoney );

			new iItemMoney = ITEM_Cost( iCaster, iItem );

			if(bIsDropItems == 0)
			{
				format(szMessage, charsmax(szMessage), "^x01%L",LANG_PLAYER,"CLIENT_PRINT_ITEM_CREATED",szItemName);
				cssbChatColor(iCaster,"%s%s",fTagWar3ft(),szMessage);
			}

			new szShowMessageLoot[256];
			format(szShowMessageLoot, charsmax(szShowMessageLoot), "+$: %d",iItemMoney);
			fShowMessagePickUpItem(iCaster,szShowMessageLoot,205,92,92,enMoney);
		}

		ITEM_RemoveID(iTarget,iItem);

	}
	// Если у противника не нашлось предметов
	else
	{
		// Формирование сообщения
		format(szMessage, charsmax(szMessage), "^x01%L",LANG_PLAYER,"CLIENT_PRINT_ITEM_NONE");
		cssbChatColor(iCaster,"%s%s",fTagWar3ft(),szMessage);
	}

	return PLUGIN_HANDLED;
}
