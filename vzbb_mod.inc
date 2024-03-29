/*
---------------------------------------------------------
   #  #  #    #===    ###    ##    #
  #    ##     #===   #      #  #    #
   #   #      #===    ###    ##    #
---------------------------------------------------------
vzbb_mod.inc
Library by <VeCo>

<VeCo>'s Zombie BaseBuilder Mod 4.0

If you modify the code, please DO NOT change the author!
---------------------------------------------------------
Contacts:
e-mail: veco.kn@gmail.com
skype: veco_kn
---------------------------------------------------------
Changes log:
 -> v 1.0 = First release!
 -> v 1.1 = Fixed double user_infect_pre. The second is
	    changed to user_infect_post.
 -> v 3.0 = Defines changed to enums.
	    Added itemteam parameter in register_shop_item
	    function and TEAM_* enum.
	    Added set_user_zombie_class native.
	    Added user_uninfect native.
	    Added grab/release block forwards.
 -> v 3.4 = Added is_user_frozen_cool native.
	    Added user_freeze_cool_* forwards.
	    Added user_freeze_cool and user_unfreeze_cool
	    natives.
 -> v 3.5 = Added get_block_fun_type and set_block_fun_type
	    natives and BLOCKS_* enum.
	    Added get_deal_discount and is_deal_offer natives.
 -> v 3.8 = Added set_user_was_zombie native.
	    Added access parameters in register_zombie_class
	    and register_shop_item natives.
	    Fixed a typo.
	    Added FORWARD_CONTINUE define for the forward
	    block ability.
	    Added set_user_can_build native.
	    Added hide_barrierent and reset_barrierent natives.
	    Added update_user_hud_data forward and set_hud_cache_*
	    natives for it.
	    Added force_user_hud_data and force_weapon_menu natives.
 -> v 3.9 = Added user_uninfect_pre and user_uninfect_post forwards.
	    Added battle_phase_begin_admin forward.
	    Added fun_block_touch_pre and fun_block_touch_post forwards.
 -> v 4.0 = Added ability to block shop_item_selected forward. (and changed
	    the way Item Buy System works)
	    Added maxbuys parameter in register_shop_item and NO_MAX_BUYS
	    define for it.
	    Added restore_user_rendering native.
---------------------------------------------------------
Don't forget to visit http://www.amxmodxbg.org :)
---------------------------------------------------------
*/

#if defined _vzbb_mod_included
	#endinput
#endif

#define _vzbb_mod_included

#if AMXX_VERSION_NUM >= 175
	#pragma reqlib vzbb_mod
	#if !defined AMXMODX_NOAUTOLOAD
		#pragma loadlib vzbb_mod
	#endif
#else
	#pragma library vzbb_mod
#endif

/*=======================================================================
                           -= Define-� =- 
========================================================================*/

#define FORWARD_CONTINUE 777 // return ... (������� forward)

#define NO_MAX_BUYS 0 // ����������� ���� ���� �������� �� ����

/*=======================================================================
                           -= Enum-� =- 
========================================================================*/

// ���� ���� �� �� ������ �����?
enum
{
	USE_BATTLE = 0,
	USE_BUILD,
	USE_BOTH
}

// ��� ���� �� ������ �����?
enum
{
	TEAM_ZOMBIES = 1,
	TEAM_HUMANS,
	TEAM_BOTH
}

// ��� �� ����� �����?
enum
{
	BLOCK_PULL = 1,
	BLOCK_PUSH
}

// ����� ����� �� ���� ���� ����?
enum
{
	MODE_NORMAL = 0,
	MODE_INFECTION
}

// ����� ������� � ��������?
enum
{
	NADE_HE = 1,
	NADE_SMOKE,
	NADE_FLASH
}

// ����� ��� ������� ���� � ����?
enum
{
	BLOCKS_NORMAL = 0,
	BLOCKS_YELLOW,
	BLOCKS_BLACK,
	BLOCKS_BLUE,
	BLOCKS_RED
}

/*=======================================================================
                           -= ������ =- 
========================================================================*/

