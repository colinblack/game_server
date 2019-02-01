重要的类和函数：
DataBase ：将内存数据保存在proto文件中的数据层基类
LogicBase ：匹配DataBase使用的逻辑层基类
CGI_ACTION_FUNCTION / LogicCmdAction ：应用层的简略模版
LogicCmdBase.h ：常用功能/活动封装的基类
LogicUnitWrap.h ：常用属性封装的基类
ConfigManager.h ：配置管理器
ActivityConfig.h ：活动时间管理器

自动化：
使用protobuf保存数据的（继承DataBase），写proto配置之后，使用Proto.cpp中的工具可以自动生成对应的结构体代码。
新增数据表的，生成数据库表之后，使用svn://192.168.100.251/sg17_s/dbcconfig 中的工具可以自动生成新的dbc。

测试工具：
部署 simulation.html 和 CgiSendUrl 即可模拟前端发包