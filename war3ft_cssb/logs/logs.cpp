// ******************************************************************
// Логирование
// ******************************************************************

#if MODE_LOG

//Лог повреждений от "магии" (проверка функции WC3_Damage)
clLog:logMagicDamage(const idVictim, const idAttacker, const iDamage,const iBeforeAfter = 0)
{
	new szLogFile[128];
	get_configsdir( szLogFile, charsmax(szLogFile) );
	formatex( szLogFile, charsmax(szLogFile), "%s/war3ft/logs/wc3_magic_damage.log", szLogFile );

	if (!file_exists(szLogFile))
	{
		write_file(szLogFile, "CSSB Warcraft 3 Frozen Throne Private", -1 );
		write_file(szLogFile, "Лог повреждений от ^"магии^" ", -1 );
		write_file(szLogFile, " ", -1 );
	}
	new szCurrentTime[64];
	get_time( "L %m/%d/%Y - %H:%M:%S", szCurrentTime,charsmax(szCurrentTime));

	new szUserNameAttacker[32];
	get_user_name(idAttacker, szUserNameAttacker, charsmax(szUserNameAttacker));
	
	new iCurrentHpAttacker = clHP:getUserHealth(idAttacker);
	new iCurrentHpVictim = clHP:getUserHealth(idVictim);

	if(!iBeforeAfter)
		write_file(szLogFile, "*** Параметры до нанесения повреждений ****", -1 );
	else
		write_file(szLogFile, "*** Параметры после нанесения повреждений ****", -1 );

	new szLogEntry[256];
	formatex(szLogEntry, charsmax(szLogEntry), "%s Ник атакера: ^"<%s>^" Здоровье атакера: ^"<%d>^" Здоровье жертвы: ^"<%d>^" Дамаг: ^"<%d>^" ", 
											   szCurrentTime,szUserNameAttacker,iCurrentHpAttacker,iCurrentHpVictim,iDamage);
	
	write_file(szLogFile, szLogEntry, -1 );
	
}

public clLog:logRaceUndead(const idAttacker,const iCurrentHealth,const Float:fFactor,const iDamage,const iBonus)
{	
	new szLogFile[128];
	get_configsdir( szLogFile, charsmax(szLogFile) );
	formatex( szLogFile, charsmax(szLogFile), "%s/war3ft/logs/wc3_undead.log", szLogFile);

	if (!file_exists(szLogFile))
	{
		write_file(szLogFile, "CSSB Warcraft 3 Frozen Throne Private", -1 );
		write_file(szLogFile, "Лог Нежити", -1 );
		write_file(szLogFile, " ", -1 );
	}

	new szCurrentTime[64];
	get_time( "L %m/%d/%Y - %H:%M:%S", szCurrentTime,charsmax(szCurrentTime));

	new iClipAmmo,iAmmo;
    new iCurWeapon = get_user_weapon(idAttacker,iClipAmmo,iAmmo);

	new szWpnName[64];
	UTIL_GetWeaponName(iCurWeapon, szWpnName, charsmax(szWpnName));

	new szLogEntry[256];
	formatex(szLogEntry, charsmax(szLogEntry), "%s Здоровье атакера: ^"<%d>^" Множитель: ^"<%0.2f>^" Дамаг: ^"<%d>^" Бонус здоровья: ^"<%d>^" Оружие: ^"<%s>^"", 
											   szCurrentTime,iCurrentHealth,fFactor,iDamage,iBonus,szWpnName);
	write_file(szLogFile, szLogEntry, -1 );

}


