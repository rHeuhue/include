#if defined _mk_stock_included 
	#endinput
#endif

#define _mk_stock_included 

#include <amxmodx>


stock Market_CountAllOffers()
{
	new count = 0;
	new data[mpArray];
	new size = ArraySize(g_marketplace_offers);

	for(new i = 0; i< size; i++)
	{
		ArrayGetArray(g_marketplace_offers, i, data)
		
		if ( !data[MP_FOR] && data[MP_STATUS] )
			count++
	}
	
	return count;
}
stock Market_CountOffersFor( const id )
{
	new count = 0;
	new data[mpArray];
	new size = ArraySize(g_marketplace_offers);

	if (!size) return 0;

	for(new i = 0; i< size; i++)
	{
		ArrayGetArray(g_marketplace_offers, i, data)
		
		if ( data[MP_FOR] == id && data[MP_STATUS])
			count++
	}
	
	return count;
}
stock bool:check_array_value(Array: g_arr, value)
{
	if (value < 0 || value >= ArraySize(g_arr))
		return false;
		
	return true;
}

bool:IsStrFloat(string[])
{
	new len = strlen(string);
	for ( new i = 0; i < len; i++ )
	{
		switch ( string[i] )
		{
			case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '-':	continue;
			default:							return false;
		}
	}
	
	return true;
}

stock bool:checkOfferByType(id, type, check, playerCoins, price) {
	switch (type) {
		case 1: {
			if (check !=2) {
				PrintMessage("[MarketError] Type = %d, Check != 2", type)

				Print(id, "%L", id, "CSRE_MARKETPLACE_ERROR")
				return false;
			}
		}
		case 0: {
			if (check != 1 || playerCoins < price) {
				PrintMessage("[MarketError] Type = %d, Check != 1 OR %d < %d", type, playerCoins, price)

				Print(id, "%L", id, "CSRE_MARKETPLACE_NOCOINS")
				return false;
			}
		}
	}

	return true;
}