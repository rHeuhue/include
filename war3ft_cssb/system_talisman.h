//const KEYSMENU = MENU_KEY_1|MENU_KEY_2|MENU_KEY_3|MENU_KEY_4|MENU_KEY_5|MENU_KEY_6|MENU_KEY_7|MENU_KEY_8|MENU_KEY_9|MENU_KEY_0;

//��������� ���������� �������� � ����
#define TALISMAN_ITEM_NECKLACE_NUM	get_pcvar_num(CVAR_wc3_t_necklace_num)  // ���������� ������� ���������� �� ����� (��������) ��� ���������
new arrTalismanNecklaceNum[33];												// ������ ������� ��� ���������� ������� ���������� �� ����� (��������)

#define TALISMAN_ITEM_HELM_NUM	get_pcvar_num(CVAR_wc3_t_helm_num)  // ���������� ������� (����) ��� ���������
new arrTalismanHelmNum[33];											// ������ ������� ��� ���������� �������  (����)


#define	MAX_TALISMANS 25	//������������ ���������� ����������

new arrTalismanNum[33];					//������� ����� ���������� � ������
new arrTalismanChange[33];				//����� ������� ���������
new arrTalismanActive[33];				//����� �������� ������� � ������
new arrListTalisman[33][MAX_TALISMANS];	//������ ���� ���������� ��������� � ������ (9 ����������)
new bool:arrPlayerInitTalisman[33];		//�������� ���� ���������� ����� ����� ����� �� ������ � ��������� ���� ������ ��� (�������� ���� ���)
new stSyncHudCreate;

//�������
#define	MAX_SPAWNS_TALISMAN	60	//������������ ���������� ����� ��������� �� ����� ���������
#define	MAX_MODE_TALISMAN	get_pcvar_num( CVAR_wc3_mode_talisman )	//������ ������ ������� ����������
#define	TIME_SPAWN_TALISMAN			get_pcvar_float( CVAR_wc3_time_spawn_talisman )		//����� ����� ����� ����� ���������� ��������
//#define	TIME_TASK_SPAWN_TALISMAN	1.0												//������ �������
#define RING_MAX	5 //������������ ����� ����� �������������� HP

//������
#define	TASK_SPAWN_TALISMAN	985645

new iTotalSpawnsTalisman = 0;	//������� ����� ��������� ��������� � ����

new entTalisman;	//�������� ���������
new bool:bIsPickUpTalisman;

//���������� ���������
new arrSpawnOrigin[MAX_SPAWNS_TALISMAN][3];

new Float:fTimeSpawnTalismanGlobal;	//���������� ������� ������� ����� ������� �������� ��������			

new szClassNameTalisman[] = "war3ft_talisman";					//��� ������ ���������

#define	TALISMAN_ITEM_NONE						-1
#define	TALISMAN_ITEM_ANKH						0	// Ankh of Reincarnation
#define	TALISMAN_ITEM_BOOTS						1	// Boots of Speed
#define	TALISMAN_ITEM_CLAWS						2	// Claws of Attack
#define	TALISMAN_ITEM_CLOAK						3	// Cloak of Shadows
#define	TALISMAN_ITEM_MASK						4	// Mask of Death
#define	TALISMAN_ITEM_NECKLACE					5	// Necklace of Immunity
#define	TALISMAN_ITEM_FROST						6	// Orb of Frost
#define	TALISMAN_ITEM_HEALTH					7	// Periapt of Health
#define	TALISMAN_ITEM_PROTECTANT				10	// Mole Protectant
#define	TALISMAN_ITEM_HELM						11	// Helm of Excellence
#define	TALISMAN_ITEM_AMULET					12	// Amulet of the Cat
#define	TALISMAN_ITEM_SOCK						13	// Sock of the Feather
#define	TALISMAN_ITEM_GLOVES					14	// Flaming Gloves of Warmth
#define	TALISMAN_ITEM_RING						15	// Ring of Regeneration + 1
#define	TALISMAN_ITEM_CHAMELEON					16	// Chameleon
#define	TALISMAN_ITEM_INTELLECT					18	// Intellect
#define	TALISMAN_ITEM_GRENADE_PROTECTION		19	// Grenade Protection
#define	TALISMAN_ITEM_MIRROR_SHIELD				20	// Mirror Shield
#define	TALISMAN_ITEM_ESP						21	// ESP
#define	TALISMAN_ITEM_FROST_ARMOR				22	// Frost Armor
#define	TALISMAN_ITEM_ULTIMATE_TIMER_DIVIDER	25	// Ultimate Timer Divider
#define	TALISMAN_ITEM_DEVOURER_LIGHT			27	//���������� ����
#define	TALISMAN_ITEM_ICE_BLOCK					28	//������� �����
#define	TALISMAN_ITEM_THIEF						29	//���������� �����
#define	TALISMAN_ITEM_MIRROR_ULTIMATE			30	//���������� ����� ������


//������ ����������
new const LIST_TALISMANS[MAX_TALISMANS] = 
{
	TALISMAN_ITEM_ANKH,						// Ankh of Reincarnation
	TALISMAN_ITEM_BOOTS,					// Boots of Speed
	TALISMAN_ITEM_CLAWS,					// Claws of Attack
	TALISMAN_ITEM_CLOAK,					// Cloak of Shadows
	TALISMAN_ITEM_MASK,						// Mask of Death
	TALISMAN_ITEM_NECKLACE,					// Necklace of Immunity
	TALISMAN_ITEM_FROST,					// Orb of Frost
	TALISMAN_ITEM_HEALTH,					// Periapt of Health
	TALISMAN_ITEM_PROTECTANT,				// Mole Protectant
	TALISMAN_ITEM_HELM,						// Helm of Excellence
	TALISMAN_ITEM_AMULET,					// Amulet of the Cat
	TALISMAN_ITEM_SOCK,						// Sock of the Feather
	TALISMAN_ITEM_GLOVES,					// Flaming Gloves of Warmth
	TALISMAN_ITEM_RING,						// Ring of Regeneration + 1
	TALISMAN_ITEM_CHAMELEON,				// Chameleon
	TALISMAN_ITEM_INTELLECT,				// Intellect
	TALISMAN_ITEM_GRENADE_PROTECTION,		// Grenade Protection
	TALISMAN_ITEM_MIRROR_SHIELD,			// Mirror Shield
	TALISMAN_ITEM_ESP,						// ESP
	TALISMAN_ITEM_FROST_ARMOR,				// Frost Armor
	TALISMAN_ITEM_ULTIMATE_TIMER_DIVIDER,	// Ultimate Timer Divider
	TALISMAN_ITEM_DEVOURER_LIGHT,			//���������� ����
	TALISMAN_ITEM_ICE_BLOCK,				//������� �����
	TALISMAN_ITEM_THIEF,					//���������� �����
	TALISMAN_ITEM_MIRROR_ULTIMATE			//���������� ����� ������
	
};


//������� ��� ������ MYSQL � SQLITE
forward DB_GetAllTalisman( idUser );
forward MYSQLX_GetAllTalisman(idUser);
forward SQLITE_GetAllTalisman(idUser);









