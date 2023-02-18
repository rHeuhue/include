/*
*	Race: Human Alliance Functions
*/

new g_HU_DevotionAuraGiven[33];

HU_ULT_Blink( idUser )
{
	
	// User can't use ultimate while planting or defusing!
	if ( arrBoolData[idUser][PB_ISPLANTING] )
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WA_ULT_VENGEANCE");
		client_print( idUser, print_center,szMessage);
		
		return;
	}
	
	// User can't Blink when he/she's stunned
	if ( arrBoolData[idUser][PB_STUNNED] )
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_HU_ULT_BLINK_1");	
		WC3_StatusText( idUser, 0, szMessage);

		return;
	}
	
	new vOldLocation[3], vNewLocation[3]
	
	// Get the player's current location
	get_user_origin( idUser, vOldLocation );
	
	// Get where the player is looking (where the player will teleport)
	get_user_origin( idUser, vNewLocation, 3 );
	
	// Play the blink sound!
	emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_BLINK], 1.0, ATTN_NORM, 0, PITCH_NORM );

	new iPlayerOldCheck = WC3_IsImmunePlayerNear( idUser, vOldLocation );
	new iPlayerNewCheck = WC3_IsImmunePlayerNear( idUser, vNewLocation );
	new iLosesCharge = 0;
	if ( iPlayerOldCheck > 0 )
	{
		iLosesCharge = iPlayerOldCheck;
	}
	else if ( iPlayerNewCheck > 0 )
	{
		iLosesCharge = iPlayerNewCheck;
	}

	// Make sure a nearby enemy doesn't have immunity
	if ( iLosesCharge > 0 )
	{
		// Remove charge since player blocked it!
		ULT_RemoveCharge(iLosesCharge);

		WC3_StatusText( idUser, 0, "%L", LANG_PLAYER, "TELEPORT_FAILED_ENEMY_IMMUNITY" );
		
		// Reset the user's ultimate
		fResetUltimateTimerDivider(idUser);

		// Display ultimate blocked message
		ULT_Blocked( idUser );

		return;
	}

	// Check to see if the user is teleporting where they shouldn't
	if ( SHARED_NearObjective( vNewLocation ) == OBJENT_VIP_ESCAPE )
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_HU_ULT_BLINK_2");
		WC3_StatusText( idUser, 0, szMessage );
		
		// Reset the user's ultimate
		fResetUltimateTimerDivider(idUser);

		return;
	}

	// If we teleport them back, make sure they don't get teleported into the ground
	vOldLocation[ZPOS] += 15;

	// Change coordinates to make sure player won't get stuck in the ground/wall
	vNewLocation[XPOS] += ( ( vNewLocation[XPOS] - vOldLocation[XPOS] > 0 ) ? -50 : 50 );
	vNewLocation[YPOS] += ( ( vNewLocation[YPOS] - vOldLocation[YPOS] > 0 ) ? -50 : 50 );
	vNewLocation[ZPOS] += 40;			

	
	// Set up some origins for some special effects!!!
	new vCenterOrigin[3], vAxisOrigin[3];
	vCenterOrigin[0]	= vOldLocation[0];
	vCenterOrigin[1]	= vOldLocation[1];
	vCenterOrigin[2]	= vOldLocation[2] + 10;
	vAxisOrigin[0]		= vOldLocation[0];
	vAxisOrigin[1]		= vOldLocation[1];
	vAxisOrigin[2]		= vOldLocation[2] + 10 + TELEPORT_RADIUS;

	// Lets create some beam cylinders!
	Create_TE_BEAMCYLINDER( vOldLocation, vCenterOrigin, vAxisOrigin, arrIdSprites[SPR_SHOCKWAVE], 0, 0, 3, 60, 0, 255, 255, 255, 255, 0 );
	
	// Modify our effects a bit for another cylinder
	vCenterOrigin[2]	+= 80;
	vAxisOrigin[2]		+= 80;
	
	// And draw another cylinder!!!
	Create_TE_BEAMCYLINDER( vOldLocation, vCenterOrigin, vAxisOrigin, arrIdSprites[SPR_SHOCKWAVE], 0, 0, 3, 60, 0, 255, 255, 255, 255, 0 );

	// Planting the bomb then teleporting = bad, lets stop this...
	client_cmd( idUser, "-use" );

	// Then lets try to slay some bitches...
	if ( get_pcvar_num( CVAR_wc3_blink_protection ) )
	{

		// Lets go ahead and make this check before they teleport...
		if ( HU_ULT_BlinkProtection( idUser, vNewLocation ) )
		{
			fResetUltimateTimerDivider(idUser);
			return;
		}
	}

	// Teleport the player!!!
	set_user_origin( idUser, vNewLocation );

	// Check if Blink landed you in a wall, if so, abort
	new parm[5];
	parm[0] = idUser;
	parm[1] = vOldLocation[0];
	parm[2] = vOldLocation[1];
	parm[3] = vOldLocation[2];
	parm[4] = vNewLocation[2];
	
	// [FS#65]
	if ( !g_EndRound )
	{
		set_task( 0.1, "_HU_ULT_BlinkStuck", TASK_BLINKSTUCK + idUser, parm, 5 );
	}
	
	fResetUltimateTimerDivider(idUser);

	emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_BLINK], 1.0, ATTN_NORM, 0, PITCH_NORM );

	return;
}

