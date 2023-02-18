// ******************************************************************
// ����: ������ (Race: Warlock) Constants
// ******************************************************************

//����� ������ (Race: Warlock )
#define clWarlock::		clWarlock_


#define clWarlock_setSkillsInit					_Warlock_ID_1
#define clWarlock_skillFatalBonds				_Warlock_ID_2
#define clWarlock_skillShadowWord				_Warlock_ID_3
#define clWarlock_fActiveSkillShadowWord		_Warlock_ID_4
#define clWarlock_skillFlamingFists				_Warlock_ID_5
#define clWarlock_fStartFlamingFists			_Warlock_ID_6
#define clWarlock_ultPermanentImmolation		_Warlock_ID_7
#define clWarlock_fCreatePermImmolation			_Warlock_ID_8
#define clWarlock_fStartPermImmolation			_Warlock_ID_9


#define WARLOCK_FLAME_DURATION arrParams[0]
#define WARLOCK_PERM_IMMOLATION arrParamsPI[0]

#define PERM_IMMOL_WARLOCK_CLASSNAME "w_perm_immolation"

#define	clWarlock_tID_FATAL_BONDS			8963248
#define clWarlock_taskActiveFatalBonds		_taskActiveFatalBonds

#define	clWarlock_tID_FLAMING_FIRST			8963249
#define clWarlock_taskFlamingFists		_taskFlamingFists

#define	clWarlock_tID_PERM_IMMOLATION		8963250
#define clWarlock_taskPermImmolation		_taskPermImmolation



new Float:ptOriginWarlock[33][3];
new Float:fAnglesWarlock[33][3];

enum enTypeDmg
{
	eArmor,
	eDmg	
};

new iFatalBondsDmg;					//WARLOCK_FATAL_BONDS_DMG - ����� �� ����� "��������� �����"
new iFatalBondsRadius;				//WARLOCK_FATAL_BONDS_RADIUS - ������ ��������� ������ "��������� �����"
new iShadowWordNum;					//WARLOCK_SHADOW_WORD_NUM - ���-�� ������������ ����� "��������� ��������" �� �����
new iShadowWordTime;				//WARLOCK_SHADOW_WORD_TIME - ����� ������� ������ ��������� "��������� ��������"
new iShadowWordRadius;				//WARLOCK_SHADOW_WORD_RADIUS - ������ ��������� ��� ������� ������ "��������� ��������"
new iShadowWordDmg;					//WARLOCK_SHADOW_WORD_DMG - ����� �� ����� "��������� ��������"
new iShadowWordHp;					//WARLOCK_SHADOW_WORD_DMG - ����� �� ����� "��������� ��������"
new iFflamingFistsNum;				//WARLOCK_FLAMING_FISTS_NUM - ���-�� ������������ ����� "�������� �����"
new iFlamingFistsDmg;				//WARLOCK_FLAMING_FISTS_DMG - ����� �� ����� "�������� �����"
new iPermImmolationDmg;				//WARLOCK_PERM_IMMOLATION_DMG - ����� �� ����� ������ "����������������"
new Float:fPermImmolationRadius;	//WARLOCK_PERM_IMMOLATION_RADIUS - ������ ��������� �� ����� ������ "����������������"
