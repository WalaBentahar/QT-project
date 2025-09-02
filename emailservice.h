#ifndef EMAILSERVICE_H
#define EMAILSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QDate>

class EmailService : public QObject
{
    Q_OBJECT

public:
    explicit EmailService(QObject *parent = nullptr);

    struct CommandInfo
    {
        int commandId;
        QString clientName;
        QString clientEmail;
        QDate commandDate;
        QString deliveryAddress;
        QString status;
        double amount;
    };

    void sendCommandConfirmationEmail(const CommandInfo &command);

signals:
    void emailSent(bool success, const QString &message);

private slots:
    void onEmailReplyFinished();

private:
    QNetworkAccessManager *networkManager;
    QString generateEmailTemplate(const CommandInfo &command);
    QJsonObject createEmailPayload(const QString &toEmail, const QString &subject, const QString &htmlContent);

    static const QString RAPIDAPI_KEY;
    static const QString RAPIDAPI_HOST;
    static const QString RAPIDAPI_URL;
};

#endif // EMAILSERVICE_H
