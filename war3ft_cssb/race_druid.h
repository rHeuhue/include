// ******************************************************************
// ����: ����� (Race: Druid) Constants
// ******************************************************************

//����� ����� (Race: Druid )
#define clDruid::		clDruid_


#define clDruid_setDruidSkillsInit		_Druid_ID_1
#define clDruid_addSkillCharge			_Druid_ID_2
#define clDruid_skillWildMush_Entangle  _Druid_ID_3
#define clDruid_skillWildMush_Healing	_Druid_ID_4
#define clDruid_skillWildMush_Explode	_Druid_ID_5
#define clDruid_fCreateWildMushroom		_Druid_ID_6
#define clDruid_ultAstralStorm			_Druid_ID_7
#define clDruid_efBeamCylinder			_Druid_ID_8
#define clDruid_setChargeNum			_Druid_ID_9
#define clDruid_skillMangle				_Druid_ID_10
#define clDruid_IsWildMushroomSetup		_Druid_ID_11
#define clDruid_IsWildMushroomResp		_Druid_ID_12
#define clDruid_fCreateWildMushroom_2	_Druid_ID_13
#define clDruid_addWMStrikeExplode		_Druid_ID_14
#define clDruid_addWMStrikeEntangle		_Druid_ID_15
#define clDruid_addWMStrikeHealing		_Druid_ID_16





enum enWildMush
{
	enWildMush_Entangle,
	enWildMush_Healing,
	enWildMush_Explode,
	enWildMush_Blood
};


//Max ���-�� �������:
new	iDruidChargeMax_1;	//DRUID_CHARGE_MAX_1
new	iDruidChargeMax_2;	//DRUID_CHARGE_MAX_2
new	iDruidChargeMax_3;	//DRUID_CHARGE_MAX_3
//Min ���-�� ������� �������:
new	iDruidChargeMin_1;	//DRUID_CHARGE_MIN_1
new	iDruidChargeMin_2;	//DRUID_CHARGE_MIN_2
new	iDruidChargeMin_3;	//DRUID_CHARGE_MIN_3
//������ ������� � ��������, ������ ������� �������� ���� �������� �����:
new	iDruidCount_1;		//DRUID_COUNT_1
new	iDruidCount_2;		//DRUID_COUNT_2
new	iDruidCount_3;		//DRUID_COUNT_3

new Float:fRadiusSpawnWild;		//DRUID_RADIUS_SPAWN_WILD - ������ �� ������� ��������� ���������� ���� �� ����� ��������
new Float:fWildHpEnt;			//DRUID_WILD_HEALTH_ENT  - �������� ����� ����: �����������
new Float:fWildHpHeal;			//DRUID_WILD_HEALTH_HEAL - �������� ����� ����: ���������
new Float:fWildHpExp;			//DRUID_WILD_HEALTH_EXP - �������� ����� ����: ����
new Float:fWildExplodeDmg;		//DRUID_WILD_EXPLODE_DMG - ����� (���� 3 - ����� ����: ����)
new Float:fWildHealingHp;		//DRUID_WILD_HEALING_HP - �������� (���� 2 - ����� ����: ���������)
new Float:fWildRadiusDmg;		//DRUID_WILD_RADIUS_DMG - ������ � ������� ������ ���������� ����� ����� c������� ����
new Float:fAStormDmg;			//DRUID_ASTRAL_STORM_DMG - ����� �� ����� ������ ���������� �����
new Float:fAStormRadiusDmg;		//DRUID_ASTRAL_STORM_RADIUS_DMG - ������ ��������� ����� ������� ���������� �����
new Float:fAstormSmallDmg;		//DRUID_ASTORM_SMALL_DMG - ����� �� ������ ����� ������ ���������� �����
new Float:fAstormSmallRadDmg;	//DRUID_ASTORM_SMALL_RADIUS_DMG - ������ ��������� �� ������ ����� ������� ���������� �����
new Float:fShanceMangle;		//DRUID_SHANCEMANGLE - ���� ������������ ����� ������
new iShanceMangleDmg;			//DRUID_SHANCEMANGLEDMG - ����� �� ����� ������

