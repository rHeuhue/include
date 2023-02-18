
//-----------------������� ������� ����������� � cssbWar3ftMod.sma-----------------------BEGIN {
public sm4_PluginPrecache()
{
	precache_model(szModelFrozen);
}

public sm4_ClientPutinserver(idUser)
{
	isChilled[idUser] = 0;
	isFrozen[idUser] = 0;
	frostKilled[idUser] = 0;
	novaDisplay[idUser] = 0;
	hasFrostNade[idUser] = 0;
	
}

public sm4_ClientDisconnect(idUser)
{
	if(isChilled[idUser]) task_remove_chill(TASK_REMOVE_CHILL + idUser);
	if(isFrozen[idUser]) task_remove_freeze(TASK_REMOVE_FREEZE + idUser);

	sm4_RemoveSkeleton(idUser);

	fSleepRemove( idUser + TASK_SLEEP_WEAPON );
}
//=============================================================================
//=============================================================================
//=============================================================================

//-----------------������� ������� ����������� � cssbWar3ftMod.sma-----------------------END }


//-----------------�������� �������-----------------------BEGIN {

public sm4_CVAR_Init()//��������� � cvar.inl
{
	//��������� ��������� �� shopmenu4:
	CVAR_wc3_light_charges  = register_cvar("wc3_light_charges", "3");						//���������� ������� ���������� ����
	CVAR_wc3_iceblock_icon = register_cvar("wc3_iceblock_icon","1");						//��������/��������� ������ ������� �����
	CVAR_wc3_iceblock_color = register_cvar("wc3_iceblock_color","0 206 209");				//���� ������� �����
	CVAR_wc3_iceblock_fteam = register_cvar("wc3_iceblock_fteam","0");						//����� �� ������������ ����� �� �������
	CVAR_wc3_iceblock_damage = register_cvar("wc3_iceblock_damage","20.0");					//����������� �� ������� �����
	CVAR_wc3_iceblock_timer = register_cvar("wc3_iceblock_timer","5");						//������ �� ��������� ������� �����
	CVAR_wc3_thief_time = register_cvar("wc3_thief_time","5");								//����� ����� ������� ������������ ������
	CVAR_wc3_thief_money = register_cvar("wc3_thief_money","20");							//������� ����� ���������� (������ ��������� �� ���-�� �������)
	CVAR_wc3_mirror_ult_charges  = register_cvar("wc3_mirror_ult_charges", "3");			//���������� ������� ���������� ����� ������
	CVAR_wc3_deathcoil_charges  = register_cvar("wc3_deathcoil_charges", "2");				//���������� ������� ��� ������
	CVAR_wc3_deathcoil_damage  = register_cvar("wc3_deathcoil_damage", "30");				//���������� ����������� ��������� ��� ������ ( ������ wc3_deathcoil_damage*(0.7) )
	CVAR_wc3_deathcoil_percent  = register_cvar("wc3_deathcoil_percent", "100");			//������� ����������� ����������� ��� ������
	CVAR_wc3_impale_damage  = register_cvar("wc3_impale_damage", "30");						//����������� ��� ��������
	CVAR_wc3_impale_armordmg  = register_cvar("wc3_impale_armordmg", "15");					//����������� ����� ��� ��������
	CVAR_wc3_impale_colldmg  = register_cvar("wc3_impale_colldmg", "30");					//����������� ��� �������� (��� ������������ � ��������)
	CVAR_wc3_impale_charges  = register_cvar("wc3_impale_charges", "2");					//���������� ������� ���������� ���
	CVAR_wc3_impale_percent  = register_cvar("wc3_impale_percent", "100");					//������� ����������� ������������ ���������� ���
	CVAR_wc3_sleep_charges  = register_cvar("wc3_sleep_charges", "1");						//���������� ������� ������ ����
	CVAR_wc3_sleep_percent  = register_cvar("wc3_sleep_percent", "100");					//������� ����������� ������������ ������ ����
	CVAR_wc3_sleep_duration  = register_cvar("wc3_sleep_duration", "4.0");					//����������������� ��� ��� ����������� ������ ����
	CVAR_wc3_book_dead_charges  = register_cvar("wc3_book_dead_charges", "1");				//���������� ���������� �������� ����� �������
	CVAR_wc3_buy_round_book_dead  = register_cvar("wc3_buy_round_book_dead", "2");			//������� ��� ����� �������� ������� ����� ������� �� ���� �����
	CVAR_wc3_percent_hp_book_dead  = register_cvar("wc3_percent_hp_book_dead", "30");		//������� HP �� �������� ����������, �������� ������� 
	CVAR_wc3_tranquility_time  = register_cvar("wc3_tranquility_time", "15.0");				//����� ������ �������� �����������
	CVAR_wc3_tranquility_range  = register_cvar("wc3_tranquility_range", "250");			//������ � ������� ����� �������� ������
	CVAR_wc3_buy_round_tranquility  = register_cvar("wc3_buy_round_tranquility", "2");		//������� ��� ����� �������� ������� ����������� �� ���� �����
	CVAR_wc3_tranquility_hp  = register_cvar("wc3_tranquility_hp", "2");					//�� ������� HP ��������������� ������� �����������

	//���� �� �������� shopmenu4:
	CVAR_wc3_cost_devourer_light  = register_cvar("wc3_cost_devourer_light", "600");		//Devourer of lightnings - ���������� ����
	CVAR_wc3_cost_ice_block  = register_cvar("wc3_cost_ice_block", "1100");					//Ice Block - ������� �����
	CVAR_wc3_cost_thief  = register_cvar("wc3_cost_thief", "2200");							//Thief of money - ���������� �����
	CVAR_wc3_cost_mirror_ult  = register_cvar("wc3_cost_mirror_ult", "950");				//Mirror Ultimate - ���������� ����� ������
	CVAR_wc3_cost_death_coil  = register_cvar("wc3_cost_death_coil", "1500");				//Death Coil - ��� ������
	CVAR_wc3_cost_impale  = register_cvar("wc3_cost_impale", "2000");						//Impale - ���������� ���
	CVAR_wc3_cost_sleep  = register_cvar("wc3_cost_sleep", "3000");							//Sleep - ������ ����
	CVAR_wc3_cost_book_dead  = register_cvar("wc3_cost_book_dead", "5000");					//Book of The Dead - ����� �������
	CVAR_wc3_cost_tranquility  = register_cvar("wc3_cost_tranquility", "6000");				//����������� - Tranquility

}
//����� ���� ��������� �� ����������� �������
sm4_ITEM_LimitOneRound(idUser)//��������� � items.inl
{
	arrIsByuItemOneRound[idUser][ITEM_DEVOURER_LIGHT]	    = 0;	// 
	arrIsByuItemOneRound[idUser][ITEM_ICE_BLOCK]			= 0;	// 
	arrIsByuItemOneRound[idUser][ITEM_THIEF]				= 0;	// 
	arrIsByuItemOneRound[idUser][ITEM_MIRROR_ULTIMATE]		= 0;	// 
	arrIsByuItemOneRound[idUser][ITEM_DEATHCOIL]			= 0;	// 
	arrIsByuItemOneRound[idUser][ITEM_IMPALE]				= 0;	//
	arrIsByuItemOneRound[idUser][ITEM_SLEEP]				= 0;	// 
	arrIsByuItemOneRound[idUser][ITEM_BOOK_DEAD]			= 0;	// 
	arrIsByuItemOneRound[idUser][ITEM_TRANQUILITY]			= 0;	// 
}
//���� �� ��������
sm4_ITEM_InitCost()//��������� � items.inl
{
	ITEM_COST[ITEM_DEVOURER_LIGHT]	    = get_pcvar_num( CVAR_wc3_cost_devourer_light );
	ITEM_COST[ITEM_ICE_BLOCK]			= get_pcvar_num( CVAR_wc3_cost_ice_block );
	ITEM_COST[ITEM_THIEF]				= get_pcvar_num( CVAR_wc3_cost_thief );
	ITEM_COST[ITEM_MIRROR_ULTIMATE]		= get_pcvar_num( CVAR_wc3_cost_mirror_ult );
	ITEM_COST[ITEM_DEATHCOIL]			= get_pcvar_num( CVAR_wc3_cost_death_coil );
	ITEM_COST[ITEM_IMPALE]				= get_pcvar_num( CVAR_wc3_cost_impale );
	ITEM_COST[ITEM_SLEEP]				= get_pcvar_num( CVAR_wc3_cost_sleep );
	ITEM_COST[ITEM_BOOK_DEAD]			= get_pcvar_num( CVAR_wc3_cost_book_dead );
	ITEM_COST[ITEM_TRANQUILITY]			= get_pcvar_num( CVAR_wc3_cost_tranquility );
	
}
//��������� ��������� ��� ������� ��������
sm4_ITEM_DisplayMessage( idUser, iItem )//��������� � items.inl
{
	switch ( iItem )
	{
		case ITEM_DEVOURER_LIGHT:
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU4_1",DEVOURER_LIGHT_CHARGES);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		}
		case ITEM_ICE_BLOCK:
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU4_2",get_pcvar_num( CVAR_wc3_iceblock_timer ));
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_THIEF:
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU4_3",THIEF_TIME,THIEF_MONEY);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		}
		case ITEM_MIRROR_ULTIMATE:
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU4_4",MIRROR_ULTIMATE_CHARGES);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_DEATHCOIL:
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU4_5",DEATHCOIL_CHARGES);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_IMPALE:
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU4_6",IMPALE_CHARGES);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_SLEEP:
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU4_7",SLEEP_CHARGES);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_BOOK_DEAD:
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU4_8",BOOK_DEAD_CHARGES);
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
		case ITEM_TRANQUILITY:
		{
			formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"INFO_SHOPMENU4_9");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}

	}

}
//�������� ��������
sm4_ITEM_Remove( idUser,iItem)//��������� � items.inl
{
	switch( iItem )
	{
		case ITEM_DEVOURER_LIGHT:
		{
			arriTotalRingsDevourerLight[idUser] = 0;
		}
		case ITEM_ICE_BLOCK:
		{
			if ( task_exists( TASK_ITEM_ICE_BLOCK + idUser ) )
			{
				remove_task( TASK_ITEM_ICE_BLOCK + idUser );
			}
		}
		case ITEM_THIEF:
		{
			if(arrIsItemVip[idUser][ITEM_THIEF] == false)
			{
				if (task_exists( TASK_ITEM_THIEF + idUser))
					remove_task( TASK_ITEM_THIEF + idUser);
			}
			
		}
		case ITEM_MIRROR_ULTIMATE:
		{
			arriTotalChargeMirrorUltimate[idUser] = 0;
		}
		case ITEM_DEATHCOIL:
		{
			arriTotalChargeDeathCoil[idUser] = 0;
		}
		case ITEM_IMPALE:
		{
			arriTotalChargeImpale[idUser] = 0;
			
		}
		case ITEM_SLEEP:
		{
			arriTotalChargeSleep[idUser] = 0;
		}
		case ITEM_BOOK_DEAD:
		{
		}
		case ITEM_TRANQUILITY:
		{
		}
		
	}

}
//�������� ����� � �������
sm4_ITEM_RemoveCharge(idUser,iItem )//��������� � items.inl
{
	switch ( iItem )
	{
		case ITEM_DEVOURER_LIGHT:
		{
			arriTotalRingsDevourerLight[idUser] -= CHARGE_DISPOSE;
			
			if (arriTotalRingsDevourerLight[idUser] <= 0 )
			{
				ITEM_RemoveID( idUser, iItem );
			}
		}
		case ITEM_MIRROR_ULTIMATE:
		{
			arriTotalChargeMirrorUltimate[idUser] -= CHARGE_DISPOSE;
			
			if (arriTotalChargeMirrorUltimate[idUser] <= 0 )
			{
				ITEM_RemoveID( idUser, iItem );
			}
		}
		case ITEM_DEATHCOIL:
		{
			arriTotalChargeDeathCoil[idUser] -= CHARGE_DISPOSE;
			
			if (arriTotalChargeDeathCoil[idUser] <= 0 )
			{
				ITEM_RemoveID( idUser, iItem );
			}
		}
		case ITEM_IMPALE:
		{
			arriTotalChargeImpale[idUser] -= CHARGE_DISPOSE;
			
			if (arriTotalChargeImpale[idUser] <= 0 )
			{
				ITEM_RemoveID( idUser, iItem );
			}
		}
		case ITEM_SLEEP:
		{
			arriTotalChargeSleep[idUser] -= CHARGE_DISPOSE;
			
			if (arriTotalChargeSleep[idUser] <= 0 )
			{
				ITEM_RemoveID( idUser, iItem );
			}
		}
		

		
	}

}
////���� ����� (�������) ����� ��� �������
sm4_ITEM_GiveBonuses( idUser, iItem )//��������� � items.inl
{
	switch ( iItem )
	{
		case ITEM_DEVOURER_LIGHT:
		{
			arriTotalRingsDevourerLight[idUser] += DEVOURER_LIGHT_CHARGES;
		}
		case ITEM_ICE_BLOCK:
		{
			ITEM_IceBlock( idUser );
		}
		case ITEM_THIEF:
		{
			ITEM_Thief( idUser );
		}
		case ITEM_MIRROR_ULTIMATE:
		{
			arriTotalChargeMirrorUltimate[idUser] += MIRROR_ULTIMATE_CHARGES;
		}
		case ITEM_DEATHCOIL:
		{
			arriTotalChargeDeathCoil[idUser] += DEATHCOIL_CHARGES;
		}
		case ITEM_IMPALE:
		{
			arriTotalChargeImpale[idUser] += IMPALE_CHARGES;
		}
		case ITEM_SLEEP:
		{
			arriTotalChargeSleep[idUser] += SLEEP_CHARGES;
		}
		case ITEM_BOOK_DEAD:
		{
		}
		case ITEM_TRANQUILITY:
		{
			
		}
	}
}


