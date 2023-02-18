// ******************************************************************
// Глобальные функции настройки вип
// ******************************************************************

//Загрузка файла настройки
public clVIP:vfLoadVipSystemFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	arrStrVipName = ArrayCreate(64, 1);
	arrStrVipFlag = ArrayCreate(64, 1);
//	arrStrVipDay = ArrayCreate(64, 1);
	arrStrVipKeys = ArrayCreate(1024, 1);


	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_VIP_SYSTEM_FILE);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load war3ft vip system file %s!", szPath);
		set_fail_state(szError);
		return;
	}
	
	// Set up some vars to hold parsing info
	new szLineData[1024], szKey[64], szValue[1024],iSection;
	
	new szName[255], szFlag[255];//, szDay[255];

	// Open customization file for reading
	new hFileIni = fopen(szPath, "rt")
	
	while (hFileIni && !feof(hFileIni))
	{
		// Read one line at a time
		fgets(hFileIni, szLineData, charsmax(szLineData))
		
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
		
		switch (iSection)
		{			
			case SECTION_OPTIONS_VIP:
			{
				// Разделение строки по символу "="
				strtok(szLineData, szKey, charsmax(szKey), szValue, charsmax(szValue), '=')
				
				// Удаление пробелов
				trim(szKey);
				trim(szValue);

				if (equal(szKey, "HP_ARMOR_MIN_ROUND"))
					iHpArmorMinRound = str_to_num(szValue);
				else if (equal(szKey, "GREANADE_ALL_ROUND"))
					iGreanadeAllRound = str_to_num(szValue);
				else if (equal(szKey, "HEGRENADE_ROUND"))
					iHegrenadeRound = str_to_num(szValue);
				else if (equal(szKey, "FLASHBANG_ROUND"))
					iFlashbangRound = str_to_num(szValue);
				else if (equal(szKey, "SMOKEGRENADE_ROUND"))
					iSmokegrenadeRound = str_to_num(szValue);
				else if (equal(szKey, "RESPAWN_ROUND"))
					iRespawnRound = str_to_num(szValue);
				else if (equal(szKey, "SPEED_VALUE"))
					fSpeedValueVip = str_to_float(szValue);
				else if (equal(szKey, "GRAVITY_VALUE"))
					fGravityValueVip = str_to_float(szValue);
				else if (equal(szKey, "HP_ROUND"))
					iHpRound = str_to_num(szValue);
				else if (equal(szKey, "HP_VALUE"))
					iHpValue = str_to_num(szValue);
				else if (equal(szKey, "ARMOR_ROUND"))
					iArmorRound = str_to_num(szValue);
				else if (equal(szKey, "ARMOR_VALUE"))
					iArmorValue = str_to_num(szValue);
				else if (equal(szKey, "MONEY_ROUND"))
					iMoneyRound = str_to_num(szValue);
				else if (equal(szKey, "MONEY_VALUE"))
					iMoneyValue = str_to_num(szValue);
				else if (equal(szKey, "AWP_ROUND"))
					iAwpRound = str_to_num(szValue);
				else if (equal(szKey, "AK47_ROUND"))
					iAk47Round = str_to_num(szValue);
				else if (equal(szKey, "DEAGLE_ROUND"))
					iDeagleRound = str_to_num(szValue);
				else if (equal(szKey, "AUG_ROUND"))
					iAugRound = str_to_num(szValue);
				else if (equal(szKey, "SG552_ROUND"))
					iSg552Round = str_to_num(szValue);
				else if (equal(szKey, "M4A1_ROUND"))
					iM4a1Round = str_to_num(szValue);
				else if (equal(szKey, "M249_ROUND"))
					iM249Round = str_to_num(szValue);
				else if (equal(szKey, "M3_ROUND"))
					iM3Round = str_to_num(szValue);
				else if (equal(szKey, "XM1014_ROUND"))
					iXm1014Round = str_to_num(szValue);
				else if (equal(szKey, "ALL_WEAPONS_ROUND"))
					iAllWeaponsRound = str_to_num(szValue);
				else if (equal(szKey, "ALL_WEAPONS_BLOCK_MAP"))
					copy(szAllWeaponsBlockMap, charsmax(szAllWeaponsBlockMap), szValue);
				else if (equal(szKey, "DHUD_MESSSAGE"))
					iDhudMesssageVip = str_to_num(szValue);
				else if (equal(szKey, "CHAT_MESSSAGE"))
					iChatMesssageVip = str_to_num(szValue);
				
				
			}//case

			case SECTION_USERS_VIP:
			{
				// Начало новой секции
				if (szLineData[0] == '"')
				{	
					// Разделение строки по символу "="
					strtok(szLineData, szKey, charsmax(szKey), szValue, charsmax(szValue), '=');
					
					// Удаление пробелов
					trim(szKey);
					trim(szValue);

					ArrayPushString(arrStrVipKeys, szValue);

					szName[0] = 0;
					szFlag[0] = 0;
					//szDay[0] = 0;
						
					//parse(szKey,szName,charsmax(szName), szFlag,charsmax(szFlag),szDay,charsmax(szDay));
					parse(szKey,szName,charsmax(szName), szFlag,charsmax(szFlag));

					ArrayPushString(arrStrVipName, szName);
					ArrayPushString(arrStrVipFlag, szFlag);
					//ArrayPushString(arrStrVipDay, szDay);

					//log_amx("Name: '%s' | Flag: '%s' | Day: '%s'",szName,szFlag,szDay);
					//log_amx("Keys: '%s'",szValue);

				}//if
			}//case

		}//switch

		
	}

	if (hFileIni) 
		fclose(hFileIni);
	
}


