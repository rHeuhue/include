// Function is called ONCE at the start of a new round BEFORE user's spawn
public EVENT_NewRound()
{
	if (!WC3_Check())
		return;

	//Очистка координат трупов
	ArrayClear(arrOriginCorpse_X);
	ArrayClear(arrOriginCorpse_Y);
	ArrayClear(arrOriginCorpse_Z);

	//Счетчик раундов
	iRoundCount += 1;

	// An additional delay is offset at round start since SVC_BAD is more likely to be triggered there
	fModelChangeTargetTime = get_gametime() + ROUNDSTART_DELAY;

	//Удаление всех брошеных вещей
	fRemoveAllItems();

	//Активация двойного опыта
	fActiveDoubleXP();

	// Reset the global ultimate delay
	new iTimeUltDelay = ArrayGetCell(arrIntUltimateTimer,0);
	g_iUltimateDelay = iTimeUltDelay;

	// User's have not spawned yet, so lets do some pre-spawn things
	new players[32], numplayers, i;
	get_players( players, numplayers );
	for ( i = 0; i < numplayers; i++ )
	{
		new idUser = players[i];
		
		ITEM_LimitOneRound(idUser);

		clVIP:fLimitItemVipOneRound(idUser);

		WC3_BeforeSpawn(idUser);

		//Для shopmenu4
		//Остановка работы предмета Спокойствие
		sm4_4_9_fRemoveSpellCasting( idUser );
		remove_task( TASK_TRANQUILITY + idUser );

		//Разморозка игрока
		sm4_4_2_UnfrozenPlayer(idUser);

		if (task_exists(clRaceDeathKnight::taskID_BLOOD_PRESENCE + idUser))
			remove_task(clRaceDeathKnight::taskID_BLOOD_PRESENCE + idUser);

		clRaceDeathKnight::bIsDamageBP[idUser] = false;
		clRaceDeathKnight::bIsUnDamageBP[idUser] = false;

		clRacePriest::fStopUlt(idUser);
		remove_task( TASK_POISON + idUser );


		if(bIsUserRace(idUser,RACE_ROGUE))
		{
			if (task_exists(clRogue::tID_VANISH + idUser))
			{
				remove_task(clRogue::tID_VANISH + idUser );
				clRogue::taskResetVanish(clRogue::tID_VANISH + idUser);
			}

			if (task_exists(clRogue::tID_CP_SPEED + idUser))
			{
				remove_task(clRogue::tID_CP_SPEED + idUser );
				clRogue::taskResetCP_Speed(clRogue::tID_CP_SPEED + idUser);
			}
		}

		if(bIsUserRace(idUser,RACE_BLOODSEEKER))
		{
			if (task_exists(clBloodseeker::tID_BLOODRAGE + idUser))
			{
				remove_task(clBloodseeker::tID_BLOODRAGE + idUser );
				clBloodseeker::taskResetBloodRage(clBloodseeker::tID_BLOODRAGE + idUser);
			}
		}

		//Обновление модели (сброс на новую)
		if (task_exists(idUser + TASK_MODELCHANGE))
		{
			remove_task(idUser + TASK_MODELCHANGE);
			fUpdateUserModel(idUser + TASK_MODELCHANGE);
		}

		//Сброс модели если игрок скелет
		if(sm4_IsPlayerSkeleton(idUser) == true)
			cssbResetPlayerModel(idUser);
				
		
		if (task_exists(idUser + clWarlock::tID_FLAMING_FIRST))
			remove_task(idUser + clWarlock::tID_FLAMING_FIRST);

		if (task_exists(idUser + clWarlock::tID_PERM_IMMOLATION))
			remove_task(idUser + clWarlock::tID_PERM_IMMOLATION);

	}//for

	//Удаление сущностей с карты в новом раунде
	uDeleteAllEntClassnameMap(HEALING_WARD_CLASSNAME);
	uDeleteAllEntClassnameMap(SHRAPNEL_SNIPER_CLASSNAME);
	uDeleteAllEntClassnameMap(STATIC_STORM_DISRUPTOR_CLASSNAME);
	uDeleteAllEntClassnameMap(PLASMA_FIELD_RAZOR_CLASSNAME);
	uDeleteAllEntClassnameMap("Wild_Mushroom");
	uDeleteAllEntClassnameMap("AstralStorm");
	uDeleteAllEntClassnameMap(PERM_IMMOL_WARLOCK_CLASSNAME);
	uDeleteAllEntClassnameMap(NECROMASTERY_SHADOW_FIEND_CLASSNAME);
	uDeleteAllEntClassnameMap(BALL_CLASSNAME);
	uDeleteAllEntClassnameMap(BEAM_CLASSNAME);
	

	//shopmenu4 - Обнуление всех массивов Книга мертвых
	sm4_fRemoveAllArrayBookDead();


	// Reset which spawn points are reserved....
	_SHARED_SpawnReset();

	// If someone restarted the game, then lets reset war3
	if ( g_GameRestarting )
	{
		WC3_ResetGame();
	}
	
	// Randomize Chameleon if we need to
	CHAM_Randomize();

	// We need to determine when the buytime is up
	if ( get_pcvar_num( CVAR_wc3_buy_time ) )
	{
		// Remove our buytime task if it exists (from a previous round)
		( task_exists( TASK_BUYTIME ) ) ? remove_task( TASK_BUYTIME ) : 0;

		g_buyTime = true;

		set_task( get_cvar_float("mp_buytime") * 60.0, "_CS_BuyTimeOver", TASK_BUYTIME );
	}

	sm4_4_2_evNewRound();


	g_freezeTime = true;

	g_EndRound = false;

}



