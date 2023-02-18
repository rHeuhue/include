
new const WAR3FT_CUSTOM_FILE_XP[] = "war3ft/options/xp.ini"

// ������ ����� �������� xp.ini
enum
{
	SECTION_NONE = 0,
	SECTION_XP_AWARDED,
	SECTION_XP_SAVE,
	SECTION_XP_KILL_SAVE
};

//����������
//���� �� ������ �������������� ����� (XP awarded when the user starts to defuse the bomb)
new iDefusingBomb;
//���� �� �������������� ����� (XP awarded when the user defuses the bomb)
new iDefusedBomb;
//���� �� ������ ��������� ����� (XP awarded when the user starts planting the bomb)
new iPlantingBomb;
//���� �� ��������� ����� (XP awarded when the user plants the bomb)
new iPlantBomb;
//���� �� ���� � ������ (XP awarded when the user spawns with the bomb)
new iSpawnBomb;
//���� �� ������ ����� (XP awarded when the user picks up the bomb)
new iBombPickup;
//���� �� ������������� � ��������� ( XP awarded when the user touches a hostage)
new iTouchHostage;
//���� �� �������� ��������� (XP awarded when the user rescues the hostage)
new iRescueHostage;
//���������� ���� �� �������� ��������� (XP lost when killing a hostage)
new iKillHostage;
//���� �� ���� ��� VIP (XP awarded for spawning as the VIP)
new iSpawnVip;
//���� �� ����� ��� VIP ( XP awarded for escaping as the VIP)
new iEscapeVip;
//���� �� �������� � ������ (XP awarded for getting a headshot)
new iKillHeadshot;
//���� �� �������� ��������������� ���������� (XP awarded for killing the hostage saver)
new iKillHostageSaver;
//���� �� �������� ������ (XP awarded for killing the defuser)
new iKillDefuser;
//���� �� �������� ������ ( XP awarded for killing the planter)
new iKillPlanter;
//���� �� �������� �������� ����� (XP awarded for killing the bomb carrier)
new iKillBombCarrier;
//���� �� �������� VIP (XP awarded for killing the VIP)
new iKillVip;
//���� �� ������ � ������ (XP awarded for winning the round)
new iWinRound;

//�������
//*******************************************************
//  ��������� �����
//*******************************************************
new Array:arrXpSave;
new Array:arrXpKillSave;