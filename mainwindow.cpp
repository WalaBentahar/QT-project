#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statisticswidget.h"
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), statisticsWidget(nullptr), trayIcon(nullptr)
{
    ui->setupUi(this);

    // Set window properties
    setWindowIcon(QIcon("notif.png"));
    setMinimumSize(1200, 800);

    // Initialize email service
    emailService = new EmailService(this);
    connect(emailService, &EmailService::emailSent, this, &MainWindow::onEmailSent);

    setupTables();
    setupConnections();
    setupStyles();
    setupSystemTray();

    // Initialize with clients page
    ui->stackedWidget->setCurrentWidget(ui->clientsPage);
    ui->clientsButton->setProperty("active", true);

    // Load initial data
    loadClientsData();
    loadCommandesData();
    updateButtonStates();

    // Show welcome notification after a short delay to ensure tray icon is ready
    QTimer::singleShot(2000, this, [this]()
                       { showNotification("WALA - Gestion Logistique", "Application démarrée avec succès! 🚀"); });
}

MainWindow::~MainWindow()
{
    if (trayIcon)
    {
        trayIcon->hide();
    }
    delete ui;
}

void MainWindow::setupConnections()
{
    // Sidebar navigation
    connect(ui->clientsButton, &QPushButton::clicked, this, &MainWindow::showClientsPage);
    connect(ui->commandesButton, &QPushButton::clicked, this, &MainWindow::showCommandesPage);
    connect(ui->statisticsButton, &QPushButton::clicked, this, &MainWindow::showStatisticsPage);

    // Client operations
    connect(ui->addClientButton, &QPushButton::clicked, this, &MainWindow::addClient);
    connect(ui->clientSearchEdit, &QLineEdit::textChanged, this, &MainWindow::searchClients);

    // Fix signal-slot connections for double click events
    connect(ui->clientsTable, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::onClientTableDoubleClick);
    connect(ui->commandesTable, &QTableWidget::cellDoubleClicked,
            this, &MainWindow::onCommandeTableDoubleClick);

    connect(ui->clientsTable, &QTableWidget::customContextMenuRequested, this, &MainWindow::onClientTableContextMenu);

    // Command operations
    connect(ui->addCommandeButton, &QPushButton::clicked, this, &MainWindow::addCommande);
    connect(ui->commandesTable, &QTableWidget::customContextMenuRequested, this, &MainWindow::onCommandeTableContextMenu);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::exportCommandesToPDF);
    connect(ui->searchCommandesButton, &QPushButton::clicked, this, &MainWindow::searchCommandes);
    connect(ui->clearSearchButton, &QPushButton::clicked, this, &MainWindow::clearSearchCommandes);
    connect(ui->commandeSearchEdit, &QLineEdit::returnPressed, this, &MainWindow::searchCommandes);

    // Sort button connections
    connect(ui->sortClientsButton, &QPushButton::clicked, this, &MainWindow::sortClients);
    connect(ui->sortCommandesButton, &QPushButton::clicked, this, &MainWindow::sortCommandes);

    // Context menus
    ui->clientsTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->commandesTable->setContextMenuPolicy(Qt::CustomContextMenu);

    // Create context menus
    clientContextMenu = new QMenu(this);
    clientContextMenu->addAction("✏️ Modifier", this, &MainWindow::editClient);
    clientContextMenu->addAction("🗑️ Supprimer", this, &MainWindow::deleteClient);
    clientContextMenu->addSeparator();
    clientContextMenu->addAction("🔄 Actualiser", this, &MainWindow::refreshClientsTable);

    commandeContextMenu = new QMenu(this);
    commandeContextMenu->addAction("✏️ Modifier", this, &MainWindow::editCommande);
    commandeContextMenu->addAction("🗑️ Supprimer", this, &MainWindow::deleteCommande);
    commandeContextMenu->addSeparator();
    commandeContextMenu->addAction("📄 Exporter PDF", this, &MainWindow::exportCommandesToPDF);
    commandeContextMenu->addAction("🔄 Actualiser", this, &MainWindow::refreshCommandesTable);
}

