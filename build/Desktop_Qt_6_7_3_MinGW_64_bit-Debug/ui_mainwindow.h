/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *sidebarFrame;
    QVBoxLayout *sidebarLayout;
    QLabel *logoLabel;
    QFrame *line;
    QPushButton *clientsButton;
    QPushButton *commandesButton;
    QPushButton *exportButton;
    QPushButton *statisticsButton;
    QSpacerItem *verticalSpacer;
    QLabel *statusLabel;
    QStackedWidget *stackedWidget;
    QWidget *clientsPage;
    QVBoxLayout *clientsLayout;
    QFrame *clientsHeaderFrame;
    QVBoxLayout *clientsHeaderMainLayout;
    QLabel *clientsTitle;
    QHBoxLayout *clientsControlsLayout;
    QComboBox *clientSortCombo;
    QPushButton *sortClientsButton;
    QSpacerItem *clientsHorizontalSpacer;
    QLineEdit *clientSearchEdit;
    QPushButton *addClientButton;
    QTableWidget *clientsTable;
    QWidget *commandesPage;
    QVBoxLayout *commandesLayout;
    QFrame *commandesHeaderFrame;
    QVBoxLayout *commandesHeaderMainLayout;
    QLabel *commandesTitle;
    QHBoxLayout *commandesSearchLayout;
    QLabel *searchLabel;
    QLineEdit *commandeSearchEdit;
    QPushButton *searchCommandesButton;
    QPushButton *clearSearchButton;
    QSpacerItem *searchSpacer;
    QHBoxLayout *commandesControlsLayout;
    QComboBox *commandeSortCombo;
    QPushButton *sortCommandesButton;
    QSpacerItem *commandesHorizontalSpacer;
    QPushButton *addCommandeButton;
    QTableWidget *commandesTable;
    QWidget *statisticsPage;
    QVBoxLayout *statisticsLayout;
    QFrame *statisticsHeaderFrame;
    QVBoxLayout *statisticsHeaderLayout;
    QLabel *statisticsTitle;
    QHBoxLayout *statsControlsLayout;
    QPushButton *refreshStatsButton;
    QSpacerItem *statsHorizontalSpacer;
    QScrollArea *statisticsScrollArea;
    QWidget *statisticsScrollContent;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"    QMainWindow {\n"
