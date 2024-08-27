#pragma once
#include "ReckonCore.h"
#include <string>
#include "internal Dependencies/glfw3.h"
#include <vector>



enum class KeyCode
{
	Space,
	AposTrophe,
	Comma,
	Minus,
	Period,
	Slash,
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Semicolon,
	Equal,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	LeftBracket,
	RightBracket,
	BackSlash,
	GraveAccent,
	Escape,
	Enter,
	Tab,
	BackSpace,
	Insert,
	Delete,
	ArrowRight,
	ArrowLeft,
	ArrowDown,
	ArrowUp,
	PageUp,
	PageDown,
	Home,
	End,
	CapsLock,
	ScrollLock,
	NumLock,
	PrintScreen,
	Pause,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	F17,
	F18,
	F19,
	F20,
	F21,
	F22,
	F23,
	F24,
	F25,
	Numpad_1,
	Numpad_2,
	Numpad_3,
	Numpad_4,
	Numpad_5,
	Numpad_6,
	Numpad_7,
	Numpad_8,
	Numpad_9,
	Numpad_Decimal,
	Numpad_Divide,
	Numpad_Multiply,
	Numpad_Add,
	Numpad_Subtract,
	Numpad_Enter,
	Numpad_Equal

};



class RCK_API Input
{
public:
	Input();
	static bool GetKeyDown(KeyCode code);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	static bool KeysDown[350];

	static void KeyDown(int remappedIndex);
	static void KeyUp(int remappedIndex);
	
	static int MapKeyCodeToIndex(KeyCode code);


};