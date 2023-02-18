// ******************************************************************
// ����: ��������� (Race: Rogue) Constants
// ******************************************************************


//����� ��������� (Race: Rogue )
#define clRogue::		clRogue_

//�������
#define clRogue_setRogueSkillsInit		_Rogue_ID_1
#define clRogue_skillSinisterStrike		_Rogue_ID_2
#define clRogue_addSkillCharge			_Rogue_ID_3
#define clRogue_skillVanish				_Rogue_ID_4
#define clRogue_skillCripplingPoison	_Rogue_ID_5
#define clRogue_ultShurikenToss			_Rogue_ID_6
#define clRogue_setChargeNum			_Rogue_ID_7

//������
#define	clRogue_tID_VANISH		952147		// Vanish - ������������
#define	clRogue_tID_CP_SPEED	521748		// 

#define clRogue_taskResetVanish			_taskResetVanish
#define clRogue_taskResetCP_Speed		_taskResetCP_Speed


#define BALL_CLASSNAME "shuriken"
#define BEAM_CLASSNAME "shuriken_beam"


new Float:fShurikenDmg;				//ROGUE_SHURIKEN_DMG - ���� ��� ������ ��������
new Float:fShurikenRadiusExp;		//ROGUE_SHURIKEN_RADIUS_EXP - ������ ����� ��� ������ ��������
new Float:fShurikenBeamRadius;		//ROGUE_SHURIKEN_BEAM_RADIUS - ������ ��������� ����� �� ��������
new Float:fShurikenBeamDmg;			//ROGUE_SHURIKEN_BEAM_DMG - ���� �� ���� ��������

//Max ���-�� �������:
new	iRogueChargeMax_1;	//ROGUE_CHARGE_MAX_1 - (���� 1 ������ - Sinister Strike - �������� ����)
new	iRogueChargeMax_2;	//ROGUE_CHARGE_MAX_2 - (���� 2 ������ - Vanish - ������������)
new	iRogueChargeMax_3;	//ROGUE_CHARGE_MAX_3 - (���� 3 ������ - Crippling Poison - ��������� ��)
//Min ���-�� ������� �������:
new	iRogueChargeMin_1;	//ROGUE_CHARGE_MIN_1 - (���� 1 ������ - Sinister Strike - �������� ����)
new	iRogueChargeMin_2;	//ROGUE_CHARGE_MIN_2 - (���� 2 ������ - Vanish - ������������)
new	iRogueChargeMin_3;	//ROGUE_CHARGE_MIN_3 - (���� 3 ������ - Crippling Poison - ��������� ��)
//������ ������� � ��������, ������ ������� �������� ���� �������� �����:
new	iRogueCount_1;		//ROGUE_COUNT_1 - (���� 1 ������ - Sinister Strike - �������� ����)
new	iRogueCount_2;		//ROGUE_COUNT_2 - (���� 2 ������ - Vanish - ������������)
new	iRogueCount_3;		//ROGUE_COUNT_3 - (���� 3 ������ - Crippling Poison - ��������� ��)

//���� ��� ����� 1 ������  (Sinister Strike - �������� ����)
new iSStrike_Secondary;	//ROGUE_SSTRIKE_SECONDARY - ���� � ���������
new iSStrike_Primary;	//ROGUE_SSTRIKE_PRIMARY - ���� � ��������
new iSStrike_Knife;		//ROGUE_SSTRIKE_KNIFE - ���� � ����
new iSStrike_Grenade;	//ROGUE_SSTRIKE_GRENADE - ���� � �������