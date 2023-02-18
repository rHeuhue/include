/* Sublime AMXX Editor v3.0.0-beta */

#if defined _hns_jumpstats_cvars_included
	#endinput
#endif
#define _hns_jumpstats_cvars_included

/* Load custom module ?

#pragma reqlib LIBRARY_NAME
#if !defined AMXMODX_NOAUTOLOAD
	#pragma loadlib LIBRARY_NAME
#endif

*/

enum _:TypeJump
{
	GOOD,
	PRO,
	HOLY,
	LEET,
	GOD
}

enum eHNSCvars_JumpStats
{
	LJ,
	CJ,
	DCJ,
	LADDER,
	BJ,
	WJ,
	DBJ,
	SCJ,
	DROPSCJ,
	DUCKBHOP,
	BHOPINDUCK,
	REALLADDERBHOP,
	UPBJ,
	UPSBJ
}

new g_eCvarStats[eHNSCvars_JumpStats][TypeJump]

enum eHNSCvars
{
	CONNECT_FLAGS[128],
	MINIMUM_DISTANCE,
	MINIMUM_DISTANCE_LOW,
	MAXIMUM_DISTANCE,
	BLOCK_CHAT_INFO,
	MINIMUM_BLOCK_REQ_TO_SHOW,
	ADMIN_ONLY,
	TEAM,
	SPEED_ALL_TEAM,
	LIGHT,
	SOUNDS,
	SCREENSHOT,
	DEMO_INFO,
	SQL,
	WEB,
	TOP_BY,
	SAVE_TOP,
	MAP_TOP,
	SAVE_EXTRAS_TOP,
	WEAPONS_TOP,
	BLOCK_TOP,
	BLOCK_WEAPONS_TOP,
	LEGAL_SETTINGS,
	FPS,
	BUG_CHECK,
	SCRIPT_DETECTION,
	SCRIPT_WORK,
	SCRIPT_NOTIFY,
	SCRIPT_PUNISHMENT,
	BAN_TYPE,
	BAN_MINUTES,
	BAN_AUTHID,
	CHAT_PREFIX,
	AIRACCELERATE,
	JUMP_GRAVITY,
	VIP_JUMPSTATS,
	VIP_ACCESS[2],
	NOSLOWDOWN,
	MAX_STRAFES,
	INGAME_STRAFES,
	MINIMUM_PRE_TO_SHOW,
	MAX_BLOCK_TO_SHOW,
	MIN_BLOCK_TO_SHOW
}

new g_eCvars[eHNSCvars]


enum eTechniqueStatus
{
	LongJump, CountJump, DoubleCJ, MultiCJ, LadderJump, LadderBhop, Bhop, StandUpBhop, DropBhop,
	StandUpCountJump, DropCJ, WeirdJump, DoubleSCJ, MultiSCJ, Drop_SCJ, DropDoubleSCJ, DropMultiSCJ,
	DuckBhopJump, Real_Ladder_Bhop, UpBhop, UpStandUpBhop, UpBhopInDuckJump, BhopInDuckJump, MultiBhop, DropDCJ, DropMCJ
}

new g_eCvarsTechnique[eTechniqueStatus]

enum ExtraCvars
{
	HUD_STATS_RED,
	HUD_STATS_GREEN,
	HUD_STATS_BLUE,
	FAIL_HUD_STATS_RED,
	FAIL_HUD_STATS_GREEN,
	FAIL_HUD_STATS_BLUE,
	Float:HUD_STATS_X,
	Float:HUD_STATS_Y,
	Float:HUD_STRAFE_X,
	Float:HUD_STRAFE_Y,
	Float:HUD_DUCK_X,
	Float:HUD_DUCK_Y,
	Float:HUD_SPEED_X,
	Float:HUD_SPEED_Y,
	Float:HUD_PRESTRAFE_X,
	Float:HUD_PRESTRAFE_Y,
	HUD_SPEED_R,
	HUD_SPEED_G,
	HUD_SPEED_B,
	HUD_PRESTRAFE_R,
	HUD_PRESTRAFE_G,
	HUD_PRESTRAFE_B,
	HUD_CHANNEL_STATS,
	HUD_CHANNEL_STRAFE,
	HUD_CHANNEL_DUCK,
	HUD_CHANNEL_SPEED,
	HUD_CHANNEL_PRE
}

new g_eCvarsExtraSettings[ExtraCvars]


enum SQLData
{
	SQL_HOST[32],
	SQL_USER[32],
	SQL_PASS[32],
	SQL_DB[32],
	URL[128],
	UPDATE_AUTH
}

new g_eCvarSQL[SQLData]


