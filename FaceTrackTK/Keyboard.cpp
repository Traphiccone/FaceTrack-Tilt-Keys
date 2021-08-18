#include "stdafx.h"
#include "Keyboard.h"

using namespace std;


CKeyboard::CKeyboard()
{
	for (int key = 0; key < 8; key++)
	{
		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;
		m_keyIDs.push_back(ip);
	}

	for (int key = 0; key < 8; key++)
	{
		m_activeKeys.push_back(false);
	}
}


CKeyboard::~CKeyboard()
{
}


void CKeyboard::KeyL()
{
	// Press the keys in the correct order
	if (m_activeKeys[0])
	{
		m_keyIDs[0].ki.dwFlags = 0; // 0 for key press
		SendInput(1, &m_keyIDs[0], sizeof(INPUT));
	}
	if (m_activeKeys[1])
	{
		m_keyIDs[1].ki.dwFlags = 0; // 0 for key press
		SendInput(1, &m_keyIDs[1], sizeof(INPUT));
	}
	if (m_activeKeys[2])
	{
		m_keyIDs[2].ki.dwFlags = 0; // 0 for key press
		SendInput(1, &m_keyIDs[2], sizeof(INPUT));
	}
	if (m_activeKeys[3])
	{
		m_keyIDs[3].ki.dwFlags = 0; // 0 for key press
		SendInput(1, &m_keyIDs[3], sizeof(INPUT));
	}

	// Release the keys in the correct order
	if (m_activeKeys[0])
	{
		m_keyIDs[0].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &m_keyIDs[0], sizeof(INPUT));
	}
	if (m_activeKeys[1])
	{
		m_keyIDs[1].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &m_keyIDs[1], sizeof(INPUT));
	}
	if (m_activeKeys[2])
	{
		m_keyIDs[2].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &m_keyIDs[2], sizeof(INPUT));
	}
	if (m_activeKeys[3])
	{
		m_keyIDs[3].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &m_keyIDs[3], sizeof(INPUT));
	}

}

void CKeyboard::KeyR()
{
	// Press the keys in the correct order
	if (m_activeKeys[4])
	{
		m_keyIDs[4].ki.dwFlags = 0; // 0 for key press
		SendInput(1, &m_keyIDs[4], sizeof(INPUT));
	}
	if (m_activeKeys[5])
	{
		m_keyIDs[5].ki.dwFlags = 0; // 0 for key press
		SendInput(1, &m_keyIDs[5], sizeof(INPUT));
	}
	if (m_activeKeys[6])
	{
		m_keyIDs[6].ki.dwFlags = 0; // 0 for key press
		SendInput(1, &m_keyIDs[6], sizeof(INPUT));
	}
	if (m_activeKeys[7])
	{
		m_keyIDs[7].ki.dwFlags = 0; // 0 for key press
		SendInput(1, &m_keyIDs[7], sizeof(INPUT));
	}

	// Release the keys in the correct order
	if (m_activeKeys[4])
	{
		m_keyIDs[4].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &m_keyIDs[4], sizeof(INPUT));
	}
	if (m_activeKeys[5])
	{
		m_keyIDs[5].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &m_keyIDs[5], sizeof(INPUT));
	}
	if (m_activeKeys[6])
	{
		m_keyIDs[6].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &m_keyIDs[6], sizeof(INPUT));
	}
	if (m_activeKeys[7])
	{
		m_keyIDs[7].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &m_keyIDs[7], sizeof(INPUT));
	}
}