// Forwards from the CSX module
public grenade_throw( idUser, greindex, wId )
{
	
	if ( !WC3_Check() )
	{
		return;
	}
	
	// If user isn't alive do nothing!
	if ( !is_user_alive( idUser ) )
	{
		return;
	}

	//Для talisman +
	// User has gloves!  Do we need to give them another grenade?
	if ( ITEM_Has( idUser, ITEM_GLOVES ) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser] == TALISMAN_ITEM_GLOVES))
	{
		ITEM_Glove_Begin( idUser );
	}

	//Для shopmenu4
	sm4_ITEM_IceBlock_Begin( idUser );
	
	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( idUser, SKILL_CRITICALGRENADE );

	// Make sure the user has the skill and we actually have a grenade index
	if ( greindex && iSkillLevel > 0 )
	{
		if(isDisabledSkillsOnMap(idUser,SKILL_CRITICALGRENADE) == true)
			return;

		// Then Critical Grenades are allowed
		if ( OR_CriticalGrenadeAllowed( idUser ) )
		{

			// Then draw it!
			if ( SHARED_IsGrenade( wId ) )
			{
				new iWidth = 3 * iSkillLevel;
				
				Create_TE_BEAMFOLLOW(greindex, arrIdSprites[SPR_TRAIL], 20, iWidth, 255, 32, 32, 196 );
			}
		}
	}
	return;
}

// HamSandwich implementation
public EVENT_TakeDamage(idVictim, iWeapon, idAttacker, Float:f_Damage, damagetype )
{

	static szWeaponClassName[32];
	pev ( iWeapon, pev_classname, szWeaponClassName, charsmax ( szWeaponClassName ) );

	new s_PlayerName[32], s_PlayerName2[32];

	get_user_name(idVictim, s_PlayerName, 31 );
	get_user_name(idAttacker, s_PlayerName2, 31 );
      
//	client_print(0,print_chat,"A %d | V %d",idAttacker,idVictim);

	if(SHARED_ValidPlayer(idAttacker) && is_user_alive(idVictim))
	{
		if (get_user_team(idAttacker) == get_user_team(idVictim) && arrBoolData[idVictim][PB_KINETIC_FIELD] == false)
			return HAM_IGNORED;
		
		//ITEM_GRENADE_PROTECTION - Grenade Protection
		if (ITEM_Has(idVictim, ITEM_GRENADE_PROTECTION ) > ITEM_NONE || 
			fWorkTalismanPassive(idVictim, arrTalismanActive[idVictim]) == TALISMAN_ITEM_GRENADE_PROTECTION ||
			arrBoolData[idVictim][PB_KINETIC_FIELD] == true ||
			clVIP:isAccesItemVip(idVictim,ITEM_GRENADE_PROTECTION) == true
		   )
		{
			if(equali(szWeaponClassName,"grenade") || equali(szWeaponClassName,"pumpkin_bomb") || equali(szWeaponClassName,"cluster_bomb"))
			{
				//client_print(0,print_chat,"szWeaponClassName %s",szWeaponClassName);

				ITEM_RemoveCharge(idVictim, ITEM_GRENADE_PROTECTION );
				return HAM_SUPERCEDE;
			}
		}

		//Рыцарь смерти
		if(bIsUserRace(idVictim,RACE_DEATH_KNIGHT))
		{
			f_Damage = clRaceDeathKnight::skillUnbreakableArmor(idAttacker,idVictim,f_Damage);
			SetHamParamFloat(4, f_Damage);
			
			if(f_Damage > 0.0)
				clRaceDeathKnight::bIsDamageBP[idVictim] = true;
		
			//client_print(idVictim,print_chat,"Damage: %.1f idAttacker:%d",f_Damage,idAttacker);
		}

		//Блэйд
		if(bIsUserRace(idVictim,RACE_RAZOR))
		{
			if(clRazor::skillStaticLink(idVictim) == true)
				SetHamParamFloat(4, 0.0);
		}
		
	}


//	client_print(idAttacker,print_chat,"DO --- Damage: %.1f health:%d",f_Damage,clHP:getUserHealth(idVictim))
//    client_print(idAttacker,print_chat,"Damage: %.1f health:%d",f_Damage,clHP:getUserHealth(idVictim))
	
/*
	if(!is_user_bot(idAttacker) || !is_user_bot(idVictim))
	{
		client_print(idAttacker,print_chat,"A wpn: %s",szWpnName);
		client_print(idVictim,print_chat,"V wpn: %s",szWpnName);
	}
	client_print( idAttacker, print_chat, "Damage: %f0.0, Victim: %d, Inflictor: %d (%s)", iDamage, idVictim, inflictor, s_Classname );
	client_print( idVictim, print_chat, "Damage: %f0.0, idAttacker: %d, Inflictor: %d (%s)", iDamage, idAttacker, inflictor, s_Classname );

	server_print( "Attacker: %d, Damage: %f0.0, Victim: %d, Inflictor: %d (%s)", idAttacker, iDamage, idVictim, inflictor, s_Classname );
*/

	return HAM_IGNORED;
}

