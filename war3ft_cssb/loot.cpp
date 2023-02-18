

public fLootPrecache()
{
	engfunc(EngFunc_PrecacheModel, szModelItems);
	engfunc(EngFunc_PrecacheModel, szModelArXpHpItems);

	idSpriteItems = engfunc(EngFunc_PrecacheModel,szSpriteItems);
	idSpriteNoItems = engfunc(EngFunc_PrecacheModel,szSpriteNoItems);

}

public fScreenFadePlayer(idUser) 
{
	message_begin(MSG_ONE, get_user_msgid("ScreenFade"), {0,0,0}, idUser) ;
	write_short(1<<12);
	write_short(1<<12);
	write_short(1<<12);
	write_byte(0);
	write_byte(200);
	write_byte(0);
	write_byte(20);
	message_end();
}

FloatToNum(Float:floatn)
{
	new str[64], num;
	float_to_str(floatn, str, 63);
	num = str_to_num(str);
	
	return num
}

//Удаление всех брошеных предметов
//(в данном случае запускается при старте нового раунда
//файл events.inl - функция public EVENT_NewRound()  )
fRemoveAllItems()
{
	if(get_pcvar_num( CVAR_wc3_loot_items ) > 0)
	{
		new nextitem  = find_ent_by_class(-1, szClassNameItems);
		while(nextitem)
		{
			remove_entity(nextitem);
			nextitem = find_ent_by_class(-1, szClassNameItems);
		}

		ArrayClear(arrIntTotalLootEntity);
		ArrayClear(arrIntOriginsLootX);
		ArrayClear(arrIntOriginsLootY);
		ArrayClear(arrIntOriginsLootZ);
		ArrayClear(arrIntItemVictimShop1);
		ArrayClear(arrIntItemVictimShop2);
		ArrayClear(arrIntItemVictimShop3);
		ArrayClear(arrIntDrawSpriteItems);
		ArrayClear(arrIntScaleSpriteItems);

		if (get_pcvar_num( CVAR_wc3_loot_remove ) == 1)
				ArrayClear(arrIntLootRemove);
	}
	
}

fCreateArXpHpClass(idUser)
{
	// get origin
	new Float:origin[3];
	pev(idUser, pev_origin, origin);

	new ent = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	if (!ent) return -1;

	// Set data
	set_pev(ent, pev_classname, szClassNameItems);
	set_pev(ent, pev_solid, SOLID_TRIGGER);
	set_pev(ent, pev_movetype, MOVETYPE_TOSS);//#define	MOVETYPE_TOSS 6 gravity/collisions
	set_pev(ent, pev_sequence, 0);
	set_pev(ent, pev_frame, 0.0);
	set_pev(ent, pev_owner, idUser);

	
	// Set size
//	new Float:mins[3] = { -20.0, -20.0, 0.0 };
//	new Float:maxs[3] = { 20.0, 20.0, 30.0 };
//	engfunc(EngFunc_SetSize, ent, mins, maxs);
	
	// Set model
	engfunc(EngFunc_SetModel, ent, szModelArXpHpItems);

	// Set position
	set_pev(ent, pev_origin, origin);
		
	// Установка невидимости и подсветки выпавшего предмета
//	fm_set_rendering(ent,kRenderFxGlowShell,arrColorNoItemsRGB[0],arrColorNoItemsRGB[1],arrColorNoItemsRGB[2],kRenderTransAlpha, 128);
	fm_set_rendering(ent,kRenderFxGlowShell,arrColorNoItemsRGB[0],arrColorNoItemsRGB[1],arrColorNoItemsRGB[2],kRenderNormal, 128);
	
	ArrayPushCell(arrIntTotalLootEntity, ent);
	ArrayPushCell(arrIntOriginsLootX, FloatToNum(origin[0]));
	ArrayPushCell(arrIntOriginsLootY, FloatToNum(origin[1]));
	ArrayPushCell(arrIntOriginsLootZ, FloatToNum(origin[2] + 10));

	/*
	if(get_pcvar_num( CVAR_wc3_loot_remove ) == 1)
	{
		new arrParams[2];
		arrParams[0] = ent;
		arrParams[1] = (TASK_LOOTREMOVE + ent);

		set_task(get_pcvar_float( CVAR_wc3_loot_stay ), "fRemoveLootItem", TASK_LOOTREMOVE + ent,arrParams, sizeof(arrParams));
	}
*/
	return -1;
}

