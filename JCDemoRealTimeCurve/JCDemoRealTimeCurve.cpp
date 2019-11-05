#include "JCDemoRealTimeCurve.h"

#include <QDebug>
#include <QElapsedTimer>

JCDemoRealTimeCurve::JCDemoRealTimeCurve(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("RealTimeCurve"));
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowState(Qt::WindowMaximized);

    setupUi();
    initialize();
}

JCDemoRealTimeCurve::~JCDemoRealTimeCurve()
{

}

void JCDemoRealTimeCurve::setupUi(void)
{
    // lineSeries
    lineSeries = new QLineSeries;
    lineSeries->clear();

    // axisX
    axisX = new QDateTimeAxis;
    // axisX->setFormat("HH:mm:ss:zzz");
    axisX->setFormat("HH:mm:ss");
    axisX->setLabelsAngle(60);
    axisX->setTickCount(11);

    // axisY
    axisY = new QValueAxis;
    axisY->setRange(0, 360);
    axisY->setTickCount(6);

    // chart
    chart = new QChart;
    chart->setTitle("RealTimeCurve");
    chart->setTheme(QChart::ChartThemeBrownSand);
    chart->legend()->hide();

    chart->addSeries(lineSeries);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    lineSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisY);

    // chartView
    chartView = new QChartView(chart);

    // gridLayout
    gridLayout = new QGridLayout;
    gridLayout->setSpacing(5);
    gridLayout->setContentsMargins(0, 0, 0, 0); //left top right bottom
    gridLayout->addWidget(chartView, 0, 0);
    gridLayout->setRowStretch(0, 1);
    gridLayout->setColumnStretch(0, 1);

    // centralWidget
    centralWidget = new QWidget;
    centralWidget->setLayout(gridLayout);

    // this
    this->setCentralWidget(centralWidget);
}

void JCDemoRealTimeCurve::initialize(void)
{
    timer = new QTimer();
    timer->setInterval(100);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start();
}

void JCDemoRealTimeCurve::onTimer(void)
{
    static bool flag = true;
    static QDateTime beginTime, endTime;

    if (flag == true) {
        flag = false;
        QElapsedTimer t;
        t.start();
        beginTime = QDateTime::currentDateTime();
        endTime = beginTime.addMSecs(MaxSize * static_cast<uint32_t>(timer->interval()));
        axisX->setMin(beginTime);
        axisX->setMax(endTime); // TODO: waste about 30ms
        // axisX->setRange(beginTime, endTime);
        qDebug() << "QElapsedTimer" << t.elapsed();
    }

    if (lineSeries->count() < static_cast<int32_t>(MaxSize)) {
        qint64 x1 = QDateTime::currentMSecsSinceEpoch();
        lineSeries->append(x1, 100.0);
    }

    // lineSeries->show();
}
