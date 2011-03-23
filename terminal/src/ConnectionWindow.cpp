#include <QKeyEvent>
#include <fstream>

#include "Terminal.hpp"
#include "ConnectionWindow.hpp"

namespace Gmgp
{

    namespace Terminal
    {
        ConnectionWindow::ConnectionWindow(Terminal& term) :
            _term(term)
        {
            this->setupUi(this);
            this->_ReadInfos();
        }

        ConnectionWindow::~ConnectionWindow()
        {
        }

        String ConnectionWindow::GetNickname() const
        {
            return this->nicknameLineEdit->text().toStdString();
        }

        void ConnectionWindow::EnableConnection(bool enable)
        {
            this->okPushButton->setEnabled(enable);
        }

        void ConnectionWindow::on_okPushButton_clicked()
        {
            this->EnableConnection(false);
            this->_term.GetNetwork()->Connect(this->addressLineEdit->text().toStdString(), this->portSpinBox->value());
            this->_WriteInfos();
        }

        void ConnectionWindow::on_quitPushButton_clicked()
        {
            this->close();
        }

        void ConnectionWindow::keyPressEvent(QKeyEvent* e)
        {
            if ((e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) && this->okPushButton->isEnabled())
                this->on_okPushButton_clicked();
            else
                this->QMainWindow::keyPressEvent(e);
        }

        void ConnectionWindow::_ReadInfos()
        {
            std::ifstream i("connection.conf");
            if (i.good())
            {
                char buf[100];
                i.getline(buf, 100);
                this->nicknameLineEdit->setText(buf);
                i.getline(buf, 100);
                this->addressLineEdit->setText(buf);
                i.getline(buf, 100);
                this->portSpinBox->setValue(::atoi(buf));
            }
        }

        void ConnectionWindow::_WriteInfos() const
        {
            std::ofstream o("connection.conf");
            o << this->nicknameLineEdit->text().toStdString() << std::endl;
            o << this->addressLineEdit->text().toStdString() << std::endl;
            o << this->portSpinBox->value() << std::endl;
        }
    }

}

