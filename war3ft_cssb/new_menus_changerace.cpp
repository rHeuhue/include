

//-----------------Базовые функции------------------------------------BEGIN {
//Инициализация массивов файла настройки меню
public cfInitArraysMenuFile()
{
	arrIntBaseMenuData = ArrayCreate(1, 1);				//Массив главного меню

	arrIntBaseMenuDataSub_1 = ArrayCreate(1, 1);		//Массив подменю 1 "Гильдия Нежити"
	arrIntBaseMenuDataSub_2 = ArrayCreate(1, 1);		//Массив подменю 2 "Гильдия Магов"
	arrIntBaseMenuDataSub_3 = ArrayCreate(1, 1);		//Массив подменю 3 "Гильдия Альянса"
	arrIntBaseMenuDataSub_4 = ArrayCreate(1, 1);		//Массив подменю 4 "Гильдия Убийц"
	arrIntBaseMenuDataSub_5 = ArrayCreate(1, 1);		//Массив подменю 5 "Гильдия Света"
	arrIntBaseMenuDataSub_6 = ArrayCreate(1, 1);		//Массив подменю 6 "Гильдия Тьмы"
}

//Загрузка файла настройки
public cfLoadCMenuFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	cfInitArraysMenuFile();

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_MENU_FILE);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load war3ft menu file %s!", szPath);
		set_fail_state(szError);
		return;
	}
	
	// Set up some vars to hold parsing info
	new szLineData[1024], szKey[64], szValue[255], iSection;
		
	// Open customization file for reading
	new fileWar3ftmenu_ini = fopen(szPath, "rt")
	
	while (fileWar3ftmenu_ini && !feof(fileWar3ftmenu_ini))
	{
		// Read one line at a time
		fgets(fileWar3ftmenu_ini, szLineData, charsmax(szLineData))
		
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
		
		//log_amx( "szKey '%s'", szKey);

		switch (iSection)
		{
			case SECTION_BASE_MENU:
			{				
				cfInitValuesBaseMenu(szKey,arrIntBaseMenuData);
				cfInitValuesRacesMenu(szKey,arrIntBaseMenuData);					
			}			
			case SECTION_BASE_MENU_SUB_1:
			{
				cfInitValuesRacesMenu(szKey,arrIntBaseMenuDataSub_1);
			}
			case SECTION_BASE_MENU_SUB_2:
			{
				cfInitValuesRacesMenu(szKey,arrIntBaseMenuDataSub_2);
			}
			case SECTION_BASE_MENU_SUB_3:
			{
				cfInitValuesRacesMenu(szKey,arrIntBaseMenuDataSub_3);
			}
			case SECTION_BASE_MENU_SUB_4:
			{
				cfInitValuesRacesMenu(szKey,arrIntBaseMenuDataSub_4);
			}
			case SECTION_BASE_MENU_SUB_5:
			{
				cfInitValuesRacesMenu(szKey,arrIntBaseMenuDataSub_5);
			}
			case SECTION_BASE_MENU_SUB_6:
			{
				cfInitValuesRacesMenu(szKey,arrIntBaseMenuDataSub_6);
			}
			case SECTION_OPTIONS_MENU:
			{
				if (equal(szKey, "MENU_COLOR_NUMBER"))
					copy(szColorNumber, charsmax(szColorNumber), szValue);
				else if (equal(szKey, "MENU_COLOR_RACE"))
					copy(szColorRace, charsmax(szColorRace), szValue);
				else if (equal(szKey, "MENU_COLOR_XP_LEVEL"))
					copy(szColorXP_Level, charsmax(szColorXP_Level), szValue);
				else if (equal(szKey, "MENU_COLOR_WORD_XP_LEVEL"))
					copy(szColorWordXP_Level, charsmax(szColorWordXP_Level), szValue);
				else if (equal(szKey, "MENU_COLOR_VS"))
					copy(szColorVS, charsmax(szColorVS), szValue);
				else if (equal(szKey, "MENU_COLOR_VS_NUMBER"))
					copy(szColorVsNum, charsmax(szColorVsNum), szValue);
				else if (equal(szKey, "MENU_SHORT_NAME_RACE"))
					iShortNameRace = str_to_num(szValue);
			}
			
		}//switch (iSection)
	}

	if (fileWar3ftmenu_ini) fclose(fileWar3ftmenu_ini)

}
public cfInitValuesBaseMenu(const szKeyMenu[], &Array:arrIntKeyMenuData)
{	
	if (equal(szKeyMenu, "MENU_ID_RACE_1"))
		ArrayPushCell(arrIntKeyMenuData,MENU_ID_RACE_1);	//"Гильдия Нежити"
	else if (equal(szKeyMenu, "MENU_ID_RACE_2"))
		ArrayPushCell(arrIntKeyMenuData,MENU_ID_RACE_2);	//"Гильдия Магов"
	else if (equal(szKeyMenu, "MENU_ID_RACE_3"))
		ArrayPushCell(arrIntKeyMenuData,MENU_ID_RACE_3);	//"Гильдия Альянса"
	else if (equal(szKeyMenu, "MENU_ID_RACE_4"))
		ArrayPushCell(arrIntKeyMenuData,MENU_ID_RACE_4);	//"Гильдия Убийц"
	else if (equal(szKeyMenu, "MENU_ID_RACE_5"))
		ArrayPushCell(arrIntKeyMenuData,MENU_ID_RACE_5);	//"Гильдия Света"
	else if (equal(szKeyMenu, "MENU_ID_RACE_6"))
		ArrayPushCell(arrIntKeyMenuData,MENU_ID_RACE_6);	//"Гильдия Тьмы"
}

