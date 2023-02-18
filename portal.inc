new mapPortals[MAX_PORTALS]
new mapTargets[MAX_TARGETS]
new mapAllrounds[MAX_ALLROUNDS]
new mapBlackholes[MAX_BLACKHOLES]

new numPortals
new numTargets
new numAllrounds
new numBlackholes

new g_filename[120];

/*
//DEBUG mode switch
#define DEBUG
*/

public create_ent_portal( Float:pOrigin[3]){
	new portal= create_entity("info_target")
	entity_set_string(portal,EV_SZ_classname,"amx_portal")
	
	entity_set_model(portal, portal_model)
	entity_set_int(portal, EV_INT_flags, FL_ALWAYSTHINK)
	set_rendering(portal, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255)
	
	new Float:MinBox[3] = {-16.0, -16.0, 0.0}
	new Float:MaxBox[3] = {16.0, 16.0, 16.0}
	entity_set_vector(portal, EV_VEC_mins, MinBox)
	entity_set_vector(portal, EV_VEC_maxs, MaxBox)
	
	entity_set_int(portal, EV_INT_solid, 1)
	entity_set_origin(portal,pOrigin);
	mapPortals[numPortals] = portal
	++numPortals
}
public create_ent_target( Float:pOrigin[3]){
	new target=create_entity("info_target")
	entity_set_string(target,EV_SZ_classname,"amx_ptarget")
	
	entity_set_model(target, target_model)
	entity_set_int(target, EV_INT_flags, FL_ALWAYSTHINK)
	set_rendering(target, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255)
	
	entity_set_origin(target,pOrigin);
	mapTargets[numTargets] = target
	++numTargets
}
public create_ent_allround( Float:pOrigin[3]){
	new allround = create_entity("info_target")
	entity_set_string(allround,EV_SZ_classname,"amx_aportal")
	
	entity_set_model(allround, allround_model)
	entity_set_int(allround, EV_INT_flags, FL_ALWAYSTHINK)
	set_rendering(allround, kRenderFxNone, 0, 0, 0, kRenderTransAdd, 255)
	
	new Float:MinBox[3] = {-16.0, -16.0, 0.0}
	new Float:MaxBox[3] = {16.0, 16.0, 16.0}
	entity_set_vector(allround, EV_VEC_mins, MinBox)
	entity_set_vector(allround, EV_VEC_maxs, MaxBox)
	
	entity_set_int(allround, EV_INT_solid, 1)
	
	entity_set_origin(allround,pOrigin)
	
	mapAllrounds[numAllrounds] = allround
	++numAllrounds
}
public create_ent_blackhole(Float:vNewOrigin[3],Float:vEntAngles[3]){
	new blackhole = create_entity("info_target")
	
	entity_set_string(blackhole, EV_SZ_classname, "amx_blackhole")
	
	entity_set_model(blackhole, blackhole_model)
	entity_set_size(blackhole, Float:{-40.0,-30.0,-40.0}, Float:{40.0,30.0,40.0})
	
	entity_set_int(blackhole, EV_INT_solid, 1)
	entity_set_int(blackhole, EV_INT_flags, FL_ALWAYSTHINK)
	
	entity_set_origin(blackhole, vNewOrigin)
	entity_set_vector(blackhole, EV_VEC_angles, vEntAngles)
	
	mapBlackholes[numBlackholes] = blackhole
	++numBlackholes
	return blackhole;
}
saveToFile(file,i,Float:origin[3]){
	new line[30];
	formatex(line,30,"[%d]^n",i);
	fputs(file,line);
	for(new i=0;i<3;i++){
		formatex(line,30,"%.0f^n",origin[i]);
		fputs(file,line);
	}
}
saveBHToFile(file,i,Float:origin[3],Float:angles[3]){
	new line[30];
	formatex(line,30,"[%d]^n",i);
	fputs(file,line);
	for(new i=0;i<3;i++){
		formatex(line,30,"%.0f^n",origin[i]);
		fputs(file,line);
	}
	for(new i=0;i<3;i++){
		formatex(line,30,"%.0f^n",angles[i]);
		fputs(file,line);
	}
}
public savePortals(id,level,cid){
	if (!cmd_access(id,level,cid,1)) return PLUGIN_HANDLED
	new filename[120];
	new Float:origin[3];
	formatex(filename,119,"%s/portals/portals/%s",cfgFolder,mapName);
	new file=fopen(filename,"w");
	for(new i=0; i<numPortals;i++){
		entity_get_vector(mapPortals[i],EV_VEC_origin, origin);
		saveToFile(file,i,origin);
	}
	fclose(file);
	formatex(filename,119,"%s/portals/targets/%s",cfgFolder,mapName);
	file=fopen(filename,"w");
	for(new i=0; i<numTargets;i++){
		entity_get_vector(mapTargets[i],EV_VEC_origin, origin);
		saveToFile(file,i,origin);
	}
	fclose(file);
	formatex(filename,119,"%s/portals/allrounds/%s",cfgFolder,mapName);
	file=fopen(filename,"w");
	for(new i=0; i<numAllrounds;i++){
		entity_get_vector(mapAllrounds[i],EV_VEC_origin, origin);
		saveToFile(file,i,origin);
	}
	fclose(file);
	formatex(filename,119,"%s/portals/blackholes/%s",cfgFolder,mapName);
	file=fopen(filename,"w");
	for(new i=0; i<numBlackholes;i++){
		new Float:angles[3];
		entity_get_vector(mapBlackholes[i], EV_VEC_origin, origin);
		entity_get_vector(mapBlackholes[i], EV_VEC_angles, angles);
		saveBHToFile(file,i,origin,angles);
	}
	fclose(file);
	client_print(id, print_center,"Saved");
	return PLUGIN_HANDLED;
}
bool:loadFromFile(i,Float:origin[3]){
	new line[10];
	new l;
	read_file(g_filename,i++, line,9,l);
	if(line[0]=='[' && line[2]==']'){
		for(new j=i;j<i+3;j++){
			read_file(g_filename,j, line,9,l);
			origin[j-i]=str_to_float(line);
		}
		return true;
	}
	return false;
	
}
bool:loadBHFromFile(i,Float:origin[3],Float:angle[3]){
	new line[10];
	new l;
	read_file(g_filename,i++, line,9,l);
	if(line[0]=='[' && line[2]==']'){
		for(new j=i;j<i+3;j++){
			read_file(g_filename,j, line,9,l);
			origin[j-i]=str_to_float(line);
		}
		i+=3;
		for(new j=i;j<i+3;j++){
			read_file(g_filename,j, line,9,l);
			angle[j-i]=str_to_float(line);
		}
		return true;
	}
	return false;
	
}
public loadPortals(){
	new i=0;
	new Float:origin[3];
	formatex(g_filename,119,"%s/portals/portals/%s",cfgFolder,mapName);
	if(file_exists(g_filename)){	
		while(loadFromFile(i,origin)){
			create_ent_portal(origin);
#if defined DEBUG
				log_amx("Portal: %.0f %.0f %.0f",origin[0],origin[1],origin[2]);
#endif
			i+=4;
		}
	}
	i=0
	formatex(g_filename,119,"%s/portals/targets/%s",cfgFolder,mapName);
	if(file_exists(g_filename)){	
		while(loadFromFile(i,origin)){
			create_ent_target(origin);
#if defined DEBUG
				log_amx("Target: %.0f %.0f %.0f",origin[0],origin[1],origin[2]);
#endif
			i+=4;
		}
	}
	i=0
	formatex(g_filename,119,"%s/portals/allrounds/%s",cfgFolder,mapName);
	if(file_exists(g_filename)){	
		while(loadFromFile(i,origin)){
			create_ent_allround(origin);
#if defined DEBUG
				log_amx("Allround: %.0f %.0f %.0f",origin[0],origin[1],origin[2]);
#endif
			i+=4;
		}
	}
	i=0;
	formatex(g_filename,119,"%s/portals/blackholes/%s",cfgFolder,mapName);
	if(file_exists(g_filename)){	
		new Float:angle[3];
		while(loadBHFromFile(i,origin,angle)){
			create_ent_blackhole(origin,angle);
#if defined DEBUG
				log_amx("Blackhole: %.0f %.0f %.0f",origin[0],origin[1],origin[2]);
				log_amx("Blackhole angle: %.0f %.0f %.0f",angle[0],angle[1],angle[2]);
#endif
			i+=7;
		}
	}
}
