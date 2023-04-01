

fCheckBuyCmdWeapons(idUser, szCmd[])
{
	new iItemWpnBuy = fGetCmdWeaponId( szCmd );
	new iTeamUser = get_user_team(idUser);

	if(iItemWpnBuy)
	{
		if(TE_WEAPONS & 1<<iItemWpnBuy )
		{
			if(iTeamUser != TEAM_T )
				return PLUGIN_CONTINUE;
		
		}
		else if(CT_WEAPONS & 1<<iItemWpnBuy )
		{
			if(iTeamUser != TEAM_CT )
				return PLUGIN_CONTINUE;
		
		}

		return efCanBuyItem(idUser, iItemWpnBuy)
	}
	return PLUGIN_CONTINUE
}

public fMenuBuyWeapons(idUser)
{
	if( !is_user_alive(idUser))
		return PLUGIN_CONTINUE;
	
	new iTeamUser = get_user_team(idUser);

	new szSlot[3];
	if(read_argv(1, szSlot, charsmax(szSlot)) == 1)
	{
		new iSlot = szSlot[0] - '0';

		if( 1 <= iSlot <= 8 )
		{
			new iMenuWeapons = cs_get_user_menu(idUser);
			
			new idMenuWpn, iKeys;
			player_menu_info(idUser, idMenuWpn, iKeys);

			if(idMenuWpn != 0 && idMenuWpn != 28)
				return PLUGIN_CONTINUE;

			if(Menu_Buy <= iMenuWeapons <= Menu_BuyItem)
			{
				new iItemWpnBuy;
				switch(iTeamUser)
				{
					case TEAM_T:
						iItemWpnBuy = g_iMenuItemsTe[iMenuWeapons-4][iSlot];

					case TEAM_CT:
						iItemWpnBuy = g_iMenuItemsCt[iMenuWeapons-4][iSlot];
				}
				
				if(iItemWpnBuy)
					return efCanBuyItem(idUser, iItemWpnBuy);
				
			}
		}
	}

	return PLUGIN_CONTINUE;
}

efCanBuyItem(idUser, iItemWpnBuy)
{
	ExecuteForward(mfBuyForward, g_iReturn, idUser, iItemWpnBuy);
	
	if(g_iReturn != PLUGIN_CONTINUE )
		return PLUGIN_HANDLED;
	
	return PLUGIN_CONTINUE;
}

