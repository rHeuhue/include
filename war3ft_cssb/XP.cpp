/*
*	XP Functions
*/

#define XP_NEARBY_RADIUS		250

// START FROM CSX.INC - This is a hack b/c we can't include CSX in the same plugin
forward bomb_planting(planter);
forward bomb_planted(planter);
forward bomb_defusing(defuser);
forward bomb_defused(defuser);
// END FROM CSX.INC



XP_Configure()
{
	
	fWpnXPMultiplier[CSW_USP			]	= 1.0;
	fWpnXPMultiplier[CSW_DEAGLE			]	= 1.0;
	fWpnXPMultiplier[CSW_GLOCK18		]	= 1.0;
	fWpnXPMultiplier[CSW_ELITE			]	= 1.0;
	fWpnXPMultiplier[CSW_P228			]	= 1.0;
	fWpnXPMultiplier[CSW_FIVESEVEN		]	= 1.0;

	fWpnXPMultiplier[CSW_XM1014			]	= 1.0;
	fWpnXPMultiplier[CSW_M3				]	= 1.0;

	fWpnXPMultiplier[CSW_MP5NAVY		]	= 1.0;
	fWpnXPMultiplier[CSW_UMP45			]	= 1.0;
	fWpnXPMultiplier[CSW_P90			]	= 1.0;
	fWpnXPMultiplier[CSW_TMP			]	= 1.0;
	fWpnXPMultiplier[CSW_MAC10			]	= 1.0;
	fWpnXPMultiplier[CSW_GALIL			]	= 1.0;
	fWpnXPMultiplier[CSW_FAMAS			]	= 1.0;

	fWpnXPMultiplier[CSW_AWP			]	= 1.0;
	fWpnXPMultiplier[CSW_M4A1			]	= 1.0;
	fWpnXPMultiplier[CSW_AK47			]	= 1.0;
	fWpnXPMultiplier[CSW_AUG			]	= 1.0;
	fWpnXPMultiplier[CSW_SG552			]	= 1.0;
	fWpnXPMultiplier[CSW_G3SG1			]	= 1.0;
	fWpnXPMultiplier[CSW_SG550			]	= 1.0;
	fWpnXPMultiplier[CSW_M249			]	= 1.0;
	fWpnXPMultiplier[CSW_SCOUT			]	= 1.0;

	fWpnXPMultiplier[CSW_HEGRENADE		]	= 1.0;
	fWpnXPMultiplier[CSW_KNIFE			]	= 1.0;

	fWpnXPMultiplier[CSW_C4				]	= 1.0;
	fWpnXPMultiplier[CSW_SMOKEGRENADE	]	= 1.0;
	fWpnXPMultiplier[CSW_FLASHBANG		]	= 1.0;


	fWpnXPMultiplier[CSW_WORLDSPAWN		]	= 0.0;
	fWpnXPMultiplier[CSW_LIGHTNING		]	= 1.0;
	fWpnXPMultiplier[CSW_SUICIDE		]	= 1.0;
	fWpnXPMultiplier[CSW_IMMOLATE		]	= 1.0;
	fWpnXPMultiplier[CSW_LOCUSTS		]	= 1.0;
	fWpnXPMultiplier[CSW_SERPENTWARD	]	= 1.0;
	fWpnXPMultiplier[CSW_SHADOW			]	= 1.0;	
	fWpnXPMultiplier[CSW_THORNS			]	= 1.0;
	fWpnXPMultiplier[CSW_CARAPACE		]	= 1.0;
	fWpnXPMultiplier[CSW_CARRION		]	= 1.0;
	fWpnXPMultiplier[CSW_ORB			]	= 1.0;
	fWpnXPMultiplier[CSW_CONCOCTION		]	= 1.0;
	fWpnXPMultiplier[CSW_BANISH			]	= 1.0;
	fWpnXPMultiplier[CSW_BLIZZARD		]	= 1.0;
	fWpnXPMultiplier[CSW_ICE_SPLINTERS	]	= 1.0;
	fWpnXPMultiplier[CSW_CHAM_FLAME_STRIKE]	= 1.0;
	fWpnXPMultiplier[CSW_DEATHCOIL	]		= 1.0; //sm4
	fWpnXPMultiplier[CSW_POISON]			= 1.0;
	fWpnXPMultiplier[CSW_WORDDEATH]			= 1.0;
	fWpnXPMultiplier[CSW_BLOOD_RAGE]		= 1.0;
	fWpnXPMultiplier[CSW_BLOOD_RITE]		= 1.0;
	
	
}

