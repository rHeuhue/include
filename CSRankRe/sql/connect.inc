#if defined _sql_connect_included
    #endinput
#endif

#define _sql_connect_included

#include <amxmodx>
#include <sqlx>

new const sqlConfig[] = "CSRankRe.cfg"

public Handle:sqlInit( 
	const sqlHost[],
	const sqlUser[],
	const sqlPass[],
	const sqlDb[]) { 

	if ( strlen(sqlHost) < 5 ) {
		// В этом случае, мы должны взять данные из sql.cfg
		//set_stored_var("initsql_host_len", "0");

		new Handle:Turple = SQL_MakeStdTuple(0)
		// Проверяем, есть ли соединение
		sqlConn(Turple, true, "sql.cfg")
		// Возвращаем стандартный дескриптор
		
		return Turple;
	}

	new Handle:Turple = SQL_MakeDbTuple(sqlHost,sqlUser,sqlPass,sqlDb);

	if ( !sqlConn(Turple, false, sqlConfig) ) {
		// Не смогли подключиться через divebans_host
		Turple = SQL_MakeStdTuple(0)
		// Проверяем, есть ли соединение
		sqlConn(Turple, true, "sql.cfg")
		// Возвращаем стандартный дескриптор
		return Turple;
	}

	return Turple;
}

stock bool:sqlConn( Handle:Turple = Empty_Handle, bool:offPlugin = false, const addToEnd[] = "sql") {
	static err,error[128]
	new Handle:connect = SQL_Connect(Turple,err,error,127)

	if(connect == Empty_Handle) {
		new message[128];
		formatex(message, charsmax(message), "[SQL Connect] Can't connect by %s",addToEnd)

		PrintMessage("%s", message)
		PrintMessage("[SQL Connect] Error %d '%s'", err, error)
		if ( offPlugin ) set_fail_state(message);
		return false;
	}

	SQL_FreeHandle(connect)
	return true;
}
