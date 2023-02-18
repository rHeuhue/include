/*
*	Race: Warden Functions
*/

WA_ULT_Vengeance( idUser )
{
	//Блокировка супер навыка врагом
	new vOldLocation[3], vNewLocation[3]
	
	get_user_origin( idUser, vOldLocation );
	get_user_origin( idUser, vNewLocation, 3 );

	new iPlayerOldCheck = WC3_IsImmunePlayerNear( idUser, vOldLocation );
	new iPlayerNewCheck = WC3_IsImmunePlayerNear( idUser, vNewLocation );
	new iLosesCharge = 0;
	if ( iPlayerOldCheck > 0 )
		iLosesCharge = iPlayerOldCheck;
	else if ( iPlayerNewCheck > 0 )
		iLosesCharge = iPlayerNewCheck;

	if ( iLosesCharge > 0 )
	{
		ULT_RemoveCharge(iLosesCharge);

		fResetUltimateTimerDivider(idUser);

		ULT_Blocked( idUser );

		return;
	}



	// User can't use ultimate while planting or defusing!
	if (arrBoolData[idUser][PB_ISPLANTING])
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WA_ULT_VENGEANCE");
		client_print(idUser, print_center, szMessage);
				
		return;
	}

	// If the user's ultimate is not available, then why are we here?
	if (!ULT_Available( idUser ) )
		return;

	// We need to respawn the user!!
	if (!is_user_alive( idUser ) )
	{
		// Make sure the user isn't changing teams and we're not at the end of the round
		if (!arrIntData[idUser][P_RESPAWNBY] )
		{
			// Remove the ultimate delay if it existed (in theory it shouldn't)
			if (task_exists( TASK_UDELAY + idUser ) )
				remove_task( TASK_UDELAY + idUser );
			
			// Set up a new ultimate delay
			fResetUltimateTimerDivider(idUser);

			// Set up the respawn task
			set_task(SPAWN_DELAY, "_SHARED_Spawn", TASK_SPAWN + idUser );

			// We need to set that we're about to respawn
			arrIntData[idUser][P_RESPAWNBY] = RESPAWN_VENGEANCE;
		}
	}	
	// Otherwise teleport back to spawn
	else
	{		
		// Lets find a free spawn and obey immunity rules
		new ent = SHARED_FindFreeSpawn( idUser, true );
		
		// No spawn found
		if (ent < 0)
		{			
			// Immune person nearby
			if ( ent == -2 )
			{
				// The user's ultimate was blocked!
				ULT_Blocked(idUser);

				// Set up a new ultimate delay
				fResetUltimateTimerDivider(idUser);

				WC3_StatusText( idUser, 0, "%L", LANG_PLAYER, "VENGEANCE_FAILED_ENEMY_IMMUNITY" );
			}

			// No spawn found
			else
			{
				WC3_StatusText( idUser, 0, "%L", LANG_PLAYER, "NO_FREE_SPAWN_FOUND");
			}
		}

		// Spawn found!
		else
		{			
			arrIntData[idUser][P_RESPAWNBY] = RESPAWN_VENGEANCE;

			new vOrigin[3], vNewOrigin[3], Float:fSpawnOrigin[3];
			
			// Get the user's origin
			get_user_origin( idUser, vOrigin );

			// Get the origin of the spawn
			entity_get_vector(ent, EV_VEC_origin, fSpawnOrigin);
			
			// Convert float vector to int vector
			FVecIVec(fSpawnOrigin, vNewOrigin);
			
			// Move the user
			set_user_origin(idUser, vNewOrigin);

			// Play teleport animation at old location
			Create_TE_TELEPORT(vOrigin);
						
			//Установка здоровья Шпиону при спавне после использования ульты
			clHP:setCurRespawnRaceHealth(idUser);

			// Play the Vengeance sound		
			emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_VENGEANCE], 1.0, ATTN_NORM, 0, PITCH_NORM );

			// Set up a new ultimate delay
			fResetUltimateTimerDivider(idUser);
		}
	}

	return;
}

// User's Blink Ability
WA_Blink(idUser)
{
	new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_BLINK );
	// User has the ability, lets initiate a "check"
	if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,SKILL_BLINK) == false)
	{
		// We don't need to check if they already have this!
		if ( arrBoolData[idUser][PB_WARDENBLINK] )
			return;

		new Float:fBlink = ArrayGetCell(arrBlink,iSkillLevel-1);
		if (random_float(fWardenSkill2MinPercent,fWardenSkill2MaxPercent) <= fBlink)
		{
			arrBoolData[idUser][PB_WARDENBLINK] = true;
			
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WA_BLINK");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		
		}
	}
	// User shouldn't have blink!
	else
	{
		arrBoolData[idUser][PB_WARDENBLINK] = false;
	}
}
//Закаленная кожа
WA_HardenedSkin( idVictim, iDamage )
{
	// Hardened Skin
	new iSkillLevel = SM_GetSkillLevel( idVictim, PASS_HARDENEDSKIN );
	if ( iSkillLevel > 0 && arrBoolData[idVictim][PB_ISFROZENSKILL] == false &&
		 isDisabledSkillsOnMap(idVictim,PASS_HARDENEDSKIN) == false
	   )
	{
		new Float:fHarden = ArrayGetCell(arrHardenedSkin,arrIntData[idVictim][P_LEVEL]);
		return ( floatround( float( iDamage ) * ( 1 - fHarden ) ) );
	}

	return iDamage;	
}

//Skill 3
//Навык: Скрытый удар (Shadow Strike), Раса: Шпион (Warden)
WA_SkillsOffensive( idAttacker, idVictim, iHitPlace )
{
	// Shadow Strike
	new iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_SHADOWSTRIKE );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_SHADOWSTRIKE) == true)
			return;

		new Float:fShadow = ArrayGetCell(arrShadowStrike,iSkillLevel-1);
		if (random_float(fWardenSkill3MinPercent,fWardenSkill3MaxPercent) <= fShadow )		
		{
			new vVictimOrigin[3], vAttackerOrigin[3]
			get_user_origin( idVictim, vVictimOrigin );
			get_user_origin( idAttacker, vAttackerOrigin );
			
			// Create the shadow strike effect
			Create_TE_SPRITETRAIL( vAttackerOrigin, vVictimOrigin, arrIdSprites[SPR_SHADOWSTRIKE], 50, 15, 1, 2, 6 );
			
			// Emit the shadow strike sound
			emit_sound( idVictim, CHAN_STATIC, arrStrSounds[SOUND_SHADOWSTRIKE], 1.0, ATTN_NORM, 0, PITCH_NORM );

			// Damage the user
			WC3_Damage( idVictim, idAttacker, iShadowStrikeDamage, CSW_SHADOW, iHitPlace );
			//Второй вариант
			//new iShadowStrikeDamage = floatround( 10 * fShadow );
			//WC3_Damage( idVictim, idAttacker, iShadowStrikeDamage, CSW_SHADOW, iHitPlace );
		}
		else if ( get_pcvar_num( CVAR_wc3_psychostats ) )
		{
			new WEAPON = CSW_SHADOW - CSW_WAR3_MIN;

			iStatsShots[idAttacker][WEAPON]++;
		}
	}
}