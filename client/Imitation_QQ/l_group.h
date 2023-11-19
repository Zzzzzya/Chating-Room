#ifndef L_GROUP_H
#define L_GROUP_H

#include <QWidget>

namespace Ui {
class L_group;
}

class L_group : public QWidget
{
    Q_OBJECT

public:
    explicit L_group(QWidget *parent = nullptr);
    ~L_group();

private slots:
    void on_btn_friend_clicked();

    void on_btn_addfriend_clicked();

    void on_btn_setgroup_clicked();

    void on_btn_apfriend_clicked();

    void on_btn_logout_clicked();

private:
    Ui::L_group *ui;
};

#endif // L_GROUP_H
