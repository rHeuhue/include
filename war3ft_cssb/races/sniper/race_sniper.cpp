// ******************************************************************
// Раса: Снайпер (Race: Sniper) Functions
// ******************************************************************


//Инициализация скилов Race: Sniper (Снайпер)
public clSniper::setSkillsInit()//добавлена в skill_manager.cpp ( SM_Init() )
{
	g_SkillOwner[SKILL_SNIPER_1			]	= RACE_SNIPER;
	g_SkillOwner[SKILL_SNIPER_2			]	= RACE_SNIPER;
	g_SkillOwner[SKILL_SNIPER_3			]	= RACE_SNIPER;
	g_SkillOwner[ULTIMATE_SNIPER		]	= RACE_SNIPER;
	g_SkillOwner[PASS_SNIPER			]	= RACE_SNIPER;

	g_SkillType[SKILL_SNIPER_1			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_SNIPER_2			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[SKILL_SNIPER_3			]	= SKILL_TYPE_TRAINABLE;
	g_SkillType[ULTIMATE_SNIPER			]	= SKILL_TYPE_ULTIMATE;
	g_SkillType[PASS_SNIPER				]	= SKILL_TYPE_PASSIVE;

	g_SkillOrder[SKILL_SNIPER_1			]	= SKILL_POS_1;
	g_SkillOrder[SKILL_SNIPER_2			]	= SKILL_POS_2;
	g_SkillOrder[SKILL_SNIPER_3			]	= SKILL_POS_3;
	g_SkillOrder[ULTIMATE_SNIPER		]	= SKILL_POS_4;
	g_SkillOrder[PASS_SNIPER			]	= SKILL_POS_NONE;
	
}

// **********************************************************************
// Скил 1 уровня - Headshot - Выстрел в голову
// **********************************************************************
clSniper::skillHeadshot(const idAttacker,const idVictim,const iBodyPart)
{
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker))
		return;

	if(!is_user_connected(idVictim))
		return;

	if(isDisabledSkillsOnMap(idAttacker,SKILL_SNIPER_1) == true)
		return;

	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_SNIPER_1 );
	if (iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false)
	{
		new Float:fHeadshot = ArrayGetCell(arrHeadshot,iSkillLevel-1);
		if (random_float(fHeadshotSkill1MinPercent,fHeadshotSkill1MaxPercent) <= fHeadshot )		
		{							
			if(iBodyPart == HIT_HEAD)//Попадание в голову
			{
				new ptVictimOrigin[3];
				get_user_origin(idVictim, ptVictimOrigin);
									
				emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_HEADSHOT], 1.0, ATTN_NORM, 0, PITCH_NORM );

				new ptPositionExp[3];
				ptPositionExp[0] = ptVictimOrigin[0];
				ptPositionExp[1] = ptVictimOrigin[1];
				ptPositionExp[2] = ptVictimOrigin[2] + random_num(10, 50);
				
				Create_TE_EXPLOSION(ptVictimOrigin, ptPositionExp, arrIdSprites[SPR_HEADSHOT], 10,15, TE_EXPLFLAG_NOSOUND + TE_EXPLFLAG_NODLIGHTS );

				new arrPlayers[32], iNumberOfPlayers, idTarget, ptTargetOrigin[3];
				new iTeam = get_user_team(idVictim);
			
				get_players(arrPlayers, iNumberOfPlayers, "a");
								
				for (new i = 0; i < iNumberOfPlayers; i++ )
				{
					idTarget = arrPlayers[i];
										
					if ( arrBoolData[idTarget][PB_ISCONNECTED] && get_user_team(idTarget) == iTeam)
					{
						if (is_user_alive(idTarget))
						{
							get_user_origin( idTarget, ptTargetOrigin );
												
							if (get_distance(ptVictimOrigin, ptTargetOrigin) < iSniperHeadshotRadius )
							{
								get_user_origin(idTarget, ptVictimOrigin );

								Create_TE_IMPLOSION(ptTargetOrigin,100, 150, 1);
								
								WC3_Damage(idTarget,idAttacker,iSniperHeadshotDmg, CSW_HEADSHOT, iBodyPart);
							
							}
						}
					}
				}

			}
		}
		
	}

}

