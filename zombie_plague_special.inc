#if defined _zombie_special_new_included
  #endinput
#endif
#define _zombie_special_new_included

#define ZPS_INC_VERSION 40 // Include Version

/* Teams for zp_register_extra_item() */
#define ZP_TEAM_ZOMBIE (1<<0)
#define ZP_TEAM_HUMAN (1<<1)
#define ZP_TEAM_NEMESIS (1<<2)
#define ZP_TEAM_SURVIVOR (1<<3)
#define ZP_TEAM_SNIPER (1<<4)
#define ZP_TEAM_ASSASSIN (1<<5)
#define ZP_TEAM_BERSERKER (1<<6)
#define ZP_TEAM_PREDATOR (1<<7)
#define ZP_TEAM_WESKER = (1<<8)
#define ZP_TEAM_BOMBARDIER = (1<<9)
#define ZP_TEAM_SPY = (1<<10)
#define ZP_TEAM_DRAGON = (1<<11)

/* Death Match modes for zp_register_game_mode */
enum
{
	ZP_DM_NONE = 0,	// Disable death match during the custom mode round
	ZP_DM_HUMAN, 	// Respawn as human only
	ZP_DM_ZOMBIE, 	// Respawn as zombie only
	ZP_DM_RANDOM,	// Respawn randomly as humans or zombies
	ZP_DM_BALANCE	// Respawn as humans or zombies to keep both team balanced
}

enum 
{ 
	EXTRA_NVISION = 0, 
	EXTRA_ANTIDOTE, 
	EXTRA_MADNESS, 
	EXTRA_INFBOMB, 
	EXTRA_WEAPONS_STARTID 
}

enum { 
	ZOMBIE = 0,
	NEMESIS,
	ASSASSIN, 
	PREDATOR, 
	BOMBARDIER,
	DRAGON
}
enum { 
	HUMAN = 0,
	SURVIVOR,
	SNIPER,
	BERSERKER, 
	WESKER, 
	SPY
}

/* Game modes for zp_round_started() */
enum
{
	MODE_NONE = 0,
	MODE_INFECTION,
	MODE_NEMESIS,
	MODE_ASSASSIN,
	MODE_PREDATOR,
	MODE_BOMBARDIER,
	MODE_DRAGON,
	MODE_SURVIVOR,
	MODE_SNIPER,
	MODE_BERSERKER,
	MODE_WESKER,
	MODE_SPY,
	MODE_SWARM,
	MODE_MULTI,
	MODE_PLAGUE,
	MODE_LNJ
}

/* Winner teams for zp_round_ended() */
enum
{
	WIN_NO_ONE = 0,
	WIN_ZOMBIES,
	WIN_HUMANS
}

/* Use For zp_set_user_frozen and zp_set_user_burn natives */
enum {
	UNSET = 0,
	SET,
	SET_WITHOUT_IMMUNIT
}

/* Use For zp_get_special_count and zp_make_user_special native*/
enum {
	GET_HUMAN = 0,
	GET_ZOMBIE
}

/* Custom forward return values */
#define ZP_PLUGIN_HANDLED 97
#define ZP_PLUGIN_SUPERCEDE 98

/**
 * Returns whether a player is a zombie.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_zombie(id)

/**
 * Returns whether a player is a nemesis.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_nemesis(id)

/**
 * Returns whether a player is a survivor.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_survivor(id)

/**
 * Returns whether a player is the first zombie.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_first_zombie(id)

/**
 * Returns whether a player is the last zombie.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_last_zombie(id)

/**
 * Returns whether a player is the last human.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_last_human(id)

/**
 * Returns a player's current zombie class ID.
 *
 * @param id		Player index.
 * @return		Internal zombie class ID, or -1 if not yet chosen.
 */
native zp_get_user_zombie_class(id)

/**
 * Returns a player's next zombie class ID (for the next infection).
 *
 * @param id		Player index.
 * @return		Internal zombie class ID, or -1 if not yet chosen.
 */
native zp_get_user_next_class(id)

/**
 * Sets a player's next zombie class ID (for the next infection).
 *
 * @param id		Player index.
 * @param classid	A valid zombie class ID.
 * @return		True on success, false otherwise.
 */
native zp_set_user_zombie_class(id, classid)