fCreateItemsClass(idUser)
{
	// get origin
	new Float:origin[3];
	pev(idUser, pev_origin, origin);

	new ent = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	if (!ent) return -1;
	
	// Set data
	set_pev(ent, pev_classname, szClassNameItems);
	set_pev(ent, pev_solid, SOLID_TRIGGER);
	set_pev(ent, pev_movetype, MOVETYPE_TOSS);//#define	MOVETYPE_TOSS 6 gravity/collisions
	set_pev(ent, pev_sequence, 0);
	set_pev(ent, pev_frame, 0.0);
	set_pev(ent, pev_owner, idUser);
	
	// Set size
//	new Float:mins[3] = { -20.0, -20.0, 0.0 };
//	new Float:maxs[3] = { 20.0, 20.0, 30.0 };
//	engfunc(EngFunc_SetSize, ent, mins, maxs);
	
	// Set model
	engfunc(EngFunc_SetModel, ent, szModelItems);

	// Set position
	set_pev(ent, pev_origin, origin);
		
	// Установка невидимости и подсветки выпавшего предмета
//	fm_set_rendering(ent,kRenderFxGlowShell,arrColorItemsRGB[0],arrColorItemsRGB[1],arrColorItemsRGB[2],kRenderTransAlpha, 128);
	fm_set_rendering(ent,kRenderFxGlowShell,arrColorItemsRGB[0],arrColorItemsRGB[1],arrColorItemsRGB[2],kRenderNormal, 128);
	
	ArrayPushCell(arrIntTotalLootEntity, ent);
	ArrayPushCell(arrIntOriginsLootX, FloatToNum(origin[0]));
	ArrayPushCell(arrIntOriginsLootY, FloatToNum(origin[1]));
	ArrayPushCell(arrIntOriginsLootZ, FloatToNum(origin[2] + 10));

	
	/*
	if(get_pcvar_num( CVAR_wc3_loot_remove ) == 1)
	{
		new arrParams[2];
		arrParams[0] = ent;
		arrParams[1] = (TASK_LOOTREMOVE + ent);

		set_task(get_pcvar_float( CVAR_wc3_loot_stay ), "fRemoveLootItem", TASK_LOOTREMOVE + ent,arrParams, sizeof(arrParams));
	}
	*/

	return -1;
}


