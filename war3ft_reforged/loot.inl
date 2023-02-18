
public fRemoveAllItems()
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
		ArrayClear(arrIntDrawSpriteItems);
		ArrayClear(arrIntScaleSpriteItems);

		if (get_pcvar_num( CVAR_wc3_loot_remove ) == 1)
				ArrayClear(arrIntLootRemove);
	}
	
}




public fCreateBonusClass(idUser)
{
	// get origin
	new Float:origin[3];
	pev(idUser, pev_origin, origin);

	new ent = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	if (!ent) return -1;

	// Set data
	set_pev(ent, pev_classname, szClassNameItems);
	set_pev(ent, pev_solid, SOLID_TRIGGER);
	set_pev(ent, pev_movetype, MOVETYPE_TOSS);      //#define	MOVETYPE_TOSS 6 gravity/collisions
	set_pev(ent, pev_sequence, 0);
	set_pev(ent, pev_frame, 0.0);
	set_pev(ent, pev_owner, idUser);

	
	// Set size
//	new Float:mins[3] = { -20.0, -20.0, 0.0 };
//	new Float:maxs[3] = { 20.0, 20.0, 30.0 };
//	engfunc(EngFunc_SetSize, ent, mins, maxs);
	
	// Set model
	engfunc(EngFunc_SetModel, ent, szModelBonusItems);

	// Set position
	set_pev(ent, pev_origin, origin);
		
	/* 
//	fm_set_rendering(ent,kRenderFxGlowShell,arrColorItemsRGB[0],arrColorItemsRGB[1],arrColorItemsRGB[2],kRenderTransAlpha, 128);
	fm_set_rendering(ent,kRenderFxGlowShell,arrColorItemsRGB[0],arrColorItemsRGB[1],arrColorItemsRGB[2],kRenderNormal, 128);
	*/ 
	
	
	ArrayPushCell(arrIntTotalLootEntity, ent);
	ArrayPushCell(arrIntOriginsLootX, FloatToNum(origin[0]));
	ArrayPushCell(arrIntOriginsLootY, FloatToNum(origin[1]));
	ArrayPushCell(arrIntOriginsLootZ, FloatToNum(origin[2] + 10));

	return -1;
}

public fCreateItemsClass(idUser)
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
		
	/*
//	fm_set_rendering(ent,kRenderFxGlowShell,arrColorItemsRGB[0],arrColorItemsRGB[1],arrColorItemsRGB[2],kRenderTransAlpha, 128);
	fm_set_rendering(ent,kRenderFxGlowShell,arrColorItemsRGB[0],arrColorItemsRGB[1],arrColorItemsRGB[2],kRenderNormal, 128);
	*/
	
	ArrayPushCell(arrIntTotalLootEntity, ent);
	ArrayPushCell(arrIntOriginsLootX, FloatToNum(origin[0]));
	ArrayPushCell(arrIntOriginsLootY, FloatToNum(origin[1]));
	ArrayPushCell(arrIntOriginsLootZ, FloatToNum(origin[2] + 10));


	return -1;
}


stock bIsItemUserSlot(idUser,iSlot)
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
	if(ITEM_Has( idUser, ITEM_MINE ) == iSlot && ITEM_HasItem( idUser, ITEM_MINE ) == ITEM_MINE )
		iVictimItemShop = ITEM_MINE;

	return iVictimItemShop;
}

stock fm_set_rendering(entity, fx = kRenderFxNone, r = 255, g = 255, b = 255, render = kRenderNormal, amount = 16) 
{
	new Float:RenderColor[3];
	RenderColor[0] = float(r);
	RenderColor[1] = float(g);
	RenderColor[2] = float(b);

	set_pev(entity, pev_renderfx, fx);
	set_pev(entity, pev_rendercolor, RenderColor);
	set_pev(entity, pev_rendermode, render);
	set_pev(entity, pev_renderamt, float(amount));

	return 1;
}

stock fDrawSprite(idUser,iLoot,iSprite,iScale)
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



stock fColorItems(iItemVictimShop1,iItemVictimShop2)
{
	new bIsDropItems = 2;
	
	if(iItemVictimShop1 != ITEM_NONE)
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
	
	if(iItemVictimShop2 != ITEM_NONE)
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

	
	if(bIsDropItems == 0)
	{
		arrColorItemsRGB[0] = 30;
		arrColorItemsRGB[1] = 144;
		arrColorItemsRGB[2] = 255;
		return arrColorItemsRGB;
	}	
	
	return arrColorItemsRGB;
}



