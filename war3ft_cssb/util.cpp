/*
*	UTIL Functions - Basically helper functions
*/

//Автоматическое (принудительное) закрытие меню игроку
UTIL_AutoHideMenu(idUser)
{
	new idMenuAutoHide, iKeysAutoHide;
	get_user_menu (idUser, idMenuAutoHide, iKeysAutoHide);

	if(idMenuAutoHide != 0 ) 
	{
		menu_cancel(idUser);				// force client to choose MENU_EXIT to destroy our menu
		show_menu(idUser, 0, "^n", 1 );    // show empty menu to hide our menu on player's screen
	}
}

UTIL_GetWeaponName( iWeapon, szWpnName[], len )
{
	switch ( iWeapon )
	{
		case CSW_KNIFE:			copy( szWpnName, len, "knife"		);

		case CSW_USP:           copy( szWpnName, len, "usp"			);
		case CSW_GLOCK18:       copy( szWpnName, len, "glock18"		);
		case CSW_DEAGLE:        copy( szWpnName, len, "deagle"		);
		case CSW_P228:          copy( szWpnName, len, "p228"		);
		case CSW_ELITE:         copy( szWpnName, len, "elite"		);
		case CSW_FIVESEVEN:     copy( szWpnName, len, "fiveseven"	);

		case CSW_M3:            copy( szWpnName, len, "m3"			);
		case CSW_XM1014:        copy( szWpnName, len, "xm1014"		);

		case CSW_MP5NAVY:       copy( szWpnName, len, "mp5navy"		);
		case CSW_TMP:           copy( szWpnName, len, "tmp"			);
		case CSW_P90:           copy( szWpnName, len, "p90"			);
		case CSW_MAC10:         copy( szWpnName, len, "mac10"		);
		case CSW_UMP45:         copy( szWpnName, len, "ump45"		);

		case CSW_AK47:          copy( szWpnName, len, "ak47"		);
		case CSW_SG552:         copy( szWpnName, len, "sg552"		);
		case CSW_M4A1:          copy( szWpnName, len, "m4a1"		);
		case CSW_AUG:           copy( szWpnName, len, "aug"			);
		case CSW_SCOUT:         copy( szWpnName, len, "scout"		);
		case CSW_AWP:           copy( szWpnName, len, "awp"			);
		case CSW_SG550:         copy( szWpnName, len, "sg550"		);
		case CSW_G3SG1:         copy( szWpnName, len, "g3sg1"		);

		case CSW_GALI:          copy( szWpnName, len, "galil"		);
		case CSW_FAMAS:         copy( szWpnName, len, "famas"		);

		case CSW_M249:          copy( szWpnName, len, "m249"		);

		case CSW_HEGRENADE:     copy( szWpnName, len, "grenade"		);
	}

	// These are common to both
	switch ( iWeapon )
	{
		case CSW_WORLDSPAWN:			copy( szWpnName, len, "world"													);
	
		case CSW_LIGHTNING:				copy( szWpnName, len,"Chain Lightning");
		case CSW_SUICIDE:				copy( szWpnName, len,"Suicide Bomber");
		case CSW_IMMOLATE:				copy( szWpnName, len,"Immolate");
		case CSW_LOCUSTS:				copy( szWpnName, len,"Locust Swarm");
		case CSW_SERPENTWARD:			copy( szWpnName, len,"Serpent Ward");
		case CSW_SHADOW:				copy( szWpnName, len,"Shadow Strike");
		case CSW_THORNS:				copy( szWpnName, len,"Thorns Aura");
		case CSW_CARAPACE:				copy( szWpnName, len,"Spiked Carapace");
		case CSW_CARRION:				copy( szWpnName, len,"Carrion Beetles");
		case CSW_ORB:					copy( szWpnName, len,"Orb of Annihilation");
		case CSW_CONCOCTION:			copy( szWpnName, len,"Unstable Concoction");
		case CSW_BANISH:				copy( szWpnName, len,"Banish");
		case CSW_BLIZZARD:				copy( szWpnName, len,"Blizzard");
		case CSW_ICE_SPLINTERS:			copy( szWpnName, len,"Ice splinters");
		case CSW_CHAM_FLAME_STRIKE:		copy( szWpnName, len,"Flame Strike");
		case CSW_DEATHCOIL:				copy( szWpnName, len,"Death Coil");
		case CSW_IMPALE:				copy( szWpnName, len,"Impale");
		case CSW_BLACKPOWER:			copy( szWpnName, len,"Black Strike");
		case CSW_POISON:				copy( szWpnName, len,"Poison");
		case CSW_RADIATION:				copy(szWpnName, len,"Radiation");
		case CSW_WORDDEATH:				copy(szWpnName, len,"Darkness word: Death");
		case CSW_BLOOD_RAGE:			copy(szWpnName, len,"Blood Rage");
		case CSW_BLOOD_RITE:			copy(szWpnName, len,"Blood Rite");
		case CSW_HEADSHOT:				copy(szWpnName, len,"Headshot");
		case CSW_SHRAPNEL:				copy(szWpnName, len,"Shrapnel");
		case CSW_GLIMPSE:				copy(szWpnName, len,"Glimpse");
		case CSW_STATIC_STORM:			copy(szWpnName, len,"Static Storm");
		case CSW_THUNDER_STRIKE:		copy(szWpnName, len,"Thunder Strike");
		case CSW_PLASMA_FIELD:			copy(szWpnName, len,"Plasma Field");
		case CSW_UNSTABLE_CURRENT:		copy(szWpnName, len,"Unstable Current");
		case CSW_FATAL_BONDS:			copy(szWpnName, len,"Fatal Bonds");
		case CSW_SHADOW_WORD:			copy(szWpnName, len,"Shadow Word");
		case CSW_FLAMING_FISTS:			copy(szWpnName, len,"Flaming Fists");
		case CSW_PERM_IMMOLATION:		copy(szWpnName, len,"Permanent Immolation");
		case CSW_CRY_HEART:				copy(szWpnName, len,"Cry from the heart");
		case CSW_REQUIEM_SOULS:			copy(szWpnName, len,"Requiem of Souls");
			

			
	}
}

