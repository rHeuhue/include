/*
*	Race: Blood Mage Functions
*/

new bool:g_bPlayerBanished[33];

//Супер навык - Ultimate
public BM_ULT_Immolate( iCaster, iTarget )
{
	emit_sound( iCaster, CHAN_STATIC, arrStrSounds[SOUND_IMMOLATE], 0.5, ATTN_NORM, 0, PITCH_NORM );

	// Emit sound and create the fire exploding effect on the player

	new vTargetOrigin[3];
	get_user_origin( iTarget, vTargetOrigin );

	Create_TE_EXPLOSION( vTargetOrigin, vTargetOrigin, arrIdSprites[SPR_IMMOLATE], 20, 24, 4 );
	Create_TE_EXPLOSION( vTargetOrigin, vTargetOrigin, arrIdSprites[SPR_BURNING], 30, 24, 4 );

	Create_ScreenShake( iTarget, (10<<12), (2<<12), (5<<12) );

	// Do initial immolate damage and make their screen shake a little

	WC3_Damage( iTarget, iCaster, iImmolateDamage, CSW_IMMOLATE, -1 )

	new parm_DoT[3];
	parm_DoT[0] = iCaster;
	parm_DoT[1] = iTarget;
	parm_DoT[2] = 1;

	// Start the ultimate DoT

	new TaskId = TASK_BURNING + iTarget;
	set_task( 1.0, "BM_ULT_Immolate_DoT", TaskId, parm_DoT, 3 );
	
	return PLUGIN_HANDLED;
}

public BM_ULT_Immolate_DoT( parm_DoT[3] )
{
	new iCaster = parm_DoT[0];
	new iTarget = parm_DoT[1];
	new iCounter = parm_DoT[2];
	
	// Stop DoT if the max number of ticks is reached

	if ( iCounter > iImmolateDot ) 
	{
		BM_ULT_Immolate_Remove( iTarget );
		return PLUGIN_HANDLED;
	}

	// Emit sound and show the burning effect on the player

	new vTargetOrigin[3];
	get_user_origin( iTarget, vTargetOrigin );

	emit_sound( iTarget, CHAN_STATIC, arrStrSounds[SOUND_IMMOLATE_BURNING], 0.5, ATTN_NORM, 0, PITCH_NORM );

	Create_TE_SPRITE( vTargetOrigin, arrIdSprites[SPR_FIRE], 3, 200 );

	// Do the DoT damage

	WC3_Damage( iTarget, iCaster, iImmolateDotDamage, CSW_IMMOLATE, -1 )

	// If the target is still alive after this, make their screen glow orange and start the task again

	if ( is_user_alive( iTarget ) )
	{
		arrIntData[iTarget][PB_ISBURNING] = true;

		Create_ScreenFade( iTarget, (1<<10), (1<<10), (1<<12), 255, 108, 0, 160 );

		parm_DoT[2]++;

		set_task( 1.0, "BM_ULT_Immolate_DoT", TASK_BURNING + iTarget, parm_DoT, 3 );

	}

	return PLUGIN_HANDLED;
}


BM_ULT_Immolate_Remove(iTarget) 
{
	arrIntData[iTarget][PB_ISBURNING] = false;

	new TaskId = TASK_BURNING + iTarget;
	remove_task( TaskId, 0 );

	return PLUGIN_HANDLED;
}

// Check to see if a player will become a Phoenix
//Скил 1 уровня - Феникс (Phoenix)
BM_PhoenixCheck(idUser)
{
	
	new iSkillLevel = SM_GetSkillLevel( idUser, SKILL_PHOENIX );
	if (iSkillLevel > 0 && arrBoolData[idUser][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idUser,SKILL_PHOENIX) == false)
	{
		new Float:fPhoenix = ArrayGetCell(arrPhoenix,iSkillLevel-1);
		if (random_float(fBloodMageSkill1MinPercent,fBloodMageSkill1MaxPercent) <= fPhoenix ) 
			arrBoolData[idUser][PB_PHOENIX] = true;
	}
	else
	{
		arrBoolData[idUser][PB_PHOENIX] = false;
	}
}

