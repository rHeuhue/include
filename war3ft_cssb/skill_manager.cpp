SM_Init()
{
	
	// Set up the Skill Owners
	g_SkillOwner[SKILL_VAMPIRICAURA			]	= RACE_UNDEAD;
	g_SkillOwner[SKILL_UNHOLYAURA			]	= RACE_UNDEAD;
	g_SkillOwner[SKILL_LEVITATION			]	= RACE_UNDEAD;
	g_SkillOwner[ULTIMATE_SUICIDE			]	= RACE_UNDEAD;

	g_SkillOwner[SKILL_INVISIBILITY			]	= RACE_HUMAN;
	g_SkillOwner[SKILL_DEVOTION				]	= RACE_HUMAN;
	g_SkillOwner[SKILL_BASH					]	= RACE_HUMAN;
	g_SkillOwner[ULTIMATE_BLINK				]	= RACE_HUMAN;

	g_SkillOwner[SKILL_CRITICALSTRIKE		]	= RACE_ORC;
	g_SkillOwner[SKILL_CRITICALGRENADE		]	= RACE_ORC;
	g_SkillOwner[SKILL_REINCARNATION		]	= RACE_ORC;
	g_SkillOwner[ULTIMATE_CHAINLIGHTNING	]	= RACE_ORC;

	g_SkillOwner[SKILL_EVASION				]	= RACE_ELF;
	g_SkillOwner[SKILL_THORNS				]	= RACE_ELF;
	g_SkillOwner[SKILL_TRUESHOT				]	= RACE_ELF;
	g_SkillOwner[ULTIMATE_ENTANGLE			]	= RACE_ELF;

	g_SkillOwner[SKILL_PHOENIX				]	= RACE_BLOOD;
	g_SkillOwner[SKILL_BANISH				]	= RACE_BLOOD;
	g_SkillOwner[SKILL_SIPHONMANA			]	= RACE_BLOOD;
	g_SkillOwner[ULTIMATE_IMMOLATE			]	= RACE_BLOOD;
	g_SkillOwner[PASS_RESISTANTSKIN			]	= RACE_BLOOD;

	g_SkillOwner[SKILL_HEALINGWAVE			]	= RACE_SHADOW;
	g_SkillOwner[SKILL_HEX					]	= RACE_SHADOW;
	g_SkillOwner[SKILL_SERPENTWARD			]	= RACE_SHADOW;
	g_SkillOwner[ULTIMATE_BIGBADVOODOO		]	= RACE_SHADOW;
	g_SkillOwner[PASS_UNSTABLECONCOCTION	]	= RACE_SHADOW;

	g_SkillOwner[SKILL_FANOFKNIVES			]	= RACE_WARDEN;
	g_SkillOwner[SKILL_BLINK				]	= RACE_WARDEN;
	g_SkillOwner[SKILL_SHADOWSTRIKE			]	= RACE_WARDEN;
	g_SkillOwner[ULTIMATE_VENGEANCE			]	= RACE_WARDEN;
	g_SkillOwner[PASS_HARDENEDSKIN			]	= RACE_WARDEN;

	g_SkillOwner[SKILL_IMPALE				]	= RACE_CRYPT;
	g_SkillOwner[SKILL_SPIKEDCARAPACE		]	= RACE_CRYPT;
	g_SkillOwner[SKILL_CARRIONBEETLES		]	= RACE_CRYPT;
	g_SkillOwner[ULTIMATE_LOCUSTSWARM		]	= RACE_CRYPT;
	g_SkillOwner[PASS_ORB					]	= RACE_CRYPT;

	//Ледяной Маг
	g_SkillOwner[SKILL_FROST_MAGE_ICE_SPLINTERS]	= RACE_FROST_MAGE;
	g_SkillOwner[SKILL_FROST_MAGE_ICE_ARROW]	= RACE_FROST_MAGE;
	g_SkillOwner[SKILL_FROST_MAGE_CONE_OF_COLD]	= RACE_FROST_MAGE;
	g_SkillOwner[ULTIMATE_FROST_MAGE_BLIZZARD]	= RACE_FROST_MAGE;


	// Set up the skill types
	g_SkillType[SKILL_VAMPIRICAURA			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_UNHOLYAURA			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_LEVITATION			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_SUICIDE			]	= SKILL_TYPE_ULTIMATE;

	g_SkillType[SKILL_INVISIBILITY			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_DEVOTION				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_BASH					]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_BLINK				]	= SKILL_TYPE_ULTIMATE;

	g_SkillType[SKILL_CRITICALSTRIKE		]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_CRITICALGRENADE		]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_REINCARNATION			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_CHAINLIGHTNING		]	= SKILL_TYPE_ULTIMATE;

	g_SkillType[SKILL_EVASION				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_THORNS				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_TRUESHOT				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_ENTANGLE			]	= SKILL_TYPE_ULTIMATE;

	g_SkillType[SKILL_PHOENIX				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_BANISH				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_SIPHONMANA			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_IMMOLATE			]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_RESISTANTSKIN			]	= SKILL_TYPE_PASSIVE;

	g_SkillType[SKILL_HEALINGWAVE			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_HEX					]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_SERPENTWARD			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_BIGBADVOODOO		]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_UNSTABLECONCOCTION		]	= SKILL_TYPE_PASSIVE;

	g_SkillType[SKILL_FANOFKNIVES			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_BLINK					]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_SHADOWSTRIKE			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_VENGEANCE			]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_HARDENEDSKIN			]	= SKILL_TYPE_PASSIVE;

	g_SkillType[SKILL_IMPALE				]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_SPIKEDCARAPACE		]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_CARRIONBEETLES		]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_LOCUSTSWARM		]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_ORB					]	= SKILL_TYPE_PASSIVE;

	//Ледяной Маг
	g_SkillType[SKILL_FROST_MAGE_ICE_SPLINTERS	]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_FROST_MAGE_ICE_ARROW]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_FROST_MAGE_CONE_OF_COLD	]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_FROST_MAGE_BLIZZARD]	= SKILL_TYPE_ULTIMATE;


	//Flame Strike - Супер навык для Хамелеона "паровоз"
	g_SkillType[ULTIMATE_CHAM_FLAME_STRIKE		]	= SKILL_TYPE_ULTIMATE;

	// Set up the skill order
	g_SkillOrder[SKILL_VAMPIRICAURA			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_UNHOLYAURA			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_LEVITATION			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_SUICIDE			]	= SKILL_POS_4;

	g_SkillOrder[SKILL_INVISIBILITY			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_DEVOTION				]	= SKILL_POS_2;
	g_SkillOrder[SKILL_BASH					]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_BLINK				]	= SKILL_POS_4;

	g_SkillOrder[SKILL_CRITICALSTRIKE		]	= SKILL_POS_1;
	g_SkillOrder[SKILL_CRITICALGRENADE		]	= SKILL_POS_2;
	g_SkillOrder[SKILL_REINCARNATION		]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_CHAINLIGHTNING	]	= SKILL_POS_4;

	g_SkillOrder[SKILL_EVASION				]	= SKILL_POS_1;
	g_SkillOrder[SKILL_THORNS				]	= SKILL_POS_2;
	g_SkillOrder[SKILL_TRUESHOT				]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_ENTANGLE			]	= SKILL_POS_4;

	g_SkillOrder[SKILL_PHOENIX				]	= SKILL_POS_1;
	g_SkillOrder[SKILL_BANISH				]	= SKILL_POS_2;
	g_SkillOrder[SKILL_SIPHONMANA			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_IMMOLATE			]	= SKILL_POS_4;
	g_SkillOrder[PASS_RESISTANTSKIN			]	= SKILL_POS_NONE;

	g_SkillOrder[SKILL_HEALINGWAVE			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_HEX					]	= SKILL_POS_2;
	g_SkillOrder[SKILL_SERPENTWARD			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_BIGBADVOODOO		]	= SKILL_POS_4;
	g_SkillOrder[PASS_UNSTABLECONCOCTION	]	= SKILL_POS_NONE;

	g_SkillOrder[SKILL_FANOFKNIVES			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_BLINK				]	= SKILL_POS_2;
	g_SkillOrder[SKILL_SHADOWSTRIKE			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_VENGEANCE			]	= SKILL_POS_4;
	g_SkillOrder[PASS_HARDENEDSKIN			]	= SKILL_POS_NONE;

	g_SkillOrder[SKILL_IMPALE				]	= SKILL_POS_1;
	g_SkillOrder[SKILL_SPIKEDCARAPACE		]	= SKILL_POS_2;
	g_SkillOrder[SKILL_CARRIONBEETLES		]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_LOCUSTSWARM		]	= SKILL_POS_4;
	g_SkillOrder[PASS_ORB					]	= SKILL_POS_NONE;

	//Ледяной Маг
	g_SkillOrder[SKILL_FROST_MAGE_ICE_SPLINTERS	]	= SKILL_POS_1;
	g_SkillOrder[SKILL_FROST_MAGE_ICE_ARROW]	= SKILL_POS_2;
	g_SkillOrder[SKILL_FROST_MAGE_CONE_OF_COLD]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_FROST_MAGE_BLIZZARD]	= SKILL_POS_4;

	//Flame Strike - Супер навык для Хамелеона "паровоз"
	g_SkillOrder[ULTIMATE_CHAM_FLAME_STRIKE		]	= SKILL_POS_4;

	clRaceDeathKnight::setSkillsInit();
	clRaceBlackMag::setSkillsInit();
	setALSkillsInit();
	clRacePriest::setPriestSkillsInit();
	clRogue::setRogueSkillsInit();
	clDruid::setDruidSkillsInit();
	clBloodseeker::setSkillsInit();
	clJuggernaut::setSkillsInit();
	clSniper::setSkillsInit();
	clDisruptor::setSkillsInit();
	clRazor::setSkillsInit();
	clWarlock::setSkillsInit();
	clShadowFiend::setSkillsInit();
}

