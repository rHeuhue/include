// Считывание расы игрока
public native_get_user_race(idUser)
{
	return arrIntData[idUser][P_RACE];
}

// Считывание названия расы игрока
public native_get_user_race_name(idUser,szShortRaceName[])
{
	param_convert(2);

	Lang_GetRaceName(arrIntData[idUser][P_RACE], idUser, szShortRaceName, 31, true );
}


// Считывание времени до появления талика
public nativeGetTimeSpawnTalisman(idUser)
{
	new iTimeSpawnTalisman = floatround(TIME_SPAWN_TALISMAN - fTimeSpawnTalismanGlobal);

	return iTimeSpawnTalisman;
}

//Прокачка опыта
public nativeSetPlayerLevel(idUser)
{
	new szPlayerName[32];
	get_user_name(idUser, szPlayerName, 31);
	log_amx("Before XP :%d Race:%d Name^"%s^"", arrIntData[idUser][P_XP], arrIntData[idUser][P_RACE], szPlayerName);
	
	ADMIN_SetLevel(idUser,szPlayerName, 31);

	log_amx("Current XP :%d Race:%d Name^"%s^"", arrIntData[idUser][P_XP], arrIntData[idUser][P_RACE], szPlayerName);

	return PLUGIN_HANDLED;
}

//Выдача талисмана
public nativeGiveTalisman(idUser,iIdTalisman)
{
	new szPlayerName[32];
	get_user_name(idUser, szPlayerName, 31);
	
	ADMIN_GiveTalisman( idUser, szPlayerName, iIdTalisman )

	return PLUGIN_HANDLED;
}


//ID рассы
public nativeGetIdRace(idUser)
{
	return arrIntData[idUser][P_RACE];
}

//Возвращает уровень
public nativeGetLvLRace(idUser)
{
	return arrIntData[idUser][P_LEVEL];
}
 
// Добавление опыта к текущему
public nativeGiveXP(idUser,iXP)
{
	if ( iXP < 0 )
		iXP = 0;

	arrIntData[idUser][P_XP] += iXP;

	XP_Check( idUser );
}