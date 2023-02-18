#if defined _globals_defines_included
	#endinput
#endif

#define _globals_defines_included 

#if !defined MAX_CLIENTS
	#define MAX_CLIENTS 32
#endif

#define csr_is_valid_player(%0) (1<=%0<=32 && is_user_connected(%0))

#define get_weapon_skin(%0) pev(%0, pev_iuser4)
#define set_weapon_skin(%0,%1) set_pev(%0, pev_iuser4, %1)

#define get_weapon_owner(%0,%1,%2) pev(%0, pev_noise3, %1, %2)
#define set_weapon_owner(%0,%1) set_pev(%0, pev_noise3, %1)

