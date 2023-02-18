new const WAR3FT_CUSTOMIZATION_FILE[] = "war3ft/war3ftmod.ini"

// ������ ����� �������� war3ftmod.ini
enum
{
	SECTION_NONE = 0,
	SECTION_BASE_OPTIONS,
	SECTION_SOUND_RACES,
	SECTION_LOOT_ITEMS,
	SECTION_BLOCK_NUMBER_RACE,
	SECTION_VIP_RACE,
	SECTION_LEVEL_VIP_RACE,
	SECTION_MOTD_RACES,
	SECTION_MULTI_XP_HOUR,
	SECTION_RACE_UNDEAD,
	SECTION_RACE_HUMAN,
	SECTION_RACE_ORC,
	SECTION_RACE_ELF,
	SECTION_RACE_BLOOD,
	SECTION_RACE_SHADOW,
	SECTION_RACE_WARDEN,
	SECTION_RACE_CRYPT,
	SECTION_RACE_FROST_MAGE,
	SECTION_RACE_DEATH_KNIGHT,
	SECTION_RACE_BLACK_MAG,
	SECTION_RACE_ALCHEMIST,
	SECTION_RACE_PRIEST,
	SECTION_RACE_ROGUE,
	SECTION_RACE_DRUID,
	SECTION_RACE_BLOODSEEKER,
	SECTION_RACE_JUGGERNAUT,
	SECTION_RACE_SNIPER,
	SECTION_RACE_DISRUPTOR,
	SECTION_RACE_RAZOR,
	SECTION_RACE_WARLOCK,
	SECTION_RACE_SHADOW_FIEND,
	SECTION_RACE_24,
	SECTION_RACE_25
}

new iOrbDamage;				//ORB_DAMAGE - ����� �� "����� �����������"
new iBaseNecklaceCharges;	//BASE_NECKLACE_CHARGES - ���-�� ������� "Necklace of Immunity""
new iBaseHelmCharges;		//BASE_HELM_CHARGES - ���-�� ������� "Helm of Excellence

new iCount;	//������� ��� ������

//[Base Options] - �������� ��������� ����
new Float:arrPointShowBarRace[2];	//BASE_SHOWBAR_RACE - ���������� ������� ��������� ������ (����,��������)
new iMinUltLevel;					//BASE_MIN_ULT_LEVEL - ����������� ������� ������� � �����

//[Sound Races] - ����� ��� ���
new Array:arrStrSoundRaceData;			//������ ������ ��� ���
new iSoundRaceOnOff;

//[Block Number Race] - ����������� ������� � �����
new iNumRaceOnOff;						//��������/��������� ��� ����������� ������� � �����
new Array:arrIntBlockNumRace;			//������ ����������� ������� � �����

//[Vip Race] - ����������� VIP ��� ����
new Array:arrIntVipRace;			//������ ����������� VIP ��� ����
new Array:arrStrFlagVipRace;		//������ ����������� ����� VIP ��� ����

//[Level Vip Race] - ���������� ������� � ���� �� ������
new Array:arrIntLevelVipRace;		//������ ����������� ������ �� ������� ���������� ������� � ���� ���� ����� �� VIP
new Array:arrStrFlagLevelVipRace;	//������ ����������� ����� VIP ��� ����

//[Motd Path] - ���� � ������ ��� MOTD ������
new iMotdRaceOnOff;				//���������/���������� ����������� MOTD ���� ��� VIP ���	
new Array:arrStrMotdPathRace;	//������ MOTD �����

//[Race: Undead Scourge]
new iExplosionMaxDamage;	//EXPLOSION_MAX_DAMAGE - ����������� ��������� ����������� �������
new iExplosionRange;		//EXPLOSION_RANGE - ��������, ���������� � ������� ��������� �����������
new iExplosionBlastRadius;	//EXPLOSION_BLAST_RADIUS - ������ ��������� ������

//[Race: Human Alliance]
new Float:fBlinkCooldown;	//BLINK_COOLDOWN - ����� ����������� ����� ���� �������� �� ������
new iBashGlowIntensity;		//BASH_GLOW_INTENSITY - �������������� ���������
new Float:fBashHoldTime;	//BASH_HOLD_TIME - ����� �������� ����� (���� Bash)

//[Race: Orcish Horde]
new iChainLightningDamage;			//CHAINLIGHTNING_DAMAGE - ��������� ����������� �������
new iChainLightningLineWidth;		//CHAINLIGHTNING_LINEWIDTH - ������� ��������� ������
new colorOrcLightningRGB[3];		//CHAINLIGHTNING_COLOR_RGB = ���� ��������� ������ (RGB)
new Float:fCriticalStrikeChance;	//CRITICAL_STRIKE_CHANCE - 15% ���� ������������ ����� "Critical Strike"

//[Race: Night Elf]
new Float:fEntangleTime;	//ENTANGLE_TIME - ����� �������� ������������ ������
new colorElfEntangleRGB[3];	//ENTANGLE_COLOR_RGB = ���� ��������� ����� (RGB)


//[Race: Blood Mage]
new iImmolateDamage;			//IMMOLATE_DAMAGE - ��������� ����� ���������� ��� ������������� �����
new iImmolateDotDamage;			//IMMOLATE_DOT_DAMAGE - ����������� ��� ������ ������������ ������� ����
new iImmolateDot;				//IMMOLATE_DOT - ���������� ������������ ������� ����
new iBanishDamage;				//BANISH_DAMAGE - ����������� ��������� ������ "Banish (��������)"
new Float:fBanishHoldTime;		//BANISH_HOLDTIME - ����� �������� ����� (���� Banish)

