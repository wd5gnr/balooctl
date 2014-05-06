#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>


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
    void updateresult(void);


    void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QProcess proc;
    QString cmd;
    QDBusConnection bus;
    QDBusInterface *iface;
};

#endif // MAINWINDOW_H
