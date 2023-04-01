/*
*	All CSSB Warcraft 3 Frozen Throne Private Specific functions
*/

#define BOT_RESPAWN			0.10			// Chance that a bot will buy a respawn scroll when dying

/***********************************************************************
		Precaching FUNCTIONS
***********************************************************************/

public WC3_Precache()
{	
	
	//*******************************************************
	// Инициализация массивов файла настройки вип героев - vip_system.ini
	//*******************************************************
	clVIP:vfLoadVipSystemFile();

	//*******************************************************
	// Инициализация массивов файла настройки брони героев - armor_races.ini
	//*******************************************************
	clAr:cfLoadArmorFile();

	//*******************************************************
	// Инициализация массивов файла настройки здоровья героев - health_races.ini
	//*******************************************************
	clHP:cfLoadHealthFile();

	//*******************************************************
	// Инициализация массивов файла настройки времени супер навыков - ultimate_races.ini
	//*******************************************************
	cfLoadUltimateFile();
		
	// *******************************************************
	// Инициализация массивов файла настройки меню - war3ftmenu.ini
	// *******************************************************
	cfLoadCMenuFile();

	// *******************************************************
	// Инициализация файла настроек скилов - skills_options.ini
	// *******************************************************
	cfLoadSkillsFile();

	// *******************************************************
	// Инициализация файла настроек опыта - xp.ini
	// *******************************************************
	cfLoadXPFile();

	// *******************************************************
	// Инициализация файла настроек - war3ftmod.ini
	// *******************************************************
	cfLoadCustomizationFile();

	// *******************************************************
	// Инициализация файла настроек - block_items.ini
	// *******************************************************
	cfLoadBlockItemsFile();

	// *******************************************************
	// Инициализация файла настроек - block_items_race.ini
	// *******************************************************
	cfLoadBlockItemsRaceFile();

	// *******************************************************
	// Инициализация файла настроек - block_races.ini
	// *******************************************************
	cfLoadBlockRacesFile();

	// *******************************************************
	// Инициализация файла настроек - block_skills.ini
	// *******************************************************
	cfLoadBlockSkillsFile();


	// *******************************************************
	// Precache - Звуки для рас
	// *******************************************************
	if(iSoundRaceOnOff > 0)
	{
		for (new i = 0; i < ArraySize(arrStrSoundRaceData); i++)
		{
			new szSoundData[255];
			ArrayGetString(arrStrSoundRaceData,i, szSoundData, charsmax(szSoundData));
			precache_sound(szSoundData);
		}
	}



	// *******************************************************
	// Precache - Звуки мода
	// *******************************************************
	copy(arrStrSounds[SOUND_VENGEANCE]				, 63, "warcraft3/MiniSpiritPissed1.wav"				);	// Warden's Ultimate
	copy(arrStrSounds[SOUND_SUICIDE]				, 63, "warcraft3/undead_exp.wav"					);	// Undead's Ultimate
	copy(arrStrSounds[SOUND_BANISH]					, 63, "warcraft3/banishcaster.wav"					);	// Banish
	copy(arrStrSounds[SOUND_LOCUSTSWARM]			, 63, "warcraft3/locustswarmloop.wav"				);	// Locust Swarm
	copy(arrStrSounds[SOUND_SHADOWSTRIKE]			, 63, "warcraft3/shadowstrikebirth.wav"				);	// Shadow Strike
	copy(arrStrSounds[SOUND_CARRION]				, 63, "warcraft3/carrionswarmlaunch1.wav"			);	// Carrion Beetles
	copy(arrStrSounds[SOUND_IMPALE]					, 63, "warcraft3/impalehit.wav"						);	// Impale
	copy(arrStrSounds[SOUND_VOODOO]					, 63, "warcraft3/divineshield.wav"					);	// Big Bad Voodoo
	copy(arrStrSounds[SOUND_FLAMESTRIKE]			, 63, "warcraft3/flamestriketargetwavenonloop1.wav"	);	// Flame Strike
	copy(arrStrSounds[SOUND_ENTANGLING]				, 63, "warcraft3/entanglingrootstarget1.wav"		);	// Entangling Roots
	copy(arrStrSounds[SOUND_LIGHTNING]				, 63, "warcraft3/lightningbolt.wav"					);	// Chain Lightning
	copy(arrStrSounds[SOUND_TELEPORT]				, 63, "warcraft3/massteleporttarget.wav"			);	// Teleport
	copy(arrStrSounds[SOUND_BLINK]					, 63, "warcraft3/blinkarrival.wav"					);	// Blink Teleport
	copy(arrStrSounds[SOUND_LEVELUP]				, 63, "warcraft3/levelupcaster.wav"					);	// Level up
	copy(arrStrSounds[SOUND_PICKUPITEM]				, 63, "warcraft3/pickupitem.wav"					);	// Buy / Pick up item
	copy(arrStrSounds[SOUND_TOME]					, 63, "warcraft3/Tomes.wav"							);	// Tome of Experience

	//copy(arrStrSounds[SOUND_ULTIMATESCAN]			, 63, "warcraft3/ultimate_beep.wav"							);	// Ultimate Beep
	copy(arrStrSounds[SOUND_ULTIMATESCAN]			, 63, "warcraft3/ultimate_beep_2.wav"							);	// Ultimate Beep

	copy(arrStrSounds[SOUND_ULTIMATEREADY]			, 63, "warcraft3/resurrecttarget.wav"				);	// Ultimate Beep
	copy(arrStrSounds[SOUND_ANNIHILATION]			, 63, "warcraft3/PurgeTarget1.wav"					);	// Orb of Annihilation
	copy(arrStrSounds[SOUND_CONCOCTION_CAST]		, 63, "warcraft3/PossessionMissileLaunch1.wav"		);	// Unstable Concoction Cast
	copy(arrStrSounds[SOUND_CONCOCTION_HIT]			, 63, "warcraft3/PossessionMissileHit1.wav"			);	// Unstable Concoction Hit
	copy(arrStrSounds[SOUND_HEX]					, 63, "warcraft3/PolymorphDone.wav"					);	// Hex
	copy(arrStrSounds[SOUND_IMMOLATE]				, 63, "warcraft3/ImmolationDecay1.wav"				);	// Immolate
	copy(arrStrSounds[SOUND_IMMOLATE_BURNING]		, 63, "warcraft3/immolate_burning.wav"				    );	// Immolate Burning
	copy(arrStrSounds[SOUND_REINCARNATION]			, 63, "warcraft3/soundpack/reincarnation.wav"		);	// Weapon Reincarnation/Ankh
	copy(arrStrSounds[SOUND_ANTEND]					, 63, "warcraft3/antend.wav"						);	// Sound played when you try to shoot a chameleoned teammate 
	copy(arrStrSounds[SOUND_ERROR]					, 63, "warcraft3/bonus/Error.wav"					);	// Sound played on errors 
	copy(arrStrSounds[SOUND_DISPELL]				, 63, "warcraft3/DispelMagicTarget.wav"				);	// Dispell an ultimate - played on idAttacker
	copy(arrStrSounds[SOUND_SPELLSHIELD]			, 63, "warcraft3/SpellShieldImpact1.wav"			);	// Dispell an ultimate - played on blocker
	copy(arrStrSounds[SOUND_DEATH_TOUCH]			, 63, "warcraft3/item_death_touch.wav"			);	// Item Death Touch
	copy(arrStrSounds[SOUND_HEALTH_POTION]			, 63, "warcraft3/item_health_potion.wav"		);	// Item Health Potion
	copy(arrStrSounds[SOUND_STEEL_SKIN]				, 63, "warcraft3/item_steel_skin.wav"			);	// Item  Steel Skin
	copy(arrStrSounds[SOUND_BLIZZARD]				, 63, "warcraft3/skill_blizzard.wav"			);	// Frost Mage Ultimate Blizzard
	copy(arrStrSounds[SOUND_ICE_SPLINTERS]			, 63, "warcraft3/skill_ice_splinters.wav"	);	// Frost Mage Skill Ice splinters
	copy(arrStrSounds[SOUND_ICE_ARROW_MISSILE]		, 63, "warcraft3/ice_arrow_missile.wav"	);	// Frost Mage Skill Ice Arrow
	copy(arrStrSounds[SOUND_ICE_EXPLODE]			, 63, "warcraft3/ice_explode.wav"	);	// Frost Mage Skill Ice Arrow Explode
	copy(arrStrSounds[SOUND_COLD_CONE_S]			, 63, "warcraft3/cold_cone_s.wav"	);	// Frost Mage Cold Cone
	copy(arrStrSounds[SOUND_COLD_CONE_E]			, 63, "warcraft3/cold_cone_e.wav"	);	// Frost Mage Cold Cone (remove)
	copy(arrStrSounds[SOUND_ICE_BLOCK_EXPLODE]		, 63, "warcraft3/ice_block_explode.wav"	);							//Взрыв Ледяной глыбы
	copy(arrStrSounds[SOUND_ICE_BLOCK_FROZEN]		, 63, "warcraft3/ice_block_frozen.wav"	);						//Заморозка Ледяной глыбы
	copy(arrStrSounds[SOUND_ICE_BLOCK_UNFROZEN]		, 63, "warcraft3/ice_block_unfrozen.wav"	);						//Разморозка Ледяной глыбы
	copy(arrStrSounds[SOUND_ICE_BLOCK_CHILLED]		, 63, "warcraft3/ice_block_chilled.wav"	);						//Заморожен Ледяной глыбой
	copy(arrStrSounds[SOUND_MIRROR_ULTIMATE_BLOCK]	, 63, "warcraft3/item_mirror_ult.wav"	);			//Блокировка отражателя супер навыка
	copy(arrStrSounds[SOUND_DEATHCOIL]				, 63, "warcraft3/DeathCoilSpecialArt1.wav"	);		//Лик смерти
	copy(arrStrSounds[SOUND_DEATHCOIL_MISSILE]		, 63, "warcraft3/DeathCoilMissileLaunch1.wav"	);	//Срабатывание Лик смерти
	copy(arrStrSounds[SOUND_SLEEP]					, 63, "warcraft3/SleepBirth1.wav"	);				//Сонная аура
	copy(arrStrSounds[SOUND_BOOK_DEAD_RAISE]		, 63, "warcraft3/book_dead_raise.wav"	);			//Вызов мертвецов хозяином
	copy(arrStrSounds[SOUND_BOOK_DEAD_WARLOCK]		, 63, "warcraft3/book_dead_warlock.wav"	);			//Звук для ожившего мертвеца
	copy(arrStrSounds[SOUND_TRANQUILITY]			, 63, "warcraft3/Tranquility.wav"	);				// Tranquility - Спокойствие
	copy(arrStrSounds[SOUND_PRECAST_HOLY]			, 63, "warcraft3/PreCastHolyMagicLow.wav"	);	
	copy(arrStrSounds[SOUND_CAST_HOLY]				, 63, "warcraft3/HolyCast.wav"	);			
	copy(arrStrSounds[SOUND_NO_GOLD]				, 63, "warcraft3/no_gold.wav"	);//Звук когда при покупке не хватает денег
	copy(arrStrSounds[SOUND_DK_UNARMOR]				, 63, "warcraft3/dk_unarmor3.wav"	); 	//Рыцарь смерти
	copy(arrStrSounds[SOUND_POISON]					, 63, "warcraft3/SpiritTouch.wav" );	//Алхимик
	copy(arrStrSounds[SOUND_FROST]					, 63, "warcraft3/FrostArrowHit1.wav" );
	copy(arrStrSounds[SOUND_RADIATION]				, 63, "warcraft3/radiation.wav" );
	copy(arrStrSounds[SOUND_FIREBALL_EXP_PRIEST]	, 63, "warcraft3/priest_fireball_exp.wav" );	//Жрец
	copy(arrStrSounds[SOUND_FIREBALL_PRIEST]		, 63, "warcraft3/priest_fireball.wav" );
	copy(arrStrSounds[SOUND_MENU_CLICK]				, 63, "warcraft3/menu_click_2.wav" );
	copy(arrStrSounds[SOUND_SINISTER_STRIKE]		, 63, "warcraft3/sinister_strike_2.wav" );
	copy(arrStrSounds[SOUND_VANISH]					, 63, "warcraft3/vanish.wav" );
	copy(arrStrSounds[SOUND_SHURIKEN_TOSS_EXP]		, 63, "warcraft3/shuriken_toss_exp.wav" );
	copy(arrStrSounds[SOUND_WISP_SPAWN]				, 63, "warcraft3/wisp_spawn.wav" );
	copy(arrStrSounds[SOUND_WISP_DEATH]				, 63, "warcraft3/wisp_death.wav" );
	copy(arrStrSounds[SOUND_ASTRAL_STORM]			, 63, "warcraft3/3_astral_storm.wav" );
	copy(arrStrSounds[SOUND_MANGLE]					, 63, "warcraft3/mangle.wav" );
	copy(arrStrSounds[SOUND_BLOODRAGE]				, 63, "warcraft3/bloodseeker_bloodrage.wav" );
	copy(arrStrSounds[SOUND_BLOODRITE]				, 63, "warcraft3/bloodseeker_bloodrite.wav" );
	copy(arrStrSounds[SOUND_HEALING_WARD]			, 63, "warcraft3/j_healing_ward.wav" );
	copy(arrStrSounds[SOUND_HEADSHOT]				, 63, "warcraft3/sniper_headshot_2.wav" );
	copy(arrStrSounds[SOUND_SHRAPNEL_FIRE]			, 63, "warcraft3/shrapnel_fire.wav" );
	copy(arrStrSounds[SOUND_SHRAPNEL_DAMAGE]		, 63, "warcraft3/shrapnel_damage.wav" );
	copy(arrStrSounds[SOUND_SHRAPNEL_EXPLODE]		, 63, "warcraft3/shrapnel_explode.wav" );
	copy(arrStrSounds[SOUND_EYE_STORM]				, 63, "warcraft3/razor_eye_storm.wav" );
	copy(arrStrSounds[SOUND_STATIC_LINK]			, 63, "warcraft3/razor_static_link.wav" );
	copy(arrStrSounds[SOUND_UNSTABLE_CURRENT]		, 63, "warcraft3/razor_unstable_current.wav" );
	copy(arrStrSounds[SOUND_PLASMA_FIELD]			, 63, "warcraft3/razor_plasma_field.wav" );
	copy(arrStrSounds[SOUND_FATAL_BONDS]			, 63, "warcraft3/warlock_fatal_bonds.wav" );
	copy(arrStrSounds[SOUND_SHADOW_WORD]			, 63, "warcraft3/warlock_shadow_word.wav" );
	copy(arrStrSounds[SOUND_FLAMING_FISTS]			, 63, "warcraft3/warlock_flaming_fists.wav" );
	copy(arrStrSounds[SOUND_PERM_IMMOL]				, 63, "warcraft3/warlock_permanent_immolation.wav" );
	copy(arrStrSounds[SOUND_CRY_HEART]				, 63, "warcraft3/shadow_fiend_cry_heart.wav" );
	copy(arrStrSounds[SOUND_NECROMASTERY]			, 63, "warcraft3/shadow_fiend_necromastery.wav" );
	copy(arrStrSounds[SOUND_NECROMASTERY_HP]		, 63, "warcraft3/shadow_fiend_necromastery_hp.wav" );
	copy(arrStrSounds[SOUND_REQUIEM_OF_SOULS]		, 63, "warcraft3/shadow_fiend_requiem_of_souls.wav" );
	copy(arrStrSounds[SOUND_REQUIEM_OF_SOULS_DMG]	, 63, "warcraft3/shadow_fiend_requiem_of_souls_dmg.wav" );
	copy(arrStrSounds[SOUND_BUY_ITEMS]				, 63, "warcraft3/buy_items.wav" );
	copy(arrStrSounds[SOUND_BLADE_FURY]				, 63, "warcraft3/j_blade_fury.wav" );
	copy(arrStrSounds[SOUND_DEMON_BLADE]			, 63, "warcraft3/j_demon_blade.wav" );
	copy(arrStrSounds[SOUND_CRITICAL_BLADE]			, 63, "warcraft3/j_critical_blade.wav" );
	copy(arrStrSounds[SOUND_TOMES]					, 63, "warcraft3/Tomes.wav" );
	copy(arrStrSounds[SOUND_THUNDER_CLAP]			, 63, "warcraft3/thunder_clap.wav" );


	//arrStrSounds[SOUND_THUNDER_CLAP]

	// Lets make sure we have all of the sound files!!!
	new i, szTmp[128];
		
	for ( i = 0; i < MAX_SOUNDS; i++ )
	{
		formatex( szTmp, 127, "sound/%s", arrStrSounds[i] );

		if (!file_exists(szTmp))// Проверка не существование файла звука
		{
			WC3_Log( true, "[ERROR] Missing sound file '%s'", szTmp );
			set_fail_state( "Sound files are missing, unable to load plugin" );
		}
		else
		{
			precache_sound( arrStrSounds[i] );
		}
	}

	// *******************************************************
	// Precache - Спрайты мода
	// *******************************************************
	copy(arrStrSprites[SPR_BANISH]				, 63, "sprites/warcraft3/blood_banish.spr" );				//Race: Blood Mage
	copy(arrStrSprites[SPR_SHADOWSTRIKE]		, 63, "sprites/warcraft3/warden_shadowstrike.spr" );		//Race: Warden
	copy(arrStrSprites[SPR_FIRE]				, 63, "sprites/warcraft3/blood_fire.spr" );					//Race: Blood Mage
	copy(arrStrSprites[SPR_BURNING]				, 63, "sprites/warcraft3/blood_burning.spr" );				//Race: Blood Mage
	copy(arrStrSprites[SPR_BEETLE]				, 63, "sprites/warcraft3/crypt_lord_beetle.spr" );			//Race: Crypt Lord
	copy(arrStrSprites[SPR_FIREBALL]			, 63, "sprites/warcraft3/undead_exp.spr" );					//Race: Undead Scourge
	copy(arrStrSprites[SPR_BEAM]				, 63, "sprites/warcraft3/elf_beam.spr" );					//Race: Night Elf
	copy(arrStrSprites[SPR_TRAIL]				, 63, "sprites/warcraft3/elf_trail.spr" );					//Race: Night Elf
	copy(arrStrSprites[SPR_SHOCKWAVE]			, 63, "sprites/warcraft3/undead_shockwave.spr" );			//Race: Undead Scourge
	copy(arrStrSprites[SPR_LIGHTNING]			, 63, "sprites/warcraft3/orc_lgtning.spr" );				//Race: Orcish Horde
	copy(arrStrSprites[SPR_FLARE]				, 63, "sprites/warcraft3/human_blueflare2.spr" );			//Race: Human Alliance
	copy(arrStrSprites[SPR_WAVE]				, 63, "sprites/warcraft3/crypt_lord_gwave1.spr" );			//Race: Crypt Lord
	copy(arrStrSprites[SPR_IMMOLATE]			, 63, "sprites/warcraft3/blood_fireball.spr" );				//Race: Blood Mage
	copy(arrStrSprites[SPR_DEATH_TOUCH]			, 63, "sprites/warcraft3/eff_death_touch.spr" );			//Death's Touch
	copy(arrStrSprites[SPR_HEALTH_POTION]		, 63, "sprites/warcraft3/eff_health_potion.spr" );			// Health Potion
	copy(arrStrSprites[SPR_STEEL_SKIN]			, 63, "sprites/warcraft3/eff_steel_skin.spr" );				// Steel Skin
	copy(arrStrSprites[SPR_BLUE_LIGHTNING]		, 63, "sprites/warcraft3/blue_lightning_blizzard.spr" );	// Frost Mage Ultimate Blizzard
	copy(arrStrSprites[SPR_ICE_FROSTBOLT]		, 63, "sprites/warcraft3/ice_frostbolt.spr" );				
	copy(arrStrSprites[SPR_ICE_SPLINTERS]		, 63, "sprites/warcraft3/ice_splinters.spr" );				// Frost Mage Ice splinters
	copy(arrStrSprites[SPR_ICE_ARROW_TRAIL]		, 63, "sprites/warcraft3/ice_arrow_trail.spr" );			// Frost Mage Ледяная стрела (Ice Arrow)
	copy(arrStrSprites[SPR_ICE_ARROW]			, 63, "sprites/warcraft3/ice_arrow.spr" );
	copy(arrStrSprites[SPR_ICE_EXPLODE]			, 63, "sprites/warcraft3/ice_explode.spr" );
	copy(arrStrSprites[SPR_SMOKE]				, 63, "sprites/warcraft3/undead_steam1.spr");	//Race: Undead Scourge
	copy(arrStrSprites[SPR_SNOW]				, 63, "sprites/warcraft3/crypt_lord_snow.spr");		//Race: Crypt Lord
	copy(arrStrSprites[SPR_ICE_BLOCK_TRAIL]		, 63, "sprites/warcraft3/ice_block_trail.spr"); 	//Для shopmenu4
	copy(arrStrSprites[SPR_MIRROR_ULTIMATE]		, 63, "sprites/warcraft3/mirror_ultimate.spr");
	copy(arrStrSprites[SPR_DEATHCOIL]			, 63, "sprites/warcraft3/deathcoil.spr");			//Лик смерти
	copy(arrStrSprites[SPR_BLOODSPRAY]			, 63, "sprites/warcraft3/bloodspray.spr");		//New Impale
	copy(arrStrSprites[SPR_BLOODDROP]			, 63, "sprites/warcraft3/blood.spr");				//New Impale2
	copy(arrStrSprites[SPR_SLEEP]				, 63, "sprites/warcraft3/sleep.spr");	//Сонная аура
	copy(arrStrSprites[SPR_DK_UNARMOR]			, 63, "sprites/warcraft3/dk_unarmor.spr" );		//Рыцарь смерти
	copy(arrStrSprites[SPR_BLACKSTRIKE]			, 63, "sprites/warcraft3/blackstrike.spr" );		//Черный маг
	copy(arrStrSprites[SPR_BLACKFIRE]			, 63, "sprites/warcraft3/blackfire.spr" );
	copy(arrStrSprites[SPR_BURNFIRE]			, 63, "sprites/warcraft3/burnfire.spr" );
	copy(arrStrSprites[SPR_POISON]				, 63, "sprites/warcraft3/PoisonSkill.spr" );	//Алхимик
	copy(arrStrSprites[SPR_ECLIPSE]				, 63, "sprites/warcraft3/Eclipse.spr" );
	copy(arrStrSprites[SPR_FIRE_PRIEST]			, 63, "sprites/warcraft3/priest_fire.spr" );		//Жрец
	copy(arrStrSprites[SPR_SMOKE_PRIEST]		, 63, "sprites/warcraft3/priest_black_smoke.spr" );
	copy(arrStrSprites[SPR_FLAME_PRIEST]		, 63, "sprites/warcraft3/priest_flame.spr" );
	copy(arrStrSprites[SPR_ZEXPLODE_PRIEST]		, 63, "sprites/warcraft3/priest_zerogxplode.spr" );
	copy(arrStrSprites[SPR_BUBBLE_PRIEST]		, 63, "sprites/warcraft3/priest_bubble.spr" );
	copy(arrStrSprites[SPR_ICON_TALISMAN]		, 63, "sprites/warcraft3/icon_talisman.spr" );
	copy(arrStrSprites[SPR_MFLASH2_BLACK_MAG]	, 63, "sprites/warcraft3/black_mag_muzzleflash2.spr" );
	copy(arrStrSprites[SPR_SINISTER_STRIKE]		, 63, "sprites/warcraft3/sinister_strike.spr" );
	copy(arrStrSprites[SPR_ROGUE_BEAM]			, 63, "sprites/warcraft3/shuriken_toss_beam.spr" );//луч
	copy(arrStrSprites[SPR_ROGUE_RING]			, 63, "sprites/warcraft3/shuriken_toss_ring.spr" );//кольцо
	copy(arrStrSprites[SPR_ROGUE_SHURIKEN]		, 63, "sprites/warcraft3/shuriken_toss.spr" );//телепорт и сам шар
	copy(arrStrSprites[SPR_DRUID_ENTANGLE]		, 63, "sprites/warcraft3/wild_mush_entangle.spr" );
	copy(arrStrSprites[SPR_DRUID_HEALING]		, 63, "sprites/warcraft3/wild_mush_healing.spr" );
	copy(arrStrSprites[SPR_ASTRAL_STORM]		, 63, "sprites/warcraft3/3_astral_storm.spr" );
	copy(arrStrSprites[SPR_MANGLE]				, 63, "sprites/warcraft3/mangle.spr" );
	copy(arrStrSprites[SPR_BLOODRITE]			, 63, "sprites/warcraft3/bloodseeker_bloodrite1.spr" );
	copy(arrStrSprites[SPR_HEADSHOT]			, 63, "sprites/warcraft3/sniper_headshot_exp.spr" );
	copy(arrStrSprites[SPR_SHRAPNEL]			, 63, "sprites/warcraft3/sniper_shrapnel_2.spr" );
	copy(arrStrSprites[SPR_SHRAPNEL_EXPLODE]	, 63, "sprites/warcraft3/sniper_shrapnel_exp_3.spr" );
	copy(arrStrSprites[SPR_STATIC_STORM]		, 63, "sprites/warcraft3/disruptor_static_storm_2.spr" );
	copy(arrStrSprites[SPR_PLASMA_FIELD]		, 63, "sprites/warcraft3/razor_plasma_field.spr" );
	copy(arrStrSprites[SPR_FL_FISTS_ARMOR]		, 63, "sprites/warcraft3/warlock_flaming_fists_armor.spr" );
	copy(arrStrSprites[SPR_FL_FISTS_DMG]		, 63, "sprites/warcraft3/warlock_flaming_fists_dmg.spr" );
	copy(arrStrSprites[SPR_PERM_IMMOL]			, 63, "sprites/warcraft3/warlock_perm_immolation.spr" );
	copy(arrStrSprites[SPR_NECROMASTERY]		, 63, "sprites/warcraft3/sf_necromastery.spr" );
	copy(arrStrSprites[SPR_NECROMASTERY_EXP]		, 63, "sprites/warcraft3/sf_necromastery_exp.spr" );


	//arrStrSprites[SPR_PLASMA_FIELD]
	//arrIdSprites[SPR_PLASMA_FIELD]	


	for ( i = 0; i < MAX_SPRITES; i++ )
	{
		if (!file_exists(arrStrSprites[i]))// Проверка не существование файла спрайта
		{
			WC3_Log( true, "[ERROR] Missing sprite file '%s'", arrStrSprites[i]);
			set_fail_state( "Sprite files are missing, unable to load plugin!" );
		}
		else
		{
			if (arrStrSprites[i][0])
			arrIdSprites[i] = precache_model( arrStrSprites[i] );
		}
	}

	// *******************************************************
	// Precache - Модели мода
	// *******************************************************
	//Модели игроков (данные модели не входят в массив и идут сами по себе т.к. не используются напрямую через массив)
	precache_model( "models/player/gign/gign.mdl"			);
	precache_model( "models/player/sas/sas.mdl"				);
	precache_model( "models/player/gsg9/gsg9.mdl"			);
	precache_model( "models/player/urban/urban.mdl"			);
	precache_model( "models/player/arctic/arctic.mdl"		);
	precache_model( "models/player/leet/leet.mdl"			);
	precache_model( "models/player/guerilla/guerilla.mdl"	);
	precache_model( "models/player/terror/terror.mdl"		);
	precache_model( "models/player/skull_t/skull_t.mdl");	//Модель скелета теров
	precache_model( "models/player/skull_ct/skull_ct.mdl");	//Модель скелета контров

	//Прекеш дополнительных моделей которые привязаны к основной. К примеру модели _t (данные модели в моде не используются)
	precache_model( "models/CSSB/tentacle2/tentacle2t.mdl" );	//моделька к tentacle2.mdl


	copy(arrStrModels[MDL_FIREBALL]			, 63, "models/CSSB/cssb_fireball/cssb_fireball.mdl");
	copy(arrStrModels[MDL_FRIEZADISC]		, 63, "models/CSSB/r_black_magician/friezadisc.mdl");
	copy(arrStrModels[MDL_FUN_SUPPLYBOX]	, 63, "models/CSSB/Items/fun_supplybox.mdl");
	copy(arrStrModels[MDL_GLASSGIBS]		, 63, "models/CSSB/glassgibs/glassgibs.mdl");
	copy(arrStrModels[MDL_BSKULL]			, 63, "models/CSSB/bskull/bskull.mdl");				// Death Coil
	copy(arrStrModels[MDL_TENTACLE]			, 63, "models/CSSB/tentacle2/tentacle2.mdl");		// Impale
	copy(arrStrModels[MDL_HEALINGWARD]		, 63, "models/CSSB/juggernaut/j_healing_ward.mdl");
	copy(arrStrModels[MDL_JKNIFE]			, 63, "models/CSSB/juggernaut/j_knife.mdl");
	//copy(arrStrModels[MDL_DKINETIC_FIELD]	, 63, "models/CSSB/disruptor/disruptor_kinetic_field.mdl");


	
	
	
	//arrStrModels[MDL_DKINETIC_FIELD]
	//arrIdModels[MDL_DKINETIC_FIELD]

	for ( i = 0; i < MAX_MODELS; i++ )
	{
		if (!file_exists(arrStrModels[i]))// Проверка не существование файла модели
		{
			WC3_Log( true, "[ERROR] Missing model file '%s'", arrStrModels[i]);
			set_fail_state( "Model files are missing, unable to load plugin!" );
		}
		else
		{
			if (arrStrModels[i][0])
			arrIdModels[i] = precache_model( arrStrModels[i] );
		}
	}
}

