
new szClassNameItems[] = "war3ft_loot_items";

new szModelItems[64];
new szModelArXpHpItems[64];
//new szSoundLootItems[64];
new szSpriteItems[64];
new idSpriteItems;
new szSpriteNoItems[64];
new idSpriteNoItems;

new Array:arrIntTotalLootEntity;	//������ ���������
new Array:arrIntOriginsLootX;		//������ ��������� ��� ����������� ������� �� X
new Array:arrIntOriginsLootY;		//������ ��������� ��� ����������� ������� �� Y
new Array:arrIntOriginsLootZ;		//������ ��������� ��� ����������� ������� �� Z

new Array:arrIntItemVictimShop1;	//������ �����, ������� ���� � ������ � ������ �����
new Array:arrIntItemVictimShop2;	//������ �����, ������� ���� � ������ �� ������ �����
new Array:arrIntItemVictimShop3;	//������ �����, ������� ���� � ������ � ������� �����

new Array:arrIntDrawSpriteItems;	//������ �������� ������������ �����
new Array:arrIntScaleSpriteItems;	//������ ��������� �������� ������������ �����

new Array:arrIntLootRemove;			//������ �������� ������� �������� ���������

new arrColorItemsRGB[3];	//���� �������� �����
new arrColorNoItemsRGB[3];	//���� ���� ��� ��������� � �������

new msgSyncObj;

#define	TASK_LOOTITEM	90865		// ID ������
#define	TASK_LOOTREMOVE	90866		// ID ������

#define task_set(%1)				set_task(%1)
#define task_remove(%1)				remove_task(%1)


enum enTypeLoot{

	enMoney = 0,
	enHealth = 1,
	enArmor = 2,
	enXP = 3,
	enOther = 4

}


//Test

new Float:fIconDelayLootItems;
new Float:fIconUpdateLootItems;