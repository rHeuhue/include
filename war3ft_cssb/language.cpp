/*
*	Language Functions
*/

#define TOTAL_MENUS 15


// This is the list of menu titles that are in war3ft.txt
new const MENU_NAMES[TOTAL_MENUS][] = 
{
	"MENU_BUY_ITEM",
	"MENU_BUY_ITEM2",
	"MENU_BUY_ITEM3",
	"MENU_BUY_ITEM4",
	"MENU_SELECT_SKILL",
	"MENU_WAR3MENU",
	"MENU_SKILLS_OPTIONS",
	"MENU_ITEM_OPTIONS",
	"MENU_RACE_OPTIONS",
	"MENU_ADMIN_MENU",
	"MENU_GIVE_PLAYERS_XP",
	"MENU_TEAM_XP",
	"MENU_RESET_XP",
	"MENU_REPLACE_ITEM",
	"MENU_PLAYERS_TALISMAN"
};

// Callback functions for the above menu names
new const MENU_CALLBACK[TOTAL_MENUS][] = 
{
	"_MENU_Shopmenu1",
	"_MENU_Shopmenu2",
	"_MENU_Shopmenu3",
	"_MENU_Shopmenu4",
	"_MENU_SelectSkill",
	"_MENU_War3Menu",
	"_menu_Skill_Options",
	"_menu_Item_Options",
	"_menu_Race_Options",
	"_menu_Admin_Options",
	"_menu_PlayerXP_Options",
	"_menu_TeamXP_Options",
	"_MENU_ResetXP",
	"_menu_ReplaceItem",
	"_menu_Players_Talisman"
};

/*
	Description: Function will register all menus for all languages
*/
public LANG_SetMenus()
{
	

	new iTotalLanguages = get_langsnum();
	new lang[3], menu[128];
	new curMenuId = -1, highestMenuId = -1;
	new iLang, iMenu;


	// Loop through every menu

	for ( iMenu = 0; iMenu < TOTAL_MENUS; iMenu++ )
	{
		// Register the menu names for each language

		for ( iLang = 0; iLang < iTotalLanguages; iLang++ )
		{
			get_lang ( iLang, lang );

			if ( lang_exists( lang ) )
			{
				formatex ( menu, 127, "%L", lang, MENU_NAMES[iMenu] );
				curMenuId = register_menuid ( menu );

				if ( curMenuId > highestMenuId )
				{
					register_menucmd ( curMenuId, 1023, MENU_CALLBACK[iMenu] );
					highestMenuId = curMenuId;
				}
			}
		}// End language loop
	}// End menu loop
}

//Function will return the race name based on the race idUser and the language of the user
Lang_GetRaceName( race_id, idUser, race_name[], len, bool:shortLookup = false )
{
	

	new szRaceHelper[64];
	
	if ( shortLookup == true )
	{
		formatex( szRaceHelper, 63, "RACE_S_%d", race_id );
	}
	else
	{
		formatex( szRaceHelper, 63, "RACE_%d", race_id );
	}

	// Lookup the race name
	formatex( race_name, len-1, "%L", idUser, szRaceHelper );
}

//Description: Function will return the shopmenu item name based on the item idUser and the language of the user
LANG_GetItemName ( item_id, idUser, item_name[], len, bool:shortLookup = false )
{
	
	

	if ( item_id < 0 )
		return;
	

	new szItemHelper[64];

	if ( shortLookup == true )
	{
		formatex( szItemHelper, 63, "ITEM_S_%d", item_id );
	}
	else
	{
		formatex( szItemHelper, 63, "ITEM_%d", item_id );
	}

	// Lookup the item name
	formatex( item_name, len, "%L", idUser, szItemHelper );
}