void MainWindow::setupTables()
{
    // Setup clients table - hide ID column
    ui->clientsTable->setColumnCount(6);
    QStringList clientHeaders = {"ID", "Nom", "Prénom", "Adresse", "Téléphone", "Email"};
    ui->clientsTable->setHorizontalHeaderLabels(clientHeaders);
    ui->clientsTable->hideColumn(0); // Hide ID column
    ui->clientsTable->horizontalHeader()->setStretchLastSection(true);
    ui->clientsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->clientsTable->setAlternatingRowColors(true);

    // Setup commands table - show montant column (7 columns total, 5 visible)
    ui->commandesTable->setColumnCount(7);
    QStringList commandeHeaders = {"ID", "ID_Client", "Client", "Date", "Adresse Livraison", "Statut", "Montant"};
    ui->commandesTable->setHorizontalHeaderLabels(commandeHeaders);
    ui->commandesTable->hideColumn(0); // Hide ID column
    ui->commandesTable->hideColumn(1); // Hide ID_Client column
    ui->commandesTable->horizontalHeader()->setStretchLastSection(true);
    ui->commandesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->commandesTable->setAlternatingRowColors(true);

    // Set column widths for better display
    ui->commandesTable->setColumnWidth(2, 150); // Client name
    ui->commandesTable->setColumnWidth(3, 100); // Date
    ui->commandesTable->setColumnWidth(4, 200); // Address
    ui->commandesTable->setColumnWidth(5, 100); // Status
    ui->commandesTable->setColumnWidth(6, 120); // Amount
}

void MainWindow::setupStyles()
{
    // Enhanced modern styling
    setStyleSheet(
        "QMainWindow {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, "
        "                                stop: 0 #f8f9fa, stop: 1 #e9ecef);"
        "}"
        "QPushButton[active=\"true\"] {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
        "                                stop: 0 #ff9a9e, stop: 1 #fecfef) !important;"
        "    color: white !important;"
        "    border: 2px solid rgba(255, 255, 255, 0.3) !important;"
        "}"
        "QTableWidget::item:hover {"
        "    background-color: rgba(255, 154, 158, 0.1);"
        "}"
        "QMenu {"
        "    background: white;"
        "    border: 2px solid #dee2e6;"
        "    border-radius: 8px;"
        "    padding: 5px;"
        "}"
        "QMenu::item {"
        "    padding: 8px 16px;"
        "    border-radius: 4px;"
        "}"
        "QMenu::item:selected {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
        "                                stop: 0 #ff9a9e, stop: 1 #fecfef);"
        "    color: white;"
        "}");
}

void MainWindow::setupSystemTray()
{
    // Check if system tray is available
    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        QMessageBox::critical(this, "System Tray",
                              "System tray is not available on this system.");
        return;
    }

    // Create tray icon - try different icon sources
    trayIcon = new QSystemTrayIcon(this);

    // Try to load the icon from different locations
    QIcon icon;
    if (QFile::exists("notif.png"))
    {
        icon = QIcon("notif.png");
    }
    else if (QFile::exists("notif.png"))
    {
        icon = QIcon("notif.png");
    }
    else
    {
        // Fallback to application icon
        icon = QIcon("notif.png");
    }

    // If still no icon, create a simple colored icon
    if (icon.isNull())
    {
        QPixmap pixmap(16, 16);
        pixmap.fill(QColor(255, 154, 158));
        icon = QIcon(pixmap);
    }

    trayIcon->setIcon(icon);
    trayIcon->setToolTip("WALA - Gestion Logistique");

    // Create tray menu
    trayMenu = new QMenu(this);

    showAction = new QAction("📱 Afficher", this);
    connect(showAction, &QAction::triggered, this, &MainWindow::showMainWindow);

    exitAction = new QAction("❌ Quitter", this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitApplication);

    trayMenu->addAction(showAction);
    trayMenu->addSeparator();
    trayMenu->addAction(exitAction);

    trayIcon->setContextMenu(trayMenu);

    // Connect tray icon activation
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);

    // Connect message clicked signal
    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::showMainWindow);

    // Show tray icon
    trayIcon->show();
}

