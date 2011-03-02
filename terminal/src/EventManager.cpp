#include <SFML/Graphics.hpp>
#include <cstring>
#include "EventManager.hpp"
#include "Constants.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        EventManager::EventManager(INetwork* network, SfmlRenderer& renderer) :
            _network(network), _renderer(renderer), _mouseX(0), _lastMouseX(0), _mouseY(0), _lastMouseY(0), _lastTime(0)
        {
            // keyboard mapping
            this->_keyboard[sf::Key::A] = Key::A;
            this->_keyboard[sf::Key::B] = Key::B;
            this->_keyboard[sf::Key::C] = Key::C;
            this->_keyboard[sf::Key::D] = Key::D;
            this->_keyboard[sf::Key::E] = Key::E;
            this->_keyboard[sf::Key::F] = Key::F;
            this->_keyboard[sf::Key::G] = Key::G;
            this->_keyboard[sf::Key::H] = Key::H;
            this->_keyboard[sf::Key::I] = Key::I;
            this->_keyboard[sf::Key::J] = Key::J;
            this->_keyboard[sf::Key::K] = Key::K;
            this->_keyboard[sf::Key::L] = Key::L;
            this->_keyboard[sf::Key::M] = Key::M;
            this->_keyboard[sf::Key::N] = Key::N;
            this->_keyboard[sf::Key::O] = Key::O;
            this->_keyboard[sf::Key::P] = Key::P;
            this->_keyboard[sf::Key::Q] = Key::Q;
            this->_keyboard[sf::Key::R] = Key::R;
            this->_keyboard[sf::Key::S] = Key::S;
            this->_keyboard[sf::Key::T] = Key::T;
            this->_keyboard[sf::Key::U] = Key::U;
            this->_keyboard[sf::Key::V] = Key::V;
            this->_keyboard[sf::Key::W] = Key::W;
            this->_keyboard[sf::Key::X] = Key::X;
            this->_keyboard[sf::Key::Y] = Key::Y;
            this->_keyboard[sf::Key::Z] = Key::Z;
            this->_keyboard[sf::Key::Num0] = Key::Num0;
            this->_keyboard[sf::Key::Num1] = Key::Num1;
            this->_keyboard[sf::Key::Num2] = Key::Num2;
            this->_keyboard[sf::Key::Num3] = Key::Num3;
            this->_keyboard[sf::Key::Num4] = Key::Num4;
            this->_keyboard[sf::Key::Num5] = Key::Num5;
            this->_keyboard[sf::Key::Num6] = Key::Num6;
            this->_keyboard[sf::Key::Num7] = Key::Num7;
            this->_keyboard[sf::Key::Num8] = Key::Num8;
            this->_keyboard[sf::Key::Num9] = Key::Num9;
            this->_keyboard[sf::Key::Escape] = Key::Escape;
            this->_keyboard[sf::Key::LControl] = Key::LControl;
            this->_keyboard[sf::Key::LShift] = Key::LShift;
            this->_keyboard[sf::Key::LAlt] = Key::LAlt;
            this->_keyboard[sf::Key::LSystem] = Key::LSystem;
            this->_keyboard[sf::Key::RControl] = Key::RControl;
            this->_keyboard[sf::Key::RShift] = Key::RShift;
            this->_keyboard[sf::Key::RAlt] = Key::RAlt;
            this->_keyboard[sf::Key::RSystem] = Key::RSystem;
            this->_keyboard[sf::Key::Menu] = Key::Menu;
            this->_keyboard[sf::Key::LBracket] = Key::LBracket;
            this->_keyboard[sf::Key::RBracket] = Key::RBracket;
            this->_keyboard[sf::Key::SemiColon] = Key::SemiColon;
            this->_keyboard[sf::Key::Comma] = Key::Comma;
            this->_keyboard[sf::Key::Period] = Key::Period;
            this->_keyboard[sf::Key::Quote] = Key::Quote;
            this->_keyboard[sf::Key::Slash] = Key::Slash;
            this->_keyboard[sf::Key::BackSlash] = Key::BackSlash;
            this->_keyboard[sf::Key::Tilde] = Key::Tilde;
            this->_keyboard[sf::Key::Equal] = Key::Equal;
            this->_keyboard[sf::Key::Dash] = Key::Dash;
            this->_keyboard[sf::Key::Space] = Key::Space;
            this->_keyboard[sf::Key::Return] = Key::Return;
            this->_keyboard[sf::Key::Back] = Key::Back;
            this->_keyboard[sf::Key::Tab] = Key::Tab;
            this->_keyboard[sf::Key::PageUp] = Key::PageUp;
            this->_keyboard[sf::Key::PageDown] = Key::PageDown;
            this->_keyboard[sf::Key::End] = Key::End;
            this->_keyboard[sf::Key::Home] = Key::Home;
            this->_keyboard[sf::Key::Insert] = Key::Insert;
            this->_keyboard[sf::Key::Delete] = Key::Delete;
            this->_keyboard[sf::Key::Add] = Key::Add;
            this->_keyboard[sf::Key::Subtract] = Key::Subtract;
            this->_keyboard[sf::Key::Multiply] = Key::Multiply;
            this->_keyboard[sf::Key::Divide] = Key::Divide;
            this->_keyboard[sf::Key::Left] = Key::Left;
            this->_keyboard[sf::Key::Right] = Key::Right;
            this->_keyboard[sf::Key::Up] = Key::Up;
            this->_keyboard[sf::Key::Down] = Key::Down;
            this->_keyboard[sf::Key::Numpad0] = Key::Numpad0;
            this->_keyboard[sf::Key::Numpad1] = Key::Numpad1;
            this->_keyboard[sf::Key::Numpad2] = Key::Numpad2;
            this->_keyboard[sf::Key::Numpad3] = Key::Numpad3;
            this->_keyboard[sf::Key::Numpad4] = Key::Numpad4;
            this->_keyboard[sf::Key::Numpad5] = Key::Numpad5;
            this->_keyboard[sf::Key::Numpad6] = Key::Numpad6;
            this->_keyboard[sf::Key::Numpad7] = Key::Numpad7;
            this->_keyboard[sf::Key::Numpad8] = Key::Numpad8;
            this->_keyboard[sf::Key::Numpad9] = Key::Numpad9;
            this->_keyboard[sf::Key::F1] = Key::F1;
            this->_keyboard[sf::Key::F2] = Key::F2;
            this->_keyboard[sf::Key::F3] = Key::F3;
            this->_keyboard[sf::Key::F4] = Key::F4;
            this->_keyboard[sf::Key::F5] = Key::F5;
            this->_keyboard[sf::Key::F6] = Key::F6;
            this->_keyboard[sf::Key::F7] = Key::F7;
            this->_keyboard[sf::Key::F8] = Key::F8;
            this->_keyboard[sf::Key::F9] = Key::F9;
            this->_keyboard[sf::Key::F10] = Key::F10;
            this->_keyboard[sf::Key::F11] = Key::F11;
            this->_keyboard[sf::Key::F12] = Key::F12;
            this->_keyboard[sf::Key::F13] = Key::F13;
            this->_keyboard[sf::Key::F14] = Key::F14;
            this->_keyboard[sf::Key::F15] = Key::F15;
            this->_keyboard[sf::Key::Pause] = Key::Pause;
            // initial keyboard status
            for (size_t i = 0; i < sf::Key::Count; ++i)
                this->_keyStatus[i] = false;
            // mouse mapping
            this->_mouse[sf::Mouse::Left] = Mouse::Left;
            this->_mouse[sf::Mouse::Right] = Mouse::Right;
            this->_mouse[sf::Mouse::Middle] = Mouse::Middle;
            this->_mouse[sf::Mouse::XButton1] = Mouse::Button4;
            this->_mouse[sf::Mouse::XButton2] = Mouse::Button5;
            this->_mouse[-1] = Mouse::Movement;
        }

        EventManager::~EventManager()
        {
        }

        int EventManager::_KeyboardToNet(int code)
        {
            if (this->_keyboard.count(code) == 1)
                return this->_keyboard[code];
            return 0;
        }

        int EventManager::_MouseToNet(int code)
        {
            if (this->_mouse.count(code) == 1)
                return this->_mouse[code];
            return 0;
        }

        void EventManager::_SendPacket(int code)
        {
            Packet p;
            p.Write8(Packet::IN_GAME);
            p.Write16(this->_network->GetClientId());
            p.Write32(code);
            this->_network->SendTcpPacket(p);
        }

        void EventManager::_HandleJoyEvent(int type, int code)
        {
            Log::E("Sending joystick event: " + String(code) + " " + (type == sf::Event::JoyButtonPressed ? "pressed" : "released") + ".");
            uint32_t event = 7000 + code; // joystick value 7000 + button (RFC)
            if (type == sf::Event::JoyButtonPressed)
                event |= INPUT_ACTION;
            this->_SendPacket(event);
        }

        void EventManager::_SendJoyMoveEvent(int code, bool pressed)
        {
            Log::D("Sending joystick event: " + String(code - 7000) + ".");
            if (pressed)
                code |= INPUT_ACTION;
            this->_SendPacket(code);
        }

        void EventManager::_HandleJoyMoveEvent(int axis, float pos)
        {
            if (axis != sf::Joy::AxisX && axis != sf::Joy::AxisY)
                return;
            if (axis == sf::Joy::AxisX)
            {
                this->_joyAxis[0] = axis == sf::Joy::AxisX && pos <= -60; // Left
                this->_joyAxis[1] = axis == sf::Joy::AxisX && pos >= 60;  // Right
            }
            else if (axis == sf::Joy::AxisY)
            {
                this->_joyAxis[2] = axis == sf::Joy::AxisY && pos <= -60; // Up
                this->_joyAxis[3] = axis == sf::Joy::AxisY && pos >= 60;  // Down
            }
        }

        void EventManager::_DoJoyMoveEvent(void)
        {
            if (this->_joyAxis[0] != this->_lastJoyAxis[0])
                this->_SendJoyMoveEvent(Key::Joy15, this->_joyAxis[0]);
            if (this->_joyAxis[1] != this->_lastJoyAxis[1])
                this->_SendJoyMoveEvent(Key::Joy13, this->_joyAxis[1]);
            if (this->_joyAxis[2] != this->_lastJoyAxis[2])
                this->_SendJoyMoveEvent(Key::Joy12, this->_joyAxis[2]);
            if (this->_joyAxis[3] != this->_lastJoyAxis[3])
                this->_SendJoyMoveEvent(Key::Joy14, this->_joyAxis[3]);
        }

        void EventManager::_HandleKeyboardEvent(int type, int code)
        {
            if (type == sf::Event::KeyPressed && this->_keyStatus[code])
                return;
            this->_keyStatus[code] = (type == sf::Event::KeyPressed);
            if (code == sf::Key::F12 && type == sf::Event::KeyPressed)
                this->_renderer.EnableInfo();
            code = this->_KeyboardToNet(code);
            Log::D("Sending key event: " + String(code) + " " + (type == sf::Event::KeyPressed ? "pressed" : "released") + ".");
            uint32_t event = code;
            if (type == sf::Event::KeyPressed)
                event |= INPUT_ACTION;
            this->_SendPacket(event);
        }

        void EventManager::_HandleMouseEvent(int type, int code)
        {
            code = this->_MouseToNet(code);
            Log::D("Sending mouse event: " + String(code) + " " + (type == sf::Event::MouseButtonPressed ? "pressed" : "released") + ".");
            uint32_t event = code << 24;
            event |= INPUT_DEVICE;
            if (type == sf::Event::MouseButtonPressed)
                event |= INPUT_ACTION;
            event |= (static_cast<int>(this->_mouseX) << 12) & X_COORD;
            event |= static_cast<int>(this->_mouseY) & Y_COORD;
            this->_SendPacket(event);
        }

        void EventManager::ProcessEvents(sf::RenderWindow* app, float time)
        {
            sf::Vector2f mousePos = app->ConvertCoords(app->GetInput().GetMouseX(), app->GetInput().GetMouseY());
            this->_mouseX = mousePos.x;
            this->_mouseY = mousePos.y;
            sf::Event event;
            ::memcpy(this->_lastJoyAxis, this->_joyAxis, sizeof(this->_joyAxis));
            while (app->GetEvent(event))
            {
                if (event.Type == sf::Event::Closed)
                    app->Close();
                else if (event.Type == sf::Event::KeyPressed || event.Type == sf::Event::KeyReleased)
                    this->_HandleKeyboardEvent(event.Type, event.Key.Code);
                else if (event.Type == sf::Event::MouseButtonPressed || event.Type == sf::Event::MouseButtonReleased)
                    this->_HandleMouseEvent(event.Type, event.MouseButton.Button);
                else if (event.Type == sf::Event::JoyMoved)
                    this->_HandleJoyMoveEvent(event.JoyMove.Axis, event.JoyMove.Position);
                else if (event.Type == sf::Event::JoyButtonPressed || event.Type == sf::Event::JoyButtonReleased)
                    this->_HandleJoyEvent(event.Type, event.JoyButton.Button);
            }
            this->_DoJoyMoveEvent();
            // Updates mouse position every 80 ms if changed, or every 1 sec
            if ((time - this->_lastTime > 0.08 && (this->_mouseX != this->_lastMouseX || this->_mouseY != this->_lastMouseY)) ||
                time - this->_lastTime > 1.0)
            {
                this->_HandleMouseEvent(sf::Event::MouseButtonReleased, -1);
                this->_lastTime = time;
            }
            this->_lastMouseX = this->_mouseX;
            this->_lastMouseY = this->_mouseY;
        }

        float EventManager::GetMouseX() const
        {
            return this->_mouseX;
        }

        float EventManager::GetMouseY() const
        {
            return this->_mouseY;
        }

    }
}

