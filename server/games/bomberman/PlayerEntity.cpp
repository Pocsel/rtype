#include "PlayerEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "BombEntity.hpp"
#include "BombInteraction.hpp"
#include "BonusInteraction.hpp"
#include "BonusEntity.hpp"
#include "Decorator.hpp"

namespace Gmgp
{
    namespace Server
    {

        PlayerEntity::PlayerEntity(Game& game, uint16_t playerId, String const&) :
            Entity(game, "Player", playerId), _colorId(0), _sprite(game.GetElapsedTime()),
            _direction(NONE), _alive(false), _justSpawned(false)
        {
            std::list<PlayerEntity*> const& list = this->_game.GetListOfPlayers();
            bool found;
            for (this->_colorId = 0; this->_colorId < 1000; ++this->_colorId)
            {
                found = false;
                std::list<PlayerEntity*>::const_iterator it = list.begin();
                std::list<PlayerEntity*>::const_iterator itEnd = list.end();
                for (; it != itEnd && found == false; ++it)
                    if ((*it)->GetColorId() == this->_colorId)
                        found = true;
                if (!found)
                    break;
            }
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::P1_DOWN_IMMO + (this->_colorId & 0x7)));
            this->_sprite.SetPositionX(Game::FULLWIDTH * 0.5);
            this->_sprite.SetPositionY(-Game::FULLHEIGHT);
            this->_sprite.SetPositionZ(150);
            this->_game.GetItemManager().AddItem(&this->_sprite);

