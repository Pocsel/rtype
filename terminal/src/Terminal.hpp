#ifndef __TERMINAL_HPP__
#define __TERMINAL_HPP__

#include <QMutex>
#include "String.hpp"
#include "INetwork.hpp"
#include "IGameView.hpp"
#include "UpdaterWindow.hpp"
#include "ConnectionWindow.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class Terminal :
            private sf::NonCopyable
        {
            public:
                explicit Terminal(int& ac, char** av);
                ~Terminal();
                int Run();
                void InformUser(String const& message) const;
                INetwork* GetNetwork();
                UpdaterWindow* GetUpdaterWindow();
                ConnectionWindow* GetConnectionWindow();
                IGameView* GetGameView();
                void CloseWindows();
            private:
                QApplication _app;
                INetwork* _network;
                UpdaterWindow* _updaterWindow;
                ConnectionWindow* _connectionWindow;
                IGameView* _gameView;
                QMutex _mutex;
        };

    }
}

#endif

