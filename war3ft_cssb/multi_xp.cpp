

//Активация двойного опыта
public fActiveDoubleXP()//добавлена в events.inl (public EVENT_NewRound())
{
	
	if (iMultiXPOnOff <= 0)
		return;

	//Обнуление двойного активации опыта
	bDoubleXPActive = false;

	new szCurrentTime[31];
	get_time("%H",szCurrentTime,charsmax(szCurrentTime));
	new iHour = str_to_num(szCurrentTime);

	for(new i = 0; i < MAX_HOUR; i++)
	{
		new iMultiXPHour = ArrayGetCell(arrIntMultiXPHourData,i);

		if(iHour == LIST_TIME[i] && iMultiXPHour == ON)
		{
			bDoubleXPActive = true;
			break;
		}
	}
}

public mxp_ClientPutinserver(idUser)//добавлена в cssbWar3ftMod.sma ( public client_putinserver( idUser ) )
{
	
	if ( idUser >= TASK_MULTIXP )
		idUser -= TASK_MULTIXP;

	fActiveDoubleXP();

	if(bDoubleXPActive == true)
	{
		new szShowMsgMultiXP[255];
		format(szShowMsgMultiXP, charsmax(szShowMsgMultiXP), "%L",LANG_PLAYER,"WC3_MULTI_XP_ACTIVE",iBonusFactorXP);
		set_dhudmessage(119,136,153,-1.0,-1.0,2,0.0,2.0,0.02,0.02);
		show_dhudmessage(idUser, szShowMsgMultiXP);

		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szShowMsgMultiXP);
	}

}