/* :: ���������� ��� ����� ����

#classname -  ����� �� ����� ����� (������: "Test Zombie")
#classinfo - ������ ���������� ������� ����� ����� (������: "g+ s-")
#classmdl - ����� �� ����� ����� (������: "zombie" , ������ �� �� ������ � models/player/���/���.mdl)
#classclawmdl - ����� �� ������ �� ����� ����� (������: "claw" , ������ �� �� ������ � models/���.mdl)
#health - ���� �� ����� ����� (������: 2000)
#gravity - ���������� �� ����� ����� (������: 0.5) (1.0 = 800 ��������� , 0.5 = 400 ���������� ...)
#speed - ������� �� ����� ����� (������: 400.0) (0.0 = �������� �������)
#access - ����� ������ ����� �� �������� �� ����� (ADMIN_ALL - �� ������)

::::: ��������� ����� ������� �� �����. (int)
*/

native register_zombie_class(const classname[],const classinfo[], const classmdl[],const classclawmdl[], health,Float:gravity,Float:speed, access)

/* :: ���������� ��� ���� � shop ������

#itemname - ����� �� ����� (������: "Test Item")
#itemcost - ���� �� ����� (������: 15)
#itemuse - ���� �� ���� �� �� �������� �����? (USE_BATTLE - � ������� ���� , USE_BUILD - � ������������ ���� , USE_BOTH - � � ����� ����)
#itemteam - ��� ���� �� ������ �����? (TEAM_ZOMBIES - ��������� , TEAM_HUMANS - ������ , TEAM_BOTH - ������)
#access - ����� ������ ����� �� �������� �� ����� (ADMIN_ALL - �� ������)
#maxbuys - ����� ���� �� ���� �� �� ���� ������ �� ����? (NO_MAX_BUYS - ����������� ���� ����)

::::: ��������� ����� ������� �� �����. (int)
*/

native register_shop_item(const itemname[], itemcost, itemuse, itemteam, access, maxbuys)

/* :: ����� ������� �� ����� �� ������ (-1 ��� � Classic Zombie)

#id - ������ �� ������

::::: ��������� ����� ������� �� ����� �� ������. (int)
*/

native get_user_zombie_class(id)

/* :: ������ ������� �� ����� �� ������

#id - ������ �� ������
#classid - ������ �� ����� ����� (-1 - Classic Zombie)
*/

native set_user_zombie_class(id,classid)

/* :: ����� ��������� �������� ��� ������� � �����

#id - ������ �� ������

::::: ��������� ����� true ��� � ����� � false - ��� �� �. (bool)
*/

native is_user_zombie(id)

/* :: ����� ��������� �������� ��� ������� � �����

#id - ������ �� ������

::::: ��������� ����� true ��� � ����� � false - ��� �� �. (bool)
*/

native is_user_human(id)

/* :: ����� ���������� �� ��������� �� �����

#id - ������ �� ������

::::: ��������� ����� ��������� �� �����. (int)
*/

native get_user_credits(id)

/* :: ������ ���������� �� ��������� �� �����

#id - ������ �� ������
#credits - ���������� �� ���������, ����� ������ �� ������� (����������� � get_user_credits ��� ������ �� ���������/���������� ������� �� �����)
*/

native set_user_credits(id,credits)

/* :: ����� ���������� �� ������������ �� ����� ����� ��������� ����, ����� � ������

#id - ������ �� ������

::::: ��������� ����� ������������ �� ����� ����� ��������� ����, ����� � ������. (float)
*/

native get_user_block_distance(id)

/* :: ������ ���������� �� ������������ �� ����� ����� ��������� ����, ����� � ������

#id - ������ �� ������
#dist - ���������� �� ������������ �� ����� ����� ��������� ����, ����� � ������, ����� ������ �� �������
*/

native set_user_block_distance(id,Float:dist)

/* :: ����� ����� ���� ����� �������, �������� � �������

::::: ��������� ����� ����� ���� ����� �������, �������� � �������. (int)
*/

native get_total_zombie_classes()

/* :: ����� ����� ���� shop �����, �������� � �������

::::: ��������� ����� ����� ���� shop �����, �������� � �������. (int)
*/

native get_total_shop_items()

/* :: ����� ��������� �������� ��� ������� ���� �� ����� � ������� ����

#id - ������ �� ������

::::: ��������� ����� true ��� ������� ���� �� ����� � ������� ���� � false - ��� �� ����. (bool)
*/

native get_user_can_build_battle(id)

/* :: ������ ���������� �� �����, �� �� ���� �� ����� ������� � � ������� ���� (������� �� ������������ �� ���������� ����� ����)

#id - ������ �� ������
#set - true : �� �� ���� �� ����� � false : �� �� �� ����
*/

native set_user_can_build_battle(id,set)