WC3_Check( idUser = 0, print_location = print_chat )
{
	if ( warcraft3 )
		return true;

	if (idUser != 0 && print_location )
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WC3_CHECK");
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
	}

	return false;
}

// Function called when the plugin loads
public WC3_Init()
{
	// Store this now so we don't need to make a native call everytime we use it
	MAXPLAYERS = get_global_int( GL_maxClients );

	// Register the CVARs
	CVAR_Init();
	
	// Initialize our items
	ITEM_Init();
	
	// Initialize our skills
	SM_Init();

	// Register the player menus
	LANG_SetMenus();
	InitLangAllMenus();

	//Для авто закупки предметов
	abi_InitLangAllMenus();

	// Register any forwards
	FWD_Register();


	//Для talisman + BEGIN {
	//Инициализация переменных
	fInitTalisman();

	//Считывание файла респаунов талисмана для конкретной карты
	fReadMapSpawnsTalisman();
	
	//Для talisman END }

	// We need to execute config file in a bit don't we?
	set_task( 0.3, "_CVAR_ExecuteConfig", TASK_EXECUTECONFIG );

	// Configure the database connection
	set_task( 1.0, "DB_Init", TASK_SETSQL );

	// Set up things when our config file has loaded the values
	set_task( 1.5, "_WC3_RunAfterConfig", TASK_AFTERCONFIG );

	// cl_minmodels check
	set_task( 4.5, "_CS_MinModelsLoop", TASK_MOLEFIX, "", 0, "b" );

	// Set up the spawn entities
	copy( szSpawnEnt[0], 31, "info_player_start" );
	copy( szSpawnEnt[1], 31, "info_player_deathmatch" );
	
	// Run the ultimate delay task
	set_task(1.0, "_ULT_Delay", TASK_UDELAY, "", 0, "b" );
	
	// We need to determine the objective entities (if they exist)
	new i, bool:bFound;
	for ( i = 0; i <= get_global_int( GL_maxEntities ); i++ )
	{
		if ( !is_valid_ent( i ) )
		{
			continue;
		}
		
		// More than were necessary was found
		if ( g_iTotalObjectiveEnts >= MAX_OBJECTIVES )
		{
			WC3_Log( true, "Woa we found more than 11" );
			break;
		}

		bFound = false;

		new szClassName[64];
		entity_get_string( i, EV_SZ_classname, szClassName, 63 );
		
		// VIP Escape zone!!
		if ( equal( szClassName, "func_vip_safetyzone") )	
		{
			g_iObjectiveEntType[g_iTotalObjectiveEnts] = OBJENT_VIP_ESCAPE;
			bFound = true;
		}

		// Hostage zone
		else if ( equal( szClassName, "hostage_entity") )
		{
			g_iObjectiveEntType[g_iTotalObjectiveEnts] = OBJENT_HOSTAGE;
			bFound = true;
		}

		// Bomb zone
		else if ( equal( szClassName, "func_bomb_target") )
		{
			g_iObjectiveEntType[g_iTotalObjectiveEnts] = OBJENT_BOMBSITE;
			bFound = true;
		}

		// Hostage escape zone
		else if ( equal( szClassName, "func_escapezone") )
		{
			g_iObjectiveEntType[g_iTotalObjectiveEnts] = OBJENT_HOSTAGE_ESCAPE;
			bFound = true;
		}

		// We found an objective entity!!!
		if ( bFound )
		{
			g_iObjectiveEnt[g_iTotalObjectiveEnts] = i;

			get_brush_entity_origin( i, g_fObjectiveOrigin[g_iTotalObjectiveEnts] );

			// Increment the total number
			g_iTotalObjectiveEnts++;
		}
	}

	// Lets find out if we should disable orc nades or gloves of warmth
	g_bOrcNadesDisabled				= WC3_MapDisableCheck( "skill_orc_nade.cfg" );


}

