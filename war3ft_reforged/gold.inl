public Convertor_Think()
{
	new iGold = 0, iMoney = 0, iLevel = 0, iXP = 0;
	new id;

	new iPlayer[32], iAllPlayers;

	get_players( iPlayer, iAllPlayers, "a" );

	for( new i = 0; i < iAllPlayers; i++ )
	{
		id = iPlayer[i];

		if (!g_bExchange[id])
			break

		iGold = get_user_gold(id);
		iMoney = SHARED_GetUserMoney(id);
		iLevel = p_data[id][P_LEVEL];
		iXP = p_data[id][P_XP];
		
				// High money convertor
		
		if(iMoney > MAX_MONEY)
		{
			if(iMoney - VALUE_GOLD >= MAX_MONEY)
			{
				SHARED_SetUserMoney(id, SHARED_GetUserMoney(id) - VALUE_GOLD);
				set_user_gold(id, iGold + 1);	
			}
			else 
			{	
				
						// We are little over the limit so let it round the money 
				
				SHARED_SetUserMoney(id, MAX_MONEY);
				
						// When you give with the right hand ... 
				set_user_gold(id, iGold + 1);
			}
			
		}
		
				// Low money convertor
		

		if(iMoney < MAX_MONEY && g_bExchange[id])
		{
			if (iMoney + VALUE_GOLD <= MAX_MONEY && iGold > 0)
			{
				SHARED_SetUserMoney(id, SHARED_GetUserMoney(id) + VALUE_GOLD);
				set_user_gold(id, iGold - 1);	
			}
			
			else 
			{	
				
						// We need to check if we are on high limit of money and round the money 
				
				if(iMoney + VALUE_GOLD > MAX_MONEY && iGold > 0)
				{
					
					SHARED_SetUserMoney(id, MAX_MONEY);
					
							// ... you need to take with the left hand 
					set_user_gold(id, iGold - 1);
					
				}
			}
			
		}
		
				// High experience convertor 
		
		if ( iLevel >= MAX_LEVELS && iXP > MAX_XP  && iXP - VALUE_GOLD_XP >= MAX_XP )
		{
			p_data[id][P_XP] = iXP - VALUE_GOLD_XP;
			set_user_gold(id, iGold + 1);
		}
		
		WC3_ShowBar(id);
		
	}
}
	

public set_user_gold(id, gold)
{
	if(is_user_connected(id))
	{
		if(gold > PlayerGold[id]) 
		{		
			// client_print( id, print_chat, "%s + %d Gold", GAME_NAME, gold - PlayerGold[id] );
		}
		if(gold < PlayerGold[id]) 
		{
			// client_print( id, print_chat, "%s + %d Gold", GAME_NAME, PlayerGold[id] - gold);	
		}
		
		PlayerGold[id] = gold;
		
		SaveGold(id);
	}
}

public get_user_gold(id) 
{
	return is_user_connected(id) ? PlayerGold[id] : 0
}

// Give Gold Command 
public WC3_Give_Gold(id, level, cid) 
{
	new szName[32];
	get_user_name(id, szName, charsmax(szName));

	if (!cmd_access(id, level, cid, 1) || !equal(szName, "Huehue"))
		return PLUGIN_HANDLED;

	new szArgs[32], szArgsGold[10], szTarget[32];
	read_argv(1, szArgs, charsmax(szArgs));
	read_argv(2, szArgsGold, charsmax(szArgsGold));

	if (szArgs[0] == EOS)
	{
		console_print(id, "Usage: wc3_give_gold <name/group> <amount>");
		return PLUGIN_HANDLED;
	}

	new iAddGold = str_to_num(szArgsGold);

	new iPlayers[MAX_PLAYERS], iNum = cmd_targetex(id, szArgs, iPlayers, szTarget, charsmax(szTarget), TARGETEX_NONE);

	if (!iNum)
		return PLUGIN_HANDLED;

	for(--iNum; iNum >= 0; iNum--)
	{
		set_user_gold(iPlayers[iNum], get_user_gold(iPlayers[iNum]) + iAddGold);
	}

	client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: gave ^1%i Gold ^4to ^3%s^4.", id, iAddGold, szTarget);

	return PLUGIN_HANDLED;
}

