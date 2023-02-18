/*
*	Конфигурационный файл настроек опыта мода CSSB Warcraft 3 Frozen Throne Private
*/

//Инициализация массивов настройки файла skills_options.ini
public fInitArraysXPFile()
{
//*******************************************************
//  Настройка опыта
//*******************************************************
	arrXpSave = ArrayCreate(1, 1);					//[Cохраняемый опыт]
	arrXpKillSave = ArrayCreate(1, 1);				//[Опыт за убийство в режиме сохраняемого]
}

//Загрузка файла настройки
public cfLoadXPFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	fInitArraysXPFile();

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_CUSTOM_FILE_XP);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load XP options file %s!", szPath);
		set_fail_state(szError);
		return;
	}
	
	// Set up some vars to hold parsing info
	new szLineData[1024], szKey[64], szValue[255], iSection,szValueSkills[255],szValueLVL[255];
	
	// Open customization file for reading
	new fileWar3ftmod_ini = fopen(szPath, "rt")
	
	while (fileWar3ftmod_ini && !feof(fileWar3ftmod_ini))
	{
		// Read one line at a time
		fgets(fileWar3ftmod_ini, szLineData, charsmax(szLineData))
		
		// Replace newlines with a null character to prevent headaches
		replace(szLineData, charsmax(szLineData), "^n", "")
		
		// Blank line or comment
		if (!szLineData[0] || szLineData[0] == ';') 
			continue;
		
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
			case SECTION_XP_AWARDED:
			{
				if (equal(szKey, "DEFUSING_BOMB"))
					iDefusingBomb = str_to_num(szValue);
				else if (equal(szKey, "DEFUSED_BOMB"))
					iDefusedBomb = str_to_num(szValue);
				else if (equal(szKey, "PLANTING_BOMB"))
					iPlantingBomb = str_to_num(szValue);
				else if (equal(szKey, "PLANT_BOMB"))
					iPlantBomb = str_to_num(szValue);
				else if (equal(szKey, "SPAWN_BOMB"))
					iSpawnBomb = str_to_num(szValue);
				else if (equal(szKey, "BOMB_PICKUP"))
					iBombPickup = str_to_num(szValue);
				else if (equal(szKey, "TOUCH_HOSTAGE"))
					iTouchHostage = str_to_num(szValue);
				else if (equal(szKey, "RESCUE_HOSTAGE"))
					iRescueHostage = str_to_num(szValue);
				else if (equal(szKey, "KILL_HOSTAGE"))
					iKillHostage = str_to_num(szValue);
				else if (equal(szKey, "SPAWN_VIP"))
					iSpawnVip = str_to_num(szValue);
				else if (equal(szKey, "ESCAPE_VIP"))
					iEscapeVip = str_to_num(szValue);
				else if (equal(szKey, "KILL_HEADSHOT"))
					iKillHeadshot = str_to_num(szValue);
				else if (equal(szKey, "KILL_HOSTAGE_SAVER"))
					iKillHostageSaver = str_to_num(szValue);
				else if (equal(szKey, "KILL_DEFUSER"))
					iKillDefuser = str_to_num(szValue);
				else if (equal(szKey, "KILL_PLANTER"))
					iKillPlanter = str_to_num(szValue);
				else if (equal(szKey, "KILL_BOMB_CARRIER"))
					iKillBombCarrier = str_to_num(szValue);
				else if (equal(szKey, "KILL_VIP"))
					iKillVip = str_to_num(szValue);
				else if (equal(szKey, "WIN_ROUND"))
					iWinRound = str_to_num(szValue);
			}			
			case SECTION_XP_SAVE://[Cохраняемый опыт]
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "XP_SAVE_LVL"))
					ArrayPushCell(arrXpSave,str_to_num(szValue));								
			}			
			case SECTION_XP_KILL_SAVE://[Опыт за убийство в режиме сохраняемого]
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "XP_KILL_SAVE_LVL"))
					ArrayPushCell(arrXpKillSave,str_to_num(szValue));
			}
		
		}//switch (iSection)
	}

	if (fileWar3ftmod_ini) fclose(fileWar3ftmod_ini)

}
