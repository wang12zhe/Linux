#include "widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    SetUITabOrder();

}

Widget::~Widget()
{
}

void Widget::initUI(){
    mainLayout = new QHBoxLayout(this);
    btnVerScreen   = new Button(tr("VerScreen"),"QPushButton{background-color:rgb(255,255,0)}");
    btnHorScreenen = new Button(tr("HorScreene"),"QPushButton{background-color:rgb(255,255,0)}");
    btn1Sensor     = new Button(tr("btn1Sensor"),"QPushButton{background-color:rgb(255,255,0)}");
    btn2Sensor     = new Button(tr("btn2Sensor"),"QPushButton{background-color:rgb(255,255,0)}");
    btn3Sensor     = new Button(tr("btn3Sensor"),"QPushButton{background-color:rgb(255,255,0)}");
    btn4Sensor     = new Button(tr("btn4Sensor"),"QPushButton{background-color:rgb(255,255,0)}");

    mainLayout->addWidget(btnHorScreenen);
    mainLayout->addWidget(btnVerScreen);
    mainLayout->addWidget(btn1Sensor);
    mainLayout->addWidget(btn2Sensor);
    mainLayout->addWidget(btn3Sensor);
    mainLayout->addWidget(btn4Sensor);
}
void Widget::SetUITabOrder(){

    QWidget::setTabOrder(btnHorScreenen,btnVerScreen);
    QWidget::setTabOrder(btnVerScreen,btn1Sensor);
    QWidget::setTabOrder(btn1Sensor,btn2Sensor);
    QWidget::setTabOrder(btn2Sensor,btn3Sensor);
    QWidget::setTabOrder(btn3Sensor,btn4Sensor);
    QWidget::setTabOrder(btn4Sensor,btnHorScreenen);
}

#if 0
void Widget::keyPressEvent(QKeyEvent *event){
    switch (event->key())
    {
        //ESC键
        case Qt::Key_Escape:
            qDebug() <<"ESC";
        break;
        //回车键
        case Qt::Key_Return:
            qDebug() <<"Enter";
        break;
        //退格键
        case Qt::Key_Backspace:
            qDebug() <<"Back";
        break;
        //空格键
        case Qt::Key_Space:
            qDebug() <<"Space";
        break;
        //F1键
        case Qt::Key_F1:
            qDebug() <<"F1";
        break;
        case Qt::Key_Tab:
            qDebug() <<"Tab";
        break;
    }
}
#endif