public _WC3_RunAfterConfig()
{
	// Configure the XP based on level
	XP_Configure();

	// Set up our CVARs - some of them
	CVAR_Configure();

	// Randomize Chameleon if necessary
	CHAM_Randomize();

	// Инициализация цен на предметы
	ITEM_InitCost();
}

// Function will prompt a user for a race or skill selection
public WC3_GetUserInput( idUser )
{
	if ( !WC3_Check() )
		return;
	
	if ( idUser >= TASK_GETINPUT )
	{
		idUser -= TASK_GETINPUT;
	}

	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
	{
		return;
	}


	// User has no race
	if ( arrIntData[idUser][P_RACE] == 0 )
	{
		new menu_id, keys;

		new menuUp = player_menu_info(idUser, menu_id, keys);

		// Only display menu if another isn't shown
		if ( menuUp <= 0 || menu_id < 0 )
		{
			WC3_ChangeRaceStart( idUser );
		}

		// Try again in 1 second
		else
		{
			set_task( 1.0, "WC3_GetUserInput", TASK_GETINPUT + idUser );
		}
	}

	// User has skills points available
	else if ( SM_TotalSkillPointsUsed( idUser ) < arrIntData[idUser][P_LEVEL] )
	{
		MENU_SelectSkill( idUser );
	}

	else
	{
		WC3_ShowBar( idUser );
	}

	return;
}

// Function will "reset" the game - i.e. "sv_restart 1"
//Функция срабатывает при рестарте
public WC3_ResetGame()
{
	new players[32], numplayers, idUser, i
	get_players(players, numplayers);

	for ( i=0; i < numplayers; i++ )
	{
		idUser = players[i];
		
		// Remove Ultimate Delay
		task_exists( TASK_UDELAY + idUser ) ? remove_task( TASK_UDELAY + idUser ) : 0;
		
		// User didn't die last round... 
		arrBoolData[idUser][PB_DIEDLASTROUND]		= false;

		//Обнуления заморозки скилов
		arrBoolData[idUser][PB_ISFROZENSKILL]		= false;

		//Обнуления заморозки игрока от Ледяной стрелы
		arrBoolData[idUser][PB_ISFROZENPLAYER]		= false;
		
		// Reset item info
		g_bPlayerBoughtAnkh[idUser]		= false;
		g_bPlayerBoughtMole[idUser]		= false;

		// Remove player's items
		ITEM_Remove( idUser, ITEM_SLOT_ONE );
		ITEM_Remove( idUser, ITEM_SLOT_TWO );
		ITEM_Remove( idUser, ITEM_SLOT_THREE );
		
		arrIntData[idUser][P_HECOUNT]			= 0;
		arrIntData[idUser][P_FLASHCOUNT]		= 0;
	}

	WC3_ShowBar( idUser );

	g_GameRestarting = false;
}

// Function will grab XP for the user
WC3_ChangeRaceStart( idUser )
{	

	// Make sure the user is on a team!
	if ( SHARED_IsOnTeam( idUser ) )
	{
		// This function will also display the changerace menu
		DB_GetAllXP(idUser,MENU_ID_DEFAULT);

		//Для talisman +
		if(arrPlayerInitTalisman[idUser] == false)
		{
			fTalismanInit(idUser);

			arrPlayerInitTalisman[idUser] = true;
		}
		
		
	}
	else
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WC3_CHANGE_RACE_START");
		client_print( idUser, print_center,szMessage);
	}
}

// Function will show the "select a race" menu to the user
WC3_ChangeRaceShowMenu(idUser, iRaceXP[MAX_RACES] = {0},iRaceLevel[MAX_RACES] = {0},iSelectIdMenu = MENU_ID_DEFAULT )
{
	// We don't want to replace the player's current XP with whats in the database now do we ?
	if (arrIntData[idUser][P_RACE] )
	{
		iRaceXP[arrIntData[idUser][P_RACE]-1] = arrIntData[idUser][P_XP];
		iRaceLevel[arrIntData[idUser][P_RACE]-1] = arrIntData[idUser][P_LEVEL];

		//XP_GetLevelByXP(iRaceXP[iMenuID-1])
	}

	//Вызов нового меню рас
	fDisplay_Menu_ChangeRace(idUser,iRaceXP,iRaceLevel,iSelectIdMenu);
}

// This will actually give the user a given race
WC3_SetRace( idUser, race )
{
	// Clear any ultimate icons that might exist
	ULT_ClearIcons( idUser );
	
	//Звуки для рас
	if(iSoundRaceOnOff > 0)
	{
		new szSoundData[255];

		switch(race)
		{
			case RACE_UNDEAD:			ArrayGetString(arrStrSoundRaceData,0, szSoundData, charsmax(szSoundData));
			case RACE_HUMAN:			ArrayGetString(arrStrSoundRaceData,1, szSoundData, charsmax(szSoundData));
			case RACE_ORC:				ArrayGetString(arrStrSoundRaceData,2, szSoundData, charsmax(szSoundData));
			case RACE_ELF:				ArrayGetString(arrStrSoundRaceData,3, szSoundData, charsmax(szSoundData));
			case RACE_BLOOD:			ArrayGetString(arrStrSoundRaceData,4, szSoundData, charsmax(szSoundData));
			case RACE_SHADOW:			ArrayGetString(arrStrSoundRaceData,5, szSoundData, charsmax(szSoundData));
			case RACE_WARDEN:			ArrayGetString(arrStrSoundRaceData,6, szSoundData, charsmax(szSoundData));
			case RACE_CRYPT:			ArrayGetString(arrStrSoundRaceData,7, szSoundData, charsmax(szSoundData));
			case RACE_CHAMELEON:		ArrayGetString(arrStrSoundRaceData,8, szSoundData, charsmax(szSoundData));
			case RACE_FROST_MAGE:		ArrayGetString(arrStrSoundRaceData,9, szSoundData, charsmax(szSoundData));
			case RACE_DEATH_KNIGHT:		ArrayGetString(arrStrSoundRaceData,10, szSoundData, charsmax(szSoundData));
			case RACE_BLACK_MAGICIAN:	ArrayGetString(arrStrSoundRaceData,11, szSoundData, charsmax(szSoundData));
			case RACE_ALCHEMIST:		ArrayGetString(arrStrSoundRaceData,12, szSoundData, charsmax(szSoundData));
			case RACE_PRIEST:			ArrayGetString(arrStrSoundRaceData,13, szSoundData, charsmax(szSoundData));
			case RACE_ROGUE:			ArrayGetString(arrStrSoundRaceData,14, szSoundData, charsmax(szSoundData));
			case RACE_DRUID:			ArrayGetString(arrStrSoundRaceData,15, szSoundData, charsmax(szSoundData));
			case RACE_BLOODSEEKER:		ArrayGetString(arrStrSoundRaceData,16, szSoundData, charsmax(szSoundData));
			case RACE_JUGGERNAUT:		ArrayGetString(arrStrSoundRaceData,17, szSoundData, charsmax(szSoundData));
			case RACE_SNIPER:			ArrayGetString(arrStrSoundRaceData,18, szSoundData, charsmax(szSoundData));
			case RACE_DISRUPTOR:		ArrayGetString(arrStrSoundRaceData,19, szSoundData, charsmax(szSoundData));
			case RACE_RAZOR:			ArrayGetString(arrStrSoundRaceData,20, szSoundData, charsmax(szSoundData));
			case RACE_WARLOCK:			ArrayGetString(arrStrSoundRaceData,21, szSoundData, charsmax(szSoundData));
			case RACE_SHADOW_FIEND:		ArrayGetString(arrStrSoundRaceData,22, szSoundData, charsmax(szSoundData));
			case RACE_24:				ArrayGetString(arrStrSoundRaceData,23, szSoundData, charsmax(szSoundData));
			case RACE_25:				ArrayGetString(arrStrSoundRaceData,24, szSoundData, charsmax(szSoundData));

		}

		if (!equal(szSoundData, ""))
			client_cmd( idUser, "speak %s",szSoundData, 1.0, ATTN_NORM, 0, PITCH_NORM ); 
						
	}
	else
	{
		emit_sound(idUser,CHAN_STATIC, arrStrSounds[SOUND_LEVELUP], 0.1, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);
//		client_cmd( idUser, "speak %s",arrStrSounds[SOUND_LEVELUP], 0.3, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM); 
	}

	// Set the user's race
	arrIntData[idUser][P_RACE] = race

	// Reset all race data
	SM_ResetSkillLevels( idUser );
	SM_ResetSkills( idUser );
	arrIntData[idUser][P_CHANGERACE] = 0

	// This function will assign the race's skills to this player
	SM_SetPlayerRace( idUser, arrIntData[idUser][P_RACE] );
	

	arrIntData[idUser][P_LEVEL] = 0;
	DB_SetDataForRace( idUser );
	
	return;
}

