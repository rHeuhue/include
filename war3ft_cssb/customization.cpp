/*------------------------------------
Файл настройки мода
------------------------------------*/
//Инициализация массивов файла настройки
public cfInitArraysCustomFile()
{
	arrStrSoundRaceData = ArrayCreate(64, 1);		//Массив звуков для рас
	arrIntMultiXPHourData = ArrayCreate(1, 1);		//Массив часов в которые получают мульти опыт
	arrIntBlockNumRace = ArrayCreate(1, 1);			//Массив ограничения доступа к расам
	arrIntVipRace = ArrayCreate(1, 1);				//Массив определения VIP для расы
	arrIntLevelVipRace = ArrayCreate(1, 1);			//Массив определения уровня до момента блокировки доступа к расе если игрок не VIP
	arrStrMotdPathRace = ArrayCreate(254, 1);		//Массив MOTD путей
	arrStrFlagVipRace	 = ArrayCreate(254, 1);		//Массив определения флага VIP для расы
	arrStrFlagLevelVipRace = ArrayCreate(254, 1);	//Массив определения флага VIP для расы (по уровню)
}

//Загрузка файла настройки
public cfLoadCustomizationFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	cfInitArraysCustomFile();

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_CUSTOMIZATION_FILE);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load war3ft customization file %s!", szPath);
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
			case SECTION_BASE_OPTIONS:
			{
				if (equal(szKey, "BASE_SHOWBAR_RACE"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrPointShowBarRace))
							arrPointShowBarRace[iCount] = str_to_float(szKey);

						iCount++;
					}
				}
				else if (equal(szKey, "BASE_MIN_ULT_LEVEL"))
					iMinUltLevel = str_to_num(szValue);
				else if (equal(szKey, "BASE_INVIS_PARACHUTE"))
					iInvisParachute = str_to_num(szValue);
				else if (equal(szKey, "BASE_NECKLACE_CHARGES"))
					iBaseNecklaceCharges = str_to_num(szValue);
				else if (equal(szKey, "BASE_HELM_CHARGES"))
					iBaseHelmCharges = str_to_num(szValue);

			}
			case SECTION_SOUND_RACES:
			{
				if (equal(szKey, "SOUND_ON_OFF"))
					iSoundRaceOnOff = str_to_num(szValue);
				else if (equal(szKey, "SOUND_UNDEAD"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_HUMAN"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_ORC"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_NIGHTELF"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_BLOODMAGE"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_SHADOWHUNTER"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_WARDEN"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_CRYPTLORD"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_CHAMELEON"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_FROST"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_DEATH_KNIGHT"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_BLACK_MAG"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_ALCHEMIST"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_PRIEST"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_ROGUE"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_DRUID"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_BLOODSEEKER"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_JUGGERNAUT"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_SNIPER"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_DISRUPTOR"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_RAZOR"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_WARLOCK"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_SHADOW_FIEND"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_24"))
					ArrayPushString(arrStrSoundRaceData, szValue);
				else if (equal(szKey, "SOUND_25"))
					ArrayPushString(arrStrSoundRaceData, szValue);
		
			}
			case SECTION_LOOT_ITEMS:
			{
				if (equal(szKey, "LOOT_MODELITEMS"))
					copy(szModelItems, charsmax(szModelItems), szValue);
				else if (equal(szKey, "LOOT_MODELARXPHPITEMS"))
					copy(szModelArXpHpItems, charsmax(szModelArXpHpItems), szValue);
				else if (equal(szKey, "LOOT_SPRITEITEMS"))
					copy(szSpriteItems, charsmax(szSpriteItems), szValue);
				else if (equal(szKey, "LOOT_SPRITENOITEMS"))
					copy(szSpriteNoItems, charsmax(szSpriteNoItems), szValue);
				else if (equal(szKey, "LOOT_ITEMS_RGB"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrColorItemsRGB))
							arrColorItemsRGB[iCount] = str_to_num(szKey);

						iCount++;
					}
				}
				else if (equal(szKey, "LOOT_NOITEMS_RGB"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(arrColorNoItemsRGB))
							arrColorNoItemsRGB[iCount] = str_to_num(szKey);

						iCount++;
					}
				}
				else if (equal(szKey, "LOOT_ICONDELAYLOOTITEMS"))
					fIconUpdateLootItems = str_to_float(szValue)
				 
			}
			case SECTION_BLOCK_NUMBER_RACE:
			{
				if (equal(szKey, "NUM_RACE_ON_OFF"))
					iNumRaceOnOff = str_to_num(szValue);
				else if (equal(szKey, "NUM_RACE_UNDEAD"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_HUMAN"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_ORC"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_NIGHTELF"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_BLOODMAGE"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_SHADOWHUNTER"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_WARDEN"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_CRYPTLORD"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_CHAMELEON"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_FROST"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_DEATH_KNIGHT"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_BLACK_MAG"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_ALCHEMIST"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_PRIEST"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_ROGUE"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_DRUID"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_BLOODSEEKER"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_JUGGERNAUT"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_SNIPER"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_DISRUPTOR"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_RAZOR"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_WARLOCK"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_SHADOW_FIEND"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_24"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				else if (equal(szKey, "NUM_RACE_25"))
					ArrayPushCell(arrIntBlockNumRace, str_to_num(szValue));
				
			}
			case SECTION_VIP_RACE:
			{
				if (equal(szKey, "VIP_RACE_UNDEAD") ||
					equal(szKey, "VIP_RACE_HUMAN") ||
					equal(szKey, "VIP_RACE_ORC") ||
					equal(szKey, "VIP_RACE_NIGHTELF") ||
					equal(szKey, "VIP_RACE_BLOODMAGE") ||
					equal(szKey, "VIP_RACE_SHADOWHUNTER") ||
					equal(szKey, "VIP_RACE_WARDEN") ||
					equal(szKey, "VIP_RACE_CRYPTLORD") ||
					equal(szKey, "VIP_RACE_CHAMELEON") ||
					equal(szKey, "VIP_RACE_FROST") ||
					equal(szKey, "VIP_RACE_DEATH_KNIGHT") ||
					equal(szKey, "VIP_RACE_BLACK_MAG") ||
					equal(szKey, "VIP_RACE_ALCHEMIST") ||
					equal(szKey, "VIP_RACE_PRIEST") ||
					equal(szKey, "VIP_RACE_ROGUE") ||
					equal(szKey, "VIP_RACE_DRUID") ||
					equal(szKey, "VIP_RACE_BLOODSEEKER") ||
					equal(szKey, "VIP_RACE_JUGGERNAUT") ||
					equal(szKey, "VIP_RACE_SNIPER") ||
					equal(szKey, "VIP_RACE_DISRUPTOR") ||
					equal(szKey, "VIP_RACE_RAZOR") ||
					equal(szKey, "VIP_RACE_WARLOCK") ||
					equal(szKey, "VIP_RACE_SHADOW_FIEND") ||
					equal(szKey, "VIP_RACE_24") ||
					equal(szKey, "VIP_RACE_25")
				)
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);

						if(iCount == 0)
							ArrayPushCell(arrIntVipRace, str_to_num(szKey));
						else if(iCount == 1)
							ArrayPushString(arrStrFlagVipRace, szKey);

						iCount++;

						//log_amx( "arrStrFlagVipRace '%s'", szKey);
					}
				}
				
			}
			case SECTION_LEVEL_VIP_RACE:
			{
				if (equal(szKey, "LEVEL_RACE_UNDEAD") ||
					equal(szKey, "LEVEL_RACE_HUMAN") ||
					equal(szKey, "LEVEL_RACE_ORC") ||
					equal(szKey, "LEVEL_RACE_NIGHTELF") ||
					equal(szKey, "LEVEL_RACE_BLOODMAGE") ||
					equal(szKey, "LEVEL_RACE_SHADOWHUNTER") ||
					equal(szKey, "LEVEL_RACE_WARDEN") ||
					equal(szKey, "LEVEL_RACE_CRYPTLORD") ||
					equal(szKey, "LEVEL_RACE_CHAMELEON") ||
					equal(szKey, "LEVEL_RACE_FROST") ||
					equal(szKey, "LEVEL_RACE_DEATH_KNIGHT") ||
					equal(szKey, "LEVEL_RACE_BLACK_MAG") ||
					equal(szKey, "LEVEL_RACE_ALCHEMIST") ||
					equal(szKey, "LEVEL_RACE_PRIEST") ||
					equal(szKey, "LEVEL_RACE_ROGUE") ||
					equal(szKey, "LEVEL_RACE_DRUID") ||
					equal(szKey, "LEVEL_RACE_BLOODSEEKER") ||
					equal(szKey, "LEVEL_RACE_JUGGERNAUT") ||
					equal(szKey, "LEVEL_RACE_SNIPER") ||
					equal(szKey, "LEVEL_RACE_DISRUPTOR") ||
					equal(szKey, "LEVEL_RACE_RAZOR") ||
					equal(szKey, "LEVEL_RACE_WARLOCK") ||
					equal(szKey, "LEVEL_RACE_SHADOW_FIEND") ||
					equal(szKey, "LEVEL_RACE_24") ||
					equal(szKey, "LEVEL_RACE_25")
				)
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount == 0)
							ArrayPushCell(arrIntLevelVipRace, str_to_num(szKey));
						else if(iCount == 1)
							ArrayPushString(arrStrFlagLevelVipRace, szKey);

						iCount++;
					}
				}				
			}
			case SECTION_MOTD_RACES:
			{
				if (equal(szKey, "MOTD_RACE_ON_OFF"))
					iMotdRaceOnOff = str_to_num(szValue);
				else if (equal(szKey, "MOTD_RACE_UNDEAD"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_HUMAN"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_ORC"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_NIGHTELF"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_BLOODMAGE"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_SHADOWHUNTER"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_WARDEN"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_CRYPTLORD"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_CHAMELEON"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_FROST"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_DEATH_KNIGHT"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_BLACK_MAG"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_ALCHEMIST"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_PRIEST"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_ROGUE"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_DRUID"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_BLOODSEEKER"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_JUGGERNAUT"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_SNIPER"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_DISRUPTOR"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_RAZOR"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_WARLOCK"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_SHADOW_FIEND"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_24"))
					ArrayPushString(arrStrMotdPathRace, szValue);
				else if (equal(szKey, "MOTD_RACE_25"))
					ArrayPushString(arrStrMotdPathRace, szValue);
		
			}
			case SECTION_MULTI_XP_HOUR:
			{
				if (equal(szKey, "MULTI_XP_ON_OFF"))
					iMultiXPOnOff = str_to_num(szValue);
				else if (equal(szKey, "BONUS_FACTOR_XP"))
					iBonusFactorXP = str_to_num(szValue);
				else if (equal(szKey, "HOUR_0"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_1"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_2"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_3"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_4"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_5"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_6"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_7"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_8"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_9"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_10"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_11"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_12"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_13"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_14"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_15"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_16"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_17"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_18"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_19"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_20"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_21"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_22"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
				else if (equal(szKey, "HOUR_23"))
					ArrayPushCell(arrIntMultiXPHourData, str_to_num(szValue));
			}
			case SECTION_RACE_UNDEAD:
			{
				if (equal(szKey, "EXPLOSION_MAX_DAMAGE"))
					iExplosionMaxDamage = str_to_num(szValue);
				else if (equal(szKey, "EXPLOSION_RANGE"))
					iExplosionRange = str_to_num(szValue);
				else if (equal(szKey, "EXPLOSION_BLAST_RADIUS"))
					iExplosionBlastRadius = str_to_num(szValue);
			}
			case SECTION_RACE_HUMAN:
			{
				if (equal(szKey, "BLINK_COOLDOWN"))
					fBlinkCooldown = str_to_float(szValue);
				else if (equal(szKey, "BASH_GLOW_INTENSITY"))
					iBashGlowIntensity = str_to_num(szValue);
				else if (equal(szKey, "BASH_HOLD_TIME"))
					fBashHoldTime = str_to_float(szValue);
			}
			case SECTION_RACE_ORC:
			{
				if (equal(szKey, "CHAINLIGHTNING_DAMAGE"))
					iChainLightningDamage = str_to_num(szValue);
				else if (equal(szKey, "CHAINLIGHTNING_LINEWIDTH"))
					iChainLightningLineWidth = str_to_num(szValue);
				else if (equal(szKey, "CHAINLIGHTNING_COLOR_RGB"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(colorOrcLightningRGB))
							colorOrcLightningRGB[iCount] = str_to_num(szKey);

						//log_amx("szKey: %s | szValue: %s",szKey,szValue);
						iCount++;
					}
				}
				else if (equal(szKey, "CRITICAL_STRIKE_CHANCE"))
					fCriticalStrikeChance = str_to_float(szValue);
								
			}
			case SECTION_RACE_ELF:
			{
				if (equal(szKey, "ENTANGLE_TIME"))
					fEntangleTime = str_to_float(szValue);
				else if (equal(szKey, "ENTANGLE_COLOR_RGB"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(colorElfEntangleRGB))
							colorElfEntangleRGB[iCount] = str_to_num(szKey);
						
						iCount++;
					}
				}
			}
			case SECTION_RACE_BLOOD:
			{
				if (equal(szKey, "IMMOLATE_DAMAGE"))
					iImmolateDamage = str_to_num(szValue);
				else if (equal(szKey, "IMMOLATE_DOT_DAMAGE"))
					iImmolateDotDamage = str_to_num(szValue);
				else if (equal(szKey, "IMMOLATE_DOT"))
					iImmolateDot = str_to_num(szValue);
				else if (equal(szKey, "BANISH_DAMAGE"))
					iBanishDamage = str_to_num(szValue);
				else if (equal(szKey, "BANISH_HOLDTIME"))
					fBanishHoldTime = str_to_float(szValue);
			}
			case SECTION_RACE_SHADOW:
			{
				if (equal(szKey, "SH_HEX_LENGTH"))
					fShHexLength = str_to_float(szValue);
				else if (equal(szKey, "SH_HEX_SPEED"))
					fShHexSpeed = str_to_float(szValue);
				else if (equal(szKey, "SH_HEALING_WAVE_RANGE"))
					iShHealingWaveRange = str_to_num(szValue);
				else if (equal(szKey, "SH_HEALING_WAVE_HEALTH"))
					iShHealingWaveHealth = str_to_num(szValue);
				else if (equal(szKey, "SH_BIGBADVOODOO_DURATION"))
					iShBigBadVoodooDuration = str_to_num(szValue);
				else if (equal(szKey, "SH_CONCOCTION_DAMAGE"))
					iShConcoctionDamage = str_to_num(szValue);
				else if (equal(szKey, "SH_CONCOCTION_RADIUS"))
					iShConcoctionRadius = str_to_num(szValue);
				else if (equal(szKey, "SH_SERPENTWARD_DAMAGE"))
					iShSerpentWardDamage = str_to_num(szValue);
				else if (equal(szKey, "SERPENTWARD_T_COLOR_RGB"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(colorSerpentWardRGB_T))
							colorSerpentWardRGB_T[iCount] = str_to_num(szKey);
						
						iCount++;
					}
				}
				else if (equal(szKey, "SERPENTWARD_CT_COLOR_RGB"))
				{
					iCount = 0;
					while (szValue[0] != 0 && strtok(szValue, szKey, charsmax(szKey), szValue, charsmax(szValue), ' '))
					{
						trim(szKey);
						trim(szValue);
						
						if(iCount < sizeof(colorSerpentWardRGB_CT))
							colorSerpentWardRGB_CT[iCount] = str_to_num(szKey);
						
						iCount++;
					}
				}
			}
			case SECTION_RACE_WARDEN:
			{
				if (equal(szKey, "VENGEANCE_HEALTH"))
					iVengeanceHealth = str_to_num(szValue);
				else if (equal(szKey, "SHADOWSTRIKE_DAMAGE"))
					iShadowStrikeDamage = str_to_num(szValue);
			}
			case SECTION_RACE_CRYPT:
			{
				if (equal(szKey, "LOCUSTSWARM_DMG_MIN"))
					iLocustSwarmDmgMin = str_to_num(szValue);
				else if (equal(szKey, "LOCUSTSWARM_DMG_MAX"))
					iLocustSwarmDmgMax = str_to_num(szValue);
				else if (equal(szKey, "CARRIONBEETLE_DAMAGE"))
					iCarrionBeetleDamage = str_to_num(szValue);
				else if (equal(szKey, "IMPALE_TYPE"))
					iImpaleType = str_to_num(szValue);
				else if (equal(szKey, "ORB_DAMAGE"))
					iOrbDamage = str_to_num(szValue);

				
			}
			case SECTION_RACE_FROST_MAGE:
			{
				if (equal(szKey, "DAMAGE_BLIZZARD"))
					iDamageBlizzard = str_to_num(szValue);
				else if (equal(szKey, "DAMAGE_ICE_BOLT"))
					iDamageIceBolt = str_to_num(szValue);
				else if (equal(szKey, "DAMAGE_BLIZZARD_RADIUS"))
					iDamageBlizzardRadius = str_to_num(szValue);
			}
			case SECTION_RACE_DEATH_KNIGHT:
			{
				if (equal(szKey, "DEATH_KNIGHT_UNARMOR_CHANCE"))
					fUnarmorChance = str_to_float(szValue);
				else if (equal(szKey, "DEATH_KNIGHT_DK_CHANCE"))
					fDeathCoilChance = str_to_float(szValue);
				else if (equal(szKey, "DEATH_KNIGHT_PERCENT_HP"))
					fPercentHP = str_to_float(szValue);
				else if (equal(szKey, "DEATH_KNIGHT_PERCENT_ARMOR"))
					fPercentArmor = str_to_float(szValue);
				else if (equal(szKey, "DEATH_KNIGHT_PERCENT_UNDAMAGE"))
					fPercentUndamage = str_to_float(szValue);
				else if (equal(szKey, "DEATH_KNIGHT_CONTROLUNDEAD_CHANCE"))
					fControlUndeadChance = str_to_float(szValue);
				else if (equal(szKey, "DEATH_KNIGHT_CONTROLUNDEAD_HP"))
					fControlUndeadHP = str_to_float(szValue);
				else if (equal(szKey, "DEATH_KNIGHT_CONTROLUNDEAD_EXP"))
					fControlUndeadExp = str_to_float(szValue);
				else if (equal(szKey, "DEATH_KNIGHT_MAX_HP_VICTIM"))
					iMaxHPVictim = str_to_num(szValue);
				
			}
			case SECTION_RACE_BLACK_MAG:
			{
				if (equal(szKey, "BLACK_MAG_MAX_NUM_DISK"))
					iMaxNumDisk = str_to_num(szValue);
				else if (equal(szKey, "BLACK_MAG_DMG_DISK"))
					iDiskDmg = str_to_num(szValue);
				else if (equal(szKey, "BLACK_MAG_BLACKSTRIKE_DAMAGE"))
					iBlackStrikeDmg = str_to_num(szValue);
			}
			case SECTION_RACE_ALCHEMIST:
			{
				if (equal(szKey, "AL_POISON_DAMAGE"))
					iAlPoisonDamage = str_to_num(szValue);
				else if (equal(szKey, "AL_POISON_NUMBER"))
					iAlPoisonNumber = str_to_num(szValue);
				else if (equal(szKey, "AL_POISON_TIME"))
					fAlPoisonTime = str_to_float(szValue);
				else if (equal(szKey, "AL_FROST_SPEED"))
					fAlFrostSpeed = str_to_float(szValue);
				else if (equal(szKey, "AL_FROST_HOLD_TIME"))
					fAlFrostHoldTime = str_to_float(szValue);
			}
			case SECTION_RACE_PRIEST:
			{
				if (equal(szKey, "PRIEST_ENTRY_FREQUENCY"))
					fEntryFrequency = str_to_float(szValue);
				else if (equal(szKey, "PRIEST_FIREDURATION"))
					fFireDuration = str_to_float(szValue);
				else if (equal(szKey, "PRIEST_FIREDAMAGE"))
					fFireDamage = str_to_float(szValue);
				else if (equal(szKey, "PRIEST_FIRE_SLOWDOWN"))
					fFireSlowdown = str_to_float(szValue);
				else if (equal(szKey, "PRIEST_FIRE_NUM_AMMO"))
					iFireNumAmmo = str_to_num(szValue);
				else if (equal(szKey, "PRIEST_BALL_EXP_RADIUS"))
					fBallExpRadius = str_to_float(szValue);
				else if (equal(szKey, "PRIEST_WORDDEATH_DMG"))
					iWordDeathDmg = str_to_num(szValue);
				else if (equal(szKey, "PRIEST_BLOCKULTRADIUS"))
					fBlockUltRadius = str_to_float(szValue);

			}
			case SECTION_RACE_ROGUE:
			{
				if (equal(szKey, "ROGUE_SHURIKEN_DMG"))
					fShurikenDmg = str_to_float(szValue);
				else if (equal(szKey, "ROGUE_SHURIKEN_RADIUS_EXP"))
					fShurikenRadiusExp = str_to_float(szValue);
				else if (equal(szKey, "ROGUE_SHURIKEN_BEAM_RADIUS"))
					fShurikenBeamRadius = str_to_float(szValue);
				else if (equal(szKey, "ROGUE_SHURIKEN_BEAM_DMG"))
					fShurikenBeamDmg = str_to_float(szValue);
				else if (equal(szKey, "ROGUE_CHARGE_MAX_1"))
					iRogueChargeMax_1 = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_CHARGE_MAX_2"))
					iRogueChargeMax_2 = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_CHARGE_MAX_3"))
					iRogueChargeMax_3 = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_CHARGE_MIN_1"))
					iRogueChargeMin_1 = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_CHARGE_MIN_2"))
					iRogueChargeMin_2 = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_CHARGE_MIN_3"))
					iRogueChargeMin_3 = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_COUNT_1"))
					iRogueCount_1 = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_COUNT_2"))
					iRogueCount_2 = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_COUNT_3"))
					iRogueCount_3 = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_SSTRIKE_SECONDARY"))
					iSStrike_Secondary = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_SSTRIKE_PRIMARY"))
					iSStrike_Primary = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_SSTRIKE_KNIFE"))
					iSStrike_Knife = str_to_num(szValue);
				else if (equal(szKey, "ROGUE_SSTRIKE_GRENADE"))
					iSStrike_Grenade = str_to_num(szValue);
			}

			case SECTION_RACE_DRUID:
			{
				if (equal(szKey, "DRUID_CHARGE_MAX_1"))
					iDruidChargeMax_1 = str_to_num(szValue);
				else if (equal(szKey, "DRUID_CHARGE_MAX_2"))
					iDruidChargeMax_2 = str_to_num(szValue);
				else if (equal(szKey, "DRUID_CHARGE_MAX_3"))
					iDruidChargeMax_3 = str_to_num(szValue);
				else if (equal(szKey, "DRUID_CHARGE_MIN_1"))
					iDruidChargeMin_1 = str_to_num(szValue);
				else if (equal(szKey, "DRUID_CHARGE_MIN_2"))
					iDruidChargeMin_2 = str_to_num(szValue);
				else if (equal(szKey, "DRUID_CHARGE_MIN_3"))
					iDruidChargeMin_3 = str_to_num(szValue);
				else if (equal(szKey, "DRUID_COUNT_1"))
					iDruidCount_1 = str_to_num(szValue);
				else if (equal(szKey, "DRUID_COUNT_2"))
					iDruidCount_2 = str_to_num(szValue);
				else if (equal(szKey, "DRUID_COUNT_3"))
					iDruidCount_3 = str_to_num(szValue);
				else if (equal(szKey, "DRUID_RADIUS_SPAWN_WILD"))
					fRadiusSpawnWild = str_to_float(szValue);
				else if (equal(szKey, "DRUID_WILD_HEALTH_ENT"))
					fWildHpEnt = str_to_float(szValue);
				else if (equal(szKey, "DRUID_WILD_HEALTH_HEAL"))
					fWildHpHeal = str_to_float(szValue);
				else if (equal(szKey, "DRUID_WILD_HEALTH_EXP"))
					fWildHpExp = str_to_float(szValue);
				else if (equal(szKey, "DRUID_WILD_EXPLODE_DMG"))
					fWildExplodeDmg = str_to_float(szValue);
				else if (equal(szKey, "DRUID_WILD_HEALING_HP"))
					fWildHealingHp = str_to_float(szValue);
				else if (equal(szKey, "DRUID_WILD_RADIUS_DMG"))
					fWildRadiusDmg = str_to_float(szValue);
				else if (equal(szKey, "DRUID_ASTRAL_STORM_DMG"))
					fAStormDmg = str_to_float(szValue);
				else if (equal(szKey, "DRUID_ASTRAL_STORM_RADIUS_DMG"))
					fAStormRadiusDmg = str_to_float(szValue);
				else if (equal(szKey, "DRUID_ASTORM_SMALL_DMG"))
					fAstormSmallDmg = str_to_float(szValue);
				else if (equal(szKey, "DRUID_ASTORM_SMALL_RADIUS_DMG"))
					fAstormSmallRadDmg = str_to_float(szValue);
				else if (equal(szKey, "DRUID_SHANCEMANGLE"))
					fShanceMangle = str_to_float(szValue);
				else if (equal(szKey, "DRUID_SHANCEMANGLEDMG"))
					iShanceMangleDmg = str_to_num(szValue);

			}
			case SECTION_RACE_BLOODSEEKER:
			{
				if (equal(szKey, "BLOODSEEKER_CHARGE_MAX_1"))
					iBloodseekerChargeMax_1 = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_CHARGE_MAX_2"))
					iBloodseekerChargeMax_2 = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_CHARGE_MAX_3"))
					iBloodseekerChargeMax_3 = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_CHARGE_MIN_1"))
					iBloodseekerChargeMin_1 = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_CHARGE_MIN_2"))
					iBloodseekerChargeMin_2 = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_CHARGE_MIN_3"))
					iBloodseekerChargeMin_3 = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_COUNT_1"))
					iBloodseekerCount_1 = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_COUNT_2"))
					iBloodseekerCount_2 = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_COUNT_3"))
					iBloodseekerCount_3 = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_BLOOD_RITE_DMG"))
					iBloodRiteDmg = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_BLOODY_MADNESS_DMG"))
					fBloodyMadnessDmg = str_to_float(szValue);
				else if (equal(szKey, "BLOODSEEKER_BLOODY_MADNESS_HP"))
					fBloodyMadnessHp = str_to_float(szValue);
				else if (equal(szKey, "BLOODSEEKER_VENDETTA_DMG_NUM"))
					iNumVendettaDMG = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_VENDETTA_DMG"))
					iVendettaDmg = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_BLOOD_RAGE_DMG"))
					iBloodRageDmg = str_to_num(szValue);
				else if (equal(szKey, "BLOODSEEKER_BLOOD_RAGE_SPEED_FACTOR"))
					fBloodRageSpeedFactor = str_to_float(szValue);
				else if (equal(szKey, "BLOODSEEKER_BLOOD_BATH_HP_FACTOR"))
					fBloodBathHpFactor = str_to_float(szValue);

			}
			case SECTION_RACE_JUGGERNAUT:
			{
				if (equal(szKey, "JUGGERNAUT_CHARGE_MAX_1"))
					iJuggernautChargeMax_1 = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_CHARGE_MAX_2"))
					iJuggernautChargeMax_2 = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_CHARGE_MAX_3"))
					iJuggernautChargeMax_3 = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_CHARGE_MIN_1"))
					iJuggernautChargeMin_1 = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_CHARGE_MIN_2"))
					iJuggernautChargeMin_2 = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_CHARGE_MIN_3"))
					iJuggernautChargeMin_3 = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_COUNT_1"))
					iJuggernautCount_1 = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_COUNT_2"))
					iJuggernautCount_2 = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_COUNT_3"))
					iJuggernautCount_3 = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_HEALING_WARD_RADIUS"))
					fHealingWardRadius = str_to_float(szValue);
				else if (equal(szKey, "JUGGERNAUT_HEALING_WARD_NUM_HEALTH"))
					iHealingWardNumHealth = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_HEALING_WARD_FREQUENCY"))
					fHealingWardFrequency = str_to_float(szValue);
				else if (equal(szKey, "JUGGERNAUT_BLADE_CRITICAL_DMG"))
					fBladeCriticalDmg = str_to_float(szValue);
				else if (equal(szKey, "JUGGERNAUT_CHANSE_DEMON_BLADE"))
					fChanseDemonBlade = str_to_float(szValue);
				else if (equal(szKey, "JUGGERNAUT_BLADE_DEMON_ARMOR"))
					iBladeDemonArmor = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_BLADE_DEMON_HP"))
					iBladeDemonHP = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_CHANSE_BLADE_DANCE"))
					fChanseBladeDance = str_to_float(szValue);
				else if (equal(szKey, "JUGGERNAUT_PERCENT_DMG_BLADE_DANCE"))
					iBladeDancePercentDmg = str_to_num(szValue);
				else if (equal(szKey, "JUGGERNAUT_WARD_HP"))
					fWardHp = str_to_float(szValue);
				
			}
			case SECTION_RACE_SNIPER:
			{
				if (equal(szKey, "SNIPER_HEADSHOT_RADIUS"))
					iSniperHeadshotRadius = str_to_num(szValue);
				else if (equal(szKey, "SNIPER_HEADSHOT_DMG"))
					iSniperHeadshotDmg = str_to_num(szValue);
				else if (equal(szKey, "SNIPER_SHRAPNEL_DMG"))
					iShrapnelDmg = str_to_num(szValue);
				else if (equal(szKey, "SNIPER_SHRAPNEL_DMG_EXP"))
					iShrapnelDmgExp = str_to_num(szValue);
				else if (equal(szKey, "SNIPER_SHRAPNEL_EXP_RADIUS"))
					fShrapnelExpRadius = str_to_float(szValue);
				else if (equal(szKey, "SNIPER_SHRAPNEL_NUM_JUMP"))
					iShrapnelNumJump = str_to_num(szValue);
				else if (equal(szKey, "SNIPER_ROUNDCOUNT_AWP"))
					iRoundCountAwp = str_to_num(szValue);
			}
			case SECTION_RACE_DISRUPTOR:
			{
				if (equal(szKey, "DISRUPTOR_GLIMPSE_DMG"))
					iDisruptorGlimpseDmg = str_to_num(szValue);
				else if (equal(szKey, "DISRUPTOR_THUNDERSTRIKE_DMG_1"))
					iDisruptorThunderStrikeDmg_1 = str_to_num(szValue);
				else if (equal(szKey, "DISRUPTOR_THUNDERSTRIKE_DMG_2"))
					iDisruptorThunderStrikeDmg_2 = str_to_num(szValue);
				else if (equal(szKey, "DISRUPTOR_THUNDERSTRIKE_RADIUS"))
					iDisruptorThunderStrikeRadius = str_to_num(szValue);
				else if (equal(szKey, "DISRUPTOR_STATIC_STORM_DMG"))
					iDisruptorStaticStormDmg = str_to_num(szValue);
				else if (equal(szKey, "DISRUPTOR_STATIC_STORM_RADIUS"))
					fDisruptorStaticStormRadius = str_to_float(szValue);
			}
			case SECTION_RACE_RAZOR:
			{
				if (equal(szKey, "RAZOR_UNSTABLE_CURRENT_DMG"))
					iUnstableCurrentDmg = str_to_num(szValue);
				else if (equal(szKey, "RAZOR_MANA_CHANCE"))
					fManaChance = str_to_float(szValue);
				else if (equal(szKey, "RAZOR_MANA_RADIUS"))
					iManaRadius = str_to_num(szValue);
				else if (equal(szKey, "RAZOR_MANA_HP"))
					iManaHP = str_to_num(szValue);
				else if (equal(szKey, "RAZOR_PLASMA_FIELD_NUM_TOUCH"))
					iPlasmaFieldNumTouch = str_to_num(szValue);
				else if (equal(szKey, "RAZOR_PLASMA_FIELD_RADIUS"))
					fPlasmaFieldRadius = str_to_float(szValue);
				else if (equal(szKey, "RAZOR_PLASMA_FIELD_DMG"))
					iPlasmaFieldDmg = str_to_num(szValue);
			}
			case SECTION_RACE_WARLOCK:
			{
				if (equal(szKey, "WARLOCK_FATAL_BONDS_DMG"))
					iFatalBondsDmg = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_FATAL_BONDS_RADIUS"))
					iFatalBondsRadius = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_SHADOW_WORD_NUM"))
					iShadowWordNum = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_SHADOW_WORD_TIME"))
					iShadowWordTime = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_SHADOW_WORD_RADIUS"))
					iShadowWordRadius = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_SHADOW_WORD_DMG"))
					iShadowWordDmg = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_SHADOW_WORD_HP"))
					iShadowWordHp = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_FLAMING_FISTS_NUM"))
					iFflamingFistsNum = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_FLAMING_FISTS_DMG"))
					iFlamingFistsDmg = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_PERM_IMMOLATION_DMG"))
					iPermImmolationDmg = str_to_num(szValue);
				else if (equal(szKey, "WARLOCK_PERM_IMMOLATION_RADIUS"))
					fPermImmolationRadius = str_to_float(szValue);
			}
			case SECTION_RACE_SHADOW_FIEND:
			{
				if (equal(szKey, "SHADOW_FIEND_PRESENCE_RADIUS"))
					iPresenceRadius = str_to_num(szValue);
				else if (equal(szKey, "SHADOW_FIEND_PRESENCE_ARMOR"))
					iPresenceArmor = str_to_num(szValue);
				else if (equal(szKey, "SHADOW_FIEND_REQUIEM_SOULS_NUM"))
					iRequiemSoulsNum = str_to_num(szValue);
				else if (equal(szKey, "SHADOW_FIEND_REQUIEM_SOULS_TIME"))
					iRequiemSoulsTime = str_to_num(szValue);
				else if (equal(szKey, "SHADOW_FIEND_REQUIEM_SOULS_DMG"))
					iRequiemSoulsDmg = str_to_num(szValue);
				else if (equal(szKey, "SHADOW_FIEND_NECROMASTERY_NUM"))
					iNecromasteryNum = str_to_num(szValue);
				else if (equal(szKey, "SHADOW_FIEND_NECROMASTERY_HP"))
					iNecromasteryHP = str_to_num(szValue);
				else if (equal(szKey, "SHADOW_FIEND_CRY_HEART_DMG"))
					iCryHeartDmg = str_to_num(szValue);
				
			}
			case SECTION_RACE_24:
			{
			}
			case SECTION_RACE_25:
			{
			}
			
		}//switch (iSection)
	}

	if (fileWar3ftmod_ini) fclose(fileWar3ftmod_ini)

}