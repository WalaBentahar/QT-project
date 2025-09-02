#include "clientdialog.h"
#include <QRegularExpression>
#include <QTimer>

ClientDialog::ClientDialog(QWidget *parent)
    : QDialog(parent), isEditing(false)
{
    setupUI();
    setupStyles();
    setupValidators();
    setWindowTitle("Ajouter un Client");
}

ClientDialog::ClientDialog(const Client &client, QWidget *parent)
    : QDialog(parent), currentClient(client), isEditing(true)
{
    setupUI();
    setupStyles();
    setupValidators();
    setWindowTitle("Modifier Client");

    // Fill fields with existing data
    nomEdit->setText(client.getNom());
    prenomEdit->setText(client.getPrenom());
    adresseEdit->setText(client.getAdresse());
    telephoneEdit->setText(client.getTelephone());
    emailEdit->setText(client.getEmail());
}

void ClientDialog::setupUI()
{
    setModal(true);
    setFixedSize(450, 400);

    QFormLayout *formLayout = new QFormLayout;

    nomEdit = new QLineEdit;
    nomEdit->setPlaceholderText("Entrez le nom (lettres uniquement)");

    prenomEdit = new QLineEdit;
    prenomEdit->setPlaceholderText("Entrez le prénom (lettres uniquement)");

    adresseEdit = new QLineEdit;
    adresseEdit->setPlaceholderText("Adresse complète de résidence");

    telephoneEdit = new QLineEdit;
    telephoneEdit->setPlaceholderText("8 chiffres (ex: 12345678)");
    telephoneEdit->setMaxLength(8);

    emailEdit = new QLineEdit;
    emailEdit->setPlaceholderText("exemple@email.com");

    formLayout->addRow("Nom *:", nomEdit);
    formLayout->addRow("Prénom *:", prenomEdit);
    formLayout->addRow("Adresse:", adresseEdit);
    formLayout->addRow("Téléphone *:", telephoneEdit);
    formLayout->addRow("Email *:", emailEdit);

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

    // Connect signals for real-time validation
    connect(nomEdit, &QLineEdit::textChanged, this, &ClientDialog::onNomChanged);
    connect(prenomEdit, &QLineEdit::textChanged, this, &ClientDialog::onPrenomChanged);
    connect(telephoneEdit, &QLineEdit::textChanged, this, &ClientDialog::onTelephoneChanged);
    connect(emailEdit, &QLineEdit::textChanged, this, &ClientDialog::onEmailChanged);
    connect(saveButton, &QPushButton::clicked, this, &ClientDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void ClientDialog::setupValidators()
{
    // Alphabetic only for nom and prenom
    QRegularExpressionValidator *alphaValidator = new QRegularExpressionValidator(
        QRegularExpression("^[a-zA-ZÀ-ÿ\\s]+$"), this);
    nomEdit->setValidator(alphaValidator);
    prenomEdit->setValidator(alphaValidator);

    // Numeric only for telephone (8 digits)
    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(
        QRegularExpression("^[0-9]{8}$"), this);
    telephoneEdit->setValidator(phoneValidator);

    // Email format
    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(
        QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"), this);
    emailEdit->setValidator(emailValidator);
}

void ClientDialog::setupStyles()
{
    setStyleSheet(
        "QDialog {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, "
        "                                stop: 0 #f5f5f5, stop: 1 #e8e8e8);"
        "    border-radius: 10px;"
        "}"
        "QLineEdit {"
        "    padding: 8px 12px;"
        "    border: 2px solid #ddd;"
        "    border-radius: 6px;"
        "    background: white;"
        "    font-size: 14px;"
        "    transition: border-color 0.3s;"
        "}"
        "QLineEdit:focus {"
        "    border-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
        "                                  stop: 0 #ff9a9e, stop: 1 #fecfef);"
        "}"
        "QLineEdit[error=\"true\"] {"
        "    border-color: #dc3545;"
        "    background-color: #fff5f5;"
        "    animation: shake 0.5s;"
        "}"
        "QPushButton {"
        "    padding: 10px 20px;"
        "    border: none;"
        "    border-radius: 6px;"
        "    font-weight: bold;"
        "    font-size: 14px;"
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
        "QLabel {"
        "    font-weight: bold;"
        "    color: #333;"
        "}");
}

void ClientDialog::onNomChanged()
{
    QString text = nomEdit->text();
    if (!text.isEmpty() && !nomEdit->hasAcceptableInput())
    {
        showFieldError(nomEdit, "Le nom doit contenir uniquement des lettres");
    }
    else
    {
        clearFieldError(nomEdit);
    }
}

void ClientDialog::onPrenomChanged()
{
    QString text = prenomEdit->text();
    if (!text.isEmpty() && !prenomEdit->hasAcceptableInput())
    {
        showFieldError(prenomEdit, "Le prénom doit contenir uniquement des lettres");
    }
    else
    {
        clearFieldError(prenomEdit);
    }
}

void ClientDialog::onTelephoneChanged()
{
    QString text = telephoneEdit->text();
    if (!text.isEmpty() && (text.length() != 8 || !telephoneEdit->hasAcceptableInput()))
    {
        showFieldError(telephoneEdit, "Le téléphone doit contenir exactement 8 chiffres");
    }
    else
    {
        clearFieldError(telephoneEdit);
    }
}

void ClientDialog::onEmailChanged()
{
    QString text = emailEdit->text();
    if (!text.isEmpty() && !emailEdit->hasAcceptableInput())
    {
        showFieldError(emailEdit, "Format email invalide (exemple@domaine.com)");
    }
    else
    {
        clearFieldError(emailEdit);
    }
}

void ClientDialog::showFieldError(QLineEdit *field, const QString &message)
{
    field->setProperty("error", true);
    field->setToolTip(message);
    field->style()->unpolish(field);
    field->style()->polish(field);
    animateFieldError(field);
}

void ClientDialog::clearFieldError(QLineEdit *field)
{
    field->setProperty("error", false);
    field->setToolTip("");
    field->style()->unpolish(field);
    field->style()->polish(field);
}

void ClientDialog::animateFieldError(QLineEdit *field)
{
    QPropertyAnimation *animation = new QPropertyAnimation(field, "pos");
    animation->setDuration(100);
    animation->setLoopCount(3);

    QPoint originalPos = field->pos();
    animation->setKeyValueAt(0, originalPos);
    animation->setKeyValueAt(0.5, originalPos + QPoint(5, 0));
    animation->setKeyValueAt(1, originalPos);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

bool ClientDialog::validateInput()
{
    bool isValid = true;

    if (nomEdit->text().trimmed().isEmpty() || !nomEdit->hasAcceptableInput())
    {
        showFieldError(nomEdit, "Le nom est obligatoire et doit contenir uniquement des lettres");
        isValid = false;
    }

    if (prenomEdit->text().trimmed().isEmpty() || !prenomEdit->hasAcceptableInput())
    {
        showFieldError(prenomEdit, "Le prénom est obligatoire et doit contenir uniquement des lettres");
        isValid = false;
    }

    if (telephoneEdit->text().length() != 8 || !telephoneEdit->hasAcceptableInput())
    {
        showFieldError(telephoneEdit, "Le téléphone doit contenir exactement 8 chiffres");
        isValid = false;
    }

    if (emailEdit->text().trimmed().isEmpty() || !emailEdit->hasAcceptableInput())
    {
        showFieldError(emailEdit, "Email obligatoire avec format valide");
        isValid = false;
    }

    return isValid;
}

void ClientDialog::accept()
{
    if (!validateInput())
    {
        return;
    }

    currentClient.setNom(nomEdit->text().trimmed());
    currentClient.setPrenom(prenomEdit->text().trimmed());
    currentClient.setAdresse(adresseEdit->text().trimmed());
    currentClient.setTelephone(telephoneEdit->text().trimmed());
    currentClient.setEmail(emailEdit->text().trimmed());

    bool success;
    if (isEditing)
    {
        success = currentClient.modifier();
    }
    else
    {
        success = currentClient.ajouter();
    }

    if (success)
    {
        QDialog::accept();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible de sauvegarder le client.");
    }
}

Client ClientDialog::getClient() const
{
    return currentClient;
}
