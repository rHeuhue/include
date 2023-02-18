#if defined _operataions_included
    #endinput
#endif

#define _operataions_included

#include <amxmodx>


new bool:Operation_blockPlayer[33];

/**
    Проверяет все ли хорошо
 */
stock bool:Operation_Check(id = -1, load = true, weaponid = -1, team = -1) {

    if ( id >= 0 && !is_user_connected(id)) {
        return false;
    }

    if (load && !g_player_data[id][PD_LOAD]) {
        return false;
    }

    if (weaponid >= 0 && weaponid > WEAPON_SIZE - 1) {
        return false;
    }

    if (team >= 0 && (team != RE_TEAM_T && team != RE_TEAM_CT)) {
        return false;
    }

    return true;
}

/**
    Добавляет скин в инвентарь игрока
 */
public bool:Operation_AddPlayerItem( id, item) {
    if ( !Operation_Check(id) ) {
        return false;
    }

    Sql_InsertItemToPlayer(id, item)
    return true;
}

/**
    Убирает скин из инвентаря игрока
 */
public bool:Operation_RemovePlayerItem( id, item) {
    if ( !Operation_Check(id) ) {
        return false;
    }

    Sql_RemoveItemFromPlayer(id, item)
    return true;
}

/**
    Получаем все скины игрока и передаем их в функцию
 */
public bool:Operation_GetPlayerItems( id,  function[]) {
    if ( !Operation_Check(id) ) {
        return false;
    }

    Sql_GetPlayerItems(id, function);
    return true;
}

public QueryLoadPlayerItems(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
    if(FailState)
    {
        return SQL_Error(Query, Error, Errcode, FailState);
    }
    
    new id = Data[OLI_ID];
    new player = Data[OLI_PLAYER];
    new Array:items = ArrayCreate(1);

    new item;
    while (SQL_MoreResults(Query)) {
        // COde
        item = SQL_ReadResult(Query, SQL_FieldNameToNum(Query, "skin"));

        if ( search_array(item) < 0 ) {
            SQL_NextRow(Query);
            continue
        }

        ArrayPushCell(items, item);
        SQL_NextRow(Query)
    }

    new func = get_func_id( Data[OLI_FUNCTION], .pluginId = -1);

    callfunc_begin_i(func, .plugin = -1);
    callfunc_push_int( id );
    callfunc_push_int(_:items);
    callfunc_push_int( player );
    callfunc_end();

    return SQL_FreeHandle(Query);
}

/**
    Устанавливаем скин игроку
 */
public bool:Operation_SetPlayerWeaponSkin(id, weaponid, playerTeam, item) {
    if ( !Operation_Check(id, true, weaponid, playerTeam) ) {
        return false;
    }

    new currentItem = get_player_weapon_skin(id, playerTeam, weaponid);

    // Если нам передали пустой предмет то обнуляем
    if (item == 0) {
        Operation_ResetPlayerWeaponSkin(id, weaponid, playerTeam);
        return true;
    }

    if (isItemsEquals(currentItem, item)) return true;

    Operation_blockPlayer[id] = true;
    if ( currentItem == 0)	Sql_InsertWeaponSkin(id, weaponid, playerTeam, item);
    else {
        Sql_UpdateWeaponSkin(id, weaponid, playerTeam, currentItem, item);
    }						
    
    set_player_weapon_skin(id, playerTeam, weaponid, item);
    
    new data[Items], index = search_array(item);
    if (index < 0 || !is_user_connected(id)) return false;

    ArrayGetArray(g_Items, index, data);
    ReplaceItem(id, weaponid, index, data[ITEM_MODEL_V], data[ITEM_MODEL_P])
    return true
}

/**
    Обнуляем скин у игрока
 */
public bool:Operation_ResetPlayerWeaponSkin(id, weaponid, playerTeam) {
    // if ( !Operation_Check(id, true, weaponid, playerTeam) ) {
    //     return false;
    // }

    new resetItem = 0;
    set_player_weapon_skin(id, playerTeam, weaponid, resetItem);
    Sql_RemoveWeaponSkin(id, playerTeam, weaponid)
    return true;
}

/**
    Обнуляем все скины у игрока
 */
public bool:Operation_ResetPlayerWeapon(id, bool:sql) {
    for(new i; i< WEAPON_SIZE + 1; i++) {
        for(new j; j< ReTeams; j++)
            g_player_weapons[id][j][i] = _:0;
    }

    if ( !sql ) return true;

    if ( !is_user_connected(id) || !g_player_data[id][PD_LOAD]) {
        return false;
    }

    SQL_ResetWeapons(id);
    return true;
}