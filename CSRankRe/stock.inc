#if defined _stock_included
    #endinput
#endif

#define _stock_included

#include <amxmodx>
#include <cstrike>

stock register_cvars()
{
    g_Cvars[CVAR_SQL_HOST] = 			register_cvar("csre_mysql_host", "localhost");
    g_Cvars[CVAR_SQL_USER] = 			register_cvar("csre_mysql_user", "root");
    g_Cvars[CVAR_SQL_PASS] = 			register_cvar("csre_mysql_pass", "");
    g_Cvars[CVAR_SQL_DB] = 				register_cvar("csre_mysql_db", "csrankre");

    g_Cvars[CVAR_SQL_TABLE] = 			register_cvar("csre_mysql_table", "CSRankRe");

    g_Cvars[CVAR_MAIN_FLAG] = 			register_cvar("csre_superadmin_flag", "h");

    g_Cvars[CVAR_EXP_KILL] = 			register_cvar("csre_exp_kill", "1");
    g_Cvars[CVAR_EXP_VIP] = 			register_cvar("csre_exp_bonus_vip", "1");
    g_Cvars[CVAR_EXP_HEAD] = 			register_cvar("csre_exp_bonus_head", "1");

    g_Cvars[CVAR_LEVEL_EXP] = 			register_cvar("csre_level_exp", "100 200 400 700 1000 1300 1700 2100 2500 3000");
     
    g_Cvars[CVAR_MIN_PLAYERS] = 		register_cvar("csre_min_players", "2");
    g_Cvars[CVAR_CASE_PRICE] = 			register_cvar("csre_price_container", "10");

    g_Cvars[CVAR_CHANCE_DROP_CASE] = 	register_cvar("csre_chance_drop_case", "30");
    g_Cvars[CVAR_CHANCE_DROP_KEY] = 	register_cvar("csre_chance_drop_key", "10");

    g_Cvars[CVAR_CHANCE_LEGENDARY] = 	register_cvar("csre_chance_legendary", "2");
    g_Cvars[CVAR_CHANCE_RARE] = 		register_cvar("csre_chance_rare", "10");

    g_Cvars[CVAR_SALE_SKIN_NORMAL] = 	register_cvar("csre_sale_skin_normal", "3");
    g_Cvars[CVAR_SALE_SKIN_RARE] = 		register_cvar("csre_sale_skin_rare", "30");
    g_Cvars[CVAR_SALE_SKIN_LEGENDARY] = register_cvar("csre_sale_skin_legendary", "60");

    g_Cvars[CVAR_MARKET_OFFERS] = 		register_cvar("csre_max_market_offers", "2");
    g_Cvars[CVAR_CHANCE_ITEM_TIME] = 	register_cvar("csre_chance_item_time", "10");

    g_Cvars[CVAR_INFORMER] = 			register_cvar("csre_informer", "1");
    g_Cvars[CVAR_INFORMER_X] = 			register_cvar("csre_informer_x", "0.01");
    g_Cvars[CVAR_INFORMER_Y] = 			register_cvar("csre_informer_y", "0.2");
    g_Cvars[CVAR_INFORMER_TEXT] = 		register_cvar("csre_informer_text", "%name%%n%Level: %level%/%max_level%%n%Exp: %exp%/%exp_next%%n%Tag: %tag%");
    
    g_Cvars[CVAR_STYLE_TOP] = 			register_cvar("csre_style_top", "default");

    g_Cvars[CVAR_VIP_FLAG] = 			register_cvar("csre_vip_flag", "t");
    g_Cvars[CVAR_VIP_EXP] = 			register_cvar("csre_vip_bonus_exp", "1");

    g_Cvars[CVAR_MEDAL_KEYS] = 			register_cvar("csre_medal_key", "3");
    g_Cvars[CVAR_TIME_KEYS_CHANCE] = 	register_cvar("csre_chance_drop_key", "15");

    new execPath[64]
    getDirByType(DirData:DIR_CONFIG, execPath, charsmax(execPath), MAIN_CONFIG)

    if ( file_exists(execPath)) {
        server_cmd("exec %s",execPath)
        return server_exec()
    }

    return PrintMessage("Can't find config file '%s'", execPath)
}