public bIsItemUserSlot(idUser,iSlot)
{
	new iVictimItemShop = ITEM_NONE;

	if(ITEM_Has( idUser, ITEM_ANKH ) == iSlot && ITEM_HasItem( idUser, ITEM_ANKH ) == ITEM_ANKH )
		iVictimItemShop = ITEM_ANKH;
	if(ITEM_Has( idUser, ITEM_BOOTS ) == iSlot && ITEM_HasItem( idUser, ITEM_BOOTS ) == ITEM_BOOTS )
		iVictimItemShop = ITEM_BOOTS;
	if(ITEM_Has( idUser, ITEM_CLAWS ) == iSlot && ITEM_HasItem( idUser, ITEM_CLAWS ) == ITEM_CLAWS )
		iVictimItemShop = ITEM_CLAWS;
	if(ITEM_Has( idUser, ITEM_CLOAK ) == iSlot && ITEM_HasItem( idUser, ITEM_CLOAK ) == ITEM_CLOAK )
		iVictimItemShop = ITEM_CLOAK;
	if(ITEM_Has( idUser, ITEM_MASK ) == iSlot && ITEM_HasItem( idUser, ITEM_MASK ) == ITEM_MASK )
		iVictimItemShop = ITEM_MASK;
	if(ITEM_Has( idUser, ITEM_NECKLACE ) == iSlot && ITEM_HasItem( idUser, ITEM_NECKLACE ) == ITEM_NECKLACE )
		iVictimItemShop = ITEM_NECKLACE;
	if(ITEM_Has( idUser, ITEM_FROST ) == iSlot && ITEM_HasItem( idUser, ITEM_FROST ) == ITEM_FROST )
		iVictimItemShop = ITEM_FROST;
	if(ITEM_Has( idUser, ITEM_HEALTH ) == iSlot && ITEM_HasItem( idUser, ITEM_HEALTH ) == ITEM_HEALTH )
		iVictimItemShop = ITEM_HEALTH;
//	if(ITEM_Has( idUser, ITEM_TOME ) == iSlot && ITEM_HasItem( idUser, ITEM_TOME ) == ITEM_TOME ) //Не входит в слот
//		client_print(idUser,print_chat,"ITEM_TOME YES");
	if(ITEM_Has( idUser, ITEM_SCROLL ) == iSlot && ITEM_HasItem( idUser, ITEM_SCROLL ) == ITEM_SCROLL )
		iVictimItemShop = ITEM_SCROLL;
	if(ITEM_Has( idUser, ITEM_PROTECTANT ) == iSlot && ITEM_HasItem( idUser, ITEM_PROTECTANT ) == ITEM_PROTECTANT )
		iVictimItemShop = ITEM_PROTECTANT;
	if(ITEM_Has( idUser, ITEM_HELM ) == iSlot && ITEM_HasItem( idUser, ITEM_HELM ) == ITEM_HELM )
		iVictimItemShop = ITEM_HELM;
	if(ITEM_Has( idUser, ITEM_AMULET ) == iSlot && ITEM_HasItem( idUser, ITEM_AMULET ) == ITEM_AMULET )
		iVictimItemShop = ITEM_AMULET;
	if(ITEM_Has( idUser, ITEM_SOCK ) == iSlot && ITEM_HasItem( idUser, ITEM_SOCK ) == ITEM_SOCK )
		iVictimItemShop = ITEM_SOCK;
	if(ITEM_Has( idUser, ITEM_GLOVES ) == iSlot && ITEM_HasItem( idUser, ITEM_GLOVES ) == ITEM_GLOVES )
		iVictimItemShop = ITEM_GLOVES;
	if(ITEM_Has( idUser, ITEM_RING ) == iSlot && ITEM_HasItem( idUser, ITEM_RING ) == ITEM_RING )
		iVictimItemShop = ITEM_RING;
	if(ITEM_Has( idUser, ITEM_CHAMELEON ) == iSlot && ITEM_HasItem( idUser, ITEM_CHAMELEON ) == ITEM_CHAMELEON )
		iVictimItemShop = ITEM_CHAMELEON;
	if(ITEM_Has( idUser, ITEM_MOLE ) == iSlot && ITEM_HasItem( idUser, ITEM_MOLE ) == ITEM_MOLE )
		iVictimItemShop = ITEM_MOLE;
	//Для shopmenu3
	if(ITEM_Has( idUser, ITEM_INTELLECT ) == iSlot && ITEM_HasItem( idUser, ITEM_INTELLECT ) == ITEM_INTELLECT )
		iVictimItemShop = ITEM_INTELLECT;
	if(ITEM_Has( idUser, ITEM_GRENADE_PROTECTION ) == iSlot && ITEM_HasItem( idUser, ITEM_GRENADE_PROTECTION ) == ITEM_GRENADE_PROTECTION )
		iVictimItemShop = ITEM_GRENADE_PROTECTION;
	if(ITEM_Has( idUser, ITEM_MIRROR_SHIELD ) == iSlot && ITEM_HasItem( idUser, ITEM_MIRROR_SHIELD ) == ITEM_MIRROR_SHIELD )
		iVictimItemShop = ITEM_MIRROR_SHIELD;
	if(ITEM_Has( idUser, ITEM_ESP ) == iSlot && ITEM_HasItem( idUser, ITEM_ESP ) == ITEM_ESP )
		iVictimItemShop = ITEM_ESP;
	if(ITEM_Has( idUser, ITEM_FROST_ARMOR ) == iSlot && ITEM_HasItem( idUser, ITEM_FROST_ARMOR ) == ITEM_FROST_ARMOR )
		iVictimItemShop = ITEM_FROST_ARMOR;
	if(ITEM_Has( idUser, ITEM_DEATH_TOUCH ) == iSlot && ITEM_HasItem( idUser, ITEM_DEATH_TOUCH ) == ITEM_DEATH_TOUCH )
		iVictimItemShop = ITEM_DEATH_TOUCH;
	if(ITEM_Has( idUser, ITEM_ULTIMATE_TIMER_DIVIDER ) == iSlot && ITEM_HasItem( idUser, ITEM_ULTIMATE_TIMER_DIVIDER ) == ITEM_ULTIMATE_TIMER_DIVIDER )
		iVictimItemShop = ITEM_ULTIMATE_TIMER_DIVIDER;
	if(ITEM_Has( idUser, ITEM_DEVOURER_LIGHT ) == iSlot && ITEM_HasItem( idUser, ITEM_DEVOURER_LIGHT ) == ITEM_DEVOURER_LIGHT )
		iVictimItemShop = ITEM_DEVOURER_LIGHT;
	if(ITEM_Has( idUser, ITEM_ICE_BLOCK ) == iSlot && ITEM_HasItem( idUser, ITEM_ICE_BLOCK ) == ITEM_ICE_BLOCK )
		iVictimItemShop = ITEM_ICE_BLOCK;
	if(ITEM_Has( idUser, ITEM_THIEF ) == iSlot && ITEM_HasItem( idUser, ITEM_THIEF ) == ITEM_THIEF )
		iVictimItemShop = ITEM_THIEF;
	if(ITEM_Has( idUser, ITEM_MIRROR_ULTIMATE ) == iSlot && ITEM_HasItem( idUser, ITEM_MIRROR_ULTIMATE ) == ITEM_MIRROR_ULTIMATE )
		iVictimItemShop = ITEM_MIRROR_ULTIMATE;
	if(ITEM_Has( idUser, ITEM_DEATHCOIL ) == iSlot && ITEM_HasItem( idUser, ITEM_DEATHCOIL ) == ITEM_DEATHCOIL )
		iVictimItemShop = ITEM_DEATHCOIL;
	if(ITEM_Has( idUser, ITEM_IMPALE ) == iSlot && ITEM_HasItem( idUser, ITEM_IMPALE ) == ITEM_IMPALE )
		iVictimItemShop = ITEM_IMPALE;
	if(ITEM_Has( idUser, ITEM_SLEEP ) == iSlot && ITEM_HasItem( idUser, ITEM_SLEEP ) == ITEM_SLEEP )
		iVictimItemShop = ITEM_SLEEP;
	if(ITEM_Has( idUser, ITEM_BOOK_DEAD ) == iSlot && ITEM_HasItem( idUser, ITEM_BOOK_DEAD ) == ITEM_BOOK_DEAD )
		iVictimItemShop = ITEM_BOOK_DEAD;
	if(ITEM_Has( idUser, ITEM_TRANQUILITY ) == iSlot && ITEM_HasItem( idUser, ITEM_TRANQUILITY ) == ITEM_TRANQUILITY )
		iVictimItemShop = ITEM_TRANQUILITY;

	return iVictimItemShop;
}

