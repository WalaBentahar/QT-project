#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QSqlQuery>
#include <QPushButton>

class PieChartWidget;
class BarChartWidget;
class LineChartWidget;
class StatsCardWidget;

class StatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    void refreshStatistics(); // Public method to refresh after database operations

public slots:
    void refreshData();

private:
    void setupUI();
    void loadStatistics();
    void createStatsCards();
    void createCharts();

    // Data structures
    struct ClientStats
    {
        int totalClients;
        int activeClients;
        int clientsWithOrders;
    };

    struct CommandeStats
    {
        int totalCommandes;
        int commandesEnAttente;
        int commandesEnCours;
        int commandesLivrees;
        int commandesAnnulees;
        double montantTotal;
        double montantMoyen;
    };

    ClientStats clientStats;
    CommandeStats commandeStats;

    // UI components
    QVBoxLayout *mainLayout;
    QHBoxLayout *cardsLayout;
    QGridLayout *chartsLayout;

    StatsCardWidget *totalClientsCard;
    StatsCardWidget *totalCommandesCard;
    StatsCardWidget *montantTotalCard;
    StatsCardWidget *montantMoyenCard;

    PieChartWidget *statusPieChart;
    BarChartWidget *monthlyBarChart;
    LineChartWidget *trendLineChart;
};

// Custom widget for statistics cards
class StatsCardWidget : public QFrame
{
    Q_OBJECT

public:
    explicit StatsCardWidget(const QString &title, const QString &value,
                             const QString &icon, const QString &color,
                             QWidget *parent = nullptr);

    void updateValue(const QString &newValue);
    void animateValue(int fromValue, int toValue);

private slots:
    void onAnimationValueChanged(const QVariant &value);

private:
    void setupUI();

    QString cardTitle;
    QString cardIcon;
    QString cardColor;
    QLabel *titleLabel;
    QLabel *valueLabel;
    QLabel *iconLabel;
    QPropertyAnimation *animation;
};

// Custom pie chart widget
class PieChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PieChartWidget(QWidget *parent = nullptr);
    void setData(const QStringList &labels, const QList<double> &values, const QStringList &colors);
    void animateChart();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void onAnimationValueChanged(const QVariant &value);
    void onHoverAnimationValueChanged(const QVariant &value);

private:
    QStringList chartLabels;
    QList<double> chartValues;
    QStringList chartColors;
    QPropertyAnimation *animation;
    QPropertyAnimation *hoverAnimation;
    double animationProgress;
    int hoveredSegment;
    double hoverAnimationProgress;
};

// Custom bar chart widget
class BarChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BarChartWidget(QWidget *parent = nullptr);

    void setData(const QStringList &labels, const QList<double> &values);
    void animateChart();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onAnimationValueChanged(const QVariant &value);

private:
    QStringList chartLabels;
    QList<double> chartValues;
    QPropertyAnimation *animation;
    double animationProgress;
};

// Custom line chart widget
class LineChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LineChartWidget(QWidget *parent = nullptr);

    void setData(const QStringList &labels, const QList<double> &values);
    void animateChart();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onAnimationValueChanged(const QVariant &value);

private:
    QStringList chartLabels;
    QList<double> chartValues;
    QPropertyAnimation *animation;
    double animationProgress;
};

#endif // STATISTICSWIDGET_H