stock bool:check_player_vip(id) {
    return bool:(get_user_flags(id) & read_flags(g_Cvars[CVAR_VIP_FLAG]))
}

stock get_player_weapon_skin (id, team, weaponid) {

    if (team != 1 && team != 2) {
        return 0;
    }
    return g_player_weapons[id][team][weaponid];
}

stock set_player_weapon_skin (id, team, weaponid, item) {
    if (team != RE_TEAM_T && team != RE_TEAM_CT) {
        return;
    }

    g_player_weapons[id][team][weaponid] = item;
}

/**
	Ищет скин по его айди из файла
 */
stock search_array( index ) {
    new skin_id[SKINS_ID_MAX_LEN];
    num_to_str( index, skin_id, charsmax(skin_id))

    new  value = -1;
    // Смотрим, есть ли такой скин в Trie
    TrieGetCell(g_ItemsTrie, skin_id, value)

    if ( value == -1) {
        // Если скина нету, ищем в Array
        value = -3;

        new data[Items], size = ArraySize(g_Items);
        for(new i = 0; i< size; i++)
        {
            ArrayGetArray(g_Items, i, data);
            if(data[ITEM_ID] == index)
                value = i;
        }

    }

    return value;
}

stock has_access( id, cvar) {
    return get_user_flags(id) & cvar_flags(cvar);
}

stock cvar_flags (const cvar)
{
    new _str[16];
    get_pcvar_string(cvar, _str, charsmax(_str))
    
    return read_flags(_str);
}

stock PrintMessage(const szMessage[], any:...)
{
    new szMsg[1024];
    vformat(szMsg, charsmax(szMsg), szMessage, 2);
    
    new LogDat[16]; 
    get_time("%Y_%m_%d", LogDat, 15);

    new LogFile[64];
    getDirByType(DirData:DIR_LOG, LogFile, charsmax(LogFile), "Log%s.log", LogDat)
    log_to_file(LogFile,"[%s] %s",LOG_PREFIX,szMsg)
    
    return -2;
}

public SQL_Error(Handle:query, const error[], errornum, failstate)
{
    new qstring[1024]
    SQL_GetQueryString(query, qstring, 1023)
    
    if(failstate == TQUERY_CONNECT_FAILED) 		PrintMessage("[SQLX] Error connected to database")
    else if (failstate == TQUERY_QUERY_FAILED) 	PrintMessage("[SQLX] Failed")

    PrintMessage("[SQLX] Error '%s' with '%d'", error, errornum)
    PrintMessage("[SQLX] %s", qstring)
    
    new LogDat[16]
    get_time("%Y_%m_%d", LogDat, 15);

    new LogFile[64];
    getDirByType(DirData:DIR_LOG, LogFile, charsmax(LogFile), "QueryError%s.log", LogDat)

    write_file(LogFile, qstring, -1);
    return SQL_FreeHandle(query)
}
stock ClearLogs()
{
    new Array: Logs;
    Logs = ArrayCreate(128);
    
    new szFile[64];
    new LogDir[64];
    getDirByType(DirData:DIR_LOG, LogDir, charsmax(LogDir), "")
    
    new dir = open_dir(LogDir, szFile, charsmax(szFile))
    
    new temp[64], log_time; new del_time = get_systime(0) - 60*60*24*7
    if(dir)
    {
        do
        {
            if(!is_log_file(szFile, strlen(szFile)))
                continue;
            
            copy(temp, charsmax(temp), szFile)

            
            replace(temp, charsmax(temp), "Log_", "")
            
            
            log_time = parse_time(temp, "%Y_%m_%d")
            
            if(log_time - del_time <= 0)
                ArrayPushString(Logs,szFile)
        }
        while(next_file(dir, szFile, charsmax(szFile)))
        
        close_dir(dir)
    }
    
    new size = ArraySize(Logs)
    for(new i; i<size; i++)
    {
        ArrayGetString(Logs, i, temp, charsmax(temp))
        
        formatex(szFile, charsmax(szFile), "%s%s",LogDir,temp)
        delete_file(szFile)
    }
    
    ArrayDestroy(Logs)
}
/**
	АОаоаоаоа
 */
