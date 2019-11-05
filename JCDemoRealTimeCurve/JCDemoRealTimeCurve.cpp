#include "JCDemoRealTimeCurve.h"

JCDemoRealTimeCurve::JCDemoRealTimeCurve(QWidget *parent)
    : QMainWindow(parent)
{
    maxSize = 31; // 只存储最新的 31 个数据
    maxX = 300;
    maxY = 100;
    splineSeries = new QSplineSeries();
    scatterSeries = new QScatterSeries();
    scatterSeries->setMarkerSize(8);

    chart = new QChart();
    chart->addSeries(splineSeries);
    chart->addSeries(scatterSeries);
    chart->legend()->hide();
    chart->setTitle(QStringLiteral("实时动态曲线"));
    chart->createDefaultAxes();

    //chart->axisX()->setRange(0, 300);
    //chart->axisY()->setRange(0, maxY);
    chart->axes().at(0)->setRange(0, 300);
    chart->axes().at(1)->setRange(0, maxY);

    chartView = new QChartView(chart);

    QValueAxis *axisx = new QValueAxis;
    axisx->setGridLineVisible(false);
    axisx->setTitleText("sample time(s)");
    // chartView->chart()->setAxisX(axisx, splineSeries);
    chartView->chart()->addAxis(axisx, Qt::AlignBottom);
    splineSeries->attachAxis(axisx);

    QValueAxis *axisy = new QValueAxis;
    axisy->setGridLineVisible(false);
    axisy->setTitleText("height(meter)");
    // chartView->chart()->setAxisY(axisy,splineSeries);
    chartView->chart()->addAxis(axisy, Qt::AlignLeft);
    splineSeries->attachAxis(axisy);

    chartView->setRenderHint(QPainter::Antialiasing);

    timerId = startTimer(200);
    qsrand(QDateTime::currentDateTime().toTime_t());

    // gridLayout
    gridLayout = new QGridLayout;
    gridLayout->setSpacing(5);
    gridLayout->setContentsMargins(0, 5, 0, 0); //left top right bottom
    gridLayout->addWidget(chartView,         0, 0);
    gridLayout->setRowStretch(0, 1);
    gridLayout->setColumnStretch(0, 1);
    // centralWidget
    centralWidget = new QWidget;
    centralWidget->setLayout(gridLayout);
    this->setCentralWidget(centralWidget);
}

JCDemoRealTimeCurve::~JCDemoRealTimeCurve()
{

}

void JCDemoRealTimeCurve::timerEvent(QTimerEvent *event)
{
    // 产生一个数据，模拟不停的接收到新数据
    if (event->timerId() == timerId) {
        int newData = qrand() % (maxY + 1);
        dataReceived(newData);
    }
}

void JCDemoRealTimeCurve::dataReceived(int value)
{
    data << value;

    // 数据个数超过了最大数量，则删除所有数据，从头开始。
    while (data.size() > maxSize) {
        data.clear();
    }

    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        splineSeries->clear();
        scatterSeries->clear();
        int dx = maxX / (maxSize-1);
        for (int i = 0; i < data.size(); ++i) {
            splineSeries->append(i*dx, data.at(i));
            scatterSeries->append(i*dx, data.at(i));
        }
    }
}