bool:clVIP:isMap()
{
	new szValue[255];
	copy(szValue, charsmax(szValue), szAllWeaponsBlockMap);

	new szMap[64];
	new szMapName[64];
	get_mapname(szMapName, charsmax(szMapName));

	while (szValue[0] != 0 && strtok(szValue, szMap, charsmax(szMap), szValue, charsmax(szValue), ','))
	{
		trim(szMap);
		trim(szValue);
		
		new iLength;
		new szRestrictName[64];
		iLength = copyc(szRestrictName, charsmax(szRestrictName), szMap, '*' );

		if (equali(szMapName, szRestrictName, iLength))
		{
			//log_amx("Map: '%s' | szRestrictName: '%s'",szMapName,szRestrictName);
			return true;
		}
	}

	return false;
}

stock clVIP:isVipActiveIndex(const idUser)
{ 
	new iVipIndex = -1;
	
	for(new i = 0; i < ArraySize(arrStrVipName); i++)
	{
		new szUserAuthid[32],szUserName[32];
		get_user_authid(idUser, szUserAuthid, charsmax(szUserAuthid));
		get_user_name(idUser, szUserName, charsmax(szUserName));

		new szAuthData[64];
		ArrayGetString(arrStrVipName,i, szAuthData, charsmax(szAuthData));
			
		new szFlags[64];
		ArrayGetString(arrStrVipFlag,i, szFlags, charsmax(szFlags));

		//new szDay[255];
		//ArrayGetString(arrStrVipDay,i, szDay, charsmax(szDay));
			
		new bitFlagVip = read_flags(szFlags);
		if(equali(szAuthData,szUserAuthid) && (bitFlagVip & FLAG_AUTHID) )//Steam ID
		{				
			arrBoolData[idUser][PB_VIP_ACCESS] = true;
			iVipIndex = i;
			break;
		}

		if(equali(szAuthData,szUserName) && (bitFlagVip & FLAG_KICK) )//Name
		{			
			arrBoolData[idUser][PB_VIP_ACCESS] = true;
			iVipIndex = i;
			break;
		}
	}


	return iVipIndex;

}

bool:clVIP:isAccesItemVip(const idUser,const idItem)
{
	if(arrBoolData[idUser][PB_VIP_ACCESS] == true && arrIsItemVip[idUser][idItem] == true)
		return true;

	return false;
}

public clVIP:fInitItemsAccessVip(const idUser)
{
	new iVipIndex = clVIP:isVipActiveIndex(idUser);

	if(iVipIndex < 0)
		return;
	
	new szVipKeys[1024];
	ArrayGetString(arrStrVipKeys,iVipIndex, szVipKeys, charsmax(szVipKeys));

	new szKey[64];
	
	while (szVipKeys[0] != 0 && strtok(szVipKeys, szKey, charsmax(szKey), szVipKeys, charsmax(szVipKeys), ','))
	{
		trim(szKey);
				
		if (equal(szKey, "ANKH"))
		{		
			arrIsItemVip[idUser][ITEM_ANKH] = true;
		}
		else if (equal(szKey, "MASK"))
		{			
			arrIsItemVip[idUser][ITEM_MASK] = true;
		}
		else if (equal(szKey, "NECKLACE"))
		{			
			arrIsItemVip[idUser][ITEM_NECKLACE] = true;
		}
		//ITEM_HEALTH - Periapt of Health
		else if (equal(szKey, "HEALTH"))
		{			
			arrIsItemVip[idUser][ITEM_HEALTH] = true;
			
			new iCurrentHealth = clHP:getUserHealth(idUser);
			new iBonusHp = get_pcvar_num(CVAR_wc3_health);
			
			clHP:setUserHealth(idUser,iCurrentHealth + iBonusHp);
		}
		else if (equal(szKey, "HELM"))
		{
			arrIsItemVip[idUser][ITEM_HELM] = true;
		}
		else if (equal(szKey, "AMULET"))
		{	
			arrIsItemVip[idUser][ITEM_AMULET] = true;
		}
		else if (equal(szKey, "INTELLECT"))
		{	
			arrIsItemVip[idUser][ITEM_INTELLECT] = true;
		}
		else if (equal(szKey, "GRENADE_PROTECTION"))
		{			
			arrIsItemVip[idUser][ITEM_GRENADE_PROTECTION] = true;
		}
		//ITEM_THIEF - Похититель
		else if (equal(szKey, "THIEF"))
		{			
			arrIsItemVip[idUser][ITEM_THIEF] = true;

			ITEM_Thief(idUser);
		}
		
	}

}

