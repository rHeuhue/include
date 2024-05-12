/* Sublime AMXX Editor v3.0.0-beta */

#if defined _crx_advmute_included
	#endinput
#endif
#define _crx_advmute_included


#pragma reqlib <crx_advmute>
#if !defined AMXMODX_NOAUTOLOAD
	#pragma loadlib <crx_advmute>
#endif

/**
 * Returns if receiver of a message is muted by sender
 *
 *
 * @return true/false whether user muted other user
 *
 */
native crx_is_user_muted(iReceiver, iSender)