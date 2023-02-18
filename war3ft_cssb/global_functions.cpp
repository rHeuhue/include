// ******************************************************************
// Глобальные функции общего назначения
// ******************************************************************

//Инициализация массивов для различных целей
public clGl::fInitArraysGlobal()//добавлена в plugin_init.cpp (public plugin_init())
{
	arrOriginCorpse_X = ArrayCreate(1, 1);
	arrOriginCorpse_Y = ArrayCreate(1, 1);
	arrOriginCorpse_Z = ArrayCreate(1, 1);
	
	//Для выпадающих вещей
	arrIntTotalLootEntity = ArrayCreate(1, 1);
	arrIntOriginsLootX = ArrayCreate(1, 1);
	arrIntOriginsLootY = ArrayCreate(1, 1);
	arrIntOriginsLootZ = ArrayCreate(1, 1);
	arrIntItemVictimShop1 = ArrayCreate(1, 1);	//Массив вещей, которые были у жертвы в первом слоте
	arrIntItemVictimShop2 = ArrayCreate(1, 1);	//Массив вещей, которые были у жертвы во втором слоте	
	arrIntItemVictimShop3 = ArrayCreate(1, 1);	//Массив вещей, которые были у жертвы в третьем слоте		
	arrIntDrawSpriteItems = ArrayCreate(1, 1);	//Массив спрайтов отрисованных вещей
	arrIntScaleSpriteItems = ArrayCreate(1, 1);	//Массив масштабов спрайтов отрисованных вещей
	arrIntLootRemove = ArrayCreate(1, 1);		//Массив таймеров отсчета удаления предметов
	
	//Для расы Хамелеон (выставление каждому игроку своих скилов)
	arrStrAuthData = ArrayCreate(64, 1);		//Массив Steam ID и ников
	arrIntWc3ChamSkill1 = ArrayCreate(1, 1);	//Массив скилов 1
	arrIntWc3ChamSkill2 = ArrayCreate(1, 1);	//Массив скилов 2
	arrIntWc3ChamSkill3 = ArrayCreate(1, 1);	//Массив скилов 3
	arrIntWc3ChamUltimate = ArrayCreate(1, 1);	//Массив супер навыков
	arrIntWc3ChamPassive = ArrayCreate(1, 1);	//Массив пассивных навыков
	arrStrFlags = ArrayCreate(64, 1);			//Массив флагов

	//ID игроков которых вызвали скелетами
	arrIntSkeletons = ArrayCreate(1, 1);	//Массив пассивных навыков sm4
}

