#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QHeaderView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QPrintDialog>
#include <QPrinter>
#include <QPageSize>
#include <QPageLayout>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTableFormat>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>
#include <QSet>
#include <QSystemTrayIcon>
#include <QAction>
#include <QTimer>
#include <QFileInfo>
#include <QPixmap>
#include "client.h"
#include "commande.h"
#include "clientdialog.h"
#include "commandedialog.h"
#include "statisticswidget.h"
#include "emailservice.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Navigation
    void showClientsPage();
    void showCommandesPage();
    void showStatisticsPage();

    // Client operations
    void addClient();
    void editClient();
    void deleteClient();
    void searchClients();
    void refreshClientsTable();
    void onClientTableContextMenu(const QPoint &pos);

    // Command operations
    void addCommande();
    void editCommande();
    void deleteCommande();
    void refreshCommandesTable();
    void onCommandeTableContextMenu(const QPoint &pos);
    void exportCommandesToPDF();
    void searchCommandes();
    void clearSearchCommandes();

    // Statistics operations
    void refreshStatistics(); // Add this declaration

    // Table events
    void onClientTableDoubleClick(int row, int column);
    void onCommandeTableDoubleClick(int row, int column);

    // Sorting operations
    void sortClients();
    void sortCommandes();

    // System tray actions
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMainWindow();
    void exitApplication();

    // Email service slots
    void onEmailSent(bool success, const QString &message);

private:
    void setupConnections();
    void setupTables();
    void setupStyles();
    void loadClientsData();
    void loadCommandesData();
    void updateButtonStates();
    void setupSystemTray();

    // PDF Export helpers
    QString generateModernPDFContent();
    void createStyledPDF(const QString &filename);
    void showNotification(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information);

    Ui::MainWindow *ui;
    QMenu *clientContextMenu;
    QMenu *commandeContextMenu;
    StatisticsWidget *statisticsWidget;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *showAction;
    QAction *exitAction;
    EmailService *emailService;
};
#endif // MAINWINDOW_H
