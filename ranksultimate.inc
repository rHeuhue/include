#if defined _ranksultimate_included
    #endinput
#endif

#define _ranksultimate_included

/**
 * Called when the client's level changes.
 *
 * @param index     Client index.
 * @param level     New level.
 * @param levelup   True if the client gained a level, false if he lost one.
 * @noreturn
 * 
 */
forward rsu_user_level_updated(index, level, bool:levelup)

/**
 * Called right after the client's XP amount changes.
 *
 * @param index     Client index.
 * @param xp        Amount of XP the client has after the change.
 * @param teamxp    True if Team XP, false otherwise.
 * @noreturn
 */
forward rsu_user_xp_updated(index, xp, bool:teamxp)

/**
 * Returns client's current XP.
 * 
 * @param index     Client index.
 * @return          Client's current XP.
 * 
 */
native rsu_get_user_xp(index)

/**
 * Returns client's next rank XP.
 * 
 * @param index     Client index.
 * @return          Client's next rank XP.
 * 
 */
native rsu_get_user_next_xp(index)

/**
 * Returns client's current level.
 * 
 * @param index     Client index.
 * @return          Client's current level.
 * 
 */
native rsu_get_user_level(index)

/**
 * Returns client's kills.
 * 
 * @param index     Client index.
 * @return          Client's kills.
 * 
 */
native rsu_get_user_kills(index)

/**
 * Returns client's deaths.
 * 
 * @param index     Client index.
 * @return          Client's deaths.
 * 
 */
native rsu_get_user_deaths(index)

/**
 * Returns client's headshots.
 * 
 * @param index     Client index.
 * @return          Client's headshots.
 * 
 */
native rsu_get_user_headshots(index)

/**
 * Returns client's assists.
 * 
 * @param index     Client index.
 * @return          Client's assists.
 * 
 */
native rsu_get_user_assists(index)

/**
 * Returns client's shots.
 * 
 * @param index     Client index.
 * @return          Client's shots.
 * 
 */
native rsu_get_user_shots(index)

/**
 * Returns client's hits.
 * 
 * @param index     Client index.
 * @return          Client's hits.
 * 
 */
native rsu_get_user_hits(index)

/**
 * Returns client's damage.
 * 
 * @param index     Client index.
 * @return          Client's damage.
 * 
 */
native rsu_get_user_damage(index)

/**
 * Returns client's MVP count.
 * 
 * @param index     Client index.
 * @return          Client's MVP count.
 * 
 */
native rsu_get_user_mvp(index)

/**
 * Returns client's rounds won.
 * 
 * @param index     Client index.
 * @return          Client's rounds won.
 * 
 */
native rsu_get_user_rounds_won(index)

 /**
 * Returns client's amount of bombs planted.
 * 
 * @param index     Client index.
 * @return          Client's bombs planted amount.
 * 
 */
native rsu_get_user_bombs_planted(index)

 /**
 * Returns client's amount of bombs exploded.
 * 
 * @param index     Client index.
 * @return          Client's bombs exploded amount.
 * 
 */
native rsu_get_user_bombs_exploded(index)

 /**
 * Returns client's amount of bombs defused.
 * 
 * @param index     Client index.
 * @return          Client's bombs defused amount.
 * 
 */
native rsu_get_user_bombs_defused(index)

/**
 * Returns client's total played time in seconds.
 * 
 * @param index     Client index.
 * @return          Client's played time in seconds.
 * 
 */
native rsu_get_user_played_time(index)

/**
 * Returns rank's name by a specific level.
 * 
 * @param level     Level number.
 * @param buffer    String buffer to store the name.
 * @param len       Maximum buffer lenght.
 * @noreturn
 * 
 */
native rsu_get_rank_by_level(level, buffer[], len)

/**
 * Returns client's current rank name.
 * 
 * @param index     Client index.
 * @param buffer    String buffer to store the name.
 * @param len       Maximum buffer lenght.
 * @noreturn
 * 
 */
native rsu_get_user_rank(index, buffer[], len)

/**
 * Returns client's current skill name.
 * 
 * @param index     Client index.
 * @param buffer    String buffer to store the name.
 * @param len       Maximum buffer lenght.
 * @noreturn
 * 
 */
native rsu_get_user_skill(index, buffer[], len)

/**
 * Returns the client's skill range.
 * 
 * @param index     Client's index.
 * @return          Client's skill range.
 * 
 */
native rsu_get_user_skill_range(index)

/**
 * Returns the client's server rank.
 * 
 * @param index     Client's index.
 * @return          Client's server rank.
 * 
 */
native rsu_get_user_server_rank(index)

/**
 * Returns the maximum amount of levels.
 * 
 * @return          Maximum amount of levels.
 * 
 */
native rsu_get_max_levels()

/**
 * Returns the maximum amount of server ranks.
 * 
 * @return          Maximum amount of server ranks.
 * 
 */
native rsu_get_max_server_ranks()

/**
 * Gives specific amount of XP to the client.
 * 
 * @param index     Client index.
 * @param amount    XP amount.
 * @return          Amount of XP.
 * 
 */
 native rsu_give_user_xp(index, amount = 0)

 /**
 * Gives specific amount of XP to the specific team.
 * 
 * @param team      0 - None, 1 - Terrorists, 2 - CTs, 3 - Spectators
 * @param amount    XP amount.
 * @return          Amount of XP.
 * 
 */
 native rsu_give_team_xp(team = 0, amount = 0)

/**
 * Checks if client's stats are loaded.
 * 
 * @param index     Client index.
 * @return          True if client's stats are loaded, false otherwise.
 * 
 */
 native rsu_is_level_loaded(index)

/**
 * Resets all stats from MySQL table.
 * 
 * @noreturn
 * 
 */
 native rsu_reset_stats()