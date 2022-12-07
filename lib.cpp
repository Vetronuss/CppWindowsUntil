#include <windows.h>
#include <iostream>
#include <conio.h>
#include <gdiplus.h>
#include <string>
#include <array>
#include <vector>
#include <iomanip>
#include <sstream>
#include <thread>

using namespace std;

std::string exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}

const vector<int> keyCode = { 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,VK_SPACE,VK_F20,VK_DECIMAL,VK_RETURN,
VK_BACK,
VK_TAB,
VK_SUBTRACT,
VK_ADD,

};
const vector<string> keys = { "0" ,"1" ,"2" ,"3" ,"4" ,"5" ,"6" ,"7" ,"8" ,"9" ,"a" ,"b" ,"c" ,"d" ,"e" ,"f" ,"g" ,"h" ,"i" ,"j" ,"k" ,"l" ,"m" ,"n" ,"o" ,"p" ,"q" ,"r" ,"s" ,"t" ,"u" ,"v" ,"w" ,"x" ,"y" ,"z"," ","_",".","\n",
"#B#",
"\t",
"-",
"+"
};

void pressKey(int key)
{
	INPUT ip;
	// ...
		// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "A" key
	ip.ki.wVk = key; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// ...
}
string readCoord(int x1, int y1, int x2, int y2)
{
	string cmd = "c:/ss.exe -rc " + to_string(x1) + " " + to_string(y1) + " " + to_string(x2) + " " + to_string(y2) + " -o ss.png";
	system(cmd.c_str());
	string out = exec("c:/tesseract.lnk C:\\Users\\Cooper\\source\\repos\\Library\\Library\\ss.png -");
	return out;
}
template< typename T >
std::string int_to_hex(T i)
{
	std::stringstream stream;
	stream << "0x"
		<< std::setfill('0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;
	return stream.str();
}

string pixelColor(int x, int y)
{
	HDC dc = GetDC(NULL);
	COLORREF color = GetPixel(dc, x, y);
	ReleaseDC(NULL, dc);


	string hex = int_to_hex(color);
	//cout << hex << endl;



	return hex;
}
void typeStr(string word, int sl = 0)
{
	for (int i = 0; i < word.length(); i++)
	{
		//find letter
		for (int l = 0; l < keys.size(); l++)
		{
			if (keys[l][0] == tolower(word[i]))
			{
				pressKey(keyCode[l]);
				if (sl > 0)
				{
					Sleep(sl);
				}
				break;
			}
		}
	}
}




string getWindowName(HWND win = GetForegroundWindow())
{

	int cTxtLen = 256;

	// Allocate memory for the string and copy
	// the string into the memory.

	LPWSTR pszMem = (LPWSTR)VirtualAlloc((LPVOID)NULL,
		(DWORD)(cTxtLen + 1), MEM_COMMIT,
		PAGE_READWRITE);
	GetWindowText(win, pszMem, cTxtLen + 1);

	int ad = GetWindowText(win, pszMem, cTxtLen);
	wstring ws(pszMem);
	string myVarS = string(ws.begin(), ws.end());
	if (win == GetDesktopWindow())
	{
		return "Desktop";
	}
	return myVarS;
}



//A version of typeStr() except works for any ASCII char but 70% slower
int sendStr(string msg)
{
	//std::string msg = "ABCD - abcd - 1234";

	std::vector<INPUT> vec;
	for (auto ch : msg)
	{
		INPUT input = { 0 };
		input.type = INPUT_KEYBOARD;
		input.ki.dwFlags = KEYEVENTF_UNICODE;
		input.ki.wScan = ch;
		vec.push_back(input);

		input.ki.dwFlags |= KEYEVENTF_KEYUP;
		vec.push_back(input);
	}



	return SendInput(vec.size(), vec.data(), sizeof(INPUT));
}
vector<int> getMouse()
{
	POINT p;;
	GetCursorPos(&p);
	return { p.x,p.y };
}

string cleanType(string str, string no)
{

	for (int i = 0; i < no.length(); i++)
	{
		int index = str.find(no[i]);
		while (index != string::npos)
		{
			str.replace(index, 1, "");
			index = str.find(no[i]);
		}
	}
	std::size_t doubleSpace = str.find("  ");
	while (doubleSpace != std::string::npos)
	{
		str.replace(doubleSpace, 1,"");
		doubleSpace = str.find("  ");
	}
	str.erase(0, 1);
	return str;
}

////////////////////////////////////////
