// ******************************************************************
// Глобальные функции настройки здоровья
// ******************************************************************

//Сообщение которое выводит на экране 255 здоровья если это число превышено
public msgHealth(idMessage,iDestMessage,iEntityMessage)
{		
	new iHealthNum = get_msg_arg_int(1);
		
	if(iHealthNum > 255)
	{
		set_msg_arg_int(1, ARG_BYTE, 255);
	
		if (is_user_alive(iEntityMessage))
		{
			new szMsgHealthArmor[256];
			formatex(szMsgHealthArmor, charsmax(szMsgHealthArmor), 
					 "%L: %d | %L: %d",LANG_PLAYER,"CURRENT_HEALTH",iHealthNum,
	 									   LANG_PLAYER,"WORD_ARMOR",clAr:getArmorNum(iEntityMessage));

			Create_StatusText(iEntityMessage, 0, szMsgHealthArmor );
		}
	}

	return PLUGIN_CONTINUE;
}

//Возвращает минимальное здоровье выставленное в параметрах
public clHP:getRaceMinHealth(const idUser)
{		
	new iRaceID = arrIntData[idUser][P_RACE];

	new iCurrentHealth = ArrayGetCell(arrIntMinHealth,0);

	switch (iRaceID)
	{
		case RACE_UNDEAD:
		{
			iCurrentHealth = ArrayGetCell(arrIntMinHealth,iRaceID);
		}
		case RACE_HUMAN:
		{	
			iCurrentHealth = ArrayGetCell(arrIntMinHealth,iRaceID);

			new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_DEVOTION);
			if (iSkillLevel > 0)
			{
				if(isDisabledSkillsOnMap(idUser,SKILL_DEVOTION) == false)
					iCurrentHealth += (iSkillLevel * iDevotionAura);
			}
		}
		case RACE_ORC..RACE_25:
		{
			iCurrentHealth = ArrayGetCell(arrIntMinHealth,iRaceID);
		}
					
	}
	
	if (ITEM_Has(idUser, ITEM_HEALTH) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_HEALTH )
		iCurrentHealth += get_pcvar_num(CVAR_wc3_health);

	return iCurrentHealth;
}

//Возвращает максимальное здоровье выставленное в параметрах
public clHP:getRaceMaxHealth(const idUser)
{		
	new iRaceID = arrIntData[idUser][P_RACE];

	new iCurrentHealth = ArrayGetCell(arrIntMaxHealth,0);

	switch (iRaceID)
	{
		case RACE_UNDEAD..RACE_25:
			iCurrentHealth = ArrayGetCell(arrIntMaxHealth,iRaceID);
					
	}
	
	if (ITEM_Has(idUser, ITEM_HEALTH) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_HEALTH )
		iCurrentHealth += get_pcvar_num(CVAR_wc3_health);

	return iCurrentHealth;
}


//Задает здоровье игроку с учетом всех скилов и предметов, которые у героя имеются
public clHP:setCurRespawnRaceHealth(const idUser)
{		
	new iRaceID = arrIntData[idUser][P_RACE];

	if(iRaceID == RACE_NONE)
		return;

	new iMinHealth = clHP:getRaceMinHealth(idUser);
	new iMaxHealth = clHP:getRaceMaxHealth(idUser);

	new iCurrentHealth = iMinHealth;

	new iSkillLevel;

	switch (iRaceID)
	{
		case RACE_UNDEAD:
			{
			}
		case RACE_HUMAN:
			{	/*			
				iSkillLevel = SM_GetSkillLevel(idUser, SKILL_DEVOTION);
				if (iSkillLevel > 0)
				{
					if(isDisabledSkillsOnMap(idUser,SKILL_DEVOTION) == false)
						iCurrentHealth += (iSkillLevel * iDevotionAura);
				}*/
			}
		case RACE_ORC:	
			{
			}
		case RACE_ELF:	
			{
			}
		case RACE_BLOOD:	
			{
			}
		case RACE_SHADOW:	
			{
			}
		case RACE_WARDEN:
			{
				if (arrIntData[idUser][P_RESPAWNBY] == RESPAWN_VENGEANCE)
					iCurrentHealth = iVengeanceHealth;
			}
		case RACE_CRYPT:	
			{
			}
		case RACE_CHAMELEON:	
			{
				iSkillLevel = SM_GetSkillLevel(idUser, SKILL_DEVOTION);
				if (iSkillLevel > 0)
				{
					if(isDisabledSkillsOnMap(idUser,SKILL_DEVOTION) == false)
						iCurrentHealth += (iSkillLevel * iDevotionAura);
				}

				// Vengeance Check
				if (arrIntData[idUser][P_RESPAWNBY] == RESPAWN_VENGEANCE)
					iCurrentHealth = iVengeanceHealth;
				
			}
		case RACE_FROST_MAGE:	
			{
			}
		case RACE_DEATH_KNIGHT:	
			{
			}
		case RACE_BLACK_MAGICIAN:
			{
			}
		case RACE_ALCHEMIST:	
			{
			}
		case RACE_PRIEST:	
			{
			}
		case RACE_ROGUE:	
			{
			}
		case RACE_DRUID:
			{
			}
		case RACE_BLOODSEEKER:	
			{
			}
		case RACE_JUGGERNAUT:	
			{
			}
		case RACE_SNIPER:		
			{
			}
		case RACE_DISRUPTOR:	
			{
			}
		case RACE_RAZOR:		
			{
			}
		case RACE_WARLOCK:		
			{
			}
		case RACE_SHADOW_FIEND:	
			{
			}
		case RACE_24:		
			{
			}
		case RACE_25:		
			{
			}

	}//switch


	//Предметы для всех
//	if (ITEM_Has(idUser, ITEM_HEALTH) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_HEALTH )
//		iCurrentHealth += get_pcvar_num(CVAR_wc3_health);
		
	if(iCurrentHealth > iMaxHealth)
		clHP:setUserHealth(idUser,iMaxHealth);
	else
		clHP:setUserHealth(idUser,iCurrentHealth);

}