void MainWindow::showNotification(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon)
{
    // Debug output
    qDebug() << "Attempting to show notification:" << title << "-" << message;

    if (trayIcon && trayIcon->isVisible())
    {
        qDebug() << "Tray icon is visible, showing message";
        trayIcon->showMessage(title, message, icon, 5000); // Show for 5 seconds
    }
    else
    {
        qDebug() << "Tray icon not available, showing fallback message box";
        // Fallback: show a message box if tray notifications aren't working
        QMessageBox msgBox;
        msgBox.setWindowTitle(title);
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void MainWindow::showMainWindow()
{
    show();
    raise();
    activateWindow();
}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        showMainWindow();
        break;
    case QSystemTrayIcon::MiddleClick:
        showNotification("WALA", "Application is running in background", QSystemTrayIcon::Information);
        break;
    default:
        break;
    }
}

void MainWindow::exitApplication()
{
    trayIcon->hide();
    QApplication::quit();
}

void MainWindow::showClientsPage()
{
    ui->stackedWidget->setCurrentWidget(ui->clientsPage);
    ui->clientsButton->setProperty("active", true);
    ui->commandesButton->setProperty("active", false);
    ui->statisticsButton->setProperty("active", false);

    // Force style update
    ui->clientsButton->style()->unpolish(ui->clientsButton);
    ui->clientsButton->style()->polish(ui->clientsButton);
    ui->commandesButton->style()->unpolish(ui->commandesButton);
    ui->commandesButton->style()->polish(ui->commandesButton);
    ui->statisticsButton->style()->unpolish(ui->statisticsButton);
    ui->statisticsButton->style()->polish(ui->statisticsButton);

    refreshClientsTable();
}

void MainWindow::showCommandesPage()
{
    ui->stackedWidget->setCurrentWidget(ui->commandesPage);
    ui->clientsButton->setProperty("active", false);
    ui->commandesButton->setProperty("active", true);
    ui->statisticsButton->setProperty("active", false);

    // Force style update
    ui->clientsButton->style()->unpolish(ui->clientsButton);
    ui->clientsButton->style()->polish(ui->clientsButton);
    ui->commandesButton->style()->unpolish(ui->commandesButton);
    ui->commandesButton->style()->polish(ui->commandesButton);
    ui->statisticsButton->style()->unpolish(ui->statisticsButton);
    ui->statisticsButton->style()->polish(ui->statisticsButton);

    refreshCommandesTable();
}

void MainWindow::showStatisticsPage()
{
    // Create statistics widget if not exists
    if (!statisticsWidget)
    {
        statisticsWidget = new StatisticsWidget;
        QVBoxLayout *layout = new QVBoxLayout(ui->statisticsScrollContent);
        layout->addWidget(statisticsWidget);
        ui->statisticsScrollContent->setLayout(layout);

        // Connect refresh button
        connect(ui->refreshStatsButton, &QPushButton::clicked,
                statisticsWidget, &StatisticsWidget::refreshData);
    }

    ui->stackedWidget->setCurrentWidget(ui->statisticsPage);

    // Update button states
    ui->clientsButton->setProperty("active", false);
    ui->commandesButton->setProperty("active", false);
    ui->statisticsButton->setProperty("active", true);

    // Force style update
    ui->clientsButton->style()->unpolish(ui->clientsButton);
    ui->clientsButton->style()->polish(ui->clientsButton);
    ui->commandesButton->style()->unpolish(ui->commandesButton);
    ui->commandesButton->style()->polish(ui->commandesButton);
    ui->statisticsButton->style()->unpolish(ui->statisticsButton);
    ui->statisticsButton->style()->polish(ui->statisticsButton);

    // Refresh statistics data
    statisticsWidget->refreshData();
}

void MainWindow::addClient()
{
    ClientDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        refreshClientsTable();
        showNotification("✅ Client Ajouté", "Nouveau client ajouté avec succès!", QSystemTrayIcon::Information);
        QMessageBox::information(this, "Succès", "Client ajouté avec succès!");
    }
}