public cfInitValuesRacesMenu(const szKeyMenu[], &Array:arrIntKeyMenuData)
{
	if (equal(szKeyMenu, "RACE_UNDEAD"))
		ArrayPushCell(arrIntKeyMenuData,RACE_UNDEAD);
	else if (equal(szKeyMenu, "RACE_HUMAN"))
		ArrayPushCell(arrIntKeyMenuData,RACE_HUMAN);	
	else if (equal(szKeyMenu, "RACE_ORC"))
		ArrayPushCell(arrIntKeyMenuData,RACE_ORC);	
	else if (equal(szKeyMenu, "RACE_ELF"))
		ArrayPushCell(arrIntKeyMenuData,RACE_ELF);	
	else if (equal(szKeyMenu, "RACE_BLOOD"))
		ArrayPushCell(arrIntKeyMenuData,RACE_BLOOD);	
	else if (equal(szKeyMenu, "RACE_SHADOW"))
		ArrayPushCell(arrIntKeyMenuData,RACE_SHADOW);	
	else if (equal(szKeyMenu, "RACE_WARDEN"))
		ArrayPushCell(arrIntKeyMenuData,RACE_WARDEN);	
	else if (equal(szKeyMenu, "RACE_CRYPT"))
		ArrayPushCell(arrIntKeyMenuData,RACE_CRYPT);	
	else if (equal(szKeyMenu, "RACE_CHAMELEON"))
		ArrayPushCell(arrIntKeyMenuData,RACE_CHAMELEON);	
	else if (equal(szKeyMenu, "RACE_FROST_MAGE"))
		ArrayPushCell(arrIntKeyMenuData,RACE_FROST_MAGE);	
	else if (equal(szKeyMenu, "RACE_DEATH_KNIGHT"))
		ArrayPushCell(arrIntKeyMenuData,RACE_DEATH_KNIGHT);	
	else if (equal(szKeyMenu, "RACE_BLACK_MAGICIAN"))
		ArrayPushCell(arrIntKeyMenuData,RACE_BLACK_MAGICIAN);	
	else if (equal(szKeyMenu, "RACE_ALCHEMIST"))
		ArrayPushCell(arrIntKeyMenuData,RACE_ALCHEMIST);	
	else if (equal(szKeyMenu, "RACE_PRIEST"))
		ArrayPushCell(arrIntKeyMenuData,RACE_PRIEST);	
	else if (equal(szKeyMenu, "RACE_ROGUE"))
		ArrayPushCell(arrIntKeyMenuData,RACE_ROGUE);	
	else if (equal(szKeyMenu, "RACE_DRUID"))
		ArrayPushCell(arrIntKeyMenuData,RACE_DRUID);	
	else if (equal(szKeyMenu, "RACE_BLOODSEEKER"))
		ArrayPushCell(arrIntKeyMenuData,RACE_BLOODSEEKER);	
	else if (equal(szKeyMenu, "RACE_JUGGERNAUT"))
		ArrayPushCell(arrIntKeyMenuData,RACE_JUGGERNAUT);	
	else if (equal(szKeyMenu, "RACE_SNIPER"))
		ArrayPushCell(arrIntKeyMenuData,RACE_SNIPER);	
	else if (equal(szKeyMenu, "RACE_DISRUPTOR"))
		ArrayPushCell(arrIntKeyMenuData,RACE_DISRUPTOR);	
	else if (equal(szKeyMenu, "RACE_RAZOR"))
		ArrayPushCell(arrIntKeyMenuData,RACE_RAZOR);	
	else if (equal(szKeyMenu, "RACE_WARLOCK"))
		ArrayPushCell(arrIntKeyMenuData,RACE_WARLOCK);	
	else if (equal(szKeyMenu, "RACE_SHADOW_FIEND"))
		ArrayPushCell(arrIntKeyMenuData,RACE_SHADOW_FIEND);	
	else if (equal(szKeyMenu, "RACE_24"))
		ArrayPushCell(arrIntKeyMenuData,RACE_24);	
	else if (equal(szKeyMenu, "RACE_25"))
		ArrayPushCell(arrIntKeyMenuData,RACE_25);

}
//Проверка на содержание в массиве ключа расы. Нужно для добавления слов Уровени и Опыт в главное меню
bool:isContentRaceArrayBaseMenu(Array:arrIntKeyMenuData)
{
	new bool:bIsContentRace = false;

	for(new i = 0; i < ArraySize(arrIntKeyMenuData); i++)
	{
		new iValueRace = ArrayGetCell(arrIntKeyMenuData,i);

		if (iValueRace == RACE_UNDEAD)
			return true;
		else if (iValueRace == RACE_HUMAN)
			return true;	
		else if (iValueRace == RACE_ORC)
			return true;
		else if (iValueRace == RACE_ELF)
			return true;
		else if (iValueRace == RACE_BLOOD)
			return true;	
		else if (iValueRace == RACE_SHADOW)
			return true;	
		else if (iValueRace == RACE_WARDEN)
			return true;	
		else if (iValueRace == RACE_CRYPT)
			return true;	
		else if (iValueRace == RACE_CHAMELEON)
			return true;	
		else if (iValueRace == RACE_FROST_MAGE)
			return true;
		else if (iValueRace == RACE_DEATH_KNIGHT)
			return true;
		else if (iValueRace == RACE_BLACK_MAGICIAN)
			return true;	
		else if (iValueRace == RACE_ALCHEMIST)
			return true;	
		else if (iValueRace == RACE_PRIEST)
			return true;	
		else if (iValueRace == RACE_ROGUE)
			return true;	
		else if (iValueRace == RACE_DRUID)
			return true;	
		else if (iValueRace == RACE_BLOODSEEKER)
			return true;
		else if (iValueRace == RACE_JUGGERNAUT)
			return true;
		else if (iValueRace == RACE_SNIPER)
			return true;	
		else if (iValueRace == RACE_DISRUPTOR)
			return true;	
		else if (iValueRace == RACE_RAZOR)
			return true;	
		else if (iValueRace == RACE_WARLOCK)
			return true;	
		else if (iValueRace == RACE_SHADOW_FIEND)
			return true;
		else if (iValueRace == RACE_24)
			return true;	
		else if (iValueRace == RACE_25)
			return true;
	}
	

	return bIsContentRace;
}