stock bool:is_log_file(CurrNAME[], len  )
{
    static S_TRY[] = ".log"
    
    if ( ( len >= 4 ) && ( CurrNAME[ len - 1 ] == S_TRY[ 3 ] ) && 
    ( CurrNAME[ len - 2 ] == S_TRY[ 2 ] ) && ( CurrNAME[ len - 3 ] == S_TRY[ 1 ] ) && 
    ( CurrNAME[ len - 4 ] == S_TRY[ 0 ] ) ) 
    return true;
    
    return false;
}
stock MenuSetProps( id,menu)
{
    static const plugin_x_format[] = "\wCSRank\rRe"

    new szText[64]
    formatex(szText, sizeof(szText) - 1, "%L", id, "CSRE_MENU_PREV")
    menu_setprop(menu, MPROP_BACKNAME, szText)
    
    formatex(szText, sizeof(szText) - 1, "%L", id, "CSRE_MENU_NEXT")
    menu_setprop(menu, MPROP_NEXTNAME, szText)
    
    formatex(szText, sizeof(szText) - 1, "%L^n^n%s\w | \y%s", id, "CSRE_MENU_EXIT", plugin_x_format, VERSION)
    menu_setprop(menu, MPROP_EXITNAME, szText)
    
    return 1
} 

stock skinClassStr(data[Items], str[], len) {
    new itemColor[] = "\w";

    switch (data[ITEM_CLASS]) {
        case 3: formatex(itemColor, charsmax(itemColor), "\y");
        case 2: formatex(itemColor, charsmax(itemColor), "\r");
        case 1: formatex(itemColor, charsmax(itemColor), "\w");
    }

    return formatex(str, len, "%s%s", itemColor, data[ITEM_NAME])
}

/**
	Гениально
 */
stock isItemsEquals( itemOne, itemTwo) {
    return 	itemOne == itemTwo
}

/**
	Проверяет надет ли определенный скин у игрока
 */
stock bool:isWeaponSkinOnPlayer(id, team, weaponid, item) {
    new current = get_player_weapon_skin(id, team, weaponid);

    if ( isItemsEquals(current, item) ) return true;

    return false;
}

/**
	ЗАменяет скин оружия у игрока
 */
stock ReplaceItem(id, wid, item, model_v[], model_p[])
{
    #define is_valid_pev(%0) (pev_valid(%0) == 2)
    
    const XO_CBASEPLAYER = 5;
    const XO_CBASEPLAYERWEAPON = 4;

    const m_pNext = 42;
    const m_iId = 43;
    const m_pActiveItem = 373;
    const m_rgpPlayerItems_CBasePlayer = 367;

    new weapon, weaponid;
    new cur_weapon = get_pdata_cbase(id, m_pActiveItem, XO_CBASEPLAYER);

    #define MAX_ITEM_SLOTS 6

    for(new i; i < MAX_ITEM_SLOTS; i++)
    {
        weapon = get_pdata_cbase(id, m_rgpPlayerItems_CBasePlayer + i, XO_CBASEPLAYER);

        while (is_valid_pev(weapon))
        {
            weaponid = get_pdata_int(weapon, m_iId, XO_CBASEPLAYERWEAPON);

            if(weaponid == wid)
            {
                set_weapon_skin(weapon, item == 0 ? ZERO_SKIN_INT : item);

                if(weapon == cur_weapon)
                {
                    set_pev(id, pev_viewmodel2, model_v);
                    set_pev(id, pev_weaponmodel2, model_p);
                }
                // stop cycles
                i = 6; break;
            }

            weapon = get_pdata_cbase(weapon, m_pNext, XO_CBASEPLAYERWEAPON);
        }
    }

    //checkSetStatus(id)
}