void MainWindow::editClient()
{
    int currentRow = ui->clientsTable->currentRow();
    if (currentRow < 0)
        return;

    // Get ID from hidden data
    int id = ui->clientsTable->item(currentRow, 0)->data(Qt::UserRole).toInt();
    QString nom = ui->clientsTable->item(currentRow, 1)->text();
    QString prenom = ui->clientsTable->item(currentRow, 2)->text();
    QString adresse = ui->clientsTable->item(currentRow, 3)->text();
    QString telephone = ui->clientsTable->item(currentRow, 4)->text();
    QString email = ui->clientsTable->item(currentRow, 5)->text();

    Client client(id, nom, prenom, adresse, telephone, email);
    ClientDialog dialog(client, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        refreshClientsTable();
        showNotification("✏️ Client Modifié", QString("Client %1 %2 mis à jour!").arg(nom).arg(prenom), QSystemTrayIcon::Information);
        QMessageBox::information(this, "Succès", "Client modifié avec succès!");
    }
}

void MainWindow::deleteClient()
{
    int currentRow = ui->clientsTable->currentRow();
    if (currentRow < 0)
        return;

    int id = ui->clientsTable->item(currentRow, 0)->data(Qt::UserRole).toInt();
    QString nom = ui->clientsTable->item(currentRow, 1)->text();

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
                                                              QString("Êtes-vous sûr de vouloir supprimer le client %1?").arg(nom),
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        Client client;
        client.setId(id);
        if (client.supprimer())
        {
            refreshClientsTable();
            showNotification("🗑️ Client Supprimé", QString("Client %1 supprimé avec succès").arg(nom), QSystemTrayIcon::Warning);
            QMessageBox::information(this, "Succès", "Client supprimé avec succès!");
        }
        else
        {
            showNotification("❌ Erreur", "Impossible de supprimer le client", QSystemTrayIcon::Critical);
            QMessageBox::critical(this, "Erreur", "Impossible de supprimer le client.");
        }
    }
}

void MainWindow::searchClients()
{
    QString searchText = ui->clientSearchEdit->text();
    if (searchText.isEmpty())
    {
        loadClientsData();
        return;
    }

    QSqlQuery query = Client::rechercherParNom(searchText);
    ui->clientsTable->setRowCount(0);

    int row = 0;
    while (query.next())
    {
        ui->clientsTable->insertRow(row);
        for (int col = 0; col < 6; col++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setData(Qt::UserRole, query.value(0).toInt()); // Store ID for operations
            ui->clientsTable->setItem(row, col, item);
        }
        row++;
    }

    // Update status with search results
    if (row > 0)
    {
        ui->statusLabel->setText(QString("🔍 %1 client(s) trouvé(s) pour '%2'").arg(row).arg(searchText));
    }
    else
    {
        ui->statusLabel->setText(QString("❌ Aucun client trouvé pour '%1'").arg(searchText));
    }
}

void MainWindow::refreshClientsTable()
{
    loadClientsData();
}

void MainWindow::loadClientsData()
{
    QSqlQuery query = Client::afficher();
    ui->clientsTable->setRowCount(0);

    int row = 0;
    while (query.next())
    {
        ui->clientsTable->insertRow(row);
        for (int col = 0; col < 6; col++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setData(Qt::UserRole, query.value(0).toInt()); // Store ID for operations
            ui->clientsTable->setItem(row, col, item);
        }
        row++;
    }
}

void MainWindow::addCommande()
{
    CommandeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        refreshCommandesTable();
        refreshStatistics();

        // Get the newly added command details for email using model method
        int commandId;
        QDate commandDate;
        QString deliveryAddress, status, clientName, clientEmail;
        double amount;

        if (Commande::getLastCommandWithClientInfo(commandId, commandDate, deliveryAddress,
                                                   status, amount, clientName, clientEmail))
        {
            EmailService::CommandInfo cmdInfo;
            cmdInfo.commandId = commandId;
            cmdInfo.commandDate = commandDate;
            cmdInfo.deliveryAddress = deliveryAddress;
            cmdInfo.status = status;
            cmdInfo.amount = amount;
            cmdInfo.clientName = clientName;
            cmdInfo.clientEmail = clientEmail;

            // Send confirmation email
            if (!cmdInfo.clientEmail.isEmpty())
            {
                emailService->sendCommandConfirmationEmail(cmdInfo);
                showNotification("📧 Email en cours", "Envoi de l'email de confirmation...", QSystemTrayIcon::Information);
            }
        }

        showNotification("📦 Commande Ajoutée", "Nouvelle commande créée avec succès!", QSystemTrayIcon::Information);
        QMessageBox::information(this, "Succès", "Commande ajoutée avec succès!");
    }
}

