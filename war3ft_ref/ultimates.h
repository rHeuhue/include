// For Icon events
#define ICON_HIDE 0 
#define ICON_SHOW 1 
#define ICON_FLASH 2 



new g_UltimateIcons[MAX_RACES-1][32] = 
					{
						"dmg_rad",				// Undead
						"item_longjump",		// Human 
						"dmg_shock",			// Orc
						"item_healthkit",		// Night Elf
						"dmg_heat",				// Blood Elf
						"suit_full",			// Troll
						"cross",				// Specter
						"dmg_gas",				// Nerubian
						"dmg_cold",				// Crystal 
						"dmg_drown"				// Druid
					};

new g_ULT_iLastIconShown[33];				// Stores what the last icon shown was for each user (race #)

