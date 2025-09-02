#include "statisticswidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QtMath>
#include <QDate>
#include <QToolTip>
#include <QMouseEvent>

StatisticsWidget::StatisticsWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    loadStatistics();
}

void StatisticsWidget::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);

    // Create statistics cards
    createStatsCards();

    // Create charts
    createCharts();

    setLayout(mainLayout);
}

void StatisticsWidget::createStatsCards()
{
    cardsLayout = new QHBoxLayout;
    cardsLayout->setSpacing(15);

    totalClientsCard = new StatsCardWidget("Total Clients", "0", "👥", "#ff9a9e");
    totalCommandesCard = new StatsCardWidget("Total Commandes", "0", "📦", "#20c997");
    montantTotalCard = new StatsCardWidget("Montant Total", "0 DT", "💰", "#6c757d");
    montantMoyenCard = new StatsCardWidget("Montant Moyen", "0 DT", "📊", "#ffc107");

    cardsLayout->addWidget(totalClientsCard);
    cardsLayout->addWidget(totalCommandesCard);
    cardsLayout->addWidget(montantTotalCard);
    cardsLayout->addWidget(montantMoyenCard);

    mainLayout->addLayout(cardsLayout);
}

void StatisticsWidget::createCharts()
{
    chartsLayout = new QGridLayout;
    chartsLayout->setSpacing(15);

    // Pie chart for order status
    QFrame *pieFrame = new QFrame;
    pieFrame->setStyleSheet("QFrame { background: white; border-radius: 10px; border: 1px solid #dee2e6; }");
    QVBoxLayout *pieLayout = new QVBoxLayout(pieFrame);
    QLabel *pieTitle = new QLabel("📊 Répartition des Statuts");
    pieTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: #495057; padding: 10px;");
    statusPieChart = new PieChartWidget;
    statusPieChart->setMinimumHeight(300);
    pieLayout->addWidget(pieTitle);
    pieLayout->addWidget(statusPieChart);

    // Bar chart for monthly orders
    QFrame *barFrame = new QFrame;
    barFrame->setStyleSheet("QFrame { background: white; border-radius: 10px; border: 1px solid #dee2e6; }");
    QVBoxLayout *barLayout = new QVBoxLayout(barFrame);
    QLabel *barTitle = new QLabel("📈 Commandes par Mois");
    barTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: #495057; padding: 10px;");
    monthlyBarChart = new BarChartWidget;
    monthlyBarChart->setMinimumHeight(300);
    barLayout->addWidget(barTitle);
    barLayout->addWidget(monthlyBarChart);

    // Line chart for trend
    QFrame *lineFrame = new QFrame;
    lineFrame->setStyleSheet("QFrame { background: white; border-radius: 10px; border: 1px solid #dee2e6; }");
    QVBoxLayout *lineLayout = new QVBoxLayout(lineFrame);
    QLabel *lineTitle = new QLabel("📉 Évolution du Chiffre d'Affaires");
    lineTitle->setStyleSheet("font-size: 16px; font-weight: bold; color: #495057; padding: 10px;");
    trendLineChart = new LineChartWidget;
    trendLineChart->setMinimumHeight(300);
    lineLayout->addWidget(lineTitle);
    lineLayout->addWidget(trendLineChart);

    chartsLayout->addWidget(pieFrame, 0, 0);
    chartsLayout->addWidget(barFrame, 0, 1);
    chartsLayout->addWidget(lineFrame, 1, 0, 1, 2);

    mainLayout->addLayout(chartsLayout);
}

