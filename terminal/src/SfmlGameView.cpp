
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include <luabind/function.hpp>
#include "SfmlGameView.hpp"
#include "Terminal.hpp"
#include "Constants.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        SfmlGameView::SfmlGameView(Terminal& term) :
            _term(term), _smoothing(false), _movementSmoothing(true), _effectsVolume(100), _musicVolume(100), _isRunning(false), _frameRateSamples(0), _frameTimeSum(0), _autoResize(true), _resizeFactor(2), _luaState(0)
        {
            this->_InitLua();
            QObject::connect(&this->_frameTimer, SIGNAL(timeout()), this, SLOT(_RenderFrame()));
        }

        SfmlGameView::~SfmlGameView()
        {
            this->_DestroyLua();
        }

        void SfmlGameView::_InitLua()
        {
            this->_luaState = lua_open();
            lua_pushcfunction(this->_luaState, luaopen_base);
            lua_pushstring(this->_luaState, "");
            lua_call(this->_luaState, 1, 0);
            lua_pushcfunction(this->_luaState, luaopen_string);
            lua_pushstring(this->_luaState, LUA_STRLIBNAME);
            lua_call(this->_luaState, 1, 0);
            lua_pushcfunction(this->_luaState, luaopen_table);
            lua_pushstring(this->_luaState, LUA_TABLIBNAME);
            lua_call(this->_luaState, 1, 0);
            lua_pushcfunction(this->_luaState, luaopen_io);
            lua_pushstring(this->_luaState, LUA_IOLIBNAME);
            lua_call(this->_luaState, 1, 0);
            lua_pushcfunction(this->_luaState, luaopen_math);
            lua_pushstring(this->_luaState, LUA_MATHLIBNAME);
            lua_call(this->_luaState, 1, 0);
            lua_pushcfunction(this->_luaState, luaopen_debug);
            lua_pushstring(this->_luaState, LUA_DBLIBNAME);
            lua_call(this->_luaState, 1, 0);
            luabind::open(this->_luaState);
        }

        void SfmlGameView::_DestroyLua()
        {
            lua_close(this->_luaState);
            this->_luaState = 0;
        }

        lua_State* SfmlGameView::GetLuaState()
        {
            return this->_luaState;
        }

        void SfmlGameView::EnableAutoResize(bool enable)
        {
            this->_autoResize = enable;
            if (enable)
                Log::D("Auto window resizing enabled.");
            else
                Log::D("Auto window resizing disabled.");
        }

        void SfmlGameView::SetResizeFactor(float factor)
        {
            if (factor > 4)
                factor = 4;
            else if (factor < 0.5)
                factor = 0.5;
            this->_resizeFactor = factor;
            Log::D("Window resize factor set to " + String(factor) + ".");
        }

        void SfmlGameView::EnableSmoothing(bool enable)
        {
            this->_smoothing = enable;
            if (enable)
                Log::D("OpenGL smoothing enabled.");
            else
                Log::D("OpenGL smoothing disabled.");
        }

        void SfmlGameView::EnableMovementSmoothing(bool enable)
        {
            this->_movementSmoothing = enable;
            if (enable)
                Log::D("Movement smoothing enabled.");
            else
                Log::D("Movement smoothing disabled.");
        }

        bool SfmlGameView::MovementSmoothing() const
        {
            return this->_movementSmoothing;
        }

        void SfmlGameView::SetEffectsVolume(size_t vol)
        {
            this->_effectsVolume = vol;
            Log::D("Effects volume set to " + String(vol) + ".");
        }

        size_t SfmlGameView::GetMusicVolume() const
        {
            return this->_musicVolume;
        }

        size_t SfmlGameView::GetEffectsVolume() const
        {
            return this->_effectsVolume;
        }

        void SfmlGameView::SetMusicVolume(size_t vol)
        {
            this->_musicVolume = vol;
            Log::D("Music volume set to " + String(vol) + ".");
        }

        void SfmlGameView::ConfirmItem(size_t)
        {
//            this->_confirmations.push(id);
        }

        void SfmlGameView::SetResolution(size_t width, size_t height)
        {
            Log::I("Changing view resolution to " + String(width) + "x" + String(height) + ".");
            sf::View& view = this->_app->GetDefaultView();
            view.SetFromRect(sf::FloatRect(0, 0, width, height));
            this->_renderer->SetSize(width, height);
            if (this->_autoResize)
            {
                this->_app->SetSize(width * this->_resizeFactor, height * this->_resizeFactor);
                Log::I("Automatic resizing to " + String(width * this->_resizeFactor) + "x" + String(height * this->_resizeFactor) + ".");
            }
        }

        void SfmlGameView::AddAnimation(size_t id, String const& path, size_t frames, size_t delay, bool isVertical)
        {
            this->_animations[id] = new SfmlAnimation(path, frames, delay, isVertical, this->_smoothing);
        }

        void SfmlGameView::AddSound(size_t id, String const& path, bool isMusic)
        {
            this->_sounds[id] = new SfmlSound(path, isMusic);
        }

        void SfmlGameView::AddLua(size_t id, String const& path, String const& functionName)
        {
            this->_scripts[id] = new LuaFile(path, functionName, this->_luaState);
        }

        void SfmlGameView::PushData(char const* data, size_t size)
        {
            Log::D("New IN_GAME packet of " + String(size) + " bytes received.");
            Packet* packet = new Packet();
            packet->WriteData(data, size);
            this->_packets.push(packet);
        }

        bool SfmlGameView::IsRunning() const
        {
            return this->_isRunning;
        }

        SfmlAnimation* SfmlGameView::GetAnimation(size_t id)
        {
            if (this->_animations.count(id) != 1)
                return 0;
            return this->_animations[id];
        }

        SfmlSound* SfmlGameView::GetSound(size_t id)
        {
            if (this->_sounds.count(id) != 1)
                return 0;
            return this->_sounds[id];
        }

        LuaFile* SfmlGameView::GetScript(size_t id)
        {
            if (this->_scripts.count(id) != 1)
                return 0;
            return this->_scripts[id];
        }

        float SfmlGameView::GetTime() const
        {
            return this->_clock.GetElapsedTime();
        }

        void SfmlGameView::_RenderFrame()
        {
            if (this->_app->IsOpened())
            {
                float frameStart = this->_clock.GetElapsedTime();
                this->_eventManager->ProcessEvents(this->_app, this->_clock.GetElapsedTime());
                this->_renderer->SetMousePos(this->_eventManager->GetMouseX(), this->_eventManager->GetMouseY());
                size_t nbPackets = this->_packets.size();
                size_t nbBytes = 0;
                while (this->_packets.size() > 0)
                {
                    nbBytes += this->_packets.front()->GetSize();
                    this->_renderer->ProcessPacket(*this->_packets.front());
                    delete this->_packets.front();
                    this->_packets.pop();
                }
                this->_renderer->SetRecvPacketInfo(nbPackets, nbBytes);
                _app->Clear();
                this->_renderer->Render(this->_app, this->_clock.GetElapsedTime());
//                this->_SendConfirmations();
                _app->Display();
                float renderTime = this->_clock.GetElapsedTime() - frameStart;
                this->_frameTimeSum += renderTime;
                ++this->_frameRateSamples;
                if (this->_frameRateSamples >= 10)
                {
                    this->_renderer->SetFrameRateInfo(1.0f / (this->_frameTimeSum / 10.0f));
                    this->_frameTimeSum = 0;
                    this->_frameRateSamples = 0;
                }
                this->_frameTimer.start(FRAMEDELAY - renderTime > 0 ? FRAMEDELAY - renderTime : 0);
            }
            else
                this->Stop();
        }

        void SfmlGameView::_Init()
        {
            Log::I("Initializing SFML game view.");
            this->_app = new sf::RenderWindow(sf::VideoMode(640, 480), "Game Terminal");
            this->_app->ShowMouseCursor(false);
            this->_renderer = new SfmlRenderer(*this);
            this->_eventManager = new EventManager(this->_term.GetNetwork(), *this->_renderer);
            this->_clock.Reset();
        }

        void SfmlGameView::_Exit()
        {
            Log::I("Quitting SFML game view.");
            this->_frameTimer.stop();
            delete this->_eventManager;
            delete this->_renderer;
            delete this->_app;
            std::map<size_t, SfmlAnimation*>::iterator itAnim = this->_animations.begin();
            std::map<size_t, SfmlAnimation*>::iterator itAnimEnd = this->_animations.end();
            for (; itAnim != itAnimEnd; ++itAnim)
                delete (*itAnim).second;
            this->_animations.clear();
            std::map<size_t, SfmlSound*>::iterator itSound = this->_sounds.begin();
            std::map<size_t, SfmlSound*>::iterator itSoundEnd = this->_sounds.end();
            for (; itSound != itSoundEnd; ++itSound)
                delete (*itSound).second;
            this->_sounds.clear();
            std::map<size_t, LuaFile*>::iterator itScript = this->_scripts.begin();
            std::map<size_t, LuaFile*>::iterator itScriptEnd = this->_scripts.end();
            for (; itScript != itScriptEnd; ++itScript)
                delete (*itScript).second;
            this->_scripts.clear();
            this->_term.CloseWindows();
            this->_isRunning = false;
        }

        void SfmlGameView::Stop()
        {
            if (this->IsRunning())
                this->_Exit();
        }

        void SfmlGameView::Start()
        {
            this->_isRunning = true;
            this->_Init();
            this->_frameTimer.start(FRAMEDELAY);
        }

    }
}