fGetCmdWeaponId( szAlias[] )
{
	new Trie:arrTrieIdCmdWeapons;
	
	arrTrieIdCmdWeapons = TrieCreate();

	TrieSetCell(arrTrieIdCmdWeapons, "p228",		CSW_P228);
	TrieSetCell(arrTrieIdCmdWeapons, "228compact",	CSW_P228);
	TrieSetCell(arrTrieIdCmdWeapons, "scout",		CSW_SCOUT);
	TrieSetCell(arrTrieIdCmdWeapons, "hegren",		CSW_HEGRENADE);
	TrieSetCell(arrTrieIdCmdWeapons, "xm1014",		CSW_XM1014);
	TrieSetCell(arrTrieIdCmdWeapons, "autoshotgun",	CSW_XM1014);
	TrieSetCell(arrTrieIdCmdWeapons, "mac10",		CSW_MAC10);
	TrieSetCell(arrTrieIdCmdWeapons, "aug",			CSW_AUG);
	TrieSetCell(arrTrieIdCmdWeapons, "bullpup",		CSW_AUG);
	TrieSetCell(arrTrieIdCmdWeapons, "sgren",		CSW_SMOKEGRENADE);
	TrieSetCell(arrTrieIdCmdWeapons, "elites",		CSW_ELITE);
	TrieSetCell(arrTrieIdCmdWeapons, "fn57",		CSW_FIVESEVEN);
	TrieSetCell(arrTrieIdCmdWeapons, "fiveseven",	CSW_FIVESEVEN);
	TrieSetCell(arrTrieIdCmdWeapons, "ump45",		CSW_UMP45);
	TrieSetCell(arrTrieIdCmdWeapons, "sg550",		CSW_SG550);
	TrieSetCell(arrTrieIdCmdWeapons, "krieg550",	CSW_SG550);
	TrieSetCell(arrTrieIdCmdWeapons, "galil",		CSW_GALIL);
	TrieSetCell(arrTrieIdCmdWeapons, "defender",	CSW_GALIL);
	TrieSetCell(arrTrieIdCmdWeapons, "famas",		CSW_FAMAS);
	TrieSetCell(arrTrieIdCmdWeapons, "clarion",		CSW_FAMAS);
	TrieSetCell(arrTrieIdCmdWeapons, "usp",			CSW_USP);
	TrieSetCell(arrTrieIdCmdWeapons, "km45",		CSW_USP);
	TrieSetCell(arrTrieIdCmdWeapons, "glock",		CSW_GLOCK18);
	TrieSetCell(arrTrieIdCmdWeapons, "9x19mm",		CSW_GLOCK18)
	TrieSetCell(arrTrieIdCmdWeapons, "awp",			CSW_AWP);
	TrieSetCell(arrTrieIdCmdWeapons, "magnum",		CSW_AWP);
	TrieSetCell(arrTrieIdCmdWeapons, "mp5",			CSW_MP5NAVY);
	TrieSetCell(arrTrieIdCmdWeapons, "smg",			CSW_MP5NAVY);
	TrieSetCell(arrTrieIdCmdWeapons, "m249",		CSW_M249);
	TrieSetCell(arrTrieIdCmdWeapons, "m3",			CSW_M3);
	TrieSetCell(arrTrieIdCmdWeapons, "12gauge",		CSW_M3);
	TrieSetCell(arrTrieIdCmdWeapons, "m4a1",		CSW_M4A1);
	TrieSetCell(arrTrieIdCmdWeapons, "tmp",			CSW_TMP);
	TrieSetCell(arrTrieIdCmdWeapons, "mp",			CSW_TMP);
	TrieSetCell(arrTrieIdCmdWeapons, "g3sg1",		CSW_G3SG1)
	TrieSetCell(arrTrieIdCmdWeapons, "d3au1",		CSW_G3SG1);
	TrieSetCell(arrTrieIdCmdWeapons, "flash",		CSW_FLASHBANG);
	TrieSetCell(arrTrieIdCmdWeapons, "deagle",		CSW_DEAGLE);
	TrieSetCell(arrTrieIdCmdWeapons, "nighthawk",	CSW_DEAGLE);
	TrieSetCell(arrTrieIdCmdWeapons, "sg552",		CSW_SG552);
	TrieSetCell(arrTrieIdCmdWeapons, "krieg552",	CSW_SG552);
	TrieSetCell(arrTrieIdCmdWeapons, "ak47",		CSW_AK47);
	TrieSetCell(arrTrieIdCmdWeapons, "cv47",		CSW_AK47);
	TrieSetCell(arrTrieIdCmdWeapons, "p90",			CSW_P90);
	TrieSetCell(arrTrieIdCmdWeapons, "c90",			CSW_P90);

	TrieSetCell(arrTrieIdCmdWeapons, "vest",		CSW_VEST);
	TrieSetCell(arrTrieIdCmdWeapons, "vesthelm",	CSW_VESTHELM);

	TrieSetCell(arrTrieIdCmdWeapons, "defuser",		CSW_DEFUSER);
	TrieSetCell(arrTrieIdCmdWeapons, "nvgs",		CSW_NVGS);
	TrieSetCell(arrTrieIdCmdWeapons, "shield",		CSW_SHIELD);
	TrieSetCell(arrTrieIdCmdWeapons, "buyammo1",	CSW_PRIMAMMO);
	TrieSetCell(arrTrieIdCmdWeapons, "primammo",	CSW_PRIMAMMO);
	TrieSetCell(arrTrieIdCmdWeapons, "buyammo2",	CSW_SECAMMO);
	TrieSetCell(arrTrieIdCmdWeapons, "secammo",		CSW_SECAMMO);
	
	strtolower(szAlias);

	new iId;
	if(TrieGetCell(arrTrieIdCmdWeapons, szAlias, iId) == false)
	{
		TrieClear(arrTrieIdCmdWeapons);
		TrieDestroy(arrTrieIdCmdWeapons);
		return 0;
	}
	
	TrieClear(arrTrieIdCmdWeapons);
	TrieDestroy(arrTrieIdCmdWeapons);

	return iId;
}

//Событие на закупку оружия в стандартном магазине
public mfClientBuyWeapons(idUser, iItemWpnBuy)
{
	if(bIsUserRace(idUser,RACE_SNIPER))
	{
		if( iItemWpnBuy != CSW_AWP && 
			iItemWpnBuy != CSW_SCOUT &&

			iItemWpnBuy != CSW_P228 &&
			iItemWpnBuy != CSW_ELITE &&
			iItemWpnBuy != CSW_FIVESEVEN &&
			iItemWpnBuy != CSW_USP &&
			iItemWpnBuy != CSW_GLOCK18 &&
			iItemWpnBuy != CSW_DEAGLE &&

			iItemWpnBuy != CSW_HEGRENADE &&
			iItemWpnBuy != CSW_SMOKEGRENADE &&
			iItemWpnBuy != CSW_FLASHBANG &&

			iItemWpnBuy != CSW_VEST &&
			iItemWpnBuy != CSW_VESTHELM &&

			iItemWpnBuy != CSW_DEFUSER	&&
			iItemWpnBuy != CSW_NVGS		&&
			iItemWpnBuy != CSW_SHIELD	&&
			iItemWpnBuy != CSW_PRIMAMMO	&&
			iItemWpnBuy != CSW_SECAMMO
		  )
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_BLOCK_WPN_SNIPER");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

			return PLUGIN_HANDLED;
		}
	}	

//    if( iItemWpnBuy == CSW_AWP && !user_has_weapon(idUser, CSW_AWP))
//    {
//		message_begin( MSG_ONE_UNRELIABLE, get_user_msgid("TextMsg"), .player=idUser )
//		{
//			write_byte( print_center );
//			write_string( "#Alias_Not_Avail" );
//			write_string( "#ArcticWarfareMagnum" );
//		}
//		message_end()

//        return PLUGIN_HANDLED;
//    }

	return PLUGIN_CONTINUE;
}