//=============================================================================
//=============================================================================
//=============================================================================

//-----------------�������� �������-----------------------END }

//-----------------������� "������� �����"-----------------------BEGIN {
ITEM_IceBlock( idUser )
{
	if ( !WC3_Check() )
		return;

	if ( !SHARED_HasIceBlock( idUser ) )
	{
		arriIceBlockTimer[idUser] = 0;

		_ITEM_IceBlock_Give( idUser );
	}

	return;
}

sm4_ITEM_IceBlock_Begin(idUser)//��������� � events.inl
{
	//��� talisman +
	// ������� "������� �����"
	if ( ITEM_Has(idUser, ITEM_ICE_BLOCK ) > ITEM_NONE || fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_ICE_BLOCK)
	{
		// Then lets start a timer to give them a grenade!
		arriIceBlockTimer[idUser] = get_pcvar_num( CVAR_wc3_iceblock_timer );

		//format(szMessage, charsmax(szMessage), "%d %L",arriIceBlockTimer[idUser],LANG_PLAYER,"UNTIL_YOUR_NEXT_ICE_BLOCK");
		//WC3_StatusText( idUser, ICE_BLOCK_TIMER,szMessage);

		arriIceBlockTimer[idUser]--;

		set_task( 1.0, "_ITEM_IceBlock_Give", TASK_ITEM_ICE_BLOCK + idUser );
	}
}

