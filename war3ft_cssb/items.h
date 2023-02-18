/*
*	Item Defines
*/



#define GRENADE_PROTECTION_CHARGES get_pcvar_num( CVAR_wc3_he_protect )	//���������� ������� ������ �� HE

#define CHARGE_DISPOSE      1
#define RING_INCREMENT      1


// Item Variable Defines
#define MAX_SHOPMENU_ITEMS  36
#define MAX_PLAYER_ITEMS    3
#define MAX_PAGE_ITEMS      9
#define ITEM_SLOT_ONE       0
#define ITEM_SLOT_TWO       1
#define ITEM_SLOT_THREE     2
#define ITEM_SLOT_FULL      3

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
//��� shopmenu3
#define ITEM_INTELLECT				18
#define ITEM_GRENADE_PROTECTION	    19
#define ITEM_MIRROR_SHIELD		    20
#define ITEM_ESP				    21
#define ITEM_FROST_ARMOR		    22
#define ITEM_DEATH_TOUCH			23
#define ITEM_HEALTH_POTION		    24	//� ���� �� ����������
#define ITEM_ULTIMATE_TIMER_DIVIDER	25	//Ultimate Timer Divider
#define ITEM_STEEL_SKIN				26

#define FROST_ARMOR_DAMAGE get_pcvar_num( CVAR_wc3_factor_dmg_frost_armor )	//������� ����������� ���������� � ������ ������������ ������� 
																			//HP = FROST_ARMOR_DAMAGE * ARMOR_RATIO(0.7)
																			//AR = FROST_ARMOR_DAMAGE * ARMOR_BONUS(0.5)

//#define DEATH_TOUCH_DAMAGE			400	//������� ����������� ������ (������� �����) 
new arrDeathTouch[33];

#define BONUS_INTELLECT	get_pcvar_num( CVAR_wc3_bonus_intellect )	//��������� XP ��� �������� Intellect

//���,��������� ���. �������������� �� OFFENSIVE_MIRROR_SHIELD% � �������� �� DEFENSIVE_MIRROR_SHIELD% ������ � ����������
#define OFFENSIVE_MIRROR_SHIELD	get_pcvar_float(CVAR_wc3_off_mirror_shield)		//�������� ���. �������������� ������
#define DEFENSIVE_MIRROR_SHIELD	get_pcvar_float(CVAR_wc3_def_mirror_shield)		//�������� ���. �������� ������
#define ABILITIES_MIRROR_SHIELD	get_pcvar_float(CVAR_wc3_abil_mirror_shield)	//�������� ���. ������

new arrIsByuItemOneRound[33][MAX_SHOPMENU_ITEMS];	// ����������� ������� ��������� (������ �� ���� �����)
//#define BYU_ITEM_ONE_ROUND_TOME	5	//������� ��� ����� �������� ������� Tome of Experience �� ���� �����


#define MAX_ITEMS_PAGE		9

// Item Variables
new g_iShopMenuItems[33][MAX_PLAYER_ITEMS];			// Holds the player's current items
new g_iFutureItem[33];                              // Holds the item that the player wants to buy 

new g_iTotalRings[33];								// Holds the number of rings the player has
new g_iNecklaceCharges[33];							// Holds the number of charges left in the player's necklace
new g_iHelmCharges[33];								// Holds the number of charges left in the player's helm

new arriTotalRingsGrenadeProtection[33];			// ���������� ����� ������ �� ������
//new arrStoreHP[33];								// �������������� HP ��� ����������� � �������


new bool:g_bPlayerBoughtAnkh[33];					// Set to true when a user buys an ankh
new bool:g_bPlayerBoughtMole[33];					// Set to true when a user buys a mole

new g_iGloveTimer[33];								// Keeps track of how much time is left to give a user a grenade

new ITEM_COST[MAX_SHOPMENU_ITEMS];                  // Holds the price of an item

#define ITEM_CHARGEABLE		1
#define ITEM_USEONBUY		2
#define ITEM_BUYWHENDEAD	4
#define ITEM_NEXTROUNDUSE	8

new g_iFlag[MAX_SHOPMENU_ITEMS] = {0};			// Stores information about items

#define ITEM_COST_RATIO		0.7
#define ITEM_COST_RATIO_VIP		0.1

#define BUY_ITEM_ONE_ROUND_ITEM_SCROLL get_pcvar_num( CVAR_wc3_buy_round_scroll ) //������� ��� ����� �������� ������� Scroll of Respawning �� ���� �����
#define BUY_ITEM_ONE_ROUND_ITEM_GLOVES get_pcvar_num( CVAR_wc3_buy_round_gloves ) //������� ��� ����� �������� ������� �������� �������� �� ���� ����� (����� ���)