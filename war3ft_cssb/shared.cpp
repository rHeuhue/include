/*
*	Shared Functions
*/


// This should be called on weapon change, on new round, when the user selects a new skill, and after an item is purchased
public SHARED_INVIS_Set( idUser )
{
	//client_print(idUser,print_chat,"SHARED_INVIS_Set");

	// Do not want to set them as invisible if the player is currently rendering
	if (!arrBoolData[idUser][PB_CAN_RENDER] || !arrBoolData[idUser][PB_ISCONNECTED])
		return;

	new iInvisLevel = 0;

	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( idUser, SKILL_INVISIBILITY );

	// If they are Human Alliance with Invisibility lets set the level
	if (iSkillLevel > 0)
	{
		if(isDisabledSkillsOnMap(idUser,SKILL_INVISIBILITY) == false)
			iInvisLevel = ArrayGetCell(arrInvisibility,iSkillLevel-1);
	}

	//Для talisman +
	// User has a Cloak of Invisibility
	if ( ITEM_Has( idUser, ITEM_CLOAK ) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_CLOAK)
	{
		// Then we are already a little invis, lets give them a little bonus for purchasing the item
		if ( iInvisLevel > 0 )
		{
			iInvisLevel = floatround( float( iInvisLevel ) / INVIS_CLOAK_DIVISOR );
		}
		else
		{
			iInvisLevel = get_pcvar_num( CVAR_wc3_cloak );
		}
	}
	
	// If the player is holding a knife they should be more invisible
	if ( SHARED_IsHoldingKnife( idUser ) )
	{
		iInvisLevel /= 2;
	}

	if ( iInvisLevel )
	{
		set_user_rendering( idUser, kRenderFxNone, 0, 0, 0, kRenderTransTexture, iInvisLevel );
		
		arrBoolData[idUser][PB_INVIS] = true;
	}

	// User should not be invisible
	else
	{
		set_user_rendering( idUser );

		arrBoolData[idUser][PB_INVIS] = false;
	}

	return;
}

// Function returns true if the user has a grenade in his inventory
SHARED_HasGrenade( idUser )
{
	new i, bool:bNadeFound = false;
	
	// Loop through all weapons and search for a grenade
	while ( g_PlayerWeapons[idUser][i] && !bNadeFound )
	{
		if ( SHARED_IsGrenade( g_PlayerWeapons[idUser][i] ) )
		{
			bNadeFound = true;
			break;
		}

		i++;
	}

	return bNadeFound;
}



// ******************************************************************
// Проверки, какое оружие у игрока {
// ******************************************************************
bool:SHARED_IsGrenade(iWeapon)
{
	if (iWeapon == CSW_HEGRENADE )
		return true;

	return false;
}

bool:SHARED_IsHoldingKnife(idUser)
{
	new iClip, iAmmo, iWeapon;
	iWeapon = get_user_weapon( idUser, iClip, iAmmo );

	if (iWeapon == CSW_KNIFE )
		return true;

	return false;
}

bool:SHARED_IsSecondaryWeapon( iWeaponID )
{
	if ( iWeaponID == CSW_ELITE || iWeaponID == CSW_FIVESEVEN || iWeaponID == CSW_USP || iWeaponID == CSW_GLOCK18 || iWeaponID == CSW_DEAGLE || iWeaponID == CSW_P90 )
		return true;

	return false;
}


bool:SHARED_IsPrimaryWeapon( iWeaponID )
{
	if ( iWeaponID == CSW_GALIL || iWeaponID == CSW_FAMAS || iWeaponID == CSW_M3 || iWeaponID == CSW_XM1014 || iWeaponID == CSW_MP5NAVY || iWeaponID == CSW_TMP || iWeaponID == CSW_P90 || iWeaponID == CSW_MAC10 || iWeaponID == CSW_UMP45 || iWeaponID == CSW_AK47 || iWeaponID == CSW_SG552 || iWeaponID == CSW_M4A1 || iWeaponID == CSW_AUG || iWeaponID == CSW_SCOUT || iWeaponID == CSW_AWP || iWeaponID == CSW_G3SG1 || iWeaponID == CSW_SG550 || iWeaponID == CSW_M249 )
		return true;

	return false;
}
// ******************************************************************
// Проверки, какое оружие у игрока }
// ******************************************************************

// Function will return the user's money
SHARED_GetUserMoney( idUser )
{
	// If user isn't connected - then he shouldn't have any money
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return 0;

	return cs_get_user_money( idUser );
}

// Function will set a user's money, if show is 1 then the difference will be displayed on screen
SHARED_SetUserMoney( idUser, money, show = 1 )
{
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return;

	cs_set_user_money(idUser, money, show );

	return;
}

// Function will return an ammo name given a weapon ID
public SHARED_GetAmmoName( iWeapID, szAmmoName[], len )
{
	switch( iWeapID )
	{
		case CSW_USP, CSW_MAC10, CSW_UMP45:
		{ 
			copy( szAmmoName, len, "ammo_45acp" );
		}
		case CSW_ELITE, CSW_GLOCK18, CSW_MP5NAVY, CSW_TMP:
		{
			copy( szAmmoName, len, "ammo_9mm" );
		}
		case CSW_FIVESEVEN, CSW_P90:
		{
			copy( szAmmoName, len, "ammo_57mm" );
		}
		case CSW_DEAGLE:
		{
			copy( szAmmoName, len, "ammo_50ae" );
		}
		case CSW_P228:
		{
			copy( szAmmoName, len, "ammo_357sig" );
		}
		case CSW_SCOUT, CSW_G3SG1, CSW_AK47:
		{
			copy( szAmmoName, len, "ammo_762nato" );
		}
		case CSW_XM1014, CSW_M3:
		{
			copy( szAmmoName, len, "ammo_buckshot" );
		}
		case CSW_AUG, CSW_SG550, CSW_GALIL, CSW_FAMAS, CSW_M4A1:
		{
			copy( szAmmoName, len, "ammo_556nato" );
		}
		case CSW_AWP:
		{
			copy( szAmmoName, len, "ammo_338magnum" );
		}
		case CSW_M249:
		{
			copy( szAmmoName, len, "ammo_556natobox" );
		}
		case CSW_SG552:
		{
			copy( szAmmoName, len, "ammo_556nato" );
		}
		default:
		{
			copy( szAmmoName, len, "" );
		}
	}
}

