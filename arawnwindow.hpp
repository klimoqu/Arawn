#ifndef ARAWNWINDOW_HPP
#define ARAWNWINDOW_HPP

#include <QtGui/QtGui>


class ArawnWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(uchar volume READ Volume WRITE SetVolume)

public:
    ArawnWindow(QWidget *parent = 0);

//    void InitializeWindow();
//    void InitializeSettings();
//    void InitializeEssentialResources();

protected:
    void closeEvent(QCloseEvent *);


};

#endif // ARAWNWINDOW_HPP