RegisterCvars()
{
	new pCvar;

	pCvar = create_cvar("hns_connect_flags", "abcdegkln", FCVAR_NONE, "What should work when players connect to the server:\
																		^n0 = none\
																		^na = colorchat\
																		^nb = stats\
																		^nc = speed\
																		^nd = showpre\
																		^ne = strafe stats\
																		^nf = beam\
																		^ng = duck stats for mcj\
																		^nh = shows message when your bhop prestrafe is failed\
																		^ni = show multibhop pre\
																		^nj = show prestrafe after duck\
																		^nk = show lj prestrafe\
																		^nl = show edge\
																		^nm = show edge when fail (without block)\
																		^nn = enable sounds\
																		^no = enable InGame strafe stats");
	bind_pcvar_string(pCvar, g_eCvars[CONNECT_FLAGS], charsmax(g_eCvars[CONNECT_FLAGS]));


	pCvar = create_cvar("hns_minimum_distance", "215", FCVAR_NONE, "Minimum Distance to count as jump");
	bind_pcvar_num(pCvar, g_eCvars[MINIMUM_DISTANCE]);

	pCvar = create_cvar("hns_minimum_distance_other", "120", FCVAR_NONE, "Minimum Distance to count as jump^nOther techniques^nUps bhop, MultiBhop, Real Ladder Bhop, Ducks Bhop, Ladder Jump");
	bind_pcvar_num(pCvar, g_eCvars[MINIMUM_DISTANCE_LOW]);

	pCvar = create_cvar("hns_maximum_distance", "290", FCVAR_NONE, "Maximum Distance to count as jump");
	bind_pcvar_num(pCvar, g_eCvars[MAXIMUM_DISTANCE]);

	pCvar = create_cvar("hns_block_chat_show", "1", FCVAR_NONE, "Will block info show in the chat message");
	bind_pcvar_num(pCvar, g_eCvars[BLOCK_CHAT_INFO]);

	pCvar = create_cvar("hns_block_chat_min", "1", FCVAR_NONE, "Minimum block to show (block more then 0=good,1=pro,2=holy,3=leet,4=god distance)");
	bind_pcvar_num(pCvar, g_eCvars[MINIMUM_BLOCK_REQ_TO_SHOW]);

	pCvar = create_cvar("hns_admin_only", "0", FCVAR_NONE, "Stats only for admins");
	bind_pcvar_num(pCvar, g_eCvars[ADMIN_ONLY]);

	pCvar = create_cvar("hns_team", "1", FCVAR_NONE, "Which team can use the jumpstats:^n0 = All(CT & T)^n1 = Terrorists (T)^n2 = Counter-Terrorists (CT)");
	bind_pcvar_num(pCvar, g_eCvars[TEAM]);

	pCvar = create_cvar("hns_speed_allteam", "1", FCVAR_NONE, "Enable/Disable command /speed for all teams");
	bind_pcvar_num(pCvar, g_eCvars[SPEED_ALL_TEAM]);

	pCvar = create_cvar("hns_light_screenfade", "0", FCVAR_NONE, "Allow highlighting after landing (1 = on, 0 = off; works for holy, leet and god distances)");
	bind_pcvar_num(pCvar, g_eCvars[LIGHT]);

	pCvar = create_cvar("hns_sounds", "0", FCVAR_NONE, "Allow Sounds:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[SOUNDS]);

	pCvar = create_cvar("hns_screenshot", "0", FCVAR_NONE, "Allow doind ScreenShot if Player is going in Top (Does not work with SQL and Map Top)");
	bind_pcvar_num(pCvar, g_eCvars[SCREENSHOT]);

	pCvar = create_cvar("hns_demo_info", "1", FCVAR_NONE, "Allow Showing info about stats when you record demo");
	bind_pcvar_num(pCvar, g_eCvars[DEMO_INFO]);

	pCvar = create_cvar("hns_sql", "0", FCVAR_NONE, "How work SQL Module:^n0 = disable^n1 = SQL Module enabled");
	bind_pcvar_num(pCvar, g_eCvars[SQL]);

	pCvar = create_cvar("hns_web", "0", FCVAR_NONE, "// Enable/Disable Web Top (1=Enable,0=Disable) - if you want standart tops with sql module, turn of web mod");
	bind_pcvar_num(pCvar, g_eCvars[WEB]);

	pCvar = create_cvar("hns_save_top_by", "2", FCVAR_NONE, "How to save Top10^n0 = Name^n1 = IP^n2 = SteamID");
	bind_pcvar_num(pCvar, g_eCvars[TOP_BY]);

	pCvar = create_cvar("hns_save_top", "1", FCVAR_NONE, "Enable/Disable Top10:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[SAVE_TOP]);

	pCvar = create_cvar("hns_map_top", "1", FCVAR_NONE, "Enable/Disable Map Top:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[MAP_TOP]);

	pCvar = create_cvar("hns_save_extras_top", "1", FCVAR_NONE, "Enable/Disable Extra Tops:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[SAVE_EXTRAS_TOP]);

	pCvar = create_cvar("hns_weapons_top", "1", FCVAR_NONE, "Enable/Disable Weapons Tops:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[WEAPONS_TOP]);

	pCvar = create_cvar("hns_block_top", "1", FCVAR_NONE, "Enable/Disable Block Tops:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[BLOCK_TOP]);

	pCvar = create_cvar("hns_block_weapons_top", "1", FCVAR_NONE, "Enable/Disable Block Tops for other weapons:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[BLOCK_WEAPONS_TOP]);

	pCvar = create_cvar("hns_legal_settings", "1", FCVAR_NONE, "Allow to check player for legal settings:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[LEGAL_SETTINGS]);

	pCvar = create_cvar("hns_fps_stats", "1", FCVAR_NONE, "Count stats with FPS or not:^n0 = Jumps with FPS count^n1 = Jumps with more tha 100FPS doesn't count");
	bind_pcvar_num(pCvar, g_eCvars[FPS]);

	pCvar = create_cvar("hns_bug_check", "1", FCVAR_NONE, "Allow checking for bug distance");
	bind_pcvar_num(pCvar, g_eCvars[BUG_CHECK]);

	pCvar = create_cvar("hns_script_detection", "0", FCVAR_NONE, "Enable/Disable Script Detection:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[SCRIPT_DETECTION]);

	pCvar = create_cvar("hns_script_work", "0", FCVAR_NONE, "Antiscript works if player distance more then (0=good,1=pro,2=holy,3=leet,4=god distance)");
	bind_pcvar_num(pCvar, g_eCvars[SCRIPT_WORK]);

	pCvar = create_cvar("hns_script_notify", "0", FCVAR_NONE, "Print messages to all people on server with scripter name");
	bind_pcvar_num(pCvar, g_eCvars[SCRIPT_NOTIFY]);

	pCvar = create_cvar("hns_script_punishment", "0", FCVAR_NONE, "0 = nothing^n1 = kick^n2 = ban");
	bind_pcvar_num(pCvar, g_eCvars[SCRIPT_PUNISHMENT]);

	pCvar = create_cvar("hns_ban_type", "0", FCVAR_NONE, "0 = standart bans^n1 = amxbans");
	bind_pcvar_num(pCvar, g_eCvars[BAN_TYPE]);

	pCvar = create_cvar("hns_ban_minutes", "45", FCVAR_NONE, "Ban time in minutes");
	bind_pcvar_num(pCvar, g_eCvars[BAN_MINUTES]);

	pCvar = create_cvar("hns_ban_by", "0", FCVAR_NONE, "Ban by:^n0 = name^n1 = ip^n2 = steam");
	bind_pcvar_num(pCvar, g_eCvars[BAN_AUTHID]);

	pCvar = create_cvar("hns_chat_prefix", "!g[HNS JumpStats]", FCVAR_NONE, "Chat prefix for all messages");
	bind_pcvar_string(pCvar, g_eCvars[CHAT_PREFIX], charsmax(g_eCvars[CHAT_PREFIX]));

	pCvar = create_cvar("hns_airaccelerate", "100", FCVAR_NONE, "How to set up a server by value sv_airaccelerate (Varible=xx, but var=0 reserved for 10aa, var=1 for 100aa)");
	bind_pcvar_num(pCvar, g_eCvars[AIRACCELERATE]);

	pCvar = create_cvar("hns_gravity", "0", FCVAR_NONE, "How to set up a server by value sv_gravity (Varible=xx, but var=0 reserved for 800 gravity, var=1 for 500 gravity)");
	bind_pcvar_num(pCvar, g_eCvars[JUMP_GRAVITY]);

	pCvar = create_cvar("hns_vip_jumpstats", "1", FCVAR_NONE, "Enable/Disable VIP JumpStats^nIdea behind is T always have Stats & CT Doesn't have stats unless has the VIP Flag");
	bind_pcvar_num(pCvar, g_eCvars[VIP_JUMPSTATS]);

	pCvar = create_cvar("hns_vip_access", "b", FCVAR_NONE, "VIP Access flag");
	bind_pcvar_string(pCvar, g_eCvars[VIP_ACCESS], charsmax(g_eCvars[VIP_ACCESS]));

	pCvar = create_cvar("hns_no_slow_down", "1", FCVAR_NONE, "Enable/Disable showing stats with No Slow Down:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[NOSLOWDOWN]);

	pCvar = create_cvar("hns_max_strafes", "20", FCVAR_NONE, "Max Strafes (If players Strafes > Max, stats doesn't show");
	bind_pcvar_num(pCvar, g_eCvars[MAX_STRAFES]);

	pCvar = create_cvar("hns_ingame_strafes", "0", FCVAR_NONE, "Enable/Disable InGame Strafe Stats:^n0 = Off^n1 = On");
	bind_pcvar_num(pCvar, g_eCvars[INGAME_STRAFES]);

	pCvar = create_cvar("hns_minimum_pre_to_show", "60", FCVAR_NONE, "Minimum pre to show in hud");
	bind_pcvar_num(pCvar, g_eCvars[MINIMUM_PRE_TO_SHOW]);

	pCvar = create_cvar("hns_max_block_to_show", "290", FCVAR_NONE, "Max block to show in edge");
	bind_pcvar_num(pCvar, g_eCvars[MAX_BLOCK_TO_SHOW]);

	pCvar = create_cvar("hns_min_block_to_show", "120", FCVAR_NONE, "Min block to show in edge");
	bind_pcvar_num(pCvar, g_eCvars[MIN_BLOCK_TO_SHOW]);

	pCvar = create_cvar("hns_sql_host", "127.0.0.1", FCVAR_NONE, "SQL Data:^nHost");
	bind_pcvar_string(pCvar, g_eCvarSQL[SQL_HOST], charsmax(g_eCvarSQL[SQL_HOST]));

	pCvar = create_cvar("hns_sql_user", "root", FCVAR_NONE, "SQL Data:^nUser");
	bind_pcvar_string(pCvar, g_eCvarSQL[SQL_USER], charsmax(g_eCvarSQL[SQL_USER]));

	pCvar = create_cvar("hns_sql_pass", "", FCVAR_NONE, "SQL Data:^nPassword");
	bind_pcvar_string(pCvar, g_eCvarSQL[SQL_PASS], charsmax(g_eCvarSQL[SQL_PASS]));

	pCvar = create_cvar("hns_sql_db", "hns_jumpstats", FCVAR_NONE, "SQL Data:^nDataBase");
	bind_pcvar_string(pCvar, g_eCvarSQL[SQL_DB], charsmax(g_eCvarSQL[SQL_DB]));

	pCvar = create_cvar("hns_url", "http://localhost/uq_jumpstats/index.php?type=lj&from_game=true", FCVAR_NONE, "URL Link");
	bind_pcvar_string(pCvar, g_eCvarSQL[URL], charsmax(g_eCvarSQL[URL]));

	pCvar = create_cvar("hns_update_auth", "1", FCVAR_NONE, "Update in DB Steam and Ip");
	bind_pcvar_num(pCvar, g_eCvarSQL[UPDATE_AUTH]);

	pCvar = create_cvar("hns_hud_stats_red", "0", FCVAR_NONE, "Color of Hud Stats message [Red]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_STATS_RED]);

	pCvar = create_cvar("hns_hud_stats_green", "150", FCVAR_NONE, "Color of Hud Stats message [Green]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_STATS_GREEN]);

	pCvar = create_cvar("hns_hud_stats_blue", "0", FCVAR_NONE, "Color of Hud Stats message [Blue]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_STATS_BLUE]);

	pCvar = create_cvar("hns_hud_failstats_red", "150", FCVAR_NONE, "Color of Hud Fail Stats message [Red]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[FAIL_HUD_STATS_RED]);

	pCvar = create_cvar("hns_hud_failstats_green", "0", FCVAR_NONE, "Color of Hud Fail Stats message [Green]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[FAIL_HUD_STATS_GREEN]);

	pCvar = create_cvar("hns_hud_failstats_blue", "0", FCVAR_NONE, "Color of Hud Fail Stats message [Blue]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[FAIL_HUD_STATS_BLUE]);

	pCvar = create_cvar("hns_stats_pos_x", "-1.0", FCVAR_NONE, "Positon of the Hud Stats message [X]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_STATS_X]);

	pCvar = create_cvar("hns_stats_pos_y", "0.62", FCVAR_NONE, "Positon of the Hud Stats message [Y]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_STATS_Y]);

	pCvar = create_cvar("hns_strafe_stats_pos_x", "0.70", FCVAR_NONE, "Positon of the Hud Strafe Stats message [X]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_STRAFE_X]);

	pCvar = create_cvar("hns_strafe_stats_pos_y", "0.40", FCVAR_NONE, "Positon of the Hud Strafe Stats message [Y]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_STRAFE_Y]);

	pCvar = create_cvar("hns_duck_stats_pos_x", "0.60", FCVAR_NONE, "Positon of the Hud Duck stats message [X]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_DUCK_X]);

	pCvar = create_cvar("hns_duck_stats_pos_y", "0.78", FCVAR_NONE, "Positon of the Hud Duck stats message [Y]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_DUCK_Y]);

	pCvar = create_cvar("hns_speedmeter_pos_x", "-1.0", FCVAR_NONE, "Positon of the Hud Speed Meter message [X]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_SPEED_X]);

	pCvar = create_cvar("hns_speedmeter_pos_y", "0.93", FCVAR_NONE, "Positon of the Hud Speed Meter message [Y]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_SPEED_Y]);

	pCvar = create_cvar("hns_prestrafe_pos_x", "-1.0", FCVAR_NONE, "Positon of the Hud Prestrafe message [X]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_PRESTRAFE_X]);

	pCvar = create_cvar("hns_prestrafe_pos_y", "0.57", FCVAR_NONE, "Positon of the Hud Prestrafe message [Y]");
	bind_pcvar_float(pCvar, g_eCvarsExtraSettings[HUD_PRESTRAFE_Y]);

	pCvar = create_cvar("hns_hud_speedmeter_red", "0", FCVAR_NONE, "Color of Hud Speed Meter message [Red]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_SPEED_R]);

	pCvar = create_cvar("hns_hud_speedmeter_green", "180", FCVAR_NONE, "Color of Hud Speed Meter message [Green]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_SPEED_G]);

	pCvar = create_cvar("hns_hud_speedmeter_blue", "0", FCVAR_NONE, "Color of Hud Speed Meter message [Blue]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_SPEED_B]);

	pCvar = create_cvar("hns_hud_prestrafe_red", "0", FCVAR_NONE, "Color of Hud PreStrafe message [Red]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_PRESTRAFE_R]);

	pCvar = create_cvar("hns_hud_prestrafe_green", "180", FCVAR_NONE, "Color of Hud PreStrafe message [Green]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_PRESTRAFE_G]);

	pCvar = create_cvar("hns_hud_prestrafe_blue", "0", FCVAR_NONE, "Color of Hud PreStrafe message [Blue]");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_PRESTRAFE_B]);

	pCvar = create_cvar("hns_hud_channel_stats", "3", FCVAR_NONE, "Color of Hud Channel Stats message");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_CHANNEL_STATS]);

	pCvar = create_cvar("hns_hud_channel_strafe", "4", FCVAR_NONE, "Color of Hud Channel Strafe message");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_CHANNEL_STRAFE]);

	pCvar = create_cvar("hns_hud_channel_duck", "1", FCVAR_NONE, "Color of Hud Channel Duck message");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_CHANNEL_DUCK]);

	pCvar = create_cvar("hns_hud_channel_speed", "2", FCVAR_NONE, "Color of Hud Channel Speed message");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_CHANNEL_SPEED]);

	pCvar = create_cvar("hns_hud_channel_pre", "3", FCVAR_NONE, "Color of Hud Channel Prestrafe message");
	bind_pcvar_num(pCvar, g_eCvarsExtraSettings[HUD_CHANNEL_PRE]);

	pCvar = create_cvar("hns_long_jump", "1", FCVAR_NONE, "Enable/Disable Long Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[LongJump]);

	pCvar = create_cvar("hns_count_jump", "1", FCVAR_NONE, "Enable/Disable Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[CountJump]);

	pCvar = create_cvar("hns_double_count_jump", "1", FCVAR_NONE, "Enable/Disable Double Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[DoubleCJ]);

	pCvar = create_cvar("hns_multi_count_jump", "1", FCVAR_NONE, "Enable/Disable Multi Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[MultiCJ]);

	pCvar = create_cvar("hns_ladder_jump", "1", FCVAR_NONE, "Enable/Disable Ladder Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[LadderJump]);

	pCvar = create_cvar("hns_ladder_bhop_jump", "1", FCVAR_NONE, "Enable/Disable Ladder Bhop Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[LadderBhop]);

	pCvar = create_cvar("hns_bhop_jump", "1", FCVAR_NONE, "Enable/Disable Bhop Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[Bhop]);

	pCvar = create_cvar("hns_standup_bhop_jump", "1", FCVAR_NONE, "Enable/Disable Stand-Up Bhop Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[StandUpBhop]);

	pCvar = create_cvar("hns_drop_bhop_jump", "1", FCVAR_NONE, "Enable/Disable Drop Bhop Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[DropBhop]);

	pCvar = create_cvar("hns_standup_count_jump", "1", FCVAR_NONE, "Enable/Disable Stand-Up Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[StandUpCountJump]);

	pCvar = create_cvar("hns_drop_count_jump", "1", FCVAR_NONE, "Enable/Disable Drop Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[DropCJ]);

	pCvar = create_cvar("hns_weird_jump", "1", FCVAR_NONE, "Enable/Disable Weird Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[WeirdJump]);

	pCvar = create_cvar("hns_double_standup_count_jump", "1", FCVAR_NONE, "Enable/Disable Double Stand-Up Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[DoubleSCJ]);

	pCvar = create_cvar("hns_multi_standup_count_jump", "1", FCVAR_NONE, "Enable/Disable Multi Stand-Up Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[MultiSCJ]);

	pCvar = create_cvar("hns_drop_standup_count_jump", "1", FCVAR_NONE, "Enable/Disable Drop Stand-Up Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[Drop_SCJ]);

	pCvar = create_cvar("hns_drop_double_standup_count_jump", "1", FCVAR_NONE, "Enable/Disable Drop Double Stand-Up Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[DropDoubleSCJ]);

	pCvar = create_cvar("hns_drop_multi_standup_count_jump", "1", FCVAR_NONE, "Enable/Disable Drop Multi Stand-Up Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[DropMultiSCJ]);

	pCvar = create_cvar("hns_duck_bhop_jump", "1", FCVAR_NONE, "Enable/Disable Duck Bhop Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[DuckBhopJump]);

	pCvar = create_cvar("hns_real_ladder_bhop_jump", "1", FCVAR_NONE, "Enable/Disable Real Ladder Bhop Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[Real_Ladder_Bhop]);

	pCvar = create_cvar("hns_up_bhop_jump", "1", FCVAR_NONE, "Enable/Disable Up Bhop Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[UpBhop]);

	pCvar = create_cvar("hns_up_standup_bhop_jump", "1", FCVAR_NONE, "Enable/Disable Up Stand-Up Bhop Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[UpStandUpBhop]);

	pCvar = create_cvar("hns_up_bhop_in_duck_jump", "1", FCVAR_NONE, "Enable/Disable Up Bhop In Duck Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[UpBhopInDuckJump]);

	pCvar = create_cvar("hns_bhop_in_duck_jump", "1", FCVAR_NONE, "Enable/Disable Bhop In Duck Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[BhopInDuckJump]);

	pCvar = create_cvar("hns_multi_bhop_jump", "1", FCVAR_NONE, "Enable/Disable Multi Bhop Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[MultiBhop]);

	pCvar = create_cvar("hns_drop_double_count_jump", "1", FCVAR_NONE, "Enable/Disable Drop Double Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[DropDCJ]);

	pCvar = create_cvar("hns_drop_multi_count_jump", "1", FCVAR_NONE, "Enable/Disable Drop Multi Count Jump Technique");
	bind_pcvar_num(pCvar, g_eCvarsTechnique[DropMCJ]);

	// LJ
	pCvar = create_cvar("hns_good_lj", "240", FCVAR_NONE, "Long Jump^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[LJ][GOOD]);

	pCvar = create_cvar("hns_pro_lj", "245", FCVAR_NONE, "Long Jump^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[LJ][PRO]);

	pCvar = create_cvar("hns_holy_lj", "250", FCVAR_NONE, "Long Jump^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[LJ][HOLY]);

	pCvar = create_cvar("hns_leet_lj", "253", FCVAR_NONE, "Long Jump^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[LJ][LEET]);

	pCvar = create_cvar("hns_god_lj", "255", FCVAR_NONE, "Long Jump^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[LJ][GOD]);

	// CJ
	pCvar = create_cvar("hns_good_cj", "250", FCVAR_NONE, "Count Jump^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[CJ][GOOD]);

	pCvar = create_cvar("hns_pro_cj", "255", FCVAR_NONE, "Count Jump^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[CJ][PRO]);

	pCvar = create_cvar("hns_holy_cj", "260", FCVAR_NONE, "Count Jump^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[CJ][HOLY]);

	pCvar = create_cvar("hns_leet_cj", "265", FCVAR_NONE, "Count Jump^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[CJ][LEET]);

	pCvar = create_cvar("hns_god_cj", "272", FCVAR_NONE, "Count Jump^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[CJ][GOD]);

	// DCJ / MCJ
	pCvar = create_cvar("hns_good_dcj", "250", FCVAR_NONE, "Double Count Jump + Multi Count Jump^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DCJ][GOOD]);

	pCvar = create_cvar("hns_pro_dcj", "255", FCVAR_NONE, "Double Count Jump + Multi Count Jump^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DCJ][PRO]);

	pCvar = create_cvar("hns_holy_dcj", "260", FCVAR_NONE, "Double Count Jump + Multi Count Jump^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DCJ][HOLY]);

	pCvar = create_cvar("hns_leet_dcj", "265", FCVAR_NONE, "Double Count Jump + Multi Count Jump^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DCJ][LEET]);

	pCvar = create_cvar("hns_god_dcj", "272", FCVAR_NONE, "Double Count Jump + Multi Count Jump^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[DCJ][GOD]);

	// Ladder
	pCvar = create_cvar("hns_good_ladder", "150", FCVAR_NONE, "Ladder Jump^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[LADDER][GOOD]);

	pCvar = create_cvar("hns_pro_ladder", "160", FCVAR_NONE, "Ladder Jump^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[LADDER][PRO]);

	pCvar = create_cvar("hns_holy_ladder", "170", FCVAR_NONE, "Ladder Jump^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[LADDER][HOLY]);

	pCvar = create_cvar("hns_leet_ladder", "185", FCVAR_NONE, "Ladder Jump^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[LADDER][LEET]);

	pCvar = create_cvar("hns_god_ladder", "190", FCVAR_NONE, "Ladder Jump^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[LADDER][GOD]);

	// Bhop / Stand-Up Bhop
	pCvar = create_cvar("hns_good_bj", "230", FCVAR_NONE, "Bhop Jump + Stand-Up Bhop Jump^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[BJ][GOOD]);

	pCvar = create_cvar("hns_pro_bj", "235", FCVAR_NONE, "Bhop Jump + Stand-Up Bhop Jump^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[BJ][PRO]);

	pCvar = create_cvar("hns_holy_bj", "240", FCVAR_NONE, "Bhop Jump + Stand-Up Bhop Jump^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[BJ][HOLY]);

	pCvar = create_cvar("hns_leet_bj", "245", FCVAR_NONE, "Bhop Jump + Stand-Up Bhop Jump^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[BJ][LEET]);

	pCvar = create_cvar("hns_god_bj", "247", FCVAR_NONE, "Bhop Jump + Stand-Up Bhop Jump^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[BJ][GOD]);

	// Weird Jump / Drop Count Jump / Ladder Bhop
	pCvar = create_cvar("hns_good_wj", "255", FCVAR_NONE, "Weird Jump + Drop CountJump + Ladder Bhop^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[WJ][GOOD]);

	pCvar = create_cvar("hns_pro_wj", "260", FCVAR_NONE, "Weird Jump + Drop CountJump + Ladder Bhop^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[WJ][PRO]);

	pCvar = create_cvar("hns_holy_wj", "265", FCVAR_NONE, "Weird Jump + Drop CountJump + Ladder Bhop^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[WJ][HOLY]);

	pCvar = create_cvar("hns_leet_wj", "270", FCVAR_NONE, "Weird Jump + Drop CountJump + Ladder Bhop^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[WJ][LEET]);

	pCvar = create_cvar("hns_god_wj", "272", FCVAR_NONE, "Weird Jump + Drop CountJump + Ladder Bhop^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[WJ][GOD]);

	// Drop Bhop Jump
	pCvar = create_cvar("hns_good_dbj", "240", FCVAR_NONE, "Drop Bhop Jump^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DBJ][GOOD]);

	pCvar = create_cvar("hns_pro_dbj", "250", FCVAR_NONE, "Drop Bhop Jump^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DBJ][PRO]);

	pCvar = create_cvar("hns_holy_dbj", "265", FCVAR_NONE, "Drop Bhop Jump^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DBJ][HOLY]);

	pCvar = create_cvar("hns_leet_dbj", "270", FCVAR_NONE, "Drop Bhop Jump^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DBJ][LEET]);

	pCvar = create_cvar("hns_god_dbj", "272", FCVAR_NONE, "Drop Bhop Jump^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[DBJ][GOD]);

	// Stand-Up CountJump
	pCvar = create_cvar("hns_good_scj", "245", FCVAR_NONE, "Stand-Up CountJump^n(Double or Multi Stand-Up CountJump = SCJ+10units)^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[SCJ][GOOD]);

	pCvar = create_cvar("hns_pro_scj", "250", FCVAR_NONE, "Stand-Up CountJump^n(Double or Multi Stand-Up CountJump = SCJ+10units)^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[SCJ][PRO]);

	pCvar = create_cvar("hns_holy_scj", "265", FCVAR_NONE, "Stand-Up CountJump^n(Double or Multi Stand-Up CountJump = SCJ+10units)^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[SCJ][HOLY]);

	pCvar = create_cvar("hns_leet_scj", "270", FCVAR_NONE, "Stand-Up CountJump^n(Double or Multi Stand-Up CountJump = SCJ+10units)^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[SCJ][LEET]);

	pCvar = create_cvar("hns_god_scj", "272", FCVAR_NONE, "Stand-Up CountJump^n(Double or Multi Stand-Up CountJump = SCJ+10units)^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[SCJ][GOD]);

	// Drop Stand-Up CountJump (Double, Multi)
	pCvar = create_cvar("hns_good_dropscj", "255", FCVAR_NONE, "Drop Stand-Up CountJump (double, multi)^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DROPSCJ][GOOD]);

	pCvar = create_cvar("hns_pro_dropscj", "260", FCVAR_NONE, "Drop Stand-Up CountJump (double, multi)^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DROPSCJ][PRO]);

	pCvar = create_cvar("hns_holy_dropscj", "265", FCVAR_NONE, "Drop Stand-Up CountJump (double, multi)^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DROPSCJ][HOLY]);

	pCvar = create_cvar("hns_leet_dropscj", "270", FCVAR_NONE, "Drop Stand-Up CountJump (double, multi)^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DROPSCJ][LEET]);

	pCvar = create_cvar("hns_god_dropscj", "272", FCVAR_NONE, "Drop Stand-Up CountJump (double, multi)^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[DROPSCJ][GOD]);

	// Duck Bhop
	pCvar = create_cvar("hns_good_duckbhop", "120", FCVAR_NONE, "Duck Bhop^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DUCKBHOP][GOOD]);

	pCvar = create_cvar("hns_pro_duckbhop", "130", FCVAR_NONE, "Duck Bhop^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DUCKBHOP][PRO]);

	pCvar = create_cvar("hns_holy_duckbhop", "140", FCVAR_NONE, "Duck Bhop^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DUCKBHOP][HOLY]);

	pCvar = create_cvar("hns_leet_duckbhop", "150", FCVAR_NONE, "Duck Bhop^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[DUCKBHOP][LEET]);

	pCvar = create_cvar("hns_god_duckbhop", "160", FCVAR_NONE, "Duck Bhop^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[DUCKBHOP][GOD]);

	// Bhop in Duck
	pCvar = create_cvar("hns_good_bhopinduck", "205", FCVAR_NONE, "Bhop in Duck^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[BHOPINDUCK][GOOD]);

	pCvar = create_cvar("hns_pro_bhopinduck", "210", FCVAR_NONE, "Bhop in Duck^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[BHOPINDUCK][PRO]);

	pCvar = create_cvar("hns_holy_bhopinduck", "215", FCVAR_NONE, "Bhop in Duck^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[BHOPINDUCK][HOLY]);

	pCvar = create_cvar("hns_leet_bhopinduck", "218", FCVAR_NONE, "Bhop in Duck^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[BHOPINDUCK][LEET]);

	pCvar = create_cvar("hns_god_bhopinduck", "220", FCVAR_NONE, "Bhop in Duck^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[BHOPINDUCK][GOD]);

	// Real Ladder Bhop
	pCvar = create_cvar("hns_good_realldbhop", "240", FCVAR_NONE, "Real Ladder Bhop^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[REALLADDERBHOP][GOOD]);

	pCvar = create_cvar("hns_pro_realldbhop", "250", FCVAR_NONE, "Real Ladder Bhop^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[REALLADDERBHOP][PRO]);

	pCvar = create_cvar("hns_holy_realldbhop", "265", FCVAR_NONE, "Real Ladder Bhop^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[REALLADDERBHOP][HOLY]);

	pCvar = create_cvar("hns_leet_realldbhop", "270", FCVAR_NONE, "Real Ladder Bhop^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[REALLADDERBHOP][LEET]);

	pCvar = create_cvar("hns_god_realldbhop", "272", FCVAR_NONE, "Real Ladder Bhop^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[REALLADDERBHOP][GOD]);

	// Up Bhop
	pCvar = create_cvar("hns_good_upbj", "225", FCVAR_NONE, "Up Bhop^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPBJ][GOOD]);

	pCvar = create_cvar("hns_pro_upbj", "230", FCVAR_NONE, "Up Bhop^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPBJ][PRO]);

	pCvar = create_cvar("hns_holy_upbj", "235", FCVAR_NONE, "Up Bhop^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPBJ][HOLY]);

	pCvar = create_cvar("hns_leet_upbj", "240", FCVAR_NONE, "Up Bhop^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPBJ][LEET]);

	pCvar = create_cvar("hns_god_upbj", "245", FCVAR_NONE, "Up Bhop^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPBJ][GOD]);

	// Up Stand-Up Bhop
	pCvar = create_cvar("hns_good_upbj", "230", FCVAR_NONE, "Up Stand-Up Bhop^nMinimum distance to show chat message. [Grey message]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPSBJ][GOOD]);

	pCvar = create_cvar("hns_pro_upsbj", "235", FCVAR_NONE, "Up Stand-Up Bhop^nMinimum distance to show chat message. [Green message]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPSBJ][PRO]);

	pCvar = create_cvar("hns_holy_upsbj", "240", FCVAR_NONE, "Up Stand-Up Bhop^nMinimum distance to show chat message. [Blue message]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPSBJ][HOLY]);

	pCvar = create_cvar("hns_leet_upsbj", "244", FCVAR_NONE, "Up Stand-Up Bhop^nMinimum distance to show chat message. [Red message]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPSBJ][LEET]);

	pCvar = create_cvar("hns_god_upsbj", "246", FCVAR_NONE, "Up Stand-Up Bhop^nMinimum distance to show chat message. [Red message + sound godlike for all players to hear]");
	bind_pcvar_num(pCvar, g_eCvarStats[UPSBJ][GOD]);

	AutoExecConfig(true, "HNS_JumpStats", "HuehuePlugins_Config")
}
