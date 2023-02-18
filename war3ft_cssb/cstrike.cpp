/*
*	Counter-Strike and Condition Zero only functions
*/

public on_EndRound()
{

	if ( !WC3_Check() )
		return;
	
	g_EndRound = true;
	
	new players[32], numplayers, i;
	get_players( players, numplayers );
	for ( i = 0; i < numplayers; i++ )
	{
		new idUser = players[i];

		UTIL_AutoHideMenu(idUser);

	}//for

	// Save XP at the end of the round?
	if ( get_pcvar_num( CVAR_wc3_save_end_round ) )
	{
		// Threaded saves on end round!
		DB_SaveAll( true );
	}
	
	return;
}

// Called when freezetime is over
public on_FreezeTimeComplete()
{

	if ( !WC3_Check() )
		return;

	g_freezeTime = false;
	
	return;
}

public on_TerroristWin()
{

	if ( !WC3_Check() )
	{
		return;
	}

	XP_WinRound( TEAM_T );

	//Отображение победителя в конце раунда
	fShowWinnPlayer(TEAM_T);

	return;
}

public on_CTWin()
{
	if ( !WC3_Check() )
	{
		return;
	}

	XP_WinRound( TEAM_CT );

	//Отображение победителя в конце раунда
	fShowWinnPlayer(TEAM_CT);

	return;
}


public _CS_MinModelsLoop()
{
	if ( !WC3_Check() )
	{
		return;
	}

	if ( get_pcvar_num( CVAR_wc3_query_client ) )
	{
		new iPlayers[32], iNumPlayers, i;
		get_players( iPlayers, iNumPlayers, "c" );
		
		for ( i = 0; i < iNumPlayers; i++ )
		{
			query_client_cvar( iPlayers[i], "cl_minmodels", "_CS_CheckMinModelsValue" );
		}
	}
}

public _CS_CheckMinModelsValue( idUser, const cvar[], const value[] )
{
	if ( equali( cvar,"cl_minmodels" ) && strcmp( value, "0" ) )
	{
		client_cmd( idUser, "echo ^"======== CSSB Warcraft 3 Frozen Throne Private ========^"" );
		format(szMessage, charsmax(szMessage), "echo ^"%L^"",LANG_PLAYER,"CLIENT_KICK_CL_MODELS_1");
		client_cmd( idUser, szMessage);
		format(szMessage, charsmax(szMessage), "echo ^"%L^"",LANG_PLAYER,"CLIENT_KICK_CL_MODELS_2");
		client_cmd( idUser, szMessage);
		client_cmd( idUser, "echo ^"=========================================^"" );
		format(szMessage, charsmax(szMessage), "kick #%d ^"%L^"",get_user_userid( idUser ),LANG_PLAYER,"CLIENT_KICK_CL_MODELS_3");	
		server_cmd( szMessage );
	} 
}

// Function called when a user's armor changes
public on_Battery( idUser )
{	
	if ( !WC3_Check() )
	{
		return;
	}
	
	if ( !bIgnoreArmorSet[idUser] )
	{
		// Store the previous value (we do this b/c the Battery event is triggered (and set to 0) before weapon reincarnation)
		arrIntData[idUser][P_LASTARMOR] = arrIntData[idUser][P_ARMORONDEATH];

		arrIntData[idUser][P_ARMORONDEATH] = read_data( 1 );
	}

	return;
}

public on_ArmorType(idUser)
{
	if (!WC3_Check())
		return;
		
	new iCurrentArmor = clAr:getUserArmor(idUser,g_ArmorType[idUser]);
	arrIntData[idUser][P_ARMORONDEATH] = iCurrentArmor;

	return;
}

