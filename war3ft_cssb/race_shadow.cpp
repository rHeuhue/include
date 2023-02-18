/*
*	Race: Shadow Hunter Functions
*/

new g_SH_SerpentGiven[33];
new bool:bWardBombCheck = false;

// ****************************************
// Shadow Hunter's Healing Wave
// ****************************************

//Скил 1 уровня - Волна жизни (Heling Wave)
// Helper function to start the healing process
public SH_HealingWave( idUser )
{
	if ( task_exists( idUser + TASK_WAVE ) == 0 )
	{
		_SH_HealingWave( idUser );
	}
}

// We don't need to ever actually "turn this off" since this task will take care of itself
public _SH_HealingWave( idUser )
{
	if ( idUser >= TASK_WAVE )
	{
		idUser -= TASK_WAVE;
	}

	// User is no longer connected
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}
	
	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel(idUser, SKILL_HEALINGWAVE);

	// User doesn't have this skill, so lets return
	//  - Also return if this was called twice
	if (iSkillLevel <= 0 || arrBoolData[idUser][PB_ISFROZENSKILL] == true || isDisabledSkillsOnMap(idUser,SKILL_HEALINGWAVE) == true)
		return;

	// Continue healing...
	if ( is_user_alive( idUser ) )
	{
		new Float:fHeal = ArrayGetCell(arrHealingWave,iSkillLevel-1);
		set_task(fHeal, "_SH_HealingWave", TASK_WAVE + idUser );
	}
	
	// Prevent healing if this player is hexed
	if ( arrBoolData[idUser][PB_HEXED] )
	{
		return;
	}

	new arrPlayers[32], iNumberOfPlayers, idTarget, ptTargetOrigin[3], ptOrigin[3];
	new iTeam = get_user_team(idUser);

	get_user_origin( idUser, ptOrigin );
	get_players( arrPlayers, iNumberOfPlayers, "a" );
	
	// Loop through each player and check to see if one is close enough to be healed
	for ( new i = 0; i < iNumberOfPlayers; i++ )
	{
		idTarget = arrPlayers[i];
		
		// User is on the idAttacker's team
		if ( arrBoolData[idTarget][PB_ISCONNECTED] && get_user_team( idTarget ) == iTeam )
		{
			if ( is_user_alive( idTarget ) )
			{
				get_user_origin( idTarget, ptTargetOrigin );
			
				// User is close enough
				if ( get_distance(ptOrigin, ptTargetOrigin) < iShHealingWaveRange )
				{
					get_user_origin( idTarget, ptOrigin )
			
					// User needs health
					new iMinHealth = clHP:getRaceMinHealth(idTarget);
					new iCurrentHealth =  clHP:getUserHealth(idTarget);
					new iBonusHp = iShHealingWaveHealth;

					if (iCurrentHealth < iMinHealth)
					{
						if(bSilentHeal[idTarget] == false)
						{
							if(sm4_IsPlayerSkeleton(idTarget) == false)//Если игрок скелет,лечиться не может
							{
								if((iCurrentHealth + iBonusHp) > iMinHealth )
									clHP:setUserHealth(idTarget,iMinHealth);
								else
									clHP:setUserHealth(idTarget,iCurrentHealth + iBonusHp);
	
							}

							Create_TE_IMPLOSION( ptOrigin, 100, 8, 1 );
						}
					}
				}
			}
		}
	}

	return;
}

// ****************************************
// Shadow Hunter's Serpent Ward
// ****************************************
//Скил 3 уровня - Змеиная суть (Serpent Ward)
SH_SerpentWard( idUser )
{
	// User should have some!
	new iSkillLevel = SM_GetSkillLevel( idUser, SKILL_SERPENTWARD );
	if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,SKILL_SERPENTWARD) == false)
	{
		
		new iSerpent = ArrayGetCell(arrSerpentWard,iSkillLevel-1);
		while ( g_SH_SerpentGiven[idUser] < iSerpent )
		{
			// Increase the available serpent wards
			arrIntData[idUser][P_SERPENTCOUNT]++;

			// Increase the total we have given the user!
			g_SH_SerpentGiven[idUser]++;

			//client_print( idUser, print_chat, "[DEBUG] Total wards increased to %d (total given so far: %d)", arrIntData[idUser][P_SERPENTCOUNT], g_SH_SerpentGiven[idUser] );
		}
	}
	// User should not have any!
	else
	{
		// Remove all available serpents!
		arrIntData[idUser][P_SERPENTCOUNT] = 0;

		// We don't need to remove any of the wards b/c the task knows to check the skill level
	}
}