// Function called right after the user's race information is set
WC3_SetRaceUp( idUser )
{
	// Do we need to give this user XP?
	new iStartLevel = get_pcvar_num( CVAR_wc3_start_level );
	if ( arrIntData[idUser][P_XP] == 0 && iStartLevel > 0 && iStartLevel <= iMaxLevels )
	{
		arrIntData[idUser][P_XP] = XP_GetByLevel( iStartLevel );

		format(szMessage, charsmax(szMessage), "%L %d",LANG_PLAYER,"CLIENT_PRINT_WC3_SET_RACE_UP",iStartLevel);	
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

	}

	// Need to check the exception here for randomized chameleon!
	if ( arrIntData[idUser][P_RACE] == RACE_CHAMELEON && get_pcvar_num( CVAR_wc3_cham_random ) )
	{
		// Skill levels were just loaded from the DB - we don't care about these
		SM_ResetSkillLevels( idUser );

		// Fill all skills randomly!
		CHAM_ConfigureSkills( idUser );
	}

	WC3_InitPlayerSkills( idUser );

	// Copy the global ULT timeout over to just this user...
	fSetUltimateDelay(idUser);
	
	// See if there are any skills available
	new iSkillsUsed = SM_TotalSkillPointsUsed( idUser );
	if ( iSkillsUsed < arrIntData[idUser][P_LEVEL] )
	{
		MENU_SelectSkill(idUser);
	}
	
	XP_Check( idUser, false );
	WC3_ShowBar(idUser);
	WC3_ShowRaceInfo(idUser);

	// Show ultimate info if available
	ULT_IconHandler( idUser );
}

public WC3_ShowBar(idUser)
{
	if (idUser >= TASKID_HUDINFO )
		idUser -= TASKID_HUDINFO;

	// User is not connected
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return;

	if (task_exists( TASKID_HUDINFO + idUser) )
		remove_task( TASKID_HUDINFO + idUser );

	new pos = 0, szXPInfo[32],szCurrentItems[32];
	new szItemInfo[256], szRaceInfo[256];
	new szRaceName[64], szShortRaceName[32];//, szItemName[32];

	// Get the race names
	Lang_GetRaceName( arrIntData[idUser][P_RACE], idUser, szRaceName, 63 );
	Lang_GetRaceName( arrIntData[idUser][P_RACE], idUser, szShortRaceName, 31, true );
	

	// Раса не выбрана
	if ( !arrIntData[idUser][P_RACE] )
	{
		pos += formatex( szRaceInfo[pos], 255, "%s ", szRaceName );
	}
	// Игрок выбрал расу
	else
	{

		// User is level 0
		if ( arrIntData[idUser][P_LEVEL] == 0 )
		{
			pos += formatex( szRaceInfo[pos], 255, "%s  XP: %d/%d ", szRaceName, arrIntData[idUser][P_XP], XP_GetByLevel( arrIntData[idUser][P_LEVEL]+1 ) );
			formatex( szXPInfo, 31, "XP: %d/%d", arrIntData[idUser][P_XP], XP_GetByLevel( arrIntData[idUser][P_LEVEL]+1 ) );
		}

		//CSSB
		// User is under level iMaxLevels
		else if ( arrIntData[idUser][P_LEVEL] < iMaxLevels )
		{
			pos += formatex( szRaceInfo[pos], 255, "%s %L: %d   XP: %d/%d ", szShortRaceName, LANG_PLAYER, "WORD_LEVEL", arrIntData[idUser][P_LEVEL], arrIntData[idUser][P_XP], XP_GetByLevel( arrIntData[idUser][P_LEVEL]+1) );
			formatex( szXPInfo, 31, "%L: %d   XP: %d/%d", LANG_PLAYER, "WORD_LEVEL", arrIntData[idUser][P_LEVEL], arrIntData[idUser][P_XP], XP_GetByLevel( arrIntData[idUser][P_LEVEL]+1 ) );
		}			
			
		// User is level iMaxLevels
		else
		{
			pos += formatex( szRaceInfo[pos], 255, "%s %L: %d   XP: %d ", szShortRaceName, LANG_PLAYER, "WORD_LEVEL", arrIntData[idUser][P_LEVEL], arrIntData[idUser][P_XP] );
			formatex( szXPInfo, 31, "%L: %d   XP: %d", LANG_PLAYER, "WORD_LEVEL", arrIntData[idUser][P_LEVEL], arrIntData[idUser][P_XP] );
		}
	}
	
	
	// Reset our position since we're using a new array
	pos = 0;

	new szItemName1[64], szItemName2[64],szItemName3[64];

	// Игрок имеет одну вещь
	if ( g_iShopMenuItems[idUser][ITEM_SLOT_ONE] > ITEM_NONE )
	{
		ITEM_Format( idUser, g_iShopMenuItems[idUser][ITEM_SLOT_ONE], szItemName1,charsmax(szItemName1))

		formatex(szCurrentItems, 31, "%L:",LANG_PLAYER,"WC3_CURRENT_ITEM");
		formatex(szItemInfo, charsmax(szItemInfo), "%s",szItemName1);

		//if(!equali(szItemName1,""))
		//	bIsItem1 = true;
	}
	// Игрок имеет две вещи
	if ( g_iShopMenuItems[idUser][ITEM_SLOT_TWO] > ITEM_NONE )
	{
		ITEM_Format( idUser, g_iShopMenuItems[idUser][ITEM_SLOT_TWO], szItemName2,charsmax(szItemName2) )

		// Then the string isn't empty and we have information in it (so we have a first item)
		if ( g_iShopMenuItems[idUser][ITEM_SLOT_ONE] > ITEM_NONE )
		{
			formatex(szCurrentItems, 31, "%L:",LANG_PLAYER,"WC3_CURRENT_ITEMS" );
			formatex(szItemInfo, charsmax(szItemInfo), "%s %L %s",
					szItemName1,
					LANG_PLAYER, "WORD_AND",
					szItemName2);
		}

		// We don't need the word "and"
		else
		{
			formatex(szItemInfo, charsmax(szItemInfo), "%s",szItemName2);
		}

	}
	// Игрок имеет три вещи
	if ( g_iShopMenuItems[idUser][ITEM_SLOT_THREE] > ITEM_NONE )
	{
		ITEM_Format( idUser, g_iShopMenuItems[idUser][ITEM_SLOT_THREE], szItemName3,charsmax(szItemName3) )
	
		formatex(szCurrentItems, 31, "%L:",LANG_PLAYER,"WC3_CURRENT_ITEMS" );

		new bool:bIsItemSlots = false;
		if ( g_iShopMenuItems[idUser][ITEM_SLOT_ONE] > ITEM_NONE && g_iShopMenuItems[idUser][ITEM_SLOT_TWO] == ITEM_NONE )
		{
			formatex(szItemInfo, charsmax(szItemInfo), "%s %L %s",
					szItemName1,
					LANG_PLAYER, "WORD_AND",
					szItemName3);

			bIsItemSlots = true;
		}

		if ( g_iShopMenuItems[idUser][ITEM_SLOT_TWO] > ITEM_NONE && g_iShopMenuItems[idUser][ITEM_SLOT_ONE] == ITEM_NONE )
		{
			formatex(szItemInfo, charsmax(szItemInfo), "%s %L %s",
					szItemName2,
					LANG_PLAYER, "WORD_AND",
					szItemName3);

			bIsItemSlots = true;
		}

		if ( g_iShopMenuItems[idUser][ITEM_SLOT_ONE] > ITEM_NONE && g_iShopMenuItems[idUser][ITEM_SLOT_TWO] > ITEM_NONE )
		{
			formatex(szItemInfo, charsmax(szItemInfo), "%s,%s,%s",szItemName1,szItemName2,szItemName3);

			bIsItemSlots = true;
		}

		// We don't need the word "and"
		if(bIsItemSlots == false)
		{
			formatex(szItemInfo, charsmax(szItemInfo), "%s",szItemName3);
		}

	}
	
	//Отображение статусной строки
	if (SHARED_IsOnTeam(idUser))
	{
		if (is_user_alive(idUser))
		{
			//Отображение текущего здоровья и брони
			new iCurrentHealth =  clHP:getUserHealth(idUser);
			new iCurrentArmor = clAr:getArmorNum(idUser);

			if(iCurrentHealth > 255 || iCurrentArmor > 255)
			{
				new szMsgHealthArmor[256];
				formatex(szMsgHealthArmor, charsmax(szMsgHealthArmor), 
				 "%L: %d | %L: %d",LANG_PLAYER,"CURRENT_HEALTH",iCurrentHealth,
	 								   LANG_PLAYER,"WORD_ARMOR",iCurrentArmor);

				Create_StatusText(idUser, 0, szMsgHealthArmor);
			}


			//Для talisman +
			new cRed = get_pcvar_num(CVAR_wc3_status_color_R);
			new cGreen = get_pcvar_num(CVAR_wc3_status_color_G);
			new cBlue = get_pcvar_num(CVAR_wc3_status_color_B);

			//Отображение в статусной строке сколько талисманов и какой активен
			new szItemNameShort[32];
			if(arrTalismanActive[idUser] != TALISMAN_ITEM_NONE)
				LANG_GetItemName(arrTalismanActive[idUser], idUser, szItemNameShort, 31, true );
			else
				formatex(szItemNameShort, charsmax(szItemNameShort), "%L",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE_NO");

			new szStringStatusTalisman[256];
			new szShowStatus[256];
			new szCharge[256];

			if(MAX_MODE_TALISMAN == 1 || MAX_MODE_TALISMAN == 2)
			{
				//Отображение для всех игроков чтобы талисманы использовать
				if(arrTalismanActive[idUser] == TALISMAN_ITEM_NECKLACE)
					formatex(szStringStatusTalisman, charsmax(szStringStatusTalisman), "%L[%d]",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE",szItemNameShort,arrTalismanNecklaceNum[idUser]);
				else if(arrTalismanActive[idUser] == TALISMAN_ITEM_HELM)
					formatex(szStringStatusTalisman, charsmax(szStringStatusTalisman), "%L[%d]",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE",szItemNameShort,arrTalismanHelmNum[idUser]);
				else
					formatex(szStringStatusTalisman, charsmax(szStringStatusTalisman), "%L",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE",szItemNameShort);

				switch(arrIntData[idUser][P_RACE])
				{
					case RACE_ROGUE:
						{
							formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_ROGUE_1],arrSkillChargeNum[idUser][SKILL_ROGUE_2],arrSkillChargeNum[idUser][SKILL_ROGUE_3]);
							formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCharge,szCurrentItems, szItemInfo);
						}
					case RACE_DRUID:
						{
							formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_DRUID_1],arrSkillChargeNum[idUser][SKILL_DRUID_2],arrSkillChargeNum[idUser][SKILL_DRUID_3]);
							formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCharge,szCurrentItems, szItemInfo);
						}
					case RACE_BLOODSEEKER:
						{
							formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_BLOODSEEKER_1],arrSkillChargeNum[idUser][SKILL_BLOODSEEKER_2],arrSkillChargeNum[idUser][SKILL_BLOODSEEKER_3]);
							formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCharge,szCurrentItems, szItemInfo);
						}
					case RACE_JUGGERNAUT:
						{
							formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_JUGGERNAUT_1],arrSkillChargeNum[idUser][SKILL_JUGGERNAUT_2],arrSkillChargeNum[idUser][SKILL_JUGGERNAUT_3]);
							formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCharge,szCurrentItems, szItemInfo);
						}					
					case RACE_24:
						{
							formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_24_1],arrSkillChargeNum[idUser][SKILL_24_2],arrSkillChargeNum[idUser][SKILL_24_3]);
							formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCharge,szCurrentItems, szItemInfo);
						}
					case RACE_25:
						{
							formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_25_1],arrSkillChargeNum[idUser][SKILL_25_2],arrSkillChargeNum[idUser][SKILL_25_3]);
							formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCharge,szCurrentItems, szItemInfo);
						}


					default:
						formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCurrentItems, szItemInfo);
				}
				
				set_hudmessage(cRed,cGreen,cBlue,arrPointShowBarRace[0], arrPointShowBarRace[1], HUDMESSAGE_FX_FADEIN, 10.0, 5.0, 2.0, 3.0, HUD_XP);
				show_hudmessage(idUser, szShowStatus);

			}
			else if(MAX_MODE_TALISMAN == 3)
			{
				//Отображение для VIP игроков имеющих статус вип чтобы талисманы использовать
				if((get_user_flags(idUser) & fVipTalisman()))
				{
					if(arrTalismanActive[idUser] == TALISMAN_ITEM_NECKLACE)
						formatex(szStringStatusTalisman, charsmax(szStringStatusTalisman), "%L[%d]",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE",szItemNameShort,arrTalismanNecklaceNum[idUser]);
					else if(arrTalismanActive[idUser] == TALISMAN_ITEM_HELM)
						formatex(szStringStatusTalisman, charsmax(szStringStatusTalisman), "%L[%d]",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE",szItemNameShort,arrTalismanHelmNum[idUser]);
					else
						formatex(szStringStatusTalisman, charsmax(szStringStatusTalisman), "%L",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE",szItemNameShort);


					switch(arrIntData[idUser][P_RACE])
					{
						case RACE_ROGUE:
							{
								formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_ROGUE_1],arrSkillChargeNum[idUser][SKILL_ROGUE_2],arrSkillChargeNum[idUser][SKILL_ROGUE_3]);
								formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCharge,szCurrentItems, szItemInfo);
							}
						case RACE_DRUID:
							{
								formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_DRUID_1],arrSkillChargeNum[idUser][SKILL_DRUID_2],arrSkillChargeNum[idUser][SKILL_DRUID_3]);
								formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCharge,szCurrentItems, szItemInfo);
							}

						default:
							formatex(szShowStatus, charsmax(szShowStatus), "%s^n%s^n%s %s",szRaceInfo,szStringStatusTalisman,szCurrentItems, szItemInfo);
					}
					
					set_hudmessage(cRed,cGreen,cBlue, arrPointShowBarRace[0],arrPointShowBarRace[1], HUDMESSAGE_FX_FADEIN, 10.0, 5.0, 2.0, 3.0, HUD_XP);
					show_hudmessage(idUser, szShowStatus);

				}
				else
				{
					//Отображение для простых игроков не имеющих статуса вип чтобы талисманы использовать
					new szRaceItemInfo[256];
					
					switch(arrIntData[idUser][P_RACE])
					{
						case RACE_ROGUE:
							{
								formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_ROGUE_1],arrSkillChargeNum[idUser][SKILL_ROGUE_2],arrSkillChargeNum[idUser][SKILL_ROGUE_3]);
								formatex( szRaceItemInfo, 255, "%s^n%s^n%s %s", szRaceInfo,szCharge,szCurrentItems, szItemInfo);
							}
						case RACE_DRUID:
							{
								formatex(szCharge, charsmax(szCharge), "%L",LANG_PLAYER,"WC3_CHARGE",arrSkillChargeNum[idUser][SKILL_DRUID_1],arrSkillChargeNum[idUser][SKILL_DRUID_2],arrSkillChargeNum[idUser][SKILL_DRUID_3]);
								formatex( szRaceItemInfo, 255, "%s^n%s^n%s %s", szRaceInfo,szCharge,szCurrentItems, szItemInfo);
							}

						default:
							formatex( szRaceItemInfo, 255, "%s^n%s %s", szRaceInfo,szCurrentItems, szItemInfo);
					}

					set_hudmessage(cRed,cGreen,cBlue, arrPointShowBarRace[0], arrPointShowBarRace[1], HUDMESSAGE_FX_FADEIN, 10.0, 5.0, 2.0, 3.0, HUD_XP);
					show_hudmessage(idUser, szRaceItemInfo);

				}
			}

		}
		else
		{
			set_hudmessage( 160, 160, 160, 0.012, 0.90, HUDMESSAGE_FX_FADEIN, 10.0, 0.0, 2.0, 3.0, HUD_XP );
			show_hudmessage( idUser, "%s", szXPInfo );
		}

		set_task(10.0, "WC3_ShowBar", idUser + TASKID_HUDINFO);
	}	

	return;
}

