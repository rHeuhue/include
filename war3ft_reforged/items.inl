/*
*	Item Functions
*/

// Item Setup Functions
ITEM_Init()
{

	ITEM_COST[ITEM_ANKH]	    = 1000;			// Ankh of Reincarnation
	ITEM_COST[ITEM_BOOTS]       = 2000;			// Boots of Speed
	ITEM_COST[ITEM_CLAWS]	    = 3000;			// Claws of Attack
	ITEM_COST[ITEM_CLOAK]	    = 3000;			// Cloak of Shadows
	ITEM_COST[ITEM_MASK]	    = 4000;			// Mask of Death
	ITEM_COST[ITEM_NECKLACE]	= 1000;			// Necklace of Immunity
	ITEM_COST[ITEM_FROST]	    = 3000;			// Orb of Frost
	ITEM_COST[ITEM_HEALTH]	    = 2000;			// Periapt of Health
	ITEM_COST[ITEM_TOME]	    = 5000;			// Tome of Experience
	ITEM_COST[ITEM_SCROLL]	    = 8000;			// Scroll of Respawning
	ITEM_COST[ITEM_PROTECTANT]	= 2000;			// Mole Protectant
	ITEM_COST[ITEM_HELM]	    = 4000;			// Helm of Excellence
	ITEM_COST[ITEM_AMULET]	    = 2000;			// Amulet of the Cat
	ITEM_COST[ITEM_SOCK]	    = 2000;			// Sock of the Feather
	ITEM_COST[ITEM_GLOVES]	    = 3000;			// Flaming Gloves of Warmth
	ITEM_COST[ITEM_RING]	    = 2000;			// Ring of Regeneration
	ITEM_COST[ITEM_CHAMELEON]	= 4000;			// Chameleon
	ITEM_COST[ITEM_MOLE]	    = 9000;			// Mole	
	ITEM_COST[ITEM_MINE]	    = 1500;			// Mine

	// Items are chargeable
	g_iFlag[ITEM_NECKLACE]	|= ITEM_CHARGEABLE;
	g_iFlag[ITEM_HELM]		|= ITEM_CHARGEABLE;

	// Items should be used when bought
	g_iFlag[ITEM_TOME]		|= ITEM_USEONBUY;

	// Items CAN be bought when dead
	g_iFlag[ITEM_ANKH]		|= ITEM_BUYWHENDEAD;
	g_iFlag[ITEM_SCROLL]	|= ITEM_BUYWHENDEAD;
	g_iFlag[ITEM_MOLE]		|= ITEM_BUYWHENDEAD;
	g_iFlag[ITEM_TOME]		|= ITEM_BUYWHENDEAD;

	// Items are used when the next round starts...
	g_iFlag[ITEM_ANKH]		|= ITEM_NEXTROUNDUSE;
	g_iFlag[ITEM_MOLE]		|= ITEM_NEXTROUNDUSE;
}

// We created this to allow for different prices of items at different levels
ITEM_Cost( id, iItem )
{
	// How much should ratio increase per level?
	new Float:fInc = ( 1.0 - ITEM_COST_RATIO ) / float( MAX_LEVELS );

	// Cost * ratio (ITEM_COST_RATIO to 1.0 dependent on level)
	new Float:fRatio = (float( p_data[id][P_LEVEL] ) * fInc) + ITEM_COST_RATIO;

	return ( p_data[id][P_RACE] != RACE_NONE ) ? floatround( float( ITEM_COST[iItem] ) * fRatio ) : ITEM_COST[iItem];
}


