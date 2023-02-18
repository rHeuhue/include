//*******************************************************
// Файл настройки времени супер навыков
//*******************************************************

//Загрузка файла настройки отката супер навыков
public cfLoadUltimateFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	arrIntUltimateTimer = ArrayCreate(1, 1);		//Массив времени супер навыков

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_ULTIMATE_RACES_FILE);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load war3ft ultimate times file %s!", szPath);
		set_fail_state(szError);
		return;
	}
	
	// Set up some vars to hold parsing info
	new szLineData[1024], szKey[64], szValue[255], iSection;
	
	// Open customization file for reading
	new fileWar3ftmod_ini = fopen(szPath, "rt")
	
	while (fileWar3ftmod_ini && !feof(fileWar3ftmod_ini))
	{
		// Read one line at a time
		fgets(fileWar3ftmod_ini, szLineData, charsmax(szLineData))
		
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
			case SECTION_ULTIMATE_RACES:
			{
	
				if (equal(szKey, "ULTIMATE_DELAY"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_UNDEAD"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_HUMAN"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_ORC"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_ELF"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_BLOOD"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_SHADOW"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_WARDEN"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_CRYPT"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_CHAMELEON"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_FROST_MAGE"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_DEATH_KNIGHT"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_BLACK_MAGICIAN"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_ALCHEMIST"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_PRIEST"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_ROGUE"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_DRUID"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_BLOODSEEKER"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_JUGGERNAUT"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_SNIPER"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_DISRUPTOR"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_RAZOR"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_WARLOCK"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_SHADOW_FIEND"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_24"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				else if (equal(szKey, "ULTIMATE_COOLDOWN_RACE_25"))
					ArrayPushCell(arrIntUltimateTimer, str_to_num(szValue));
				
			}
						
			
		}//switch (iSection)
	}

	if (fileWar3ftmod_ini) fclose(fileWar3ftmod_ini)

}




//Ускорение таймера если есть предмет ITEM_ULTIMATE_TIMER_DIVIDER
fResetUltimateTimerDivider(idUser, iDecrement = 0,iHideIcon = true )
{
//	if (!is_user_alive(idUser)) 
//		return;

	new iRaceID = arrIntData[idUser][P_RACE];

	new iTimeCoolDown;

	switch (iRaceID)
	{
		case RACE_UNDEAD..RACE_25:
		{
			iTimeCoolDown = ArrayGetCell(arrIntUltimateTimer,iRaceID);
		}

	}

	ULT_ResetCooldown(idUser,iTimeCoolDown + iDecrement,iHideIcon);

}

//Задание стартового счетчика для супер навыка
public fSetUltimateDelay(idUser)
{
//	if (!is_user_alive(idUser)) 
//		return;

	new iTimeUltDelay = ArrayGetCell(arrIntUltimateTimer,0);

	arrIntData[idUser][P_ULTIMATEDELAY] = iTimeUltDelay;

}