//Цвет выпавших вещей
stock fColorItems(iItemVictimShop1,iItemVictimShop2,iItemVictimShop3)
{
				new bIsDropItems = 3;
				
				if(iItemVictimShop1 != ITEM_NONE)//Если были у жертвы вещи в слоте 1
				{
					arrColorItemsRGB[0] = 255;
					arrColorItemsRGB[1] = 0;
					arrColorItemsRGB[2] = 0;
					return arrColorItemsRGB;
				}
				else
				{
					bIsDropItems -= 1;
				}
				
				if(iItemVictimShop2 != ITEM_NONE)//Если были у жертвы вещи в слоте 2
				{
					arrColorItemsRGB[0] = 255;
					arrColorItemsRGB[1] = 0;
					arrColorItemsRGB[2] = 0;
					return arrColorItemsRGB;
				}
				else
				{
					bIsDropItems -= 1;
				}

				if(iItemVictimShop3 != ITEM_NONE)//Если были у жертвы вещи в слоте 3
				{
					arrColorItemsRGB[0] = 255;
					arrColorItemsRGB[1] = 0;
					arrColorItemsRGB[2] = 0;
					return arrColorItemsRGB;
				}
				else
				{
					bIsDropItems -= 1;
				}
				
				//Если у жертвы совсем не оказалось предметов
				if(bIsDropItems == 0)
				{
					arrColorItemsRGB[0] = 30;
					arrColorItemsRGB[1] = 144;
					arrColorItemsRGB[2] = 255;
					return arrColorItemsRGB;
				}	
				
	return arrColorItemsRGB;
}


//Есть ли выпавшие вещи у жертвы
stock fIsDropItems(iItemVictimShop1,iItemVictimShop2,iItemVictimShop3)
{
	new bIsDropItems = 3;
	
	if(iItemVictimShop1 == ITEM_NONE)//Если были у жертвы вещи в слоте 1
		bIsDropItems -= 1;
	
	if(iItemVictimShop2 == ITEM_NONE)//Если были у жертвы вещи в слоте 2
		bIsDropItems -= 1;

	if(iItemVictimShop3 == ITEM_NONE)//Если были у жертвы вещи в слоте 3
		bIsDropItems -= 1;
	
	//Если у жертвы совсем не оказалось предметов
	if(bIsDropItems == 0)
		return bIsDropItems;
				
	return bIsDropItems;
}

