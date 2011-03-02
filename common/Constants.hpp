#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

namespace Gmgp
{

    enum ItemParam
    {
        RESOURCE_ID = 0x8000,
        X_POS = 0x4000,
        Y_POS = 0x2000,
        X_SPEED = 0x1000,
        Y_SPEED = 0x0800,
        X_ACCEL = 0x0400,
        Y_ACCEL = 0x0200,
        LIFE_TIME_MS = 0x0100,
        LIFE_TIME_CYCLES = 0x0080,
        DISAPEAR = 0x0040,
        Z_POS = 0x0020,
        BLINKING = 0x0010,
        CURSOR = 0x0008,
        RESPONSE = 0x0004,
        FRAME = 0x0002,
        LUA_ID = 0x0001
    };

    enum EventType
    {
        INPUT = 0,
        CONFIRMATION = 1
    };

    enum InputDevice
    {
        KEYBOARD = 0,
        MOUSE = 1
    };

    enum InputAction
    {
        RELEASED = 0,
        PRESSED = 1
    };

    enum EventMask
    {
        EVENT_TYPE = 0x80000000,
        INPUT_DEVICE = 0x40000000,
        INPUT_ACTION = 0x20000000,
        KEY_VALUE = 0x1FFFFFFF,
        BUTTON_VALUE = 0x1F000000,
        X_COORD = 0x00FFF000,
        Y_COORD = 0x00000FFF,
        CONFIRM_PARAMS = 0x00FFFF00,
        CONFIRM_ITEMS = 0x000000FF
    };

#define EVENT_KEYVALUE(ev) ((ev) & Gmgp::KEY_VALUE)
#define EVENT_BUTTONVALUE(ev) ((((ev) & Gmgp::BUTTON_VALUE) >> 24) & 0x1F)
#define EVENT_XCOORD(ev) ((((ev) & Gmgp::X_COORD) >> 12) & 0xFFF)
#define EVENT_YCOORD(ev) ((ev) & Gmgp::Y_COORD)
#define EVENT_CONFIRMPARAMS(ev) ((((ev) & Gmgp::CONFIRM_PARAMS) >> 8) & 0xFFFF)
#define EVENT_CONFIRMITEMS(ev) ((ev) & Gmgp::CONFIRM_ITEMS)

    enum ResourceType
    {
        ANIMATION = 0,
        SOUND = 1,
        LUA = 2
    };

    namespace Key
    {

        enum Key
        {
            A = 'a',
            B = 'b',
            C = 'c',
            D = 'd',
            E = 'e',
            F = 'f',
            G = 'g',
            H = 'h',
            I = 'i',
            J = 'j',
            K = 'k',
            L = 'l',
            M = 'm',
            N = 'n',
            O = 'o',
            P = 'p',
            Q = 'q',
            R = 'r',
            S = 's',
            T = 't',
            U = 'u',
            V = 'v',
            W = 'w',
            X = 'x',
            Y = 'y',
            Z = 'z',
            Num0 = '0',
            Num1 = '1',
            Num2 = '2',
            Num3 = '3',
            Num4 = '4',
            Num5 = '5',
            Num6 = '6',
            Num7 = '7',
            Num8 = '8',
            Num9 = '9',
            Escape = 256,
            LControl = 312,
            LShift = 314,
            LAlt = 1000,
            LSystem = 1005,
            RControl = 789,
            RShift = 1024,
            RAlt = 545,
            RSystem = 899,
            Menu = 898,
            LBracket = 897,
            RBracket = 900,
            SemiColon = 2000,
            Comma = 2001,
            Period = 2002,
            Quote = 3040,
            Slash = 4000,
            BackSlash = 4001,
            Tilde = 4005,
            Equal = 3333,
            Dash = 2222,
            Space = 1111,
            Return = 11111,
            Back = 8000,
            Tab = 9000,
            PageUp = 9100,
            PageDown = 9200,
            End = 9300,
            Home = 9400,
            Insert = 9500,
            Delete = 9600,
            Add = 9700,
            Subtract = 9800,
            Multiply = 9900,
            Divide = 10001,
            Left = 10002,
            Right = 9801,
            Up = 9802,
            Down = 9803,
            Numpad0 = 9084,
            Numpad1 = 9085,
            Numpad2 = 6000,
            Numpad3 = 6100,
            Numpad4 = 6101,
            Numpad5 = 6102,
            Numpad6 = 6103,
            Numpad7 = 6104,
            Numpad8 = 6500,
            Numpad9 = 6600,
            F1 = 6666,
            F2 = 6667,
            F3 = 6668,
            F4 = 6669,
            F5 = 6610,
            F6 = 6611,
            F7 = 6700,
            F8 = 6701,
            F9 = 6709,
            F10 = 6800,
            F11 = 6801,
            F12 = 6888,
            F13 = 1000000,
            F14 = 1000001,
            F15 = 1234234,
            Pause = 2342893,
            Joy0 = 7000,
            Joy1 = 7001,
            Joy2 = 7002,
            Joy3 = 7003,
            Joy4 = 7004,
            Joy5 = 7005,
            Joy6 = 7006,
            Joy7 = 7007,
            Joy8 = 7008,
            Joy9 = 7009,
            Joy10 = 7010,
            Joy11 = 7011,
            Joy12 = 7012, // Up
            Joy13 = 7013, // Right
            Joy14 = 7014, // Down
            Joy15 = 7015  // Left
        };

    }

    namespace Mouse
    {

        enum Mouse
        {
            Left = 0,
            Right = 1,
            Middle = 2,
            Button4 = 3,
            Button5 = 4,
            Movement = 5
        };

    }
}

#endif

