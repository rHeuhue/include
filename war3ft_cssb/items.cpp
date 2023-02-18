/*
*	Item Functions
*/
//Цены на предметы
ITEM_InitCost()
{
	ITEM_COST[ITEM_ANKH]	    = get_pcvar_num( CVAR_wc3_cost_ankh );	// Ankh of Reincarnation
	ITEM_COST[ITEM_BOOTS]       = get_pcvar_num( CVAR_wc3_cost_boots_of_speed );			// Boots of Speed
	ITEM_COST[ITEM_CLAWS]	    = get_pcvar_num( CVAR_wc3_cost_claws_of_attack );			// Claws of Attack
	ITEM_COST[ITEM_CLOAK]	    = get_pcvar_num( CVAR_wc3_cost_cloak_of_shadows );			// Cloak of Shadows
	ITEM_COST[ITEM_MASK]	    = get_pcvar_num( CVAR_wc3_cost_mask_of_death );			// Mask of Death
	ITEM_COST[ITEM_NECKLACE]	= get_pcvar_num( CVAR_wc3_cost_necklace );			// Necklace of Immunity
	ITEM_COST[ITEM_FROST]	    = get_pcvar_num( CVAR_wc3_cost_orb_of_frost );			// Orb of Frost
	ITEM_COST[ITEM_HEALTH]	    = get_pcvar_num( CVAR_wc3_cost_health );			// Periapt of Health
	ITEM_COST[ITEM_TOME]	    = get_pcvar_num( CVAR_wc3_cost_tome );			// Tome of Experience
	ITEM_COST[ITEM_SCROLL]	    = get_pcvar_num( CVAR_wc3_cost_scroll );			// Scroll of Respawning
	ITEM_COST[ITEM_PROTECTANT]	= get_pcvar_num( CVAR_wc3_cost_mole_protect );			// Mole Protectant
	ITEM_COST[ITEM_HELM]	    = get_pcvar_num( CVAR_wc3_cost_helm );			// Helm of Excellence
	ITEM_COST[ITEM_AMULET]	    = get_pcvar_num( CVAR_wc3_cost_amulet_cat );			// Amulet of the Cat
	ITEM_COST[ITEM_SOCK]	    = get_pcvar_num( CVAR_wc3_cost_sock );			// Sock of the Feather
	ITEM_COST[ITEM_GLOVES]	    = get_pcvar_num( CVAR_wc3_cost_flaming_gloves );			// Flaming Gloves of Warmth
	ITEM_COST[ITEM_RING]	    = get_pcvar_num( CVAR_wc3_cost_ring );			// Ring of Regeneration + 1
	ITEM_COST[ITEM_CHAMELEON]	= get_pcvar_num( CVAR_wc3_cost_chameleon );			// Chameleon
	ITEM_COST[ITEM_MOLE]	    = get_pcvar_num( CVAR_wc3_cost_mole );		// Mole
	//Для shopmenu3
	ITEM_COST[ITEM_INTELLECT]	    = get_pcvar_num( CVAR_wc3_cost_intellect );		// Intellect
	ITEM_COST[ITEM_GRENADE_PROTECTION]	= get_pcvar_num( CVAR_wc3_cost_he_protect );	// Grenade Protection
	ITEM_COST[ITEM_MIRROR_SHIELD]	    = get_pcvar_num( CVAR_wc3_cost_mirror_shield );	// Mirror Shield
	ITEM_COST[ITEM_ESP]					= get_pcvar_num( CVAR_wc3_cost_esp );	// ESP
	ITEM_COST[ITEM_FROST_ARMOR]			= get_pcvar_num( CVAR_wc3_cost_frost_armor );	// Frost Armor
	ITEM_COST[ITEM_DEATH_TOUCH]			= get_pcvar_num( CVAR_wc3_cost_death_touch );	//Death's Touch
	ITEM_COST[ITEM_HEALTH_POTION]	    = get_pcvar_num( CVAR_wc3_cost_health_potion );	// Health Potion
	ITEM_COST[ITEM_ULTIMATE_TIMER_DIVIDER]	= get_pcvar_num( CVAR_wc3_cost_ult_timer );	// Ultimate Timer Divider
	ITEM_COST[ITEM_STEEL_SKIN]   = get_pcvar_num( CVAR_wc3_cost_steel_skin );				// Steel Skin

	//Для shopmenu4
	sm4_ITEM_InitCost();

}

// Item Setup Functions
ITEM_Init()
{	
	// Items are chargeable
	//Предметы с зарядами
	g_iFlag[ITEM_NECKLACE]	|= ITEM_CHARGEABLE;
	g_iFlag[ITEM_HELM]		|= ITEM_CHARGEABLE;
	g_iFlag[ITEM_RING]		|= ITEM_CHARGEABLE;

	//Для shopmenu3
	g_iFlag[ITEM_GRENADE_PROTECTION] |= ITEM_CHARGEABLE;
	g_iFlag[ITEM_DEATH_TOUCH] |= ITEM_CHARGEABLE;

	//Для shopmenu4
	g_iFlag[ITEM_DEVOURER_LIGHT] |= ITEM_CHARGEABLE;
	g_iFlag[ITEM_MIRROR_ULTIMATE] |= ITEM_CHARGEABLE;
	g_iFlag[ITEM_DEATHCOIL] |= ITEM_CHARGEABLE;
	g_iFlag[ITEM_IMPALE] |= ITEM_CHARGEABLE;
	g_iFlag[ITEM_SLEEP] |= ITEM_CHARGEABLE;
	g_iFlag[ITEM_BOOK_DEAD] |= ITEM_USEONBUY;
	g_iFlag[ITEM_TRANQUILITY] |= ITEM_USEONBUY;

	// Items should be used when bought
	//Предмет используется сразу при покупке
	g_iFlag[ITEM_TOME]		|= ITEM_USEONBUY;
	g_iFlag[ITEM_HEALTH_POTION]		|= ITEM_USEONBUY;
	g_iFlag[ITEM_STEEL_SKIN]		|= ITEM_USEONBUY;

	// Items CAN be bought when dead
	//Предметы может покупать когда мертв
//	g_iFlag[ITEM_ANKH]		|= ITEM_CHARGEABLE;
	g_iFlag[ITEM_ANKH]		|= ITEM_BUYWHENDEAD;
	g_iFlag[ITEM_SCROLL]	|= ITEM_BUYWHENDEAD;
	g_iFlag[ITEM_MOLE]		|= ITEM_BUYWHENDEAD;
	g_iFlag[ITEM_TOME]		|= ITEM_BUYWHENDEAD;

	// Items are used when the next round starts...
	//Предметы используются когда стартует следующий раунд
	g_iFlag[ITEM_ANKH]		|= ITEM_NEXTROUNDUSE;
	g_iFlag[ITEM_MOLE]		|= ITEM_NEXTROUNDUSE;
}