// Called when a user begins defusing the bomb
public bomb_defusing( defuser )
{
	if ( !WC3_Check() )
		return;
	

	// Make sure that this isn't called more than once per round
	if ( !bHasBegunPlantingOrDefusing[defuser] )
	{
		new iBonusXP = XP_Give( defuser, iDefusingBomb );

		if ( iBonusXP != 0 )
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_DEFUSING_BOMB",iBonusXP);	
			cssbChatColor(defuser,"%s%s",fTagWar3ft(),szMessage);
		}
	}

	bHasBegunPlantingOrDefusing[defuser] = true;
}

// Called when a user defuses the bomb
public bomb_defused( defuser )
{
	

	if ( !WC3_Check() )
		return;
	
	new iBonusXP = XP_Give( defuser, iDefusedBomb );

	if ( iBonusXP != 0 )
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_DEFUSED_BOMB",iBonusXP);	
		cssbChatColor(defuser,"%s%s",fTagWar3ft(),szMessage);
	}

	g_iPlayerRole[defuser] = 0;
}

// Called when a user begins planting the bomb
public bomb_planting( planter )
{
	
	if ( !WC3_Check() )
		return;
	
	// Make sure that this isn't called more than once per round
	if ( !bHasBegunPlantingOrDefusing[planter] )
	{
		new iBonusXP = XP_Give( planter, iPlantingBomb );

		if ( iBonusXP != 0 )
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_PLANTING_BOMB",iBonusXP);	
			cssbChatColor(planter,"%s%s",fTagWar3ft(),szMessage);
		}
	}

	g_iPlayerRole[planter] = PLR_BOMB_PLANTER;
	bHasBegunPlantingOrDefusing[planter] = true;
}

// Called when a user has planted the bomb
public bomb_planted( planter )
{
	

	if ( !WC3_Check() )
		return;
	
	new iBonusXP = XP_Give( planter, iPlantBomb );

	if ( iBonusXP != 0 )
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_PLANTED_BOMB",iBonusXP);	
		cssbChatColor(planter,"%s%s",fTagWar3ft(),szMessage);
	}

	g_iPlayerRole[planter] = 0;
	arrBoolData[planter][PB_ISPLANTING] = false;

	// Serpent Ward Check
	SH_BombPlanted();
}

