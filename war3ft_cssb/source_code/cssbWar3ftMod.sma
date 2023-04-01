//Warcraft 3 Frozen Throne by Geesu http://www.war3ft.com
//Авторы мода Geesu, Avanderik & YamiKaitou (версия 3.0 RC13)
//Внес изменения SMaster
//Официальный сайт perfect-soft.su

#pragma tabsize			0
//#pragma semicolon		1

new const WC3_NAME[]		=	"CSSB War3FT MOD Private";
new const WC3_AUTHOR[]	=	"SMaster";
new const WC3_VERSION[]	=	"6.7";
new const WC3_SITE[]		=	"http://perfect-soft.su";
new const WC3_ICQ[]		=	"607-786-179";
new const WC3_SKYPE[]		=	"xonahead";


#pragma reqclass	xstats
#pragma reqlib		engine
#pragma reqlib		fun
#pragma reqlib		fakemeta
#pragma reqlib		cstrike
#pragma loadlib		sqlite
#pragma loadlib		mysql
#pragma loadlib		cssb

#include <amxmodx>
#include <amxmisc>
#include <engine>
#include <fun>
#include <fakemeta>
#include <fakemeta_util>
#include <cstrike>
#include <dbi>
#include <sqlx>
#include <hamsandwich>
#include <csstats>
#include <xs>
#include <maths>
#include <celltravtrie>
#include <message_stocks>



#include "war3ft_cssb/global_functions.h"

#include "war3ft_cssb/skills_options.h"
#include "war3ft_cssb/skills_options.cpp"

#include "war3ft_cssb/xp_options.h"
#include "war3ft_cssb/xp_options.cpp"


// Header files that contain function declarations and variables

#include "war3ft_cssb/logs/logs.h"
#include "war3ft_cssb/chat/chat.h"
#include "war3ft_cssb/set_player_model/set_player_model.h"
#include "war3ft_cssb/client_buy_weapons/client_buy_weapons.h"
#include "war3ft_cssb/block_skills.h"
#include "war3ft_cssb/block_races.h"
#include "war3ft_cssb/block_items_race.h"
#include "war3ft_cssb/block_items.h"
#include "war3ft_cssb/customization.h"
#include "war3ft_cssb/on_off_options.h"
#include "war3ft_cssb/race_options.h"
#include "war3ft_cssb/resource.h"
#include "war3ft_cssb/constants.cpp"
#include "war3ft_cssb/db/db_common.h"
#include "war3ft_cssb/db/db_mysqlx.h"
#include "war3ft_cssb/db/db_sqlite.h"
#include "war3ft_cssb/items.h"
#include "war3ft_cssb/XP.h"
#include "war3ft_cssb/war3ft.h"
#include "war3ft_cssb/cstrike.h"
#include "war3ft_cssb/menus.h"
#include "war3ft_cssb/shared.h"
#include "war3ft_cssb/ultimates.h"
#include "war3ft_cssb/loot.h"
#include "war3ft_cssb/showwin.h"
//#include "war3ft_cssb/infokiller.h"
#include "war3ft_cssb/item_esp.h"
#include "war3ft_cssb/item_death_touch.h"
#include "war3ft_cssb/item_health_potion.h"
#include "war3ft_cssb/ultimate_timer_divider.h"
#include "war3ft_cssb/item_steel_skin.h"
#include "war3ft_cssb/race_frost_mag.h"
#include "war3ft_cssb/vip_skills.h"
#include "war3ft_cssb/shopmenu4.h"
#include "war3ft_cssb/item_ice_block.h"
#include "war3ft_cssb/item_death_coil.h"
#include "war3ft_cssb/item_impale.h"
#include "war3ft_cssb/item_sleep.h"
#include "war3ft_cssb/item_tranquility.h"
#include "war3ft_cssb/system_talisman.h"
#include "war3ft_cssb/natives.h"
#include "war3ft_cssb/new_menus_changerace.h"
#include "war3ft_cssb/autobuy_items.h"
#include "war3ft_cssb/multi_xp.h"
#include "war3ft_cssb/race_death_knight.h"
#include "war3ft_cssb/race_black_magician.h"
#include "war3ft_cssb/race_priest.h"
#include "war3ft_cssb/race_rogue.h"
#include "war3ft_cssb/race_druid.h"
#include "war3ft_cssb/motd.h"
#include "war3ft_cssb/races/bloodseeker/race_bloodseeker.h"
#include "war3ft_cssb/races/juggernaut/race_juggernaut.h"
#include "war3ft_cssb/races/sniper/race_sniper.h"
#include "war3ft_cssb/races/disruptor/race_disruptor.h"
#include "war3ft_cssb/races/razor/race_razor.h"
#include "war3ft_cssb/races/warlock/race_warlock.h"
#include "war3ft_cssb/races/shadow_fiend/race_shadow_fiend.h"
#include "war3ft_cssb/health/health.h"
#include "war3ft_cssb/armor/armor.h"
#include "war3ft_cssb/vip_system/vip_system.h"


// Source Code
#include "war3ft_cssb/cvar.cpp"