LANG_GetItemInfo( item_id, idUser, item_description[], len )
{
	

	switch ( item_id )
	{
		case ITEM_ANKH:			formatex ( item_description, len, "%L", idUser, "ITEM_I_0");
		case ITEM_BOOTS:		formatex ( item_description, len, "%L", idUser, "ITEM_I_1");
		case ITEM_CLAWS:		formatex ( item_description, len, "%L", idUser, "ITEM_I_2", get_pcvar_num( CVAR_wc3_claw ), get_pcvar_num( CVAR_wc3_claw ) );
		case ITEM_CLOAK:		formatex ( item_description, len, "%L", idUser, "ITEM_I_3" );
		case ITEM_MASK:			formatex ( item_description, len, "%L", idUser, "ITEM_I_4" );
		case ITEM_NECKLACE:		formatex ( item_description, len, "%L", idUser, "ITEM_I_5" );
		case ITEM_FROST:		formatex ( item_description, len, "%L", idUser, "ITEM_I_6" );
		case ITEM_HEALTH:		formatex ( item_description, len, "%L", idUser, "ITEM_I_7" );
		case ITEM_TOME:			formatex ( item_description, len, "%L", idUser, "ITEM_I_8" );
		case ITEM_SCROLL:		formatex ( item_description, len, "%L", idUser, "ITEM_I_9" );
		case ITEM_PROTECTANT:	formatex ( item_description, len, "%L", idUser, "ITEM_I_10" );
		case ITEM_HELM:			formatex ( item_description, len, "%L", idUser, "ITEM_I_11" );
		case ITEM_AMULET:		formatex ( item_description, len, "%L", idUser, "ITEM_I_12" );
		case ITEM_SOCK:			formatex ( item_description, len, "%L", idUser, "ITEM_I_13" );
		case ITEM_GLOVES:		formatex ( item_description, len, "%L", idUser, "ITEM_I_14", get_pcvar_num( CVAR_wc3_glove_timer ) );
		case ITEM_RING:			formatex ( item_description, len, "%L", idUser, "ITEM_I_15" );
		case ITEM_CHAMELEON:	formatex ( item_description, len, "%L", idUser, "ITEM_I_16" );
		case ITEM_MOLE:			formatex ( item_description, len, "%L", idUser, "ITEM_I_17" );
		//Для shopmenu3
		case ITEM_INTELLECT:				formatex ( item_description, len, "%L", idUser, "ITEM_I_18",BONUS_INTELLECT);
		case ITEM_GRENADE_PROTECTION:		formatex ( item_description, len, "%L", idUser, "ITEM_I_19" );
		case ITEM_MIRROR_SHIELD:			formatex ( item_description, len, "%L", idUser, "ITEM_I_20",floatround(OFFENSIVE_MIRROR_SHIELD * 100),"%",floatround(DEFENSIVE_MIRROR_SHIELD * 100),"%");
		case ITEM_ESP:						formatex ( item_description, len, "%L", idUser, "ITEM_I_21" );
		case ITEM_FROST_ARMOR:				formatex ( item_description, len, "%L", idUser, "ITEM_I_22",floatround(FROST_ARMOR_DAMAGE * ARMOR_RATIO),floatround(FROST_ARMOR_DAMAGE * ARMOR_BONUS));
		case ITEM_DEATH_TOUCH:				formatex ( item_description, len, "%L", idUser, "ITEM_I_23" );
		case ITEM_HEALTH_POTION:			formatex ( item_description, len, "%L", idUser, "ITEM_I_24" );
		case ITEM_ULTIMATE_TIMER_DIVIDER:	formatex ( item_description, len, "%L", idUser, "ITEM_I_25",RESET_ULTIMATE_TIMER);
		case ITEM_STEEL_SKIN:				formatex ( item_description, len, "%L", idUser, "ITEM_I_26");
		//Для shopmenu4
		case ITEM_DEVOURER_LIGHT:			formatex ( item_description, len, "%L", idUser, "ITEM_I_27");
		case ITEM_ICE_BLOCK:				formatex ( item_description, len, "%L", idUser, "ITEM_I_28" );
		case ITEM_THIEF:					formatex ( item_description, len, "%L", idUser, "ITEM_I_29",THIEF_TIME,THIEF_MONEY);
		case ITEM_MIRROR_ULTIMATE:			formatex ( item_description, len, "%L", idUser, "ITEM_I_30");
		case ITEM_DEATHCOIL:				formatex ( item_description, len, "%L", idUser, "ITEM_I_31");
		case ITEM_IMPALE:					formatex ( item_description, len, "%L", idUser, "ITEM_I_32" );
		case ITEM_SLEEP:					formatex ( item_description, len, "%L", idUser, "ITEM_I_33",SLEEP_DURATION);
		case ITEM_BOOK_DEAD:				formatex ( item_description, len, "%L", idUser, "ITEM_I_34",BOOK_DEAD_CHARGES);
		case ITEM_TRANQUILITY:				formatex ( item_description, len, "%L", idUser, "ITEM_I_35",TRANQUILITY_TIME);

		default:							formatex ( item_description, len, " " );
	}
}

//Description: Function will return the skill name based on the race idUser, skill idUser and the language of the user
LANG_GetSkillName( skill_id, idUser, skill_name[], len, func_id )
{	
	

	// Handle everything else
	if ( skill_id < 0 || skill_id >= MAX_SKILLS )
	{
		WC3_Log( true, "[%d] Invalid skill: %d", func_id, skill_id );
		return;
	}

	new szSkillHelper[64];

	formatex ( szSkillHelper, 63, "SKILL_%d", skill_id );
	formatex ( skill_name, len-1, "%L", idUser, szSkillHelper );
}

