
#define NOVA_DAMAGE				10		// Nova Damage	

#define	CM_ARCANE_MAX			16000	// Max money 
#define	CM_ARCANE_FREQ			10.0		// Freq of aura 
#define CM_ARCANE_RANGE	  		750		// Range to money wave

#define DAMAGE_FIELD			40		
#define DAMAGE_FIELD_RADIUS		750


// Crystal Nova
CM_SkillsOffensive( iAttacker, iVictim, iHitPlace )
{

	static iSkillLevel;

	// Nova 
	iSkillLevel = SM_GetSkillLevel( iAttacker, SKILL_NOVA );
	if ( iSkillLevel > 0 )
	{

		if ( random_float( 0.0, 1.0 ) <= p_nova[iSkillLevel-1] )
		{
			new vVictimOrigin[3], vAttackerOrigin[3]
			get_user_origin( iVictim, vVictimOrigin );
			get_user_origin( iAttacker, vAttackerOrigin );
			
			// Create the nova effect
			Create_TE_SPRITETRAIL( vAttackerOrigin, vVictimOrigin, g_iSprites[SPR_NOVA],50, random_num(27,30), 1, random_num(30,70), 40 )
			
			// Emit the nova sound
			emit_sound( iAttacker, CHAN_STATIC, g_szSounds[SOUND_NOVA], 1.0, ATTN_NORM, 0, PITCH_NORM );
			emit_sound( iVictim, CHAN_STATIC, g_szSounds[SOUND_NOVA], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
			// Damage the user
			WC3_Damage( iVictim, iAttacker, NOVA_DAMAGE, CSW_SHADOW, iHitPlace );
		}
	}
}


// Arcane Aura
// Helper function to start the healing process
public CM_MoneyWave( id )
{
	if ( !task_exists( id + TASK_AURA ) )
	{
		_CM_MoneyWave( id );
	}
}

// We don't need to ever actually "turn this off" since this task will take care of itself
public _CM_MoneyWave( id )
{
	
	if ( id >= TASK_AURA )
	{
		id -= TASK_AURA;
	}

	// User is no longer connected :/
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}
	
	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_ARCANE );

	// User doesn't have this skill, so lets return
	//  - Also return if this was called twice
	if ( iSkillLevel <= 0 )
	{
		return;
	}

	// Continue healing...
	if ( is_user_alive( id ) )
	{
		set_task( CM_ARCANE_FREQ, "_CM_MoneyWave", TASK_AURA + id );
	}
	
	// Prevent healing if this player is hexed
	if ( p_data_b[id][PB_HEXED] )
	{
		return;
	}


	new players[32], numberofplayers, targetid, targetorigin[3], origin[3];
	new iTeam = get_user_team( id );

	get_user_origin( id, origin );
	get_players( players, numberofplayers, "a" );
	
	// Loop through each player and check to see if one is close enough to be healed
	for ( new i = 0; i < numberofplayers; i++ )
	{
		targetid = players[i];
		
		if ( p_data_b[targetid][PB_ISCONNECTED] && get_user_team( targetid ) == iTeam )
		{
			get_user_origin( targetid, targetorigin );
			
			
			if ( get_distance(origin, targetorigin) < CM_ARCANE_RANGE )
			{
				get_user_origin( targetid, origin )
				
				
				if ( SHARED_GetUserMoney( targetid ) + p_arcane[iSkillLevel-1] <= CM_ARCANE_MAX )
				{
					SHARED_SetUserMoney( targetid, SHARED_GetUserMoney( targetid ) + p_arcane[iSkillLevel-1], 1 );

				}
				else 
				{
					SHARED_SetUserMoney( targetid, CM_ARCANE_MAX, 1 );
				}
				
				// SHARED_Glow( targetid, 0, 0, 100, 0 );
			}
		}
	}

	return;
}

// CM Ultimate 

