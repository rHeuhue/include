#if defined _jailbreak_included
	#endinput
#endif

#if !defined _jailbreak_const_included
	#include <jailbreak_const>
#endif

#define _jailbreak_included


/* From LastRequest */

//Returns current Last request
native LastRequest:jb_get_lastrequest();

//Returns Last request Guard/Prisoner player
native jb_get_lrplayer(LastRequestPlayer:player);


/* From SpecialDays */

//Returns current special day
native Days:jb_get_specialday();

//Gets the name of the current special day
native jb_get_specialday_name(destination[], len);

//Returns whether user is president or not
native bool:jb_specialday_is_president(id);

//Returns whether user can pick weapons within special days checks
native bool:jb_specialday_canpickweapons(id);

//Forward called before day start
forward jb_specialday_started_pre(Days:iDay);

//Forward called after day start
forward jb_specialday_started_post(Days:iDay);

//Forward called after day end
forward jb_specialday_end();

/* From JailBreak Simon */

//Returns SIMON player index
native jb_get_simonindex();

//Returns SIMON's last said message
native jb_get_simon_last_cmd(destination[], len);

//Returns whether user is SIMON or not
native jb_is_user_simon(id);

/* From JailBreak Main */

//Returns the number of round currently playing
native jb_get_day();

//Returns the current day of week
native jb_get_dayofweek();


/* From JailBreak Models */

//Resets user model using jailbreak models
native jb_reset_model(id);

/* From JailBreak Cells */

//Checks whether a button is cell opening or not
native bool:jb_is_cellbutton(ent);

//Opens cells
native jb_open_cells();

/* From JailBreak Freeday */

//Returns whether a user has freeday or not
native bool:jb_is_user_freeday(id);

/* From JailBreak Shop Main */

// Items should be registred only during this forward
forward jb_register_items();

// Registers new item
//
// @param name[] - Item name to be displayed in the menu
// @param price - Item price
//
// @return item id
native jb_register_shopitem(name[], price);

// Registers new item
//
// @param name[] - Item name to be displayed in the menu
// @param price - Item price
//
// @return item id
native jb_register_vshopitem(name[], price);

//Returns player's points
native jb_get_userpoints(id);

//Sets player's VIP points
native jb_set_userpoints(id, points);

//Returns player's VIP points
native jb_get_vuserpoints(id);

//Sets player's points
native jb_set_vuserpoints(id, points);

//Called before item purchase
//
//return SHOP_BLOCK if you want to block item purchase
forward jb_item_bought_pre(id, item);

//Called after item purchase
forward jb_item_boight_post(id, item);

//Called before item purchase
//
//return SHOP_BLOCK if you want to block item purchase
forward jb_vitem_bought_pre(id, item);

//Called after item purchase
forward jb_vitem_boight_post(id, item);

//Called before opening the shop menu
//
//return SHOP_BLOCK if you want to block shop opening
forward jb_openshop_pre(id);

//Called after opening the shop menu
forward jb_openshop_post(id);

//Called before opening the shop menu
//
//return SHOP_BLOCK if you want to block shop opening
forward jb_vopenshop_pre(id);

//Called after opening the shop menu
forward jb_vopenshop_post(id);

/* From JailBreak Shop Item Chameleon */

//Returns whether a player is chameleon or not
native jb_is_user_chameleon(id);