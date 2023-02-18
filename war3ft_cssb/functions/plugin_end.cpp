// ******************************************************************
// 
// ******************************************************************

public plugin_end()
{
	if ( !WC3_Check() )
		return;
	
	FWD_Destroy();
	DB_SaveAll( false );
	DB_Prune();
	DB_Close();

	DestroyForward(mfBuyForward);
	DestroyForward(mfSelectRace);
	DestroyForward(mfSpawn);
	DestroyForward(mfChangeSkin);
	

	return;
}