public ITEM_CanBuy( id, iItem )
{
	// User doesn't have the money
	if ( SHARED_GetUserMoney( id ) < ITEM_Cost( id, iItem ) )
	{
		client_print( id, print_center, "You have insufficient funds.");

		return false;
	}
	
	// User already owns the item and it's not a chargeable item!
	else if ( ITEM_Has( id, iItem ) > ITEM_NONE && !ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
	{
		client_print( id, print_center, "You already own this item.");

		return false;
	}
	
	// Make sure these items can be bought if the user is dead
	else if ( !is_user_alive( id ) && !ITEM_CheckFlag( iItem, ITEM_BUYWHENDEAD ) ) 
	{
		client_print( id, print_center, "You can not buy this item when dead." );

		return false;
	}
	
	// User has necklace + blink, they don't need a necklace
	else if ( iItem == ITEM_NECKLACE && p_data_b[id][PB_WARDENBLINK] )
	{
		client_print( id, print_center, "You are already immune to ultimates becouse of your skills." );

		return false;
	}

	// User doesn't need an ankh if they're going to reincarnate
	else if ( iItem == ITEM_ANKH && SM_GetSkillLevel( id, SKILL_REINCARNATION ) == 3 && !p_data[id][P_CHANGERACE] && p_data[id][P_RACE] != RACE_CHAMELEON )
	{
		client_print( id, print_center, "You will already reincarnate your weapons becouse of your skills." );

		return false;
	}
	
	
	// User has purchased gloves when they're disabled on this map
	else if ( iItem == ITEM_GLOVES && g_bGlovesDisabled )
	{
		client_print_color( id, print_team_default, "^4%s ^3Gloves are disabled on this map.", GAME_NAME );

		return false;
	}

	// User is already going to reincarnate weapons because they bought an ankh earlier (probably lost it when died)
	else if ( ( iItem == ITEM_ANKH && g_bPlayerBoughtAnkh[id] ) || ( iItem == ITEM_MOLE && g_bPlayerBoughtMole[id] ) )
	{
		client_print( id, print_center, "You already own this item." );

		return false;
	}

	return true;
}


// Used with new shopmenu
public ITEM_CanBuyCheckSilent( id, iItem )
{
	// User doesn't have the money
	if ( SHARED_GetUserMoney( id ) < ITEM_Cost( id, iItem ) )
	{
		//client_print( id, print_center, "You have insufficient funds.");

		return false;
	}
	
	// User already owns the item and it's not a chargeable item!
	else if ( ITEM_Has( id, iItem ) > ITEM_NONE && !ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
	{
		//client_print( id, print_center, "You already own this item.");

		return false;
	}
	
	// Make sure these items can be bought if the user is dead
	else if ( !is_user_alive( id ) && !ITEM_CheckFlag( iItem, ITEM_BUYWHENDEAD ) ) 
	{
		//client_print( id, print_center, "You can not buy this item when dead." );

		return false;
	}
	
	// User has necklace + blink, they don't need a necklace
	else if ( iItem == ITEM_NECKLACE && p_data_b[id][PB_WARDENBLINK] )
	{
		//client_print( id, print_center, "You are already immune to ultimates becouse of your skills." );

		return false;
	}

	// User doesn't need an ankh if they're going to reincarnate
	else if ( iItem == ITEM_ANKH && SM_GetSkillLevel( id, SKILL_REINCARNATION ) == 3 && !p_data[id][P_CHANGERACE] && p_data[id][P_RACE] != RACE_CHAMELEON )
	{
		// client_print( id, print_center, "You will already reincarnate your weapons becouse of your skills." );

		return false;
	}
	
	
	// User has purchased gloves when they're disabled on this map
	else if ( iItem == ITEM_GLOVES && g_bGlovesDisabled )
	{
		//	client_print( id, print_chat, "Gloves are disabled on this map." );

		return false;
	}

	// User is already going to reincarnate weapons because they bought an ankh earlier (probably lost it when died)
	else if ( ( iItem == ITEM_ANKH && g_bPlayerBoughtAnkh[id] ) || ( iItem == ITEM_MOLE && g_bPlayerBoughtMole[id] ) )
	{
			// client_print( id, print_center, "You already own this item." );

		return false;
	}

	return true;
}


public ITEM_Buy( id, iItem )
{

	
	// If the user can buy this item...
	if ( ITEM_CanBuy( id, iItem ) )
	{

		// User's items are full
		if ( ITEM_GetSlot( id ) == ITEM_SLOT_FULL && !ITEM_CheckFlag( iItem, ITEM_USEONBUY ) )
		{

			// We only care about items being full if this item isn't a use on buy
			if ( !ITEM_CheckFlag( iItem, ITEM_USEONBUY ) )
			{

				new bool:bShowReplaceMenu = false;

				// One time use...
				if ( !ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
				{
					//client_print( id, print_chat, "[DEBUG] Item is not chargeable" );

					bShowReplaceMenu = true;
				}

				// We also need to replace it if the item is chargeable but they don't own that item
				if ( ITEM_Has( id, iItem ) == ITEM_NONE && ITEM_CheckFlag( iItem, ITEM_CHARGEABLE ) )
				{
					//client_print( id, print_chat, "[DEBUG] Doesn't have item and new item is chargeable" );

					bShowReplaceMenu = true;
				}

				if ( bShowReplaceMenu )
				{
					g_iFutureItem[id] = iItem;

					MENU_ReplaceItem( id );

					return;
				}
			}
		}
	
		// We're clear!

		// Remove user's money
		new iNewMoney = SHARED_GetUserMoney( id ) - ITEM_Cost( id, iItem );
		SHARED_SetUserMoney( id, iNewMoney );

		ITEM_GiveItem( id, iItem );
	}

	return;
}

// Item Buy Functions
bool:ITEM_MenuCanBuyCheck( id )
{
	// Duh how can they buy if they're dead!
	if ( !p_data_b[id][PB_ISCONNECTED] )
	{
		return false;
	}

	new isPlayerAlive		= is_user_alive( id );

	if ( !get_pcvar_num( CVAR_wc3_buy_dead ) && !isPlayerAlive )
	{
		client_print( id, print_center, "You can not buy this item when dead." );
		
		return false;
	}
	
	else if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		new isPlayerInBuyZone	= cs_get_user_buyzone( id )
		
		if ( get_pcvar_num( CVAR_wc3_buy_time ) && !g_buyTime )
		{
			client_print( id, print_center, "The shop is closed.");

			return false;
		}
		
		else if ( get_pcvar_num( CVAR_wc3_buy_zone ) && !isPlayerInBuyZone && isPlayerAlive )
		{
			client_print( id, print_center, "You need to be in buy zone.");
			
			return false;
		}
	}
	
	return true;
}

// Item Preset Function
ITEM_GiveItem( id, iItem )
{

	// This item we should use instantly
	if ( ITEM_CheckFlag( iItem, ITEM_USEONBUY ) )
	{
		if ( iItem == ITEM_TOME )
		{
			ITEM_Tome( id );

			return;
		}
	}

	// They are just adding some charges
	else
	{
		// Actually set our item variable
		if ( is_user_alive( id ) )
		{
			ITEM_Equip( id, iItem );
		}

		// Display message to the user regarding the item they just purchased
		ITEM_DisplayMessage( id, iItem );

		// Give bonuses
		ITEM_GiveBonuses( id, iItem );

		// Play purchase sound
		emit_sound(id, CHAN_AUTO, g_szSounds[SOUND_BUY], 1.0, ATTN_NORM, 0, PITCH_NORM );
	}

	WC3_ShowBar( id );

	return;
}

ITEM_DisplayMessage( id, iItem )
{
	// Display a message regarding the item they just purchased
	switch ( iItem )
	{
		case ITEM_ANKH:
		{
			client_print_color( id, print_team_default,"^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_ANKH][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_ANKH][ITEM_DESCRIPTION]);
		}

		case ITEM_BOOTS:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_BOOTS][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_BOOTS][ITEM_DESCRIPTION]);
		}

		case ITEM_CLAWS:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_CLAWS][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_CLAWS][ITEM_DESCRIPTION]);
		}

		case ITEM_CLOAK:
		{
			client_print_color(id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_CLOAK][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_CLOAK][ITEM_DESCRIPTION]);
		}

		case ITEM_MASK:
		{
			client_print_color(id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_MASK][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_MASK][ITEM_DESCRIPTION]);
		}

		case ITEM_NECKLACE:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_NECKLACE][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_NECKLACE][ITEM_DESCRIPTION]);
		}

		case ITEM_FROST:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_FROST][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_FROST][ITEM_DESCRIPTION]);
		}

		case ITEM_HEALTH:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_HEALTH][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_HEALTH][ITEM_DESCRIPTION]);
		}

		case ITEM_SCROLL:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_SCROLL][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_SCROLL][ITEM_DESCRIPTION]);
		}

		case ITEM_PROTECTANT:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_PROTECTANT][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_PROTECTANT][ITEM_DESCRIPTION]);
		}

		case ITEM_HELM:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_HELM][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_HELM][ITEM_DESCRIPTION]);
		}

		case ITEM_AMULET:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_AMULET][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_AMULET][ITEM_DESCRIPTION]);
		}

		case ITEM_SOCK:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_SOCK][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_SOCK][ITEM_DESCRIPTION]);
		}

		case ITEM_GLOVES:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_GLOVES][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_GLOVES][ITEM_DESCRIPTION]);
		}

		case ITEM_RING:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_RING][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_RING][ITEM_DESCRIPTION]);
		}

		case ITEM_CHAMELEON:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_CHAMELEON][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_CHAMELEON][ITEM_DESCRIPTION]);
		}

		case ITEM_MOLE:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_MOLE][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_MOLE][ITEM_DESCRIPTION]);
		}
		
		case ITEM_MINE:
		{
			client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_MINE][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_MINE][ITEM_DESCRIPTION]);
		}
	}
}

