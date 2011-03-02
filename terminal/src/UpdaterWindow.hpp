#ifndef __UPDATERWINDOW_HPP__
#define __UPDATERWINDOW_HPP__

#include <SFML/System/NonCopyable.hpp>
#include "ui_updater.h"
#include "String.hpp"

namespace Gmgp
{
    namespace Terminal
    {
        class Terminal;
        class UpdaterWindow :
            public QMainWindow, private Ui::Updater
        {
            Q_OBJECT
            public:
                explicit UpdaterWindow(Terminal& term);
                ~UpdaterWindow();
                void AddMessage(String const& message);
                void EnablePlay(bool enable);
                void SetTotalBar(int val);
                void SetCurrentBar(int val);
                void SetStatus(String const& status);
            private slots:
                void on_cancelPushButton_clicked();
                void on_playPushButton_clicked();
                void on_enableSmoothingCheckBox_stateChanged(int state);
                void on_enableMovementSmoothingCheckBox_stateChanged(int state);
                void on_musicSlider_valueChanged();
                void on_effectsSlider_valueChanged();
                void on_portSpinBox_valueChanged(int val);
                void on_autoResizeCheckBox_stateChanged(int state);
                void on_resizeFactorSpinBox_valueChanged(double val);
            private:
                void keyPressEvent(QKeyEvent* e);
                Terminal& _term;
        };
    }
}

#endif

