new const WAR3FT_CUSTOMIZATION_FILE[] = "war3ft/war3ftmod.ini"

// Секции файла настроек war3ftmod.ini
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

new iOrbDamage;				//ORB_DAMAGE - Дамаг от "Сфера уничтожения"
new iBaseNecklaceCharges;	//BASE_NECKLACE_CHARGES - Кол-во зарядов "Necklace of Immunity""
new iBaseHelmCharges;		//BASE_HELM_CHARGES - Кол-во зарядов "Helm of Excellence

new iCount;	//Счетчик для циклов

//[Base Options] - Основные настройки мода
new Float:arrPointShowBarRace[2];	//BASE_SHOWBAR_RACE - Координаты главной статусной строки (расы,предметы)
new iMinUltLevel;					//BASE_MIN_ULT_LEVEL - Минимальный уровень доступа к ульте

//[Sound Races] - Звуки для рас
new Array:arrStrSoundRaceData;			//Массив звуков для рас
new iSoundRaceOnOff;

//[Block Number Race] - Ограничение доступа к расам
new iNumRaceOnOff;						//Включить/выключить все ограничения доступа к расам
new Array:arrIntBlockNumRace;			//Массив ограничения доступа к расам

//[Vip Race] - Определение VIP для расы
new Array:arrIntVipRace;			//Массив определения VIP для расы
new Array:arrStrFlagVipRace;		//Массив определения флага VIP для расы

//[Level Vip Race] - Блокировка доступа к расе по уровню
new Array:arrIntLevelVipRace;		//Массив определения уровня до момента блокировки доступа к расе если игрок не VIP
new Array:arrStrFlagLevelVipRace;	//Массив определения флага VIP для расы

//[Motd Path] - Путь к файлам для MOTD окошек
new iMotdRaceOnOff;				//Включение/отключение отображения MOTD окон для VIP рас	
new Array:arrStrMotdPathRace;	//Массив MOTD путей

//[Race: Undead Scourge]
new iExplosionMaxDamage;	//EXPLOSION_MAX_DAMAGE - Максимально наносимые повреждения взрывом
new iExplosionRange;		//EXPLOSION_RANGE - Диапозон, оказываясь в котором наносятся повреждения
new iExplosionBlastRadius;	//EXPLOSION_BLAST_RADIUS - Радиус отрисовки взрыва

//[Race: Human Alliance]
new Float:fBlinkCooldown;	//BLINK_COOLDOWN - Время перезапуска ульты если телепорт не удался
new iBashGlowIntensity;		//BASH_GLOW_INTENSITY - Интенсивоность подсветки
new Float:fBashHoldTime;	//BASH_HOLD_TIME - Время задержки удара (скил Bash)

//[Race: Orcish Horde]
new iChainLightningDamage;			//CHAINLIGHTNING_DAMAGE - Наносимые повреждения молнией
new iChainLightningLineWidth;		//CHAINLIGHTNING_LINEWIDTH - Толщина отрисовки молнии
new colorOrcLightningRGB[3];		//CHAINLIGHTNING_COLOR_RGB = Цвет отрисовки молнии (RGB)
new Float:fCriticalStrikeChance;	//CRITICAL_STRIKE_CHANCE - 15% шанс срабатывания скила "Critical Strike"

//[Race: Night Elf]
new Float:fEntangleTime;	//ENTANGLE_TIME - Время действия запутывающик корней
new colorElfEntangleRGB[3];	//ENTANGLE_COLOR_RGB = Цвет отрисовки сетки (RGB)


//[Race: Blood Mage]
new iImmolateDamage;			//IMMOLATE_DAMAGE - Начальный ущерб нанесенный при использовании ульты
new iImmolateDotDamage;			//IMMOLATE_DOT_DAMAGE - Повреждения при каждом срабатывании вспышки огня
new iImmolateDot;				//IMMOLATE_DOT - Количество срабатываний вспышек огня
new iBanishDamage;				//BANISH_DAMAGE - Повреждения наносимые скилом "Banish (Изгнание)"
new Float:fBanishHoldTime;		//BANISH_HOLDTIME - Время задержки удара (скил Banish)

//[Race: Shadow Hunter]
new Float:fShHexLength;			//SH_HEX_LENGTH - Время, через которое сбрасывается действие (скил Hex)
new Float:fShHexSpeed;			//SH_HEX_SPEED - Скорость устанавливаемая при воздействии на жертву (скил Hex)
new iShHealingWaveRange;		//SH_HEALING_WAVE_RANGE - Диапозон охвата лечения Охотником товарищей по команде
new iShHealingWaveHealth;		//SH_HEALING_WAVE_HEALTH - Количество HP получаемое при лечении за раз
new iShBigBadVoodooDuration;	//SH_BIGBADVOODOO_DURATION - Время действия ульты Охотника
new iShConcoctionDamage;		//SH_CONCOCTION_DAMAGE - Повреждение окружающих при вызове волны (скил Unstable Concoction)
new iShConcoctionRadius;		//SH_CONCOCTION_RADIUS - Радиус охвата окружающих при вызове волны (скил Unstable Concoction)
new iShSerpentWardDamage;		//SH_SERPENTWARD_DAMAGE - Повреждения наносимы змеей (скил Змеиная суть)
new colorSerpentWardRGB_T[3];	//SERPENTWARD_T_COLOR_RGB = Цвет отрисовки молнии команды теров (RGB)
new colorSerpentWardRGB_CT[3];	//SERPENTWARD_CT_COLOR_RGB = Цвет отрисовки сетки команды контров(RGB)

