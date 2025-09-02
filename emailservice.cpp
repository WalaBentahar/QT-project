#include "emailservice.h"
#include <QDebug>
#include <QUrlQuery>
#include <QJsonArray>

const QString EmailService::RAPIDAPI_KEY = "f9debc9ff2msh946dd00ab5714abp158c43jsnd587eec5858c";
const QString EmailService::RAPIDAPI_HOST = "send-bulk-emails.p.rapidapi.com";
const QString EmailService::RAPIDAPI_URL = "https://send-bulk-emails.p.rapidapi.com/api/send/otp/mail";

EmailService::EmailService(QObject *parent)
    : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
}

void EmailService::sendCommandConfirmationEmail(const CommandInfo &command)
{
    if (command.clientEmail.isEmpty())
    {
        emit emailSent(false, "Email du client non disponible");
        return;
    }

    QString subject = QString("🚚 Confirmation de votre commande #%1 - WALA Logistique").arg(command.commandId);
    QString htmlContent = generateEmailTemplate(command);

    QJsonObject payload = createEmailPayload(command.clientEmail, subject, htmlContent);

    QNetworkRequest request;
    request.setUrl(QUrl(RAPIDAPI_URL));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-RapidAPI-Key", RAPIDAPI_KEY.toUtf8());
    request.setRawHeader("X-RapidAPI-Host", RAPIDAPI_HOST.toUtf8());

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = networkManager->post(request, data);
    connect(reply, &QNetworkReply::finished, this, &EmailService::onEmailReplyFinished);

    qDebug() << "Sending email to:" << command.clientEmail;
}

