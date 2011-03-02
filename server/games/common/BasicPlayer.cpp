#include "BasicPlayer.hpp"
#include "Log.hpp"
#include "Packet.hpp"

namespace Gmgp
{
    namespace Server
    {

        BasicPlayer::BasicPlayer(uint16_t id,
                                 String const& nick,
                                 ITcpSocketProxy* socketProxy,
                                 IGame& game) :
            _id(id), _nick(nick), _mouseX(0), _mouseY(0), _disabled(false),
            _socketProxy(socketProxy), _game(game), _pingLife(10),
            _needToUnregister(false)
        {
            for (size_t i = 0; i < MAX_KEYS; ++i)
            {
                this->_keys[i] = -1;
                this->_keyClicks[i] = -1;
                this->_keyReleases[i] = -1;
            }
            for (size_t i = 0; i < MAX_BUTTONS; ++i)
            {
                this->_buttons[i] = -1;
                this->_buttonClicks[i] = -1;
                this->_buttonReleases[i] = -1;
            }

            this->_handlers[Packet::IN_GAME] = &BasicPlayer::_InGameHandler;
            this->_handlers[Packet::PING] = &BasicPlayer::_PingHandler;
            this->_handlers[Packet::PONG] = &BasicPlayer::_PongHandler;

            this->_game.GetService().RegisterTcpSocket(this->_socketProxy,
                                              b00st::bind(&BasicPlayer::_ReadHandler, *this));
            this->_needToUnregister = true;
        }

        BasicPlayer::~BasicPlayer()
        {
            if (this->_needToUnregister)
                this->_game.GetService().UnregisterTcpSocket(this->_socketProxy);
        }

        void BasicPlayer::DisableItems(bool enable)
        {
            this->_disabled = enable;
        }

        bool BasicPlayer::IsDisabled() const
        {
            return this->_disabled;
        }

        uint16_t BasicPlayer::GetId() const
        {
            return this->_id;
        }

        String const& BasicPlayer::GetNick() const
        {
            return this->_nick;
        }

        void BasicPlayer::EventOnPressedKey(int key)
        {
            if (this->KeyPressed(static_cast<Key::Key>(key)))
                return;
            for (size_t i = 0; i < MAX_KEYS; ++i)
                if (this->_keyClicks[i] == -1)
                {
                    this->_keyClicks[i] = key;
                    break;
                }
            for (size_t i = 0; i < MAX_KEYS; ++i)
                if (this->_keys[i] == -1)
                {
                    this->_keys[i] = key;
                    break;
                }
        }

        void BasicPlayer::EventOnReleasedKey(int key)
        {
            if (this->KeyPressed(static_cast<Key::Key>(key)))
                for (size_t i = 0; i < MAX_KEYS; ++i)
                    if (this->_keyReleases[i] == -1)
                    {
                        this->_keyReleases[i] = key;
                        break;
                    }
            for (size_t i = 0; i < MAX_KEYS; ++i)
                if (this->_keys[i] == key)
                    this->_keys[i] = -1;
        }

        void BasicPlayer::EventOnPressedButton(int button, size_t x, size_t y)
        {
            this->_mouseX = x;
            this->_mouseY = y;
            if (this->ButtonPressed(static_cast<Mouse::Mouse>(button)))
                return;
            for (size_t i = 0; i < MAX_BUTTONS; ++i)
                if (this->_buttonClicks[i] == -1)
                {
                    this->_buttonClicks[i] = button;
                    break;
                }
            for (size_t i = 0; i < MAX_BUTTONS; ++i)
                if (this->_buttons[i] == -1)
                {
                    this->_buttons[i] = button;
                    break;
                }
        }

        void BasicPlayer::EventOnReleasedButton(int button, size_t x, size_t y)
        {
            if (this->ButtonPressed(static_cast<Mouse::Mouse>(button)))
                for (size_t i = 0; i < MAX_BUTTONS; ++i)
                    if (this->_buttonReleases[i] == -1)
                    {
                        this->_buttonReleases[i] = button;
                        break;
                    }
            for (size_t i = 0; i < MAX_BUTTONS; ++i)
                if (this->_buttons[i] == button)
                    this->_buttons[i] = -1;
            this->_mouseX = x;
            this->_mouseY = y;
        }

        void BasicPlayer::ResetClicks()
        {
            for (size_t i = 0; i < MAX_KEYS; ++i)
            {
                this->_keyClicks[i] = -1;
                this->_keyReleases[i] = -1;
            }
            for (size_t i = 0; i < MAX_BUTTONS; ++i)
            {
                this->_buttonClicks[i] = -1;
                this->_buttonReleases[i] = -1;
            }
        }

