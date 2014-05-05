#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cmd="qdbus org.kde.baloo.file /indexer org.kde.baloo.file.statusMessage";
    proc.start(cmd);
    updateresult();
    QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateresult()));
     timer->start(10000);
}


void MainWindow::updateresult()
{
    QString result;
    QString prefix;
    proc.waitForFinished();
    result=QString(proc.readAll());
    prefix=result.mid(0,8);
    if (prefix=="Indexing") ui->checkBox->setChecked(true); else ui->checkBox->setChecked(false);
    ui->status->setText(result);
    proc.start(cmd);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    QProcess *qdbus=new QProcess(this);
    QString cmdline="qdbus org.kde.baloo.file /indexer org.kde.baloo.file.";
    cmdline+=checked?"resume":"suspend";
    qdbus->start(cmdline);
    qdbus->waitForFinished();
    // need to throw away the possibly stale result
    proc.waitForFinished();
    proc.readAll();
    proc.start(cmd);
    updateresult();

}
