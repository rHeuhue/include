// - Death Coil ------------------------------------------- //
#define DEATHCOIL_DAMAGE	get_pcvar_num( CVAR_wc3_deathcoil_damage )//���������� ����������� ��������� ��� ������ ( ������ wc3_deathcoil_damage*(0.7) )
#define DEATHCOIL_VELOCITY	800.0    // (  float) velocity of death coil towards target
#define DEATHCOIL_DURATION	3.0    // (  float) life of deathcoil before removal

//���� ��� �������� �� ���4
new DEATHCOIL_SHELL_RGB[3]	=	{255,0,0};
new DEATHCOIL_TRAIL_RGB[3]	=	{225,0,43};

//���� ��� HP
new DEATHCOIL_SHELL_HP_RGB[3]	=	{160,255,0};
new DEATHCOIL_TRAIL_HP_RGB[3]	=	{96,224,0};

//���� ��� �����
new DEATHCOIL_SHELL_ARMOR_RGB[3]	=	{30,144,255};
new DEATHCOIL_TRAIL_ARMOR_RGB[3]	=	{0,191,255};



enum {
eDcAtack,
eDcHP,
eDcArmor
};

#define GLOW_R                         0    // Glow reference values
#define GLOW_G                         1
#define GLOW_B                         2
