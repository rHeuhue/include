

public sm4_4_5_DeathCoil(idAttacker,idVictim)//Добавлена в events.inl
{

	if(get_user_team( idVictim ) != get_user_team( idAttacker ) )
	{
		InitDeathCoil( idAttacker, idVictim,eDcAtack);
		ITEM_RemoveCharge(idAttacker, ITEM_DEATHCOIL );
	}

	return PLUGIN_HANDLED;
}

/* - Death Coil ------------------------------------------------- */
public InitDeathCoil(idAttacker,idVictim,iTypeDC)
{
	emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_DEATHCOIL_MISSILE], 1.0, ATTN_NORM, 0, PITCH_NORM );

	//Создание модели черепа
	new Float:fOrigin[3];
	entity_get_vector( idAttacker, EV_VEC_origin, fOrigin );

	//new entSkull = WC3_ENTITY_create( "DEATH_COIL", arrStrModels[MDL_BSKULL], fOrigin, MOVETYPE_NOCLIP, SOLID_TRIGGER, DEATHCOIL_DURATION );
	new entSkull = WC3_ENTITY_create( "DEATH_COIL", arrStrModels[MDL_BSKULL], fOrigin, MOVETYPE_BOUNCE, SOLID_BBOX, DEATHCOIL_DURATION );

	entity_set_edict(entSkull, EV_ENT_owner, idAttacker );
	entity_set_edict(entSkull, EV_ENT_enemy, idVictim );
	entity_set_int(entSkull,EV_INT_iuser1,iTypeDC);

	switch(iTypeDC)
	{
		case eDcAtack:
		{
			set_entity_rendering(entSkull, kRenderFxGlowShell, DEATHCOIL_SHELL_RGB[GLOW_R], DEATHCOIL_SHELL_RGB[GLOW_G], DEATHCOIL_SHELL_RGB[GLOW_B], kRenderNormal, 48 );
			Create_TE_BEAMFOLLOW(entSkull, arrIdSprites[SPR_TRAIL], 5, 8, DEATHCOIL_TRAIL_RGB[GLOW_R], DEATHCOIL_TRAIL_RGB[GLOW_G], DEATHCOIL_TRAIL_RGB[GLOW_B], 160 );
		}
		case eDcHP:
		{
			set_entity_rendering(entSkull, kRenderFxGlowShell, DEATHCOIL_SHELL_HP_RGB[GLOW_R], DEATHCOIL_SHELL_HP_RGB[GLOW_G], DEATHCOIL_SHELL_HP_RGB[GLOW_B], kRenderNormal, 48 );
			Create_TE_BEAMFOLLOW(entSkull, arrIdSprites[SPR_TRAIL], 5, 8, DEATHCOIL_TRAIL_HP_RGB[GLOW_R], DEATHCOIL_TRAIL_HP_RGB[GLOW_G], DEATHCOIL_TRAIL_HP_RGB[GLOW_B], 160 );
		}
		case eDcArmor:
		{
			set_entity_rendering(entSkull, kRenderFxGlowShell, DEATHCOIL_SHELL_ARMOR_RGB[GLOW_R], DEATHCOIL_SHELL_ARMOR_RGB[GLOW_G], DEATHCOIL_SHELL_ARMOR_RGB[GLOW_B], kRenderNormal, 48 );
			Create_TE_BEAMFOLLOW(entSkull, arrIdSprites[SPR_TRAIL], 5, 8, DEATHCOIL_TRAIL_ARMOR_RGB[GLOW_R], DEATHCOIL_TRAIL_ARMOR_RGB[GLOW_G], DEATHCOIL_TRAIL_ARMOR_RGB[GLOW_B], 160 );
		}
	}

	// Seek idVictim
	new arg_write[1];
	arg_write[0] = entSkull;

	fDeathCoilSeek( arg_write );

	return PLUGIN_HANDLED;
}

public fDeathCoilSeek( arg_read[1] )
{

	new skull = arg_read[0];

	if ( !WC3_is_valid_ent( skull ) )
		return PLUGIN_HANDLED;

	new idVictim = entity_get_edict( skull, EV_ENT_enemy );

	if ( !is_user_alive( idVictim ) )
		return PLUGIN_HANDLED;

	// Project skull towards idVictim
	set_velocity_to_ent( skull, idVictim, DEATHCOIL_VELOCITY );

	// Repeat until idVictim is hit
	new task = TASK_TEMPENTITY + skull;
	set_task( 0.1, "fDeathCoilSeek", task, arg_read, 1 );

	return PLUGIN_HANDLED;
}