// **********************************************************************
// Скил 2 уровня - Phase Boots  - Фазовый ускоритель
// **********************************************************************
bool:clSniper::skillPhaseBoots(const idUser,const iWeapon,&Float:fNewSpeed)
{
	if(iWeapon != CSW_AWP && iWeapon != CSW_SCOUT)
		return false;

	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
		return false;

	new iSkillLevel = SM_GetSkillLevel(idUser, SKILL_SNIPER_2);
		
	if (iSkillLevel > 0 && isDisabledSkillsOnMap(idUser,SKILL_SNIPER_2) == false)
	{
		fNewSpeed = ArrayGetCell(arrPhaseBoots,iSkillLevel-1);

		return true;
	}

	return false;
}



// **********************************************************************
// Скил 3 уровня - Заряды шрапнели - Shrapnel charge
// **********************************************************************
//Прокачка зарядов для выстрела шрапнелью 


// **********************************************************************
// Скил 4 уровня - Слонобой - Elephant Gun
// **********************************************************************
public clSniper::skillElephantGun(idUser)
{	
	if(!is_user_alive(idUser) || !is_user_connected(idUser))
		return;
	
	if(isDisabledSkillsOnMap(idUser,PASS_SNIPER) == true)
		return;

	clSniper::fShowMenuAWP(idUser);
	
}

//Вызов отображения меню с выбором Авп
clSniper::fShowMenuAWP(idUser, iPage = 0)
{
	if(user_has_weapon(idUser,CSW_SCOUT) || user_has_weapon(idUser,CSW_AWP))
		return;

	new idMenu,szMenuData[256];
	
	//Название главного меню
	formatex(szMenuData, charsmax(szMenuData), "%L", LANG_PLAYER, "WC3_MENU_AWP");
	idMenu = menu_create(szMenuData, "_Callback_SUB_MENU_AWP");

	new szAwp[64];
	formatex(szAwp, charsmax(szAwp), "%L", LANG_PLAYER, "WC3_MENU_AWP_1");
	menu_additem(idMenu,szAwp,"1",0,-1);
	formatex(szAwp, charsmax(szAwp), "%L", LANG_PLAYER, "WC3_MENU_AWP_2");
	menu_additem(idMenu,szAwp,"2",0,-1);
			
	// Если нет предметов в меню
	if (menu_items(idMenu) <= 0)
	{
		menu_destroy(idMenu);
		return;
	}
			
	//Пункты меню (назад - следующий - выход)
	formatex(szMenuData, charsmax(szMenuData), "\w%L", LANG_PLAYER, "WC3_MENU_EXIT");
	menu_setprop(idMenu, MPROP_EXITNAME, szMenuData);

	menu_display(idUser, idMenu, iPage);
}

