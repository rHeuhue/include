/*
*	Race: Orcish Horde Functions
*/

// Initial Ultimate call
public OR_ULT_ChainLightning( iCaster, iTarget, iBodyPart )
{

	// Display the lightning effect
	OR_ULT_ChainEffect( iCaster, iTarget, iChainLightningLineWidth, iChainLightningDamage, iBodyPart );
	
	// Now we need to search for the next "jump"
	new parm[5];
	parm[0] = iTarget;
	parm[1] = iChainLightningDamage;
	parm[2] = iChainLightningLineWidth;
	parm[3] = iCaster;
	parm[4] = iBodyPart;

	set_task( 0.2, "_OR_ULT_ChainLightning", TASK_LIGHTNING + iTarget, parm, 5 );
}

// Called on subsequent ultimate calls ( i.e. lightninghitnext )
public _OR_ULT_ChainLightning( parm[5] )
{
	// parm[0] = enemy
	// parm[1] = damage
	// parm[2] = linewidth
	// parm[3] = idAttacker
	// parm[4] = bodypart

	new iEnemy = parm[0];

	if ( !arrBoolData[iEnemy][PB_ISCONNECTED] )
	{
		return;
	}

	new iCaster		= parm[3];
	new iBodyPart	= parm[4];
	new iCasterTeam	= get_user_team( iCaster )

	new vOrigin[3];
	get_user_origin( iEnemy, vOrigin );

	new players[32], numberofplayers;
	get_players( players, numberofplayers, "a" );


	new i, iTarget = 0;
	new iClosestTarget = 0, iClosestDistance = 0;
	new iDistanceBetween = 0;
	new vTargetOrigin[3]

	new bool:bFound = false;  

	// Loop through every player
	for ( i = 0; i < numberofplayers; i++ )
	{
		iTarget = players[i];
		
		// Make sure our target player isn't on the same team!
		if ( get_user_team( iTarget ) != iCasterTeam )
		{
			get_user_origin( iTarget, vTargetOrigin )
			
			iDistanceBetween = get_distance( vOrigin, vTargetOrigin );

			// Verify the user is within range and has not been previously hit
			if ( iDistanceBetween < LIGHTNING_RANGE && !arrBoolData[iTarget][PB_LIGHTNINGHIT] )
			{

				// Make sure target isn't immune!
				if ( ULT_CanUserBlockUlt( iTarget,iCaster )  )
				{
					ULT_RemoveCharge(iTarget);
					
					// Let the idAttacker know the ultimate was blocked!
					ULT_Blocked( iCaster );
					
					// Just say the user was hit so they aren't tried to be hit the next round (possibility of removing multiple charges)
					arrBoolData[iTarget][PB_LIGHTNINGHIT] = true;

					bFound = true;
				}

				// Then we can hit this user!
				else
				{
					
					// This user is closest!! Lets make a note of this...
					if ( iDistanceBetween < iClosestDistance || iClosestTarget == 0 )
					{
						iClosestDistance = iDistanceBetween;
						iClosestTarget = iTarget;
					}

				}//end immune check
			}//end distance/hit check
		}//end team check
	}//end for

	// Then we have a valid target!!!
	if ( iClosestTarget && bFound == false ) 
	{
		// Damage should be decreased by 2/3 on each jump
		parm[1] = floatround(float(parm[2])*2/3);

		// Decrease line width as well
		parm[2] = floatround(float(parm[2])*2/3);
		
		// Display the actual lightning
		OR_ULT_ChainEffect( iCaster, iClosestTarget, parm[2], parm[1], iBodyPart );

		// Lets call this again on our next target!
		parm[0] = iClosestTarget;
		set_task( 0.2, "_OR_ULT_ChainLightning", TASK_LIGHTNINGNEXT + iCaster, parm, 5 );
	}

	// No valid target found - reset all lightning hit variables
	else
	{
		for ( i = 0; i < numberofplayers; i++ )
		{
			iTarget = players[i];

			arrBoolData[iTarget][PB_LIGHTNINGHIT] = false;
		}
	}

	return;
}

