#include "SfmlRenderer.hpp"
#include "SfmlGameView.hpp"
#include "SpriteItem.hpp"
#include "SoundItem.hpp"
#include "Log.hpp"
#include "Constants.hpp"

#ifdef _WIN32
// Info: WINDOWS C'est de la merde (ou la SFML, on ne sait pas trop la)
namespace sf
{
    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    Uint32 Font::ourDefaultCharset[] =
    {
        // Printable characters in ASCII range
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E,

        // Printable characters in extended ASCII range
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0x2A, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
        0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
        0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
        0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
        0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE,

        // To make it a valid string
        0x00
    };
}
#endif

namespace Gmgp
{
    namespace Terminal
    {

        SfmlRenderer::SfmlRenderer(SfmlGameView& view) :
            _view(view), _width(320), _height(240), _infoEnabled(false), _fpsInfo(0), _recvPacketInfo(0), _lastNetUpdate(0), _recvTotalPackets(0), _recvTotalBytes(0)
        {
            this->_layers.resize(257); // 256 +1 for sounds
            this->_font.LoadFromFile("Vera.ttf", 12);
        }

        SfmlRenderer::~SfmlRenderer()
        {
            std::map<size_t, IItem*>::iterator it = this->_items.begin();
            std::map<size_t, IItem*>::iterator itEnd = this->_items.end();
            for (; it != itEnd; ++it)
                delete it->second;
        }

        void SfmlRenderer::SetRecvPacketInfo(size_t nb, size_t bytes)
        {
            this->_recvPacketInfo = nb;
            this->_recvTotalPackets += nb;
            this->_recvBytesInfo = bytes;
            this->_recvTotalBytes += bytes;
        }

        void SfmlRenderer::SetFrameRateInfo(float fps)
        {
            this->_fpsInfo = fps;
        }

        void SfmlRenderer::SetSize(size_t width, size_t height)
        {
            this->_width = width;
            this->_height = height;
        }

        size_t SfmlRenderer::GetWidth() const
        {
            return this->_width;
        }

        size_t SfmlRenderer::GetHeight() const
        {
            return this->_height;
        }

        void SfmlRenderer::SetMousePos(float x, float y)
        {
            this->_mouseX = x;
            this->_mouseY = y;
        }

        float SfmlRenderer::GetMouseX() const
        {
            return this->_mouseX;
        }

        float SfmlRenderer::GetMouseY() const
        {
            return this->_mouseY;
        }

        void SfmlRenderer::EnableInfo()
        {
            this->_infoEnabled = !this->_infoEnabled;
        }

        void SfmlRenderer::Render(sf::RenderWindow* app, float time)
        {
            std::vector< std::list<IItem*> >::iterator it = this->_layers.begin();
            std::vector< std::list<IItem*> >::iterator itEnd = this->_layers.end();
            for (; it != itEnd; ++it)
            {
                std::list<IItem*>::iterator itItem = it->begin();
                std::list<IItem*>::iterator itItemEnd = it->end();
                for (; itItem != itItemEnd; ++itItem)
                    (*itItem)->Render(app, time);
            }
            if (this->_infoEnabled)
                this->_ShowInfos(app, time);
            this->_ProcessKillPool();
        }

        void SfmlRenderer::_ShowInfos(sf::RenderWindow* app, float time)
        {
            sf::Shape bg = sf::Shape::Rectangle(0, 0, 185, 40, sf::Color(0, 0, 0, 100));
            app->Draw(bg);
            sf::String fps(String(this->_fpsInfo) + " avg FPS", this->_font);
            fps.SetSize(12);
            fps.Move(0, 0);
            app->Draw(fps);
            sf::String items(String(this->_items.size()) + " items", this->_font);
            items.SetSize(12);
            items.Move(0, 12);
            app->Draw(items);
            if (time - this->_lastNetUpdate >= 1)
            {
                this->_recvNetText = String(this->_recvTotalBytes) + "B/s, " + String(this->_recvTotalPackets) + "p/s";
                this->_recvTotalPackets = 0;
                this->_recvTotalBytes = 0;
                this->_lastNetUpdate = time;
            }
            sf::String recv(this->_recvNetText + " (" + String(this->_recvBytesInfo) + "B, " + String(this->_recvPacketInfo) + "p)", this->_font);
            recv.SetSize(12);
            recv.Move(0, 24);
            app->Draw(recv);
        }