//Поражение игрока
static fDeathCoilDamage(idAttacker,idVictim,iTypeDC) 
{

	// Play sound
	emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_DEATHCOIL], 1.0, ATTN_NORM, 0, PITCH_NORM );

	// Generate effects
	fDeathCoilEffects(idVictim,iTypeDC);

	// Unset velocity
	new Float:fVelocity[3];
	entity_get_vector(idVictim, EV_VEC_velocity, fVelocity );

	fVelocity[0] = 0.0;
	fVelocity[1] = 0.0;

	// Apply damage
	WC3_Damage(idVictim,idAttacker, DEATHCOIL_DAMAGE, CSW_DEATHCOIL, -1 );

	return PLUGIN_HANDLED;
}


//Прибавление здоровья
public fDeathCoilHP(idVictim,idAttacker,iTypeDC)
{
	//Рыцарь смерти
	if(bIsUserRace(idVictim,RACE_DEATH_KNIGHT) ||
	   bIsUserRace(idVictim,RACE_CHAMELEON)
	  )
	{

		// Play sound
		emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_DEATHCOIL], 1.0, ATTN_NORM, 0, PITCH_NORM );

		// Generate effects
		fDeathCoilEffects(idAttacker,iTypeDC);

		// Unset velocity
		new Float:fVelocity[3];
		entity_get_vector(idAttacker, EV_VEC_velocity, fVelocity );

		fVelocity[0] = 0.0;
		fVelocity[1] = 0.0;
	
		new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_DEATH_KNIGHT_DEATH_COIL);
		
		if(iSkillLevel > 0)
		{
			new iMaxHealth = clHP:getRaceMaxHealth(idVictim);
			new iCurrentHealth =  clHP:getUserHealth(idVictim);

			new Float:fDeathcoil = ArrayGetCell(arrDeathCoil,iSkillLevel-1);
			new iBonusHp = floatround(clHP:getUserHealth(idAttacker) * fDeathcoil);
				

			#if MODE_LOG
					#if LOG_SKILL_DEATH_COIL > 0
						clLog:logRaceDeathKnight2(fDeathcoil,iBonusHp);
					#endif
				#endif


			if((iCurrentHealth + iBonusHp) > iMaxHealth)
				clHP:setUserHealth(idVictim,iMaxHealth);
			else
				clHP:setUserHealth(idVictim,iCurrentHealth + iBonusHp);

			
		}
	}

	return PLUGIN_HANDLED;
}

//Прибавление брони
public fDeathCoilArmor(idVictim,idAttacker,iTypeDC)
{
	//Рыцарь смерти
	if(bIsUserRace(idVictim,RACE_DEATH_KNIGHT) ||
	   bIsUserRace(idVictim,RACE_CHAMELEON)
	  )
	{
		// Play sound
		emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_DEATHCOIL], 1.0, ATTN_NORM, 0, PITCH_NORM );

		// Generate effects
		fDeathCoilEffects(idAttacker,iTypeDC);

		// Unset velocity
		new Float:fVelocity[3];
		entity_get_vector(idAttacker, EV_VEC_velocity, fVelocity );

		fVelocity[0] = 0.0;
		fVelocity[1] = 0.0;

	
		new iSkillLevel = SM_GetSkillLevel(idVictim, SKILL_DEATH_KNIGHT_DEATH_COIL);
		
		if(iSkillLevel > 0)
		{		
			new Float:fDeathcoil = ArrayGetCell(arrDeathCoil,iSkillLevel-1);
		
			new iMaxArmor = clAr:getRaceMaxArmor(idVictim);
			new CsArmorType:tArmor;
			new iCurrentArmor =  clAr:getUserArmor(idVictim,tArmor);
			new iBonusArmor =  floatround((iCurrentArmor == 0) ? (fDeathcoil) : (iCurrentArmor * fDeathcoil));
			
			if((iCurrentArmor + iBonusArmor) > iMaxArmor)
				clAr:setUserArmor(idVictim,iMaxArmor);
			else
				clAr:setUserArmor(idVictim,iCurrentArmor + iBonusArmor);

		}
	}

	return PLUGIN_HANDLED;
}


