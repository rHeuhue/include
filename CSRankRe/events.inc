#if defined _events_included
	#endinput
#endif

#define _events_included

#include <amxmodx>

stock const EVENT_INI_TAGS[] = "[EVENT]";

const EVENT_INVALID_EVENT = 0

enum _:Events {
	EVENT_ID,
	EVENT_NAME[64],
	EVENT_START_DATE[16],
	EVENT_END_DATE[16],

	Array:EVENT_ITEMS
}

new Array:g_events
stock bool: isEventsEnabled = true;

public Events_Init() { g_events = ArrayCreate(Events); Events_Parse(g_events); Events_ReCompileSkins(g_Items, g_events); }

public Events_end() { 
	new data[Events]; 
	for(new i; i < ArraySize(g_events); i++) {
		ArrayGetArray(g_events, i, data);

		if (data[EVENT_ITEMS] ) ArrayDestroy(data[EVENT_ITEMS])
	}

	ArrayDestroy(g_events);	
}

stock Events_Parse(Array:events) {
	if ( !Events_isEnable() ) {
		return 0
	}

	new eventFile[64]; getDirByType(DIR_CONFIG, eventFile, charsmax(eventFile), "Events.ini")

	if ( !file_exists(eventFile) ) {
		Events_setEnable(false)
		return PrintMessage("Event's file not found, check [%s]", eventFile)
	}

	new f = fopen(eventFile, "r");

	new filedata[256], bool:index;
	new data[Events], _event_id[6];

	while(!feof(f)) {
		fgets(f, filedata, charsmax(filedata))
		trim(filedata);

		if (!filedata[0] || filedata[0] == '#') continue;

		if (equali(filedata, EVENT_INI_TAGS, strlen(EVENT_INI_TAGS))) {
			index = !index;

			if ( !index ) {
				// FINISH
				ArrayPushArray(events, data)
				continue;
			}

			replace(filedata, charsmax(filedata), EVENT_INI_TAGS, "");
			trim(filedata);

			data[EVENT_ITEMS] = _:ArrayCreate(1);
			parse(filedata, _event_id, charsmax(_event_id), data[EVENT_NAME], 63, data[EVENT_START_DATE], 15, data[EVENT_END_DATE], 15);

			data[EVENT_ID] = str_to_num(_event_id);
			continue;
		}

		if ( filedata[0] != '^"')	{
			PrintMessage("[Events] Unkown option to parse '%s'", filedata);
			continue;
		}

		parse(filedata, _event_id, charsmax(_event_id))
		new c = convert_skin_id(_event_id, charsmax(_event_id))
		//PrintMessage("-> %s : %d", data[EVENT_NAME], c)
		ArrayPushCell(data[EVENT_ITEMS], c )

	}

	fclose(f)
	return PrintMessage("Load %d event(s)", ArraySize(events))
 }

/**
	Присваивает скинам эвенты
	@param items массив со скинами
	@param events массив с эвентами
 */
stock Events_ReCompileSkins(Array:items, Array:events) {

	if ( !Events_isEnable() ) return;

	new itemsSize = ArraySize(items);
	
	new data[Items];
	for(new i; i < itemsSize; i++) {
		ArrayGetArray(items, i, data);

		// Return Type INT
		data[ITEM_EVENT] = _:Events_getEventsByWeapon(events, data[ITEM_ID])

		ArraySetArray(items, i, data)
	}
}

/**
	Возвращает эвент по ID, EVENT_INVALID_EVENT Если такого нет.
 */
stock Events_GetEventByID( event_id ) {
	new data[Events], size = ArraySize(g_events);
	for(new i; i<size; i++) {
		ArrayGetArray(g_events, i, data);

		if (data[EVENT_ID] == event_id) return i;
	}

	return EVENT_INVALID_EVENT;
 }


/**
	Возвращает текущий эвент или EVENT_INVALID_EVENT, если эвентов нету
 */
public Events_GetCurrentEvent() {
	static event = EVENT_INVALID_EVENT;

	if (Events_isValidEvent(event) || !Events_isEnable()) return event;

	new data[Events], size = ArraySize(g_events);

	new d, m, y; date(y,m,d)
	new cTime = get_systime(0), eTimeStart, eTimeEnd;
	new timeFormat[32];
	for(new i; i<size; i++) {
		ArrayGetArray(g_events, i, data);

		// 26.08 --> 26.08.2020
		if ( containi(data[EVENT_START_DATE], ".") ) 	formatex(timeFormat, charsmax(timeFormat), "%s.%d", data[EVENT_START_DATE], y)
		else											formatex(timeFormat, charsmax(timeFormat), "%s.%d.%d", data[EVENT_START_DATE], m, y)

		eTimeStart = parse_time(timeFormat, "%d.%m.%Y");

		// 26.08 --> 26.08.2020
		if ( containi(data[EVENT_END_DATE], ".") ) 		formatex(timeFormat, charsmax(timeFormat), "%s.%d", data[EVENT_END_DATE], y)
		else											formatex(timeFormat, charsmax(timeFormat), "%s.%d.%d", data[EVENT_END_DATE], m, y)

		eTimeEnd = parse_time(timeFormat, "%d.%m.%Y");

		if ( cTime - eTimeStart > 0 && cTime - eTimeEnd < 0 ) {
			event = data[EVENT_ID];
			break;
		}
	}

	return event;
}

/**
	Получает все эвенты в которых есть указанный item_id (skin_id)
 */
stock Events_getEventsByWeapon( Array:events, item_id ) {
	new eventsSize = ArraySize(events);

	new data[Events];
	for(new i; i< eventsSize; i++) {
		ArrayGetArray(events, i, data);

		if (Events_isItemInEvent( data[EVENT_ITEMS], item_id)) return data[EVENT_ID]
	}

	return EVENT_INVALID_EVENT;
}

stock bool:Events_isItemInEvent( Array: eventItems, item) {
	new size = ArraySize(eventItems);

	if ( !size ) return false;

	for(new j; j<size; j++) {
		if ( item == ArrayGetCell(eventItems, j) ) {
			return true;
		}
	}

	return false;
}

stock Events_getEventInfo( event_id ) {
	new eventData[Events];

	if (event_id <= EVENT_INVALID_EVENT)
		return eventData;
		
	new event = Events_GetEventByID( g_Event )
	ArrayGetArray(g_events, event, eventData)
	return eventData
}

public Events_isEnable() {
	return isEventsEnabled;
}

public Events_setEnable(bool:enable) {
	isEventsEnabled = enable;
}

public Events_isValidEvent(event) {
	return event > EVENT_INVALID_EVENT
}

stock getEventDate(data[Events], start[], startLen, end[], endLen) {
	new d, m, y; date(y,m,d)

	if ( containi(data[EVENT_START_DATE], ".") ) 	formatex(start, startLen, "%s.%d", data[EVENT_START_DATE], y)
	else											formatex(start, startLen, "%s.%d.%d", data[EVENT_START_DATE], m, y)

	if ( containi(data[EVENT_END_DATE], ".") ) 		formatex(end, endLen, "%s.%d", data[EVENT_END_DATE], y)
	else											formatex(end, endLen, "%s.%d.%d", data[EVENT_END_DATE], m, y)

	return 1;
}