public client_damage(idAttacker, idVictim, iDamage, iWeapon, iHitPlace, TA )
{

	if (!WC3_Check())
		return;
	
	// If they damage themself we don't care now do we ?
	if (idVictim == idAttacker )
		return;
	
	//Death's Touch
	if (ITEM_Has(idAttacker, ITEM_DEATH_TOUCH ) > ITEM_NONE && arrDeathTouch[idAttacker])
	{
		new parm[5], vOrigin[3];
		get_user_origin(idVictim, vOrigin);

		parm[0] = idVictim;
		parm[1] = 6;
		parm[2] = vOrigin[0];
		parm[3] = vOrigin[1];
		parm[4] = vOrigin[2];

		emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_DEATH_TOUCH], 1.0, ATTN_NORM, 0, PITCH_NORM );
		
		set_task(0.2, "fDrawDeathTouchExplode", TASK_DEATH_TOUCH + idVictim, parm, 5 );
				
		WC3_Kill( idVictim, idAttacker, iWeapon, 0 );	
		ITEM_RemoveID(idAttacker, ITEM_DEATH_TOUCH );

	}


	//Для talisman +
	// Frost Armor
	if (ITEM_Has(idVictim, ITEM_FROST_ARMOR ) > ITEM_NONE || fWorkTalismanPassive(idVictim, arrTalismanActive[idVictim]) == TALISMAN_ITEM_FROST_ARMOR)
	{
		WC3_Damage(idAttacker,idVictim,FROST_ARMOR_DAMAGE, iWeapon,0);
		SHARED_GlowShell(idVictim,0,139,139,0.2);
	}

	g_iDamageDealt[idAttacker][idVictim] += iDamage;


	// Bot should "auto" cast his/her ultimate on random
	if ( SHARED_ValidPlayer( idAttacker ) && is_user_bot( idAttacker ) && random_num( 0, 100 ) <= ( BOT_CAST_ULT_CHANCE * 100 ) )
	{
		// Check for an actual ultimate is done in this function, why do it twice?
		cmd_Ultimate(idAttacker);
	}
	

	// We need to make sure that we have a valid attacker and the user isn't hexed
	if (SHARED_ValidPlayer( idAttacker ) && !arrBoolData[idAttacker][PB_HEXED] )
	{
		//Для talisman +
		//Mirror Shield
		if (ITEM_Has(idVictim, ITEM_MIRROR_SHIELD ) > ITEM_NONE || fWorkTalismanPassive(idVictim, arrTalismanActive[idVictim]) == TALISMAN_ITEM_MIRROR_SHIELD)
		{
			iDamage = iDamage - floatround(iDamage * OFFENSIVE_MIRROR_SHIELD);
			SHARED_GlowShell(idVictim,255,105,180,0.2);
		}

		//Наступательные скилы
		UD_SkillsOffensive( idAttacker,idVictim,iDamage );
		HU_SkillsOffensive( idAttacker, idVictim );
		OR_SkillsOffensive( idAttacker, idVictim, iWeapon, iDamage, iHitPlace );
		NE_SkillsOffensive( idAttacker, idVictim, iWeapon, iDamage, iHitPlace );
		BM_SkillsOffensive( idAttacker, idVictim, iDamage );
		SH_SkillsOffensive( idAttacker, idVictim );
		WA_SkillsOffensive( idAttacker, idVictim, iHitPlace );
		CL_SkillsOffensive( idAttacker, idVictim, iHitPlace );
		FM_SkillsOffensive( idAttacker, idVictim, iHitPlace );
		FM_SkillsOffensive_Ice_Arrow( idAttacker, idVictim);
		FM_SkillsOffensive_Cone_Cold( idAttacker, idVictim);
		clRaceBlackMag::setSkillsOffensive(idAttacker,idVictim,iHitPlace );
		AC_SkillsOffensive( idAttacker, idVictim, iHitPlace );
		clSniper::skillHeadshot(idAttacker,idVictim,iHitPlace);
		clDisruptor::skillThunderStrike(idAttacker,idVictim);
		clWarlock::skillFlamingFists(idVictim,idAttacker);	
		clShadowFiend::skillCryHeart(idVictim,idAttacker);

		if(bIsUserRace(idAttacker,RACE_DRUID))
		{
			clDruid::skillMangle(idAttacker,idVictim,iWeapon,iHitPlace);
			clDruid::addWMStrikeExplode(idAttacker,idVictim);
			clDruid::addWMStrikeEntangle(idAttacker,idVictim);
		}

		if(bIsUserRace(idAttacker,RACE_ROGUE))
		{
			clRogue::skillSinisterStrike(idAttacker,idVictim,iWeapon,SKILL_ROGUE_1);
			clRogue::skillCripplingPoison(idAttacker,idVictim,SKILL_ROGUE_3);
		}

		if(bIsUserRace(idAttacker,RACE_BLOODSEEKER))
		{
			clBloodseeker::skillBloodRage(idAttacker,idVictim,SKILL_BLOODSEEKER_1);
			clBloodseeker::skillBloodRite(idAttacker,idVictim,SKILL_BLOODSEEKER_3);
			clBloodseeker::skillVendetta(idAttacker,idVictim,iWeapon,iHitPlace);
		}

		if(bIsUserRace(idAttacker,RACE_JUGGERNAUT))
		{
			clJuggernaut::skillDemonBlade(idAttacker,SKILL_JUGGERNAUT_3);
			clJuggernaut::skillBladeDance(idAttacker,idVictim,iDamage,iWeapon,iHitPlace);
		}
	}

	// Make sure we can run the defensive skills
	if ( SHARED_ValidPlayer( idAttacker ) && !arrBoolData[idVictim][PB_HEXED] )
	{
		//Для talisman +
		//Mirror Shield
		if (ITEM_Has(idVictim, ITEM_MIRROR_SHIELD ) > ITEM_NONE || fWorkTalismanPassive(idVictim, arrTalismanActive[idVictim]) == TALISMAN_ITEM_MIRROR_SHIELD)
		{
			iDamage = iDamage - floatround(iDamage * DEFENSIVE_MIRROR_SHIELD);
			SHARED_GlowShell(idVictim,255,105,180,0.2);
		}

		//Защитные скилы
		NE_SkillsDefensive( idAttacker, idVictim, iDamage, iHitPlace );
		BM_SkillsDefensive( idAttacker, idVictim, iDamage );
		SH_SkillsDefensive( idAttacker, idVictim );
		CL_SkillsDefensive( idAttacker, idVictim, iDamage, iHitPlace );
		clRaceBlackMag::setSkillsDefensive(idAttacker,idVictim);
		AC_SkillsDefensive( idAttacker, idVictim );
		clDisruptor::skillGlimpse(idAttacker,idVictim);
		clRazor::skillEyeOfTheStorm(idAttacker,idVictim);

		if(bIsUserRace(idVictim,RACE_DRUID))
		{
			clDruid::addWMStrikeHealing(idAttacker,idVictim);
		}
		
	}

	// Item abilities
	if ( SHARED_ValidPlayer( idAttacker ) )
	{
		//Для talisman +
		//Mirror Shield
		if (ITEM_Has(idVictim, ITEM_MIRROR_SHIELD ) > ITEM_NONE || fWorkTalismanPassive(idVictim, arrTalismanActive[idVictim]) == TALISMAN_ITEM_MIRROR_SHIELD)
		{
			iDamage = iDamage - floatround(iDamage * ABILITIES_MIRROR_SHIELD);
			SHARED_GlowShell(idVictim,255,105,180,0.2);
		}

		ITEM_Offensive( idAttacker, idVictim, iWeapon, iDamage, iHitPlace );
	}


	if(bIsUserRace(idVictim,RACE_BLOODSEEKER))
		iAmountVendettaDMG[idVictim] += iDamage;

	//client_print(idAttacker, print_chat, "Damage: %d | iAmountDMG: %d", iDamage,iAmountDMG[idAttacker]);
		
	return;
}