public clVIP:fResetItemsAccessVip(const idUser)
{
	
	arrIsItemVip[idUser][ITEM_ANKH]						= false;	// Ankh of Reincarnation
	arrIsItemVip[idUser][ITEM_BOOTS]					= false;	// Boots of Speed
	arrIsItemVip[idUser][ITEM_CLAWS]					= false;	// Claws of Attack
	arrIsItemVip[idUser][ITEM_CLOAK]					= false;	// Cloak of Shadows
	arrIsItemVip[idUser][ITEM_MASK]						= false;	// Mask of Death
	arrIsItemVip[idUser][ITEM_NECKLACE]					= false;	// Necklace of Immunity
	arrIsItemVip[idUser][ITEM_FROST]					= false;	// Orb of Frost
	arrIsItemVip[idUser][ITEM_HEALTH]					= false;	// Periapt of Health
	arrIsItemVip[idUser][ITEM_TOME]						= false;	// Tome of Experience
	arrIsItemVip[idUser][ITEM_SCROLL]					= false;	// Scroll of Respawning
	arrIsItemVip[idUser][ITEM_PROTECTANT]				= false;	// Mole Protectant
	arrIsItemVip[idUser][ITEM_HELM]						= false;	// Helm of Excellence
	arrIsItemVip[idUser][ITEM_AMULET]				    = false;	// Amulet of the Cat
	arrIsItemVip[idUser][ITEM_SOCK]						= false;	// Sock of the Feather
	arrIsItemVip[idUser][ITEM_GLOVES]					= false;	// Flaming Gloves of Warmth
	arrIsItemVip[idUser][ITEM_RING]						= false;	// Ring of Regeneration + 1
	arrIsItemVip[idUser][ITEM_CHAMELEON]				= false;	// Chameleon
	arrIsItemVip[idUser][ITEM_MOLE]						= false;	// Mole
	arrIsItemVip[idUser][ITEM_INTELLECT]				= false;	// Intellect
	arrIsItemVip[idUser][ITEM_GRENADE_PROTECTION]		= false;	// Grenade Protection
	arrIsItemVip[idUser][ITEM_MIRROR_SHIELD]			= false;	// Mirror Shield
	arrIsItemVip[idUser][ITEM_ESP]						= false;	// ESP
	arrIsItemVip[idUser][ITEM_FROST_ARMOR]				= false;	// Frost Armor
	arrIsItemVip[idUser][ITEM_DEATH_TOUCH]				= false;	//Death's Touch
	arrIsItemVip[idUser][ITEM_HEALTH_POTION]			= false;	// Health Potion
	arrIsItemVip[idUser][ITEM_ULTIMATE_TIMER_DIVIDER]	= false;	// Ultimate Timer Divider
	arrIsItemVip[idUser][ITEM_STEEL_SKIN]				= false;	// Steel Skin
	arrIsItemVip[idUser][ITEM_DEVOURER_LIGHT]			= false;	// 
	arrIsItemVip[idUser][ITEM_ICE_BLOCK]				= false;	// 
	arrIsItemVip[idUser][ITEM_THIEF]					= false;	// 
	arrIsItemVip[idUser][ITEM_MIRROR_ULTIMATE]			= false;	// 
	arrIsItemVip[idUser][ITEM_DEATHCOIL]				= false;	// 
	arrIsItemVip[idUser][ITEM_IMPALE]					= false;	//
	arrIsItemVip[idUser][ITEM_SLEEP]					= false;	// 
	arrIsItemVip[idUser][ITEM_BOOK_DEAD]				= false;	// 
	arrIsItemVip[idUser][ITEM_TRANQUILITY]				= false;	// 
}

clVIP:fShowVipMenu(const idUser,iPage = 0)
{
	new iVipIndex = clVIP:isVipActiveIndex(idUser);

	if(iVipIndex < 0)
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_VIP_NO_ACCESS",iAllWeaponsRound);
		cssbChatColor(idUser,"%s%s",clVIP:fTagVip(),szMessage);

		return;
	}
	
	new idMenu,szMenuData[256];
	
	//Название главного меню
	formatex(szMenuData, charsmax(szMenuData), "%L", LANG_PLAYER, "WC3_MENU_VIP");
	idMenu = menu_create(szMenuData, "_Callback_VIP_MENU");

	new szVipKeys[1024];
	ArrayGetString(arrStrVipKeys,iVipIndex, szVipKeys, charsmax(szVipKeys));

	new szKey[64];
	
	while (szVipKeys[0] != 0 && strtok(szVipKeys, szKey, charsmax(szKey), szVipKeys, charsmax(szVipKeys), ','))
	{
		trim(szKey);
				
		new szLangItem[64];
		if (equal(szKey, "GREANADE_ALL"))
		{		
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_1",iGreanadeAllRound - arrIsItemVipOneRound[idUser][1]);
				menu_additem(idMenu,szLangItem,"1",0,-1);
			}
		}
		else if (equal(szKey, "HEGRENADE"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_2",iHegrenadeRound - arrIsItemVipOneRound[idUser][2]);
				menu_additem(idMenu,szLangItem,"2",0,-1);
			}
		}
		else if (equal(szKey, "FLASHBANG"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_3",iFlashbangRound - arrIsItemVipOneRound[idUser][3]);
				menu_additem(idMenu,szLangItem,"3",0,-1);
			}
		}
		else if (equal(szKey, "SMOKEGRENADE"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_4",iSmokegrenadeRound - arrIsItemVipOneRound[idUser][4]);
				menu_additem(idMenu,szLangItem,"4",0,-1);
			}
		}
		else if (equal(szKey, "RESPAWN"))
		{			
			formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_5",iRespawnRound - arrIsItemVipOneRound[idUser][5]);
			menu_additem(idMenu,szLangItem,"5",0,-1);
		}
		else if (equal(szKey, "SPEED"))
		{	
			new szOnOff[64];
			if(arrBoolData[idUser][PB_VIP_SPEED] == true)
				formatex(szOnOff, charsmax(szOnOff), "%L", LANG_PLAYER, "WC3_MENU_VIP_OFF");	
			else
				formatex(szOnOff, charsmax(szOnOff), "%L", LANG_PLAYER, "WC3_MENU_VIP_ON");

			formatex(szLangItem, charsmax(szLangItem), "%L %s", LANG_PLAYER, "WC3_MENU_VIP_6",fSpeedValueVip,szOnOff);
			menu_additem(idMenu,szLangItem,"6",0,-1);
		}
		else if (equal(szKey, "GRAVITY"))
		{	
			new szOnOff[64];
			if(arrBoolData[idUser][PB_VIP_GRAVITY] == true)
				formatex(szOnOff, charsmax(szOnOff), "%L", LANG_PLAYER, "WC3_MENU_VIP_OFF");	
			else
				formatex(szOnOff, charsmax(szOnOff), "%L", LANG_PLAYER, "WC3_MENU_VIP_ON");

			formatex(szLangItem, charsmax(szLangItem), "%L %s", LANG_PLAYER, "WC3_MENU_VIP_7",fGravityValueVip * 1000,szOnOff);
			menu_additem(idMenu,szLangItem,"7",0,-1);
		}
		else if (equal(szKey, "HP"))
		{			
			formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_8",iHpValue,iHpRound - arrIsItemVipOneRound[idUser][8]);
			menu_additem(idMenu,szLangItem,"8",0,-1);
		}
		else if (equal(szKey, "ARMOR"))
		{			
			formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_9",iArmorValue,iArmorRound - arrIsItemVipOneRound[idUser][9]);
			menu_additem(idMenu,szLangItem,"9",0,-1);
		}
		else if (equal(szKey, "MONEY"))
		{			
			formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_10",iMoneyValue,iMoneyRound - arrIsItemVipOneRound[idUser][10]);
			menu_additem(idMenu,szLangItem,"10",0,-1);
		}
		else if (equal(szKey, "AWP"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_11",iAwpRound - arrIsItemVipOneRound[idUser][11]);
				menu_additem(idMenu,szLangItem,"11",0,-1);
			}
		}
		else if (equal(szKey, "AK47"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_12",iAk47Round - arrIsItemVipOneRound[idUser][12]);
				menu_additem(idMenu,szLangItem,"12",0,-1);
			}
		}
		else if (equal(szKey, "DEAGLE"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_13",iDeagleRound - arrIsItemVipOneRound[idUser][13]);
				menu_additem(idMenu,szLangItem,"13",0,-1);
			}
		}
		else if (equal(szKey, "AUG"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_14",iAugRound - arrIsItemVipOneRound[idUser][14]);
				menu_additem(idMenu,szLangItem,"14",0,-1);
			}
		}
		else if (equal(szKey, "SG552"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_15",iSg552Round - arrIsItemVipOneRound[idUser][15]);
				menu_additem(idMenu,szLangItem,"15",0,-1);
			}
		}
		else if (equal(szKey, "M4A1"))
		{		
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_16",iM4a1Round - arrIsItemVipOneRound[idUser][16]);
				menu_additem(idMenu,szLangItem,"16",0,-1);
			}
		}
		else if (equal(szKey, "M249"))
		{	
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_17",iM249Round - arrIsItemVipOneRound[idUser][17]);
				menu_additem(idMenu,szLangItem,"17",0,-1);
			}
		}
		else if (equal(szKey, "M3"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_18",iM3Round - arrIsItemVipOneRound[idUser][18]);
				menu_additem(idMenu,szLangItem,"18",0,-1);
			}
		}
		else if (equal(szKey, "XM1014"))
		{			
			if(clVIP:isMap() == false)
			{
				formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_19",iXm1014Round - arrIsItemVipOneRound[idUser][19]);
				menu_additem(idMenu,szLangItem,"19",0,-1);
			}
		}
		else if (equal(szKey, "HP_ARMOR_MIN"))
		{			
			new iMinHealth = clHP:getRaceMinHealth(idUser);
			new iMaxArmor = clAr:getRaceMaxArmor(idUser);

			formatex(szLangItem, charsmax(szLangItem), "%L", LANG_PLAYER, "WC3_MENU_VIP_20",iMinHealth,iMaxArmor,iHpArmorMinRound - arrIsItemVipOneRound[idUser][20]);
			menu_additem(idMenu,szLangItem,"20",0,-1);
		}
	}

	// Если нет предметов в меню
	if (menu_items(idMenu) <= 0)
	{
		menu_destroy(idMenu);
		return;
	}			

	//Пункты меню (назад - следующий - выход)
	formatex(szMenuData, charsmax(szMenuData), "\w%L", LANG_PLAYER, "WC3_MENU_BACK");
	menu_setprop(idMenu, MPROP_BACKNAME, szMenuData);
	formatex(szMenuData, charsmax(szMenuData), "\w%L", LANG_PLAYER, "WC3_MENU_NEXT");
	menu_setprop(idMenu, MPROP_NEXTNAME, szMenuData);
	formatex(szMenuData, charsmax(szMenuData), "\r%L", LANG_PLAYER, "WC3_MENU_EXIT");
	menu_setprop(idMenu, MPROP_EXITNAME, szMenuData);

	menu_display(idUser, idMenu, iPage);

}


