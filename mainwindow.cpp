#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager=new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(serverConnection(QNetworkReply*)));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkConnection()));
    timer->start(1000);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::checkConnection()
{
    QNetworkAccessManager *nam=new QNetworkAccessManager;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam->get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if(reply->bytesAvailable())
    {
        ui->statusBar->showMessage("connected");
    }
    else
       {
        ui->statusBar->showm("conecting ...");
    }
}

void MainWindow::serverConnection(QNetworkReply *reply)
{
    QString data=(QString) reply->readAll();
    QJsonDocument jsd=QJsonDocument::fromJson(data.toUtf8());
    jsb=jsd.object();
}

void MainWindow::setPage(int index)
{
    ui->main->setCurrentIndex(index);
}

void MainWindow::on_welcom_startMessanging_clicked()
{
    ui->main->setCurrentIndex(1);
}

void MainWindow::on_start_signUp_clicked()
{
    ui->main->setCurrentIndex(2);
}

void MainWindow::on_start_signIn_clicked()
{
    ui->main->setCurrentIndex(3);
}


void MainWindow::on_signUp_signUp_clicked()
{
    ui->signUp_errBox->setStyleSheet("color : red;border-style: none none solid none;");

    if(ui->signUp_username->text()=="")
    {
        ui->signUp_errBox->move(260,160);
        ui->signUp_errBox->setText("* Choose an username");
    }
    else if(ui->signUp_password->text()=="")
    {
        ui->signUp_errBox->move(260,220);
        ui->signUp_errBox->setText("* Enter a password");
    }
    else if(ui->signUp_confirmPassword->text()=="")
    {
        ui->signUp_errBox->move(380,220);
        ui->signUp_errBox->setText("* Confirm your password");
    }
    else if(ui->signUp_confirmPassword->text()!=ui->signUp_password->text())
    {
        ui->signUp_errBox->move(380,220);
        ui->signUp_errBox->setText("* Those passwords didn't match.\nTry again.");
        ui->signUp_confirmPassword->setText("");
    }
    else
    {
        QString r="http://api.softserver.org:1104/";
        request.setUrl(QUrl(r+"signup?username="+ui->signUp_username->text()+"&password="+ui->signUp_password->text()
                             +"&firstname="+ui->signUp_firstName->text()+"&lastname="+ui->signUp_lastName->text()));
        QNetworkReply *reply = manager->get(request);
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        if(jsb["code"].toString()=="200")
        {
            ui->main->setCurrentIndex(1);
        }
        else if (jsb["code"].toString()=="204")
        {
            ui->signUp_errBox->move(260,160);
            ui->signUp_errBox->setText("* That username is taken. please try again");
            ui->signUp_username->setText("");
        }
    }

}

void MainWindow::on_signUp_back_clicked()
{
    ui->main->setCurrentIndex(1);
}

void MainWindow::on_signIn_back_clicked()
{
    ui->main->setCurrentIndex(1);
}

void MainWindow::on_signIn_signIn_clicked()
{

    QString r="http://api.softserver.org:1104/";
    request.setUrl(QUrl(r+"login?username="+ui->signIn_username->text()+"&password="+ui->signIn_password->text()));
    QNetworkReply *reply = manager->get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(jsb["message"].toString()=="Logged in Successfully")
    {
        ui->main->setCurrentIndex(4);

        QString ttoken=jsb["token"].toString();

        QString r="http://api.softserver.org:1104/";
        request.setUrl(QUrl(r+"getname?username="+ui->signIn_username->text()));
        QNetworkReply *reply = manager->get(request);
        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        _mainUser=new HmUser(ui->signIn_username->text(),ui->signIn_password->text(),ttoken
                                ,jsb["firstname"].toString(),jsb["lastname"].toString());
        run();
    }
    else if (jsb["message"].toString()=="You are already logged in!")
    {
        ui->signIn_errBox->setText("some one else is in this account");
        ui->signUp_password->setText("");
    }
    else if (jsb["message"].toString()== "Password is not Correct")
    {
        ui->signIn_errBox->setText("psssword is not correct");
        ui->signUp_password->setText("");
    }
    else if (jsb["message"].toString()=="User Not Found")
    {
        ui->signIn_errBox->setText("user not found");
        ui->signUp_password->setText("");
        ui->signUp_username->setText("");
    }
}

void MainWindow::run()
{
    QVBoxLayout * layout =new QVBoxLayout;
    const QString block = "block ";
    QString num;

    QString r="http://api.softserver.org:1104/";
    request.setUrl(QUrl(r+"getchannellist?token="+_mainUser->get_token()));
    QNetworkReply *reply = manager->get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    num="";
    for(int i=12 ; jsb["message"].toString()[i]!='-' ; i++)
        num=num+jsb["message"].toString()[i];

    for(int i=0 ; i<num.toInt() ; i++)
    {
        QJsonObject jsblocks = jsb.value(block+QString::number(i)).toObject();
        Hdestination *tchannel=new Hchannel(jsblocks.value("channel_name").toString() , jsblocks.value("channel_title").toString());
        tchannel->setText(jsblocks.value("channel_name").toString());
        layout->insertWidget(0,tchannel);
        tchannel->setFixedSize(150,120);
        _mainUser->add_dst(tchannel);
    }




  /*  Hdestination * btn = new Hdestination("yy","yy","");
            btn->setFixedSize(150,120);
            btn->setText("Hello world");
            layout->addWidget(btn,0,Qt::AlignCenter);
            layout->insertWidget(0,btn,0,Qt::AlignRight);
            layout->setAlignment(btn,Qt::AlignHCenter);*/

    QWidget *x=new QWidget;
    x->setLayout(layout);
    ui->scrollArea->setWidget(x);
}
