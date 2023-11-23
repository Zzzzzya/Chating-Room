
# 目录

1. [接口文档] (#接口文档)
2. [安装依赖] (#安装依赖)
3. [关于conf.json] (#关于conf.json)
4. [关于test.sql] (#test.sql)
5. [关于main.cc] (#关于main.cc)

# 1.接口文档

## 声明一个连接池

```cpp
  ConnectionPool* pool = ConnectionPool::getConnectionPool();
```

## 创建一个线程

```cpp
  template <class Function, class... Args>
  explicit thread(Function&& f, Args&&... args)

  std::thread t1(op2, pool, 0, 1000);  
  // 启动新线程并执行给定函数的代码
  // 使用提供的参数。
```

第一个参数为函数指针 ， 后续参数为函数所需要的参数

## 声明一个连接对象

```cpp
  MysqlConn conn;
```

### 连接对象相关操作

```cpp
  // 初始化数据库连接
  MysqlConn();
  // 释放数据库连接
  ~MysqlConn();
```

```cpp
  // 连接数据库
  bool connect(const std::string& user, const std::string& passwd, const std::string dbName, const std::string& ip, const unsigned int& port = 3306);

  /**
  * @param user 数据库连接的用户名。
  * @param passwd 数据库连接的密码
  * @param dbName 要连接的数据库的名称。
  * @param ip MySQL服务器的IP地址。
  * @param port MySQL 服务器的端口号（如果未指定，则默认为 3306）。
  *
  * @return true if the connection is successful, false otherwise.
  */
```

```cpp

  // 更新数据库：包括 insert update delete 操作
  bool update(const std::string& sql);

  /**
  * @param sql 需要执行的sql语句
  */
```

```cpp
  // 查询数据库
  bool query(const std::string& sql);

  /**
  * @param sql 需要执行的sql语句
  */
```

```cpp
  // 遍历查询得到的结果集
  bool next();
  // 得到结果集中的字段值
  std::string value(int index);
  // 事务操作
  bool transaction();
  // 提交事务
  bool commit();
  // 事务回滚
  bool rollbock();
  // 刷新起始的空闲时间点
  void refreshAliveTime();
  // 计算连接存活的总时长
  long long getAliveTime();
```

# 2.安装依赖

   确保系统中安装了项目所需的依赖项，例如 JSON FOR MODERN C++ 等。

## 配置

### Linux版本

  Ubuntu 22.04.6 LTS

### Mysql

```shell
    # 安装mysql
    sudo apt upgrade && sudo apt install mysql-server mysql-client libmysqlclient-dev
    # 进入mysql
    sudo mysql -u root
    # 创建用户——(这里根据自己所需配置)
    create user 'xl'@'%' identified by 'root';
    # 给新用户符全部权限
    grant all on *.* to 'xl'@'%';
    
    # 退出mysql
    exit
```

### jsoncpp

```shell
    # 安装jsoncpp
    sudo apt upgrade && sudo apt install libjsoncpp-dev
```

### CMake

(可直接跳过这步)

```shell
    # 要编译本项目，要安装CMake
    sudo apt upgrade && sudo apt install cmake    

    # 将可执行文件链接动态库，使用jsoncpp
    target_link_libraries(database_connect_pool jsoncpp)

    # 将可执行文件链接动态库，使用mysqlclient
    target_link_libraries(database_connect_pool libmysqlclient.so)

## 编译测试main.c

    # 在build目录下，执行以下命令
    cmake ..
    make

## 运行
    # 可执行文件，在bin/下
```

# 3.关于conf.json

conf.json内存储的是数据库服务器相关信息。存储于./bin/

# 4.关于test.sql

文件内是sql语句，会创建一个`chat_online`数据库 和 三个表（与数据库存储方案中一致）。

# 5. 关于main.cc

main.cc 内是一个测试代码，分别测试了单线程，多线程，使用线程池和不使用线程池的情况所用时间
