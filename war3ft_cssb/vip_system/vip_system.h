// ******************************************************************
// Глобальные функции настройки вип
// ******************************************************************

//Класс общих функций для игроков
#define clVIP:		clVIP_

//Функции
#define clVIP_vfLoadVipSystemFile		_VIP_ID_1
#define clVIP_isVipActiveIndex			_VIP_ID_2
#define clVIP_fStripWpnSecondary		_VIP_ID_3
#define clVIP_fStripWpnPrimary			_VIP_ID_4
#define clVIP_fMenuDestroyVip			_VIP_ID_5
#define clVIP_fTeleportRespawn			_VIP_ID_6
#define clVIP_fLimitItemVipOneRound		_VIP_ID_8
#define clVIP_isCountRoundVip			_VIP_ID_9
#define clVIP_isActiveAllWpnRound		_VIP_ID_10
#define clVIP_isMap						_VIP_ID_11
#define clVIP_fInitItemsAccessVip		_VIP_ID_12
#define clVIP_fResetItemsAccessVip		_VIP_ID_13
#define clVIP_isAccesItemVip			_VIP_ID_14
#define clVIP_fShowMessageDhud			_VIP_ID_15
#define clVIP_fShowMessageChat			_VIP_ID_16
#define clVIP_fTagVip					_VIP_ID_17



new const WAR3FT_VIP_SYSTEM_FILE[] = "war3ft/vip_system/vip_system.ini"

new Array:arrStrVipName;
new Array:arrStrVipFlag;
//new Array:arrStrVipDay;
new Array:arrStrVipKeys;


new arrIsItemVipOneRound[33][21];				// Ограничение взятия предметов для VIP (только на один раунд)
new bool:arrIsItemVip[33][MAX_SHOPMENU_ITEMS];	// Есть ли предмет у вип игрока

// Секции файла настроек vip_system.ini
enum
{
	SECTION_NONE = 0,
	SECTION_OPTIONS_VIP,
	SECTION_USERS_VIP
	
}

new iHpArmorMinRound;				//HP_ARMOR_MIN_ROUND
new iGreanadeAllRound;				//GREANADE_ALL_ROUND
new iHegrenadeRound;				//HEGRENADE_ROUND
new iFlashbangRound;				//FLASHBANG_ROUND
new iSmokegrenadeRound;				//SMOKEGRENADE_ROUND
new iRespawnRound;					//RESPAWN_ROUND
new Float:fSpeedValueVip;			//SPEED_VALUE
new Float:fGravityValueVip;			//GRAVITY_VALUE
new iHpRound;						//HP_ROUND
new iHpValue;						//HP_VALUE
new iArmorRound;					//ARMOR_ROUND
new iArmorValue;					//ARMOR_VALUE
new iMoneyRound;					//MONEY_ROUND
new iMoneyValue;					//MONEY_VALUE
new iAwpRound;						//AWP_ROUND
new iAk47Round;						//AK47_ROUND
new iDeagleRound;					//DEAGLE_ROUND
new iAugRound;						//AUG_ROUND
new iSg552Round;					//SG552_ROUND
new iM4a1Round;						//M4A1_ROUND
new iM249Round;						//M249_ROUND
new iM3Round;						//M3_ROUND
new iXm1014Round;					//XM1014_ROUND
new iAllWeaponsRound;				//ALL_WEAPONS_ROUND
new szAllWeaponsBlockMap[255];		//ALL_WEAPONS_BLOCK_MAP
new iDhudMesssageVip;				//DHUD_MESSSAGE
new iChatMesssageVip;				//CHAT_MESSSAGE

enum enTypeItemVip
{
	enHP_ARMOR_MIN = 0,
	enGREANADE_ALL = 1,
	enHEGRENADE = 2,
	enFLASHBANG = 3,
	enSMOKEGRENADE = 4,
	enRESPAWN = 5,
	enSPEED = 6,
	enGRAVITY = 7,
	enHP = 8,
	enARMOR = 9,
	enMONEY = 10,
	enAWP = 11,
	enAK47 = 12,
	enDEAGLE = 13,
	enAUG = 14,
	enSG552 = 15,
	enM4A1 = 16,
	enM249 = 17,
	enM3 = 18,
	enXM1014 = 19
};

/*
new szArrName[33][255];
new szArrFlag[33][255];
new szArrDay[33][255];
*/