void MainWindow::editCommande()
{
    int currentRow = ui->commandesTable->currentRow();
    if (currentRow < 0)
        return;

    // Get command ID from hidden data
    int id = ui->commandesTable->item(currentRow, 0)->data(Qt::UserRole).toInt();

    // Get other data to create Commande object
    int idClient = ui->commandesTable->item(currentRow, 1)->text().toInt();
    QString dateStr = ui->commandesTable->item(currentRow, 3)->text();
    QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
    QString adresse = ui->commandesTable->item(currentRow, 4)->text();
    QString statut = ui->commandesTable->item(currentRow, 5)->text();
    QString montantStr = ui->commandesTable->item(currentRow, 6)->text();
    double montant = montantStr.replace(" DT", "").toDouble();

    Commande commande(id, idClient, date, adresse, statut, montant);
    CommandeDialog dialog(commande, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        refreshCommandesTable();
        refreshStatistics();
        showNotification("✏️ Commande Modifiée", QString("Commande mise à jour!"));
        QMessageBox::information(this, "Succès", "Commande modifiée avec succès!");
    }
}

void MainWindow::deleteCommande()
{
    int currentRow = ui->commandesTable->currentRow();
    if (currentRow < 0)
        return;

    int id = ui->commandesTable->item(currentRow, 0)->data(Qt::UserRole).toInt();
    QString client = ui->commandesTable->item(currentRow, 2)->text();

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
                                                              QString("Êtes-vous sûr de vouloir supprimer la commande de %1?").arg(client),
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        Commande commande;
        commande.setId(id);
        if (commande.supprimer())
        {
            refreshCommandesTable();
            refreshStatistics();
            showNotification("🗑️ Commande Supprimée", QString("Commande de %1 supprimée").arg(client), QSystemTrayIcon::Warning);
            QMessageBox::information(this, "Succès", "Commande supprimée avec succès!");
        }
        else
        {
            showNotification("❌ Erreur", "Impossible de supprimer la commande", QSystemTrayIcon::Critical);
            QMessageBox::critical(this, "Erreur", "Impossible de supprimer la commande.");
        }
    }
}

void MainWindow::refreshCommandesTable()
{
    loadCommandesData();
}

void MainWindow::loadCommandesData()
{
    QSqlQuery query = Commande::afficher();
    ui->commandesTable->setRowCount(0);

    int row = 0;
    while (query.next())
    {
        ui->commandesTable->insertRow(row);

        // Store all data including hidden IDs
        ui->commandesTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));                                                        // ID_COMMANDE
        ui->commandesTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));                                                        // ID_CLIENT
        ui->commandesTable->setItem(row, 2, new QTableWidgetItem(query.value(6).toString() + " " + query.value(7).toString()));                      // Client name
        ui->commandesTable->setItem(row, 3, new QTableWidgetItem(QDate::fromString(query.value(2).toString(), Qt::ISODate).toString("dd/MM/yyyy"))); // Date
        ui->commandesTable->setItem(row, 4, new QTableWidgetItem(query.value(3).toString()));                                                        // Address
        ui->commandesTable->setItem(row, 5, new QTableWidgetItem(query.value(4).toString()));                                                        // Status
        ui->commandesTable->setItem(row, 6, new QTableWidgetItem(QString::number(query.value(5).toDouble(), 'f', 2) + " DT"));                       // Amount

        // Store ID for operations
        ui->commandesTable->item(row, 0)->setData(Qt::UserRole, query.value(0).toInt());

        row++;
    }

    // Update status
    ui->statusLabel->setText(QString("📦 %1 commande(s) affichée(s)").arg(row));
}

void MainWindow::exportCommandesToPDF()
{
    QString filename = QFileDialog::getSaveFileName(this, "Exporter en PDF",
                                                    "commandes_" + QDate::currentDate().toString("yyyy-MM-dd") + ".pdf",
                                                    "Fichiers PDF (*.pdf)");

    if (!filename.isEmpty())
    {
        createStyledPDF(filename);
        showNotification("📄 Export PDF", "Rapport exporté avec succès vers:\n" + QFileInfo(filename).fileName(), QSystemTrayIcon::Information);
    }
}

