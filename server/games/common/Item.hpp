#ifndef __ITEM_HPP__
#define __ITEM_HPP__

namespace Gmgp
{
    namespace Server
    {

        class Item
        {
            public:
                explicit Item(float spawnTime = 0);
                ~Item();
                void SetPlayerId(uint16_t id);
                uint16_t GetPlayerId() const;
                void Run(float time);
                void ResetParamMask();
                bool HasChanged() const;
                void SetChanged(bool enable);
                uint16_t GetParamMask() const;
                void SetResourceId(uint32_t id);
                uint32_t GetResourceId() const;
                void SetPositionX(float pos);
                float GetPositionX() const;
                void SetPositionY(float pos);
                float GetPositionY() const;
                void SetSpeedX(float speed);
                float GetSpeedX() const;
                void SetSpeedY(float speed);
                float GetSpeedY() const;
                void SetAccelX(float accel);
                float GetAccelX() const;
                void SetAccelY(float accel);
                float GetAccelY() const;
                void SetLifeTimeMs(size_t ms);
                size_t GetLifeTimeMs() const;
                void SetLifeTimeCycles(size_t cycles);
                size_t GetLifeTimeCycles() const;
                void SetDisapear(bool enable);
                bool GetDisapear() const;
                void SetPositionZ(size_t pos);
                size_t GetPositionZ() const;
                void SetBlinking(size_t freq);
                size_t GetBlinking() const;
                void SetCursor(bool enable);
                bool GetCursor() const;
                void SetResponse(bool enable);
                bool GetResponse() const;
                void SetFrame(size_t frame);
                size_t GetFrame() const;
                void SetLuaId(uint16_t id);
                uint16_t GetLuaId() const;

            protected:
                uint16_t _playerId;
                float _lastTime;
                uint16_t _mask;
                bool _updated;
                uint32_t _resourceId;
                float _posX;
                float _posY;
                float _speedX;
                float _speedY;
                float _accelX;
                float _accelY;
                size_t _lifeTimeMs;
                size_t _lifeTimeCycles;
                bool _disapear;
                size_t _posZ;
                size_t _blinking;
                bool _cursor;
                bool _response;
                size_t _frame;
                uint16_t _luaId;
        };

    }
}

#endif