//Отображение сообщения при поднятии предмета
stock fShowMsgPickUpItem(idUserTouch,szShowMessage[256],iRed,iGreen,iBlue)
{
	set_hudmessage(iRed,iGreen,iBlue,0.85,0.5,0,0.0,5.0,0.02,0.02,-1);
	ShowSyncHudMsg(idUserTouch, msgSyncObj,szShowMessage);
}


//Отображение сообщения при поднятии предмета
stock fShowMessagePickUpItem(idUserTouch,szShowMessage[256],iRed,iGreen,iBlue,iTypeLoot)
{
	UTIL_ClearDHudChannel(idUserTouch);
	UTIL_ClearHudChannel(idUserTouch,HUD_XP);
	WC3_ShowBar(idUserTouch);


	switch(iTypeLoot)
	{
		case enMoney:
			{
				set_dhudmessage(iRed,iGreen,iBlue, 0.85,0.5,2,0.0,2.0,0.02,0.02);
				show_dhudmessage(idUserTouch, szShowMessage);

			}

		case enHealth:
			{
				set_dhudmessage(iRed,iGreen,iBlue, 0.85,0.55,2,0.0,2.0,0.02,0.02);
				show_dhudmessage(idUserTouch, szShowMessage);
			}

		case enArmor:
			{
				set_dhudmessage(iRed,iGreen,iBlue, 0.85,0.6,2,0.0,2.0,0.02,0.02);
				show_dhudmessage(idUserTouch, szShowMessage);
			}

		case enXP:
			{
				set_dhudmessage(iRed,iGreen,iBlue, 0.85,0.65,2,0.0,2.0,0.02,0.02);
				show_dhudmessage(idUserTouch, szShowMessage);
			}

		case enOther:
			{
				set_dhudmessage(iRed,iGreen,iBlue, 0.85,0.45,2,0.0,2.0,0.02,0.02);
				show_dhudmessage(idUserTouch, szShowMessage);
			}
	}
	
}



//Запуск счетчика отсчета на удаление предмета 
public fRunCalcRemoveLootItem()
{
	if (get_pcvar_num( CVAR_wc3_loot_remove ) == 0)
		return;

	if(ArraySize(arrIntTotalLootEntity) == 0)
		return;

	for (new i = 0; i < ArraySize(arrIntTotalLootEntity); i++)
	{
		new entLoot = ArrayGetCell(arrIntTotalLootEntity, i);
		if (!is_valid_ent(entLoot)) 
			continue;

		new iTimerLoot = ArrayGetCell(arrIntLootRemove, i);

		if(iTimerLoot == 0)
		{
			fRemoveLootItem(entLoot);
		}
		else
		{
			ArraySetCell(arrIntLootRemove,i, iTimerLoot - 1);

		}
	}


}
		
//Удаление предмета если он долго лежит на земле
public fRemoveLootItem(idEntLootItem)
{
	if(!is_valid_ent(idEntLootItem))
		return;
		
	entity_set_int(idEntLootItem, EV_INT_movetype, MOVETYPE_FLY);
	entity_set_int(idEntLootItem, EV_INT_rendermode, kRenderTransAlpha);
	entity_set_int(idEntLootItem, EV_INT_renderfx, kRenderFxGlowShell);
	entity_set_float(idEntLootItem, EV_FL_renderamt, 255.0);
	entity_set_vector(idEntLootItem, EV_VEC_rendercolor, Float:{255.0, 255.0, 0.0});
	entity_set_vector(idEntLootItem, EV_VEC_velocity, Float:{0.0, 0.0, 20.0});

	new arrParams[2];
	arrParams[0] = idEntLootItem;
	arrParams[1] = 250;

	fEffectRemoveLootItem(arrParams);

}

