#ifndef NEW_FRIEND_H
#define NEW_FRIEND_H

#include <QWidget>

namespace Ui {
class New_friend;
}

class New_friend : public QWidget
{
    Q_OBJECT

public:
    explicit New_friend(QWidget *parent = nullptr);
    ~New_friend();

private slots:
    void on_pushButton_clicked();

    void on_btn_back_clicked();

    void on_btn_reject_clicked();

    void on_btn_accept_clicked();

private:
    Ui::New_friend *ui;
};

#endif // NEW_FRIEND_H