public SH_PlaceSerpentWard( idUser )
{

	// User is hexed, can't use any skills
	if ( arrBoolData[idUser][PB_HEXED] )
	{
		WC3_StatusText( idUser, 0, "%L", LANG_PLAYER, "HEX_NO_ABILITY" );
	}

	// User is alive we can place a ward!
	else if ( is_user_alive( idUser ) && SM_GetSkillLevel( idUser, SKILL_SERPENTWARD ) > 0 && 
		      arrIntData[idUser][P_SERPENTCOUNT] > 0 && 
			  isDisabledSkillsOnMap(idUser,SKILL_SERPENTWARD) == false
			)
	{

		// Serpent Ward
		if ( SH_CanPlaceWard( idUser ))
		{
			new parm[5], origin[3]

			get_user_origin( idUser, origin );
			parm[0] = origin[0];
			parm[1] = origin[1];
			parm[2] = origin[2];
			parm[3] = idUser;
			parm[4] = get_user_team( idUser );

			_SH_DrawSerpentWard( parm );
			arrIntData[idUser][P_SERPENTCOUNT]--;

			WC3_StatusText( idUser, 0, "%L", LANG_PLAYER, "SERPENT_WARD", arrIntData[idUser][P_SERPENTCOUNT] );
		}
		else
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SH_PLACE_SERPENT_WARD");
			WC3_StatusText( idUser, 0, szMessage);
		}
	}
}

// Called when the bomb is planted
SH_BombPlanted()
{
	bWardBombCheck = true;

	set_task( 1.0, "_SH_ResetBombCheck", 0 );
}


public _SH_ResetBombCheck()
{
	bWardBombCheck = false;
}

public _SH_DrawSerpentWard( parm[5] )
{

	if ( !WC3_Check() )
	{
		return;
	}

	new idUser = parm[3];

	// User is no longer connected, stop drawing wards
	if( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}

	// User is no longer alive, don't draw wards
	if ( !is_user_alive( idUser ) )
	{
		arrIntData[idUser][P_SERPENTCOUNT]++;
		return;
	}

	// User doesn't have this skill anymore! Remove the ward!
	if ( SM_GetSkillLevel( idUser, SKILL_SERPENTWARD ) <= 0 || 
		 arrBoolData[idUser][PB_ISFROZENSKILL] == true ||
		 isDisabledSkillsOnMap(idUser,SKILL_SERPENTWARD) == true
	   )
	{
		return;
	}

	// Don't allow the ward to be by a hostage or the bom
	if ( bWardBombCheck )
	{
		if ( !SH_CheckWard( parm ) )
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SH_DRAW_SERPENT_WARD");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

			return;
		}
	}

	new origin[3], start[3], end[3], red, blue, green
	origin[0]=parm[0]
	origin[1]=parm[1]
	origin[2]=parm[2]
	
	// Set up the top of the ward
	start[0] = origin[0]
	start[1] = origin[1]
	start[2] = origin[2] + 600

	// Set up the bottom of the ward
	end[0] = origin[0]
	end[1] = origin[1]
	end[2] = origin[2] - 600

	if ( parm[4] == TS )
	{
		red		= colorSerpentWardRGB_T[0];
		green	= colorSerpentWardRGB_T[1];
		blue	= colorSerpentWardRGB_T[2];
	}
	else
	{
		red		= colorSerpentWardRGB_CT[0];
		green	= colorSerpentWardRGB_CT[1];
		blue	= colorSerpentWardRGB_CT[2];
	}
	
	// Draw the serpent ward
	Create_TE_BEAMPOINTS( start, end, arrIdSprites[SPR_LIGHTNING], 1, 5, 2, 500, 20, red, green, blue, 100, 100 );

	// Now lets check and see if any players are near that need to be damaged
	new players[32], numberofplayers;
	new targetid, targetorigin[3];

	get_players( players, numberofplayers, "a" );
	
	for ( new i = 0; i < numberofplayers; i++ )
	{
		targetid = players[i];

		if ( parm[4] != get_user_team( targetid ) )
		{
			get_user_origin( targetid, targetorigin );

			if ( get_distance( origin, targetorigin ) < 100 )
			{
				//Для talisman +
				//Для shopmenu4
				//ITEM_DEVOURER_LIGHT 27 - Пожиратель змей
				if (ITEM_Has(targetid, ITEM_DEVOURER_LIGHT ) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_DEVOURER_LIGHT)
				{
					ITEM_RemoveCharge(targetid, ITEM_DEVOURER_LIGHT );
					arrIntData[idUser][P_SERPENTCOUNT]++;
					return;
				}
				else
				{
					new iHealth = clHP:getUserHealth( targetid ); 

					if (iHealth - iShSerpentWardDamage <= 1 )
						clHP:setUserHealth(targetid,1);
					else
						WC3_Damage( targetid, idUser, iShSerpentWardDamage, CSW_SERPENTWARD, -1 ); 
				
					client_cmd(targetid, "speak %s",arrStrSounds[SOUND_THUNDER_CLAP], 0.3, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM); 

					// Create screen fade on the owners screen
					Create_ScreenFade( idUser, (1<<10), (1<<10), (1<<12), red, green, blue, 64 );
					Create_ScreenFade( targetid, (1<<10), (1<<10), (1<<12), red, green, blue, 126 );
				}
			}
		}
	}

	set_task( 0.5, "_SH_DrawSerpentWard", TASK_LIGHT + idUser, parm, 5 );

	return;
}

