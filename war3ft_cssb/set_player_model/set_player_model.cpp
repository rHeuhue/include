
//натив
public native_set_player_model(plugin_id, num_params)
{
	new idUser = get_param(1);
	
	if (!is_user_connected(idUser))
		return false;
		
	new szNewModel[MODELNAME_MAXLENGTH];
	get_string(2, szNewModel, charsmax(szNewModel));
	
	remove_task(idUser+TASK_MODELCHANGE);
	flag_set(iHasCustomModel, idUser);
	
	copy(arrCustomPlayerModel[idUser], charsmax(arrCustomPlayerModel[]), szNewModel);
/*	
#if defined SET_MODELINDEX_OFFSET	
	new modelpath[32+(2*MODELNAME_MAXLENGTH)]
	formatex(modelpath, charsmax(modelpath), "models/player/%s/%s.mdl", szNewModel, szNewModel)
	arrCustomModelIndex[idUser] = engfunc(EngFunc_ModelIndex, modelpath)
#endif
*/
	new szCurrentModel[MODELNAME_MAXLENGTH];
	fGetUserModel(idUser, szCurrentModel, charsmax(szCurrentModel));
	
	if (!equal(szCurrentModel, szNewModel))
		fUpdateUserModel(idUser + TASK_MODELCHANGE);
	
	return true;
}

//натив
public native_reset_player_model(plugin_id, num_params)
{
	new idUser = get_param(1);
	
	if (!is_user_connected(idUser))
		return false;
		
	// Player doesn't have a custom model, no need to reset
	if (!flag_get(iHasCustomModel, idUser))
		return true;
	
	remove_task(idUser + TASK_MODELCHANGE);

	flag_unset(iHasCustomModel, idUser);

	fResetUserModel(idUser);
	
	return true;
}


public fwSetClientKeyValue(idUser, const infobuffer[], const key[], const value[])
{
	if (flag_get(iHasCustomModel, idUser) && equal(key, "model"))
	{
		new szCurrentModel[MODELNAME_MAXLENGTH];
		fGetUserModel(idUser, szCurrentModel, charsmax(szCurrentModel));
		
		if (!equal(szCurrentModel, arrCustomPlayerModel[idUser]) && !task_exists(idUser+TASK_MODELCHANGE))
			fSetUserModel(idUser+TASK_MODELCHANGE);
/*		
#if defined SET_MODELINDEX_OFFSET
		fSetUseModelIndex(idUser)
#endif
*/		
		return FMRES_SUPERCEDE;
	}
	
	return FMRES_IGNORED;
}



public fSetUserModel(idTask)
{
	set_user_info(ID_MODELCHANGE, "model", arrCustomPlayerModel[ID_MODELCHANGE]);
}

stock fSetUseModelIndex(idUser)
{
	if (pev_valid(idUser) != PDATA_SAFE)
		return;
	
	set_pdata_int(idUser, OFFSET_MODELINDEX, arrCustomModelIndex[idUser]);
}

stock fResetUserModelIndex(idUser)
{
	if (pev_valid(idUser) != PDATA_SAFE)
		return;
	
	switch (fGetUserTeam(idUser))
	{
		case CS_TEAM_T:
		{
			set_pdata_int(idUser, OFFSET_MODELINDEX, engfunc(EngFunc_ModelIndex, DEFAULT_MODELINDEX_T));
		}
		case CS_TEAM_CT:
		{
			set_pdata_int(idUser, OFFSET_MODELINDEX, engfunc(EngFunc_ModelIndex, DEFAULT_MODELINDEX_CT));
		}
	}
}

stock fGetUserModel(idUser, model[], len)
{
	get_user_info(idUser, "model", model, len);
}

stock fResetUserModel(idUser)
{
	// Set some generic model and let CS automatically reset player model to default
	//copy(arrCustomPlayerModel[idUser], charsmax(arrCustomPlayerModel[]), "gordon");
	copy(arrCustomPlayerModel[idUser], charsmax(arrCustomPlayerModel[]), "uryferwdg");

	fUpdateUserModel(idUser + TASK_MODELCHANGE);
/*
#if defined SET_MODELINDEX_OFFSET
	fResetUserModelIndex(idUser)
#endif
*/

}

stock fUpdateUserModel(idTask)
{
	new Float:fCurrentTime;
	fCurrentTime = get_gametime();
	
	if (fCurrentTime - fModelChangeTargetTime >= MODELCHANGE_DELAY)
	{
		fSetUserModel(idTask);
		fModelChangeTargetTime = fCurrentTime;
	}
	else
	{
		set_task((fModelChangeTargetTime + MODELCHANGE_DELAY) - fCurrentTime, "fSetUserModel", idTask);

		fModelChangeTargetTime = fModelChangeTargetTime + MODELCHANGE_DELAY;
	}
}

stock CsTeams:fGetUserTeam(idUser)
{
	if (pev_valid(idUser) != PDATA_SAFE)
		return CS_TEAM_UNASSIGNED;
	
	return CsTeams:get_pdata_int(idUser, OFFSET_CSTEAMS);
}