public clGl::fPrintInfoMod(idUser)
{
	//client_cmd(idUser, "clear");

	client_print(idUser,print_console,"**************************************************");
	//***CSSB War3FT MOD Private***
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MOD_NAME",WC3_NAME);
	client_print(idUser,print_console,szMessage);
	//Версия мода:
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_MOD_VERSION",WC3_VERSION);
	client_print(idUser,print_console,szMessage);
	//Автор мода:
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_AUTHOR_MOD",WC3_AUTHOR);
	client_print(idUser,print_console,szMessage);
	//Официальный сайт мода:
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_AUTHOR_SITE",WC3_SITE);
	client_print(idUser,print_console,szMessage);
	//Skype автора мода:
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_AUTHOR_SKYPE",WC3_SKYPE);
	client_print(idUser,print_console,szMessage);
	//ICQ автора мода:
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_AUTHOR_ICQ",WC3_ICQ);
	client_print(idUser,print_console,szMessage);
	client_print(idUser,print_console," ");
	//Команда просмотра информации о моде: cssb_version
	formatex(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_CMD");
	client_print(idUser,print_console,szMessage);
	client_print(idUser,print_console,"**************************************************");
}

//Парашют
public clGl::fParachuteActive(idUser)
{
	if (!is_user_alive(idUser))
			return;

	new Float:fFallSpeed = -100.0;	

	new iButtonCurrent = get_user_button(idUser);
	new iButtonOld = get_user_oldbutton(idUser);

	if (iButtonCurrent & IN_USE) 
	{
		new Float:fVecVelocity[3];
		entity_get_vector(idUser, EV_VEC_velocity, fVecVelocity);

		if (fVecVelocity[2] < 0.0) 
		{
			entity_set_int(idUser, EV_INT_sequence, 3);
			entity_set_int(idUser, EV_INT_gaitsequence, 1);
			entity_set_float(idUser, EV_FL_frame, 1.0);
			entity_set_float(idUser, EV_FL_framerate, 1.0);
			set_user_gravity(idUser, 0.1);
			
			//Делаем полную невидимость
			fm_set_rendering(idUser,kRenderFxGlowShell,0,0,0,kRenderTransAlpha,iInvisParachute);

			fVecVelocity[2] = (fVecVelocity[2] + 40.0 < fFallSpeed) ? fVecVelocity[2] + 40.0 : fFallSpeed;
			entity_set_vector(idUser, EV_VEC_velocity, fVecVelocity);
		}
		else
		{
			SHARED_SetGravity(idUser);
			//Восстанавливаем нормальную невидимость
			fm_set_rendering(idUser);
			//Восстанавливаем невидимсть если скил Невидимости или имеется плащ
			SHARED_INVIS_Set(idUser);
		}
	}
	else if ((iButtonOld & IN_USE)) 
	{
		SHARED_SetGravity(idUser);
		//Восстанавливаем нормальную невидимость
		fm_set_rendering(idUser);
		//Восстанавливаем невидимсть если скил Невидимости или имеется плащ
		SHARED_INVIS_Set(idUser);
	}
}


//Если игрок сидит в спектрах(команда не выбрана)
bool:clGl::isUserNoTeam(const idUser)
{	
	if(!SHARED_IsOnTeam(idUser))
	{
		format(szMessage, charsmax(szMessage), "%L",LANG_PLAYER,"CLIENT_PRINT_NO_ALIVE");
		cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

		return false;
	}

	return true;

}



















////////////Тесты различных функций {

/*
	//Прикольный эффект  (где-нибудь применить его)
	//Наподобии отброса можно сделать
	if ((pev(idUser, pev_flags) & FL_ONGROUND))
	{
		static Float:velocity[3];
		pev(idUser, pev_velocity, velocity);
		xs_vec_mul_scalar(velocity, 5.0, velocity);
		set_pev(idUser, pev_velocity, velocity);
	}	
*/


/*
public fwKeyValue(idEntity, pKeyValueData)
{
    new szClassName[32];
    get_kvd(pKeyValueData, KV_ClassName, szClassName,31);
        
    new szKeyName[32], szValue[32];
    new iNumvalue;
    
    get_kvd(pKeyValueData, KV_KeyName, szKeyName, 31);
    get_kvd(pKeyValueData, KV_Value, szValue, 31);
    iNumvalue = str_to_num(szValue);


	//server_print("Ent #%d count=%d", idEntity, iNumvalue);
	server_print("C = %s | K = %s | V = %s", szClassName,szKeyName,szValue);

	return FMRES_IGNORED;
}*/




public fTest1(idUser)
{
/*
//----------Вывод активной модели оружия----------	
	new model[128];
	new ptr = pev(idUser, pev_viewmodel);
	global_get(glb_pStringBase, ptr, model, 127);
	formatex(szMessage, charsmax(szMessage), "%s",model);
	cssbChatColor(idUser,"%s%s",fTagWar3ft(),szMessage);

//----------Координата нахождения игрока и смещение точки до уровня глаз----------	
	new Float:viewOfs[3];
	new Float:ptStart[3], Float:ptEnd[3];
	pev(idUser, pev_origin, ptStart);
	pev(idUser, pev_origin, ptEnd);
	pev(idUser, pev_view_ofs, viewOfs);
	xs_vec_add(ptEnd, viewOfs, ptEnd);

	Create_TE_BEAMPOINTS(uFloatPointToInt(ptStart), uFloatPointToInt(ptEnd), arrIdSprites[SPR_BEAM], 0, 0, 100, 10, 5, colorElfEntangleRGB[0], colorElfEntangleRGB[1], colorElfEntangleRGB[2], 255, 0 );

//----------Направление куда смотрит игрок----------
	// Объявляем используемые переменные
	new Float:origin2[3], Float:vViewOfs[3], Float:angle[3], Float:fPunchAngle[3]//, tr
	// Получить координаты игрока
	pev(idUser, pev_origin, origin2)
	// Получить смещение глаз игрока
	pev(idUser, pev_view_ofs, vViewOfs)
	// Складываем смещение глаз и координаты игрока - получаем координаты его глаз
	xs_vec_add(origin2, vViewOfs, origin2)
	// Получаем угол куда смотрит игрок
	pev(idUser, pev_v_angle, angle)
	// Это так сказать "искажение" угла взора игрока
	pev(idUser, pev_punchangle, fPunchAngle)
	// Складываем и получаем настоящий угол
	xs_vec_add(angle, fPunchAngle, angle)
	// Делаем из угла единичный вектор
	engfunc(EngFunc_MakeVectors, angle)
	// Получаем этот вектор
	global_get(glb_v_forward, angle)
	// Умножаем его
	xs_vec_mul_scalar(angle, 100.0, angle)
	// Прибавляем к координатам игрока, чтобы получить вектор от координат игрока, направленный по его взору
	xs_vec_add(angle, origin2, angle)
	// Трассируем линию от координат до конца вектора
//	engfunc(EngFunc_TraceLine, origin2, angle, 0, idUser, tr)
	// Получаем конечную точку
//	get_tr2(tr, TR_vecEndPos, angle)
	// Освобождаем "указатель" трассирования
//	free_tr2(tr)
//   После этого начальная позиция пули в origin, конечная в angle

	Create_TE_BEAMPOINTS(uFloatPointToInt(ptEnd), uFloatPointToInt(angle), arrIdSprites[SPR_BEAM], 0, 0, 100, 10, 5,   0,0,255,    255, 0 );

//----------Разворот на определенный градус вектора от заданной точки и на заданное расстояние----------
	angle[0] = ptStart[0];
	angle[1] = ptStart[1];
	angle[2] = ptStart[2];

	angle[0] += 100*cos(90.0*M_PI/180);
	angle[1] += -100*sin(90.0*M_PI/180);

	Create_TE_BEAMPOINTS(uFloatPointToInt(ptStart), uFloatPointToInt(angle), arrIdSprites[SPR_BEAM], 0, 0, 100, 10, 5,   255,0,0,    255, 0 );
*/
/*
									180
									 ^
								     |
								     |
								     |
              	  90<------Игрок смотрит вперед ------>270
								     |
								     |
								     |
									 v
	   разворот по часовой  <--- 0
*/

	new Float:ptOriginPlayer[3];
	pev(idUser, pev_origin, ptOriginPlayer); // Координата игрока
	//ptOriginPlayer[2] -= 10;

	new Float:ptForward[3];
	ptForward = uFloatPointToFloat(ptOriginPlayer);
	new Float:ptLeft[3];
	ptLeft = uFloatPointToFloat(ptOriginPlayer);
	new Float:ptBack[3];
	ptBack = uFloatPointToFloat(ptOriginPlayer);
	new Float:ptRight[3];
	ptRight = uFloatPointToFloat(ptOriginPlayer);

	ptForward = uPointRotate(100.0,0.0,ptForward);//синий цвет
//	Create_TE_BEAMPOINTS(uFloatPointToInt(ptOriginPlayer), uFloatPointToInt(ptForward), arrIdSprites[SPR_BEAM], 0, 0, 100, 10, 5,   0,0,255,    255, 0 );

	ptRight = uPointRotate(100.0,90.0,ptRight);//желтый цвет
//	Create_TE_BEAMPOINTS(uFloatPointToInt(ptOriginPlayer), uFloatPointToInt(ptRight), arrIdSprites[SPR_BEAM], 0, 0, 100, 10, 5,   232,236,18,    255, 0 );

	ptBack = uPointRotate(100.0,180.0,ptBack); //красный цвет
//	Create_TE_BEAMPOINTS(uFloatPointToInt(ptOriginPlayer), uFloatPointToInt(ptBack), arrIdSprites[SPR_BEAM], 0, 0, 100, 10, 5,   255,0,0,    255, 0 );

	ptLeft = uPointRotate(100.0,270.0,ptLeft);//зеленый цвет
//	Create_TE_BEAMPOINTS(uFloatPointToInt(ptOriginPlayer), uFloatPointToInt(ptLeft), arrIdSprites[SPR_BEAM], 0, 0, 100, 10, 5,   0,255,0,    255, 0 );


	new idEntity = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	
	if(!pev_valid(idEntity))
	{
		//cssbChatColor(idUser,"%s%s",fTagWar3ft(),"pev_valid(idEntity)");
		return;
	}
	
	set_pev(idEntity, pev_classname, "test1");									// Задаем класс создаваемой сущности
	set_pev(idEntity, pev_origin, ptForward);									// Задаем позицию сущности
	set_pev(idEntity, pev_fuser1, 0.0);											// Сохраням угол
	set_pev(idEntity, pev_vuser1, ptOriginPlayer);								// Сохраняем точку респауна

	set_pev(idEntity, pev_owner, idUser);										// Задаем сущности владельца	
	set_pev(idEntity, pev_modelindex, arrIdSprites[SPR_DRUID_ENTANGLE]);				// Задаем индекс создаваемой сущности
	fm_set_rendering(idEntity, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255);	// Задание прозрачнсти

	/*
	new Float: velocity[3];
	velocity_by_aim(idUser, 5000, velocity);
	set_pev(idEntity, pev_velocity, velocity); // Задает скорость и направление куда смотрит игрок
*/


	//engfunc(EngFunc_SetModel, idEntity, arrStrSprites[SPR_ROGUE_SHURIKEN]);
	
	//set_pev(idEntity, pev_effects, pev(idEntity, pev_effects) | EF_BRIGHTFIELD);	//Частицы
	//set_pev(idEntity, pev_effects, pev(idEntity, pev_effects) | EF_BRIGHTLIGHT);	//Большое Освещение
	//set_pev(idEntity, pev_effects, pev(idEntity, pev_effects) | EF_DIMLIGHT);	//Маленькое Освещение
	//set_pev(idEntity, pev_effects, pev(idEntity, pev_effects) | EF_INVLIGHT);	//Аура
	//set_pev(idEntity, pev_effects, pev(idEntity, pev_effects) | EF_LIGHT);	//Быстро пульсирующий с мелкой подсветкой
	//set_pev(idEntity, pev_effects, pev(idEntity, pev_effects) | EF_NODRAW);	//Сущность исчезает полностью
		
	
//	set_pev(idEntity, pev_movetype, MOVETYPE_BOUNCEMISSILE); //отскакивает от стен (гравитация не работает)
//	set_pev(idEntity, pev_solid, SOLID_BBOX);

	set_pev(idEntity, pev_movetype, MOVETYPE_FLY);
/*
// pev(entity, pev_movetype) values
#define	MOVETYPE_NONE                   0           // Never moves
#define	MOVETYPE_WALK                   3           // Player only - moving on the ground
#define	MOVETYPE_STEP                   4           // Gravity, special edge handling -- monsters use this
#define	MOVETYPE_FLY                    5           // Нет силы тяжести т.е. может летать,но не сталкивается с препятствиями
#define	MOVETYPE_TOSS                   6           // Gravity/Collisions
#define	MOVETYPE_PUSH                   7           // No clip to world, push and crush
#define	MOVETYPE_NOCLIP                 8           // No gravity, no collisions, still do velocity/avelocity
#define	MOVETYPE_FLYMISSILE             9           // Extra size to monsters
#define	MOVETYPE_BOUNCE                 10          // Just like Toss, but reflect velocity when contacting surfaces
#define MOVETYPE_BOUNCEMISSILE          11          // Bounce w/o gravity
#define MOVETYPE_FOLLOW                 12          // Track movement of aiment
#define	MOVETYPE_PUSHSTEP               13          // BSP model that needs physics/world collisions (uses nearest hull for world collision)
*/
	set_pev(idEntity, pev_solid, SOLID_BBOX);
/*
// pev(entity, pev_solid) values
// NOTE: Some movetypes will cause collisions independent of SOLID_NOT/SOLID_TRIGGER when the entity moves
// SOLID only effects OTHER entities colliding with this one when they move - UGH!
#define	SOLID_NOT                       0           // No interaction with other objects
#define	SOLID_TRIGGER                   1           // Touch on edge, but not blocking
#define	SOLID_BBOX                      2           // Touch on edge, block
#define	SOLID_SLIDEBOX                  3           // Touch on edge, but not an onground
#define	SOLID_BSP                       4           // BSP clip, touch on edge, block
*/

	set_pev(idEntity, pev_scale, 0.1);				//Задаем масштаб сущности
	set_pev(idEntity, pev_dmg, 15.0);				// Закладываем дамаг в сущность (обрабатывается потом)
	set_pev(idEntity, pev_dmgtime,get_gametime());			// Закладываем время через которое будет работать дамаг

	/* Для спрайта не работает
	set_pev(idEntity, pev_frame, 0.0);
	set_pev(idEntity, pev_sequence, 1); //Номер анимации модели
    set_pev(idEntity, pev_animtime, get_gametime()); // В какую секунду сработает анимация
    set_pev(idEntity, pev_framerate, 1.0);	//Скорость анимации
	*/

	dllfunc(DLLFunc_Spawn, idEntity);	//Делаем респаун сущности


//	new iTeam = get_user_team(idOwnerModel);
//	set_pev(idEntity,pev_team,iTeam);

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);	//Запуск обработчика Think

//	
//	set_pev(idEntity, pev_model, arrIdSprites[SPR_ROGUE_SHURIKEN]);

}

