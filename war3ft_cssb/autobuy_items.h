/*
*	���� ������� ���������
*/

//����� ���������� �������
#define	MAX_NUM_AUTO_MENUS 2

//��������� �������
new const MENU_TITLES_AUTOBUY_ITEMS[MAX_NUM_AUTO_MENUS][] = 
{
	"MENU_ID_BASE_AUTOBUY_ITEMS",
	"MENU_ID_DELETE_AUTOBUY_ITEMS"
};
//������� ������ ������� � ����
new const MENU_CALLBACK_AUTOBUY_ITEMS_ALL[MAX_NUM_AUTO_MENUS][] = 
{
	"_Callback_MENU_BaseABI",
	"_Callback_SUB_MENU_DeleteABI"
};

new arriShopAutoItems[33][MAX_PLAYER_ITEMS];			// ������ ���� ���������� ���������

new bool:bAutoBuyOnOff[33];	// (���������\���������� ����-�������)
