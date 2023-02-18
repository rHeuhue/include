/*
*	Race: Black magician (Черный маг) Functions
*/

//-----------------Базовые функции------------------------------------BEGIN {
//Инициализация скилов
public clRaceBlackMag::setSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	// Set up the Skill Owners
	g_SkillOwner[SKILL_BLACKSTRIKE				]	= RACE_BLACK_MAGICIAN;
	g_SkillOwner[SKILL_BLACKSHADOW				]	= RACE_BLACK_MAGICIAN;
	g_SkillOwner[SKILL_BLACKPOWER				]	= RACE_BLACK_MAGICIAN;
	g_SkillOwner[ULTIMATE_BLACKLIGHTNING		]	= RACE_BLACK_MAGICIAN;
	
	// Set up the skill types
	g_SkillType[SKILL_BLACKSTRIKE				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_BLACKSHADOW				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_BLACKPOWER				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_BLACKLIGHTNING			]	= SKILL_TYPE_ULTIMATE;
	
	// Set up the skill order
	g_SkillOrder[SKILL_BLACKSTRIKE				]	= SKILL_POS_1;
	g_SkillOrder[SKILL_BLACKSHADOW				]	= SKILL_POS_2;
	g_SkillOrder[SKILL_BLACKPOWER				]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_BLACKLIGHTNING		]	= SKILL_POS_4;

}

//=============================================================================
//=============================================================================
//=============================================================================
//-----------------Базовые функции-----------------------------------------------END }

// *******************************************************
// Супер навык - Власть крови - Blood Presence
// *******************************************************
public clRaceBlackMag::ultBlackLight(idUser, iTarget,vOldLocation[3], vNewLocation[3])
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
		set_task( 0.1, "_BM_ULT_BlinkStuck", TASK_BLINKSTUCK + idUser, parm, 5 );
	}
	
	fResetUltimateTimerDivider(idUser);

	return;
}

// Function will check to see if a user is stuck in a wall
public _BM_ULT_BlinkStuck( parm[] )
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
		
		Create_TE_TELEPORT( vOrigin );
	}	
	
	return;
}

// *******************************************************
// Скил 1 уровня - Black Strike - Темный Удар
// Скил 2 уровня - Black Shadow - Ужас
// *******************************************************
clRaceBlackMag::setSkillsOffensive(idAttacker,idVictim,iHitPlace)
{
	// Скил 1 уровня - Black Strike - Темный Удар
	new iSkillLevel = SM_GetSkillLevel(idAttacker,SKILL_BLACKSTRIKE );
	if( iSkillLevel > 0 && isDisabledSkillsOnMap(idAttacker,SKILL_BLACKSTRIKE) == false)
	{
		new Float:fBstrike = ArrayGetCell(arrBlackStrike,iSkillLevel-1);
		if ( random_float(fBlackMagSkill1MinPercent,fBlackMagSkill1MaxPercent) <= fBstrike )
		{
			new vTargetOrigin[3], vAttackerOrigin[3], vVictimOrigin[3]; 
			get_user_origin( idVictim, vTargetOrigin );

			Create_TE_EXPLOSION( vTargetOrigin, vTargetOrigin, arrIdSprites[SPR_BLACKFIRE], 20, 24, 4 );
			Create_TE_EXPLOSION( vTargetOrigin, vTargetOrigin, arrIdSprites[SPR_BURNFIRE], 30, 24, 4 );

			get_user_origin( idVictim, vVictimOrigin );
			get_user_origin( idAttacker, vAttackerOrigin );

			Create_TE_SPRITETRAIL( vAttackerOrigin, vVictimOrigin, arrIdSprites[SPR_BLACKSTRIKE], 50, 15, 2, 2, 6 );

			// Damage the user
			WC3_Damage( idVictim, idAttacker, iBlackStrikeDmg, CSW_BLACKPOWER, iHitPlace );
		}
	}


	// Скил 2 уровня - Black Shadow - Ужас
	iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_BLACKSHADOW );
	if ( iSkillLevel > 0 )
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_BLACKSHADOW) == true)
			return;

		new Float:fBshadow = ArrayGetCell(arrBlackShadow,iSkillLevel-1);
		if (random_float(fBlackMagSkill2MinPercent,fBlackMagSkill2MaxPercent) <= fBshadow && !SHARED_IsPlayerSlowed( idVictim ) )
		{		
			arrBoolData[idVictim][PB_STUNNED] = true;
			SHARED_SetSpeed( idVictim );

			new parm[5];

			set_task(SHADOW_HOLD_TIME, "SHARED_ResetMaxSpeed", TASK_RESETSPEED + idVictim );

			// Make the user glow!
			SHARED_Glow( idVictim, 225, 20, 147, 0 );

			Create_ScreenShake( idVictim, (10<<12), (3<<12), (6<<12) );	

			Create_ScreenFade( idVictim, 4, (1<<10), (1<<12), 148, 0, 211, 255 );

			set_task(0.5, "_BB_SuicideBlastCircles", TASK_BEAMCYLINDER + idVictim, parm, 5 );
		}
	}
   
 }

