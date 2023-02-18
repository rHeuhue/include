

ITEM_SteelSkin(idUser,iItem)
{
	if (!is_user_alive(idUser)) 
		return;

	//Режимы работы предметов "Стальная кожа" и "Микстура здоровья":
	//Настройка значений выполняется в health_races.ini и armor_races.ini 
	//[1] - Прибавляет к текущему здоровью и броне значения (HEALTH_ITEM и ARMOR_ITEM) 
	//[2] - Восстанавливает минимальное значение здоровья и брони выставленные герою
	//[3] - Восстанавливает максимальное значение здоровья и брони  выставленные герою


	new iModeHpArmor = get_pcvar_num(CVAR_wc3_mode_hp_armor);

	switch(iModeHpArmor)
	{
		case 1:
		{
			new iMaxArmor = clAr:getRaceMaxArmor(idUser);
			new CsArmorType:tArmor;
			new iCurrentArmor =  clAr:getUserArmor(idUser,tArmor);
			new iBonusArmor = iArmorItemRace;

			if((iCurrentArmor + iBonusArmor) > iMaxArmor)
				clAr:setUserArmor(idUser,iMaxArmor);
			else
				clAr:setUserArmor(idUser,iCurrentArmor + iBonusArmor);


		}
		case 2:
		{
			new iMinArmor = clAr:getRaceMinArmor(idUser);
			new CsArmorType:tArmor;
			new iCurrentArmor =  clAr:getUserArmor(idUser,tArmor);
		
			if (iCurrentArmor < iMinArmor)
			{
				clAr:setUserArmor(idUser,iMinArmor);
			}
			else
			{
				new iItemMoney = ITEM_Cost(idUser, iItem);
				new iCurrentMoney = SHARED_GetUserMoney(idUser);
				
				SHARED_SetUserMoney(idUser, iCurrentMoney + iItemMoney,0);

				return;
			}

		}
		case 3:
		{
			new iMaxArmor = clAr:getRaceMaxArmor(idUser);
			new CsArmorType:tArmor;
			new iCurrentArmor =  clAr:getUserArmor(idUser,tArmor);
			
			if(iCurrentArmor < iMaxArmor)
				clAr:setUserArmor(idUser,iMaxArmor);
						
		}
	}	


	format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU3_9");
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

	EffectRestoreArmor(idUser);
	
	client_cmd(idUser, "speak %s",arrStrSounds[SOUND_STEEL_SKIN], 0.3, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM); 

	arrIsByuItemOneRound[idUser][ITEM_STEEL_SKIN]++;

}

// Effect
EffectRestoreArmor(idUser)
{
	if (!is_user_alive(idUser)) 
		return;
	
	static Float:origin[3];
	pev(idUser,pev_origin,origin);
    
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY); 
	write_byte(TE_EXPLOSION); // TE_EXPLOSION
	write_coord(floatround(origin[0])); // origin x
	write_coord(floatround(origin[1])); // origin y
	write_coord(floatround(origin[2])); // origin z
	write_short(arrIdSprites[SPR_STEEL_SKIN]); // sprites
	write_byte(15); // scale in 0.1's
	write_byte(12); // framerate
	write_byte(14); // flags 
	message_end(); // message end
	
	message_begin(MSG_ONE_UNRELIABLE, gmsgScreenFade,_, idUser);
	write_short(1<<10);
	write_short(1<<10);
	write_short(0x0000);
	write_byte(238);//r
	write_byte(232);  //g
	write_byte(170);  //b
	write_byte(75);
	message_end();

}

stock fm_cs_get_user_armor(client, &CsArmorType:armortype)
{
    armortype = CsArmorType:get_pdata_int(client, OFFSET_ARMORTYPE, EXTRAOFFSET);
   
    static Float:armorvalue;
    pev(client, pev_armorvalue, armorvalue);
    return floatround(armorvalue);
}
 
stock fm_cs_set_user_armor(client, armorvalue, CsArmorType:armortype)
{
    set_pdata_int(client, OFFSET_ARMORTYPE, _:armortype, EXTRAOFFSET);
   
    set_pev(client, pev_armorvalue, float(armorvalue));
   
    if( armortype != CS_ARMOR_NONE )
    {
        static ArmorType;
        if( ArmorType || (ArmorType = get_user_msgid("ArmorType")) )
        {
                emessage_begin(MSG_ONE_UNRELIABLE, ArmorType, _, client);
                ewrite_byte((armortype == CS_ARMOR_VESTHELM) ? 1 : 0);
                emessage_end();
        }
    }
}