void MainWindow::createStyledPDF(const QString &filename)
{
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    // Fix for Qt 6 - use setPageSize instead of setPaperSize
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(filename);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QTextDocument document;
    QString htmlContent = generateModernPDFContent();
    document.setHtml(htmlContent);
    document.print(&printer);

    QMessageBox::information(this, "Succès", "PDF exporté avec succès!\nFichier: " + filename);
    QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}

QString MainWindow::generateModernPDFContent()
{
    QString html = QString(
                       "<!DOCTYPE html>"
                       "<html><head><meta charset='UTF-8'>"
                       "<style>"
                       "body { font-family: 'Segoe UI', Arial, sans-serif; margin: 20px; background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%); }"
                       ".header { text-align: center; margin-bottom: 30px; padding: 20px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; border-radius: 10px; }"
                       ".header h1 { margin: 0; font-size: 28px; }"
                       ".header p { margin: 5px 0; font-size: 14px; opacity: 0.9; }"
                       ".info-box { background: white; padding: 15px; margin: 20px 0; border-radius: 8px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }"
                       ".stats { display: flex; justify-content: space-around; margin: 20px 0; }"
                       ".stat-item { text-align: center; background: white; padding: 15px; border-radius: 8px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); min-width: 150px; }"
                       ".stat-number { font-size: 24px; font-weight: bold; color: #667eea; }"
                       ".stat-label { font-size: 12px; color: #666; margin-top: 5px; }"
                       "table { width: 100%; border-collapse: collapse; margin-top: 20px; background: white; border-radius: 8px; overflow: hidden; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }"
                       "th { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; padding: 15px 10px; text-align: left; font-weight: 600; }"
                       "td { padding: 12px 10px; border-bottom: 1px solid #f0f0f0; }"
                       "tr:nth-child(even) { background-color: #f8f9ff; }"
                       "tr:hover { background-color: #e8eaff; }"
                       ".status-badge { padding: 4px 8px; border-radius: 12px; font-size: 11px; font-weight: bold; }"
                       ".status-delivered { background: #d4edda; color: #155724; }"
                       ".status-pending { background: #fff3cd; color: #856404; }"
                       ".status-processing { background: #cce5ff; color: #004085; }"
                       ".status-cancelled { background: #f8d7da; color: #721c24; }"
                       ".amount { font-weight: bold; color: #28a745; }"
                       ".footer { margin-top: 30px; text-align: center; color: #666; font-size: 12px; }"
                       "</style></head><body>"

                       "<div class='header'>"
                       "<h1>🚚 WALA - Rapport des Commandes</h1>"
                       "<p>Gestion Logistique & Livraison</p>"
                       "<p>Généré le %1</p>"
                       "</div>"

                       "<div class='info-box'>"
                       "<h3>📊 Statistiques Générales</h3>"
                       "<div class='stats'>"
                       "<div class='stat-item'>"
                       "<div class='stat-number'>%2</div>"
                       "<div class='stat-label'>Total Commandes</div>"
                       "</div>"
                       "<div class='stat-item'>"
                       "<div class='stat-number'>%3 DT</div>"
                       "<div class='stat-label'>Montant Total</div>"
                       "</div>"
                       "<div class='stat-item'>"
                       "<div class='stat-number'>%4</div>"
                       "<div class='stat-label'>Clients Actifs</div>"
                       "</div>"
                       "</div>"
                       "</div>"

                       "<table>"
                       "<thead>"
                       "<tr><th>ID</th><th>Client</th><th>Date</th><th>Adresse</th><th>Statut</th><th>Montant</th></tr>"
                       "</thead>"
                       "<tbody>")
                       .arg(QDateTime::currentDateTime().toString("dddd dd MMMM yyyy à hh:mm"));

    // Calculate statistics
    int totalCommandes = ui->commandesTable->rowCount();
    double montantTotal = 0.0;
    QSet<QString> clientsUniques;

    // Add table rows
    for (int row = 0; row < ui->commandesTable->rowCount(); ++row)
    {
        QString id = ui->commandesTable->item(row, 0)->text();
        QString client = ui->commandesTable->item(row, 1)->text();
        QString date = ui->commandesTable->item(row, 2)->text();
        QString adresse = ui->commandesTable->item(row, 3)->text();
        QString statut = ui->commandesTable->item(row, 4)->text();
        QString montant = ui->commandesTable->item(row, 5)->text();

        // Add to statistics
        clientsUniques.insert(client);
        QString montantNum = montant.replace(" DT", "");
        montantTotal += montantNum.toDouble();

        // Determine status class
        QString statusClass = "status-pending";
        if (statut == "Livré")
            statusClass = "status-delivered";
        else if (statut == "En cours")
            statusClass = "status-processing";
        else if (statut == "Annulé")
            statusClass = "status-cancelled";

        html += QString(
                    "<tr>"
                    "<td>%1</td>"
                    "<td>%2</td>"
                    "<td>%3</td>"
                    "<td>%4</td>"
                    "<td><span class='status-badge %5'>%6</span></td>"
                    "<td class='amount'>%7</td>"
                    "</tr>")
                    .arg(id, client, date, adresse, statusClass, statut, montant);
    }

    html += "</tbody></table>";

    html += QString(
        "<div class='footer'>"
        "<p>Document généré automatiquement par WALA - Gestion Logistique</p>"
        "<p>© 2025 - Tous droits réservés</p>"
        "</div>"
        "</body></html>");

    // Update statistics in HTML
    html = html.arg(QString::number(totalCommandes))
               .arg(QString::number(montantTotal, 'f', 2))
               .arg(QString::number(clientsUniques.size()));

    return html;
}

