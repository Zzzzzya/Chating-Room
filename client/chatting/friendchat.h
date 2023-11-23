#ifndef FRIENDCHAT_H
#define FRIENDCHAT_H

#include <QWidget>
#include<QVector>

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
    ~friendChat();

public slots:
    void updateFriendList(const QString& friendName);

    void showSignalChatting();

private slots:
    void on_friendBtn_clicked();

    void on_groupBtn_clicked();

    void on_addFriendBtn_clicked();

    void on_creatGroupBtn_clicked();

    void on_applyBtn_clicked();

private:
    Ui::friendChat *ui;
};

#endif // FRIENDCHAT_H