//Регистрация всех меню для поддержки мультиязычности
public InitLangAllMenus()
{
	new iTotalLanguages = get_langsnum();
	new lang[3], menu[256];
	new curMenuId = -1, highestMenuId = -1;
	new iLang, iMenu;

	// Loop through every menu
	for ( iMenu = 0; iMenu < MAX_NUM_MENUS; iMenu++ )
	{
		// Register the menu names for each language
		for ( iLang = 0; iLang < iTotalLanguages; iLang++ )
		{
			get_lang ( iLang, lang );

			if ( lang_exists( lang ) )
			{
				formatex ( menu, 255, "%L", lang, MENU_TITLES[iMenu] );
				curMenuId = register_menuid ( menu );
				
				if ( curMenuId > highestMenuId )
				{
					register_menucmd ( curMenuId, 1023, MENU_CALLBACK_ALL[iMenu] );
					highestMenuId = curMenuId;
				}
			}
		}// End language loop
	}// End menu loop
}

//Вызов отображения менюшек
public fDisplay_Menu_ChangeRace( idUser, iRaceXP[MAX_RACES],iRaceLevel[MAX_RACES],iSelectIdMenu)
{
	arrRaceXP = iRaceXP;
	
	switch (iSelectIdMenu)
	{
		case MENU_ID_DEFAULT:
		{
			fBuildMenu(idUser,"MENU_SELECT_RACE",iRaceXP,iRaceLevel,arrIntBaseMenuData,MENU_ID_DEFAULT);
		}
		case MENU_ID_RACE_1:
		{
			fBuildMenu(idUser,"MENU_ID_RACE_1",iRaceXP,iRaceLevel,arrIntBaseMenuDataSub_1,MENU_ID_RACE_1);
		}
		case MENU_ID_RACE_2:
		{
			fBuildMenu(idUser,"MENU_ID_RACE_2",iRaceXP,iRaceLevel,arrIntBaseMenuDataSub_2,MENU_ID_RACE_2);
		}
		case MENU_ID_RACE_3:
		{
			fBuildMenu(idUser,"MENU_ID_RACE_3",iRaceXP,iRaceLevel,arrIntBaseMenuDataSub_3,MENU_ID_RACE_3);
		}
		case MENU_ID_RACE_4:
		{
			fBuildMenu(idUser,"MENU_ID_RACE_4",iRaceXP,iRaceLevel,arrIntBaseMenuDataSub_4,MENU_ID_RACE_4);
		}
		case MENU_ID_RACE_5:
		{
			fBuildMenu(idUser,"MENU_ID_RACE_5",iRaceXP,iRaceLevel,arrIntBaseMenuDataSub_5,MENU_ID_RACE_5);
		}
		case MENU_ID_RACE_6:
		{
			fBuildMenu(idUser,"MENU_ID_RACE_6",iRaceXP,iRaceLevel,arrIntBaseMenuDataSub_6,MENU_ID_RACE_6);
		}
		
	}
	return PLUGIN_CONTINUE;
}

