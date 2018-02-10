#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tasktraypopup.h"
#include <QSystemTrayIcon>
#include <QShowEvent>
#include <QDesktopWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
    , taskTrayPopup(nullptr)
{
    hide();
    setFocusPolicy(Qt::StrongFocus);
    //ui->setupUi(this);

    trayIcon = new QSystemTrayIcon(this);
    //trayIcon->setContextMenu(trayIconMenu);

    QIcon icon = QApplication::style()->standardIcon( QStyle::SP_TitleBarMenuButton );
    trayIcon->setIcon(icon);

    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::onTrayMessageClicked);
    connect(trayIcon, &QSystemTrayIcon::activated,      this, &MainWindow::onTrayIconActivated);

    trayIcon->show();
}

MainWindow::~MainWindow()
{
    delete taskTrayPopup;
    //delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    event->ignore();

    hide();
}

void MainWindow::showEvent(QShowEvent * /*event*/)
{
    //event->ignore();
}

void MainWindow::on_pushButton_clicked()
{
    //QRect rc = ui->pushButton->rect();
    //CalendarPopup dlg;
    //dlg.exec();

}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    qDebug() << "MainWindow::onTrayIconActivated" << reason << taskTrayPopup;
    switch (reason) {
    case QSystemTrayIcon::Trigger: {
        qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << taskTrayPopup;
        if (!taskTrayPopup) {
            qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << taskTrayPopup;
            taskTrayPopup = new TaskTrayPopup();
            connect(taskTrayPopup, &TaskTrayPopup::toggleMainWindow, this, &MainWindow::onToggleMainWindow);
            QRect rcTray = trayIcon->geometry();
            QRect rc = taskTrayPopup->geometry();
            qDebug() << rcTray << rc;
            rc.setRect(rcTray.left() - (rc.width()-rcTray.width())/2, rcTray.bottom(), rc.width(), rc.height());
            taskTrayPopup->setGeometry(rc);
            taskTrayPopup->exec();
            qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << taskTrayPopup;
        }
        else {
            qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << taskTrayPopup;
            taskTrayPopup->close();
            qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << taskTrayPopup;
        }
        qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << taskTrayPopup;
        delete taskTrayPopup;
        taskTrayPopup = nullptr;
        qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << taskTrayPopup;
        break; }
    case QSystemTrayIcon::DoubleClick:
        //iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1) % iconComboBox->count());
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void MainWindow::onTrayMessageClicked()
{
    qDebug() << "MainWindow::onTrayMessageClicked" << __LINE__ << taskTrayPopup;
}

void MainWindow::onToggleMainWindow()
{
    if (taskTrayPopup) {
        taskTrayPopup->close();
        delete taskTrayPopup;
        taskTrayPopup = nullptr;
    }

    qDebug() << "MainWindow::onToggleMainWindow" << __LINE__ << taskTrayPopup << isVisible();
    if (!isVisible()) {
        show();
        activateWindow();
    }
    else {
        hide();
    }
}

#if 0
void MainWindow::focusInEvent(QFocusEvent * /*event*/)
{
    qDebug() << "MainWindow::focusInEvent";

}

bool MainWindow::event(QEvent *e)
{
    qDebug() << "MainWindow::event" << e->type() << qApp->activeWindow() << (qApp->activeWindow() == this ? "AM" : "AM NOT");
    switch ( e->type() )
    {
    case QEvent::WindowActivate:
        qDebug( "WindowActivate - I %s the active window!", qApp->activeWindow() == this ? "AM" : "AM NOT" );
        break;
    default:
        break;
    }
    return QMainWindow::event(e) ;
}
#endif
