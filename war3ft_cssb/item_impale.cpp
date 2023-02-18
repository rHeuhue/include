

public sm4_4_6_Impale( idAttacker, idVictim )//Добавлена в events.inl
{

	if(get_user_team( idVictim ) != get_user_team( idAttacker ) )
	{
		InitImpale( idAttacker, idVictim );
		ITEM_RemoveCharge(idAttacker, ITEM_IMPALE );
	}

	return PLUGIN_HANDLED;
}

/* - Impale ------------------------------------------------- */
static InitImpale( idAttacker, idVictim )
{
	emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_IMPALE], 1.0, ATTN_NORM, 0, PITCH_NORM );

	// Raise claw
	new Float:fOrigin[3], Origin[3];
	entity_get_vector( idVictim, EV_VEC_origin, fOrigin );

	fOrigin[2] += 180.0;
	new claw = WC3_ENTITY_create( "IMPALE_CLAW", arrStrModels[MDL_TENTACLE], fOrigin, MOVETYPE_TOSS, SOLID_NOT, 1.5 );

	new Float:fVelocity[3] = { 0.0, 0.0, 500.0 };
	entity_set_vector( claw, EV_VEC_velocity, fVelocity );
	entity_set_float( claw, EV_FL_gravity, 1.5 );

	set_entity_rendering( claw, kRenderFxGlowShell, 128, 96, 160, kRenderTransTexture, 32 );

	// Launch into air
	new Velocity[3];
	get_entity_velocity( idVictim, Velocity );

	Velocity[2] = IMPALE_VELOCITY;
	set_entity_velocity( idVictim, Velocity );

	// Beam trail
	Create_TE_BEAMFOLLOW(idVictim, arrIdSprites[SPR_TRAIL], 5, 3, 160, 0, 48, 128 );

	// Blood sprites
	for ( new i = 0; i < 2; i++ )
	{
		get_user_origin( idVictim, Origin );

		for ( new j = 0; j < 5; j++ )
		{
			Origin[0] += random_num( -100,100 ) * j;
			Origin[1] += random_num( -100,100 ) * j;
			Origin[2] += random_num( 0,100 ) * j;

			Create_TE_BLOODSPRITE(Origin, arrIdSprites[SPR_BLOODSPRAY],arrIdSprites[SPR_BLOODDROP], 248, 15 );
		}
	}

	// Blood decals
	for ( new i = 0; i < 5; i++ )
	{
		static const BLOOD_SMALL[7] = {190,191,192,193,194,195,197};

		get_user_origin( idVictim, Origin );

		Origin[0] += random_num( -100,100 );
		Origin[1] += random_num( -100,100 );
		Origin[2] -= 36;

		Create_TE_WORLDDECAL(Origin, BLOOD_SMALL[random_num( 0,6 )] );
	}

	// Remove armor
	if (clAr:getArmorNum(idVictim))
	{
		new iNewArmor = clAr:getArmorNum(idVictim) - IMPALE_ARMORDAMAGE;

		if (iNewArmor < 0)
			iNewArmor = 0;

		clAr:setUserArmor(idVictim, iNewArmor);
	}

	// Remove health
	WC3_Damage(idVictim,idAttacker,IMPALE_DAMAGE, CSW_IMPALE, -1 );

	if ( is_user_alive( idVictim ) )
	{
		// Screen Fade
		Create_ScreenFade( idVictim, (1<<10), (1<<10), FADE_OUT, 160, 0, 48, 160 );

		new arg_write[3];
		arg_write[0] = idVictim;
		arg_write[1] = Origin[2];

		g_PlayerImpaled[idVictim] = idAttacker;

		new task = TASK_IMPALE + idVictim;
		set_task( 0.1, "fImpaleThink", task, arg_write, 3 );
	}

	return PLUGIN_HANDLED;

}


public fImpaleThink( arg_read[3] ) 
{

	new idVictim = arg_read[0];
	new idAttacker = g_PlayerImpaled[idVictim];

	new OldOrigin = arg_read[1];
	new OldVelocity = arg_read[2];

	new Velocity[3];
	get_entity_velocity( idVictim, Velocity );

	// Checks player height on descent, assumes collision if < IMPALE_MINDISTANCE
	if ( OldVelocity >= 0 && Velocity[2] <= 0 )
	{
		new Origin[3];
		get_user_origin( idVictim, Origin );

		new iDistance = Origin[2] - OldOrigin;

		if ( iDistance < IMPALE_MINDISTANCE )
		{
			emit_sound(idVictim,CHAN_STATIC, arrStrSounds[SOUND_IMPALE], 0.25, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);


			// Blood streams
			Origin[2] += 10;

			for ( new i = 0; i < 2; i++ )
			{
				new Vector[3];
				Vector[0] = random_num( 20,300 );
				Vector[1] = random_num( 20,300 );
				Vector[2] = 0;

				Create_TE_BLOODSTREAM(Origin, Vector, 70, random_num( 100,200 ) );
			}

			// Apply damage
			WC3_Damage(idVictim,idAttacker, IMPALE_COLLISIONDAMAGE, CSW_IMPALE, -1 );

			// Screen fade
			if ( is_user_alive( idVictim ) )
				Create_ScreenFade( idVictim, (1<<10), (1<<10), FADE_MODULATE_OUT, 0, 0, 0, 160 );
		}
	}

	if ( !( get_entity_flags( idVictim ) & FL_ONGROUND ) && g_PlayerImpaled[idVictim] )
	{
		arg_read[2] = Velocity[2];

		new task = TASK_IMPALE + idVictim;
		set_task( 0.1, "fImpaleThink", task, arg_read, 3 );
	}

	else
	{
		fImpaleRemove( idVictim );
	}

	return PLUGIN_HANDLED;
}


public fImpaleRemove( id ) 
{

	new task = TASK_IMPALE + id;
	remove_task( task, 0 );

	g_PlayerImpaled[id] = 0;
	Remove_TE_BEAMFOLLOW(id );
}