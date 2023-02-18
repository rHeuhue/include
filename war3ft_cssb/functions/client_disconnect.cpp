// ******************************************************************
// 
// ******************************************************************

public client_disconnect(idUser)
{
	if ( !WC3_Check() )
		return;

	if (task_exists(idUser + TASK_MODELCHANGE))
		remove_task(idUser + TASK_MODELCHANGE);

	flag_unset(iHasCustomModel, idUser);

	// Update the user's timestamps for each race if we're saving XP
	//Обновление времени когда игрок был на сервере в последний раз
	DB_UpdateTimestamp(idUser);

	if(bIsUserRace(idUser,RACE_JUGGERNAUT))
		uDeleteAllEntClassnameUser(HEALING_WARD_CLASSNAME,idUser);
			
	arrIntData[idUser][P_SPECMODE]			= 0;
	arrBoolData[idUser][PB_ISBURNING]		= false;
	arrBoolData[idUser][PB_DIEDLASTROUND]	= false;
	arrBoolData[idUser][PB_JUSTJOINED]		= false;
	arrBoolData[idUser][PB_ISCONNECTED]	= false;
	bIgnoreArmorSet[idUser]				= false;
	arrBoolData[idUser][PB_VIP_SPEED] = false;
	arrBoolData[idUser][PB_VIP_GRAVITY] = false;
	arrBoolData[idUser][PB_VIP_ACCESS] = false;

	clVIP:fResetItemsAccessVip(idUser);
	

	// Reset xp assist
	for (new i = 0; i < MAXPLAYERS; i++ )
		g_iDamageDealt[idUser][i] = 0;
	
	// Save the user's XP if we have XP to save
	if (!is_user_bot(idUser) && arrIntData[idUser][P_RACE] && arrIntData[idUser][P_XP] )
		DB_SaveXP( idUser, true );
	
	if ( get_pcvar_num( CVAR_wc3_psychostats ) )
	{
		static szWeapon[64];

		static szTeam[16], szName[32], szAuthid[32];
		new iWeap, iUserid = get_user_userid( idUser );

		if ( is_user_connected(idUser) )
		{
			get_user_team( idUser, szTeam, 15 );
		}
		get_user_name(idUser, szName, 31 );
		get_user_authid(idUser, szAuthid, 31 );

		for ( iWeap = CSW_WAR3_MIN; iWeap <=CSW_WAR3_MAX; iWeap++ )
		{
			format( szWeapon, 63, "" );

			switch( iWeap )
			{
				case CSW_LIGHTNING:     		LANG_GetSkillName( ULTIMATE_CHAINLIGHTNING	, LANG_SERVER,	szWeapon	, 63, 20 );
				case CSW_SUICIDE:			LANG_GetSkillName( ULTIMATE_SUICIDE			, LANG_SERVER,	szWeapon	, 63, 21 );
				case CSW_IMMOLATE:	    	LANG_GetSkillName( ULTIMATE_IMMOLATE		, LANG_SERVER,	szWeapon	, 63, 22 );
				case CSW_LOCUSTS:			LANG_GetSkillName( ULTIMATE_LOCUSTSWARM		, LANG_SERVER,	szWeapon	, 63, 23 );
				case CSW_SERPENTWARD:   		LANG_GetSkillName( SKILL_SERPENTWARD		, LANG_SERVER,	szWeapon	, 63, 24 );
				case CSW_SHADOW:				LANG_GetSkillName( SKILL_SHADOWSTRIKE		, LANG_SERVER,	szWeapon	, 63, 25 );
				case CSW_THORNS:				LANG_GetSkillName( SKILL_THORNS				, LANG_SERVER,	szWeapon	, 63, 26 );
				case CSW_CARAPACE:			LANG_GetSkillName( SKILL_SPIKEDCARAPACE		, LANG_SERVER,	szWeapon	, 63, 27 );
				case CSW_CARRION:			LANG_GetSkillName( SKILL_CARRIONBEETLES		, LANG_SERVER,	szWeapon	, 63, 28 );
				case CSW_ORB:				LANG_GetSkillName( PASS_ORB					, LANG_SERVER,	szWeapon	, 63, 29 );
				case CSW_CONCOCTION:			LANG_GetSkillName( PASS_UNSTABLECONCOCTION	, LANG_SERVER,	szWeapon	, 63, 30 );
				case CSW_BLIZZARD:			LANG_GetSkillName( ULTIMATE_FROST_MAGE_BLIZZARD,LANG_SERVER,szWeapon	, 63, 31 );
				case CSW_ICE_SPLINTERS:		LANG_GetSkillName( SKILL_FROST_MAGE_ICE_SPLINTERS,LANG_SERVER,szWeapon	, 63, 31 );
				case CSW_CHAM_FLAME_STRIKE:	LANG_GetSkillName( ULTIMATE_CHAM_FLAME_STRIKE,LANG_SERVER,szWeapon	, 63, 31 );
				case CSW_BLOODBOIL:			LANG_GetSkillName(SKILL_DEATH_KNIGHT_BLOOD_BOIL,LANG_SERVER,szWeapon, 63, 31 );
				case CSW_BLACKPOWER:			LANG_GetSkillName(SKILL_BLACKSTRIKE,LANG_SERVER,szWeapon, 63, 31 );
				case CSW_POISON:				LANG_GetSkillName( SKILL_POISON	, LANG_SERVER,	szWeapon	, 63, 31 );	
				case CSW_RADIATION:			LANG_GetSkillName( ULTIMATE_RADIATION	, LANG_SERVER,	szWeapon	, 63, 31 );	
				case CSW_WORDDEATH:			LANG_GetSkillName( ULTIMATE_PRIEST_DARKNESS_WORD_DEATH, LANG_SERVER,	szWeapon	, 63, 31 );	
				case CSW_BLOOD_RAGE:			LANG_GetSkillName( SKILL_BLOODSEEKER_1, LANG_SERVER,	szWeapon	, 63, 31 );	
				case CSW_HEADSHOT:			LANG_GetSkillName( SKILL_SNIPER_1, LANG_SERVER,	szWeapon	, 63, 31 );	
				case CSW_SHRAPNEL:			LANG_GetSkillName( SKILL_SNIPER_1, LANG_SERVER,	szWeapon	, 63, 31 );	
							
				
			}
			
			replace( szWeapon, 63, " ", "_" );

			new WEAPON = iWeap - CSW_WAR3_MIN;
			
			if ( iStatsShots[idUser][WEAPON] || iStatsHits[idUser][WEAPON] || iStatsKills[idUser][WEAPON] ||
			iStatsHS[idUser][WEAPON] || iStatsTKS[idUser][WEAPON] || iStatsDamage[idUser][WEAPON] ||
			iStatsDeaths[idUser][WEAPON] || iStatsHead[idUser][WEAPON] ||
			iStatsChest[idUser][WEAPON] || iStatsStomach[idUser][WEAPON] || 
			iStatsLeftArm[idUser][WEAPON] || iStatsRightArm[idUser][WEAPON] || 
			iStatsLeftLeg[idUser][WEAPON] || iStatsRightLeg[idUser][WEAPON] )
			{

				log_message("^"%s<%d><%s><%s>^" triggered ^"weaponstats^" (weapon ^"%s^") (shots ^"%d^") (hits ^"%d^") \ 
							(kills ^"%d^") (headshots ^"%d^") (tks ^"%d^") (damage ^"%d^")(deaths ^"%d^")", 
							szName, iUserid, szAuthid, szTeam, szWeapon, 
							iStatsShots[idUser][WEAPON], iStatsHits[idUser][WEAPON], iStatsKills[idUser][WEAPON], iStatsHS[idUser][WEAPON], 
							iStatsTKS[idUser][WEAPON], iStatsDamage[idUser][WEAPON], iStatsDeaths[idUser][WEAPON] );
				
				log_message("^"%s<%d><%s><%s>^" triggered ^"weaponstats2^" (weapon ^"%s^") (head ^"%d^") \
				(chest ^"%d^") (stomach ^"%d^") (leftarm ^"%d^") (rightarm ^"%d^") (leftleg ^"%d^") (rightleg ^"%d^")", 
				szName, iUserid, szAuthid, szTeam, szWeapon, 
				iStatsHead[idUser][WEAPON], iStatsChest[idUser][WEAPON], iStatsStomach[idUser][WEAPON],
				iStatsLeftArm[idUser][WEAPON], iStatsRightArm[idUser][WEAPON], iStatsLeftLeg[idUser][WEAPON],
				iStatsRightLeg[idUser][WEAPON] );
			
				iStatsShots[idUser][WEAPON]		= 0;
				iStatsHits[idUser][WEAPON]		= 0;
				iStatsKills[idUser][WEAPON]		= 0;
				iStatsHS[idUser][WEAPON]		= 0;
				iStatsTKS[idUser][WEAPON]		= 0;
				iStatsDamage[idUser][WEAPON]	= 0;
				iStatsDeaths[idUser][WEAPON]	= 0;
				iStatsHead[idUser][WEAPON]		= 0;
				iStatsChest[idUser][WEAPON]		= 0;
				iStatsStomach[idUser][WEAPON]	= 0;
				iStatsLeftArm[idUser][WEAPON]	= 0;
				iStatsRightArm[idUser][WEAPON]	= 0;
				iStatsLeftLeg[idUser][WEAPON]	= 0;
				iStatsRightLeg[idUser][WEAPON]	= 0;
			}
		}
	}
	
	if ( is_user_connected(idUser))
		sm4_ClientDisconnect(idUser);
	
	
	
}