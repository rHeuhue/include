
/*
#if defined _cl_buy_included
  #endinput
#endif
#define _cl_buy_included

#pragma reqlib cl_buy
*/

#define CSW_DEFUSER		33
#define CSW_NVGS		34
#define CSW_SHIELD		35
#define CSW_PRIMAMMO	36
#define CSW_SECAMMO		37

forward mfClientBuyWeapons(id, item);

enum _:iMenus {
	Menu_Buy = 4,
	Menu_BuyPistol = 5,
	Menu_BuyRifle = 6,
	Menu_BuyMachineGun = 7,
	Menu_BuyShotgun = 8,
	Menu_BuySubMachineGun = 9,
	Menu_BuyItem = 10
}

const TE_WEAPONS = 1<<CSW_ELITE | 1<<CSW_GALIL | 1<<CSW_AK47 | 1<<CSW_SG552 | 1<<CSW_G3SG1 | 1<<CSW_MAC10
const CT_WEAPONS = 1<<CSW_FIVESEVEN | 1<<CSW_FAMAS | 1<<CSW_M4A1 | 1<<CSW_AUG | 1<<CSW_SG550 | 1<<CSW_TMP | 1<<CSW_SHIELD

#define m_iMenu 205
#define cs_get_user_menu(%0)	get_pdata_int(%0, m_iMenu)

new const g_iMenuItemsTe[][] = {
	{0, 0, 0, 0, 0, 0, CSW_PRIMAMMO, CSW_SECAMMO, 0}, /* Menu_Buy */
	{0, CSW_GLOCK18, CSW_USP, CSW_P228, CSW_DEAGLE, CSW_ELITE, 0, 0, 0}, /* Menu_BuyPistol */
	{0, CSW_GALIL, CSW_AK47, CSW_SCOUT, CSW_SG552, CSW_AWP, CSW_G3SG1, 0, 0}, /* Menu_BuyRifle */
	{0, CSW_M249, 0, 0, 0, 0, 0, 0, 0}, /* Menu_BuyMachineGun */
	{0, CSW_M3, CSW_XM1014, 0, 0, 0, 0, 0, 0}, /* Menu_BuyShotgun */
	{0, CSW_MAC10, CSW_MP5NAVY, CSW_UMP45, CSW_P90, 0, 0, 0, 0}, /* Menu_BuySubMachineGun */
	{0, CSW_VEST, CSW_VESTHELM, CSW_FLASHBANG, CSW_HEGRENADE, CSW_SMOKEGRENADE, CSW_NVGS, 0, 0} /* Menu_BuyItem */
}

new const g_iMenuItemsCt[][] = {
	{0, 0, 0, 0, 0, 0, CSW_PRIMAMMO, CSW_SECAMMO, 0}, /* Menu_Buy */
	{0, CSW_GLOCK18, CSW_USP, CSW_P228, CSW_DEAGLE, CSW_FIVESEVEN, 0, 0, 0}, /* Menu_BuyPistol */
	{0, CSW_FAMAS, CSW_SCOUT, CSW_M4A1, CSW_AUG, CSW_SG550, CSW_AWP, 0, 0}, /* Menu_BuyRifle */
	{0, CSW_M249, 0, 0, 0, 0, 0, 0, 0}, /* Menu_BuyMachineGun */
	{0, CSW_M3, CSW_XM1014, 0, 0, 0, 0, 0, 0}, /* Menu_BuyShotgun */
	{0, CSW_TMP, CSW_MP5NAVY, CSW_UMP45, CSW_P90, 0, 0, 0, 0}, /* Menu_BuySubMachineGun */
	{0, CSW_VEST, CSW_VESTHELM, CSW_FLASHBANG, CSW_HEGRENADE, CSW_SMOKEGRENADE, CSW_NVGS, CSW_DEFUSER, CSW_SHIELD} /* Menu_BuyItem */
}

new mfBuyForward, g_iReturn;