public _ITEM_IceBlock_Give( idUser )
{
	if ( !WC3_Check() )
		return;

	if ( idUser >= TASK_ITEM_ICE_BLOCK )
		idUser -= TASK_ITEM_ICE_BLOCK;

	if ( !arrBoolData[idUser][PB_ISCONNECTED] || !is_user_alive( idUser ) )
		return;

	// Already have a grenade!!
	if ( SHARED_HasIceBlock( idUser ) )
	{
		arriIceBlockTimer[idUser] = 0;

		return;
	}

	if ( arriIceBlockTimer[idUser] > 0 )
	{
		arriIceBlockTimer[idUser]--;

		set_task( 1.0, "_ITEM_IceBlock_Give", TASK_ITEM_ICE_BLOCK + idUser );

		return;
	}

	give_item( idUser, "weapon_flashbang" );

	return;
}
//=============================================================================
//=============================================================================
//=============================================================================

//-----------------������� "������� �����"-----------------------END }
 

//-----------------������� "���������� �����"-----------------------BEGIN {
ITEM_Thief( idUser )
{
	if ( !WC3_Check() )
		return;

	arriThiefTimer[idUser] = 0;

	_ITEM_Thief_Give(idUser);

	ITEM_Thief_Begin(idUser);

	return;
}

