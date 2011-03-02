#ifndef __SFMLRENDERER_HPP__
#define __SFMLRENDERER_HPP__

#include <list>
#include <map>
#include "IItem.hpp"
#include "Packet.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class SfmlGameView;

        class SfmlRenderer :
            private sf::NonCopyable
        {
            public:
                explicit SfmlRenderer(SfmlGameView& view);
                ~SfmlRenderer();
                void Render(sf::RenderWindow* app, float time);
                void ProcessPacket(Packet const& p);
                void AddItem(IItem* item, size_t pos);
                void RemoveItem(IItem* item, size_t pos);
                void DeleteItem(IItem* item);
                void SetSize(size_t width, size_t height);
                void SetMousePos(float x, float y);
                size_t GetWidth() const;
                size_t GetHeight() const;
                float GetMouseX() const;
                float GetMouseY() const;
                void EnableInfo();
                void SetFrameRateInfo(float fps);
                void SetRecvPacketInfo(size_t nb, size_t bytes);
            private:
                void _ProcessKillPool();
                void _RemoveAllItems();
                void _ShowInfos(sf::RenderWindow* app, float time);
                SfmlGameView& _view;
                std::map<size_t, IItem*> _items;
                std::vector< std::list<IItem*> > _layers;
                std::list<IItem*> _killPool;
                size_t _width;
                size_t _height;
                float _mouseX;
                float _mouseY;
                sf::Font _font;
                bool _infoEnabled;
                float _fpsInfo;
                size_t _recvPacketInfo;
                size_t _recvBytesInfo;
                float _lastNetUpdate;
                size_t _recvTotalPackets;
                size_t _recvTotalBytes;
                String _recvNetText;
        };

    }
}

#endif