public Test_Think(idEntity)
{
	if (!pev_valid(idEntity)) 
		return;


	//Анимация спрайта
	if (entity_get_float(idEntity, EV_FL_frame) > 6)
		entity_set_float(idEntity, EV_FL_frame, 0.0);
	else
		entity_set_float(idEntity, EV_FL_frame, entity_get_float(idEntity, EV_FL_frame) + 1.0);

	
	//new idOwner = pev(idEntity, pev_owner);

	
	new Float:ptForwardRotate[3];
//	pev(idOwner, pev_origin, ptForwardRotate);
	pev(idEntity, pev_vuser1, ptForwardRotate);
	//ptForwardRotate[2] -= 10;

	//Разворачиваем сущность на заданный градус
	new Float:fAngle = float(pev(idEntity, pev_fuser1));
	ptForwardRotate = uPointRotate(100.0,fAngle,ptForwardRotate);

	set_pev(idEntity, pev_origin, ptForwardRotate);	
	set_pev(idEntity, pev_fuser1, fAngle + 3.0);

//	xs_vec_set(pt, 0.0,0.0, -1.0);
	
//	new Float:fDmg = float(pev(idEntity, pev_dmg));
	new Float:fDmgTimeGlowworm = float(pev(idEntity, pev_dmgtime));
//	engfunc(EngFunc_RemoveEntity, idEntity);


	new Float:ptOriginEntity[3];
	pev(idEntity, pev_origin, ptOriginEntity);
	
	new idVictim;
	while ((idVictim = engfunc(EngFunc_FindEntityInSphere, idVictim, ptOriginEntity, 150.0)))
	{
		//if (pev(idVictim, pev_takedamage) && is_visible(idVictim, idEntity) && idVictim != idOwner)
		if (pev(idVictim, pev_takedamage) && is_visible(idVictim, idEntity))
		{
			new Float:ptOriginVictim[3]; 
			pev(idVictim, pev_origin, ptOriginVictim);



			if ((fDmgTimeGlowworm + 1.0) > get_gametime())
				break;
			
			fDmgTimeGlowworm = get_gametime();
			set_pev(idEntity, pev_dmgtime,fDmgTimeGlowworm);
		
		
		

			//ExecuteHamB(Ham_TakeDamage, idVictim, idEntity, idOwner, 0.0, DMG_ENERGYBEAM );
			//ExecuteHamB(Ham_TakeDamage, idVictim, idEntity, idOwner, 0.0, DMG_FREEZE );

			//new Float:vVelocity[3]; 
			//xs_vec_set(vVelocity, 10.0, 0.0, 0.0);
//			pev(idVictim, pev_velocity, vVelocity);
			//static Float:velocity[3]
			//velocity_by_aim(idVictim, 10, vVelocity) ;

			//new Float:ptNewVictim[3];
			//xs_vec_sub(ptOriginVictim, ptForwardRotate, ptOriginVictim);
			//xs_vec_add(ptOriginVictim,ptForwardRotate, ptNewVictim);

			//engfunc(EngFunc_MakeVectors, ptNewVictim);
			//global_get(glb_v_forward, ptNewVictim);
			//xs_vec_normalize(ptNewVictim,ptNewVictim);
			//xs_vec_mul_scalar(ptNewVictim, 100.0, ptNewVictim);

			//velocity_by_aim(idUser, 650, velocity);
			//set_pev(idEntity, pev_velocity, vVelocity);

		//	set_pev(idEntity, pev_velocity, Float:{0.0, 0.0, 0.0});

			//pev(idEntity, pev_origin, ptForwardRotate);
			//set_pev(idEntity, pev_vuser1, ptOriginEntity);

//			Create_TE_BEAMPOINTS(uFloatPointToInt(ptOriginEntity), uFloatPointToInt(ptOriginVictim), arrIdSprites[SPR_BEAM], 0, 0, 100, 10, 5,   0,255,0,    255, 0 );
			Create_TE_BEAMENTS( idEntity, idVictim, arrIdSprites[SPR_LIGHTNING], 0, 1, 1, 20, 30, 0,255,0,    255, 0 );
			
	

	//		cssbChatColor(idVictim,"time: %f",get_gametime());
//			cssbChatColor(idVictim,"fDmgTime: %f",fDmgTime);
			cssbChatColor(idVictim,"fDmgTimeGlowworm: %f",fDmgTimeGlowworm);
			
		}
	}

	set_pev(idEntity, pev_nextthink, get_gametime() + 0.1);

	//cssbChatColor(idOwner,"fAngle: %f",fAngle);
}