// Function used to spawn a player
public _SHARED_Spawn( idUser )
{
	// Respawning isn't necessary w/CSDM - so lets not do that!
//	if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 && get_pcvar_num(CVAR_wc3_respawn_onoff) == 0)
//	{
//		return;
//	}

	idUser -= TASK_SPAWN;

	// User is no longer connected or is not on a team
	if ( !arrBoolData[idUser][PB_ISCONNECTED] || !SHARED_IsOnTeam( idUser ) )
	{
		return;
	}

	// Round has ended, lets give money back if they bought a scroll
	if (g_EndRound)
	{
		if ( arrIntData[idUser][P_RESPAWNBY] == RESPAWN_ITEM )
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_RESPAWN_ITEM");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		
			SHARED_SetUserMoney( idUser, SHARED_GetUserMoney( idUser ) + ITEM_Cost( idUser, ITEM_SCROLL ) );
		}

		return;
	}

	// Reset items when the user spawns!
	g_iShopMenuItems[idUser][ITEM_SLOT_ONE]	= ITEM_NONE;
	g_iShopMenuItems[idUser][ITEM_SLOT_TWO] = ITEM_NONE;
	g_iShopMenuItems[idUser][ITEM_SLOT_THREE] = ITEM_NONE;
	
	if ( is_user_alive( idUser ) )
	{
		//client_print(idUser,print_chat,"_SHARED_Spawn is_user_alive");
		return;
	}

	// Give the user godmode for a little
	set_user_godmode( idUser, 1 );
	arrBoolData[idUser][PB_NO_DAMAGE] = true;

	// Save their previous weapons!
	SHARED_CopySavedWeapons( idUser );

	// Ignore the armor settaging...
	bIgnoreArmorSet[idUser] = true;

	// We don't want to call a crap-ton of WC3 functions when we're spawning them 3 times do we ?
	bIgnorePlayerSpawning[idUser] = true;

	// Spawn the player
	ExecuteHamB(Ham_CS_RoundRespawn,idUser);
	
	arrBoolData[idUser][PB_SLOWED]		= false;
	arrBoolData[idUser][PB_STUNNED]	= false;
	arrBoolData[idUser][PB_GIVEITEMS]	= true;
	
	// Reset the user's skin to normal
	SHARED_ChangeSkin( idUser, SKIN_RESET );

	// The user should no longer be a mole!
	arrBoolData[idUser][PB_MOLE] = false;

	set_task( 0.2, "_SHARED_Spawn_Final", TASK_SPAWNPLAYER + idUser );
	set_task( 0.4, "_SHARED_CS_GiveWeapons", TASK_GIVEITEMS + idUser );
	set_task( 1.0, "_SHARED_SpawnRemoveGod", TASK_SPAWNREMOVEGOD + idUser );

	//client_print(idUser,print_chat,"_SHARED_Spawn OK");

	return;
}

public _SHARED_SpawnRemoveGod( idUser )
{
	idUser -= TASK_SPAWNREMOVEGOD;

	// Only do this if the user is connected
	if ( arrBoolData[idUser][PB_ISCONNECTED] )
	{
		set_user_godmode( idUser, 0 );
		arrBoolData[idUser][PB_NO_DAMAGE] = false;
	}
}

// Function will just spawn a player again
public _SHARED_Spawn_Final( idUser )
{
	idUser -= TASK_SPAWNPLAYER;

	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return;
	
	// OK lets do something on this spawn!
	bIgnorePlayerSpawning[idUser] = false;

//	set_pev(idUser, pev_spawnflags, 3);
//	dllfunc(DLLFunc_Spawn, idUser);
//	set_pev(idUser, pev_iuser1, 0);
	
	bIgnoreArmorSet[idUser] = false;

	// If we don't give them a suit then they won't have a HUD
	give_item(idUser, "item_suit" );
		
	clHP:setCurRespawnRaceHealth(idUser);

	clVIP:fInitItemsAccessVip(idUser);

	SHARED_CS_Reincarnation(idUser);
	
	return;
}