// Function will display the level information in the center of the user's screen
WC3_ShowRaceInfo( idUser )
{
	if ( arrIntData[idUser][P_RACE] != 0 )
	{
		new szSkillName[64], iSkillLevel;

		new szTrainable[256],	szUltimate[256],	szPassive[256];
		new posT = 0,			posU = 0,			posP = 0;

		// Loop through all available skills to find the trainable options...
		for ( new iSkillID = 0; iSkillID < MAX_SKILLS; iSkillID++ )
		{
			// Get the skill's level
			iSkillLevel = SM_GetSkillLevel( idUser, iSkillID);

			// If the skill level is > 0 then the user has this skill!
			if ( iSkillLevel > 0 )
			{
				// Get the skill's name
				LANG_GetSkillName( iSkillID , idUser, szSkillName, 63, 19 );

				// Trainable skill
				if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_TRAINABLE )
				{
					posT += formatex( szTrainable[posT], 255-posT, "^n%s %L %d", szSkillName, LANG_PLAYER, "WORD_LEVEL", iSkillLevel );
				}

				// Skill is an ultimate
				else if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_ULTIMATE && iSkillLevel > 0 )
				{
					posU += formatex( szUltimate[posU], 255-posU, "^n%L: %s", LANG_PLAYER, "WORD_ULTIMATE", szSkillName );
				}

				// Skill is passive
				else if ( SM_GetSkillType( iSkillID ) == SKILL_TYPE_PASSIVE )
				{
					posP += formatex( szPassive[posP], 255-posP, "^n%s", szSkillName );
				}
			}
		}

		// Get the race's name
		new szRaceName[64];
		Lang_GetRaceName( arrIntData[idUser][P_RACE], idUser, szRaceName, 63 );
		
		// Add the header
		new szMsg[1024];
		formatex( szMsg, 1023, "%s^n%L %d", szRaceName, LANG_PLAYER, "WORD_LEVEL", arrIntData[idUser][P_LEVEL] );

		// Add all the skills to the message!
		strcat( szMsg, szTrainable, 1023 );
		strcat( szMsg, szUltimate, 1023 );
		strcat( szMsg, szPassive, 1023 );


		WC3_StatusText( idUser, TXT_RACE_INFO, szMsg );
	}
	
	// User has no race
	else
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WC3_RACE_FIRST");
		WC3_StatusText( idUser, TXT_RACE_INFO,szMessage);
	}
}

// Function simply checks if an enemy of idUser is near vOrigin and has a necklace/warden's blink
WC3_IsImmunePlayerNear(idUser, vOrigin[3] )
{
	new players[32], numplayers, vTargetOrigin[3], i;
	new iTeam = get_user_team( idUser );

	// Get all players
	get_players( players, numplayers, "a" );
	
	// Loop through all players and check for immunity
	for ( i = 0; i < numplayers; i++ )
	{
		
		// Make sure that the user we're looking at is on the opposite team of "idUser"
		if ( get_user_team( players[i] ) != iTeam )
		{	
			get_user_origin( players[i], vTargetOrigin );
			
			// Check the distance
			if ( get_distance( vOrigin, vTargetOrigin ) <= IMMUNITY_RADIUS )
			{

				// Does this player have a necklace or warden's blink?
				if ( ULT_CanUserBlockUlt(players[i],idUser))
				{
					return players[i];
				}
			}
		}
	}

	return 0;
}

WC3_ResetSkills( idUser )
{
	// Reset the user's skills
	if ( arrBoolData[idUser][PB_RESETSKILLS] ) 
	{
		arrIntData[idUser][P_LEVEL]		= 0;
		SM_ResetSkillLevels( idUser );

		WC3_ShowBar( idUser );
		XP_Check( idUser, false );

		arrBoolData[idUser][PB_RESETSKILLS] = false;

		return 1;
	}

	return 0;
}

