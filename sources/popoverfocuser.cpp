#include "popoverfocuser.h"


Focuser::PopoverFocuser(QWidget *w)
{
    this->widget = w;
}

void PopoverFocuser::show()
{
    this->widget->show();
    this->focus();
}

void PopoverFocuser::focus()
{
    this->widget->activateWindow();
    this->widget->raise();
}