// Reincarnation for Counter-Strike and Condition Zero
public SHARED_CS_Reincarnation( idUser )
{
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}

	// Giving weapons will only screw things up w/CSDM - so lets not do that!
	if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 && get_pcvar_num(CVAR_wc3_respawn_onoff) == 0)
	{
		//g_bPlayerBoughtAnkh[idUser] = false;
		return;
	}

	new bool:bGiveWeapons = false;
	
	// If the give items flag is true
	if ( arrBoolData[idUser][PB_GIVEITEMS] )
	{
		bGiveWeapons = true;
		arrBoolData[idUser][PB_GIVEITEMS] = false;
	}
	
	// Check based on skill or if the user has an item
	if ( arrBoolData[idUser][PB_DIEDLASTROUND] == true )
	{
		static iSkillLevel;
		iSkillLevel = SM_GetSkillLevel(idUser, SKILL_REINCARNATION );

		// Orc's Reincarnation
		if ( iSkillLevel > 0 && isDisabledSkillsOnMap(idUser,SKILL_REINCARNATION) == false)
		{
			new Float:fAnkh = ArrayGetCell(arrEquipmentreincarnation,iSkillLevel-1);
			if (random_float(fOrcSkill3MinPercent, fOrcSkill3MaxPercent ) <= fAnkh )
			{
				bGiveWeapons = true;		
			}
		}
				
		// Ankh - ITEM_ANKH - Ankh of Reincarnation
		if (g_bPlayerBoughtAnkh[idUser] || 
			fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_ANKH ||
			clVIP:isAccesItemVip(idUser,ITEM_ANKH) == true	
			)
		{
			bGiveWeapons = true;

			g_bPlayerBoughtAnkh[idUser] = false;
		}	
	}

	if ( bGiveWeapons )
	{
		client_cmd(idUser, "speak %s", arrStrSounds[SOUND_REINCARNATION] );
		
		// Make the user glow!
		SHARED_Glow( idUser, 0, 100, 0, 0 );

		// Screen fade green
		Create_ScreenFade( idUser, (1<<10), (1<<10), (1<<12), 0, 255, 0, 255 );
		
		// Give the user their weapons from last round
		_SHARED_CS_GiveWeapons(idUser);

	}
	else
	{
		if ( !cs_get_user_nvg( idUser ) )
		{
			arrBoolData[idUser][PB_NIGHTVISION] = false;
		}
	}

	return;	
}	

public _SHARED_CS_GiveWeapons(idUser)
{

	if ( idUser >= TASK_GIVEITEMS )
	{
		idUser -= TASK_GIVEITEMS;
	}

	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return;

	// Check to see if the user should have the bomb
	new bool:bGiveBomb = false;
	if ( cs_get_user_plant( idUser ) )
	{
		bGiveBomb = true;
	}

	// Remove all weapons
	strip_user_weapons( idUser );

	// Give armor
	if (arrIntData[idUser][P_LASTARMOR])
		clAr:setUserArmorOnType(idUser, arrIntData[idUser][P_LASTARMOR], g_ArmorType[idUser] );
		
	// Give a defuse kit
	if ( arrBoolData[idUser][PB_DEFUSE] )
	{
		give_item(idUser, "item_thighpack");
		// Check for bomb on the back of chameleon
		if ( arrBoolData[idUser][PB_SKINSWITCHED] )
			entity_set_int(idUser, EV_INT_body, 0);

	}

	if ( arrBoolData[idUser][PB_NIGHTVISION] )
	{
		cs_set_user_nvg( idUser, 1 );
	}

	// Give the user a bomb
	if ( bGiveBomb )
	{
		give_item( idUser, "weapon_c4" );

		cs_set_user_plant( idUser, 1, 1 );
	}
	
	new iWeapID = 0, i = 0, bool:bPrimaryFound = false;
	for ( i = 0; i < 32; i++ )
	{
		iWeapID = g_PlayerLastWeapons[idUser][i];

		if ( iWeapID )
		{
			if ( iWeapID != CSW_C4 && iWeapID != CSW_FLASHBANG )
			{
				new szWeaponName[32], szAmmoName[32];
				get_weaponname( iWeapID, szWeaponName, 31 );
				SHARED_GetAmmoName( iWeapID, szAmmoName, 31 );
				
				if ( contain( szWeaponName, "weapon_" ) == 0 )
				{
					give_item( idUser, szWeaponName );

					if ( strlen( szAmmoName ) > 0 )
					{
						give_item( idUser, szAmmoName );
						give_item( idUser, szAmmoName );
						give_item( idUser, szAmmoName );
						give_item( idUser, szAmmoName );
						give_item( idUser, szAmmoName );
					}
				}
			}
		}

		if ( SHARED_IsPrimaryWeapon( iWeapID ) )
		{
			new szWeaponName[32];
			get_weaponname( iWeapID, szWeaponName, 31 );

			bPrimaryFound = true;
		}
	}

	// Only give it if the user doesn't have a primary weapon
	if ( arrBoolData[idUser][PB_SHIELD] )
	{
		if ( !bPrimaryFound )
		{
			give_item( idUser, "weapon_shield" );
		}
	}

	// Give them their flash bangs back
	while ( arrIntData[idUser][P_FLASHCOUNT] > 0 )
	{
		give_item( idUser, "weapon_flashbang" );

		arrIntData[idUser][P_FLASHCOUNT]--;
	}

	//Для того чтобы работали Глыба и Перчатки когда покупаешь Возрождение (скролл)
	ITEM_GiveAllBonuses(idUser);

	set_task( 0.4, "_SHARED_SetSilenceBurst", TASK_SILENCEBURST + idUser );

	return;
}

public _SHARED_SetSilenceBurst( idUser )
{
	if ( idUser >= TASK_SILENCEBURST )
	{
		idUser -= TASK_SILENCEBURST;
	}

	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}


	new iWeaponEnt = find_ent_by_owner( -1, "weapon_m4a1", idUser );
	if ( is_valid_ent( iWeaponEnt ) )
	{
		cs_set_weapon_silen( iWeaponEnt, arrBoolData[idUser][PB_M4A1_SILENCED], 1 );
	}

	iWeaponEnt = find_ent_by_owner( -1, "weapon_usp", idUser );
	if ( is_valid_ent( iWeaponEnt ) )
	{
		cs_set_weapon_silen( iWeaponEnt, arrBoolData[idUser][PB_USP_SILENCED], 1 );
	}

	iWeaponEnt = find_ent_by_owner( -1, "weapon_famas", idUser );
	if ( is_valid_ent( iWeaponEnt ) )
	{
		cs_set_weapon_burst( iWeaponEnt, arrBoolData[idUser][PB_FAMAS_BURST] );
	}

	iWeaponEnt = find_ent_by_owner( -1, "weapon_glock18", idUser );
	if ( is_valid_ent( iWeaponEnt ) )
	{
		cs_set_weapon_burst( iWeaponEnt, arrBoolData[idUser][PB_GLOCK_BURST] );
	}
}

