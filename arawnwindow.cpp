#include "arawnwindow.hpp"
#include "ui_arawnwindow.h"

ArawnWindow::ArawnWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArawnWindow)
{
    ui->setupUi(this);
}

ArawnWindow::~ArawnWindow()
{
    delete ui;
}
