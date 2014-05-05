#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

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
};

#endif // MAINWINDOW_H
