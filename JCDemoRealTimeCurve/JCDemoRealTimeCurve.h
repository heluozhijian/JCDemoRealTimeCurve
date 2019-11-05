#ifndef JCDEMOREALTIMECURVE_H
#define JCDEMOREALTIMECURVE_H

#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QTimer>
// TODO: 不能包含这两个头文件，否则会报错
//#include <QDateTimeAxis>
//#include <QValueAxis>
#include <QtCharts> // 代替QDateTimeAxis和QValueAxis
using namespace QtCharts;

class JCDemoRealTimeCurve : public QMainWindow
{
    Q_OBJECT
public:
    explicit JCDemoRealTimeCurve(QWidget *parent = nullptr);
    ~JCDemoRealTimeCurve();

private:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QChartView *chartView;
    QChart *chart;
    QLineSeries *lineSeries;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QTimer *timer;

    const uint32_t MaxSize = 100;

    void setupUi(void);
    void initialize(void);

signals:

public slots:

private slots:
    void onTimer(void);
};

#endif // JCDEMOREALTIMECURVE_H
