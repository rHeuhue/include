// For Icon events
#define ICON_HIDE 0 
#define ICON_SHOW 1 
#define ICON_FLASH 2 

new g_UltimateIcons[MAX_RACES][32] = 
					{
						"dmg_rad",				// Undead
						"item_longjump",		// Human Alliance
						"dmg_shock",			// Orcish Horde
						"item_healthkit",		// Night Elf
						"dmg_heat",				// Blood Mage
						"suit_full",			// Shadow Hunter
						"cross",				// Warden
						"dmg_gas",				// Crypt Lord
						"dmg_chem",				// Chameleon
						"dmg_cold",				// Frost Mage
						"cross",				// Death knight
						"dmg_gas",				// Black magician
						"dmg_bio",				// Alchemist
						"dmg_heat",				// Priest
						"dmg_shock",			// Rogue
						"dmg_bio",				// Druid
						"dmg_bio",				// ���������
						"dmg_shock",			// ����������
						"dmg_shock",			// �������
						"dmg_shock",			// �����������
						"dmg_bio",				// ���� �����
						"dmg_heat",				// ���� ������
						"cross",				// ���� ��������
						"dmg_bio",				// ���� 24
						"dmg_bio"				// ���� 25
					};

new g_ULT_iLastIconShown[33];				// Stores what the last icon shown was for each user (race #)

