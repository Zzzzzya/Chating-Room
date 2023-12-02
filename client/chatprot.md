### 连接建立和身份验证

#### 连接建立：

客户端向服务器发起连接请求，建立TCP连接。

#### 身份验证：

##### 登录请求:

```
{
  "type": "request",
  "subtype": "login",
  "content": {
    "username": ,
    "password": ,
	"time":"YYYY-MM-DD HH:MM:SS"
  }
}
```

客户端发送用户名和密码等身份验证信息进行登录。
服务器验证用户信息，如果验证成功，允许客户端登录。

```
{
  "type": "response",
  "subtype": "login",
  "success": true/false

}
```



##### 注册申请：

```
{
  "type": "request",
  "subtype": "register",
  "content": {
    "username": _________,
	"password": _________,
	"time":"YYYY-MM-DD HH:MM:SS"
  }
}
```

客户端发送用户名和密码等身份验证信息进行注册。
服务器验证用户信息并查重，如果成功，则允许客户注册。

```
{
  "type": "response",
  "subtype": "register",
  "success": true/false
}

```



### 好友管理

#### 添加(非申请)/删除好友：

客户端可以向服务器发送添加或删除好友的请求。

```
{
  "type": "request",
  "subtype": "add_friend"/"del_friend",
  "content": {
    "username":_________,
    "friend_username": _________
  }
}
```

```
{
  "type": "response",
  "subtype": "add_friend"/"del_friend",
  "success":true/false
}
```

服务器处理请求并更新用户的好友列表。

#### 查看好友列表：

客户端向服务器请求用户的好友列表。

```
{
  "type": "request",
  "subtype": "get_friend_list",
  "content": {
    "username": __________
  }
}
```

服务端向客户端发送用户的好友列表

```
{
  "type": "response",
  "subtype": "get_friend_list",
  "success": true,
  "message": [
    {"name": "friend1_name", "isOnline": 1},		// 在线
    {"name": "friend2_name", "isOnline": 0},		// 离线
    {"name": "friend3_name", "isOnline": 1}
  ]
}
```



#### 申请好友

```
{
  "type": "request",
  "subtype": "apply_friend",
  "content": {
	"applicant":___________,
    "friend_account":___________
  }
}
```

响应函数

```
{
  "type": "response",
  "subtype": "apply_friend",
  "success":true/false
}
```

#### 请求好友申请列表

```
{
  "type": "request",
  "subtype": "friend_Apply_request",
  "content": {
	"username":_______________				// 申请者
  }
}
```

响应函数

```
{
  "type": "response",
  "subtype": "friend_Apply_request",
  "success":true/false,
  "friend_Apply_List":[
  		"name": "applicant1_name",
  		"name": "applicant2_name",
  		"name": "applicant3_name"
  ]
}
```



### 即时通讯

#### 发送消息：

客户端发送消息给特定好友。

```
{
  "type": "message",
  "subtype": "text",
  "content": {
    "sendername": __________,			// 发送方
    "recipientname": __________,     	// 接收方 
    "time": "YYYY-MM-DD HH:MM:SS",
    "data":  							// 发送内容
  }
}
```

```
{
  "type": "response",
  "subtype": "text",
  "success":true/false
}
```



#### 接收消息：

客户端接收服务器转发的消息，并显示在用户界面上。

```
{
  "type": "response",
  "subtype": "text"/"group_message",
  "content": {
    "sender": __________,
    "recipient": __________,
    "time": "YYYY-MM-DD HH:MM:SS",
    "data": 
  }
}
```



### 群组聊天

#### 查看群组列表：

客户端向服务器请求用户的群组列表。

```
{
  "type": "request",
  "subtype": "get_group_list",
  "content": {
    "username": __________
  }
}
```

服务端向客户端发送用户的群组列表

```
{
  "type": "response",
  "subtype": "get_group_list",
  "success": true/false,
  "message": ["group1_Name","group2_Name",······]
} 
```



#### 查看群的成员以及人数:

客户端向服务器请求

```
{
  "type": "request",
  "subtype": "get_groupMembers_count",
  "content": {
    "groupName": __________
  }
}
```



服务端向客户端发送

```
{
  "type": "response",
  "subtype":  "get_groupMembers_count",
  "success": true/false,
  "message":{			// 是个JsonObject
		"count":    ,
		"members":["mem1","mem2",······]
  }
}
```



#### 创建/加入/退出群组：

##### 创建群组：

```
{
  "type": "request",
  "subtype": "create_group",
  "content": {
     "username":__________,
	 "group_name": __________,
     "members": __________,
	"time":"YYYY-MM-DD HH:MM:SS"
  }
}
```

```
{
  "type": "response",
  "subtype": "create_group",
  "success": true/false
}
```



##### 加入群组:

```
{
  "type": "request",
  "subtype": "join_group",
  "content": {
    "username": __________,
    "groupname": __________
  }
}
```

```
{
  "type": "response",
  "subtype": "join_group",
  "success": true/false
}
```

##### 退出群组:

```
{
  "type": "request",
  "subtype": "leave_group",
  "content": {
    "groupname": __________,
    "username": __________
  }
}
```

```
{
  "type": "response",
  "subtype": "leave_group",
  "success": true/false
}
```



#### 群组消息：

客户端发送消息到群组，服务器将消息广播给群组成员。

```
{
 "type":"message",
  "subtype": "group_message",
  "content": {
    "groupname": __________, 
    "sender": __________,
    "time": "YYYY-MM-DD HH:MM:SS",
    "data":	__________					// 发送内容
  }
}
```

```
{
  "type": "response",
  "subtype": "group_message",
  "success": true/false,
}


```