public fEffectRemoveLootItem(arr[2]) // arr = [idEntLootItem, Float:fStart
{
	new idEntLootItem = arr[0];
	new iStart = arr[1];

	if(!is_valid_ent(idEntLootItem))
	{
		task_remove(TASK_LOOTITEM + idEntLootItem);
		return;
	}

	static Float:fFadeAmount[4096];

	if(iStart)
	{
		task_remove(TASK_LOOTITEM + idEntLootItem);
		fFadeAmount[idEntLootItem] = float(iStart);
	}

	fFadeAmount[idEntLootItem] -= 25.0;

	if(fFadeAmount[idEntLootItem] > 0.0)
	{
		entity_set_float(idEntLootItem, EV_FL_renderamt, fFadeAmount[idEntLootItem]);

			new arrParams[2];
			arrParams[0] = idEntLootItem;
			arrParams[1] = 0;
			task_set(0.1, "fEffectRemoveLootItem",TASK_LOOTITEM + idEntLootItem,arrParams, sizeof(arrParams));
	}
	else
	{
		new classname[32];
		pev(idEntLootItem, pev_classname, classname, sizeof classname - 1);

		if (equali(classname, "war3ft_loot_items"))
		{
			for (new i = 0; i < ArraySize(arrIntTotalLootEntity); i++)
			{
				if(idEntLootItem == ArrayGetCell(arrIntTotalLootEntity, i))
				{
					new entLoot = ArrayGetCell(arrIntTotalLootEntity, i);
					if (is_valid_ent(entLoot)) 
						engfunc(EngFunc_RemoveEntity, entLoot);

					ArrayDeleteItem(arrIntTotalLootEntity,i);
					ArrayDeleteItem(arrIntOriginsLootX,i);
					ArrayDeleteItem(arrIntOriginsLootY,i);
					ArrayDeleteItem(arrIntOriginsLootZ,i);
					ArrayDeleteItem(arrIntItemVictimShop1,i);
					ArrayDeleteItem(arrIntItemVictimShop2,i);
					ArrayDeleteItem(arrIntItemVictimShop3,i);
					ArrayDeleteItem(arrIntDrawSpriteItems,i);
					ArrayDeleteItem(arrIntScaleSpriteItems,i);
					ArrayDeleteItem(arrIntLootRemove,i);
					
					//client_print(0,print_chat,"Item DELETE");

					break;
				}
			}

		}
	}
}

//Отрисовка иконок
public client_PostThink(idUser)
{
	if(!is_user_alive(idUser)) 
	return;

	if ((fIconDelayLootItems + fIconUpdateLootItems) > get_gametime()) 
		return;
		
	fIconDelayLootItems = get_gametime();

	//Включение/отключение иконки отображающейся над выпавшим талисманом
	if(get_pcvar_num( CVAR_wc3_icon_talisman ) > 0)
		create_icon_origin(idUser, entTalisman, arrIdSprites[SPR_ICON_TALISMAN]);

	if(get_pcvar_num( CVAR_wc3_loot_items ) > 0)
	{
		if (!is_user_alive(idUser) || ArraySize(arrIntTotalLootEntity) == 0)
			return;

		for (new i = 0; i < ArraySize(arrIntTotalLootEntity); i++)
		{
			new iSprite = ArrayGetCell(arrIntDrawSpriteItems, i);
			new iScale = ArrayGetCell(arrIntScaleSpriteItems, i);
			fDrawSprite(idUser,i,iSprite,iScale);
		}
	}

	return;
}


stock create_icon_origin(id, ent, sprite)
{
	if(!is_user_alive(id) || !is_user_connected(id)) 
      return;

	if (!pev_valid(ent)) 
		return;
	
	new Float:fMyOrigin[3]
	entity_get_vector(id, EV_VEC_origin, fMyOrigin)
	
	new target = ent
	new Float:fTargetOrigin[3]
	entity_get_vector(target, EV_VEC_origin, fTargetOrigin)
	fTargetOrigin[2] += 70.0
	
	if (!is_in_viewcone(id, fTargetOrigin)) 
		return;

	new Float:fMiddle[3], Float:fHitPoint[3]
	xs_vec_sub(fTargetOrigin, fMyOrigin, fMiddle)
	trace_line(-1, fMyOrigin, fTargetOrigin, fHitPoint)
							
	new Float:fWallOffset[3], Float:fDistanceToWall
	fDistanceToWall = vector_distance(fMyOrigin, fHitPoint) - 10.0
	normalize(fMiddle, fWallOffset, fDistanceToWall)
	
	new Float:fSpriteOffset[3]
	xs_vec_add(fWallOffset, fMyOrigin, fSpriteOffset)
	new Float:fScale//, Float:fDistanceToTarget = vector_distance(fMyOrigin, fTargetOrigin)
	fScale = 0.01 * fDistanceToWall;
	
	new scale = floatround(fScale)
	scale = max(scale, 1)
	scale = min(scale, 2)
	scale = max(scale, 1)
	
	te_sprite(id, fSpriteOffset, sprite, scale, 100);
}

