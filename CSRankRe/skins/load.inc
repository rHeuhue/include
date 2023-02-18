#if defined _skins_load_included 
	#endinput
#endif

#define _skins_load_included 

#include <amxmodx>

stock ReadFile_Skins()
{
	new fileSkin[64]; getDirByType(DIR_CONFIG, fileSkin, charsmax(fileSkin), "Skins.ini")
	new f = fopen(fileSkin, "r")
	
	if(!f)	{
		return;
	}
	
	new skin_id[SKINS_ID_MAX_LEN];
	new item_class[SKINS_RARITY_MAX_LEN];

	new filedata[512];
	new data[Items];
	new prefix[2];

	new getItemFromContainer[6]
	
	while(!feof(f))
	{
		fgets(f, filedata, charsmax(filedata))
		
		if(!filedata[0] || filedata[0] == '#' || filedata[0] == ';'  || filedata[0] != '^"')
			continue;
		
		getItemFromContainer[0] = '^0'

		parse(filedata, skin_id, charsmax(skin_id), data[ITEM_REPLACE], 31, data[ITEM_NAME], 63,\
		data[ITEM_MODEL_V], 63,data[ITEM_MODEL_P], 63,data[ITEM_MODEL_W], 63, item_class, charsmax(item_class), getItemFromContainer, charsmax(getItemFromContainer))

		prefix[0] = skin_id[0];
		if ( !is_str_num(prefix) ) replace(skin_id, charsmax(skin_id), prefix, "");

		switch (prefix[0]) {
			case 'l' : data[ITEM_ID] = 10000 + str_to_num(skin_id);
			case 'r' : data[ITEM_ID] = 5000 + str_to_num(skin_id);
			case 'n' : data[ITEM_ID] = 1000 + str_to_num(skin_id);

			default:data[ITEM_ID] = str_to_num(skin_id);
		}


		if ( equali(item_class, "normal") ) 			data[ITEM_CLASS] = 1;
		else if ( equali(item_class, "rare") ) 			data[ITEM_CLASS] = 2;
		else if ( equali(item_class, "legendary") ) 	data[ITEM_CLASS] = 3;
		else 											data[ITEM_CLASS] = str_to_num(item_class);

		// По умолчанию можно получить из контейнера
		if ( !getItemFromContainer[0] ) data[ITEM_GET_FROM_CONTAINER] = true
		else if ( getItemFromContainer[0] && equali(getItemFromContainer, "yes")) data[ITEM_GET_FROM_CONTAINER] = true
		else if (getItemFromContainer[0] && equali(getItemFromContainer, "no")) data[ITEM_GET_FROM_CONTAINER] = false

		ArrayPushArray(g_Items, data)
		
		num_to_str( data[ITEM_ID], skin_id, charsmax(skin_id))
		TrieSetCell( g_ItemsTrie, skin_id, ArraySize(g_Items) - 1)
	}
	
	PrintMessage("[%s] Load %d skins", PLUGIN, ArraySize(g_Items))
}
stock PrecacheSkins()
{
	new size = ArraySize(g_Items);
	new data[Items];

	for(new i = 0; i<size; i++)
	{
		ArrayGetArray(g_Items, i, data)

		loadSkins_precache((data[ITEM_MODEL_V]), data[ITEM_CLASS], true)
		loadSkins_precache((data[ITEM_MODEL_P]), data[ITEM_CLASS])
		loadSkins_precache((data[ITEM_MODEL_W]), data[ITEM_CLASS])
	}
}

stock loadSkins_precache( model[], model_rarity, bool:force = false ) {
	new ext = bool:file_exists(model);

	if (!ext) {
		return PrintMessage("[%s] ERROR! Can't find File '%s'",PLUGIN, model)
	}

	if (force) {
		return precache_model(model)
	}

	if (model_rarity == 1) {
		return 0;
	}

	return precache_model(model)
}