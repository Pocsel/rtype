#include <luabind/function.hpp>
#include "LuaFile.hpp"
#include "Log.hpp"
#include "SpriteItem.hpp"
#include "SfmlGameView.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        LuaFile::LuaFile(String const& path, String const& functionName, lua_State* state) :
            _loaded(false), _path(path), _functionName(functionName), _state(state)
        {
            Log::D("New script: " + this->_path + ".");
            if ((luaL_loadfile(this->_state, path.c_str()) || lua_pcall(this->_state, 0, LUA_MULTRET, 0)) == 0)
                this->_loaded = true;
            else
                Log::W("Failed to load " + this->_path + ": " + lua_tostring(this->_state, -1));
        }

        LuaFile::~LuaFile()
        {
            Log::D("Destroying script: " + this->_path + ".");
        }

        void LuaFile::_SetGlobals(SpriteItem* sprite)
        {
            luabind::globals(this->_state)["posX"] = sprite->GetPositionX();
            luabind::globals(this->_state)["posY"] = sprite->GetPositionY();
            luabind::globals(this->_state)["speedX"] = sprite->GetSpeedX();
            luabind::globals(this->_state)["speedY"] = sprite->GetSpeedY();
            luabind::globals(this->_state)["accelX"] = sprite->GetAccelX();
            luabind::globals(this->_state)["accelY"] = sprite->GetAccelY();
            luabind::globals(this->_state)["framePos"] = sprite->GetFrame();
        }
        void LuaFile::_GetGlobals(SpriteItem* sprite)
        {
            sprite->SetPositionX(luabind::object_cast<float>(luabind::globals(this->_state)["posX"]));
            sprite->SetPositionY(luabind::object_cast<float>(luabind::globals(this->_state)["posY"]));
            sprite->SetSpeedX(luabind::object_cast<float>(luabind::globals(this->_state)["speedX"]));
            sprite->SetSpeedY(luabind::object_cast<float>(luabind::globals(this->_state)["speedY"]));
            sprite->SetAccelX(luabind::object_cast<float>(luabind::globals(this->_state)["accelX"]));
            sprite->SetAccelY(luabind::object_cast<float>(luabind::globals(this->_state)["accelY"]));
            sprite->SetFrame(luabind::object_cast<float>(luabind::globals(this->_state)["framePos"]));
        }

        void LuaFile::Create(SpriteItem* sprite)
        {
            if (!this->_loaded)
                return;
            try
            {
                this->_SetGlobals(sprite);
                luabind::call_function<void>(this->_state, String(this->_functionName + "Create").c_str(), sprite->GetId());
            }
            catch (std::exception&)
            {
            }
        }

        void LuaFile::Delete(SpriteItem* sprite)
        {
            if (!this->_loaded)
                return;
            try
            {
                this->_SetGlobals(sprite);
                luabind::call_function<void>(this->_state, String(this->_functionName + "Delete").c_str(), sprite->GetId());
            }
            catch (std::exception&)
            {
            }
        }

        void LuaFile::Run(SpriteItem* sprite, float spawnTime, float curTime, float elapsedTime)
        {
            if (!this->_loaded)
                return;
            try
            {
                this->_SetGlobals(sprite);
                luabind::call_function<void>(this->_state, this->_functionName.c_str(), sprite->GetId(), spawnTime, curTime, elapsedTime);
                this->_GetGlobals(sprite);
            }
            catch (std::exception&)
            {
            }
        }

    }
}

