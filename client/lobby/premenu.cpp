#include "premenu.h"
#include "ui_premenu.h"

#include <QMessageBox>
#include <QPushButton>

PreMenu::PreMenu(QWidget *parent)
    : QDialog(parent), ui(new Ui::PreMenu)
{
    ui->setupUi(this);
    setModal(true);

    setFixedSize(400, 370);
    ui->frame->setFixedSize(400, 370);

    QRect parentRect = parent->rect();
    QPoint parentTopLeft = parent->mapToGlobal(parentRect.topLeft());

    int x = parentTopLeft.x() + (parentRect.width() - this->width()) / 2;
    int y = parentTopLeft.y() + (parentRect.height() - this->height()) / 2;

    this->move(x, y);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->setStyleSheet(R"(QPushButton {
        background-color: #7e8c72;
        border-top: 2px solid #d7dacd;
        border-left: 2px solid #d7dacd;
        border-bottom: 2px solid #4a4a4a;
        border-right: 2px solid #4a4a4a;
        padding: 4px 10px;
        color: white;
        font-weight: bold;
        font: 700 "Trebuchet MS";
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

    connect(ui->closeButton, &QPushButton::clicked, this, &QDialog::reject);

    connect(ui->acceptButton, &QPushButton::clicked, this, [=]() {
        if (ui->ipInput->text().isEmpty() || ui->portInput->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Completá IP y puerto.");
            return;
        }
        accept();
    });


}

PreMenu::~PreMenu()
{
    delete ui;
}

void PreMenu::on_closeButton_clicked()
{
    QApplication::quit();

}
