// ******************************************************************
// ����: �������� (Race: Shadow Fiend) Constants
// ******************************************************************

//����� �������� (Race: ShadowFiend )
#define clShadowFiend::		clShadowFiend_


#define clShadowFiend_setSkillsInit					_ShadowFiend_ID_1
#define clShadowFiend_ultNecromastery				_ShadowFiend_ID_2
#define clShadowFiend_fStartNecromastery			_ShadowFiend_ID_3
#define clShadowFiend_fCreateNecromastery			_ShadowFiend_ID_4
#define clShadowFiend_fUpNecromastery				_ShadowFiend_ID_5
#define clShadowFiend_skillPresenceDL				_ShadowFiend_ID_6
#define clShadowFiend_skillRequiemSouls				_ShadowFiend_ID_7
#define clShadowFiend_fActiveRequiemSouls			_ShadowFiend_ID_8
#define clShadowFiend_fCreateRequiemSouls			_ShadowFiend_ID_9
#define clShadowFiend_skillCryHeart					_ShadowFiend_ID_10
#define clShadowFiend_fCreateCryHeart				_ShadowFiend_ID_11


#define NECROMASTERY_SHADOW_FIEND_CLASSNAME "sf_necromastery"

#define	clShadowFiend_tID_NECROMASTERY		8963251
#define clShadowFiend_taskNecromastery		_taskNecromastery


#define	clShadowFiend_tID_REQUIEM_SOULS		8963253
#define clShadowFiend_taskRequiemSouls		_taskRequiemSouls


#define	clShadowFiend_tID_PRESENCE_DL		8963252
#define clShadowFiend_taskActivePresDL		_taskActivePresDL

#define	clShadowFiend_tID_CRY_HEART			8963253
#define clShadowFiend_taskActiveCryHeart	_taskActiveCryHeart

enum enTypeEntShadowFiend
{
	eNecromastery,
	eRequiemSouls,
	eCryHeart
};

new iPresenceRadius;				//SHADOW_FIEND_PRESENCE_RADIUS - ������ ��������� ������ "����������� ������� �����"
new iPresenceArmor;					//SHADOW_FIEND_PRESENCE_ARMOR - ���-�� �����, ������� �������� � ������
new iRequiemSoulsNum;				//SHADOW_FIEND_REQUIEM_SOULS_NUM - ���-�� ������������ ����� "������� ���" �� �����
new iRequiemSoulsTime;				//SHADOW_FIEND_REQUIEM_SOULS_TIME - ����� ������� ������ ��������� "������� ���"
new iRequiemSoulsDmg;				//SHADOW_FIEND_REQUIEM_SOULS_DMG - ����� �� ����� "������� ���"
new iNecromasteryNum;				//SHADOW_FIEND_NECROMASTERY_NUM - ���-�� ���������� ��� �� ��� ����� ������� "��������� ���"
new iNecromasteryHP;				//SHADOW_FIEND_NECROMASTERY_HP - ���-�� �������� ���������� �� ����� ����
new iCryHeartDmg;					//SHADOW_FIEND_CRY_HEART_DMG - ����� �� ����� "���� ����"
