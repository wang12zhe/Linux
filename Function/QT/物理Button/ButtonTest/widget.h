#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QKeyEvent>
#include "button.h"
#include <QDebug>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Button *btnVerScreen;
    Button *btnHorScreenen;
    Button *btn1Sensor;
    Button *btn2Sensor;
    Button *btn3Sensor;
    Button *btn4Sensor;

    QHBoxLayout *mainLayout;
   // void keyPressEvent(QKeyEvent *);
    void initUI();
    void SetUITabOrder();
};
#endif // WIDGET_H
