




public set_user_levelbank(id, level)
{
	if(is_user_connected(id))
	{
		
		LevelBankBonus[id] = level;
		
		SaveLevelBank(id);
	}
}

public get_user_levelbank(id) 
{
	return is_user_connected(id) ? LevelBankBonus[id] : 0
}



public SaveLevelBank(id) 
{
	new Name[32];
	get_user_name(id, Name, 31);
	
	static Data[64]
	formatex(Data, sizeof(Data) - 1, "^"%i^"", LevelBankBonus[id])
	
	new Save[64]
	format(Save,sizeof(Save) - 1, "^"%s^" %s", Name, Data)
	
	new Line[128], Linie, IsPlayer = false, Arg1[32]
	
	new FileOpen = fopen(LevelBankFile, "rt")
	while(!feof(FileOpen)) 
	{
		fgets(FileOpen, Line, 127)
		trim(Line)
		
		parse(Line, Arg1, 31)
		
		if (equali(Arg1, Name)) 
		{
			write_file(LevelBankFile, Save, Linie)
			IsPlayer = true
			break
		}
		
		Linie++
	}
	fclose(FileOpen)
	if (!IsPlayer) 
	{
		write_file(LevelBankFile, Save, -1)
	}
}


public LoadLevelBank(id) 
{
	new Name[32];
	get_user_name(id, Name, 31);
	
	new Line[128], IsPlayer = false, Arg1[32], Arg2[32];
	
	new FileOpen = fopen(LevelBankFile, "rt")
	while(!feof(FileOpen)) 
	{
		fgets(FileOpen, Line, 127)
		trim(Line)
		
		parse(Line, Arg1, 31, Arg2, 31)
		
		if (equali(Arg1, Name)) 
		{
			LevelBankBonus[id] = str_to_num(Arg2)
			IsPlayer = true
			break
		}
	}
	fclose(FileOpen)
	
	if (!IsPlayer) 
	{
		// Player not found so we have a new player 
		LevelBankBonus[id] = LEVEL_BANK;
	}
}