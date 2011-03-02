#ifndef __SFMLGAMEVIEW_HPP__
#define __SFMLGAMEVIEW_HPP__

#include <SFML/Graphics.hpp>
#include <QMutex>
#include <QTimer>
#include <QThread>
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include "IGameView.hpp"
#include "Packet.hpp"
#include "SfmlSound.hpp"
#include "SfmlAnimation.hpp"
#include "LuaFile.hpp"
#include "SfmlRenderer.hpp"
#include "EventManager.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class Terminal;
        class SfmlGameView :
            public QObject, public IGameView, private sf::NonCopyable
        {
            Q_OBJECT
            public:
                explicit SfmlGameView(Terminal& term);
                ~SfmlGameView();
                void Start();
                void Stop();
                bool IsRunning() const;
                void PushData(char const* data, size_t size);
                void AddAnimation(size_t id, String const& path, size_t frames, size_t delay, bool isVertical);
                void AddSound(size_t id, String const& path, bool isMusic);
                void AddLua(size_t id, String const& path, String const& functionName);
                void SetResolution(size_t width, size_t height);
                void EnableSmoothing(bool enable);
                void EnableMovementSmoothing(bool enable);
                bool MovementSmoothing() const;
                void SetEffectsVolume(size_t vol);
                size_t GetEffectsVolume() const;
                void SetMusicVolume(size_t vol);
                size_t GetMusicVolume() const;
                void ConfirmItem(size_t id);
                SfmlAnimation* GetAnimation(size_t id);
                SfmlSound* GetSound(size_t id);
                LuaFile* GetScript(size_t id);
                void EnableAutoResize(bool enable);
                void SetResizeFactor(float val);
                lua_State* GetLuaState();
                float GetTime() const;
            private slots:
                void _RenderFrame();
            private:
                enum
                {
                    FRAMEDELAY = 20
                };
                void _Init();
                void _Exit();
                void _InitLua();
                void _DestroyLua();
                Terminal& _term;
                sf::RenderWindow* _app;
                QTimer _frameTimer;
                std::queue<Packet*> _packets;
                std::map<size_t, SfmlAnimation*> _animations;
                std::map<size_t, SfmlSound*> _sounds;
                std::map<size_t, LuaFile*> _scripts;
                SfmlRenderer* _renderer;
                sf::Clock _clock;
                bool _smoothing;
                bool _movementSmoothing;
                size_t _effectsVolume;
                size_t _musicVolume;
                EventManager* _eventManager;
                bool _isRunning;
                size_t _frameRateSamples;
                float _frameTimeSum;
                bool _autoResize;
                float _resizeFactor;
                lua_State* _luaState;
        };

    }
}

#endif