//Общая функция формирования менюшек
public fBuildMenu(idUser,szKeyLangMenu[],iRaceXP[MAX_RACES],iRaceLevel[MAX_RACES],const Array:arrListItemId,iMenuID)
{
	new iMaxItemList = ArraySize(arrListItemId);

	new iPos = 0;
	new szMenuData[512],szXP[16],szLevel[16];
	
	//Поиск максимальной длины строки опыта
	new iLengthMax = 0;
	for(new i = 1; i <= MAX_RACES; i++)
	{
		num_to_str(iRaceLevel[i-1], szLevel, 15 );
		new iLength = strlen(szLevel);

		if(iLengthMax < iLength)
			iLengthMax = iLength;
	}

	//client_print(idUser,print_chat,"iLengthMax: %d",iLengthMax);

	new idKeysMenu = (1<<9);
	
	new szRaceName[MAX_RACES+1][64];//Хранение названий рас

	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "\r%L",LANG_PLAYER,szKeyLangMenu);

	//Отобразить слово Опыт и Уровень в заглавии
	switch (iMenuID)
	{
		case MENU_ID_DEFAULT:
		{			
			if(isContentRaceArrayBaseMenu(arrIntBaseMenuData) == true)
				iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s\R%L   %L^n^n",szColorWordXP_Level,LANG_PLAYER, "MENU_WORD_EXPERIENCE",LANG_PLAYER,"WORD_LEVEL" );
		}
		case MENU_ID_RACE_1,MENU_ID_RACE_2,MENU_ID_RACE_3,MENU_ID_RACE_4,MENU_ID_RACE_5,MENU_ID_RACE_6:
		{
			iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s\R%L   %L^n^n",szColorWordXP_Level,LANG_PLAYER, "MENU_WORD_EXPERIENCE",LANG_PLAYER,"WORD_LEVEL" );
			
		}
	}


	//Cчетчик рас в команде
	new arrRaceTeam[3][MAX_RACES+1];
	fGetNumRacePlayers(idUser,arrRaceTeam);

	//Цикл по количеству пунктов в меню
	for(new iKeyItemList = 0; iKeyItemList < iMaxItemList; iKeyItemList++)
	{
		//new iMenuID = arrListItemId[iKeyItemList];
		new iMenuID = ArrayGetCell(arrListItemId,iKeyItemList);
		
		new szNumSpace[64];

		if(iMenuID <= MAX_RACES && iMenuID != 0)
		{
			//Считывание названия расы
			if(iShortNameRace > 0)
				Lang_GetRaceName(iMenuID, idUser, szRaceName[iMenuID],63,true);
			else
				Lang_GetRaceName(iMenuID, idUser, szRaceName[iMenuID],63);

			//Префикс
			new szPrefix[64];
			formatex(szPrefix, charsmax(szPrefix), "%L",LANG_PLAYER,"VIP_PREFIX");

			new iVipValue = ArrayGetCell(arrIntVipRace,iMenuID-1);
			if(iVipValue > 0)
				strcat(szRaceName[iMenuID],szPrefix, charsmax(szPrefix) );

			//Добавление счетчиков рас в команде
			if(get_pcvar_num(CVAR_wc3_show_menu_race_team) > 0)
			{
				new szNumRace[64];
				formatex(szNumRace, charsmax(szNumRace), "%s   (%s%d %svs %s%d%s)",
					szColorVS,szColorVsNum,arrRaceTeam[TEAM_T][iMenuID],
					szColorVS,szColorVsNum,arrRaceTeam[TEAM_CT][iMenuID],szColorVS);

				strcat(szRaceName[iMenuID],szNumRace, charsmax(szNumRace) );
			}

			//Перевод целого значения XP в строку
			num_to_str(iRaceXP[iMenuID-1], szXP, 15 );
			//Перевод целого значения Уровня в строку
			num_to_str(iRaceLevel[iMenuID-1], szLevel, 15 );

			//Разница в количестве символов
			new iNumSpace = (iLengthMax - strlen(szLevel))*2 + 15;
			
			new szSpace[8];
			formatex(szSpace,charsmax(szSpace), " ");
			
			for(new i = 0; i < iNumSpace; i++)
				strcat(szNumSpace,szSpace, charsmax(szNumSpace) );
			
		}
		
		switch (iMenuID)
		{
			case RACE_UNDEAD,RACE_HUMAN,RACE_ORC,RACE_ELF,RACE_BLOOD,
				 RACE_SHADOW,RACE_WARDEN,RACE_CRYPT,RACE_FROST_MAGE,
				 RACE_DEATH_KNIGHT,RACE_CHAMELEON,
				 RACE_BLACK_MAGICIAN,RACE_ALCHEMIST,RACE_PRIEST,RACE_ROGUE,
				 RACE_DRUID,
				 RACE_BLOODSEEKER,RACE_JUGGERNAUT,RACE_SNIPER,RACE_DISRUPTOR,RACE_RAZOR,RACE_WARLOCK,RACE_SHADOW_FIEND,RACE_24,RACE_25:
			{
				iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos,"%s%d.%s%s\R%s%s%s%s^n",
					            szColorNumber,iKeyItemList + 1,szColorRace,szRaceName[iMenuID],szColorXP_Level,
								szXP,
								szNumSpace,
								szLevel);

				idKeysMenu |= (1<<iKeyItemList)
			}
			case MENU_ID_RACE_1:
			{
				iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s%d. %s%L^n",
					             szColorNumber,iKeyItemList + 1,szColorRace,LANG_PLAYER, "MENU_ID_RACE_1" );
				idKeysMenu |= (1<<iKeyItemList)
			}
			case MENU_ID_RACE_2:
			{
				iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s%d. %s%L^n",
					             szColorNumber,iKeyItemList + 1,szColorRace,LANG_PLAYER, "MENU_ID_RACE_2" );
				idKeysMenu |= (1<<iKeyItemList)
			}
			case MENU_ID_RACE_3:
			{
				iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s%d. %s%L^n",
					             szColorNumber,iKeyItemList + 1,szColorRace,LANG_PLAYER, "MENU_ID_RACE_3" );
				idKeysMenu |= (1<<iKeyItemList)
			}
			case MENU_ID_RACE_4:
			{
				iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s%d. %s%L^n",
					             szColorNumber,iKeyItemList + 1,szColorRace,LANG_PLAYER, "MENU_ID_RACE_4" );
				idKeysMenu |= (1<<iKeyItemList)
			}
			case MENU_ID_RACE_5:
			{
				//Отобразить название после нужного заголовка \rВыбор героя Dota:^n
				iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "\r%L",LANG_PLAYER,"MENU_SELECT_RACE_DOTA");		

				iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s%d. %s%L^n",
					             szColorNumber,iKeyItemList + 1,szColorRace,LANG_PLAYER, "MENU_ID_RACE_5" );
				idKeysMenu |= (1<<iKeyItemList)
			}
			case MENU_ID_RACE_6:
			{
				iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s%d. %s%L^n",
					             szColorNumber,iKeyItemList + 1,szColorRace,LANG_PLAYER, "MENU_ID_RACE_6" );
				idKeysMenu |= (1<<iKeyItemList)
			}
			
		}//switch

	}//for


	//Добавление кнопки Назад в подменюшки
	switch(iMenuID)
	{
		case MENU_ID_RACE_1,MENU_ID_RACE_2,MENU_ID_RACE_3,MENU_ID_RACE_4,MENU_ID_RACE_5,MENU_ID_RACE_6:
		{
			iPos += formatex(szMenuData[iPos], charsmax(szMenuData)-iPos, "^n^n\w9. %L",LANG_PLAYER,"BACK_STRING")
			idKeysMenu |= (1<<8)
		}
	}

	//Пункт Выход
	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "^n\d0. %L",LANG_PLAYER,"WORD_EXIT");

	new szMenuName[128];
	format(szMenuName, charsmax(szMenuName), "%L",LANG_PLAYER,szKeyLangMenu);
	show_menu(idUser,idKeysMenu,szMenuData,-1,szMenuName);
	
	return PLUGIN_CONTINUE;
}