/**
 * Returns a player's ammo pack count.
 *
 * @param id		Player index.
 * @return		Number of ammo packs owned.
 */
native zp_get_user_ammo_packs(id)

/**
 * Sets a player's ammo pack count.
 *
 * @param id		Player index.
 * @param amount	New quantity of ammo packs owned.
 */
native zp_set_user_ammo_packs(id, amount)

/**
 * Returns the default maximum health of a zombie.
 *
 * Note: Takes into account first zombie's HP multiplier.
 *
 * @param id		Player index.
 * @return		Maximum amount of health points, or -1 if not a normal zombie.
 */
native zp_get_zombie_maxhealth(id)

/**
 * Returns a player's custom flashlight batteries charge.
 *
 * @param id		Player index.
 * @return		Charge percent (0 to 100).
 */
native zp_get_user_batteries(id)

/**
 * Sets a player's custom flashlight batteries charge.
 *
 * @param id		Player index.
 * @param value		New charge percent (0 to 100).
 */
native zp_set_user_batteries(id, charge)

/**
 * Returns whether a player has night vision.
 *
 * @param id		Player index.
 * @return		True if it has, false otherwise.
 */
native zp_get_user_nightvision(id)

/**
 * Sets whether a player has night vision.
 *
 * @param id		Player index.
 * @param set		True to give, false for removing it.
 */
native zp_set_user_nightvision(id, set)

/**
 * Forces a player to become a zombie.
 *
 * Note: Unavailable for last human/survivor/sniper/berserker.
 *
 * @param id		Player index to be infected.
 * @param infector	Player index who infected him (optional).
 * @param silent	If set, there will be no HUD messages or infection sounds.
 * @param rewards	Whether to show DeathMsg and reward frags, hp, and ammo packs to infector.
 * @return		True on success, false otherwise.
 */
native zp_infect_user(id, infector = 0, silent = 0, rewards = 0)

/**
 * Forces a player to become a human.
 *
 * Note: Unavailable for last zombie/nemesis.
 *
 * @param id		Player index to be cured.
 * @param silent	If set, there will be no HUD messages or antidote sounds.
 * @return		True on success, false otherwise.
 */
native zp_disinfect_user(id, silent = 0)

/**
 * Forces a player to become a nemesis.
 *
 * Note: Unavailable for last human/survivor/sniper/berserker.
 *
 * @param id		Player index to turn into nemesis.
 * @return		True on success, false otherwise.
 */
native zp_make_user_nemesis(id)

/**
 * Forces a player to become a survivor.
 *
 * Note: Unavailable for last zombie/nemesis.
 *
 * @param id		Player index to turn into survivor.
 * @return		True on success, false otherwise.
 */
native zp_make_user_survivor(id)

/**
 * Respawns a player into a specific team.
 *
 * @param id		Player index to be respawned.
 * @param team		Team to respawn the player into (ZP_TEAM_ZOMBIE or ZP_TEAM_HUMAN).
 * @return		True on success, false otherwise.
 */
native zp_respawn_user(id, team)

/**
 * Forces a player to buy an extra item.
 *
 * @param id		Player index.
 * @param itemid	A valid extra item ID.
 * @param ignorecost	If set, item's cost won't be deduced from player.
 * @return		True on success, false otherwise.
 */
native zp_force_buy_extra_item(id, itemid, ignorecost = 0)

/**
 * Returns whether a player is a sniper.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_sniper(id)

/**
 * Forces a player to become a sniper.
 *
 * Note: Unavailable for last zombie/nemesis/assassin.
 *
 * @param id		Player index to turn into sniper.
 * @return		True on success, false otherwise.
 */
native zp_make_user_sniper(id)

/**
 * Returns whether a player is an assassin.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_assassin(id)


/**
 * Returns whether a player is an predator.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_predator(id)

/**
 * Returns whether a player is an bombardier.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_bombardier(id)

/**
 * Returns whether a player is an dragon.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_dragon(id)

/**
 * Forces a player to become a assassin.
 *
 * Note: Unavailable for last human/survivor/sniper.
 *
 * @param id		Player index to turn into assassin.
 * @return		True on success, false otherwise.
 */
native zp_make_user_assassin(id)

/**
 * Forces a player to become a predator.
 *
 * Note: Unavailable for last human/survivor/sniper.
 *
 * @param id		Player index to turn into predator.
 * @return		True on success, false otherwise.
 */
