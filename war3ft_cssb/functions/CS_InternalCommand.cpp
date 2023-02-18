// ******************************************************************
// 
// ******************************************************************

public CS_InternalCommand(idUser, const szCommand[])
{
	if(!is_user_connected(idUser)) 
		return PLUGIN_CONTINUE;

	//Снайпер
	if(is_user_alive(idUser) && bIsUserRace(idUser,RACE_SNIPER))
	{
		// Отлов команд на закупку (Оружие)
		new szCmd[13];
		if(copy(szCmd, charsmax(szCmd), szCommand) < 12 )
			return fCheckBuyCmdWeapons(idUser, szCmd);
	}
		
	return PLUGIN_CONTINUE;
}