#if defined _views_info_player_include
  #endinput
#endif

#define _views_info_player_include

#include <amxmodx>
#include <csrank>

#include <fakemeta>
#include <cstrike>

public fwdPlayerPreThink(id)
{
    if ( !isAlive[id] || id < 0 || id >= MaxPlayers)
        return ;
        
    new target, body;
    get_user_aiming(id, target, body, 9999);
		
    if( target > 0 && target < MaxPlayers && isAlive[target] )
	{
		new CsTeams:targetTeam = cs_get_user_team(target);
        #if !defined INFO_ENEMY
        new CsTeams:team = cs_get_user_team(id);
		if( targetTeam == team )
        #endif
		{	
            new sMessage[64];

            new level = csr_get_value(target, CSR_VALUE_LEVEL), exp = csr_get_value(target, CSR_VALUE_EXP),\
            medals = csr_get_value(target, CSR_VALUE_MEDALS);
            
            formatex(sMessage, 63, "Level %d - Exp %d | Medals %d", level, exp, medals);
            
            if( targetTeam == CS_TEAM_CT )      set_hudmessage(0, 63, 127, COORD, 0, 0.0, 0.1, 0.0, 0.0, 3);
			else if( targetTeam == CS_TEAM_T )  set_hudmessage(127, 0, 0, COORD, 0, 0.0, 0.1, 0.0, 0.0, 3);
            
            show_hudmessage(id, "%s", sMessage);
            
            new name[32];
            get_user_name(id, name, charsmax(name));

            //log_to_file(LOG_FILE, "Player '%s' see: %s", name, sMessage);
		}
	}
}