// Give the user bonuses for their items (except charges)
ITEM_GiveAllBonuses( id )
{

	// Loop through all item slots
	for ( new i = ITEM_SLOT_ONE; i <= ITEM_SLOT_TWO; i++ )
	{
		
		// Do we have a valid item here?
		if ( g_iShopMenuItems[id][i] != ITEM_NONE )
		{

			// Don't want to give the user more charges for free do we?
			//  And we don't want to give the bonuses if this is a next round use item (i.e. if we do then mole for infinity - that doesn't seem nice)
			if ( !ITEM_CheckFlag( g_iShopMenuItems[id][i], ITEM_CHARGEABLE ) && !ITEM_CheckFlag( g_iShopMenuItems[id][i], ITEM_NEXTROUNDUSE ) )
			{
				ITEM_GiveBonuses( id, g_iShopMenuItems[id][i] );
			}
		}
	}
}

// Give our players their bonus!
ITEM_GiveBonuses( id, iItem )
{
	
	// Display a message regarding the item they just purchased
	switch ( iItem )
	{
		case ITEM_ANKH:
		{
			g_bPlayerBoughtAnkh[id] = true;
		}

		case ITEM_BOOTS:
		{
			SHARED_SetSpeed( id );
		}

		case ITEM_CLOAK:
		{
			SHARED_INVIS_Set( id );
		}

		case ITEM_NECKLACE:
		{
			g_iNecklaceCharges[id] += NECKLACE_CHARGES;
		}

		case ITEM_HEALTH:
		{
			new iHealth = get_pcvar_num( CVAR_wc3_health );
			iHealth += get_user_health( id );
			set_user_health( id, iHealth );
		}

		case ITEM_SCROLL:
		{
			if ( !is_user_alive( id ) )
			{
				ITEM_Scroll( id );
			}
		}

		case ITEM_HELM:
		{
			g_iHelmCharges[id] += HELM_CHARGES;
		}

		case ITEM_SOCK:
		{
			SHARED_SetGravity( id );
		}

		case ITEM_GLOVES:
		{
			ITEM_Gloves( id );
		}

		case ITEM_RING:
		{
			if ( !task_exists( TASK_ITEM_RING + id ) )
			{
				_ITEM_Ring( id );
			}
		}

		case ITEM_CHAMELEON:
		{
			SHARED_ChangeSkin( id, SKIN_SWITCH );
		}

		case ITEM_MOLE:
		{
			g_bPlayerBoughtMole[id] = true;
		}
		
		case ITEM_PROTECTANT:
		{
			ITEM_EnableProtectant(id);
		}
		
		/*
		case ITEM_MINE:
		{
			if(g_Dropped[id]) 
			{
				g_PlayerMines[id]  = 0
			} 
			else 
			{
				//g_PlayerMines[id] = MAXMINES
				g_PlayerMines[id] = BUY_MINE
			}
			
			g_lasermine[id] = true
		
		}
		*/
						
	}
}

