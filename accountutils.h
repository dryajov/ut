#ifndef ACCOUNTUTILS_H
#define ACCOUNTUTILS_H

#include <QObject>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "ui_settings.h"

class accountUtils : public QObject
{
    Q_OBJECT
public:
    explicit accountUtils(QObject *parent = 0);
    QSettings settings;
    QString setting_path;

signals:
   void creating_account(QString);
   void purchase_checked(QString);

public slots:
   void check_purchased(QString);
private slots:
   void check_purchase_request_done();
private:
   Ui::settings settingsUi;

};

#endif // ACCOUNTUTILS_H
