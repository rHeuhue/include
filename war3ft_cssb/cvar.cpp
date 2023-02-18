/*
*	CVAR Functions
*/

// Half-Life CVARs
new CVAR_mp_friendlyfire;
new CVAR_sv_gravity;

// Other plugin CVARs
new CVAR_csdm_active;

// Miscellaneous Configuration CVARs
new CVAR_wc3_query_client;
new CVAR_wc3_show_player;
new CVAR_wc3_buy_dead;
new CVAR_wc3_buy_time;
new CVAR_wc3_buy_zone;
new CVAR_wc3_spec_position;
new CVAR_wc3_grenade_protection;
new CVAR_wc3_cheats;
new CVAR_wc3_psychostats;
//new CVAR_wc3_race_limit;
new CVAR_wc3_start_level;

// Admin CVARs
new CVAR_wc3_admin_flag;

// XP CVARs
new CVAR_wc3_min_players;
new CVAR_wc3_ignore_bots;
new CVAR_wc3_xp_multiplier;
new CVAR_wc3_show_kill_obj;
new CVAR_wc3_show_objectives;

// XP Saving CVARs
new CVAR_wc3_save_pruning;
new CVAR_wc3_days_before_delete;
new CVAR_wc3_save_by;
new CVAR_wc3_save_xp_db;

// Database CVARs
new CVAR_wc3_sql_dbhost;
new CVAR_wc3_sql_dbuser;
new CVAR_wc3_sql_dbpass;
new CVAR_wc3_sql_dbname;
new CVAR_wc3_save_end_round;

// Ultimate CVARs
new CVAR_wc3_entangle_drop;
new CVAR_wc3_blink_protection;
new CVAR_wc3_blink_dizziness;

// Items
new CVAR_wc3_tome;
new CVAR_wc3_boots;
new CVAR_wc3_claw;
new CVAR_wc3_health;
new CVAR_wc3_frost;
new CVAR_wc3_mask;
new CVAR_wc3_cloak;
new CVAR_wc3_sock;
new CVAR_wc3_glove_timer;
new CVAR_wc3_glove_orc_damage;

// Chameleon
new CVAR_wc3_cham_random;
new CVAR_wc3_cham_skill1;
new CVAR_wc3_cham_skill2;
new CVAR_wc3_cham_skill3;
new CVAR_wc3_cham_ultimate;
new CVAR_wc3_cham_passive;

// Bot CVARs
new CVAR_wc3_bot_buy_item;

//��������� ��������� � �������
new CVAR_wc3_loot_items;
new CVAR_wc3_loot_items_percent;
new CVAR_wc3_loot_ar_hp_xp_percent;
new CVAR_wc3_loot_items_health;
new CVAR_wc3_loot_items_armor;
new CVAR_wc3_loot_remove;
new CVAR_wc3_loot_stay;


//����� � ��� ���������� � �������
new CVAR_wc3_info_killer_onoff;
new CVAR_wc3_info_killer_flags;

//��� Respawn ��������
//�������� ���������� ������ � ���� � ��� ������� �������� Ankh of Reincarnation
new CVAR_wc3_respawn_onoff;

//����������� ��������� ������ (����� ���� � ���������)
new CVAR_wc3_status_color_R;
new CVAR_wc3_status_color_G;
new CVAR_wc3_status_color_B;

//��������� ������� ��� ��������� ����������� (��� ��� ������,�����,�������,����,����)
new CVAR_wc3_glowshell_time;
new CVAR_wc3_glowshell_amount;

//����� XP ��� �����
new	CVAR_wc3_bonus_xp;	//������� XP ����� �������� ������������ 1.1 = 110%
new	CVAR_wc3_bonus_xp_flag;	//���� ������� � ������ XP

//���������� ������ ����� ������:
new CVAR_wc3_show_winner;	//����������� ���������� ���������� � ����� ������

