/*
*	Race: Crypt Lord Functions
*/

// Returns victim idUser
//  -1 if no target
//  -2 if ult blocked
CL_ULT_LocustGetTarget( idUser )
{
	new iTeam = get_user_team( idUser );

	// First thing we need to do is find an alive player that isn't immune to target :)
	new players[32], numberofplayers, i, iTargetID;
	new iTargets[33], iTotalTargets = 0;

	get_players( players, numberofplayers, "a" );

	for ( i = 0; i < numberofplayers; i++ )
	{
		iTargetID = players[i];

		if ( get_user_team( iTargetID ) != iTeam )
		{
			iTargets[iTotalTargets++] = iTargetID;
		}
	}
	
	// No victims found
	if ( iTotalTargets == 0 )
	{
		return -1;
	}

	// Lets find ourselves a victim
	new idVictim = 0, iRandomSpot;
	while ( idVictim == 0 )
	{
		iRandomSpot = random_num( 0, iTotalTargets );

		idVictim = iTargets[iRandomSpot];
	}

	// Then the user's ultimate was blocked :/
	if ( ULT_CanUserBlockUlt( idVictim,idUser ) )
	{
		ULT_RemoveCharge(idVictim);
		ULT_Blocked( idUser );

		// Reset the user's ultimate
		fResetUltimateTimerDivider(idUser);

		return -2;
	}

	return idVictim;
}

CL_ULT_LocustSwarm( idAttacker )
{
	new idVictim = CL_ULT_LocustGetTarget( idAttacker );

// No target was found :/
	if ( idVictim == -1 )
	{
		//set_hudmessage( 178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, -1 );
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_CL_ULT_LOCUST_EFFECT_1");
		WC3_StatusText( idAttacker, TXT_BLINK_CENTER,szMessage);
		
		return;
	}

	// Ultimate was blocked - do nothing
	if ( idVictim == -2 )
	{
		return;
	}
		
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

			ULT_Icon( idAttacker, ICON_HIDE );

			// Reset the cooldown
			fResetUltimateTimerDivider(idAttacker,0,false);

			return;
		}

		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MIRROR_ULT");
		cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);

		sm4_EffectMirrorUltimate(idVictim);

		// Lets get the origin of the idAttacker
		new vCasterOrigin[3];
		get_user_origin( idAttacker, vCasterOrigin );
		
		ULT_Icon( idAttacker, ICON_HIDE );

		new parm[10];
		parm[0] = idVictim;	// Attacker
		parm[1] = idAttacker;	// Victim
		parm[2] = vCasterOrigin[0];
		parm[3] = vCasterOrigin[1];
		parm[4] = vCasterOrigin[2];
		parm[5] = 1;

		// Reset the cooldown
		fResetUltimateTimerDivider(idAttacker,0,false);

		// Start the effects!!
		_CL_ULT_LocustEffect( parm );

		ITEM_RemoveCharge(idVictim, ITEM_MIRROR_ULTIMATE );
	}
	else
	{
		// Lets get the origin of the idAttacker
		new vCasterOrigin[3];
		get_user_origin( idAttacker, vCasterOrigin );
		
		// Flash their ultimate!
		ULT_Icon( idAttacker, ICON_FLASH );

		new parm[10];
		parm[0] = idAttacker;		// idAttacker
		parm[1] = idVictim;	// victim
		parm[2] = vCasterOrigin[0];
		parm[3] = vCasterOrigin[1];
		parm[4] = vCasterOrigin[2];
		parm[5] = 0;

		// Reset the cooldown
		fResetUltimateTimerDivider(idAttacker,0,false);

		// Start the effects!!
		_CL_ULT_LocustEffect( parm );
	}

	return;
}

