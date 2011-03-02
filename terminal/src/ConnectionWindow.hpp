#ifndef __CONNECTIONWINDOW_HPP__
#define __CONNECTIONWINDOW_HPP__

#include "ui_connection.h"
#include "String.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class Terminal;
        class ConnectionWindow :
            public QMainWindow, private Ui::Connection
        {
            Q_OBJECT
            public:
                explicit ConnectionWindow(Terminal& term);
                ~ConnectionWindow();
                void EnableConnection(bool enable);
                String GetNickname() const;
            private slots:
                void on_okPushButton_clicked();
                void on_quitPushButton_clicked();
            private:
                void keyPressEvent(QKeyEvent* e);
                void _ReadInfos();
                void _WriteInfos() const;
                Terminal& _term;
        };

    }
}

#endif