stock te_sprite(id, Float:origin[3], sprite, scale, brightness)
{	
	message_begin(MSG_ONE, SVC_TEMPENTITY, _, id)
	write_byte(TE_SPRITE)
	write_coord(floatround(origin[0]))
	write_coord(floatround(origin[1]))
	write_coord(floatround(origin[2]))
	write_short(sprite)
	write_byte(scale) 
	write_byte(brightness)
	message_end()
}
stock normalize(Float:fIn[3], Float:fOut[3], Float:fMul)
{
	new Float:fLen = xs_vec_len(fIn)
	xs_vec_copy(fIn, fOut)
	
	fOut[0] /= fLen, fOut[1] /= fLen, fOut[2] /= fLen
	fOut[0] *= fMul, fOut[1] *= fMul, fOut[2] *= fMul
}

//Функция отрисовки
fDrawSprite(idUser,iLoot,iSprite,iScale)
{
	message_begin(MSG_ONE_UNRELIABLE, SVC_TEMPENTITY, {0, 0, 0}, idUser);
	write_byte(TE_SPRITE); // additive sprite, plays 1 cycle
	write_coord(ArrayGetCell(arrIntOriginsLootX, iLoot)); // xpos
	write_coord(ArrayGetCell(arrIntOriginsLootY, iLoot)); // ypos
	write_coord(ArrayGetCell(arrIntOriginsLootZ, iLoot)); // zpos
	write_short(iSprite); // spr index
	write_byte(iScale); // (scale in 0.1's)
	write_byte(30); //brightness
	message_end();
}

