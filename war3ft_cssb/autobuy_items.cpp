/*
*	����-������� ���������
*/

//-----------------������� ������� ����������� � cssbWar3ftMod.sma-----------------------BEGIN {
public abi_ClientConnect(idUser)
{


	arriShopAutoItems[idUser][ITEM_SLOT_ONE]	= ITEM_NONE;
	arriShopAutoItems[idUser][ITEM_SLOT_TWO] = ITEM_NONE;
	arriShopAutoItems[idUser][ITEM_SLOT_THREE] = ITEM_NONE;
	
}

//=============================================================================
//=============================================================================
//=============================================================================

//-----------------������� ������� ����������� � cssbWar3ftMod.sma-----------------------END }

//������������� ����������
public abi_InitDataAutoBuy(idUser)//��������� � war3ft.inl (WC3_PlayerInit( idUser ))
{
	
	bAutoBuyOnOff[idUser] = false;
	
}

//����������� ���� ���� ��� ��������� ���������������
public abi_InitLangAllMenus()//��������� � war3ft.inl (public WC3_Init())
{
	
	new iTotalLanguages = get_langsnum();
	new lang[3], menu[256];
	new curMenuId = -1, highestMenuId = -1;
	new iLang, iMenu;

	// Loop through every menu
	for ( iMenu = 0; iMenu < MAX_NUM_AUTO_MENUS; iMenu++ )
	{
		// Register the menu names for each language
		for ( iLang = 0; iLang < iTotalLanguages; iLang++ )
		{
			get_lang ( iLang, lang );

			if ( lang_exists( lang ) )
			{
				formatex ( menu, 255, "%L", lang, MENU_TITLES_AUTOBUY_ITEMS[iMenu] );
				curMenuId = register_menuid ( menu );
				
				if ( curMenuId > highestMenuId )
				{
					register_menucmd ( curMenuId, 1023, MENU_CALLBACK_AUTOBUY_ITEMS_ALL[iMenu] );
					highestMenuId = curMenuId;
				}
			}
		}// End language loop
	}// End menu loop
}


//-----------------������� ����-----------------------BEGIN {
//����� ��������� ����������� ����
fShowMenuAutoBuyBase(idUser)
{
	
	new iPos = 0;
	new szMenuData[512];
	new szColorNumber[16] = "\y";
	new szColorText[16] = "\w";

//	new idKeysMenu = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<9);
	new idKeysMenu = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<9);

	//���������
	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "%L^n^n",LANG_PLAYER,"MENU_ID_BASE_AUTOBUY_ITEMS");
	//������
	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s1. %s%L^n^n",szColorNumber,szColorText,LANG_PLAYER,"ID_AUTOBUY_ITEMS");
	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s2. %s%L^n",szColorNumber,szColorText,LANG_PLAYER,"MENU_ID_ADD_AUTOBUY_ITEMS");
	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s3. %s%L^n^n",szColorNumber,szColorText,LANG_PLAYER,"MENU_ID_DELETE_AUTOBUY_ITEMS");
	
	if(bAutoBuyOnOff[idUser] == false )
		iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s4. %s%L [ \r%L\w ]^n^n",szColorNumber,szColorText,LANG_PLAYER,"ID_AUTOBUY_ITEMS_ON_OFF",LANG_PLAYER,"ID_ENABLED");
	else
		iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s4. %s%L [ \r%L\w ]^n^n",szColorNumber,szColorText,LANG_PLAYER,"ID_AUTOBUY_ITEMS_ON_OFF",LANG_PLAYER,"ID_DISABLED");