static fDeathCoilEffects(idVictim,iTypeDC)
{
	new Origin[3];
	get_user_origin( idVictim, Origin );

	switch(iTypeDC)
	{
		case eDcAtack:
		{
			Create_ScreenFade( idVictim, (1<<10), (1<<10), FADE_OUT, DEATHCOIL_TRAIL_RGB[GLOW_R], DEATHCOIL_TRAIL_RGB[GLOW_G], DEATHCOIL_TRAIL_RGB[GLOW_B], 160 );
			Create_TE_ELIGHT(idVictim, Origin, 100, DEATHCOIL_TRAIL_RGB[GLOW_R], DEATHCOIL_TRAIL_RGB[GLOW_G],DEATHCOIL_TRAIL_RGB[GLOW_B], 10, 0 );
		}
		case eDcHP:
		{

			Create_ScreenFade( idVictim, (1<<10), (1<<10), FADE_OUT, DEATHCOIL_TRAIL_HP_RGB[GLOW_R], DEATHCOIL_TRAIL_HP_RGB[GLOW_G], DEATHCOIL_TRAIL_HP_RGB[GLOW_B], 160 );
			Create_TE_ELIGHT(idVictim, Origin, 100, DEATHCOIL_TRAIL_HP_RGB[GLOW_R], DEATHCOIL_TRAIL_HP_RGB[GLOW_G],DEATHCOIL_TRAIL_HP_RGB[GLOW_B], 10, 0 );
		}
		case eDcArmor:
		{

			Create_ScreenFade( idVictim, (1<<10), (1<<10), FADE_OUT, DEATHCOIL_TRAIL_ARMOR_RGB[GLOW_R], DEATHCOIL_TRAIL_ARMOR_RGB[GLOW_G], DEATHCOIL_TRAIL_ARMOR_RGB[GLOW_B], 160 );
			Create_TE_ELIGHT(idVictim, Origin, 100, DEATHCOIL_TRAIL_ARMOR_RGB[GLOW_R], DEATHCOIL_TRAIL_ARMOR_RGB[GLOW_G],DEATHCOIL_TRAIL_ARMOR_RGB[GLOW_B], 10, 0 );
		}
	}

	Create_TE_EXPLOSION( Origin, Origin, arrIdSprites[SPR_DEATHCOIL], 20, 24, 4 );


	return PLUGIN_HANDLED;
}


static fDeathCoilRemove( skull ) 
{
	new task = TASK_TEMPENTITY + skull;
	remove_task( task, 0 );

	if (is_valid_ent(skull)) 
		remove_entity( skull );

	return PLUGIN_HANDLED;
}


public touchDeathCoil(entSkull, idWorldPlayer ) 
{

	//Если попадает в какое-нибудь место (стена,пол и т.д.)
	if(idWorldPlayer == 0) 
	{
		fCreateExplodeIceArrow(entSkull);
		fDeathCoilRemove( entSkull );
		
		return PLUGIN_CONTINUE;
	}
	//Если попадает в игрока
	else if(is_user_connected(idWorldPlayer))
	{
		new idAttacker = entity_get_edict(entSkull, EV_ENT_owner );
		new idVictim = entity_get_edict(entSkull, EV_ENT_enemy );

		new iTypeDC = entity_get_int(entSkull, EV_INT_iuser1 ) 

		//Если попадает в игрока и он не из твоей команды
		if(get_user_team(idWorldPlayer) != get_user_team(idAttacker))
		{
			switch(iTypeDC)
			{
				case eDcAtack:
				{
					fDeathCoilDamage(idAttacker,idVictim,iTypeDC);
				}
				case eDcHP:
				{
					fDeathCoilHP(idAttacker,idVictim,iTypeDC);
				}
				case eDcArmor:
				{

					fDeathCoilArmor(idAttacker,idVictim,iTypeDC );
				}
			}

			fDeathCoilRemove( entSkull );

		}
		//Если попадает в игрока и он из твоей команды
		else 
		{
		}
	} 
	//Если игрок запустил стрелу и вышел с сервера
	else
	{
		fCreateExplodeIceArrow(entSkull);
		fDeathCoilRemove( entSkull );
		
	}

	return PLUGIN_CONTINUE;
}

public WC3_is_valid_ent( ent ) 
{
	// Don't want to look up info for an invalid ent
	if ( !is_valid_ent( ent ) )
		return ( false );

	new szWar3Entities[][64] = {"DEATH_COIL", "ROOT_PLANT", "IMPALE_CLAW", "SLEEP_Z", "REJUV_FLARE", "FLAME_STRIKE", "HEAL_EFFECT" };

	new szClassName[64];
	entity_get_string( ent, EV_SZ_classname, szClassName, 63 );

	// See if this class is in our list
	for ( new i = 0; i < sizeof( szWar3Entities ); i++ )
	{
		if ( equal( szClassName, szWar3Entities[i] ) )
			return ( true );
	}

	return ( false );
}


public WC3_ENTITY_create( szClassName[32], szModel[64], Float:fOrigin[3], iMoveType, iSolidType, Float:fLife )
{

	new ent = create_entity( "info_target" );
	entity_set_string( ent, EV_SZ_classname, szClassName );

	entity_set_model( ent, szModel );
	entity_set_origin( ent, fOrigin );

	entity_set_int( ent, EV_INT_movetype, iMoveType );
	entity_set_int( ent, EV_INT_solid, iSolidType );

	if ( fLife )
	{
		new arg_write[1];
		arg_write[0] = ent;

		new task = TASK_TEMPENTITY + ent;

		set_task( fLife, "WC3_ENTITY_remove", task, arg_write, 1 );
	}

	return ( ent );
}


public WC3_ENTITY_remove( arg_read[1] ) 
{

	new ent = arg_read[0];

	if ( WC3_is_valid_ent( ent ) )
		remove_entity( ent );

	return PLUGIN_HANDLED;
}