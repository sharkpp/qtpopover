#ifndef POPOVER_FOCUSER_H
#define POPOVER_FOCUSER_H

#include <QWidget>

class PopoverFocuser {
    QWidget *widget;
public:
    PopoverFocuser(QWidget *);
    void show();
    void focus();
};

#endif // POPOVER_FOCUSER_H