/***** NEW SKILL SET UP BELOW!! *****/

SM_SetPlayerRace( idUser, iRace )
{
	

	static i;

	// Set up the chameleon skills
	if ( iRace == RACE_CHAMELEON )
	{
		new bool:bIsListEmpty = false;
		new iChamSkillsAux[5];

		if (ArrayGetCell(arrIntVipRace,8) == 1 )
			bIsListEmpty = VIP_SetPlayerSkills( idUser, iChamSkillsAux);
	
		if(bIsListEmpty == true)
			g_ChamSkills = iChamSkillsAux;

		g_bPlayerSkills[idUser][g_ChamSkills[0]] = true;
		g_bPlayerSkills[idUser][g_ChamSkills[1]] = true;
		g_bPlayerSkills[idUser][g_ChamSkills[2]] = true;
		g_bPlayerSkills[idUser][g_ChamSkills[3]] = true;
		g_bPlayerSkills[idUser][g_ChamSkills[4]] = true;
	}

	else
	{		
		for ( i = 0; i < MAX_SKILLS; i++ )
		{			
			if ( g_SkillOwner[i] == iRace )
			{
				g_bPlayerSkills[idUser][i] = true;
			}
		}
	}
}

// Function will reset all of the user's skill levels
SM_ResetSkillLevels( idUser )
{
	

	static i;

	for ( i = 0; i < MAX_SKILLS; i++ )
	{
		g_PlayerSkillLevel[idUser][i] = 0;
	}
}

