// ******************************************************************
// 
// ******************************************************************

public client_connect( id )
{
	if ( !WC3_Check() )
		return;
		
	// Initialize this player
	WC3_PlayerInit( id );

	client_cmd( id, "hud_centerid 0" );


	arrIntData[id][P_RESPAWNBY]				= 0;
	arrIntData[id][P_SPECMODE]				= 0;

	arrBoolData[id][PB_ISBURNING]			= false;
	arrBoolData[id][PB_JUSTJOINED]			= true;
	arrBoolData[id][PB_CAN_RENDER]			= true;
	arrBoolData[id][PB_HAS_SPAWNED]		= false;
	arrBoolData[id][PB_SKINSWITCHED]		= false;

	// User should have no items on connect...
	g_iShopMenuItems[id][ITEM_SLOT_ONE]	= ITEM_NONE;
	g_iShopMenuItems[id][ITEM_SLOT_TWO] = ITEM_NONE;
	g_iShopMenuItems[id][ITEM_SLOT_THREE] = ITEM_NONE;	
		
	//Для авто-закупки предметов
	abi_ClientConnect(id);
	
	arrIntData[id][P_HECOUNT]		= 0;
	arrIntData[id][P_FLASHCOUNT]	= 0;

	// Reset the "cheat" variables
	new j;
	for ( j = 0; j < MAX_RACES; j++ )
		g_bGivenLevel10[id][j]	= false;

	return;
}