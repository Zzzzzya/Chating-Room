#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <QWidget>
#include<Qvector>

namespace Ui {
class groupchat;
}

class groupchat : public QWidget
{
    Q_OBJECT

public:
    explicit groupchat(QWidget *parent = nullptr);
    void showOnlineNum(int total);
    void showOnlineNumber(QVector<QString>&group_name);
    ~groupchat();

private slots:
    void on_friendBtn_clicked();

    void on_groupBtn_clicked();

    void on_addFriendBtn_clicked();

    void on_creatGroupBtn_clicked();

    void on_applyBtn_clicked();

private:
    Ui::groupchat *ui;
};

#endif // GROUPCHAT_H