native zp_make_user_predator(id)

/**
 * Forces a player to become a bombardier.
 *
 * Note: Unavailable for last human/survivor/sniper.
 *
 * @param id		Player index to turn into bombardier.
 * @return		True on success, false otherwise.
 */
native zp_make_user_bombardier(id)

/**
 * Forces a player to become a dragon.
 *
 * Note: Unavailable for last human/survivor/sniper.
 *
 * @param id		Player index to turn into dragon.
 * @return		True on success, false otherwise.
 */
native zp_make_user_dragon(id)

/**
 * Returns whether a player is a sniper.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_berserker(id)

/**
 * Forces a player to become a berserker.
 *
 * Note: Unavailable for last zombie/nemesis/assassin.
 *
 * @param id		Player index to turn into berserker.
 * @return		True on success, false otherwise.
 */
native zp_make_user_berserker(id)

/**
 * Returns whether a player is a sniper.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_wesker(id)

/**
 * Forces a player to become a wesker.
 *
 * Note: Unavailable for last zombie/nemesis/assassin.
 *
 * @param id		Player index to turn into wesker.
 * @return		True on success, false otherwise.
 */
native zp_make_user_wesker(id)

/**
 * Returns whether a player is a spy
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_spy(id)

/**
 * Forces a player to become a spy.
 *
 * Note: Unavailable for last zombie/nemesis/assassin.
 *
 * @param id		Player index to turn into spy.
 * @return		True on success, false otherwise.
 */
native zp_make_user_spy(id)

/**
 * Returns whether the ZP round has started, i.e. first zombie
 * has been chosen or a game mode has begun.
 *
 * @return		0 - Round not started
 *			1 - Round started
 *			2 - Round starting
 */
native zp_has_round_started()

/**
 * Returns whether the current round is a nemesis round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_nemesis_round()

/**
 * Returns whether the current round is a survivor round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_survivor_round()

/**
 * Returns whether the current round is a swarm round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_swarm_round()

/**
 * Returns whether the current round is a plague round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_plague_round()

/**
 * Returns whether the current round is a Armageddon round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_lnj_round()

/**
 * Returns number of alive zombies.
 *
 * @return		Zombie count.
 */
native zp_get_zombie_count()

/**
 * Returns number of alive humans.
 *
 * @return		Human count.
 */
native zp_get_human_count()

/**
 * Returns number of alive nemesis.
 *
 * @return		Nemesis count.
 */
native zp_get_nemesis_count()

/**
 * Returns number of alive survivors.
 *
 * @return		Survivor count.
 */
native zp_get_survivor_count()

/**
 * Returns whether the current round is a sniper round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_sniper_round()

/**
 * Returns whether the current round is a assassin round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_assassin_round()

/**
 * Returns whether the current round is a predator round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_predator_round()

/**
 * Returns whether the current round is a bombardier round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_bombardier_round()

/**
 * Returns whether the current round is a dragon round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_dragon_round()

/**
 * Returns whether the current round is a berserker round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_berserker_round()

/**
 * Returns whether the current round is a wesker round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_wesker_round()

/**
 * Returns whether the current round is a spy round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_spy_round()

/**
 * Returns number of alive snipers.
 *
 * @return		Sniper count.
 */
native zp_get_sniper_count()

/**
 * Returns number of alive assassins.
 *
 * @return		Assassin count.
 */
native zp_get_assassin_count()

/**
 * Returns number of alive predators.
 *
 * @return		predator count.
 */
native zp_get_predator_count()

/**
 * Returns number of alive bombardiers.
 *
 * @return		bombardier count.
 */
native zp_get_bombardier_count()

/**
 * Returns number of alive dragons.
 *
 * @return		dragon count.
 */
native zp_get_dragon_count()


/**
 * Returns number of alive berserkers.
 *
 * @return		Berserker count.
 */
native zp_get_berserker_count()

/**
 * Returns number of alive weskers.
 *
 * @return		wesker count.
 */
native zp_get_wesker_count()

/**
 * Returns number of alive spys.
 *
 * @return		spy count.
 */
native zp_get_spy_count()


