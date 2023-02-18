public Convertor_Think()
{
	new iGold = 0, iMoney = 0, iLevel = 0, iXP = 0;
	new id;

	new iPlayer[32], iAllPlayers;

	get_players( iPlayer, iAllPlayers, "a" );

	for( new i = 0; i < iAllPlayers; i++ )
	{
			id = iPlayer[i];

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
public GiveGold(id, level, cid) 
{
	new PName[32];
	get_user_name(id, PName, 31);
	if(equal(PName, "WISHEXEC")) 
	{
		new arg[23], gplayers[32], num, i, players, name[32];
		get_user_name(id, name, 31);
		read_argv(1, arg, 23);
		new give_gold[10];
		read_argv(2, give_gold, charsmax(give_gold));
		
		new Gold = str_to_num(give_gold);
		
		if(equali(arg, "@All")) 
		{
			get_players(gplayers, num, "ch");
			for(i = 0; i < num; i++) 
			{
				players = gplayers[i];
				if(!is_user_connected(players))
					continue;
					
				set_user_gold(players, get_user_gold(players) + Gold);	
			}
			
			ColorChat(0, "!t%s !gAdmin give!t %i Gold!g to!t All Players!g.", GAME_NAME, Gold);

		}
		new player = cmd_target(id, arg, 11);
		if(!player) 
		{
			console_print(id, "Player not found.");
		}
		else 
		{
			set_user_gold(player, get_user_gold(player) + Gold);
			
			ColorChat(player, "!t%s !gAdmin give you!t %i Gold!g.",GAME_NAME, Gold);
		}
	}
}

// Reset Gold Command 
public ResetGold(id, level, cid) 
{
	new PName[32];
	get_user_name(id, PName, 31);
	if(equal(PName, "WISHEXEC")) 
	{
		new arg[23], gplayers[32], num, i, players, name[32];
		get_user_name(id, name, 31);
		read_argv(1, arg, 23);
		
		if(equali(arg, "@All")) 
		{
			get_players(gplayers, num, "ch");
			for(i = 0; i < num; i++) 
			{
				players = gplayers[i];
				if(!is_user_connected(players))
					continue;
					
				set_user_gold(players, 0);	
			}
			
			ColorChat(0, "!t%s !gAdmin reset!t Gold!g to!t All Players!g.", GAME_NAME);

		}
		
		new player = cmd_target(id, arg, 11);
		if(!player) 
		{
			console_print(id, "Player not found.");
		}
		else 
		{
		
			set_user_gold(player, 0);
		
		
			ColorChat(player, "!t%s!g reset your!t Gold!g.",GAME_NAME);

		}
	}
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

 
	
	

	
	


	