// Called on certain player events
public on_PlayerAction()
{
	

	if ( !WC3_Check() )
		return;
	
	new sArg[64], sAction[64], sName[64];
	new iUserId, idUser;

	read_logargv( 0,sArg,64 );
	read_logargv( 2,sAction,64 );
	parse_loguser( sArg,sName,64,iUserId );
	idUser = find_player( "k", iUserId );

	if ( idUser == 0 )
	{
		return;
	}

	// If the round is over do not award XP!
	if ( g_EndRound )
	{
		return;
	}

	// Spawned with the bomb 
	if (equal(sAction,"Spawned_With_The_Bomb"))
	{
		g_iPlayerRole[idUser] = PLR_BOMB_CARRIER;
		new iBonusXP = XP_Give( idUser, iSpawnBomb );

		if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_objectives))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_SPAWNING_WITH_BOMB",iBonusXP);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	// Dropped bomb 
	else if (equal(sAction,"Dropped_The_Bomb"))
	{
		g_iPlayerRole[idUser] = 0;
		new iBonusXP = XP_Give( idUser, -1 * iBombPickup );

		if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_objectives))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_LOST_BOMB",-1 * iBonusXP);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	// Picked up bomb 
	else if (equal(sAction,"Got_The_Bomb"))
	{ 
		g_iPlayerRole[idUser] = PLR_BOMB_CARRIER;
		new iBonusXP = XP_Give( idUser, iBombPickup );

		if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_objectives))
		{
			format(szMessage, charsmax(szMessage),"%L",LANG_PLAYER,"AWARD_FOR_PICKING_UP_BOMB",iBonusXP);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	// Hostage touched 
	else if (equal(sAction,"Touched_A_Hostage"))
	{
		g_iPlayerRole[idUser] = PLR_HOSTAGE_RESCUER;
		new iBonusXP = XP_Give( idUser, iTouchHostage );

		if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_objectives))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_BEGINNING_HOSTAGE_RESCUE",iBonusXP);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	// Hostage rescued 
	else if (equal(sAction,"Rescued_A_Hostage"))
	{
		new iBonusXP = XP_Give( idUser, iRescueHostage );

		if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_objectives))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_RESCUING_HOSTAGE",iBonusXP);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	// Hostage killed 
	else if (equal(sAction,"Killed_A_Hostage"))
	{
		new iBonusXP = XP_Give( idUser, -1 * iKillHostage );

		if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_objectives))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_KILLING_HOSTAGE",-1 * iBonusXP);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	// VIP spawn 
	else if (equal(sAction,"Became_VIP"))
	{ 
		g_iPlayerRole[idUser] = PLR_VIP;
		new iBonusXP = XP_Give( idUser, iSpawnVip );

		if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_objectives))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_SPAWN_AS_VIP",iBonusXP);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	// VIP escaped 
	else if (equal(sAction,"Escaped_As_VIP"))
	{
		new iBonusXP = XP_Give( idUser, iEscapeVip );

		if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_objectives))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_ESCAPED_VIP",iBonusXP);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	
}