public SHARED_SaveWeapons( idUser )
{
	if ( !is_user_alive( idUser ) )
		return;

	// Clear Array
	for( new i = 0; i < 32; i++ )
		g_PlayerWeapons[idUser][i] = 0;

	new num = 0;
	get_user_weapons( idUser, g_PlayerWeapons[idUser], num );
	
	return;
}

// Copy the weapons over right before reset hud is called, that way we don't lose our last round weapons when the round restarts
public SHARED_CopySavedWeapons( idUser )
{
	for ( new i = 0; i < 33; i++ )
	{
		for ( new j = 0; j < 32; j++ )
		{
			g_PlayerLastWeapons[i][j] = g_PlayerWeapons[i][j];
		}
	}
}

// Sets the user's speed, should be called after freezetime, on weapon change and after a speed modifying skill has been called
public SHARED_SetSpeed(idUser)
{
	if ( idUser >= TASK_UNHOLYSPEED )
		idUser -= TASK_UNHOLYSPEED;

	if (!arrBoolData[idUser][PB_ISCONNECTED] )
		return;
	
	// We should NOT change the user's speed during freezetime
	if (g_freezeTime)
	{
		return;
	}
	// User is stunned, we shouldn't change their speed
	else if (arrBoolData[idUser][PB_STUNNED])
	{
		set_user_maxspeed(idUser, 1.0);
		return;
	}
	// User is hexed, they should be slowed
	else if (arrBoolData[idUser][PB_HEXED])
	{
		set_user_maxspeed( idUser, fShHexSpeed);
		return;
	}
	else if (arrBoolData[idUser][PB_FROST])
	{
		set_user_maxspeed( idUser, fAlFrostSpeed);
		return;
	}
	// User is slowed
	else if (arrBoolData[idUser][PB_SLOWED])
	{
		set_user_maxspeed( idUser, get_pcvar_float( CVAR_wc3_frost ) );
		return;
	}
	// Скорость для вип игрока
	else if (arrBoolData[idUser][PB_VIP_SPEED])
	{
		set_user_maxspeed(idUser, fSpeedValueVip);
		return;
	}
	
	new Float:fNewSpeed = 0.0;
	new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_UNHOLYAURA);
	
	// Unholy Aura bonus
	if (iSkillLevel > 0 && isDisabledSkillsOnMap(idUser,SKILL_UNHOLYAURA) == false)
		fNewSpeed = ArrayGetCell(arrUnholyAura,iSkillLevel-1)


	new iClip, iAmmo;
	new iWeapon = get_user_weapon(idUser, iClip, iAmmo);
	
	if(iWeapon == 0)
		return;

	//Скорость Бладсикера - Скил 1 уровня - Blood Rage - Ярость крови
	if (arrBoolData[idUser][PB_BLOODRAGE] && bIsUserRace(idUser,RACE_BLOODSEEKER))
		fNewSpeed = CS_WEAPON_SPEED[iWeapon] * fBloodRageSpeedFactor;


	//Скорость Снайпера - Скил 2 уровня - Phase Boots  - Фазовый ускоритель
	if (bIsUserRace(idUser,RACE_SNIPER))
	{
		new Float:fNewSpeedSniper = 0.0;
		if(clSniper::skillPhaseBoots(idUser,iWeapon,fNewSpeedSniper))
			fNewSpeed = fNewSpeedSniper;
	}

	// Boots of Speed bonus
	if ( ITEM_Has( idUser, ITEM_BOOTS ) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_BOOTS)
	{
		new iClip, iAmmo;
		new iWeapon = get_user_weapon( idUser, iClip, iAmmo );
		
		if(iWeapon == 0)
			return;

		// Then just apply the bonus!
		if ( fNewSpeed > 0.0 )
			fNewSpeed *= ( 1.0 + get_pcvar_float( CVAR_wc3_boots ) );
		// User only has boots
		else
		{
			// Give them the bonus
			if (g_iPlayerRole[idUser] == PLR_VIP)
				fNewSpeed = CS_SPEED_VIP * ( 1.0 + get_pcvar_float( CVAR_wc3_boots ) );
			// Player zoomed in
			else if ( g_bPlayerZoomed[idUser] )
				fNewSpeed = CS_WEAPON_SPEED_ZOOM[iWeapon] * ( 1.0 + get_pcvar_float( CVAR_wc3_boots ) );
			// Regular
			else
				fNewSpeed = CS_WEAPON_SPEED[iWeapon] * ( 1.0 + get_pcvar_float( CVAR_wc3_boots ) );
		}

	}//ITEM_Has(idUser, ITEM_BOOTS)
		
	// Change the user's speed!
	//Установка нового значения скорости
	if (fNewSpeed > 0.0)
	{
		//if(!(get_user_flags(idUser) & ADMIN_LEVEL_H)) 
			set_user_maxspeed(idUser,fNewSpeed);
		//else
		//	set_user_maxspeed( idUser, 1000.0 );
		//client_print(0,print_chat,"Speed: %f",fNewSpeed);
		//client_print(0,print_chat,"Speed: %f",get_user_maxspeed(idUser));
		return;
	}

	//Сброс скорости если у игрока нет способностей или предметов (либо если они были)
	// Here we want to reset the user's speed
	if (g_iPlayerRole[idUser] == PLR_VIP )
		set_user_maxspeed( idUser, CS_SPEED_VIP );//Скорость если игрок VIP (на самой карте где спасти VIP) 
	else if ( g_bPlayerZoomed[idUser] )
		set_user_maxspeed( idUser, CS_WEAPON_SPEED_ZOOM[iWeapon] );//Скорость с прицелом
	else
		set_user_maxspeed( idUser, CS_WEAPON_SPEED[iWeapon]);//Скорость с текущим оружием

	return;
}