// Log the death of a user
UTIL_LogDeath( idVictim, iKiller, iWeapon )
{
	new szKillerName[32], szVictimName[32];
	new szKillerTeam[32], szVictimTeam[32];
	new szKillerAuth[32], szVictimAuth[32];
	new szWeaponName[32];

	new iKillerUserID = get_user_userid( iKiller );
	new iVictimUserID = get_user_userid( idVictim );

	UTIL_GetWeaponName( iWeapon, szWeaponName, 31 );

	get_user_name(		iKiller	, szKillerName	, 31 );
	get_user_name(		idVictim	, szVictimName	, 31 );
	get_user_team(		iKiller	, szKillerTeam	, 31 );
	get_user_team(		idVictim	, szVictimTeam	, 31 );
	get_user_authid(	iKiller	, szKillerAuth	, 31 );
	get_user_authid(	idVictim	, szVictimAuth	, 31 );

	log_message("^"%s<%d><%s><%s>^" killed ^"%s<%d><%s><%s>^" with ^"%s^"", szKillerName, iKillerUserID, szKillerAuth, szKillerTeam, szVictimName, iVictimUserID, szVictimAuth, szVictimTeam, szWeaponName );
}

stock UTIL_EntInView(idUser, iEnt)
{
	new Float:vPlayerOrigin[3];
	entity_get_vector( idUser, EV_VEC_origin, vPlayerOrigin );

	new Float:vEntOrigin[3];
	entity_get_vector( iEnt, EV_VEC_origin, vEntOrigin );

	new Float:vReturn[3];

	new iHitEnt = trace_line( idUser, vPlayerOrigin, vEntOrigin, vReturn );

	if ( iHitEnt == iEnt )
	{
		return 1;
	}
	
	return 0;
}

UTIL_ClearHudChannel( idUser, iChannel )
{
	set_hudmessage( 0, 0, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0, iChannel );
	show_hudmessage( idUser, "" );
}

stock UTIL_ClearDHudChannel(idUser,iClear = 8) //под вопросом (толку пока не видно)
{
	for (new iDHUD = 0; iDHUD < iClear; iDHUD++)
	{
		set_dhudmessage(0, 0, 0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0 );
		show_dhudmessage(idUser, "");
	}
}
         


//Когда один игрок смотрит на другого
stock UTIL_CanSeePlayer(idUser, iTargetID)
{
	if(!is_user_alive(idUser) || !is_user_connected(idUser)) 
      return 0;

	if(!is_user_alive(iTargetID) || !is_user_connected(iTargetID)) 
      return 0;

	new Float:vOrigin[3];
	entity_get_vector(iTargetID, EV_VEC_origin, vOrigin );

	return is_in_viewcone(idUser, vOrigin);
}