public clLog:logRaceOrc(const idAttacker,const Float:fFactor,const iDamage,const iBonus)
{	
	new szLogFile[128];
	get_configsdir( szLogFile, charsmax(szLogFile) );
	formatex( szLogFile, charsmax(szLogFile), "%s/war3ft/logs/wc3_orc.log", szLogFile);

	if (!file_exists(szLogFile))
	{
		write_file(szLogFile, "CSSB Warcraft 3 Frozen Throne Private", -1 );
		write_file(szLogFile, "Лог Орка", -1 );
		write_file(szLogFile, " ", -1 );
	}

	new szCurrentTime[64];
	get_time( "L %m/%d/%Y - %H:%M:%S", szCurrentTime,charsmax(szCurrentTime));

	new iClipAmmo,iAmmo;
    new iCurWeapon = get_user_weapon(idAttacker,iClipAmmo,iAmmo);

	new szWpnName[64];
	UTIL_GetWeaponName(iCurWeapon, szWpnName, charsmax(szWpnName));

	new szLogEntry[256];
	formatex(szLogEntry, charsmax(szLogEntry), "%s Множитель: ^"<%0.2f>^" Дамаг: ^"<%d>^" Бонус дамага: ^"<%d>^" Оружие: ^"<%s>^"", 
											   szCurrentTime,fFactor,iDamage,iBonus,szWpnName);
	write_file(szLogFile, szLogEntry, -1 );

}


public clLog:logRaceElf(const idAttacker,const Float:fFactor,const iDamage,const iBonus)
{	
	new szLogFile[128];
	get_configsdir( szLogFile, charsmax(szLogFile) );
	formatex( szLogFile, charsmax(szLogFile), "%s/war3ft/logs/wc3_elf.log", szLogFile);

	if (!file_exists(szLogFile))
	{
		write_file(szLogFile, "CSSB Warcraft 3 Frozen Throne Private", -1 );
		write_file(szLogFile, "Лог Ельфа", -1 );
		write_file(szLogFile, " ", -1 );
	}

	new szCurrentTime[64];
	get_time( "L %m/%d/%Y - %H:%M:%S", szCurrentTime,charsmax(szCurrentTime));

	new iClipAmmo,iAmmo;
    new iCurWeapon = get_user_weapon(idAttacker,iClipAmmo,iAmmo);

	new szWpnName[64];
	UTIL_GetWeaponName(iCurWeapon, szWpnName, charsmax(szWpnName));

	new szLogEntry[256];
	formatex(szLogEntry, charsmax(szLogEntry), "%s Множитель: ^"<%0.2f>^" Дамаг: ^"<%d>^" Бонус дамага: ^"<%d>^" Оружие: ^"<%s>^"", 
											   szCurrentTime,fFactor,iDamage,iBonus,szWpnName);
	write_file(szLogFile, szLogEntry, -1 );

}


public clLog:logRaceBlood(const idAttacker,const Float:fFactor,const iDamage,const iBonus)
{	
	new szLogFile[128];
	get_configsdir( szLogFile, charsmax(szLogFile) );
	formatex( szLogFile, charsmax(szLogFile), "%s/war3ft/logs/wc3_blood.log", szLogFile);

	if (!file_exists(szLogFile))
	{
		write_file(szLogFile, "CSSB Warcraft 3 Frozen Throne Private", -1 );
		write_file(szLogFile, "Лог Кровавого мага", -1 );
		write_file(szLogFile, " ", -1 );
	}

	new szCurrentTime[64];
	get_time( "L %m/%d/%Y - %H:%M:%S", szCurrentTime,charsmax(szCurrentTime));

	new iClipAmmo,iAmmo;
    new iCurWeapon = get_user_weapon(idAttacker,iClipAmmo,iAmmo);

	new szWpnName[64];
	UTIL_GetWeaponName(iCurWeapon, szWpnName, charsmax(szWpnName));

	new szLogEntry[256];
	formatex(szLogEntry, charsmax(szLogEntry), "%s Множитель: ^"<%0.2f>^" Дамаг: ^"<%d>^" Бонус здоровья: ^"<%d>^" Оружие: ^"<%s>^"", 
											   szCurrentTime,fFactor,iDamage,iBonus,szWpnName);
	write_file(szLogFile, szLogEntry, -1 );

}

