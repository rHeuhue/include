/*
*	Race: Undead Scourge Functions
*/

UD_Suicide( idUser )
{
	
	// Ultimate has been used, so we can't use it again!
	if ( !ULT_Available( idUser ) )
		return;

	// If we ult while changing teams, you will kill your old teammates, we don't want that!!
	if ( arrBoolData[idUser][PB_CHANGINGTEAM] )
		return;

	// Play the undead explosion sound!!!
	emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_SUICIDE], 1.0, ATTN_NORM, 0, PITCH_NORM );

	new parm[5], vOrigin[3];
	get_user_origin( idUser, vOrigin );

	parm[0] = idUser;
	parm[1] = 6;
	parm[2] = vOrigin[0];
	parm[3] = vOrigin[1];
	parm[4] = vOrigin[2];

	// Set up the tasks to damage + draw effects
	set_task( 0.5, "_UD_SuicideExplode", TASK_EXPLOSION + idUser, parm, 5 );
	set_task( 0.5, "_UD_SuicideBlastCircles", TASK_BEAMCYLINDER + idUser, parm, 5 );
	
	// Create an implosion effect where they died
	Create_TE_IMPLOSION( vOrigin, 100, 20, 5 );
	
	// Set up an ultimate delay (in case the user respawns)
	fResetUltimateTimerDivider(idUser);
}


// This is only use in _UD_SuicideExplode so declaring it here should be fine
new bool:bIgnoreDmg[33] = false;

// Draw the explosions
public _UD_SuicideExplode( parm[5] )
{
	new idUser = parm[0];

	if ( get_pcvar_num( CVAR_wc3_psychostats ) )
	{
		new WEAPON = CSW_SUICIDE - CSW_WAR3_MIN;

		iStatsShots[idUser][WEAPON]++;
	}

	new vOrigin[3], vPosition[3];
	vOrigin[0] = parm[2];
	vOrigin[1] = parm[3];
	vOrigin[2] = parm[4];

	vPosition[0] = vOrigin[0] + random_num( -100, 100 );
	vPosition[1] = vOrigin[1] + random_num( -100, 100 );
	vPosition[2] = vOrigin[2] + random_num( -50, 50 );
	
	Create_TE_EXPLOSION( vOrigin, vPosition, arrIdSprites[SPR_FIREBALL], (random_num(0,20) + 20), 12, TE_EXPLFLAG_NONE );

	Create_TE_Smoke( vOrigin, vPosition, arrIdSprites[SPR_SMOKE], 60, 10 );

	new players[32], numberofplayers;
	get_players( players, numberofplayers, "a" );

	new i, iTargetID, vTargetOrigin[3], iDamage, iDistance;
	new iMultiplier = ( iExplosionMaxDamage * iExplosionMaxDamage ) / iExplosionRange;
	new iTeam = get_user_team( idUser );
	
	// Check all players and see if they should be damaged
	for ( i = 0; i < numberofplayers; i++ )
	{
		iTargetID = players[i];
		
		// Get origin of target
		get_user_origin( iTargetID, vTargetOrigin );

		// Get distance in b/t target and idAttacker
		iDistance = get_distance( vOrigin, vTargetOrigin );
		
		// Make sure this user is close enough to do damage + isn't immune + isn't on the same team + isn't already immune to all damage
		if ( iDistance < iExplosionRange && iTeam != get_user_team( iTargetID ) && !bIgnoreDmg[iTargetID] )
		{

			if ( ULT_CanUserBlockUlt( iTargetID,idUser ) )
			{
				ULT_RemoveCharge(iTargetID);

				ULT_Blocked( idUser );
				
				bIgnoreDmg[iTargetID] = true;
			}
			
			// The user isn't immune!
			else
			{
			
				// Calculate the damage to be done
				iDamage = ( iExplosionRange - iDistance) * iMultiplier;
				iDamage = sqroot( iDamage );
				
				//Рыцарь смерти
				if(arrIntData[iTargetID][P_RACE] == RACE_DEATH_KNIGHT)
					if (random_float(0.0,1.0) <= fControlUndeadExp ) // шанс срабатывания защиты от взрыва Нежити
						iDamage = 0;

				// Damage them!!!!
				WC3_Damage(iTargetID, idUser, iDamage, CSW_SUICIDE, -1 );


				// Lets shake up their screen a bit
				Create_ScreenShake(iTargetID, (1<<14), (1<<13), (1<<14) );
			}
		}

		// Reset the "don't damage" rule
		if ( parm[1] - 1 <= 0 )
		{
			bIgnoreDmg[iTargetID] = false;
		}
	}

	--parm[1];
	
	// Lets keep going if we have some left!
	if ( parm[1] > 0 )
	{
		set_task( 0.1, "_UD_SuicideExplode", TASK_EXPLOSION + idUser, parm, 5 );
	}
}