//	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s5. %s%L^n",szColorNumber,szColorText,LANG_PLAYER,"ID_AUTOBUY_ITEMS_SAVE");
		
	//����� �����
	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "^n\d0. %L",LANG_PLAYER,"WORD_EXIT");

	new szMenuName[128];
	format(szMenuName, charsmax(szMenuName), "%L",LANG_PLAYER,"MENU_ID_BASE_AUTOBUY_ITEMS");
	show_menu(idUser,idKeysMenu,szMenuData,-1,szMenuName);

	return PLUGIN_CONTINUE;
}
//����� ����������� ���� ��� ���������� ��������� � ����-�������
fShowMenuAutoBuyAdd(idUser, iPage = 0)
{
	
	new idMenu,szNumber[64],szMenuData[256];
	
	//�������� �������� ����
	formatex(szMenuData, charsmax(szMenuData), "\y%L", LANG_PLAYER, "MENU_ID_ADD_AUTOBUY_ITEMS");
	idMenu = menu_create(szMenuData, "_Callback_SUB_MENU_AddABI");

	new iMaxShopmenuItems = 27;

	if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0)
	{
		if(get_pcvar_num(CVAR_wc3_shopmenu4_vip) == 0)
		{
			iMaxShopmenuItems = MAX_SHOPMENU_ITEMS;
		}
		else if(get_pcvar_num( CVAR_wc3_shopmenu4 ) > 0 && (get_user_flags(idUser) & fVipShop4()))
		{
			iMaxShopmenuItems = MAX_SHOPMENU_ITEMS;
		}
	}


	// ���������� ������� � ����
	for(new i = 0; i < iMaxShopmenuItems; i++)
	{
		new szItemName[32],szNameItemMenu[256];
		LANG_GetItemName(i, idUser, szItemName, 31, true );

		formatex(szNumber, charsmax(szNumber), "%d", i);

		for(new iItem = 0; iItem < MAX_PLAYER_ITEMS; iItem++)
		{
			if(arriShopAutoItems[idUser][iItem] == i)
			{
				formatex(szNameItemMenu, charsmax(szNameItemMenu), "%s [\r%L\w]",szItemName,LANG_PLAYER,"ID_ADD");
				break;
			}
			else
			{
				formatex(szNameItemMenu, charsmax(szNameItemMenu), "%s",szItemName);
			}
		}

		menu_additem(idMenu,szNameItemMenu,szNumber,0,-1);
	}
	
	// ���� ��� ��������� � ����
	if (menu_items(idMenu) <= 0)
	{
		menu_destroy(idMenu);
		return;
	}
			
	//������ ���� (����� - ��������� - �����)
	formatex(szMenuData, charsmax(szMenuData), "\w%L", LANG_PLAYER, "WC3_MENU_BACK");
	menu_setprop(idMenu, MPROP_BACKNAME, szMenuData);
	formatex(szMenuData, charsmax(szMenuData), "\w%L", LANG_PLAYER, "WC3_MENU_NEXT");
	menu_setprop(idMenu, MPROP_NEXTNAME, szMenuData);
	formatex(szMenuData, charsmax(szMenuData), "\r%L", LANG_PLAYER, "WC3_MENU_BACK_BASE");
	menu_setprop(idMenu, MPROP_EXITNAME, szMenuData);
	
	menu_display(idUser, idMenu, iPage);
}

//����� ����������� ���� ��� �������� ��������� �� ����-�������
fShowMenuAutoBuyDelete(idUser)
{
	
	new iPos = 0;
	new szMenuData[512];
	new szColorNumber[16] = "\y";
	new szColorText[16] = "\w";

	new idKeysMenu = (1<<0)|(1<<1)|(1<<2)|(1<<9);

	//���������
	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "\y%L^n^n",LANG_PLAYER,"MENU_ID_DELETE_AUTOBUY_ITEMS");
	
	new bool:bIsSelect = false;

	for(new i = 0; i < MAX_PLAYER_ITEMS; i++)
	{
		new iNumberItem = arriShopAutoItems[idUser][i];

		if(fHasItemAutoBuy(idUser,iNumberItem) != ITEM_NONE )
		{
			new szItemName[32];
			LANG_GetItemName(iNumberItem, idUser, szItemName, 31, true );

			iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "%s%d. %s%s^n",szColorNumber,i+1,szColorText,szItemName);

			bIsSelect = true;
		}
	}
		
	//������� � ������� ����
	iPos += format(szMenuData[iPos], charsmax(szMenuData)-iPos, "^n\r0. \r%L",LANG_PLAYER,"WC3_MENU_BACK_BASE");

	if(bIsSelect == true)
	{
		new szMenuName[128];
		format(szMenuName, charsmax(szMenuName), "%L",LANG_PLAYER,"MENU_ID_DELETE_AUTOBUY_ITEMS");
		show_menu(idUser,idKeysMenu,szMenuData,-1,szMenuName);
	}
	else
	{
		//client_print(idUser,print_chat,"Not Items");

		fShowMenuAutoBuyBase(idUser);
	}

	return PLUGIN_CONTINUE;
}


