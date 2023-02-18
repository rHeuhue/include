

//Вывод в чат информации о киллере
public fInfoKiller(idKiller,idVictim)
{
	
	new szMessageFlagA[512];
	new szMessageFlagAB[512];
   
	new szFlagsInfoKiller[24];
	get_pcvar_string(CVAR_wc3_info_killer_flags, szFlagsInfoKiller,charsmax(szFlagsInfoKiller));
	new bitInfoKiller = read_flags( szFlagsInfoKiller);
	
   new strNameKiller[33], strNameVictim[33];
   get_user_name(idKiller,strNameKiller,charsmax(strNameKiller));
   get_user_name(idVictim,strNameVictim,charsmax(strNameVictim));

   if( (idKiller != idVictim)  &&  (idKiller != 0) )
  {
 
      if (bitInfoKiller & 1) 
      {
			new iHealth = clHP:getUserHealth(idKiller);
   			new iArmor = clAr:getArmorNum(idKiller);
   		
			if(!SM_IsValidRace( arrIntData[idKiller][P_RACE] ))
					return;
				
			new szShortRaceNameKiller[32];
			Lang_GetRaceName(arrIntData[idKiller][P_RACE],idKiller, szShortRaceNameKiller,charsmax(szShortRaceNameKiller),true);

			format(szMessageFlagA, charsmax(szMessageFlagA), "^x01%L: ^x03%s ^x01[^x04%L:^x03%d ^x04%L:^x03%d ^x04%L:^x03%s ^x04%L:^x03%d ^x01]",
			LANG_PLAYER,"WC3_KILLER",strNameKiller,
			LANG_PLAYER,"WC3_HEALTH",iHealth,
			LANG_PLAYER,"WC3_ARMOR",iArmor,
			LANG_PLAYER,"WC3_RACE",szShortRaceNameKiller,
			LANG_PLAYER, "WORD_LEVEL",arrIntData[idKiller][P_LEVEL]);

			cssbChatColor(idVictim,"%s%s",fTagWar3ft(),szMessageFlagA);
     }

      if (bitInfoKiller & 2) 
      {
			new arrServerStats[8];
			new arrServerHits[8];
			get_user_stats(idKiller,arrServerStats,arrServerHits);
	    
			new iRankPos = get_user_stats(idKiller, arrServerStats, arrServerHits);

			format(szMessageFlagAB, charsmax(szMessageFlagAB), "^x01%L: ^x01[ ^x04%L:^x03%d ^x04%L:^x03%d ^x04%L:^x03%d ^x04%L:^x03%d ^x01]",
			LANG_PLAYER,"WC3_STATS",
			LANG_PLAYER,"WC3_KILLS",arrServerStats[0],
			LANG_PLAYER,"WC3_DEATHS",arrServerStats[1],
			LANG_PLAYER,"WC3_HEADSHOTS",arrServerStats[2],
			LANG_PLAYER,"WC3_RANK",iRankPos);

			cssbChatColor(idVictim,"%s%s",fTagWar3ft(),szMessageFlagAB);
      }

  }

}