#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocalSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

    void on_exitButton_clicked();

    void on_computeButton_clicked();

    void on_breakButton_clicked();

private:
    Ui::MainWindow *ui;
    QLocalSocket localSocket;
    bool DisconnectSocket();
};
#endif // MAINWINDOW_H