bool:SH_CanPlaceWard( idUser )
{
	new vPlayerOrigin[3];
 	get_user_origin( idUser, vPlayerOrigin );

	// Make sure the user isn't trying to place a ward near a hostage
	if ( SHARED_NearObjective( vPlayerOrigin ) == OBJENT_HOSTAGE )
	{
		return false;
	}

	//Проверка установки "Ядовитой змеи" на респауне врагов
	if(SH_Lock_SerpentWard( idUser ) == true)
		return false;

	// Make sure the user isn't trying to place a ward near the bomb
 	new Float:vEntOrigin[3];
 	new vEntityOrigin[3];
 	
 	new iEnt = find_ent_by_model( -1, "grenade", "models/w_c4.mdl" )
 	
	if ( iEnt && is_valid_ent( iEnt ) ) 
	{
		
    	entity_get_vector( iEnt, EV_VEC_origin, vEntOrigin )
    
    	vEntityOrigin[0] = floatround( vEntOrigin[0] );
    	vEntityOrigin[1] = floatround( vEntOrigin[1] );
    	vEntityOrigin[2] = floatround( vEntOrigin[2] );
    	
    	if ( get_distance( vPlayerOrigin, vEntityOrigin ) < 250 )
		{
    		return false;
		}
	}
	
	return true;
}

bool:SH_CheckWard( parm[5] )
{
	new vPlayerOrigin[3];
	
	vPlayerOrigin[0] = parm[0];
	vPlayerOrigin[1] = parm[1];
	vPlayerOrigin[2] = parm[2];
	
	new Float:vEntOrigin[3];
	new vEntityOrigin[3];
	
	new iEnt = find_ent_by_model( -1, "grenade", "models/w_c4.mdl" );
	
	if ( iEnt && is_valid_ent( iEnt ) )
	{
		entity_get_vector( iEnt, EV_VEC_origin, vEntOrigin )
		
		vEntityOrigin[0] = floatround( vEntOrigin[0] );
		vEntityOrigin[1] = floatround( vEntOrigin[1] );
		vEntityOrigin[2] = floatround( vEntOrigin[2] );
		
		if ( get_distance( vPlayerOrigin, vEntityOrigin ) < 250 )
		{
			return false;
		}
	}
	
	return true;
}

// ****************************************
// Shadow Hunter's Big Bad Voodoo
// ****************************************
//Супер навык
public SH_Ult_BigBadVoodoo(idUser)
{
	if (!arrBoolData[idUser][PB_ISCONNECTED])
		return;

	//Блокировка супер навыка врагом
	new vOldLocation[3], vNewLocation[3];
	
	get_user_origin( idUser, vOldLocation );
	get_user_origin( idUser, vNewLocation, 3 );

	new iPlayerOldCheck = WC3_IsImmunePlayerNear(idUser, vOldLocation);
	new iPlayerNewCheck = WC3_IsImmunePlayerNear(idUser, vNewLocation);
	new iLosesCharge = 0;
	if ( iPlayerOldCheck > 0 )
		iLosesCharge = iPlayerOldCheck;
	else if ( iPlayerNewCheck > 0 )
		iLosesCharge = iPlayerNewCheck;

	if (iLosesCharge > 0)
	{
		ULT_RemoveCharge(iLosesCharge);

		fResetUltimateTimerDivider(idUser);

		ULT_Blocked(idUser);

		return;
	}

	arrBoolData[idUser][PB_GODMODE] = true;

	arrBoolData[idUser][PB_CAN_RENDER] = false;

	// Set up the user's ultimate delay
	fResetUltimateTimerDivider(idUser,iShBigBadVoodooDuration,false);
	
	ULT_Icon( idUser, ICON_FLASH );
	
	Create_BarTime( idUser, iShBigBadVoodooDuration, 0 );
		
	emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_VOODOO], 1.0, ATTN_NORM, 0, PITCH_NORM );

	set_user_rendering( idUser, kRenderFxGlowShell, 255, 245, 50, kRenderNormal, 16 );

	new vOrigin[3];
	get_user_origin( idUser, vOrigin );
	vOrigin[2] += 75;

	Create_TE_ELIGHT( idUser, vOrigin, 100, 255, 245, 200, iShBigBadVoodooDuration, 0 );

	set_task( float(iShBigBadVoodooDuration ), "SH_Ult_Remove", TASK_RESETGOD + idUser );

	return;
}

