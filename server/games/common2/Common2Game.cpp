#include "Common2Game.hpp"
#include "Common2Resources.hpp"
#include "Common2PlayerEntity.hpp"
#include "Common2ManagerEntity.hpp"

#include "AnimationResourceInfo.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            Common2Game<E, G, PE, ME, T, W, H, P>::Common2Game(String const& name)
            : BasicGame<E, Common2Player<E, G, PE> >(name, T, W, H)
            {
                Log::I("Common2 game created.");
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            Common2Game<E, G, PE, ME, T, W, H, P>::~Common2Game()
            {
                Log::I("Common2 game destroyed.");
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            void Common2Game<E, G, PE, ME, T, W, H, P>::RegisterPlayerEntity(PE* player)
            {
                if (this->_running)
                    this->_players.push_back(player);
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            void Common2Game<E, G, PE, ME, T, W, H, P>::UnregisterPlayerEntity(PE* player)
            {
                if (this->_running)
                    this->_players.remove(player);
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            size_t Common2Game<E, G, PE, ME, T, W, H, P>::GetNumberOfPlayers() const
            {
                return this->_players.size();
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            std::list<PE*> const& Common2Game<E, G, PE, ME, T, W, H, P>::GetListOfPlayers() const
            {
                return this->_players;
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            void Common2Game<E, G, PE, ME, T, W, H, P>::_InitializeCommon2Resources()
            {
                this->_Load(Common2Resources::COUNTER, new AnimationResourceInfo("common2/data/animations/counter.png", 6, 1000, false));
                this->_Load(Common2Resources::FONT, new AnimationResourceInfo("common/data/animations/font1.png", 94, 0, false));
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            void Common2Game<E, G, PE, ME, T, W, H, P>::_InitializeResources()
            {
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            void Common2Game<E, G, PE, ME, T, W, H, P>::_Load(int id, AResourceInfo* res)
            {
                this->GetResourceManager().RegisterResource(id, res);
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            void Common2Game<E, G, PE, ME, T, W, H, P>::_PreRun()
            {
                this->_manager = this->_CreateManagerEntity();
            }

        template<typename E, typename G, typename PE, typename ME, size_t T, size_t W, size_t H, size_t P>
            void Common2Game<E, G, PE, ME, T, W, H, P>::_PostRun()
            {
                delete this->_manager;
            }

    }
}