void StatisticsWidget::loadStatistics()
{
    // Reset all statistics to 0 before loading
    clientStats = ClientStats();
    commandeStats = CommandeStats();

    // Load client statistics
    QSqlQuery clientQuery;
    clientQuery.prepare("SELECT COUNT(*) FROM CLIENT");
    if (clientQuery.exec() && clientQuery.next())
    {
        clientStats.totalClients = clientQuery.value(0).toInt();
    }

    clientQuery.prepare("SELECT COUNT(DISTINCT ID_CLIENT) FROM COMMANDE");
    if (clientQuery.exec() && clientQuery.next())
    {
        clientStats.clientsWithOrders = clientQuery.value(0).toInt();
    }

    // Load command statistics
    QSqlQuery commandeQuery;
    commandeQuery.prepare("SELECT COUNT(*), SUM(MONTANT), AVG(MONTANT) FROM COMMANDE");
    if (commandeQuery.exec() && commandeQuery.next())
    {
        commandeStats.totalCommandes = commandeQuery.value(0).toInt();
        commandeStats.montantTotal = commandeQuery.value(1).toDouble();
        commandeStats.montantMoyen = commandeQuery.value(2).toDouble();
    }

    // Reset status counters
    commandeStats.commandesEnAttente = 0;
    commandeStats.commandesEnCours = 0;
    commandeStats.commandesLivrees = 0;
    commandeStats.commandesAnnulees = 0;

    // Load status statistics
    commandeQuery.prepare("SELECT STATUT, COUNT(*) FROM COMMANDE GROUP BY STATUT");
    if (commandeQuery.exec())
    {
        while (commandeQuery.next())
        {
            QString status = commandeQuery.value(0).toString();
            int count = commandeQuery.value(1).toInt();

            if (status == "En attente")
                commandeStats.commandesEnAttente = count;
            else if (status == "En cours")
                commandeStats.commandesEnCours = count;
            else if (status == "Livre")
                commandeStats.commandesLivrees = count;
            else if (status == "Annule")
                commandeStats.commandesAnnulees = count;
        }
    }

    refreshData();
}

void StatisticsWidget::refreshData()
{
    // Update cards with animation
    totalClientsCard->animateValue(0, clientStats.totalClients);
    totalCommandesCard->animateValue(0, commandeStats.totalCommandes);
    montantTotalCard->updateValue(QString::number(commandeStats.montantTotal, 'f', 2) + " DT");
    montantMoyenCard->updateValue(QString::number(commandeStats.montantMoyen, 'f', 2) + " DT");

    // Update pie chart
    QStringList statusLabels = {"En attente", "En cours", "Livre", "Annule"};
    QList<double> statusValues = {
        (double)commandeStats.commandesEnAttente,
        (double)commandeStats.commandesEnCours,
        (double)commandeStats.commandesLivrees,
        (double)commandeStats.commandesAnnulees};
    QStringList statusColors = {"#ffc107", "#17a2b8", "#28a745", "#dc3545"};
    statusPieChart->setData(statusLabels, statusValues, statusColors);
    statusPieChart->animateChart();

    // Update bar chart (monthly data)
    QStringList monthLabels;
    QList<double> monthValues;
    QSqlQuery monthQuery;
    monthQuery.prepare("SELECT TO_CHAR(DATE_COMMANDE, 'MM/YYYY'), COUNT(*) "
                       "FROM COMMANDE WHERE DATE_COMMANDE >= ADD_MONTHS(SYSDATE, -6) "
                       "GROUP BY TO_CHAR(DATE_COMMANDE, 'MM/YYYY') "
                       "ORDER BY TO_CHAR(DATE_COMMANDE, 'MM/YYYY')");
    if (monthQuery.exec())
    {
        while (monthQuery.next())
        {
            monthLabels.append(monthQuery.value(0).toString());
            monthValues.append(monthQuery.value(1).toDouble());
        }
    }
    monthlyBarChart->setData(monthLabels, monthValues);
    monthlyBarChart->animateChart();

    // Update line chart (revenue trend)
    QStringList trendLabels;
    QList<double> trendValues;
    QSqlQuery trendQuery;
    trendQuery.prepare("SELECT TO_CHAR(DATE_COMMANDE, 'MM/YYYY'), SUM(MONTANT) "
                       "FROM COMMANDE WHERE DATE_COMMANDE >= ADD_MONTHS(SYSDATE, -6) "
                       "GROUP BY TO_CHAR(DATE_COMMANDE, 'MM/YYYY') "
                       "ORDER BY TO_CHAR(DATE_COMMANDE, 'MM/YYYY')");
    if (trendQuery.exec())
    {
        while (trendQuery.next())
        {
            trendLabels.append(trendQuery.value(0).toString());
            trendValues.append(trendQuery.value(1).toDouble());
        }
    }
    trendLineChart->setData(trendLabels, trendValues);
    trendLineChart->animateChart();
}