void CKeyboard::ConvertStringsToKeys()
{
	CreateCodeList();

	for (int i = 0; i < m_stringKeyIDs.size(); i++)
	{
		if (m_stringKeyIDs[i] == L"(OPTIONAL)")
		{
			m_activeKeys[i] = false;
		}	
		else if (VKcodes.find(m_stringKeyIDs[i].MakeUpper()) != VKcodes.end())
		{
			m_keyIDs[i] = (VKcodes.find(m_stringKeyIDs[i])->second);
			m_activeKeys[i] = true;
		}
		else if (m_stringKeyIDs[i].Find(L"'") == 0)
		{
			m_stringKeyIDs[i].MakeUpper();
			m_stringKeyIDs[i] = m_stringKeyIDs[i][1];
			if (VKcodes.find(m_stringKeyIDs[i]) != VKcodes.end())
			{
				m_keyIDs[i] = (VKcodes.find(m_stringKeyIDs[i])->second);
				m_activeKeys[i] = true;
			}
		}
		else
		{
			m_stringKeyIDs[i].MakeUpper();
			if (m_stringKeyIDs[i].Find(L"VK_") != 0)
			{
				m_stringKeyIDs[i].Insert(0, L"VK_");
			}
			if (VKcodes.find(m_stringKeyIDs[i]) != VKcodes.end())
			{
				m_keyIDs[i] = (VKcodes.find(m_stringKeyIDs[i])->second);
				m_activeKeys[i] = true;
			}
		}
	}
}