// Function will reset what skills the user has
SM_ResetSkills( idUser )
{
	

	static i;

	for ( i = 0; i < MAX_SKILLS; i++ )
	{
		g_bPlayerSkills[idUser][i] = false;
	}
}

// Function will return the skill ID number based on the position (i.e. used after a skill is selected)
SM_GetSkillByPos( idUser, iPos )
{
	

	static i, j;
	j = 0;

	new iUserSkills[MAX_SKILLS] = {-1, ...};

	// Sort by trainable first
	for ( i = 0; i < MAX_SKILLS; i++ )
	{
		if ( g_bPlayerSkills[idUser][i] && g_SkillType[i] == SKILL_TYPE_TRAINABLE )
		{
			iUserSkills[j++] = i;
		}
	}

	// Then sort by ultimates
	for ( i = 0; i < MAX_SKILLS; i++ )
	{
		if ( g_bPlayerSkills[idUser][i] && g_SkillType[i] == SKILL_TYPE_ULTIMATE )
		{
			iUserSkills[j++] = i;
		}
	}

	// Then sort by passive
	for ( i = 0; i < MAX_SKILLS; i++ )
	{
		if ( g_bPlayerSkills[idUser][i] && g_SkillType[i] == SKILL_TYPE_PASSIVE )
		{
			iUserSkills[j++] = i;
		}
	}

	// Now lets return the position

	if ( iUserSkills[iPos] != -1 )
	{
		return iUserSkills[iPos];
	}

	return -1;
}