void StatisticsWidget::refreshStatistics()
{
    // Public method to refresh all statistics - call this after add/edit/delete operations
    loadStatistics();
}

// StatsCardWidget implementation
StatsCardWidget::StatsCardWidget(const QString &title, const QString &value,
                                 const QString &icon, const QString &color,
                                 QWidget *parent)
    : QFrame(parent), cardTitle(title), cardIcon(icon), cardColor(color)
{
    setupUI();
    setStyleSheet(QString(
                      "QFrame {"
                      "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, "
                      "                                stop: 0 %1, stop: 1 white);"
                      "    border-radius: 10px;"
                      "    border: 1px solid #dee2e6;"
                      "    padding: 15px;"
                      "}")
                      .arg(color));

    animation = new QPropertyAnimation(this, "");
    animation->setDuration(1500);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(animation, &QPropertyAnimation::valueChanged, this, &StatsCardWidget::onAnimationValueChanged);
}

void StatsCardWidget::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    iconLabel = new QLabel(cardIcon);
    iconLabel->setStyleSheet("font-size: 32px; color: white;");
    iconLabel->setAlignment(Qt::AlignCenter);

    titleLabel = new QLabel(cardTitle);
    titleLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: white; margin-top: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);

    valueLabel = new QLabel("0");
    valueLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: white; margin-top: 5px;");
    valueLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(iconLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(valueLabel);
    layout->addStretch();
}

void StatsCardWidget::updateValue(const QString &newValue)
{
    valueLabel->setText(newValue);
}

void StatsCardWidget::animateValue(int fromValue, int toValue)
{
    animation->setStartValue(fromValue);
    animation->setEndValue(toValue);
    animation->start();
}

void StatsCardWidget::onAnimationValueChanged(const QVariant &value)
{
    valueLabel->setText(QString::number(value.toInt()));
}

// PieChartWidget implementation
PieChartWidget::PieChartWidget(QWidget *parent)
    : QWidget(parent), animationProgress(0.0), hoveredSegment(-1), hoverAnimationProgress(0.0)
{
    animation = new QPropertyAnimation(this, "");
    animation->setDuration(1200); // Reduced duration for faster refresh
    animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(animation, &QPropertyAnimation::valueChanged, this, &PieChartWidget::onAnimationValueChanged);

    hoverAnimation = new QPropertyAnimation(this, "");
    hoverAnimation->setDuration(200); // Faster hover response
    hoverAnimation->setEasingCurve(QEasingCurve::OutCubic);
    connect(hoverAnimation, &QPropertyAnimation::valueChanged, this, &PieChartWidget::onHoverAnimationValueChanged);

    setMouseTracking(true);
}

void PieChartWidget::setData(const QStringList &labels, const QList<double> &values, const QStringList &colors)
{
    chartLabels = labels;
    chartValues = values;
    chartColors = colors;

    // Reset animation progress when new data is set
    animationProgress = 0.0;
    update();
}

void PieChartWidget::animateChart()
{
    // Stop any existing animation
    if (animation->state() == QPropertyAnimation::Running)
    {
        animation->stop();
    }

    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start();
}

void PieChartWidget::onAnimationValueChanged(const QVariant &value)
{
    animationProgress = value.toDouble();
    update();
}

void PieChartWidget::onHoverAnimationValueChanged(const QVariant &value)
{
    hoverAnimationProgress = value.toDouble();
    update();
}

void PieChartWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (chartValues.isEmpty())
    {
        QWidget::mouseMoveEvent(event);
        return;
    }

    QRect rect = this->rect().adjusted(20, 20, -20, -40);
    int radius = qMin(rect.width(), rect.height()) / 2;
    QPoint center = rect.center();
    QPoint mousePos = event->pos();

    // Calculate distance from center
    double distance = qSqrt(qPow(mousePos.x() - center.x(), 2) + qPow(mousePos.y() - center.y(), 2));

    if (distance > radius)
    {
        if (hoveredSegment != -1)
        {
            hoveredSegment = -1;
            hoverAnimation->setStartValue(hoverAnimationProgress);
            hoverAnimation->setEndValue(0.0);
            hoverAnimation->start();
            QToolTip::hideText();
        }
        QWidget::mouseMoveEvent(event);
        return;
    }

    // Calculate angle from center to mouse position
    double dx = mousePos.x() - center.x();
    double dy = mousePos.y() - center.y();
    double angle = qAtan2(-dy, dx) * 180.0 / M_PI; // Negative dy to match Qt coordinate system

    // Normalize angle to 0-360 range, starting from top (12 o'clock position)
    angle = fmod(angle + 90 + 360, 360);

    // Find which segment the mouse is over - use only non-zero values for total
    double total = 0;
    for (double value : chartValues)
    {
        if (value > 0)
        {
            total += value;
        }
    }

    if (total == 0)
    {
        QWidget::mouseMoveEvent(event);
        return;
    }

    double currentAngle = 0;
    int newHoveredSegment = -1;

    // Check each segment in the same order as they are drawn
    for (int i = 0; i < chartValues.size(); ++i)
    {
        // Skip segments with 0 values (same logic as in paintEvent)
        if (chartValues[i] == 0)
        {
            continue;
        }

        double percentage = chartValues[i] / total;
        double segmentAngle = percentage * 360;

        // Check if mouse angle falls within this segment
        if (angle >= currentAngle && angle < currentAngle + segmentAngle)
        {
            newHoveredSegment = i;
            break;
        }

        // Only advance angle for non-zero values
        currentAngle += segmentAngle;
    }

    if (newHoveredSegment != hoveredSegment)
    {
        hoveredSegment = newHoveredSegment;

        if (hoveredSegment != -1)
        {
            hoverAnimation->setStartValue(hoverAnimationProgress);
            hoverAnimation->setEndValue(1.0);
            hoverAnimation->start();

            // Show tooltip with correct data
            double percentage = (chartValues[hoveredSegment] / total) * 100;
            QString tooltipText = QString("📊 %1\n📈 Count: %2\n📊 Percentage: %3%")
                                      .arg(chartLabels[hoveredSegment])
                                      .arg(QString::number(chartValues[hoveredSegment], 'f', 0))
                                      .arg(QString::number(percentage, 'f', 1));
            QToolTip::showText(event->globalPos(), tooltipText, this);
        }
        else
        {
            hoverAnimation->setStartValue(hoverAnimationProgress);
            hoverAnimation->setEndValue(0.0);
            hoverAnimation->start();
            QToolTip::hideText();
        }
    }

    QWidget::mouseMoveEvent(event);
}

void PieChartWidget::leaveEvent(QEvent *event)
{
    if (hoveredSegment != -1)
    {
        hoveredSegment = -1;
        hoverAnimation->setStartValue(hoverAnimationProgress);
        hoverAnimation->setEndValue(0.0);
        hoverAnimation->start();
        QToolTip::hideText();
    }
    QWidget::leaveEvent(event);
}

void PieChartWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (chartValues.isEmpty())
        return;

    // Calculate total only from non-zero values
    double total = 0;
    for (double value : chartValues)
    {
        if (value > 0)
        {
            total += value;
        }
    }

    if (total == 0)
    {
        // Draw empty state
        painter.setPen(QPen(Qt::gray, 2));
        painter.setFont(QFont("Arial", 14));
        painter.drawText(rect(), Qt::AlignCenter, "No data available");
        return;
    }

    QRect rect = this->rect().adjusted(20, 20, -20, -40);
    int radius = qMin(rect.width(), rect.height()) / 2;
    QPoint center = rect.center();

    // Start from top (12 o'clock position) - Qt uses 0 degrees at 3 o'clock, so -90 degrees for top
    double startAngle = -90;

    for (int i = 0; i < chartValues.size(); ++i)
    {
        // Skip segments with 0 values completely
        if (chartValues[i] == 0)
        {
            continue;
        }

        double percentage = chartValues[i] / total;
        double spanAngle = percentage * 360 * animationProgress;

        // Apply hover effect
        int currentRadius = radius;
        QColor segmentColor(chartColors[i]);
        int offsetX = 0, offsetY = 0;

        if (i == hoveredSegment)
        {
            currentRadius += (int)(15 * hoverAnimationProgress);
            segmentColor = segmentColor.lighter(100 + (int)(30 * hoverAnimationProgress));

            // Calculate position for hover effect - use middle of segment
            double midAngle = (startAngle + spanAngle / 2) * M_PI / 180.0;
            offsetX = (int)(8 * hoverAnimationProgress * qCos(midAngle));
            offsetY = (int)(8 * hoverAnimationProgress * qSin(midAngle));
        }

        painter.setBrush(segmentColor);
        painter.setPen(QPen(Qt::white, 2));

        painter.drawPie(center.x() - currentRadius + offsetX,
                        center.y() - currentRadius + offsetY,
                        currentRadius * 2, currentRadius * 2,
                        startAngle * 16, spanAngle * 16);

        // Only advance the angle for non-zero values
        startAngle += percentage * 360 * animationProgress;
    }

    // Draw legend with hover effects - adjusted spacing to fit all items on one line
    int legendY = rect.bottom() + 15;
    int legendX = 10; // Start closer to left edge

    // Calculate available width and divide by number of non-zero items
    int visibleItems = 0;
    for (int i = 0; i < chartLabels.size(); ++i)
    {
        if (chartValues[i] > 0)
        {
            visibleItems++;
        }
    }

    int availableWidth = width() - 20; // Total width minus margins
    int itemWidth = visibleItems > 0 ? availableWidth / visibleItems : 150;
    itemWidth = qMin(itemWidth, 180); // Maximum width per item

    for (int i = 0; i < chartLabels.size(); ++i)
    {
        // Skip empty segments in legend
        if (chartValues[i] == 0)
        {
            continue;
        }

        QColor legendColor(chartColors[i]);
        if (i == hoveredSegment)
        {
            legendColor = legendColor.lighter(130);
        }

        painter.setBrush(legendColor);
        painter.setPen(QPen(Qt::gray, 1));
        painter.drawRect(legendX, legendY, 12, 12); // Slightly smaller squares

        painter.setPen(Qt::black);
        QFont legendFont = painter.font();
        legendFont.setPointSize(8); // Smaller font size
        if (i == hoveredSegment)
        {
            legendFont.setBold(true);
        }
        painter.setFont(legendFont);

        QString legendText = QString("%1 (%2)")
                                 .arg(chartLabels[i])
                                 .arg(QString::number(chartValues[i], 'f', 0));

        // Draw text with word wrap if needed
        QRect textRect(legendX + 18, legendY - 5, itemWidth - 25, 25);
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, legendText);

        legendX += itemWidth; // Move to next position
    }
}


// BarChartWidget implementation
BarChartWidget::BarChartWidget(QWidget *parent)
    : QWidget(parent), animationProgress(0.0)
{
    animation = new QPropertyAnimation(this, "");
    animation->setDuration(1500);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(animation, &QPropertyAnimation::valueChanged, this, &BarChartWidget::onAnimationValueChanged);
}

void BarChartWidget::setData(const QStringList &labels, const QList<double> &values)
{
    chartLabels = labels;
    chartValues = values;
}

void BarChartWidget::animateChart()
{
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start();
}

void BarChartWidget::onAnimationValueChanged(const QVariant &value)
{
    animationProgress = value.toDouble();
    update();
}

void BarChartWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (chartValues.isEmpty())
        return;

    double maxValue = *std::max_element(chartValues.begin(), chartValues.end());
    if (maxValue == 0)
        return;

    QRect rect = this->rect().adjusted(40, 20, -20, -40);
    int barWidth = rect.width() / chartValues.size() - 10;

    // Draw gradient background
    QLinearGradient gradient(0, rect.top(), 0, rect.bottom());
    gradient.setColorAt(0, QColor(255, 154, 158, 50));
    gradient.setColorAt(1, QColor(254, 207, 239, 50));
    painter.fillRect(rect, gradient);

    for (int i = 0; i < chartValues.size(); ++i)
    {
        double value = chartValues[i] * animationProgress;
        int barHeight = (value / maxValue) * rect.height();

        int x = rect.left() + i * (barWidth + 10);
        int y = rect.bottom() - barHeight;

        // Draw bar with gradient
        QLinearGradient barGradient(0, y, 0, rect.bottom());
        barGradient.setColorAt(0, QColor(255, 154, 158));
        barGradient.setColorAt(1, QColor(254, 207, 239));

        painter.setBrush(barGradient);
        painter.setPen(QPen(Qt::white, 1));
        painter.drawRect(x, y, barWidth, barHeight);

        // Draw value on top of bar
        painter.setPen(Qt::black);
        painter.drawText(x, y - 5, barWidth, 20, Qt::AlignCenter, QString::number(value, 'f', 0));

        // Draw label
        painter.drawText(x, rect.bottom() + 5, barWidth, 20, Qt::AlignCenter,
                         i < chartLabels.size() ? chartLabels[i] : QString::number(i));
    }
}

// LineChartWidget implementation
LineChartWidget::LineChartWidget(QWidget *parent)
    : QWidget(parent), animationProgress(0.0)
{
    animation = new QPropertyAnimation(this, "");
    animation->setDuration(2000);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(animation, &QPropertyAnimation::valueChanged, this, &LineChartWidget::onAnimationValueChanged);
}

void LineChartWidget::setData(const QStringList &labels, const QList<double> &values)
{
    chartLabels = labels;
    chartValues = values;
}

void LineChartWidget::animateChart()
{
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start();
}

void LineChartWidget::onAnimationValueChanged(const QVariant &value)
{
    animationProgress = value.toDouble();
    update();
}

void LineChartWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (chartValues.isEmpty())
        return;

    double maxValue = *std::max_element(chartValues.begin(), chartValues.end());
    double minValue = *std::min_element(chartValues.begin(), chartValues.end());
    if (maxValue == minValue)
        return;

    QRect rect = this->rect().adjusted(40, 20, -20, -40);

    // Draw grid
    painter.setPen(QPen(QColor(200, 200, 200), 1));
    int gridLines = 5;
    for (int i = 0; i <= gridLines; ++i)
    {
        int y = rect.top() + (rect.height() * i / gridLines);
        painter.drawLine(rect.left(), y, rect.right(), y);
    }

    // Draw line chart
    if (chartValues.size() > 1)
    {
        QPainterPath path;
        QPointF firstPoint;

        for (int i = 0; i < chartValues.size() && i < (int)(chartValues.size() * animationProgress); ++i)
        {
            double normalizedValue = (chartValues[i] - minValue) / (maxValue - minValue);
            int x = rect.left() + (rect.width() * i / (chartValues.size() - 1));
            int y = rect.bottom() - (normalizedValue * rect.height());

            QPointF point(x, y);

            if (i == 0)
            {
                firstPoint = point;
                path.moveTo(point);
            }
            else
            {
                path.lineTo(point);
            }

            // Draw point
            painter.setBrush(QColor(255, 154, 158));
            painter.setPen(QPen(Qt::white, 2));
            painter.drawEllipse(point, 4, 4);
        }

        // Draw line with gradient
        QPen linePen;
        linePen.setWidth(3);
        linePen.setColor(QColor(255, 154, 158));
        painter.setPen(linePen);
        painter.drawPath(path);
    }

    // Draw labels
    painter.setPen(Qt::black);
    for (int i = 0; i < chartLabels.size(); ++i)
    {
        int x = rect.left() + (rect.width() * i / qMax(1, chartLabels.size() - 1));
        painter.drawText(x - 30, rect.bottom() + 5, 60, 20, Qt::AlignCenter, chartLabels[i]);
    }
}