// All we want to check is if the user was killed by the bomb
public client_death( idAttacker, idVictim, iWeapon, hitplace, TK )
{
	// Check out who the inflictor was
	new iInflictor = entity_get_edict( idVictim, EV_ENT_dmg_inflictor );

	// Check to see if the death was from the bomb
	if ( !SHARED_ValidPlayer( iInflictor ) && iWeapon != CSW_HEGRENADE && iInflictor )
	{
		
		if ( is_valid_ent ( iInflictor ) )
		{
			new szClassName[64];
			entity_get_string( iInflictor, EV_SZ_classname, szClassName, 63 );

			// Check the classname of our inflictor
			if ( equali( szClassName, "grenade" ) || equali( szClassName, "env_explosion" ) )
			{
				iWeapon = CSW_C4;
				idAttacker = 0;

				// Well if this isn't set, shouldn't it be?
				if ( !arrBoolData[idVictim][PB_DIEDLASTROUND] )
				{
					on_Death( idVictim, idAttacker, iWeapon, 0 );
				}
				//client_print( idVictim, print_chat, "[DEBUG] You were just killed by the bomb (%s) Alive? %d", szClassName, is_user_alive( idVictim ) );
			}
		}
	}

	return PLUGIN_HANDLED;
}

public on_Death(idVictim, idAttacker, iWeaponID, iHeadshot )
{
	if ( !WC3_Check() )
		return;
	
	if(!is_user_connected(idVictim)) 
      return;

	if(!is_user_connected(idAttacker)) 
     return;
	  

	// For some reason the damage passed by explosions is not actually correct (perhaps armor adjustments weren't done yet), so lets check
	if ( is_user_alive( idVictim ) && iWeaponID == CSW_C4 )
		return;

	// Check for NightVision
	arrBoolData[idVictim][PB_NIGHTVISION]	= (cs_get_user_nvg( idVictim )) ? true : false;

	// Check if a user had a shield on death
	arrBoolData[idVictim][PB_SHIELD]		= (cs_get_user_shield( idVictim )) ? true : false;

	// See if the user has a defuse kit
	arrBoolData[idVictim][PB_DEFUSE]		= (cs_get_user_defuse( idVictim )) ? true : false;

	// Save the number of flash grenades the user has
	arrIntData[idVictim][P_FLASHCOUNT]		= cs_get_user_bpammo( idVictim, CSW_FLASHBANG );
	
	// Check to see if weapons were silenced on death
	new iWeaponUSPEnt = find_ent_by_owner( -1, "weapon_usp", idVictim );
	new iWeaponM4A1Ent = find_ent_by_owner( -1, "weapon_m4a1", idVictim );
	
	if ( is_valid_ent( iWeaponUSPEnt ) )
	{
		arrBoolData[idVictim][PB_USP_SILENCED]	= cs_get_weapon_silen( iWeaponUSPEnt ) ? true : false;
	}

	if ( is_valid_ent( iWeaponM4A1Ent ) )
	{
		arrBoolData[idVictim][PB_M4A1_SILENCED]	= cs_get_weapon_silen( iWeaponM4A1Ent ) ? true : false;
	}


	// Check to see if weapons were in burst mode on death
	new iWeaponGlock18Ent = find_ent_by_owner( -1, "weapon_glock18", idVictim );
	new iWeaponFamasEnt = find_ent_by_owner( -1, "weapon_famas", idVictim );

	if ( is_valid_ent( iWeaponGlock18Ent ) )
	{
		arrBoolData[idVictim][PB_GLOCK_BURST]	= cs_get_weapon_burst( iWeaponGlock18Ent ) ? true : false;
	}

	if ( is_valid_ent( iWeaponFamasEnt ) )
	{
		arrBoolData[idVictim][PB_FAMAS_BURST]	= cs_get_weapon_burst( iWeaponFamasEnt ) ? true : false;
	}
	
	WC3_Death( idVictim, idAttacker, iWeaponID, iHeadshot );
	
	return;
}

// Hook for CS/CZ
public on_DeathMsg()
{

	if ( !WC3_Check() )
	{
		return;
	}

	new idAttacker	= read_data( 1 );
	new idVictim		= read_data( 2 );
	new iHeadshot	= read_data( 3 );
	new iWeaponID;
	get_user_attacker( idVictim, iWeaponID );

	//Отключение ESP
	if (ITEM_Has(idVictim, ITEM_ESP ) > ITEM_NONE )
		fDisableItemESP(idVictim);


	on_Death( idVictim, idAttacker, iWeaponID, iHeadshot );

	
	if(get_pcvar_num(CVAR_wc3_respawn_onoff) == 1)
	{
		//if(arrIntData[idVictim][P_RACE] == RACE_ORC)
			SHARED_CopySavedWeapons( idVictim );
	}
	
	//Вывод в чат информации о киллере
	if(get_pcvar_num(CVAR_wc3_info_killer_onoff) == 1)
		fInfoKiller(idAttacker,idVictim);

	return;
}

