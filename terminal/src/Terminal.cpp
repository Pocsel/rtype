#include <QApplication>
#include <QMessageBox>
#include "Terminal.hpp"
#include "QtNetwork.hpp"
#include "SfmlGameView.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        Terminal::Terminal(int& ac, char** av) :
            _app(ac, av)
        {
            this->_network = new QtNetwork(*this);
            this->_updaterWindow = new UpdaterWindow(*this);
            this->_connectionWindow = new ConnectionWindow(*this);
            this->_gameView = new SfmlGameView(*this);
        }

        Terminal::~Terminal()
        {
            delete this->_updaterWindow;
            delete this->_connectionWindow;
        }

        int Terminal::Run()
        {
            this->_connectionWindow->show();
            return this->_app.exec();
        }

        void Terminal::InformUser(String const& message) const
        {
            QMessageBox::information(0, "Message", message.c_str(), 0, 0, 0);
        }

        void Terminal::CloseWindows()
        {
            QMutexLocker lock(&this->_mutex);
            this->_updaterWindow->close();
            this->_connectionWindow->close();
        }

        INetwork* Terminal::GetNetwork()
        {
            QMutexLocker lock(&this->_mutex);
            return this->_network;
        }

        UpdaterWindow* Terminal::GetUpdaterWindow()
        {
            QMutexLocker lock(&this->_mutex);
            return this->_updaterWindow;
        }

        ConnectionWindow* Terminal::GetConnectionWindow()
        {
            QMutexLocker lock(&this->_mutex);
            return this->_connectionWindow;
        }

        IGameView* Terminal::GetGameView()
        {
            QMutexLocker lock(&this->_mutex);
            return this->_gameView;
        }

    }
}

