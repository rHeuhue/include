// Считывание расы игрока
native cssb_get_user_race(idUser);

// Считывание названия расы игрока
native cssb_get_user_race_name(idUser,szShortRaceName[]);

// Считывание времени до появления талика
native cssbGetTimeSpawnTalisman(idUser);

//Прокачка опыта
native cssbSetPlayerLevel(idUser);

//Выдача талисмана
native cssbSetPlayerTalisman(idUser,iIdTalisman);

//ID рассы
native cssbGetIdRace(idUser);

//Возвращает уровень
native cssbGetLvLRace(idUser);

// Добавление опыта к текущему
native cssbGiveXP(idUser,iXP);

native cssbItemGetSlot(idUser);
native cssbIsItemUserSlot(idUser,iSlot);
native cssbItemGiveItem(idUser,iItem);
native cssbItemCost( idUser, iItem );