// Item Equip Function
ITEM_Equip( id, iItem )
{
	new iItemSlot = ITEM_GetSlot( id );

	// Items are not full
	if ( iItemSlot != ITEM_SLOT_FULL )
	{

		new iOldItem = g_iShopMenuItems[id][iItemSlot];

		if ( iItem == iOldItem || ITEM_Has( id, iItem ) > ITEM_NONE )
		{
			// Might hit this if we added charges - we want to update the user's HUD
			WC3_ShowBar( id );

			return;
		}

		// Remove the user's old item if necessary
		else if ( g_iShopMenuItems[id][iItemSlot] > ITEM_NONE )
		{
			ITEM_Remove( id, iItemSlot );
		}
			
		// Set their new item
		g_iShopMenuItems[id][iItemSlot] = iItem;
	}

	WC3_ShowBar( id );

	return;
}

// Item Remove Functions
ITEM_RemoveID( id, iItem )
{
	new iItemSlot = ITEM_Has( id, iItem );

	if ( iItemSlot > ITEM_NONE )
	{
		ITEM_Remove( id, iItemSlot );
	}

	return;
}

ITEM_Remove( id, iItemSlot, bResetAnkhMole = true )
{
	new iItem = g_iShopMenuItems[id][iItemSlot];

	g_iShopMenuItems[id][iItemSlot] = ITEM_NONE;

	switch( iItem )
	{
		case ITEM_ANKH:
		{
			if ( bResetAnkhMole )
			{
				g_bPlayerBoughtAnkh[id] = false;
			}
		}

		case ITEM_BOOTS:
		{
			SHARED_SetSpeed( id );
		}

		case ITEM_CLOAK:
		{
			SHARED_INVIS_Set( id );
		}

		case ITEM_NECKLACE:
		{
			g_iNecklaceCharges[id] = 0;
		}

		case ITEM_HEALTH:
		{
			new iNewHealth = get_user_health( id ) - get_pcvar_num( CVAR_wc3_health );
			
			// Lets not kill the user, give them 1 health
			iNewHealth = ( ( iNewHealth <= 0 ) ? 1 : iNewHealth );

			set_user_health( id, iNewHealth );
		}

		case ITEM_HELM:
		{
			g_iHelmCharges[id] = 0;
		}
		
		case ITEM_SOCK:
		{
			SHARED_SetGravity( id );
		}

		case ITEM_GLOVES:
		{
			if ( task_exists( TASK_ITEM_GLOVES + id ) )
			{
				remove_task( TASK_ITEM_GLOVES + id );
			}
		}

		case ITEM_RING:
		{
			if ( task_exists( TASK_ITEM_RING + id ) )
			{
				remove_task( TASK_ITEM_RING + id );
			}
			
		}

		case ITEM_CHAMELEON:
		{
			SHARED_ChangeSkin( id, SKIN_RESET );
		}

		case ITEM_MOLE:
		{
			if ( bResetAnkhMole )
			{
				g_bPlayerBoughtMole[id] = false;
			}
		}
		
		case ITEM_PROTECTANT:
		{
			ITEM_DisableProtectant(id);
		}
		
		/*
		case ITEM_MINE:
		{
				g_lasermine[id] = false
				g_Dropped[id] = true
		
		}
		*/
	}

	WC3_ShowBar( id );

	return;
}

