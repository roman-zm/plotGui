#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    circle = new QCPCurve(ui->widget->xAxis, ui->widget->yAxis);
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->yAxis->setRange(-10,10);
    ui->widget->xAxis->setRange(-10,10);
    ui->widget->yAxis->setLabel("y");
    ui->widget->xAxis->setLabel("x");
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::genName(double a, double b, double c)
{
    QString response;
    QTextStream out(&response);
    if(a!=0) out << a<<"x^2";
    if(b!=0){
        if(b<0) out<<"-"<<b<<"x";
        else out<<b<<"x";
    }
    if(c!=0){
        if(c<0) out<<"-"<<c;
        else out<<c;
    }
    return response;
}

void Widget::on_linearPlotButton_clicked()
{
    double Ox=-10, Ex=10, h=0.05, a=ui->aSpinBox->value(),
            b=ui->bSpinBox->value(), c=ui->cSpinBox->value();
    int N =(Ex-Ox)/h;

    QVector<double> x(N), y(N);

    for(double i=0, X=Ox; X<=Ex; i+=1, X+=h){
        x[i] = X;
        y[i] = a*X*X+b*X+c;
    }

    ui->widget->graph(0)->setData(x,y);
    ui->widget->graph(0)->setName(this->genName(a,b,c));
    ui->widget->replot();
}

void Widget::on_circlePlotButton_clicked()
{
    double r = ui->rSpinBox->value();
    double xCenter = ui->xCenter->value();
    double yCenter = ui->yCenter->value();
    int pointCount = 500;
    QVector<double> x(pointCount), y(pointCount);
    for (int i=0; i<pointCount; ++i)
    {
      double phi = (i/(double)pointCount-1)*2*M_PI;
      x[i] = xCenter + r*qCos(phi);
      y[i] = yCenter + r*qSin(phi);
    }
    circle->setData(x,y);
    ui->widget->replot();

}

void Widget::on_addPointButton_clicked()
{
    QVector<double> px, py;
    px.push_back(ui->pxSpinBox->value());
    py.push_back(ui->pySpinBox->value());
    ui->widget->graph(1)->addData(px,py);
    ui->widget->graph(1)->setPen(QColor(50, 50,50,255));
    ui->widget->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    //coordsLabel.
    QCPItemText *text = new QCPItemText(ui->widget);
    QString label = QString::number(px[px.size()-1])+","+QString::number(py[py.size()-1]);
    text->setText(label);
    text->position->setCoords(px[px.size()-1], py[py.size()-1]+0.5);
    ui->widget->replot();
}

void Widget::on_pushButton_clicked()
{
    ui->widget->graph(1)->data()->clear();
    ui->pxSpinBox->setValue(0);
    ui->pySpinBox->setValue(0);
    ui->widget->replot();
}
