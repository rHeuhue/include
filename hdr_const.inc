#if defined _hdeathrun_const_included
	#endinput
#endif
#define _hdeathrun_const_included

/* Load custom module ?

#pragma reqlib LIBRARY_NAME
#if !defined AMXMODX_NOAUTOLOAD
	#pragma loadlib LIBRARY_NAME
#endif

*/

public stock const MOD_VERSION[] = "HDR_ReAPI_0.0.2"
public stock const MOD_AUTHOR[] = "Huehue"

#include <WPMGPrintChatColor>
#include <reapi_stocks>

public stock const MOD_PREFIX[] = "Huehue's DeathRun"
public stock const MOD_CHAT_PREFIX[] = "!y[!gHDR!y]"
public stock const MOD_MENU_PREFIX[] = "\w[\yHDR\w]"

public stock const MOD_AUTHOR_DISCORD[] = "Discord: Ivaylo#1914"

enum
{
	HDR_HANDLED = 0,
	HDR_CONTINUE,
	HDR_HANDLED_MAIN
}

enum _:eHDR_XYZ
{
	X, Y, Z
}

enum _:eHDR_FXYZ
{
	Float:X, Float:Y, Float:Z
}

enum _:eHDR_RGB
{
	R, G, B
}

enum TeamName:eHDR_Teams
{
	HDR_UNASSIGNED = TEAM_UNASSIGNED,
	HDR_ACTIVATOR = TEAM_TERRORIST,
	HDR_RUNNER = TEAM_CT,
	HDR_SPECTATOR = TEAM_SPECTATOR
}


stock PCC(const pPlayer, const szInputMessage[], any:...)
{
	static szMessage[191]
	new iLen = formatex(szMessage, charsmax(szMessage), "%s  ", MOD_CHAT_PREFIX)
	vformat(szMessage[iLen], charsmax(szMessage) - iLen, szInputMessage, 3)
	
	PrintChatColor(pPlayer, PRINT_COLOR_GREY, szMessage)
}

stock client_cmdex(id, const command[], any:...)
{
	#pragma unused command
	
	if (id == 0 || is_user_connected(id))
	{
		new szMessage[256]
		
		format_args(szMessage, charsmax(szMessage), 1)
		
		message_begin(id == 0 ? MSG_ALL : MSG_ONE, 51, _, id)
		write_byte(strlen(szMessage) + 2)
		write_byte(10)
		write_string(szMessage)
		message_end()
	}
}