// Returns the user's level for a certain skill
SM_GetSkillLevel( idUser, skill_id)
{
	

	if ( !SM_IsValidSkill( skill_id ) )
		return 0;
	
	// User doesn't have this skill
	if ( !g_bPlayerSkills[idUser][skill_id] )
	{
		return -1;
	}

	// If it's a passive skill, we'll just return the player's current level
	if ( g_SkillType[skill_id] == SKILL_TYPE_PASSIVE )
	{
		return arrIntData[idUser][P_LEVEL];
	}

	return g_PlayerSkillLevel[idUser][skill_id];
}

// Set the user's skill level for a given skill
SM_SetSkillLevel( idUser, skill_id, iLevel, iDebugID )
{
	

	if ( !SM_IsValidSkill( skill_id ) )
		return;
	

	// User doesn't have this skill
	if ( !g_bPlayerSkills[idUser][skill_id] )
	{
		return;
	}
	
	// We shouldn't be setting a passive skill's level!
	if ( g_SkillType[skill_id] == SKILL_TYPE_PASSIVE )
	{
		//WC3_Log( false, "Setting a passive skill's level %d to %d (%d)", skill_id, iLevel, iDebugID );

		log_error( AMX_ERR_NATIVE, "Setting a passive skill's level %d to %d (%d)", skill_id, iLevel, iDebugID );

		return;
	}
	
	// Technically we shouldn't have a skill level EVER greater than 3 right?
	if ( iLevel > iMaxSkillLevel )
		return;
	
	//static iLastSkillLevel;
	//iLastSkillLevel = g_PlayerSkillLevel[idUser][skill_id];

	// Set our new skill value
	g_PlayerSkillLevel[idUser][skill_id] = iLevel;

	// This will configure the skill (make any changes that should be necessary)
	//SM_SkillSet( idUser, skill_id, iLastSkillLevel, iLevel );
	SM_SkillSet( idUser, skill_id );

	return;
}


// Checks to see if a skill ID is valid
bool:SM_IsValidSkill( skill_id )
{
	if ( skill_id >= 0 && skill_id < MAX_SKILLS )
	{
		return true;
	}

	return false;
}

// Function will get a random skill for the user's current skills (great for bots)
SM_GetRandomSkill(idUser)
{
	

	// Make sure a skill is available
	if ( !SM_SkillAvailable( idUser ) )
		return -1;
	
	static iRandomSkill;
	

	// Initial condition selected
	iRandomSkill = random_num( 0, MAX_SKILLS - 1 );

	while ( !g_bPlayerSkills[idUser][iRandomSkill] )
	{
		iRandomSkill = random_num( 0, MAX_SKILLS - 1 );
	}

	return iRandomSkill;
}

