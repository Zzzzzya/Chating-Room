#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev);
    bool checkMessage();
    ~login();

private slots:
    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
