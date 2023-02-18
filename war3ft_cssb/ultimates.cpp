/*
*	Common Ultimate Functions
*/

// This is ran every second...
public _ULT_Delay()
{
	
	//Для talisman
	taskCounterLoopTalisman();

	//Запуск счетчика отсчета на удаление предмета 
	fRunCalcRemoveLootItem();

	// Decrement the global counter
	g_iUltimateDelay--;
	
	// Now we need to loop through all players and decrement their ultimate delay
	new arrPlayers[32], iNumPlayers, idUser;
	get_players(arrPlayers, iNumPlayers);

	for (new i = 0; i < iNumPlayers; i++ )
	{
		idUser = arrPlayers[i];

		if (!is_user_bot(idUser))
			fResetSelectRace(idUser);

		if(bIsUserRace(idUser,RACE_ROGUE))
		{
			clRogue::addSkillCharge(SKILL_ROGUE_1,idUser,1);
			clRogue::addSkillCharge(SKILL_ROGUE_2,idUser,1);
			clRogue::addSkillCharge(SKILL_ROGUE_3,idUser,1);
		}
		if(bIsUserRace(idUser,RACE_DRUID))
		{
			clDruid::addSkillCharge(SKILL_DRUID_1,idUser,1);
			clDruid::addSkillCharge(SKILL_DRUID_2,idUser,1);
			clDruid::addSkillCharge(SKILL_DRUID_3,idUser,1);
		}
		if(bIsUserRace(idUser,RACE_BLOODSEEKER))
		{
			clBloodseeker::addSkillCharge(SKILL_BLOODSEEKER_1,idUser,1);
			clBloodseeker::addSkillCharge(SKILL_BLOODSEEKER_2,idUser,1);
			clBloodseeker::addSkillCharge(SKILL_BLOODSEEKER_3,idUser,1);
		}
		if(bIsUserRace(idUser,RACE_JUGGERNAUT))
		{
			clJuggernaut::addSkillCharge(SKILL_JUGGERNAUT_1,idUser,2);
			clJuggernaut::addSkillCharge(SKILL_JUGGERNAUT_2,idUser,1);
			clJuggernaut::addSkillCharge(SKILL_JUGGERNAUT_3,idUser,1);
		}

		if(bIsUserRace(idUser,RACE_SNIPER))
			clSniper::fStripGuns(idUser);

		if(bIsUserRace(idUser,RACE_WARLOCK))
			clWarlock::skillShadowWord(idUser);

		if(bIsUserRace(idUser,RACE_SHADOW_FIEND))
			clShadowFiend::skillRequiemSouls(idUser);
	

/*
		new szModel[32]; //Куда запишем модель, которая сейчас
		get_user_info(idUser, "model", szModel, charsmax( szModel )); //Получаем модель
		client_print(idUser,print_chat,"szModel: %s",szModel);
*/
		// Reduce the user's ultimate delay

	//	if(g_freezeTime == false)
	//		SHARED_SetSpeed(idUser);

		//Для talisman +
		if ( ITEM_Has( idUser, ITEM_ULTIMATE_TIMER_DIVIDER ) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_ULTIMATE_TIMER_DIVIDER)
		{
				if(arrIntData[idUser][P_ULTIMATEDELAY] >= RESET_ULTIMATE_TIMER)
					arrIntData[idUser][P_ULTIMATEDELAY] -= RESET_ULTIMATE_TIMER;
				else
					arrIntData[idUser][P_ULTIMATEDELAY]--;
		}	
		else
		{
			arrIntData[idUser][P_ULTIMATEDELAY]--;
		}

		// Then the user's ultimate is ready
		if (arrIntData[idUser][P_ULTIMATEDELAY] == 0 )
			ULT_IconHandler(idUser);
	
/*
		//Дает XP 50000 в 18:00:00
		new szName[32];
		get_user_name(idUser, szName, 31 );

		new szCurrentTime[64];
		get_time("%H:%M:%S", szCurrentTime,63 );

//		client_print(idUser,print_chat,"Time is: %s",szCurrentTime)

		if(equal(szCurrentTime,"18:00:00"))
			ADMIN_GiveXP( idUser,szName, 50000 );

*/



	}//for



}

