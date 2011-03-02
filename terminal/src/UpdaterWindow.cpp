#include <QTimer>
#include <QKeyEvent>
#include "Terminal.hpp"
#include "UpdaterWindow.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        UpdaterWindow::UpdaterWindow(Terminal& term) :
            _term(term)
        {
            this->setupUi(this);
        }

        UpdaterWindow::~UpdaterWindow()
        {
        }

        void UpdaterWindow::on_autoResizeCheckBox_stateChanged(int state)
        {
            this->_term.GetGameView()->EnableAutoResize(state == Qt::Checked);
        }

        void UpdaterWindow::on_resizeFactorSpinBox_valueChanged(double val)
        {
            this->_term.GetGameView()->SetResizeFactor(val);
        }

        void UpdaterWindow::on_portSpinBox_valueChanged(int)
        {
        }

        void UpdaterWindow::on_musicSlider_valueChanged()
        {
            this->_term.GetGameView()->SetMusicVolume(this->musicSlider->value());
        }

        void UpdaterWindow::on_effectsSlider_valueChanged()
        {
            this->_term.GetGameView()->SetEffectsVolume(this->effectsSlider->value());
        }

        void UpdaterWindow::SetTotalBar(int val)
        {
            if (val < 0)
                val = 0;
            else if (val > 100)
                val = 100;
            this->totalProgressBar->setValue(val);
        }

        void UpdaterWindow::SetCurrentBar(int val)
        {
            if (val < 0)
                val = 0;
            else if (val > 100)
                val = 100;
            this->currentProgressBar->setValue(val);
        }

        void UpdaterWindow::SetStatus(String const& status)
        {
            this->statusLabel->setText(status.c_str());
        }

        void UpdaterWindow::EnablePlay(bool enable)
        {
            this->playPushButton->setEnabled(enable);
        }

        void UpdaterWindow::AddMessage(String const& message)
        {
            this->statusTextEdit->append(message.c_str());
        }

        void UpdaterWindow::on_playPushButton_clicked()
        {
            this->AddMessage("Waiting for the server to start a game...");
            this->SetStatus("Starting a game...");
            this->EnablePlay(false);
            Packet start;
            start.Write8(Packet::LETS_GO);
            start.Write16(0); // unused port
            this->_term.GetNetwork()->SendTcpPacket(start);
        }

        void UpdaterWindow::on_enableSmoothingCheckBox_stateChanged(int state)
        {
            this->_term.GetGameView()->EnableSmoothing(state == Qt::Checked);
        }

        void UpdaterWindow::on_enableMovementSmoothingCheckBox_stateChanged(int state)
        {
            this->_term.GetGameView()->EnableMovementSmoothing(state == Qt::Checked);
        }

        void UpdaterWindow::on_cancelPushButton_clicked()
        {
            this->close();
        }

        void UpdaterWindow::keyPressEvent(QKeyEvent* e)
        {
            if ((e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) && this->playPushButton->isEnabled())
                this->on_playPushButton_clicked();
            else
                this->QMainWindow::keyPressEvent(e);
        }

    }
}