public SHARED_ResetMaxSpeed(idUser)
{

	if (idUser >= TASK_RESETSPEED )
		idUser -= TASK_RESETSPEED;

	if (!arrBoolData[idUser][PB_ISCONNECTED] )
		return;
	
	// User should no longer be stunned
	arrBoolData[idUser][PB_STUNNED] = false;

	// User should no longer be slowed
	arrBoolData[idUser][PB_SLOWED]	= false;

	arrBoolData[idUser][PB_FROST] = false;

	arrBoolData[idUser][PB_BLOODRAGE] = false;

	SHARED_SetSpeed(idUser);

	return;
}

// Returns true if the user is hexed/stunned/slowed
SHARED_IsPlayerSlowed( idUser )
{
	if ( arrBoolData[idUser][PB_STUNNED] || arrBoolData[idUser][PB_SLOWED] )
	{
		return true;
	}

	return false;
}

// Function changes your skin for ITEM_MOLE and Chameleon
public SHARED_ChangeSkin(idUser, iFlag)
{
	if(sm4_IsPlayerSkeleton(idUser) == false)
	{
		ExecuteForward(mfChangeSkin, mfChangeSkinReturn,idUser,iFlag);

		if(mfChangeSkinReturn == 975647)
			return;
	}

	new szSkin[32];
	
	// Reset the user's model
	if ( iFlag == SKIN_RESET && arrBoolData[idUser][PB_SKINSWITCHED] )
	{
		cs_reset_user_model(idUser);
		
		arrBoolData[idUser][PB_SKINSWITCHED] = false;
	}
	
	// Switch the user's skin to the opposing team
	else if ( iFlag == SKIN_SWITCH )
	{
		new iTeam = get_user_team( idUser );
		
		new iModelNum = random_num( 0, 3 );
		
		// Save which skin we're going to use
		if ( iTeam == TEAM_CT )
			add( szSkin, 31, SKIN_T[iModelNum] );
		else
			add( szSkin, 31, SKIN_CT[iModelNum] );
		
		cs_set_user_model( idUser, szSkin );

		if (cs_get_user_defuse(idUser))
			entity_set_int(idUser, EV_INT_body, 0);

		arrBoolData[idUser][PB_SKINSWITCHED] = true;
	}
	

	return;
}

public SHARED_SetGravity( idUser )
{

	// Can't set gravity if user isn't connected!
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}
	
	// If gravity is less than this, lets not change per-user b/c it BLOWS ASS in game
	if ( CVAR_sv_gravity == 0 || get_pcvar_num( CVAR_sv_gravity ) > 650 )
	{
		static iSkillLevel;
		iSkillLevel = arrBoolData[idUser][PB_HEXED] ? 0 : SM_GetSkillLevel( idUser, SKILL_LEVITATION );

		new Float:fGravityLevel = 1.0;

		// If this user does want their gravity to be changed!
		if ( ( iSkillLevel > 0 ) && g_bLevitation[idUser] && !arrBoolData[idUser][PB_HEXED] )
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_LEVITATION) == false)
				fGravityLevel = ArrayGetCell(arrLevitation,iSkillLevel-1);
		}

		//Для talisman +
		// Set the user's gravity based on the item
		if ( ITEM_Has( idUser, ITEM_SOCK ) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser] == TALISMAN_ITEM_SOCK))
		{
			
			// User has levitation + sock, give them an extra bonus
			if ( fGravityLevel < 1.0 )
			{
				fGravityLevel /= 2.0;

			}
			// User just has sock
			else
			{
				fGravityLevel = get_pcvar_float( CVAR_wc3_sock );
			}
		}

		// Гравитация для вип игрока
		if (arrBoolData[idUser][PB_VIP_GRAVITY])
			fGravityLevel = fGravityValueVip;
		
		// Set the user's gravity!
		set_user_gravity( idUser, fGravityLevel );
	}

	return;
}

public SHARED_IsOnTeam( idUser )
{
	new iTeam = get_user_team( idUser );

	if ( iTeam == CTS || iTeam == TS )
	{
		return true;
	}

	return false;
}

// Reset our reserved spawn points
public _SHARED_SpawnReset()
{
	new i;
	
	g_iSpawnInc = 0;
	for ( i = 0; i < TOTAL_SPAWNS; i++ )
	{
		g_iSpawnReserved[i] = 0;
	}
}

// Determine if this entity is reserved for another player
bool:SHARED_SpawnReserved( ent )
{
	new i;

	for ( i = 0; i < g_iSpawnInc; i++ )
	{
		if ( g_iSpawnReserved[i] == ent )
		{
			return true;
		}
	}

	return false;
}

