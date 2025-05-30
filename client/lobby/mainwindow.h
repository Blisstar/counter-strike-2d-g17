#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QPixmap>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showMenuButtons(bool show);

private slots:
    void on_newgameButton_clicked();

    void on_findserversButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
