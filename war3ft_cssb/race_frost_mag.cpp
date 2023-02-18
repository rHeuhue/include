/*
*	Race: Frost Mage Functions
*/

// ****************************************
// Frost Mage Blizzard Ultimate
// ����� ����� "������� ����" - Ultimate
// ****************************************
public FM_ULT_Blizzard( iCaster, iTarget, iBodyPart )
{
	emit_sound(iCaster, CHAN_STATIC, arrStrSounds[SOUND_BLIZZARD], 0.5, ATTN_NORM, 0, PITCH_NORM );

	new vOrigin[3];
	get_user_origin( iTarget, vOrigin );

	new ptStartBlizzard[3], ptEndBlizzard[3];
	ptStartBlizzard[0] = vOrigin[0];
	ptStartBlizzard[1] = vOrigin[1];
	ptStartBlizzard[2] = vOrigin[2] + 600;
	ptEndBlizzard[0] = vOrigin[0];
	ptEndBlizzard[1] = vOrigin[1];
	ptEndBlizzard[2] = vOrigin[2] - 600;

	new ptStartIceBolt[3], ptEndIceBolt[3];
	ptStartIceBolt[0] = vOrigin[0];
	ptStartIceBolt[1] = vOrigin[1];
	ptStartIceBolt[2] = vOrigin[2] + 100;
	ptEndIceBolt[0] = vOrigin[0];
	ptEndIceBolt[1] = vOrigin[1];
	ptEndIceBolt[2] = vOrigin[2] + 50;

	WC3_Damage(iTarget, iCaster,iDamageBlizzard, CSW_BLIZZARD, iBodyPart );

	Create_TE_BEAMPOINTS(ptStartBlizzard, ptEndBlizzard, arrIdSprites[SPR_BLUE_LIGHTNING],0, 0, 15, 255, 0, 255, 255, 255, 255, 0);

	//������� �����
	for(new i = 1; i < 6; i++) 
		Create_TE_SPRITETRAIL(ptStartIceBolt, ptEndIceBolt, arrIdSprites[SPR_ICE_FROSTBOLT],50, random_num(27,30), 1, random_num(30,70), 40 )

	new team = get_user_team( iTarget );
	new arrPlayers[32], iNumPlayers, vClosestTargetOrigin[3];
	get_players(arrPlayers, iNumPlayers, "a");

	//����������� ���������� ������������ �������� �������
	for(new i = 0; i < iNumPlayers; i++ )
	{
		if ( is_user_alive( arrPlayers[i] ) )
		{
			if (arrPlayers[i] != iTarget)
			{
				if ( get_user_team( arrPlayers[i] ) == team )
				{
					get_user_origin( arrPlayers[i], vClosestTargetOrigin );

					if ( get_distance( vOrigin, vClosestTargetOrigin ) <= iDamageBlizzardRadius )
					{
						WC3_Damage( arrPlayers[i],iCaster, iDamageIceBolt, CSW_BLIZZARD, 0 );
											
						emit_sound(iTarget, CHAN_STATIC, arrStrSounds[SOUND_BLIZZARD], 0.5, ATTN_NORM, 0, PITCH_NORM );
					}
				}
			}
		}
	}
	
	return PLUGIN_HANDLED;
}

//���� 1 ������ - ������� ���� (Ice splinters)
FM_SkillsOffensive( idAttacker, idVictim, iHitPlace )
{
	if ( !arrBoolData[idVictim][PB_ISCONNECTED] || !arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;
		
	new iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_FROST_MAGE_ICE_SPLINTERS );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false
		&& ((get_user_team( idAttacker ) != get_user_team( idVictim ))))
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_FROST_MAGE_ICE_SPLINTERS) == true)
			return;

		new Float:fIceSplinters = ArrayGetCell(arrIceSplinters,iSkillLevel-1);
		if (random_float(fIceSkill1MinPercent,fIceSkill1MaxPercent) <= fIceSplinters )
		{
			new vVictimOrigin[3], vAttackerorigin[3];
			get_user_origin( idVictim, vVictimOrigin );
			get_user_origin( idAttacker, vAttackerorigin );
						
			Create_TE_SPRITETRAIL(vAttackerorigin, vVictimOrigin, arrIdSprites[SPR_ICE_SPLINTERS],50, random_num(27,30), 1, random_num(30,70), 40 )
			
			emit_sound( idAttacker, CHAN_STATIC, arrStrSounds[SOUND_ICE_SPLINTERS], 1.0, ATTN_NORM, 0, PITCH_NORM );
			emit_sound( idVictim, CHAN_STATIC, arrStrSounds[SOUND_ICE_SPLINTERS], 1.0, ATTN_NORM, 0, PITCH_NORM );

			WC3_Damage( idVictim, idAttacker,floatround(fIceSplinters), CSW_ICE_SPLINTERS, iHitPlace );
		}
		else if ( get_pcvar_num( CVAR_wc3_psychostats ) )
		{
			new WEAPON = CSW_ICE_SPLINTERS - CSW_WAR3_MIN;

			iStatsShots[idAttacker][WEAPON]++;
		}
	}
		
}