// Find a free spawn!
SHARED_FindFreeSpawn( idUser, bImmunityCheck = false, bReverseTeam = false )
{

	new iPlayersInVicinity, iSpawnID, iEntList[1], vOrigin[3], iNearbyPlayer;
	new ent = -1;
	new Float:fSpawnOrigin[3];
	new Float:fVicinity = 96.0;
	new bool:bFound = false;
	new bool:bImmunityNear = false;
	
	new iTeam = get_user_team( idUser );

	// Reverse the team IDs (i.e. Mole would want this)
	if ( bReverseTeam )
		iTeam = ( ( iTeam == TEAM_CT ) ? TEAM_T : TEAM_CT );

		iSpawnID = ( ( iTeam == TEAM_CT ) ? 0 : 1 );
	
	// Loop through each ent until we find a spawn entity that we want
	do {
		ent = find_ent_by_class( ent, szSpawnEnt[iSpawnID] );
		
		// Valid ent found
		if ( ent != 0 )
		{
			entity_get_vector( ent, EV_VEC_origin, fSpawnOrigin );
			
			// Convert float vector to int vector
			FVecIVec( fSpawnOrigin, vOrigin );

			// Check to see if there are players in this spawn
			iPlayersInVicinity = find_sphere_class( 0, "player", fVicinity, iEntList, 1, fSpawnOrigin );
			
			// We have a free spawn!!
			if ( iPlayersInVicinity == 0 )
			{

				// Make sure it isn't reserved
				if ( !SHARED_SpawnReserved( ent ) )
				{

					// Then we need to reserve it :)
					g_iSpawnReserved[g_iSpawnInc++] = ent;

					// We need to make sure there isn't anyone nearby that is immune
					if ( bImmunityCheck )
					{
						iNearbyPlayer = WC3_IsImmunePlayerNear( idUser, vOrigin );

						// Immune found
						if ( iNearbyPlayer > 0 )
						{
							ULT_RemoveCharge(iNearbyPlayer);

							bImmunityNear = true;
						}

						// We're clear!
						else
						{
							bImmunityNear = false;
							bFound = true;
						}
					}
					
					// We have a free spawn we can quit!
					else
					{
						bFound = true;
					}
				}
			}
		}
	}
	while ( ent && !bFound && !bImmunityNear )
	
	// Reset the spawn points...
	if ( !task_exists( TASK_RESETSPAWNS ) )
	{
		set_task( 0.3, "_SHARED_SpawnReset", TASK_RESETSPAWNS );
	}

	// Failed, nothing found
	if ( !bFound )
	{
		// Return a different value so they know the reason for failing
		if ( bImmunityCheck && bImmunityNear )
		{
			return -2;
		}

		return -1;
	}
	

	// Otherwise we found something!
	return ent;
}
/*
//-------------------- Test {

//Вызов отображения меню для отображения вопроса о перемещении
fShowMenuFanOfKnives(idUser, iPage = 0)
{
	new idMenu,szMenuData[256];
	
	//Название главного меню
	formatex(szMenuData, charsmax(szMenuData), "\y%L", LANG_PLAYER, "MENU_ID_FAN_OF_KNIVES");
	idMenu = menu_create(szMenuData, "_Callback_MENU_FanOfKnives");

	formatex(szMessage, charsmax(szMessage),"%L",LANG_PLAYER, "MENU_ID_FAN_OF_KNIVES_1");
	menu_additem(idMenu,szMessage,"1",0,-1);

	formatex(szMessage, charsmax(szMessage),"%L",LANG_PLAYER, "MENU_ID_FAN_OF_KNIVES_2");
	menu_additem(idMenu,szMessage,"2",0,-1);

	// Если нет пунктов в меню
	if (menu_items(idMenu) <= 0)
	{
		menu_destroy(idMenu);
		return;
	}
			
	//Пункты меню (назад - следующий - выход)
	formatex(szMenuData, charsmax(szMenuData), "\r%L", LANG_PLAYER, "WC3_MENU_EXIT");
	menu_setprop(idMenu, MPROP_EXITNAME, szMenuData);
	
	menu_display(idUser, idMenu, iPage);
}

//Функция выбора пунктов в под меню Добавления предметов
public _Callback_MENU_FanOfKnives(idUser, idMenu, idItem)
{
	// Возврат в главное меню
	if (idItem == MENU_EXIT)
	{
		menu_destroy(idMenu);

		bOnOffTeleport[idUser] = false;

		return PLUGIN_HANDLED;
	}
	
	static _access, szInfoMenu[8], callback;
	menu_item_getinfo(idMenu, idItem, _access, szInfoMenu, sizeof(szInfoMenu) - 1, _, _, callback);
	
	new iNumberItem = str_to_num(szInfoMenu);
	
	switch(iNumberItem)
	{
		case 1:
			{
				bOnOffTeleport[idUser] = true;
			}
		case 2:
			{
				bOnOffTeleport[idUser] = false;
			}

	}
	

	menu_destroy(idMenu);

	//client_print(0,print_chat,"iNumberItem: %d |idItem: %d",iNumberItem,idItem);	

	return PLUGIN_HANDLED;
}

//-------------------- Test }
*/

SHARED_MoleCheck(idUser, bItemOnly = false )
{
	new parm[2];
	parm[1] = 0;
/*
	if(bOnOffTeleport[idUser] == true)
	{
		parm[1] = 1;
		bOnOffTeleport[idUser] = false;
	}*/

	// Only do a skill check if bItemOnly is false - Условие если срабатывает скилл
	if (!bItemOnly)
	{
		static iSkillLevel;
		iSkillLevel = SM_GetSkillLevel(idUser, SKILL_FANOFKNIVES );

		if (iSkillLevel > 0 && isDisabledSkillsOnMap(idUser,SKILL_FANOFKNIVES) == false)
		{
			new Float:fFan = ArrayGetCell(arrFanOfKnives,iSkillLevel-1);
			if (random_float(fWardenSkill1MinPercent,fWardenSkill1MaxPercent) <= fFan )
			{
				if(bNomole[idUser] == false)// Если блокировка выключена
					parm[1] = 1;

				//fShowMenuFanOfKnives(idUser);
			}
		}
	}
	
	// Mole from an item? - Имеется предмет
	if ( parm[1] == 0 )
	{
		if ( g_bPlayerBoughtMole[idUser] )
		{
			parm[1] = 2;
			
			ITEM_RemoveID(idUser, ITEM_MOLE);
			g_bPlayerBoughtMole[idUser] = false;
		}
	}

	// OK then lets mole!!
	if ( parm[1] > 0 )
	{
		parm[0] = idUser;
		
		set_task( 0.1, "_SHARED_Mole", TASK_MOLE + idUser, parm, 2 );
	}
}

