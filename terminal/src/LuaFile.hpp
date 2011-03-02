#ifndef __LUAFILE_HPP__
#define __LUAFILE_HPP__

#include <SFML/Graphics.hpp>
#include "String.hpp"

struct lua_State;

namespace Gmgp
{
    namespace Terminal
    {

        class SpriteItem;

        class LuaFile :
            private sf::NonCopyable
        {
            public:
                LuaFile(String const& path, String const& functionName, lua_State* state);
                ~LuaFile();
                void Run(SpriteItem* sprite, float spawnTime, float curTime, float elapsedTime);
                void Delete(SpriteItem* sprite);
                void Create(SpriteItem* sprite);
            private:
                void _SetGlobals(SpriteItem* sprite);
                void _GetGlobals(SpriteItem* sprite);
                bool _loaded;
                String _path;
                String _functionName;
                lua_State* _state;
        };

    }
}

#endif

