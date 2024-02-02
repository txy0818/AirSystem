## **【问题描述】**
航班订票系统包括：录入航班信息、修改航班信息、订票、退票、查询某条航线的情况等等。试设计一个航班订票系统，将上述业务活动借助于计算机系统完成。
## **【基本要求】**
1)定义一个主菜单，方便用户实现下述操作。
2)可以录入航班信息。要求数据存储在一个数据文件中，其数据构成以及具体的数据信息请结合实际情况进行自定义。
3)修改航班信息。当航班信息改变时，可以修改航班信息。
4)存盘和导入。所有航班信息可保存到磁盘文件，也可在需要的时候从磁盘文件导入到内存。
5)可以查询某条航线的情况。例如：输入航班号，查询起降时间，起飞抵达城市，航班票价，票价折扣，确定航班是否满仓。
6)提供各种查询功能。例如，按起飞（抵达）城市查询、按航班公司查询、按票价折扣查询等。
7)可以订票。如果该航班已经无票，可以提供相关可选择航班。
8)可以退票。退票后修改相关数据文件。
9)客户资料包括：姓名，证件号，订票数量及航班情况，客户资料需以文件保存，并可实现文件导入。
【进一步完成内容】
1)订票要有编号，订单需以文件保存，并可实现文件导入；
2)提供客户资料查询功能，提供订单查询功能；
3)界面设计，要求菜单简洁、易操作、界面美观。

主要思路：航班的key是航班号，用户的key是用户名，用折半查找来加快检索速度

实现是在Linux下开发，可以在windows下运行，页面的尺寸可能不匹配
![CentOS-2024-02-03-03-10-30.png](https://cdn.nlark.com/yuque/0/2024/png/38890709/1706901153066-609eef03-61cf-4910-9f6d-d9ec467ec206.png#averageHue=%23f6eae2&clientId=u5fcefbd8-fe34-4&from=paste&height=840&id=u1c04f65a&originHeight=1050&originWidth=1680&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=185187&status=done&style=none&taskId=uf5bb634c-5cfe-41f8-a492-dee638bec08&title=&width=1344)
![CentOS-2024-02-03-03-10-40.png](https://cdn.nlark.com/yuque/0/2024/png/38890709/1706901153836-c7f1212f-8649-4e73-85b8-da415f2474f1.png#averageHue=%23a1a08e&clientId=u5fcefbd8-fe34-4&from=paste&height=840&id=u1d5622e1&originHeight=1050&originWidth=1680&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=690575&status=done&style=none&taskId=uafe68652-41d4-46de-8869-ba4b56e154e&title=&width=1344)![CentOS-2024-02-03-03-10-48.png](https://cdn.nlark.com/yuque/0/2024/png/38890709/1706901153580-9809105d-f06a-4367-b062-58762cd610f1.png#averageHue=%2375b3b5&clientId=u5fcefbd8-fe34-4&from=paste&height=840&id=ud0105402&originHeight=1050&originWidth=1680&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=426403&status=done&style=none&taskId=ue8a6f67b-fed9-411b-b6ab-9bce686125f&title=&width=1344)![CentOS-2024-02-03-03-10-55.png](https://cdn.nlark.com/yuque/0/2024/png/38890709/1706901153359-8def8090-c035-4db2-af51-66bca75a0317.png#averageHue=%23aad3e0&clientId=u5fcefbd8-fe34-4&from=paste&height=840&id=u309b7858&originHeight=1050&originWidth=1680&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=322618&status=done&style=none&taskId=uf95e4ce2-4d82-45fa-b6d9-852a1838db8&title=&width=1344)![CentOS-2024-02-03-03-11-06.png](https://cdn.nlark.com/yuque/0/2024/png/38890709/1706901154671-4297d2fa-17e3-4627-bb89-4da6d4cd832c.png#averageHue=%23aed19f&clientId=u5fcefbd8-fe34-4&from=paste&height=840&id=ucf419e57&originHeight=1050&originWidth=1680&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=283611&status=done&style=none&taskId=u3ca0a739-8b78-462b-b021-89b47ecdb39&title=&width=1344)



![CentOS-2024-02-03-03-11-27.png](https://cdn.nlark.com/yuque/0/2024/png/38890709/1706901155244-d56ff2fd-0652-48c6-a3b6-aab904900100.png#averageHue=%23a9d2df&clientId=u5fcefbd8-fe34-4&from=paste&height=840&id=udd6369d7&originHeight=1050&originWidth=1680&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=364394&status=done&style=none&taskId=u10e43ad9-cd48-46c8-951a-d28414c7ae5&title=&width=1344)
![CentOS-2024-02-03-03-11-33.png](https://cdn.nlark.com/yuque/0/2024/png/38890709/1706901153520-da90690b-3f5a-4fdc-88dd-413ebbcdb438.png#averageHue=%23aad3e0&clientId=u5fcefbd8-fe34-4&from=paste&height=840&id=u9a642d6f&originHeight=1050&originWidth=1680&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=394429&status=done&style=none&taskId=u399a71ad-cee5-4e85-9b51-93057be6bfb&title=&width=1344)

## 依赖
Qt creator (qt5)
将airplaneFile.txt, announcement.txt, manager.txt, user.txt放入该目录下（即与可执行文件同级目录）
![image.png](https://cdn.nlark.com/yuque/0/2024/png/38890709/1706901456798-8b68e6d1-ae45-4fde-a145-17c64037a752.png#averageHue=%23f9f9f9&clientId=u5fcefbd8-fe34-4&from=paste&height=696&id=u67757611&originHeight=870&originWidth=1434&originalType=binary&ratio=1.25&rotation=0&showTitle=false&size=138310&status=done&style=none&taskId=u990c374b-5040-4828-9636-affc247fd1f&title=&width=1147.2)