//Выбор рас
public fSelectRace(idUser,iRace)
{
	//Заблокирована ли раса на карте
	new szShortRaceName[32];
	if(isDisabledRaceOnMap(idUser,iRace,szShortRaceName) == true)
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_RACE_DISABLED_ON_MAP",szShortRaceName);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		WC3_ChangeRaceStart(idUser);

		return;
	}

	//Ограничение количества выбранных рас за одну команду
	if(iNumRaceOnOff > 0)
	{
		new bRaceUsed[MAX_RACES+1] = {0}, iRaceID, iTargetID;

		new iTeamCurrentUser;
		iTeamCurrentUser = get_user_team(idUser);

		new arrPlayers[32], iNumPlayers;

		if(iTeamCurrentUser == TEAM_T)
			get_players(arrPlayers, iNumPlayers, "e","TERRORIST");
		if(iTeamCurrentUser == TEAM_CT)
			get_players(arrPlayers, iNumPlayers, "e","CT");

		for (new i = 0; i < iNumPlayers; i++ )
		{
			iTargetID = arrPlayers[i];

			if(idUser == iTargetID)
				continue;

			iRaceID	= arrIntData[iTargetID][P_RACE];

			if(iRace == iRaceID)
			{
				bRaceUsed[iRaceID-1]++;

				//cssbChatColor(idUser,"%s %d -- %d",fTagWar3ft(),iRace,iRaceID);
			}
		}

		for(new i = 0; i < ArraySize(arrIntBlockNumRace); i++)
		{
			new iBlockNumRace = ArrayGetCell(arrIntBlockNumRace,i);

			//cssbChatColor(idUser,"%d ++++ %d --- %d",iBlockNumRace,bRaceUsed[i],i);

			new szRaceName[64];
			Lang_GetRaceName(iRace, idUser, szRaceName, 63 );

			if(bRaceUsed[i] == 0)
				continue;

			if(bRaceUsed[i] >= iBlockNumRace && iBlockNumRace != 0)
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_RACE_BLOCK_NUM",szRaceName,iBlockNumRace);
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			
				WC3_ChangeRaceStart(idUser);

				return; 
			}
		}
	}


	//Выбор или изменение расы
	// User currently has a race
	if (arrIntData[idUser][P_RACE] != 0 )
	{
		DB_SaveXP(idUser,true);

		// Change the user's race at the start of next round
		if ( iRace != arrIntData[idUser][P_RACE] )
		{
			
			// Special message for csdm
			if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 )
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MENU_CHANGE_RACE");
				client_print( idUser, print_center,szMessage);
				
			}	
			else
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CENTER_CHANGED_NEXT");
				client_print( idUser, print_center,szMessage);				
			}

			arrIntData[idUser][P_CHANGERACE] = iRace;

			arrBoolData[idUser][PB_CHANGE_RESET_RACE] = true;
		}

		// Do nothing
		else
		{
			arrIntData[idUser][P_CHANGERACE] = 0;
		}
	}

	// User doesn't have a race so give it to him!!!
	else
	{
		WC3_SetRace(idUser,iRace);

		if(bIsUserRace(idUser,RACE_SNIPER) && iRoundCount > iRoundCountAwp)
			clSniper::skillElephantGun(idUser);

		//Установка здоровья и брони героям
		clHP:setCurRespawnRaceHealth(idUser);
		clAr:setCurRespawnRaceArmor(idUser);

		clVIP:fInitItemsAccessVip(idUser);

		ExecuteForward(mfSelectRace, mfSelectRaceReturn, idUser, iRace);
	}
}