WC3_ShowSpecInfo( idUser, iTargetID )
{
	// Get the target's name
	new szTargetName[32];
	get_user_name( iTargetID, szTargetName, 31 ); 
	
	// Get the target's race name
	new szRaceName[64];
	Lang_GetRaceName( arrIntData[iTargetID][P_RACE], idUser, szRaceName, 63, true );
	
	new szMsg[512], iMsgPos = 0;

	// User is level 0
	if ( arrIntData[iTargetID][P_LEVEL] == 0 )
	{
		iMsgPos += formatex( szMsg, 511, "%s  XP: %d/%d", szRaceName, arrIntData[iTargetID][P_XP], XP_GetByLevel( arrIntData[iTargetID][P_LEVEL]+1 ) );
	}

	//CSSB
	// User is under level iMaxLevels
	else if ( arrIntData[iTargetID][P_LEVEL] < iMaxLevels )
	{
		iMsgPos += formatex( szMsg, 511, "%s %L: %d   XP: %d/%d", szRaceName, LANG_PLAYER, "WORD_LEVEL", arrIntData[iTargetID][P_LEVEL], arrIntData[iTargetID][P_XP], XP_GetByLevel( arrIntData[iTargetID][P_LEVEL]+1 ) );
	}			
		
	// User is level iMaxLevels
	else
	{
		iMsgPos += formatex( szMsg, 511, "%s %L: %d   XP: %d", szRaceName, LANG_PLAYER, "WORD_LEVEL", arrIntData[iTargetID][P_LEVEL], arrIntData[iTargetID][P_XP] );
	}
	
	//CSSB
	// Reset our position counter
	//new pos = 0;

	new szItemName[32], szItemName2[32],szItemName3[32],szCurrentItems[32];

	// Get the item and race names
	LANG_GetItemName( g_iShopMenuItems[iTargetID][ITEM_SLOT_ONE], idUser, szItemName, 31, true );
	LANG_GetItemName( g_iShopMenuItems[iTargetID][ITEM_SLOT_TWO], idUser, szItemName2, 31, true );
	LANG_GetItemName( g_iShopMenuItems[iTargetID][ITEM_SLOT_THREE], idUser, szItemName3, 31, true );
	
	new bool:ItemSlotOne = false;
	new bool:ItemSlotTwo = false;
	new bool:HasMoreThanOneRing = false;
	
	if ( g_iTotalRings[iTargetID] > 1 )
		HasMoreThanOneRing = true;

	//Игрок имеет однин предмет
	if ( g_iShopMenuItems[iTargetID][ITEM_SLOT_ONE] > ITEM_NONE && g_iShopMenuItems[iTargetID][ITEM_SLOT_ONE] != ITEM_MOLE )
	{
		formatex(szCurrentItems, 31, "%L:",LANG_PLAYER,"WC3_CURRENT_ITEMS" );

		// Then they have rings, lets print how many there are
		if ( HasMoreThanOneRing && g_iShopMenuItems[iTargetID][ITEM_SLOT_ONE] == ITEM_RING )
			iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, "^n%s %s x%d",szCurrentItems, szItemName, g_iTotalRings[iTargetID] );
		else
			iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, "^n%s %s",szCurrentItems, szItemName );

		ItemSlotOne = true;
	}

	//Игрок имеет два предмета
	if ( g_iShopMenuItems[iTargetID][ITEM_SLOT_TWO] > ITEM_NONE && g_iShopMenuItems[iTargetID][ITEM_SLOT_TWO] != ITEM_MOLE )
	{
		// Then the string isn't empty and we have information in it (so we have a first item)
		if ( ItemSlotOne )
		{

			// Then they have rings, lets print how many there are
			if (HasMoreThanOneRing && g_iShopMenuItems[iTargetID][ITEM_SLOT_TWO] == ITEM_RING)
				iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, " %L %s x%d", LANG_PLAYER, "WORD_AND", szItemName2, g_iTotalRings[iTargetID] );
			else
				iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, " %L %s", LANG_PLAYER, "WORD_AND", szItemName2 );

			ItemSlotTwo = true;
		}
		// We don't need the word "and"
		else
		{
			formatex(szCurrentItems, 31, "%L:",LANG_PLAYER,"WC3_CURRENT_ITEMS" );
			
			// Then they have rings, lets print how many there are
			if (HasMoreThanOneRing && g_iShopMenuItems[iTargetID][ITEM_SLOT_TWO] == ITEM_RING)
				iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, "^n%s %s x%d",szCurrentItems, szItemName2, g_iTotalRings[iTargetID] );
			else
				iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, "^n%s %s",szCurrentItems, szItemName2 );
			
		}
		
	}

	//Игрок имеет три предмета
	if ( g_iShopMenuItems[iTargetID][ITEM_SLOT_THREE] > ITEM_NONE && g_iShopMenuItems[iTargetID][ITEM_SLOT_THREE] != ITEM_MOLE )
	{
		// Then the string isn't empty and we have information in it (so we have a first item)
		if ( ItemSlotOne == true && ItemSlotTwo == true )
		{
			// Then they have rings, lets print how many there are
			if (HasMoreThanOneRing && g_iShopMenuItems[iTargetID][ITEM_SLOT_THREE] == ITEM_RING)
				iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, " %L %s x%d", LANG_PLAYER, "WORD_AND", szItemName3, g_iTotalRings[iTargetID] );
			else
				iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, " %L %s", LANG_PLAYER, "WORD_AND", szItemName3 );
			
		}
		// We don't need the word "and"
		else
		{
			formatex(szCurrentItems, 31, "%L:",LANG_PLAYER,"WC3_CURRENT_ITEMS" );
			
			// Then they have rings, lets print how many there are
			if (HasMoreThanOneRing && g_iShopMenuItems[iTargetID][ITEM_SLOT_THREE] == ITEM_RING)
				iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, "^n%s %s x%d",szCurrentItems, szItemName3, g_iTotalRings[iTargetID] );
			else
				iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, "^n%s %s",szCurrentItems, szItemName3 );	
			
		}
		
	}

	//Для talisman +
	// Add the Health + Armor to the message
	iMsgPos += formatex( szMsg[iMsgPos], 512-iMsgPos, "^n%L: %d %L: %d", LANG_PLAYER, "CURRENT_HEALTH", clHP:getUserHealth( iTargetID ), LANG_PLAYER, "WORD_ARMOR", clAr:getArmorNum(iTargetID));
		
	// Format the message
	new Float:fSpecTime = SPEC_HOLDTIME;

	if (get_pcvar_num( CVAR_wc3_spec_position ) == 0 )
		set_hudmessage( 255, 255, 255, 0.018, 0.89, 2, 1.5, fSpecTime, 0.02, 5.0, HUD_SPEC_INFO );
	else
		set_hudmessage( 255, 255, 255, 0.65, 0.89, 2, 1.5, fSpecTime, 0.02, 5.0, HUD_SPEC_INFO );

	//Отображение в статусной строке сколько талисманов и какой активен
	new szItemNameShort[32];
	if(arrTalismanActive[iTargetID] != TALISMAN_ITEM_NONE)
		LANG_GetItemName(arrTalismanActive[iTargetID], iTargetID, szItemNameShort, 31, true );
	else
		formatex(szItemNameShort, charsmax(szItemNameShort), "%L",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE_NO");

	if(MAX_MODE_TALISMAN == 1)
	{
		iMsgPos += formatex(szMsg[iMsgPos], 512-iMsgPos, "^n%L^n%L",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE",szItemNameShort,LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_NUM",arrTalismanNum[iTargetID]);
		show_hudmessage(idUser, szMsg);
	}
	else if(MAX_MODE_TALISMAN == 2)
	{
		iMsgPos += formatex(szMsg[iMsgPos], 512-iMsgPos, "^n%L",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE",szItemNameShort);
		show_hudmessage(idUser, szMsg);
	}
	else if(MAX_MODE_TALISMAN == 3)
	{
		if((get_user_flags(iTargetID) & fVipTalisman()))
		{
			iMsgPos += formatex(szMsg[iMsgPos], 512-iMsgPos, "^n%L",LANG_PLAYER,"WC3_SHOW_STATUS_TALISMAN_ACTIVE",szItemNameShort);
			show_hudmessage(idUser, szMsg);
		}
		else
		{
			show_hudmessage(idUser, szMsg );
		}
	}

}

// Function will print a message in the center of the screen
WC3_StatusText( idUser, iType, const fmt[], ... )
{
	static szFormattedText[512];

	vformat( szFormattedText, 511, fmt, 4 );

	// I.E. "You have gained a level"
	if ( iType == TXT_TOP_CENTER )
		set_hudmessage( 200, 100, 0, -1.0, 0.25, HUDMESSAGE_FX_FADEIN, 1.0, 2.0, 0.1, 0.2, HUD_AUTO );
	// I.E. /level
	else if ( iType == TXT_RACE_INFO )
		set_hudmessage( 255, 255, 255, -1.0, 0.3, HUDMESSAGE_FX_FADEIN, 3.0, 5.0, 0.1, 0.2, HUD_RACE_INFO );
	// Ultimate messages
	else if ( iType == TXT_ULTIMATE )
		set_hudmessage( 255, 208, 0, -1.0, 0.85, HUDMESSAGE_FX_FADEIN, 6.0, 0.5, 0.1, 0.5, HUD_ULTIMATE );
	// I.E. Suicide Bomb Armed
	else if ( iType == TXT_BLINK_CENTER )
		set_hudmessage( 79, 209, 204, -1.0, -0.4, HUDMESSAGE_FX_FLICKER, 0.5, 1.7, 0.2, 0.2, HUD_AUTO );
	// I.E. "You have evaded a shot"
	else if ( iType == TXT_SKILL )
		set_hudmessage( 0, 0, 255, 0.75, 0.85, HUDMESSAGE_FX_FADEIN, 6.0, 3.0, 0.2, 0.7, HUD_SKILL );
	// I.E.
	else if ( iType == TXT_TIMER )
		set_hudmessage( 0, 100, 0, 0.05, 0.65, HUDMESSAGE_FX_WRITEOUT, 0.02, 10.0, 0.01, 0.1, HUD_TIMER );	
	else if ( iType == ICE_BLOCK_TIMER )
		set_hudmessage( 0, 206, 209, 0.05, 0.55, HUDMESSAGE_FX_FLICKER, 0.5, 2.0, 0.2, 0.2, HUD_AUTO );
	// All other cases
	else
		set_hudmessage( 255, 255, 10, -1.0, -0.4, HUDMESSAGE_FX_FLICKER, 0.5, 2.0, 0.2, 0.2, HUD_AUTO );

	show_hudmessage( idUser, szFormattedText );

}

public WC3_Damage(idVictim, idAttacker, iDamage, iWeapon, iBodyPart )
{
	// We have an invalid attacker/victim, that sucks...
	if (idAttacker == 0 || idVictim == 0)
		return;
	
	// User is not alive, why damage them more?
	if (!is_user_alive( idVictim ) )
		return;

	
	#if MODE_LOG
		clLog:logMagicDamage(idVictim,idAttacker,iDamage,0);
	#endif


	// Don't damage if we shouldn't!
	if ( arrBoolData[idVictim][PB_NO_DAMAGE] )
		return;

	// Warden's Hardened Skin
	iDamage = WA_HardenedSkin(idVictim,iDamage);

	//Рыцарь смерти
	if(arrIntData[idVictim][P_RACE] == RACE_DEATH_KNIGHT)
	{
		if(clRaceDeathKnight::bIsUnDamageBP[idVictim] == true)
			iDamage = iDamage - floatround(iDamage * fPercentUndamage);
	}


	if (iBodyPart == -1 )
		iBodyPart = random_num( 1, 7 );

	// Modify the amount of damage done based on the user's armor
	new Float:fNewDamage	= float( iDamage ) * ARMOR_RATIO;
	new Float:fArmorLost	= ( float( iDamage ) - fNewDamage ) * ARMOR_BONUS;
	new Float:fCurrentArmor	= float( clAr:getArmorNum( idVictim ) );

	// Does this use more armor than we have?
	if ( fArmorLost > fCurrentArmor )
	{
		fArmorLost = fCurrentArmor;
		fArmorLost *= ( 1 / ARMOR_BONUS );

		fNewDamage = float( iDamage ) - fArmorLost;

		clAr:setUserArmor(idVictim, 0);
	}
	else
	{
		new iNewArmor = floatround( fCurrentArmor - (3.0 * fArmorLost));

		clAr:setUserArmor(idVictim, iNewArmor);
	}

	iDamage = floatround( fNewDamage );


	new iHeadshot = 0;
	if (iBodyPart == 1 )
		iHeadshot = 1;

	// Psychostats Statistics is turned on!
	if ( get_pcvar_num( CVAR_wc3_psychostats ) )
	{
		if ( CSW_WAR3_MIN <= iWeapon <= CSW_WAR3_MAX )
		{
			new iSkillWeapon = iWeapon - CSW_WAR3_MIN;
			
			// Make the "generic" the stomach
			if ( iBodyPart == -1 )
			{
				iBodyPart = HIT_STOMACH;
			}
		
			if ( iBodyPart == HIT_HEAD )
			{
				iStatsHead[idAttacker][iSkillWeapon]++;
			}
			else if ( iBodyPart == HIT_CHEST )
			{
				iStatsChest[idAttacker][iSkillWeapon]++;
			}
			else if ( iBodyPart == HIT_STOMACH )
			{
				iStatsStomach[idAttacker][iSkillWeapon]++;
			}
			else if ( iBodyPart == HIT_LEFTARM )
			{
				iStatsLeftArm[idAttacker][iSkillWeapon]++;
			}
			else if ( iBodyPart == HIT_RIGHTARM )
			{
				iStatsRightArm[idAttacker][iSkillWeapon]++;
			}
			else if ( iBodyPart == HIT_LEFTLEG )
			{
				iStatsLeftLeg[idAttacker][iSkillWeapon]++;
			}
			else if ( iBodyPart == HIT_RIGHTLEG )
			{
				iStatsRightLeg[idAttacker][iSkillWeapon]++;
			}

			iStatsHits[idAttacker][iSkillWeapon]++;
			iStatsShots[idAttacker][iSkillWeapon]++;
			iStatsDamage[idAttacker][iSkillWeapon] += iDamage;
		}
	}

	//Стандартный код
	// Magical damage should go toward kill assist
	g_iDamageDealt[idAttacker][idVictim] += iDamage;

	new iHealth = clHP:getUserHealth( idVictim );
	
	// User has been killed
	if ( iHealth - iDamage <= 0 )
		WC3_Kill(idVictim, idAttacker, iWeapon, iHeadshot );
	else
		clHP:setUserHealth(idVictim,iHealth - iDamage);
	

	return;
}

public WC3_Death(idVictim, idKiller, iWeaponID, iHeadshot )
{
	new Float:ptOriginCorpse[3];	
	pev(idVictim, pev_origin, ptOriginCorpse);
	
	ArrayPushCell(arrOriginCorpse_X,ptOriginCorpse[0]);
	ArrayPushCell(arrOriginCorpse_Y,ptOriginCorpse[1]);
	ArrayPushCell(arrOriginCorpse_Z,ptOriginCorpse[2]);

	// Award XP	
	XP_onDeath(idVictim, idKiller, iWeaponID, iHeadshot );

	// Reset the "about to spawn" variable
	arrIntData[idVictim][P_RESPAWNBY] = 0;
	
	// Remove the bar time if the user dies during god mode (in theory this shouldn't be possible)
	if (arrBoolData[idVictim][PB_GODMODE])
		Create_BarTime(idVictim, 0, 0 );

	// Lets give a little extra money if CSDM is on...
	if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 )
		SHARED_SetUserMoney( idKiller, SHARED_GetUserMoney( idKiller ) + 300, 1 );

	// Give the bot a chance to respawn
	if ( is_user_bot( idVictim ) )
	{
		if ( random_float(0.01, 1.0 ) <= BOT_RESPAWN )
		{
			_MENU_Shopmenu2( idVictim, ITEM_SCROLL - 1 );
		}
	}

	// Remove icon because you don't have an ultimate when you're dead
	ULT_Icon( idVictim, ICON_HIDE );	

	// Player is no longer a mole after they die, right?
	arrBoolData[idVictim][PB_MOLE] = false;

	// Yes the user died...
	arrBoolData[idVictim][PB_DIEDLASTROUND] = true;

	// Suicide Bomber should go off when the user dies
	if ( SM_GetSkillLevel( idVictim, ULTIMATE_SUICIDE ) > 0 )
	{	
		if(isDisabledSkillsOnMap(idVictim,ULTIMATE_SUICIDE) == false)
		{
			if ( arrBoolData[idVictim][PB_HEXED] )
			{
				WC3_StatusText( idVictim, TXT_ULTIMATE, "%L", LANG_PLAYER, "HEX_NO_ABILITY" );
				client_cmd( idVictim, "speak %s", arrStrSounds[SOUND_ERROR] );
			}
			else
			{
				UD_Suicide( idVictim );
			}
		}
	}

	// *******************************************************
	// Супер навык - Слово Тьмы: Смерть - Darkness word: Death
	// *******************************************************
	if (SM_GetSkillLevel( idVictim, ULTIMATE_PRIEST_DARKNESS_WORD_DEATH ) > 0 )
	{	
		if(isDisabledSkillsOnMap(idVictim,ULTIMATE_PRIEST_DARKNESS_WORD_DEATH) == false)
			clRacePriest::ultDarkWordDeath(idVictim);
	}
	
	// Check to see if a player should be revived
	BM_PhoenixSpawn( idVictim );

	// Does the user have a scroll?
	if ( ITEM_Has( idVictim, ITEM_SCROLL ) > ITEM_NONE )
	{
		ITEM_Scroll(idVictim);
	}

	// Should we respawn for Vengeance?
	if ( SM_GetSkillLevel(idVictim, ULTIMATE_VENGEANCE ) > 0 && idKiller != idVictim && !g_EndRound &&
		 isDisabledSkillsOnMap(idVictim,ULTIMATE_VENGEANCE) == false
	   )
	{
		// Killer has immunity, user shouldn't respawn :/
		if ( ULT_CanUserBlockUlt( idKiller,idVictim ) )
		{
			ULT_RemoveCharge(idKiller);
		
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_WC3_DEATH");	
			cssbChatColor(idVictim,"%s%s",fTagWar3ft(),szMessage);
				
		}
		
		// User can't use their ultimate when they're hexed
		else if ( arrBoolData[idVictim][PB_HEXED] )
		{
			WC3_StatusText( idVictim, TXT_ULTIMATE, "%L", LANG_PLAYER, "HEX_NO_ABILITY" );
		
			client_cmd( idVictim, "speak %s", arrStrSounds[SOUND_ERROR] );
		}
		
		// Otherwise lets spawn them!!!
		else
		{
			WA_ULT_Vengeance(idVictim);
		}
	}

	// Remove hex if the user is hexed
	if ( arrBoolData[idVictim][PB_HEXED] )
	{
		if ( task_exists( TASK_HEX + idVictim) )
		{
			remove_task( TASK_HEX + idVictim );
		}

		_SH_RemoveHex( idVictim + TASK_HEX );
	}


	if (task_exists(clRaceDeathKnight::taskID_BLOOD_PRESENCE + idVictim))
	{
		remove_task(clRaceDeathKnight::taskID_BLOOD_PRESENCE + idVictim);

		clRaceDeathKnight::bIsDamageBP[idVictim] = false;
		clRaceDeathKnight::bIsUnDamageBP[idVictim] = false;
		
	}

	// Удаление заморозки скилов
	if ( arrBoolData[idVictim][PB_ISFROZENSKILL] == true )
	{
		if (task_exists( TASK_FROZEN_SKILL + idVictim) )
			remove_task( TASK_FROZEN_SKILL + idVictim );

		fRemoveFrozenSkill( idVictim + TASK_FROZEN_SKILL );
	}

	// Удаление заморозки от Скила Ледяная стрела
	if ( arrBoolData[idVictim][PB_ISFROZENPLAYER] == true )
	{
		if (task_exists( TASK_REMOVE_FROZEN + idVictim) )
			remove_task( TASK_REMOVE_FROZEN + idVictim );

		fRemoveFreeze(idVictim + TASK_REMOVE_FROZEN );
	}

	if(bIsUserRace(idVictim,RACE_ROGUE))
	{
		if (task_exists(clRogue::tID_VANISH + idVictim))
			remove_task(clRogue::tID_VANISH + idVictim );

		clRogue::taskResetVanish(clRogue::tID_VANISH + idVictim);

		uDeleteAllEntClassnameUser(BALL_CLASSNAME,idVictim);
		uDeleteAllEntClassnameUser(BEAM_CLASSNAME,idVictim);

	}

	if(bIsUserRace(idVictim,RACE_DRUID))
	{
		uDeleteAllEntClassnameUser("Wild_Mushroom",idVictim);
		uDeleteAllEntClassnameUser("AstralStorm",idVictim);
	}

	if(bIsUserRace(idVictim,RACE_BLOODSEEKER))
	{
		uDeleteAllEntClassnameUser("Wild_Mushroom",idVictim);

		if (task_exists(clBloodseeker::tID_BLOODRAGE + idVictim))
		{
			remove_task(clBloodseeker::tID_BLOODRAGE + idVictim );
			clBloodseeker::taskResetBloodRage(clBloodseeker::tID_BLOODRAGE + idVictim);
		}
		if (task_exists(clBloodseeker::tID_BLOODRITE_A + idVictim))
		{
			remove_task(clBloodseeker::tID_BLOODRITE_A + idVictim );
			clBloodseeker::taskResetBloodRiteA(clBloodseeker::tID_BLOODRITE_A + idVictim);
		}
	}

	if(bIsUserRace(idVictim,RACE_JUGGERNAUT))
	{
		uDeleteAllEntClassnameMap(HEALING_WARD_CLASSNAME);
	}

	if (task_exists(clBloodseeker::tID_BLOODRITE_V + idVictim))
	{
		remove_task(clBloodseeker::tID_BLOODRITE_V + idVictim );
		clBloodseeker::taskResetBloodRiteV(clBloodseeker::tID_BLOODRITE_V + idVictim);
	}

	if(bIsUserRace(idKiller,RACE_BLOODSEEKER))
		clBloodseeker::skillBloodBath(idKiller,idVictim,SKILL_BLOODSEEKER_2);

	if(bIsUserRace(idVictim,RACE_SNIPER))
	{
		uDeleteAllEntClassnameUser(SHRAPNEL_SNIPER_CLASSNAME,idVictim);
		UTIL_AutoHideMenu(idVictim);
	}

	if(bIsUserRace(idVictim,RACE_SHADOW_FIEND))
		uDeleteAllEntClassnameUser(NECROMASTERY_SHADOW_FIEND_CLASSNAME,idVictim);
			
	//Сброс модели если игрок скелет
	if(sm4_IsPlayerSkeleton(idVictim) == true)
		cssbResetPlayerModel(idVictim);
	

////Выпадение предметов BEGIN {

	if(get_pcvar_num( CVAR_wc3_loot_items ) > 0)
	{
		//Определение какие предметы были у жертвы	
		//Для shopmenu
		new iVictimItemShop1 = bIsItemUserSlot(idVictim,ITEM_SLOT_ONE);
		//Для shopmenu2
		new iVictimItemShop2 = bIsItemUserSlot(idVictim,ITEM_SLOT_TWO);
		//Для shopmenu3
		new iVictimItemShop3 = bIsItemUserSlot(idVictim,ITEM_SLOT_THREE);

		//Проверка на наличие вещей
		new bIsDropItems = fIsDropItems(iVictimItemShop1,iVictimItemShop2,iVictimItemShop3);
		if(bIsDropItems != 0)//Если есть предметы
		{
			if (random_num(0, 100 ) <= get_pcvar_num( CVAR_wc3_loot_items_percent ) ) 
			{
				ArrayPushCell(arrIntItemVictimShop1, iVictimItemShop1);
				ArrayPushCell(arrIntItemVictimShop2, iVictimItemShop2);
				ArrayPushCell(arrIntItemVictimShop3,iVictimItemShop3);
				ArrayPushCell(arrIntDrawSpriteItems, idSpriteItems);
				ArrayPushCell(arrIntScaleSpriteItems, 8);

				if (get_pcvar_num( CVAR_wc3_loot_remove ) == 1)
					ArrayPushCell(arrIntLootRemove, get_pcvar_num( CVAR_wc3_loot_stay ));
				

				
				fCreateItemsClass(idVictim);
			
			}

		}
		else//Если нет предметов
		{
			if(get_pcvar_num( CVAR_wc3_loot_items ) == 2)
			{
				if (random_num(0, 100 ) <= get_pcvar_num( CVAR_wc3_loot_ar_hp_xp_percent ) ) 
				{
					ArrayPushCell(arrIntItemVictimShop1, iVictimItemShop1);
					ArrayPushCell(arrIntItemVictimShop2, iVictimItemShop2);
					ArrayPushCell(arrIntItemVictimShop3,iVictimItemShop3);
					ArrayPushCell(arrIntDrawSpriteItems, idSpriteNoItems);
					ArrayPushCell(arrIntScaleSpriteItems, 3);

					if (get_pcvar_num( CVAR_wc3_loot_remove ) == 1)
						ArrayPushCell(arrIntLootRemove, get_pcvar_num( CVAR_wc3_loot_stay ));

					fCreateArXpHpClass(idVictim);

				}
			}
		}
		
		
	}

//Выпадение предметов END }
		
	//Удаление из массива скелета если жертва им является
	sm4_RemoveSkeleton(idVictim);

	//Остановка работы предмета Спокойствие
	sm4_4_9_fRemoveSpellCasting( idVictim );
	remove_task( TASK_TRANQUILITY + idVictim );

	ITEM_UserDied( idVictim );

	//Для talisman +
	fTalismanUserDied(idVictim);
	
	set_task( 1.0, "WC3_GetUserInput", TASK_GETINPUT + idVictim );

	return;
}

