#include "accountutils.h"
#include <QDebug>
#include <QStandardPaths>
#include <QMessageBox>
#include <QTextCodec>
#include <QApplication>
#include "mainwindow.h"


accountUtils::accountUtils(QObject *parent) : QObject(parent)
{
    settings.setObjectName("settings");
    setting_path =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);
}


//check purchased
void accountUtils::check_purchased(QString username){
    QNetworkRequest newRequest;
    newRequest.setUrl(QUrl("http://www.ktechpit.com/USS/WW/accounts/html/chkout/check.php?username="+username));

    QNetworkAccessManager *networkManager =new QNetworkAccessManager;
    QNetworkReply *reply = networkManager->get(newRequest);
    const bool connected = connect(reply,SIGNAL(finished()),this,SLOT(check_purchase_request_done()));
    qDebug()<<"ACCOUNT_UTILS"<<"Checking account for:"<<username<<connected;
}

void accountUtils::check_purchase_request_done(){
    qDebug()<<"ACCOUNT_UTILS"<<"check Purchase requestDone";
    QNetworkReply *reply = ((QNetworkReply*)sender());
    QNetworkRequest request = reply->request();
    QString username = request.url().toString().split("user=").last();
    QByteArray ans= reply->readAll();
    QString s_data = QTextCodec::codecForMib(106)->toUnicode(ans);  //106 is textcode for UTF-8 here --- http://www.iana.org/assignments/character-sets/character-sets.xml

    if(reply->error()== QNetworkReply::NoError){
         if(s_data.contains("true")){
            settings.setValue("account_created",true);
            qDebug()<<"ACCOUNT_UTILS"<<"Checked account for:"<<username;
            emit purchase_checked(username+"-"+s_data);
        }else if(s_data.contains("false")){
            QMessageBox msgBox;
            msgBox.setText("<b>Account type is Evaluation</b>");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setInformativeText("");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setWindowModality(Qt::ApplicationModal);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret= msgBox.exec();
            switch (ret){
            case QMessageBox::Ok:
                 msgBox.accept();
                break;
            default:
                 msgBox.accept();
                break;
            }
          emit purchase_checked(username+"-"+s_data);
        }
    }else{
        emit purchase_checked(username+"-"+s_data);
    }
}
