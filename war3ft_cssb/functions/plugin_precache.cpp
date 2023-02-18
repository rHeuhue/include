// ******************************************************************
// 
// ******************************************************************



public plugin_precache()
{

	//register_forward(FM_PrecacheModel, "PrecacheModel"); 
   // register_forward(FM_PrecacheSound, "PrecacheSound");    

	WC3_Precache();
	
	fLootPrecache();

	format(szSpriteItemWhite, charsmax(szSpriteItemWhite), "%s","sprites/white.spr");
	idSpriteItemWhite = engfunc(EngFunc_PrecacheModel,szSpriteItemWhite);

	sm4_PluginPrecache();
}

//Отлов какие файлы попали в прекеш
/*
public PrecacheModel(const szModel[])  
{  

	log_to_file("test.txt","Model: %s",szModel);

	
    for(new i = 0; i < sizeof(g_Models); i++) 
    { 
        if( containi(szModel, g_Models[i]) != -1 )  
        {  
            forward_return(FMV_CELL, 0)  
            return FMRES_SUPERCEDE  
        }  
    } 
	
    return FMRES_IGNORED  
}  

public PrecacheSound(const szSound[])  
{  
	log_to_file("test.txt","Sound: %s",szSound);

	
    for(new i = 0; i < sizeof(g_Sounds); i++) 
    { 
        if( containi(szSound, g_Sounds[i]) != -1 )  
        {  
            forward_return(FMV_CELL, 0)  
            return FMRES_SUPERCEDE  
        }  
    } 
	
    return FMRES_IGNORED  
} 
*/