// Draw the blast circles
public _UD_SuicideBlastCircles( parm[5] )
{
	new vOrigin[3], vPosition[3];

	vOrigin[0] = parm[2];
	vOrigin[1] = parm[3];
	vOrigin[2] = parm[4] - 16;

	vPosition[0] = vOrigin[0];
	vPosition[1] = vOrigin[1];
	vPosition[2] = vOrigin[2] + iExplosionBlastRadius;

	Create_TE_BEAMCYLINDER( vOrigin, vOrigin, vPosition, arrIdSprites[SPR_SHOCKWAVE], 0, 0, 6, 16, 0, 188, 220, 255, 255, 0 );

	vOrigin[2] = ( vOrigin[2] - iExplosionBlastRadius ) + ( iExplosionBlastRadius / 2 );

	Create_TE_BEAMCYLINDER( vOrigin, vOrigin, vPosition, arrIdSprites[SPR_SHOCKWAVE], 0, 0, 6, 16, 0, 188, 220, 255, 255, 0 );
}


UD_SkillsOffensive(idAttacker,idVictim,iDamage)
{
	if(!is_user_connected(idVictim)) 
      return;

	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
      return;
	
	if (!arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;

	// Vampiric Aura
	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_VAMPIRICAURA );
	if (iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISCONNECTED] && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_VAMPIRICAURA) == true)
			return;
		
		new iMinHealth = clHP:getRaceMinHealth(idAttacker);
		new iCurrentHealth =  clHP:getUserHealth(idAttacker);
		
		new Float:fVampiric = ArrayGetCell(arrVampiricAura,iSkillLevel-1);
		new iBonusHp = floatround( float( iDamage ) * fVampiric);

		#if MODE_LOG
			clLog:logRaceUndead(idAttacker,iCurrentHealth,fVampiric,iDamage,iBonusHp);
		#endif

		//Если Нежить наносит повреждение Рыцарю смерти
		if(arrIntData[idVictim][P_RACE] == RACE_DEATH_KNIGHT)
		{
			if(isDisabledSkillsOnMap(idVictim,PASS_DEATH_KNIGHT_CONTROL_UNDEAD) == false)
			{
				new iHealth_DK		= clHP:getUserHealth(idVictim);
				new iMinHealth_DK	= clHP:getRaceMinHealth(idVictim);
				new iBonusHealth_DK = floatround(fControlUndeadHP * iBonusHp);

				if (random_float(0.0,1.0) <= fControlUndeadChance )// шанс срабатывания отдачи Нежитью поглощаемого HP
				{
					if ((iHealth_DK + iBonusHealth_DK) > iMinHealth_DK )
						clHP:setUserHealth(idVictim,iMinHealth_DK);
					else
						clHP:setUserHealth(idVictim,iHealth_DK + iBonusHealth_DK);

				}

				SHARED_GlowShell(idAttacker,0,238,118,get_pcvar_float( CVAR_wc3_glowshell_time ),get_pcvar_num( CVAR_wc3_glowshell_amount ));
				Create_ScreenFade(idVictim, (1<<10), (1<<10), (1<<12), 0, 255, 0, iBonusHealth_DK );
			}
		}
		else
		{
			if (iCurrentHealth < iMinHealth)
			{
				if( (iCurrentHealth + iBonusHp) > iMinHealth )
					clHP:setUserHealth(idAttacker,iMinHealth);
				else
					clHP:setUserHealth(idAttacker,iCurrentHealth + iBonusHp);

			}

			SHARED_GlowShell(idVictim,0,238,118,get_pcvar_float( CVAR_wc3_glowshell_time ),get_pcvar_num( CVAR_wc3_glowshell_amount ));

			Create_ScreenFade(idAttacker, (1<<10), (1<<10), (1<<12), 0, 255, 0, iBonusHp);

		}
		
	}//if
}