public OR_ULT_ChainEffect( iCaster, iTarget, iLineWidth, iDamage, iBodyPart )
{

	// Make sure we set this user as hit, otherwise we'll hit him again
	arrBoolData[iTarget][PB_LIGHTNINGHIT] = true;
	
	// Damage the user
	WC3_Damage( iTarget, iCaster, iDamage, CSW_LIGHTNING, iBodyPart );
	
	// Create the lightning
	Create_TE_BEAMENTS( iCaster, iTarget, arrIdSprites[SPR_LIGHTNING], 0, 15, 10, iLineWidth, 10, colorOrcLightningRGB[0], colorOrcLightningRGB[1], colorOrcLightningRGB[2], 255, 0 );
	
	// Get the target's origin
	new vOrigin[3]
	get_user_origin( iTarget, vOrigin );
	
	// Create an elight on the target
	Create_TE_ELIGHT( iTarget, vOrigin, 100, 255, 255, 255, 10, 0 );

	// Play the lightning sound
	emit_sound( iCaster, CHAN_STATIC, arrStrSounds[SOUND_LIGHTNING], 1.0, ATTN_NORM, 0, PITCH_NORM );

	return;
}

// Function checks to see if critical grenades are allowed
bool:OR_CriticalGrenadeAllowed(idUser)
{

	// Need to do the glove check
	if ( ITEM_Has( idUser, ITEM_GLOVES ) > ITEM_NONE && !get_pcvar_num( CVAR_wc3_glove_orc_damage ) )
		return false;

	if (fWorkTalismanPassive(idUser, arrTalismanActive[idUser] == TALISMAN_ITEM_GLOVES) && !get_pcvar_num( CVAR_wc3_glove_orc_damage ) )
		return false;

	// Check to see if we are on a disabled map
	if ( g_bOrcNadesDisabled )
		return false;

	return true;
}

OR_SkillsOffensive(idAttacker, idVictim, iWeapon, iDamage, iHitPlace )
{
	// Critical Strike
	new iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_CRITICALSTRIKE );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_CRITICALSTRIKE) == true)
			return;

		if (random_float(0.0, 1.0 ) <= fCriticalStrikeChance)
		{
			new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_CRITICALSTRIKE);

			new Float:fCritical = ArrayGetCell(arrCriticalStrike,iSkillLevel-1);
			new iBonusDamage = floatround( float( iDamage ) * fCritical );
			

			#if MODE_LOG
				#if LOG_SKILL_CRITICALSTRIKE > 0
					clLog:logRaceOrc(idAttacker,fCritical,iDamage,iBonusDamage);
				#endif
			#endif

			// Damage our victim
			WC3_Damage(idVictim, idAttacker, iBonusDamage, iWeapon, iHitPlace );
			
			// Make the user glow
			SHARED_Glow(idVictim, iBonusDamage, 0, 0, 0 );
			
			// Lets make a screenfade
			Create_ScreenFade(idVictim, (1<<10), (1<<10), (1<<12), 255, 0, 0, g_GlowLevel[idVictim][0] );

		}
	}

	

	// Critical Grenade
	iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_CRITICALGRENADE );

	if (iSkillLevel > 0)
	{
		if (ITEM_Has(idVictim, ITEM_GRENADE_PROTECTION ) == ITEM_NONE && 
			arrBoolData[idAttacker][PB_ISFROZENSKILL] == false &&
			arrBoolData[idVictim][PB_KINETIC_FIELD] == false
			)
		{		
		
			// Can only do this if the user has a grenade
			if (SHARED_IsGrenade(iWeapon) )
			{
				if (OR_CriticalGrenadeAllowed(idAttacker) )
				{					
					new Float:fGrenade = ArrayGetCell(arrCriticalGrenade,iSkillLevel-1);
					new iBonusDamage = floatround( float(iDamage) * fGrenade );
					
					#if MODE_LOG
					#if LOG_SKILL_CRITICALGRENADE > 0
						clLog:logRaceOrc(idAttacker,fGrenade,iDamage,iBonusDamage);
					#endif
					#endif

					WC3_Damage( idVictim, idAttacker, iBonusDamage, iWeapon, iHitPlace );

					SHARED_Glow( idVictim, iBonusDamage, 0, 0, 0 );
					
					Create_ScreenFade( idVictim, (1<<10), (1<<10), (1<<12), 255, 0, 0, g_GlowLevel[idVictim][0] );
				}
			}//if

		}//if

	}//if
}