//Отображение сообщения DHOD при взятии предмета випом
stock clVIP:fShowMessageDhud(const idUser,const iTypeItem)
{
	if(iDhudMesssageVip <= 0)
		return;
	
	UTIL_ClearDHudChannel(idUser);
	UTIL_ClearHudChannel(idUser,HUD_XP);
	WC3_ShowBar(idUser);

	new iRed = random_num(0,255);
	new iGreen = random_num(0,255);
	new iBlue = random_num(0,255);

	new szShowMessage[256];

	new szUserName[32];
	get_user_name(idUser, szUserName, charsmax(szUserName));

	switch(iTypeItem)
	{
		case enHP_ARMOR_MIN:
		{
			new iMinHealth = clHP:getRaceMinHealth(idUser);
			new iMaxArmor = clAr:getRaceMaxArmor(idUser);

			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L^n(%d | %d)",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_20",iMinHealth,iMaxArmor);
		}
		case enGREANADE_ALL:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_1");
				
		}
		case enHEGRENADE:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_2");
		}
		case enFLASHBANG:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_3");	
		}
		case enSMOKEGRENADE:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_4");	
		}
		case enRESPAWN:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_5");		
		}
		case enSPEED:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L^n%.1f",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_6",fSpeedValueVip);	
		}
		case enGRAVITY:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L^n%.1f",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_7",fGravityValueVip * 1000);	
		}
		case enHP:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L^n%d",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_8",iHpValue);	
		}
		case enARMOR:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L^n%d",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_9",iArmorValue);	
		}
		case enMONEY:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L^n%d",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_10",iMoneyValue);	
		}
		case enAWP:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_11");	
		}
		case enAK47:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_12");	
		}
		case enDEAGLE:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_13");	
		}
		case enAUG:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_14");	
		}
		case enSG552:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_15");	
		}
		case enM4A1:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_16");	
		}
		case enM249:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_17");	
		}
		case enM3:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_18");	
		}
		case enXM1014:
		{
			format(szShowMessage, charsmax(szShowMessage), "%s^n+ %L",szUserName,LANG_PLAYER,"WC3_CHAT_VIP_19");	
		}
		
	}//switch

	set_dhudmessage(iRed,iGreen,iBlue,0.83,0.5,2,0.0,2.0,0.02,0.02);

	if(iDhudMesssageVip == 1)
		show_dhudmessage(idUser, szShowMessage);
	else if(iDhudMesssageVip == 2)
		show_dhudmessage(0, szShowMessage);
	
}

