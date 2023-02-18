/*
*	Item Defines
*/


// Item Charge Defines
#define NECKLACE_CHARGES	4
#define HELM_CHARGES		3
#define CHARGE_DISPOSE      1

#define	RING_FREQ			2.0
#define RING_BONUS     		5

// Item Variable Defines


#define MAX_PLAYER_ITEMS    2

#define ITEM_SLOT_ONE       0
#define ITEM_SLOT_TWO       1
#define ITEM_SLOT_FULL      2

#define ITEM_NONE          -1
#define ITEM_ANKH		    0
#define ITEM_BOOTS		    1
#define ITEM_CLAWS		    2
#define ITEM_CLOAK		    3
#define ITEM_MASK		    4
#define ITEM_NECKLACE	    5
#define ITEM_FROST		    6
#define ITEM_HEALTH		    7
#define ITEM_TOME		    8
#define ITEM_SCROLL		    9
#define ITEM_PROTECTANT     10
#define ITEM_HELM		    11
#define ITEM_AMULET		    12
#define ITEM_SOCK		    13
#define ITEM_GLOVES		    14
#define ITEM_RING		    15
#define ITEM_CHAMELEON	    16
#define ITEM_MOLE		    17
#define	ITEM_MINE			18

#define MAX_SHOPMENU_ITEMS  19


new ITEM_COST[MAX_SHOPMENU_ITEMS];                  // Holds the price of an item


// Item Variables
new g_iShopMenuItems[33][MAX_PLAYER_ITEMS];			// Holds the player's current items
new g_iFutureItem[33];                              // Holds the item that the player wants to buy 

new g_iNecklaceCharges[33];							// Holds the number of charges left in the player's necklace
new g_iHelmCharges[33];								// Holds the number of charges left in the player's helm

new bool:g_bPlayerBoughtAnkh[33];					// Set to true when a user buys an ankh
new bool:g_bPlayerBoughtMole[33];					// Set to true when a user buys a mole

new g_iGloveTimer[33];								// Keeps track of how much time is left to give a user a grenade



#define ITEM_CHARGEABLE		1
#define ITEM_USEONBUY		2
#define ITEM_BUYWHENDEAD	4
#define ITEM_NEXTROUNDUSE	8

new g_iFlag[MAX_SHOPMENU_ITEMS] = {0};			// Stores information about items

#define ITEM_COST_RATIO		0.7

new bool:iProtectant[33];

#define	TASK_PROTECTANT			97854

#define	FREQUENCY_PROTECTANT 	2.0
#define	RADIUS_PROTECTANT		700

#define BUY_MINE		1