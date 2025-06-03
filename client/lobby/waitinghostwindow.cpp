#include "waitinghostwindow.h"
#include "ui_waitinghostwindow.h"

WaitingHostWindow::WaitingHostWindow(QWidget *parent, ClientProtocol& _clientProtocol)
    : QDialog(parent)
    , ui(new Ui::WaitingHostWindow)
    , clientProtocol(_clientProtocol)
{
    ui->setupUi(this);
    setFixedSize(300, 200);
    ui->frame->setFixedSize(300, 200);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    QRect parentRect = parent->rect();
    QPoint parentTopLeft = parent->mapToGlobal(parentRect.topLeft());

    int x = parentTopLeft.x() + (parentRect.width() - this->width()) / 2;
    int y = parentTopLeft.y() + (parentRect.height() - this->height()) / 2;

    this->move(x, y);
}

WaitingHostWindow::~WaitingHostWindow()
{
    delete ui;
}
