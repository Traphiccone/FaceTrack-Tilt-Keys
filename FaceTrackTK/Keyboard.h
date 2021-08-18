#define WINVER 0x0500
#include <windows.h>
#include <vector>
#include <map>



#pragma once
class CKeyboard
{
public:
	CKeyboard();
	
	virtual ~CKeyboard();

	void KeyL();
	void KeyR();
	void ConvertStringsToKeys();
	void CreateCodeList();

	void SetStringKeys(std::vector<CString> keys){ 
		m_stringKeyIDs = keys;  ConvertStringsToKeys(); }
private:

	std::vector<CString> m_stringKeyIDs; //[0] = L1, [2] = L2 ... [4] = R1, [5] = R2...
	std::vector<INPUT> m_keyIDs;		 //[0] = L1, [2] = L2 ... [4] = R1, [5] = R2...
	std::map< CString, INPUT > VKcodes;
	std::vector<BOOL> m_activeKeys;		 //Matches above pattern for additional keys
};