#include "war3ft_cssb/chat/chat.cpp"
#include "war3ft_cssb/race_undead.cpp"         							// Undead Scourge   - 1
#include "war3ft_cssb/race_human.cpp"									// Human Alliance	- 2
#include "war3ft_cssb/race_orc.cpp"										// Orcish Horde		- 3
#include "war3ft_cssb/race_elf.cpp"										// Night Elf		- 4
#include "war3ft_cssb/race_blood.cpp"									// Blood Mage		- 5
#include "war3ft_cssb/race_shadow.cpp"									// Shadow Hunter	- 6
#include "war3ft_cssb/race_warden.cpp"          							// Warden           - 7
#include "war3ft_cssb/race_crypt.cpp"									// Crypt Lord       - 8
#include "war3ft_cssb/race_chameleon.cpp"								// Chameleon		- 9
#include "war3ft_cssb/race_frost_mag.cpp"								// Frost Mage		- 10
#include "war3ft_cssb/race_death_knight.cpp"								// Death knight		- 11
#include "war3ft_cssb/race_black_magician.cpp"							// Black magician	- 12
#include "war3ft_cssb/race_alchemist.cpp"								// Alchemis			- 13
#include "war3ft_cssb/race_priest.cpp"									// Priest			- 14
#include "war3ft_cssb/race_rogue.cpp"									// Rogue			- 15
#include "war3ft_cssb/race_druid.cpp"									// Druid			- 16
#include "war3ft_cssb/races/bloodseeker/race_bloodseeker.cpp"			// Bloodseeker		- 17
#include "war3ft_cssb/races/juggernaut/race_juggernaut.cpp"				// Juggernaut		- 18
#include "war3ft_cssb/races/sniper/race_sniper.cpp"						// Sniper			- 19
#include "war3ft_cssb/races/disruptor/race_disruptor.cpp"				// Disruptor		- 20
#include "war3ft_cssb/races/razor/race_razor.cpp"						// Razor			- 21
#include "war3ft_cssb/races/warlock/race_warlock.cpp"					// Warlock			- 22
#include "war3ft_cssb/races/shadow_fiend/race_shadow_fiend.cpp"			// Shadow Fiend		- 23



#include "war3ft_cssb/forwards.cpp"
#include "war3ft_cssb/effects.cpp"
#include "war3ft_cssb/XP.cpp"
#include "war3ft_cssb/db/db_mysqlx.cpp"
#include "war3ft_cssb/db/db_sqlite.cpp"
#include "war3ft_cssb/db/db_common.cpp"
#include "war3ft_cssb/war3ft.cpp"
#include "war3ft_cssb/events.cpp"
#include "war3ft_cssb/clientCommands.cpp"
#include "war3ft_cssb/items.cpp"
#include "war3ft_cssb/stocks.cpp"
#include "war3ft_cssb/shared.cpp"
#include "war3ft_cssb/menus.cpp"
#include "war3ft_cssb/motd.cpp"
#include "war3ft_cssb/language.cpp"
#include "war3ft_cssb/admin.cpp"
#include "war3ft_cssb/ultimates.cpp"
#include "war3ft_cssb/util.cpp"
#include "war3ft_cssb/skill_manager.cpp"
#include "war3ft_cssb/cstrike.cpp"
#include "war3ft_cssb/loot.cpp"
#include "war3ft_cssb/showwin.cpp"
#include "war3ft_cssb/infokiller.cpp"
#include "war3ft_cssb/item_esp.cpp"
#include "war3ft_cssb/item_death_touch.cpp"
#include "war3ft_cssb/item_health_potion.cpp"
#include "war3ft_cssb/ultimate_timer_divider.cpp"
#include "war3ft_cssb/item_steel_skin.cpp"
#include "war3ft_cssb/ult_race_blood.cpp"
#include "war3ft_cssb/vip_skills.cpp"
#include "war3ft_cssb/shopmenu4.cpp"
#include "war3ft_cssb/item_ice_block.cpp"
#include "war3ft_cssb/item_death_coil.cpp"
#include "war3ft_cssb/item_impale.cpp"
#include "war3ft_cssb/item_sleep.cpp"
//#include "war3ft_cssb/race_vip_models.cpp"
#include "war3ft_cssb/item_tranquility.cpp"
#include "war3ft_cssb/system_talisman.cpp"

#include "war3ft_cssb/natives.cpp"
#include "war3ft_cssb/new_menus_changerace.cpp"
#include "war3ft_cssb/autobuy_items.cpp"
#include "war3ft_cssb/customization.cpp"
#include "war3ft_cssb/multi_xp.cpp"
#include "war3ft_cssb/global_functions.cpp"
#include "war3ft_cssb/block_items.cpp"
#include "war3ft_cssb/block_items_race.cpp"
#include "war3ft_cssb/block_races.cpp"
#include "war3ft_cssb/block_skills.cpp"
#include "war3ft_cssb/logs/logs.cpp"

#include "war3ft_cssb/functions/plugin_init.cpp"
#include "war3ft_cssb/functions/plugin_end.cpp"
#include "war3ft_cssb/functions/plugin_precache.cpp"

#include "war3ft_cssb/functions/client_putinserver.cpp"
#include "war3ft_cssb/functions/client_connect.cpp"
#include "war3ft_cssb/functions/client_disconnect.cpp"
#include "war3ft_cssb/functions/client_PreThink.cpp"
#include "war3ft_cssb/functions/plugin_natives.cpp"

#include "war3ft_cssb/functions/plugin_modules.cpp"
#include "war3ft_cssb/functions/error_filter.cpp"
#include "war3ft_cssb/functions/module_filter.cpp"
#include "war3ft_cssb/functions/native_filter.cpp"

#include "war3ft_cssb/functions/plugin_cfg.cpp"
#include "war3ft_cssb/functions/client_command.cpp"
#include "war3ft_cssb/functions/CS_InternalCommand.cpp"


#include "war3ft_cssb/client_buy_weapons/client_buy_weapons.cpp"
#include "war3ft_cssb/set_player_model/set_player_model.cpp"
#include "war3ft_cssb/health/health.cpp"
#include "war3ft_cssb/armor/armor.cpp"
#include "war3ft_cssb/vip_system/vip_system.cpp"

	