        void SfmlRenderer::AddItem(IItem* item, size_t pos)
        {
            this->_layers[pos].push_back(item);
        }

        void SfmlRenderer::RemoveItem(IItem* item, size_t pos)
        {
            this->_layers[pos].remove(item);
        }

        void SfmlRenderer::DeleteItem(IItem* item)
        {
            std::list<IItem*>::iterator it = this->_killPool.begin();
            std::list<IItem*>::iterator itEnd = this->_killPool.end();
            for (; it != itEnd; ++it)
                if (*it == item)
                    return; // item already in kill pool
            this->_killPool.push_back(item);
        }

        void SfmlRenderer::_ProcessKillPool()
        {
            std::list<IItem*>::iterator it = this->_killPool.begin();
            std::list<IItem*>::iterator itEnd = this->_killPool.end();
            for (; it != itEnd; ++it)
            {
                std::map<size_t, IItem*>::iterator itItem = this->_items.begin();
                std::map<size_t, IItem*>::iterator itItemEnd = this->_items.end();
                while (itItem != itItemEnd)
                    if (itItem->second == *it)
                    {
                        Log::D("Destroying item " + String(itItem->first) + ".");
                        this->_items.erase(itItem++);
                    }
                    else
                        ++itItem;
                std::vector< std::list<IItem*> >::iterator itLayer = this->_layers.begin();
                std::vector< std::list<IItem*> >::iterator itLayerEnd = this->_layers.end();
                for (; itLayer != itLayerEnd; ++itLayer)
                    itLayer->remove(*it);
                delete *it;
            }
            this->_killPool.clear();
        }

