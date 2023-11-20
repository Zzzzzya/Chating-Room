#ifndef FRIENDCHAT_H
#define FRIENDCHAT_H

#include <QWidget>
#include<QVector>
#include<QListWidgetItem>

namespace Ui {
class friendChat;
}

class friendChat : public QWidget
{
    Q_OBJECT

public:
    explicit friendChat(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev);
    void showOnlineNum(int total,int online);
    void showOnlineNumber(QVector<QString> &onlineperson);
    void showSignalChatting();
    ~friendChat();

private slots:
    void on_friendBtn_clicked();

    void on_groupBtn_clicked();

    void on_addFriendBtn_clicked();

    void on_creatGroupBtn_clicked();

    void on_applyBtn_clicked();

    void itemClicked(QListWidgetItem* item);



private:
    Ui::friendChat *ui;
};

#endif // FRIENDCHAT_H
