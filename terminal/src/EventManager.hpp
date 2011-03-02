#ifndef __EVENTMANAGER_HPP__
#define __EVENTMANAGER_HPP__

#include <SFML/Graphics.hpp>
#include "INetwork.hpp"
#include "SfmlRenderer.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class EventManager :
            private sf::NonCopyable
        {
        public:
            explicit EventManager(INetwork* network, SfmlRenderer& renderer);
            ~EventManager();
            void ProcessEvents(sf::RenderWindow* app, float time);
            float GetMouseX() const;
            float GetMouseY() const;
        private:
            void _SendPacket(int code);
            void _HandleKeyboardEvent(int type, int code);
            void _HandleMouseEvent(int type, int code);
            void _HandleJoyEvent(int type, int code);
            void _HandleJoyMoveEvent(int axis, float pos);
            void _DoJoyMoveEvent(void);
            void _SendJoyMoveEvent(int code, bool pressed);
            int _KeyboardToNet(int code);
            int _MouseToNet(int code);
            INetwork* _network;
            SfmlRenderer& _renderer;
            float _mouseX;
            float _lastMouseX;
            float _mouseY;
            float _lastMouseY;
            std::map<int, int> _keyboard;
            std::map<int, int> _mouse;
            bool _keyStatus[sf::Key::Count];
            float _lastTime;
            bool _joyAxis[4];
            bool _lastJoyAxis[4];
        };

    }
}

#endif