//���� 2 ������ - ������� ������ (Ice Arrow)
FM_SkillsOffensive_Ice_Arrow(idAttacker, idVictim)
{
	if ( !arrBoolData[idVictim][PB_ISCONNECTED] || !arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;

	new iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_FROST_MAGE_ICE_ARROW );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false 
		&& ((get_user_team( idAttacker ) != get_user_team( idVictim ))))
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_FROST_MAGE_ICE_ARROW) == true)
			return;

		new Float:fIceArrow = ArrayGetCell(arrIceArrow,iSkillLevel-1);
		if ( random_float(fIceSkill2MinPercent,fIceSkill2MaxPercent) <= fIceArrow )
		{
			if ( task_exists( TASK_REMOVE_FROZEN + idVictim ) == 0 )
			{
				fCreateIceArrowTrail(idAttacker);

				emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_ICE_ARROW_MISSILE], 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
						
		}
		
	}
		
}

public fCreateIceArrowTrail(idAttacker)
 {
	if (!is_user_alive(idAttacker)) 
		return PLUGIN_HANDLED;

	new Float: fOrigin[3], Float:fAngle[3],Float: fVelocity[3];
	pev(idAttacker, pev_origin, fOrigin);
	pev(idAttacker, pev_view_ofs, fAngle);
	fm_velocity_by_aim(idAttacker, 2.0, fVelocity, fAngle);
	fAngle[0] *= -1.0;
	
	// create ent
	new entIceArrow = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, "info_target"));
	set_pev(entIceArrow, pev_classname, "IceArrow");
	engfunc(EngFunc_SetModel, entIceArrow, "sprites/warcraft3/ice_arrow.spr");
	set_pev(entIceArrow, pev_mins, Float:{-1.0, -1.0, -1.0});
	set_pev(entIceArrow, pev_maxs, Float:{1.0, 1.0, 1.0});
	set_pev(entIceArrow, pev_origin, fOrigin);
	fOrigin[0] += fVelocity[0];
	fOrigin[1] += fVelocity[1];
	fOrigin[2] += fVelocity[2];

	entity_set_float(entIceArrow,EV_FL_framerate,1.0);//framerate
	entity_set_int(entIceArrow, EV_INT_rendermode, 5);//randermode
	entity_set_float(entIceArrow, EV_FL_renderamt, 255.0);//visable

	set_pev(entIceArrow, pev_movetype, MOVETYPE_BOUNCE);
	set_pev(entIceArrow, pev_gravity, 0.01);
	fVelocity[0] *= 1000;
	fVelocity[1] *= 1000;
	fVelocity[2] *= 1000;
	set_pev(entIceArrow, pev_velocity, fVelocity);
	set_pev(entIceArrow, pev_owner, idAttacker);
	set_pev(entIceArrow, pev_angles, fAngle);
	set_pev(entIceArrow, pev_solid, SOLID_BBOX);//store the enitty id
	
	// invisible ent
	//fm_set_rendering(ent, kRenderFxGlowShell, 0, 0, 0, kRenderTransAlpha, 0);
	
	// show trail	
	message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte(TE_BEAMFOLLOW);
	write_short(entIceArrow);//entity
	write_short(arrIdSprites[SPR_ICE_ARROW_TRAIL]);//model
	write_byte(25);// byte (life in 0.1's)
	write_byte(9);// byte (line width in 0.1's)
	write_byte(42);// byte (color)
	write_byte(170);// byte (color)
	write_byte(255);// byte (color)
	write_byte(255);// byte (brightness)
	message_end();

	return PLUGIN_HANDLED;

}

