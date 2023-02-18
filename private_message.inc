#if defined _private_message_included
	#endinput
#endif
#define _private_message_included

/**
 * Returns if chat blocked.
 *
 *
 * @return			true/false
 */
native bool:pm_is_chat_blocked();

/**
 * Returns if player blocked.
 *
 * @param blocker		Player who blocked
 * @param blocked		Blocked player
 *
 * @return			true/false
 */
native bool:pm_is_player_blocked(blocker, blocked);

/**
 * Set value for block/unblock chat.
 *
 * @param id		Player admin
 * @param value		Bool value
 *
 * @noreturn
 */
native pm_block_use(bool:value);

/**
 * Send a message from player to player.
 *
 * @param sender		Player sender
 * @param receiver		Player receiver
 * @param message		Message
 *
 * @noreturn
 */
native pm_send_message(sender, receiver, message[]);

/**
 * Called when sends a message.
 *
 * @param sender	Player sender
 * @param receiver	Player receiver
 * @param message	Message
 *
 * @return			PLUGIN_CONTINUE to let send a message
 *					PLUGIN_HANDLED or higher to prevent send a message
 */
forward pm_message_sent(sender, receiver, message[]);

/**
 * Called when a player blocks another player.
 *
 * @param blocker	Player blocker
 * @param blocked	Player blocked
 * @param block		True if blocked, otherwise false
 *
 *
 * @return			PLUGIN_CONTINUE to let block/unblock a player
 *					PLUGIN_HANDLED or higher to prevent block/unblock a player
 */
forward pm_player_blocked(blocker, blocked, bool:block);