"        background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, \n"
"                                   stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"    }\n"
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sidebarFrame = new QFrame(centralwidget);
        sidebarFrame->setObjectName("sidebarFrame");
        sidebarFrame->setMinimumSize(QSize(250, 0));
        sidebarFrame->setMaximumSize(QSize(250, 16777215));
        sidebarFrame->setStyleSheet(QString::fromUtf8("\n"
"        QFrame {\n"
"            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \n"
"                                       stop: 0 #6c757d, stop: 1 #495057);\n"
"            border-right: 3px solid qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                   stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"        }\n"
"       "));
        sidebarLayout = new QVBoxLayout(sidebarFrame);
        sidebarLayout->setSpacing(0);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(0, 0, 0, 0);
        logoLabel = new QLabel(sidebarFrame);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setAlignment(Qt::AlignCenter);

        sidebarLayout->addWidget(logoLabel);

        line = new QFrame(sidebarFrame);
        line->setObjectName("line");
        line->setStyleSheet(QString::fromUtf8("color: rgba(255, 255, 255, 0.3);"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        sidebarLayout->addWidget(line);

        clientsButton = new QPushButton(sidebarFrame);
        clientsButton->setObjectName("clientsButton");
        clientsButton->setStyleSheet(QString::fromUtf8("\n"
"           QPushButton {\n"
"               background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                          stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"               border: none;\n"
"               padding: 15px;\n"
"               text-align: left;\n"
"               color: white;\n"
"               font-weight: bold;\n"
"               font-size: 14px;\n"
"               border-radius: 8px;\n"
"           }\n"
"           QPushButton:hover {\n"
"               background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                          stop: 0 #ff8a95, stop: 1 #fedde5);\n"
"           }\n"
"           QPushButton:pressed {\n"
"               background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                          stop: 0 #ff7a85, stop: 1 #fccde5);\n"
"           }\n"
"          "));

        sidebarLayout->addWidget(clientsButton);

        commandesButton = new QPushButton(sidebarFrame);
        commandesButton->setObjectName("commandesButton");
        commandesButton->setStyleSheet(QString::fromUtf8("\n"
"           QPushButton {\n"
"               background: transparent;\n"
"               border: 2px solid rgba(255, 255, 255, 0.3);\n"
"               padding: 15px;\n"
"               text-align: left;\n"
"               color: white;\n"
"               font-weight: bold;\n"
"               font-size: 14px;\n"
"               border-radius: 8px;\n"
"           }\n"
"           QPushButton:hover {\n"
"               background: rgba(255, 255, 255, 0.1);\n"
"               border-color: rgba(255, 255, 255, 0.5);\n"
"           }\n"
"           QPushButton:pressed {\n"
"               background: rgba(255, 255, 255, 0.2);\n"
"           }\n"
"          "));

        sidebarLayout->addWidget(commandesButton);

        exportButton = new QPushButton(sidebarFrame);
        exportButton->setObjectName("exportButton");
        exportButton->setStyleSheet(QString::fromUtf8("\n"
"           QPushButton {\n"
"               background: transparent;\n"
"               border: 2px solid rgba(255, 255, 255, 0.3);\n"
"               padding: 15px;\n"
"               text-align: left;\n"
"               color: white;\n"
"               font-weight: bold;\n"
"               font-size: 14px;\n"
"               border-radius: 8px;\n"
"           }\n"
"           QPushButton:hover {\n"
"               background: rgba(255, 255, 255, 0.1);\n"
"               border-color: rgba(255, 255, 255, 0.5);\n"
"           }\n"
"          "));

        sidebarLayout->addWidget(exportButton);

        statisticsButton = new QPushButton(sidebarFrame);
        statisticsButton->setObjectName("statisticsButton");
        statisticsButton->setStyleSheet(QString::fromUtf8("\n"
"           QPushButton {\n"
"               background: transparent;\n"
"               border: 2px solid rgba(255, 255, 255, 0.3);\n"
"               padding: 15px;\n"
"               text-align: left;\n"
"               color: white;\n"
"               font-weight: bold;\n"
"               font-size: 14px;\n"
"               border-radius: 8px;\n"
"           }\n"
"           QPushButton:hover {\n"
"               background: rgba(255, 255, 255, 0.1);\n"
"               border-color: rgba(255, 255, 255, 0.5);\n"
"           }\n"
"          "));

        sidebarLayout->addWidget(statisticsButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(verticalSpacer);

        statusLabel = new QLabel(sidebarFrame);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignCenter);

        sidebarLayout->addWidget(statusLabel);


        horizontalLayout->addWidget(sidebarFrame);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        clientsPage = new QWidget();
        clientsPage->setObjectName("clientsPage");
        clientsLayout = new QVBoxLayout(clientsPage);
        clientsLayout->setObjectName("clientsLayout");
        clientsLayout->setContentsMargins(20, 20, 20, 20);
        clientsHeaderFrame = new QFrame(clientsPage);
        clientsHeaderFrame->setObjectName("clientsHeaderFrame");
        clientsHeaderFrame->setStyleSheet(QString::fromUtf8("\n"
"            QFrame {\n"
"                background: white;\n"
"                border-radius: 10px;\n"
"                border: 1px solid #dee2e6;\n"
"            }\n"
"           "));
        clientsHeaderMainLayout = new QVBoxLayout(clientsHeaderFrame);
        clientsHeaderMainLayout->setObjectName("clientsHeaderMainLayout");
        clientsHeaderMainLayout->setContentsMargins(20, 15, 20, 15);
        clientsTitle = new QLabel(clientsHeaderFrame);
        clientsTitle->setObjectName("clientsTitle");

        clientsHeaderMainLayout->addWidget(clientsTitle);

        clientsControlsLayout = new QHBoxLayout();
        clientsControlsLayout->setObjectName("clientsControlsLayout");
        clientSortCombo = new QComboBox(clientsHeaderFrame);
        clientSortCombo->addItem(QString());
        clientSortCombo->addItem(QString());
        clientSortCombo->addItem(QString());
        clientSortCombo->setObjectName("clientSortCombo");
        clientSortCombo->setStyleSheet(QString::fromUtf8("\n"
"                 QComboBox {\n"
"                     padding: 8px 12px;\n"
"                     border: 2px solid #dee2e6;\n"
"                     border-radius: 6px;\n"
"                     font-size: 14px;\n"
"                     min-width: 180px;\n"
"                     background: white;\n"
"                 }\n"
"                 QComboBox:focus {\n"
"                     border-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                  stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"                 }\n"
"                "));

        clientsControlsLayout->addWidget(clientSortCombo);

        sortClientsButton = new QPushButton(clientsHeaderFrame);
        sortClientsButton->setObjectName("sortClientsButton");
        sortClientsButton->setStyleSheet(QString::fromUtf8("\n"
"                 QPushButton {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #6c757d, stop: 1 #495057);\n"
"                     border: none;\n"
"                     padding: 8px 16px;\n"
"                     color: white;\n"
"                     font-weight: bold;\n"
"                     border-radius: 6px;\n"
"                     min-width: 80px;\n"
"                 }\n"
"                 QPushButton:hover {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #5a6268, stop: 1 #343a40);\n"
"                 }\n"
"                "));

        clientsControlsLayout->addWidget(sortClientsButton);

        clientsHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        clientsControlsLayout->addItem(clientsHorizontalSpacer);

        clientSearchEdit = new QLineEdit(clientsHeaderFrame);
        clientSearchEdit->setObjectName("clientSearchEdit");
        clientSearchEdit->setStyleSheet(QString::fromUtf8("\n"
"                 QLineEdit {\n"
"                     padding: 8px 12px;\n"
"                     border: 2px solid #dee2e6;\n"
"                     border-radius: 6px;\n"
"                     font-size: 14px;\n"
"                     min-width: 250px;\n"
"                 }\n"
"                 QLineEdit:focus {\n"
"                     border-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                  stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"                 }\n"
"                "));

        clientsControlsLayout->addWidget(clientSearchEdit);

        addClientButton = new QPushButton(clientsHeaderFrame);
        addClientButton->setObjectName("addClientButton");
        addClientButton->setStyleSheet(QString::fromUtf8("\n"
"                 QPushButton {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"                     border: none;\n"
"                     padding: 8px 16px;\n"
"                     color: white;\n"
"                     font-weight: bold;\n"
"                     border-radius: 6px;\n"
"                     min-width: 130px;\n"
"                 }\n"
"                 QPushButton:hover {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #ff8a95, stop: 1 #fedde5);\n"
"                 }\n"
"                "));

        clientsControlsLayout->addWidget(addClientButton);


        clientsHeaderMainLayout->addLayout(clientsControlsLayout);


        clientsLayout->addWidget(clientsHeaderFrame);

        clientsTable = new QTableWidget(clientsPage);
        clientsTable->setObjectName("clientsTable");
        clientsTable->setStyleSheet(QString::fromUtf8("\n"
"            QTableWidget {\n"
"                background: white;\n"
"                border: 1px solid #dee2e6;\n"
"                border-radius: 10px;\n"
"                gridline-color: #f8f9fa;\n"
"                font-size: 14px;\n"
"            }\n"
"            QTableWidget::item {\n"
"                padding: 8px;\n"
"            }\n"
"            QTableWidget::item:selected {\n"
"                background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                           stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"                color: white;\n"
"            }\n"
"            QHeaderView::section {\n"
"                background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \n"
"                                           stop: 0 #6c757d, stop: 1 #495057);\n"
"                color: white;\n"
"                padding: 10px;\n"
"                border: none;\n"
"                font-weight: bold;\n"
"            }\n"
"           "));
        clientsTable->setAlternatingRowColors(true);
        clientsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        clientsLayout->addWidget(clientsTable);

        stackedWidget->addWidget(clientsPage);
        commandesPage = new QWidget();
        commandesPage->setObjectName("commandesPage");
        commandesLayout = new QVBoxLayout(commandesPage);
        commandesLayout->setObjectName("commandesLayout");
        commandesLayout->setContentsMargins(20, 20, 20, 20);
        commandesHeaderFrame = new QFrame(commandesPage);
        commandesHeaderFrame->setObjectName("commandesHeaderFrame");
        commandesHeaderFrame->setStyleSheet(QString::fromUtf8("\n"
"            QFrame {\n"
"                background: white;\n"
"                border-radius: 10px;\n"
"                border: 1px solid #dee2e6;\n"
"            }\n"
"           "));
        commandesHeaderMainLayout = new QVBoxLayout(commandesHeaderFrame);
        commandesHeaderMainLayout->setObjectName("commandesHeaderMainLayout");
        commandesHeaderMainLayout->setContentsMargins(20, 15, 20, 15);
        commandesTitle = new QLabel(commandesHeaderFrame);
        commandesTitle->setObjectName("commandesTitle");

        commandesHeaderMainLayout->addWidget(commandesTitle);

        commandesSearchLayout = new QHBoxLayout();
        commandesSearchLayout->setObjectName("commandesSearchLayout");
        searchLabel = new QLabel(commandesHeaderFrame);
        searchLabel->setObjectName("searchLabel");

        commandesSearchLayout->addWidget(searchLabel);

        commandeSearchEdit = new QLineEdit(commandesHeaderFrame);
        commandeSearchEdit->setObjectName("commandeSearchEdit");
        commandeSearchEdit->setStyleSheet(QString::fromUtf8("\n"
"                 QLineEdit {\n"
"                     padding: 8px 12px;\n"
"                     border: 2px solid #dee2e6;\n"
"                     border-radius: 6px;\n"
"                     font-size: 14px;\n"
"                     min-width: 300px;\n"
"                     background: white;\n"
"                 }\n"
"                 QLineEdit:focus {\n"
"                     border-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                  stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"                 }\n"
"                "));

        commandesSearchLayout->addWidget(commandeSearchEdit);

        searchCommandesButton = new QPushButton(commandesHeaderFrame);
        searchCommandesButton->setObjectName("searchCommandesButton");
        searchCommandesButton->setStyleSheet(QString::fromUtf8("\n"
"                 QPushButton {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #28a745, stop: 1 #20c997);\n"
"                     border: none;\n"
"                     padding: 8px 16px;\n"
"                     color: white;\n"
"                     font-weight: bold;\n"
"                     border-radius: 6px;\n"
"                     min-width: 110px;\n"
"                 }\n"
"                 QPushButton:hover {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #218838, stop: 1 #1c7430);\n"
"                 }\n"
"                "));

        commandesSearchLayout->addWidget(searchCommandesButton);

        clearSearchButton = new QPushButton(commandesHeaderFrame);
        clearSearchButton->setObjectName("clearSearchButton");
        clearSearchButton->setStyleSheet(QString::fromUtf8("\n"
"                 QPushButton {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #6c757d, stop: 1 #495057);\n"
"                     border: none;\n"
"                     padding: 8px 16px;\n"
"                     color: white;\n"
"                     font-weight: bold;\n"
"                     border-radius: 6px;\n"
"                     min-width: 80px;\n"
"                 }\n"
"                 QPushButton:hover {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #5a6268, stop: 1 #343a40);\n"
"                 }\n"
"                "));

        commandesSearchLayout->addWidget(clearSearchButton);

        searchSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        commandesSearchLayout->addItem(searchSpacer);


        commandesHeaderMainLayout->addLayout(commandesSearchLayout);

        commandesControlsLayout = new QHBoxLayout();
        commandesControlsLayout->setObjectName("commandesControlsLayout");
        commandeSortCombo = new QComboBox(commandesHeaderFrame);
        commandeSortCombo->addItem(QString());
        commandeSortCombo->addItem(QString());
        commandeSortCombo->addItem(QString());
        commandeSortCombo->setObjectName("commandeSortCombo");
        commandeSortCombo->setStyleSheet(QString::fromUtf8("\n"
"                 QComboBox {\n"
"                     padding: 8px 12px;\n"
"                     border: 2px solid #dee2e6;\n"
"                     border-radius: 6px;\n"
"                     font-size: 14px;\n"
"                     min-width: 180px;\n"
"                     background: white;\n"
"                 }\n"
"                 QComboBox:focus {\n"
"                     border-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                  stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"                 }\n"
"                "));

        commandesControlsLayout->addWidget(commandeSortCombo);

        sortCommandesButton = new QPushButton(commandesHeaderFrame);
        sortCommandesButton->setObjectName("sortCommandesButton");
        sortCommandesButton->setStyleSheet(QString::fromUtf8("\n"
"                 QPushButton {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #6c757d, stop: 1 #495057);\n"
"                     border: none;\n"
"                     padding: 8px 16px;\n"
"                     color: white;\n"
"                     font-weight: bold;\n"
"                     border-radius: 6px;\n"
"                     min-width: 80px;\n"
"                 }\n"
"                 QPushButton:hover {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #5a6268, stop: 1 #343a40);\n"
"                 }\n"
"                "));

        commandesControlsLayout->addWidget(sortCommandesButton);

        commandesHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        commandesControlsLayout->addItem(commandesHorizontalSpacer);

        addCommandeButton = new QPushButton(commandesHeaderFrame);
        addCommandeButton->setObjectName("addCommandeButton");
        addCommandeButton->setStyleSheet(QString::fromUtf8("\n"
"                 QPushButton {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"                     border: none;\n"
"                     padding: 8px 16px;\n"
"                     color: white;\n"
"                     font-weight: bold;\n"
"                     border-radius: 6px;\n"
"                     min-width: 150px;\n"
"                 }\n"
"                 QPushButton:hover {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #ff8a95, stop: 1 #fedde5);\n"
"                 }\n"
"                "));

        commandesControlsLayout->addWidget(addCommandeButton);


        commandesHeaderMainLayout->addLayout(commandesControlsLayout);


        commandesLayout->addWidget(commandesHeaderFrame);

        commandesTable = new QTableWidget(commandesPage);
        commandesTable->setObjectName("commandesTable");
        commandesTable->setStyleSheet(QString::fromUtf8("\n"
"            QTableWidget {\n"
"                background: white;\n"
"                border: 1px solid #dee2e6;\n"
"                border-radius: 10px;\n"
"                gridline-color: #f8f9fa;\n"
"                font-size: 14px;\n"
"            }\n"
"            QTableWidget::item {\n"
"                padding: 8px;\n"
"            }\n"
"            QTableWidget::item:selected {\n"
"                background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                           stop: 0 #ff9a9e, stop: 1 #fecfef);\n"
"                color: white;\n"
"            }\n"
"            QHeaderView::section {\n"
"                background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \n"
"                                           stop: 0 #6c757d, stop: 1 #495057);\n"
"                color: white;\n"
"                padding: 10px;\n"
"                border: none;\n"
"                font-weight: bold;\n"
"            }\n"
"           "));
        commandesTable->setAlternatingRowColors(true);
        commandesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        commandesLayout->addWidget(commandesTable);

        stackedWidget->addWidget(commandesPage);
        statisticsPage = new QWidget();
        statisticsPage->setObjectName("statisticsPage");
        statisticsLayout = new QVBoxLayout(statisticsPage);
        statisticsLayout->setObjectName("statisticsLayout");
        statisticsLayout->setContentsMargins(20, 20, 20, 20);
        statisticsHeaderFrame = new QFrame(statisticsPage);
        statisticsHeaderFrame->setObjectName("statisticsHeaderFrame");
        statisticsHeaderFrame->setStyleSheet(QString::fromUtf8("\n"
"            QFrame {\n"
"                background: white;\n"
"                border-radius: 10px;\n"
"                border: 1px solid #dee2e6;\n"
"            }\n"
"           "));
        statisticsHeaderLayout = new QVBoxLayout(statisticsHeaderFrame);
        statisticsHeaderLayout->setObjectName("statisticsHeaderLayout");
        statisticsHeaderLayout->setContentsMargins(20, 15, 20, 15);
        statisticsTitle = new QLabel(statisticsHeaderFrame);
        statisticsTitle->setObjectName("statisticsTitle");

        statisticsHeaderLayout->addWidget(statisticsTitle);

        statsControlsLayout = new QHBoxLayout();
        statsControlsLayout->setObjectName("statsControlsLayout");
        refreshStatsButton = new QPushButton(statisticsHeaderFrame);
        refreshStatsButton->setObjectName("refreshStatsButton");
        refreshStatsButton->setStyleSheet(QString::fromUtf8("\n"
"                 QPushButton {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #28a745, stop: 1 #20c997);\n"
"                     border: none;\n"
"                     padding: 8px 16px;\n"
"                     color: white;\n"
"                     font-weight: bold;\n"
"                     border-radius: 6px;\n"
"                     min-width: 120px;\n"
"                 }\n"
"                 QPushButton:hover {\n"
"                     background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, \n"
"                                                stop: 0 #218838, stop: 1 #1c7430);\n"
"                 }\n"
"                "));

        statsControlsLayout->addWidget(refreshStatsButton);

        statsHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        statsControlsLayout->addItem(statsHorizontalSpacer);


        statisticsHeaderLayout->addLayout(statsControlsLayout);


        statisticsLayout->addWidget(statisticsHeaderFrame);

        statisticsScrollArea = new QScrollArea(statisticsPage);
        statisticsScrollArea->setObjectName("statisticsScrollArea");
        statisticsScrollArea->setWidgetResizable(true);
        statisticsScrollArea->setStyleSheet(QString::fromUtf8("\n"
"            QScrollArea {\n"
"                border: none;\n"
"                background: transparent;\n"
"            }\n"
"           "));
        statisticsScrollContent = new QWidget();
        statisticsScrollContent->setObjectName("statisticsScrollContent");
        statisticsScrollContent->setGeometry(QRect(0, 0, 1128, 600));
        statisticsScrollArea->setWidget(statisticsScrollContent);

        statisticsLayout->addWidget(statisticsScrollArea);

        stackedWidget->addWidget(statisticsPage);

        horizontalLayout->addWidget(stackedWidget);

        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        menubar->setStyleSheet(QString::fromUtf8("\n"
"     QMenuBar {\n"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \n"
"                                    stop: 0 #6c757d, stop: 1 #495057);\n"
"         color: white;\n"
"         padding: 5px;\n"
"     }\n"
"     QMenuBar::item:selected {\n"
"         background: rgba(255, 255, 255, 0.2);\n"
"         border-radius: 4px;\n"
"     }\n"
"    "));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setStyleSheet(QString::fromUtf8("\n"
"     QStatusBar {\n"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \n"
"                                    stop: 0 #6c757d, stop: 1 #495057);\n"
"         color: white;\n"
"     }\n"
"    "));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\360\237\232\232 Gestion Logistique - Livraison", nullptr));
        logoLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600; color:#ffffff;\">\360\237\232\232 WALA</span></p><p align=\"center\"><span style=\" font-size:12pt; color:#ffffff;\">Gestion Logistique</span></p></body></html>", nullptr));
        clientsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\221\245 Clients", nullptr));
        commandesButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246 Commandes", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 Export PDF", nullptr));
        statisticsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 Statistiques", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" color:#ffffff; font-size:10pt;\">\360\237\237\242 Connect\303\251</span></p></body></html>", nullptr));
        clientsTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#495057;\">\360\237\221\245 Gestion des Clients</span></p></body></html>", nullptr));
        clientSortCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\360\237\223\213 Trier par nom", nullptr));
        clientSortCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\360\237\223\215 Trier par adresse", nullptr));
        clientSortCombo->setItemText(2, QCoreApplication::translate("MainWindow", "\360\237\223\212 Trier par nb commandes", nullptr));

        sortClientsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Trier", nullptr));
        clientSearchEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher par nom, pr\303\251nom ou adresse...", nullptr));
        addClientButton->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter Client", nullptr));
        commandesTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#495057;\">\360\237\223\246 Gestion des Commandes</span></p></body></html>", nullptr));
        searchLabel->setText(QCoreApplication::translate("MainWindow", "<span style=\"font-weight:600; color:#495057;\">\360\237\224\215 Recherche:</span>", nullptr));
        commandeSearchEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par adresse, statut ou montant...", nullptr));
        searchCommandesButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher", nullptr));
        clearSearchButton->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Effacer", nullptr));
        commandeSortCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\360\237\223\205 Trier par date", nullptr));
        commandeSortCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\360\237\222\260 Trier par montant", nullptr));
        commandeSortCombo->setItemText(2, QCoreApplication::translate("MainWindow", "\360\237\223\213 Trier par statut", nullptr));

        sortCommandesButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Trier", nullptr));
        addCommandeButton->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter Commande", nullptr));
        statisticsTitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:600; color:#495057;\">\360\237\223\212 Tableau de Bord - Statistiques</span></p></body></html>", nullptr));
        refreshStatsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Actualiser", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
