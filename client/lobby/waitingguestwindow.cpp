#include "waitingguestwindow.h"
#include "ui_waitingguestwindow.h"

WaitingGuestWindow::WaitingGuestWindow(ClientProtocol& _clientProtocol, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WaitingGuestWindow)
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

WaitingGuestWindow::~WaitingGuestWindow()
{
    delete ui;
}