            this->_game.RegisterPlayerEntity(this);
        }

        PlayerEntity::~PlayerEntity()
        {
            this->_game.UnregisterPlayerEntity(this);
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
        }

        void PlayerEntity::Spawn(int x, int y)
        {
            Log::D("Player spawning at " + String(x) + "x" + String(y) + ".");
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::P1_DOWN_IMMO + (this->_colorId & 0x7)));
            this->_sprite.SetPositionX(Game::CaseToX(x));
            this->_sprite.SetPositionY(Game::CaseToY(y) - Y_OFFSET);
            this->_target.x = Game::CaseToX(x);
            this->_target.y = Game::CaseToY(y);

            this->_power = 1;
            this->_nbBombs = 1;
            this->_alive = true;
            this->_justSpawned = true;
        }

        bool PlayerEntity::IsAlive() const
        {
            return this->_alive;
        }

        void PlayerEntity::Run(float)
        {
            try
            {
                Player& player = this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId());
                if (player.KeyClicked(Key::Escape))
                {
                    std::map<uint16_t, IGame*> const& gameList = this->_game.GetServer().GetGameList();
                    IGame* mainGame = gameList.begin()->second;
                    if (mainGame != &this->_game)
                    {
                        Log::D("Player returning to MainMenu.");
                        this->_game.MovePlayer(this->GetPlayerId(), mainGame);
                        return;
                    }
                }

                if (this->_alive == false)
                    return;

                if (this->_justSpawned)
                { // suppression des murs autour
                    this->_game.GetEntityManager().GetInteractionManager().AddInteraction(InteractionPtr(new BombInteraction(0)),
                                                                                          Circle(this->_target.x + Game::CASE_SIZE, this->_target.y, Game::CASE_SIZE * 0.4f));
                    this->_game.GetEntityManager().GetInteractionManager().AddInteraction(InteractionPtr(new BombInteraction(0)),
                                                                                          Circle(this->_target.x - Game::CASE_SIZE, this->_target.y, Game::CASE_SIZE * 0.4f));
                    this->_game.GetEntityManager().GetInteractionManager().AddInteraction(InteractionPtr(new BombInteraction(0)),
                                                                                          Circle(this->_target.x, this->_target.y + Game::CASE_SIZE, Game::CASE_SIZE * 0.4f));
                    this->_game.GetEntityManager().GetInteractionManager().AddInteraction(InteractionPtr(new BombInteraction(0)),
                                                                                          Circle(this->_target.x, this->_target.y - Game::CASE_SIZE, Game::CASE_SIZE * 0.4f));
                    this->_justSpawned = false;
                }
                this->_Movement(player);

                this->_Bombing(player);

                this->_Taunt(player);

            }
            catch (std::exception&)
            {
            }

            this->_game.GetEntityManager().GetInteractionManager().Interact(*this, Point(this->_target.x, this->_target.y));
        }

        void PlayerEntity::_Taunt(Player& player)
        {
            if (player.KeyClicked(Key::T) || player.KeyClicked(Key::Joy3))
            {
                Item sprite;
                sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::TAUNT));
                sprite.SetPositionX(this->_sprite.GetPositionX());
                sprite.SetPositionY(this->_sprite.GetPositionY() - Y_OFFSET);
                sprite.SetLifeTimeCycles(1);
                sprite.SetPositionZ(140);
                this->_game.GetItemManager().SendItem(sprite);

                Decorator::PlaySound(Resources::AOK_ROGGAN, this->_game);
            }

            if (player.KeyClicked(Key::Y) || player.KeyClicked(Key::Joy0))
            {
                Item sprite;
                sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::TAUNT));
                sprite.SetPositionX(this->_sprite.GetPositionX());
                sprite.SetPositionY(this->_sprite.GetPositionY() - Y_OFFSET);
                sprite.SetLifeTimeCycles(1);
                sprite.SetPositionZ(140);
                this->_game.GetItemManager().SendItem(sprite);

                Decorator::PlaySound(Resources::AOK_WOLOLO, this->_game);
            }
        }

        void PlayerEntity::_Bombing(Player& player)
        {
            if ((player.KeyClicked(Key::Space) || player.KeyClicked(Key::Joy2)) &&
                this->_game.HasWall(this->_sprite.GetPositionX(), this->_sprite.GetPositionY() - Y_OFFSET) == false)
            {
                std::list<BombEntity*> const& bombList = this->_game.GetListOfBombs();
                int count = 0;
                for (std::list<BombEntity*>::const_iterator it = bombList.begin(),
                     ite = bombList.end() ; it != ite ; ++it)
                {
                    if ((*it)->GetPlayerId() == this->GetPlayerId())
                        ++count;
                }
                if (count < this->_nbBombs)
                { // Spawn bomb !!
                    Decorator::PlaySound(Resources::WA_PUTBOMB, this->_game);
                    new BombEntity(this->_game, this->GetPlayerId(), this->_power,
                                   Game::CaseToX(Game::XToCase(this->_sprite.GetPositionX())),
                                   Game::CaseToY(Game::YToCase(this->_sprite.GetPositionY() - Y_OFFSET)));
                }
            }
        }

        void PlayerEntity::_Movement(Player& player)
        {
            bool arrived = false;
            if (this->_direction)
            {
                if (this->_direction == UP)
                {
                    if (this->_sprite.GetPositionY() + Y_OFFSET <= this->_target.y)
                        arrived = true;
                }
                else if (this->_direction == DOWN)
                {
                    if (this->_sprite.GetPositionY() + Y_OFFSET >= this->_target.y)
                        arrived = true;
                }
                else if (this->_direction == LEFT)
                {
                    if (this->_sprite.GetPositionX() <= this->_target.x)
                        arrived = true;
                }
                else
                {
                    if (this->_sprite.GetPositionX() >= this->_target.x)
                        arrived = true;
                }
            }

            bool backInCourse = false;
            if (!this->_direction || arrived)
            {
                if ((player.KeyPressed(Key::Up) || player.KeyPressed(Key::Joy12)) && !this->_game.HasWall(this->_target.x, this->_target.y - Game::CASE_SIZE))
                {
                    if (this->_direction == LEFT || this->_direction == RIGHT)
                    {
                        this->_sprite.SetSpeedX(0);
                        this->_sprite.SetPositionX(this->_target.x);
                    }
                    backInCourse = true;
                    this->_target.y -= Game::CASE_SIZE;
                    if (this->_direction != UP)
                    {
                        this->_sprite.SetSpeedY(-SPEED);
                        this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::P1_UP_MOVE + (this->_colorId & 0x7)));
                        this->_direction = UP;
                    }
                }
                else if ((player.KeyPressed(Key::Down) || player.KeyPressed(Key::Joy14)) && !this->_game.HasWall(this->_target.x, this->_target.y + Game::CASE_SIZE))
                {
                    if (this->_direction == LEFT || this->_direction == RIGHT)
                    {
                        this->_sprite.SetSpeedX(0);
                        this->_sprite.SetPositionX(this->_target.x);
                    }
                    backInCourse = true;
                    this->_target.y += Game::CASE_SIZE;
                    if (this->_direction != DOWN)
                    {
                        this->_sprite.SetSpeedY(SPEED);
                        this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::P1_DOWN_MOVE + (this->_colorId & 0x7)));
                        this->_direction = DOWN;
                    }
                }
                else if ((player.KeyPressed(Key::Left) || player.KeyPressed(Key::Joy15)) && !this->_game.HasWall(this->_target.x - Game::CASE_SIZE, this->_target.y))
                {
                    if (this->_direction == UP || this->_direction == DOWN)
                    {
                        this->_sprite.SetSpeedY(0);
                        this->_sprite.SetPositionY(this->_target.y - Y_OFFSET);
                    }
                    backInCourse = true;
                    this->_target.x -= Game::CASE_SIZE;
                    if (this->_direction != LEFT)
                    {
                        this->_sprite.SetSpeedX(-SPEED);
                        this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::P1_LEFT_MOVE + (this->_colorId & 0x7)));
                        this->_direction = LEFT;
                    }
                }
                else if ((player.KeyPressed(Key::Right) || player.KeyPressed(Key::Joy13)) && !this->_game.HasWall(this->_target.x + Game::CASE_SIZE, this->_target.y))
                {
                    if (this->_direction == UP || this->_direction == DOWN)
                    {
                        this->_sprite.SetSpeedY(0);
                        this->_sprite.SetPositionY(this->_target.y - Y_OFFSET);
                    }
                    backInCourse = true;
                    this->_target.x += Game::CASE_SIZE;
                    if (this->_direction != RIGHT)
                    {
                        this->_sprite.SetSpeedX(SPEED);
                        this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::P1_RIGHT_MOVE + (this->_colorId & 0x7)));
                        this->_direction = RIGHT;
                    }
                }
            }

            if (arrived && !backInCourse)
            {
                this->_sprite.SetPositionX(this->_target.x);
                this->_sprite.SetPositionY(this->_target.y - Y_OFFSET);
                this->_sprite.SetSpeedX(0);
                this->_sprite.SetSpeedY(0);
                this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId((this->_direction == UP ? Resources::P1_UP_IMMO + (this->_colorId & 0x7):
                                                                                            (this->_direction == DOWN ? Resources::P1_DOWN_IMMO + (this->_colorId & 0x7):
                                                                                             (this->_direction == LEFT ? Resources::P1_LEFT_IMMO + (this->_colorId & 0x7):
                                                                                              Resources::P1_RIGHT_IMMO + (this->_colorId & 0x7))))));
                this->_direction = NONE;
            }
        }

        int PlayerEntity::GetColorId() const
        {
            return this->_colorId;
        }

        void PlayerEntity::_Die(uint16_t killerId)
        {
            {
                Item sprite;
                sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::P1_DEATH + (this->_colorId & 0x7)));
                sprite.SetPositionX(this->_sprite.GetPositionX());
                sprite.SetPositionY(this->_sprite.GetPositionY() - Y_OFFSET);
                sprite.SetLifeTimeCycles(1);
                sprite.SetPositionZ(140);
                this->_game.GetItemManager().SendItem(sprite);
            }

            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::P1_DOWN_IMMO + (this->_colorId & 0x7)));
            this->_sprite.SetPositionX(Game::FULLWIDTH * 0.5);
            this->_sprite.SetPositionY(-Game::FULLHEIGHT);
            this->_sprite.SetSpeedX(0);
            this->_sprite.SetSpeedY(0);
            this->_alive = false;

            if (killerId == 0)
                return;

            for (int i = 1 ; i < this->_power ; ++i)
                new BonusEntity(this->_game, this->_target.x, this->_target.y, BonusEntity::POWER);
            for (int i = 1 ; i < this->_nbBombs ; ++i)
                new BonusEntity(this->_game, this->_target.x, this->_target.y, BonusEntity::BOMB);

            if (killerId == this->GetPlayerId())
                return;

            Decorator::PlaySound(Resources::WA_KILL, this->_game);

            try
            {
                this->_game.GetPlayerManager().GetPlayer(killerId).AddToScore(1);
            }
            catch (std::exception&)
            {
            }
        }

        bool PlayerEntity::Interact(BombInteraction& interaction)
        {
            this->_Die(interaction.GetPlayerId());
            return false;
        }

        bool PlayerEntity::Interact(BonusInteraction& interaction)
        {
            if (interaction.IsPickedUp())
                return true;
            if (interaction.GetType() == BonusEntity::POWER)
                ++this->_power;
            else
                ++this->_nbBombs;
            interaction.PickedUp();
            return true;
        }

    }
}