public _Callback_SUB_MENU_AWP(idUser, idMenu, idItem)
{
	if ( !WC3_Check() )
		return PLUGIN_HANDLED;

	if(!is_user_alive(idUser) || !is_user_connected(idUser))
	{
		menu_destroy(idMenu);
		return PLUGIN_HANDLED;
	}

	// Возврат в главное меню
	if (idItem == MENU_EXIT)
	{
		menu_destroy(idMenu);
		return PLUGIN_HANDLED;
	}
	
	static _access, szInfoMenu[8], callback;
	menu_item_getinfo(idMenu, idItem, _access, szInfoMenu, sizeof(szInfoMenu) - 1, _, _, callback);
	
	new iNumberItem = str_to_num(szInfoMenu);
	

	switch (iNumberItem)
	{
		case 1:		
			{
				
				ham_strip_weapon(idUser,"weapon_awp");
				ham_strip_weapon(idUser,"weapon_scout");
				drop_weapons(idUser, 1);
				
				give_item(idUser, "weapon_awp" );
				give_item(idUser,"ammo_338magnum");
				give_item(idUser,"ammo_338magnum");
				give_item(idUser,"ammo_338magnum");				
			}
		case 2:
			{
				
				ham_strip_weapon(idUser,"weapon_awp");
				ham_strip_weapon(idUser,"weapon_scout");
				drop_weapons(idUser, 1);

				give_item(idUser, "weapon_scout" );
				give_item(idUser,"ammo_762nato");
				give_item(idUser,"ammo_762nato");
				give_item(idUser,"ammo_762nato");
				give_item(idUser,"ammo_762nato");
				give_item(idUser,"ammo_762nato");
				give_item(idUser,"ammo_762nato");
				give_item(idUser,"ammo_762nato");
				give_item(idUser,"ammo_762nato");
				give_item(idUser,"ammo_762nato");
			}
	}


	menu_destroy(idMenu);
		
	return PLUGIN_HANDLED;
}


public fwHamPlayerWeaponTouch(entWeaponBox, idUserTouch)
{
	if(!pev_valid(entWeaponBox))
		return HAM_IGNORED;

	if (!SHARED_ValidPlayer(idUserTouch))
		return HAM_IGNORED;
	
	if(!is_user_alive(idUserTouch))
		return HAM_IGNORED;

	if(bIsUserRace(idUserTouch,RACE_SNIPER))
	{
		new szModelWeaponBox[64];
		pev(entWeaponBox, pev_model, szModelWeaponBox, charsmax(szModelWeaponBox)); 

		new iIndexWeapon = getIdWeaponFromModels(szModelWeaponBox);

		if( iIndexWeapon != CSW_AWP && 
			iIndexWeapon != CSW_SCOUT &&

			iIndexWeapon != CSW_P228 &&
			iIndexWeapon != CSW_ELITE &&
			iIndexWeapon != CSW_FIVESEVEN &&
			iIndexWeapon != CSW_USP &&
			iIndexWeapon != CSW_GLOCK18 &&
			iIndexWeapon != CSW_DEAGLE &&

			iIndexWeapon != CSW_HEGRENADE &&
			iIndexWeapon != CSW_SMOKEGRENADE &&
			iIndexWeapon != CSW_FLASHBANG &&

			iIndexWeapon != CSW_VEST &&
			iIndexWeapon != CSW_VESTHELM &&

			iIndexWeapon != CSW_C4
		  )
			return HAM_SUPERCEDE;
	}	

	return HAM_IGNORED;
}

public clSniper::fStripGuns(idUser)
{	
	if(!is_user_alive(idUser) || !is_user_connected(idUser))
		return;
	
	new iIndexWeapon, iClip, iAmmo;
	iIndexWeapon = get_user_weapon(idUser, iClip, iAmmo);

	if( iIndexWeapon != CSW_AWP && 
		iIndexWeapon != CSW_SCOUT &&

		iIndexWeapon != CSW_P228 &&
		iIndexWeapon != CSW_ELITE &&
		iIndexWeapon != CSW_FIVESEVEN &&
		iIndexWeapon != CSW_USP &&
		iIndexWeapon != CSW_GLOCK18 &&
		iIndexWeapon != CSW_DEAGLE &&

		iIndexWeapon != CSW_HEGRENADE &&
		iIndexWeapon != CSW_SMOKEGRENADE &&
		iIndexWeapon != CSW_FLASHBANG &&

		iIndexWeapon != CSW_VEST &&
		iIndexWeapon != CSW_VESTHELM &&

		iIndexWeapon != CSW_C4 &&

		iIndexWeapon != CSW_KNIFE
	  )
	{

		if(user_has_weapon(idUser, iIndexWeapon))
		{
			stStripUserGun(idUser, iIndexWeapon); 

			format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_BLOCK_WPN_SNIPER");
			cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);
		}
	}
	
}