// Event triggered when you look at another player
public on_ShowStatus(idUser)
{
	if (!WC3_Check())
		return;

	//Очищает когда слева внизу отображает здоровье на кого навел (мусор короче :) )
	Create_StatusText(idUser,0,"");
	UTIL_ClearHudChannel(idUser, HUD_SHOWSTATUS);

	new idTarget = read_data( 2 );
	if(is_user_alive(idUser) && is_user_connected(idUser) &&
		is_user_alive(idTarget) && is_user_connected(idTarget))
		{
			//Отображение текущего здоровья и брони
			new iCurrentHealth =  clHP:getUserHealth(idUser);
			new iCurrentArmor = clAr:getArmorNum(idUser);

			if(iCurrentHealth > 255 || iCurrentArmor > 255)
			{
				new szMsgHealthArmor[256];
				formatex(szMsgHealthArmor, charsmax(szMsgHealthArmor), 
				 "%L: %d | %L: %d",LANG_PLAYER,"CURRENT_HEALTH",iCurrentHealth,
	 								   LANG_PLAYER,"WORD_ARMOR",iCurrentArmor);

				Create_StatusText(idUser, 0, szMsgHealthArmor);
			}


			new iTargetTeam = get_user_team( idTarget );
			new iViewerTeam = get_user_team( idUser );

			// Same team check
			if ( iViewerTeam == iTargetTeam )
			{
				// Check if your teammate looks like the enemy!
				if ( arrBoolData[idTarget][PB_SKINSWITCHED] )
				{
					new szMessageDontShot[256];
					format(szMessageDontShot, charsmax(szMessageDontShot),
						"%L",LANG_PLAYER, "HES_ON_YOUR_TEAM_DONT_SHOOT");

					set_dhudmessage(79, 79, 79 ,-1.0,0.30,0, 0.01, 1.0, 0.01, 0.01);
					show_dhudmessage(idUser, szMessageDontShot);
					
					client_cmd( idUser, "speak %s", arrStrSounds[SOUND_ANTEND] );
				}
			}

		// Отображение информации на экране при наведении прицелом
		if ( get_pcvar_num( CVAR_wc3_show_player ) )
		{
				new szTargetName[32];
				get_user_name(idTarget, szTargetName,charsmax(szTargetName));
							
				if(!SM_IsValidRace( arrIntData[idTarget][P_RACE] ))
					return;
				
				new szShortRaceNameTarget[32];
				Lang_GetRaceName(arrIntData[idTarget][P_RACE], idUser, szShortRaceNameTarget,charsmax(szShortRaceNameTarget),true);
			
				new szMessageStatus[256];

				new iColorRGB_TEAM_T[3];
				iColorRGB_TEAM_T[0] = 255;
				iColorRGB_TEAM_T[1] = 69;
				iColorRGB_TEAM_T[2] = 0;

				new iColorRGB_TEAM_CT[3];
				iColorRGB_TEAM_CT[0] = 58;
				iColorRGB_TEAM_CT[1] = 95;
				iColorRGB_TEAM_CT[2] = 205;
				
				if(iViewerTeam == TEAM_T)//Если наводящий курсор из команды террористов
				{
					if(iTargetTeam == TEAM_T)
					{
						format(szMessageStatus, charsmax(szMessageStatus), 
						"%s ^n%L %d %L %d ^n%L %s ^n%L %d",
						szTargetName,
						LANG_PLAYER, "WC3_HEALTH",
						clHP:getUserHealth(idTarget),
						LANG_PLAYER, "WC3_ARMOR",
						clAr:getArmorNum(idTarget),
						LANG_PLAYER, "WC3_RACE",
						szShortRaceNameTarget,				
						LANG_PLAYER, "WORD_LEVEL",
						arrIntData[idTarget][P_LEVEL]);
											
						set_hudmessage(iColorRGB_TEAM_T[0],iColorRGB_TEAM_T[1],iColorRGB_TEAM_T[2], -1.0, 0.60, 0, 0.01, 3.0, 0.01, 0.01, HUD_SHOWSTATUS );
						show_hudmessage(idUser,szMessageStatus);
						
					}
					if(iTargetTeam == TEAM_CT)
					{
						format(szMessageStatus, charsmax(szMessageStatus), 
						"%s  ^n%L %s ^n%L %d",
						szTargetName,
						LANG_PLAYER, "WC3_RACE",
						szShortRaceNameTarget,				
						LANG_PLAYER, "WORD_LEVEL",
						arrIntData[idTarget][P_LEVEL]);
						
						set_hudmessage(iColorRGB_TEAM_CT[0],iColorRGB_TEAM_CT[1],iColorRGB_TEAM_CT[2], -1.0, 0.60, 0, 0.01, 3.0, 0.01, 0.01, HUD_SHOWSTATUS );
						show_hudmessage(idUser,szMessageStatus);
					}
				}

				if(iViewerTeam == TEAM_CT)//Если наводящий курсор из команды коунтер-террористов
				{
					if(iTargetTeam == TEAM_T)
					{
						format(szMessageStatus, charsmax(szMessageStatus), 
						"%s  ^n%L %s ^n%L %d",
						szTargetName,
						LANG_PLAYER, "WC3_RACE",
						szShortRaceNameTarget,				
						LANG_PLAYER, "WORD_LEVEL",
						arrIntData[idTarget][P_LEVEL]);
						
						set_hudmessage(iColorRGB_TEAM_T[0],iColorRGB_TEAM_T[1],iColorRGB_TEAM_T[2], -1.0, 0.60, 0, 0.01, 3.0, 0.01, 0.01, HUD_SHOWSTATUS );
						show_hudmessage(idUser,szMessageStatus);
					}
					if(iTargetTeam == TEAM_CT)
					{
					
						format(szMessageStatus, charsmax(szMessageStatus), 
						"%s ^n%L %d %L %d ^n%L %s ^n%L %d",
						szTargetName,
						LANG_PLAYER, "WC3_HEALTH",
						clHP:getUserHealth(idTarget),
						LANG_PLAYER, "WC3_ARMOR",
						clAr:getArmorNum(idTarget),
						LANG_PLAYER, "WC3_RACE",
						szShortRaceNameTarget,				
						LANG_PLAYER, "WORD_LEVEL",
						arrIntData[idTarget][P_LEVEL]);
					
						set_hudmessage(iColorRGB_TEAM_CT[0],iColorRGB_TEAM_CT[1],iColorRGB_TEAM_CT[2], -1.0, 0.60, 0, 0.01, 3.0, 0.01, 0.01, HUD_SHOWSTATUS );
						show_hudmessage(idUser,szMessageStatus);
					}
				}

		}//if ( get_pcvar_num( CVAR_wc3_show_player ) )

	 }//if(is_user_alive(idUser) && is_user_connected(idUser)

	return;
}

