// ******************************************************************
// 
// ******************************************************************

public CS_InternalCommand(idUser, const szCommand[])
{
	if(!is_user_connected(idUser)) 
		return PLUGIN_CONTINUE;

	//�������
	if(is_user_alive(idUser) && bIsUserRace(idUser,RACE_SNIPER))
	{
		// ����� ������ �� ������� (������)
		new szCmd[13];
		if(copy(szCmd, charsmax(szCmd), szCommand) < 12 )
			return fCheckBuyCmdWeapons(idUser, szCmd);
	}
		
	return PLUGIN_CONTINUE;
}