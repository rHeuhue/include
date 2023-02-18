colored_print(target, const message[], any:...)
{
	static buffer[512], i, argscount
	argscount = numargs()

	if (!target) {
		static player
		for (player = 1; player <= 32; player++) {
			if (!is_user_connected(player)) continue;
			
			static changed[5], changedcount
			changedcount = 0
			
			for (i = 2; i < argscount; i++) {
				if (getarg(i) == LANG_PLAYER) {
					setarg(i, 0, player)
					changed[changedcount] = i
					changedcount++
				}
			}
			
			vformat(buffer, charsmax(buffer), message, 3)
			format(buffer, charsmax(buffer), "^x04[^1DM^x04]^x01 %s", buffer)
			
			replace_all ( buffer, 187, "!g", "^4" )
			replace_all ( buffer, 187, "!y", "^1" )
			replace_all ( buffer, 187, "!t", "^3" )
			
			message_begin(MSG_ONE_UNRELIABLE, get_user_msgid ( "SayText" ), _, player)
			write_byte(player)
			write_string(buffer)
			message_end()
			
			for (i = 0; i < changedcount; i++) setarg(changed[i], 0, LANG_PLAYER)
		}
	} else {		
		vformat(buffer, charsmax(buffer), message, 3)
		format(buffer, charsmax(buffer), "^x04[^1DM^x04]^x01 %s", buffer)
		
		replace_all ( buffer, 187, "!g", "^4" )
		replace_all ( buffer, 187, "!y", "^1" )
		replace_all ( buffer, 187, "!t", "^3" )
		
		message_begin(MSG_ONE, get_user_msgid ( "SayText" ), _, target)
		write_byte(target)
		write_string(buffer)
		message_end()
	}
}