fm_velocity_by_aim(iIndex, Float:fDistance, Float:fVelocity[3], Float:fViewAngle[3])
{
	pev(iIndex, pev_v_angle, fViewAngle);
	fVelocity[0] = floatcos(fViewAngle[1], degrees) * fDistance;
	fVelocity[1] = floatsin(fViewAngle[1], degrees) * fDistance;
	fVelocity[2] = floatcos(fViewAngle[0]+90.0, degrees) * fDistance;
	return 1;
}

//�������� ������ ��� ������������� ������ � ������� ��� ������������
public fCreateExplodeIceArrow(entIceArrow)
{
	new Float:fOrigin[3];
	new iOrigin[3];
	entity_get_vector(entIceArrow, EV_VEC_origin, fOrigin);
	FVecIVec(fOrigin, iOrigin);

	message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
	write_byte(TE_GLOWSPRITE);
	write_coord(iOrigin[0]);
	write_coord(iOrigin[1]);
	write_coord(iOrigin[2]);
	write_short(arrIdSprites[SPR_ICE_EXPLODE]);// model
	write_byte(3);// life 0.x sec
	write_byte(6);	// size
	write_byte(110);// brightness
	message_end();

	emit_sound(entIceArrow, CHAN_AUTO, arrStrSounds[SOUND_ICE_EXPLODE], 1.0, ATTN_NORM, 0, PITCH_NORM);

	if (is_valid_ent(entIceArrow)) 
		remove_entity(entIceArrow);
}


public touchIceArrow(entIceArrow,idWorldPlayer) 
{
	//���� ������ �������� � �����-������ ����� (�����,��� � �.�.)
	if(idWorldPlayer == 0) 
	{
		fCreateExplodeIceArrow(entIceArrow);
	}
	//���� ������ �������� � ������
	else if(is_user_connected(idWorldPlayer) && arrBoolData[idWorldPlayer][PB_ISFROZENPLAYER] == false)
	{
		//���� ������ �������� � ������ � �� �� �� ����� �������
		new idAttacker = entity_get_edict(entIceArrow,EV_ENT_owner);
		if(get_user_team(idWorldPlayer) != get_user_team(idAttacker))
		{
			//�������� ������� ���������
			message_begin(MSG_ONE, get_user_msgid("ScreenFade"), _, idWorldPlayer);
			write_short(0);// duration
			write_short(0);// hold time
			write_short(FFADE_STAYOUT);// fade type
			write_byte(0);// red
			write_byte(50);// green
			write_byte(200);// blue
			write_byte(100);// alpha
			message_end();

			fm_set_rendering(idWorldPlayer, kRenderFxGlowShell, 0, 100, 200, kRenderNormal, 25);

			// Prevent from jumping
			if (pev(idWorldPlayer, pev_flags) & FL_ONGROUND)
				set_pev(idWorldPlayer, pev_gravity, 999999.9);// set really high
			else
				set_pev(idWorldPlayer, pev_gravity, 0.000001);// no gravity

			set_pev(idWorldPlayer, pev_velocity, Float:{0.0,0.0,0.0});// stop motion
			set_pev(idWorldPlayer, pev_maxspeed, 1.0);// prevent from moving

			fCreateExplodeIceArrow(entIceArrow);

			arrBoolData[idWorldPlayer][PB_ISFROZENPLAYER] = true;

			new iSkillLevel = SM_GetSkillLevel(idAttacker, SKILL_FROST_MAGE_ICE_ARROW );
			if(iSkillLevel > 0 && isDisabledSkillsOnMap(idAttacker,SKILL_FROST_MAGE_ICE_ARROW) == false)
			{
				new Float:fIceArrow = ArrayGetCell(arrIceArrow,iSkillLevel-1);
				set_task(fIceArrow, "fRemoveFreeze", TASK_REMOVE_FROZEN + idWorldPlayer );
			}

		}
		//���� ������ �������� � ������ � �� �� ����� �������
		else 
		{
			fCreateExplodeIceArrow(entIceArrow)
		}
	} 
	//���� ����� �������� ������ � ����� � �������
	else
	{
		fCreateExplodeIceArrow(entIceArrow);
	}
}