XP_onDeath( idVictim, idAttacker, iWeaponIndex, iHeadshot )
{

	

	// We don't want to give XP to the world
	if ( idAttacker == 0 )
	{
		return;
	}

	// We don't want to give XP to suiciders
	else if ( idAttacker == idVictim )
	{
		return;
	}
	
	new iLevel = arrIntData[idVictim][P_LEVEL]
	new iBonusXP, iXP = floatround( XP_GivenByLevel( iLevel ) * fWpnXPMultiplier[iWeaponIndex] );

	// Check for a team kill
	if ( get_user_team( idAttacker ) == get_user_team( idVictim ) )
	{
		// Remove XP since he killed his teammate
		iBonusXP = XP_Give( idAttacker, -1 * iXP );

		// This message should be displayed no matter what XP_kill_objectives is, b/c it's a no-no
		if ( iBonusXP != 0 )
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_TEAM_KILL",-1 * iBonusXP);	
			cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);
		}

	}

	// Otherwise the player killed the other team
	else
	{
		// Award XP for a kill
		iBonusXP = XP_Give( idAttacker, iXP );
		
		if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_kill_obj))
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_ENEMY_KILL",iBonusXP);	
			cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);
		}

		// User had a headshot?  Give bonus XP!
		if ( iHeadshot )
		{
			iBonusXP = XP_Give( idAttacker, iKillHeadshot );
			
			if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_kill_obj))
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_KILL_HEADSHOT",iBonusXP);
				cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);
			}
		}

		new iAssistLevel, iAssistXP, iVictimMaxHealth;
		new Float:fMultiplier;

		// Award XP for other people doing damage to this victim
		for ( new i = 0; i < MAXPLAYERS; i++ )
		{
			// Then this player dealt some damage to this player this round
			if ( g_iDamageDealt[i][idVictim] > 0 && idAttacker != i )
			{
				iVictimMaxHealth = clHP:getRaceMaxHealth(idVictim);
				fMultiplier = float( g_iDamageDealt[i][idVictim] ) / float( iVictimMaxHealth );
				
				iAssistLevel = arrIntData[i][P_LEVEL];
				iAssistXP = XP_GivenByLevel( iAssistLevel );

				// Need a ratio of XP to award to person who dealt damage
				iBonusXP = XP_Give( i, ( floatround( float( iAssistXP ) * fMultiplier ) / 2 ) );

				if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_kill_obj))
				{
					format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_KILL_ASSIST",iBonusXP);
					cssbChatColor(i,"%s%s",fTagWar3ft(),szMessage);
				}

				// victim may respawn, so reset the counter
				g_iDamageDealt[i][idVictim] = 0;
			}
		}

		// User killed a hostage rescuer
		if ( g_iPlayerRole[idVictim] == PLR_HOSTAGE_RESCUER )
		{
			iBonusXP = XP_Give( idAttacker, iKillHostageSaver );
			
			if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_kill_obj))
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_KILL_HOSTAGE_RESCUER",iBonusXP);
				cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		// User killed the bomb defuser
		else if ( g_iPlayerRole[idVictim] == PLR_BOMB_DEFUSER )
		{
			iBonusXP = XP_Give( idAttacker, iKillDefuser );
			
			if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_kill_obj))
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_KILL_DEFUSER",iBonusXP);
				cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		// User killed the bomb planter
		else if ( g_iPlayerRole[idVictim] == PLR_BOMB_PLANTER )
		{
			iBonusXP = XP_Give( idAttacker, iKillPlanter );
			
			if ( iBonusXP != 0 && get_pcvar_num( CVAR_wc3_show_kill_obj ) )
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_KILL_PLANTER",iBonusXP);
				cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		// User killed the bomb carrier
		else if ( g_iPlayerRole[idVictim] == PLR_BOMB_CARRIER )
		{
			iBonusXP = XP_Give( idAttacker, iKillBombCarrier );
			
			if ( iBonusXP != 0 && get_pcvar_num(CVAR_wc3_show_kill_obj))
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_KILL_BOMB_CARRIER",iBonusXP);
				cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);
			}
		}
		// user killed the VIP
		else if ( g_iPlayerRole[idVictim] == PLR_VIP )
		{
			iBonusXP = XP_Give( idAttacker, iKillVip );
			
			if ( iBonusXP != 0 && get_pcvar_num( CVAR_wc3_show_objectives ) )
			{
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_KILL_VIP",iBonusXP);
				cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);
			}
		}
				
		g_iPlayerRole[idVictim] = 0;
	}
}


XP_WinRound( iWinner )
{
	

	new players[32], numberofplayers, i, idUser;
	get_players( players, numberofplayers );

	for ( i = 0; i < numberofplayers; i++ )
	{
		idUser = players[i];

		// Is the user on the correct team?
		if ( get_user_team( idUser ) == iWinner )
		{

			new iBonusXP = XP_Give( idUser, iWinRound );

			if ( get_pcvar_num(CVAR_wc3_show_objectives))
			{				
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"AWARD_FOR_WINNING_ROUND",iBonusXP);
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
		}
	}
}

XP_GetByLevel( iLevel )
{
	
	if ( iLevel < 0 || iLevel > iMaxLevels )
		return 0;
	
	// Change based on XP multiplier!
	new Float:fXPMult = get_pcvar_float( CVAR_wc3_xp_multiplier );

	new iXpSave = ArrayGetCell(arrXpSave,iLevel);
	return floatround( iXpSave * fXPMult );
		
}


XP_GivenByLevel( iLevel )
{
	

	if ( iLevel < 0 || iLevel > iMaxLevels )
		return 0;
	
	new iXpKillSave = ArrayGetCell(arrXpKillSave,iLevel);
	return iXpKillSave;
	
}

bool:XP_MinPlayers()
{
	new iNum = 0;

	// Don't ignore bots
	if ( get_pcvar_num( CVAR_wc3_ignore_bots ) == 0 )
	{
		iNum = get_playersnum();
	}
	// Ignore bots, spectators, and HLTV
	else
	{
		new players[32];
		new iNumCT;
		get_players( players, iNum, "ce", "TERRORIST" );
		get_players( players, iNumCT, "ce", "CT" );
		iNum += iNumCT;
	}

	if ( iNum < get_pcvar_num( CVAR_wc3_min_players ) )
	{
		return false;
	}

	return true;
}