// We created this to allow for different prices of items at different levels
public ITEM_Cost( idUser, iItem )
{
		

	// How much should ratio increase per level?
	//Насколько отношение должно увеличиться за уровень?
	new Float:fInc = ( 1.0 - ITEM_COST_RATIO ) / float( iMaxLevels );

	// Cost * ratio (ITEM_COST_RATIO to 1.0 dependent on level)
	// Стоимость * отношение (ITEM_COST_RATIO к 1.0 зависящий на уровне)
	new Float:fRatio = (float( arrIntData[idUser][P_LEVEL] ) * fInc) + ITEM_COST_RATIO;
		
	//Сниженные цены для админов и VIP игроков
	new Float:fPercent = get_pcvar_float(CVAR_wc3_cost_percent_vip);

	if((get_user_flags(idUser) & fBuyItemCost()))
		return ( arrIntData[idUser][P_RACE] != RACE_NONE ) ? floatround( (float( ITEM_COST[iItem] ) * fRatio) * fPercent ) : ITEM_COST[iItem];

	return ( arrIntData[idUser][P_RACE] != RACE_NONE ) ? floatround( float( ITEM_COST[iItem] ) * fRatio ) : ITEM_COST[iItem];
}

//Для авто закупки предметов
ITEM_CanBuy(idUser,iItem, bool:bIsAutoBuy = false )
{

	

	//Ограничение на покупку предмета "прикосновение смерти"
	new iNumPlayers = get_playersnum();

	// User doesn't have the money
	if ( SHARED_GetUserMoney( idUser ) < ITEM_Cost( idUser, iItem ) )
	{
		if(!bIsAutoBuy)
		{
			client_print( idUser, print_center, "%L", LANG_PLAYER, "INSUFFICIENT_FUNDS" );
			client_cmd(idUser, "speak %s", arrStrSounds[SOUND_NO_GOLD] );
		}

		return false;
	}
	// User already owns the item and it's not a chargeable item!
	else if ( ITEM_Has( idUser, iItem ) > ITEM_NONE && !ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
	{
		if(!bIsAutoBuy)
			client_print( idUser, print_center, "%L", LANG_PLAYER, "ALREADY_OWN_THAT_ITEM" );

		return false;
	}
	
	// Make sure these items can be bought if the user is dead
	else if ( !is_user_alive( idUser ) && !ITEM_CheckFlag( iItem, ITEM_BUYWHENDEAD ) ) 
	{
		if(!bIsAutoBuy)
			client_print( idUser, print_center, "%L", LANG_PLAYER, "NOT_PURCHASE_WHEN_DEAD" );

		return false;
	}
	
	// User has necklace + blink, they don't need a necklace
	else if ( iItem == ITEM_NECKLACE && arrBoolData[idUser][PB_WARDENBLINK] )
	{
		if(!bIsAutoBuy)
			client_print( idUser, print_center, "%L", LANG_PLAYER, "CLIENT_PRINT_ITEM_CAN_BUY_0" );

		return false;
	}

	// Запрет покупки предмета "Защита от HE"
	else if ( iItem == ITEM_GRENADE_PROTECTION && arrBoolData[idUser][PB_KINETIC_FIELD] )
	{
		if(!bIsAutoBuy)
			client_print( idUser, print_center, "%L", LANG_PLAYER, "CLIENT_PRINT_ITEM_CAN_BUY_3" );

		return false;
	}


	// User doesn't need an ankh if they're going to reincarnate
	else if ( iItem == ITEM_ANKH && SM_GetSkillLevel( idUser, SKILL_REINCARNATION ) == 3 && !arrIntData[idUser][P_CHANGERACE] && arrIntData[idUser][P_RACE] != RACE_CHAMELEON )
	{
		if(!bIsAutoBuy)
			client_print( idUser, print_center, "%L", LANG_PLAYER, "CLIENT_PRINT_ITEM_CAN_BUY_1" );

		return false;
	}
	
	// User has purchased the maximum allowed rings
	else if ( g_iTotalRings[idUser] >= 5 && iItem == ITEM_RING )
	{
		if(!bIsAutoBuy)
			client_print( idUser, print_center, "%L", LANG_PLAYER, "NOT_PURCHASE_MORE_THAN_FIVE_RINGS" );

		return false;
	}

	// User is already going to reincarnate weapons because they bought an ankh earlier (probably lost it when died)
	else if ( ( iItem == ITEM_ANKH && g_bPlayerBoughtAnkh[idUser] ) || ( iItem == ITEM_MOLE && g_bPlayerBoughtMole[idUser] ) )
	{
		if(!bIsAutoBuy)
			client_print( idUser, print_center, "%L", LANG_PLAYER, "ALREADY_OWN_THAT_ITEM" );

		return false;
	}



	//Ограничение на покупку предмета Прикосновение смерти
	else if ( ( iItem == ITEM_DEATH_TOUCH && arrIsByuItemOneRound[idUser][iItem] == BUY_ITEM_ONE_ROUND_DEATH_TOUCH ))
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LIMIT_BUY_ONE_ROUND",BUY_ITEM_ONE_ROUND_DEATH_TOUCH);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}

	//Ограничение на покупку предмета Микстура здоровья
	else if ( ( iItem == ITEM_HEALTH_POTION && arrIsByuItemOneRound[idUser][iItem] == BUY_ITEM_ONE_ROUND_HEALTH_POTION ))
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LIMIT_BUY_ONE_ROUND",BUY_ITEM_ONE_ROUND_HEALTH_POTION);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}

	//Ограничение на покупку предмета Стальная кожа
	else if ( ( iItem == ITEM_STEEL_SKIN && arrIsByuItemOneRound[idUser][iItem] == BUY_ITEM_ONE_ROUND_STEEL_SKIN ))
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LIMIT_BUY_ONE_ROUND",BUY_ITEM_ONE_ROUND_STEEL_SKIN);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}

	//Заблокирован ли предмет на карте
	new szItemName[32];
	if(isDisabledItemOnMap(idUser,iItem,szItemName) == true)
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ITEM_DISABLED_ON_MAP",szItemName);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}

	//Заблокирован ли предмет для Расы
	if(isDisabledItemRace(idUser,iItem,szItemName) == true)
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_ITEM_BLOCK",szItemName);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}

	//Если покупатель предмета сам является скелетом
	if(sm4_IsPlayerSkeleton(idUser) == true)
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_NO_BUY_SKELETON");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}
	//Ограничение на покупку предмета Книга мертвых
	else if ( ( iItem == ITEM_BOOK_DEAD && arrIsByuItemOneRound[idUser][iItem] == BUY_ITEM_ONE_ROUND_BOOK_DEAD ))
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LIMIT_BUY_ONE_ROUND",BUY_ITEM_ONE_ROUND_BOOK_DEAD);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}
	//Ограничение на покупку предмета Спокойствие
	else if ( ( iItem == ITEM_TRANQUILITY && arrIsByuItemOneRound[idUser][iItem] == BUY_ITEM_ONE_ROUND_TRANQUILITY ))
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LIMIT_BUY_ONE_ROUND",BUY_ITEM_ONE_ROUND_TRANQUILITY);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}
	else if( iItem == ITEM_TRANQUILITY && arrPlayerInfo[idUser][fCurrentSpeed] > MAX_CASTING_VELOCITY)
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_NO_MOVING_TRANQUILITY");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}
	else if( (iItem == ITEM_TRANQUILITY && arrPlayerInfo[idUser][bCastingSpell] == true) || ( iItem == ITEM_TRANQUILITY && task_exists( TASK_TRANQUILITY + idUser )) )
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_NO_BUY_TRANQUILITY");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}
	else if ( ( iItem == ITEM_DEATH_TOUCH && iNumPlayers < BUY_ITEM_MIN_PLAYERS_DEATH_TOUCH))
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MIN_PLAYERS",BUY_ITEM_MIN_PLAYERS_DEATH_TOUCH);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		return false;
	}
	//Ограничение на покупку предмета Scroll of Respawning
	else if ( ( iItem == ITEM_SCROLL && arrIsByuItemOneRound[idUser][iItem] >= BUY_ITEM_ONE_ROUND_ITEM_SCROLL ))
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LIMIT_BUY_ONE_ROUND",BUY_ITEM_ONE_ROUND_ITEM_SCROLL);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}
	//Ограничение на покупку предмета Огненные перчатки
	else if ( ( iItem == ITEM_GLOVES && 
				arrIsByuItemOneRound[idUser][iItem] == BUY_ITEM_ONE_ROUND_ITEM_GLOVES && 
				arrIntData[idUser][P_RACE] == RACE_ORC))
	{
		if(!bIsAutoBuy)
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_LIMIT_BUY_ONE_ROUND",BUY_ITEM_ONE_ROUND_ITEM_GLOVES);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		return false;
	}

	client_cmd(idUser, "speak %s",arrStrSounds[SOUND_BUY_ITEMS], 1.0, ATTN_NORM, 0, PITCH_NORM ); 
	
	return true;
}
//Для авто закупки предметов
ITEM_Buy( idUser, iItem, bool:bIsAutoBuy = false )
{
	
	

	// If the user can buy this item...
	if ( ITEM_CanBuy( idUser,iItem,bIsAutoBuy ) )
	{

		// User's items are full
		if ( ITEM_GetSlot( idUser ) == ITEM_SLOT_FULL && !ITEM_CheckFlag( iItem, ITEM_USEONBUY ) )
		{

			// We only care about items being full if this item isn't a use on buy
			if ( !ITEM_CheckFlag( iItem, ITEM_USEONBUY ) )
			{
				new bool:bShowReplaceMenu = false;

				// One time use...
				if ( !ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
				{
					//client_print( idUser, print_chat, "[DEBUG] Item is not chargeable" );

					bShowReplaceMenu = true;
				}

				// We also need to replace it if the item is chargeable but they don't own that item
				if ( ITEM_Has( idUser, iItem ) == ITEM_NONE && ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
				{
					//client_print( idUser, print_chat, "[DEBUG] Doesn't have item and new item is chargeable" );

					bShowReplaceMenu = true;
				}

				if ( bShowReplaceMenu )
				{
					g_iFutureItem[idUser] = iItem;

					MENU_ReplaceItem( idUser );

					return;
				}
			}
		}
	
		// Remove user's money
		new iNewMoney = SHARED_GetUserMoney( idUser ) - ITEM_Cost( idUser, iItem );
		SHARED_SetUserMoney( idUser, iNewMoney );

		ITEM_GiveItem( idUser, iItem );
	}

	return;
}

// Item Buy Functions
bool:ITEM_MenuCanBuyCheck( idUser )
{
	

	// Duh how can they buy if they're dead!
	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return false;

	new isPlayerAlive		= is_user_alive( idUser );
	if ( !get_pcvar_num( CVAR_wc3_buy_dead ) && !isPlayerAlive )
	{
		client_print( idUser, print_center, "%L", LANG_PLAYER, "NOT_BUY_ITEMS_WHEN_DEAD" );
		
		return false;
	}

	new isPlayerInBuyZone	= cs_get_user_buyzone( idUser )
	if ( get_pcvar_num( CVAR_wc3_buy_time ) && !g_buyTime )
	{
		client_print( idUser, print_center, "%0.0f %L",(get_cvar_float( "mp_buytime" ) * 60.0 ), LANG_PLAYER, "SECONDS_HAVE_PASSED_CANT_BUY");
												
		return false;
	}
	else if ( get_pcvar_num( CVAR_wc3_buy_zone ) && !isPlayerInBuyZone && isPlayerAlive )
	{
		client_print( idUser, print_center, "%L", LANG_PLAYER, "MUST_BE_IN_BUYZONE" );
		
		return false;
	}

	
	return true;
}

// Item Preset Function
public ITEM_GiveItem(idUser,iItem)
{
		

	//Заблокирован ли предмет для Расы
	new szItemName[32];
	if(isDisabledItemRace(idUser,iItem,szItemName) == true)
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_ITEM_BLOCK",szItemName);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		return;
	}


	// This item we should use instantly
	if ( ITEM_CheckFlag( iItem, ITEM_USEONBUY ) )
	{
		if ( iItem == ITEM_TOME )
		{
			ITEM_Tome( idUser );
			return;
		}

		if (iItem == ITEM_HEALTH_POTION)
		{
			ITEM_HealthPotion(idUser,iItem);
			return;
		}

		if ( iItem == ITEM_STEEL_SKIN )
		{
			ITEM_SteelSkin(idUser,iItem);
			return;
		}

		//Для shopmenu4
		if ( iItem == ITEM_BOOK_DEAD )
		{
			sm4_ITEM_Book_Dead(idUser,iItem);
			return;
		}
		if ( iItem == ITEM_TRANQUILITY )
		{
			sm4_4_9_Tranquility( idUser,iItem );
			return;
		}
		
	}

	// They are just adding some charges
	else
	{
		// Actually set our item variable
		if ( is_user_alive( idUser ) )
		{
			ITEM_Equip( idUser, iItem );
		}

		// Display message to the user regarding the item they just purchased
		ITEM_DisplayMessage( idUser, iItem );

		// Give bonuses
		ITEM_GiveBonuses( idUser, iItem );

		// Play purchase sound
		emit_sound( idUser, CHAN_STATIC, arrStrSounds[SOUND_PICKUPITEM], 1.0, ATTN_NORM, 0, PITCH_NORM );
	}

	WC3_ShowBar( idUser );

	return;
}

ITEM_DisplayMessage( idUser, iItem )
{
		

	// Display a message regarding the item they just purchased
	switch ( iItem )
	{
		case ITEM_ANKH:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU_1");				
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_BOOTS:
		{
			format(szMessage, charsmax(szMessage), "%L %0.1f%%",LANG_PLAYER,"INFO_SHOPMENU_2",((get_pcvar_float(CVAR_wc3_boots)) * 100.00 ));	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_CLAWS:
		{
			format(szMessage, charsmax(szMessage), "%L %d",LANG_PLAYER,"INFO_SHOPMENU_3",get_pcvar_num(CVAR_wc3_claw));	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_CLOAK:
		{
			new Float:fInvis = 100.0 * ( float( get_pcvar_num( CVAR_wc3_cloak ) ) / 255.0 );
			
			format(szMessage, charsmax(szMessage), "%L %0.1f%%",LANG_PLAYER,"INFO_SHOPMENU_4",fInvis);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_MASK:
		{
			new Float:fMask = (100.0 * get_pcvar_float(CVAR_wc3_mask));
		
			format(szMessage, charsmax(szMessage), "%L %0.1f%%",LANG_PLAYER,"INFO_SHOPMENU_5",fMask);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_NECKLACE:
		{
			format(szMessage, charsmax(szMessage), "%L %d",LANG_PLAYER,"INFO_SHOPMENU_6",iBaseNecklaceCharges);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_FROST:
		{
			new Float:fFrost = 100.0 * (get_pcvar_float(CVAR_wc3_frost) / 260.0);
			
			format(szMessage, charsmax(szMessage), "%L %0.1f%%",LANG_PLAYER,"INFO_SHOPMENU_7",fFrost);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_HEALTH:
		{
			format(szMessage, charsmax(szMessage), "%L %d",LANG_PLAYER,"INFO_SHOPMENU_8",get_pcvar_num(CVAR_wc3_health));	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_SCROLL:
		{
			if (is_user_alive(idUser))
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU2_1");	
			else
				format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU2_1_DEAD");	
						
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_PROTECTANT:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU2_2");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_HELM:
		{
			format(szMessage, charsmax(szMessage), "%L %d",LANG_PLAYER,"INFO_SHOPMENU2_3",iBaseHelmCharges);	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_AMULET:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU2_4");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_SOCK:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU2_5");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

		case ITEM_GLOVES:
		{
			format(szMessage, charsmax(szMessage), "%L %d %L",LANG_PLAYER,"INFO_SHOPMENU2_6",get_pcvar_num(CVAR_wc3_glove_timer),LANG_PLAYER,"WC3_SECONDS");	
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_RING:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU2_7");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_CHAMELEON:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU2_8");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_MOLE:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU2_9");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}		
		case ITEM_INTELLECT:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU3_1",BONUS_INTELLECT);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_GRENADE_PROTECTION:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU3_2");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_MIRROR_SHIELD:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU3_3",floatround(OFFENSIVE_MIRROR_SHIELD * 100),"%%",floatround(DEFENSIVE_MIRROR_SHIELD * 100),"%%");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_ESP:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU3_4");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_FROST_ARMOR:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU3_5",floatround(FROST_ARMOR_DAMAGE * ARMOR_RATIO),floatround(FROST_ARMOR_DAMAGE * ARMOR_BONUS));
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_DEATH_TOUCH:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU3_6");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}		
		case ITEM_ULTIMATE_TIMER_DIVIDER:
		{
			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU3_8",RESET_ULTIMATE_TIMER);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}		
	}
	
	sm4_ITEM_DisplayMessage( idUser, iItem );
}


// Give the user bonuses for their items (except charges)
ITEM_GiveAllBonuses(idUser)
{
		
	
	//Если изменяем на другой
	if(arrTalismanChange[idUser] != TALISMAN_ITEM_NONE)
	{
		arrTalismanActive[idUser] = arrTalismanChange[idUser];

	//	client_print(idUser,print_chat,"CHANGE GB: %d",arrTalismanChange[idUser]);

		fActivateTalismanPassive(idUser, arrTalismanChange[idUser]);

		arrTalismanChange[idUser] = TALISMAN_ITEM_NONE;

		SHARED_SetGravity(idUser);

		SHARED_SetSpeed(idUser);
	}
	else
	{
		fActivateTalismanPassive(idUser, arrTalismanActive[idUser]);

		//client_print(idUser,print_chat,"CURRENT GB: %d",arrTalismanActive[idUser]);
	}

	//client_print(0,print_chat,"ITEM_GiveAllBonuses: %d",arrTalismanActive[idUser]);

	// Loop through all item slots
	for ( new i = ITEM_SLOT_ONE; i <= ITEM_SLOT_THREE; i++ )
	{
		
		// Do we have a valid item here?
		if ( g_iShopMenuItems[idUser][i] != ITEM_NONE )
		{

			// Don't want to give the user more charges for free do we?
			//  And we don't want to give the bonuses if this is a next round use item (i.e. if we do then mole for infinity - that doesn't seem nice)
			if ( !ITEM_CheckFlag( g_iShopMenuItems[idUser][i], ITEM_CHARGEABLE ) && !ITEM_CheckFlag( g_iShopMenuItems[idUser][i], ITEM_NEXTROUNDUSE ) )
			{
				ITEM_GiveBonuses( idUser, g_iShopMenuItems[idUser][i] );
			}
		}
	}
}

// Give our players their bonus!
ITEM_GiveBonuses(idUser, iItem)
{
		

	// Display a message regarding the item they just purchased
	switch (iItem)
	{
		case ITEM_ANKH:
		{
			g_bPlayerBoughtAnkh[idUser] = true;
		}

		case ITEM_BOOTS:
		{
			SHARED_SetSpeed( idUser );
		}

		case ITEM_CLOAK:
		{
			SHARED_INVIS_Set( idUser );
		}

		case ITEM_NECKLACE:
		{
			g_iNecklaceCharges[idUser] += iBaseNecklaceCharges;
		}

		case ITEM_HEALTH:
		{	
			new iMaxHealth = clHP:getRaceMaxHealth(idUser);
			new iCurrentHealth =  clHP:getUserHealth(idUser);
			new iBonusHp = get_pcvar_num( CVAR_wc3_health );
			
			if((iCurrentHealth + iBonusHp) > iMaxHealth)
				clHP:setUserHealth(idUser,iMaxHealth);
			else
				clHP:setUserHealth(idUser,iCurrentHealth + iBonusHp);
				
		}

		case ITEM_SCROLL:
		{
			if ( !is_user_alive( idUser ) )
			{
				ITEM_Scroll( idUser );
			}
		}

		case ITEM_HELM:
		{
			g_iHelmCharges[idUser] += iBaseHelmCharges;
		}

		case ITEM_SOCK:
		{
			SHARED_SetGravity( idUser );
		}

		case ITEM_GLOVES:
		{
			ITEM_Gloves( idUser );
		}

		case ITEM_RING:
		{
			g_iTotalRings[idUser] += RING_INCREMENT;

			if ( !task_exists( TASK_ITEM_RING + idUser ) )
			{
				_ITEM_Ring( idUser );
			}
		}

		case ITEM_CHAMELEON:
		{
			SHARED_ChangeSkin( idUser, SKIN_SWITCH );
		}

		case ITEM_MOLE:
		{
			g_bPlayerBoughtMole[idUser] = true;
		}

		//Для shopmenu3
		case ITEM_INTELLECT:
		{
		}
		case ITEM_GRENADE_PROTECTION:
		{
			arriTotalRingsGrenadeProtection[idUser] += GRENADE_PROTECTION_CHARGES;
		}		
		case ITEM_ESP:
		{
			fEnableItemESP(idUser);
		}		
		case ITEM_DEATH_TOUCH:
		{
			arrDeathTouch[idUser] = true;
			arrIsByuItemOneRound[idUser][ITEM_DEATH_TOUCH]++;
		}		
	}

	//Для shopmenu4
	sm4_ITEM_GiveBonuses( idUser, iItem );
}

// Item Equip Function
ITEM_Equip( idUser, iItem )
{
	

	new iItemSlot = ITEM_GetSlot( idUser );

	// Items are not full
	if ( iItemSlot != ITEM_SLOT_FULL )
	{

		new iOldItem = g_iShopMenuItems[idUser][iItemSlot];

		if ( iItem == iOldItem || ITEM_Has( idUser, iItem ) > ITEM_NONE )
		{
			// Might hit this if we added charges - we want to update the user's HUD
			WC3_ShowBar( idUser );

			return;
		}

		// Remove the user's old item if necessary
		else if ( g_iShopMenuItems[idUser][iItemSlot] > ITEM_NONE )
		{
			ITEM_Remove( idUser, iItemSlot );
		}
			
		// Set their new item
		g_iShopMenuItems[idUser][iItemSlot] = iItem;
	
	}

	WC3_ShowBar( idUser );

	return;
}

// Item Remove Functions
ITEM_RemoveID( idUser, iItem )
{
		

	new iItemSlot = ITEM_Has( idUser, iItem );

	if ( iItemSlot > ITEM_NONE )
	{
		ITEM_Remove( idUser, iItemSlot );
	}

	return;
}

ITEM_Remove( idUser, iItemSlot, bResetAnkhMole = true )
{
	
	

	new iItem = g_iShopMenuItems[idUser][iItemSlot];

	g_iShopMenuItems[idUser][iItemSlot] = ITEM_NONE;

	switch( iItem )
	{
		case ITEM_ANKH:
		{
			if ( bResetAnkhMole )
			{
				g_bPlayerBoughtAnkh[idUser] = false;
			}
		}

		case ITEM_BOOTS:
		{
			SHARED_SetSpeed( idUser );
		}

		case ITEM_CLOAK:
		{
			SHARED_INVIS_Set( idUser );
		}

		case ITEM_NECKLACE:
		{
			g_iNecklaceCharges[idUser] = 0;
		}

		case ITEM_HEALTH:
		{
			new iCurrentHealth =  clHP:getUserHealth(idUser);
			new iNewHealth = iCurrentHealth - get_pcvar_num(CVAR_wc3_health);
			iNewHealth = ( ( iNewHealth <= 0 ) ? 1 : iNewHealth );

			clHP:setUserHealth(idUser,iNewHealth);

		}

		case ITEM_HELM:
		{
			g_iHelmCharges[idUser] = 0;
		}
		
		case ITEM_SOCK:
		{
			SHARED_SetGravity( idUser );
		}

		case ITEM_GLOVES:
		{
			if ( task_exists( TASK_ITEM_GLOVES + idUser ) )
			{
				remove_task( TASK_ITEM_GLOVES + idUser );
			}
		}

		case ITEM_RING:
		{
			if ( task_exists( TASK_ITEM_RING + idUser ) )
			{
				remove_task( TASK_ITEM_RING + idUser );
			}
			
			// Set the number of rings to 0
			g_iTotalRings[idUser] = 0;
		}

		case ITEM_CHAMELEON:
		{
			SHARED_ChangeSkin( idUser, SKIN_RESET );
		}

		case ITEM_MOLE:
		{
			if ( bResetAnkhMole )
			{
				g_bPlayerBoughtMole[idUser] = false;
			}
		}
		case ITEM_GRENADE_PROTECTION:
		{
			arriTotalRingsGrenadeProtection[idUser] = 0;
		}		
		case ITEM_ESP:
		{
			fDisableItemESP(idUser);
		}		
		case ITEM_DEATH_TOUCH:
		{
			arrDeathTouch[idUser] = false;
		}
		
	}

	//Для shopmenu4
	sm4_ITEM_Remove( idUser,iItem);

	WC3_ShowBar( idUser );

	return;
}

ITEM_RemoveCharge( idUser, iItem )
{
		

	//Для talisman +
	fTalismanRemoveCharge(idUser,iItem);

	if ( ITEM_Has( idUser, iItem ) > ITEM_NONE )//Есть ли предмет чтобы удалить заряд
	{
		switch ( iItem )
		{
			case ITEM_NECKLACE:
			{
				g_iNecklaceCharges[idUser] -= CHARGE_DISPOSE;
				
				if ( g_iNecklaceCharges[idUser] <= 0 )
				{
					ITEM_RemoveID( idUser, iItem );
				}
			}

			case ITEM_HELM:
			{
				g_iHelmCharges[idUser] -= CHARGE_DISPOSE;
				
				if ( g_iHelmCharges[idUser] <= 0 )
				{
					ITEM_RemoveID( idUser, iItem );
				}
			}

			case ITEM_RING:
			{
				g_iTotalRings[idUser] -= CHARGE_DISPOSE;
				
				if ( g_iTotalRings[idUser] <= 0 )
				{
					ITEM_RemoveID( idUser, iItem );
				}
			}
			//Для shopmenu3
			case ITEM_GRENADE_PROTECTION:
			{
				arriTotalRingsGrenadeProtection[idUser] -= CHARGE_DISPOSE;
				
				if (arriTotalRingsGrenadeProtection[idUser] <= 0 )
				{
					ITEM_RemoveID( idUser, iItem );
				}
			}
		}

		//Для shopmenu4
		sm4_ITEM_RemoveCharge(idUser,iItem);
	}

	WC3_ShowBar( idUser );

	return;
}


//Проверка свободен ли слот
// Item Get Functions
public ITEM_GetSlot(idUser)
{
		

	if (g_iShopMenuItems[idUser][ITEM_SLOT_ONE] > ITEM_NONE && 
		g_iShopMenuItems[idUser][ITEM_SLOT_TWO] > ITEM_NONE &&
		g_iShopMenuItems[idUser][ITEM_SLOT_THREE] > ITEM_NONE)
		return ITEM_SLOT_FULL;

	if (g_iShopMenuItems[idUser][ITEM_SLOT_ONE] > ITEM_NONE && 
		g_iShopMenuItems[idUser][ITEM_SLOT_TWO] == ITEM_NONE &&
		g_iShopMenuItems[idUser][ITEM_SLOT_THREE] == ITEM_NONE)
		return ITEM_SLOT_TWO;

	if (g_iShopMenuItems[idUser][ITEM_SLOT_ONE] > ITEM_NONE && 
		g_iShopMenuItems[idUser][ITEM_SLOT_TWO] == ITEM_NONE &&
		g_iShopMenuItems[idUser][ITEM_SLOT_THREE] > ITEM_NONE)
		return ITEM_SLOT_TWO;

	if (g_iShopMenuItems[idUser][ITEM_SLOT_ONE] > ITEM_NONE && 
		g_iShopMenuItems[idUser][ITEM_SLOT_TWO] > ITEM_NONE &&
		g_iShopMenuItems[idUser][ITEM_SLOT_THREE] == ITEM_NONE)
		return ITEM_SLOT_THREE;

	return ITEM_SLOT_ONE;//Первый свободен если все не заняты
}

ITEM_Has( idUser, iItem )
{
		

	if ( g_iShopMenuItems[idUser][ITEM_SLOT_ONE] == iItem )
		return ITEM_SLOT_ONE;

	if ( g_iShopMenuItems[idUser][ITEM_SLOT_TWO] == iItem )
		return ITEM_SLOT_TWO;

	if ( g_iShopMenuItems[idUser][ITEM_SLOT_THREE] == iItem )
		return ITEM_SLOT_THREE;

	return ITEM_NONE;
}

// Item Death Function
//Удаление всех предметов когда игрок умирает
ITEM_UserDied(idUser)
{
		

	// The user just died, remove all items
	if ( g_iShopMenuItems[idUser][ITEM_SLOT_ONE] > ITEM_NONE )
		ITEM_Remove( idUser, ITEM_SLOT_ONE, false );

	if ( g_iShopMenuItems[idUser][ITEM_SLOT_TWO] > ITEM_NONE )
		ITEM_Remove( idUser, ITEM_SLOT_TWO, false );

	if ( g_iShopMenuItems[idUser][ITEM_SLOT_THREE] > ITEM_NONE )
		ITEM_Remove( idUser, ITEM_SLOT_THREE, false );


}

// Item Specific Functions
ITEM_Offensive( idAttacker, idVictim, iWeapon, iDamage, iHitPlace )
{
	
	//Для talisman +
	// Claws of Attack
	if ( ITEM_Has( idAttacker, ITEM_CLAWS ) > ITEM_NONE || fWorkTalismanPassive(idAttacker, arrTalismanActive[idAttacker]) == TALISMAN_ITEM_CLAWS)
	{	
		WC3_Damage( idVictim, idAttacker, get_pcvar_num( CVAR_wc3_claw ), iWeapon, iHitPlace );
		
		SHARED_Glow( idAttacker, (2 * get_pcvar_num( CVAR_wc3_claw ) ), 0, 0, 0 );

		Create_ScreenFade( idVictim, (1<<10), (1<<10), (1<<12), 255, 0, 0, g_GlowLevel[idVictim][0] );
	}
	
	// Mask of Death - Маска смерти - ITEM_MASK
	if (ITEM_Has(idAttacker, ITEM_MASK ) > ITEM_NONE && arrBoolData[idAttacker][PB_ISCONNECTED] ||
		(fWorkTalismanPassive(idAttacker, arrTalismanActive[idAttacker]) == TALISMAN_ITEM_MASK && arrBoolData[idAttacker][PB_ISCONNECTED]) ||
		clVIP:isAccesItemVip(idAttacker,ITEM_MASK) == true
	   )
	{
		new iCurrentHealth = clHP:getUserHealth(idAttacker);
		new iMinHealth = clHP:getRaceMinHealth(idAttacker);
		
		if (iCurrentHealth < iMinHealth)
		{
			new iBonusHealth = floatround( float( iDamage ) * get_pcvar_float(CVAR_wc3_mask) );
			
			new iVampiricBonus = 0;
			if(isDisabledSkillsOnMap(idAttacker,SKILL_VAMPIRICAURA) == false)
				iVampiricBonus = arrBoolData[idAttacker][PB_HEXED] ? 0 : SM_GetSkillLevel(idAttacker, SKILL_VAMPIRICAURA);

			// Then the user already gets a bonus, lets lower the total amount the user is going to get
			if (iVampiricBonus > 0)
				iBonusHealth /= iVampiricBonus;
					
			// User needs to be set to max health
			if ( (iCurrentHealth + iBonusHealth) > iMinHealth)
				clHP:setUserHealth(idAttacker,iMinHealth);
			else
				clHP:setUserHealth(idAttacker,iCurrentHealth + iBonusHealth);
			
			SHARED_Glow(idAttacker, 0, iBonusHealth, 0, 0 );

			Create_ScreenFade( idAttacker, (1<<10), (1<<10), (1<<12), 0, 255, 0, g_GlowLevel[idAttacker][1] );
		}
	}

	//Для talisman
	// Orb of Frost +
	if ( ITEM_Has( idAttacker, ITEM_FROST ) > ITEM_NONE || fWorkTalismanPassive(idAttacker, arrTalismanActive[idAttacker]) == TALISMAN_ITEM_FROST)
	{
		// Only slow them if they aren't slowed/stunned already
		if ( !SHARED_IsPlayerSlowed( idVictim ) )
		{

			arrBoolData[idVictim][PB_SLOWED]	= true;

			SHARED_SetSpeed( idVictim );

			set_task( 1.0, "SHARED_ResetMaxSpeed", TASK_RESETSPEED + idVictim );

			SHARED_Glow(idAttacker, 0, 0, 0, 100 );

			Create_ScreenFade( idVictim, (1<<10), (1<<10), (1<<12), 255, 255, 255, g_GlowLevel[idVictim][3] );
		}
	}
}

ITEM_Tome( idUser )
{
		
	new iXp = get_pcvar_num(CVAR_wc3_tome) + XP_GivenByLevel( arrIntData[idUser][P_LEVEL] );
	
	new iBonusXP = XP_Give( idUser, iXp );

	if (iBonusXP != 0)
	{
		format(szMessage, charsmax(szMessage), "%L %d XP",LANG_PLAYER,"INFO_SHOPMENU_9",iBonusXP);	
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
	}

	emit_sound(idUser,CHAN_STATIC, arrStrSounds[SOUND_TOMES], 0.3, ATTN_NORM,SND_CHANGE_VOL, PITCH_NORM);

	return;
}

ITEM_Gloves( idUser )
{
	

	if ( !WC3_Check() )
		return;

	if ( !SHARED_HasGrenade( idUser ) )
	{
		g_iGloveTimer[idUser] = 0;

		_ITEM_Glove_Give( idUser );
	}

	arrIsByuItemOneRound[idUser][ITEM_GLOVES]++;

	return;
}

ITEM_Glove_Begin( idUser )
{
		

	// Then lets start a timer to give them a grenade!
	g_iGloveTimer[idUser] = get_pcvar_num( CVAR_wc3_glove_timer );

	format(szMessage, charsmax(szMessage), "%d %L",g_iGloveTimer[idUser],LANG_PLAYER,"UNTIL_YOUR_NEXT_GRENADE");
	WC3_StatusText( idUser, TXT_TIMER,szMessage);

	g_iGloveTimer[idUser]--;

	set_task(1.0, "_ITEM_Glove_Give", TASK_ITEM_GLOVES + idUser );
}

public _ITEM_Glove_Give( idUser )
{
		
	if (!WC3_Check())
		return;


	if ( idUser >= TASK_ITEM_GLOVES )
	{
		idUser -= TASK_ITEM_GLOVES;
	}

	if ( !arrBoolData[idUser][PB_ISCONNECTED] || !is_user_alive(idUser))
	{
		return;
	}

	// Only need to save once! - this is b/c I'm not sure when the loss of a grenade is updated - and I wanted SHARED_HasGrenade to work @ all times!
	if ( g_iGloveTimer[idUser] == get_pcvar_num( CVAR_wc3_glove_timer ) - 1 )
	{
		SHARED_SaveWeapons( idUser );
	}

	// Already have a grenade!!
	if ( SHARED_HasGrenade( idUser ) )
	{
		g_iGloveTimer[idUser] = 0;

		return;
	}

	if ( g_iGloveTimer[idUser] > 0 )
	{
		format(szMessage, charsmax(szMessage), "%d %L",g_iGloveTimer[idUser],LANG_PLAYER,"UNTIL_YOUR_NEXT_GRENADE");
		WC3_StatusText( idUser, TXT_TIMER,szMessage);

		g_iGloveTimer[idUser]--;

		set_task(1.0, "_ITEM_Glove_Give", TASK_ITEM_GLOVES + idUser);

		return;
	}

	give_item(idUser, "weapon_hegrenade");

	// Display a message to the user
	WC3_StatusText( idUser, TXT_TIMER, "%L", LANG_PLAYER, "ENJOY_A_GRENADE" )

	return;
}		

ITEM_BuyRings(idUser)
{
		

	//Заблокирован ли предмет на карте
	new szItemName[32];
	if(isDisabledItemOnMap(idUser,ITEM_RING,szItemName) == true)
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_ITEM_DISABLED_ON_MAP",szItemName);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		return;
	}

	//Заблокирован ли предмет для Расы
	if(isDisabledItemRace(idUser,ITEM_RING,szItemName) == true)
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_ITEM_BLOCK",szItemName);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		return;
	}

	new iItemSlot = ITEM_GetSlot( idUser );

	// Items are full
	if ( iItemSlot == ITEM_SLOT_FULL && ITEM_Has( idUser, ITEM_RING ) == ITEM_NONE )
	{
		g_iFutureItem[idUser] = -3;

		MENU_ReplaceItem( idUser );

		return;
	}

	new iMoney;
	new iAdditionalRings = 0;
	
	while ( g_iTotalRings[idUser] + iAdditionalRings < 5 )
	{
		iMoney = SHARED_GetUserMoney( idUser );

		if ( iMoney < ITEM_Cost( idUser, ITEM_RING ) )
		{
			break;
		}

		iAdditionalRings++;
		
		new iNewMoney = iMoney - ITEM_Cost( idUser, ITEM_RING );
		SHARED_SetUserMoney( idUser, iNewMoney, 1 );
	}

	// Then we need to give them some rings!
	if ( iAdditionalRings > 0 )
	{

		// Subtract 1 b/c ITEM_GiveItem will add one
		g_iTotalRings[idUser] += ( ( iAdditionalRings * RING_INCREMENT ) - ( RING_INCREMENT ) );

		ITEM_GiveItem( idUser, ITEM_RING );
	}

	return;
}

public _ITEM_Ring( idUser )
{
	
	if ( !WC3_Check() )
		return;
	
	if ( idUser >= TASK_ITEM_RING )
	{
		idUser -= TASK_ITEM_RING;
	}

	//Для talisman + BEGIN {
	if ( !arrBoolData[idUser][PB_ISCONNECTED] || ITEM_Has( idUser, ITEM_RING ) == ITEM_NONE && bIsActiveTalisman(idUser,TALISMAN_ITEM_RING) == false)
		return;

	new iBonusHealth;
	if(fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_RING)
		iBonusHealth = RING_MAX;
	else
		iBonusHealth = g_iTotalRings[idUser];
	//Для talisman END }

	while (iBonusHealth > 0)
	{
		new iMaxHealth = clHP:getRaceMaxHealth(idUser);
		new iCurrentHealth =  clHP:getUserHealth(idUser);
		new iBonusHp = 1;

		if (iCurrentHealth < iMaxHealth)
		{
			if( (iCurrentHealth + iBonusHp) > iMaxHealth )
				clHP:setUserHealth(idUser,iMaxHealth);
			else
				clHP:setUserHealth(idUser,iCurrentHealth + iBonusHp);

		}
		iBonusHealth--;
	}

	set_task( 2.0, "_ITEM_Ring", TASK_ITEM_RING + idUser );

	return;
}

ITEM_Scroll( idUser )
{
		

	// Make sure the user isn't about to respawn when we do these checks
	if ( !arrIntData[idUser][P_RESPAWNBY] )
	{
		arrIntData[idUser][P_RESPAWNBY] = RESPAWN_ITEM;

		arrIsByuItemOneRound[idUser][ITEM_SCROLL]++;

		set_task( SPAWN_DELAY, "_SHARED_Spawn", TASK_SPAWN + idUser );
	}
}

ITEM_CheckFlag( iItemID, iFlag )
{
	if ( g_iFlag[iItemID] & iFlag )
	{
		return true;
	}

	return false;	
}

// Format the item for WC3_ShowBar
ITEM_Format( idUser, iItem, szItemString[], iLen )
{
		

	new szItemName[32];
	LANG_GetItemName( iItem, idUser, szItemName, 31, true );

	// Special options
	if ( iItem == ITEM_NECKLACE )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, g_iNecklaceCharges[idUser] );
	}

	else if ( iItem == ITEM_HELM )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, g_iHelmCharges[idUser] );
	}

	else if ( iItem == ITEM_RING )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, g_iTotalRings[idUser] );
	}
	//Для shopmenu3
	else if ( iItem == ITEM_GRENADE_PROTECTION )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, arriTotalRingsGrenadeProtection[idUser] );
	}
	//Для shopmenu4
	else if ( iItem == ITEM_DEVOURER_LIGHT )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, arriTotalRingsDevourerLight[idUser] );
	}
	else if ( iItem == ITEM_MIRROR_ULTIMATE )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, arriTotalChargeMirrorUltimate[idUser] );
	}
	else if ( iItem == ITEM_DEATHCOIL )
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, arriTotalChargeDeathCoil[idUser] );
	}
	else if ( iItem == ITEM_IMPALE)
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, arriTotalChargeImpale[idUser] );
	}
	else if ( iItem == ITEM_SLEEP)
	{
		formatex( szItemString, iLen, "%s[%d]", szItemName, arriTotalChargeSleep[idUser] );
	}

	

	// All other cases
	else
	{
		copy( szItemString, iLen, szItemName );
	}
}

