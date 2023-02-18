#if defined _rank_system_huehue_included
	#endinput
#endif
#define _rank_system_huehue_included

/* Load custom module ?

#pragma reqlib LIBRARY_NAME
#if !defined AMXMODX_NOAUTOLOAD
	#pragma loadlib LIBRARY_NAME
#endif

*/


/**
 * Returns a player's current level.
 *
 * @param id		Player index.
 * @return			Internal level, or -1 if not yet connected.
 */
native get_user_level(id)

/**
 * Sets a player's new level.
 *
 * @param id		Player index.
 * @param iLevel 	A valid level number
 * @return			True on success, false otherwise.
 *
 * Example: set_user_level(id, get_user_level(id) + 1)
 */
native set_user_level(id, iLevel)

/**
 * Returns a player's current experience.
 *
 * @param id		Player index.
 * @return			Internal experience, or -1 if not yet connected.
 */
native get_user_exp(id)


/**
 * Sets a player's new experience amount.
 *
 * @param id		Player index.
 * @param iExp	 	A valid experience number
 * @return			True on success, false otherwise.
 *
 * Example: set_user_exp(id, get_user_exp(id) + 10)
 */
native set_user_exp(id, iExp)

/**
 * Returns a player's current rank.
 *
 * @param id		Player index.
 * @param szRank	String
 * @param iLen		String length
 * @return			Internal rank name, or nothing if not yet connected.
 *
 * Example: get_user_rank_name(id, szRank, charsmax(szRank))
 */
native get_user_rank_name(id, szRank[], iLen)

/**
 * Returns a player's next level needed experience.
 *
 * @param id		Player index.
 * @return			Internal next level needed experience, or 0 if max rank reached.
 */
native get_user_next_exp(id)

/**
 * Returns a player's next level needed experience.
 *
 * @param id		Player index.
 * @return			Internal next level, or 0 if max rank reached.
 */
native get_user_next_level(id)

/**
 * Returns a player's next level rank name.
 *
 * @param id		Player index.
 * @param szRank	String
 * @param iLen		String length
 * @return			Internal next level rank name, or 0 if max rank reached.
 */
native get_user_next_rank_name(id, szRank[], iLen)

/**
 * Returns a rank name by level.
 *
 * @param iLevel	Level number.
 * @param szRank	String
 * @param iLen		String length
 * @return			Internal rank name from level, or -1 if not yet connected.
 *
 * Example: get_rank_name_by_level(get_user_level(id))
 */
native get_rank_name_by_level(iLevel, szRank[], iLen)

/**
 * Returns a total ranks system have.
 *
 * @No params
 * @return			Internal total rank value
 */
native get_total_ranks()

/**
 * Returns a player's check if ranks increased or decreased.
 *
 * @param id		Player index.
 * @param iType		0 for decreasing, 1 for increasing value
 * @return			Internal check if ranks increased or decreased.
 */
native update_rank_info(id, iType)

/**
 * Returns a rank experience by level check.
 *
 * @param iLevel	Level number for rank
 * @return			Needed experience for rank up.
 */
native get_rank_exp(iLevel)

/**
 * Sets a player's new rank without checks and displaying in chat achieve/lost message.
 *
 * @param id		Player index.
 * @param iLevel 	A valid level number
 * @return			True on success, false otherwise.
 *
 * Example: set_user_rank(id, 10)
 * It will set to player the rank #10 from your Ranks.ini file!
 */
native set_user_rank(id, iRankNum)

/**
 * Gets plugin prefix from file.
 *
 * @param szPrefix	String
 * @param iLen		String length
 * @return			Plugin prefix from file
 *
 * Example: new szPrefix[32]
 *			get_plugin_prefix(szPrefix, charsmax(szPrefix))
 *			client_print(iIndex, print_chat, "Your plugin prefix is %s", szPrefix)
 */
native get_plugin_prefix(szPrefix[], iLen)

/**
 * Gets plugin vip flag from file.
 *
 * @param szFlag	String
 * @param iLen		String length
 * @return			Vip flag from file
 *
 * Example: new szFlag[32]
 *			get_vip_flag(szFlag, charsmax(szFlag))
 *			client_print(iIndex, print_chat, "Vip flag is %s", szFlag)
 * Example2:
 *			if (get_user_flags(iIndex) & read_flags(szFlag))
 *				// Your code here..
 */
native get_vip_flag(szFlag[], iLen)

/*
 * Gets hud colors from file.
 * @param szColors	String
 * @param iLen		String Length
 *
 * Example: new szColors[12], szRed[6], szGreen[6], szBlue[6], iRed, iGreen, iBlue
 *			get_hud_colors(szColors, charsmax(szColors))
 *			parse(szColors, szRed, charsmax(szRed), szGreen, charsmax(szGreen), szBlue, charsmax(szBlue))
 *			iRed = str_to_num(szRed)
 *			iGreen = str_to_num(szGreen)
 *			iBlue = str_to_num(szBlue)
 *
 */
native get_hud_colors(szColors[], iLen)

/*
 * Returns hud position X from file.
 * @No params
 * @return			Float X position
 */
native Float:get_hud_position_x()

/*
 * Returns hud position Y from file.
 * @No params
 * @return			Float Y position
 */
native Float:get_hud_position_y()

/*
 * Returns hud effect from file.
 * @No params
 * @return			Internal Effect [ 0 = Nothing | 1 = Blink ]
 */
native get_hud_effect()