//Определяет какой пункт выбран раса или меню (дает расу или открывает другое меню)
public fSelectKeyMenu(idUser,iMenuID)
{
	switch (iMenuID)
	{
		case RACE_UNDEAD,RACE_HUMAN,RACE_ORC,
			RACE_ELF,RACE_BLOOD,RACE_SHADOW,
			RACE_WARDEN,RACE_CRYPT,RACE_CHAMELEON,
			RACE_FROST_MAGE,RACE_DEATH_KNIGHT,RACE_BLACK_MAGICIAN,RACE_ALCHEMIST,
			RACE_PRIEST,RACE_ROGUE,RACE_DRUID,
			RACE_BLOODSEEKER,RACE_JUGGERNAUT,RACE_SNIPER,RACE_DISRUPTOR,RACE_RAZOR,RACE_WARLOCK,RACE_SHADOW_FIEND,RACE_24,RACE_25:
		{
			if(isPlayerSelectRaceVIP(idUser,iMenuID) == false)
				fSelectRace(idUser,iMenuID);
		}
		case MENU_ID_RACE_1:
		{
			DB_GetAllXP( idUser,MENU_ID_RACE_1);
		}
		case MENU_ID_RACE_2:
		{
			DB_GetAllXP( idUser,MENU_ID_RACE_2);
		}
		case MENU_ID_RACE_3:
		{
			DB_GetAllXP( idUser,MENU_ID_RACE_3);
		}
		case MENU_ID_RACE_4:
		{
			DB_GetAllXP( idUser,MENU_ID_RACE_4);
		}
		case MENU_ID_RACE_5:
		{
			DB_GetAllXP(idUser,MENU_ID_RACE_5);
		}
		case MENU_ID_RACE_6:
		{
			DB_GetAllXP(idUser,MENU_ID_RACE_6);
		}		

	}//switch
	
}

