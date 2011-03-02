#ifndef COMMON2__MANAGERENTITY_HPP__
#define COMMON2__MANAGERENTITY_HPP__

#include <vector>
#include <list>
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, typename G>
            class Common2TextEntity;

        template<typename E, typename G, typename PE>
            class Common2ManagerEntity :
                public E
        {
        public:
            explicit Common2ManagerEntity(G& game, size_t nbPlayers);
            virtual ~Common2ManagerEntity();
            virtual void Run(float time);

        private:
            struct Score
            {
                Item* icon;
                Common2TextEntity<E, G>* nick;
                int score;
                Common2TextEntity<E, G>* scoreText;
            };

            void _ClearPanel();
            void _UpdatePanel();

        protected:
            virtual void _SpawnMap();
            virtual void _DestroyMap();
            virtual void _StartMusic();
            virtual void _RestartMusic();
            virtual int _GetIconId() const = 0; // player icon
            virtual int _GetBgId() const = 0; // background

        protected:
            size_t _nbPlayers;

        private:
            bool _bgReady;
            bool _started;
            size_t _lastNbOfPlayers;
            std::list<Score*> _scores;
            float _spawnStart;
            bool _mapDestroyed;
            Item _bg;
        };

    }
}

#endif

