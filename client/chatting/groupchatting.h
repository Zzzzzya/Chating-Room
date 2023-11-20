#ifndef GROUPCHATTING_H
#define GROUPCHATTING_H

#include <QWidget>

namespace Ui {
class groupChatting;
}

class groupChatting : public QWidget
{
    Q_OBJECT

public:
    explicit groupChatting(QWidget *parent = nullptr);
    ~groupChatting();

private:
    Ui::groupChatting *ui;
};

#endif // GROUPCHATTING_H