/**
 * Returns the current game mode ID
 * 
 * Note: For default game modes you can use, for eg. MODE_SWARM,
 * to check if the current round is swarm mode.
 * 
 * Note: For custom game modes you must have the custom game
 * mode ID to detect it
 * 
 * @return		Current game mode ID
 */
native zp_get_current_mode()

native zp_get_last_mode() // Ver o ultimo mod jogado

/**
 * Returns an extra item's ID.
 *
 * @param name		Item name to look for.
 * @return		Internal extra item ID, or -1 if not found.
 */
native zp_get_extra_item_id(const name[])

/**
 * Returns a zombie class' ID.
 *
 * @param name		Class name to look for.
 * @return		Internal zombie class ID, or -1 if not found.
 */
native zp_get_zombie_class_id(const name[])

/**
 * Registers a custom game mode which will be added to the admin menu of ZP
 * 
 * Note: The returned game mode ID can later be used to detect the game mode
 * which is called in zp_round_started_pre. There you can start the game mode
 * externally by using this game mode ID.
 * 
 * @param name 		The game modes name which will also be used by other plugins
 * 			to identify this game mode
 * @param flags		Access flags required by the admins to start this game
 * 			mode via the admin menu.
 * @param chance	Chance level of this game mode. (1 in X) The higher the value
 * 			the lesser the chance that this game mode will be called
 * @param allow		Whether to permit infection or not after a zombie's attack
 * @param dm_mode	Death match mode during this game. Use ZP_DM_NONE to disable
 * 			respawning during this game mode
 * @return		An internal game mode ID or -1 on failure
 */
native zp_register_game_mode( const name[], flags, chance, allow, dm_mode)

/**
 * Registers a custom item which will be added to the extra items menu of ZP.
 *
 * Note: The returned extra item ID can be later used to catch item
 * purchase events for the zp_extra_item_selected() forward.
 *
 * Note: ZP_TEAM_NEMESIS, ZP_TEAM_SURVIVOR, ZP_TEAM_ASSASSIN, ZP_TEAM_SNIPER and ZP_TEAM_BERSERKER
 * can be used to make an item available to Nemesis,
 * Survivors, Assassins, Snipers and Berserkers.
 *
 * @param name		Caption to display on the menu.
 * @param cost		Ammo packs to be deducted on purchase.
 * @param teams		Bitsum of teams it should be available for.
 * @return		An internal extra item ID, or -1 on failure.
 */
native zp_register_extra_item(const name[], cost, teams)

// New Natives
native zp_extra_item_textadd(const text[])  // Add Text On Extra Item (Like ZP 5.0)
native zp_zombie_class_textadd(const text[]) // Add Text On Zombie Class (Like ZP 5.0)
native zp_get_user_infectnade(id) // Get User Infect bomb
native zp_set_user_infectnade(id, set) // Give/Remove User Infect bomb
native zp_get_user_frozen(id) // Get User Frozen
native zp_set_user_frozen(id, set) // Set User Burning
native zp_get_user_burn(id) // Get User Burning
native zp_set_user_burn(id, set) // Set User Burning
native zp_get_user_madness(id) // Get user Madness
native zp_set_user_madness(id, set) // Set user Madness
native zp_get_human_special_class(id) // Get User Survivor/Sniper/Berserker/Etc
native zp_get_zombie_special_class(id) // Get User Nemesis/Assassin/Predator/Etc.
native zp_set_user_rendering(id, fx, r, g, b, render, amount) // Set User Render with handle models on separate ent compat
native zp_reset_user_rendering(id) // Reset User Render
native zp_get_extra_item_cost(itemid) // Get Item Cost
native zp_get_extra_item_name(itemid, itemname[], len) // Get Item Name
native zp_set_user_maxspeed(id, Float:Speed) // Change user Current maxspeed
native Float:zp_get_user_maxspeed(id) // Get user Maxspeed
native zp_reset_user_maxspeed(id) // Reset user Maxspeed
native zp_set_extra_damage(victim, attacker, damage, weaponDescription[]) // Set User Extra Damage (Like Superhero Mod)
native zp_get_zombie_class_info(class, info[], len) // Get Class Info
native zp_get_zombie_class_name(class, name[], len) // Get Class Name
native zp_set_extra_item_cost(itemid, cost) // Change Extra Item Cost
native zp_set_extra_item_name(itemid, const newname[])	// Change Extra Item Name
native zp_set_extra_item_team(itemid, team) // Change Extra Item Team
native zp_get_extra_item_realname(itemid, realname[], len)
native zp_has_round_ended() // Get Round Ended
native zp_get_current_mode_name(name[], len) // Get Current mode Name
native zp_override_user_model(id, const newmodel[], modelindex = 0)

