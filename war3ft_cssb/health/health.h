// ******************************************************************
// ���������� ������� ��������� ��������
// ******************************************************************

//����� ����� ������� ��� �������
#define clHP:		clHP_

//�������
#define clHP_getRaceMinHealth			_HP_ID_1
#define clHP_getRaceMaxHealth			_HP_ID_2
#define clHP_getUserHealth				_HP_ID_3
#define clHP_setUserHealth				_HP_ID_4
#define clHP_cfLoadHealthFile			_HP_ID_5
#define clHP_setCurRespawnRaceHealth	_HP_ID_6
#define clHP_getArmorNum				_HP_ID_8



new const WAR3FT_HEALTH_FILE[] = "war3ft/health/health_races.ini"

// ������ ����� �������� health_races.ini
enum
{
	SECTION_NONE = 0,
	SECTION_HEALTH_OPTIONS
	
}

new Array:arrIntMinHealth;		//������ ������������ ��������
new Array:arrIntMaxHealth;		//������ ������������� ��������

new arrHealthRace[2];


new iHealthItemRace;			//HEALTH_ITEM - ���������� �������� ������������ ��� ������������� �������� "�������� ��������"