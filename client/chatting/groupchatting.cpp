#include "groupchatting.h"
#include "ui_groupchatting.h"

groupChatting::groupChatting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupChatting)
{
    ui->setupUi(this);
}

groupChatting::~groupChatting()
{
    delete ui;
}