//�������� ���������
public fRemoveFreeze( idUser )
{
	if ( idUser >= TASK_REMOVE_FROZEN )
		idUser -= TASK_REMOVE_FROZEN;

	if ( !arrBoolData[idUser][PB_ISCONNECTED] )
		return;

	arrBoolData[idUser][PB_ISFROZENPLAYER] = false;

//	client_print(0,print_chat,"fRemoveFreeze");

	SHARED_SetGravity( idUser );
	
	SHARED_SetSpeed( idUser );

	fm_set_rendering(idUser);

	// Gradually remove screen's blue tint
	message_begin(MSG_ONE, get_user_msgid("ScreenFade"), _, idUser);
	write_short(UNIT_SECOND);// duration
	write_short(0);// hold time
	write_short(FFADE_IN);// fade type
	write_byte(0);// red
	write_byte(50);// green
	write_byte(200);// blue
	write_byte(100);// alpha
	message_end();
	
	static origin2[3];
	get_user_origin(idUser, origin2);
	
	// Glass shatter
	message_begin(MSG_PVS, SVC_TEMPENTITY, origin2);
	write_byte(TE_BREAKMODEL);
	write_coord(origin2[0]); // x
	write_coord(origin2[1]); // y
	write_coord(origin2[2]+24); // z
	write_coord(16);// size x
	write_coord(16);// size y
	write_coord(16);// size z
	write_coord(random_num(-50, 50));// velocity x
	write_coord(random_num(-50, 50));// velocity y
	write_coord(25);// velocity z
	write_byte(10);// random velocity
	write_short(arrIdModels[MDL_GLASSGIBS]);// model
	write_byte(10);// count
	write_byte(25);// life
	write_byte(BREAK_GLASS); // flags
	message_end();

	return;
}

//���� 3 ������ - ����� ������ (Cold cone)
FM_SkillsOffensive_Cone_Cold(idAttacker, idVictim)
{
	if ( !arrBoolData[idVictim][PB_ISCONNECTED] || !arrBoolData[idAttacker][PB_ISCONNECTED] )
		return;

	new iSkillLevel = SM_GetSkillLevel( idAttacker, SKILL_FROST_MAGE_CONE_OF_COLD );
	if ( iSkillLevel > 0 && arrBoolData[idAttacker][PB_ISFROZENSKILL] == false
		&& ((get_user_team( idAttacker ) != get_user_team( idVictim ))))
	{
		if(isDisabledSkillsOnMap(idAttacker,SKILL_FROST_MAGE_CONE_OF_COLD) == true)
			return;

		new Float:fConeCold = ArrayGetCell(arrColdCone,iSkillLevel-1);
		if ( random_float(fIceSkill3MinPercent,fIceSkill3MaxPercent) <= fConeCold )
		{
			if ( task_exists( TASK_FROZEN_SKILL + idVictim ) == 0 )
			{
				new vVictimOrigin[3],vAxisOrigin[3];
				get_user_origin( idVictim, vVictimOrigin );

				vAxisOrigin[2] += vVictimOrigin[2] + 100;
				Create_TE_BEAMCYLINDER( vVictimOrigin, vVictimOrigin, vAxisOrigin, arrIdSprites[SPR_SHOCKWAVE], 0, 0, 4, 60, 0, 41, 138, 255, 200, 0 );

				arrBoolData[idVictim][PB_ISFROZENSKILL] = true;

				set_task(fConeCold, "fRemoveFrozenSkill", TASK_FROZEN_SKILL + idVictim );

				emit_sound(idAttacker, CHAN_STATIC, arrStrSounds[SOUND_COLD_CONE_S], 1.0, ATTN_NORM, 0, PITCH_NORM );
				emit_sound(idVictim, CHAN_STATIC, arrStrSounds[SOUND_COLD_CONE_S], 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
						
		}
		
	}
}

//�������� ��������� ������
public fRemoveFrozenSkill(idUser)
{
	if (idUser >= TASK_FROZEN_SKILL )
		idUser -= TASK_FROZEN_SKILL;

	if (!arrBoolData[idUser][PB_ISCONNECTED] )
		return;

	//client_print(0,print_chat,"fRemoveFrozenSkill");

	arrBoolData[idUser][PB_ISFROZENSKILL] = false;

	emit_sound(idUser, CHAN_STATIC, arrStrSounds[SOUND_COLD_CONE_E], 1.0, ATTN_NORM, 0, PITCH_NORM );

	return;
}