#include "commandedialog.h"
#include "client.h"
#include <QSqlQuery>

CommandeDialog::CommandeDialog(QWidget *parent)
    : QDialog(parent), isEditing(false)
{
    setupUI();
    setupStyles();
    loadClients();
    setWindowTitle("Ajouter une Commande");
}

CommandeDialog::CommandeDialog(const Commande &commande, QWidget *parent)
    : QDialog(parent), currentCommande(commande), isEditing(true)
{
    setupUI();
    setupStyles();
    loadClients();
    setWindowTitle("Modifier Commande");

    // Fill fields with existing data
    for (int i = 0; i < clientCombo->count(); ++i)
    {
        if (clientCombo->itemData(i).toInt() == commande.getIdClient())
        {
            clientCombo->setCurrentIndex(i);
            break;
        }
    }
    dateEdit->setDate(commande.getDateCommande());
    adresseLivraisonEdit->setText(commande.getAdresseLivraison());
    statutCombo->setCurrentText(commande.getStatut());
    montantSpinBox->setValue(commande.getMontant());
}

void CommandeDialog::setupUI()
{
    setModal(true);
    setFixedSize(520, 380); // Increased size for better layout

    QFormLayout *formLayout = new QFormLayout;

    clientCombo = new QComboBox;
    clientCombo->setMinimumHeight(40);

    dateEdit = new QDateEdit;
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("dd/MM/yyyy");
    dateEdit->setMinimumWidth(200);
    dateEdit->setMinimumHeight(40);

    adresseLivraisonEdit = new QLineEdit;
    adresseLivraisonEdit->setPlaceholderText("Adresse complète de livraison...");
    adresseLivraisonEdit->setMinimumHeight(40);

    statutCombo = new QComboBox;
    statutCombo->addItems({"En attente", "En cours", "Livré", "Annulé"});
    statutCombo->setMinimumHeight(40);

    montantSpinBox = new QDoubleSpinBox;
    montantSpinBox->setRange(0.0, 999999.99);
    montantSpinBox->setDecimals(2);
    montantSpinBox->setSuffix(" DT");
    montantSpinBox->setMinimumHeight(40);

    formLayout->addRow("Client *:", clientCombo);
    formLayout->addRow("Date de commande *:", dateEdit);
    formLayout->addRow("Adresse de livraison *:", adresseLivraisonEdit);
    formLayout->addRow("Statut:", statutCombo);
    formLayout->addRow("Montant *:", montantSpinBox);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    saveButton = new QPushButton("💾 Enregistrer");
    cancelButton = new QPushButton("❌ Annuler");

    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    setupValidators();

    connect(saveButton, &QPushButton::clicked, this, &CommandeDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void CommandeDialog::setupValidators()
{
    // Connect validation signals
    connect(adresseLivraisonEdit, &QLineEdit::textChanged, this, [this]()
            {
        if (!adresseLivraisonEdit->text().trimmed().isEmpty()) {
            clearFieldError(adresseLivraisonEdit);
        } });

    connect(montantSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double value)
            {
        if (value > 0) {
            clearFieldError(montantSpinBox);
        } });
}

void CommandeDialog::setupStyles()
{
    setStyleSheet(
        "QDialog {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, "
        "                                stop: 0 #f5f5f5, stop: 1 #e8e8e8);"
        "    border-radius: 10px;"
        "}"
        "QComboBox, QDateEdit, QLineEdit, QDoubleSpinBox {"
        "    padding: 8px 12px;"
        "    border: 2px solid #ddd;"
        "    border-radius: 6px;"
        "    background: white;"
        "    font-size: 14px;"
        "    min-height: 20px;"
        "}"
        "QComboBox:focus, QDateEdit:focus, QLineEdit:focus, QDoubleSpinBox:focus {"
        "    border-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
        "                                  stop: 0 #ff9a9e, stop: 1 #fecfef);"
        "}"
        "QWidget[error=\"true\"] {"
        "    border-color: #dc3545 !important;"
        "    background-color: #fff5f5 !important;"
        "}"
        "QPushButton {"
        "    padding: 12px 24px;"
        "    border: none;"
        "    border-radius: 6px;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    min-width: 120px;"
        "}"
        "QPushButton:first-child {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
        "                                stop: 0 #ff9a9e, stop: 1 #fecfef);"
        "    color: white;"
        "}"
        "QPushButton:last-child {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
        "                                stop: 0 #a8a8a8, stop: 1 #d0d0d0);"
        "    color: #333;"
        "}"
        "QPushButton:hover {"
        "    transform: translateY(-2px);"
        "}"
        "QLabel {"
        "    font-weight: bold;"
        "    color: #333;"
        "    font-size: 14px;"
        "}"
        "QFormLayout {"
        "    spacing: 15px;"
        "}");
}

void CommandeDialog::showFieldError(QWidget *field, const QString &message)
{
    field->setProperty("error", true);
    field->setToolTip(message);
    field->style()->unpolish(field);
    field->style()->polish(field);
}

void CommandeDialog::clearFieldError(QWidget *field)
{
    field->setProperty("error", false);
    field->setToolTip("");
    field->style()->unpolish(field);
    field->style()->polish(field);
}

bool CommandeDialog::validateInput()
{
    bool isValid = true;

    // Clear all previous errors
    clearFieldError(clientCombo);
    clearFieldError(adresseLivraisonEdit);
    clearFieldError(montantSpinBox);

    if (clientCombo->currentIndex() == -1)
    {
        showFieldError(clientCombo, "Veuillez sélectionner un client.");
        QMessageBox::warning(this, "Erreur de validation", "Veuillez sélectionner un client.");
        isValid = false;
    }

    if (adresseLivraisonEdit->text().trimmed().isEmpty())
    {
        showFieldError(adresseLivraisonEdit, "L'adresse de livraison est obligatoire.");
        QMessageBox::warning(this, "Erreur de validation", "L'adresse de livraison est obligatoire.");
        isValid = false;
    }

    if (montantSpinBox->value() <= 0)
    {
        showFieldError(montantSpinBox, "Le montant doit être supérieur à 0.");
        QMessageBox::warning(this, "Erreur de validation", "Le montant doit être supérieur à 0 DT.");
        isValid = false;
    }

    return isValid;
}

void CommandeDialog::accept()
{
    if (!validateInput())
    {
        return;
    }

    currentCommande.setIdClient(clientCombo->currentData().toInt());
    currentCommande.setDateCommande(dateEdit->date());
    currentCommande.setAdresseLivraison(adresseLivraisonEdit->text().trimmed());
    currentCommande.setStatut(statutCombo->currentText());
    currentCommande.setMontant(montantSpinBox->value());

    bool success;
    if (isEditing)
    {
        success = currentCommande.modifier();
    }
    else
    {
        success = currentCommande.ajouter();
    }

    if (success)
    {
        QDialog::accept();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible de sauvegarder la commande.");
    }
}

Commande CommandeDialog::getCommande() const
{
    return currentCommande;
}

void CommandeDialog::loadClients()
{
    clientCombo->clear();
    QSqlQuery query = Client::afficher();

    while (query.next())
    {
        int id = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        QString displayText = QString("%1 %2").arg(nom, prenom);
        clientCombo->addItem(displayText, id);
    }

    // Add placeholder if no clients found
    if (clientCombo->count() == 0)
    {
        clientCombo->addItem("Aucun client disponible", -1);
        clientCombo->setEnabled(false);
    }
    else
    {
        clientCombo->setEnabled(true);
    }
}