// Function will check to see if a user is stuck in a wall
public _HU_ULT_BlinkStuck( parm[] )
{

	new idUser = parm[0]	 

	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}

	new vOldLocation[3], vOrigin[3];

	vOldLocation[0] = parm[1];
	vOldLocation[1] = parm[2];
	vOldLocation[2] = parm[3];

	get_user_origin( idUser, vOrigin );
	
	// Then the user is stuck :/
	if ( parm[4] == vOrigin[2] )
	{

		WC3_StatusText( idUser, 0, "%L", LANG_PLAYER, "TELEPORT_FAILED_BAD_DESTINATION" );
		
		// This will try to move the user back - if this fails then they will be teleported back to their spawn instead of left stuck!
		SHARED_Teleport( idUser, vOldLocation );

		ULT_ResetCooldown( idUser, floatround(fBlinkCooldown) );
	}

	// Otherwise they teleported correctly!
	else
	{

		// Sprays white bubbles everywhere
		new vStartOrigin[3];
		vStartOrigin[0] = vOrigin[0];
		vStartOrigin[1] = vOrigin[1];
		vStartOrigin[2] = vOrigin[2] + 40;
		
		Create_TE_SPRITETRAIL( vStartOrigin, vOrigin, arrIdSprites[SPR_FLARE], 30, 10, 1, 50, 10 );

		// Flash the player
		if ( get_pcvar_num( CVAR_wc3_blink_dizziness ) == 1 )
		{
			Create_ScreenFade( idUser, (1<<15), (1<<10), (1<<12), 0, 0, 255, 180 );
		}

		// Lets just flash them with a nice white screen :)
		else
		{
			Create_ScreenFade( idUser, (1<<15), (1<<10), (1<<12), 255, 255, 255, 255 );
		}
	}	
	
	return;
}