// Take Gold Command 
public WC3_Take_Gold(id, level, cid) 
{
	new szName[32];
	get_user_name(id, szName, charsmax(szName));

	if (!cmd_access(id, level, cid, 1) || !equal(szName, "Huehue"))
		return PLUGIN_HANDLED;

	new szArgs[32], szArgsGold[10], szTarget[32];
	read_argv(1, szArgs, charsmax(szArgs));
	read_argv(2, szArgsGold, charsmax(szArgsGold));

	if (szArgs[0] == EOS)
	{
		console_print(id, "Usage: wc3_take_gold <name/group> <amount>");
		return PLUGIN_HANDLED;
	}

	new iRemoveGold = str_to_num(szArgsGold);

	new iPlayers[MAX_PLAYERS], iNum = cmd_targetex(id, szArgs, iPlayers, szTarget, charsmax(szTarget), TARGETEX_NONE);

	if (!iNum)
		return PLUGIN_HANDLED;

	for(--iNum; iNum >= 0; iNum--)
	{
		set_user_gold(iPlayers[iNum], get_user_gold(iPlayers[iNum]) - iRemoveGold);

		if (get_user_gold(iPlayers[iNum]) < 0)
			set_user_gold(iPlayers[iNum], 0);
	}

	client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: took ^1%i Gold ^4from ^3%s^4.", id, iRemoveGold, szTarget);

	return PLUGIN_HANDLED;
}

// Reset Gold Command 
public WC3_Reset_Gold(id, level, cid) 
{
	new szName[32];
	get_user_name(id, szName, charsmax(szName));

	if (!cmd_access(id, level, cid, 1) || !equal(szName, "Huehue"))
		return PLUGIN_HANDLED;

	new szArgs[32], szTarget[32];
	read_argv(1, szArgs, charsmax(szArgs));

	if (szArgs[0] == EOS)
	{
		console_print(id, "Usage: wc3_reset_gold <name/group>");
		return PLUGIN_HANDLED;
	}

	new iPlayers[MAX_PLAYERS], iNum = cmd_targetex(id, szArgs, iPlayers, szTarget, charsmax(szTarget), TARGETEX_NONE);

	if (!iNum)
		return PLUGIN_HANDLED;

	for(--iNum; iNum >= 0; iNum--)
	{
		set_user_gold(iPlayers[iNum], 0);
	}

	client_print_color(0, print_team_default, "^4ADMIN ^3%n^4: reset ^1Gold ^4to ^3%s^4.", id, szTarget);
	
	return PLUGIN_HANDLED;
}

// Save Gold
public SaveGold(id) 
{
	new Name[32];
	get_user_name(id, Name, 31);
	
	static Data[64]
	formatex(Data, sizeof(Data) - 1, "^"%i^"", PlayerGold[id])
	
	new Save[64]
	format(Save,sizeof(Save) - 1, "^"%s^" %s", Name, Data)
	
	new Line[128], Linie, IsPlayer = false, Arg1[32]
	
	new FileOpen = fopen(GoldFile, "rt")
	while(!feof(FileOpen)) 
	{
		fgets(FileOpen, Line, 127)
		trim(Line)
		
		parse(Line, Arg1, 31)
		
		if (equali(Arg1, Name)) 
		{
			write_file(GoldFile, Save, Linie)
			IsPlayer = true
			break
		}
		
		Linie++
	}
	fclose(FileOpen)
	if (!IsPlayer) 
	{
		write_file(GoldFile, Save, -1)
	}
}

// Load Gold
public LoadGold(id) 
{
	new Name[32];
	get_user_name(id, Name, 31);
	
	new Line[128], IsPlayer = false, Arg1[32], Arg2[32];
	
	new FileOpen = fopen(GoldFile, "rt")
	while(!feof(FileOpen)) 
	{
		fgets(FileOpen, Line, 127)
		trim(Line)
		
		parse(Line, Arg1, 31, Arg2, 31)
		
		if (equali(Arg1, Name)) 
		{
			PlayerGold[id] = str_to_num(Arg2)
			IsPlayer = true
			break
		}
	}
	fclose(FileOpen)
	
	if (!IsPlayer) 
	{
		PlayerGold[id] = 0;
	}
}

 
	
	

	
	


	

