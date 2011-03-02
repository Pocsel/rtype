#include "Item.hpp"
#include "Constants.hpp"
#include "String.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        Item::Item(float spawnTime /* = 0 */) :
            _playerId(0), _lastTime(spawnTime), _mask(0), _updated(false), _resourceId(0), _posX(-10000), _posY(-10000), _speedX(0), _speedY(0), _accelX(0), _accelY(0), _lifeTimeMs(0), _lifeTimeCycles(0), _disapear(false), _posZ(128), _blinking(0), _cursor(false), _response(false), _frame(0), _luaId(0)
        {
        }

        Item::~Item()
        {
        }

        void Item::SetPlayerId(uint16_t id)
        {
            this->_playerId = id;
        }

        uint16_t Item::GetPlayerId() const
        {
            return this->_playerId;
        }

        void Item::Run(float time)
        {
            float timeOffset = time - this->_lastTime;
            this->_speedX += this->_accelX * timeOffset;
            this->_speedY += this->_accelY * timeOffset;
            this->_posX += this->_speedX * timeOffset;
            this->_posY += this->_speedY * timeOffset;
            this->_lastTime = time;
        }

        void Item::ResetParamMask()
        {
            this->_mask = 0;
        }

        bool Item::HasChanged() const
        {
            return this->_updated;
        }

        void Item::SetChanged(bool enable)
        {
            this->_updated = enable;
        }

        uint16_t Item::GetParamMask() const
        {
            return this->_mask;
        }

        void Item::SetResourceId(uint32_t id)
        {
            this->_resourceId = id;
            this->_mask |= RESOURCE_ID;
            this->_updated = true;
        }

        uint32_t Item::GetResourceId() const
        {
            return this->_resourceId;
        }

        void Item::SetPositionX(float pos)
        {
            this->_posX = pos;
            this->_mask |= X_POS;
            this->_updated = true;
        }

        float Item::GetPositionX() const
        {
            return this->_posX;
        }

        void Item::SetPositionY(float pos)
        {
            this->_posY = pos;
            this->_mask |= Y_POS;
            this->_updated = true;
        }

        float Item::GetPositionY() const
        {
            return this->_posY;
        }

        void Item::SetSpeedX(float speed)
        {
            this->_speedX = speed;
            this->_mask |= X_SPEED;
            this->_updated = true;
        }

        float Item::GetSpeedX() const
        {
            return this->_speedX;
        }

        void Item::SetSpeedY(float speed)
        {
            this->_speedY = speed;
            this->_mask |= Y_SPEED;
            this->_updated = true;
        }

        float Item::GetSpeedY() const
        {
            return this->_speedY;
        }

        void Item::SetAccelX(float accel)
        {
            this->_accelX = accel;
            this->_mask |= X_ACCEL;
            this->_updated = true;
        }

        float Item::GetAccelX() const
        {
            return this->_accelX;
        }

        void Item::SetAccelY(float accel)
        {
            this->_accelY = accel;
            this->_mask |= Y_ACCEL;
            this->_updated = true;
        }

        float Item::GetAccelY() const
        {
            return this->_accelY;
        }

        void Item::SetLifeTimeMs(size_t ms)
        {
            this->_lifeTimeMs = ms;
            this->_mask |= LIFE_TIME_MS;
            this->_updated = true;
        }

        size_t Item::GetLifeTimeMs() const
        {
            return this->_lifeTimeMs;
        }

        void Item::SetLifeTimeCycles(size_t cycles)
        {
            this->_lifeTimeCycles = cycles;
            this->_mask |= LIFE_TIME_CYCLES;
            this->_updated = true;
        }

        size_t Item::GetLifeTimeCycles() const
        {
            return this->_lifeTimeCycles;
        }

        void Item::SetDisapear(bool enable)
        {
            this->_disapear = enable;
            if (enable)
                this->_mask |= DISAPEAR;
            else
                this->_mask &= ~DISAPEAR;
            this->_updated = true;
        }

        bool Item::GetDisapear() const
        {
            return this->_disapear;
        }

        void Item::SetPositionZ(size_t pos)
        {
            this->_posZ = pos;
            this->_mask |= Z_POS;
            this->_updated = true;
        }

        size_t Item::GetPositionZ() const
        {
            return this->_posZ;
        }

        void Item::SetBlinking(size_t freq)
        {
            this->_blinking = freq;
            this->_mask |= BLINKING;
            this->_updated = true;
        }

        size_t Item::GetBlinking() const
        {
            return this->_blinking;
        }

        void Item::SetCursor(bool enable)
        {
            this->_cursor = enable;
            if (enable)
                this->_mask |= CURSOR;
            else
                this->_mask &= ~CURSOR;
            this->_updated = true;
        }

        bool Item::GetCursor() const
        {
            return this->_cursor;
        }

        void Item::SetResponse(bool enable)
        {
            this->_response = enable;
            if (enable)
                this->_mask |= RESPONSE;
            else
                this->_mask &= ~RESPONSE;
            this->_updated = true;
        }

        bool Item::GetResponse() const
        {
            return this->_response;
        }

        void Item::SetFrame(size_t frame)
        {
            this->_frame = frame;
            this->_mask |= FRAME;
            this->_updated = true;
        }

        size_t Item::GetFrame() const
        {
            return this->_frame;
        }

        void Item::SetLuaId(uint16_t id)
        {
            this->_luaId = id;
            this->_mask |= LUA_ID;
            this->_updated = true;
        }

        uint16_t Item::GetLuaId() const
        {
            return this->_luaId;
        }

    }
}

