#include "Input.h"
#include <algorithm>
#include <iostream>

// Define the static member
bool Input::KeysDown[350] = { false };

Input::Input()
{
    std::fill(std::begin(KeysDown), std::end(KeysDown), false);
}

int Input::MapKeyCodeToIndex(KeyCode code)
{
    switch (code)
    {
    case KeyCode::Space:
        return GLFW_KEY_SPACE;
    case KeyCode::AposTrophe:
        return GLFW_KEY_APOSTROPHE;
    case KeyCode::Comma:
        return GLFW_KEY_COMMA;
    case KeyCode::Minus:
        return GLFW_KEY_MINUS;
    case KeyCode::Period:
        return GLFW_KEY_PERIOD;
    case KeyCode::Slash:
        return GLFW_KEY_SLASH;
    case KeyCode::Zero:
        return GLFW_KEY_0;
    case KeyCode::One:
        return GLFW_KEY_1;
    case KeyCode::Two:
        return GLFW_KEY_2;
    case KeyCode::Three:
        return GLFW_KEY_3;
    case KeyCode::Four:
        return GLFW_KEY_4;
    case KeyCode::Five:
        return GLFW_KEY_5;
    case KeyCode::Six:
        return GLFW_KEY_6;
    case KeyCode::Seven:
        return GLFW_KEY_7;
    case KeyCode::Eight:
        return GLFW_KEY_8;
    case KeyCode::Nine:
        return GLFW_KEY_9;
    case KeyCode::Semicolon:
        return GLFW_KEY_SEMICOLON;
    case KeyCode::Equal:
        return GLFW_KEY_EQUAL;
    case KeyCode::A:
        return GLFW_KEY_A;
    case KeyCode::B:
        return GLFW_KEY_B;
    case KeyCode::C:
        return GLFW_KEY_C;
    case KeyCode::D:
        return GLFW_KEY_D;
    case KeyCode::E:
        return GLFW_KEY_E;
    case KeyCode::F:
        return GLFW_KEY_F;
    case KeyCode::G:
        return GLFW_KEY_G;
    case KeyCode::H:
        return GLFW_KEY_H;
    case KeyCode::I:
        return GLFW_KEY_I;
    case KeyCode::J:
        return GLFW_KEY_J;
    case KeyCode::K:
        return GLFW_KEY_K;
    case KeyCode::L:
        return GLFW_KEY_L;
    case KeyCode::M:
        return GLFW_KEY_M;
    case KeyCode::N:
        return GLFW_KEY_N;
    case KeyCode::O:
        return GLFW_KEY_O;
    case KeyCode::P:
        return GLFW_KEY_P;
    case KeyCode::Q:
        return GLFW_KEY_Q;
    case KeyCode::R:
        return GLFW_KEY_R;
    case KeyCode::S:
        return GLFW_KEY_S;
    case KeyCode::T:
        return GLFW_KEY_T;
    case KeyCode::U:
        return GLFW_KEY_U;
    case KeyCode::V:
        return GLFW_KEY_V;
    case KeyCode::W:
        return GLFW_KEY_W;
    case KeyCode::X:
        return GLFW_KEY_X;
    case KeyCode::Y:
        return GLFW_KEY_Y;
    case KeyCode::Z:
        return GLFW_KEY_Z;
    case KeyCode::LeftBracket:
        return GLFW_KEY_LEFT_BRACKET;
    case KeyCode::RightBracket:
        return GLFW_KEY_RIGHT_BRACKET;
    case KeyCode::BackSlash:
        return GLFW_KEY_BACKSLASH;
    case KeyCode::GraveAccent:
        return GLFW_KEY_GRAVE_ACCENT;
    case KeyCode::Escape:
        return GLFW_KEY_ESCAPE;
    case KeyCode::Enter:
        return GLFW_KEY_ENTER;
    case KeyCode::Tab:
        return GLFW_KEY_TAB;
    case KeyCode::BackSpace:
        return GLFW_KEY_BACKSPACE;
    case KeyCode::Insert:
        return GLFW_KEY_INSERT;
    case KeyCode::Delete:
        return GLFW_KEY_DELETE;
    case KeyCode::ArrowRight:
        return GLFW_KEY_RIGHT;
    case KeyCode::ArrowLeft:
        return GLFW_KEY_LEFT;
    case KeyCode::ArrowDown:
        return GLFW_KEY_DOWN;
    case KeyCode::ArrowUp:
        return GLFW_KEY_UP;
    case KeyCode::PageUp:
        return GLFW_KEY_PAGE_UP;
    case KeyCode::PageDown:
        return GLFW_KEY_PAGE_DOWN;
    case KeyCode::Home:
        return GLFW_KEY_HOME;
    case KeyCode::End:
        return GLFW_KEY_END;
    case KeyCode::CapsLock:
        return GLFW_KEY_CAPS_LOCK;
    case KeyCode::ScrollLock:
        return GLFW_KEY_SCROLL_LOCK;
    case KeyCode::NumLock:
        return GLFW_KEY_NUM_LOCK;
    case KeyCode::PrintScreen:
        return GLFW_KEY_PRINT_SCREEN;
    case KeyCode::Pause:
        return GLFW_KEY_PAUSE;
    case KeyCode::F1:
        return GLFW_KEY_F1;
    case KeyCode::F2:
        return GLFW_KEY_F2;
    case KeyCode::F3:
        return GLFW_KEY_F3;
    case KeyCode::F4:
        return GLFW_KEY_F4;
    case KeyCode::F5:
        return GLFW_KEY_F5;
    case KeyCode::F6:
        return GLFW_KEY_F6;
    case KeyCode::F7:
        return GLFW_KEY_F7;
    case KeyCode::F8:
        return GLFW_KEY_F8;
    case KeyCode::F9:
        return GLFW_KEY_F9;
    case KeyCode::F10:
        return GLFW_KEY_F10;
    case KeyCode::F11:
        return GLFW_KEY_F11;
    case KeyCode::F12:
        return GLFW_KEY_F12;
    case KeyCode::F13:
        return GLFW_KEY_F13;
    case KeyCode::F14:
        return GLFW_KEY_F14;
    case KeyCode::F15:
        return GLFW_KEY_F15;
    case KeyCode::F16:
        return GLFW_KEY_F16;
    case KeyCode::F17:
        return GLFW_KEY_F17;
    case KeyCode::F18:
        return GLFW_KEY_F18;
    case KeyCode::F19:
        return GLFW_KEY_F19;
    case KeyCode::F20:
        return GLFW_KEY_F20;
    case KeyCode::F21:
        return GLFW_KEY_F21;
    case KeyCode::F22:
        return GLFW_KEY_F22;
    case KeyCode::F23:
        return GLFW_KEY_F23;
    case KeyCode::F24:
        return GLFW_KEY_F24;
    case KeyCode::F25:
        return GLFW_KEY_F25;
    case KeyCode::Numpad_1:
        return GLFW_KEY_KP_1;
    case KeyCode::Numpad_2:
        return GLFW_KEY_KP_2;
    case KeyCode::Numpad_3:
        return GLFW_KEY_KP_3;
    case KeyCode::Numpad_4:
        return GLFW_KEY_KP_4;
    case KeyCode::Numpad_5:
        return GLFW_KEY_KP_5;
    case KeyCode::Numpad_6:
        return GLFW_KEY_KP_6;
    case KeyCode::Numpad_7:
        return GLFW_KEY_KP_7;
    case KeyCode::Numpad_8:
        return GLFW_KEY_KP_8;
    case KeyCode::Numpad_9:
        return GLFW_KEY_KP_9;
    case KeyCode::Numpad_Decimal:
        return GLFW_KEY_KP_DECIMAL;
    case KeyCode::Numpad_Divide:
        return GLFW_KEY_KP_DIVIDE;
    case KeyCode::Numpad_Multiply:
        return GLFW_KEY_KP_MULTIPLY;
    case KeyCode::Numpad_Add:
        return GLFW_KEY_KP_ADD;
    case KeyCode::Numpad_Subtract:
        return GLFW_KEY_KP_SUBTRACT;
    case KeyCode::Numpad_Enter:
        return GLFW_KEY_KP_ENTER;
    case KeyCode::Numpad_Equal:
        return GLFW_KEY_KP_EQUAL;
    default:
        return -1; // Return an invalid value or handle it as needed
    }
}

void Input::KeyDown(int remappedIndex)
{
    if (remappedIndex >= 0 && remappedIndex < 350)
    {
        KeysDown[remappedIndex] = true;
    }
}

void Input::KeyUp(int remappedIndex)
{
    if (remappedIndex >= 0 && remappedIndex < 350)
    {
        KeysDown[remappedIndex] = false;
    }
}

bool Input::GetKeyDown(KeyCode code)
{
    return Input::KeysDown[MapKeyCodeToIndex(code)];
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    int remappedIndex = key;
    if (action == GLFW_PRESS)
    {
        Input::KeyDown(remappedIndex);
        std::cout << "Key Pressed: " << remappedIndex << " Value: " << KeysDown[remappedIndex] << std::endl;

    }
    else if (action == GLFW_RELEASE)
    {
        Input::KeyUp(remappedIndex);
        std::cout << "Key Released: " << remappedIndex << " Value: " << KeysDown[remappedIndex] << std::endl;
    }
}