//Отображение сообщения в чат при взятии предмета випом
stock clVIP:fShowMessageChat(const idUser,const iTypeItem)
{
	if(iChatMesssageVip <= 0)
		return;
	
	new szShowMessage[256];

	new szUserName[32];
	get_user_name(idUser, szUserName, charsmax(szUserName));

	switch(iTypeItem)
	{
		case enHP_ARMOR_MIN:
		{
			new iMinHealth = clHP:getRaceMinHealth(idUser);
			new iMaxArmor = clAr:getRaceMaxArmor(idUser);

			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^" !y(!t%d !y| !t%d!y)",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_20",iMinHealth,iMaxArmor);
		}
		case enGREANADE_ALL:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_1");
				
		}
		case enHEGRENADE:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_2");
		}
		case enFLASHBANG:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_3");	
		}
		case enSMOKEGRENADE:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_4");	
		}
		case enRESPAWN:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_5");		
		}
		case enSPEED:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^" !t%.1f",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_6",fSpeedValueVip);	
		}
		case enGRAVITY:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^" !t%.1f",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_7",fGravityValueVip * 1000);	
		}
		case enHP:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^" !t%d",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_8",iHpValue);	
		}
		case enARMOR:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^" !t%d",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_9",iArmorValue);	
		}
		case enMONEY:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^" !t%d",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_10",iMoneyValue);	
		}
		case enAWP:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_11");	
		}
		case enAK47:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_12");	
		}
		case enDEAGLE:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_13");	
		}
		case enAUG:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_14");	
		}
		case enSG552:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_15");	
		}
		case enM4A1:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_16");	
		}
		case enM249:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_17");	
		}
		case enM3:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_18");	
		}
		case enXM1014:
		{
			format(szShowMessage, charsmax(szShowMessage), "!t%s %L !g^"%L^"",szUserName,LANG_PLAYER,"WC3_APPLY",LANG_PLAYER,"WC3_CHAT_VIP_19");	
		}
		
	}//switch	

	if(iChatMesssageVip == 1)
		cssbChatColor(idUser,"%s%s",clVIP:fTagVip(),szShowMessage);
	else if(iChatMesssageVip == 2)
		cssbChatColor(0,"%s%s",clVIP:fTagVip(),szShowMessage);
	
}


stock clVIP:fTagVip()
{
	new szTag[64];
	formatex(szTag, sizeof(szTag) - 1, "%L%L%L ",LANG_PLAYER,"WC3_BRACKET_LEFT_VIP",LANG_PLAYER,"WC3_PREFIX_VIP",LANG_PLAYER,"WC3_BRACKET_RIGHT_VIP");
	return szTag;
}