// This function is called when a user dies
BM_PhoenixSpawn( idUser )
{
	
	// If this user is about to respawn, then we don't even want to check
	if ( arrIntData[idUser][P_RESPAWNBY] || g_EndRound )
	{
		return;
	}

	new iTeam = get_user_team( idUser );
	new iPhoenixID = BM_PhoenixExists( iTeam );
	
	// Then we have a Phoenix!!
	if ( iPhoenixID != -1 )
	{

		// Lets make sure they're not going to revive themself
		if ( iPhoenixID != idUser )
		{
			// The idAttacker is no longer a Phoenix
			arrBoolData[iPhoenixID][PB_PHOENIX] = false;
			
			// The user is about to respawn
			arrIntData[idUser][P_RESPAWNBY] = RESPAWN_PHOENIX;
			
			// Respawn the user
			set_task( SPAWN_DELAY, "_SHARED_Spawn", TASK_SPAWN + idUser );

			new szCastername[32], szSpawnerName[32];

			get_user_name( iPhoenixID, szCastername,31 )
			get_user_name( idUser, szSpawnerName, 31 )

			format(szMessage, charsmax(szMessage), "%s %L",szCastername,LANG_PLAYER,"HAS_REVIVED_YOU");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"YOU_HAVE_REVIVED",szSpawnerName);	
			cssbChatColor(iPhoenixID,"%s%s",fTagWar3ft(),szMessage);

		}
	}

	return;
}

// Check to see if a Phoenix exists on a given team
BM_PhoenixExists( iTeam )
{

	new players[32], numberofplayers, idUser, i;
	get_players(players, numberofplayers, "a");

	// Loop through all the players to find someone with phoenix
	for ( i = 0; i < numberofplayers; i++ )
	{
		idUser = players[i];

		if ( get_user_team( idUser ) == iTeam )
		{
			if ( arrBoolData[idUser][PB_PHOENIX] && !arrBoolData[idUser][PB_HEXED] )
			{
				return idUser;
			}
		}
	}

	return -1;
}

//Скил 2 уровня - Изгнание (Banish)
public _BM_BanishReturn( parm[] )
{
	
	new idUser = parm[0];
	
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}

	// If the round is over we want to move the player back - otherwise they might be moved after they have respawned - that'd be bad
	if ( parm[1] > 0 && !g_EndRound )
	{
		parm[1]--;
		
		// Black screen the user!
		Create_ScreenFade( idUser, 2, (1<<10), (1<<12), 0, 0, 0, 255 );

		set_task( 0.1, "_BM_BanishReturn", TASK_BANISH + idUser, parm, 5 );
	}
	else
	{
		new vOrigin[3];
		vOrigin[0] = parm[2];
		vOrigin[1] = parm[3];
		vOrigin[2] = parm[4];

		// Move the user back!
		SHARED_Teleport( idUser, vOrigin );

		// Make the user glow!
		SHARED_Glow( idUser, 0, 0, 0, 100 );

		// Create a screen fade
		Create_ScreenFade( idUser, 0, 0, 0, 0, 0, 0, 0 );

		// User is no longer banished
		g_bPlayerBanished[idUser] = false;
	}
	
}

