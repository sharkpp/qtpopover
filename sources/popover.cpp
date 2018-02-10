#include "popover.h"
#include "popoverfocuser.h"
#include <QBitmap>
#include <QPainter>
#include <QRegularExpression>
#include <QEvent>
#include <QTimer>
#include <QDebug>
#include <QApplication>

Popover::Popover(QWidget *parent)
    : QDialog(parent)
    , lazyShowWindow(new QTimer(this))
{
    qDebug() << "Popover::Popover()";

    connect(lazyShowWindow, SIGNAL(timeout()), this, SLOT(on_lazyShowWindow()));

    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

void Popover::resizeEvent(QResizeEvent *)
{
    QRect wndRect = rect();

    // *__/\___  * = 原点
    // |      |  時計回りに描画
    // +------+

    const int FUKIDASHI_HEIGHT = 15;
    const int FUKIDASHI_WIDTH  = 30;

    // 吹き出しの矢印分をずらす
    QString ss = styleSheet();
    ss.replace(QRegularExpression("\\s*margin-top\\s*:\\s*.+?;"), "");
    setStyleSheet(QString("%1 margin-top: %2px;").arg(ss).arg(FUKIDASHI_HEIGHT));

    // 吹き出しの形にウインドウの形を加工
    QPolygon poly;
    poly  << QPoint(wndRect.x(), wndRect.y() + FUKIDASHI_HEIGHT)
          << QPoint(wndRect.x() + wndRect.width() / 2 - FUKIDASHI_WIDTH / 2, wndRect.y() + FUKIDASHI_HEIGHT)
          << QPoint(wndRect.x() + wndRect.width() / 2, wndRect.y())
          << QPoint(wndRect.x() + wndRect.width() / 2 + FUKIDASHI_WIDTH / 2, wndRect.y() + FUKIDASHI_HEIGHT)
          << QPoint(wndRect.x() + wndRect.width(), wndRect.y() + FUKIDASHI_HEIGHT)
          << QPoint(wndRect.x() + wndRect.width(), wndRect.y() + wndRect.height())
          << QPoint(wndRect.x(), wndRect.y() + wndRect.height())
          //<< QPoint(wndRect.x(), wndRect.y() + FUKIDASHI_HEIGHT)
             ;
    QRegion newMask(poly);
    setMask(newMask);
}

bool Popover::event(QEvent *e)
{
//    qDebug() << "Popover::event" << e->type();
    qDebug() << "Popover::event" << e->type() << QApplication::activeWindow() << (QApplication::activeWindow() == this ? "AM" : "AM NOT");
    if (QEvent::WindowDeactivate == e->type()) {
        qDebug() << "Popover::event" << __LINE__;
        done(0);
        e->ignore();
        return true;
    }
    return QDialog::event(e) ;
}

void Popover::focusOutEvent(QFocusEvent * /*event*/)
{
    qDebug() << "Popover::focusOutEvent";
    //done(0);
}

void Popover::showEvent(QShowEvent * /*event*/)
{
    qDebug() << "Popover::showEvent";
    //activateWindow();
    //setFocus();
    //lazyShowWindow->start(10000);
    PopoverFocuser f(this);
    f.focus();
}

void Popover::on_lazyShowWindow()
{
    activateWindow();
    setFocus();

}