// Function will verify if the user's level/information is correct and checks to see if the user has gained a level
XP_Check( idUser, bShowGained = true )
{
	

	new iOldLevel = arrIntData[idUser][P_LEVEL], i;
	
	// Make sure the user doesn't have negative experience
	if ( arrIntData[idUser][P_XP] < 0 )
	{
		arrIntData[idUser][P_XP] = 0;
	}

	// Determine what the user's level should be
	for ( i = 0; i <= iMaxLevels; i++ )
	{
		// User has enough XP to advance to the next level
		if ( arrIntData[idUser][P_XP] >= XP_GetByLevel( i ) )
		{
			arrIntData[idUser][P_LEVEL] = i;
		}

		// On this increment the user doesn't have enough XP to advance to the next level
		else
		{
			break;
		}
	}

	// User gained a level
	if ( arrIntData[idUser][P_LEVEL] > iOldLevel && arrIntData[idUser][P_RACE] != 0 && bShowGained )
	{
		WC3_StatusText( idUser, TXT_TOP_CENTER, "%L", LANG_PLAYER, "YOU_GAINED_A_LEVEL" );
		
		// Only play the sound if the user is alived!!
		if ( is_user_alive( idUser ) )
		{
			emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_LEVELUP], 1.0, ATTN_NORM, 0, PITCH_NORM );


		}
	}

	// We might need to lower the skills the user has ( can occur if you load XP info from a database and the XP multiplier has changed )
	new iSkillsUsed = SM_TotalSkillPointsUsed( idUser );
	new iSkillID, iSkillLevel;
	new bool:bSkillRemoved = false;

	while ( iSkillsUsed > arrIntData[idUser][P_LEVEL] )
	{
		// We might need to remove the ult first!
		if ( arrIntData[idUser][P_LEVEL] < iMinUltLevel )
		{
			new iUltimateID = SM_GetSkillOfType( idUser, SKILL_TYPE_ULTIMATE );
			
			// Then we need to remove this!
			if ( SM_GetSkillLevel( idUser, iUltimateID) == 1 )
			{
				// Remove the ult
				SM_SetSkillLevel( idUser, iUltimateID, 0, 0 );

				bSkillRemoved = true;

				// Clear ult icon!
				ULT_ClearIcons( idUser );

				// Get our current skills used
				iSkillsUsed = SM_TotalSkillPointsUsed( idUser );

				// Restart the loop!
				continue;
			}
		}

		iSkillID = SM_GetRandomSkill( idUser );
		iSkillLevel = SM_GetSkillLevel( idUser, iSkillID);

		// We don't want a passive skill or a skill that is level 0 so keep trying
		while ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_PASSIVE || iSkillLevel == 0 )
		{
			iSkillID = SM_GetRandomSkill( idUser );
			iSkillLevel = SM_GetSkillLevel( idUser, iSkillID);
		}
		
		// OK at this point we have a valid skill, lets remove a level!
		SM_SetSkillLevel( idUser, iSkillID, iSkillLevel - 1, 1 );

		bSkillRemoved = true;

		// Get our current skills used
		iSkillsUsed = SM_TotalSkillPointsUsed( idUser );
	}
	
	// Need to reset all skill data for the given race if we've removed a skill
	if ( bSkillRemoved )
	{
		WC3_InitPlayerSkills( idUser );
	}

	// OK lets check the total skills the user has, and maybe show them the selectskills menu
	new iTotalSkillsUsed = SM_TotalSkillPointsUsed( idUser );

	if ( iTotalSkillsUsed < arrIntData[idUser][P_LEVEL] )
	{
		MENU_SelectSkill( idUser );
	}

	WC3_ShowBar( idUser );
}