//[Race: Shadow Hunter]
new Float:fShHexLength;			//SH_HEX_LENGTH - �����, ����� ������� ������������ �������� (���� Hex)
new Float:fShHexSpeed;			//SH_HEX_SPEED - �������� ��������������� ��� ����������� �� ������ (���� Hex)
new iShHealingWaveRange;		//SH_HEALING_WAVE_RANGE - �������� ������ ������� ��������� ��������� �� �������
new iShHealingWaveHealth;		//SH_HEALING_WAVE_HEALTH - ���������� HP ���������� ��� ������� �� ���
new iShBigBadVoodooDuration;	//SH_BIGBADVOODOO_DURATION - ����� �������� ����� ��������
new iShConcoctionDamage;		//SH_CONCOCTION_DAMAGE - ����������� ���������� ��� ������ ����� (���� Unstable Concoction)
new iShConcoctionRadius;		//SH_CONCOCTION_RADIUS - ������ ������ ���������� ��� ������ ����� (���� Unstable Concoction)
new iShSerpentWardDamage;		//SH_SERPENTWARD_DAMAGE - ����������� �������� ����� (���� ������� ����)
new colorSerpentWardRGB_T[3];	//SERPENTWARD_T_COLOR_RGB = ���� ��������� ������ ������� ����� (RGB)
new colorSerpentWardRGB_CT[3];	//SERPENTWARD_CT_COLOR_RGB = ���� ��������� ����� ������� �������(RGB)

//[Race: Warden]
new iVengeanceHealth;			//VENGEANCE_HEALTH - ����������������� �������� ����� ������������� �����
new iShadowStrikeDamage;		//SHADOWSTRIKE_DAMAGE - ���������� ����������� ��������� ������� ������ (���� Shadow Strike)

//[Race: Crypt Lord]
new iLocustSwarmDmgMin;			//LOCUSTSWARM_DMG_MIN - ����������� ���������� ����������� ��������� ������ (��������)
new iLocustSwarmDmgMax;			//LOCUSTSWARM_DMG_MAX - ������������ ���������� ����������� ��������� ������ (��������)
new iCarrionBeetleDamage;		//CARRIONBEETLE_DAMAGE - ����������� ��������� ���������� (���� Carrion Beetles)
new iImpaleType;				//IMPALE_TYPE - ��� ������������� ��� ������������ ����� �����������(Impale) (1 - ��������, 0 - �������� ��� ������� )

//[Race: Frost Mage]
new iDamageBlizzard;			//DAMAGE_BLIZZARD - ����������� ��������� ������� ���� ����� ������� "������� ����"
new iDamageIceBolt;				//DAMAGE_ICE_BOLT -  ����������� ��������� �������������� ���� �� ����������� ������� ������
new iDamageBlizzardRadius;		//DAMAGE_BLIZZARD_RADIUS - ������ ����������� ��������� �������������� ���� �� ����������� ������� ������ "������� ����"

//[Race: Death knight]
new Float:fUnarmorChance		// DEATH_KNIGHT_UNARMOR_CHANCE - 20% ���� ������������ ����� ������������ ����� ( Unbreakable Armor)
new Float:fDeathCoilChance		// DEATH_KNIGHT_DK_CHANCE - 10% ���� ������������ ����� ��� ������ (Death Coil)

new Float:fPercentHP			// DEATH_KNIGHT_PERCENT_HP - ������������ ���������� �� 30%
new Float:fPercentArmor			// DEATH_KNIGHT_PERCENT_ARMOR - ���������� ����� ���������� �� 55%
new Float:fPercentUndamage		// DEATH_KNIGHT_PERCENT_UNDAMAGE - ���������� ���� �� ������ ����� ����������� �� 10%

new Float:fControlUndeadChance	// DEATH_KNIGHT_CONTROLUNDEAD_CHANCE - 50% ���� ������������ ������ ������� ������������ HP
new Float:fControlUndeadHP		// DEATH_KNIGHT_CONTROLUNDEAD_HP - 50% HP ������� ������ ������ ������ ������ ��� ����������
new Float:fControlUndeadExp		// DEATH_KNIGHT_CONTROLUNDEAD_EXP - 100% ���� ������������ ������ �� ������ ������
new iMaxHPVictim;				// DEATH_KNIGHT_MAX_HP_VICTIM - ������������ �������� �������� ������ ����� ������������ ���� "��������� �����"

//[Race: Black mag]
new iMaxNumDisk				//BLACK_MAG_MAX_NUM_DISK - ���������� ������
new iDiskDmg				//BLACK_MAG_DMG_DISK - ����������� ��������� ������
new iBlackStrikeDmg			//BLACK_MAG_BLACKSTRIKE_DAMAGE - ����������� ��������� ������ Black Strike (������ ����)

//[Race: Alchemist]
new iAlPoisonDamage;		//AL_POISON_DAMAGE		- ��������� ���� �� ����� "������"
new iAlPoisonNumber;		//AL_POISON_NUMBER		- ������� ��� ������� ���� ���� "������"
new Float:fAlPoisonTime;	//AL_POISON_TIME		- �������� ����� ���������� ����� ������ "������" (� ��������)
new Float:fAlFrostSpeed;	//AL_FROST_SPEED		- �������� ������ ������������ ������ "������� �������"
new Float:fAlFrostHoldTime; //AL_FROST_HOLD_TIME	- ����� ������� �������� ����� ��������� � ����� "������� �������" (� ��������)


//������ ����������
new iInvisParachute;		//BASE_INVIS_PARACHUTE - ����������� ����������� ��������