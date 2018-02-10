#include "mainwindow.h"
#include <QApplication>
#include <QMessageLogger>
#include <QDebug>
#include <QTime>

void TimestampedDebugOutput(QtMsgType type, const QMessageLogContext & /*context*/, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch(type){
    case QtDebugMsg:
        QMessageLogger("", -1, 0).debug() << QTime::currentTime().toString("hh:mm:ss.zzz") << "DEBUG:" << localMsg.constData();
        break;
    case QtInfoMsg:
        QMessageLogger("", -1, 0).info() << QTime::currentTime().toString("hh:mm:ss.zzz") << "INFO:" << localMsg.constData();
        break;
    case QtWarningMsg:
        QMessageLogger("", -1, 0).warning() << QTime::currentTime().toString("hh:mm:ss.zzz") << "WRNING:" << localMsg.constData();
        break;
    case QtCriticalMsg:
        QMessageLogger("", -1, 0).critical() << QTime::currentTime().toString("hh:mm:ss.zzz") << "CRITICAL:" << localMsg.constData();
        break;
    case QtFatalMsg:
        QMessageLogger("", -1, 0).critical() << QTime::currentTime().toString("hh:mm:ss.zzz") << "FATAL:" << localMsg.constData();
        abort();
    }
}

int main(int argc, char *argv[])
{
#ifndef QT_NO_DEBUG
    qInstallMessageHandler(TimestampedDebugOutput);
#endif

    QApplication::setQuitOnLastWindowClosed(false);
    QApplication a(argc, argv);

    MainWindow w;
    //w.show();

    return a.exec();
}
