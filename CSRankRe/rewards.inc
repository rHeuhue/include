#if defined _rewards_included 
    #endinput
#endif

#define _rewards_included 

#include <amxmodx>

enum _: Rewards
{
    REWARDS_NONE = 0,

    REWARDS_EXP,
    REWARDS_CASE,
    REWARDS_KEY,
    REWARDS_COIN,

    REWARDS_SKIN
}

static const _szRewards_reward[Rewards][] = 
{
    "",
    "exp",
    "case",
    "key",
    "coin",
    "skin"
}

stock const REWARDS_INI_TAG[] = "[REWARDS]";

stock Rewards_Init() {
    g_rewards = ArrayCreate(RewardsArray)
    Rewards_readConfig()
}

stock Rewards_end() {
    ArrayDestroy(g_rewards)
}

stock Rewards_Check(id)
{
    if ( !Rewards_isEnabled() ) return;

    new sys = get_systime(0);
    if ( g_player_data[id][PD_CHECK_TIME] != 0 && g_player_data[id][PD_CHECK_TIME] - sys > 0) return;
    g_player_data[id][PD_CHECK_TIME] = sys + 3600*24*1; // one day
    AddRewardToPlayer(id)
}

stock AddRewardToPlayer(id) {
    
    if ( g_player_stats[id][PS_REWARDS] >= ArraySize(g_rewards) ) {
        g_player_stats[id][PS_REWARDS] = 0;
    }

    new data[RewardsArray]
    ArrayGetArray(g_rewards, g_player_stats[id][PS_REWARDS], data)
    
    new reward[32];
    Rewards_getReward(id, data[RA_TYPE], data[RA_COUNT], reward, charsmax(reward))
    Rewards_AddReward(id, data[RA_TYPE], data[RA_COUNT]);

    new screenFade[3];
    for(new i; i<3; i++)    screenFade[i] = random_num(50, 200)

    CmdScreenFade(id, 3, screenFade, 100)

    Print(id, "%L", id, "CSRE_REWARDS_CHAT", g_player_stats[id][PS_REWARDS] + 1, reward)
    g_player_stats[id][PS_REWARDS] += 1;
}

public Rewards_AddReward( id, const reward, const count)
{
    new cid = count;

    switch (reward)
    {
        case REWARDS_NONE:   	return;
        case REWARDS_EXP:    	CoreExp_ExpUpdate(id, count, true, false)
        case REWARDS_CASE:		Stats_AddPlayerCases(id, count)
        case REWARDS_KEY: 		Stats_AddPlayerKeys(id, count)
        case REWARDS_COIN:		Stats_AddPlayerCoins(id, count)
        case REWARDS_SKIN:		Skins_GenerateContainer(id, abs(cid))
        
    }
}

public Rewards_getReward( id, const reward, const count, str[], len)
{
    switch (reward)
    {
        case REWARDS_NONE:   formatex(str, len, "%L", id, "CSRE_REWARDS_NONE" )
        case REWARDS_EXP:    formatex(str, len, "%L", id, "CSRE_REWARDS_EXP", count )
        case REWARDS_CASE:   formatex(str, len, "%L", id, "CSRE_REWARDS_CASE", count )
        case REWARDS_KEY:    formatex(str, len, "%L", id, "CSRE_REWARDS_KEY", count )
        case REWARDS_COIN:    formatex(str, len, "%L", id, "CSRE_REWARDS_COIN", count )
        case REWARDS_SKIN:    {
            new skin[36];

            switch (count) {
                case -3: formatex(skin, charsmax(skin), "\y%L", id, "CSRE_ITEM_LEGENDARY")
                case -2: formatex(skin, charsmax(skin), "\r%L", id, "CSRE_ITEM_RARE")
                case -1: formatex(skin, charsmax(skin), "\w%L", id, "CSRE_ITEM_NORMAL")

                default: {
                    new data[Items]
                    ArrayGetArray(g_Items, search_array(count), data)
                    skinClassStr(data, skin, charsmax(skin))
                }
            }

            formatex(str, len, "%L %s", id, "CSRE_REWARDS_SKIN", skin )
        }
    }
}

public Rewards_readConfig ( )
{
    new fileWishes[64]; getDirByType(DIR_CONFIG, fileWishes, charsmax(fileWishes), "Rewards.ini")

    if ( !file_exists(fileWishes) )
        return PrintMessage("[Rewards], wishes config file not found, check [%s]", fileWishes)

    new f = fopen( fileWishes, "r");

    new filedata[256], bool:index = false;
    new data[RewardsArray], lReward[12], lCount[12];
    
    new prefix[2];
    while (!feof(f))
    {
        fgets(f, filedata, charsmax(filedata));
        trim(filedata);

        if(!filedata[0] || filedata[0] == '#')  continue;
        
        if(equali(filedata, REWARDS_INI_TAG, strlen(REWARDS_INI_TAG)))
        {
            index = !index;
            continue;
        }
        
        if ( !index || filedata[0] != '"') continue

        parse(filedata, lReward, charsmax(lReward), lCount, charsmax(lCount));
        for( new i = REWARDS_NONE; i < sizeof(_szRewards_reward); i++) if (equali(lReward, _szRewards_reward[i]) )    data[RA_TYPE] = i;

        prefix[0] = lCount[0];
        if ( !is_str_num(prefix) ) replace(lCount, charsmax(lCount), prefix, "");

        switch (prefix[0]) {
            case 'l' : data[RA_COUNT] = 10000 + str_to_num(lCount);
            case 'r' : data[RA_COUNT] = 5000 + str_to_num(lCount);
            case 'n' : data[RA_COUNT] = 1000 + str_to_num(lCount);

            case 'w' : data[RA_COUNT] = -1;
            case 'e' : data[RA_COUNT] = -2;
            case 'y' : data[RA_COUNT] = -3;

            default : data[RA_COUNT] = str_to_num(lCount);
        }

        ArrayPushArray(g_rewards, data)
    }


    PrintMessage("Load %d Rewards", ArraySize(g_rewards))
    return fclose(f);
}


stock bool:Rewards_isEnabled() {
    static size = 0;
    if ( !size ) size = ArraySize(g_rewards)

    return size > 0;
}