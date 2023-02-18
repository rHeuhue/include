// ******************************************************************
// 
// ******************************************************************

public client_putinserver( idUser )
{
	if ( !WC3_Check() )
		return;

	// Check for steam ID pending
	static szPlayerID[32];
	get_user_authid( idUser, szPlayerID, 31 );
	
	// Then the player doesn't have a steam id, lets make them reconnect
	if ( equal(szPlayerID, "STEAM_ID_PENDING") )
		client_cmd( idUser, "reconnect" );

	// Get the user's ID!
	DB_FetchUniqueID( idUser );

	arrBoolData[idUser][PB_ISCONNECTED] = true;
	
	// Check user's cvar if the user isn't a bot and if we're not running a 64-bit server
	if ( !is_user_bot( idUser ) && !is_amd64_server() )
		query_client_cvar( idUser, "cl_minmodels", "_CS_CheckMinModelsValue" );
		

	sm4_ClientPutinserver(idUser);
		
	set_task(3.0, "mxp_ClientPutinserver", TASK_MULTIXP + idUser );
	
	return;
}