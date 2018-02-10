#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QWidget>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}
class TaskTrayPopup;

class MainWindow
    : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    //void focusInEvent(QFocusEvent *event);
    //bool event(QEvent *e);

private slots:
    void on_pushButton_clicked();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onTrayMessageClicked();
    void onToggleMainWindow();

private:
    //Ui::MainWindow *ui;
    QSystemTrayIcon* trayIcon;
    TaskTrayPopup* taskTrayPopup;
};

#endif // MAINWINDOW_H
