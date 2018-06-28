#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork>
#include <QTimer>
#include <QVBoxLayout>
#include <QVector>
#include "hmuser.h"
#include<QMovie>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setPage(int index);
private slots:
    void serverConnection(QNetworkReply *);
//    void serverConnection(QString);
    void run();

    void checkConnection();
    //pushbotton clicks
    void on_welcom_startMessanging_clicked();
    void on_start_signUp_clicked();
    void on_start_signIn_clicked();
    void on_signUp_signUp_clicked();
    void on_signUp_back_clicked();
    void on_signIn_back_clicked();
    void on_signIn_signIn_clicked();

private:
    Ui::MainWindow *ui;
    QJsonObject jsb;
    QNetworkAccessManager *manager;
    QNetworkRequest request;

    //mainuser

    HmUser *_mainUser;




};

#endif // MAINWINDOW_H