        void SfmlRenderer::ProcessPacket(Packet const& p)
        {
            try
            {
                p.Read32(); // server time
                while (p.BytesLeft())
                {
                    // params declaration
                    size_t resourceId = 0;
                    float posX = 0;
                    float posY = 0;
                    float speedX = 0;
                    float speedY = 0;
                    float accelX = 0;
                    float accelY = 0;
                    size_t lifeTimeMs = 0;
                    size_t lifeTimeCycles = 0;
                    bool disapear = false;
                    size_t posZ = 0;
                    size_t blinking = 0;
                    bool cursor = false;
                    bool response = false;
                    size_t frame = 0;
                    size_t luaId = 0;

                    // packet header
                    size_t nbItems = p.Read8();
                    if (nbItems == 0)
                        this->_RemoveAllItems();
                    std::list<size_t> ids;
                    for (size_t i = 0; i < nbItems; ++i)
                        ids.push_back(p.Read32());

                    if (ids.size() > 0)
                    {
                        uint16_t mask = p.Read16();

                        // params of packet
                        if (mask & RESOURCE_ID)
                            resourceId = p.Read16();
                        if (mask & X_POS)
                            posX = p.ReadFloat();
                        if (mask & Y_POS)
                            posY = p.ReadFloat();
                        if (mask & X_SPEED)
                            speedX = p.ReadFloat();
                        if (mask & Y_SPEED)
                            speedY = p.ReadFloat();
                        if (mask & X_ACCEL)
                            accelX = p.ReadFloat();
                        if (mask & Y_ACCEL)
                            accelY = p.ReadFloat();
                        if (mask & LIFE_TIME_MS)
                            lifeTimeMs = p.Read16();
                        if (mask & LIFE_TIME_CYCLES)
                            lifeTimeCycles = p.Read8();
                        if (mask & DISAPEAR)
                            disapear = true;
                        if (mask & Z_POS)
                            posZ = p.Read8();
                        if (mask & BLINKING)
                            blinking = p.Read16();
                        if (mask & CURSOR)
                            cursor = true;
                        if (mask & RESPONSE)
                            response = true;
                        if (mask & FRAME)
                            frame = p.Read16();
                        if (mask & LUA_ID)
                            luaId = p.Read16();

                        // item update
                        std::list<size_t>::iterator it = ids.begin();
                        std::list<size_t>::iterator itEnd = ids.end();
                        for (; it != itEnd; ++it)
                        {
                            if (mask == 0) // item deletion
                            {
                                if (this->_items.count(*it) == 1)
                                {
                                    this->DeleteItem(this->_items[*it]);
                                    //Log::D("Deletion order for item " + String(*it) + ".");
                                }
                                else
                                    Log::W("Received deletion order for an unknown item.");
                            }
                            else
                            {
                                // gets the item or creates it
                                bool itemCreated = false;
                                IItem* target;
                                if (this->_items.count(*it) == 1)
                                    target = this->_items[*it];
                                else
                                {
                                    if (mask & RESOURCE_ID)
                                    {
                                        itemCreated = true;
                                        if (this->_view.GetAnimation(resourceId) != 0)
                                        {
                                            target = new SpriteItem(*it, resourceId, this->_view, *this);
                                            this->_items[*it] = target;
                                            //Log::D("New item " + String(*it) + " (image).");
                                        }
                                        else if (this->_view.GetSound(resourceId) != 0)
                                        {
                                            target = new SoundItem(resourceId, this->_view, *this);
                                            this->_items[*it] = target;
                                            //Log::D("New item " + String(*it) + " (sound).");
                                        }
                                        else
                                        {
                                            Log::W("Received a new item with an invalid resource ID.");
                                            continue;
                                        }
                                    }
                                    else
                                    {
                                        Log::W("Received a new item with no resource ID.");
                                        continue;
                                    }
                                }
                                // item params update
                                if (mask & RESOURCE_ID && !itemCreated)
                                    target->SetResourceId(resourceId);
                                if (mask & X_POS)
                                    target->SetPositionX(posX);
                                if (mask & Y_POS)
                                    target->SetPositionY(posY);
                                if (mask & X_SPEED)
                                    target->SetSpeedX(speedX);
                                if (mask & Y_SPEED)
                                    target->SetSpeedY(speedY);
                                if (mask & X_ACCEL)
                                    target->SetAccelX(accelX);
                                if (mask & Y_ACCEL)
                                    target->SetAccelY(accelY);
                                if (mask & LIFE_TIME_MS)
                                    target->SetLifeTimeMs(lifeTimeMs);
                                if (mask & LIFE_TIME_CYCLES)
                                    target->SetLifeTimeCycles(lifeTimeCycles);
                                target->SetDisapear(disapear);
                                if (mask & Z_POS)
                                    target->SetPositionZ(posZ);
                                if (mask & BLINKING)
                                    target->SetBlinking(blinking);
                                target->SetCursor(cursor);
                                if (response)
                                    this->_view.ConfirmItem(*it);
                                if (mask & FRAME)
                                    target->SetFrame(frame);
                                if (mask & LUA_ID)
                                    target->SetLuaId(luaId);
                                //Log::D("Item " + String(*it) + " updated.");
                            }
                        }
                    }
                }
            }
            catch (std::exception& e)
            {
                Log::W("Malformed IN_GAME packet: " + String(e.what()) + ".");
            }
        }

        void SfmlRenderer::_RemoveAllItems()
        {
            Log::D("Removing all items!");
            std::map<size_t, IItem*>::iterator it = this->_items.begin();
            std::map<size_t, IItem*>::iterator itEnd = this->_items.end();
            for (; it != itEnd; ++it)
                this->DeleteItem(it->second);
            this->_ProcessKillPool(); // VITE SUPPRIMME
        }

    }
}

