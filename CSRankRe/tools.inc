#if defined _tools_included
    #endinput
#endif

#define _tools_included

#include <amxmodx>

#define pluginName PLUGIN

#define getDir(%0,%1,%2) get_localinfo(%0,%1,%2)

enum DirData {
    DIR_CONFIG = 0,
    DIR_LOG,
    DIR_DATA
}

stock dirTypeName[DirData][] = {
    "amxx_configsdir",
    "amxx_logs",
    "amxx_datadir"
}
/* Return path of dirType with plugin_name. For Example: dirType=DIR_LOGS, addons/amxmodx/logs/Plugin/
    @param DirData:dirType dir const
    @param out[] - result string
    @param len
    @param addToEnd[] - string that add in the end of path

    @return int
    
 */
stock getDirByType( DirData:dirType, out[], len, addToEnd[], any:...) {
    
    new base[64], szMsg[64];

    getDir( dirTypeName[dirType],base, charsmax(base));
    vformat(szMsg, charsmax(szMsg), addToEnd, 5);

    formatex(out, len, "%s/%s/", base, pluginName);
    if ( !dir_exists(out) ) mkdir(out);

    return formatex(out, len, "%s/%s/%s", base,pluginName, szMsg);
}
/* Create path of dirType with plugin_name. For Example: dirType=DIR_LOGS, addons/amxmodx/logs/Plugin/
    @param DirData:dirType - dir const

    @return bool
 */
stock bool:createDirByType(DirData:dirType) {
    new base[64];
    getDir( dirTypeName[dirType],base, charsmax(base));

    formatex(base, charsmax(base), "%s/%s", base,pluginName)
    return dir_exists(base) ? true : !mkdir(base);

}

stock Print( const id, const szMessage[], any:...)
{
	new szMsg[196];
	vformat(szMsg, charsmax(szMsg), szMessage, 3);

	return client_print_color(id, print_team_grey, "^1[^4%s^1] %s", PLUGIN, szMsg)
}

stock bool:IsValidStr( str[] ) {
    return bool:str[0];
}
stock is_valid_steamid( UserAuthID[] )
{
	if (equali(UserAuthID, "STEAM_ID_LAN") || equali(UserAuthID, "STEAM_ID_PENDING") || equali(UserAuthID, "VALVE_ID_LAN") || equali(UserAuthID,"VALVE_ID_PENDING") || equali(UserAuthID, "STEAM_666:88:666"))
		return 0;

	return 1
}
stock SQL_SafeString(input[], len)
{
	replace_all(input, len, "'", "*");
	replace_all(input, len, "^"", "*"); // ^"
	replace_all(input, len, "`", "*");
}

stock bool:ArraySearchCell( Array:array, cell) {
    new size = ArraySize(array);
    
    for(new i;i<size; i++) {
        if ( ArrayGetCell(array, i) == cell) return true;
    }

    return false;
}
/*
get_dir_vars( out, len, saveToPath[] = "") {
    if ( !strlen(saveToPath) )
        return getDirByType(DirData:DIR_DATA, dataDir, charsmax(dataDir), "assign.txt");

    if ( containi(saveToPath, "assign.txt") == -1 ) {
        if ( dir_exists(saveToPath) )
            add(saveToPath, charsmax(saveToPath), "/assign.txt")
        else return 0;
    }

    return formatex(out,len, "%s", saveToPath);
}
bool:set_stored_var( const key[], const value[], saveToPath[] = "" ) {
    new filename[64];

    get_dir_vars(filename, charsmax(filename), saveToPath);

    static const temp_vault_name[] = "assign_set_data.txt"

	new file = fopen(temp_vault_name, "wt");
    new vault = fopen(filename, "rt");

    new _data[128], _key[64], _other[3],bool:replaced = false;
    while( !feof(vault) )
    {
		fgets(vault, _data, sizeof(_data) - 1);
		parse(_data, _key, sizeof(_key) - 1, _other, sizeof(_other) - 1);
		
		if( equal(_key, key) && !replaced )
		{
			fprintf(file, "^"%s^" ^"%s^"^n", key, data);
			replaced = true;
		}
		else fputs(file, _data);
	}
	
	if( !replaced ) fprintf(file, "^"%s^" ^"%s^"^n", key, data);
	
	fclose(file);
	fclose(vault);
	
	delete_file(filename);
	
	while( !rename_file(temp_vault_name, filename, 1) ) { }
    return true;
}

bool:get_stored_var( const key[], out[], len, saveToPath[] = "") {
    new filename[64];
	get_dir_vars(filename, charsmax(filename), saveToPath);
	
	new vault = fopen(filename, "rt");
	new _data[128], _key[64];
	
	while( !feof(vault) )
	{
		fgets(vault, _data, sizeof(_data) - 1);
		parse(_data, _key, sizeof(_key) - 1, data, len);
		
		if( equal(_key, key) )
			return fclose(vault);
	}
	
	fclose(vault);
	return !copy(data, len, "");
}
*/
stock bool:strcopy(  const pre[], const post[], const str[], out[] ) {
    new find = containi(str, pre);
    new len = strlen(pre);
    if ( find == -1 ) return false;

    find += len;
    new end = containi(str, post);

    return bool:copy(out, end - find, str[find])
}