/* :: ����� ������ �� �������� �� �����, ����� ������� ����� � �������

#id - ������ �� ������

::::: ��������� ����� ������ �� �������� �� �����, ����� ������� ����� � �������. (int)
*/

native get_user_block_ent(id)

/* :: ������ ������ �� �������� �� �����, ����� ������� ����� � �������

#id - ������ �� ������
#ent - ������ �� ��������
*/

native set_user_block_ent(id,ent)

/* :: ����� �������� �������� ��� � freezetime � �������

::::: ��������� ����� true ��� � � false - ��� �� �. (bool)
*/

native is_freezetime()

/* :: ����� ���������� ����� �� ������������ ����

::::: ��������� ����� ���������� ����� �� ������������ ���� � �������. (int)
*/

native get_build_phase_remaining_time()

/* :: ����� �������� �������� ��� �������� ����� �� ������ (��� � ������� � ������������ ����)

::::: ��������� ����� true ��� ����� � false - ��� �� �����. (bool)
*/

native user_can_build()

/* :: ������ ���� �������� ����� �� ������ (���� � ������� � ���������� ����)

#build - true - ��� �����, false - ��� �� �����
*/

native set_user_can_build(build)

/* :: ����� �������� �������� �� ������ �� ���� � �������

::::: ��������� ����� �������� �������� �� ������ �� ���� � ������� (MODE_NORMAL - �������� ����� (� ��������) , MODE_INFECTION - ����� � ��������) . (int)
*/

native get_roundmode()

/* :: ����� ��������� �������� ��� ������� � ��� ����� ��� ��������� ��

#id - ������ �� ������

::::: ��������� ����� true ��� � ��� ����� � false - ��� �� � ���. (bool)
*/

native was_user_zombie(id)

/* :: ������ �������� ���� ������� � ��� ����� ��� ��������� �� (��� � ��� ������ �� ����� �� ���� �����, �������� �� ��� ��������)

#id - ������ �� ������
#true - ���������� - 1 ��� � ���, 0 - ��� �� �
*/

native set_user_was_zombie(id,true)

/* :: ����� ��������� �������� ��� ������� � ������ (��������� �� ���������)

#id - ������ �� ������

::::: ��������� ����� true ��� � � false - ��� �� �. (bool)
*/

native is_user_banned(id)

/* :: ����� ���������� �� ���������� ���� �� ������� ��� ������

#id - ������ �� ������

::::: ��������� ����� ���������� �� ���������� ���� �� ������� ��� ������. (int)
*/

native get_user_fire_duration(id)

/* :: ������ ���������� �� o��������� ���� �� ������� ��� ������

#id - ������ �� ������
#dist - ���������� �� o��������� ���� �� ������� ��� ������, ����� ������ �� ������� (1 - �� �� ����� �������� �� �����)
*/

native set_user_fire_duration(id,duration)

/* :: ����� ��������� �������� ��� ������� � �������

#id - ������ �� ������

::::: ��������� ����� true ��� � � false - ��� �� �. (bool)
*/

native is_user_frozen(id)

/* :: ����� ��������� �������� ��� ������� � ������� (������� �� �� ����)

#id - ������ �� ������

::::: ��������� ����� true ��� � � false - ��� �� �. (bool)
*/

native is_user_frozen_cool(id)

/* :: ������� �����

#attacker - ������ �� ������ ���������
#victim - ������ �� ������ ������
#duration - ���������� ���� �� ������� ��� ������ (0 - ���������� �� �� ����� �� CVAR-a vzbb_grenade_fire_duration)
*/

native user_burn(attacker,victim,duration)

/* :: �������� �����

#id - ������ �� ������
*/

native user_freeze(id)

/* :: �������� ����� (������� ������� ������� �� �� ����)

#id - ������ �� ������
*/

native user_freeze_cool(id)

/* :: �������� ������������ �� �����

#id - ������ �� ������
*/

native user_unfreeze(id)

/* :: �������� �������� �� �����

#id - ������ �� ������
*/

native user_unfreeze_cool(id)

/* :: ��������� �����

#victim - ������ �� ��������
#infector - ������ �� ������������
*/

native user_infect(victim,infector)

/* :: ����������� �����

#id - ������ �� ������
*/

native user_uninfect(id)

/* :: ����� �������� ��� �� ����

#ent - ������ �� �������� �� �����

::::: ��������� ����� �������� ��� �� ����� (int)
*/

native get_block_fun_type(ent)

