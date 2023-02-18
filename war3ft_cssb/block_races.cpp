/*------------------------------------
Файл блокировки рас на карте
------------------------------------*/
//Инициализация массивов файла настройки
public cfInitArraysBlockRacesFile()
{
	arrTrieBlockRacesMap = TravTrieCreate();
}

//Загрузка файла настройки
public cfLoadBlockRacesFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	cfInitArraysBlockRacesFile();

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_BLOCK_RACES_FILE);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load war3ft block items file %s!", szPath);
		set_fail_state(szError);
		return;
	}
	
	// Set up some vars to hold parsing info
	new szLineData[1024], szKey[64], szValue[255], iSection;
	
	// Open customization file for reading
	new fileBlockRaces_ini = fopen(szPath, "rt")
	
	while (fileBlockRaces_ini && !feof(fileBlockRaces_ini))
	{
		// Read one line at a time
		fgets(fileBlockRaces_ini, szLineData, charsmax(szLineData))
		
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
			case SECTION_BLOCK_RACES:
			{
				if (equal(szKey, "BLOCK_RACE_UNDEAD"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_UNDEAD", szValue);
				else if (equal(szKey, "BLOCK_RACE_HUMAN"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_HUMAN", szValue);
				else if (equal(szKey, "BLOCK_RACE_ORC"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_ORC", szValue);
				else if (equal(szKey, "BLOCK_RACE_ELF"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_ELF", szValue);
				else if (equal(szKey, "BLOCK_RACE_BLOOD"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_BLOOD", szValue);
				else if (equal(szKey, "BLOCK_RACE_SHADOW"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_SHADOW", szValue);
				else if (equal(szKey, "BLOCK_RACE_WARDEN"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_WARDEN", szValue);
				else if (equal(szKey, "BLOCK_RACE_CRYPT"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_CRYPT", szValue);
				else if (equal(szKey, "BLOCK_RACE_CHAMELEON"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_CHAMELEON", szValue);
				else if (equal(szKey, "BLOCK_RACE_FROST_MAGE"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_FROST_MAGE", szValue);
				else if (equal(szKey, "BLOCK_RACE_DEATH_KNIGHT"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_DEATH_KNIGHT", szValue);
				else if (equal(szKey, "BLOCK_RACE_BLACK_MAGICIAN"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_BLACK_MAGICIAN", szValue);
				else if (equal(szKey, "BLOCK_RACE_ALCHEMIST"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_ALCHEMIST", szValue);
				else if (equal(szKey, "BLOCK_RACE_PRIEST"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_PRIEST", szValue);
				else if (equal(szKey, "BLOCK_RACE_ROGUE"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_ROGUE", szValue);
				else if (equal(szKey, "BLOCK_RACE_DRUID"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_DRUID", szValue);
				else if (equal(szKey, "BLOCK_RACE_BLOODSEEKER"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_BLOODSEEKER", szValue);
				else if (equal(szKey, "BLOCK_RACE_JUGGERNAUT"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_JUGGERNAUT", szValue);
				else if (equal(szKey, "BLOCK_RACE_SNIPER"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_SNIPER", szValue);
				else if (equal(szKey, "BLOCK_RACE_DISRUPTOR"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_DISRUPTOR", szValue);
				else if (equal(szKey, "BLOCK_RACE_RAZOR"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_RAZOR", szValue);
				else if (equal(szKey, "BLOCK_RACE_WARLOCK"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_WARLOCK", szValue);
				else if (equal(szKey, "BLOCK_RACE_SHADOW_FIEND"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_SHADOW_FIEND", szValue);
				else if (equal(szKey, "BLOCK_RACE_24"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_24", szValue);
				else if (equal(szKey, "BLOCK_RACE_25"))
					TravTrieSetString(arrTrieBlockRacesMap,"BLOCK_RACE_25", szValue);
			}
				
		}//switch (iSection)
	}

	if (fileBlockRaces_ini) fclose(fileBlockRaces_ini)

}


bool:isDisabledRaceOnMap(idUser,iRaceId,szShortRaceName[])
{
	Lang_GetRaceName(iRaceId, idUser, szShortRaceName, 31, true );

	new szKey[64], szValue[255];

	new travTrieIter:trieIterator = GetTravTrieIterator(arrTrieBlockRacesMap);
	while(MoreTravTrie(trieIterator))
	{
		ReadTravTrieKey(trieIterator,szKey,charsmax(szKey));
		ReadTravTrieString(trieIterator,szValue,charsmax(szValue));
		//log_amx("Key: '%s' = '%s'",szKey,szValue);

		if ( (equal(szKey, "BLOCK_RACE_UNDEAD") && iRaceId == RACE_UNDEAD) ||
			 (equal(szKey, "BLOCK_RACE_HUMAN") && iRaceId == RACE_HUMAN) ||
			 (equal(szKey, "BLOCK_RACE_ORC") && iRaceId == RACE_ORC) ||
			 (equal(szKey, "BLOCK_RACE_ELF") && iRaceId == RACE_ELF) ||
			 (equal(szKey, "BLOCK_RACE_BLOOD") && iRaceId == RACE_BLOOD) ||
			 (equal(szKey, "BLOCK_RACE_SHADOW") && iRaceId == RACE_SHADOW) ||
			 (equal(szKey, "BLOCK_RACE_WARDEN") && iRaceId == RACE_WARDEN) ||
			 (equal(szKey, "BLOCK_RACE_CRYPT") && iRaceId == RACE_CRYPT) ||
			 (equal(szKey, "BLOCK_RACE_CHAMELEON") && iRaceId == RACE_CHAMELEON) ||
			 (equal(szKey, "BLOCK_RACE_FROST_MAGE") && iRaceId == RACE_FROST_MAGE) ||
			 (equal(szKey, "BLOCK_RACE_DEATH_KNIGHT") && iRaceId == RACE_DEATH_KNIGHT) ||
			 (equal(szKey, "BLOCK_RACE_BLACK_MAGICIAN") && iRaceId == RACE_BLACK_MAGICIAN) ||
			 (equal(szKey, "BLOCK_RACE_ALCHEMIST") && iRaceId == RACE_ALCHEMIST) ||
			 (equal(szKey, "BLOCK_RACE_PRIEST") && iRaceId == RACE_PRIEST) ||
			 (equal(szKey, "BLOCK_RACE_ROGUE") && iRaceId == RACE_ROGUE) ||
			 (equal(szKey, "BLOCK_RACE_DRUID") && iRaceId == RACE_DRUID) ||
			 (equal(szKey, "BLOCK_RACE_BLOODSEEKER") && iRaceId == RACE_BLOODSEEKER) ||
			 (equal(szKey, "BLOCK_RACE_JUGGERNAUT") && iRaceId == RACE_JUGGERNAUT) ||
			 (equal(szKey, "BLOCK_RACE_SNIPER") && iRaceId == RACE_SNIPER) ||
			 (equal(szKey, "BLOCK_RACE_DISRUPTOR") && iRaceId == RACE_DISRUPTOR) ||
			 (equal(szKey, "BLOCK_RACE_RAZOR") && iRaceId == RACE_RAZOR) ||
			 (equal(szKey, "BLOCK_RACE_WARLOCK") && iRaceId == RACE_WARLOCK) ||
			 (equal(szKey, "BLOCK_RACE_SHADOW_FIEND") && iRaceId == RACE_SHADOW_FIEND) ||
			 (equal(szKey, "BLOCK_RACE_24") && iRaceId == RACE_24) ||
			 (equal(szKey, "BLOCK_RACE_25") && iRaceId == RACE_25)
		   )
		{
			if(isMap(szValue) == true)
			{
				DestroyTravTrieIterator(trieIterator);
				return true;
			}
		}
 
	}//while

	DestroyTravTrieIterator(trieIterator);

	return false;
}