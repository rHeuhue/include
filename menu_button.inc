stock UTIL_MenuButton(iNumber = -1) {

	new szButton[16];
	if(iNumber == -1) formatex(szButton, charsmax(szButton), "\r[\y#\r]");
	else formatex(szButton, charsmax(szButton), "\r[\y%d\r]", iNumber);
	
	return szButton;

}