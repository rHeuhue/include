/*
*	UTIL Functions - Basically helper functions
*/

UTIL_GetWeaponName( iWeapon, szWpnName[], len )
{

	// Counter-Strike and Condition Zero Weapons
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		switch ( iWeapon )
		{
			case CSW_KNIFE:			copy( szWpnName, len, "knife"		);

			case CSW_USP:           copy( szWpnName, len, "usp"			);
			case CSW_GLOCK18:       copy( szWpnName, len, "glock18"		);
			case CSW_DEAGLE:        copy( szWpnName, len, "deagle"		);
			case CSW_P228:          copy( szWpnName, len, "p228"		);
			case CSW_ELITE:         copy( szWpnName, len, "elite"		);
			case CSW_FIVESEVEN:     copy( szWpnName, len, "fiveseven"	);

			case CSW_M3:            copy( szWpnName, len, "m3"			);
			case CSW_XM1014:        copy( szWpnName, len, "xm1014"		);

			case CSW_MP5NAVY:       copy( szWpnName, len, "mp5navy"		);
			case CSW_TMP:           copy( szWpnName, len, "tmp"			);
			case CSW_P90:           copy( szWpnName, len, "p90"			);
			case CSW_MAC10:         copy( szWpnName, len, "mac10"		);
			case CSW_UMP45:         copy( szWpnName, len, "ump45"		);

			case CSW_AK47:          copy( szWpnName, len, "ak47"		);
			case CSW_SG552:         copy( szWpnName, len, "sg552"		);
			case CSW_M4A1:          copy( szWpnName, len, "m4a1"		);
			case CSW_AUG:           copy( szWpnName, len, "aug"			);
			case CSW_SCOUT:         copy( szWpnName, len, "scout"		);
			case CSW_AWP:           copy( szWpnName, len, "awp"			);
			case CSW_SG550:         copy( szWpnName, len, "sg550"		);
			case CSW_G3SG1:         copy( szWpnName, len, "g3sg1"		);

			case CSW_GALI:          copy( szWpnName, len, "galil"		);
			case CSW_FAMAS:         copy( szWpnName, len, "famas"		);

			case CSW_M249:          copy( szWpnName, len, "m249"		);

			case CSW_HEGRENADE:     copy( szWpnName, len, "grenade"		);
		}
	}

	

	// These are common to both
	switch ( iWeapon )
	{
		case CSW_WORLDSPAWN:    copy( szWpnName, len, "world"													);

		case CSW_LIGHTNING:      copy( szWpnName, len, "world"													);
		case CSW_SUICIDE:		 copy( szWpnName, len, "world"													);
		case CSW_IMMOLATE:		 copy( szWpnName, len, "world"													);
		case CSW_LOCUSTS:		 copy( szWpnName, len, "world"													);
		case CSW_SERPENTWARD:    copy( szWpnName, len, "world"													);
		case CSW_SHADOW:		 copy( szWpnName, len, "world"													);
		case CSW_THORNS:		 copy( szWpnName, len, "world"													);
		case CSW_CARAPACE:		 copy( szWpnName, len, "world"													);
		case CSW_CARRION:		 copy( szWpnName, len, "world"													);
		case CSW_ORB:			 copy( szWpnName, len, "world"													);
		case CSW_CONCOCTION:	 copy( szWpnName, len, "world"													);
		case CSW_BANISH:		 copy( szWpnName, len, "world"													);
	}
}

// Log the death of a user
UTIL_LogDeath( iVictim, iKiller, iWeapon )
{
	new szKillerName[32], szVictimName[32];
	new szKillerTeam[32], szVictimTeam[32];
	new szKillerAuth[32], szVictimAuth[32];
	new szWeaponName[32];

	new iKillerUserID = get_user_userid( iKiller );
	new iVictimUserID = get_user_userid( iVictim );

	UTIL_GetWeaponName( iWeapon, szWeaponName, 31 );

	get_user_name(		iKiller	, szKillerName	, 31 );
	get_user_name(		iVictim	, szVictimName	, 31 );
	get_user_team(		iKiller	, szKillerTeam	, 31 );
	get_user_team(		iVictim	, szVictimTeam	, 31 );
	get_user_authid(	iKiller	, szKillerAuth	, 31 );
	get_user_authid(	iVictim	, szVictimAuth	, 31 );

	log_message("^"%s<%d><%s><%s>^" killed ^"%s<%d><%s><%s>^" with ^"%s^"", szKillerName, iKillerUserID, szKillerAuth, szKillerTeam, szVictimName, iVictimUserID, szVictimAuth, szVictimTeam, szWeaponName );
}

stock UTIL_EntInView( id, iEnt )
{
	new Float:vPlayerOrigin[3];
	entity_get_vector( id, EV_VEC_origin, vPlayerOrigin );

	new Float:vEntOrigin[3];
	entity_get_vector( iEnt, EV_VEC_origin, vEntOrigin );

	new Float:vReturn[3];

	new iHitEnt = trace_line( id, vPlayerOrigin, vEntOrigin, vReturn );

	if ( iHitEnt == iEnt )
	{
		return 1;
	}
	
	return 0;
}

UTIL_ClearHudChannel( id, iChannel )
{
	set_hudmessage( 0, 0, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0, iChannel );
	show_hudmessage( id, "" );
}

UTIL_ShowOnRadar( id, iTarget, Float:fOrigin[ 3 ] )
{
	
	
	//Make a dot on players radar.
	message_begin( MSG_ONE_UNRELIABLE, g_iMsgIdHostagePos, .player = id );
	write_byte( id );
	write_byte( iTarget );
	engfunc( EngFunc_WriteCoord, fOrigin[ 0 ] );
	engfunc( EngFunc_WriteCoord, fOrigin[ 1 ] );
	engfunc( EngFunc_WriteCoord, fOrigin[ 2 ] );
	message_end( );
	
	//Make the dot red.
	message_begin( MSG_ONE_UNRELIABLE, g_iMsgIdHostageK, .player = id );
	write_byte( iTarget );
	message_end( );
	
}

stock UTIL_CanSeePlayer( id, iTargetID )
{
	new Float:vOrigin[3];
	entity_get_vector( iTargetID, EV_VEC_origin, vOrigin );

	return is_in_viewcone( id, vOrigin );
}