//������� ������ ������� � �������� ����
public _Callback_MENU_BaseABI(idUser,iKey)
{
	
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

	if(iKey == 9) //�����
		return PLUGIN_HANDLED;

	switch (iKey)
	{
		case 0://������ ���������� ��������
		{
			fBuyAllItems(idUser);
		}
		case 1://�������� �������� � ����-�������
		{
			fShowMenuAutoBuyAdd(idUser);
		}
		case 2://������� �������� �� ����-�������
		{
			fShowMenuAutoBuyDelete(idUser);
		}
		case 3://����-�������: [���/����]
		{
			if(bAutoBuyOnOff[idUser] == false) //��������� ����-�������
			{
				bAutoBuyOnOff[idUser] = true;

				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_AUTOBUY_ON");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}
			else//����������
			{
				bAutoBuyOnOff[idUser] = false;

				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_AUTOBUY_OFF");
				cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
			}

			fShowMenuAutoBuyBase(idUser);
		}
		case 4://��������� ���������
		{
		}
	}

//	client_print(idUser,print_chat,"iKey: %d",iKey);

	return PLUGIN_HANDLED;
}
//������� ������ ������� � ��� ���� ���������� ���������
public _Callback_SUB_MENU_AddABI(idUser, idMenu, idItem)
{
	
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

	// ������� � ������� ����
	if (idItem == MENU_EXIT)
	{
		fShowMenuAutoBuyBase(idUser);

		menu_destroy(idMenu);
		return PLUGIN_HANDLED;
	}
	
	static _access, szInfoMenu[8], callback;
	menu_item_getinfo(idMenu, idItem, _access, szInfoMenu, sizeof(szInfoMenu) - 1, _, _, callback);
	
	new iNumberItem = str_to_num(szInfoMenu);
	
	for(new iItem = 0; iItem < MAX_PLAYER_ITEMS; iItem++)
	{
		if(fHasItemAutoBuy(idUser,arriShopAutoItems[idUser][iItem]) == ITEM_NONE )
		{
			arriShopAutoItems[idUser][iItem] = iNumberItem;
			break;
		}
	}

	menu_destroy(idMenu);

	fShowMenuAutoBuyAdd(idUser,floatround( float(iNumberItem / 7)) );

	//client_print(0,print_chat,"iNumberItem: %d |idItem: %d",iNumberItem,idItem);	

	return PLUGIN_HANDLED;
}

//������� ������ ������� � ��� ���� �������� ���������
public _Callback_SUB_MENU_DeleteABI(idUser,iKey)
{
	
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

	//������� � ������� ����
	if(iKey == 9)
	{
		fShowMenuAutoBuyBase(idUser);

		return PLUGIN_HANDLED;
	}

	if(iKey >= 3)
		return PLUGIN_HANDLED;

	arriShopAutoItems[idUser][iKey] = ITEM_NONE;

	fShowMenuAutoBuyDelete(idUser);

	//client_print(idUser,print_chat,"iKey: %d",iKey);

	return PLUGIN_HANDLED;
}
//=============================================================================
//=============================================================================
//=============================================================================

//������� ����----------------------------------------END }

//���������� ���� �� ���������� ������� � ������ ����-�������
stock fHasItemAutoBuy(idUser,iItem)
{

	if ( arriShopAutoItems[idUser][ITEM_SLOT_ONE] == iItem )
		return iItem;

	else if ( arriShopAutoItems[idUser][ITEM_SLOT_TWO] == iItem )
		return iItem;

	else if ( arriShopAutoItems[idUser][ITEM_SLOT_THREE] == iItem )
		return iItem;

	return ITEM_NONE;
}

//������� ��� ��������� ����������� � ������ ����-�������
public fBuyAllItems(idUser)
{
	
	for(new iItem = 0; iItem < MAX_PLAYER_ITEMS; iItem++)
	{
		if(fHasItemAutoBuy(idUser,arriShopAutoItems[idUser][iItem]) != ITEM_NONE )
			ITEM_Buy( idUser, arriShopAutoItems[idUser][iItem],true);
	}
}
