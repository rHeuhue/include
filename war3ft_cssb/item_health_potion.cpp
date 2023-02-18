
ITEM_HealthPotion(idUser,iItem)
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
			new iMaxHealth = clHP:getRaceMaxHealth(idUser);
			new iCurrentHealth =  clHP:getUserHealth(idUser);
			new iBonusHp = iHealthItemRace;
			
			if( (iCurrentHealth + iBonusHp) > iMaxHealth)
				clHP:setUserHealth(idUser,iMaxHealth);
			else
				clHP:setUserHealth(idUser,iCurrentHealth + iBonusHp);
		}
		case 2:
		{
			new iMinHealth = clHP:getRaceMinHealth(idUser);
			new iCurrentHealth =  clHP:getUserHealth(idUser);
		
			if (iCurrentHealth < iMinHealth)
			{
				clHP:setUserHealth(idUser,iMinHealth);
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
			new iMaxHealth = clHP:getRaceMaxHealth(idUser);
			new iCurrentHealth =  clHP:getUserHealth(idUser);
						
			if(iCurrentHealth < iMaxHealth)
				clHP:setUserHealth(idUser,iMaxHealth);
			
		}
	}	

	format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU3_7");
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

	EffectRestoreHealth(idUser);

	client_cmd(idUser, "speak %s",arrStrSounds[SOUND_HEALTH_POTION], 0.3, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM); 

	arrIsByuItemOneRound[idUser][ITEM_HEALTH_POTION]++;

}

// Effect
EffectRestoreHealth(idUser)
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
	write_short(arrIdSprites[SPR_HEALTH_POTION]); // sprites
	write_byte(15); // scale in 0.1's
	write_byte(12); // framerate
	write_byte(14); // flags 
	message_end(); // message end
	
	message_begin(MSG_ONE_UNRELIABLE, gmsgScreenFade,_, idUser);
	write_short(1<<10);
	write_short(1<<10);
	write_short(0x0000);
	write_byte(0);//r
	write_byte(255);  //g
	write_byte(0);  //b
	write_byte(75);
	message_end();
}