//Проверка является игрок VIP или нет
bool:isPlayerSelectRaceVIP(idUser,iRaceVip)
{
	new szRaceName[64];
	Lang_GetRaceName(iRaceVip, idUser, szRaceName, 63 );
	new szMotdPath[255];

	//Определение [Vip Race]
	new szFlagVip[255];
	for(new i = 0; i < ArraySize(arrIntVipRace); i++)
	{
		new iRaceCurrent = (i + 1);
		new iVipValue = ArrayGetCell(arrIntVipRace,i);
		ArrayGetString(arrStrFlagVipRace,i, szFlagVip, charsmax(szFlagVip));

		if(!(get_user_flags(idUser) & fVipRace(szFlagVip)) && iRaceCurrent == iRaceVip && iVipValue != 0)
		{
			if(iMotdRaceOnOff > 0 )
			{
				ArrayGetString(arrStrMotdPathRace,i, szMotdPath, charsmax(szMotdPath));
				show_motd(idUser,szMotdPath, szRaceName);
			}

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_RACE_BLOCK",szRaceName);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
					
			WC3_ChangeRaceStart(idUser);

			return true;
		}
	}


	//Определение [Vip Race]  - Проверяется один раз когда игрок зашел на сервер.
	new szFlagLevelVip[255];
	for(new i = 0; i < ArraySize(arrIntLevelVipRace); i++)
	{
		new iRaceCurrent = (i + 1);
		new iBlockLevel = ArrayGetCell(arrIntLevelVipRace,i);
		ArrayGetString(arrStrFlagLevelVipRace,i, szFlagLevelVip, charsmax(szFlagLevelVip));
	
		//Если нет доступа и игрок прокачал расу больше определяемого уровня для расы
		if(!(get_user_flags(idUser) & fVipRace(szFlagLevelVip)) && 
			(XP_GetLevelByXP(arrRaceXP[iRaceVip-1])  >= iBlockLevel) && 
			(iRaceCurrent == iRaceVip && iBlockLevel > 0)
		   )
		{
			if(iMotdRaceOnOff > 0 )
			{
				ArrayGetString(arrStrMotdPathRace,i, szMotdPath, charsmax(szMotdPath));
				show_motd(idUser,szMotdPath, szRaceName);
			}

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_RACE_BLOCK_LEVEL",szRaceName,iBlockLevel);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
					
			WC3_ChangeRaceStart(idUser);

			return true;
		}
	}

	//Определение [Vip Race]  - Проверяеются текущие уровень и опыт которые игрок набил во время игры 
	for(new i = 0; i < ArraySize(arrIntLevelVipRace); i++)
	{
		new iRaceCurrent = (i + 1);
		new iBlockLevel = ArrayGetCell(arrIntLevelVipRace,i);
		ArrayGetString(arrStrFlagLevelVipRace,i, szFlagLevelVip, charsmax(szFlagLevelVip));
	
		//Если нет доступа и игрок прокачал расу больше определяемого уровня для расы
		if(!(get_user_flags(idUser) & fVipRace(szFlagLevelVip)) && 
			(arrIntData[idUser][P_LEVEL]  >= iBlockLevel) && 
			(iRaceCurrent == iRaceVip && iBlockLevel > 0)
		   )
		{
			if(iMotdRaceOnOff > 0 )
			{
				ArrayGetString(arrStrMotdPathRace,i, szMotdPath, charsmax(szMotdPath));
				show_motd(idUser,szMotdPath, szRaceName);
			}

			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_RACE_BLOCK_LEVEL",szRaceName,iBlockLevel);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
					
			WC3_ChangeRaceStart(idUser);

			return true;
		}
	}

	return false;
}

//=============================================================================
//=============================================================================
//=============================================================================
//-----------------Базовые функции-----------------------------------------------END }


//-----------------Функции выбора пунктов меню-----------------------BEGIN {
//Функция выбора пунктов в меню выбора рас		
public _Callback_MENU_SelectRace(idUser,iKey)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

	if(iKey == 9) //Выход
		return PLUGIN_HANDLED;
	
	new iSelectRaceId = ArrayGetCell(arrIntBaseMenuData,iKey);
	fSelectKeyMenu(idUser,iSelectRaceId);

	return PLUGIN_HANDLED;
}

//Функция выбора пунктов в под меню "Гильдия Нежити"
public _Callback_SUB_MENU_ID_1(idUser,iKey)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

//	client_print(idUser,print_chat,"iKey: %d",iKey);

	if(iKey == 8) //Назад
	{
		DB_GetAllXP(idUser,MENU_ID_DEFAULT);
		return PLUGIN_HANDLED;
	}

	if(iKey == 9) //Выход
		return PLUGIN_HANDLED;

	new iSelectRaceId = ArrayGetCell(arrIntBaseMenuDataSub_1,iKey);
	fSelectKeyMenu(idUser,iSelectRaceId);

	return PLUGIN_HANDLED;
}

//Функция выбора пунктов в под меню "Гильдия Магов"
public _Callback_SUB_MENU_ID_2(idUser,iKey)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

//	client_print(idUser,print_chat,"iKey: %d",iKey);

	if(iKey == 8) //Назад
	{
		DB_GetAllXP( idUser,MENU_ID_DEFAULT);
		return PLUGIN_HANDLED;
	}

	if(iKey == 9) //Выход
		return PLUGIN_HANDLED;

	new iSelectRaceId = ArrayGetCell(arrIntBaseMenuDataSub_2,iKey);
	fSelectKeyMenu(idUser,iSelectRaceId);

	return PLUGIN_HANDLED;
}

//Функция выбора пунктов в под меню "Гильдия Альянса"
public _Callback_SUB_MENU_ID_3(idUser,iKey)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