public _SHARED_Mole( parm[2] )
{
	
	new idUser = parm[0];

	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}

	// Lets search for a new spawn (ignore immunity, reverse team ids)	
	new ent = SHARED_FindFreeSpawn( idUser, false, true );
	
	// Free spawn found!!
	if ( ent > 0 )
	{
		new vOrigin[3], Float:fSpawnOrigin[3];
		
		// Set the right angels
		entity_get_vector( ent, EV_VEC_angles, fSpawnOrigin );
		entity_set_vector( idUser, EV_VEC_angles, fSpawnOrigin );
		entity_set_int( idUser, EV_INT_fixangle, 1 );
		
		// Get the origin of the spawn
		entity_get_vector( ent, EV_VEC_origin, fSpawnOrigin );
		
		// Convert float vector to int vector
		FVecIVec( fSpawnOrigin, vOrigin );
		
		// Change the user's skin
		SHARED_ChangeSkin( idUser, SKIN_SWITCH );
		
		// Move the user
		set_user_origin( idUser, vOrigin );

		// Shake the user's screen
		Create_ScreenShake( idUser, (255<< 14), (10 << 14), (255<< 14) );
		
		// User is a mole
		arrBoolData[idUser][PB_MOLE] = true;

	}

	// No spawn found
	else
	{
		// Moving b/c of item - if no spot then give the user his/her money back!
		if ( parm[1] == 2 )
		{
			SHARED_SetUserMoney( idUser, SHARED_GetUserMoney( idUser ) + ITEM_Cost( idUser, ITEM_MOLE ), 1 );
		
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"NO_SPOT_MOLE_MONEY");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			
		}

		// Moving b/c of skill
		else
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"NO_SPOT_TO_MOLE");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}

	return; 
} 

bool:SHARED_ValidPlayer( idUser )
{
	if ( idUser < 1 || idUser > MAXPLAYERS )
	{
		return false;
	}

	return true;
}

#define MAXGLOW					150

SHARED_Glow( idUser, iRed, iGreen, iBlue, iAll )
{
	
	// Not allowed to glow right now...
	if ( !arrBoolData[idUser][PB_CAN_RENDER] )
		return;
			
	// Don't glow if invisible
	else if ( SM_GetSkillLevel( idUser, SKILL_INVISIBILITY ) > 0 || 
			  ITEM_Has( idUser, ITEM_CLOAK ) > ITEM_NONE ||
			  bIsActiveTalisman(idUser,TALISMAN_ITEM_CLOAK) // Для talisman +
			 )
	{
		return;
	}

	// Only glow if the task doesn't exist!
	else if ( task_exists( TASK_GLOW + idUser ) )
	{
		return;
	}
	
	if ( iAll )
	{
		g_GlowLevel[idUser][0]	= 0;
		g_GlowLevel[idUser][1]	= 0;
		g_GlowLevel[idUser][2]	= 0;
		g_GlowLevel[idUser][3]	+= iAll;
	}
	else if ( iRed )
	{
		g_GlowLevel[idUser][0]	+= iRed;
		g_GlowLevel[idUser][1]	= 0;
		g_GlowLevel[idUser][2]	= 0;
		g_GlowLevel[idUser][3]	= 0;
	}
	else if ( iGreen )
	{
		g_GlowLevel[idUser][0]	= 0;
		g_GlowLevel[idUser][1]	+= iGreen;
		g_GlowLevel[idUser][2]	= 0;
		g_GlowLevel[idUser][3]	= 0;
	}
	else if ( iBlue )
	{
		g_GlowLevel[idUser][0]	= 0;
		g_GlowLevel[idUser][1]	= 0;
		g_GlowLevel[idUser][2]	+= iBlue;
		g_GlowLevel[idUser][3]	= 0;
	}

	// Lets make sure its not over the max!
	g_GlowLevel[idUser][0] = ( ( g_GlowLevel[idUser][0] > MAXGLOW ) ? MAXGLOW : g_GlowLevel[idUser][0] );
	g_GlowLevel[idUser][1] = ( ( g_GlowLevel[idUser][1] > MAXGLOW ) ? MAXGLOW : g_GlowLevel[idUser][1] );
	g_GlowLevel[idUser][2] = ( ( g_GlowLevel[idUser][2] > MAXGLOW ) ? MAXGLOW : g_GlowLevel[idUser][2] );
	g_GlowLevel[idUser][3] = ( ( g_GlowLevel[idUser][3] > MAXGLOW ) ? MAXGLOW : g_GlowLevel[idUser][3] );
	

	_SHARED_Glow( idUser );
}

