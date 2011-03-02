
#ifndef BOINGLASERENTITY_HPP_
# define BOINGLASERENTITY_HPP_

#include <vector>

#include "GameEntity.hpp"
#include "Item.hpp"
#include "FriendlyBulletEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;
        class WallInteraction;

        class BoingLaserEntity : public FriendlyBulletEntity
        {
        public:
            enum Direction
            {
                RIGHT,
                UPRIGHT,
                DOWNRIGHT,
                LEFT,
                UPLEFT,
                DOWNLEFT
            };

        private:
            enum Frame
            {
                SP_LEFT = 0,
                SP_RIGHT = 0,
                SP_UPLEFT = 2,
                SP_DOWNRIGHT = 2,
                SP_UPRIGHT = 1,
                SP_DOWNLEFT = 1,
                SP_UP_COL = 3,
                SP_DOWN_COL = 4,
                SP_RIGHT_COL = 5,
                SP_LEFT_COL = 6
            };

            enum Constant
            {
                SPEED_STRAIGHT = 240,
                SPEED_DIAG = 169,
                MAX_BOING = 4
            };


        public:
            explicit BoingLaserEntity(Game& game,
                                      Direction direction,
                                      float posX,
                                      float posY,
                                      uint16_t playerId = 0);
            virtual ~BoingLaserEntity(void);

            // Interactions
            virtual bool Interact(WallInteraction& interaction);

        private:
            virtual void _ExplodeEffects(void);
            void _SetFrame(void);

            void _RightCollision(Point const& pos);
            void _LeftCollision(Point const& pos);
            void _UpLeftVerticalCollision(Point const& pos);
            void _UpLeftHorizontalCollision(Point const& pos);
            void _DownLeftVerticalCollision(Point const& pos);
            void _DownLeftHorizontalCollision(Point const& pos);
            void _UpRightVerticalCollision(Point const& pos);
            void _UpRightHorizontalCollision(Point const& pos);
            void _DownRightVerticalCollision(Point const& pos);
            void _DownRightHorizontalCollision(Point const& pos);


            Direction _direction;
            int _boingCount;
            std::vector<void (BoingLaserEntity::*)(Point const& pos)> _horizontalCollisions;
            std::vector<void (BoingLaserEntity::*)(Point const& pos)> _verticalCollisions;
        };

    }
}

#endif // !BOINGLASERENTITY_HPP_
