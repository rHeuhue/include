// ******************************************************************
// 
// ******************************************************************

public client_command(idUser)
{
	if(!is_user_connected(idUser)) 
		return PLUGIN_CONTINUE;

	//Снайпер
	if(is_user_alive(idUser) && bIsUserRace(idUser,RACE_SNIPER))
	{
		// Отлов команд на закупку (Оружие)
		new szCommand[13];
		if(read_argv(0, szCommand, charsmax(szCommand)) < 12 )
			return fCheckBuyCmdWeapons(idUser, szCommand);
	}

	return PLUGIN_CONTINUE;
}