public _CL_ULT_LocustEffect( parm[] )
{
	new idAttacker	= parm[0];
	new idVictim		= parm[1];

	if ( !is_user_alive( idVictim ) || !arrBoolData[idVictim][PB_ISCONNECTED] )
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_CL_ULT_LOCUST_EFFECT_0");	
		cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);

		// Need to find a new victim here...
		//new idVictim = CL_ULT_LocustGetTarget( idAttacker );

		// No target was found :/
		if ( idVictim == -1 )
		{
			//set_hudmessage( 178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, -1 );
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_CL_ULT_LOCUST_EFFECT_1");
			WC3_StatusText( idAttacker, TXT_BLINK_CENTER,szMessage);
		
			// Set ultimate timer back to 0
			arrIntData[idAttacker][P_ULTIMATEDELAY] = 0;

			// Show icon + play ultimate ready sound
			ULT_IconHandler( idAttacker );

			return;
		}

		// Ultimate was blocked - do nothing
		else if ( idVictim == -2 )
		{
			ULT_Icon( idAttacker, ICON_HIDE );

			return;
		}

	}

	new MULTIPLIER = 150 // the lower the number the faster it reaches the target

	new vVictimOrigin[3], vFunnel[3];
	get_user_origin( idVictim, vVictimOrigin );

	// Origin of the funnel
	vFunnel[0] = parm[2];
	vFunnel[1] = parm[3];
	vFunnel[2] = parm[4];
	
	// Draw a funnel
	Create_TE_LARGEFUNNEL( vFunnel, arrIdSprites[SPR_SNOW], 0 );
	
	// Now we need to calculate where the next funnel will be drawn
	new vDist[3];
	vDist[XPOS] = CL_HLP_Diff( vVictimOrigin[0], vFunnel[0] );
	vDist[YPOS] = CL_HLP_Diff( vVictimOrigin[1], vFunnel[1] );
	vDist[ZPOS] = CL_HLP_Diff( vVictimOrigin[2], vFunnel[2] );	
	
	new i;
	for ( i = 0; i < 3; i++ )
	{
		
		if ( CL_HLP_Diff( vVictimOrigin[i], vFunnel[i] - MULTIPLIER ) < vDist[i] )
		{
			vFunnel[i] -= MULTIPLIER;
		}
		else if ( CL_HLP_Diff( vVictimOrigin[i], vFunnel[0] + MULTIPLIER ) < vDist[i] )
		{
			vFunnel[i] += MULTIPLIER;
		}
		else
		{
			vFunnel[i] = vVictimOrigin[i];
		}
	}

	// Now we need to set the parms so (if/when) we call this function again it knows the next origin
	parm[2] = vFunnel[0];
	parm[3] = vFunnel[1];
	parm[4] = vFunnel[2];


	// Still not close enough to our target
	if ( !( vDist[XPOS] < 50 && vDist[YPOS] < 50 && vDist[ZPOS] < 50 ) )
	{
		new Float:fTime = 0.2;

		set_task( fTime, "_CL_ULT_LocustEffect", idAttacker + TASK_FUNNELS, parm, 5 );
	}

	// We're close enough, we can damage them!
	else
	{
		new iDamage = random_num( iLocustSwarmDmgMin, iLocustSwarmDmgMax );

		WC3_Damage( idVictim, idAttacker, iDamage, CSW_LOCUSTS, -1 );

		if(parm[5] == 0)
		{
			emit_sound( idVictim, CHAN_STATIC, arrStrSounds[SOUND_LOCUSTSWARM], 1.0, ATTN_NORM, 0, PITCH_NORM );

			ULT_Icon( idAttacker, ICON_HIDE );

			new szName[32];
			get_user_name( idVictim, szName, 31 );
		
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_CL_ULT_LOCUST_EFFECT_3",szName, iDamage);
			cssbChatColor(idAttacker,"%s%s",fTagWar3ft(),szMessage);
		}

		if(parm[5] == 1) //Если сработал Отражатель
		{
			emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_LOCUSTSWARM], 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	
		
	}
}

CL_HLP_Diff( iNum, iNum2 )
{
	if ( iNum > iNum2 )
	{
		return (iNum-iNum2);
	}
	else
	{
		return (iNum2-iNum);
	}
	#if AMXX_VERSION_NUM < 183
	return 0;
	#endif
}

