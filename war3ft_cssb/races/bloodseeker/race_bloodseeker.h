// ******************************************************************
// ����: ��������� (Race: Bloodseeker) Constants
// ******************************************************************

//����� ��������� (Race: Bloodseeker )
#define clBloodseeker::		clBloodseeker_


#define clBloodseeker_setSkillsInit					_Bloodseeker_ID_1
#define clBloodseeker_addSkillCharge				_Bloodseeker_ID_2
#define clBloodseeker_skillBloodRage				_Bloodseeker_ID_3
#define clBloodseeker_fShowMenuAbility				_Bloodseeker_ID_4
#define clBloodseeker_Callback_Menu					_Callback_Menu_Bloodseeker
#define clBloodseeker_skillBloodBath				_Bloodseeker_ID_5
#define clBloodseeker_skillBloodRite				_Bloodseeker_ID_6
#define clBloodseeker_skillVendetta					_Bloodseeker_ID_7
#define clBloodseeker_ultBloodyMadness				_Bloodseeker_ID_8




#define	clBloodseeker_tID_BLOODRAGE		8963245
#define clBloodseeker_taskResetBloodRage	_taskResetBloodRage

#define	clBloodseeker_tID_BLOODRITE_A		9632578
#define clBloodseeker_taskResetBloodRiteA	_taskResetBloodRiteA

#define	clBloodseeker_tID_BLOODRITE_V		78542001
#define clBloodseeker_taskResetBloodRiteV	_taskResetBloodRiteV


//Max ���-�� �������:
new	iBloodseekerChargeMax_1;	//BLOODSEEKER_CHARGE_MAX_1
new	iBloodseekerChargeMax_2;	//BLOODSEEKER_CHARGE_MAX_2
new	iBloodseekerChargeMax_3;	//BLOODSEEKER_CHARGE_MAX_3
//Min ���-�� ������� �������:
new	iBloodseekerChargeMin_1;	//BLOODSEEKER_CHARGE_MIN_1
new	iBloodseekerChargeMin_2;	//BLOODSEEKER_CHARGE_MIN_2
new	iBloodseekerChargeMin_3;	//BLOODSEEKER_CHARGE_MIN_3
//������ ������� � ��������, ������ ������� �������� ���� �������� �����:
new	iBloodseekerCount_1;		//BLOODSEEKER_COUNT_1
new	iBloodseekerCount_2;		//BLOODSEEKER_COUNT_2
new	iBloodseekerCount_3;		//BLOODSEEKER_COUNT_3


new iAmountVendettaDMG[33];

new iBloodRiteDmg;					//BLOODSEEKER_BLOOD_RITE_DMG - ����� ��������� ������ "�������� �����"
new Float:fBloodyMadnessDmg;		//BLOODSEEKER_BLOODY_MADNESS_DMG - ����� ��������� ������ "�������� �������"
new Float:fBloodyMadnessHp;			//BLOODSEEKER_BLOODY_MADNESS_HP - �������� ����� "�������� �������" (1 ��������)
new iNumVendettaDMG;				//BLOODSEEKER_VENDETTA_DMG_NUM - ����� ������ ����������� �����. ���������� ��� ������������ ����� "������� �����"
new iVendettaDmg;					//BLOODSEEKER_VENDETTA_DMG - ����� �� ����� "������� �����"
new iBloodRageDmg;					//BLOODSEEKER_BLOOD_RAGE_DMG - ����� ��������� ������ "������ �����"
new Float:fBloodRageSpeedFactor;	//BLOODSEEKER_BLOOD_RAGE_SPEED_FACTOR - ��������� �������� ��� ���������� "������ �����"
new Float:fBloodBathHpFactor;		//BLOODSEEKER_BLOOD_BATH_HP_FACTOR - ��������� �������� ��� ���������� "�������� ����"