// *******************************************************
// Супер навык - Шрапнель - Shrapnel
// *******************************************************
public clSniper::ultShrapnel(idAttacker)
{		
	if(!is_user_alive(idAttacker) || !is_user_connected(idAttacker)) 
		return;
	
	emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_SHRAPNEL_FIRE], 1.0, ATTN_NORM, 0, PITCH_NORM );
	
	new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_SNIPER_3);

	if(iSkillLevel <= 0)
		iSkillLevel = 1;

	new iShrapnelCharge = ArrayGetCell(arrSkillShrapnelCharge,iSkillLevel-1);

	for(new i = 0; i < iShrapnelCharge; i++)
	{
		clSniper::fCreateShrapnel(SHRAPNEL_SNIPER_CLASSNAME,idAttacker,
								 random_float(50.0,150.0),
								 arrIdSprites[SPR_SHRAPNEL],
								 random_num(1100,2500),
								 random_float(-15.0,30.0),
								 2,
								 random_float(-1.0471975511966,1.0471975511966));
	}

	fResetUltimateTimerDivider(idAttacker);

}

bool:clSniper::fCreateShrapnel(const szClassname[],const idUser,const Float:fRadiusSpawn,
							   const iModelIndex,const iVelocityAux,
							   const Float:fOriginOffset,
							   const iAxis,
							   const Float:fAngleRotate)
{	
	new Float:ptOriginPlayer[3];
	pev(idUser, pev_origin, ptOriginPlayer);
  	
	new Float:fAngles[3];
	pev(idUser, pev_v_angle, fAngles);
	engfunc(EngFunc_MakeVectors, fAngles);
	global_get(glb_v_forward, fAngles);
	xs_vec_mul_scalar(fAngles, fRadiusSpawn, fAngles);
	fAngles = uRotate(fAngleRotate,fAngles);
	xs_vec_add(ptOriginPlayer, fAngles, ptOriginPlayer);

	new idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	
	if(!pev_valid(idEntity)) 
		return false;
		
	set_pev(idEntity, pev_classname, szClassname);								// Задаем класс создаваемой сущности
	set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
	set_pev(idEntity, pev_modelindex, iModelIndex);								// Задаем индекс создаваемой сущности
	fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти

	set_pev(idEntity, pev_movetype, MOVETYPE_BOUNCE);
	set_pev(idEntity, pev_solid, SOLID_BBOX);
		
	set_pev(idEntity, pev_gravity, 0.8);
	set_pev(idEntity,pev_iuser1,iShrapnelNumJump);		// Количество отскоков от стен

	set_pev(idEntity, pev_scale, 0.07);
	set_pev(idEntity, pev_health, 100.0);
	set_pev(idEntity, pev_takedamage, DAMAGE_YES);
	
	new Float:fVelocityAim[3];
	velocity_by_aim(idUser, iVelocityAux, fVelocityAim);
	set_pev(idEntity, pev_velocity, fVelocityAim);//Скорость движения сущности (вперед летит)

	new Float:fAnglesV[3];
	pev(idUser, pev_angles, fAnglesV);
	set_pev(idEntity, pev_angles, fAnglesV);//Задание сущности угла поворота
	set_pev(idEntity, pev_fixangle, 1);

	ptOriginPlayer[iAxis] += fOriginOffset;
	
	set_pev(idEntity, pev_origin, ptOriginPlayer);

	return true;

}

