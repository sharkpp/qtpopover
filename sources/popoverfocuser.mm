#include "popoverfocuser.h"
#import <Cocoa/Cocoa.h>

PopoverFocuser::PopoverFocuser(QWidget *w)
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
    // https://developer.apple.com/documentation/appkit/nsapplication/1428468-activateignoringotherapps
    [NSApp activateIgnoringOtherApps:YES];

    this->widget->activateWindow();
    this->widget->raise();
}
