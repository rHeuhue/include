#if defined _hdr_core_included
	#endinput
#endif
#define _hdr_core_included


/**
 * Get player index of current Activator.
 * 
 * @return					Activator index.
 */
native hdr_get_activator()

/**
 * Get player index of who will became activator in new round.
 * 
 * @return					Activator index.
 */
native hdr_get_next_activator()

/**
 * Set player who will became activator in new round.
 * 
 * @param id				Next activator index.
 */
native hdr_set_next_activator(id)

/**
 * Forward which called when chosen new activator(new round or disconnect).
 * 
 * @param id				Activator index.
 */
forward HDR_On_New_Activator(id)

/**
 * Forward which called when activator wins.
 * 
 * @param id				Activator index.
 *
 * NOTE: Return everyone of Activators id
 */
forward HDR_On_Activator_Win(id)

/**
 * Forward which called when runners win.
 * 
 * @param id				Runners index.
 *
 * NOTE: Return everyone of Runners id
 */
forward HDR_On_Runners_Win(id)

/**
 * Forward which called when new round begins.
 * 
 */
forward HDR_On_Round_Started()

/**
 * Forward which called when round ends.
 * 
 */
forward HDR_On_Round_End()

/**
 * Forward which called when runner/activator spawns.
 * 
 * @param id				Player index.
 */
forward HDR_On_Player_Spawn(id)