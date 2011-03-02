#ifndef __BASICPLAYER_HPP__
#define __BASICPLAYER_HPP__

#include "String.hpp"
#include "NonCopyable.hpp"
#include "Constants.hpp"
#include "IGame.hpp"

namespace Gmgp
{
    namespace Server
    {

        class BasicPlayer : private b00st::NonCopyable
        {
        public:
            explicit BasicPlayer(uint16_t id,
                                 String const& nick,
                                 ITcpSocketProxy* socketProxy,
                                 IGame& game);
            virtual ~BasicPlayer();
            uint16_t GetId() const;
            String const& GetNick() const;
            void EventOnPressedKey(int key);
            void EventOnReleasedKey(int key);
            void EventOnPressedButton(int button, size_t x, size_t y);
            void EventOnReleasedButton(int button, size_t x, size_t y);
            void ResetClicks();
            bool KeyPressed(Gmgp::Key::Key key) const;
            bool KeyClicked(Gmgp::Key::Key key) const;
            bool KeyReleased(Gmgp::Key::Key key) const;
            bool ButtonPressed(Gmgp::Mouse::Mouse button) const;
            bool ButtonClicked(Gmgp::Mouse::Mouse button) const;
            bool ButtonReleased(Gmgp::Mouse::Mouse button) const;
            size_t GetMouseX() const;
            size_t GetMouseY() const;
            void DisableItems(bool enable);
            bool IsDisabled() const;

        private:
            enum
            {
                MAX_KEYS = 6,
                MAX_BUTTONS = 3
            };
            uint16_t _id;
            String _nick;
            int _keys[MAX_KEYS];
            int _keyClicks[MAX_KEYS];
            int _keyReleases[MAX_KEYS];
            int _buttons[MAX_BUTTONS];
            int _buttonClicks[MAX_BUTTONS];
            int _buttonReleases[MAX_BUTTONS];
            size_t _mouseX;
            size_t _mouseY;
            bool _disabled;

        public:
            ITcpSocketProxy* GetSocketProxy(void);
            void SendPacket(Packet const& packet);
            bool Ping(void);

        private:
            bool _ReadHandler(int errorCode, char* data, size_t len);
            bool _ParsePacket(Packet& packet);

            bool _InGameHandler(Packet& packet);
            bool _PingHandler(Packet& packet);
            bool _PongHandler(Packet& packet);
            std::map<uint8_t, bool (BasicPlayer::*)(Packet&)> _handlers;

            ITcpSocketProxy* _socketProxy;
            IGame& _game;

            size_t _pingLife;

            bool _needToUnregister;
        };

    }
}

#endif

