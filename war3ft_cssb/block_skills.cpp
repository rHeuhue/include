/*------------------------------------
Файл скилов на карте
------------------------------------*/
//Инициализация массивов файла настройки
public cfInitArraysBlockSkillsFile()
{
	arrTrieBlockSkillsMap = TravTrieCreate();
}

//Загрузка файла настройки
public cfLoadBlockSkillsFile()//добавлена в war3ft.cpp ( public WC3_Precache() )
{
	cfInitArraysBlockSkillsFile();

	new szPath[64];
	get_configsdir(szPath, charsmax(szPath));
	format(szPath, charsmax(szPath), "%s/%s", szPath, WAR3FT_BLOCK_SKILLS_FILE);
	
	// File not present
	if (!file_exists(szPath))
	{
		new szError[100];
		formatex(szError, charsmax(szError), "Cannot load war3ft block skills file %s!", szPath);
		set_fail_state(szError);
		return;
	}
	
	// Set up some vars to hold parsing info
	new szLineData[1024], szKey[64], szValue[255], iSection;
	
	// Open customization file for reading
	new fileBlockSkills_ini = fopen(szPath, "rt")
	
	while (fileBlockSkills_ini && !feof(fileBlockSkills_ini))
	{
		// Read one line at a time
		fgets(fileBlockSkills_ini, szLineData, charsmax(szLineData))
		
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
			case SECTION_BLOCK_SKILLS:
			{
				if (equal(szKey, "BLOCK_SKILL_VAMPIRICAURA"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_VAMPIRICAURA", szValue);
				else if (equal(szKey, "BLOCK_SKILL_UNHOLYAURA"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_UNHOLYAURA", szValue);
				else if (equal(szKey, "BLOCK_SKILL_LEVITATION"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_LEVITATION", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_SUICIDE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_SUICIDE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_INVISIBILITY"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_INVISIBILITY", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DEVOTION"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DEVOTION", szValue);
				else if (equal(szKey, "BLOCK_SKILL_BASH"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_BASH", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_BLINK"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_BLINK", szValue);
				else if (equal(szKey, "BLOCK_SKILL_CRITICALSTRIKE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_CRITICALSTRIKE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_CRITICALGRENADE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_CRITICALGRENADE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_REINCARNATION"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_REINCARNATION", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_CHAINLIGHTNING"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_CHAINLIGHTNING", szValue);
				else if (equal(szKey, "BLOCK_SKILL_EVASION"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_EVASION", szValue);
				else if (equal(szKey, "BLOCK_SKILL_THORNS"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_THORNS", szValue);
				else if (equal(szKey, "BLOCK_SKILL_TRUESHOT"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_TRUESHOT", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_ENTANGLE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_ENTANGLE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_PHOENIX"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_PHOENIX", szValue);
				else if (equal(szKey, "BLOCK_SKILL_BANISH"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_BANISH", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SIPHONMANA"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SIPHONMANA", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_IMMOLATE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_IMMOLATE", szValue);
				else if (equal(szKey, "BLOCK_PASS_RESISTANTSKIN"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_RESISTANTSKIN", szValue);
				else if (equal(szKey, "BLOCK_SKILL_HEALINGWAVE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_HEALINGWAVE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_HEX"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_HEX", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SERPENTWARD"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SERPENTWARD", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_BIGBADVOODOO"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_BIGBADVOODOO", szValue);
				else if (equal(szKey, "BLOCK_PASS_UNSTABLECONCOCTION"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_UNSTABLECONCOCTION", szValue);
				else if (equal(szKey, "BLOCK_SKILL_FANOFKNIVES"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_FANOFKNIVES", szValue);
				else if (equal(szKey, "BLOCK_SKILL_BLINK"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_BLINK", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SHADOWSTRIKE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SHADOWSTRIKE", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_VENGEANCE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_VENGEANCE", szValue);
				else if (equal(szKey, "BLOCK_PASS_HARDENEDSKIN"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_HARDENEDSKIN", szValue);
				else if (equal(szKey, "BLOCK_SKILL_IMPALE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_IMPALE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SPIKEDCARAPACE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SPIKEDCARAPACE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_CARRIONBEETLES"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_CARRIONBEETLES", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_LOCUSTSWARM"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_LOCUSTSWARM", szValue);
				else if (equal(szKey, "BLOCK_PASS_ORB"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_ORB", szValue);
				else if (equal(szKey, "BLOCK_SKILL_FROST_MAGE_ICE_SPLINTERS"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_FROST_MAGE_ICE_SPLINTERS", szValue);
				else if (equal(szKey, "BLOCK_SKILL_FROST_MAGE_ICE_ARROW"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_FROST_MAGE_ICE_ARROW", szValue);
				else if (equal(szKey, "BLOCK_SKILL_FROST_MAGE_CONE_OF_COLD"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_FROST_MAGE_CONE_OF_COLD", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_FROST_MAGE_BLIZZARD"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_FROST_MAGE_BLIZZARD", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_CHAM_FLAME_STRIKE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_CHAM_FLAME_STRIKE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DEATH_KNIGHT_UNARMOR"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DEATH_KNIGHT_UNARMOR", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DEATH_KNIGHT_BLOOD_BOIL"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DEATH_KNIGHT_BLOOD_BOIL", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DEATH_KNIGHT_DEATH_COIL"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DEATH_KNIGHT_DEATH_COIL", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE", szValue);
				else if (equal(szKey, "BLOCK_PASS_DEATH_KNIGHT_CONTROL_UNDEAD"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_DEATH_KNIGHT_CONTROL_UNDEAD", szValue);
				else if (equal(szKey, "BLOCK_SKILL_BLACKSTRIKE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_BLACKSTRIKE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_BLACKSHADOW"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_BLACKSHADOW", szValue);
				else if (equal(szKey, "BLOCK_SKILL_BLACKPOWER"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_BLACKPOWER", szValue);
				else if (equal(szKey, "BLOCK_ABILITY_BLACK_MAG"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ABILITY_BLACK_MAG", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_BLACKLIGHTNING"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_BLACKLIGHTNING", szValue);
				else if (equal(szKey, "BLOCK_SKILL_POISON"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_POISON", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SHOCK"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SHOCK", szValue);
				else if (equal(szKey, "BLOCK_SKILL_FROST"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_FROST", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_RADIATION"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_RADIATION", szValue);
				else if (equal(szKey, "BLOCK_PASS_HYPNOSIS"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_HYPNOSIS", szValue);
				else if (equal(szKey, "BLOCK_SKILL_PRIEST_ENTRYINTOCHASM"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_PRIEST_ENTRYINTOCHASM", szValue);
				else if (equal(szKey, "BLOCK_SKILL_PRIEST_SACRED_FIRE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_PRIEST_SACRED_FIRE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_PRIEST_SPIRITUAL_ACCURACY"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_PRIEST_SPIRITUAL_ACCURACY", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_PRIEST_DARKNESS_WORD_DEATH"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_PRIEST_DARKNESS_WORD_DEATH", szValue);
				else if (equal(szKey, "BLOCK_PASS_PRIEST_MYSTICISM"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_PRIEST_MYSTICISM", szValue);
				else if (equal(szKey, "BLOCK_SKILL_ROGUE_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_ROGUE_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_ROGUE_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_ROGUE_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_ROGUE_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_ROGUE_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_ROGUE"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_ROGUE", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DRUID_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DRUID_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DRUID_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DRUID_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DRUID_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DRUID_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_DRUID"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_DRUID", szValue);
				else if (equal(szKey, "BLOCK_PASS_MANGLE_DRUID"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_MANGLE_DRUID", szValue);
				else if (equal(szKey, "BLOCK_SKILL_BLOODSEEKER_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_BLOODSEEKER_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_BLOODSEEKER_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_BLOODSEEKER_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_BLOODSEEKER_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_BLOODSEEKER_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_BLOODSEEKER"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_BLOODSEEKER", szValue);
				else if (equal(szKey, "BLOCK_PASS_BLOODSEEKER"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_BLOODSEEKER", szValue);
				else if (equal(szKey, "BLOCK_SKILL_JUGGERNAUT_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_JUGGERNAUT_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_JUGGERNAUT_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_JUGGERNAUT_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_JUGGERNAUT_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_JUGGERNAUT_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_JUGGERNAUT"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_JUGGERNAUT", szValue);
				else if (equal(szKey, "BLOCK_PASS_JUGGERNAUT"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_JUGGERNAUT", szValue);
				else if (equal(szKey, "BLOCK_ABILITY_JUGGERNAUT"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ABILITY_JUGGERNAUT", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SNIPER_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SNIPER_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SNIPER_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SNIPER_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SNIPER_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SNIPER_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_SNIPER"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_SNIPER", szValue);
				else if (equal(szKey, "BLOCK_PASS_SNIPER"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_SNIPER", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DISRUPTOR_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DISRUPTOR_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DISRUPTOR_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DISRUPTOR_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_DISRUPTOR_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_DISRUPTOR_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_DISRUPTOR"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_DISRUPTOR", szValue);
				else if (equal(szKey, "BLOCK_PASS_DISRUPTOR"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_DISRUPTOR", szValue);
				else if (equal(szKey, "BLOCK_SKILL_RAZOR_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_RAZOR_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_RAZOR_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_RAZOR_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_RAZOR_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_RAZOR_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_RAZOR"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_RAZOR", szValue);
				else if (equal(szKey, "BLOCK_PASS_RAZOR"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_RAZOR", szValue);
				else if (equal(szKey, "BLOCK_SKILL_WARLOCK_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_WARLOCK_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_WARLOCK_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_WARLOCK_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_WARLOCK_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_WARLOCK_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_WARLOCK"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_WARLOCK", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SHADOW_FIEND_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SHADOW_FIEND_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SHADOW_FIEND_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SHADOW_FIEND_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_SHADOW_FIEND_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_SHADOW_FIEND_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_SHADOW_FIEND"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_SHADOW_FIEND", szValue);
				//Раса 24
				else if (equal(szKey, "BLOCK_SKILL_24_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_24_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_24_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_24_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_24_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_24_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_24"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_24", szValue);
				else if (equal(szKey, "BLOCK_PASS_24"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_24", szValue);
				//Раса 25
				else if (equal(szKey, "BLOCK_SKILL_25_1"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_25_1", szValue);
				else if (equal(szKey, "BLOCK_SKILL_25_2"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_25_2", szValue);
				else if (equal(szKey, "BLOCK_SKILL_25_3"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_SKILL_25_3", szValue);
				else if (equal(szKey, "BLOCK_ULTIMATE_25"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_ULTIMATE_25", szValue);
				else if (equal(szKey, "BLOCK_PASS_25"))
					TravTrieSetString(arrTrieBlockSkillsMap,"BLOCK_PASS_25", szValue);
				
  			}
				
		}//switch (iSection)
	}

	if (fileBlockSkills_ini) fclose(fileBlockSkills_ini)

}


bool:isDisabledSkillsOnMap(idUser,iSkillId,szSkillName[] = "")
{
	LANG_GetSkillName(iSkillId,idUser,szSkillName, 63, 99 );

	new szKey[64], szValue[255];

	new travTrieIter:trieIterator = GetTravTrieIterator(arrTrieBlockSkillsMap);
	while(MoreTravTrie(trieIterator))
	{
		ReadTravTrieKey(trieIterator,szKey,charsmax(szKey));
		ReadTravTrieString(trieIterator,szValue,charsmax(szValue));
		//log_amx("Key: '%s' = '%s'",szKey,szValue);

		if ( (equal(szKey, "BLOCK_SKILL_VAMPIRICAURA")						&& iSkillId == SKILL_VAMPIRICAURA) ||
			(equal(szKey, "BLOCK_SKILL_UNHOLYAURA")							&& iSkillId == SKILL_UNHOLYAURA) ||
			(equal(szKey, "BLOCK_SKILL_LEVITATION")							&& iSkillId == SKILL_LEVITATION) ||
			(equal(szKey, "BLOCK_ULTIMATE_SUICIDE")							&& iSkillId == ULTIMATE_SUICIDE) ||
			(equal(szKey, "BLOCK_SKILL_INVISIBILITY")						&& iSkillId == SKILL_INVISIBILITY) ||
			(equal(szKey, "BLOCK_SKILL_DEVOTION")							&& iSkillId == SKILL_DEVOTION) ||
			(equal(szKey, "BLOCK_SKILL_BASH")								&& iSkillId == SKILL_BASH) ||
			(equal(szKey, "BLOCK_ULTIMATE_BLINK")							&& iSkillId == ULTIMATE_BLINK) ||
			(equal(szKey, "BLOCK_SKILL_CRITICALSTRIKE")						&& iSkillId == SKILL_CRITICALSTRIKE) ||
			(equal(szKey, "BLOCK_SKILL_CRITICALGRENADE")					&& iSkillId == SKILL_CRITICALGRENADE) ||
			(equal(szKey, "BLOCK_SKILL_REINCARNATION")						&& iSkillId == SKILL_REINCARNATION) ||
			(equal(szKey, "BLOCK_ULTIMATE_CHAINLIGHTNING")					&& iSkillId == ULTIMATE_CHAINLIGHTNING) ||
			(equal(szKey, "BLOCK_SKILL_EVASION")							&& iSkillId == SKILL_EVASION) ||
			(equal(szKey, "BLOCK_SKILL_THORNS")								&& iSkillId == SKILL_THORNS) ||
			(equal(szKey, "BLOCK_SKILL_TRUESHOT")							&& iSkillId == SKILL_TRUESHOT) ||
			(equal(szKey, "BLOCK_ULTIMATE_ENTANGLE")						&& iSkillId == ULTIMATE_ENTANGLE) ||
			(equal(szKey, "BLOCK_SKILL_PHOENIX")							&& iSkillId == SKILL_PHOENIX) ||
			(equal(szKey, "BLOCK_SKILL_BANISH")								&& iSkillId == SKILL_BANISH) ||
			(equal(szKey, "BLOCK_SKILL_SIPHONMANA")							&& iSkillId == SKILL_SIPHONMANA) ||
			(equal(szKey, "BLOCK_ULTIMATE_IMMOLATE")						&& iSkillId == ULTIMATE_IMMOLATE) ||
			(equal(szKey, "BLOCK_PASS_RESISTANTSKIN")						&& iSkillId == PASS_RESISTANTSKIN) ||
			(equal(szKey, "BLOCK_SKILL_HEALINGWAVE")						&& iSkillId == SKILL_HEALINGWAVE) ||
			(equal(szKey, "BLOCK_SKILL_HEX")								&& iSkillId == SKILL_HEX) ||
			(equal(szKey, "BLOCK_SKILL_SERPENTWARD")						&& iSkillId == SKILL_SERPENTWARD) ||
			(equal(szKey, "BLOCK_ULTIMATE_BIGBADVOODOO")					&& iSkillId == ULTIMATE_BIGBADVOODOO) ||
			(equal(szKey, "BLOCK_PASS_UNSTABLECONCOCTION")					&& iSkillId == PASS_UNSTABLECONCOCTION) ||
			(equal(szKey, "BLOCK_SKILL_FANOFKNIVES")						&& iSkillId == SKILL_FANOFKNIVES) ||
			(equal(szKey, "BLOCK_SKILL_BLINK")								&& iSkillId == SKILL_BLINK) ||
			(equal(szKey, "BLOCK_SKILL_SHADOWSTRIKE")						&& iSkillId == SKILL_SHADOWSTRIKE) ||
			(equal(szKey, "BLOCK_ULTIMATE_VENGEANCE")						&& iSkillId == ULTIMATE_VENGEANCE) ||
			(equal(szKey, "BLOCK_PASS_HARDENEDSKIN")						&& iSkillId == PASS_HARDENEDSKIN) ||
			(equal(szKey, "BLOCK_SKILL_IMPALE")								&& iSkillId == SKILL_IMPALE) ||
			(equal(szKey, "BLOCK_SKILL_SPIKEDCARAPACE")						&& iSkillId == SKILL_SPIKEDCARAPACE) ||
			(equal(szKey, "BLOCK_SKILL_CARRIONBEETLES")						&& iSkillId == SKILL_CARRIONBEETLES) ||
			(equal(szKey, "BLOCK_ULTIMATE_LOCUSTSWARM")						&& iSkillId == ULTIMATE_LOCUSTSWARM) ||
			(equal(szKey, "BLOCK_PASS_ORB")									&& iSkillId == PASS_ORB) ||
			(equal(szKey, "BLOCK_SKILL_FROST_MAGE_ICE_SPLINTERS")			&& iSkillId == SKILL_FROST_MAGE_ICE_SPLINTERS) ||
			(equal(szKey, "BLOCK_SKILL_FROST_MAGE_ICE_ARROW")				&& iSkillId == SKILL_FROST_MAGE_ICE_ARROW) ||
			(equal(szKey, "BLOCK_SKILL_FROST_MAGE_CONE_OF_COLD")			&& iSkillId == SKILL_FROST_MAGE_CONE_OF_COLD) ||
			(equal(szKey, "BLOCK_ULTIMATE_FROST_MAGE_BLIZZARD")				&& iSkillId == ULTIMATE_FROST_MAGE_BLIZZARD) ||
			(equal(szKey, "BLOCK_ULTIMATE_CHAM_FLAME_STRIKE")				&& iSkillId == ULTIMATE_CHAM_FLAME_STRIKE) ||
			(equal(szKey, "BLOCK_SKILL_DEATH_KNIGHT_UNARMOR")				&& iSkillId == SKILL_DEATH_KNIGHT_UNARMOR) ||
			(equal(szKey, "BLOCK_SKILL_DEATH_KNIGHT_BLOOD_BOIL")			&& iSkillId == SKILL_DEATH_KNIGHT_BLOOD_BOIL) ||
			(equal(szKey, "BLOCK_SKILL_DEATH_KNIGHT_DEATH_COIL")			&& iSkillId == SKILL_DEATH_KNIGHT_DEATH_COIL) ||
			(equal(szKey, "BLOCK_ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE")		&& iSkillId == ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE) ||
			(equal(szKey, "BLOCK_PASS_DEATH_KNIGHT_CONTROL_UNDEAD")			&& iSkillId == PASS_DEATH_KNIGHT_CONTROL_UNDEAD) ||
			(equal(szKey, "BLOCK_SKILL_BLACKSTRIKE")						&& iSkillId == SKILL_BLACKSTRIKE) ||
			(equal(szKey, "BLOCK_SKILL_BLACKSHADOW")						&& iSkillId == SKILL_BLACKSHADOW) ||
			(equal(szKey, "BLOCK_SKILL_BLACKPOWER")							&& iSkillId == SKILL_BLACKPOWER) ||
			(equal(szKey, "BLOCK_ULTIMATE_BLACKLIGHTNING")					&& iSkillId == ULTIMATE_BLACKLIGHTNING) ||
			(equal(szKey, "BLOCK_SKILL_POISON")								&& iSkillId == SKILL_POISON) ||
			(equal(szKey, "BLOCK_SKILL_SHOCK")								&& iSkillId == SKILL_SHOCK) ||
			(equal(szKey, "BLOCK_SKILL_FROST")								&& iSkillId == SKILL_FROST) ||
			(equal(szKey, "BLOCK_ULTIMATE_RADIATION")						&& iSkillId == ULTIMATE_RADIATION) ||
			(equal(szKey, "BLOCK_PASS_HYPNOSIS")							&& iSkillId == PASS_HYPNOSIS) ||
			(equal(szKey, "BLOCK_SKILL_PRIEST_ENTRYINTOCHASM")				&& iSkillId == SKILL_PRIEST_ENTRYINTOCHASM) ||
			(equal(szKey, "BLOCK_SKILL_PRIEST_SACRED_FIRE")					&& iSkillId == SKILL_PRIEST_SACRED_FIRE) ||
			(equal(szKey, "BLOCK_SKILL_PRIEST_SPIRITUAL_ACCURACY")			&& iSkillId == SKILL_PRIEST_SPIRITUAL_ACCURACY) ||
			(equal(szKey, "BLOCK_ULTIMATE_PRIEST_DARKNESS_WORD_DEATH")		&& iSkillId == ULTIMATE_PRIEST_DARKNESS_WORD_DEATH) ||
			(equal(szKey, "BLOCK_PASS_PRIEST_MYSTICISM")					&& iSkillId == PASS_PRIEST_MYSTICISM) ||
			(equal(szKey, "BLOCK_SKILL_ROGUE_1")							&& iSkillId == SKILL_ROGUE_1) ||
			(equal(szKey, "BLOCK_SKILL_ROGUE_2")							&& iSkillId == SKILL_ROGUE_2) ||
			(equal(szKey, "BLOCK_SKILL_ROGUE_3")							&& iSkillId == SKILL_ROGUE_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_ROGUE")							&& iSkillId == ULTIMATE_ROGUE) ||
			(equal(szKey, "BLOCK_SKILL_DRUID_1")							&& iSkillId == SKILL_DRUID_1) ||
			(equal(szKey, "BLOCK_SKILL_DRUID_2")							&& iSkillId == SKILL_DRUID_2) ||
			(equal(szKey, "BLOCK_SKILL_DRUID_3")							&& iSkillId == SKILL_DRUID_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_DRUID")							&& iSkillId == ULTIMATE_DRUID) ||
			(equal(szKey, "BLOCK_PASS_MANGLE_DRUID")						&& iSkillId == PASS_MANGLE_DRUID) 
		   )
		{
			if(isMap(szValue) == true)
			{
				DestroyTravTrieIterator(trieIterator);
				return true;
			}

		}//if

		//Из-за ошибки fatal error 102: table overflow: "staging buffer" пришлось разделить условия на две части

			//Раса Бладсикер
		if ((equal(szKey, "BLOCK_SKILL_BLOODSEEKER_1")								&& iSkillId == SKILL_BLOODSEEKER_1) ||
			(equal(szKey, "BLOCK_SKILL_BLOODSEEKER_2")								&& iSkillId == SKILL_BLOODSEEKER_2) ||
			(equal(szKey, "BLOCK_SKILL_BLOODSEEKER_3")								&& iSkillId == SKILL_BLOODSEEKER_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_BLOODSEEKER")								&& iSkillId == ULTIMATE_BLOODSEEKER) ||
			(equal(szKey, "BLOCK_PASS_BLOODSEEKER")									&& iSkillId == PASS_BLOODSEEKER) ||
			//Раса Джагернаут
			(equal(szKey, "BLOCK_SKILL_JUGGERNAUT_1")								&& iSkillId == SKILL_JUGGERNAUT_1) ||
			(equal(szKey, "BLOCK_SKILL_JUGGERNAUT_2")								&& iSkillId == SKILL_JUGGERNAUT_2) ||
			(equal(szKey, "BLOCK_SKILL_JUGGERNAUT_3")								&& iSkillId == SKILL_JUGGERNAUT_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_JUGGERNAUT")								&& iSkillId == ULTIMATE_JUGGERNAUT) ||
			(equal(szKey, "BLOCK_PASS_JUGGERNAUT")									&& iSkillId == PASS_JUGGERNAUT) ||
			//Раса Снайпер
			(equal(szKey, "BLOCK_SKILL_SNIPER_1")								&& iSkillId == SKILL_SNIPER_1) ||
			(equal(szKey, "BLOCK_SKILL_SNIPER_2")								&& iSkillId == SKILL_SNIPER_2) ||
			(equal(szKey, "BLOCK_SKILL_SNIPER_3")								&& iSkillId == SKILL_SNIPER_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_SNIPER")								&& iSkillId == ULTIMATE_SNIPER) ||
			(equal(szKey, "BLOCK_PASS_SNIPER")									&& iSkillId == PASS_SNIPER) ||
			//Раса Разрушитель
			(equal(szKey, "BLOCK_SKILL_DISRUPTOR_1")								&& iSkillId == SKILL_DISRUPTOR_1) ||
			(equal(szKey, "BLOCK_SKILL_DISRUPTOR_2")								&& iSkillId == SKILL_DISRUPTOR_2) ||
			(equal(szKey, "BLOCK_SKILL_DISRUPTOR_3")								&& iSkillId == SKILL_DISRUPTOR_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_DISRUPTOR")								&& iSkillId == ULTIMATE_DISRUPTOR) ||
			(equal(szKey, "BLOCK_PASS_DISRUPTOR")									&& iSkillId == PASS_DISRUPTOR) ||
			//Раса Блэйд
			(equal(szKey, "BLOCK_SKILL_RAZOR_1")								&& iSkillId == SKILL_RAZOR_1) ||
			(equal(szKey, "BLOCK_SKILL_RAZOR_2")								&& iSkillId == SKILL_RAZOR_2) ||
			(equal(szKey, "BLOCK_SKILL_RAZOR_3")								&& iSkillId == SKILL_RAZOR_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_RAZOR")								&& iSkillId == ULTIMATE_RAZOR) ||
			(equal(szKey, "BLOCK_PASS_RAZOR")									&& iSkillId == PASS_RAZOR) ||
			//Раса Варлок
			(equal(szKey, "BLOCK_SKILL_WARLOCK_1")								&& iSkillId == SKILL_WARLOCK_1) ||
			(equal(szKey, "BLOCK_SKILL_WARLOCK_2")								&& iSkillId == SKILL_WARLOCK_2) ||
			(equal(szKey, "BLOCK_SKILL_WARLOCK_3")								&& iSkillId == SKILL_WARLOCK_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_WARLOCK")								&& iSkillId == ULTIMATE_WARLOCK) ||
			//(equal(szKey, "BLOCK_PASS_WARLOCK")									&& iSkillId == PASS_WARLOCK) ||
			//Раса Невермор
			(equal(szKey, "BLOCK_SKILL_SHADOW_FIEND_1")								&& iSkillId == SKILL_SHADOW_FIEND_1) ||
			(equal(szKey, "BLOCK_SKILL_SHADOW_FIEND_2")								&& iSkillId == SKILL_SHADOW_FIEND_2) ||
			(equal(szKey, "BLOCK_SKILL_SHADOW_FIEND_3")								&& iSkillId == SKILL_SHADOW_FIEND_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_SHADOW_FIEND")								&& iSkillId == ULTIMATE_SHADOW_FIEND) ||
			//(equal(szKey, "BLOCK_PASS_SHADOW_FIEND")									&& iSkillId == PASS_SHADOW_FIEND) ||
			//Раса 24
			(equal(szKey, "BLOCK_SKILL_24_1")								&& iSkillId == SKILL_24_1) ||
			(equal(szKey, "BLOCK_SKILL_24_2")								&& iSkillId == SKILL_24_2) ||
			(equal(szKey, "BLOCK_SKILL_24_3")								&& iSkillId == SKILL_24_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_24")								&& iSkillId == ULTIMATE_24) ||
			(equal(szKey, "BLOCK_PASS_24")									&& iSkillId == PASS_24) ||
			//Раса 25
			(equal(szKey, "BLOCK_SKILL_25_1")								&& iSkillId == SKILL_25_1) ||
			(equal(szKey, "BLOCK_SKILL_25_2")								&& iSkillId == SKILL_25_2) ||
			(equal(szKey, "BLOCK_SKILL_25_3")								&& iSkillId == SKILL_25_3) ||
			(equal(szKey, "BLOCK_ULTIMATE_25")								&& iSkillId == ULTIMATE_25) ||
			(equal(szKey, "BLOCK_PASS_25")									&& iSkillId == PASS_25)

		   )
		{
			if(isMap(szValue) == true)
			{
				DestroyTravTrieIterator(trieIterator);
				return true;
			}

		}//if


 
	}//while

	DestroyTravTrieIterator(trieIterator);

	return false;
}

bool:isDisabledAbiltyOnMap(iIdAbility)
{
	new szKey[64], szValue[255];

	new travTrieIter:trieIterator = GetTravTrieIterator(arrTrieBlockSkillsMap);
	while(MoreTravTrie(trieIterator))
	{
		ReadTravTrieKey(trieIterator,szKey,charsmax(szKey));
		ReadTravTrieString(trieIterator,szValue,charsmax(szValue));

		if ( 
			 (equal(szKey, "BLOCK_ABILITY_BLACK_MAG") && iIdAbility == 1000) ||
			 (equal(szKey, "BLOCK_ABILITY_JUGGERNAUT") && iIdAbility == 1001)
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