public clLog:logRaceCrypt(const idAttacker,const Float:fFactor,const iDamage,const iBonus)
{	
	new szLogFile[128];
	get_configsdir( szLogFile, charsmax(szLogFile) );
	formatex( szLogFile, charsmax(szLogFile), "%s/war3ft/logs/wc3_crypt.log", szLogFile);

	if (!file_exists(szLogFile))
	{
		write_file(szLogFile, "CSSB Warcraft 3 Frozen Throne Private", -1 );
		write_file(szLogFile, "Лог Лорд мертвых", -1 );
		write_file(szLogFile, " ", -1 );
	}

	new szCurrentTime[64];
	get_time( "L %m/%d/%Y - %H:%M:%S", szCurrentTime,charsmax(szCurrentTime));

	new iClipAmmo,iAmmo;
    new iCurWeapon = get_user_weapon(idAttacker,iClipAmmo,iAmmo);

	new szWpnName[64];
	UTIL_GetWeaponName(iCurWeapon, szWpnName, charsmax(szWpnName));

	new szLogEntry[256];
	formatex(szLogEntry, charsmax(szLogEntry), "%s Множитель: ^"<%0.2f>^" Дамаг: ^"<%d>^" Бонус здоровья: ^"<%d>^" Оружие: ^"<%s>^"", 
											   szCurrentTime,fFactor,iDamage,iBonus,szWpnName);
	write_file(szLogFile, szLogEntry, -1 );

}

public clLog:logRaceDeathKnight(const idAttacker,const Float:fFactor,const Float:fDamage,const Float:fBonus)
{	
	new szLogFile[128];
	get_configsdir( szLogFile, charsmax(szLogFile) );
	formatex(szLogFile, charsmax(szLogFile), "%s/war3ft/logs/wc3_death_knight.log", szLogFile);

	if (!file_exists(szLogFile))
	{
		write_file(szLogFile, "CSSB Warcraft 3 Frozen Throne Private", -1 );
		write_file(szLogFile, "Лог Рыцарь смерти", -1 );
		write_file(szLogFile, " ", -1 );
	}

	new szCurrentTime[64];
	get_time("L %m/%d/%Y - %H:%M:%S", szCurrentTime,charsmax(szCurrentTime));

	new iClipAmmo,iAmmo;
    new iCurWeapon = get_user_weapon(idAttacker,iClipAmmo,iAmmo);

	new szWpnName[64];
	UTIL_GetWeaponName(iCurWeapon, szWpnName, charsmax(szWpnName));

	new szLogEntry[256];
	formatex(szLogEntry, charsmax(szLogEntry), "%s Множитель: ^"<%0.2f>^" Дамаг: ^"<%0.2f>^" Бонус дамага: ^"<%0.2f>^" Оружие: ^"<%s>^"", 
											   szCurrentTime,fFactor,fDamage,fBonus,szWpnName);
	write_file(szLogFile, szLogEntry, -1 );

}

public clLog:logRaceDeathKnight2(const Float:fFactor,const iBonus)
{	
	new szLogFile[128];
	get_configsdir( szLogFile, charsmax(szLogFile) );
	formatex(szLogFile, charsmax(szLogFile), "%s/war3ft/logs/wc3_death_knight.log", szLogFile);

	if (!file_exists(szLogFile))
	{
		write_file(szLogFile, "CSSB Warcraft 3 Frozen Throne Private", -1 );
		write_file(szLogFile, "Лог Рыцарь смерти", -1 );
		write_file(szLogFile, " ", -1 );
	}

	new szCurrentTime[64];
	get_time("L %m/%d/%Y - %H:%M:%S", szCurrentTime,charsmax(szCurrentTime));

	new szLogEntry[256];
	formatex(szLogEntry, charsmax(szLogEntry), "%s Множитель: ^"<%0.2f>^" Бонус здоровья: ^"<%d>^" ", 
											   szCurrentTime,fFactor,iBonus);
	write_file(szLogFile, szLogEntry, -1 );

}


#endif