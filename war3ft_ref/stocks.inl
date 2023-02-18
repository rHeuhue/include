stock get_user_maxhealth( id )
{

	new maxHealth = 100

	static iSkillLevel;
	iSkillLevel = SM_GetSkillLevel( id, SKILL_DEVOTION );

	// Human Devotion Skill
	if ( iSkillLevel > 0 )
	{
		maxHealth += iSkillLevel * p_devotion;
	}


	// Player has a health bonus from the Periapt of Health

	if ( ITEM_Has( id, ITEM_HEALTH ) > ITEM_NONE )
		maxHealth += get_pcvar_num( CVAR_wc3_health );

	return maxHealth
}

// Function checks to see if the weapon is a pistol
stock SHARED_IsSecondaryWeapon( iWeaponID )
{
	// Check for Counter-Strike or Condition Zero
	if ( g_MOD == GAME_CSTRIKE || g_MOD == GAME_CZERO )
	{
		if ( iWeaponID == CSW_ELITE || iWeaponID == CSW_FIVESEVEN || iWeaponID == CSW_USP || iWeaponID == CSW_GLOCK18 || iWeaponID == CSW_DEAGLE || iWeaponID == CSW_P90 )
		{
			return true;
		}
	}
	



	return false;
}

// Check the vip 
stock is_user_vip(id)
{
   
   if(get_user_flags(id) & VIP_LEVEL) return true
   else return false
   
   //return PLUGIN_CONTINUE
}

// Nice color message 
stock ColorChat(const id, const input[], any:...) {
	new count = 1, players[32];
	static msg[191];
	vformat(msg, 190, input, 3);
	
	replace_all(msg, 190, "!g", "^4");
	replace_all(msg, 190, "!y", "^1");
	replace_all(msg, 190, "!t", "^3");
	
	if(id) players[0] = id;
	else get_players(players, count, "ch"); {
		for(new i = 0; i < count; i++) {
			if(is_user_connected(players[i])) {
				message_begin(MSG_ONE_UNRELIABLE, get_user_msgid("SayText"), _, players[i]);
				write_byte(players[i]);
				write_string(msg);
				message_end();
			}
		}
	} 
}

// Wall Icon 

stock create_icon_origin(id, ent, sprite) // By sontung0
{
	if (!pev_valid(ent)) return;
	
	new Float:fMyOrigin[3]
	entity_get_vector(id, EV_VEC_origin, fMyOrigin)
	
	new target = ent
	new Float:fTargetOrigin[3]
	entity_get_vector(target, EV_VEC_origin, fTargetOrigin)
	fTargetOrigin[2] += 40.0
	
	if (!is_in_viewcone(id, fTargetOrigin)) return;

	new Float:fMiddle[3], Float:fHitPoint[3]
	xs_vec_sub(fTargetOrigin, fMyOrigin, fMiddle)
	trace_line(-1, fMyOrigin, fTargetOrigin, fHitPoint)
							
	new Float:fWallOffset[3], Float:fDistanceToWall
	fDistanceToWall = vector_distance(fMyOrigin, fHitPoint) - 10.0
	normalize(fMiddle, fWallOffset, fDistanceToWall)
	
	new Float:fSpriteOffset[3]
	xs_vec_add(fWallOffset, fMyOrigin, fSpriteOffset)
	new Float:fScale
	fScale = 0.01 * fDistanceToWall
	
	new scale = floatround(fScale)
	scale = max(scale, 1)
	scale = min(scale, WALL_ICON_SIZE)
	scale = max(scale, 1)

	te_sprite(id, fSpriteOffset, sprite, scale, WALL_ICON_LIGHT)
	

}


stock te_sprite(id, Float:origin[3], sprite, scale, brightness) // By sontung0
{	
	message_begin(MSG_ONE, SVC_TEMPENTITY, _, id)
	write_byte(TE_SPRITE)
	write_coord(floatround(origin[0]))
	write_coord(floatround(origin[1]))
	write_coord(floatround(origin[2]))
	write_short(sprite)
	write_byte(scale) 
	write_byte(brightness)
	message_end()
}

stock normalize(Float:fIn[3], Float:fOut[3], Float:fMul) // By sontung0
{
	new Float:fLen = xs_vec_len(fIn)
	xs_vec_copy(fIn, fOut)
	
	fOut[0] /= fLen, fOut[1] /= fLen, fOut[2] /= fLen
	fOut[0] *= fMul, fOut[1] *= fMul, fOut[2] *= fMul
}