stock fIsDropItems(iItemVictimShop1,iItemVictimShop2)
{
	new bIsDropItems = 2;

	if(iItemVictimShop1 == ITEM_NONE)
		bIsDropItems -= 1;

	if(iItemVictimShop2 == ITEM_NONE)
		bIsDropItems -= 1;



	if(bIsDropItems == 0)
		return bIsDropItems;

	return bIsDropItems;
}


stock fShowMsgPickUpItem(idUserTouch,szShowMessage[256],iRed,iGreen,iBlue)
{
	set_hudmessage(iRed,iGreen,iBlue,0.85,0.5,0,0.0,5.0,0.02,0.02,-1);
	ShowSyncHudMsg(idUserTouch, msgSyncObj,szShowMessage);
}



stock fShowMessagePickUpItem(idUserTouch,szShowMessage[256],iRed,iGreen,iBlue,iTypeLoot)
{
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
		
public fRemoveLootItem(idEntLootItem)
{
	if(!is_valid_ent(idEntLootItem))
		return;
		
	entity_set_int(idEntLootItem, EV_INT_movetype, MOVETYPE_FLY);
	entity_set_int(idEntLootItem, EV_INT_rendermode, kRenderTransAlpha);
	entity_set_int(idEntLootItem, EV_INT_renderfx, kRenderFxGlowShell);
	entity_set_float(idEntLootItem, EV_FL_renderamt, 255.0);
	//entity_set_vector(idEntLootItem, EV_VEC_rendercolor, Float:{255.0, 255.0, 0.0});
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



/* Remove or Activate the Fly Sprite 
public client_PostThink(idUser)
{
	if(get_pcvar_num( CVAR_wc3_loot_items ) > 0)
	{
		if (!is_user_alive(idUser) || ArraySize(arrIntTotalLootEntity) == 0) return;

		for (new i = 0; i < ArraySize(arrIntTotalLootEntity); i++)
		{
			new iSprite = ArrayGetCell(arrIntDrawSpriteItems, i);
			new iScale = ArrayGetCell(arrIntScaleSpriteItems, i);
			fDrawSprite(idUser,i,iSprite,iScale);
		}
	}
	
	return;
}
*/

public FM_Player_Touch(idEntityTouched, idUserTouch)
{ 
	if(get_pcvar_num( CVAR_wc3_loot_items ) > 0)
	{
		if (!pev_valid(idEntityTouched) || !is_user_alive(idUserTouch))
			return FMRES_IGNORED
		
		new classname[32]
		pev(idEntityTouched, pev_classname, classname, sizeof classname - 1)
		
		new iSumMoney = 0;
		
		if (equali(classname, "war3ft_loot_items"))
		{
			for (new i = 0; i < ArraySize(arrIntTotalLootEntity); i++)
			{
				if(idEntityTouched == ArrayGetCell(arrIntTotalLootEntity, i))
				{
					new entLoot = ArrayGetCell(arrIntTotalLootEntity, i);
					if (is_valid_ent(entLoot)) 
						engfunc(EngFunc_RemoveEntity, entLoot);
					
					
					Create_ScreenFade( idUserTouch, (1<<10), (1<<10), (1<<12), 255, 200, 0, 160 );
					emit_sound(idUserTouch, CHAN_AUTO, g_szSounds[SOUND_BUY], 1.0, ATTN_NORM, 0, PITCH_NORM );
					
					
					new iItemVictimShop1 = ArrayGetCell(arrIntItemVictimShop1, i);
					new iItemVictimShop2 = ArrayGetCell(arrIntItemVictimShop2, i);
					new bIsDropItems = 2;
					new szShowMessageLoot[256];
					
					if(iItemVictimShop1 != ITEM_NONE)
					{
							if(ITEM_GetSlot( idUserTouch ) != ITEM_SLOT_FULL && 
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_ONE) != iItemVictimShop1 &&
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_TWO) != iItemVictimShop1)
							{
								
								ITEM_GiveItem( idUserTouch, iItemVictimShop1);
							}
							else
							{
								
								new iItemMoneyDrop1 = ITEM_Cost( idUserTouch, iItemVictimShop1 );
								iSumMoney += iItemMoneyDrop1;
							}
					}
					else
					{
						bIsDropItems -= 1;
					}
					
					if(iItemVictimShop2 != ITEM_NONE)
					{
							if(ITEM_GetSlot( idUserTouch ) != ITEM_SLOT_FULL && 
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_ONE) != iItemVictimShop2 &&
								bIsItemUserSlot(idUserTouch,ITEM_SLOT_TWO) != iItemVictimShop2)
							{
								ITEM_GiveItem( idUserTouch, iItemVictimShop2 );
							}
							else
							{
								
								new iItemMoneyDrop2 = ITEM_Cost( idUserTouch, iItemVictimShop2 );
								iSumMoney += iItemMoneyDrop2;
							}
					}
					else
					{
						bIsDropItems -= 1;
					}
					
					
					
					if(iSumMoney > 0)
					{
						SHARED_SetUserMoney( idUserTouch,SHARED_GetUserMoney( idUserTouch ) + iSumMoney, 1 );
								
						format(szShowMessageLoot, charsmax(szShowMessageLoot), "+$: %d",iSumMoney);
						fShowMessagePickUpItem(idUserTouch,szShowMessageLoot,188,143,143,enMoney);
					}
					
					
					if(bIsDropItems == 0)
					{
								
						switch(random_num(0, 2))
						{
							case 0:
							{
								new iNumHealth = get_pcvar_num(CVAR_wc3_loot_items_health);
								new iUserTouchHealth = SHARED_GetUserHealth(idUserTouch);
								if( (iUserTouchHealth + iNumHealth) > 255)
									SHARED_SetUserHealth( idUserTouch,255);
								else
									SHARED_SetUserHealth( idUserTouch,iUserTouchHealth + iNumHealth);
								
								format(szShowMessageLoot, charsmax(szShowMessageLoot), "+HP: %d",iNumHealth);
								fShowMessagePickUpItem(idUserTouch,szShowMessageLoot,255,100,100,enHealth);
							}
							case 1:
							{	
								
								new iNumArmor = get_pcvar_num(CVAR_wc3_loot_items_armor);
								static CsArmorType:tArmor;
								new iUserTouchArmor = cs_get_user_armor(idUserTouch, tArmor);
								if( (iUserTouchArmor + iNumArmor) > 255)	
									cs_set_user_armor(idUserTouch, 255, tArmor);
								else
									cs_set_user_armor(idUserTouch, iUserTouchArmor + iNumArmor, tArmor);
								
								format(szShowMessageLoot, charsmax(szShowMessageLoot), "+AP: %d",iNumArmor);
								fShowMessagePickUpItem(idUserTouch,szShowMessageLoot,100,255,255,enArmor);
							
													
							}
							case 2:
							{
								new iLevel = p_data[idUserTouch][P_LEVEL];
								new iBonusXP = XP_GivenByLevel( iLevel ) + 5;
								XP_Give( idUserTouch, iBonusXP );
							
								format(szShowMessageLoot, charsmax(szShowMessageLoot), "+XP: %d",iBonusXP);
								fShowMessagePickUpItem(idUserTouch,szShowMessageLoot,200,200,200,enXP);
							
							}
						}
					}
			
					ArrayDeleteItem(arrIntTotalLootEntity,i);
					ArrayDeleteItem(arrIntOriginsLootX,i);
					ArrayDeleteItem(arrIntOriginsLootY,i);
					ArrayDeleteItem(arrIntOriginsLootZ,i);
					ArrayDeleteItem(arrIntItemVictimShop1,i);
					ArrayDeleteItem(arrIntItemVictimShop2,i);
					ArrayDeleteItem(arrIntDrawSpriteItems,i);
					ArrayDeleteItem(arrIntScaleSpriteItems,i);
					
					if (get_pcvar_num( CVAR_wc3_loot_remove ) == 1)
						ArrayDeleteItem(arrIntLootRemove,i);
					
					
					break;
				}
			}
		}
	}
	
	return FMRES_IGNORED
}

stock FloatToNum(Float:floatn)
{
	new str[64], num;
	float_to_str(floatn, str, 63);
	num = str_to_num(str);
	
	return num
}