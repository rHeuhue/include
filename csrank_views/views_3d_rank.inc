#if defined _views_rank_include
  #endinput
#endif

#define _views_rank_include

#include <amxmodx>
#include <csrank>

#include < fakemeta >


#define foreach for(new id = 1; id<MaxPlayers; id++) \
					if (is_user_connected(id))

rank_precache()
{
    precache_model ( gsz_RankModel )
}

rank_put_in ( const index )
{
    create_rank_entity ( index )
}

rank_disc( const index )
{
    if ( gi_PlayerRank [ index ] > 0 )
        engfunc ( EngFunc_RemoveEntity, gi_PlayerRank [ index ] )
        
    gi_PlayerRank [ index ] = 0
}
#if DISPLAY_TYPE > 0
public Round_event()
{
	foreach
	{
		hide_rank_entity( id, true);
	}

	set_task( DISPLAY_TIME, "HideAllRanks", 3331)
}
public HideAllRanks()
{
	foreach
	{
		hide_rank_entity( id, false);
	}
}
#endif
stock create_rank_entity ( index )
{
    gi_PlayerRank [ index ] = engfunc ( EngFunc_CreateNamedEntity, engfunc ( EngFunc_AllocString, "info_target" ) )
	
    set_pev ( gi_PlayerRank [ index ], pev_movetype, MOVETYPE_FOLLOW )
    set_pev ( gi_PlayerRank [ index ], pev_aiment, index )
    set_pev ( gi_PlayerRank [ index ], pev_rendermode, kRenderNormal )
    set_pev ( gi_PlayerRank [ index ], pev_renderfx, kRenderFxGlowShell )
    set_pev ( gi_PlayerRank [ index ], pev_renderamt, 5.0 )
	
    engfunc ( EngFunc_SetModel, gi_PlayerRank [ index ], gsz_RankModel )
	
	new name[32];
	get_user_name(index, name, 31);

	//log_to_file(LOG_FILE, "Player '%s' take entity %d", name, gi_PlayerRank[index])
	#if DISPLAY_TYPE > 0
    // Скрываем
	hide_rank_entity( index, false);
	#endif
}

stock hide_rank_entity( id, bool:visible = false )
{
	// Модели нету
	if ( ! pev_valid(gi_PlayerRank [ id ]) ) return;

	new _pw = pev( gi_PlayerRank [ id ] , pev_effects);
	new hide= _pw & EF_NODRAW;

	// Уже скрыта или отрисована
	if ( (hide && !visible) || (!hide && visible) ) return;

	if ( !hide && !visible )
	{
		new name[32];
		get_user_name(id, name, 31);

		//log_to_file(LOG_FILE, "Hide rank for player '%s'", name)
		set_pev ( gi_PlayerRank [ id ], pev_effects,  _pw | EF_NODRAW )
	}
		

	if ( hide && visible )
	{
		new name[32];
		get_user_name(id, name, 31);

		//log_to_file(LOG_FILE, "Show rank for player '%s'", name)
		set_pev ( gi_PlayerRank [ id ], pev_effects,  _pw & ~EF_NODRAW )
	}
		
}
public check_rank ( index )
{
	new PlayerRank = get_player_rank ( index )
	
	new name[32];
	get_user_name(index, name, 31);

	//log_to_file(LOG_FILE, "Player Rank for '%s' is %d", name, PlayerRank);

	set_pev ( gi_PlayerRank [ index ], pev_body, PlayerRank )
	
	switch ( PlayerRank )
	{
		case 1, 2, 3:
		{
			set_pev ( gi_PlayerRank [ index ], pev_rendercolor, { 255.0, 255.0, 255.0 } )
		}
		
		default:
		{
			set_pev ( gi_PlayerRank [ index ], pev_rendercolor, { 255.0, 255.0, 0.0 } )
		}
	}
}

stock get_player_rank ( id )
{
	
	new PlayerFrags = csr_get_value ( id, CSR_VALUE_MEDALS );

	switch ( PlayerFrags )
	{
		case RANK_MEDAL_1:	return 1
		case RANK_MEDAL_2:	return 2
		case RANK_MEDAL_3:	return 3
		case RANK_MEDAL_4:	return 4
		case RANK_MEDAL_5:	return 5
		case RANK_MEDAL_6:	return 6
		case RANK_MEDAL_7:	return 7
		case RANK_MEDAL_8:	return 8
		case RANK_MEDAL_9:	return 9
		
		default:
		{
			return 10
		}
	}
	
	return 0
}