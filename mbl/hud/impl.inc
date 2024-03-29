#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
	bool:PlayerTogHUD[MAX_PLAYERS][E_TOGGLE_HUD:E_TOG_SIZE];

YCMD:togglehud(playerid, params[], help)
{
	ShowControlHUDDialog(playerid);
	return 1;
}

ShowControlHUDDialog(playerid)
{
	inline const Response(response, listitem, string:inputtext[]) 
	{
		#pragma unused response, inputtext, listitem

		if (response)
		{
			CustomRPC_ToggleHud(playerid, listitem, PlayerTogHUD[playerid][E_TOGGLE_HUD:listitem]); // ���������� 1 �ѧ����� 0 ����ͻԴ㹤����á (��Ѻ�Դ/�Դ)
			PlayerTogHUD[playerid][E_TOGGLE_HUD:listitem] = !PlayerTogHUD[playerid][E_TOGGLE_HUD:listitem];

			@return ShowControlHUDDialog(playerid);
		}
	}

	new szDialogMsg[80 + 22 * _:E_TOG_SIZE + 1];
	format(szDialogMsg, sizeof(szDialogMsg), 
		"᪷\t[%s]\n�ô���\t[%s]\n���ª���\t[%s]\n�Դ��\t[%s]\nHUD\t[%s]\n��ª��� (Speaker SAMPVoice)\t[%s]\n��ͤ��� 3DText\t[%s]",
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_CHAT] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_RADAR] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_TAG] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_WIDGET] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_HUD] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_SPEAKER] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE""),
			PlayerTogHUD[playerid][E_TOGGLE_HUD:E_TOG_3DTEXT] ? (""INDIANRED"OFF"WHITE"") : (""FORESTGREEN"ON"WHITE"")
	
		);

	Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_LIST, "��äǺ��� HUD (����Ѻ��������� 134)", szDialogMsg, "���͡", "�Դ˹�ҵ�ҧ");
}

stock CustomRPC_ToggleHud(playerid, hud_id, bool:toggled)
{
	new BitStream:bsn = BS_New();
	BS_WriteUint8(bsn, CUSTOM_SYNC);
	BS_WriteInt32(bsn, 1);

	BS_WriteInt32(bsn, hud_id);
	BS_WriteInt32(bsn, toggled);

	PR_SendPacket(bsn, playerid);
}

stock CustomRPC_ToggleEditableButton(playerid, bool:toggled)
{
	new BitStream:bsn = BS_New();
	BS_WriteUint8(bsn, CUSTOM_SYNC);
	BS_WriteInt32(bsn, 2);

	BS_WriteBool(bsn, toggled);

	PR_SendPacket(bsn, playerid);
}