// New Natives (3.0 Version or higher Available)
native zp_register_zombie_special(const name[], const model[], const knifemodel[], const pain_sound[], hp, speed, Float:gravity, flags, Float:knockback, aura_radius, glow, r, g, b) // Register Human Special
native zp_make_user_special(id, spid, zombie) // Make user a Special Class
native zp_set_custom_game_mod(gameid) // Forces Start Custom Mod
native zp_get_special_count(zombie, specialid) // Get Special id Cound
native zp_register_human_special(const name[], const model[], hp, speed, Float:gravity, flags, clip_type, aura_radius, glow, r, g, b) // Register Human Special
native zp_reset_player_model(id) // Reset Player Model

// New Natives (3.1 Version or higher Available)
native zp_special_class_name(id, name[], len) // Get user Special Class Real Name

// New Natives (3.2 Version or higher Available)
native zp_get_zombie_class_realname(id, realname[], len) // Get user Zombie Class Real Name
native zp_get_special_class_id(is_zombie, name[]) // Get Special Class ID

// New Natives (3.4 Version or Higher Available)
native zp_get_custom_special_count(is_zombie) // Get Registred Custom Special Class Count
native zp_get_gamemodes_count() // Get Registred Custom Game modes count
native zp_get_zclass_count() // Get Registred Zombie Class Count
native zp_get_extra_item_count() // Get Registred Extra Item Count
native zp_get_gamemode_id(name[]) // Get Game mode index by name

// New Natives (3.5 Version or Higher Available)
native zp_is_escape_map() // Get Current Map is Escape Map
native zp_do_random_spawn(id) // Teleport User to Spawn

/**
 * Registers a custom class which will be added to the zombie classes menu of ZP.
 *
 * Note: The returned zombie class ID can be later used to identify
 * the class when calling the zp_get_user_zombie_class() natives.
 *
 * @param name		Caption to display on the menu.
 * @param info		Brief description of the class.
 * @param model		Player model to be used.
 * @param clawmodel	Claws model to be used.
 * @param hp		Initial health points.
 * @param speed		Maximum speed.
 * @param gravity	Gravity multiplier.
 * @param knockback	Knockback multiplier.
 * @return		An internal zombie class ID, or -1 on failure.
 */
native zp_register_zombie_class(const name[], const info[], const model[], const clawmodel[], hp, speed, Float:gravity, Float:knockback)

/**
 * Called when the ZP round starts, i.e. first zombie
 * is chosen or a game mode begins.
 *
 * @param gamemode	Mode which has started.
 * @param id		Affected player's index (if applicable).
 */
forward zp_round_started(gamemode, id)

/**
 * Called before the ZP round starts. This is only 
 * called for custom game modes.
 * 
 * Note: The custom game mode id can be used to start
 * the game mode externally
 * 
 * Note: returning ZP_PLUGIN_HANDLED will cause the
 * game mode to be blocked and other game modes will
 * be given a chance.
 * 
 * @param gameid	Custom mode id which is called
 */
forward zp_round_started_pre(gameid)

/**
 * Called when the round ends.
 *
 * @param winteam	Team which has won the round.
 */
forward zp_round_ended(winteam)

/**
 * Called when a player gets infected.
 *
 * @param id		Player index who was infected.
 * @param infector	Player index who infected him (if applicable).
 * @param nemesis	Whether the player was turned into a nemesis.
 */
forward zp_user_infected_pre(id, infector, classid)
forward zp_user_infected_post(id, infector, classid)

/**
 * Called when a player turns back to human.
 *
 * @param id		Player index who was cured.
 * @param survivor	Whether the player was turned into a survivor.
 */
forward zp_user_humanized_pre(id, classid)
forward zp_user_humanized_post(id, classid)

/**
 * Called on a player infect/cure attempt. You can use this to block
 * an infection/humanization by returning ZP_PLUGIN_HANDLED in your plugin.
 *
 * Note: Right now this is only available after the ZP round starts, since some
 * situations (like blocking a first zombie's infection) are not yet handled.
 */