ITEM_RemoveCharge( id, iItem )
{
	if ( ITEM_Has( id, iItem ) > ITEM_NONE )
	{
		switch ( iItem )
		{
			case ITEM_NECKLACE:
			{
				g_iNecklaceCharges[id] -= CHARGE_DISPOSE;
				
				if ( g_iNecklaceCharges[id] <= 0 )
				{
					ITEM_RemoveID( id, iItem );
				}
			}

			case ITEM_HELM:
			{
				g_iHelmCharges[id] -= CHARGE_DISPOSE;
				
				if ( g_iHelmCharges[id] <= 0 )
				{
					ITEM_RemoveID( id, iItem );
				}
			}
		}
	}

	WC3_ShowBar( id );
	return;
}


// Item Get Functions
ITEM_GetSlot( id )
{
	if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] > ITEM_NONE && g_iShopMenuItems[id][ITEM_SLOT_TWO] > ITEM_NONE )
		return ITEM_SLOT_FULL;

	else if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] > ITEM_NONE )
		return ITEM_SLOT_TWO;

	return ITEM_SLOT_ONE;
}

ITEM_Has( id, iItem )
{
	if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] == iItem )
		return ITEM_SLOT_ONE;

	else if ( g_iShopMenuItems[id][ITEM_SLOT_TWO] == iItem )
		return ITEM_SLOT_TWO;

	return ITEM_NONE;
}

// Item Death Function
ITEM_UserDied( id )
{
	// The user just died, remove all items
	if ( g_iShopMenuItems[id][ITEM_SLOT_ONE] > ITEM_NONE )
	{
		ITEM_Remove( id, ITEM_SLOT_ONE, false );
	}

	if ( g_iShopMenuItems[id][ITEM_SLOT_TWO] > ITEM_NONE )
	{
		ITEM_Remove( id, ITEM_SLOT_TWO, false );
	}
}

// Item Specific Functions

ITEM_Offensive( iAttacker, iVictim, iWeapon, iDamage, iHitPlace )
{

	// Claws of Attack
	if ( ITEM_Has( iAttacker, ITEM_CLAWS ) > ITEM_NONE )
	{	
		WC3_Damage( iVictim, iAttacker, get_pcvar_num( CVAR_wc3_claw ), iWeapon, iHitPlace );
		
		SHARED_Glow( iAttacker, (2 * get_pcvar_num( CVAR_wc3_claw ) ), 0, 0, 0 );

		Create_ScreenFade( iVictim, (1<<10), (1<<10), (1<<12), 255, 0, 0, g_GlowLevel[iVictim][0] );
	}

	// Mask of Death
	if ( ITEM_Has( iAttacker, ITEM_MASK ) > ITEM_NONE && p_data_b[iAttacker][PB_ISCONNECTED])
	{
		new iHealth = get_user_health( iAttacker );
		new iBonusHealth = floatround( float( iDamage ) * get_pcvar_float( CVAR_wc3_mask ) );
		
		new iVampiricBonus = p_data_b[iAttacker][PB_HEXED] ? 0 : SM_GetSkillLevel( iAttacker, SKILL_VAMPIRICAURA );

		// Then the user already gets a bonus, lets lower the total amount the user is going to get
		if ( iVampiricBonus > 0 )
		{
			iBonusHealth /= iVampiricBonus;
		}
		
		// User needs to be set to max health
		if ( iHealth + iBonusHealth > get_user_maxhealth( iAttacker ) )
		{
			set_user_health( iAttacker, get_user_maxhealth( iAttacker ) );
		}
		
		// Give them bonus
		else
		{
			set_user_health( iAttacker, iHealth + iBonusHealth );
		}

		SHARED_Glow( iAttacker, 0, iBonusHealth, 0, 0 );

		Create_ScreenFade( iAttacker, (1<<10), (1<<10), (1<<12), 0, 255, 0, g_GlowLevel[iAttacker][1] );
	}

	// Orb of Frost
	if ( ITEM_Has( iAttacker, ITEM_FROST ) > ITEM_NONE )
	{
		// Only slow them if they aren't slowed/stunned already
		if ( !SHARED_IsPlayerSlowed( iVictim ) )
		{

			p_data_b[iVictim][PB_SLOWED]	= true;

			SHARED_SetSpeed( iVictim );

			set_task( 1.0, "SHARED_ResetMaxSpeed", TASK_RESETSPEED + iVictim );

			SHARED_Glow( iAttacker, 0, 0, 0, 100 );

			Create_ScreenFade( iVictim, (1<<10), (1<<10), (1<<12), 255, 255, 255, g_GlowLevel[iVictim][3] );
		}
	}
}

