#ifndef WAITINGHOSTWINDOW_H
#define WAITINGHOSTWINDOW_H

#include <QDialog>
#include "../client_protocol.h"

namespace Ui {
class WaitingHostWindow;
}

class WaitingHostWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingHostWindow(QWidget *parent = nullptr, ClientProtocol& _clientProtocol);
    ~WaitingHostWindow();

private:
    Ui::WaitingHostWindow *ui;
    ClientProtocol& clientProtocol;
};

#endif // WAITINGHOSTWINDOW_H