// Draw the blast circles
public _BB_SuicideBlastCircles( parm[5] )
{
	new vOrigin[3], vPosition[3];

	vOrigin[0] = parm[2];
	vOrigin[1] = parm[3];
	vOrigin[2] = parm[4] - 16;

	vPosition[0] = vOrigin[0];
	vPosition[1] = vOrigin[1];
	vPosition[2] = vOrigin[2] + 250;

	Create_TE_BEAMCYLINDER( vOrigin, vOrigin, vPosition, arrIdSprites[SPR_SHOCKWAVE], 0, 0, 6, 16, 0, 255, 20, 155, 255, 0 );

	vOrigin[2] = ( vOrigin[2] - 250 ) + ( 250 / 2 );

	Create_TE_BEAMCYLINDER( vOrigin, vOrigin, vPosition, arrIdSprites[SPR_SHOCKWAVE], 0, 0, 6, 16, 0, 255, 20, 155, 255, 0 );
}

// *******************************************************
// Скил 3 уровня - Black Power - Черная Сила
// *******************************************************
clRaceBlackMag::setSkillsDefensive(idAttacker,idVictim)
{
	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( idVictim, SKILL_BLACKPOWER );
	if (iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
	{
		if(isDisabledSkillsOnMap(idVictim,SKILL_BLACKPOWER) == true)
			return;

		new Float:fBpower = ArrayGetCell(arrBlackPower,iSkillLevel-1);
		if (random_float(fBlackMagSkill3MinPercent,fBlackMagSkill3MaxPercent) <= fBpower )
		{
			emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_IMPALE], 1.0, ATTN_NORM, 0, PITCH_NORM );
					
			new Float:vVelocity[3];
			entity_get_vector(idAttacker, EV_VEC_velocity, vVelocity);
			vVelocity[2] += 190.0;
			entity_set_vector(idAttacker, EV_VEC_velocity, vVelocity);

			entity_set_int(idAttacker, EV_INT_gaitsequence, 6);
		
		}
	}
}

public clRaceBlackMag::setAbilityBlast(idUser)
{
   if( g_friezadisk[idUser] > 0 && is_user_alive(idUser))
   {
    //Makes an array of origin in the (x,y,z) coordinate system.
    new origin[3]
	g_friezadisk[idUser] = g_friezadisk[idUser] - 1

    //Makes an array of velocity, specifically in the (x,y,z) coordinate system 
    new velocity[3] 

    new Float:fOrigin[3], Float:fVelocity[3]
    get_user_origin(idUser, origin, 1)
    new Float: minBound[3] = {-50.0, -50.0, 0.0}  //sets the minimum bound of entity
    new Float: maxBound[3] = {50.0, 50.0, 0.0}    //sets the maximum bound of entity
    IVecFVec(origin, fOrigin)

   
    new Float:viewing_angles[3]
    new distance_from_user = 70
    entity_get_vector(idUser, EV_VEC_angles, viewing_angles)
    fOrigin[0] += floatcos(viewing_angles[1], degrees) * distance_from_user
    fOrigin[1] += floatsin(viewing_angles[1], degrees) * distance_from_user
    fOrigin[2] += floatsin(-viewing_angles[0], degrees) * distance_from_user

    new NewEnt = create_entity("info_target")  //Makes an object 
    entity_set_string(NewEnt, EV_SZ_classname, szClassNameDisk); //sets the classname of the entity
 
    //This tells what the object will look like 
    entity_set_model(NewEnt, arrStrModels[MDL_FRIEZADISC]);

    //This will set the origin of the entity 
    entity_set_origin(NewEnt, fOrigin) 

    //This will set the movetype of the entity 
    entity_set_int(NewEnt,EV_INT_movetype, MOVETYPE_BOUNCE) 

	set_pev(NewEnt, pev_gravity, 0.01);

    //This makes the entity touchable
    entity_set_int(NewEnt, EV_INT_solid, SOLID_BBOX)

    //This will set the velocity of the entity 
    velocity_by_aim(idUser, 750, fVelocity) 
    FVecIVec(fVelocity, velocity)

    //Sets the size of the entity
    entity_set_size(NewEnt, minBound, maxBound)

    //Sets who the owner of the entity is
    entity_set_edict(NewEnt, EV_ENT_owner, idUser)

    //This will set the entity in motion 
    entity_set_vector(NewEnt, EV_VEC_velocity, fVelocity) 
   
    new lifetime = 5

    message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
    write_byte(22)       //TE_BEAMFOLLOW
    write_short(NewEnt)  //The entity to attach the sprite to
    write_short(arrIdSprites[SPR_MFLASH2_BLACK_MAG])  //sprite's model
    write_byte(lifetime)   //life in 0.1 seconds
    write_byte(50)   //width of sprite
    write_byte(255)  //red
    write_byte(0)    //green
    write_byte(255)  //blue
    write_byte(255)  //brightness
    message_end()
	
    return
  }
}