ULT_ResetCooldown( idUser, iTime, iHideIcon = true )
{
	

	arrIntData[idUser][P_ULTIMATEDELAY]	= iTime;


	// Hide the user's ultimate icon
	if ( iHideIcon )
	{
		ULT_Icon( idUser, ICON_HIDE );
	}
}

// This function will handle ultimate icons - basically shows if appropriate or hides if appropriate
ULT_IconHandler( idUser )
{
	
	
	if ( !WC3_Check() )
		return;
		
	new bool:bShowIcon = true;

	// User has no ultimate!
	new iUltimateID = SM_GetSkillOfType( idUser, SKILL_TYPE_ULTIMATE );
	if ( iUltimateID > -1 && SM_GetSkillLevel( idUser, iUltimateID) <= 0 )
	{
		bShowIcon = false;
	}
	
	// User's delay is longer!
	else if ( arrIntData[idUser][P_ULTIMATEDELAY] > 0 )
	{
		bShowIcon = false;
	}

	// User is dead - don't show icon!
	else if ( !is_user_alive( idUser ) )
	{
		bShowIcon = false;
	}

	// User isn't connected! - don't show icon!
	else if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		bShowIcon = false;
	}


	// We need to hide the user's icon!
	if ( !bShowIcon )
	{
		// In theory I could remember what was displayed when - but easy way out is this
		ULT_ClearIcons( idUser );
	}

	// Show the user's icon!
	else
	{
		// Play the ultimate ready sound
		client_cmd( idUser, "speak %s", arrStrSounds[SOUND_ULTIMATEREADY] )
		
		// Give the user a graphical message that their ultimate is ready
		WC3_StatusText( idUser, TXT_ULTIMATE, "%L", LANG_PLAYER, "ULTIMATE_READY" );
		
		// Show their ultimate icon
		ULT_Icon( idUser, ICON_SHOW );
	}
}