SM_GetRandomSkillByType( idUser, type )
{

	

	// Make sure a skill is available
	if ( !SM_SkillAvailable( idUser ) )
		return -1;
	
	static iRandomSkill;
	

	// Initial condition selected
	iRandomSkill = random_num( 0, MAX_SKILLS - 1 );

	while ( !g_bPlayerSkills[idUser][iRandomSkill] || g_SkillType[iRandomSkill] != type )
	{
		iRandomSkill = random_num( 0, MAX_SKILLS - 1 );
	}

	return iRandomSkill;
}


bool:SM_SkillAvailable( idUser )
{
	static i;

	for ( i = 0; i < MAX_SKILLS; i++ )
	{
		if ( g_bPlayerSkills[idUser][i] )
		{
			return true;
		}
	}

	return false;
}

// Function will simply return the skill type
SM_GetSkillType( skill_id )
{
	

	if ( !SM_IsValidSkill( skill_id ) )
		return 0;
	
	return g_SkillType[skill_id];
}

SM_TotalSkillPointsUsed( idUser )
{
	static i, iTotal;
	iTotal = 0;

	for ( i = 0; i < MAX_SKILLS; i++ )
	{
		if ( g_SkillType[i] == SKILL_TYPE_TRAINABLE || g_SkillType[i] == SKILL_TYPE_ULTIMATE )
		{
			if ( g_bPlayerSkills[idUser][i] )
			{
				iTotal += g_PlayerSkillLevel[idUser][i];
			}
		}
	}

	return iTotal;
}

// Function will return a skill of a certain type
SM_GetSkillOfType( idUser, type, iStart = 0 )
{
	static i;

	for ( i = iStart; i < MAX_SKILLS; i++ )
	{
		if ( g_bPlayerSkills[idUser][i] && g_SkillType[i] == type )
		{
			return i;
		}
	}

	return -1;
}

bool:SM_IsValidRace( iRace )
{
	if ( 1 <= iRace <= MAX_RACES )
	{
		return true;
	}

	return false;
}


// After we know which skill to give the user - we call this function to give it to them!
SM_SetSkill( idUser, iSkillID )
{
	
	if ( !SM_IsValidSkill( iSkillID ) )
		return;
	
	// Get the user's current skill level
	new iCurrentLevel = SM_GetSkillLevel(idUser,iSkillID);

	if ( iCurrentLevel + 1 > iMaxSkillLevel )
	{
		WC3_Log( true, "Attempted to increase skill %d to %d", iSkillID, iCurrentLevel + 1 );

		return;
	}

	// Add one to their level!
	SM_SetSkillLevel( idUser, iSkillID, iCurrentLevel + 1, 6 );

	// User selected an ultimate + global cooldown is done
	if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_ULTIMATE )
	{
		ULT_IconHandler( idUser );
	}

	return;
}

