/*------------------------------------
Файл блокировки предмета на карте
------------------------------------*/
//Инициализация массивов файла настройки
public cfInitArraysBlockItemsFile()
{
	arrTrieBlockItemsMap = TravTrieCreate();
}

//Загрузка файла настройки
public cfLoadBlockItemsFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	cfInitArraysBlockItemsFile();

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_BLOCK_ITEMS_FILE);
	
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
	new fileBlockItems_ini = fopen(szPath, "rt")
	
	while (fileBlockItems_ini && !feof(fileBlockItems_ini))
	{
		// Read one line at a time
		fgets(fileBlockItems_ini, szLineData, charsmax(szLineData))
		
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
			case SECTION_BLOCK_ITEMS:
			{
				if (equal(szKey, "BLOCK_ITEM_ANKH"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_ANKH", szValue);
				else if (equal(szKey, "BLOCK_ITEM_BOOTS"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_BOOTS", szValue);
				else if (equal(szKey, "BLOCK_ITEM_CLAWS"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_CLAWS", szValue);
				else if (equal(szKey, "BLOCK_ITEM_CLOAK"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_CLOAK", szValue);
				else if (equal(szKey, "BLOCK_ITEM_MASK"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_MASK", szValue);
				else if (equal(szKey, "BLOCK_ITEM_NECKLACE"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_NECKLACE", szValue);
				else if (equal(szKey, "BLOCK_ITEM_FROST"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_FROST", szValue);
				else if (equal(szKey, "BLOCK_ITEM_HEALTH"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_HEALTH", szValue);
				else if (equal(szKey, "BLOCK_ITEM_TOME"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_TOME", szValue);
				else if (equal(szKey, "BLOCK_ITEM_SCROLL"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_SCROLL", szValue);
				else if (equal(szKey, "BLOCK_ITEM_PROTECTANT"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_PROTECTANT", szValue);
				else if (equal(szKey, "BLOCK_ITEM_HELM"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_HELM", szValue);
				else if (equal(szKey, "BLOCK_ITEM_AMULET"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_AMULET", szValue);
				else if (equal(szKey, "BLOCK_ITEM_SOCK"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_SOCK", szValue);
				else if (equal(szKey, "BLOCK_ITEM_GLOVES"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_GLOVES", szValue);
				else if (equal(szKey, "BLOCK_ITEM_RING"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_RING", szValue);
				else if (equal(szKey, "BLOCK_ITEM_CHAMELEON"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_CHAMELEON", szValue);
				else if (equal(szKey, "BLOCK_ITEM_MOLE"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_MOLE", szValue);
				else if (equal(szKey, "BLOCK_ITEM_INTELLECT"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_INTELLECT", szValue);
				else if (equal(szKey, "BLOCK_ITEM_GRENADE_PROTECTION"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_GRENADE_PROTECTION", szValue);
				else if (equal(szKey, "BLOCK_ITEM_MIRROR_SHIELD"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_MIRROR_SHIELD", szValue);
				else if (equal(szKey, "BLOCK_ITEM_ESP"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_ESP", szValue);
				else if (equal(szKey, "BLOCK_ITEM_FROST_ARMOR"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_FROST_ARMOR", szValue);
				else if (equal(szKey, "BLOCK_ITEM_DEATH_TOUCH"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_DEATH_TOUCH", szValue);
				else if (equal(szKey, "BLOCK_ITEM_HEALTH_POTION"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_HEALTH_POTION", szValue);
				else if (equal(szKey, "BLOCK_ITEM_ULTIMATE_TIMER_DIVIDER"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_ULTIMATE_TIMER_DIVIDER", szValue);
				else if (equal(szKey, "BLOCK_ITEM_STEEL_SKIN"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_STEEL_SKIN", szValue);
				else if (equal(szKey, "BLOCK_ITEM_DEVOURER_LIGHT"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_DEVOURER_LIGHT", szValue);
				else if (equal(szKey, "BLOCK_ITEM_ICE_BLOCK"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_ICE_BLOCK", szValue);
				else if (equal(szKey, "BLOCK_ITEM_THIEF"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_THIEF", szValue);
				else if (equal(szKey, "BLOCK_ITEM_MIRROR_ULTIMATE"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_MIRROR_ULTIMATE", szValue);
				else if (equal(szKey, "BLOCK_ITEM_DEATHCOIL"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_DEATHCOIL", szValue);
				else if (equal(szKey, "BLOCK_ITEM_IMPALE"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_IMPALE", szValue);
				else if (equal(szKey, "BLOCK_ITEM_SLEEP"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_SLEEP", szValue);
				else if (equal(szKey, "BLOCK_ITEM_BOOK_DEAD"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_BOOK_DEAD", szValue);
				else if (equal(szKey, "BLOCK_ITEM_TRANQUILITY"))
					TravTrieSetString(arrTrieBlockItemsMap,"BLOCK_ITEM_TRANQUILITY", szValue);
			}
				
		}//switch (iSection)
	}

	if (fileBlockItems_ini) fclose(fileBlockItems_ini)

}


bool:isDisabledItemOnMap(idUser,iItem,szItemName[])
{
	LANG_GetItemName(iItem, idUser, szItemName, 31, true);

	new szKey[64], szValue[255];

	new travTrieIter:trieIterator = GetTravTrieIterator(arrTrieBlockItemsMap);
	while(MoreTravTrie(trieIterator))
	{
		ReadTravTrieKey(trieIterator,szKey,charsmax(szKey));
		ReadTravTrieString(trieIterator,szValue,charsmax(szValue));
		//log_amx("Key: '%s' = '%s'",szKey,szValue);

		if ( (equal(szKey, "BLOCK_ITEM_ANKH") && iItem == BLOCK_ITEM_ANKH) ||
			 (equal(szKey, "BLOCK_ITEM_BOOTS") && iItem == BLOCK_ITEM_BOOTS) ||
			 (equal(szKey, "BLOCK_ITEM_CLAWS") && iItem == BLOCK_ITEM_CLAWS) ||
			 (equal(szKey, "BLOCK_ITEM_CLOAK") && iItem == BLOCK_ITEM_CLOAK) ||
			 (equal(szKey, "BLOCK_ITEM_MASK") && iItem == BLOCK_ITEM_MASK) ||
			 (equal(szKey, "BLOCK_ITEM_NECKLACE") && iItem == BLOCK_ITEM_NECKLACE) ||
			 (equal(szKey, "BLOCK_ITEM_FROST") && iItem == BLOCK_ITEM_FROST) ||
			 (equal(szKey, "BLOCK_ITEM_HEALTH") && iItem == BLOCK_ITEM_HEALTH) ||
			 (equal(szKey, "BLOCK_ITEM_TOME") && iItem == BLOCK_ITEM_TOME) ||
			 (equal(szKey, "BLOCK_ITEM_SCROLL") && iItem == BLOCK_ITEM_SCROLL) ||
			 (equal(szKey, "BLOCK_ITEM_PROTECTANT") && iItem == BLOCK_ITEM_PROTECTANT) ||
			 (equal(szKey, "BLOCK_ITEM_HELM") && iItem == BLOCK_ITEM_HELM) ||
			 (equal(szKey, "BLOCK_ITEM_AMULET") && iItem == BLOCK_ITEM_AMULET) ||
			 (equal(szKey, "BLOCK_ITEM_SOCK") && iItem == BLOCK_ITEM_SOCK) ||
			 (equal(szKey, "BLOCK_ITEM_GLOVES") && iItem == BLOCK_ITEM_GLOVES) ||
			 (equal(szKey, "BLOCK_ITEM_RING") && iItem == BLOCK_ITEM_RING) ||
			 (equal(szKey, "BLOCK_ITEM_CHAMELEON") && iItem == BLOCK_ITEM_CHAMELEON) ||
			 (equal(szKey, "BLOCK_ITEM_MOLE") && iItem == BLOCK_ITEM_MOLE) ||
			 (equal(szKey, "BLOCK_ITEM_INTELLECT") && iItem == BLOCK_ITEM_INTELLECT) ||
			 (equal(szKey, "BLOCK_ITEM_GRENADE_PROTECTION") && iItem == BLOCK_ITEM_GRENADE_PROTECTION) ||
			 (equal(szKey, "BLOCK_ITEM_MIRROR_SHIELD") && iItem == BLOCK_ITEM_MIRROR_SHIELD) ||
			 (equal(szKey, "BLOCK_ITEM_ESP") && iItem == BLOCK_ITEM_ESP) ||
			 (equal(szKey, "BLOCK_ITEM_FROST_ARMOR") && iItem == BLOCK_ITEM_FROST_ARMOR) ||
			 (equal(szKey, "BLOCK_ITEM_DEATH_TOUCH") && iItem == BLOCK_ITEM_DEATH_TOUCH) ||
			 (equal(szKey, "BLOCK_ITEM_HEALTH_POTION") && iItem == BLOCK_ITEM_HEALTH_POTION) ||
			 (equal(szKey, "BLOCK_ITEM_ULTIMATE_TIMER_DIVIDER") && iItem == BLOCK_ITEM_ULTIMATE_TIMER_DIVIDER) ||
			 (equal(szKey, "BLOCK_ITEM_STEEL_SKIN") && iItem == BLOCK_ITEM_STEEL_SKIN) ||
			 (equal(szKey, "BLOCK_ITEM_DEVOURER_LIGHT") && iItem == BLOCK_ITEM_DEVOURER_LIGHT) ||
			 (equal(szKey, "BLOCK_ITEM_ICE_BLOCK") && iItem == BLOCK_ITEM_ICE_BLOCK) ||
			 (equal(szKey, "BLOCK_ITEM_THIEF") && iItem == BLOCK_ITEM_THIEF) ||
			 (equal(szKey, "BLOCK_ITEM_MIRROR_ULTIMATE") && iItem == BLOCK_ITEM_MIRROR_ULTIMATE) ||
			 (equal(szKey, "BLOCK_ITEM_DEATHCOIL") && iItem == BLOCK_ITEM_DEATHCOIL) ||
			 (equal(szKey, "BLOCK_ITEM_IMPALE") && iItem == BLOCK_ITEM_IMPALE) ||
			 (equal(szKey, "BLOCK_ITEM_SLEEP") && iItem == BLOCK_ITEM_SLEEP) ||
			 (equal(szKey, "BLOCK_ITEM_BOOK_DEAD") && iItem == BLOCK_ITEM_BOOK_DEAD) ||
			 (equal(szKey, "BLOCK_ITEM_TRANQUILITY") && iItem == BLOCK_ITEM_TRANQUILITY)
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


bool:isMap(szValue[255])
{
	new szMap[64];
	new szMapName[64];
	get_mapname(szMapName, charsmax(szMapName) );

	while (szValue[0] != 0 && strtok(szValue, szMap, charsmax(szMap), szValue, charsmax(szValue), ','))
	{
		trim(szMap);
		trim(szValue);
		
		new iLength;
		new szRestrictName[64];
		iLength = copyc(szRestrictName, charsmax(szRestrictName), szMap, '*' );

		if (equali(szMapName, szRestrictName, iLength ) )
			return true;
	}

	return false;
}