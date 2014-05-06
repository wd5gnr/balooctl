/*
 * balooctl - Monitor and control baloo file indexing
    Copyright (C) 2014  Al Williams al.williams@awce.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

Yes this should use QtDbus but this is a very quick hack. I may or may not
fix it later.
*/

// Polling time in seconds (or 0 to operate only on demand)
#define SCAN_TIME 30


#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusReply>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    bus("Session")
{
    bus= QDBusConnection::sessionBus();
    iface= new QDBusInterface("org.kde.baloo.file","/indexer","org.kde.baloo.file",bus,this);
    ui->setupUi(this);
    updateresult();
    QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(updateresult()));
#if SCAN_TIME != 0
     timer->start(SCAN_TIME*1000);
#endif
}


void MainWindow::updateresult()
{
    QString result;
    QString prefix;
    QDBusReply<QString> reply=iface->call("statusMessage");
    if (reply.isValid())
    {
        result=reply.value();
    }
    else
    {
        result=reply.error().message();
    }
    prefix=result.mid(0,8);
    if (prefix=="Indexing") ui->checkBox->setChecked(true); else ui->checkBox->setChecked(false);
    ui->status->setText(result);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked) iface->call("resume"); else iface->call("suspend");
    updateresult();

}