new g_iLastCurWeapon[33];
public on_CurWeapon( idUser )
{
	// read_data(1) = isActive?
	// read_data(2) = weapon index
	// read_data(3) = ammo

	if ( !WC3_Check() )
		return;

	//client_print(idUser,print_chat,"on_CurWeapon");

	new iCurWeapon = read_data( 2 );

	// Then a weapon strip was triggered - we don't want to save now do we?
	if (iCurWeapon == 0 && read_data( 1 ) == 0 && read_data( 3 ) == 0)
		return;

	// Record the last time a shot was fired
	fLastShotFired[idUser] = halflife_time();
	
	// Save the user's weapons
	SHARED_SaveWeapons( idUser );
		
	// We only need to run these functions if the user's weapon has changed since our last function call!
	if ( g_iLastCurWeapon[idUser] != iCurWeapon && SHARED_ValidPlayer( idUser ))
	{
		// Check to see if we should set the player's invisibility
		SHARED_INVIS_Set( idUser );
		
		// Set the user's speed
		SHARED_SetSpeed( idUser );
	}

	g_iLastCurWeapon[idUser] = iCurWeapon;

	return;
}

public on_Drop( idUser )
{
	if ( !WC3_Check() )
	{
		return;
	}

	SHARED_SaveWeapons( idUser );

	return;
}

// HamSandwich implementation
public EVENT_Spawn(idUser)
{
	if (!WC3_Check())
		return HAM_HANDLED;
	
	// ResetHUD can be called when the user is not alive, lets ignore those calls
	if (!is_user_alive(idUser))
		return HAM_HANDLED;

	// Store the player's team!
	g_iPlayerTeam[idUser] = get_user_team( idUser );

	// Prespawn call
	//   - Purpose is to have a spawn call that happens before everything else!
	WC3_PreSpawn(idUser);
	
	// This is the first time the user has spawned this round
	if ( !arrBoolData[idUser][PB_HAS_SPAWNED] )
	{	
		EVENT_PlayerInitialSpawn( idUser );

		g_friezadisk[idUser] = iMaxNumDisk;

		arrBoolData[idUser][PB_HAS_SPAWNED] = true;
	}

	// Start a new session under the following conditions:
	//		- CSDM - rounds never end!!!
//	if (( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 ) )
		WC3_NewSession( idUser );

	// Should be called at the end of each spawn
	WC3_PostSpawn(idUser);

	//Для shopmenu4
	sm4_4_2_hamPlayerSpawn(idUser);

	if(sm4_IsPlayerSkeleton(idUser) == false)
		ExecuteForward(mfSpawn, mfSpawnReturn,idUser,0);

	return HAM_HANDLED;
}

// Function called EVERYTIME a user spawns!
public on_ResetHud( idUser )
{

	if ( !WC3_Check() )
	{
		return PLUGIN_CONTINUE;
	}

	// ResetHUD can be called when the user is not alive, lets ignore those calls
	if ( !is_user_alive( idUser ) )
	{
		return PLUGIN_CONTINUE;
	}
		

	// Store the player's team!
	g_iPlayerTeam[idUser] = get_user_team( idUser );

	// We're forcibly respawning the player - so lets just return
	if ( bIgnorePlayerSpawning[idUser] )
	{
		return PLUGIN_CONTINUE;
	}

	// Prespawn call
	//   - Purpose is to have a spawn call that happens before everything else!
	WC3_PreSpawn( idUser );

	// This is the first time the user has spawned this round
	if ( !arrBoolData[idUser][PB_HAS_SPAWNED] )
	{	
		EVENT_PlayerInitialSpawn( idUser );
		arrBoolData[idUser][PB_HAS_SPAWNED] = true;
	}

	// Should be called at the end of each spawn
	WC3_PostSpawn( idUser );

	arrBoolData[idUser][PB_ISBURNING] = false;
	arrIntData[idUser][P_FLAMECOUNT] = 0;

	return PLUGIN_CONTINUE;
}

// Function is called when the user is spawned at the START of each round - only WC3_PreSpawn is called first
//		TRIGGERED BY: ResetHUD
public EVENT_PlayerInitialSpawn( idUser )
{
	// Display the cheat message ONLY if they just joined!
	if ( arrBoolData[idUser][PB_JUSTJOINED] && get_pcvar_num(CVAR_wc3_cheats) )
	{
		format(szMessage, charsmax(szMessage), "%L /level10",LANG_PLAYER,"CLIENT_PRINT_EVENT_PLAYER_INITIAL_SPAWN");	
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		
		arrBoolData[idUser][PB_JUSTJOINED]	= false;
	}

	// Display the new Chameleon skills for the round
	if ( arrIntData[idUser][P_RACE] == 9 && get_pcvar_num( CVAR_wc3_cham_random ) )
	{
		WC3_ShowRaceInfo( idUser );
	}

	//if ( CVAR_csdm_active == 0)
		WC3_NewSession(idUser);

	return;
}



