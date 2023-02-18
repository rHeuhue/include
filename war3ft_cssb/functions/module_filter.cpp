// ******************************************************************
// 
// ******************************************************************

/*
public module_filter( const module[] )
{
	
	// We don't need to display a message, we'll display it later if we need to (when the DB is set up if XP Saving is on)
	if ( equal( module, "dbi" ) || equal( module, "sqlx" ) )
	{
		return PLUGIN_HANDLED;
	}
	// Dammit plugin can't load now :/ - technically we should never get here unless the module doesn't exist in the modules folder
	else
	{
		WC3_Log( true, "Please enable the '%s' module in your modules.ini file", module );

		return PLUGIN_CONTINUE;
	}

	return PLUGIN_HANDLED;
}
*/