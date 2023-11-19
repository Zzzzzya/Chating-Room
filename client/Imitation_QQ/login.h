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
    ~login();

private slots:
    void on_btn_friend_clicked();

    void on_btn_group_clicked();

    void on_btn_addfriend_clicked();

    void on_btn_setgroup_clicked();

    void on_btn_apfriend_clicked();

    void on_btn_logout_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
