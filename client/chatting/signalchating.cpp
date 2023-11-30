#include "signalchating.h"
#include "ui_signalchating.h"
#include<QColorDialog>
#include "friendchat.h"
#include"mysocket.h"
#include "usersql.h"

extern MySocket *mysocket;
extern UserSql *user;

signalChating::signalChating(QWidget *parent,QString name) :
    QWidget(parent),
    ui(new Ui::signalChating)
{
    ui->setupUi(this);
    this->Name=name;
    setFixedSize(730,450);
    connect(mysocket,&MySocket::chatMessageReceived,this,&signalChating::showMessage);
}

signalChating::~signalChating()
{
    delete ui;
}

void signalChating::showMessage(const QString& message)
{
    ui->textBrowser->setText(message);
}

void signalChating::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textEdit->setCurrentFont(f);
    ui->textEdit->setFocus();
}

void signalChating::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->textEdit->setFontPointSize(arg1.toDouble());
    ui->textEdit->setFocus();
}


void signalChating::on_boldBtn_clicked(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
    ui->textEdit->setFocus();
}


void signalChating::on_slopeBtn_clicked(bool checked)
{
    ui->textEdit->setFontItalic(checked);
    ui->textEdit->setFocus();
}


void signalChating::on_underlineBtn_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
    ui->textEdit->setFocus();
}


void signalChating::on_setColorBtn_clicked()
{
    color=QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
        ui->textEdit->setFocus();
    }
}

//需要数据库,且不写
void signalChating::on_preserveBtn_clicked()
{

}

void signalChating::on_clearBtn_clicked()
{
    ui->textBrowser->clear();
}

//要用到socket
void signalChating::on_sendBtn_clicked()
{
    mysocket->sendFriendMessage(user->userName,this->Name,ui->textEdit->toPlainText());
}

void signalChating::on_exitBtn_clicked()
{
    this->hide();
}