// This function will display/flash/hide the race's ultimate icon on the screen
ULT_Icon( idUser, flag )
{
	

	// If they mysteriously lost a level - we shouldn't display the icon (i.e. admin command)
	if ( arrIntData[idUser][P_LEVEL] < iMinUltLevel && flag != ICON_HIDE )
	{
		flag = ICON_HIDE;
	}

	new iRaceID = arrIntData[idUser][P_RACE];
	
	// If we're chameleon we need to display the icon of the ultimate we have
	if ( arrIntData[idUser][P_RACE] == RACE_CHAMELEON )
	{
		new iChamUltimate = g_ChamSkills[3];
		iRaceID = g_SkillOwner[iChamUltimate];
		
	}
	
	
	
	// We should only do this if we have a valid race ID
	if ( iRaceID )
	{
		new r, g, b;

		// Each race has its on color for its icon...
		switch ( iRaceID )
		{
			case RACE_UNDEAD:			r=255,	g=0,	b=0;		// Undead
			case RACE_HUMAN:			r=0,	g=120,	b=120;		// Human
			case RACE_ORC:				r=255,	g=255,	b=255;		// Orc
			case RACE_ELF:				r=0,	g=0,	b=255;		// Night Elf
			case RACE_BLOOD:			r=255,	g=0,	b=0;		// Blood Mage
			case RACE_SHADOW:			r=0,	g=200,	b=200;		// Shadow Hunter
			case RACE_WARDEN:			r=255,	g=0,	b=0;		// Warden
			case RACE_CRYPT:			r=0,	g=255,	b=0;		// Crypt Lord
			case RACE_CHAMELEON:		r=218,	g=165,	b=32;		// Chameleon
			case RACE_FROST_MAGE:		r=30,	g=144,	b=255;		// Frost Mage
			case RACE_DEATH_KNIGHT:		r=0,	g=191,	b=255;		// Death knight
			case RACE_BLACK_MAGICIAN:	r=0,	g=191,	b=255;		// Black magician
			case RACE_ALCHEMIST:		r=255,	g=140,	b=0;		// Alchemist
			case RACE_PRIEST:			r=255,	g=127,	b=80;		// Priest
			case RACE_ROGUE:			r=255,	g=0,	b=0;		// Rogue
			case RACE_DRUID:			r=12,	g=244,	b=50;		// Druid
			case RACE_BLOODSEEKER:		r=252,	g=33,	b=59;		// Бладсикер
			case RACE_JUGGERNAUT:		r=225,	g=37,	b=184;		// Раса Джагернаут
			case RACE_SNIPER:			r=224,	g=78,	b=41;		// Раса Снайпер
			case RACE_DISRUPTOR:		r=14,	g=200,	b=238;		// Раса Разрушитель
			case RACE_RAZOR:			r=211,	g=233,	b=19;		// Раса Блэйд
			case RACE_WARLOCK:			r=252,	g=0,	b=63;		// Раса Варлок
			case RACE_SHADOW_FIEND:		r=227,	g=252,	b=48;		// Раса Невермор
			case RACE_24:				r=12,	g=244,	b=50;		// Раса 24
			case RACE_25:				r=12,	g=244,	b=50;		// Раса 25

		}
					
		// Special circumstances should be done here
		switch ( flag )
		{
			case ICON_FLASH:
			{
				// Change colors for Suicide Bomber or Immolate
				if ( SM_GetSkillLevel( idUser, ULTIMATE_SUICIDE ) > 0 || 
					SM_GetSkillLevel( idUser, ULTIMATE_IMMOLATE ) > 0 ||
					SM_GetSkillLevel( idUser, ULTIMATE_PRIEST_DARKNESS_WORD_DEATH ) > 0)
				{
					r=255, g=255, b=255;
				}
			}
		}

		// Create the status icon
		Create_StatusIcon( idUser, flag, g_UltimateIcons[iRaceID - 1], r, g, b );

		// Remember what icon we displayed
		if ( flag == ICON_SHOW || flag == ICON_FLASH )
		{
			g_ULT_iLastIconShown[idUser] = iRaceID;
		}

		// No icon shown
		else if ( flag == ICON_HIDE )
		{
			g_ULT_iLastIconShown[idUser] = 0;
		}
	}
}

ULT_ClearIcons( idUser )
{
	

	// Remove the last icon that was shown!
	if ( g_ULT_iLastIconShown[idUser] > 0 )
		Create_StatusIcon( idUser, ICON_HIDE, g_UltimateIcons[g_ULT_iLastIconShown[idUser]-1], 0, 0, 0 );
		

}

ULT_Available( idUser )
{

	

	// User needs ult + can't have it used + can't have a delay + can't have a global delay
	//if ( arrIntData[idUser][P_ULTIMATEDELAY] <= 0 && g_iUltimateDelay <= 0 )
	if ( arrIntData[idUser][P_ULTIMATEDELAY] <= 0 )
	{
		new iSkillID = SM_GetSkillOfType( idUser, SKILL_TYPE_ULTIMATE );
		new iSkillLevel = SM_GetSkillLevel( idUser, iSkillID);
		
		if ( iSkillLevel > 0 )
		{
			return true;
		}
	}

	return false;
}

// This will simply CHECK if a user can block an ultimate!
bool:ULT_CanUserBlockUlt(const idVictimBlockUlt, const idAttacker)
{
	

	new bool:bCanBlock = false;

	if (arrBoolData[idVictimBlockUlt][PB_WARDENBLINK] && !arrBoolData[idVictimBlockUlt][PB_HEXED])
	{
		bCanBlock = true;
	}
	//ITEM_NECKLACE - Necklace of Immunity
	else if (ITEM_Has( idVictimBlockUlt, ITEM_NECKLACE ) > ITEM_NONE || 
		     (fWorkTalismanPassive(idVictimBlockUlt, arrTalismanActive[idVictimBlockUlt]) == TALISMAN_ITEM_NECKLACE && arrTalismanNecklaceNum[idVictimBlockUlt] > 0) ||
		     clVIP:isAccesItemVip(idVictimBlockUlt,ITEM_NECKLACE) == true
		    )
	{
		bCanBlock = true;
	}

	// Скил 3 уровня - Unstable Current - Неустойчивый поток
	//Если жертва Блэйд, то применяем обратный удар электрическим зарядом
	if(bIsUserRace(idVictimBlockUlt,RACE_RAZOR))
		clRazor::skillUnstableCurrent(idVictimBlockUlt,idAttacker);
		

	
	return bCanBlock;
}

