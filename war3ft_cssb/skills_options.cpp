/*
*	Конфигурационный файл настроек скилов мода CSSB Warcraft 3 Frozen Throne Private
*/

//Инициализация массивов настройки файла skills_options.ini
public fInitArraysSkillsFile()
{
//*******************************************************
// Раса: Нежить (Race: Undead Scourge)
//*******************************************************
	arrVampiricAura = ArrayCreate(1, 1);			//[Скил 1 уровня - Аура вампира (Vampiric Aura) (float)]
	arrUnholyAura = ArrayCreate(1, 1);				//[Скил 2 уровня - Нечистая аура (Unholy Aura) (float)]
	arrLevitation = ArrayCreate(1, 1);				//[Скил 3 уровня - Полет (Levitation) (float)]

//*******************************************************
// Раса: Альянс Людей (Race: Human)
//*******************************************************
	arrInvisibility = ArrayCreate(1, 1);			//[Скил 1 уровня - Невидимость (Invisibility) (int)]
//	iDevotionAura;									//[Скил 2 уровня - Аура преданности (Devotion Aura) (int)]
	arrBash = ArrayCreate(1, 1);					//[Скил 3 уровня - Удар (Bash) (float)]

//*******************************************************
// Раса: Орда Орков (Race: Orc)
//*******************************************************
	arrCriticalStrike = ArrayCreate(1, 1);			//[Скил 1 уровня - Критический удар (Critical Strike) (float)]
	arrCriticalGrenade = ArrayCreate(1, 1);			//[Скил 2 уровня - Критические гранаты (Critical Grenade) (float)]
	arrEquipmentreincarnation = ArrayCreate(1, 1);	//[Скил 3 уровня - Восстановление оружия (Equipment Reincarnation) (float)]
//*******************************************************
// Раса: Ночные Эльфы (Race: Night Elf)
//*******************************************************
	arrEvasion = ArrayCreate(1, 1);					//[Скил 1 уровня - Уклонение (Evasion) (float)]
	arrThornsAura = ArrayCreate(1, 1);				//[Скил 2 уровня - Шипастая аура (Thorns Aura) (float)]
	arrTrueshotAura = ArrayCreate(1, 1);			//[Скил 3 уровня - Аура правдивости (Trueshot Aura) (float)]

//*******************************************************
// Раса: Кровавый Маг (Race: Blood Mage)
//*******************************************************
	arrPhoenix = ArrayCreate(1, 1);					//[Скил 1 уровня - Феникс (Phoenix) (float)]
	arrBanish = ArrayCreate(1, 1);					//[Скил 2 уровня - Изгнание (Banish) (float)]
	arrSiphonMana = ArrayCreate(1, 1);				//[Скил 3 уровня - Похищение брони (Siphon Mana) (float)]
	arrResistantSkin = ArrayCreate(1, 1);			//[Скил 4 уровня - Шипованая кожа (Resistant Skin) (float)]

//*******************************************************
// Раса: Призрачный Охотник (Race: Shadow Hunter)
//*******************************************************
	arrHealingWave = ArrayCreate(1, 1);				//[Скил 1 уровня - Волна жизни (Healing Wave) (float)]
	arrHex = ArrayCreate(1, 1);						//[Скил 2 уровня - Проклятье (Hex) (float)]
	arrSerpentWard = ArrayCreate(1, 1);				//[Скил 3 уровня - Змеиная суть (Serpent Ward) (int)]
	arrUnstableConcoction = ArrayCreate(1, 1);		//[Скил 4 уровня - Неустойчивый концентрат (Unstable Concoction) (float)]

//*******************************************************
// Раса: Шпион (Race: Warden)
//*******************************************************
	arrFanOfKnives = ArrayCreate(1, 1);				//[Скил 1 уровня - Веселье клинков (Fan of Knives) (float)]
	arrBlink = ArrayCreate(1, 1);					//[Скил 2 уровня - Потеря концентрации (Blink) (float)]
	arrShadowStrike = ArrayCreate(1, 1);			//[Скил 3 уровня - Скрытый удар (Shadow Strike) (float)]
	arrHardenedSkin = ArrayCreate(1, 1);			//[Скил 4 уровня - Закаленная кожа (Hardened Skin) (float)]

//*******************************************************
// Раса: Лорд Мертвых (Race: Crypt Lord)
//*******************************************************
	arrImpale = ArrayCreate(1, 1);					//[Скил 1 уровня - Запутывание (Impale) (float)]
	arrSpikedCarapace = ArrayCreate(1, 1);			//[Скил 2 уровня - Шипованая броня (Spiked Carapace) (float)]
	arrCarrionBeetle = ArrayCreate(1, 1);			//[Скил 3 уровня - Трупоеды (Carrion Beetles) (float)]
	arrOrbOfAnnihilation = ArrayCreate(1, 1);		//[Скил 4 уровня - Сфера уничтожения (Orb of Annihilation) (float)]

//*******************************************************
// Раса: Ледяной маг (Race: Ice magician)
//*******************************************************
	arrIceSplinters = ArrayCreate(1, 1);			//[Скил 1 уровня - Осколки льда (Ice splinters) (float)]	
	arrIceArrow = ArrayCreate(1, 1);				//[Скил 2 уровня - Ледяная стрела (Ice arrow) (float)]
	arrColdCone = ArrayCreate(1, 1);				//[Скил 3 уровня - Конус холода (Cold cone) (float)]

//*******************************************************
// Раса: Рыцарь смерти (Race: Death knight)
//*******************************************************
	arrUnbreakableArmor = ArrayCreate(1, 1);		//[Скил 1 уровня - Несокрушимая броня (Unbreakable Armor) (float)]
	arrBloodBoil = ArrayCreate(1, 1);				//[Скил 2 уровня - Вскипание крови (Blood Boil) (float)]
	arrDeathCoil = ArrayCreate(1, 1);				//[Скил 3 уровня - Лик смерти (Death Coil) (float)]

//*******************************************************
// Раса: Черный маг (Race: Black Mag)
//*******************************************************
	arrBlackStrike = ArrayCreate(1, 1);				//[Скил 1 уровня - Темный удар (Dark Blow) (float)]
	arrBlackShadow = ArrayCreate(1, 1);				//[Скил 2 уровня - Ужас (Horror) (float)]
	arrBlackPower = ArrayCreate(1, 1);				//[Скил 3 уровня - Черная сила (Black Force) (float)]

//*******************************************************
// Раса: Алхимик (Race: Alchemist)
//*******************************************************
	arrPoison = ArrayCreate(1, 1);					//[Скил 1 уровня - Колба отравы (Poison flask) (float)]
	arrShock = ArrayCreate(1, 1);					//[Скил 2 уровня - Сотрясение (Concussion) (float)]
	arrFrost = ArrayCreate(1, 1);					//[Скил 3 уровня - Ледяное дыхание (Ice breath) (float)]
	arrPassHypnosis = ArrayCreate(1, 1);			//[Скил 4 уровня - Гипноз (Hypnosis) (float)]

//*******************************************************
// Раса: Жрец (Race: Priest)
//*******************************************************
	arrEntryintochasm = ArrayCreate(1, 1);			//[Скил 1 уровня - Вхождение в бездну (Entry into a chasm) (float)]
	arrSacredFire = ArrayCreate(1, 1);				//[Скил 2 уровня - Священный огонь (Sacred fire) (float)]
	arrSpiritualAccuracy = ArrayCreate(1, 1);		//[Скил 3 уровня - Духовная меткость (Spiritual accuracy) (float)]
	arrMysticism = ArrayCreate(1, 1);				//[Скил 4 уровня - Мистицизм (Mysticism) (int)]

//*******************************************************
// Раса: Разбойник (Race: Rogue)
//*******************************************************
	arrSinisterStrike = ArrayCreate(1, 1);			//[Скил 1 уровня - Коварный удар (Sinister Strike) (float)]
	arrVanish = ArrayCreate(1, 1);					//[Скил 2 уровня - Исчезновение (Vanish) (float)]
	arrCripplingPoison = ArrayCreate(1, 1);			//[Скил 3 уровня - Калечащий яд (Crippling Poison) (float)]
//*******************************************************
// Раса: Друид (Race: Druid)
//*******************************************************
	arrWildEntanglement = ArrayCreate(1, 1);		//[Скил 1 уровня - Дикий гриб: Запутывание (Wild Mushroom: Entanglement) (float)]
	arrWildHealing = ArrayCreate(1, 1);				//[Скил 2 уровня - Дикий гриб: Исцеление (Wild Mushroom: Healing)(float)]
	arrWildExplode = ArrayCreate(1, 1);				//[Скил 3 уровня - Дикий гриб: Удар (Wild Mushroom: Explode) (float)]


//*******************************************************
// Раса: (Бладсикер) Кровавый искатель (Race: Bloodseeker)
//*******************************************************
	arrBloodRage = ArrayCreate(1, 1);
	arrBloodBath = ArrayCreate(1, 1);
	arrBloodRite = ArrayCreate(1, 1);

//*******************************************************
// Раса: Джагернаут (Race: Juggernaut)
//*******************************************************
	arrHealingWard = ArrayCreate(1, 1);
	arrCriticalBlade = ArrayCreate(1, 1);
	arrDemonBlade = ArrayCreate(1, 1);

//*******************************************************
// Раса: Снайпер (Race: Sniper)
//*******************************************************
	arrHeadshot = ArrayCreate(1, 1);
	arrPhaseBoots = ArrayCreate(1, 1);
	arrSkillShrapnelCharge = ArrayCreate(1, 1);

//*******************************************************
// Раса: Разрушитель (Race: Disruptor)
//*******************************************************
	arrGlimpse = ArrayCreate(1, 1);
	arrThunderStrike = ArrayCreate(1, 1);
	arrKineticField = ArrayCreate(1, 1);

//*******************************************************
// Раса: Блэйд (Race: Razor)
//*******************************************************
	arrEyeOfTheStorm = ArrayCreate(1, 1);
	arrStaticLink = ArrayCreate(1, 1);
	arrUnstableCurrent = ArrayCreate(1, 1);

//*******************************************************
// Раса: Варлок (Колдун) (Race: Warlock)
//*******************************************************
	arrFatalBonds = ArrayCreate(1, 1);
	arrShadowWord = ArrayCreate(1, 1);
	arrFlamingFists = ArrayCreate(1, 1);

//*******************************************************
// Раса: Невермор (Race: Shadow Fiend)
//*******************************************************
	arrPresenceDarkLord = ArrayCreate(1, 1);
	arrRequiemSouls = ArrayCreate(1, 1);
	arrCryHeart = ArrayCreate(1, 1);

//*******************************************************
// Раса: 24 (Race: 24)
//*******************************************************
//	arrSkill_1_24 = ArrayCreate(1, 1);
//	arrSkill_2_24 = ArrayCreate(1, 1);
//	arrSkill_3_24 = ArrayCreate(1, 1);

//*******************************************************
// Раса: 25 (Race: 25)
//*******************************************************
//	arrSkill_1_25 = ArrayCreate(1, 1);
//	arrSkill_2_25 = ArrayCreate(1, 1);
//	arrSkill_3_25 = ArrayCreate(1, 1);

}



