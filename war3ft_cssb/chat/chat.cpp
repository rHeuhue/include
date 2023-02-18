

stock fTagWar3ft()
{
	new szTag[64];
	formatex(szTag, sizeof(szTag) - 1, "%L%L%L ",LANG_PLAYER,"WC3_BRACKET_LEFT",LANG_PLAYER,"WC3_MODCLIENT",LANG_PLAYER,"WC3_BRACKET_RIGHT");
	return szTag;
}

stock cssbChatColor(const idUser, const input[], any:...)
{
    new count = 1, arrPlayers[32];
	new szMsgText[256];
    vformat(szMsgText, charsmax(szMsgText), input, 3);
    
    replace_all(szMsgText, charsmax(szMsgText), "!g", "^4");
    replace_all(szMsgText, charsmax(szMsgText), "!y", "^1");
    replace_all(szMsgText, charsmax(szMsgText), "!t", "^3");
    
    if (idUser) 
		arrPlayers[0] = idUser; 
	else 
		get_players(arrPlayers, count, "ch");
    {
        for (new i = 0; i < count; i++)
        {
            if (is_user_connected(arrPlayers[i]))
            {
                message_begin(MSG_ONE_UNRELIABLE, get_user_msgid("SayText"), _, arrPlayers[i]);
                write_byte(arrPlayers[i]);
                write_string(szMsgText);
                message_end();
            }
        }
    }
} 