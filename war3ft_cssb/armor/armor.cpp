// ******************************************************************
// Глобальные функции настройки брони
// ******************************************************************

//Сообщение которое выводит на экране 255 брони если это число превышено.
public msgArmor(idMessage,iDestMessage,iEntityMessage)
{		
	new iArmorNum = get_msg_arg_int(1);
		
	if(iArmorNum > 255)
	{
		set_msg_arg_int(1, ARG_SHORT, 255);
	
		if (is_user_alive(iEntityMessage))
		{
			new szMsgHealthArmor[256];
			formatex(szMsgHealthArmor, charsmax(szMsgHealthArmor), 
					 "%L: %d | %L: %d",LANG_PLAYER,"CURRENT_HEALTH",clHP:getUserHealth(iEntityMessage),
	 									   LANG_PLAYER,"WORD_ARMOR",iArmorNum);

			Create_StatusText(iEntityMessage, 0, szMsgHealthArmor);
		}
	}

	return PLUGIN_CONTINUE;
}


//Возвращает минимальное кол-во брони выставленное в параметрах
public clAr:getRaceMinArmor(const idUser)
{		
	new iRaceID = arrIntData[idUser][P_RACE];

	switch (iRaceID)
	{
		case RACE_UNDEAD..RACE_25:
			return ArrayGetCell(arrIntMinArmor,iRaceID);
					
	}

	return ArrayGetCell(arrIntMinArmor,0);
}

//Возвращает максимальное кол-во брони выставленное в параметрах
public clAr:getRaceMaxArmor(const idUser)
{		
	new iRaceID = arrIntData[idUser][P_RACE];

	switch (iRaceID)
	{
		case RACE_UNDEAD..RACE_25:
			return ArrayGetCell(arrIntMaxArmor,iRaceID);
					
	}

	return ArrayGetCell(arrIntMaxArmor,0);
}


//Задает броню игроку с учетом всех скилов и предметов, которые у героя имеются
public clAr:setCurRespawnRaceArmor(const idUser)
{		
	new iRaceID = arrIntData[idUser][P_RACE];

	if(iRaceID == RACE_NONE)
		return;

	new iMinArmor = clAr:getRaceMinArmor(idUser);
	new iMaxArmor = clAr:getRaceMaxArmor(idUser);

	new CsArmorType:tArmor;
	new iCurrentArmor = clAr:getUserArmor(idUser,tArmor);

	switch (iRaceID)
	{
		case RACE_UNDEAD:
			{
			}
		case RACE_HUMAN:
			{				
				
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
				
			}
		case RACE_CRYPT:	
			{
			}
		case RACE_CHAMELEON:	
			{				
				
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

	
	if(iCurrentArmor < iMinArmor)
	{
		clAr:setUserArmor(idUser,iMinArmor);
		return;
	}
	else
	{
		if(iCurrentArmor > iMaxArmor)
			clAr:setUserArmor(idUser,iMaxArmor);
		else
			clAr:setUserArmor(idUser,iCurrentArmor);
	}

}


//Функция возвращает количество здоровья игрока
public clAr:getUserArmor(const idUser, &CsArmorType:tArmor)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
		return 0;

	new iCurrentArmor = cs_get_user_armor(idUser, tArmor);
	
	return iCurrentArmor;
}

//Функция устанавливает количество здоровья игроку
public clAr:setUserArmor(const idUser,const iArmorNum)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
		return;

	if(iArmorNum <= 0)
	{
		cs_set_user_armor(idUser,0, CS_ARMOR_NONE);
		return;
	}

	new CsArmorType:tArmor;
	clAr:getUserArmor(idUser, tArmor);

	if(tArmor == CS_ARMOR_NONE)
		cs_set_user_armor(idUser,iArmorNum, CS_ARMOR_VESTHELM);
	else
		cs_set_user_armor(idUser,iArmorNum, tArmor);
		
	/*
	enum CsArmorType {
	CS_ARMOR_NONE = 0, // no armor
	CS_ARMOR_KEVLAR = 1, // armor
	CS_ARMOR_VESTHELM = 2 // armor and helmet
	};
	*/

	return;
}

public clAr:setUserArmorOnType(const idUser,const iArmorNum,const CsArmorType:tArmor)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
		return;

	if(iArmorNum <= 0)
	{
		cs_set_user_armor(idUser,0, CS_ARMOR_NONE);
		return;
	}

	cs_set_user_armor(idUser,iArmorNum, tArmor);
		
	return;
}

//Функция возвращает только количество брони игрока
public clAr:getArmorNum(const idUser)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
		return 0;
	
	new iArmorAmount = pev(idUser, pev_armorvalue);
	
	return iArmorAmount;
}


//Загрузка файла настройки
public  clAr:cfLoadArmorFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	arrIntMinArmor = ArrayCreate(1, 1);		//Массив минимального брони
	arrIntMaxArmor = ArrayCreate(1, 1);		//Массив максимального брони

	//Начальное брони для обычных игроков не имеющих расы
	ArrayPushCell(arrIntMinArmor, 100);
	ArrayPushCell(arrIntMaxArmor, 255);

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_ARMOR_FILE);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load war3ft armor file %s!", szPath);
		set_fail_state(szError);
		return;
	}
	
	// Set up some vars to hold parsing info
	new szLineData[1024], szKey[64], szValue[255], iSection;
	
	// Open customization file for reading
	new fileArmor_ini = fopen(szPath, "rt")
	
	while (fileArmor_ini && !feof(fileArmor_ini))
	{
		// Read one line at a time
		fgets(fileArmor_ini, szLineData, charsmax(szLineData))
		
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
			case SECTION_ARMOR_OPTIONS:
			{
				if (equal(szKey, "ARMOR_ITEM"))
					iArmorItemRace = str_to_num(szValue);
				else if (equal(szKey, "ARMOR_RACE_UNDEAD"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_HUMAN"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_ORC"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_ELF"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_BLOOD"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_SHADOW"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_WARDEN"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_CRYPT"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_CHAMELEON"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_FROST_MAGE"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_DEATH_KNIGHT"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_BLACK_MAGICIAN"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_ALCHEMIST"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_PRIEST"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_ROGUE"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_DRUID"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_BLOODSEEKER"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_JUGGERNAUT"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_SNIPER"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_DISRUPTOR"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_RAZOR"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_WARLOCK"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_SHADOW_FIEND"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_24"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}
				else if (equal(szKey, "ARMOR_RACE_25"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrArmorRace[iCount] = str_to_num(szKey);

						iCount++;
					}

					ArrayPushCell(arrIntMinArmor, arrArmorRace[0]);
					ArrayPushCell(arrIntMaxArmor, arrArmorRace[1]);
					
				}

			}
			
			
		}//switch (iSection)
	}

	if (fileArmor_ini) 
		fclose(fileArmor_ini)

}