public touchBmDisk(entDisk, idWorldPlayer)
{ 
	if (!pev_valid(entDisk))
	{
		remove_entity( entDisk );
		return 0;
	}

	if(!is_user_connected(idWorldPlayer))
	{
		remove_entity( entDisk );
		return 0;
	}

    new aimvec[3], Float:fAimvec[3]; 
    entity_get_vector(idWorldPlayer, EV_VEC_origin, fAimvec);
    FVecIVec(fAimvec, aimvec); 


    if(idWorldPlayer == entity_get_edict(entDisk, EV_ENT_owner))
		return PLUGIN_HANDLED;
         
	special_effects(entDisk, 0, aimvec);

	//Если попадает в какое-нибудь место (стена,пол и т.д.)
	if(idWorldPlayer == 0) 
	{
		if (is_valid_ent(entDisk)) 
			remove_entity( entDisk );
		
		return PLUGIN_CONTINUE;
	}
	//Если попадает в игрока
	else if(is_user_connected(idWorldPlayer))
	{
		new idAttacker = entity_get_edict( entDisk, EV_ENT_owner );
//		new idVictim = entity_get_edict( entDisk, EV_ENT_enemy );
		//Если попадает в игрока и он не из твоей команды
		if(get_user_team(idWorldPlayer) != get_user_team(idAttacker))
		{
			special_effects(entDisk, idWorldPlayer, aimvec);

			if (is_valid_ent(entDisk)) 
				remove_entity( entDisk );


		}
		//Если попадает в игрока и он из твоей команды
		else 
		{
			special_effects(entDisk, idWorldPlayer, aimvec);

			if (is_valid_ent(entDisk)) 
				remove_entity( entDisk );
		}
	} 
	//Если игрок запустил стрелу и вышел с сервера
	else
	{
		special_effects(entDisk, idWorldPlayer, aimvec);

		if (is_valid_ent(entDisk)) 
			remove_entity( entDisk );
		
	}

	return PLUGIN_CONTINUE;

} 
//----------------------------------------------------------------------------------------- 
public special_effects(pToucher, pTouched, aimvec[3])
{
	new Float:fVelocity[3]
	new velocity[3]
	entity_get_vector(pToucher, EV_VEC_velocity, fVelocity)
	FVecIVec(fVelocity, velocity)

	new killer = entity_get_edict(pToucher, EV_ENT_owner)
	new victim = pTouched


	if(is_user_alive(pTouched) && get_user_team( killer ) != get_user_team( victim ) )
	{
		message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
		write_byte(101)  //BLOODSTREAM
		write_coord(aimvec[0])
		write_coord(aimvec[1])
		write_coord(aimvec[2])
		write_coord(velocity[0])
		write_coord(velocity[1])
		write_coord(velocity[2])
		write_byte(95)
		write_byte(100)
		message_end()

		new victim = pTouched
		WC3_Damage(victim, killer, iDiskDmg, CSW_LIGHTNING, -1 )
	}
	
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
	write_byte(9)  //SPARKS
	write_coord(aimvec[0])
	write_coord(aimvec[1])
	write_coord(aimvec[2])
	message_end()

}

public decay_effects(NewEnt, origin[3])  //removes the entity plus adds a decaying effect
{
	if(is_valid_ent(NewEnt)){
		remove_entity(NewEnt)
		message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
		write_byte(14) //IMPLOSION
		write_coord(origin[0])
		write_coord(origin[1])
		write_coord(origin[2])
		write_byte(50)
		write_byte(10)
		write_byte(10)
		message_end()
	}
} 