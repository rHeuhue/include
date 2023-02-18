// ******************************************************************
// Инициализация при загрузке плагина
// ******************************************************************


public plugin_init()
{
	register_plugin( WC3_NAME, WC3_VERSION, WC3_AUTHOR );
		
	gmsgDeathMsg		= get_user_msgid( "DeathMsg"	);
	gmsgScreenFade		= get_user_msgid( "ScreenFade"	);
	gmsgScreenShake		= get_user_msgid( "ScreenShake"	);
	gmsgScoreInfo		= get_user_msgid( "ScoreInfo"	);
	
	iFakeMeta_ModuleRunning = is_module_loaded("FakeMeta");


	////////////Тесты различных функций }
	
	mfBuyForward	= CreateMultiForward("mfClientBuyWeapons",	ET_STOP, FP_CELL, FP_CELL);
	mfSelectRace	= CreateMultiForward("mfSelectRace",		ET_STOP, FP_CELL, FP_CELL);
	mfSpawn			= CreateMultiForward("mfSpawn",				ET_STOP, FP_CELL, FP_CELL);
	mfChangeSkin	= CreateMultiForward("mfChangeSkin",		ET_STOP, FP_CELL, FP_CELL);

			
	register_clcmd("showvipmenu"		, "CMD_Handler"		, -1 );

	register_clcmd("menuselect", "fMenuBuyWeapons");
	
	register_clcmd( "cssb_version"		, "CMD_Handler"		, -1 );
	
	register_clcmd( "silentheal"		, "CMD_Handler"		, -1 );
	register_clcmd( "nomole"			, "CMD_Handler"		, -1 );
	
	register_clcmd( "autobuyitems"		, "CMD_Handler"		, -1 );//Для авто закупки предметов
	register_clcmd( "talisman"			, "CMD_Handler"		, -1 );	
	register_concmd( "playerskills"		, "CMD_Handler"		, -1 );

//	register_clcmd( "debug"				, "CMD_Handler"		, -1 );
	register_clcmd( "levitation"		, "CMD_Handler"		, -1 );
	register_clcmd( "war3menu"			, "CMD_Handler"		, -1 );
	register_clcmd( "changerace"		, "CMD_Handler"		, -1 );
	register_clcmd( "selectskill"		, "CMD_Handler"		, -1 );
	register_clcmd( "skillsinfo"		, "CMD_Handler"		, -1 );
	register_clcmd( "resetskills"		, "CMD_Handler"		, -1 );
	register_clcmd( "resetxp"			, "CMD_Handler"		, -1 );
	register_clcmd( "war3menuitems"		, "CMD_Handler"		, -1 );
	register_clcmd( "shopmenu"			, "CMD_Handler"		, -1 );
	register_clcmd( "shopmenu2"			, "CMD_Handler"		, -1 );
	register_clcmd( "shopmenu3"			, "CMD_Handler"		, -1 );
	register_clcmd( "shopmenu4"			, "CMD_Handler"		, -1 );	
	register_clcmd( "ability"			, "CMD_Handler"		, -1 );
	register_clcmd( "ankh"				, "CMD_Handler"		, -1 );
	register_clcmd( "amulet"			, "CMD_Handler"		, -1 );
	register_clcmd( "boots"				, "CMD_Handler"		, -1 );
	register_clcmd( "claws"				, "CMD_Handler"		, -1 );
	register_clcmd( "cloak"				, "CMD_Handler"		, -1 );
	register_clcmd( "chameleon"			, "CMD_Handler"		, -1 );
	register_clcmd( "frost"				, "CMD_Handler"		, -1 );
	register_clcmd( "gloves"			, "CMD_Handler"		, -1 );
	register_clcmd( "health"			, "CMD_Handler"		, -1 );
	register_clcmd( "helm"				, "CMD_Handler"		, -1 );
	register_clcmd( "mask"				, "CMD_Handler"		, -1 );
	register_clcmd( "mole"				, "CMD_Handler"		, -1 );
	register_clcmd( "necklace"			, "CMD_Handler"		, -1 );
	register_clcmd( "rings"				, "CMD_Handler"		, -1 );
	register_clcmd( "socks"				, "CMD_Handler"		, -1 );
	register_clcmd( "scroll"			, "CMD_Handler"		, -1 );
	register_clcmd( "molepr"			, "CMD_Handler"		, -1 );
	register_clcmd( "tome"				, "CMD_Handler"		, -1 );
	register_clcmd( "level"				, "CMD_Handler"		, -1 );
	register_clcmd( "say"				, "cmd_Say"			, -1 );
	register_clcmd( "say_team"			, "cmd_Say"			, -1 );
	register_clcmd( "war3help"			, "CMD_Handler"		, -1 );
	register_clcmd( "ultimate"			, "cmd_Ultimate"	, -1 );
	register_clcmd( "fullupdate"		, "cmd_fullupdate"	, -1 );
	register_clcmd( "drop"				, "on_Drop"			, -1 );
	register_clcmd( "jointeam"			, "cmd_Jointeam"	, -1 );

	//Для shopmenu3
	register_clcmd( "brain"				, "CMD_Handler"		, -1 );
	register_clcmd( "nogren"			, "CMD_Handler"		, -1 );
	register_clcmd( "mirror"			, "CMD_Handler"		, -1 );
	register_clcmd( "esp"				, "CMD_Handler"		, -1 );
	register_clcmd( "farmor"			, "CMD_Handler"		, -1 );
	register_clcmd( "deathtouch"		, "CMD_Handler"		, -1 );
	register_clcmd( "hpp"				, "CMD_Handler"		, -1 );
	register_clcmd( "ulttimediv"		, "CMD_Handler"		, -1 );
	register_clcmd( "steelskin"			, "CMD_Handler"		, -1 );
	
	//Для shopmenu4
	register_clcmd( "devlight"		, "CMD_Handler"		, -1 );
	register_clcmd( "iceblock"		, "CMD_Handler"		, -1 );
	register_clcmd( "thief"			, "CMD_Handler"		, -1 );
	register_clcmd( "mirrorult"		, "CMD_Handler"		, -1 );
	register_clcmd( "deathcoil"		, "CMD_Handler"		, -1 );
	register_clcmd( "impale"		, "CMD_Handler"		, -1 );
	register_clcmd( "sleep"			, "CMD_Handler"		, -1 );
	register_clcmd( "skeletons"		, "CMD_Handler"		, -1 );
	register_clcmd( "tranquility"	, "CMD_Handler"		, -1 );
		
	
			
	// Admin Commands
	register_concmd( "wc3_givexp"		, "ADMIN_Handler"		, -1 , " -- Gives XP to players"				);
	register_concmd( "wc3_setlevel"	    , "ADMIN_Handler"		, -1 , " -- Sets a player's level"				);
	register_concmd( "wc3_giveitem"		, "ADMIN_Handler"		, -1 , " -- Gives an item to a player"			);
	register_concmd( "wc3_enable"		, "ADMIN_Handler"		, -1 , " -- Enables war3ft"						);
	register_concmd( "wc3_disable"		, "ADMIN_Handler"		, -1 , " -- Disables war3ft"					);
	//Для talisman 
	register_concmd( "wc3_givetalisman"	, "ADMIN_Handler"		, -1 , " -- Gives an talisman to a player"			);	
	
	
	// Depreciated Admin Commands
	register_concmd( "amx_givexp"		, "ADMIN_Handler"		, -1 , " -- Gives XP to players"				);

	// Server Admin Commands (used by external plugins)
	register_srvcmd( "amx_takexp"		, "ADMIN_ServerHandler"	);
	register_srvcmd( "changexp"			, "ADMIN_ServerHandler"	);

	//FM Форварды
	register_forward(FM_TraceLine, "TRIGGER_TraceLine");
	register_forward(FM_Touch,"player_Touch");
	register_forward(FM_SetModel,"fwSetModel",1); //sm4

	register_forward(FM_SetClientKeyValue, "fwSetClientKeyValue");
	
	
	
	//HAM Форварды
	RegisterHam(Ham_TakeDamage, "player", "EVENT_TakeDamage" );
	RegisterHam(Ham_Spawn, "player", "EVENT_Spawn", 1);
	RegisterHam(Ham_Killed, "player", "fwHamKilled");
	RegisterHam(Ham_CS_RoundRespawn, "player", "fwRoundRespawn", 1);
	RegisterHam(Ham_TraceAttack, "player", "fwTraceAttack", 1);
	RegisterHam(Ham_Player_ResetMaxSpeed,"player","fwHamPlayerResetMaxSpeed",1); //sm4
	RegisterHam(Ham_Think,"grenade","fwHamThinkGrenade",0); //sm4
	RegisterHam(Ham_Use, "player_weaponstrip", "fwHamUsePlayerWeaponstrip", 1); //sm4
	RegisterHam(Ham_Item_Deploy, "weapon_flashbang", "fwHamItemDeployFlashBang", 1); //sm4
	RegisterHam(Ham_Item_Holster, "weapon_flashbang", "fwHamItemHolsterFlashBang", 1); //sm4
	RegisterHam(Ham_Item_AddToPlayer, "weapon_flashbang", "fwHamItemAddToPlayerFlashBang", 1); //sm4
	RegisterHam(Ham_Item_AddDuplicate, "weapon_flashbang", "fwHamItemAddDuplicateFlashBang", 1); //sm4
	RegisterHam(Ham_Player_PreThink,	"player",	"fwHamPlayerPreThink" ); //sm4

	//Снайпер
	RegisterHam(Ham_Touch, "weaponbox", "fwHamPlayerWeaponTouch"); 
	register_touch(SHRAPNEL_SNIPER_CLASSNAME, "*", "touchShrapnel");
	
	//Джагернаут
	register_think(HEALING_WARD_CLASSNAME, "thinkHealingWard");
	register_touch(CRITICAL_BLADE_CLASSNAME, "*", "touchCriticalBlade");
	
	//Разрушитель
	register_think(STATIC_STORM_DISRUPTOR_CLASSNAME, "thinkStaticStorm");
	register_touch(STATIC_STORM_DISRUPTOR_CLASSNAME, "*", "touchStaticStorm");
	
	//Блэйд
	register_think(PLASMA_FIELD_RAZOR_CLASSNAME, "thinkPlasmaField");
	register_touch(PLASMA_FIELD_RAZOR_CLASSNAME, "*", "touchPlasmaField");

	//Варлок
	register_touch(PERM_IMMOL_WARLOCK_CLASSNAME, "*", "touchPermImmolation");
	
	//Невермор
	register_think(NECROMASTERY_SHADOW_FIEND_CLASSNAME, "thinkNecromastery");
	register_touch(NECROMASTERY_SHADOW_FIEND_CLASSNAME, "player", "touchNecromastery");
	
	
	//Друид
	register_think("Wild_Mushroom", "thinkWildMushroom");
	register_touch("AstralStorm", "*", "touchAstralStorm");
	
	//Разбойник
	register_think(BALL_CLASSNAME, "ShurikenBall_Think");
	register_think(BEAM_CLASSNAME, "ShurikenBeam_Think");
	register_touch(BALL_CLASSNAME, "*", "ShurikenBall_Explode_Touch");
	
	//Для расы Жнец
	RegisterHam(Ham_TraceAttack, "player", "fwHamTraceAttackPriest",1);
	for (new i = 0; i < sizeof WEAPON_CLASSNAME; i++)
	{
		if (strlen(WEAPON_CLASSNAME[i]) == 0)
			continue;
		
		RegisterHam(Ham_Weapon_PrimaryAttack, WEAPON_CLASSNAME[i], "fwHamWeapPriAttack");
	}
	
	//Жрец
	register_touch("entBallFire", "*", "touchBallFire");
	register_think("_entBallFire", "thinkBallFire");
	
	//Touch (Скил 2 Ледяная стрела)
	register_touch("IceArrow","*","touchIceArrow");
	
	//Touch (Лик смерти)
	register_touch( "DEATH_COIL",   "*", "touchDeathCoil" );//sm4
	
	//Черный маг
	register_touch("bmdisk","*","touchBmDisk");

	//Для talisman
	register_think("war3ft_talisman", "Talisman_Think");
	stSyncHudCreate = CreateHudSyncObj();
		
	//Сообщения
	register_message(get_user_msgid("DeathMsg"),"msgDeathMessage");
	register_message(get_user_msgid("Health"), "msgHealth");
	register_message(get_user_msgid("Battery"), "msgArmor");
	


	//События
	register_event( "DeathMsg"			, "on_DeathMsg"		, "a"								);
	register_event( "CurWeapon"			, "on_CurWeapon"	, "be"	, "1=1"						);
	register_event( "HideWeapon"		, "on_CurWeapon"	, "b"								);
//	register_event( "ResetHUD"			, "on_ResetHud"		, "be"								);
	register_event( "TextMsg"			, "on_GameRestart"	, "a"	, "2&#Game_will_restart_in" );
	register_event( "HLTV"				, "EVENT_NewRound"	, "a"	, "1=0"	,			"2=0"	);
	register_event( "ResetHUD"			, "evResetHud"		, "b"								); //sm4
	
	
	//Create HudSyncObj
	msgSyncObj = CreateHudSyncObj();
	
	register_dictionary( "cssbWar3ftMod.txt");
	register_dictionary( "cssbWar3ftHelp.txt");
	register_dictionary( "cssbWar3ftVip.txt");

	// Game Specific Initialization
	gmsgBarTime			= get_user_msgid( "BarTime"		);
	gmsgStatusText		= get_user_msgid( "StatusText"	);
	gmsgStatusIcon		= get_user_msgid( "StatusIcon"	);

	register_logevent( "on_PlayerAction"		, 3		, "1=triggered"								);
	register_logevent( "on_FreezeTimeComplete"	, 2		, "0=World triggered"	, "1=Round_Start"	);
	register_logevent( "on_EndRound"			, 2		, "0=World triggered"	, "1=Round_End"		);
			
	register_event( "SendAudio"		, "on_TerroristWin"		, "a"	, "2=%!MRAD_terwin"					);
	register_event( "SendAudio"		, "on_CTWin"			, "a"	, "2=%!MRAD_ctwin"					);
	register_event( "ArmorType"		, "on_ArmorType"		, "be"										);
	register_event( "Battery"		, "on_Battery"			, "be"										);
	register_event( "WeapPickup"	, "on_WeapPickup"		, "b"										); 
	register_event( "StatusValue"	, "on_ShowStatus"		, "be"	, "1=2"		,"2!0"					);
	register_event( "StatusValue"	, "on_HideStatus"		, "be"	, "1=1"		,"2=0"					);
	register_event( "SetFOV"		, "on_Zoom"				, "be"										);
	register_event( "BarTime"		, "on_BombPlanting"		, "be"	, "1=3"								);
	register_event( "BarTime"		, "on_BombStopPlanting"	, "b"	, "1=0"								);

	//Отлов смены команды
	register_event( "TeamInfo" , "evTeamInfo" , "a" );
	 
	// Old Style
	register_menucmd( register_menuid( "BuyItem" )	, (1<<3)	, "cmd_hegren"	);

	// VGUI
	register_menucmd( -34	, (1<<3)	, "cmd_hegren"	);

	// Steam
	register_clcmd( "hegren"	, "cmd_hegren"	);
	
	// Old style menu (now its jointeam client command)
	register_menucmd( register_menuid( "Team_Select" , 1 )	, (1<<0)|(1<<1)|(1<<4)	, "cmd_Teamselect" );

	register_event("TextMsg", "on_GameRestart", "a", "2&#Game_C");
	
	// Plugin initialization procedures
	WC3_Init();
	
		
	//Инициализация массивов для различных целей
	clGl::fInitArraysGlobal();
}