void MainWindow::onClientTableContextMenu(const QPoint &pos)
{
    if (ui->clientsTable->itemAt(pos))
    {
        clientContextMenu->exec(ui->clientsTable->mapToGlobal(pos));
    }
}

void MainWindow::onCommandeTableContextMenu(const QPoint &pos)
{
    if (ui->commandesTable->itemAt(pos))
    {
        commandeContextMenu->exec(ui->commandesTable->mapToGlobal(pos));
    }
}

void MainWindow::onClientTableDoubleClick(int row, int column)
{
    Q_UNUSED(column)
    ui->clientsTable->selectRow(row);
    editClient();
}

void MainWindow::onCommandeTableDoubleClick(int row, int column)
{
    Q_UNUSED(column)
    ui->commandesTable->selectRow(row);
    editCommande();
}

void MainWindow::updateButtonStates()
{
    // Update status label
    ui->statusLabel->setText("🟢 Connecté - Base Oracle");
}

void MainWindow::sortClients()
{
    int index = ui->clientSortCombo->currentIndex();
    QString criteria;

    switch (index)
    {
    case 0:
        criteria = "nom";
        break;
    case 1:
        criteria = "adresse";
        break;
    case 2:
        criteria = "commandes";
        break;
    default:
        criteria = "nom";
        break;
    }

    QSqlQuery query = Client::trierPar(criteria);

    ui->clientsTable->setRowCount(0);
    int row = 0;
    while (query.next())
    {
        ui->clientsTable->insertRow(row);
        for (int col = 0; col < 6; col++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setData(Qt::UserRole, query.value(0).toInt());
            ui->clientsTable->setItem(row, col, item);
        }
        row++;
    }
}

void MainWindow::sortCommandes()
{
    int index = ui->commandeSortCombo->currentIndex();
    QString criteria;

    switch (index)
    {
    case 0:
        criteria = "date";
        break;
    case 1:
        criteria = "montant";
        break;
    case 2:
        criteria = "statut";
        break;
    default:
        criteria = "date";
        break;
    }

    QSqlQuery query = Commande::trierPar(criteria);

    ui->commandesTable->setRowCount(0);
    int row = 0;
    while (query.next())
    {
        ui->commandesTable->insertRow(row);

        ui->commandesTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->commandesTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->commandesTable->setItem(row, 2, new QTableWidgetItem(query.value(6).toString() + " " + query.value(7).toString()));
        ui->commandesTable->setItem(row, 3, new QTableWidgetItem(QDate::fromString(query.value(2).toString(), Qt::ISODate).toString("dd/MM/yyyy")));
        ui->commandesTable->setItem(row, 4, new QTableWidgetItem(query.value(3).toString()));
        ui->commandesTable->setItem(row, 5, new QTableWidgetItem(query.value(4).toString()));
        ui->commandesTable->setItem(row, 6, new QTableWidgetItem(QString::number(query.value(5).toDouble(), 'f', 2) + " DT"));

        ui->commandesTable->item(row, 0)->setData(Qt::UserRole, query.value(0).toInt());
        row++;
    }
}