public _SHARED_Glow( idUser )
{
	
	if ( idUser >= TASK_GLOW )
	{
		idUser -= TASK_GLOW;
	}

	// User is no longer connected, so lets not continue this!
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}
	
	new iRed	= g_GlowLevel[idUser][0];
	new iGreen	= g_GlowLevel[idUser][1];
	new iBlue	= g_GlowLevel[idUser][2];
	new iAll	= g_GlowLevel[idUser][3];

	// Then we want to glow
	if ( iRed || iGreen || iBlue )
	{

		g_GlowLevel[idUser][0] = ( ( iRed > 5 )		? iRed - 5		: 0 );
		g_GlowLevel[idUser][1] = ( ( iGreen > 5 )	? iGreen - 5	: 0 );
		g_GlowLevel[idUser][2] = ( ( iBlue > 5 )	? iBlue - 5		: 0 );

		set_user_rendering( idUser, kRenderFxGlowShell, iRed, iGreen, iBlue, kRenderNormal, 16 );
	}

	else if ( iAll )
	{
		g_GlowLevel[idUser][3] = ( ( iAll > 5 )		? iAll - 5		: 0 );
		
		set_user_rendering( idUser, kRenderFxGlowShell, iAll, iAll, iAll, kRenderNormal, 16 );
	}

	// No more glowing!
	else
	{
		set_user_rendering( idUser );

		return;
	}

	set_task( 0.2, "_SHARED_Glow", TASK_GLOW + idUser );

	return;
}

// Returns if an origin is near an objective (returns which objective)
SHARED_NearObjective( vOrigin[3] )
{

	new i, Float:fOrigin[3];
	
	// Convert vector to float
	IVecFVec( vOrigin, fOrigin );

	// Check the distances
	for ( i = 0; i < g_iTotalObjectiveEnts; i++ )
	{
		new Float:fDistance = vector_distance( fOrigin, g_fObjectiveOrigin[i] );

		if ( fDistance < 250.0 )
		{
			return g_iObjectiveEntType[i];
		}
	}

	return -1;
}

stock SHARED_ForceWeaponChange( idUser )
{
	new iAmmo, iClip, szWeaponName[32], i;
	new num = 0, iWeapons[32];

	new iCurWeapon = get_user_weapon( idUser, iAmmo, iClip );

	// We need a valid current weapon to do this!
	if ( iCurWeapon != 0 )
	{
		// Get all weapons the user is holding
		get_user_weapons( idUser, iWeapons, num );

		// Loop through all weapons
		for ( i = 0; i < num; i++ )
		{
			
			// Find a weapon the player isn't currently holding
			if ( iWeapons[i] != iCurWeapon && iWeapons[i] > 0 )
			{
				get_weaponname( iWeapons[i], szWeaponName, 31 );

				client_cmd( idUser, szWeaponName );

				break;
			}
		}

		// Switch back to the user's current weapon
		get_weaponname( iCurWeapon, szWeaponName, 31 );
		client_cmd( idUser, szWeaponName );
	}

	return;
}

// This will teleport a user to a location and test to make sure they were actually moved there
SHARED_Teleport( idUser, vOrigin[3] )
{
	// Increase so user doesn't get stuck in ground
	vOrigin[2] += 15;

	// Attempt to move the user
	set_user_origin( idUser, vOrigin );

	new iParm[4];
	iParm[0] = vOrigin[0];
	iParm[1] = vOrigin[1];
	iParm[2] = vOrigin[2];
	iParm[3] = idUser;

	// Set up the parameters
	set_task( 0.1, "_SHARED_Teleport", TASK_TELEPORT + idUser, iParm, 4 );
}

public _SHARED_Teleport( parm[] )
{
	new idUser = parm[3];
	new vOrigin[3];
	
	get_user_origin( idUser, vOrigin );


	// User is stuck, lets teleport them back to their spawn
	if ( vOrigin[2] == parm[2] )
	{
		// Find a spawn - ignore immunity and team reversal
		new iSpawnEnt = SHARED_FindFreeSpawn( idUser, false, false );
		
		// We can move the user yay!
		if ( iSpawnEnt > 0 )
		{
			new Float:fSpawnOrigin[3], vOrigin[3];
			
			// Get the origin of the spawn point
			entity_get_vector( iSpawnEnt, EV_VEC_origin, fSpawnOrigin );

			// Convert float vector to int vector
			FVecIVec( fSpawnOrigin, vOrigin );
			
			// Move the user
			SHARED_Teleport( idUser, vOrigin );
			
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SHARED_TELEPORT_0");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			
		}
		// We can't move the user - that sux0rsz
		else
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_SHARED_TELEPORT_1");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
}

//Подсветка игрока нужным цветом
SHARED_GlowShell(idUser, iRed, iGreen, iBlue,Float:fTime,iAmountGlow = 16)
{
	if (!arrBoolData[idUser][PB_CAN_RENDER] || !arrBoolData[idUser][PB_ISCONNECTED] )
		return;
		
	// Подсветка не будет работать если есть скил Невидимость
	else if (SM_GetSkillLevel( idUser, SKILL_INVISIBILITY ) > 0 || 
			 ITEM_Has( idUser, ITEM_CLOAK ) > ITEM_NONE ||
			 bIsActiveTalisman(idUser,TALISMAN_ITEM_CLOAK)//Для talisman
			 )
	{
		return;
	}

	// Only glow if the task doesn't exist!
	else if ( task_exists( TASK_GLOW_SHELL + idUser ) )
		return;
		
	//set_user_rendering(idUser, kRenderFxGlowShell,iRed,iGreen,iBlue, kRenderNormal, 16 );
	set_user_rendering(idUser, kRenderFxGlowShell,iRed,iGreen,iBlue, kRenderNormal, iAmountGlow );

	set_task(fTime, "SHARED_GlowShell_OFF", TASK_GLOW_SHELL + idUser );
}
//Выключение подсветки игрока
public SHARED_GlowShell_OFF( idUser )
{
	if ( idUser >= TASK_GLOW_SHELL )
		idUser -= TASK_GLOW_SHELL;

	// User is no longer connected, so lets not continue this!
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return;
	
	// No more glowing!
	set_user_rendering( idUser );

	return;
}