//Когда прикасаешься к предмету
public player_Touch(idEntityTouched, idUserTouch)
{ 
	if(get_pcvar_num( CVAR_wc3_loot_items ) > 0)
	{
		if (!pev_valid(idEntityTouched) || !is_user_alive(idUserTouch))
			return FMRES_IGNORED
		
		new szClassname[32];
		pev(idEntityTouched, pev_classname, szClassname, sizeof szClassname - 1)
		
		new iSumMoney = 0;
	
		if (equali(szClassname, "war3ft_loot_items"))
		{
			for (new i = 0; i < ArraySize(arrIntTotalLootEntity); i++)
			{
				if(idEntityTouched == ArrayGetCell(arrIntTotalLootEntity, i))
				{
					new entLoot = ArrayGetCell(arrIntTotalLootEntity, i);
					if (is_valid_ent(entLoot)) 
						engfunc(EngFunc_RemoveEntity, entLoot);
					
					fScreenFadePlayer(idUserTouch);
					
					new iItemVictimShop1 = ArrayGetCell(arrIntItemVictimShop1, i);
					new iItemVictimShop2 = ArrayGetCell(arrIntItemVictimShop2, i);
					new iItemVictimShop3 = ArrayGetCell(arrIntItemVictimShop3, i);
					new bIsDropItems = 3;
					new szShowMessageLoot[256];
					
					if(iItemVictimShop1 != ITEM_NONE)//Если были у жертвы вещи в слоте 1
					{
							if(ITEM_GetSlot( idUserTouch ) != ITEM_SLOT_FULL && 
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_ONE) != iItemVictimShop1 &&
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_TWO) != iItemVictimShop1 &&
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_THREE) != iItemVictimShop1)
							{
								
								ITEM_GiveItem( idUserTouch, iItemVictimShop1);
							}
							else
							{
								//Вознаграждение если у подобравшего все слоты заняты.Дается денежка за вещь
								new iItemMoneyDrop1 = ITEM_Cost( idUserTouch, iItemVictimShop1 );
								iSumMoney += iItemMoneyDrop1;
							}
					}
					else
					{
						bIsDropItems -= 1;
					}
					
					if(iItemVictimShop2 != ITEM_NONE)//Если были у жертвы вещи в слоте 2
					{
							if(ITEM_GetSlot( idUserTouch ) != ITEM_SLOT_FULL && 
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_ONE) != iItemVictimShop2 &&
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_TWO) != iItemVictimShop2 &&
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_THREE) != iItemVictimShop2)
							{
								ITEM_GiveItem( idUserTouch, iItemVictimShop2 );
							}
							else
							{
								//Вознаграждение если у подобравшего все слоты заняты.Дается денежка за вещь
								new iItemMoneyDrop2 = ITEM_Cost( idUserTouch, iItemVictimShop2 );
								iSumMoney += iItemMoneyDrop2;
							}
					}
					else
					{
						bIsDropItems -= 1;
					}
					
					if(iItemVictimShop3 != ITEM_NONE)//Если были у жертвы вещи в слоте 3
					{
							if(ITEM_GetSlot( idUserTouch ) != ITEM_SLOT_FULL && 
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_ONE) != iItemVictimShop3 &&
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_TWO) != iItemVictimShop3 &&
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_THREE) != iItemVictimShop3)
							{
								ITEM_GiveItem( idUserTouch, iItemVictimShop3 );
							}
							else
							{
								//Вознаграждение если у подобравшего все слоты заняты.Дается денежка за вещь
								new iItemMoneyDrop3 = ITEM_Cost( idUserTouch, iItemVictimShop3 );
								iSumMoney += iItemMoneyDrop3;
							}
					}
					else
					{
						bIsDropItems -= 1;
					}
					
					//Начисление денег за все предметы
					if(iSumMoney > 0)
					{
						SHARED_SetUserMoney( idUserTouch,SHARED_GetUserMoney( idUserTouch ) + iSumMoney, 1 );
								
						format(szShowMessageLoot, charsmax(szShowMessageLoot), "+$: %d",iSumMoney);
						//fShowMsgPickUpItem(idUserTouch,szShowMessageLoot,188,143,143);
						fShowMessagePickUpItem(idUserTouch,szShowMessageLoot,188,143,143,enMoney);
					}
					
					//Если у жертвы совсем не оказалось предметов
					if(bIsDropItems == 0)
					{
						//client_print(idUserTouch,print_chat,"XP: %d",XP_GivenByLevel( iLevel ));
						//client_print(idUserTouch,print_chat,"XP 2: %d",XP_GetByLevel( iLevel ));
											
						switch(random_num(0, 2))
						{
							case 0:
							{
								new iMaxHealth = clHP:getRaceMaxHealth(idUserTouch);
								new iCurrentHealth =  clHP:getUserHealth(idUserTouch);
								new iBonusHp = get_pcvar_num(CVAR_wc3_loot_items_health);
								
								if((iCurrentHealth + iBonusHp) > iMaxHealth)
									clHP:setUserHealth(idUserTouch,iMaxHealth);
								else
									clHP:setUserHealth(idUserTouch,iCurrentHealth + iBonusHp);
								
								format(szShowMessageLoot, charsmax(szShowMessageLoot), "+HP: %d",iBonusHp);
								fShowMessagePickUpItem(idUserTouch,szShowMessageLoot,205,92,92,enHealth);
							}
							case 1:
							{
								new iMaxArmor = clAr:getRaceMaxArmor(idUserTouch);
								new CsArmorType:tArmor;
								new iCurrentArmor =  clAr:getUserArmor(idUserTouch,tArmor);
								new iBonusArmor = get_pcvar_num(CVAR_wc3_loot_items_armor);
								
								if((iCurrentArmor + iBonusArmor) > iMaxArmor)
									clAr:setUserArmor(idUserTouch,iMaxArmor);
								else
									clAr:setUserArmor(idUserTouch,iCurrentArmor + iBonusArmor);

								format(szShowMessageLoot, charsmax(szShowMessageLoot), "+AR: %d",iBonusArmor);
								fShowMessagePickUpItem(idUserTouch,szShowMessageLoot,0,255,127,enArmor);
							}
							case 2:
							{
								new iLevel = arrIntData[idUserTouch][P_LEVEL];
								new iBonusXP = XP_GivenByLevel( iLevel );
								XP_Give( idUserTouch, iBonusXP );
							
								format(szShowMessageLoot, charsmax(szShowMessageLoot), "+XP: %d",iBonusXP);
								fShowMessagePickUpItem(idUserTouch,szShowMessageLoot,188,143,143,enXP);
							
							}
						}
					}
			
					ArrayDeleteItem(arrIntTotalLootEntity,i);
					ArrayDeleteItem(arrIntOriginsLootX,i);
					ArrayDeleteItem(arrIntOriginsLootY,i);
					ArrayDeleteItem(arrIntOriginsLootZ,i);
					ArrayDeleteItem(arrIntItemVictimShop1,i);
					ArrayDeleteItem(arrIntItemVictimShop2,i);
					ArrayDeleteItem(arrIntItemVictimShop3,i);
					ArrayDeleteItem(arrIntDrawSpriteItems,i);
					ArrayDeleteItem(arrIntScaleSpriteItems,i);
					
					if (get_pcvar_num( CVAR_wc3_loot_remove ) == 1)
						ArrayDeleteItem(arrIntLootRemove,i);
					
					
					break;
				}
			}
		}//if (equali(classname, "war3ft_loot_items"))
	}//if(get_pcvar_num( CVAR_wc3_loot_items ) > 0)
	
	//Для talisman +
	touchPlayerTalisman(idEntityTouched, idUserTouch);

	return FMRES_IGNORED
}