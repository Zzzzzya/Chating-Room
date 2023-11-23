#ifndef SIGNALCHATING_H
#define SIGNALCHATING_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTcpSocket>

namespace Ui {
class signalChating;
}

typedef struct
{
    QString usrname;
    QString usrpass;
}info;
class signalChating : public QWidget
{
    Q_OBJECT

public:
    explicit signalChating(QWidget *parent = nullptr);
    ~signalChating();

    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    // 查询全部数据
    void queryTable(QList<QString> &list);
    // 插入数据
    // 关闭数据库
    void closeDb(void);

private slots:
    void on_preserveBtn_clicked();
    void on_sendBtn_clicked();

private:
    Ui::signalChating *ui;
    QSqlDatabase db; // 数据库连接对象
    QTcpSocket *socket; // TCP通信对象
};

#endif // SIGNALCHATING_H