ULT_RemoveCharge(idUser)
{
	

	//Для talisman +
	if ( ITEM_Has( idUser, ITEM_NECKLACE ) > ITEM_NONE || arrTalismanNecklaceNum[idUser] > 0)
	{
		ITEM_RemoveCharge( idUser, ITEM_NECKLACE );
	}
	else if ( arrBoolData[idUser][PB_WARDENBLINK] )
	{}
	
	format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ULT_REMOVE_CHARGE");	
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

	// Play ultimate blocked sound
	emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_SPELLSHIELD], 1.0, ATTN_NORM, 0, PITCH_NORM );
}

ULT_Blocked(idUser)
{
	

	// Maybe play a sound here instead?
	format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ULT_BLOCKED");	
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
	
	// Play ultimate blocked sound
	emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_DISPELL], 1.0, ATTN_NORM, 0, PITCH_NORM );
}

public _ULT_Ping( parm[] )
{
	

	new idUser = parm[0];
	new iTimeLeft = parm[1];
	
	// Decrement our timer
	parm[1]--;
	
	// User died or diconnected
	if ( !arrBoolData[idUser][PB_ISCONNECTED] || !is_user_alive( idUser ) )
	{
		arrBoolData[idUser][PB_ISSEARCHING] = false;
	}
	
	// This is the last "playing" of the sound, no target was found :/
	if ( iTimeLeft == 0 )
	{
		arrBoolData[idUser][PB_ISSEARCHING] = false;
		
		if ( ULT_Available( idUser ) )
		{
			ULT_Icon( idUser, ICON_SHOW );
		}
	}
	
	// Then we need to play the sound + flash their icon!
	if ( arrBoolData[idUser][PB_ISSEARCHING] )
	{
		// Flash their ultimate icon
		ULT_Icon( idUser, ICON_FLASH );

		// Play the ping sound
		emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_ULTIMATESCAN], 1.0, ATTN_NORM, 0, PITCH_NORM );

		set_task( 1.0, "_ULT_Ping", TASK_ULTPING + idUser, parm, 2 );
	}

	return;
}

// Function called before user's spawn
ULT_Reset( idUser )
{
	

	// Remove any explosions that are occuring, we don't want them carried over to the next round
	task_exists( TASK_EXPLOSION + idUser )		? remove_task( TASK_EXPLOSION + idUser ) : 0;
	task_exists( TASK_BEAMCYLINDER + idUser )	? remove_task( TASK_BEAMCYLINDER + idUser ) : 0;

	// Stop Crypt Lord's Ultimate
	task_exists( TASK_FUNNELS + idUser )		? remove_task( TASK_FUNNELS + idUser ) : 0;

	// Stop the ultimate cooldowns since they will reset at round start
	task_exists( TASK_UDELAY + idUser )			? remove_task( TASK_UDELAY + idUser ) : 0;
	
	// Reset Big Bad Voodoo
	if ( task_exists( TASK_RESETGOD + idUser ) )
	{
		remove_task( TASK_RESETGOD + idUser );

		SH_Ult_Remove( idUser );
	}
	
	// Set this to false to stop searching ultimates (used by NE + ORC + BM ultimates)
	arrBoolData[idUser][PB_ISSEARCHING] = false;

	// Hide their ultimate icon
	ULT_Icon( idUser, ICON_HIDE );
}