//[Race: Warden]
new iVengeanceHealth;			//VENGEANCE_HEALTH - Восстанавливаемое здоровье после использования ульты
new iShadowStrikeDamage;		//SHADOWSTRIKE_DAMAGE - Количество повреждений наносимые скрытым ударом (скил Shadow Strike)

//[Race: Crypt Lord]
new iLocustSwarmDmgMin;			//LOCUSTSWARM_DMG_MIN - Минимальное количество повреждений наносимое ультой (саранчей)
new iLocustSwarmDmgMax;			//LOCUSTSWARM_DMG_MAX - Маскимальное количество повреждений наносимое ультой (саранчей)
new iCarrionBeetleDamage;		//CARRIONBEETLE_DAMAGE - Повреждения наносимые трупоедами (скил Carrion Beetles)
new iImpaleType;				//IMPALE_TYPE - Тип подбрасывания при срабатывании скила Запутывание(Impale) (1 - стандарт, 0 - примерно как распрыг )

//[Race: Frost Mage]
new iDamageBlizzard;			//DAMAGE_BLIZZARD - Повреждения наносимые главной цели супер навыком "Снежная буря"
new iDamageIceBolt;				//DAMAGE_ICE_BOLT -  Повреждения наносимые второстепенной цели от рассыпанных ледяных болтов
new iDamageBlizzardRadius;		//DAMAGE_BLIZZARD_RADIUS - Радиус повреждений наносимый второстепенной цели от рассыпанных ледяных болтов "Снежная буря"

//[Race: Death knight]
new Float:fUnarmorChance		// DEATH_KNIGHT_UNARMOR_CHANCE - 20% шанс срабатывания скила несокрушимая броня ( Unbreakable Armor)
new Float:fDeathCoilChance		// DEATH_KNIGHT_DK_CHANCE - 10% шанс срабатывания скила лик смерти (Death Coil)

new Float:fPercentHP			// DEATH_KNIGHT_PERCENT_HP - Выносливость повышается на 30%
new Float:fPercentArmor			// DEATH_KNIGHT_PERCENT_ARMOR - Показатель брони повышается на 55%
new Float:fPercentUndamage		// DEATH_KNIGHT_PERCENT_UNDAMAGE - Получаемый урон от скилов врага уменьшается на 10%

new Float:fControlUndeadChance	// DEATH_KNIGHT_CONTROLUNDEAD_CHANCE - 50% шанс срабатывания отдачи Нежитью поглощаемого HP
new Float:fControlUndeadHP		// DEATH_KNIGHT_CONTROLUNDEAD_HP - 50% HP которое Нежить отдает Рыцарю смерти при поглощении
new Float:fControlUndeadExp		// DEATH_KNIGHT_CONTROLUNDEAD_EXP - 100% шанс срабатывания защиты от взрыва Нежити
new iMaxHPVictim;				// DEATH_KNIGHT_MAX_HP_VICTIM - Максимальное значение здоровья жертвы чтобы подействовал скил "Вскипание крови"

//[Race: Black mag]
new iMaxNumDisk				//BLACK_MAG_MAX_NUM_DISK - Количество дисков
new iDiskDmg				//BLACK_MAG_DMG_DISK - Повреждения наносимые диском
new iBlackStrikeDmg			//BLACK_MAG_BLACKSTRIKE_DAMAGE - Повреждения наносимые скилом Black Strike (Темный Удар)

//[Race: Alchemist]
new iAlPoisonDamage;		//AL_POISON_DAMAGE		- Наносимый урон от скила "Отрава"
new iAlPoisonNumber;		//AL_POISON_NUMBER		- Сколько раз нанесет урон скил "Отрава"
new Float:fAlPoisonTime;	//AL_POISON_TIME		- Интервал между нанесением урона скилом "Отрава" (в секундах)
new Float:fAlFrostSpeed;	//AL_FROST_SPEED		- Скорость игрока замороженого скилом "Ледяное дыхание"
new Float:fAlFrostHoldTime; //AL_FROST_HOLD_TIME	- Через сколько удалится эфект заморозки у скила "Ледяное дыхание" (в секундах)


//Другие переменные
new iInvisParachute;		//BASE_INVIS_PARACHUTE - Выставление невидимости парашюту