ITEM_Tome( id )
{
	new iXp = get_pcvar_num( CVAR_wc3_tome ) + XP_GivenByLevel( p_data[id][P_LEVEL] );
		
	

	new iBonusXP = XP_Give( id, iXp );

	if ( iBonusXP != 0 )
	{
		client_print_color( id, print_team_default, "^4%s ^3%s ^1: ^4%s", GAME_NAME, Lang_ItemDatabase[ITEM_TOME][ITEM_NAME_LONG], Lang_ItemDatabase[ITEM_TOME][ITEM_DESCRIPTION]);
	}

	emit_sound( id, CHAN_STATIC, "warcraft3/Tomes.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );

	return;
}

ITEM_Gloves( id )
{
	if ( !WC3_Check() )
	{
		return;
	}

	if ( !SHARED_HasGrenade( id ) )
	{
		g_iGloveTimer[id] = 0;

		_ITEM_Glove_Give( id );
	}

	return;
}

ITEM_Glove_Begin( id )
{
	// Then lets start a timer to give them a grenade!
	g_iGloveTimer[id] = get_pcvar_num( CVAR_wc3_glove_timer );

	//WC3_StatusText( id, TXT_TIMER, "Explosive grenade in %d seconds.", g_iGloveTimer[id] );
	WC3_SyncGrenadeHud( id );

	g_iGloveTimer[id]--;

	set_task( 1.0, "_ITEM_Glove_Give", TASK_ITEM_GLOVES + id );
}

public _ITEM_Glove_Give( id )
{
	if ( !WC3_Check() )
	{
		return;
	}

	if ( id >= TASK_ITEM_GLOVES )
	{
		id -= TASK_ITEM_GLOVES;
	}

	if ( !p_data_b[id][PB_ISCONNECTED] || !is_user_alive( id ) )
	{
		return;
	}

	// Only need to save once! - this is b/c I'm not sure when the loss of a grenade is updated - and I wanted SHARED_HasGrenade to work @ all times!
	if ( g_iGloveTimer[id] == get_pcvar_num( CVAR_wc3_glove_timer ) - 1 )
	{
		SHARED_SaveWeapons( id );
	}



	// Lets do CS/CZ only
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		// Already have a grenade!!
		if ( SHARED_HasGrenade( id ) )
		{
			g_iGloveTimer[id] = 0;

			return;
		}
	}


	if ( g_iGloveTimer[id] > 0 )
	{
		//WC3_StatusText( id, TXT_TIMER, "Explosive grenade in %d seconds.", g_iGloveTimer[id] );
		WC3_SyncGrenadeHud( id );

		g_iGloveTimer[id]--;

		set_task( 1.0, "_ITEM_Glove_Give", TASK_ITEM_GLOVES + id );

		return;
	}

	
	give_item( id, "weapon_hegrenade" );
	

	

	// Display a message to the user
	//WC3_StatusText( id, TXT_TIMER, "Explosive Grenade !" )
	WC3_SyncGrenadeHud( id );

	return;
}		


public _ITEM_Ring( id )
{
	
	if ( id >= TASK_ITEM_RING )
	{
		id -= TASK_ITEM_RING;
	}

	if ( !p_data_b[id][PB_ISCONNECTED] || ITEM_Has( id, ITEM_RING ) == ITEM_NONE )
	{
		return;
	}

	new iBonusHealth = RING_BONUS;

	while ( iBonusHealth > 0 )
	{
		new iHealth =  get_user_health( id ) + 1;

		if ( iHealth <= get_user_maxhealth( id ) )
		{
			set_user_health( id, iHealth );
		}

		iBonusHealth--;
	}

	set_task( RING_FREQ, "_ITEM_Ring", TASK_ITEM_RING + id );

	return;
}