//	client_print(idUser,print_chat,"iKey: %d",iKey);

	if(iKey == 8) //Назад
	{
		DB_GetAllXP( idUser,MENU_ID_DEFAULT);
		return PLUGIN_HANDLED;
	}

	if(iKey == 9) //Выход
		return PLUGIN_HANDLED;

	new iSelectRaceId = ArrayGetCell(arrIntBaseMenuDataSub_3,iKey);
	fSelectKeyMenu(idUser,iSelectRaceId);

	return PLUGIN_HANDLED;
}

//Функция выбора пунктов в под меню "Гильдия Убийц"
public _Callback_SUB_MENU_ID_4(idUser,iKey)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

//	client_print(idUser,print_chat,"iKey: %d",iKey);

	if(iKey == 8) //Назад
	{
		DB_GetAllXP( idUser,MENU_ID_DEFAULT);
		return PLUGIN_HANDLED;
	}

	if(iKey == 9) //Выход
		return PLUGIN_HANDLED;

	new iSelectRaceId = ArrayGetCell(arrIntBaseMenuDataSub_4,iKey);
	fSelectKeyMenu(idUser,iSelectRaceId);

	return PLUGIN_HANDLED;
}

//Функция выбора пунктов в под меню "Гильдия Света"
public _Callback_SUB_MENU_ID_5(idUser,iKey)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

//	client_print(idUser,print_chat,"iKey: %d",iKey);

	if(iKey == 8) //Назад
	{
		DB_GetAllXP( idUser,MENU_ID_DEFAULT);
		return PLUGIN_HANDLED;
	}

	if(iKey == 9) //Выход
		return PLUGIN_HANDLED;

	new iSelectRaceId = ArrayGetCell(arrIntBaseMenuDataSub_5,iKey);
	fSelectKeyMenu(idUser,iSelectRaceId);

	return PLUGIN_HANDLED;
}

//Функция выбора пунктов в под меню "Гильдия Тьмы"
public _Callback_SUB_MENU_ID_6(idUser,iKey)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

//	client_print(idUser,print_chat,"iKey: %d",iKey);

	if(iKey == 8) //Назад
	{
		DB_GetAllXP( idUser,MENU_ID_DEFAULT);
		return PLUGIN_HANDLED;
	}

	if(iKey == 9) //Выход
		return PLUGIN_HANDLED;

	new iSelectRaceId = ArrayGetCell(arrIntBaseMenuDataSub_6,iKey);
	fSelectKeyMenu(idUser,iSelectRaceId);

	return PLUGIN_HANDLED;
}

//=============================================================================
//=============================================================================
//=============================================================================
//-----------------Функции выбора пунктов меню-----------------------END }

public fResetSelectRace(idUser)
{
	if(arrResetRace[idUser] == false)
	{
		if(arrIntData[idUser][P_RACE] == RACE_NONE)
			return;

		//Сброс расы если превышен уровень ограничения
		if(isPlayerSelectRaceVIP(idUser,arrIntData[idUser][P_RACE]) == true)
		{
			DB_SaveXP(idUser,false);

			arrResetRace[idUser] = true;

			set_task(7.0, "taskRestRace", idUser + TASKID_RESETRACE);
		}
	}
}

public taskRestRace(idUser)
{
	if (idUser >= TASKID_RESETRACE )
		idUser -= TASKID_RESETRACE;

	fResetUltimateTimerDivider(idUser);

	WC3_PlayerInit(idUser);

	arrIntData[idUser][P_RACE] = 0;
	arrIntData[idUser][P_CHANGERACE] = 0;

	WC3_ChangeRaceStart(idUser);
	WC3_ShowBar(idUser);

	arrResetRace[idUser] = false;
}

public fGetNumRacePlayers(idUser,arrRaceTeam[3][MAX_RACES+1])
{
	new iPlayers[32], iNumPlayers;
	get_players( iPlayers, iNumPlayers );

	new bool:bRaceUsed[MAX_RACES+1] = {false}, iTargetID;
	for (new i = 0; i < iNumPlayers; i++ )
	{
		new iID	= iPlayers[i];
		new iRace	= arrIntData[iID][P_RACE];
		
		bRaceUsed[iRace] = true;
	}

	for (new iRaceID = 1; iRaceID < MAX_RACES + 1; iRaceID++ )
	{
		if (bRaceUsed[iRaceID])
		{
			for (new iTeam = TEAM_T; iTeam <= TEAM_CT + 1; iTeam++ )
			{
				for (new k = 0; k < iNumPlayers; k++ )
				{
					iTargetID = iPlayers[k];
					if (arrIntData[iTargetID][P_RACE] == iRaceID && get_user_team(iTargetID) == iTeam)
					{
						if (iTeam == TEAM_T)
						{
							arrRaceTeam[TEAM_T][iRaceID]++;
						}
						else if (iTeam == TEAM_CT)
						{
							arrRaceTeam[TEAM_CT][iRaceID]++;
						}
					}
				}//end player loop
			}//end team loop
		}
	}//end race loop
}


