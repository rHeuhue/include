#define DR_CROW_FORM_DURATION	3



public DR_ULT_Crow( id )
{
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}

	ULT_ResetCooldown( id, get_pcvar_num( CVAR_wc3_ult_cooldown ) + DR_CROW_FORM_DURATION, false );

	ULT_Icon( id, ICON_FLASH );
	
	Create_BarTime( id, DR_CROW_FORM_DURATION, 0 );
		
	emit_sound( id, CHAN_STATIC, g_szSounds[SOUND_VOODOO], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
	set_user_noclip(id,1);
	
	
	get_user_origin(id, CrowStartPosition[id], 0);
	

	set_task( float( DR_CROW_FORM_DURATION ), "DR_Ult_Remove", TASK_CROWFORM + id );

	return;
}

public DR_Ult_Remove( id )
{
	if ( id >= TASK_CROWFORM )
	{
		id -= TASK_CROWFORM;
	}

	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return;
	}

	set_user_noclip(id,0);

	ULT_Icon( id, ICON_HIDE );
	
	Check_Crow(id);

	return;
}


public Check_Crow(id)
{
	if (!is_user_alive(id)) 
	return;

	get_user_origin(id, CrowLastPosition[id], 0);

	new Float:iVelocity[3]
	Entvars_Get_Vector(id, EV_VEC_velocity, iVelocity)

	// Force a little jump 
	if ( iVelocity[0]==0.0 && iVelocity[1]==0.0 ) 
	{
		iVelocity[0] += 20.0
		iVelocity[2] += 100.0
		Entvars_Set_Vector(id, EV_VEC_velocity, iVelocity)
	}

	set_task(0.4,"Slay_Bad_Crow",id)
}

public Slay_Bad_Crow(id)
{
	new iOrigin[3]

	if (!is_user_alive(id)) 
	return;

	get_user_origin(id, iOrigin, 0)
	if ( CrowLastPosition[id][0] == iOrigin[0] && CrowLastPosition[id][1] == iOrigin[1] && CrowLastPosition[id][2] == iOrigin[2] && is_user_alive(id) ) 
	{
		//user_kill(id);
		// client_print( id, print_chat, "%s You can not survive in wall without crow form.", GAME_NAME);
		
		set_user_origin( id, CrowStartPosition[id] );
		client_print( id, print_chat, "%s You can not survive in wall.", GAME_NAME);
	}
}



// Roar 
DR_SkillsDefensive( iAttacker, iVictim )
{

	static iSkillLevel;

	iSkillLevel = SM_GetSkillLevel( iVictim, SKILL_ROAR );
	if ( iSkillLevel > 0 )
	{

		if ( random_float( 0.0, 1.0 ) <= p_roar[iSkillLevel-1] )
		{
	
			// Emit the roar sound
			emit_sound( iAttacker, CHAN_STATIC, g_szSounds[SOUND_ROAR], 1.0, ATTN_NORM, 0, PITCH_NORM );
			//emit_sound( iVictim, CHAN_STATIC, g_szSounds[SOUND_ROAR], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
			Create_ScreenFade( iAttacker, (9<<15), (9<<10), (5<<12), 255, 255, 255, 255 );
			
			
		}
	}
}


// Radar 

public FW_RadarThink( id )
{
	if( !is_user_alive( id ) )
		return FMRES_IGNORED;
		
	static iSkillLevel;

	iSkillLevel = SM_GetSkillLevel( id, SKILL_CYCLONE );
	
	g_fCurrentTime = get_gametime( );
	
	
	if( cs_get_user_team( id ) == CS_TEAM_CT && iSkillLevel > 0 )
	{
		
		if( g_fNextRadarTime[ id ] <= g_fCurrentTime )
		{
		
			
			g_fNextRadarTime[ id ] = g_fCurrentTime + RADAR_DELAY;
			static bool:bBeep;
			bBeep = false;
			
			static Float:fDruidOrigin[ 3 ];
			pev( id, pev_origin, fDruidOrigin ); 
			
			for( new iTero = 1; iTero <= g_iMaxPlayers; iTero++ )
			{
				if( cs_get_user_team( iTero ) == CS_TEAM_T && is_user_alive( iTero ) && get_user_health(iTero) <= p_cyclone[iSkillLevel-1] )
				{
				
						static Float:fOrigin[ 3 ];
						pev( iTero, pev_origin, fOrigin );
						
						UTIL_ShowOnRadar( id, iTero, fOrigin );
			
						bBeep = true;
						
						if( get_distance_f( fDruidOrigin, fOrigin ) <= 1000.0 )
						{
							// emit_sound( iTero, CHAN_AUTO, g_szSounds[SOUND_BEAP], 1.0, ATTN_NORM, 0, PITCH_NORM );
							
						}
						
				}
			}
					
			if( bBeep )
			{
				//	emit_sound( id, CHAN_AUTO, g_szSounds[SOUND_BEAP], 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
					
		}
		
	}
	else if( cs_get_user_team( id ) == CS_TEAM_T && iSkillLevel > 0 )
	{
		
		if( g_fNextRadarTime[ id ] <= g_fCurrentTime )
		{
			
			g_fNextRadarTime[ id ] = g_fCurrentTime + RADAR_DELAY;
			static bool:bBeep;
			bBeep = false;
			
			static Float:fDruidOrigin[ 3 ];
			pev( id, pev_origin, fDruidOrigin );
			
			for( new iCT = 1; iCT <= g_iMaxPlayers; iCT++ )
			{
				if( cs_get_user_team( iCT ) == CS_TEAM_CT && is_user_alive( iCT ) && get_user_health(iCT) <= p_cyclone[iSkillLevel-1] )
				{
				
						static Float:fOrigin[ 3 ];
						pev( iCT, pev_origin, fOrigin );
						
						UTIL_ShowOnRadar( id, iCT, fOrigin );
						
						bBeep = true;
						
						if( get_distance_f( fDruidOrigin, fOrigin ) <= 1000.0 )
						{
							// emit_sound( iCT, CHAN_AUTO, g_szSounds[SOUND_BEAP], 1.0, ATTN_NORM, 0, PITCH_NORM );
						}
						
				}
			}
					
			if( bBeep )
			{
				// emit_sound( id, CHAN_AUTO, g_szSounds[SOUND_BEAP], 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
					
		}
		
	}
	
	
	
	
	
	
	
	/*
	else if( cs_get_user_team( id ) == CS_TEAM_T )
	{
		
		
		static Float:fFurienOrigin[ 3 ];
		pev( id, pev_origin, fFurienOrigin );
		
		static Float:fVelocity[ 3 ];
		pev( id, pev_velocity, fVelocity );
		
		static Float:fCurSpeed;
		fCurSpeed = vector_length( fVelocity );
		
		if( fCurSpeed > float( get_pcvar_num( g_iCvarMinFurienSpeed ) ) )
		{	
	
			static iAnti;
			for( iAnti = 1; iAnti <= g_iMaxPlayers; iAnti++ )
			{
				if( cs_get_user_team( iAnti ) == CS_TEAM_CT && is_user_alive( iAnti ) )
				{
					static Float:fAntiOrigin[ 3 ];
					pev( iAnti, pev_origin, fAntiOrigin );
					
					if( get_distance_f( fFurienOrigin, fAntiOrigin ) <= float( get_pcvar_num( g_iCvarRadarRange ) ) )
					{
						g_bDrawFurienOnRadar[ id ] = true;
						
						break;
					}
				}
			}
		}
		else
		{
			g_bDrawFurienOnRadar[ id ] = false;
		}
		
	}
	*/
	
	
	return FMRES_IGNORED;
	
}