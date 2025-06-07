#include "newgamewindow.h"
#include "ui_newgamewindow.h"
#include "waitinghostwindow.h"

#include <QStyledItemDelegate>
#include <QPainter>


class NoHighlightDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override {
        QStyleOptionViewItem opt(option);
        initStyleOption(&opt, index);

        if (opt.state & QStyle::State_Selected) {
            opt.state &= ~QStyle::State_Selected;
            opt.state &= ~QStyle::State_HasFocus;

            QPalette palette = opt.palette;
            palette.setColor(QPalette::Highlight, Qt::transparent);
            palette.setColor(QPalette::HighlightedText, palette.color(QPalette::Text));
            opt.palette = palette;
        }

        QStyledItemDelegate::paint(painter, opt, index);

        if (option.state & QStyle::State_Selected) {
            painter->save();
            QPen pen(QColor("#bfa949"));
            pen.setWidth(2);
            painter->setPen(pen);
            painter->drawRect(option.rect.adjusted(1, 1, -2, -2));
            painter->restore();
        }
    }
};


NewGameWindow::NewGameWindow(ClientProtocol& _clientProtocol, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewGameWindow)
    , clientProtocol(_clientProtocol)
{
    ui->setupUi(this);
    setFixedSize(500, 540);
    ui->frame->setFixedSize(500, 540);

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

    ui->mapList->setItemDelegate(new NoHighlightDelegate(ui->mapList));

    ui->mapList->setViewMode(QListView::IconMode);
    ui->mapList->setIconSize(QSize(100, 80));
    ui->mapList->setResizeMode(QListView::Adjust);
    ui->mapList->setSelectionMode(QAbstractItemView::SingleSelection);

    QListWidgetItem *mapDust = new QListWidgetItem(QIcon("../media/dust.jpg"), "Dust2");
    mapDust->setSizeHint(QSize(120, 90));
    QListWidgetItem *mapAztec = new QListWidgetItem(QIcon("../media/aztec.jpeg"), "Aztec");
    mapAztec->setSizeHint(QSize(120, 90));
    QListWidgetItem *mapNuke = new QListWidgetItem(QIcon("../media/nuke.jpeg"), "Nuke");
    mapNuke->setSizeHint(QSize(120, 90));

    ui->mapList->setIconSize(QSize(100, 70));

    QFont font;
    font.setPointSize(13);
    mapNuke->setFont(font);
    mapAztec->setFont(font);
    mapDust->setFont(font);

    mapNuke->setForeground(QBrush(QColor("#bfa949")));
    mapAztec->setForeground(QBrush(QColor("#bfa949")));
    mapDust->setForeground(QBrush(QColor("#bfa949")));

    ui->mapList->addItem(mapDust);
    ui->mapList->addItem(mapAztec);
    ui->mapList->addItem(mapNuke);
}

NewGameWindow::~NewGameWindow()
{
    delete ui;
}


void NewGameWindow::on_startButton_clicked()
{
    QListWidgetItem* selectedItem = ui->mapList->currentItem();
    if (selectedItem) {
        std::string gameName =  ui->inputGameName->text().toStdString();
        int index = ui->mapList->row(selectedItem);
        std::string playerName =  ui->inputPlayerName->text().toStdString();
        
        clientProtocol.send_message(ClientMessage(ClientMessageType::CreateGame, CreateGame(gameName, index, playerName)));

        WaitingHostWindow *win = new WaitingHostWindow(clientProtocol, this->parentWidget());
        win->setWindowModality(Qt::ApplicationModal);
        win->show();

        this->close();
        this->deleteLater();
    }
    
}