// This is called when the user is no longer viewing the player
public on_HideStatus(idUser)
{
	if ( !WC3_Check() )
	{
		return;
	}

	if ( get_pcvar_num( CVAR_wc3_show_player ) && !g_freezeTime )
	{
		UTIL_ClearHudChannel( idUser, HUD_SHOWSTATUS );
		UTIL_ClearDHudChannel( idUser );
	}

	ClearSyncHud(idUser, msgSyncObj);
}

// Function is called when buytime is over
public _CS_BuyTimeOver()
{
	g_buyTime = false;
}

public on_WeapPickup( idUser )
{ 

	if ( !WC3_Check() )
	{
		return;
	}

	SHARED_SaveWeapons( idUser );

	return;
}

public on_GameRestart()
{
	if ( !WC3_Check() )
		return;
	
	// Save all XP on game restart - do not do this threaded or it might take 300 years
	DB_SaveAll(false);

	g_GameRestarting = true;

	sm4_4_2_evRoundRestart();

	iRoundCount = 0;

	return;
}

// From war3x
public on_Zoom(idUser)
{

	if ( !WC3_Check() )
	{
		return;
	}

	if ( read_data( 1 ) < 90 )
	{
		g_bPlayerZoomed[idUser] = true;
	}

	else
	{
		g_bPlayerZoomed[idUser] = false;
	}

	// We will need to change the user's speed on zooming
	SHARED_SetSpeed( idUser );

	return;
}

public on_BombPlanting( idUser )
{
	arrBoolData[idUser][PB_ISPLANTING] = true;
}

public on_BombStopPlanting( idUser )
{
	arrBoolData[idUser][PB_ISPLANTING] = false;
}