public WC3_Kill( idVictim, iKiller, iWeapon, iHeadshot )
{
	new szWpnName[64], iRet = 0;
	UTIL_GetWeaponName( iWeapon, szWpnName, 63 );
	ExecuteForward( fwd_ReportKill, iRet, iKiller, idVictim, iWeapon, szWpnName );

	// Save stats information?
	if ( get_pcvar_num( CVAR_wc3_psychostats ) )
	{
		if ( CSW_WAR3_MIN <= iWeapon <= CSW_WAR3_MAX )
		{
			new iSkillWeapon = iWeapon - CSW_WAR3_MIN;
			
			if ( SHARED_ValidPlayer( iKiller ) )
			{

				// Team kill
				if ( get_user_team( idVictim ) == get_user_team( iKiller ) )
				{
					iStatsTKS[iKiller][iSkillWeapon]++;
				}

				// Random chance so some skills that aren't headshots have a chance
				if ( ( iHeadshot || random_num( 0, 100 ) < 30 ) )
				{
					iStatsHS[iKiller][iSkillWeapon]++;
				}

				iStatsKills[iKiller][iSkillWeapon]++;
			}

			iStatsDeaths[iKiller][iSkillWeapon]++;
		}
	}

	// Remove all ultimate icons since the user is going to be killed...
	ULT_ClearIcons( idVictim );

	new iVictimTeam = get_user_team( idVictim );
	new iKillerTeam = get_user_team( iKiller );

	// Create Death Message
	if ( is_user_alive( idVictim ) )
	{
		// Kill Victim
		WC3_KillUser( idVictim, iKiller, iWeapon );

		// Update frags ( realtime )
		new iVictimFrags = get_user_frags( idVictim );

		new iVictimDeaths = get_user_deaths( idVictim );

		Create_ScoreInfo( idVictim, iVictimFrags, iVictimDeaths, 0, iVictimTeam );

		// Get the weapon name
		new szWeaponName[256];
		UTIL_GetWeaponName( iWeapon, szWeaponName, charsmax(szWeaponName) );

		Create_DeathMsg_CS( iKiller, idVictim, iHeadshot, szWeaponName );
	}

	// Call all war3 functions when the user dies
 	WC3_Death( idVictim, iKiller, iWeapon, iHeadshot );

	// Award $300 for a Kill
	// Make sure they're not on the same team
	if ( iVictimTeam != iKillerTeam && iKiller != idVictim )
		SHARED_SetUserMoney( iKiller, SHARED_GetUserMoney( iKiller ) + 300, 1 );

	// Get the killer's frags
	new iKillerFrags = get_user_frags( iKiller ) + 1;

	// Team Kill
	if ( iVictimTeam == iKillerTeam && iKiller != idVictim )
	{
		// Remove one from the killer's frags

		iKillerFrags = get_user_frags( iKiller ) - 2; // (-2 since when we init'd it was +1)

		set_user_frags( iKiller, iKillerFrags );
	}

	// Update frags ( realtime )
	if ( is_user_connected( iKiller ) )
	{
		new iKillerDeaths = get_user_deaths( iKiller );
		
		// If we don't do this then next round the number of kills will go back to what it was
		set_user_frags( iKiller, iKillerFrags );

		// Updates realtime
		Create_ScoreInfo( iKiller, iKillerFrags, iKillerDeaths, 0, iKillerTeam );
	}

	// Log it so psychostats can pick the death up...
	UTIL_LogDeath( idVictim, iKiller, iWeapon );

	return;
}

public WC3_KillUser( idVictim, iKiller, iWeapon )
{
	

	set_msg_block(gmsgDeathMsg, BLOCK_ONCE );

	user_kill( idVictim, 1 );

}

// Funtion will check a file to see if the mapname exists
bool:WC3_MapDisableCheck( szFileName[] )
{
	// Format the Orc Nade Disable File
	new szFile[128];
	get_configsdir( szFile, 127 );
	formatex( szFile, 127, "%s/war3ft/disable/%s", szFile, szFileName );

	if ( !file_exists( szFile ) )
		return false;

	new iLineNum, szData[64], iTextLen, iLen;
	new szMapName[64], szRestrictName[64];
	get_mapname( szMapName, 63 );

	while ( read_file( szFile, iLineNum, szData, 63, iTextLen ) )
	{
		iLen = copyc( szRestrictName, 63, szData, '*' );

		if ( equali( szMapName, szRestrictName, iLen ) )
		{
			return true;
		}

		iLineNum++;
	}

	return false;
}


// This function can be called at ANY time to configure and/or remove skills for a given race
//Срабатывает при каждом спавне
WC3_InitPlayerSkills(idUser)
{
	// Undead's Unholy Aura
	SHARED_SetSpeed( idUser );

	// Undead's Levitation
	SHARED_SetGravity( idUser );
	
	// Human's Invisibility
	SHARED_INVIS_Set( idUser );
	
	// Human's Health
	HU_DevotionAura( idUser );

	// Blood Mage's Phoenix
	BM_PhoenixCheck( idUser );

	// Shadow Hunter's Healing Wave
	SH_HealingWave( idUser );

	//  Скил 2 уровня - Blood Boil - Вскипание крови
	clRaceDeathKnight::skillBloodBoil(idUser);

	// Скил 1 уровня - Presence of the Dark Lord - Присутствие Темного Лорда
	clShadowFiend::skillPresenceDL(idUser);

	// Shadow Hunter's Serpent Ward
	SH_SerpentWard( idUser );

	// Warden's Blink
	WA_Blink( idUser );

	// Скил 3 уровня - Кинетическое поле - Kinetic Field
	clDisruptor::skillKineticField(idUser);

	// Скил 1 уровня - Fatal Bonds - Фатальная связь
	clWarlock::skillFatalBonds(idUser);

	// Скил 4 уровня - Манна небесная - Manna
	if(bIsUserRace(idUser,RACE_RAZOR))
		clRazor::skillManna(idUser);
	

	// Stop all ultimates if the user shouldn't have an ultimate!
	new iUltimateID = SM_GetSkillOfType( idUser, SKILL_TYPE_ULTIMATE );
	if ( iUltimateID > -1 && SM_GetSkillLevel( idUser, iUltimateID) <= 0 )
	{
		ULT_Reset( idUser );
	}

	//Считывание файла users_vips.ini при ициализации
	fInitVipsUsersSkills();
}

// Function called right before the user spawns - ONLY ON NEW ROUND!
// Вызывается до респауна только в новом раунде
WC3_BeforeSpawn(idUser)
{
	// Remove the spectating info if necessary
	if ( g_fLastSpecDisplay[idUser] >= halflife_time() )
	{
		UTIL_ClearHudChannel( idUser, HUD_SPEC_INFO );
		UTIL_ClearDHudChannel( idUser );
	}

	//Обнуления заморозки скилов
	arrBoolData[idUser][PB_ISFROZENSKILL]		= false;

	//Обнуления заморозки игрока от Ледяной стрелы
	arrBoolData[idUser][PB_ISFROZENPLAYER]		= false;

	// Reset who the user was spectating
	g_iSpectatingID[idUser] = -1;

	// Reset the player's role
	g_iPlayerRole[idUser] = 0;
	
	// User shouldn't be a mole anymore...
	arrBoolData[idUser][PB_MOLE] = false;

	// Reset the bomb/defusing check
	bHasBegunPlantingOrDefusing[idUser] = false;

	// Reset all ultimates
	ULT_Reset( idUser );

	// Reset certain player variables
	arrBoolData[idUser][PB_HAS_SPAWNED]		= false;
	arrIntData[idUser][P_RESPAWNBY]				= 0;

	// Remove any reset_maxspeeds occuring (could cause a person to move during freezetime)
	task_exists( TASK_RESETSPEED + idUser ) ? remove_task( TASK_RESETSPEED + idUser ) : 0;
	
	// Save a copy of what weapons the user had the previous round (for weapon reincarnation)
	SHARED_CopySavedWeapons( idUser );

	// Remove any serpant wards
	( task_exists( TASK_LIGHT + idUser ) ) ? remove_task( TASK_LIGHT + idUser ) : 0;
}