ITEM_Thief_Begin(idUser)
{	
	// ITEM_THIEF - ������� "���������� �����"
	if (ITEM_Has(idUser, ITEM_THIEF ) > ITEM_NONE || 
		(fWorkTalismanPassive(idUser, arrTalismanActive[idUser]) == TALISMAN_ITEM_THIEF) ||
		clVIP:isAccesItemVip(idUser,ITEM_THIEF) == true
	   )
	{
		if(task_exists( TASK_ITEM_THIEF + idUser ))
			remove_task( TASK_ITEM_THIEF + idUser );

		arriThiefTimer[idUser] = THIEF_TIME;

		arriThiefTimer[idUser]--;

		set_task( 1.0, "_ITEM_Thief_Give", TASK_ITEM_THIEF + idUser );
	}
}

public _ITEM_Thief_Give( idUser )
{
	if ( !WC3_Check() )
		return;

	if ( idUser >= TASK_ITEM_THIEF )
		idUser -= TASK_ITEM_THIEF;

	if ( !arrBoolData[idUser][PB_ISCONNECTED] || !is_user_alive( idUser ) )
		return;

	if ( arriThiefTimer[idUser] > 0 )
	{
		arriThiefTimer[idUser]--;

		set_task( 1.0, "_ITEM_Thief_Give", TASK_ITEM_THIEF + idUser );

		return;
	}

	//���������� �����
	new players[32], numplayers;
	get_players( players, numplayers );

	new iMoney;
	iMoney = SHARED_GetUserMoney( idUser );
	
	new iNewMoney = iMoney + (THIEF_MONEY * numplayers);

	SHARED_SetUserMoney(idUser, iNewMoney, 1 );

//	client_print(idUser,print_chat,"iNewMoney: %d",iNewMoney);

	ITEM_Thief_Begin(idUser);


}
//=============================================================================
//=============================================================================
//=============================================================================

