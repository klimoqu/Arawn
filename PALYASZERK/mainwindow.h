#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QMainWindow>
#include <QModelIndex>
#include <QTableWidgetItem>
#include <vector>
#include <QDir>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_tableWidget_pressed(const QModelIndex &index);

    void on_nehezdoboz_pressed();

    void on_ur_pressed();

    void on_fu_pressed();

    void on_fal_pressed();

    void on_doboz_pressed();

    void on_lyuk_pressed();

    void mentes();

    void betoltes();

    void newMap();

    void on_ok_clicked();

    void on_cancel_clicked();

    void changedType();

private:
    Ui::MainWindow *ui;
    qint32 type;
    std::vector<std::vector<QString> > elem;

    void load(QString nev);

};

#endif // MAINWINDOW_H
