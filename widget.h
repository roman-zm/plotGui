#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<qcustomplot.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_linearPlotButton_clicked();

    void on_circlePlotButton_clicked();

    void on_addPointButton_clicked();

    void on_pushButton_clicked();

private:
    QString genName(double a, double b, double c);
    Ui::Widget *ui;
    QCPCurve *circle;
};

#endif // WIDGET_H
