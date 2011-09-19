#ifndef ARAWNWINDOW_HPP
#define ARAWNWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class ArawnWindow;
}

class ArawnWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArawnWindow(QWidget *parent = 0);
    ~ArawnWindow();

private:
    Ui::ArawnWindow *ui;
};

#endif // ARAWNWINDOW_HPP