public _Callback_VIP_MENU(idUser, idMenu, idItem)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;




	// Возврат в главное меню
	if (idItem == MENU_EXIT)
	{
		menu_destroy(idMenu);
		return PLUGIN_HANDLED;
	}
	
	static _access, szInfoMenu[8], callback;
	menu_item_getinfo(idMenu, idItem, _access, szInfoMenu, sizeof(szInfoMenu) - 1, _, _, callback);
	
	new iNumberItem = str_to_num(szInfoMenu);
	
	switch (iNumberItem)
	{
		case 1://GREANADE_ALL
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][1], iGreanadeAllRound))
				return PLUGIN_HANDLED;

			//HE Grenade
			give_item(idUser, "weapon_hegrenade" );

			//Concussion Grenades (i.e. Flashbang)
			give_item(idUser, "weapon_flashbang" );
			give_item(idUser, "weapon_flashbang" );
			 		 
			//Smoke grenades
			give_item(idUser, "weapon_smokegrenade" );

			arrIsItemVipOneRound[idUser][1]++;

			clVIP:fShowMessageDhud(idUser,enGREANADE_ALL);
			clVIP:fShowMessageChat(idUser,enGREANADE_ALL);
						
		}
		case 2://HEGRENADE
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][2], iHegrenadeRound))
				return PLUGIN_HANDLED;

			//HE Grenade
			give_item(idUser, "weapon_hegrenade");

			arrIsItemVipOneRound[idUser][2]++;

			clVIP:fShowMessageDhud(idUser,enHEGRENADE);
			clVIP:fShowMessageChat(idUser,enHEGRENADE);
				
		}
		case 3://FLASHBANG
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][3], iFlashbangRound))
				return PLUGIN_HANDLED;

			//Concussion Grenades (i.e. Flashbang)
			give_item(idUser, "weapon_flashbang" );
			give_item(idUser, "weapon_flashbang" );

			arrIsItemVipOneRound[idUser][3]++;

			clVIP:fShowMessageDhud(idUser,enFLASHBANG);
			clVIP:fShowMessageChat(idUser,enFLASHBANG);

		}
		case 4://SMOKEGRENADE
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][4], iSmokegrenadeRound))
				return PLUGIN_HANDLED;

			//Smoke grenades
			give_item(idUser, "weapon_smokegrenade" );

			arrIsItemVipOneRound[idUser][4]++;

			clVIP:fShowMessageDhud(idUser,enSMOKEGRENADE);
			clVIP:fShowMessageChat(idUser,enSMOKEGRENADE);

		}
		case 5://RESPAWN
		{			
			if(!clGl::isUserNoTeam(idUser))
			{
				menu_destroy(idMenu);
				return PLUGIN_HANDLED;
			}

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][5], iRespawnRound))
				return PLUGIN_HANDLED;


			new iRespEntity;

			new iTeam = get_user_team(idUser);
			if (iTeam == TEAM_T )
				iRespEntity = CanTeleportOnBaseT();
			if (iTeam == TEAM_CT )
				iRespEntity = CanTeleportOnBaseCT();

			if(pev_valid(iRespEntity))
			{
				clVIP:fTeleportRespawn(idUser, iRespEntity);
				
				WC3_PostSpawn(idUser);

				arrIsItemVipOneRound[idUser][5]++;

				clVIP:fShowMessageDhud(idUser,enRESPAWN);
				clVIP:fShowMessageChat(idUser,enRESPAWN);
			}
			
		}
		case 6://SPEED
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;
			
			arrBoolData[idUser][PB_VIP_SPEED] = ( ( arrBoolData[idUser][PB_VIP_SPEED] == false ) ? true : false );

			SHARED_SetSpeed(idUser);

			arrIsItemVipOneRound[idUser][6]++;

			if(arrBoolData[idUser][PB_VIP_SPEED] == true)
			{
				clVIP:fShowMessageDhud(idUser,enSPEED);
				clVIP:fShowMessageChat(idUser,enSPEED);
			}

		}
		case 7://GRAVITY
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			arrBoolData[idUser][PB_VIP_GRAVITY] = ( ( arrBoolData[idUser][PB_VIP_GRAVITY] == false ) ? true : false );

			SHARED_SetGravity(idUser);

			arrIsItemVipOneRound[idUser][7]++;

			if(arrBoolData[idUser][PB_VIP_GRAVITY] == true)
			{
				clVIP:fShowMessageDhud(idUser,enGRAVITY);
				clVIP:fShowMessageChat(idUser,enGRAVITY);
			}

		}
		case 8://HP
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][8], iHpRound))
				return PLUGIN_HANDLED;

			new iMaxHealth = clHP:getRaceMaxHealth(idUser);
			new iCurrentHealth =  clHP:getUserHealth(idUser);
			new iBonusHp = iHpValue;

			if (iCurrentHealth < iMaxHealth)
			{
				if( (iCurrentHealth + iBonusHp) > iMaxHealth )
					clHP:setUserHealth(idUser,iMaxHealth);
				else
					clHP:setUserHealth(idUser,iCurrentHealth + iBonusHp);
			}

			arrIsItemVipOneRound[idUser][8]++;

			clVIP:fShowMessageDhud(idUser,enHP);
			clVIP:fShowMessageChat(idUser,enHP);
			
		}
		case 9://ARMOR
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][9], iArmorRound))
				return PLUGIN_HANDLED;

			new iMaxArmor = clAr:getRaceMaxArmor(idUser);
			new CsArmorType:tArmor;
			new iCurrentArmor =  clAr:getUserArmor(idUser,tArmor);
			new iBonusArmor = iArmorValue;

			if((iCurrentArmor + iBonusArmor) > iMaxArmor)
				clAr:setUserArmor(idUser,iMaxArmor);
			else
				clAr:setUserArmor(idUser,iCurrentArmor + iBonusArmor);

			arrIsItemVipOneRound[idUser][9]++;

			clVIP:fShowMessageDhud(idUser,enARMOR);
			clVIP:fShowMessageChat(idUser,enARMOR);
		}
		case 10://MONEY
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][10], iMoneyRound))
				return PLUGIN_HANDLED;

			new iMoneyUserCurrent = SHARED_GetUserMoney(idUser);
			new iBonusMoney = iMoneyValue;
			SHARED_SetUserMoney(idUser, iMoneyUserCurrent + iBonusMoney, 1 );

			arrIsItemVipOneRound[idUser][10]++;

			clVIP:fShowMessageDhud(idUser,enMONEY);
			clVIP:fShowMessageChat(idUser,enMONEY);

		}
		case 11://AWP
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isActiveAllWpnRound(idUser,idMenu,idItem))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][11], iAwpRound))
				return PLUGIN_HANDLED;

			clVIP:fStripWpnPrimary(idUser);

			give_item(idUser, "weapon_awp" );
			give_item(idUser,"ammo_338magnum");
			give_item(idUser,"ammo_338magnum");
			give_item(idUser,"ammo_338magnum");	

			arrIsItemVipOneRound[idUser][11]++;

			clVIP:fShowMessageDhud(idUser,enAWP);
			clVIP:fShowMessageChat(idUser,enAWP);

		}
		case 12://AK47
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isActiveAllWpnRound(idUser,idMenu,idItem))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][12], iAk47Round))
				return PLUGIN_HANDLED;

			clVIP:fStripWpnPrimary(idUser);

			give_item(idUser, "weapon_ak47");
			give_item(idUser, "ammo_762nato");
			give_item(idUser, "ammo_762nato");
			give_item(idUser, "ammo_762nato");
			
			arrIsItemVipOneRound[idUser][12]++;

			clVIP:fShowMessageDhud(idUser,enAK47);
			clVIP:fShowMessageChat(idUser,enAK47);

		}
		case 13://DEAGLE
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isActiveAllWpnRound(idUser,idMenu,idItem))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][13], iDeagleRound))
				return PLUGIN_HANDLED;
			
			clVIP:fStripWpnSecondary(idUser);

			give_item(idUser, "weapon_deagle");
			give_item(idUser, "ammo_50ae");
			give_item(idUser, "ammo_50ae");
			give_item(idUser, "ammo_50ae");
			give_item(idUser, "ammo_50ae");
			give_item(idUser, "ammo_50ae");

			arrIsItemVipOneRound[idUser][13]++;

			clVIP:fShowMessageDhud(idUser,enDEAGLE);
			clVIP:fShowMessageChat(idUser,enDEAGLE);

		}
		case 14://AUG
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isActiveAllWpnRound(idUser,idMenu,idItem))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][14], iAugRound))
				return PLUGIN_HANDLED;

			clVIP:fStripWpnPrimary(idUser);

			give_item(idUser, "weapon_aug");
			give_item(idUser, "ammo_556nato");
			give_item(idUser, "ammo_556nato");
			give_item(idUser, "ammo_556nato");

			arrIsItemVipOneRound[idUser][14]++;

			clVIP:fShowMessageDhud(idUser,enAUG);
			clVIP:fShowMessageChat(idUser,enAUG);

		}
		case 15://SG552
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isActiveAllWpnRound(idUser,idMenu,idItem))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][15], iSg552Round))
				return PLUGIN_HANDLED;

			clVIP:fStripWpnPrimary(idUser);

			give_item(idUser, "weapon_sg552");
			give_item(idUser, "ammo_556nato");
			give_item(idUser, "ammo_556nato");
			give_item(idUser, "ammo_556nato");

			arrIsItemVipOneRound[idUser][15]++;

			clVIP:fShowMessageDhud(idUser,enSG552);
			clVIP:fShowMessageChat(idUser,enSG552);

		}
		case 16://M4A1
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isActiveAllWpnRound(idUser,idMenu,idItem))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][16], iM4a1Round))
				return PLUGIN_HANDLED;
			
			clVIP:fStripWpnPrimary(idUser);

			give_item(idUser, "weapon_m4a1");
			give_item(idUser, "ammo_556nato");
			give_item(idUser, "ammo_556nato");
			give_item(idUser, "ammo_556nato");

			arrIsItemVipOneRound[idUser][16]++;

			clVIP:fShowMessageDhud(idUser,enM4A1);
			clVIP:fShowMessageChat(idUser,enM4A1);

		}
		case 17://M249
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isActiveAllWpnRound(idUser,idMenu,idItem))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][17], iM249Round))
				return PLUGIN_HANDLED;
			
			clVIP:fStripWpnPrimary(idUser);

			give_item(idUser, "weapon_m249");
			give_item(idUser, "ammo_556natobox");
			give_item(idUser, "ammo_556natobox");
			give_item(idUser, "ammo_556natobox");
			give_item(idUser, "ammo_556natobox");
			give_item(idUser, "ammo_556natobox");
			give_item(idUser, "ammo_556natobox");
			give_item(idUser, "ammo_556natobox");	

			arrIsItemVipOneRound[idUser][17]++;

			clVIP:fShowMessageDhud(idUser,enM249);
			clVIP:fShowMessageChat(idUser,enM249);

		}
		case 18://M3
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isActiveAllWpnRound(idUser,idMenu,idItem))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][18], iM3Round))
				return PLUGIN_HANDLED;

			clVIP:fStripWpnPrimary(idUser);

			give_item(idUser, "weapon_m3");
			give_item(idUser, "ammo_buckshot");
			give_item(idUser, "ammo_buckshot");
			give_item(idUser, "ammo_buckshot");
			give_item(idUser, "ammo_buckshot");

			arrIsItemVipOneRound[idUser][18]++;

			clVIP:fShowMessageDhud(idUser,enM3);
			clVIP:fShowMessageChat(idUser,enM3);

		}
		case 19://XM1014
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isActiveAllWpnRound(idUser,idMenu,idItem))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][19], iXm1014Round))
				return PLUGIN_HANDLED;

			clVIP:fStripWpnPrimary(idUser);

			give_item(idUser, "weapon_xm1014");
			give_item(idUser, "ammo_buckshot");
			give_item(idUser, "ammo_buckshot");
			give_item(idUser, "ammo_buckshot");
			give_item(idUser, "ammo_buckshot");
			give_item(idUser, "ammo_buckshot");

			arrIsItemVipOneRound[idUser][19]++;

			clVIP:fShowMessageDhud(idUser,enXM1014);
			clVIP:fShowMessageChat(idUser,enXM1014);

		}
		case 20://HP_ARMOR_MIN
		{
			if(!clVIP:fMenuDestroyVip(idUser,idMenu))
				return PLUGIN_HANDLED;

			if(!clVIP:isCountRoundVip(idUser,idMenu,idItem,arrIsItemVipOneRound[idUser][20], iHpArmorMinRound))
				return PLUGIN_HANDLED;

			new iMinHealth = clHP:getRaceMinHealth(idUser);
			clHP:setUserHealth(idUser,iMinHealth);
			
			new iMaxArmor = clAr:getRaceMaxArmor(idUser);
			clAr:setUserArmor(idUser,iMaxArmor);
				
			arrIsItemVipOneRound[idUser][20]++;

			clVIP:fShowMessageDhud(idUser,enHP_ARMOR_MIN);
			clVIP:fShowMessageChat(idUser,enHP_ARMOR_MIN);
		}
			
	}

	menu_destroy(idMenu);

	clVIP:fShowVipMenu(idUser,floatround(float(idItem / 7)));
		
	return PLUGIN_HANDLED;
}

