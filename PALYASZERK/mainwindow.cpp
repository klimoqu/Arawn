#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->fu->setStyleSheet("QPushButton {color: black; background-color: rgb(0, 255, 127);}");

    ui->lista->setEnabled(false);
    ui->ok->setEnabled(false);
    ui->cancel->setEnabled(false);

    ui->lista->setVisible(false);
    ui->ok->setVisible(false);
    ui->cancel->setVisible(false);
    ui->frameLoad->setVisible(false);

    type = 2;
    elem.resize(20);
    for(int j=0;j<20;j++) elem[j].resize(13, "2");

    for(int z=0;z<ui->tableWidget->rowCount();z++)//13
    {
        for(int u=0;u<ui->tableWidget->columnCount();u++)//20
        {
            QTableWidgetItem *id = new QTableWidgetItem();
            id->setIcon(QIcon(QPixmap("pic/field" + elem[u][z] + ".png")));
            ui->tableWidget->setItem(z, u, id);
        }
    }
    ui->tableWidget->setIconSize(QSize(33,33));

    ui->actionBetoltes->setIcon(QIcon(QPixmap("pic/mappa.png")));
    ui->actionMentes->setIcon(QIcon(QPixmap("pic/floppy.png")));

    connect(ui->actionBetoltes, SIGNAL(triggered()), this, SLOT(betoltes()));
    connect(ui->actionMentes, SIGNAL(triggered()), this, SLOT(mentes()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newMap()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->doboz,SIGNAL(clicked()), this, SLOT(changedType()));
    connect(ui->fal,SIGNAL(clicked()), this, SLOT(changedType()));
    connect(ui->fu,SIGNAL(clicked()), this, SLOT(changedType()));
    connect(ui->lyuk,SIGNAL(clicked()), this, SLOT(changedType()));
    connect(ui->ur,SIGNAL(clicked()), this, SLOT(changedType()));
    connect(ui->nehezdoboz,SIGNAL(clicked()), this, SLOT(changedType()));
}

void MainWindow::newMap()
{
    type = 2;
    elem.resize(0);
    elem.resize(20);
    for(int j=0;j<20;j++) elem[j].resize(13, "2");

    for(int z=0;z<ui->tableWidget->rowCount();z++)//13
    {
        for(int u=0;u<ui->tableWidget->columnCount();u++)//20
        {
            qDebug()<<elem[u][z];
            ui->tableWidget->item(z,u)->setIcon(QIcon(QPixmap("pic/field" + elem[u][z] + ".png")));
        }
    }
}

void MainWindow::changedType()
{
    QPushButton *qps = (QPushButton*)sender();

    ui->doboz->setStyleSheet("QPushButton {color: black;}");
    ui->ur->setStyleSheet("QPushButton {color: black;}");
    ui->nehezdoboz->setStyleSheet("QPushButton {color: black;}");
    ui->lyuk->setStyleSheet("QPushButton {color: black;}");
    ui->fu->setStyleSheet("QPushButton {color: black;}");
    ui->fal->setStyleSheet("QPushButton {color: black;}");

    qps->setStyleSheet("QPushButton {color: blue; background-color: rgb(0, 255, 127);}");
}

void MainWindow::mentes()
{
    QDir d(QDir::currentPath()+"/maps/");

    QStringList e = d.entryList();
    QString max = e.first();
    foreach(QString str, e) if(str > max) max = str;

    int nev = max.split(".").first().toInt() + 1;
    QString ujnev = QString::number(nev);
    if(nev<10) ujnev.push_front("0");
    if(nev<100) ujnev.push_front("0");

    ujnev.push_back(".map");

    QFile f("maps/"+ujnev);
    if(f.open(QIODevice::WriteOnly))
    {
        QTextStream out(&f);
        for(int j=0;j<20;j++){
            for(int k=0;k<13;k++){
                out << elem[j][k];
                if(k<12) out << " ";
            }
            if(j<19) out << "\n";
        }
    }
    f.close();
}

void MainWindow::load(QString nev)
{
        elem.resize(0);

        QFile f("maps/"+nev);
        if(f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&f);
            while(!in.atEnd())
            {
                QString line = in.readLine();
                elem.push_back(line.split(" ").toVector().toStdVector());
            }

            for(int z=0;z<ui->tableWidget->rowCount();z++)//13
            {
                for(int u=0;u<ui->tableWidget->columnCount();u++)//20
                {
                    ui->tableWidget->item(z,u)->setIcon(QIcon(QPixmap("pic/field" + elem[u][z] + ".png")));
                }
            }
        }
        f.close();
}

void MainWindow::betoltes()
{
    QDir d(QDir::currentPath()+"/maps/");
    QStringList e = d.entryList().filter(QRegExp("[0-9]*.map"));
    ui->lista->clear();
    ui->lista->addItems(e);

    QPalette palette = ui->frameLoad->palette();
    palette.setColor( backgroundRole(), QColor( 100, 100, 100 ) );
    ui->frameLoad->setPalette( palette );
    ui->frameLoad->setAutoFillBackground( true );

    ui->lista->setEnabled(true);
    ui->ok->setEnabled(true);
    ui->cancel->setEnabled(true);

    ui->lista->setVisible(true);
    ui->ok->setVisible(true);
    ui->cancel->setVisible(true);
    ui->frameLoad->setVisible(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_pressed(const QModelIndex &index)
{
    int s, o;

    s = ui->tableWidget->currentItem()->row();
    o = ui->tableWidget->currentItem()->column();

    if(!(
          (o == 0 && (s <= 2 || s >= 10)) ||
          (o == 1 && (s <= 0 || s >= 12)) ||
          (o == 2 && (s <= 0 || s >= 12)) ||
          (o == 17 && (s <= 0 || s >= 12)) ||
          (o == 18 && (s <= 0 || s >= 12)) ||
          (o == 19 && (s <= 2 || s >= 10))
       ))
    {
        ui->tableWidget->currentItem()->setIcon(QIcon(QPixmap("pic/field"+QString::number(type)+".png")));
        elem[ui->tableWidget->currentItem()->column()][ui->tableWidget->currentItem()->row()] = QString::number(type);
    }
}


void MainWindow::on_fal_pressed()        { type = 0; }
void MainWindow::on_doboz_pressed()      { type = 1; }
void MainWindow::on_fu_pressed()         { type = 2; }
void MainWindow::on_nehezdoboz_pressed() { type = 3; }
void MainWindow::on_ur_pressed()         { type = 4; }
void MainWindow::on_lyuk_pressed()       { type = 5; }

void MainWindow::on_ok_clicked()
{
    ui->lista->setEnabled(false);
    ui->ok->setEnabled(false);
    ui->cancel->setEnabled(false);

    ui->lista->setVisible(false);
    ui->ok->setVisible(false);
    ui->cancel->setVisible(false);
    ui->frameLoad->setVisible(false);

    load(ui->lista->currentText());
}

void MainWindow::on_cancel_clicked()
{
    ui->lista->setEnabled(false);
    ui->ok->setEnabled(false);
    ui->cancel->setEnabled(false);

    ui->lista->setVisible(false);
    ui->ok->setVisible(false);
    ui->cancel->setVisible(false);
    ui->frameLoad->setVisible(false);
}
