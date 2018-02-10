#include "tasktraypopup.h"
#include "ui_tasktraypopup.h"
#include <QApplication>
#include <QDate>
#include <QDebug>

TaskTrayPopup::TaskTrayPopup(QWidget *parent)
    : Popover(parent)
    , ui(new Ui::TaskTrayPopup)
{
    ui->setupUi(this);
    adjustSize();
}

TaskTrayPopup::~TaskTrayPopup()
{
    delete ui;
}

void TaskTrayPopup::on_exitButton_clicked()
{
    QApplication::quit();
}

void TaskTrayPopup::on_toggleMainWindowButton_clicked()
{
    emit toggleMainWindow();
}