public fTest2(idUser)
{
	
}




//Хороший пример отрисовки лазера по направлению прицела игрока.
/*
	new iOrigin[3]
	get_user_origin(idUser, iOrigin)
	client_print(idUser, print_chat, "Origin: %d, %d, %d", iOrigin[0], iOrigin[1], iOrigin[2])
	
	new Float:fOrigin[3]
	
	// fm_get_aim_origin() from fakemet_util.inc
	new Float:start[3], Float:view_ofs[3];
	pev(idUser, pev_origin, start);
	pev(idUser, pev_view_ofs, view_ofs);
	xs_vec_add(start, view_ofs, start);

	new Float:dest[3];
	pev(idUser, pev_v_angle, dest);
	engfunc(EngFunc_MakeVectors, dest);
	global_get(glb_v_forward, dest);
	xs_vec_mul_scalar(dest, 9999.0, dest);
	xs_vec_add(start, dest, dest);

	new pTrace = create_tr2()
	engfunc(EngFunc_TraceLine, start, dest, 0, idUser, pTrace);
	get_tr2(pTrace, TR_vecEndPos, fOrigin);
	new hitent = get_tr2(pTrace, TR_pHit)
	free_tr2(pTrace)
	
	if( pev_valid(hitent) )
	{
		new szClassname[32]
		pev(hitent, pev_classname, szClassname, charsmax(szClassname))
		client_print(idUser, print_chat, szClassname)
	}
	
	message_begin(MSG_BROADCAST ,SVC_TEMPENTITY)
	write_byte(TE_BEAMPOINTS)
	write_coord(iOrigin[0])	// start position
	write_coord(iOrigin[1])
	write_coord(iOrigin[2])
	write_coord(floatround(fOrigin[0]))	// end position
	write_coord(floatround(fOrigin[1]))
	write_coord(floatround(fOrigin[2]))
	write_short(arrIdSprites[SPR_LIGHTNING])	// sprite index
	write_byte(0)	// starting frame
	write_byte(0)	// frame rate in 0.1's
	write_byte(50)	// life in 0.1's
	write_byte(10)	// line width in 0.1's
	write_byte(0)	// noise amplitude in 0.01's
	write_byte(255)	// Red
	write_byte(0)	// Green
	write_byte(0)	// Blue
	write_byte(127)	// brightness
	write_byte(0)	// scroll speed in 0.1's
	message_end()
	
	// message_begin(MSG_BROADCAST ,SVC_TEMPENTITY)
	// write_byte(TE_BEAMCYLINDER)
	// write_coord(iOrigin[0]) // position.x
	// write_coord(iOrigin[1]) // position.y
	// write_coord(iOrigin[2]) // position.z
	// write_coord(iOrigin[0]) // axis.x
	// write_coord(iOrigin[1]) // axis.y
	// write_coord(iOrigin[2]+100) // axis.z
	// write_short(arrIdSprites[SPR_LIGHTNING]) // sprite index
	// write_byte(0) // starting frame
	// write_byte(0) // frame rate in 0.1's
	// write_byte(50) // life in 0.1's
	// write_byte(10) // line width in 0.1's
	// write_byte(0) // noise amplitude in 0.01's
	// write_byte(0) // R
	// write_byte(0) // G
	// write_byte(255) // B
	// write_byte(127) // brightness
	// write_byte(0) // scroll speed in 0.1's
	// message_end()

*/

////////////Тесты различных функций }

