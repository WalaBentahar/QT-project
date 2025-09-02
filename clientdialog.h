#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QComboBox>
#include <QRegularExpressionValidator>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include "client.h"

class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = nullptr);
    explicit ClientDialog(const Client &client, QWidget *parent = nullptr);

    Client getClient() const;

private slots:
    void accept() override;
    void onNomChanged();
    void onPrenomChanged();
    void onTelephoneChanged();
    void onEmailChanged();

private:
    void setupUI();
    void setupStyles();
    void setupValidators();
    bool validateInput();
    void showFieldError(QLineEdit *field, const QString &message);
    void clearFieldError(QLineEdit *field);
    void animateFieldError(QLineEdit *field);

    QLineEdit *nomEdit;
    QLineEdit *prenomEdit;
    QLineEdit *adresseEdit;
    QLineEdit *telephoneEdit;
    QLineEdit *emailEdit;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QComboBox *sortCombo;

    Client currentClient;
    bool isEditing;
};

#endif // CLIENTDIALOG_H