stock CmdScreenFade(id, Timer, Colors[3], Alpha) 
{	
    static msg_ScreenFade
    
    if(!msg_ScreenFade)
        msg_ScreenFade = get_user_msgid("ScreenFade");
        
    message_begin(MSG_ONE_UNRELIABLE, msg_ScreenFade, _, id);
    write_short((1<<12) * 2* Timer);
    write_short(1<<12);
    write_short(0);
    write_byte(Colors[0]);
    write_byte(Colors[1]);
    write_byte(Colors[2]);
    write_byte(Alpha);
    message_end();
}

stock get_sale_price(const item_class) {
    
    switch (item_class) {
        case 3: return get_pcvar_num(g_Cvars[CVAR_SALE_SKIN_LEGENDARY]);
        case 2: return get_pcvar_num(g_Cvars[CVAR_SALE_SKIN_RARE]);
    }

    return get_pcvar_num(g_Cvars[CVAR_SALE_SKIN_NORMAL]);
}

stock get_hud_color_skin( skin_level, color[3] ) {
    color[0] = 150;
    color[1] = 150;
    color[2]  =150;

    switch (skin_level) {
        case ITEM_CLASS_LEGENDARY: {
            color[0] = 255;
            color[1] = 255;
            color[2]  =0;
        }
        case ITEM_CLASS_RARE: {
            color[0] = 255;
            color[1] = 0;
            color[2]  =0;
        }
    }
}
/**
	Конвертирует буквенный ID в числа вида "l1" "r1" "n1"
 */
stock convert_skin_id( skin_id[], len) {
    new prefix[2];
    prefix[0] = skin_id[0];
    if ( !is_str_num(prefix) ) replace(skin_id, len, prefix, "");

    new count = 0;
    switch (prefix[0]) {
        case 'l' : count = 10000 + str_to_num(skin_id);
        case 'r' : count = 5000 + str_to_num(skin_id);
        case 'n' : count = 1000 + str_to_num(skin_id);

        default : count = str_to_num(skin_id);
    }

    return count
}

/**
    К сожалению на 1.8.2 есть баги с функцией get_user_team, поэтому дописываем свою
 */
stock get_user_team2(id)
{
    new CsTeams:team = cs_get_user_team(id);

    switch (team) {
        case CS_TEAM_UNASSIGNED: return RE_TEAM_UNKOWN;
        case CS_TEAM_T: return RE_TEAM_T;
        case CS_TEAM_CT: return RE_TEAM_CT;
        case CS_TEAM_SPECTATOR: return RE_TEAM_SPECTATOR;
    }

    return RE_TEAM_UNKOWN
}


stock get_weapon_csw(weapon_name[])
{
    static weapons[][] = 
    {
        "", "weapon_p228", "weapon_shield", "weapon_scout", "weapon_hegrenade", "weapon_xm1014", "weapon_c4",
        "weapon_mac10", "weapon_aug", "weapon_smokegrenade", "weapon_elite", "weapon_fiveseven", "weapon_ump45",
        "weapon_sg550", "weapon_galil", "weapon_famas", "weapon_usp", "weapon_glock18", "weapon_awp", "weapon_mp5navy",
        "weapon_m249", "weapon_m3", "weapon_m4a1", "weapon_tmp", "weapon_g3sg1", "weapon_flashbang", "weapon_deagle",
        "weapon_sg552", "weapon_ak47", "weapon_knife", "weapon_p90"
    };

    for(new i = 1; i < sizeof(weapons); i++)
    {
        if(equali(weapon_name, weapons[i]))
        {
            return i;
        }
    }

    return 0;
}

