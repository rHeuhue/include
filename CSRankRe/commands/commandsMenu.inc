#if defined _commands_menu_included 
	#endinput
#endif

#define _commands_menu_included 

#include <amxmodx>

stock AdminMenu(id) {
	if ( !has_access(id, g_Cvars[CVAR_MAIN_FLAG]) ) {
		return Print(id, "You don't have access to this menu")
	}

	new title[128]; formatex(title, charsmax(title), "%L", id, "CSRE_ADMIN_MENU")
	new menu = menu_create(title, "HandleAdminMenu");

	MenuSetProps(id, menu)

	formatex(title, charsmax(title), "%L", id, "CSRE_ADMIN_MENU_ADD")
	menu_additem(menu, title, "1")

	return menu_display(id, menu, 0)
}

public HandleAdminMenu(id, menu, item)
{
	if(item == MENU_EXIT)
		return menu_destroy(menu);
	
	new data[6], _dummy[1];
	new access, callback;
	menu_item_getinfo(menu, item, access, data,5, _dummy, charsmax(_dummy), callback);

	//new uid = str_to_num(data);

	return menu_destroy(menu);
}