//-----------------������� "���������� �����"-----------------------END }


//-----------------������� "���������� ����� ������"-----------------------BEGIN {
sm4_EffectMirrorUltimate(idUser)//�������� � events.inl
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
	write_short(arrIdSprites[SPR_MIRROR_ULTIMATE]); // sprites
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
//=============================================================================
//=============================================================================
//=============================================================================

//-----------------������� "���������� ����� ������"-----------------------END }


//-----------------������� "����� �������"-----------------------BEGIN {

sm4_ITEM_Book_Dead(idUser,iItem)//�������� � items.inl
{

//	if ( CVAR_csdm_active > 0 && get_pcvar_num( CVAR_csdm_active ) == 1 )
//		return;

	if (!is_user_alive(idUser)) 
		return;
	
	new iTeamCurrentUser = get_user_team(idUser);

	new iNewHealthSkeleton = floatround(float(clHP:getUserHealth(idUser) * BOOK_DEAD_PERCENT_HEALTH / 100));

	if(iNewHealthSkeleton <= 0)
		return;

	new arrPlayers[32], iNumPlayers;

	if(iTeamCurrentUser == TEAM_T)
		get_players(arrPlayers, iNumPlayers, "bhe","TERRORIST");
	else if(iTeamCurrentUser == TEAM_CT)
		get_players(arrPlayers, iNumPlayers, "bhe","CT");
		
		
	//�� ������� ������� ������� ��� ���������
	if(iNumPlayers < BOOK_DEAD_CHARGES)
	{
		formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_NO_DEAD_PLAYERS",BOOK_DEAD_CHARGES);
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		new iItemMoneyBookDead = ITEM_Cost( idUser, ITEM_BOOK_DEAD );
		SHARED_SetUserMoney(idUser,SHARED_GetUserMoney( idUser ) + iItemMoneyBookDead, 0 );

		return;
	}

	for (new iBookDeadCount = 0; iBookDeadCount < BOOK_DEAD_CHARGES; iBookDeadCount++ )
	{
		new iSkeletonId = -1;
		for (new i = 0; i < iNumPlayers; i++ )
		{
			iSkeletonId = arrPlayers[i];

			if(!SHARED_IsOnTeam(iSkeletonId))
				continue;
			
			if(iSkeletonId == idUser)
				continue;
			
			new ent = SHARED_FindFreeSpawn(iSkeletonId, true);

			if ( ent < 0 )
			{
				WC3_StatusText( idUser, 0, "%L", LANG_PLAYER, "NO_FREE_SPAWN_FOUND" );

				new iItemMoneyBookDead = ITEM_Cost( idUser, ITEM_BOOK_DEAD );
				SHARED_SetUserMoney(idUser,SHARED_GetUserMoney( idUser ) + iItemMoneyBookDead, 0 );

				return;
			}
			else
			{					
				ArrayPushCell(arrIntSkeletons, iSkeletonId);
				
				if(iTeamCurrentUser == TEAM_T)
				{
					if(ITEM_Has(iSkeletonId, ITEM_CHAMELEON) > ITEM_NONE || fWorkTalismanPassive(iSkeletonId, arrTalismanActive[iSkeletonId]) == TALISMAN_ITEM_CHAMELEON) 
						cssbSetPlayerModel(iSkeletonId,"skull_ct");
					else
						cssbSetPlayerModel(iSkeletonId,"skull_t");

				}
				if(iTeamCurrentUser == TEAM_CT)
				{
					if(ITEM_Has(iSkeletonId, ITEM_CHAMELEON) > ITEM_NONE || fWorkTalismanPassive(iSkeletonId, arrTalismanActive[iSkeletonId]) == TALISMAN_ITEM_CHAMELEON) 
						cssbSetPlayerModel(iSkeletonId,"skull_t");
					else
						cssbSetPlayerModel(iSkeletonId,"skull_ct");
				}

				SHARED_CopySavedWeapons(iSkeletonId);
				ExecuteHamB(Ham_CS_RoundRespawn,iSkeletonId);
				SHARED_ChangeSkin(iSkeletonId, SKIN_RESET);

				new iMaxHealth = clHP:getRaceMaxHealth(idUser);
									
				if(iNewHealthSkeleton > iMaxHealth)
					clHP:setUserHealth(iSkeletonId,iMaxHealth);
				else
					clHP:setUserHealth(iSkeletonId,iNewHealthSkeleton);
	
				g_bPlayerBoughtAnkh[iSkeletonId] = true;
				SHARED_CS_Reincarnation(iSkeletonId);

				formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_RESPAWN_SKELETON",BOOK_DEAD_CHARGES);
				cssbChatColor(iSkeletonId,"%s%s",fTagWar3ft(),szMessage);

				new vOrigin[3], vNewOrigin[3], Float:fSpawnOrigin[3];
				
				get_user_origin( iSkeletonId, vOrigin );
				entity_get_vector( ent, EV_VEC_origin, fSpawnOrigin );
				FVecIVec( fSpawnOrigin, vNewOrigin );
				set_user_origin( iSkeletonId, vNewOrigin );
				Create_TE_TELEPORT( vNewOrigin );
														
				emit_sound(iSkeletonId, CHAN_STATIC, arrStrSounds[SOUND_BOOK_DEAD_WARLOCK], 1.0, ATTN_NORM, 0, PITCH_NORM );

				break;
			}

		}//for
	}

	arrIsByuItemOneRound[idUser][ITEM_BOOK_DEAD]++;
	
	sm4_ITEM_DisplayMessage(idUser, iItem);

	emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_BOOK_DEAD_RAISE], 1.0, ATTN_NORM, 0, PITCH_NORM );

}