//���� �� ��������
new CVAR_wc3_cost_ankh;	//Ankh of Reincarnation
new CVAR_wc3_cost_boots_of_speed;	//Boots of Speed
new CVAR_wc3_cost_claws_of_attack;	//Claws of Attack
new CVAR_wc3_cost_cloak_of_shadows;	//Cloak of Shadows
new CVAR_wc3_cost_mask_of_death;	//Mask of Death
new CVAR_wc3_cost_necklace;	//Necklace of Immunity
new CVAR_wc3_cost_orb_of_frost;	//Orb of Frost
new CVAR_wc3_cost_health;	//Periapt of Health
new CVAR_wc3_cost_tome;	//Tome of Experience
new CVAR_wc3_cost_scroll;	//Scroll of Respawning
new CVAR_wc3_cost_mole_protect;	//Mole Protectant
new CVAR_wc3_cost_helm;	//Helm of Excellence
new CVAR_wc3_cost_amulet_cat;	//Amulet of the Cat
new CVAR_wc3_cost_sock;	//Sock of the Feather
new CVAR_wc3_cost_flaming_gloves;	//Flaming Gloves of Warmth
new CVAR_wc3_cost_ring;	//Ring of Regeneration + 1
new CVAR_wc3_cost_chameleon;	//Chameleon
new CVAR_wc3_cost_mole;	//Mole
new CVAR_wc3_cost_intellect;	//Intellect
new CVAR_wc3_cost_he_protect;	//Grenade Protection
new CVAR_wc3_cost_mirror_shield;	//Mirror Shield
new CVAR_wc3_cost_esp;	//ESP
new CVAR_wc3_cost_frost_armor;	//Frost Armor
new CVAR_wc3_cost_death_touch;	//Death's Touch
new CVAR_wc3_cost_health_potion;	//Health Potion
new CVAR_wc3_cost_ult_timer;	//Ultimate Timer Divider
new CVAR_wc3_cost_steel_skin;	//Steel Skin

//��������� ��������� �� shopmenu3:
new CVAR_wc3_bonus_intellect;			//��������� XP ��� �������� Intellect
new CVAR_wc3_he_protect;				//���������� ������� ������ �� HE
new CVAR_wc3_off_mirror_shield;			//�������� ���. �������������� ������
new CVAR_wc3_def_mirror_shield;			//�������� ���. �������� ������
new CVAR_wc3_abil_mirror_shield;		//�������� ���. ������
new CVAR_wc3_frequency_esp;				//������� ������������ ���������
new CVAR_wc3_radius_esp;				//������ ���������
new CVAR_wc3_factor_dmg_frost_armor;	//������� ����������� ���������� � ������ ������������ ������� 
										//HP = wc3_factor_dmg_frost_armor * 0.7
										//AR = wc3_factor_dmg_frost_armor * 0.5
new CVAR_wc3_buy_round_death_touch;		//������� ��� ����� �������� ������� Death's Touch �� ���� �����
new CVAR_wc3_buy_round_hp;				//������� ��� ����� �������� ������� Health Potion �� ���� �����
new CVAR_wc3_reset_ultimate_timer;		//�� ������� ��� ����� ����� ����� ���������� �������
new CVAR_wc3_buy_round_steel_skin;		//������� ��� ����� �������� ������� Steel Skin �� ���� �����

//��� talisman +
//������� ����������
new CVAR_wc3_time_spawn_talisman;		//����� ����� ����� ����� ���������� ��������
new CVAR_wc3_gl_time_spawn_talisman;	//���������� ������� ������� ����� ������� �������� ��������
new CVAR_wc3_mode_talisman;				//������ ������ ������� ����������:
										//[1 - ���������� � ����] - �������� ���������� �� �����.���������� ��� �����. ��� ��������� ��������� ����������� � ���� ������. (��������� �� ���������)
										//[2 - ������� �����] - �������� �� ���������� �� �����.��� �������� �� ������ ������ ������������� �������� ����������� ������������ ���������.
										//[3 - VIP �����] - �������� �� ���������� �� �����.������� ������ �� ����� ������ � ����������.VIP ������������� �������� ��� ���������.
