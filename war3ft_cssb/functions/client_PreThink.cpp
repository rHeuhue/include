// ******************************************************************
// 
// ******************************************************************

public client_PreThink(idUser)
{
	if (!WC3_Check())
		return;

	if (arrBoolData[idUser][PB_ISCONNECTED])
	{
		if (is_user_alive(idUser))
		{
			//Парашют
			if(get_pcvar_num(CVAR_wc3_parachute) > 0)
				clGl::fParachuteActive(idUser);
						
			// This is used so we can't hear the undead's footsteps at level 3
			if ( SM_GetSkillLevel(idUser, SKILL_UNHOLYAURA ) > 0 && !arrBoolData[idUser][PB_STUNNED] && !arrBoolData[idUser][PB_SLOWED] )
			{
				new Float:vel[3];
				entity_get_vector(idUser, EV_VEC_velocity, vel);
			
				// When this is true, the user is walking...  lets hope :P
				if ( vector_length( vel ) < 180.0 )
				{
					entity_set_int( idUser, EV_INT_flTimeStepSound, 999 );
				}

				// Otherwise if we just set it on the previous tick we need to set it back
				else if ( entity_get_int(idUser, EV_INT_flTimeStepSound) > 500 )
				{
					entity_set_int( idUser, EV_INT_flTimeStepSound, 200 );
				}
			}

			//ITEM_AMULET - Amulet of the Cat
			if ( ITEM_Has( idUser, ITEM_AMULET ) > ITEM_NONE || 
				 fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_AMULET ||
			 	 bIsUserRace(idUser,RACE_DISRUPTOR) ||
				 clVIP:isAccesItemVip(idUser,ITEM_AMULET) == true
				)
			{
				entity_set_int( idUser, EV_INT_flTimeStepSound, 999 );
			}
					
		}
		
		// User is dead
		else
		{

			// Check to see if spectated player has changed
			new iTarget = entity_get_int( idUser, EV_INT_iuser2 );
			
			new Float:fTime = halflife_time();

			// Then we are looking at a new player or the last hud message has disappeared
			if ( g_iSpectatingID[idUser] != iTarget || g_fLastSpecDisplay[idUser] <= fTime )
			{

				// We have a valid target!!
				if ( SHARED_ValidPlayer( iTarget ) && iTarget != idUser )
				{
					WC3_ShowSpecInfo( idUser, iTarget );

					g_fLastSpecDisplay[idUser] = fTime + SPEC_HOLDTIME;
				}

				g_iSpectatingID[idUser] = iTarget;
			}
		}
	}

	return;
}