// Given a player idUser - will simply give them a random skill point! - it will always give an ult @ level 6
// returns false if no point was given
SM_GiveRandomSkillPoint( idUser )
{
	
	// Then there is nothing to give!
	if ( SM_TotalSkillPointsUsed( idUser ) >= arrIntData[idUser][P_LEVEL] )
		return false;
	

	// Give them their ultimate if we can
	if ( arrIntData[idUser][P_LEVEL] >= iMinUltLevel )
	{
		new iUltSkill = SM_GetRandomSkillByType( idUser, SKILL_TYPE_ULTIMATE );
		
		if ( iUltSkill != -1 && SM_GetSkillLevel(idUser, iUltSkill) == 0 )
		{
			// Set up the skill...
			SM_SetSkill( idUser, iUltSkill );

			//client_print( idUser, print_chat, "[DEBUG] Ultimate given: %d", iUltSkill );

			return true;
		}
	}
	
	new iRandomSkill = SM_GetRandomSkillByType( idUser, SKILL_TYPE_TRAINABLE );
	new iSkillLevel = SM_GetSkillLevel( idUser, iRandomSkill);

	// Sweetest conditional statement ever
	while ( iSkillLevel + 1 > iMaxSkillLevel || arrIntData[idUser][P_LEVEL] <= 2 * iSkillLevel )
	{
		//server_print( "[%d:%d] %d >= %d || %d <= %d", iRandomSkill, iSkillLevel, iSkillLevel + 1, iMaxSkillLevel, arrIntData[idUser][P_LEVEL], 2 * iSkillLevel );

		iRandomSkill = SM_GetRandomSkillByType( idUser, SKILL_TYPE_TRAINABLE );
		iSkillLevel = SM_GetSkillLevel( idUser, iRandomSkill);
	}
			
	// Set up the skill...
	SM_SetSkill( idUser, iRandomSkill );

	
	return true;
}

SM_SkillSet(idUser, iSkillID)
{
	

	switch( iSkillID )
	{
		case SKILL_UNHOLYAURA:				// Undead's Unholy Aura
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_UNHOLYAURA) == false)
				SHARED_SetSpeed( idUser );
		}

		case SKILL_LEVITATION:				// Undead's Levitation
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_LEVITATION) == false)
				SHARED_SetGravity( idUser );
		}
		case SKILL_INVISIBILITY:			// Human's Invisibility
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_INVISIBILITY) == false)
				SHARED_INVIS_Set(idUser);
		}
		case SKILL_DEVOTION:				// Human's Devotion Aura
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_DEVOTION) == false)
				HU_DevotionAura(idUser);
		}
		case SKILL_PHOENIX:					// Blood Mage's Phoenix
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_PHOENIX) == false)
				BM_PhoenixCheck( idUser );
		}
		case SKILL_HEALINGWAVE:				// Shadow Hunter's Healing Wave
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_HEALINGWAVE) == false)
				SH_HealingWave( idUser )
		}
		case SKILL_SERPENTWARD:				// Shadow Hunter's Serpent Ward
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_SERPENTWARD) == false)
				SH_SerpentWard( idUser );
		}
		case SKILL_BLINK:					// Warden's Blink
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_BLINK) == false)
				WA_Blink( idUser );
		}
		case SKILL_DEATH_KNIGHT_BLOOD_BOIL:	// Скил 2 уровня - Blood Boil - Вскипание крови
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_DEATH_KNIGHT_BLOOD_BOIL) == false)
				clRaceDeathKnight::skillBloodBoil( idUser );
		}
		case SKILL_DISRUPTOR_3:	
		{
			// Скил 3 уровня - Кинетическое поле - Kinetic Field
			if(isDisabledSkillsOnMap(idUser,SKILL_DISRUPTOR_3) == false)
				clDisruptor::skillKineticField(idUser);
		}
		case PASS_RAZOR:
		{
			// Скил 4 уровня - Манна небесная - Manna
			if(isDisabledSkillsOnMap(idUser,PASS_RAZOR) == false)
				clRazor::skillManna(idUser);
		}
		case SKILL_WARLOCK_1:	
		{
			// Скил 1 уровня - Fatal Bonds - Фатальная связь
			if(isDisabledSkillsOnMap(idUser,SKILL_WARLOCK_1) == false)
				clWarlock::skillFatalBonds(idUser);
		}
		case SKILL_SHADOW_FIEND_1:	// Скил 1 уровня - Presence of the Dark Lord - Присутствие Темного Лорда
		{
			if(isDisabledSkillsOnMap(idUser,SKILL_SHADOW_FIEND_1) == false)
				clShadowFiend::skillPresenceDL(idUser);
		}	

		
	}

	return;
}