public clVIP:fTeleportRespawn(const idUser, const resp_ent)
{
	new Float: ptOriginPlayer[3], Float: angles[3];
	
	if(!pev_valid(resp_ent)) 
		return;

	pev(resp_ent, pev_origin, ptOriginPlayer);
	pev(resp_ent, pev_angles, angles);
		
	Create_TE_BEAMTORUS(ptOriginPlayer, 250, arrIdSprites[SPR_ROGUE_RING], 0, 9, 5,   15,    3,    255, 255, 255,    255,  0, 0);
	
	new iTeam = get_user_team(idUser);

	if (iTeam == TEAM_T )
	{
		message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
		write_byte(TE_DLIGHT);
		engfunc(EngFunc_WriteCoord, ptOriginPlayer[0]);
		engfunc(EngFunc_WriteCoord, ptOriginPlayer[1]);
		engfunc(EngFunc_WriteCoord, ptOriginPlayer[2]);
		write_byte(50) ;
		write_byte(238); // red
		write_byte(19); // green
		write_byte(45); // blue
		write_byte(255);
		write_byte(3);
		write_byte(1);
		message_end();
	}
				
	if (iTeam == TEAM_CT )
	{
		message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
		write_byte(TE_DLIGHT);
		engfunc(EngFunc_WriteCoord, ptOriginPlayer[0]);
		engfunc(EngFunc_WriteCoord, ptOriginPlayer[1]);
		engfunc(EngFunc_WriteCoord, ptOriginPlayer[2]);
		write_byte(50) ;
		write_byte(19); // red
		write_byte(89); // green
		write_byte(238); // blue
		write_byte(255);
		write_byte(3);
		write_byte(1);
		message_end();
	}
	
	emit_sound(idUser, CHAN_WEAPON, arrStrSounds[SOUND_VENGEANCE], 1.0, ATTN_NORM, 0, PITCH_NORM);
	
	ExecuteHamB(Ham_CS_RoundRespawn,idUser);

	set_pev(idUser, pev_velocity, Float:{0.0, 0.0, 0.0});
	set_pev(idUser, pev_basevelocity, Float:{0.0, 0.0, 0.0});
	
	set_pev(idUser, pev_origin, ptOriginPlayer);
	set_pev(idUser, pev_angles, angles);
	set_pev(idUser, pev_fixangle, true);

	
}