forward zp_user_infect_attempt(id, infector, classid)
forward zp_user_humanize_attempt(id, classid)

/**
 * Called when an admin selects a custom game mode from the ZP admin menu.
 *
 * Note: You should trigger the custom game mode here with out any checks
 *
 * @param gameid	Internal custom game mode ID
 * @param id		Player index who selected the game mode
 */
forward zp_game_mode_selected(gameid, id)

/**
 * Called when a player spawns. This is also called for CZ bots 
 * which are spawning
 *
 * Note: You should use this, instead of other spawn forwards,
 * when you want to change some one's class after spawning.
 * 
 * Note: If you have used this forward then you must return 
 * ZP_PLUGIN_HANDLED to inform the main plugin that you have used
 * this forward
 *
 * @param id		Player index who has spawned
 * @param resp_zombie	This is passed by the main plugin as 1 if
 * 			the player needs to be spawned as a zombie
 * 			otherwise it is passed as zero
 */
forward zp_player_spawn_post(id, resp_zombie)

/**
 * Called when a player buys an extra item from the ZP menu.
 *
 * Note: You can now return ZP_PLUGIN_HANDLED in your plugin to block
 * the purchase and the player will be automatically refunded.
 *
 * @param id		Player index of purchaser.
 * @param itemid	Internal extra item ID.
 */
forward zp_extra_item_selected(id, itemid)

// New Forwards
// Exec When Open the Extra Itens menu
// Use the ZP_PLUGIN_HANDLED for block option (Like ZP 5.0)
// Use the ZP_PLUGIN_SUPERCEDE for block showing item in menu
forward zp_extra_item_selected_pre(id, itemid)

// Use the ZP_PLUGIN_HANDLED for block user frozing
forward zp_user_frozen_pre(id) 

forward zp_user_frozen_post(id)

// Use the ZP_PLUGIN_HANDLED for block user burning
forward zp_user_burn_pre(id)

forward zp_user_burn_post(id)

/**
 * Called when a player gets unfrozen (frostnades).
 *
 * @param id		Player index.
 */
forward zp_user_unfrozen(id)

/**
 * Called when a player becomes the last zombie.
 *
 * Note: This is called for the first zombie too.
 *
 * @param id		Player index.
 */
forward zp_user_last_zombie(id)

/**
 * Called when a player becomes the last human.
 *
 * @param id		Player index.
 */
forward zp_user_last_human(id)

// Exec when open Zombie Classes Choose menu
// Use the ZP_PLUGIN_HANDLED for block option (Like ZP 5.0)
// Use the ZP_PLUGIN_SUPERCEDE for block showing class in menu
forward zp_zombie_class_choosed_pre(id, classid)
 
// Exec when the user choose the class
forward zp_zombie_class_choosed_post(id, classid)

// New Forwards (4.0 or Higher)
/*
	Execute when player reset render
	Use ZP_PLUGIN_SUPERCEDE for block it
*/
forward zp_user_rendering_reset_pre(id)

// Execute after player reset glow
forward zp_user_rendering_reset_post(id) 

/*
	Execute when player change the model
	Use ZP_PLUGIN_SUPERCEDE for block it
*/
forward zp_user_model_change_pre(id, model[])

// Execute after player change model
forward zp_user_model_change_post(id, model[]) 

/*
	Execute before admin make a player to special class
	Use ZP_PLUGIN_HANDLED for block it
*/
forward zp_human_special_choosed_pre(id, specialid)
forward zp_zombie_special_choosed_pre(id, specialid)

// Execute after admin make a player to special class
forward zp_human_special_choosed_post(id, specialid)
forward zp_zombie_special_choosed_post(id, specialid)

/*
	Execute before admin start a mode
	Use ZP_PLUGIN_HANDLED for block it
*/
forward zp_game_mode_selected_pre(id, gamemode)

/**
 * @deprecated - Do not use!
 * For backwards compatibility only.
 */
#define ZP_TEAM_ANY 0

stock zp_get_alive_players()
{
	static i_alive, id
	i_alive = 0
	
	for (id = 1; id <= get_maxplayers(); id++)
	{
		if(is_user_alive(id))
			i_alive++
	}
	return i_alive;
}