public SH_Ult_Remove( idUser )
{
	if ( idUser >= TASK_RESETGOD )
		idUser -= TASK_RESETGOD;
	
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return;
	
	arrBoolData[idUser][PB_CAN_RENDER] = true;

	arrBoolData[idUser][PB_GODMODE] = false;

	ULT_Icon( idUser, ICON_HIDE );

	SHARED_INVIS_Set( idUser );

	return;
}


// ****************************************
// Shadow Hunter's Hex
// ****************************************
//Скил 2 уровня - Проклятье (Hex)
SH_SkillsOffensive( idAttacker, idVictim )
{
	if(!is_user_alive(idVictim) || !is_user_connected(idVictim)) 
      return;

	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
      return;

	// Hex
	new iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_HEX );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_HEX) == true)
			return;

		new Float:fHex = ArrayGetCell(arrHex,iSkillLevel-1);
		if (random_float(fHunterSkill2MinPercent,fHunterSkill2MaxPercent) <= fHex )
		{
						
			// We need to identify the victim as slowed + hexed			
			arrBoolData[idVictim][PB_HEXED] = true
			arrBoolData[idVictim][PB_SLOWED] = true;
				
			// Slow the user's speed
			SHARED_SetSpeed( idVictim );

			// Set the user's gravity
			SHARED_SetGravity( idVictim );

			// Set the user's rendering
			SHARED_INVIS_Set( idVictim );


			// Remove user's devotion aura
			new iCurrentHealth = clHP:getUserHealth(idVictim);
			if (iCurrentHealth - g_HU_DevotionAuraGiven[idVictim] <= 0 )
				clHP:setUserHealth(idVictim,1);
			else
				clHP:setUserHealth(idVictim,iCurrentHealth - g_HU_DevotionAuraGiven[idVictim]);
			
			g_HU_DevotionAuraGiven[idVictim] = 0;



			// Create the "remove hex" task
			set_task(fShHexLength ,"_SH_RemoveHex", TASK_HEX + idVictim );

			// Play the hex sound
			emit_sound( idVictim, CHAN_STATIC, arrStrSounds[SOUND_HEX], 1.0, ATTN_NORM, 0, PITCH_NORM );

			// Make the user glow!
			//SHARED_Glow( idVictim, 150, 150, 150, 0 );
			SHARED_GlowShell(idVictim,178,34,34,get_pcvar_float( CVAR_wc3_glowshell_time ),get_pcvar_num( CVAR_wc3_glowshell_amount ));

			// Lets create a screen fade
			Create_ScreenFade( idVictim, (1<<10), (1<<10), (1<<12), 255, 255, 255, 75 )
		}
	}
}

public _SH_RemoveHex( idUser )
{
	idUser -= TASK_HEX;

	if( !arrBoolData[idUser][PB_ISCONNECTED] )
		return PLUGIN_HANDLED;
	
	arrBoolData[idUser][PB_CAN_RENDER] = true;
	arrBoolData[idUser][PB_HEXED]		= false;
	
	if ( is_user_alive( idUser ) )
	{
		// Reset the user's speed
		SHARED_ResetMaxSpeed( idUser );

		// Reset the user's gravity
		SHARED_SetGravity( idUser );

		// Reset the user's rendering
		SHARED_INVIS_Set( idUser );

		// Reset the user's devotion aura
		HU_DevotionAura( idUser );

		emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_HEX], 1.0, ATTN_NORM, 0, PITCH_NORM );
	}

	return PLUGIN_HANDLED;
}

