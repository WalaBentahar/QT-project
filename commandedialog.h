#ifndef COMMANDEDIALOG_H
#define COMMANDEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "commande.h"

class CommandeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommandeDialog(QWidget *parent = nullptr);
    explicit CommandeDialog(const Commande &commande, QWidget *parent = nullptr);

    Commande getCommande() const;

private slots:
    void accept() override;

private:
    void setupUI();
    void setupStyles();
    void loadClients();
    bool validateInput();
    void setupValidators();
    void showFieldError(QWidget *field, const QString &message);
    void clearFieldError(QWidget *field);

    QComboBox *clientCombo;
    QDateEdit *dateEdit;
    QLineEdit *adresseLivraisonEdit;
    QComboBox *statutCombo;
    QDoubleSpinBox *montantSpinBox;
    QPushButton *saveButton;
    QPushButton *cancelButton;

    Commande currentCommande;
    bool isEditing;
};

#endif // COMMANDEDIALOG_H