bool:clVIP:isActiveAllWpnRound(const idUser,const idMenu,const idItem)
{	
	if(iRoundCount < iAllWeaponsRound)
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_VIP_ACTIVE_WPN",iAllWeaponsRound);
		cssbChatColor(idUser,"%s%s",clVIP:fTagVip(),szMessage);

		menu_destroy(idMenu);

		clVIP:fShowVipMenu(idUser,floatround(float(idItem / 7)));
		
		return false;
	}

	return true;

}

bool:clVIP:isCountRoundVip(const idUser,const idMenu,const idItem,const iCountRoundItemVip, const iValueRoundItemVip)
{	
	if(iCountRoundItemVip >= iValueRoundItemVip)
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_VIP_COUNT_ROUND",iValueRoundItemVip);
		cssbChatColor(idUser,"%s%s",clVIP:fTagVip(),szMessage);

		menu_destroy(idMenu);

		clVIP:fShowVipMenu(idUser,floatround(float(idItem / 7)));
		
		return false;
	}

	return true;

}


//Закрытие меню если выбран пункт который не должен срабатывать если игрок жив
bool:clVIP:fMenuDestroyVip(const idUser,const idMenu)
{
	if (!WC3_Check())
		return false;

	if(!is_user_alive(idUser) || !is_user_connected(idUser))
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_VIP_NO_ALIVE");
		cssbChatColor(idUser,"%s%s",clVIP:fTagVip(),szMessage);

		menu_destroy(idMenu);
		return false;
	}

	return true;
}

//Удаление всех автоматов
public clVIP:fStripWpnPrimary(const idUser)
{
	//Benneli M3 Super90
	ham_strip_weapon(idUser,"weapon_m3");
  
	//Benneli XM1014
	ham_strip_weapon(idUser,"weapon_xm1014");
  
	//H&K MP5-Navy
	ham_strip_weapon(idUser,"weapon_mp5navy");
  
	//Steyr Tactical
	ham_strip_weapon(idUser,"weapon_tmp");
 
	//FN P90
	ham_strip_weapon(idUser,"weapon_p90");
 
	//Ingram MAC-10
	ham_strip_weapon(idUser,"weapon_mac10");
 
	//IDF Defender
	ham_strip_weapon(idUser,"weapon_galil");
  
	//Clarion 5.56
	ham_strip_weapon(idUser,"weapon_famas");
  
	//H&K UMP
	ham_strip_weapon(idUser,"weapon_ump45");
  
	//AK-47
	ham_strip_weapon(idUser,"weapon_ak47");
 
 	//Colt M4A1 Carbine
	ham_strip_weapon(idUser,"weapon_m4a1");
  
	//Steyr AUG
	ham_strip_weapon(idUser,"weapon_aug");
  
	//Sig SG-552 Commando
	ham_strip_weapon(idUser,"weapon_sg552");
  
	//Steyr Scout
	ham_strip_weapon(idUser,"weapon_scout");
  
	//AI Arctic Warfare/Magnum
	ham_strip_weapon(idUser,"weapon_awp");
  
	//H&K G3/SG-1
	ham_strip_weapon(idUser,"weapon_g3sg1");
  
	//Sig SG-550 Sniper
	ham_strip_weapon(idUser,"weapon_sig550");
 
	//FN M249 Para
	ham_strip_weapon(idUser,"weapon_m249");
  
}

//Удаление всех пистолетов
public clVIP:fStripWpnSecondary(const idUser)
{
	//H&K USP .45 Tactical
	ham_strip_weapon(idUser,"weapon_usp");
	
	//Glock 18 Select Fire
	ham_strip_weapon(idUser,"weapon_glock18");
	
	//Desert Eagle .50 AE
	ham_strip_weapon(idUser,"weapon_deagle");
	
	//SIG P228
	ham_strip_weapon(idUser,"weapon_p228");
	
	//Dual Beretta 96G
	ham_strip_weapon(idUser,"weapon_elite");
	
	//FN Five-Seven
	ham_strip_weapon(idUser,"weapon_fiveseven");

}

//Сброс всех счетчиков на ограничение взятия предмета
public clVIP:fLimitItemVipOneRound(const idUser)
{
		
	arrIsItemVipOneRound[idUser][0] = 0;
	arrIsItemVipOneRound[idUser][1] = 0;
	arrIsItemVipOneRound[idUser][2] = 0;
	arrIsItemVipOneRound[idUser][3] = 0;
	arrIsItemVipOneRound[idUser][4] = 0;
	arrIsItemVipOneRound[idUser][5] = 0;
	arrIsItemVipOneRound[idUser][6] = 0;
	arrIsItemVipOneRound[idUser][7] = 0;
	arrIsItemVipOneRound[idUser][8] = 0;
	arrIsItemVipOneRound[idUser][9] = 0;
	arrIsItemVipOneRound[idUser][10] = 0;
	arrIsItemVipOneRound[idUser][11] = 0;
	arrIsItemVipOneRound[idUser][12] = 0;
	arrIsItemVipOneRound[idUser][13] = 0;
	arrIsItemVipOneRound[idUser][14] = 0;
	arrIsItemVipOneRound[idUser][15] = 0;
	arrIsItemVipOneRound[idUser][16] = 0;
	arrIsItemVipOneRound[idUser][17] = 0;
	arrIsItemVipOneRound[idUser][18] = 0;
	arrIsItemVipOneRound[idUser][19] = 0;
	arrIsItemVipOneRound[idUser][20] = 0;

}