/* :: ������ ������� ��� �� ����

#ent - ������ �� �������� �� �����
#funtype - ������� ��� �� �����
(BLOCKS_YELLOW - ����������� �� ���� , BLOCKS_BLACK - �������� ����;
BLOCKS_BLUE - ������� ���� , BLOCKS_RED - �������� ����)
*/

native set_block_fun_type(ent,funtype)

/* :: �������� �������� ��� �� ����

#ent - ������ �� �������� �� �����
*/

native reset_block_fun_type(ent)

/* :: ����� ���������� �� ����������� �� "Round Deal" � ���������� ����

::::: ��������� ����� ���������� �� �����������. (int)
*/

native get_deal_discount()

/* :: ����� ��������� �������� ���� ������ � � �������� �� "Round Deal" � ���������� ����

::::: ��������� ����� true ��� � � false - ��� �� �. (bool)
*/

native is_deal_offer(itemid)

/* :: �������� ��������� (��� ��� ������) */

native hide_barrierent()

/* :: ���������� ���������������� �� ��������� (��� ��� ������) */

native reset_barrierent()

/* :: ������ ����� �� HUD-a �� ��������, �� ������� �� HUD-a �� ������ (����������� ��� update_user_hud_data forward-a)

#text - ������� (���������� ������� - 128 �������, �������� ������ �� � ������������� ����������)
*/

native set_hud_cache_text(text[])

/* :: ������ ���� (� RGB ������) �� HUD-a �� ��������, �� ������� �� HUD-a �� ������ (����������� ��� update_user_hud_data forward-a)

#r - ������ ����
#g - ����� ����
#b - ��� ����
*/

native set_hud_cache_colors(r,g,b)

/* :: ������ ������� �� ��������� �� HUD-a �� ��������, �� ������� �� HUD-a �� ������ (����������� ��� update_user_hud_data forward-a)

#condition - ������� (����������� true, �� �� �� ������� ������ ��� ������ ������)
*/

native set_hud_cache_condition(bool:condition)

/* :: ������� ��������� �� ��������� �� HUD-a �� �������� */

native force_user_hud_data()

/* :: ������� ��������� �� ������ �� ������

#id - ������ �� ������
*/

native force_weapon_menu(id)

/* :: �������� rendering-� �� ������ (������� �� ��������� �� glow � ���������� �� ������������ �� ������)

#id - ������ �� ������
*/

native restore_user_rendering(id)

/*=======================================================================
                           -= Forward-� =- 
========================================================================*/

/* :: ������� �� ��� �������� �� ����� ����

#id - ������ �� ������
#classid - ������ �� ����� �����
*/

forward zombie_class_selected(id,classid)

/* :: ������� �� ��� �������� �� ���� �� shop ������

#id - ������ �� ������
#itemid - ������ �� �����

:::::: ������� �������� FORWARD_CONTINUE, �� �� ��������� ���������� �� ����� ����.
*/

forward shop_item_selected(id,itemid)

/* :: ������� �� ��� ������� ��� ������ �� ����

#id - ������ �� ������
#pullpush_type - ��� �� ��������� �� ����� (1 - ������� , 2 - ������)

:::::: ������� �������� FORWARD_CONTINUE, �� �� ������ ������������ �� forward-a.
*/

forward block_pull_push(id,pullpush_type)

/* :: ������� �� ���� ����������� �� ������� ���� */

forward battle_phase_begin()

/* :: ������� �� ���� �������������� ��������� �� ������� ���� �� ����� (� ��������� /start)

#id - ������ �� ���������������, ������� ���������
 */

forward battle_phase_begin_admin(id)

/* :: ������� �� ����� �������� �� �������

#owner - ������ �� ����������� �� ���������
#ent - ������ �� �������� �� ���������
#nade_type - ��� �� ��������� (1 - HE grenade (FireNade) , 2 - Smoke grenade , 3 - Flashbang (FrostNade))

:::::: ������� �������� FORWARD_CONTINUE, �� �� ������ ������������ �� forward-a.
*/

forward nade_throw_pre(owner,ent,nade_type)

/* :: ������� �� ���� �������� �� �������

#owner - ������ �� ����������� �� ���������
#ent - ������ �� �������� �� ���������
#nade_type - ��� �� ��������� (1 - HE grenade (FireNade) , 2 - Smoke grenade , 3 - Flashbang (FrostNade))
*/

forward nade_throw_post(owner,ent,nade_type)

/* :: ������� �� ����� ����� ������� �� ���� ��� ��������� �� �����

#id -  ������ �� ������
*/

forward user_burn_pre(id)

