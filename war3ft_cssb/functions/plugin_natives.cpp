// ******************************************************************
// 
// ******************************************************************

public plugin_natives()
{
		
	//register_library("cl_buy");

	//set_module_filter( "module_filter" );
	//set_native_filter( "native_filter" );
	//set_error_filter( "error_filter" );
		
	register_native("cssb_get_user_race", "native_get_user_race", 1);
	register_native("cssb_get_user_race_name", "native_get_user_race_name", 1);		
	
	register_native("cssbGetTimeSpawnTalisman", "nativeGetTimeSpawnTalisman", 1);
	register_native("cssbSetPlayerLevel", "nativeSetPlayerLevel", 1);	
	register_native("cssbSetPlayerTalisman", "nativeGiveTalisman", 1);
	
	register_native("cssbGetIdRace", "nativeGetIdRace", 1);
	register_native("cssbGetLvLRace", "nativeGetLvLRace", 1);
	register_native("cssbGiveXP", "nativeGiveXP", 1);
		
	register_native("cssbItemGetSlot", "ITEM_GetSlot", 1);
	register_native("cssbIsItemUserSlot", "bIsItemUserSlot", 1);
	register_native("cssbItemGiveItem", "ITEM_GiveItem", 1);
	register_native("cssbItemCost", "ITEM_Cost", 1);
	

	//register_library("cs_player_models_api");
	register_native("cssbSetPlayerModel", "native_set_player_model");
	register_native("cssbResetPlayerModel", "native_reset_player_model");
}