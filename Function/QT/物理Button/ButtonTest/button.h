#ifndef BUTTON_H
#define BUTTON_H
#include <QPushButton>
#include <QColor>
class Button:public QPushButton
{
    Q_OBJECT
public:
    Button(QWidget *parent);
    Button(QString Name,QString Style);
    ~Button();

private:
    QString btnStyle;
protected:
      virtual void focusInEvent(QFocusEvent *e);
      virtual void focusOutEvent(QFocusEvent *e);
};

#endif // BUTTON_H