// Function will make sure the user isn't in an invalid location in a map
HU_ULT_BlinkProtection( idUser, vOrigin[3] )
{

	new bool:bSlay = false;
	new Float:fOrigin[3];
	
	// Convert origin to float
	IVecFVec( vOrigin, fOrigin );
	
	// User shouldn't be teleporting into the sky!
	if ( point_contents( fOrigin ) == CONTENTS_SKY )
	{
		bSlay = true;
	}

	// Get the current map name
	new szMapName[32];
	get_mapname( szMapName, 32 );
	
	// Only do these checks if we're in CS/CZ
	if ( !bSlay )
	{
		new x = vOrigin[0];
		new y = vOrigin[1];
		new z = vOrigin[2];
		
		// Don't teleport too high
		if ( equali( szMapName, "de_dust" ) )
		{
			if ( z > 220 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "awp_assault" ) )
		{
			if( z > 520 && y > 2400 && y < 2600 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "de_dust_cz" ) )
		{
			if ( z > 220 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "de_aztec_cz" ) )
		{
			if ( z > 300 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "cs_assault_upc" ) )
		{
			if( z > 650 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "de_aztec" ) )
		{
			if( z > 300 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "de_cbble" ) || equali( szMapName, "de_cbble_cz" ) )
		{
			if ( z > 315 )
			{
				if ( ! ( ( x > -1320 && x < -1150 ) && ( y > 2600 && y < 2900 ) ) )
				{
					bSlay = true;
				}
			}           
		}

		else if ( equali( szMapName, "cs_assault" ) )
		{
			if ( z > 700 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "cs_militia" ) || equali( szMapName, "cs_militia_cz" ) )
		{
			if ( z > 500 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "cs_italy" ) )
		{
			if ( z > -220 && y < -2128 )
			{
					bSlay = true;
			}
			else if( z > 250 )
			{
				if ( ( x < -1000 && x > -1648 ) && ( y > 1900 && y < 2050 ) )
				{
					bSlay = true;
				}
				else if ( ( x < -1552 && x > -1648 ) && ( y > 1520 && y < 2050 ) )
				{
					bSlay = true;
				}
			}
		}

		else if ( equali( szMapName, "cs_italy_cz" ) )
		{
			if ( y > 2608 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "de_dust2" ) )
		{
			if ( z > 270 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "de_dust2_cz" ) )
		{
			if ( z > 270 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "fy_dustworld" ) )
		{
			if ( z > 82 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "fy_pool_day" ) )
		{
			if ( z > 190 )
			{
				bSlay = true;
			}
		}

		else if ( equali( szMapName, "as_oilrig" ) )
		{
			if ( x > 1700 )
			{
				bSlay = true;
			}
		}
	}
	
	// For some reason bSlay is always true on this map, but you should be able to teleport anywhere
	if ( equali( szMapName, "cs_mice_final" ) )
		bSlay = false;


	// Slay the user!!!
	if ( bSlay )
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"SLAIN_FOR_TELEPORTING");	
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		user_kill(idUser, 1);
	}

	return bSlay;
}

HU_DevotionAura(idUser)
{
	if (!is_user_alive(idUser))
		return;
	
	if(isDisabledSkillsOnMap(idUser,SKILL_DEVOTION) == true)
		return;

 	new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_DEVOTION);
 	
	// Already given
	new DevotionAuraGiven = g_HU_DevotionAuraGiven[idUser];
		
	// Then the user has devotion aura
	if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false)
		g_HU_DevotionAuraGiven[idUser] = iDevotionAura * iSkillLevel;
	else
		g_HU_DevotionAuraGiven[idUser] = 0;
 
	// Player may even lose HP because of this
	DevotionAuraGiven = g_HU_DevotionAuraGiven[idUser] - DevotionAuraGiven;

	new iMaxHealth = clHP:getRaceMaxHealth(idUser);
	new iCurrentHealth =  clHP:getUserHealth(idUser);
	new iBonusHp = DevotionAuraGiven;

	if ((iCurrentHealth + iBonusHp) <= 0)
		clHP:setUserHealth(idUser,1);

	if (iCurrentHealth + iBonusHp > iMaxHealth)
		clHP:setUserHealth(idUser,iMaxHealth);
	else
		clHP:setUserHealth(idUser,iCurrentHealth + iBonusHp);

}

HU_SkillsOffensive( idAttacker, idVictim )
{
	// Bash
	new iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_BASH );
	if (iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_BASH) == true)
			return;

		new Float:fBash = ArrayGetCell(arrBash,iSkillLevel-1);
		if ( random_float(fHumanSkill3MinPercent, fHumanSkill3MaxPercent ) <= fBash && !SHARED_IsPlayerSlowed( idVictim ) )
		{		

			arrBoolData[idVictim][PB_STUNNED] = true;
			SHARED_SetSpeed( idVictim );
			
			set_task(fBashHoldTime, "SHARED_ResetMaxSpeed", TASK_RESETSPEED + idVictim );

			// Make the user glow!
			SHARED_Glow( idVictim, 0, 0, 0, iBashGlowIntensity );
						
			// Create a screen fade
			Create_ScreenFade( idVictim, (1<<10), (1<<10), (1<<12), 255, 255, 255, g_GlowLevel[idVictim][3] )
		}
	}
}