ITEM_Scroll( id )
{
	// Make sure the user isn't about to respawn when we do these checks
	if ( !p_data[id][P_RESPAWNBY] )
	{
		p_data[id][P_RESPAWNBY] = RESPAWN_ITEM;

		set_task( SPAWN_DELAY, "_SHARED_Spawn", TASK_SPAWN + id );
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
ITEM_Format( id, iItem, szItemString[], iLen )
{
	
	if ( iItem == ITEM_NECKLACE )
	{
		formatex( szItemString, iLen, "%s[%d]", Lang_ItemDatabase[iItem][ITEM_NAME_SHORT], g_iNecklaceCharges[id] );
	}

	else if ( iItem == ITEM_HELM )
	{
		formatex( szItemString, iLen, "%s[%d]", Lang_ItemDatabase[iItem][ITEM_NAME_SHORT], g_iHelmCharges[id] );
	}
	
	else
	{
		copy( szItemString, iLen, Lang_ItemDatabase[iItem][ITEM_NAME_SHORT] );
	}
}

ITEM_HasItem( idUser, iItem )
{
	if ( g_iShopMenuItems[idUser][ITEM_SLOT_ONE] == iItem )
		return iItem;

	else if ( g_iShopMenuItems[idUser][ITEM_SLOT_TWO] == iItem )
		return iItem;

	return ITEM_NONE;
}

public ITEM_EnableProtectant(id)
{
	if(task_exists(id + TASK_PROTECTANT))
		remove_task(id + TASK_PROTECTANT);

	iProtectant[id] = true;
	
	set_task(FREQUENCY_PROTECTANT, "Check_Protectant", id + TASK_PROTECTANT, _, _, "b");
	
}

public ITEM_DisableProtectant(id)
{
	iProtectant[id] = false;

	if(task_exists(id + TASK_PROTECTANT))
		remove_task(id + TASK_PROTECTANT);
}

public Check_Protectant(id)
{	
	if (id >= TASK_PROTECTANT )
			id -= TASK_PROTECTANT;

	if(!is_user_connected(id) || !is_user_alive(id) || !iProtectant[id]) 
	{
		if(task_exists(id + TASK_PROTECTANT))
			remove_task(id + TASK_PROTECTANT);

		return PLUGIN_CONTINUE;
	}
	
	new iPlayers[32], iNum;
	get_players(iPlayers, iNum, "a");
	
	for(new i = 0; i < iNum; ++i)
	{
		new iVictim = iPlayers[i];
		new iTeamAttacker = get_user_team(id);
		new iTeamVictim = get_user_team(iVictim);

		if(iTeamAttacker == iTeamVictim || id == iVictim) 
			continue;

		if( SM_GetSkillLevel( iVictim, SKILL_INVISIBILITY ) > 0 || ITEM_Has(iVictim, ITEM_CLOAK ) > ITEM_NONE || p_data_b[iVictim][PB_SKINSWITCHED] )
		{
		
			new iOrigin[3];
			get_user_origin(iVictim, iOrigin, 0);
				
			message_begin(MSG_ONE, SVC_TEMPENTITY, iOrigin, id);
			write_byte(21);
			write_coord(iOrigin[0]);
			write_coord(iOrigin[1]);
			write_coord(iOrigin[2] - 20);
			write_coord(iOrigin[0]);
			write_coord(iOrigin[1]);
			write_coord(iOrigin[2] + RADIUS_PROTECTANT);
			write_short(g_iSprites[SPR_TRAIL]);
			write_byte(0);
			write_byte(1);
			write_byte(6); 
			write_byte(8);
			write_byte(1);
			write_byte(100);
			write_byte(255);
			write_byte(100);
			write_byte(192);
			write_byte(0);
			message_end();
		
		}
	}

	return PLUGIN_CONTINUE;
}





public remove_mines()
{
	new ent = find_ent_by_class(-1, "lasermine")
	while(ent) 
	{
		remove_entity(ent)
		ent = find_ent_by_class(ent, "lasermine")
	}
}

Create_Mine(id)
{
	new Mine = create_entity("info_target")
	if(is_valid_ent(Mine))  
	{
		entity_set_string(Mine, EV_SZ_classname, "lasermine")
		entity_set_int(Mine, EV_INT_movetype, MOVETYPE_FLY)
		entity_set_int(Mine, EV_INT_solid, SOLID_NOT)
		entity_set_model(Mine, "models/v_tripmine.mdl")
	
		entity_set_float(Mine, EV_FL_frame, 0.0)
		entity_set_int(Mine, EV_INT_body, 3)
		entity_set_int(Mine, EV_INT_sequence, 7)
		entity_set_float(Mine, EV_FL_framerate, 0.0)

		entity_set_float(Mine, EV_FL_takedamage, 1.0)
		entity_set_float(Mine, EV_FL_dmg, 100.0)
		entity_set_float(Mine, EV_FL_health, float(MINE_HEALTH))

		entity_set_int(Mine, EV_INT_iuser2, 0)

		new Float:MinBox[3] = {-8.0, -8.0, -8.0}
		new Float:MaxBox[3] = {8.0, 8.0, 8.0}
		entity_set_size(Mine, MinBox, MaxBox)

		new Float:vOrigin[3]
		entity_get_vector(id, EV_VEC_origin, vOrigin)
		
		new Float:flVelocity[3]
		VelocityByAim(id, 64, flVelocity)

		new Float:vTraceEnd[3]
		vTraceEnd[0] = flVelocity[0] + vOrigin[0]
		vTraceEnd[1] = flVelocity[1] + vOrigin[1]
		vTraceEnd[2] = flVelocity[2] + vOrigin[2]

		new Float:vTraceResult[3]
		trace_line(id, vOrigin, vTraceEnd, vTraceResult)

		new Float:vNormal[3]
		if(trace_normal(id, vOrigin, vTraceEnd, vNormal) < 1)
		{
			remove_entity(Mine)
			client_print_color(id, print_team_default, "^4%s ^3You must plant the mine on a wall.", GAME_NAME)
			return  
		}
		
		ITEM_RemoveID( id, ITEM_MINE);
		
		new Float:vNewOrigin[3]
		
		vNewOrigin[0] = vTraceResult[0] + (vNormal[0] * 8.0)
		vNewOrigin[1] = vTraceResult[1] + (vNormal[1] * 8.0)
		vNewOrigin[2] = vTraceResult[2] + (vNormal[2] * 8.0)
		
		entity_set_origin(Mine, vNewOrigin)
		
		new Float:vMineAngles[3]
		vector_to_angle(vNormal, vMineAngles)	
		entity_set_vector(Mine, EV_VEC_angles, vMineAngles)
		
		new Float:vBeamEnd[3]
		
		vBeamEnd[0] = vNewOrigin[0] + (vNormal[0] * 8192)
		vBeamEnd[1] = vNewOrigin[1] + (vNormal[1] * 8192)
		vBeamEnd[2] = vNewOrigin[2] + (vNormal[2] * 8192)
		
		new Float:vTracedBeamEnd[3]
		trace_line(-1, vNewOrigin, vBeamEnd, vTracedBeamEnd)
		entity_set_vector(Mine, EV_VEC_vuser1, vTracedBeamEnd)
		
		emit_sound(Mine, CHAN_WEAPON, "weapons/mine_deploy.wav", 1.0, ATTN_NORM, 0, PITCH_NORM)
		emit_sound(Mine, CHAN_ITEM, "weapons/mine_charge.wav", 1.0, ATTN_NORM, 0, PITCH_NORM)
		
		new PlayerTeam = get_user_team(id)
		entity_set_int(Mine, MINE_INT_TEAM, PlayerTeam)
		entity_set_int(Mine, MINE_OWNER, id)
		
		client_print_color(id, print_team_default, "^4%s ^3Land mine is now active.", GAME_NAME)
		
		new param[1]
		param[0] = Mine
		set_task(3.5, "Mine_Activate", 0, param, 1)	
	}
	
	return  
}

public Mine_Activate(param[]) 
{
	new Mine = param[0]
	if(is_valid_ent(Mine)) 
	{
		entity_set_int(Mine, EV_INT_iuser2, 1)
		entity_set_int(Mine, EV_INT_solid, 2)
		entity_set_float(Mine, EV_FL_nextthink, halflife_time() + 0.01)
		emit_sound(Mine, CHAN_ITEM, "weapons/mine_activate.wav", 1.0, ATTN_NORM, 0, PITCH_NORM)
	}
}
	
public Lasermine_Think(Mine)
{
	if(is_valid_ent(Mine)) 
	{
		new TeamColor[3], MineTeam = entity_get_int(Mine, MINE_INT_TEAM)
		switch(MineTeam)
		{
			case 1:
			{
				TeamColor[0] = 255
				TeamColor[1] = 0
				TeamColor[2] = 0
			}
			case 2:
			{
				TeamColor[0] = 0
				TeamColor[1] = 0
				TeamColor[2] = 255
			}
		}
			
		new Float:vOrigin[3], Float:vEnd[3]
		entity_get_vector(Mine, EV_VEC_origin, vOrigin)
		entity_get_vector(Mine, EV_VEC_vuser1, vEnd)
		
		message_begin(MSG_BROADCAST, SVC_TEMPENTITY) 
		write_byte(0)
		write_coord(floatround(vOrigin[0]))
		write_coord(floatround(vOrigin[1]))
		write_coord(floatround(vOrigin[2]))
		write_coord(floatround(vEnd[0]))
		write_coord(floatround(vEnd[1]))
		write_coord(floatround(vEnd[2]))
		write_short(beam)
		write_byte(0)
		write_byte(0)
		write_byte(3)
		write_byte(5)
		write_byte(0)
		write_byte(TeamColor[0])
		write_byte(TeamColor[1])
		write_byte(TeamColor[2])
		write_byte(255)
		write_byte(0)
		message_end()
		
		if(entity_get_int(Mine, EV_INT_iuser2) == 1) 
		{	
			if(entity_get_float(Mine, EV_FL_health) <= 500) 
			{
				Detonate_Mine(Mine)
				return PLUGIN_CONTINUE;
			}
			else
			{
				new Float:vOrigin[3], Float:vEnd[3]
				entity_get_vector(Mine, EV_VEC_origin, vOrigin)
				entity_get_vector(Mine, EV_VEC_vuser1, vEnd)	
					
				new Float:vTrace[3], id = trace_line(Mine, vOrigin, vEnd, vTrace)		
				if(is_user_connected(id) && is_user_alive(id)) 
				{	
		
					new VictimTeam = get_user_team(id)
					new MineTeam = entity_get_int(Mine, MINE_INT_TEAM)
					
					if(VictimTeam != MineTeam)
					{
					
						new MineOwner = entity_get_int(Mine, MINE_OWNER)
					
						WC3_Damage( id, MineOwner, MINE_DAMAGE, CSW_HEGRENADE, HITGROUP_GENERIC );
					
						emit_sound(id, CHAN_WEAPON, "debris/beamstart9.wav", 1.0, ATTN_NORM, 0, PITCH_NORM)
						
						Detonate_Mine(Mine);
						return PLUGIN_CONTINUE;
					}
				}
					
			}
		}
	}
	entity_set_float(Mine, EV_FL_nextthink, halflife_time() + 0.01);
	return PLUGIN_HANDLED;
}

Detonate_Mine(Mine) 
{
	new Float:vOrigin[3]
	entity_get_vector(Mine, EV_VEC_origin, vOrigin)

	message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
	write_byte(99)
	write_short(Mine)
	message_end()

	message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
	write_byte(3)
	write_coord(floatround(vOrigin[0]))
	write_coord(floatround(vOrigin[1]))
	write_coord(floatround(vOrigin[2]))
	write_short(boom)
	write_byte(50)
	write_byte(15)
	write_byte(0)
	message_end()

	radius_damage(vOrigin, 1, 50)
	remove_entity(Mine)
	
	return 
	
}


