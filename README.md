# CppWindowsUntil
A small collection of functions and libraries I use.

## Docs:

### string exec(const char* cmd);

Gets the output from a system command
```cpp
string out = exec("Time /T");
std::cout << out << endl;
```
output: `"12:34 AM"`

### void pressKey(int key);

Simulates a keypress, key is a windows c++ key code [(Win docs)](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)
```cpp
pressKey(VK_TAB);
```
output: presses the tab key


### string readCoord(int x1, int y1, int x2, int y2);
Reads words from the screen using tesseract! (You must change the code in the function to point to the tesseract exe/project folder)
```cpp
string out = readCoord(0,0,1920,1080);
std::cout << out << endl;
```
output: uses ai to read the screen and prints it out


### string int_to_hex(<type> i);

converts a number to a hex string
```cpp
string a = int_to_hex(45);
std::cout << a << endl;
```
output: `0x00002d`

### string pixelColor(int x, int y);

Gets a pixels color of the screen in hex format
```cpp
string pc = pixelColor(0,0);
std::cout << pc << endl;
```
output: `0x00000000`

### void typeStr(string word, int sl = 0);

uses the pressKey function to input characters of a string, the 2nd parameter is for delay between each press in ms.

can only type basic characters
```cpp
typeStr("Hello World!");
```
output: types "hello world ";

### string getWindowName(HWND win = GetForegroundWindow());

gets the window name of a certain HWND, defaults to currently focused window.
```cpp
string g = getWindowName();
std::cout << g << endl;
```
output: `Untitled - Notepad`

### int sendStr(string msg)

A version of typeStr() except works for any ASCII char but 70% slower

returns SendInput UINT callback
```cpp
int a = sendStr("Hello World!");
std::cout << a << endl;
```
output: types "Hello World!" then prints error code: `1`

### vector<int> getMouse()

returns an vector of size 2 with the x and y pos of the mouse
```cpp
vector<int> mousePos = getMouse();
std::cout << mousePos[0] << ", " << mousePos[1] << endl;
```
output `"35, 78"`

### string cleanType(string str, string no)

removes all occurances of no characters in str
```cpp
string str = "Hello World!";
str = cleanType(str,"Hl!");
std::cout << str << endl;
```

output: `"eo World"`
