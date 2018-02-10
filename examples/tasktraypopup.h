#ifndef TASKTRAYPOPUP_H
#define TASKTRAYPOPUP_H

#include "popover.h"

namespace Ui {
class TaskTrayPopup;
}

class TaskTrayPopup
        : public Popover
{
    Q_OBJECT

public:
    explicit TaskTrayPopup(QWidget *parent = 0);
    ~TaskTrayPopup();

signals:
    void toggleMainWindow();

private slots:
    void on_exitButton_clicked();
    void on_toggleMainWindowButton_clicked();

private:
    Ui::TaskTrayPopup *ui;
};

#endif // TASKTRAYPOPUP_H