// Reset the user's XP to 0
public XP_Reset(idUser)
{

	

	arrIntData[idUser][P_LEVEL]		= 0;
	arrIntData[idUser][P_XP]		= 0;
	SM_ResetSkillLevels(idUser);

	// Save after resetting the user's XP
	DB_SaveXP( idUser, true );

	WC3_ShowBar( idUser );

	format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"YOUR_XP_HAS_BEEN_RESET");
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

	// Reset the skills...

	SHARED_INVIS_Set( idUser );

	// Undead's Unholy Aura
	SHARED_SetGravity( idUser );

	// Set the user's speed
	SHARED_SetSpeed( idUser );

	return PLUGIN_CONTINUE;
}	

// Function from war3x thanks ryan!!!
public XP_GetAdminFlag()
{

    new szFlags[24];
    get_pcvar_string( CVAR_wc3_admin_flag, szFlags, 23 );

    return ( read_flags( szFlags ) );
}

stock XP_Give(idUser, iBonusXP )
{

	

	if ( !WC3_Check() || !idUser )
		return 0;

	// Make sure we have the minimum amount of players
	if ( !XP_MinPlayers() )
		return 0;

	// Bonus calculated by:
	// Bonus XP * (lvl of player/float(iMaxLevels) + 1.0)
	// I.E. if Player is level iMaxLevels, then it will be Bonus XP * 2.0
	



	if (iBonusXP != 0)
	{
		new Float:fCurrentLevel = float(arrIntData[idUser][P_LEVEL]);
		new Float:iLevelMultiplier = (fCurrentLevel / float(iMaxLevels)) + 1.0;
		
		new iRealBonusXP = floatround(iLevelMultiplier * iBonusXP);

		//ITEM_INTELLECT - Intellect
		if (ITEM_Has(idUser, ITEM_INTELLECT ) > ITEM_NONE || 
			(fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_INTELLECT) ||
			clVIP:isAccesItemVip(idUser,ITEM_INTELLECT) == true
		   )
		{	
			iRealBonusXP = floatround(iLevelMultiplier * iBonusXP * BONUS_INTELLECT);

			if(!is_user_bot(idUser))
			{
				new szShowMessageXPBonus[256];
				format(szShowMessageXPBonus, charsmax(szShowMessageXPBonus), "+%d*XP: %d",BONUS_INTELLECT,iRealBonusXP);
				//fShowMsgPickUpItem(idUser,szShowMessageXPBonus,205,92,92);
				fShowMessagePickUpItem(idUser,szShowMessageXPBonus,205,92,92,enOther);
				
			}
		}

		//Если игрок имеет флаг 'p'
		if((get_user_flags(idUser) & fBonusXP()))
			iRealBonusXP += floatround(iRealBonusXP * get_pcvar_float(CVAR_wc3_bonus_xp) );
			
		if(bDoubleXPActive == true)
			iRealBonusXP *= iBonusFactorXP;
		
		//Жрец
		// *******************************************************
		// Скил 4 уровня - Мистицизм - Mysticism - пассивный
		// *******************************************************
		new iSkillLevel = SM_GetSkillLevel(idUser,PASS_PRIEST_MYSTICISM );
		if (iSkillLevel > 0 && isDisabledSkillsOnMap(idUser,PASS_PRIEST_MYSTICISM) == false)
		{
			new iMysticism = ArrayGetCell(arrMysticism,arrIntData[idUser][P_LEVEL]);
			if (iMysticism > 0)
					iRealBonusXP += iMysticism;
		}

		arrIntData[idUser][P_XP] += iRealBonusXP;

		XP_Check(idUser);

		return iRealBonusXP;
	}

	return 0;
}


stock XP_GetLevelByXP( iXP )
{
	

    if ( iXP < 0 || iXP == 0 )
     return 0;

    new Float:fXPMult = get_pcvar_float( CVAR_wc3_xp_multiplier );

    new iResultLevel = 0;
    for (new iLevel = 0; iLevel <= iMaxLevels; iLevel++ )
    {
		new iXpSave = ArrayGetCell(arrXpSave,iLevel);
		if(iXP >= floatround(iXpSave * fXPMult ))
			iResultLevel = iLevel;
		
    }

    return iResultLevel;
}