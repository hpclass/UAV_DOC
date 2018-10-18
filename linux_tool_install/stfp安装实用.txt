特点:
1）sftp 与 ftp 有着几乎一样的语法和功能。
2）SFTP 为 SSH的一部分，是一种传输档案至 Blogger 伺服器的安全方式。
3）SFTP本身没有单独的守护进程，它必须使用sshd守护进程（端口号默认是22）来完成相应的连接操作
4）SFTP安全性非常高
5）SSH软件已经包含SFTP安全文件传输子系统

安装方法:

1. 查看是否安装ssh
ssh -version

2. 没有发现ssh就安装ssh 【仅仅实用文件传输就是不要安装client】
安装ssh-client命令：sudo apt-get install openssh-client
安装ssh-server命令：sudo apt-get install openssh-server   

3. 启动ssh服务
sudo /etc/init.d/ssh restart

4. 查看是否启动成功
zht@zht-Ubuntu:~$ ps -e|grep ssh
 2151 ?        00:00:00 ssh-agent
 5313 ?        00:00:00 sshd

5. 测试是否成功

The authenticity of host '192.168.1.107 (192.168.1.107)' can't be established.
ECDSA key fingerprint is SHA256:f83tSawxo1U2Guyu6p5xvSmyfBCSUbJJsNXIbZKjnWQ.
Are you sure you want to continue connecting (yes/no)? yes
Warning: Permanently added '192.168.1.107' (ECDSA) to the list of known hosts.
yangang@192.168.1.107's password: 

【输入你的密码】

6. 成功登录的界面

Welcome to Ubuntu 15.10 (GNU/Linux 4.2.0-16-generic x86_64)

 * Documentation:  https://help.ubuntu.com/

224 packages can be updated.
0 updates are security updates.


7.在flashFTP中设置
  1) 新建1个连接
  2) 选择协议，SFTP, 输入网址192.168.1.107, 用户名yangang
     密码725807