/* :: ������� �� ���� ����� ������� �� ���� ��� ��������� �� �����

#id - ������ �� ������
*/

forward user_burn_post(id)

/* :: ������� �� ��� ������������ �� �������� �� �����

#id - ������ �� ������
*/

forward user_remove_burn(id)

/* :: ������� �� ����� ����������� �� �����

#id - ������ �� ������
*/

forward user_freeze_pre(id)

/* :: ������� �� ���� ����������� �� �����

#id - ������ �� ������
*/

forward user_freeze_post(id)

/* :: ������� �� ����� ������������ �� ������������� �� �����

#id - ������ �� ������
*/

forward user_unfreeze_pre(id)

/* :: ������� �� ���� ������������ �� ������������� �� �����

#id - ������ �� ������
*/

forward user_unfreeze_post(id)

/* :: ������� �� ����� ����� �� ������� �� �� ����

#id - ������ �� ������
*/

forward user_freeze_cool_pre(id)

/* :: ������� �� ���� ���� ����� ������� �� �� ����

#id - ������ �� ������
*/

forward user_freeze_cool_post(id)

/* :: ������� �� ����� ����� �� ���� �� �� ����

#id - ������ �� ������
*/

forward user_unfreeze_cool_pre(id)

/* :: ������� �� ���� ���� ����� ���� �� �� ����

#id - ������ �� ������
*/

forward user_unfreeze_cool_post(id)

/* :: ������� �� ����� ����������� �� �����

#victim - ������ �� ��������
#infector - ������ �� ������������

:::::: ������� �������� FORWARD_CONTINUE, �� �� ������ ������������ �� forward-a.
*/

forward user_infect_pre(victim,infector)

/* :: ������� �� ���� ����������� �� �����

#victim - ������ �� ��������
*/

forward user_infect_post(victim)

/* :: ������� �� ����� ������������� �� �����

#id - ������ �� ������

:::::: ������� �������� FORWARD_CONTINUE, �� �� ������ ������������ �� forward-a.
*/

forward user_uninfect_pre(id)

/* :: ������� �� ���� ������������� �� �����

#id - ������ �� ������
*/

forward user_uninfect_post(id)

/* :: ������� �� ����� ������� �� ����

#id - ������ �� ������

:::::: ������� �������� FORWARD_CONTINUE, �� �� ������ ������������ �� forward-a.
*/

forward grab_block_pre(id)

/* :: ������� �� ���� ������� �� ����

#id - ������ �� ������

:::::: ������� �������� FORWARD_CONTINUE, �� �� ������ ������������ �� forward-a.
*/

forward grab_block_post(id)

/* :: ������� �� ����� ��������� �� ����

#id - ������ �� ������
*/

forward release_block_pre(id)

/* :: ������� �� ���� ��������� �� ����

#id - ������ �� ������
*/

forward release_block_post(id)

/* :: ������� �� ��� ����� ���������� �� HUD-� �� ��������

:::::: ������� �������� FORWARD_CONTINUE, �� �� �������� ������� ���� HUD-a ��� ������� ������� �� �������� � ������� ����.
*/

forward update_user_hud_data()

/* :: ������� �� ����� ��������� �� ����� ��� ������� ����

#id - ������ �� ������
#ent - ������ �� �������� �� �����
#funtype - ������� ��� �� �����
(BLOCKS_YELLOW - ����������� �� ���� , BLOCKS_BLACK - �������� ����;
BLOCKS_BLUE - ������� ���� , BLOCKS_RED - �������� ����)

:::: ������� �������� FORWARD_CONTINUE, �� �� ��������� ������ �� �������� ����.
*/

forward fun_block_touch_pre(id,ent,funtype)

/* :: ������� �� ���� ��������� �� ����� ��� ������� ����

#id - ������ �� ������
#ent - ������ �� �������� �� �����
#funtype - ������� ��� �� �����
(BLOCKS_YELLOW - ����������� �� ���� , BLOCKS_BLACK - �������� ����;
BLOCKS_BLUE - ������� ���� , BLOCKS_RED - �������� ����)
*/

forward fun_block_touch_post(id,ent,funtype)
/* AMXX-Studio Notes - DO NOT MODIFY BELOW HERE
*{\\ rtf1\\ ansi\\ deff0{\\ fonttbl{\\ f0\\ fnil Tahoma;}}\n\\ viewkind4\\ uc1\\ pard\\ lang1026\\ f0\\ fs16 \n\\ par }
*/