// ******************************************************************
// Создание и управление эффектами для скила
// ******************************************************************
public touchShrapnel(idEntity, idWorldPlayer)
{
	//client_print(0,print_chat,"idEntity: %d | idWorldPlayer: %d",idEntity,idWorldPlayer);

	if (!pev_valid(idEntity))
		return PLUGIN_HANDLED;

	new idOwner = pev(idEntity, pev_owner);
	
	new Float:ptOriginEntity[3];
	pev(idEntity, pev_origin, ptOriginEntity);

	new Float:ptOriginOwner[3];
	pev(idOwner, pev_origin, ptOriginOwner);

	//Соприкосновение с миром (стены,пол...)
	if(idWorldPlayer == 0)
	{	
		new iNumJump = pev(idEntity, pev_iuser1);	// Количество отскоков от стен
		
		if(iNumJump <= 0)
		{
			message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
			write_byte(TE_BEAMCYLINDER);
			engfunc(EngFunc_WriteCoord, ptOriginEntity[0]);// center position (X)
			engfunc(EngFunc_WriteCoord, ptOriginEntity[1]);// center position (Y)
			engfunc(EngFunc_WriteCoord, ptOriginEntity[2]);// center position (Z)
			engfunc(EngFunc_WriteCoord, ptOriginEntity[0]);// axis and radius (X)
			engfunc(EngFunc_WriteCoord, ptOriginEntity[1]);// axis and radius (Y)
			engfunc(EngFunc_WriteCoord, ptOriginEntity[2] + fShrapnelExpRadius);// axis and radius (Z)
			write_short(arrIdSprites[SPR_SHRAPNEL_EXPLODE]) ;
			write_byte(0);// starting frame
			write_byte(10);// frame rate in 0.1's
			write_byte(3); // life in 0.1's
			write_byte(20); // line width in 0.1's
			write_byte(0); // noise amplitude in 0.01's
			write_byte(255);// color (red)
			write_byte(255);// color (green)
			write_byte(255);// color (blue)
			write_byte(255);// brightness
			write_byte(0);// scroll speed in 0.1's
			message_end();


			new idFindPlayer;
			while ((idFindPlayer = engfunc(EngFunc_FindEntityInSphere, idFindPlayer, ptOriginEntity, fShrapnelExpRadius)))
			{
				if(!SHARED_ValidPlayer(idFindPlayer))
					continue;

				if (get_user_team(idFindPlayer) != get_user_team(idOwner) && is_user_alive(idFindPlayer))
				{
					WC3_Damage(idFindPlayer,idOwner,iShrapnelDmgExp, CSW_SHRAPNEL, -1);
					ExecuteHamB(Ham_TakeDamage, idFindPlayer, idEntity, idOwner, 0.0, DMG_BULLET);
																
					Create_ScreenFade(idFindPlayer, (1<<12), (1<<12), (1<<6), 227, 195, 69, 255 );
					
				}//if

			}//while	

			emit_sound(idEntity, CHAN_STATIC, arrStrSounds[SOUND_SHRAPNEL_EXPLODE], 1.0, ATTN_NORM, 0, PITCH_NORM );

			remove_entity(idEntity);
			return PLUGIN_HANDLED;
		}
				
		iNumJump -= 1;
		set_pev(idEntity,pev_iuser1,iNumJump);		
	
	}
	else
	{
		if(!SHARED_ValidPlayer(idWorldPlayer) || !SHARED_ValidPlayer(idOwner))
		{
			remove_entity(idEntity);
			return PLUGIN_HANDLED;
		}
									
		if (get_user_team(idWorldPlayer) != get_user_team(idOwner) && is_user_alive(idWorldPlayer))
		{
			WC3_Damage(idWorldPlayer,idOwner,iShrapnelDmg, CSW_SHRAPNEL, -1);
			ExecuteHamB(Ham_TakeDamage, idWorldPlayer, idEntity, idOwner, 0.0, DMG_BULLET | DMG_NEVERGIB);
														
			Create_ScreenFade(idWorldPlayer, (1<<12), (1<<12), (1<<6), 255, 0, 0, 255 );
			
			emit_sound(idWorldPlayer, CHAN_STATIC, arrStrSounds[SOUND_SHRAPNEL_DAMAGE], 1.0, ATTN_NORM, 0, PITCH_NORM );

			remove_entity(idEntity);
			return PLUGIN_HANDLED;

		}//if


	}
	
	return PLUGIN_CONTINUE;
}