//Загрузка файла настройки
public cfLoadSkillsFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	fInitArraysSkillsFile();

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_CUSTOM_FILE_SKILLS);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load skills options file %s!", szPath);
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
			case SECTION_MAX_LEVELS:
			{
				if (equal(szKey, "MAX_LEVELS"))
					iMaxLevels = str_to_num(szValue);
		
			}
			case SECTION_MAX_SKILL_LEVEL:
			{
				if (equal(szKey, "MAX_SKILL_LEVEL"))
					iMaxSkillLevel = str_to_num(szValue);
								
			}
			//Undead
			case SECTION_UNDEAD_SKILL1:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				//log_amx("szKey [%s] | szValueSkills [ %s ] | LVL [%s] | szValue [%s]",szKey,szValueSkills,szValueLVL,szValue);
				if (equal(szValueSkills, "UNDEAD_SKILL1_LVL"))
					ArrayPushCell(arrVampiricAura,str_to_float(szValue));
				
			}
			case SECTION_UNDEAD_SKILL2:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "UNDEAD_SKILL2_LVL"))
					ArrayPushCell(arrUnholyAura,str_to_float(szValue));
			}
			case SECTION_UNDEAD_SKILL3:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "UNDEAD_SKILL3_LVL"))
					ArrayPushCell(arrLevitation,str_to_float(szValue));
			}
			//Human
			case SECTION_HUMAN_SKILL1:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "HUMAN_SKILL1_LVL"))
					ArrayPushCell(arrInvisibility,str_to_num(szValue));
			
			}
			case SECTION_HUMAN_SKILL2:
			{
				if (equal(szKey, "HUMAN_SKILL2_DEVOTION_AURA"))
					iDevotionAura = str_to_num(szValue);
				
			}
			case SECTION_HUMAN_SKILL3:
			{
				if (equal(szKey, "HUMAN_SKILL3_MIN_PERCENT"))
					fHumanSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "HUMAN_SKILL3_MAX_PERCENT"))
					fHumanSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "HUMAN_SKILL3_LVL"))
					ArrayPushCell(arrBash,str_to_float(szValue));
			
			}
			//Orc
			case SECTION_ORC_SKILL1:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ORC_SKILL1_LVL"))
					ArrayPushCell(arrCriticalStrike,str_to_float(szValue));
			
			}
			case SECTION_ORC_SKILL2:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ORC_SKILL2_LVL"))
					ArrayPushCell(arrCriticalGrenade,str_to_float(szValue));				
				
			}
			case SECTION_ORC_SKILL3:
			{
				if (equal(szKey, "ORC_SKILL3_MIN_PERCENT"))
					fOrcSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ORC_SKILL3_MAX_PERCENT"))
					fOrcSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ORC_SKILL3_LVL"))
					ArrayPushCell(arrEquipmentreincarnation,str_to_float(szValue));
			
			}
			//Night Elf
			case SECTION_ELF_SKILL1:
			{
				if (equal(szKey, "ELF_SKILL1_MIN_PERCENT"))
					fElfSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ELF_SKILL1_MAX_PERCENT"))
					fElfSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ELF_SKILL1_LVL"))
					ArrayPushCell(arrEvasion,str_to_float(szValue));
			
			}
			case SECTION_ELF_SKILL2:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ELF_SKILL2_LVL"))
					ArrayPushCell(arrThornsAura,str_to_float(szValue));				
				
			}
			case SECTION_ELF_SKILL3:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ELF_SKILL3_LVL"))
					ArrayPushCell(arrTrueshotAura,str_to_float(szValue));
			
			}

			//Blood Mage
			case SECTION_BLOOD_MAGE_SKILL1:
			{
				if (equal(szKey, "BLOOD_MAGE_SKILL1_MIN_PERCENT"))
					fBloodMageSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "BLOOD_MAGE_SKILL1_MAX_PERCENT"))
					fBloodMageSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLOOD_MAGE_SKILL1_LVL"))
					ArrayPushCell(arrPhoenix,str_to_float(szValue));
			
			}
			case SECTION_BLOOD_MAGE_SKILL2:
			{
				if (equal(szKey, "BLOOD_MAGE_SKILL2_MIN_PERCENT"))
					fBloodMageSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "BLOOD_MAGE_SKILL2_MAX_PERCENT"))
					fBloodMageSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLOOD_MAGE_SKILL2_LVL"))
					ArrayPushCell(arrBanish,str_to_float(szValue));				
				
			}
			case SECTION_BLOOD_MAGE_SKILL3:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLOOD_MAGE_SKILL3_LVL"))
					ArrayPushCell(arrSiphonMana,str_to_float(szValue));
			
			}
			case SECTION_BLOOD_MAGE_SKILL4:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLOOD_MAGE_SKILL4_LVL"))
					ArrayPushCell(arrResistantSkin,str_to_float(szValue));
			
			}
			//Shadow Hunter
			case SECTION_HUNTER_SKILL1:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "HUNTER_SKILL1_LVL"))
					ArrayPushCell(arrHealingWave,str_to_float(szValue));
			
			}
			case SECTION_HUNTER_SKILL2:
			{
				if (equal(szKey, "HUNTER_SKILL2_MIN_PERCENT"))
					fHunterSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "HUNTER_SKILL2_MAX_PERCENT"))
					fHunterSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "HUNTER_SKILL2_LVL"))
					ArrayPushCell(arrHex,str_to_float(szValue));				
				
			}
			case SECTION_HUNTER_SKILL3:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "HUNTER_SKILL3_LVL"))
					ArrayPushCell(arrSerpentWard,str_to_num(szValue));
			
			}
			case SECTION_HUNTER_SKILL4:
			{
				if (equal(szKey, "HUNTER_SKILL4_MIN_PERCENT"))
					fHunterSkill4MinPercent = str_to_float(szValue);
				else if (equal(szKey, "HUNTER_SKILL4_MAX_PERCENT"))
					fHunterSkill4MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "HUNTER_SKILL4_LVL"))
					ArrayPushCell(arrUnstableConcoction,str_to_float(szValue));
			
			}

			//Warden
			case SECTION_WARDEN_SKILL1:
			{
				if (equal(szKey, "WARDEN_SKILL1_MIN_PERCENT"))
					fWardenSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "WARDEN_SKILL1_MAX_PERCENT"))
					fWardenSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "WARDEN_SKILL1_LVL"))
					ArrayPushCell(arrFanOfKnives,str_to_float(szValue));
			
			}
			case SECTION_WARDEN_SKILL2:
			{
				if (equal(szKey, "WARDEN_SKILL2_MIN_PERCENT"))
					fWardenSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "WARDEN_SKILL2_MAX_PERCENT"))
					fWardenSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "WARDEN_SKILL2_LVL"))
					ArrayPushCell(arrBlink,str_to_float(szValue));				
				
			}
			case SECTION_WARDEN_SKILL3:
			{
				if (equal(szKey, "WARDEN_SKILL3_MIN_PERCENT"))
					fWardenSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "WARDEN_SKILL3_MAX_PERCENT"))
					fWardenSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "WARDEN_SKILL3_LVL"))
					ArrayPushCell(arrShadowStrike,str_to_float(szValue));
			
			}
			case SECTION_WARDEN_SKILL4:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "WARDEN_SKILL4_LVL"))
					ArrayPushCell(arrHardenedSkin,str_to_float(szValue));
			
			}
			//Crypt Lord
			case SECTION_LORD_SKILL1:
			{
				if (equal(szKey, "LORD_SKILL1_MIN_PERCENT"))
					fLordSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "LORD_SKILL1_MAX_PERCENT"))
					fLordSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "LORD_SKILL1_LVL"))
					ArrayPushCell(arrImpale,str_to_float(szValue));
			
			}
			case SECTION_LORD_SKILL2:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "LORD_SKILL2_LVL"))
					ArrayPushCell(arrSpikedCarapace,str_to_float(szValue));				
				
			}
			case SECTION_LORD_SKILL3:
			{
				if (equal(szKey, "LORD_SKILL3_MIN_PERCENT"))
					fLordSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "LORD_SKILL3_MAX_PERCENT"))
					fLordSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "LORD_SKILL3_LVL"))
					ArrayPushCell(arrCarrionBeetle,str_to_float(szValue));
			
			}
			case SECTION_LORD_SKILL4:
			{
				if (equal(szKey, "LORD_SKILL4_MIN_PERCENT"))
					fLordSkill4MinPercent = str_to_float(szValue);
				else if (equal(szKey, "LORD_SKILL4_MAX_PERCENT"))
					fLordSkill4MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "LORD_SKILL4_LVL"))
					ArrayPushCell(arrOrbOfAnnihilation,str_to_float(szValue));
			
			}
			//Ice magician
			case SECTION_ICE_SKILL1:
			{
				if (equal(szKey, "ICE_SKILL1_MIN_PERCENT"))
					fIceSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ICE_SKILL1_MAX_PERCENT"))
					fIceSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ICE_SKILL1_LVL"))
					ArrayPushCell(arrIceSplinters,str_to_float(szValue));
			
			}
			case SECTION_ICE_SKILL2:
			{
				if (equal(szKey, "ICE_SKILL2_MIN_PERCENT"))
					fIceSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ICE_SKILL2_MAX_PERCENT"))
					fIceSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ICE_SKILL2_LVL"))
					ArrayPushCell(arrIceArrow,str_to_float(szValue));				
				
			}
			case SECTION_ICE_SKILL3:
			{
				if (equal(szKey, "ICE_SKILL3_MIN_PERCENT"))
					fIceSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ICE_SKILL3_MAX_PERCENT"))
					fIceSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ICE_SKILL3_LVL"))
					ArrayPushCell(arrColdCone,str_to_float(szValue));
			
			}
			//Death knight
			case SECTION_KNIGHT_SKILL1:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "KNIGHT_SKILL1_LVL"))
					ArrayPushCell(arrUnbreakableArmor,str_to_float(szValue));
			
			}
			case SECTION_KNIGHT_SKILL2:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "KNIGHT_SKILL2_LVL"))
					ArrayPushCell(arrBloodBoil,str_to_float(szValue));				
				
			}
			case SECTION_KNIGHT_SKILL3:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "KNIGHT_SKILL3_LVL"))
					ArrayPushCell(arrDeathCoil,str_to_float(szValue));
			
			}
			//Black Mag
			case SECTION_BLACK_MAG_SKILL1:
			{
				if (equal(szKey, "BLACK_MAG_SKILL1_MIN_PERCENT"))
					fBlackMagSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "BLACK_MAG_SKILL1_MAX_PERCENT"))
					fBlackMagSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLACK_MAG_SKILL1_LVL"))
					ArrayPushCell(arrBlackStrike,str_to_float(szValue));
			
			}
			case SECTION_BLACK_MAG_SKILL2:
			{
				if (equal(szKey, "BLACK_MAG_SKILL2_MIN_PERCENT"))
					fBlackMagSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "BLACK_MAG_SKILL2_MAX_PERCENT"))
					fBlackMagSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLACK_MAG_SKILL2_LVL"))
					ArrayPushCell(arrBlackShadow,str_to_float(szValue));				
				
			}
			case SECTION_BLACK_MAG_SKILL3:
			{
				if (equal(szKey, "BLACK_MAG_SKILL3_MIN_PERCENT"))
					fBlackMagSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "BLACK_MAG_SKILL3_MAX_PERCENT"))
					fBlackMagSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLACK_MAG_SKILL3_LVL"))
					ArrayPushCell(arrBlackPower,str_to_float(szValue));
			
			}
			//Alchemist
			case SECTION_ALCHEMIST_SKILL1:
			{
				if (equal(szKey, "ALCHEMIST_SKILL1_MIN_PERCENT"))
					fAlchemistSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ALCHEMIST_SKILL1_MAX_PERCENT"))
					fAlchemistSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ALCHEMIST_SKILL1_LVL"))
					ArrayPushCell(arrPoison,str_to_float(szValue));
			
			}
			case SECTION_ALCHEMIST_SKILL2:
			{
				if (equal(szKey, "ALCHEMIST_SKILL2_MIN_PERCENT"))
					fAlchemistSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ALCHEMIST_SKILL2_MAX_PERCENT"))
					fAlchemistSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ALCHEMIST_SKILL2_LVL"))
					ArrayPushCell(arrShock,str_to_float(szValue));				
				
			}
			case SECTION_ALCHEMIST_SKILL3:
			{
				if (equal(szKey, "ALCHEMIST_SKILL3_MIN_PERCENT"))
					fAlchemistSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ALCHEMIST_SKILL3_MAX_PERCENT"))
					fAlchemistSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ALCHEMIST_SKILL3_LVL"))
					ArrayPushCell(arrFrost,str_to_float(szValue));
			
			}
			case SECTION_ALCHEMIST_SKILL4:
			{
				if (equal(szKey, "ALCHEMIST_SKILL4_MIN_PERCENT"))
					fAlchemistSkill4MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ALCHEMIST_SKILL4_MAX_PERCENT"))
					fAlchemistSkill4MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ALCHEMIST_SKILL4_LVL"))
					ArrayPushCell(arrPassHypnosis,str_to_float(szValue));
			
			}
			//Priest
			case SECTION_PRIEST_SKILL1:
			{
				if (equal(szKey, "PRIEST_SKILL1_MIN_PERCENT"))
					fPriestSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "PRIEST_SKILL1_MAX_PERCENT"))
					fPriestSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "PRIEST_SKILL1_LVL"))
					ArrayPushCell(arrEntryintochasm,str_to_float(szValue));
			
			}
			case SECTION_PRIEST_SKILL2:
			{
				if (equal(szKey, "PRIEST_SKILL2_MIN_PERCENT"))
					fPriestSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "PRIEST_SKILL2_MAX_PERCENT"))
					fPriestSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "PRIEST_SKILL2_LVL"))
					ArrayPushCell(arrSacredFire,str_to_float(szValue));				
				
			}
			case SECTION_PRIEST_SKILL3:
			{
				if (equal(szKey, "PRIEST_SKILL3_MIN_PERCENT"))
					fPriestSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "PRIEST_SKILL3_MAX_PERCENT"))
					fPriestSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "PRIEST_SKILL3_LVL"))
					ArrayPushCell(arrSpiritualAccuracy,str_to_float(szValue));
			
			}
			case SECTION_PRIEST_SKILL4:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "PRIEST_SKILL4_LVL"))
					ArrayPushCell(arrMysticism,str_to_num(szValue));
			
			}

			//Rogue
			case SECTION_ROGUE_SKILL1:
			{
				if (equal(szKey, "ROGUE_SKILL1_MIN_PERCENT"))
					fRogueSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ROGUE_SKILL1_MAX_PERCENT"))
					fRogueSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ROGUE_SKILL1_LVL"))
					ArrayPushCell(arrSinisterStrike,str_to_float(szValue));
			
			}
			case SECTION_ROGUE_SKILL2:
			{
				if (equal(szKey, "ROGUE_SKILL2_MIN_PERCENT"))
					fRogueSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ROGUE_SKILL2_MAX_PERCENT"))
					fRogueSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ROGUE_SKILL2_LVL"))
					ArrayPushCell(arrVanish,str_to_float(szValue));				
				
			}
			case SECTION_ROGUE_SKILL3:
			{
				if (equal(szKey, "ROGUE_SKILL3_MIN_PERCENT"))
					fRogueSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "ROGUE_SKILL3_MAX_PERCENT"))
					fRogueSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "ROGUE_SKILL3_LVL"))
					ArrayPushCell(arrCripplingPoison,str_to_float(szValue));
			
			}

			//Druid
			case SECTION_DRUID_SKILL1:
			{
				if (equal(szKey, "DRUID_SKILL1_MIN_PERCENT"))
					fDruidSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "DRUID_SKILL1_MAX_PERCENT"))
					fDruidSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "DRUID_SKILL1_LVL"))
					ArrayPushCell(arrWildEntanglement,str_to_float(szValue));
			
			}
			case SECTION_DRUID_SKILL2:
			{
				if (equal(szKey, "DRUID_SKILL2_MIN_PERCENT"))
					fDruidSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "DRUID_SKILL2_MAX_PERCENT"))
					fDruidSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "DRUID_SKILL2_LVL"))
					ArrayPushCell(arrWildHealing,str_to_float(szValue));				
				
			}
			case SECTION_DRUID_SKILL3:
			{
				if (equal(szKey, "DRUID_SKILL3_MIN_PERCENT"))
					fDruidSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "DRUID_SKILL3_MAX_PERCENT"))
					fDruidSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "DRUID_SKILL3_LVL"))
					ArrayPushCell(arrWildExplode,str_to_float(szValue));
			
			}
			//17 - Бладсикер
			case SECTION_BLOODSEEKER_SKILL1:
			{
				if (equal(szKey, "BLOODSEEKER_SKILL1_MIN_PERCENT"))
					fBloodseekerSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "BLOODSEEKER_SKILL1_MAX_PERCENT"))
					fBloodseekerSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLOODSEEKER_SKILL1_LVL"))
					ArrayPushCell(arrBloodRage,str_to_float(szValue));
			
			}
			case SECTION_BLOODSEEKER_SKILL2:
			{
				if (equal(szKey, "BLOODSEEKER_SKILL2_MIN_PERCENT"))
					fBloodseekerSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "BLOODSEEKER_SKILL2_MAX_PERCENT"))
					fBloodseekerSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLOODSEEKER_SKILL2_LVL"))
					ArrayPushCell(arrBloodBath,str_to_float(szValue));				
				
			}
			case SECTION_BLOODSEEKER_SKILL3:
			{
				if (equal(szKey, "BLOODSEEKER_SKILL3_MIN_PERCENT"))
					fBloodseekerSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "BLOODSEEKER_SKILL3_MAX_PERCENT"))
					fBloodseekerSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "BLOODSEEKER_SKILL3_LVL"))
					ArrayPushCell(arrBloodRite,str_to_float(szValue));
			}
			
			//18 - Джагернаут
			case SECTION_JUGGERNAUT_SKILL1:
			{
				if (equal(szKey, "JUGGERNAUT_SKILL1_MIN_PERCENT"))
					fJuggernautSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "JUGGERNAUT_SKILL1_MAX_PERCENT"))
					fJuggernautSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "JUGGERNAUT_SKILL1_LVL"))
					ArrayPushCell(arrHealingWard,str_to_float(szValue));
			
			}
			case SECTION_JUGGERNAUT_SKILL2:
			{
				if (equal(szKey, "JUGGERNAUT_SKILL2_MIN_PERCENT"))
					fJuggernautSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "JUGGERNAUT_SKILL2_MAX_PERCENT"))
					fJuggernautSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "JUGGERNAUT_SKILL2_LVL"))
					ArrayPushCell(arrCriticalBlade,str_to_float(szValue));				
				
			}
			case SECTION_JUGGERNAUT_SKILL3:
			{
				if (equal(szKey, "JUGGERNAUT_SKILL3_MIN_PERCENT"))
					fJuggernautSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "JUGGERNAUT_SKILL3_MAX_PERCENT"))
					fJuggernautSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "JUGGERNAUT_SKILL3_LVL"))
					ArrayPushCell(arrDemonBlade,str_to_float(szValue));
			}
			//19 - Снайпер			
			case SECTION_SNIPER_SKILL1:
			{
				if (equal(szKey, "SNIPER_SKILL1_MIN_PERCENT"))
					fHeadshotSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "SNIPER_SKILL1_MAX_PERCENT"))
					fHeadshotSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "SNIPER_SKILL1_LVL"))
					ArrayPushCell(arrHeadshot,str_to_float(szValue));
			
			}
			case SECTION_SNIPER_SKILL2:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "SNIPER_SKILL2_LVL"))
					ArrayPushCell(arrPhaseBoots,str_to_float(szValue));				
				
			}
			case SECTION_SNIPER_SKILL3:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "SNIPER_SKILL3_LVL"))
					ArrayPushCell(arrSkillShrapnelCharge,str_to_num(szValue));
			}
			
			//Разрушитель
			case SECTION_DISRUPTOR_SKILL1:
			{
				if (equal(szKey, "DISRUPTOR_SKILL1_MIN_PERCENT"))
					fGlimpseSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "DISRUPTOR_SKILL1_MAX_PERCENT"))
					fGlimpseSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "DISRUPTOR_SKILL1_LVL"))
					ArrayPushCell(arrGlimpse,str_to_float(szValue));
			
			}
			case SECTION_DISRUPTOR_SKILL2:
			{
				if (equal(szKey, "DISRUPTOR_SKILL2_MIN_PERCENT"))
					fThunderStrikeSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "DISRUPTOR_SKILL2_MAX_PERCENT"))
					fThunderStrikeSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "DISRUPTOR_SKILL2_LVL"))
					ArrayPushCell(arrThunderStrike,str_to_float(szValue));				
				
			}
			case SECTION_DISRUPTOR_SKILL3:
			{
				if (equal(szKey, "DISRUPTOR_SKILL3_MIN_PERCENT"))
					fKineticFieldSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "DISRUPTOR_SKILL3_MAX_PERCENT"))
					fKineticFieldSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "DISRUPTOR_SKILL3_LVL"))
					ArrayPushCell(arrKineticField,str_to_float(szValue));
			}
			//Блэйд
			case SECTION_RAZOR_SKILL1:
			{
				if (equal(szKey, "RAZOR_SKILL1_MIN_PERCENT"))
					fEyeOfTheStormSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "RAZOR_SKILL1_MAX_PERCENT"))
					fEyeOfTheStormSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "RAZOR_SKILL1_LVL"))
					ArrayPushCell(arrEyeOfTheStorm,str_to_float(szValue));
			
			}
			case SECTION_RAZOR_SKILL2:
			{
				if (equal(szKey, "RAZOR_SKILL2_MIN_PERCENT"))
					fStaticLinkSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "RAZOR_SKILL2_MAX_PERCENT"))
					fStaticLinkSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "RAZOR_SKILL2_LVL"))
					ArrayPushCell(arrStaticLink,str_to_float(szValue));				
				
			}
			case SECTION_RAZOR_SKILL3:
			{
				if (equal(szKey, "RAZOR_SKILL3_MIN_PERCENT"))
					fUnstableCurSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "RAZOR_SKILL3_MAX_PERCENT"))
					fUnstableCurSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "RAZOR_SKILL3_LVL"))
					ArrayPushCell(arrUnstableCurrent,str_to_float(szValue));
			}
			//Варлок
			case SECTION_WARLOCK_SKILL1:
			{
				if (equal(szKey, "WARLOCK_SKILL1_MIN_PERCENT"))
					fFatalBondsSkill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "WARLOCK_SKILL1_MAX_PERCENT"))
					fFatalBondsSkill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "WARLOCK_SKILL1_LVL"))
					ArrayPushCell(arrFatalBonds,str_to_float(szValue));
			
			}
			case SECTION_WARLOCK_SKILL2:
			{
				if (equal(szKey, "WARLOCK_SKILL2_MIN_PERCENT"))
					fShadowWordSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "WARLOCK_SKILL2_MAX_PERCENT"))
					fShadowWordSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "WARLOCK_SKILL2_LVL"))
					ArrayPushCell(arrShadowWord,str_to_float(szValue));				
				
			}
			case SECTION_WARLOCK_SKILL3:
			{
				if (equal(szKey, "WARLOCK_SKILL3_MIN_PERCENT"))
					fFlamingFistsSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "WARLOCK_SKILL3_MAX_PERCENT"))
					fFlamingFistsSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "WARLOCK_SKILL3_LVL"))
					ArrayPushCell(arrFlamingFists,str_to_float(szValue));
			}			
			//Невермор
			case SECTION_SHADOW_FIEND_SKILL1:
			{
				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "SHADOW_FIEND_SKILL1_LVL"))
					ArrayPushCell(arrPresenceDarkLord,str_to_float(szValue));
			
			}
			case SECTION_SHADOW_FIEND_SKILL2:
			{
				if (equal(szKey, "SHADOW_FIEND_SKILL2_MIN_PERCENT"))
					fRequiemSoulsSkill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "SHADOW_FIEND_SKILL2_MAX_PERCENT"))
					fRequiemSoulsSkill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "SHADOW_FIEND_SKILL2_LVL"))
					ArrayPushCell(arrRequiemSouls,str_to_float(szValue));				
				
			}
			case SECTION_SHADOW_FIEND_SKILL3:
			{
				if (equal(szKey, "SHADOW_FIEND_SKILL3_MIN_PERCENT"))
					fCryHeartSkill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "SHADOW_FIEND_SKILL3_MAX_PERCENT"))
					fCryHeartSkill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "SHADOW_FIEND_SKILL3_LVL"))
					ArrayPushCell(arrCryHeart,str_to_float(szValue));
			}
			
			//24
			/*
			case SECTION_24_SKILL1:
			{
				if (equal(szKey, "24_SKILL1_MIN_PERCENT"))
					f24Skill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "24_SKILL1_MAX_PERCENT"))
					f24Skill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "24_SKILL1_LVL"))
					ArrayPushCell(arrSkill_1_24,str_to_float(szValue));
			
			}
			case SECTION_24_SKILL2:
			{
				if (equal(szKey, "24_SKILL2_MIN_PERCENT"))
					f24Skill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "24_SKILL2_MAX_PERCENT"))
					f24Skill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "24_SKILL2_LVL"))
					ArrayPushCell(arrSkill_2_24,str_to_float(szValue));				
				
			}
			case SECTION_24_SKILL3:
			{
				if (equal(szKey, "24_SKILL3_MIN_PERCENT"))
					f24Skill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "24_SKILL3_MAX_PERCENT"))
					f24Skill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "24_SKILL3_LVL"))
					ArrayPushCell(arrSkill_3_24,str_to_float(szValue));
			}*/

			//25
			/*
			case SECTION_25_SKILL1:
			{
				if (equal(szKey, "25_SKILL1_MIN_PERCENT"))
					f25Skill1MinPercent = str_to_float(szValue);
				else if (equal(szKey, "25_SKILL1_MAX_PERCENT"))
					f25Skill1MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "25_SKILL1_LVL"))
					ArrayPushCell(arrSkill_1_25,str_to_float(szValue));
			
			}
			case SECTION_25_SKILL2:
			{
				if (equal(szKey, "25_SKILL2_MIN_PERCENT"))
					f25Skill2MinPercent = str_to_float(szValue);
				else if (equal(szKey, "25_SKILL2_MAX_PERCENT"))
					f25Skill2MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "25_SKILL2_LVL"))
					ArrayPushCell(arrSkill_2_25,str_to_float(szValue));				
				
			}
			case SECTION_25_SKILL3:
			{
				if (equal(szKey, "25_SKILL3_MIN_PERCENT"))
					f25Skill3MinPercent = str_to_float(szValue);
				else if (equal(szKey, "25_SKILL3_MAX_PERCENT"))
					f25Skill3MaxPercent = str_to_float(szValue);

				strtok(szKey, szValueSkills, charsmax(szValueSkills), szValueLVL, charsmax(szValueLVL), '@')
				if (equal(szValueSkills, "25_SKILL3_LVL"))
					ArrayPushCell(arrSkill_3_25,str_to_float(szValue));
					
			}
			*/

		}//switch (iSection)
	}

	if (fileWar3ftmod_ini) fclose(fileWar3ftmod_ini)

}