//Возвращает есть ли конкретный предмет
ITEM_HasItem( idUser, iItem )
{
		

	if ( g_iShopMenuItems[idUser][ITEM_SLOT_ONE] == iItem )
		return iItem;

	else if ( g_iShopMenuItems[idUser][ITEM_SLOT_TWO] == iItem )
		return iItem;

	else if ( g_iShopMenuItems[idUser][ITEM_SLOT_THREE] == iItem )
		return iItem;

	return ITEM_NONE;
}

//Сброс всех счетчиков на ограничение покупок
ITEM_LimitOneRound(idUser)
{
		

	arrIsByuItemOneRound[idUser][ITEM_ANKH]	    = 0;			// Ankh of Reincarnation
	arrIsByuItemOneRound[idUser][ITEM_BOOTS]       = 0;			// Boots of Speed
	arrIsByuItemOneRound[idUser][ITEM_CLAWS]	    = 0;		// Claws of Attack
	arrIsByuItemOneRound[idUser][ITEM_CLOAK]	    = 0;		// Cloak of Shadows
	arrIsByuItemOneRound[idUser][ITEM_MASK]	    = 0;			// Mask of Death
	arrIsByuItemOneRound[idUser][ITEM_NECKLACE]	= 0;			// Necklace of Immunity
	arrIsByuItemOneRound[idUser][ITEM_FROST]	    = 0;		// Orb of Frost
	arrIsByuItemOneRound[idUser][ITEM_HEALTH]	    = 0;		// Periapt of Health
	arrIsByuItemOneRound[idUser][ITEM_TOME]	    = 0;			// Tome of Experience
	arrIsByuItemOneRound[idUser][ITEM_SCROLL]	    = 0;		// Scroll of Respawning
	arrIsByuItemOneRound[idUser][ITEM_PROTECTANT]	= 0;		// Mole Protectant
	arrIsByuItemOneRound[idUser][ITEM_HELM]	    = 0;			// Helm of Excellence
	arrIsByuItemOneRound[idUser][ITEM_AMULET]	    = 0;		// Amulet of the Cat
	arrIsByuItemOneRound[idUser][ITEM_SOCK]	    = 0;			// Sock of the Feather
	arrIsByuItemOneRound[idUser][ITEM_GLOVES]	    = 0;		// Flaming Gloves of Warmth
	arrIsByuItemOneRound[idUser][ITEM_RING]	    = 0;			// Ring of Regeneration + 1
	arrIsByuItemOneRound[idUser][ITEM_CHAMELEON]	= 0;		// Chameleon
	arrIsByuItemOneRound[idUser][ITEM_MOLE]	    = 0;			// Mole
	//Для shopmenu3
	arrIsByuItemOneRound[idUser][ITEM_INTELLECT]	    = 0;		// Intellect
	arrIsByuItemOneRound[idUser][ITEM_GRENADE_PROTECTION]	= 0;	// Grenade Protection
	arrIsByuItemOneRound[idUser][ITEM_MIRROR_SHIELD]	    = 0;	// Mirror Shield
	arrIsByuItemOneRound[idUser][ITEM_ESP]					= 0;	// ESP
	arrIsByuItemOneRound[idUser][ITEM_FROST_ARMOR]			= 0;	// Frost Armor
	arrIsByuItemOneRound[idUser][ITEM_DEATH_TOUCH]			= 0;	//Death's Touch
	arrIsByuItemOneRound[idUser][ITEM_HEALTH_POTION]	    = 0;	// Health Potion
	arrIsByuItemOneRound[idUser][ITEM_ULTIMATE_TIMER_DIVIDER]	= 0;	// Ultimate Timer Divider
	arrIsByuItemOneRound[idUser][ITEM_STEEL_SKIN]   = 0;				// Steel Skin

	//Для shopmenu4
	sm4_ITEM_LimitOneRound(idUser);
}