//Проверяет видит ли игрок другого с учетом стен 
stock bool:UTIL_CanSeeToWall(entindex1, entindex2)
{
	if ((!iFakeMeta_ModuleRunning) || !entindex1 || !entindex2)
		return false;

	if (pev_valid(entindex1) && pev_valid(entindex1))
	{
		new flags = pev(entindex1, pev_flags);
		if (flags & EF_NODRAW || flags & FL_NOTARGET)
		{
			return false;
		}

		new Float:lookerOrig[3];
		new Float:targetBaseOrig[3];
		new Float:targetOrig[3];
		new Float:temp[3];

		pev(entindex1, pev_origin, lookerOrig);
		pev(entindex1, pev_view_ofs, temp);
		lookerOrig[0] += temp[0];
		lookerOrig[1] += temp[1];
		lookerOrig[2] += temp[2];

		pev(entindex2, pev_origin, targetBaseOrig);
		pev(entindex2, pev_view_ofs, temp);
		targetOrig[0] = targetBaseOrig [0] + temp[0];
		targetOrig[1] = targetBaseOrig [1] + temp[1];
		targetOrig[2] = targetBaseOrig [2] + temp[2];

		engfunc(EngFunc_TraceLine, lookerOrig, targetOrig, 0, entindex1, 0); //  checks the had of seen player
		if (get_tr2(0, TraceResult:TR_InOpen) && get_tr2(0, TraceResult:TR_InWater))
		{
			return false;
		} 
		else 
		{
			new Float:flFraction;
			get_tr2(0, TraceResult:TR_flFraction, flFraction);
			if (flFraction == 1.0 || (get_tr2(0, TraceResult:TR_pHit) == entindex2))
			{
				return true;
			}
			else
			{
				targetOrig[0] = targetBaseOrig [0];
				targetOrig[1] = targetBaseOrig [1];
				targetOrig[2] = targetBaseOrig [2];
				engfunc(EngFunc_TraceLine, lookerOrig, targetOrig, 0, entindex1, 0); //  checks the body of seen player
				get_tr2(0, TraceResult:TR_flFraction, flFraction);
				if (flFraction == 1.0 || (get_tr2(0, TraceResult:TR_pHit) == entindex2))
				{
					return true;
				}
				else
				{
					targetOrig[0] = targetBaseOrig [0];
					targetOrig[1] = targetBaseOrig [1];
					targetOrig[2] = targetBaseOrig [2] - 17.0;
					engfunc(EngFunc_TraceLine, lookerOrig, targetOrig, 0, entindex1, 0); //  checks the legs of seen player
					get_tr2(0, TraceResult:TR_flFraction, flFraction);
					if (flFraction == 1.0 || (get_tr2(0, TraceResult:TR_pHit) == entindex2))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

//Считывает координаты игрока как float и переводит в int
stock UTIL_GetOriginInt(idUser, ptOrigin[3])
{
	new Float:fVector[3];
	pev(idUser,pev_origin,fVector);

	ptOrigin[0] = floatround(fVector[0]);
	ptOrigin[1] = floatround(fVector[1]);
	ptOrigin[2] = floatround(fVector[2]);
}

//Входящее значение - точка с плавающей запятой т.е. Float
//Возвращаемое значение - точка с плавающей запятой т.е. Float
stock Float:uFloatPointToFloat(Float:ptAux[3])
{	
	new Float:pt[3];
	pt[0] = ptAux[0];
	pt[1] = ptAux[1];
	pt[2] = ptAux[2];

	return pt;
}

//Входящее значение - точка с плавающей запятой т.е. Float
//Возвращаемое значение - точка с целыми т.е. int
stock uFloatPointToInt(Float:ptAux[3])
{
	new pt[3];
	pt[0] = floatround(ptAux[0]); 
	pt[1] = floatround(ptAux[1]); 
	pt[2] = floatround(ptAux[2]);

	return pt;
}

//Поворот точки (вектора) на заданный угол и радиус
//Входящее значение - точка с плавающей запятой т.е. Float
stock Float:uPointRotate(Float:fRadiusAux,Float:fAngleAux,Float:ptAux[3])
{	
	new Float:pt[3];
	pt[0] = ptAux[0];
	pt[1] = ptAux[1];
	pt[2] = ptAux[2];

	pt[0] += fRadiusAux*cos(fAngleAux*M_PI/180);
	pt[1] += -fRadiusAux*sin(fAngleAux*M_PI/180);

	return pt;
}

//Поворот точки (вектора) на заданный угол и радиус
//Входящее значение - точка с плавающей запятой т.е. Float
//Рабочий механизм,поворачивает куда надо )))
stock Float:uRotate(Float:fAngleAux,Float:ptAux[3])
{
	//Работает в радианах
	new Float:ptRotated[3];
	ptRotated[2] = ptAux[2];

	ptRotated[0] = ptAux[0] * cos(fAngleAux) - ptAux[1] * sin(fAngleAux);
	ptRotated[1] = ptAux[0] * sin(fAngleAux) + ptAux[1] * cos(fAngleAux);

	return ptRotated;
}

//Удаление всех сущностей по названию класса со всей карты
stock uDeleteAllEntClassnameMap(const szClassNameEnt[])
{
	new idEntity;
	while ((idEntity = engfunc(EngFunc_FindEntityByString, idEntity, "classname",szClassNameEnt) ))
	{
		if (!pev_valid(idEntity)) 
			return;

		engfunc(EngFunc_RemoveEntity, idEntity);
	}
}


//Удаление всех сущностей по названию класса принадлежащие игроку
stock uDeleteAllEntClassnameUser(const szClassNameEnt[], const idUser)
{
	new idEntity;
	while ((idEntity = engfunc(EngFunc_FindEntityByString, idEntity, "classname",szClassNameEnt) ))
	{
		if (!pev_valid(idEntity)) 
			return;

		new idOwner = pev(idEntity, pev_owner);

		if(idUser == idOwner)
			engfunc(EngFunc_RemoveEntity, idEntity);

//		cssbChatColor(0,"uDeleteAllEntClassnameUser: %d",idEntity);
	}
}

//Поиск сущности по классу принадлежащую игроку. (возвращает первую попавшуюся)
stock isEntUserOwner(const szClassNameEnt[], const idUser)
{
	new idEntity;
	while ((idEntity = engfunc(EngFunc_FindEntityByString, idEntity, "classname",szClassNameEnt) ))
	{
		if (!pev_valid(idEntity)) 
			return false;

		new idOwner = pev(idEntity, pev_owner);

		if(idUser == idOwner)
			return true;

//		cssbChatColor(0,"uDeleteAllEntClassnameUser: %d",idEntity);
	}

	return false;
}

/*
Актуальность данной функции заключается в том, что если не выполнить проверку чем является точка куда перемещаем игрока, 
то он может оказаться в стене, полу или в другом игроке, что не даст возможность продолжать играть. 
Функция uIsHullVacant вернет результат проверки что вокруг проверяемой 
точки достаточно места для того что бы туда переместить игрока.
#define HULL_POINT                      0
#define HULL_HUMAN                      1
#define HULL_LARGE                      2
#define HULL_HEAD    
*/
stock bool:uIsHullVacant(const Float:origin[3], hull) 
{
	new tr = 0;
	engfunc(EngFunc_TraceHull, origin, origin, 0, hull, 0, tr);
	if (!get_tr2(tr, TR_StartSolid) && !get_tr2(tr, TR_AllSolid) && get_tr2(tr, TR_InOpen))
		return true;
	
	return false;
}

//Возвращает точку до стены от игрока
stock uGetPointTraceWall(idUser, Float:ptOriginWall[3])
{			
	new Float:ptOriginPlayer[3];
	new Float:vViewOfs[3];
	new Float:fPunchAngle[3];

	pev(idUser, pev_origin, ptOriginPlayer);					// Координата игрока
	pev(idUser, pev_view_ofs, vViewOfs);						// Получить смещение глаз игрока
	xs_vec_add(ptOriginPlayer, vViewOfs, ptOriginPlayer);		// Складываем смещение глаз и координаты игрока - получаем координаты его глаз
	pev(idUser, pev_v_angle, ptOriginWall);					// Получаем угол куда смотрит игрок
	pev(idUser, pev_punchangle, fPunchAngle);					// Это так сказать "искажение" угла взора игрока
	xs_vec_add(ptOriginWall, fPunchAngle, ptOriginWall);		// Складываем и получаем настоящий угол
	engfunc(EngFunc_MakeVectors, ptOriginWall);				// Делаем из угла единичный вектор
	global_get(glb_v_forward, ptOriginWall);					// Получаем этот вектор
	xs_vec_mul_scalar(ptOriginWall, 4048.0, ptOriginWall);	// Умножаем его
	xs_vec_add(ptOriginWall, ptOriginPlayer, ptOriginWall);	// Прибавляем к координатам игрока, чтобы получить вектор от координат игрока, направленный по его взору

	new tr;
	engfunc(EngFunc_TraceLine,ptOriginPlayer, ptOriginWall, 0, idUser, tr);	// Трассируем линию от координат до конца вектора
	get_tr2(tr, TR_vecEndPos, ptOriginWall);									// Получаем конечную точку
	free_tr2(tr);
}