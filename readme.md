# Coo-coo chatroom

### Project introduction

<img src="img/project introduction.png" alt="project introduction" style="zoom:67%;" />

### UI Design

<img src="img/UI Design.png" alt="UI display" style="zoom: 50%;" />

### System Design

系统采用客户端-服务器架构，分为Client端和Server端两部分。系统结构图如下：

<img src="img/System structure.png" alt="System structure" style="zoom: 50%;" />

客户端与服务器采用socket通讯，使用json格式作为通讯数据格式。json中封装MsgType，根据MsgType封装其他信息。接口接受json后，首先拆包，根据MsgType进行分类处理。
