#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev);
    ~Register();

private slots:
    void on_registerBtn_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