LANG_GetSkillInfo( skill_id, idUser, skill_description[], len )
{
	
	switch (skill_id)
	{
		// Undead Scourge
		case SKILL_VAMPIRICAURA:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_0" );
		case SKILL_UNHOLYAURA:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_1" );
		case SKILL_LEVITATION:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_2" );
		case ULTIMATE_SUICIDE:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_3" );

		// Human Alliance
		case SKILL_INVISIBILITY:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_4" );
		case SKILL_DEVOTION:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_5" );
		case SKILL_BASH:				formatex ( skill_description, len, "%L", idUser, "SKILL_I_6" );
		case ULTIMATE_BLINK:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_7" );

		// Orcish Horde
		case SKILL_CRITICALSTRIKE:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_8" );
		case SKILL_CRITICALGRENADE:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_9" );
		case SKILL_REINCARNATION:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_10" );
		case ULTIMATE_CHAINLIGHTNING:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_11" );

		// Night Elf
		case SKILL_EVASION:				formatex ( skill_description, len, "%L", idUser, "SKILL_I_12" );
		case SKILL_THORNS:				formatex ( skill_description, len, "%L", idUser, "SKILL_I_13" );
		case SKILL_TRUESHOT:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_14" );
		case ULTIMATE_ENTANGLE:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_15" );

		// Blood Mage
		case SKILL_PHOENIX:				formatex ( skill_description, len, "%L", idUser, "SKILL_I_16" );
		case SKILL_BANISH:				formatex ( skill_description, len, "%L", idUser, "SKILL_I_17" );
		case SKILL_SIPHONMANA:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_18" );
		case ULTIMATE_IMMOLATE:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_19" );
		case PASS_RESISTANTSKIN:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_20" );

		// Shadow Hunter
		case SKILL_HEALINGWAVE:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_21" );
		case SKILL_HEX:					formatex ( skill_description, len, "%L", idUser, "SKILL_I_22" );
		case SKILL_SERPENTWARD:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_23" );
		case ULTIMATE_BIGBADVOODOO:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_24" );
		case PASS_UNSTABLECONCOCTION:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_25" );

		// Warden
		case SKILL_FANOFKNIVES:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_26" );
		case SKILL_BLINK:				formatex ( skill_description, len, "%L", idUser, "SKILL_I_27" );
		case SKILL_SHADOWSTRIKE:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_28" );
		case ULTIMATE_VENGEANCE:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_29" );
		case PASS_HARDENEDSKIN:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_30" );

		// Crypt Lord
		case SKILL_IMPALE:				formatex ( skill_description, len, "%L", idUser, "SKILL_I_31" );
		case SKILL_SPIKEDCARAPACE:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_32" );
		case SKILL_CARRIONBEETLES:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_33" );
		case ULTIMATE_LOCUSTSWARM:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_34" );
		case PASS_ORB:					formatex ( skill_description, len, "%L", idUser, "SKILL_I_35" );

		// Frost Mage
		case SKILL_FROST_MAGE_ICE_SPLINTERS:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_36" );
		case SKILL_FROST_MAGE_ICE_ARROW:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_37" );
		case SKILL_FROST_MAGE_CONE_OF_COLD:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_38" );
		case ULTIMATE_FROST_MAGE_BLIZZARD:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_39" );

		//Flame Strike - Супер навык для Хамелеона "паровоз"
		case ULTIMATE_CHAM_FLAME_STRIKE:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_40" );

		// Рыцарь смерти
		case SKILL_DEATH_KNIGHT_UNARMOR:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_41",floatround(fUnarmorChance * 100) );
		case SKILL_DEATH_KNIGHT_BLOOD_BOIL:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_42" );
		case SKILL_DEATH_KNIGHT_DEATH_COIL:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_43" );
		case ULTIMATE_DEATH_KNIGHT_BLOOD_PRESENCE:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_44",floatround(fPercentHP * 100),floatround(fPercentArmor * 100),floatround(fPercentUndamage * 100) );
		case PASS_DEATH_KNIGHT_CONTROL_UNDEAD:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_45",floatround(fControlUndeadHP * 100),floatround(fControlUndeadExp * 100) );
	
		// Черный маг
		case SKILL_BLACKSTRIKE:					formatex ( skill_description, len, "%L", idUser, "SKILL_I_46",iBlackStrikeDmg);
		case SKILL_BLACKSHADOW:					formatex ( skill_description, len, "%L", idUser, "SKILL_I_47" );
		case SKILL_BLACKPOWER:					formatex ( skill_description, len, "%L", idUser, "SKILL_I_48" );
		case ULTIMATE_BLACKLIGHTNING:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_49" );

		//Alchemis - Алхимик
		case SKILL_POISON:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_50" );
		case SKILL_SHOCK:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_51" );
		case SKILL_FROST:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_52" );
		case ULTIMATE_RADIATION:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_53" );
		case PASS_HYPNOSIS:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_54" );

		//Priest - Жрец
		case SKILL_PRIEST_ENTRYINTOCHASM:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_55" );
		case SKILL_PRIEST_SACRED_FIRE:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_56" );
		case SKILL_PRIEST_SPIRITUAL_ACCURACY:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_57" );
		case ULTIMATE_PRIEST_DARKNESS_WORD_DEATH:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_58" );
		case PASS_PRIEST_MYSTICISM:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_59" );

		//Rogue - Разбойник
		case SKILL_ROGUE_1:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_60",iSStrike_Secondary,iSStrike_Primary,iSStrike_Knife,iSStrike_Grenade);
		case SKILL_ROGUE_2:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_61" );
		case SKILL_ROGUE_3:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_62" );
		case ULTIMATE_ROGUE:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_63" );

		//Druid - Друид
		case SKILL_DRUID_1:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_64");
		case SKILL_DRUID_2:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_65" );
		case SKILL_DRUID_3:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_66" );
		case ULTIMATE_DRUID:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_67" );
		case PASS_MANGLE_DRUID:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_68",fShanceMangle*100,iShanceMangleDmg);

		//Бладсикер
		case SKILL_BLOODSEEKER_1:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_69");
		case SKILL_BLOODSEEKER_2:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_70");
		case SKILL_BLOODSEEKER_3:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_71");
		case ULTIMATE_BLOODSEEKER:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_72") ;
		case PASS_BLOODSEEKER:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_73");

		//Раса Джагернаут
		case SKILL_JUGGERNAUT_1:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_74");
		case SKILL_JUGGERNAUT_2:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_75");
		case SKILL_JUGGERNAUT_3:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_76");
		case ULTIMATE_JUGGERNAUT:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_77") ;
		case PASS_JUGGERNAUT:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_78");

		//Раса Снайпер
		case SKILL_SNIPER_1:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_79");
		case SKILL_SNIPER_2:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_80");
		case SKILL_SNIPER_3:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_81");
		case ULTIMATE_SNIPER:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_82") ;
		case PASS_SNIPER:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_83");

		//Раса Разрушитель
		case SKILL_DISRUPTOR_1:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_84");
		case SKILL_DISRUPTOR_2:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_85");
		case SKILL_DISRUPTOR_3:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_86");
		case ULTIMATE_DISRUPTOR:	formatex ( skill_description, len, "%L", idUser, "SKILL_I_87");
		case PASS_DISRUPTOR:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_88");

		//Раса Блэйд
		case SKILL_RAZOR_1:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_89");
		case SKILL_RAZOR_2:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_90");
		case SKILL_RAZOR_3:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_91");
		case ULTIMATE_RAZOR:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_92");
		case PASS_RAZOR:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_93");

		//Раса Варлок
		case SKILL_WARLOCK_1:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_94");
		case SKILL_WARLOCK_2:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_95");
		case SKILL_WARLOCK_3:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_96");
		case ULTIMATE_WARLOCK:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_97");
		//case PASS_WARLOCK:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_98");

		//Раса Невермор
		case SKILL_SHADOW_FIEND_1:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_99");
		case SKILL_SHADOW_FIEND_2:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_100");
		case SKILL_SHADOW_FIEND_3:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_101");
		case ULTIMATE_SHADOW_FIEND:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_102");
		case PASS_SHADOW_FIEND:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_103");

		//Раса 24
		case SKILL_24_1:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_104");
		case SKILL_24_2:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_105");
		case SKILL_24_3:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_106");
		case ULTIMATE_24:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_107");
		case PASS_24:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_108");

		//Раса 25
		case SKILL_25_1:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_109");
		case SKILL_25_2:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_110");
		case SKILL_25_3:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_111");
		case ULTIMATE_25:		formatex ( skill_description, len, "%L", idUser, "SKILL_I_112");
		case PASS_25:			formatex ( skill_description, len, "%L", idUser, "SKILL_I_113");
			
	}
}

fGetSkillName(iSkillID,szSkillName[],iLength)
{	
	
	if (iSkillID < 0 || iSkillID >= MAX_SKILLS)
		return;

	new szSkillKey[64];
	formatex (szSkillKey,63, "SKILL_%d", iSkillID);
	formatex (szSkillName, iLength-1, "%L", LANG_PLAYER,szSkillKey);
}