//Функция возвращает количество здоровья игрока
public clHP:getUserHealth(const idUser)
{
	if (!arrBoolData[idUser][PB_ISCONNECTED] )
		return 0;

	new Float:fHealth;
	pev(idUser,pev_health,fHealth);

	return floatround(fHealth);
}

//Функция устанавливает количество здоровья игроку
public clHP:setUserHealth(const idUser,const iHealth)
{
	if (!arrBoolData[idUser][PB_ISCONNECTED])
		return;

	iHealth > 0 ? set_pev(idUser, pev_health, float(iHealth)) : dllfunc(DLLFunc_ClientKill, idUser);


	return;
}


//Загрузка файла настройки
public  clHP:cfLoadHealthFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	arrIntMinHealth = ArrayCreate(1, 1);		//Массив минимального здоровья
	arrIntMaxHealth = ArrayCreate(1, 1);		//Массив максимального здоровья

	//Начальное здоровье для обычных игроков не имеющих расы
	ArrayPushCell(arrIntMinHealth, 100);
	ArrayPushCell(arrIntMaxHealth, 255);

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_HEALTH_FILE);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load war3ft health file %s!", szPath);
		set_fail_state(szError);
		return;
	}
	
	// Set up some vars to hold parsing info
	new szLineData[1024], szKey[64], szValue[255], iSection;
	
	// Open customization file for reading
	new fileHealth_ini = fopen(szPath, "rt")
	
	while (fileHealth_ini && !feof(fileHealth_ini))
	{
		// Read one line at a time
		fgets(fileHealth_ini, szLineData, charsmax(szLineData))
		
		// Replace newlines with a null character to prevent headaches
		replace(szLineData, charsmax(szLineData), "^n", "")
		
		// Blank line or comment
		if (!szLineData[0] || szLineData[0] == ';') continue;
		
		// Начало новой секции
		if (szLineData[0] == '[')
		{
			iSection++
			continue;
		}
		
		// Разделение строки по символу "="
		strtok(szLineData, szKey, charsmax(szKey), szValue, charsmax(szValue), '=')
		
		// Удаление пробелов
		trim(szKey);
		trim(szValue);
		
		switch (iSection)
		{
			case SECTION_HEALTH_OPTIONS:
			{
				if (equal(szKey, "HEALTH_ITEM"))
					iHealthItemRace = str_to_num(szValue);
				else if (equal(szKey, "HEALTH_RACE_UNDEAD"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_HUMAN"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_ORC"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_ELF"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_BLOOD"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_SHADOW"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_WARDEN"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_CRYPT"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_CHAMELEON"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_FROST_MAGE"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_DEATH_KNIGHT"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_BLACK_MAGICIAN"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_ALCHEMIST"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_PRIEST"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_ROGUE"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_DRUID"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_BLOODSEEKER"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_JUGGERNAUT"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_SNIPER"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_DISRUPTOR"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_RAZOR"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_WARLOCK"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_SHADOW_FIEND"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_24"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}
				else if (equal(szKey, "HEALTH_RACE_25"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrHealthRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinHealth, arrHealthRace[0]);
					ArrayPushCell(arrIntMaxHealth, arrHealthRace[1]);
					
				}

			}
			
			
		}//switch (iSection)
	}

	if (fileHealth_ini) 
		fclose(fileHealth_ini)

}