// Called when a user looks somewhere
public TRIGGER_TraceLine( Float:v1[3], Float:v2[3], noMonsters, pentToSkip )
{
	if (!WC3_Check())
		return FMRES_IGNORED;

	new idAttacker = pentToSkip;
	new idVictim = get_tr(TR_pHit);
	new iHitZone = (1 << get_tr(TR_iHitgroup));
	

	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return FMRES_IGNORED;

	if(!is_user_connected(idVictim)) 
		return FMRES_IGNORED;


	new iClipAmmo,iAmmo;
    new iCurWeapon = get_user_weapon(idAttacker,iClipAmmo,iAmmo);

	new iCurButton = pev(idAttacker,pev_button);


	// Make sure we have a valid victim
	if ( SHARED_ValidPlayer( idVictim ) && arrBoolData[idVictim][PB_ISCONNECTED] )
	{
		// We need to have a valid player!
		if ( SHARED_ValidPlayer( idAttacker ) )
		{
			// This is a check for ultimates that need to "search" for a target
			if ( arrBoolData[idAttacker][PB_ISSEARCHING] )
			{

				// Now lets make sure the person he's looking at is in view and isn't on the same team
				if ( get_user_team( idAttacker ) != get_user_team( idVictim ) ) //&& UTIL_EntInView( idAttacker, idVictim ) )
				{
					
					// Check to see if the user should block this ultimate!
					if ( !g_EndRound && ULT_CanUserBlockUlt(idVictim,idAttacker) )
					{
						ULT_RemoveCharge(idVictim);
						ULT_Blocked( idAttacker );
					}

					// Then the user's ult should work!
					else
					{

						//Для talisman +
						//Для shopmenu4
						//ITEM_MIRROR_ULTIMATE - Отражатель супер навыка - Mirror Ultimate
						if ( (ITEM_Has(idVictim, ITEM_MIRROR_ULTIMATE ) > ITEM_NONE && ITEM_HasItem( idVictim, ITEM_NECKLACE ) != ITEM_NECKLACE) ||
							 (fWorkTalismanPassive(idVictim, arrTalismanActive[idVictim]) == TALISMAN_ITEM_MIRROR_ULTIMATE && ITEM_HasItem( idVictim, ITEM_NECKLACE ) != ITEM_NECKLACE)
						   )
						{

							if(ITEM_Has(idAttacker, ITEM_NECKLACE ) > ITEM_NONE)
							{
								formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MIRROR_ULT_BLOCKED");
								cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);

								emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_MIRROR_ULTIMATE_BLOCK], 1.0, ATTN_NORM, 0, PITCH_NORM );
								emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_MIRROR_ULTIMATE_BLOCK], 1.0, ATTN_NORM, 0, PITCH_NORM );

								ITEM_RemoveCharge(idAttacker, ITEM_NECKLACE );
								ITEM_RemoveCharge(idVictim, ITEM_MIRROR_ULTIMATE );

								// No longer searching since we found a target
								arrBoolData[idAttacker][PB_ISSEARCHING]	= false;

								// Set up the user's ultimate delay
								fResetUltimateTimerDivider(idAttacker);

								return FMRES_SUPERCEDE;
							}

							formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MIRROR_ULT");
							cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);

							sm4_EffectMirrorUltimate(idVictim);

							// Well we do have a target so lets execute the user's ultimate!!
							if ( SM_GetSkillLevel( idAttacker, ULTIMATE_CHAINLIGHTNING ) > 0 )
							{
								OR_ULT_ChainLightning(idVictim,idAttacker, iHitZone );
							}
							else if ( SM_GetSkillLevel(idAttacker, ULTIMATE_ENTANGLE ) > 0 )
							{
								NE_ULT_Entangle(idVictim,idAttacker);
							}
							else if ( SM_GetSkillLevel( idAttacker, ULTIMATE_IMMOLATE ) > 0 )
							{
								BM_ULT_Immolate(idVictim,idAttacker );
							}
							else if ( SM_GetSkillLevel( idAttacker, ULTIMATE_FROST_MAGE_BLIZZARD ) > 0 )
							{
								FM_ULT_Blizzard(idVictim,idAttacker, iHitZone );
								
							}
							else if (SM_GetSkillLevel(idAttacker, ULTIMATE_BLOODSEEKER ) > 0 )
							{
								clBloodseeker::ultBloodyMadness(idVictim,idAttacker);
								
							}

							ITEM_RemoveCharge(idVictim, ITEM_MIRROR_ULTIMATE );
						}
						else
						{
							// Well we do have a target so lets execute the user's ultimate!!
							if ( SM_GetSkillLevel( idAttacker, ULTIMATE_CHAINLIGHTNING ) > 0 )
							{
								OR_ULT_ChainLightning( idAttacker, idVictim, iHitZone );
							}
							else if ( SM_GetSkillLevel( idAttacker, ULTIMATE_ENTANGLE ) > 0 )
							{
								NE_ULT_Entangle( idAttacker, idVictim );
							}
							else if ( SM_GetSkillLevel( idAttacker, ULTIMATE_IMMOLATE ) > 0 )
							{
								BM_ULT_Immolate( idAttacker, idVictim );
							}
							else if ( SM_GetSkillLevel( idAttacker, ULTIMATE_FROST_MAGE_BLIZZARD ) > 0 )
							{
								FM_ULT_Blizzard( idAttacker, idVictim, iHitZone );
							}
							else if ( SM_GetSkillLevel( idAttacker, ULTIMATE_BLACKLIGHTNING ) > 0 )
							{
							
								new vOldLocation[3], vNewLocation[3]
								
								get_user_origin(idAttacker, vOldLocation );
								get_user_origin(idVictim, vNewLocation);

								clRaceBlackMag::ultBlackLight(idAttacker,idVictim,vOldLocation,vNewLocation);
								clRaceBlackMag::ultBlackLight(idVictim,idAttacker,vNewLocation,vOldLocation);
								
							}
							else if ( SM_GetSkillLevel( idAttacker, ULTIMATE_RADIATION) > 0 )
							{
								AC_ULT_Eclipse( idAttacker, idVictim );
							}
							else if (SM_GetSkillLevel(idAttacker, ULTIMATE_BLOODSEEKER ) > 0 )
							{
								clBloodseeker::ultBloodyMadness(idAttacker,idVictim);
								
							}
							if (SM_GetSkillLevel(idAttacker, ULTIMATE_JUGGERNAUT ) > 0 )
							{
								clJuggernaut::ultBladeFury(idAttacker);
							}
							if (SM_GetSkillLevel(idAttacker, ULTIMATE_SNIPER) > 0 )
							{
								clSniper::ultShrapnel(idAttacker);
							}
							if (SM_GetSkillLevel(idAttacker, ULTIMATE_DISRUPTOR ) > 0 )
							{
								clDisruptor::ultStaticStorm(idAttacker,idVictim);
							}
							if (SM_GetSkillLevel(idAttacker, ULTIMATE_RAZOR ) > 0 )
							{
								clRazor::ultPlasmaField(idAttacker,idVictim);
							}
							if (SM_GetSkillLevel(idAttacker, ULTIMATE_WARLOCK ) > 0 )
							{
								clWarlock::ultPermanentImmolation(idAttacker,idVictim);
							}
							
							
						}
					}
					
					// No longer searching since we found a target
					arrBoolData[idAttacker][PB_ISSEARCHING]	= false;

					// Set up the user's ultimate delay
					fResetUltimateTimerDivider(idAttacker);
				}
			
			}

			//Для shopmenu4
			//ITEM_DEATHCOIL - Death Coil - Лик смерти
			if ( ITEM_Has( idAttacker, ITEM_DEATHCOIL ) > ITEM_NONE )
			{
				if (random_num(0, 99 ) <= get_pcvar_num( CVAR_wc3_deathcoil_percent ) ) 
					sm4_4_5_DeathCoil( idAttacker, idVictim);
			}

			//ITEM_IMPALE - Impale - Пронзающий шип
			if ( ITEM_Has( idAttacker, ITEM_IMPALE ) > ITEM_NONE )
			{
				if (random_num(0, 99 ) <= get_pcvar_num( CVAR_wc3_impale_percent ) ) 
					sm4_4_6_Impale( idAttacker, idVictim);
			}

			//ITEM_SLEEP - Sleep - Сонная аура
			if ( ITEM_Has( idAttacker, ITEM_SLEEP ) > ITEM_NONE )
			{
				if (random_num(0, 99 ) <= get_pcvar_num( CVAR_wc3_sleep_percent ) ) 
					sm4_4_7_Sleep( idAttacker, idVictim);
			}
			
			// This is a nice check for Helm of Excellence
			//ITEM_HELM	- Helm of Excellence
			if ((ITEM_Has(idVictim, ITEM_HELM ) > ITEM_NONE && !bIsUserRace(idAttacker,RACE_SNIPER)) || 
				(fWorkTalismanPassive(idVictim, arrTalismanActive[idVictim] == TALISMAN_ITEM_HELM) && arrTalismanHelmNum[idVictim] > 0 && !bIsUserRace(idAttacker,RACE_SNIPER)) ||
				 clVIP:isAccesItemVip(idVictim,ITEM_HELM) == true
				)
			{
				// Friendly fire is off! - This means same team shouldn't remove a charge!
				if ( !get_pcvar_num( CVAR_mp_friendlyfire ) )
				{
					if ( g_iPlayerTeam[idAttacker] == g_iPlayerTeam[idVictim] )
					{
						return FMRES_IGNORED;
					}
				}

				if(!(iCurButton & IN_ATTACK) || (iCurButton & IN_RELOAD))
					return FMRES_IGNORED;

				switch(iCurWeapon)
				{
					case CSW_KNIFE,CSW_HEGRENADE,CSW_C4,CSW_FLASHBANG,CSW_SMOKEGRENADE:
						return FMRES_IGNORED;
				}

				// If its a headshot then we want to block it
				if ( iHitZone & (1 << 1) )
				{
					set_tr( TR_flFraction, 1.0 );
					
					// Make sure we have a valid attacker!
					if ( SHARED_ValidPlayer( idAttacker ) )
					{
						// Do the check to see if we should flash the screen orange
						new Float:fTime = halflife_time();
						new Float:fDifference = fTime - fLastShotFired[idAttacker];

						if ( fDifference < 0.1 && fDifference > 0.0 )
						{
							Create_ScreenFade( idVictim, (1<<10), (1<<10), (1<<12), 0, 0, 255, 150 );

							// Lets remove a charge from the helm!
							ITEM_RemoveCharge( idVictim, ITEM_HELM );
						}
					}
					
					return FMRES_SUPERCEDE;
				}
			}

			
			//Рыцарь смерти
			// *******************************************************
			// Скил 2 уровня - Лик смерти - Death Coil
			// *******************************************************
			if (SM_GetSkillLevel(idVictim, SKILL_DEATH_KNIGHT_DEATH_COIL ) > 0 )
			{
				// Do the check to see if we should "evade" this shot
				new Float:fTime = halflife_time();
				new Float:fDifference = fTime - fLastShotFired[idAttacker];

				//client_print(idAttacker,print_center,"fDifference: %.1f",fDifference);

				if ( SHARED_ValidPlayer( idAttacker ) && fDifference < fDeathCoilChance && fDifference > 0.0 )
				{
					clRaceDeathKnight::skillDeathCoil(idVictim,idAttacker);

					return FMRES_SUPERCEDE;
				}
			}

			//Жрец
			// *******************************************************
			// Скил 1 уровня - Entry into a chasm - Вхождение в бездну
			// *******************************************************
			if (SM_GetSkillLevel(idAttacker, SKILL_PRIEST_ENTRYINTOCHASM ) > 0 )
			{
				new Float:fTime = halflife_time();
				new Float:fDifference = fTime - fLastShotFired[idAttacker];

				if ( SHARED_ValidPlayer( idAttacker ) && fDifference < fEntryFrequency && fDifference > 0.0 )
				{
					clRacePriest::skillEntryInChasm(idVictim,idAttacker);

					return FMRES_SUPERCEDE;
				}
			}
			

			//Джагернаут
			// *******************************************************
			// Скил 2 уровня - Критический клинок (Critical Blade)
			// *******************************************************
			if (SM_GetSkillLevel(idAttacker, SKILL_JUGGERNAUT_2 ) > 0 )
			{
				if(!(iCurButton & IN_ATTACK) || (iCurButton & IN_RELOAD))
					return FMRES_IGNORED;

				switch(iCurWeapon)
				{
					case CSW_KNIFE,CSW_HEGRENADE,CSW_C4,CSW_FLASHBANG,CSW_SMOKEGRENADE:
						return FMRES_IGNORED;
				}

				new Float:fTime = halflife_time();
				new Float:fDifference = fTime - fLastShotFired[idAttacker];

				if ( SHARED_ValidPlayer(idAttacker) && fDifference < 0.1 && fDifference > 0.0 )
				{
					clJuggernaut::skillCriticalBlade(idAttacker,SKILL_JUGGERNAUT_2);

					return FMRES_SUPERCEDE;
				}
			}

			// Check to see if this user has night elf's evasion
			if (SM_GetSkillLevel(idVictim, SKILL_EVASION ) > 0)
			{
				if(!(iCurButton & IN_ATTACK) || (iCurButton & IN_RELOAD))
					return FMRES_IGNORED;

				switch(iCurWeapon)
				{
					case CSW_KNIFE,CSW_HEGRENADE,CSW_C4,CSW_FLASHBANG,CSW_SMOKEGRENADE:
						return FMRES_IGNORED;
				}

				// Do the check to see if we should "evade" this shot
				new Float:fTime = halflife_time();
				new Float:fDifference = fTime - fLastShotFired[idAttacker];

				if ( SHARED_ValidPlayer( idAttacker ) && fDifference < 0.1 && fDifference > 0.0 )
				{

					// Friendly fire is off! - This means we shouldn't evade since no damage will be done!
					if ( !get_pcvar_num( CVAR_mp_friendlyfire ) )
					{
						if ( g_iPlayerTeam[idAttacker] == g_iPlayerTeam[idVictim] )
						{
							return FMRES_IGNORED;
						}
					}
					
					// Then we should evade this shot!
					if ( NE_Evasion( idVictim, iHitZone ) )
					{
						set_tr( TR_flFraction, 1.0 );
						
						format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_EVENT_EVADED_SHOT");
						WC3_StatusText( idVictim, TXT_SKILL, szMessage);

						return FMRES_SUPERCEDE;
					}
				}
			}
			
			// Mole protectant
			if ( arrBoolData[idAttacker][PB_MOLE] && ITEM_Has( idVictim, ITEM_PROTECTANT ) > ITEM_NONE ||
				 arrBoolData[idAttacker][PB_MOLE] && fWorkTalismanPassive(idVictim, arrTalismanActive[idVictim]) == TALISMAN_ITEM_PROTECTANT)
			{	
				new Float:fTime = halflife_time();

				if ( fTime - fLastShotFired[idAttacker] < 0.1  )
				{
					format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"SHOT_DEFLECTED");	
					cssbChatColor(idVictim,"%s%s",fTagWar3ft(),szMessage);
		
					set_tr( TR_flFraction, 1.0 );

					return FMRES_SUPERCEDE;
				}
			}

			// Check for Big Bad Voodoo's ultimate!
			if (arrBoolData[idVictim][PB_GODMODE])
			{
				new bool:bBlockDamage = true;

				// Do we allow this person to be attacked by this player?
				if ( arrBoolData[idAttacker][PB_BIGBAD_ATTACKER] )
					bBlockDamage = false;
				// Check to see if immunity is available for the attacker
				else if (ULT_CanUserBlockUlt(idAttacker,idVictim))
				{
					// Remove charge and display message to attacker
					ULT_RemoveCharge(idAttacker);

					// Display message about user's ultimate being blocked!
					ULT_Blocked( idVictim );

					// This user can attack someone with big bad voodoo!
					arrBoolData[idAttacker][PB_BIGBAD_ATTACKER] = true;

					// Reset the attacker dmg
					new Float:fTimeCoolDown = ArrayGetCell(arrIntUltimateTimer,RACE_SHADOW);
					set_task(fTimeCoolDown, "_SH_ResetBigBadAttacker", TASK_BIGBADATTACKER + idAttacker );
				}

				// Block the damage!
				if (bBlockDamage)
				{
					set_tr(TR_flFraction, 1.0);

					return FMRES_SUPERCEDE;
				}
			}
		}
	}
	
	return FMRES_IGNORED;
}

