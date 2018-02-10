#ifndef POPOVER_H
#define POPOVER_H

#include <QObject>
#include <QDialog>

class QTimer;

class Popover
        : public QDialog
{
    Q_OBJECT

public:
    Popover(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
    void focusOutEvent(QFocusEvent *event);
    void showEvent(QShowEvent *event);
    bool event(QEvent *e);

private slots:
    void on_lazyShowWindow();

private:
    QTimer *lazyShowWindow;
};

#endif // POPOVER_H