QString EmailService::generateEmailTemplate(const CommandInfo &command)
{
    QString template_html = QString(
                                "<!DOCTYPE html>"
                                "<html lang='fr'>"
                                "<head>"
                                "    <meta charset='UTF-8'>"
                                "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                                "    <title>Confirmation de commande</title>"
                                "    <style>"
                                "        * { margin: 0; padding: 0; box-sizing: border-box; }"
                                "        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); padding: 20px; }"
                                "        .email-container { max-width: 600px; margin: 0 auto; background: white; border-radius: 15px; overflow: hidden; box-shadow: 0 10px 30px rgba(0,0,0,0.2); }"
                                "        .header { background: linear-gradient(135deg, #ff9a9e 0%, #fecfef 100%); padding: 30px; text-align: center; color: white; }"
                                "        .header h1 { font-size: 28px; margin-bottom: 10px; }"
                                "        .header p { font-size: 16px; opacity: 0.9; }"
                                "        .content { padding: 40px 30px; }"
                                "        .greeting { font-size: 18px; color: #333; margin-bottom: 20px; }"
                                "        .order-card { background: linear-gradient(135deg, #f8f9fa 0%, #e9ecef 100%); border-radius: 10px; padding: 25px; margin: 20px 0; border-left: 5px solid #ff9a9e; }"
                                "        .order-header { display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px; }"
                                "        .order-number { font-size: 24px; font-weight: bold; color: #ff6b6b; }"
                                "        .order-date { color: #666; font-size: 14px; }"
                                "        .order-details { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; }"
                                "        .detail-item { }"
                                "        .detail-label { font-weight: bold; color: #333; font-size: 14px; margin-bottom: 5px; }"
                                "        .detail-value { color: #666; font-size: 16px; }"
                                "        .amount-highlight { background: linear-gradient(135deg, #28a745 0%, #20c997 100%); color: white; padding: 15px; border-radius: 8px; text-align: center; margin: 20px 0; }"
                                "        .amount-highlight .amount { font-size: 28px; font-weight: bold; }"
                                "        .status-badge { display: inline-block; padding: 8px 16px; border-radius: 20px; font-size: 14px; font-weight: bold; }"
                                "        .status-pending { background: #fff3cd; color: #856404; }"
                                "        .status-processing { background: #cce5ff; color: #004085; }"
                                "        .next-steps { background: #e3f2fd; border-radius: 10px; padding: 20px; margin: 25px 0; }"
                                "        .next-steps h3 { color: #1976d2; margin-bottom: 15px; }"
                                "        .next-steps ul { list-style: none; }"
                                "        .next-steps li { margin: 8px 0; padding-left: 25px; position: relative; }"
                                "        .next-steps li:before { content: '✅'; position: absolute; left: 0; }"
                                "        .footer { background: #f8f9fa; padding: 30px; text-align: center; color: #666; }"
                                "        .footer h3 { color: #333; margin-bottom: 15px; }"
                                "        .contact-info { display: flex; justify-content: center; gap: 30px; margin: 20px 0; }"
                                "        .contact-item { text-align: center; }"
                                "        .contact-icon { font-size: 24px; margin-bottom: 5px; }"
                                "        .social-links { margin: 20px 0; }"
                                "        .social-links a { display: inline-block; margin: 0 10px; text-decoration: none; color: #ff9a9e; font-size: 20px; }"
                                "        .disclaimer { font-size: 12px; color: #999; margin-top: 20px; }"
                                "    </style>"
                                "</head>"
                                "<body>"
                                "    <div class='email-container'>"
                                "        <div class='header'>"
                                "            <h1>🚚 WALA Logistique</h1>"
                                "            <p>Votre partenaire de confiance pour la livraison</p>"
                                "        </div>"
                                "        "
                                "        <div class='content'>"
                                "            <div class='greeting'>"
                                "                Bonjour <strong>%1</strong>,<br><br>"
                                "                Nous avons le plaisir de confirmer que votre commande a été enregistrée avec succès ! 🎉"
                                "            </div>"
                                "            "
                                "            <div class='order-card'>"
                                "                <div class='order-header'>"
                                "                    <div class='order-number'>Commande #%2</div>"
                                "                    <div class='order-date'>%3</div>"
                                "                </div>"
                                "                "
                                "                <div class='order-details'>"
                                "                    <div class='detail-item'>"
                                "                        <div class='detail-label'>📍 Adresse de livraison</div>"
                                "                        <div class='detail-value'>%4</div>"
                                "                    </div>"
                                "                    <div class='detail-item'>"
                                "                        <div class='detail-label'>📋 Statut</div>"
                                "                        <div class='detail-value'>"
                                "                            <span class='status-badge status-pending'>%5</span>"
                                "                        </div>"
                                "                    </div>"
                                "                </div>"
                                "            </div>"
                                "            "
                                "            <div class='amount-highlight'>"
                                "                <div>Montant total</div>"
                                "                <div class='amount'>%6 DT</div>"
                                "            </div>"
                                "            "
                                "            <div class='next-steps'>"
                                "                <h3>🚀 Prochaines étapes</h3>"
                                "                <ul>"
                                "                    <li>Préparation de votre commande dans nos entrepôts</li>"
                                "                    <li>Attribution d'un transporteur qualifié</li>"
                                "                    <li>Envoi des détails de suivi par SMS/Email</li>"
                                "                    <li>Livraison à l'adresse indiquée</li>"
                                "                </ul>"
                                "            </div>"
                                "            "
                                "            <p style='color: #666; text-align: center; margin: 25px 0;'>"
                                "                Vous recevrez une notification dès que votre commande sera expédiée avec les informations de suivi."
                                "            </p>"
                                "        </div>"
                                "        "
                                "        <div class='footer'>"
                                "            <h3>📞 Besoin d'aide ?</h3>"
                                "            <div class='contact-info'>"
                                "                <div class='contact-item'>"
                                "                    <div class='contact-icon'>📧</div>"
                                "                    <div>support@wala.tn</div>"
                                "                </div>"
                                "                <div class='contact-item'>"
                                "                    <div class='contact-icon'>📱</div>"
                                "                    <div>+216 XX XXX XXX</div>"
                                "                </div>"
                                "                <div class='contact-item'>"
                                "                    <div class='contact-icon'>🌐</div>"
                                "                    <div>www.wala.tn</div>"
                                "                </div>"
                                "            </div>"
                                "            "
                                "            <div class='social-links'>"
                                "                <a href='#'>📘 Facebook</a>"
                                "                <a href='#'>📷 Instagram</a>"
                                "                <a href='#'>🐦 Twitter</a>"
                                "            </div>"
                                "            "
                                "            <div class='disclaimer'>"
                                "                © 2025 WALA Logistique. Tous droits réservés.<br>"
                                "                Cet email a été envoyé automatiquement, merci de ne pas y répondre."
                                "            </div>"
                                "        </div>"
                                "    </div>"
                                "</body>"
                                "</html>")
                                .arg(command.clientName)
                                .arg(command.commandId)
                                .arg(command.commandDate.toString("dddd dd MMMM yyyy"))
                                .arg(command.deliveryAddress)
                                .arg(command.status)
                                .arg(QString::number(command.amount, 'f', 2));

    return template_html;
}

QJsonObject EmailService::createEmailPayload(const QString &toEmail, const QString &subject, const QString &htmlContent)
{
    QJsonObject payload;
    payload["subject"] = subject;
    payload["from"] = "gateway.smtp587@gmail.com"; // Use the API's sender email

    // Send "to" as a string, not an array
    payload["to"] = toEmail;

    payload["senders_name"] = "WALA Logistique";
    payload["body"] = htmlContent; // The API uses "body" instead of "html"

    return payload;
}

void EmailService::onEmailReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply)
        return;

    QByteArray responseData = reply->readAll();
    qDebug() << "Email API Response:" << responseData;
    qDebug() << "HTTP Status Code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();

        // Check for success in response
        if (jsonObj.contains("status") || responseData.contains("success") ||
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
        {
            emit emailSent(true, "Email envoyé avec succès!");
        }
        else
        {
            QString errorMsg = jsonObj.contains("message") ? jsonObj["message"].toString() : "Erreur inconnue";
            emit emailSent(false, "Erreur lors de l'envoi: " + errorMsg);
        }
    }
    else
    {
        qDebug() << "Network error:" << reply->errorString();
        qDebug() << "HTTP Status:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        emit emailSent(false, "Erreur réseau: " + reply->errorString());
    }

    reply->deleteLater();
}
//email