        bool BasicPlayer::KeyPressed(Gmgp::Key::Key key) const
        {
            for (size_t i = 0; i < MAX_KEYS; ++i)
                if (this->_keys[i] == key)
                    return true;
            return false;
        }

        bool BasicPlayer::KeyClicked(Gmgp::Key::Key key) const
        {
            for (size_t i = 0; i < MAX_KEYS; ++i)
                if (this->_keyClicks[i] == key)
                    return true;
            return false;
        }

        bool BasicPlayer::KeyReleased(Gmgp::Key::Key key) const
        {
            for (size_t i = 0; i < MAX_KEYS; ++i)
                if (this->_keyReleases[i] == key)
                    return true;
            return false;
        }

        bool BasicPlayer::ButtonPressed(Gmgp::Mouse::Mouse button) const
        {
            for (size_t i = 0; i < MAX_BUTTONS; ++i)
                if (this->_buttons[i] == button)
                    return true;
            return false;
        }

        bool BasicPlayer::ButtonClicked(Gmgp::Mouse::Mouse button) const
        {
            for (size_t i = 0; i < MAX_BUTTONS; ++i)
                if (this->_buttonClicks[i] == button)
                    return true;
            return false;
        }

        bool BasicPlayer::ButtonReleased(Gmgp::Mouse::Mouse button) const
        {
            for (size_t i = 0; i < MAX_BUTTONS; ++i)
                if (this->_buttonReleases[i] == button)
                    return true;
            return false;
        }

        size_t BasicPlayer::GetMouseX() const
        {
            return this->_mouseX;
        }

        size_t BasicPlayer::GetMouseY() const
        {
            return this->_mouseY;
        }

        ITcpSocketProxy* BasicPlayer::GetSocketProxy(void)
        {
            return this->_socketProxy;
        }

        void BasicPlayer::SendPacket(Packet const& packet)
        {
            this->_socketProxy->Send(packet);
        }

        bool BasicPlayer::Ping(void)
        {
            if (--this->_pingLife == 0)
                return false;
            Packet p;
            p.Write8(Packet::PING);
            p.WriteString("Y A L A P _ A");
            this->SendPacket(p);
            return true;
        }

        bool BasicPlayer::_ReadHandler(int errorCode, char* data, size_t len)
        {
            if (errorCode == -1)
            {
                delete this->_socketProxy;
                this->_disabled = true;
                this->_needToUnregister = false;
                this->_game.RemovePlayer(this->_id);
                return true;
            }
            this->_socketProxy->pc_PushRawData(data, len);
            Packet* packet;
            while ((packet = this->_socketProxy->pc_GetPacket()) != 0)
            {
                if (this->_ParsePacket(*packet))
                {
                    delete packet;
                    delete this->_socketProxy;
                    this->_needToUnregister = false;
                    this->_game.RemovePlayer(this->_id);
                    return true;
                }
                delete packet;
            }
            return false;
        }

        bool BasicPlayer::_ParsePacket(Packet& packet)
        {
            try
            {
                uint8_t type = packet.Read8();
                if (this->_handlers.find(type) == this->_handlers.end())
                {
                    Log::I("Unknown packet type : Client out !");
                    packet.Dump();
                    return true;
                }
                return (this->*this->_handlers[type])(packet);
            }
            catch (std::exception&)
            {
                Log::I("Someone sent a wrong packet : out !");
                packet.Dump();
                return true;
            }
            return false;
        }

        bool BasicPlayer::_InGameHandler(Packet& packet)
        {
            packet.Read16(); // playerId
            uint32_t event = packet.Read32();
            if ((event & EVENT_TYPE) == INPUT)
            {
                if ((event & INPUT_DEVICE) == KEYBOARD)
                {
                    if ((event & INPUT_ACTION) == RELEASED)
                        this->EventOnReleasedKey(EVENT_KEYVALUE(event));
                    else
                        this->EventOnPressedKey(EVENT_KEYVALUE(event));
                }
                else
                {
                    if ((event & INPUT_ACTION) == RELEASED)
                        this->EventOnReleasedButton(EVENT_BUTTONVALUE(event), EVENT_XCOORD(event), EVENT_YCOORD(event));
                    else
                        this->EventOnPressedButton(EVENT_BUTTONVALUE(event), EVENT_XCOORD(event), EVENT_YCOORD(event));
                }
            }
            return false;
        }

        bool BasicPlayer::_PingHandler(Packet& packet)
        {
            Packet packet2;
            packet2.Write8(Packet::PONG);
            packet2.WriteString(packet.ReadString());
            this->SendPacket(packet2);
            return false;
        }

        bool BasicPlayer::_PongHandler(Packet&)
        {
            this->_pingLife = 10;
            return false;
        }

    }
}