//Скил 4 уровня - Неустойчивы концентрат (Unstable Concocnion)
SH_SkillsDefensive( idAttacker, idVictim )
{
	// Unstable Concoction
	new iSkillLevel = SM_GetSkillLevel( idVictim, PASS_UNSTABLECONCOCTION );
	if (iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
	{
		if(isDisabledSkillsOnMap(idVictim,PASS_UNSTABLECONCOCTION) == true)
			return;

		new Float:fConcoction = ArrayGetCell(arrUnstableConcoction,iSkillLevel);
		if (random_float(fHunterSkill4MinPercent,fHunterSkill4MaxPercent) <= fConcoction )
		{
			
			new vOrigin[3], vInitOrigin[3], vAxisOrigin[3], i;
			
			// Get origin of victim
			get_user_origin( idVictim, vOrigin );
			
			// Play sound on attacker
			emit_sound( idAttacker, CHAN_STATIC, arrStrSounds[SOUND_CONCOCTION_CAST], 1.0, ATTN_NORM, 0, PITCH_NORM );
			
			// Set up the origins for the effect
			vInitOrigin[0] = vOrigin[0];
			vInitOrigin[1] = vOrigin[1];
			vInitOrigin[2] = vOrigin[2] - 16;

			vAxisOrigin[0] = vOrigin[0];
			vAxisOrigin[1] = vOrigin[1];
			vAxisOrigin[2] = vOrigin[2] + iShConcoctionRadius;
			
			// Display the effect on the attacker
			for ( i = 0; i < 200; i += 25 )
			{
				Create_TE_BEAMCYLINDER( vOrigin, vInitOrigin, vAxisOrigin, arrIdSprites[SPR_SHOCKWAVE], 0, 0, 9, 20, 0, 188, 220, 255, 255, 0 );

				vInitOrigin[2] += 25;
			}

			//---
			new team = get_user_team( idVictim );
			new players[32], numberofplayers, vTargetOrigin[3];
			get_players(players, numberofplayers, "a");
			
			// Loop through all players and see if anyone nearby needs to be damaged
			//Повреждение окружающих при вызове волны.
			for( i = 0; i < numberofplayers; i++ )
			{
				if ( is_user_alive( players[i] ) )
				{
					// Then we have a target on the other team!!
					if ( get_user_team( players[i] ) != team )
					{
						get_user_origin( players[i], vTargetOrigin );

						// Make sure they are close enough
						if ( get_distance( vOrigin, vTargetOrigin ) <= iShConcoctionRadius )
						{
							// Damage
							WC3_Damage( players[i], idVictim, iShConcoctionDamage, CSW_CONCOCTION, 0 );
						
							// Let the victim know he hit someone
							emit_sound( idVictim, CHAN_STATIC, arrStrSounds[SOUND_CONCOCTION_HIT], 1.0, ATTN_NORM, 0, PITCH_NORM );
						}
					}
				}
			}//---
		}
		else if ( get_pcvar_num( CVAR_wc3_psychostats ) )
		{
			new WEAPON = CSW_CONCOCTION - CSW_WAR3_MIN;

			iStatsShots[idVictim][WEAPON]++;
		}
	}
}

// This function is called to reset the ability of an attacker to attack a user running big bad voodoo
public _SH_ResetBigBadAttacker( idUser )
{
	if (!WC3_Check())
		return;
	
	if ( idUser >= TASK_BIGBADATTACKER )
		idUser -= TASK_BIGBADATTACKER;
	
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return;
	
	arrBoolData[idUser][PB_BIGBAD_ATTACKER] = false;
	
	format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SH_RESET_BIG_BAD_ATTACKER");	
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
}

//Проверка установки "Ядовитой змеи" на респауне врагов
bool:SH_Lock_SerpentWard( idUser )
{
	new vPlayerOrigin[3];
	get_user_origin( idUser, vPlayerOrigin );

	new iSpawnID,vOrigin[3];
	new entInfoSpawn = -1;
	new Float:fSpawnOrigin[3];
	new bool:bFound = false;

	new iTeam = get_user_team( idUser );
	iTeam = ( ( iTeam == TEAM_CT ) ? TEAM_T : TEAM_CT );
	iSpawnID = ( ( iTeam == TEAM_CT ) ? 0 : 1 );

	do {
		entInfoSpawn = find_ent_by_class( entInfoSpawn, szSpawnEnt[iSpawnID] );

		if ( entInfoSpawn != 0 )
		{
			entity_get_vector( entInfoSpawn, EV_VEC_origin, fSpawnOrigin );

			FVecIVec( fSpawnOrigin, vOrigin );

			if ( get_distance( vPlayerOrigin, vOrigin ) < 250 )
			{
				bFound = true;

				break;
			}
		}
	}
	while ( entInfoSpawn && !bFound )

	return bFound;
}