public CM_ULT_Field( id )
{

	// Ultimate has been used, so we can't use it again!
	if ( !ULT_Available( id ) )
	{
		return;
	}

	// If we ult while changing teams, you will kill your old teammates, we don't want that!!
	if ( p_data_b[id][PB_CHANGINGTEAM] )
	{
		return;
	}
	
	
	emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_FIELD], 1.0, ATTN_NORM, 0, PITCH_NORM );

	new players[32], numberofplayers, targetid, targetorigin[3], origin[3], vOrigin[3];
	new TargetNumber = 0;
	new BlockerNumber = 0;
	new iTeam = get_user_team( id );
	
	get_user_origin( id, vOrigin );
	
	new vPosition[3];

	vPosition[0] = vOrigin[0];
	vPosition[1] = vOrigin[1];
	vPosition[2] = vOrigin[2] + DAMAGE_FIELD_RADIUS;

	Create_TE_BEAMCYLINDER( vOrigin, vOrigin, vPosition, g_iSprites[SPR_SHOCKWAVE], 0, 0, 6, 16, 0, 0, 100, 200, 190, 0 );
	

	get_user_origin( id, origin );
	get_players( players, numberofplayers, "a" );
	
	// Loop through each player and check to see if one is close enough to be healed
	for ( new i = 0; i < numberofplayers; i++ )
	{
		targetid = players[i];
		
		// User is not on the player team
		if ( p_data_b[targetid][PB_ISCONNECTED] && get_user_team( targetid ) != iTeam )
		{
			get_user_origin( targetid, targetorigin );
						
			// User is close enough
			if ( get_distance(origin, targetorigin) <  DAMAGE_FIELD_RADIUS )
			{
			
				if ( ULT_CanUserBlockUlt( targetid ) )
				{
					ULT_RemoveCharge( targetid, 5 );
					
					BlockerNumber++;
				
				}
				else 
				{
				
					TargetNumber++;
					
					get_user_origin( targetid, vOrigin );

					new ptStartBlizzard[3], ptEndBlizzard[3];
					ptStartBlizzard[0] = vOrigin[0];
					ptStartBlizzard[1] = vOrigin[1];
					ptStartBlizzard[2] = vOrigin[2] + 600;
					ptEndBlizzard[0] = vOrigin[0];
					ptEndBlizzard[1] = vOrigin[1];
					ptEndBlizzard[2] = vOrigin[2] - 600;

					new ptStartIceBolt[3], ptEndIceBolt[3];
					ptStartIceBolt[0] = vOrigin[0];
					ptStartIceBolt[1] = vOrigin[1];
					ptStartIceBolt[2] = vOrigin[2] + 100;
					ptEndIceBolt[0] = vOrigin[0];
					ptEndIceBolt[1] = vOrigin[1];
					ptEndIceBolt[2] = vOrigin[2] + 50;

					emit_sound(targetid, CHAN_STATIC, g_szSounds[SOUND_NOVA], 0.5, ATTN_NORM, 0, PITCH_NORM );
					
					Create_ScreenFade( targetid, (1<<10), (1<<10), (1<<12), 0, 100, 200, 160 );
					
					Create_ScreenShake( targetid, (10<<12), (2<<12), (5<<12) );
					
					WC3_Damage(targetid, id, DAMAGE_FIELD, CSW_BANISH, 0 );

					Create_TE_BEAMPOINTS(ptStartBlizzard, ptEndBlizzard, g_iSprites[SPR_FIELD],0, 0, 15, 255, 0, 255, 255, 255, 255, 0);

					for(new i = 1; i < 3; i++) 
						Create_TE_SPRITETRAIL(ptStartIceBolt, ptEndIceBolt, g_iSprites[SPR_NOVA], 50, random_num(27,30), 1, random_num(30,70), 40 )
		
				}
			}
		}
	}
	
	if ( TargetNumber == 0 )
	{
		client_print( id, print_chat, "%s No enemy around or enemy has immunity.", GAME_NAME);
	}
	else
	{
		//client_print( id, print_chat, "%s You hit %d enemy targets.", GAME_NAME, TargetNumber);
	}
	
	ULT_Icon( id, ICON_HIDE );
	
	ULT_ResetCooldown( id, get_pcvar_num( CVAR_wc3_ult_cooldown ) );
	
	return ;
}



// CM Frostbite

CM_Frostbite( id )
{
	
	if ( !SHARED_HasSmokeGrenade( id ) )
	{
		g_iBiteTimer[id] = 0;

		_CM_Frostbite_Give( id );
	}

	return;
}

CM_Frostbite_Begin( id )
{
	// Lets check skill only to set timer, we already checked before if he has the skill 
	
	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_BITE );
	
	g_iBiteTimer[id] = p_frostbite[iSkillLevel-1];

	// WC3_StatusText( id, TXT_TIMER, "Frozen grenade in %d seconds.", g_iBiteTimer[id] );
	WC3_SyncGrenadeHud( id );

	g_iBiteTimer[id]--;

	set_task( 1.0, "_CM_Frostbite_Give", TASK_FROSTBITE + id );
}

public _CM_Frostbite_Give( id )
{
	
	if ( id >= TASK_FROSTBITE )
	{
		id -= TASK_FROSTBITE;
	}

	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_BITE );
	
	if(iSkillLevel <= 0)
	{
		return;
	}
	
	
	if ( !p_data_b[id][PB_ISCONNECTED] || !is_user_alive( id ) )
	{
		return;
	}

	if ( g_iBiteTimer[id] == g_iBiteTimer[id] - 1 )
	{
		SHARED_SaveWeapons( id );
	}


	if ( SHARED_HasSmokeGrenade( id ) )
	{
		g_iBiteTimer[id] = 0;

		return;
	}
	


	if ( g_iBiteTimer[id] > 0 )
	{
	
	//	WC3_StatusText( id, TXT_TIMER, "Frozen grenade in %d seconds.", g_iBiteTimer[id] );
	WC3_SyncGrenadeHud( id );

		g_iBiteTimer[id]--;

		set_task( 1.0, "_CM_Frostbite_Give", TASK_FROSTBITE + id );

		return;
	}


		give_item( id, "weapon_smokegrenade" );
	


	// Display a message to the user
	// WC3_StatusText( id, TXT_TIMER, "Frozen Grenade !" )
	WC3_SyncGrenadeHud( id );

	return;
}		