// This is called at the START of a user spawning
// Вызывается перед респауном
WC3_PreSpawn( idUser )
{
	// Reset human's devotion aura - this needs to be done here
	//  - If we don't do it here, then a user can get > 145 health... i.e. 190
	g_HU_DevotionAuraGiven[idUser]	= 0;

	//Если игрок сменил расу, выбранные предметы и талисманы будут сброшены
	if(arrBoolData[idUser][PB_CHANGE_RESET_RACE])
	{	
		arrTalismanActive[idUser] = TALISMAN_ITEM_NONE;
		arrTalismanChange[idUser] = TALISMAN_ITEM_NONE;

		ITEM_Remove(idUser, ITEM_SLOT_ONE);
		ITEM_Remove(idUser, ITEM_SLOT_TWO);
		ITEM_Remove(idUser, ITEM_SLOT_THREE);

		arrBoolData[idUser][PB_CHANGE_RESET_RACE] = false;

		g_bPlayerBoughtAnkh[idUser] = false;		// User didn't buy an ankh!
		g_bPlayerBoughtMole[idUser] = false;		// User didn't buy mole!
	}

}

// This is called at the end of someone spawning - i.e. NewSession called before this
// Вызывается после респауна
WC3_PostSpawn(idUser)
{
	// These things need to be reset when the user spawns
	WC3_ResetOnSpawn( idUser );

	// Do we need to give the user a gravity boost?
	SHARED_SetGravity( idUser );

	// Set the user's speed!
	SHARED_SetSpeed( idUser );

	// Give the user their item bonuses!
	ITEM_GiveAllBonuses(idUser);
	
	//Для talisman +
	fPostSpawnTalisman(idUser);

	//Для авто закупки предметов
	if(bAutoBuyOnOff[idUser] == true)
		fBuyAllItems(idUser);

	//Остановка работы предмета Спокойствие
	sm4_4_9_fRemoveSpellCasting( idUser );
	remove_task( TASK_TRANQUILITY + idUser );


	//Раса Жрец
	arrFireWeapon[idUser] = iFireNumAmmo;
	arrIsWorkFireWeapon[idUser] = false;
	

	//Добавлен SH_HealingWave если CSDM активен
	if (( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 ))
	{
		SH_HealingWave(idUser);

		// Скил 2 уровня - Blood Boil - Вскипание крови
		clRaceDeathKnight::skillBloodBoil(idUser);

		// Скил 1 уровня - Presence of the Dark Lord - Присутствие Темного Лорда
		clShadowFiend::skillPresenceDL(idUser);
	}

	arrIntData[idUser][P_HECOUNT]		= 0;
		
	// If we need to give the user their weapons back, then lets
	SHARED_CS_Reincarnation(idUser);

	// If the user's ultimate is ready, lets show their icon!
	ULT_IconHandler( idUser );
	
	// Check for bomb on the back of chameleon
	if ( arrBoolData[idUser][PB_SKINSWITCHED] )
		entity_set_int(idUser, EV_INT_body, 0);


	// If the user is a bot they should have a chance to buy an item
	if ( is_user_bot( idUser ) )
	{
		new Float:fBotChance = get_pcvar_float( CVAR_wc3_bot_buy_item );

		if ( fBotChance > 0 && random_float(0.01, 1.0 ) <= fBotChance )
		{
			( random_num( 1, 2 ) == 1 ) ? _MENU_Shopmenu1( idUser, random_num( 0, 8 ) ) : _MENU_Shopmenu2( idUser, random_num( 0, 8 ) );
		}
	}

	// Find out if they need to choose a race or select a skill
	set_task( 0.3, "WC3_GetUserInput", TASK_GETINPUT + idUser );

	// Set this last - otherwise some skills might be screwed up
	arrBoolData[idUser][PB_DIEDLASTROUND]	= false;

	if (( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 ))
		WC3_NewSession( idUser );

	//Если игрок сменил команду раса и все остальное будет сброшено
	if (arrBoolData[idUser][PB_CHANGE_TEAM_RESET_RACE] == true)
		WC3_PlayerInit(idUser);
				

	if(bIsUserRace(idUser,RACE_SNIPER) && iRoundCount > iRoundCountAwp)
		clSniper::skillElephantGun(idUser);
	
	//Установка здоровья и брони героям
	clHP:setCurRespawnRaceHealth(idUser);
	clAr:setCurRespawnRaceArmor(idUser);

	clVIP:fInitItemsAccessVip(idUser);

	//client_print(idUser,print_chat,"WC3_PostSpawn OK");
}

// Configure this player
//   - this should be called whenever a "new round" begins, for example:
//		CSDM - whenever anyone spawns
//		Normal CS/CZ - @ start of new round
WC3_NewSession(idUser)
{
	
	// If it's a bot, should we change the race?
	if ( is_user_bot( idUser ) )
	{
		// Give the bot some random XP if we're saving XP
		if (!arrIntData[idUser][P_XP] )
			arrIntData[idUser][P_XP] = XP_GetByLevel( floatround(random_float(0.01,3.16)*random_float(0.01,3.16)) );
			
		
		arrIntData[idUser][P_RACE] = random_num(1, MAX_RACES - 3);
			
		// Now lets set the bot's race!
		WC3_SetRace( idUser, arrIntData[idUser][P_RACE] );
		
	}

	// Reset Assist XP handler!
	for ( new i = 0; i < MAXPLAYERS; i++ )
		g_iDamageDealt[idUser][i] = 0;
	
	// Ultimate cooldown on session start!
	// CSDM isn't running!
	if ( ! ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 ) )
		fSetUltimateDelay(idUser);
	
	// Should we mole b/c of an item?
	SHARED_MoleCheck( idUser, true );			// Only check item!

	// Reset some shizit!
	WC3_ResetOnNewSession( idUser );

	new bool:bChangedRace = false;

	// User has a race selection pending, set it
	//	- Changing race should get priority over reseting skills!
	if ( arrIntData[idUser][P_CHANGERACE] )
	{
		WC3_SetRace( idUser, arrIntData[idUser][P_CHANGERACE] );
		
		bChangedRace = true;

		if ( arrBoolData[idUser][PB_RESETSKILLS] )
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_PB_RESETSKILLS");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			
			arrBoolData[idUser][PB_RESETSKILLS] = false;
		}
	}

	// Reset user skills if we need to
	if ( WC3_ResetSkills( idUser ) )
	{
		// We need to return here b/c we don't want to set everyones' abilities!
		return;
	}

	// Should we mole b/c of an ability?
	SHARED_MoleCheck( idUser );			// Check skill
	
	// If we made it this far we need to configure the user's skills!
	// Set the user's skills!
	if ( !bChangedRace )
	{
		// This is called when we set a player's race - so we don't need to call it if their race was changed!
		WC3_InitPlayerSkills( idUser );
	}
}

WC3_ResetOnNewSession(idUser)
{
	

	// Shadow Hunter's Serpent Wards
	arrIntData[idUser][P_SERPENTCOUNT]	= 0;
	g_SH_SerpentGiven[idUser]		= 0;

	// Warden's shouldn't default being immune
	arrBoolData[idUser][PB_WARDENBLINK] = false;
	arrBoolData[idUser][PB_KINETIC_FIELD] = false;
	
	arrIntData[idUser][PB_SHADOW_WORD_NUM] = 0;
	arrIntData[idUser][PB_SHADOW_WORD_TIME] = 0;

	arrIntData[idUser][PB_REQUIEM_SOULS_NUM] = 0;
	arrIntData[idUser][PB_REQUIEM_SOULS_TIME] = 0;
	
}

WC3_ResetOnSpawn( idUser )
{
	fDeleteBlockItemTalisman(idUser);

	// Human should gain health when he spawns right?
	HU_DevotionAura( idUser );

	// User isn't changing a team if they just spawned
	arrBoolData[idUser][PB_CHANGINGTEAM]	= false;

	// Reset suicide attempt
	arrBoolData[idUser][PB_SUICIDEATTEMPT] = false;
	
	// User should not be burning
	arrBoolData[idUser][PB_ISBURNING]		= false;
	arrIntData[idUser][P_FLAMECOUNT] = 0;

	// The user should not be frozen when they spawn
	SHARED_ResetMaxSpeed( idUser );

	// Reset the user's skin
	SHARED_ChangeSkin( idUser, SKIN_RESET );

	// User won't be zoomed when they spawn!
	g_bPlayerZoomed[idUser]				= false;

	//client_print(idUser,print_chat,"WC3_ResetOnSpawn");

	
}

// Called when a player first joins the server! - we need to reset everything!
//Функция срабатывает когда игрок подсоединяется к серверу т.е. сбрасываются все значения
WC3_PlayerInit(idUser)
{
	clVIP:fInitItemsAccessVip(idUser);

	clDruid::setChargeNum(idUser);
	clRogue::setChargeNum(idUser);
	clBloodseeker::setChargeNum(idUser);
	clJuggernaut::setChargeNum(idUser);

	// Reset all skill information for this player!
	SM_ResetSkillLevels( idUser );
	SM_ResetSkills(idUser);

	// This player shouldn't have a race/level or xp yet! - I mean they did just join duh!
	arrIntData[idUser][P_RACE]					= 0;
	arrIntData[idUser][P_LEVEL]					= 0;
	arrIntData[idUser][P_XP]					= 0;

	g_SH_SerpentGiven[idUser]			= 0;			// Shadow Hunter's Serpent Ward - Amount given
	arrIntData[idUser][P_SERPENTCOUNT]		= 0;			// Shadow Hunter's Serpent Ward - Total the user currently has

	arrBoolData[idUser][PB_WARDENBLINK]	= false;		// Warden's Blink - Shouldn't start off immune right?  duh!
	arrBoolData[idUser][PB_KINETIC_FIELD] = false;
	
	arrIntData[idUser][PB_SHADOW_WORD_NUM] = 0;
	arrIntData[idUser][PB_SHADOW_WORD_TIME] = 0;
	
	arrIntData[idUser][PB_REQUIEM_SOULS_NUM] = 0;
	arrIntData[idUser][PB_REQUIEM_SOULS_TIME] = 0;

	g_bLevitation[idUser]				= true;			// By default a user's levitation should be enabled!


	g_iSpectatingID[idUser] = -1;						// Reset who the user was spectating

	g_iPlayerRole[idUser] = 0;							// Reset the player's role
	
	arrBoolData[idUser][PB_MOLE] = false;					// User shouldn't be a mole anymore...

	bHasBegunPlantingOrDefusing[idUser] = false;		// Reset the bomb/defusing check

	arrBoolData[idUser][PB_HAS_SPAWNED]	= false;		// Has the user spawned?  nope
	
	arrIntData[idUser][P_RESPAWNBY]			= 0;			// What did they respawn by?  Nothing I hope the user just joined!

	bIgnorePlayerSpawning[idUser]		= false;		// We don't want to ignore when the player spawns do we?

	g_ULT_iLastIconShown[idUser]		= 0;			// User hasn't shown an icon yet!


	// Misc Item shizit
	g_bPlayerBoughtAnkh[idUser]			= false;		// User didn't buy an ankh!
	g_bPlayerBoughtMole[idUser]			= false;		// User didn't buy mole!

	arrBoolData[idUser][PB_LIGHTNINGHIT]	= false;		// User wasn't hit by lightning!  They just joined!

	arrBoolData[idUser][PB_NO_DAMAGE]		= false;		// User should be damaged

	g_iDBPlayerUniqueID[idUser]			= 0;			// Reset the user's UniqueID

	for ( new i = 0; i < MAXPLAYERS; i++ )
		g_iDamageDealt[idUser][i]		= 0;			// Reset damage dealt

	arrIntData[idUser][P_CHANGERACE]		= 0;			// User shouldn't have a changerace pending

	bDBXPRetrieved[idUser]				= false;		// User hasn't gotten his/her XP since he's being reset right?

	arrBoolData[idUser][PB_BIGBAD_ATTACKER]	= false;	// User isn't allowed to attack someone running it duh!

	// Reset charges!
	g_iTotalRings[idUser]				= 0;
	g_iNecklaceCharges[idUser]			= 0;
	g_iHelmCharges[idUser]				= 0;

	//Для shopmenu3
	arriTotalRingsGrenadeProtection[idUser] = 0;		// Количество колец защиты от гранат
	arrDeathTouch[idUser] = false;						// Прикосновение смерти

	//Для shopmenu4
	arriTotalRingsDevourerLight[idUser] = 0;			// Массив зарядов пожирателя змей
	arriTotalChargeMirrorUltimate[idUser] = 0;			// Массив зарядов отражателя супер навыка
	arriTotalChargeDeathCoil[idUser] = 0;				// Массив зарядов Лик смерти
	arriTotalChargeImpale[idUser] = 0;					// Массив зарядов Пронзающий Шип
	arriTotalChargeSleep[idUser] = 0;					// Массив зарядов Сонная аура
	g_iPlayerTeam[idUser]				= -1;			// Player doesn't have a team yet! So reset it!
	
	fPlayerInitTalisman(idUser);

	//Для авто закупки предметов
	abi_InitDataAutoBuy(idUser);

	clRaceDeathKnight::bIsDamageBP[idUser] = false;
	clRaceDeathKnight::bIsUnDamageBP[idUser] = false;

	arrBoolData[idUser][PB_CHANGE_TEAM_RESET_RACE]	= false;
	arrBoolData[idUser][PB_CHANGE_RESET_RACE]	= false;
	
	bNomole[idUser] = false;		// (включение\отключение скила крота у шпиона)
	bSilentHeal[idUser] = false;	// (включение\отключение лечения от охотника)
}

// Function will simply log to a file as well as amxx log
WC3_Log( bool:bAmxx, const fmt[], ... )
{
	static szFormattedText[512];
	vformat( szFormattedText, 511, fmt, 3 );

	// Write to amxx log file
	if ( bAmxx )
	{
		log_amx(szFormattedText);
	}

	new szLogFile[128];
	get_configsdir( szLogFile, 127 );
	formatex(szLogFile, 127, "%s/war3ft/logs/wc3_error.log", szLogFile);
}