CL_SkillsOffensive( idAttacker, idVictim, iHitPlace )
{
	if ( !arrBoolData[idVictim][PB_ISCONNECTED] || !arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;

	// Orb of Annihilation
	new iSkillLevel = SM_GetSkillLevel( idAttacker, PASS_ORB );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idAttacker,PASS_ORB) == false)
	{

		new Float:fOrb = ArrayGetCell(arrOrbOfAnnihilation,arrIntData[idAttacker][P_LEVEL]);
		if (random_float(fLordSkill4MinPercent,fLordSkill4MaxPercent) <= fOrb )
		{
			new vVictimOrigin[3];
			get_user_origin( idVictim, vVictimOrigin );
			
			vVictimOrigin[2] -= 20;
			
			// Create the orb effect (отображение сферы)
			Create_TE_SPRITE( vVictimOrigin, arrIdSprites[SPR_WAVE], 10, 200 );
			
			// Play the orb sound
			emit_sound( idVictim, CHAN_STATIC, arrStrSounds[SOUND_ANNIHILATION], 1.0, ATTN_NORM, 0, PITCH_NORM );

			// Damage the user
			if (is_user_alive( idAttacker ) && is_user_alive( idVictim ))
				WC3_Damage( idVictim, idAttacker, iOrbDamage, CSW_ORB, iHitPlace );
		}
		else if ( get_pcvar_num( CVAR_wc3_psychostats ) )
		{
			new WEAPON = CSW_ORB - CSW_WAR3_MIN;

			iStatsShots[idAttacker][WEAPON]++;
		}
	}
	
	// Carrion Beetles 
	iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_CARRIONBEETLES );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idAttacker,SKILL_CARRIONBEETLES) == false)
	{
		new Float:fCarrion = ArrayGetCell(arrCarrionBeetle,iSkillLevel-1);
		if ( random_float(fLordSkill3MinPercent,fLordSkill3MaxPercent) <= fCarrion )
		{
			new vVictimOrigin[3], vAttackerorigin[3];
			get_user_origin( idVictim, vVictimOrigin );
			get_user_origin( idAttacker, vAttackerorigin );
			
			// Create the Carrion Beetle effect (отображение человечков)
			Create_TE_SPRITETRAIL( vAttackerorigin, vVictimOrigin, arrIdSprites[SPR_BEETLE], 15, 15, 1, 2, 6 );
			
			// Play the carrion beetle sound
			emit_sound( idVictim, CHAN_STATIC, arrStrSounds[SOUND_CARRION], 1.0, ATTN_NORM, 0, PITCH_NORM );

			WC3_Damage( idVictim, idAttacker, iCarrionBeetleDamage, CSW_CARRION, iHitPlace );
		}

		else if ( get_pcvar_num( CVAR_wc3_psychostats ) )
		{
			new WEAPON = CSW_CARRION - CSW_WAR3_MIN;

			iStatsShots[idAttacker][WEAPON]++;
		}
	}
	
	if(iImpaleType > 0)
	{
		// Impale (Запутывние скил 1 уровня) - Стандартный скил
		iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_IMPALE );
		if (iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idAttacker,SKILL_IMPALE) == false)
		{
			new Float:fImpale = ArrayGetCell(arrImpale,iSkillLevel-1);
			if (random_float(fLordSkill1MinPercent,fLordSkill1MaxPercent) <= fImpale )
			{
				// Play the impale sound
				emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_IMPALE], 1.0, ATTN_NORM, 0, PITCH_NORM );
				
				new Float:vVelocity[3];
				entity_get_vector( idVictim, EV_VEC_velocity, vVelocity );

				vVelocity[0] = random_float(100.0, 400.0 );
				vVelocity[1] = random_float(100.0, 400.0 );
				vVelocity[2] = random_float(400.0, 700.0 );

				entity_set_vector( idVictim, EV_VEC_velocity, vVelocity );
			}
		}
	}
	else
	{
		// Impale (Запутывние скил 1 уровня) - Подкидывание примерно как в распрыге
		iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_IMPALE );
		if (iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false && isDisabledSkillsOnMap(idAttacker,SKILL_IMPALE) == false)
		{
			new Float:fImpale = ArrayGetCell(arrImpale,iSkillLevel-1);
			if (random_float(fLordSkill1MinPercent,fLordSkill1MaxPercent) <= fImpale )
			{
				// Play the impale sound
				emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_IMPALE], 1.0, ATTN_NORM, 0, PITCH_NORM );
						
				new Float:vVelocity[3];
				entity_get_vector(idVictim, EV_VEC_velocity, vVelocity);
				vVelocity[2] += 190.0;
				entity_set_vector(idVictim, EV_VEC_velocity, vVelocity);

				entity_set_int(idVictim, EV_INT_gaitsequence, 6);
			}
		}
	}//if(iImpaleType > 0)
}

//Шипованная броня
CL_SkillsDefensive(idAttacker, idVictim, iDamage, iHitPlace )
{
	if ( !arrBoolData[idVictim][PB_ISCONNECTED] || !arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;

	// Spiked Carapace
	new iSkillLevel = SM_GetSkillLevel( idVictim, SKILL_SPIKEDCARAPACE );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
	{
		if(isDisabledSkillsOnMap(idVictim,SKILL_SPIKEDCARAPACE) == true)
			return;

		new Float:fSpiked = ArrayGetCell(arrSpikedCarapace,iSkillLevel-1);
		
		new iMaxArmor = clAr:getRaceMaxArmor(idVictim);
		new CsArmorType:tArmor;
		new iCurrentArmor =  clAr:getUserArmor(idVictim,tArmor);
		new iBonusArmor = floatround( float(iDamage) * fSpiked );
		
		#if MODE_LOG
			#if LOG_SKILL_SPIKEDCARAPACE > 0
				clLog:logRaceCrypt(idAttacker,fSpiked,iDamage,iBonusArmor);
			#endif
		#endif

		if((iCurrentArmor + iBonusArmor) > iMaxArmor)
			clAr:setUserArmor(idVictim,iMaxArmor);
		else
			clAr:setUserArmor(idVictim,iCurrentArmor + iBonusArmor);

		if (is_user_alive(idAttacker))
		{
			WC3_Damage(idAttacker, idVictim, iBonusArmor, CSW_CARAPACE, iHitPlace );
			
			SHARED_Glow(idAttacker, ( 3 * iBonusArmor ), 0, 0, 0 );
			
			Create_ScreenFade(idAttacker, (1<<10), (1<<10), (1<<12), 255, 0, 0, iBonusArmor );
		}
	}
}