void CKeyboard::CreateCodeList()
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.dwFlags = 0;

	ip.ki.wVk = VK_LBUTTON;
	VKcodes[L"VK_LBUTTON"] = { ip };
	ip.ki.wVk = VK_RBUTTON;
	VKcodes[L"VK_RBUTTON"] = { ip };
	ip.ki.wVk = VK_CANCEL;
	VKcodes[L"VK_CANCEL"] = { ip };
	ip.ki.wVk = VK_MBUTTON;
	VKcodes[L"VK_MBUTTON"] = { ip };
	ip.ki.wVk = VK_XBUTTON1;
	VKcodes[L"VK_XBUTTON1"] = { ip };
	ip.ki.wVk = VK_XBUTTON2;
	VKcodes[L"VK_XBUTTON2"] = { ip };
	ip.ki.wVk = VK_BACK;
	VKcodes[L"VK_BACK"] = { ip };
	ip.ki.wVk = VK_TAB;
	VKcodes[L"VK_TAB"] = { ip };
	ip.ki.wVk = VK_CLEAR;
	VKcodes[L"VK_CLEAR"] = { ip };
	ip.ki.wVk = VK_RETURN;
	VKcodes[L"VK_RETURN"] = { ip };
	ip.ki.wVk = VK_SHIFT;
	VKcodes[L"VK_SHIFT"] = { ip };
	ip.ki.wVk = VK_CONTROL;
	VKcodes[L"VK_CONTROL"] = { ip };
	ip.ki.wVk = VK_MENU;
	VKcodes[L"VK_MENU"] = { ip };
	ip.ki.wVk = VK_PAUSE;
	VKcodes[L"VK_PAUSE"] = { ip };
	ip.ki.wVk = VK_CAPITAL;
	VKcodes[L"VK_CAPITAL"] = { ip };
	ip.ki.wVk = VK_KANA;
	VKcodes[L"VK_KANA"] = { ip };
	ip.ki.wVk = VK_HANGUL;
	VKcodes[L"VK_HANGUL"] = { ip };
	ip.ki.wVk = VK_JUNJA;
	VKcodes[L"VK_JUNJA"] = { ip };
	ip.ki.wVk = VK_FINAL;
	VKcodes[L"VK_FINAL"] = { ip };
	ip.ki.wVk = VK_HANJA;
	VKcodes[L"VK_HANJA"] = { ip };
	ip.ki.wVk = VK_KANJI;
	VKcodes[L"VK_KANJI"] = { ip };
	ip.ki.wVk = VK_ESCAPE;
	VKcodes[L"VK_ESCAPE"] = { ip };
	ip.ki.wVk = VK_CONVERT;
	VKcodes[L"VK_CONVERT"] = { ip };
	ip.ki.wVk = VK_NONCONVERT;
	VKcodes[L"VK_NONCONVERT"] = { ip };
	ip.ki.wVk = VK_ACCEPT;
	VKcodes[L"VK_ACCEPT"] = { ip };
	ip.ki.wVk = VK_MODECHANGE;
	VKcodes[L"VK_MODECHANGE"] = { ip };
	ip.ki.wVk = VK_SPACE;
	VKcodes[L"VK_SPACE"] = { ip };
	ip.ki.wVk = VK_PRIOR;
	VKcodes[L"VK_PRIOR"] = { ip };
	ip.ki.wVk = VK_NEXT;
	VKcodes[L"VK_NEXT"] = { ip };
	ip.ki.wVk = VK_END;
	VKcodes[L"VK_END"] = { ip };
	ip.ki.wVk = VK_HOME;
	VKcodes[L"VK_HOME"] = { ip };
	ip.ki.wVk = VK_LEFT;
	VKcodes[L"VK_LEFT"] = { ip };
	ip.ki.wVk = VK_UP;
	VKcodes[L"VK_UP"] = { ip };
	ip.ki.wVk = VK_RIGHT;
	VKcodes[L"VK_RIGHT"] = { ip };
	ip.ki.wVk = VK_DOWN;
	VKcodes[L"VK_DOWN"] = { ip };
	ip.ki.wVk = VK_SELECT;
	VKcodes[L"VK_SELECT"] = { ip };
	ip.ki.wVk = VK_PRINT;
	VKcodes[L"VK_PRINT"] = { ip };
	ip.ki.wVk = VK_EXECUTE;
	VKcodes[L"VK_EXECUTE"] = { ip };
	ip.ki.wVk = VK_SNAPSHOT;
	VKcodes[L"VK_SNAPSHOT"] = { ip };
	ip.ki.wVk = VK_INSERT;
	VKcodes[L"VK_INSERT"] = { ip };
	ip.ki.wVk = VK_DELETE;
	VKcodes[L"VK_DELETE"] = { ip };
	ip.ki.wVk = VK_HELP;
	VKcodes[L"VK_HELP"] = { ip };
	ip.ki.wVk = '0';
	VKcodes[L"0"] = { ip };
	ip.ki.wVk = '1';
	VKcodes[L"1"] = { ip };
	ip.ki.wVk = '2';
	VKcodes[L"2"] = { ip };
	ip.ki.wVk = '3';
	VKcodes[L"3"] = { ip };
	ip.ki.wVk = '4';
	VKcodes[L"4"] = { ip };
	ip.ki.wVk = '5';
	VKcodes[L"5"] = { ip };
	ip.ki.wVk = '6';
	VKcodes[L"6"] = { ip };
	ip.ki.wVk = '7';
	VKcodes[L"7"] = { ip };
	ip.ki.wVk = '8';
	VKcodes[L"8"] = { ip };
	ip.ki.wVk = '9';
	VKcodes[L"9"] = { ip };
	ip.ki.wVk = 'A';
	VKcodes[L"A"] = { ip };
	ip.ki.wVk = 'B';
	VKcodes[L"B"] = { ip };
	ip.ki.wVk = 'C';
	VKcodes[L"C"] = { ip };
	ip.ki.wVk = 'D';
	VKcodes[L"D"] = { ip };
	ip.ki.wVk = 'E';
	VKcodes[L"E"] = { ip };
	ip.ki.wVk = 'F';
	VKcodes[L"F"] = { ip };
	ip.ki.wVk = 'G';
	VKcodes[L"G"] = { ip };
	ip.ki.wVk = 'H';
	VKcodes[L"H"] = { ip };
	ip.ki.wVk = 'I';
	VKcodes[L"I"] = { ip };
	ip.ki.wVk = 'J';
	VKcodes[L"J"] = { ip };
	ip.ki.wVk = 'K';
	VKcodes[L"K"] = { ip };
	ip.ki.wVk = 'L';
	VKcodes[L"L"] = { ip };
	ip.ki.wVk = 'M';
	VKcodes[L"M"] = { ip };
	ip.ki.wVk = 'N';
	VKcodes[L"N"] = { ip };
	ip.ki.wVk = 'O';
	VKcodes[L"O"] = { ip };
	ip.ki.wVk = 'P';
	VKcodes[L"P"] = { ip };
	ip.ki.wVk = 'Q';
	VKcodes[L"Q"] = { ip };
	ip.ki.wVk = 'R';
	VKcodes[L"R"] = { ip };
	ip.ki.wVk = 'S';
	VKcodes[L"S"] = { ip };
	ip.ki.wVk = 'T';
	VKcodes[L"T"] = { ip };
	ip.ki.wVk = 'U';
	VKcodes[L"U"] = { ip };
	ip.ki.wVk = 'V';
	VKcodes[L"V"] = { ip };
	ip.ki.wVk = 'W';
	VKcodes[L"W"] = { ip };
	ip.ki.wVk = 'X';
	VKcodes[L"X"] = { ip };
	ip.ki.wVk = 'Y';
	VKcodes[L"Y"] = { ip };
	ip.ki.wVk = 'Z';
	VKcodes[L"Z"] = { ip };
	ip.ki.wVk = VK_LWIN;
	VKcodes[L"VK_LWIN"] = { ip };
	ip.ki.wVk = VK_RWIN;
	VKcodes[L"VK_RWIN"] = { ip };
	ip.ki.wVk = VK_APPS;
	VKcodes[L"VK_APPS"] = { ip };
	ip.ki.wVk = VK_SLEEP;
	VKcodes[L"VK_SLEEP"] = { ip };
	ip.ki.wVk = VK_NUMPAD0;
	VKcodes[L"VK_NUMPAD0"] = { ip };
	ip.ki.wVk = VK_NUMPAD1;
	VKcodes[L"VK_NUMPAD1"] = { ip };
	ip.ki.wVk = VK_NUMPAD2;
	VKcodes[L"VK_NUMPAD2"] = { ip };
	ip.ki.wVk = VK_NUMPAD3;
	VKcodes[L"VK_NUMPAD3"] = { ip };
	ip.ki.wVk = VK_NUMPAD4;
	VKcodes[L"VK_NUMPAD4"] = { ip };
	ip.ki.wVk = VK_NUMPAD5;
	VKcodes[L"VK_NUMPAD5"] = { ip };
	ip.ki.wVk = VK_NUMPAD6;
	VKcodes[L"VK_NUMPAD6"] = { ip };
	ip.ki.wVk = VK_NUMPAD7;
	VKcodes[L"VK_NUMPAD7"] = { ip };
	ip.ki.wVk = VK_NUMPAD8;
	VKcodes[L"VK_NUMPAD8"] = { ip };
	ip.ki.wVk = VK_NUMPAD9;
	VKcodes[L"VK_NUMPAD9"] = { ip };
	ip.ki.wVk = VK_MULTIPLY;
	VKcodes[L"VK_MULTIPLY"] = { ip };
	ip.ki.wVk = VK_ADD;
	VKcodes[L"VK_ADD"] = { ip };
	ip.ki.wVk = VK_SEPARATOR;
	VKcodes[L"VK_SEPARATOR"] = { ip };
	ip.ki.wVk = VK_SUBTRACT;
	VKcodes[L"VK_SUBTRACT"] = { ip };
	ip.ki.wVk = VK_DECIMAL;
	VKcodes[L"VK_DECIMAL"] = { ip };
	ip.ki.wVk = VK_DIVIDE;
	VKcodes[L"VK_DIVIDE"] = { ip };
	ip.ki.wVk = VK_F1;
	VKcodes[L"VK_F1"] = { ip };
	ip.ki.wVk = VK_F2;
	VKcodes[L"VK_F2"] = { ip };
	ip.ki.wVk = VK_F3;
	VKcodes[L"VK_F3"] = { ip };
	ip.ki.wVk = VK_F4;
	VKcodes[L"VK_F4"] = { ip };
	ip.ki.wVk = VK_F5;
	VKcodes[L"VK_F5"] = { ip };
	ip.ki.wVk = VK_F6;
	VKcodes[L"VK_F6"] = { ip };
	ip.ki.wVk = VK_F7;
	VKcodes[L"VK_F7"] = { ip };
	ip.ki.wVk = VK_F8;
	VKcodes[L"VK_F8"] = { ip };
	ip.ki.wVk = VK_F9;
	VKcodes[L"VK_F9"] = { ip };
	ip.ki.wVk = VK_F10;
	VKcodes[L"VK_F10"] = { ip };
	ip.ki.wVk = VK_F11;
	VKcodes[L"VK_F11"] = { ip };
	ip.ki.wVk = VK_F12;
	VKcodes[L"VK_F12"] = { ip };
	ip.ki.wVk = VK_F13;
	VKcodes[L"VK_F13"] = { ip };
	ip.ki.wVk = VK_F14;
	VKcodes[L"VK_F14"] = { ip };
	ip.ki.wVk = VK_F15;
	VKcodes[L"VK_F15"] = { ip };
	ip.ki.wVk = VK_F16;
	VKcodes[L"VK_F16"] = { ip };
	ip.ki.wVk = VK_F17;
	VKcodes[L"VK_F17"] = { ip };
	ip.ki.wVk = VK_F18;
	VKcodes[L"VK_F18"] = { ip };
	ip.ki.wVk = VK_F19;
	VKcodes[L"VK_F19"] = { ip };
	ip.ki.wVk = VK_F20;
	VKcodes[L"VK_F20"] = { ip };
	ip.ki.wVk = VK_F21;
	VKcodes[L"VK_F21"] = { ip };
	ip.ki.wVk = VK_F22;
	VKcodes[L"VK_F22"] = { ip };
	ip.ki.wVk = VK_F23;
	VKcodes[L"VK_F23"] = { ip };
	ip.ki.wVk = VK_F24;
	VKcodes[L"VK_F24"] = { ip };
	ip.ki.wVk = VK_NUMLOCK;
	VKcodes[L"VK_NUMLOCK"] = { ip };
	ip.ki.wVk = VK_SCROLL;
	VKcodes[L"VK_SCROLL"] = { ip };
	ip.ki.wVk = VK_LSHIFT;
	VKcodes[L"VK_LSHIFT"] = { ip };
	ip.ki.wVk = VK_RSHIFT;
	VKcodes[L"VK_RSHIFT"] = { ip };
	ip.ki.wVk = VK_LCONTROL;
	VKcodes[L"VK_LCONTROL"] = { ip };
	ip.ki.wVk = VK_RCONTROL;
	VKcodes[L"VK_RCONTROL"] = { ip };
	ip.ki.wVk = VK_LMENU;
	VKcodes[L"VK_LMENU"] = { ip };
	ip.ki.wVk = VK_RMENU;
	VKcodes[L"VK_RMENU"] = { ip };
	ip.ki.wVk = VK_BROWSER_BACK;
	VKcodes[L"VK_BROWSER_BACK"] = { ip };
	ip.ki.wVk = VK_BROWSER_FORWARD;
	VKcodes[L"VK_BROWSER_FORWARD"] = { ip };
	ip.ki.wVk = VK_BROWSER_REFRESH;
	VKcodes[L"VK_BROWSER_REFRESH"] = { ip };
	ip.ki.wVk = VK_BROWSER_STOP;
	VKcodes[L"VK_BROWSER_STOP"] = { ip };
	ip.ki.wVk = VK_BROWSER_SEARCH;
	VKcodes[L"VK_BROWSER_SEARCH"] = { ip };
	ip.ki.wVk = VK_BROWSER_FAVORITES;
	VKcodes[L"VK_BROWSER_FAVORITES"] = { ip };
	ip.ki.wVk = VK_BROWSER_HOME;
	VKcodes[L"VK_BROWSER_HOME"] = { ip };
	ip.ki.wVk = VK_VOLUME_MUTE;
	VKcodes[L"VK_VOLUME_MUTE"] = { ip };
	ip.ki.wVk = VK_VOLUME_DOWN;
	VKcodes[L"VK_VOLUME_DOWN"] = { ip };
	ip.ki.wVk = VK_VOLUME_UP;
	VKcodes[L"VK_VOLUME_UP"] = { ip };
	ip.ki.wVk = VK_MEDIA_NEXT_TRACK;
	VKcodes[L"VK_MEDIA_NEXT_TRACK"] = { ip };
	ip.ki.wVk = VK_MEDIA_PREV_TRACK;
	VKcodes[L"VK_MEDIA_PREV_TRACK"] = { ip };
	ip.ki.wVk = VK_MEDIA_STOP;
	VKcodes[L"VK_MEDIA_STOP"] = { ip };
	ip.ki.wVk = VK_MEDIA_PLAY_PAUSE;
	VKcodes[L"VK_MEDIA_PLAY_PAUSE"] = { ip };
	ip.ki.wVk = VK_LAUNCH_MAIL;
	VKcodes[L"VK_LAUNCH_MAIL"] = { ip };
	ip.ki.wVk = VK_LAUNCH_MEDIA_SELECT;
	VKcodes[L"VK_LAUNCH_MEDIA_SELECT"] = { ip };
	ip.ki.wVk = VK_LAUNCH_APP1;
	VKcodes[L"VK_LAUNCH_APP1"] = { ip };
	ip.ki.wVk = VK_LAUNCH_APP2;
	VKcodes[L"VK_LAUNCH_APP2"] = { ip };
	ip.ki.wVk = VK_OEM_1;
	VKcodes[L"VK_OEM_1"] = { ip };
	ip.ki.wVk = VK_OEM_PLUS;
	VKcodes[L"VK_OEM_PLUS"] = { ip };
	ip.ki.wVk = VK_OEM_COMMA;
	VKcodes[L"VK_OEM_COMMA"] = { ip };
	ip.ki.wVk = VK_OEM_MINUS;
	VKcodes[L"VK_OEM_MINUS"] = { ip };
	ip.ki.wVk = VK_OEM_PERIOD;
	VKcodes[L"VK_OEM_PERIOD"] = { ip };
	ip.ki.wVk = VK_CAPITAL;
	VKcodes[L"VK_CAPITAL"] = { ip };
	ip.ki.wVk = VK_CAPITAL;
	VKcodes[L"VK_CAPITAL"] = { ip };
	ip.ki.wVk = VK_OEM_2;
	VKcodes[L"VK_OEM_2"] = { ip };
	ip.ki.wVk = VK_OEM_3;
	VKcodes[L"VK_OEM_3"] = { ip };
	ip.ki.wVk = VK_OEM_4;
	VKcodes[L"VK_OEM_4"] = { ip };
	ip.ki.wVk = VK_OEM_5;
	VKcodes[L"VK_OEM_5"] = { ip };
	ip.ki.wVk = VK_OEM_6;
	VKcodes[L"VK_OEM_6"] = { ip };
	ip.ki.wVk = VK_OEM_7;
	VKcodes[L"VK_OEM_7"] = { ip };
	ip.ki.wVk = VK_OEM_8;
	VKcodes[L"VK_OEM_8"] = { ip };
	ip.ki.wVk = VK_OEM_102;
	VKcodes[L"VK_OEM_102"] = { ip };
	ip.ki.wVk = VK_PROCESSKEY;
	VKcodes[L"VK_PROCESSKEY"] = { ip };
	ip.ki.wVk = VK_PACKET;
	VKcodes[L"VK_PACKET"] = { ip };
	ip.ki.wVk = VK_ATTN;
	VKcodes[L"VK_ATTN"] = { ip };
	ip.ki.wVk = VK_CRSEL;
	VKcodes[L"VK_CRSEL"] = { ip };
	ip.ki.wVk = VK_EXSEL;
	VKcodes[L"VK_EXSEL"] = { ip };
	ip.ki.wVk = VK_EREOF;
	VKcodes[L"VK_EREOF"] = { ip };
	ip.ki.wVk = VK_PLAY;
	VKcodes[L"VK_PLAY"] = { ip };
	ip.ki.wVk = VK_ZOOM;
	VKcodes[L"VK_ZOOM"] = { ip };
	ip.ki.wVk = VK_NONAME;
	VKcodes[L"VK_NONAME"] = { ip };
	ip.ki.wVk = VK_PA1;
	VKcodes[L"VK_PA1"] = { ip };
	ip.ki.wVk = VK_OEM_CLEAR;
	VKcodes[L"VK_OEM_CLEAR"] = { ip };
}

//INPUT ip;

//// Set up a generic keyboard event.
//ip.type = INPUT_KEYBOARD;
//ip.ki.wScan = 0; // hardware scan code for key
//ip.ki.time = 0;
//ip.ki.dwExtraInfo = 0;
//// Press the "Q" key
//ip.ki.wVk = 'Q'; // 0x51 virtual-key code for the "q" key
//ip.ki.dwFlags = 0; // 0 for key press
//SendInput(1, &ip, sizeof(INPUT));
//Sleep(15);

////Release the "Q" key
//ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
//SendInput(1, &ip, sizeof(INPUT));