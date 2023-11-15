#ifndef L_FRIEND_H
#define L_FRIEND_H

#include <QWidget>

namespace Ui {
class L_friend;
}

class L_friend : public QWidget
{
    Q_OBJECT

public:
    explicit L_friend(QWidget *parent = nullptr);
    ~L_friend();

private slots:
    void on_btn_group_clicked();

    void on_btn_addfriend_clicked();

    void on_btn_setgroup_clicked();

    void on_btn_apfriend_clicked();

private:
    Ui::L_friend *ui;
};

#endif // L_FRIEND_H
