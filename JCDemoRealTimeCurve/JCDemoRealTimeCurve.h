#ifndef JCDEMOREALTIMECURVE_H
#define JCDEMOREALTIMECURVE_H

#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QtCharts>

class JCDemoRealTimeCurve : public QMainWindow
{
    Q_OBJECT

public:
    JCDemoRealTimeCurve(QWidget *parent = nullptr);
    ~JCDemoRealTimeCurve() Q_DECL_OVERRIDE;

private:
    QWidget *centralWidget;
    QGridLayout *gridLayout;

    void dataReceived(int value);
    int timerId;
    int maxSize;  // data 最多存储 maxSize 个元素
    int maxX;
    int maxY;
    QList<double> data; // 存储业务数据的 list
    QChart *chart;
    QChartView *chartView;
    QSplineSeries *splineSeries;
    QScatterSeries *scatterSeries;

protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
};

#endif // JCDEMOREALTIMECURVE_H