void MainWindow::searchCommandes()
{
    QString searchText = ui->commandeSearchEdit->text().trimmed();

    if (searchText.isEmpty())
    {
        loadCommandesData();
        return;
    }

    ui->commandesTable->setRowCount(0);

    // Multi-criteria search query
    QSqlQuery query;
    QString sql = "SELECT c.*, cl.NOM, cl.PRENOM FROM COMMANDE c "
                  "JOIN CLIENT cl ON c.ID_CLIENT = cl.ID_CLIENT WHERE (";

    // Search in address (case insensitive)
    sql += "UPPER(c.ADRESSE_LIVRAISON) LIKE UPPER(:search_text1) OR ";

    // Search in status (case insensitive)
    sql += "UPPER(c.STATUT) LIKE UPPER(:search_text2) OR ";

    // Search in amount (try to convert search text to number)
    sql += "c.MONTANT = :search_amount OR ";
    sql += "TO_CHAR(c.MONTANT, '999999.99') LIKE :search_text3";

    sql += ") ORDER BY c.DATE_COMMANDE DESC";

    query.prepare(sql);

    // Bind search parameters
    QString searchPattern = "%" + searchText + "%";
    query.bindValue(":search_text1", searchPattern);
    query.bindValue(":search_text2", searchPattern);
    query.bindValue(":search_text3", searchPattern);

    // Try to parse as number for amount search
    bool isNumber;
    double searchAmount = searchText.toDouble(&isNumber);
    if (isNumber)
    {
        query.bindValue(":search_amount", searchAmount);
    }
    else
    {
        query.bindValue(":search_amount", -1); // Use -1 as impossible amount
    }

    if (query.exec())
    {
        int row = 0;
        while (query.next())
        {
            ui->commandesTable->insertRow(row);

            ui->commandesTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->commandesTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->commandesTable->setItem(row, 2, new QTableWidgetItem(query.value(6).toString() + " " + query.value(7).toString()));
            ui->commandesTable->setItem(row, 3, new QTableWidgetItem(QDate::fromString(query.value(2).toString(), Qt::ISODate).toString("dd/MM/yyyy")));
            ui->commandesTable->setItem(row, 4, new QTableWidgetItem(query.value(3).toString()));
            ui->commandesTable->setItem(row, 5, new QTableWidgetItem(query.value(4).toString()));
            ui->commandesTable->setItem(row, 6, new QTableWidgetItem(QString::number(query.value(5).toDouble(), 'f', 2) + " DT"));

            ui->commandesTable->item(row, 0)->setData(Qt::UserRole, query.value(0).toInt());
            row++;
        }

        // Update status with search results
        ui->statusLabel->setText(QString("🔍 %1 commande(s) trouvée(s) pour '%2'").arg(row).arg(searchText));
    }
    else
    {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la recherche: " + query.lastError().text());
    }
}

void MainWindow::clearSearchCommandes()
{
    ui->commandeSearchEdit->clear();
    loadCommandesData();
}

void MainWindow::refreshStatistics()
{
    // Only refresh if statistics widget exists and is created
    if (statisticsWidget)
    {
        statisticsWidget->refreshStatistics();
    }
}

void MainWindow::onEmailSent(bool success, const QString &message)
{
    if (success)
    {
        showNotification("✅ Email Envoyé", "Email de confirmation envoyé au client!", QSystemTrayIcon::Information);
        qDebug() << "Email sent successfully:" << message;
    }
    else
    {
        showNotification("❌ Erreur Email", "Impossible d'envoyer l'email: " + message, QSystemTrayIcon::Warning);
        qDebug() << "Email sending failed:" << message;
    }
}