//Скил 3 уровня - Похищение денег (Siphon Mana)
BM_SkillsOffensive( idAttacker, idVictim, iDamage )
{
	// Siphon Mana
	new iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_SIPHONMANA );
	if ( iSkillLevel > 0 && ((get_user_team( idAttacker ) != get_user_team( idVictim ))) && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false )
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_SIPHONMANA) == true)
			return;

		new Float:fMana = ArrayGetCell(arrSiphonMana,iSkillLevel-1);
		new iMoney = floatround(fMana * SHARED_GetUserMoney(idVictim));
		
		// Remove the money from the victim
		SHARED_SetUserMoney( idVictim, SHARED_GetUserMoney( idVictim ) - iMoney, 1 );
		
		// Give the money to the attacker
		SHARED_SetUserMoney( idAttacker, SHARED_GetUserMoney( idAttacker ) + iMoney, 1 );

		// Make the user glow!
		//SHARED_Glow( idVictim, 0, iDamage, 0, 0 );
		SHARED_GlowShell(idVictim,0,255,iDamage,get_pcvar_float( CVAR_wc3_glowshell_time ),get_pcvar_num( CVAR_wc3_glowshell_amount ));
		
		// Create a screen fade (purplish)
		Create_ScreenFade( idAttacker, (1<<10), (1<<10), (1<<12), 144, 58, 255, g_GlowLevel[idAttacker][1] );
	}
}

//Скил 4 уровня -  Шипованная кожа (Resistant Skin)
BM_SkillsDefensive(idAttacker, idVictim, iDamage )
{
	if(!is_user_alive(idVictim)|| !is_user_connected(idVictim))  
		return;

	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
		return;
	
	// Resistant Skin - Стандарт
	new iSkillLevel = SM_GetSkillLevel( idVictim, PASS_RESISTANTSKIN );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idVictim,PASS_RESISTANTSKIN) == false)
	{
		new Float:fResistant = ArrayGetCell(arrResistantSkin,arrIntData[idVictim][P_LEVEL]);
		new iBonusHealth = floatround( float( iDamage ) * fResistant );
		
		#if MODE_LOG
		#if LOG_PASS_RESISTANTSKIN > 0
			clLog:logRaceBlood(idAttacker,fResistant,iDamage,iBonusHealth);
		#endif
		#endif

		if (arrBoolData[idVictim][PB_ISCONNECTED])
		{			
			new iMinHealth = clHP:getRaceMinHealth(idVictim);
			new iCurrentHealth =  clHP:getUserHealth(idVictim);
			new iBonusHp = iBonusHealth;
			
			if((iCurrentHealth + iBonusHp) > iMinHealth)
				clHP:setUserHealth(idVictim,iMinHealth);
			else
				clHP:setUserHealth(idVictim,iCurrentHealth + iBonusHp);
		}
	}

	// Banish
	iSkillLevel = SM_GetSkillLevel( idVictim, SKILL_BANISH );
	if (iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idVictim,SKILL_BANISH) == false)
	{
		new Float:fBanish = ArrayGetCell(arrBanish,iSkillLevel-1);	
		if ( random_float(fBloodMageSkill2MinPercent,fBloodMageSkill2MaxPercent) <= fBanish )
		{

			// Make sure the user isn't banished and that the enemy isn't in the victim's view (victim might be attacking them)
			if ( !g_bPlayerBanished[idAttacker] && !UTIL_CanSeePlayer( idVictim, idAttacker ) )
			{

				// Deal some damage
				WC3_Damage( idAttacker, idVictim, iBanishDamage, CSW_BANISH, 0 );
				
				// Play the Banish sound
				emit_sound( idAttacker, CHAN_STATIC, arrStrSounds[SOUND_BANISH], 1.0, ATTN_NORM, 0, PITCH_NORM );

				// Black screen the user!
				Create_ScreenFade( idAttacker, 2, (1<<10), (1<<12), 0, 0, 0, 255 );

				new vOrigin[3];
				get_user_origin( idAttacker, vOrigin );

				new parm[5];
				parm[0] = idAttacker;
				parm[1] = floatround( fBanishHoldTime * 10.0 );
				parm[2] = vOrigin[0];
				parm[3] = vOrigin[1];
				parm[4] = vOrigin[2];

				// Create the "banish" sprite
				Create_TE_SPRITE( vOrigin, arrIdSprites[SPR_BANISH], 10, 255 );

				vOrigin[2] -= 2000;

				set_user_origin( idAttacker, vOrigin );

				set_task( 0.1, "_BM_BanishReturn", TASK_BANISH + idAttacker, parm, 5 );
			}
		}
	}
}