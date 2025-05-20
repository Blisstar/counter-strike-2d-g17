#include "newgamewindow.h"
#include "ui_newgamewindow.h"

NewGameWindow::NewGameWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewGameWindow)
{
    ui->setupUi(this);
    setFixedSize(500, 470);
    ui->frame->setFixedSize(500, 470);

    ui->playersSpinBox->adjustSize();

    QRect parentRect = parent->rect();
    QPoint parentTopLeft = parent->mapToGlobal(parentRect.topLeft());

    int x = parentTopLeft.x() + (parentRect.width() - this->width()) / 2;
    int y = parentTopLeft.y() + (parentRect.height() - this->height()) / 2;

    this->move(x, y);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    connect(ui->closeButton, &QPushButton::clicked, this, &NewGameWindow::close);
    connect(ui->cancelButton, &QPushButton::clicked, this, &NewGameWindow::close);

    this->setStyleSheet(R"(QPushButton {
        background-color: #7e8c72;
        border-top: 2px solid #d7dacd;
        border-left: 2px solid #d7dacd;
        border-bottom: 2px solid #4a4a4a;
        border-right: 2px solid #4a4a4a;
        padding: 4px 10px;
        color: white;

        font-family: "Verdana";
    }

    QPushButton:hover {
        background-color: #96a783;
    }

    QPushButton:pressed {
        border-top: 2px solid #4a4a4a;
        border-left: 2px solid #4a4a4a;
        border-bottom: 2px solid #d7dacd;
        border-right: 2px solid #d7dacd;
        background-color: #6b7960;
    }
    )");

    ui->mapSelector->addItem("Opción 1");
    ui->mapSelector->addItem("Opción 2");
    ui->mapSelector->addItem("Opción 3");
}

NewGameWindow::~NewGameWindow()
{
    delete ui;
}
