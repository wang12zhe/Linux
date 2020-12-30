#include "button.h"

Button::Button(QWidget *parent)
{

}

Button::Button(QString Name,QString Style)
{
    btnStyle = Style;
    this->setText(Name);
}

Button::~Button()
{

}

void Button::focusInEvent(QFocusEvent *e)
{
    //setStyleSheet("QPushButton{background-color:rgb(255,255,0)}");
    setStyleSheet(btnStyle);

}

void Button::focusOutEvent(QFocusEvent *e)
{
    setStyleSheet("QPushButton{background-color:rgb(255,255,255)}");
}