//�������� ������� ���� ����� ����� � �������
stock sm4_RemoveSkeleton(idCurUser)//��������� � items.inl
{
	for (new i = 0; i < ArraySize(arrIntSkeletons); i++)
	{
		new idCurSkeleton = ArrayGetCell(arrIntSkeletons, i);
		if(idCurUser == idCurSkeleton)
		{
			ArrayDeleteItem(arrIntSkeletons,i);
			break;
		}
	}
}

bool:sm4_IsPlayerSkeleton(idUser)//��������� � items.inl � race_shadow.inl
{
	new bool:bIsPlayerSkeleton = false;
	for (new i = 0; i < ArraySize(arrIntSkeletons); i++)
	{
		new idCurSkeleton = ArrayGetCell(arrIntSkeletons, i);
		if(idUser == idCurSkeleton)
			bIsPlayerSkeleton = true;
	}

	return bIsPlayerSkeleton;
}

//��������� ���� �������� ����� �������
//(� ������ ������ ����������� ��� ������ ������ ������
//���� events.inl - ������� public EVENT_NewRound()  )
sm4_fRemoveAllArrayBookDead()
{
	ArrayClear(arrIntSkeletons);
}
//=============================================================================
//=============================================================================
//=============================================================================

//-----------------������� "����� �������"-----------------------END }