//Сброс расы если игрок сменил команду для того чтобы учесть ограничение на расы
new g_iCurTeam[ 33 ] = { 'U' , ... };
public evTeamInfo( )
{
	if(iNumRaceOnOff > 0)
	{
		static idUser; 
		idUser = read_data( 1 );
		static szTeam[ 2 ]; 
		read_data(2,szTeam,1);
	    
		if ( g_iCurTeam[idUser] != szTeam[0] )
		{
			g_iCurTeam[idUser] = szTeam[0];
	        
			switch(szTeam[0] )
			{
				case 'T': //Terrorist
				{
					//cssbChatColor(idUser,"%s --- Terrorist",szTeam);

					if(arrIntData[idUser][P_RACE] != RACE_NONE)
						arrBoolData[idUser][PB_CHANGE_TEAM_RESET_RACE] = true;

				}
				case 'C': //CT
				{
					//cssbChatColor(idUser,"%s --- CT",szTeam);

					if(arrIntData[idUser][P_RACE] != RACE_NONE)
						arrBoolData[idUser][PB_CHANGE_TEAM_RESET_RACE] = true;
				}
				case 'S': //Spectator
				{
				   // cssbChatColor(idUser,"%s --- Spectator",szTeam);

					if(arrIntData[idUser][P_RACE] != RACE_NONE)
						arrBoolData[idUser][PB_CHANGE_TEAM_RESET_RACE] = true;
				}
			}
		}
	}
}  