new	CVAR_wc3_talisman_flag;				//���� ������� � ���������� ��� VIP (��� ������� ��� ������� ����� wc3_mode_talisman 3)
new	CVAR_wc3_pl_talisman_respawn;		//����������� ���������� ������� ��� �������� ��������� �� �����
new	CVAR_wc3_pl_talisman_activate;		//����������� ���������� ������� ��� ��������� ��������� � ����
new	CVAR_wc3_t_helm_num;				//���������� ������� (����) ��� ���������
new	CVAR_wc3_t_necklace_num;			//���������� ������� ���������� �� ����� (��������) ��� ���������

//������ �� ��������
new CVAR_wc3_cost_percent_vip;			//������� ��������� �������� �� �����
new CVAR_wc3_cost_vip_flag;				//���� ������� � ��������� ����� ��� VIP

new CVAR_wc3_buy_round_scroll;			//������� ��� ����� �������� ������� Scroll of Respawning �� ���� �����
new CVAR_wc3_min_pl_death_touch;		//����������� ���������� ������� ��� ����������� ������������� �������� "������������� ������"
new CVAR_wc3_buy_round_gloves;			//������� ��� ����� �������� ������� �������� �������� �� ���� ����� (����� ���)

new CVAR_wc3_icon_talisman;				//���������/���������� ������ �������������� ��� �������� ����������

new CVAR_wc3_shopmenu4;					//���������/���������� shopmenu4
new	CVAR_wc3_shopmenu4_vip;				//������������ ������� � shopmenu4 (0 - ��� ����; 1 - ��� VIP)
new CVAR_wc3_shopmenu4_flag;			//���� ������� � shopmenu4

new CVAR_wc3_parachute;					//���������/���������� ��������-���������

new CVAR_wc3_show_menu_race_team;		//���������/���������� ����������� � ���� ������ ��� �������� ���������� ������� �������� �����

new CVAR_wc3_mode_hp_armor;				//������ ������ ��������� "�������� ����" � "�������� ��������":
										//��������� �������� ����������� � health_races.ini � armor_races.ini 
										//[1] - ���������� � �������� �������� � ����� �������� (HEALTH_ITEM � ARMOR_ITEM) 
										//[2] - ��������������� ����������� �������� �������� � ����� ������������ �����
										//[3] - ��������������� ������������ �������� �������� � �����  ������������ �����


public CVAR_Init()
{
	CVAR_wc3_admin_flag				= register_cvar( "wc3_admin_flag"			, "m"							);

	// Miscellaneous Configuration CVARs
	CVAR_wc3_query_client			= register_cvar( "wc3_query_client"			, "1"							);
	CVAR_wc3_show_player			= register_cvar( "wc3_show_player"			, "1"							);
	CVAR_wc3_buy_dead				= register_cvar( "wc3_buy_dead"				, "1"							);
	CVAR_wc3_buy_time				= register_cvar( "wc3_buy_time"				, "0"							);
	CVAR_wc3_buy_zone				= register_cvar( "wc3_buy_zone"				, "0"							);
	CVAR_wc3_spec_position			= register_cvar( "wc3_spec_position"		, "0"							);
	CVAR_wc3_grenade_protection		= register_cvar( "wc3_grenade_protection"	, "0"							);
	CVAR_wc3_cheats					= register_cvar( "wc3_cheats"				, "0"		, FCVAR_SERVER		);
	CVAR_wc3_psychostats			= register_cvar( "wc3_psychostats"			, "1"							);
	//CVAR_wc3_race_limit				= register_cvar( "wc3_race_limit"			, "0"		, FCVAR_SERVER		);
	CVAR_wc3_start_level			= register_cvar( "wc3_start_level"			, "0"							);

	// Saving CVARs
	CVAR_wc3_save_pruning			= register_cvar( "wc3_save_pruning"			, "0"		, FCVAR_SERVER		);
	CVAR_wc3_days_before_delete		= register_cvar( "wc3_days_before_delete"	, "31"							);
	CVAR_wc3_save_end_round			= register_cvar( "wc3_save_end_round"		, "1"							);
	CVAR_wc3_save_xp_db				= register_cvar( "wc3_save_xp_db"			, "0"							);
	CVAR_wc3_save_by				= register_cvar( "wc3_save_by"				, "0"							);


	// Ultimate CVARs
	CVAR_wc3_entangle_drop			= register_cvar( "wc3_entangle_drop"		, "0"							);
	CVAR_wc3_blink_protection		= register_cvar( "wc3_blink_protection"		, "1"							);
	CVAR_wc3_blink_dizziness		= register_cvar( "wc3_blink_dizziness"		, "0"							);

	// Item CVARs
	CVAR_wc3_tome					= register_cvar( "wc3_tome"					, "50"							);
	CVAR_wc3_boots					= register_cvar( "wc3_boots"				, "0.10"						);
	CVAR_wc3_claw					= register_cvar( "wc3_claw"					, "6"							);
	CVAR_wc3_health					= register_cvar( "wc3_health"				, "15"							);
	CVAR_wc3_frost					= register_cvar( "wc3_frost"				, "125"							);
	CVAR_wc3_mask					= register_cvar( "wc3_mask"					, "0.3"							);
	CVAR_wc3_cloak					= register_cvar( "wc3_cloak"				, "150"							);
	CVAR_wc3_sock					= register_cvar( "wc3_sock"					, "0.5"							);
	CVAR_wc3_glove_timer			= register_cvar( "wc3_glove_timer"			, "10"							);
	CVAR_wc3_glove_orc_damage		= register_cvar( "wc3_glove_orc_damage"		, "0"							);

	// Chameleon Race CVARs
	CVAR_wc3_cham_random			= register_cvar( "wc3_cham_random"			, "1"							);
	CVAR_wc3_cham_skill1			= register_cvar( "wc3_cham_skill1"			, ""							);
	CVAR_wc3_cham_skill2			= register_cvar( "wc3_cham_skill2"			, ""							);
	CVAR_wc3_cham_skill3			= register_cvar( "wc3_cham_skill3"			, ""							);
	CVAR_wc3_cham_ultimate			= register_cvar( "wc3_cham_ultimate"		, ""							);
	CVAR_wc3_cham_passive			= register_cvar( "wc3_cham_passive"			, ""							);

	// Database CVARs

	CVAR_wc3_sql_dbhost				= register_cvar( "wc3_sql_dbhost"			, "127.0.0.1"					);
	CVAR_wc3_sql_dbuser				= register_cvar( "wc3_sql_dbuser"			, "root"						);
	CVAR_wc3_sql_dbpass				= register_cvar( "wc3_sql_dbpass"			, ""							);
	CVAR_wc3_sql_dbname				= register_cvar( "wc3_sql_dbname"			, "amx"							);

	// XP Modifier CVARs

	CVAR_wc3_min_players			= register_cvar( "wc3_min_players"			, "2"							);
	CVAR_wc3_ignore_bots			= register_cvar( "wc3_ignore_bots"			, "0"							);
	CVAR_wc3_show_kill_obj			= register_cvar( "wc3_show_kill_obj"		, "0"							);
	CVAR_wc3_show_objectives		= register_cvar( "wc3_show_objectives"		, "1"							);
	CVAR_wc3_xp_multiplier			= register_cvar( "wc3_xp_multiplier"		, "1.0"		, FCVAR_SERVER		);
	
	// Bot CVARs

	CVAR_wc3_bot_buy_item			= register_cvar( "wc3_bot_buy_item"			, "0.33"						);
	CVAR_wc3_bot_buy_item			= register_cvar( "wc3_bot_buy_item"			, "0.33"						);

	//��������� ��������� � �������
	CVAR_wc3_loot_items = register_cvar( "wc3_loot_items","2");
	CVAR_wc3_loot_items_percent = register_cvar( "wc3_loot_items_percent","100");
	CVAR_wc3_loot_ar_hp_xp_percent = register_cvar( "wc3_loot_ar_hp_xp_percent","100");
	CVAR_wc3_loot_items_health = register_cvar( "wc3_loot_items_health","10");
	CVAR_wc3_loot_items_armor = register_cvar( "wc3_loot_items_armor","20");
	CVAR_wc3_loot_remove = register_cvar( "wc3_loot_remove","0");
	CVAR_wc3_loot_stay = register_cvar( "wc3_loot_stay","10");

	//����� � ��� ���������� � �������
	CVAR_wc3_info_killer_onoff = register_cvar( "wc3_info_killer_onoff","1");
	CVAR_wc3_info_killer_flags = register_cvar( "wc3_info_killer_flags","ab");
	
	//��� Respawn ��������
	CVAR_wc3_respawn_onoff = register_cvar( "wc3_respawn_onoff","1");

	//����������� ����� ��������� ������ (����� ���� � ���������)
	CVAR_wc3_status_color_R = register_cvar("wc3_status_color_R", "0");
	CVAR_wc3_status_color_G = register_cvar("wc3_status_color_G", "255");
	CVAR_wc3_status_color_B = register_cvar("wc3_status_color_B", "0");

	//��������� ������� ��� ��������� ����������� (��� ��� ������,�����,����)
	CVAR_wc3_glowshell_time  = register_cvar("wc3_glowshell_time", "0.3");
	CVAR_wc3_glowshell_amount  = register_cvar("wc3_glowshell_amount", "30");
	
	//����� XP ��� �����
	CVAR_wc3_bonus_xp  = register_cvar("wc3_bonus_xp", "1.1");	//������� XP ����� �������� ������������ 1.1 = 110%
	CVAR_wc3_bonus_xp_flag  = register_cvar("wc3_bonus_xp_flag", "p");	//���� ������� � ������ XP

	//���������� ������ ����� ������:
	CVAR_wc3_show_winner  = register_cvar("wc3_show_winner", "1");	//����������� ���������� ���������� � ����� ������

	//���� �� ��������:
	CVAR_wc3_cost_ankh  = register_cvar("wc3_cost_ankh", "1500");							//Ankh of Reincarnation
	CVAR_wc3_cost_boots_of_speed  = register_cvar("wc3_cost_boots_of_speed", "2500");		//Boots of Speed
	CVAR_wc3_cost_claws_of_attack  = register_cvar("wc3_cost_claws_of_attack", "1000");		//Claws of Attack
	CVAR_wc3_cost_cloak_of_shadows  = register_cvar("wc3_cost_cloak_of_shadows", "800");	//Cloak of Shadows
	CVAR_wc3_cost_mask_of_death  = register_cvar("wc3_cost_mask_of_death", "2000");			//Mask of Death
	CVAR_wc3_cost_necklace  = register_cvar("wc3_cost_necklace", "800");					//Necklace of Immunity
	CVAR_wc3_cost_orb_of_frost  = register_cvar("wc3_cost_orb_of_frost", "2000");			//Orb of Frost
	CVAR_wc3_cost_health  = register_cvar("wc3_cost_health", "1000");						//Periapt of Health
	CVAR_wc3_cost_tome  = register_cvar("wc3_cost_tome", "4000");							//Tome of Experience
	CVAR_wc3_cost_scroll  = register_cvar("wc3_cost_scroll", "6000");						//Scroll of Respawning
	CVAR_wc3_cost_mole_protect  = register_cvar("wc3_cost_mole_protect", "1500");			//Mole Protectant
	CVAR_wc3_cost_helm  = register_cvar("wc3_cost_helm", "3000");							//Helm of Excellence
	CVAR_wc3_cost_amulet_cat  = register_cvar("wc3_cost_amulet_cat", "1500");				//Amulet of the Cat
	CVAR_wc3_cost_sock  = register_cvar("wc3_cost_sock", "1500");							//Sock of the Feather
	CVAR_wc3_cost_flaming_gloves  = register_cvar("wc3_cost_flaming_gloves", "1750");		//Flaming Gloves of Warmth
	CVAR_wc3_cost_ring  = register_cvar("wc3_cost_ring", "1000");							//Ring of Regeneration + 1
	CVAR_wc3_cost_chameleon  = register_cvar("wc3_cost_chameleon", "4500");					//Chameleon
	CVAR_wc3_cost_mole  = register_cvar("wc3_cost_mole", "16000");							//Mole
	CVAR_wc3_cost_intellect  = register_cvar("wc3_cost_intellect", "700");					//Intellect
	CVAR_wc3_cost_he_protect  = register_cvar("wc3_cost_he_protect", "840");				//Grenade Protection
	CVAR_wc3_cost_mirror_shield  = register_cvar("wc3_cost_mirror_shield", "3500");			//Mirror Shield
	CVAR_wc3_cost_esp  = register_cvar("wc3_cost_esp", "700");								//ESP
	CVAR_wc3_cost_frost_armor  = register_cvar("wc3_cost_frost_armor", "2100");				//Frost Armor
	CVAR_wc3_cost_death_touch  = register_cvar("wc3_cost_death_touch", "6000");				//Death's Touch
	CVAR_wc3_cost_health_potion  = register_cvar("wc3_cost_health_potion", "3400");			//Health Potion
	CVAR_wc3_cost_ult_timer  = register_cvar("wc3_cost_ult_timer", "1050");					//Ultimate Timer Divider
	CVAR_wc3_cost_steel_skin  = register_cvar("wc3_cost_steel_skin", "3500");				//Steel Skin
		
	//��������� ��������� �� shopmenu3:
	CVAR_wc3_bonus_intellect  = register_cvar("wc3_bonus_intellect", "3");					//��������� XP ��� �������� Intellect
	CVAR_wc3_he_protect  = register_cvar("wc3_he_protect", "3");							//���������� ������� ������ �� HE
	CVAR_wc3_off_mirror_shield  = register_cvar("wc3_off_mirror_shield", "0.30");			//�������� ���. �������������� ������
	CVAR_wc3_def_mirror_shield  = register_cvar("wc3_def_mirror_shield", "0.40");			//�������� ���. �������� ������
	CVAR_wc3_abil_mirror_shield  = register_cvar("wc3_abil_mirror_shield", "0.25");			//�������� ���. ������
	CVAR_wc3_frequency_esp  = register_cvar("wc3_frequency_esp", "2.0");					//������� ������������ ���������
	CVAR_wc3_radius_esp  = register_cvar("wc3_radius_esp", "700");							//������ ���������
	CVAR_wc3_factor_dmg_frost_armor  = register_cvar("wc3_factor_dmg_frost_armor", "4");	//������� ����������� ���������� � ������ ������������ ������� 
																							//HP = wc3_factor_dmg_frost_armor * 0.7
																							//AR = wc3_factor_dmg_frost_armor * 0.5
	CVAR_wc3_buy_round_death_touch  = register_cvar("wc3_buy_round_death_touch", "5");		//������� ��� ����� �������� ������� Death's Touch �� ���� �����
	CVAR_wc3_buy_round_hp  = register_cvar("wc3_buy_round_hp", "1");						//������� ��� ����� �������� ������� Health Potion �� ���� �����
	CVAR_wc3_reset_ultimate_timer  = register_cvar("wc3_reset_ultimate_timer", "2");		//�� ������� ��� ����� ����� ����� ���������� �������
	CVAR_wc3_buy_round_steel_skin  = register_cvar("wc3_buy_round_steel_skin", "1");		//������� ��� ����� �������� ������� Steel Skin �� ���� �����

	//��� shopmenu4
	sm4_CVAR_Init();

	//��� talisman +
	//������� ����������
	CVAR_wc3_time_spawn_talisman  = register_cvar("wc3_time_spawn_talisman", "3600.0");		//����� ����� ����� ����� ���������� ��������
	CVAR_wc3_gl_time_spawn_talisman  = register_cvar("wc3_gl_time_spawn_talisman", "0.0");	//���������� ������� ������� ����� ������� �������� ��������
	CVAR_wc3_mode_talisman = register_cvar("wc3_mode_talisman", "1");						//������ ������ ������� ����������:
																							//[1 - ���������� � ����] - �������� ���������� �� �����.���������� ��� �����. ��� ��������� ��������� ����������� � ���� ������. (��������� �� ���������)
																							//[2 - ������� �����] - �������� �� ���������� �� �����.��� �������� �� ������ ������ ������������� �������� ����������� ������������ ���������.
																							//[3 - VIP �����] - �������� �� ���������� �� �����.������� ������ �� ����� ������ � ����������.VIP ������������� �������� ��� ���������.
	CVAR_wc3_talisman_flag = register_cvar("wc3_talisman_flag", "p");						//���� ������� � ���������� ��� VIP (��� ������� ��� ������� ����� wc3_mode_talisman 3)
	CVAR_wc3_pl_talisman_respawn = register_cvar("wc3_pl_talisman_respawn", "2");			//����������� ���������� ������� ��� �������� ��������� �� �����
	CVAR_wc3_pl_talisman_activate = register_cvar("wc3_pl_talisman_activate", "2");			//����������� ���������� ������� ��� ��������� ��������� � ����
	CVAR_wc3_t_helm_num = register_cvar("wc3_talisman_helm_num", "5");						//���������� ������� (����) ��� ���������
	CVAR_wc3_t_necklace_num = register_cvar("wc3_talisman_necklace_num", "5");				//���������� ������� ���������� �� ����� (��������) ��� ���������
	
	//������ �� ��������
	CVAR_wc3_cost_percent_vip = register_cvar("wc3_cost_percent_vip", "0.8");	//������� ��������� �������� �� �����
	CVAR_wc3_cost_vip_flag  = register_cvar("wc3_cost_vip_flag", "t");	//���� ������� � ��������� ����� ��� VIP

	CVAR_wc3_buy_round_scroll = register_cvar("wc3_buy_round_scroll", "2");	//������� ��� ����� �������� ������� Scroll of Respawning �� ���� �����
	CVAR_wc3_buy_round_gloves = register_cvar("wc3_buy_round_gloves", "1");	//������� ��� ����� �������� ������� �������� �������� �� ���� ����� (����� ���)

	CVAR_wc3_min_pl_death_touch = register_cvar("wc3_min_pl_death_touch", "4");	//����������� ���������� ������� ��� ����������� ������������� �������� "������������� ������"
	
	CVAR_wc3_icon_talisman	= register_cvar("wc3_icon_talisman", "1");			//���������/���������� ������ �������������� ��� �������� ����������

	CVAR_wc3_shopmenu4	= register_cvar("wc3_shopmenu4", "1");					//���������/���������� shopmenu4
	CVAR_wc3_shopmenu4_vip  = register_cvar("wc3_shopmenu4_vip", "0");			//������������ ������� � shopmenu4 (0 - ��� ����; 1 - ��� VIP)
	CVAR_wc3_shopmenu4_flag  = register_cvar("wc3_shopmenu4_flag", "t");		//���� ������� � shopmenu4

	CVAR_wc3_parachute = register_cvar("wc3_parachute", "1");		//���������/���������� ��������-���������

	CVAR_wc3_show_menu_race_team = register_cvar("wc3_show_menu_race_team", "1");		//���������/���������� ����������� � ���� ������ ��� �������� ���������� ������� �������� �����


	CVAR_wc3_mode_hp_armor = register_cvar("wc3_mode_hp_armor", "1");		//������ ������ ��������� "�������� ����" � "�������� ��������":
																			//��������� �������� ����������� � health_races.ini � armor_races.ini 
																			//[1] - ���������� � �������� �������� � ����� �������� (HEALTH_ITEM � ARMOR_ITEM) 
																			//[2] - ��������������� ����������� �������� �������� � ����� ������������ �����
																			//[3] - ��������������� ������������ �������� �������� � �����  ������������ �����

}

// Function will configure the various CVARs
CVAR_Configure()
{
	// Get Half-Life CVAR Pointers
	CVAR_mp_friendlyfire	= get_cvar_pointer( "mp_friendlyfire" );
	CVAR_sv_gravity			= get_cvar_pointer( "sv_gravity" );

	// Get other plugin cvars
	CVAR_csdm_active		= get_cvar_pointer( "csdm_active" );

	CHAM_Configure();
}

public _CVAR_ExecuteConfig()
{
	// Format our config file
	new szConfigFile[64];
	get_configsdir( szConfigFile, 63 );
	add( szConfigFile, 63, "/war3ft/war3FT.cfg" );

	// Make sure the config file exists!
	if ( file_exists( szConfigFile ) )
	{
		server_cmd( "exec %s", szConfigFile );
	}
	else
	{
		WC3_Log( true, "[ERROR] Config file '%s' missing!", szConfigFile );

		set_fail_state( "Config file is missing, unable to load plugin" );
	}
}