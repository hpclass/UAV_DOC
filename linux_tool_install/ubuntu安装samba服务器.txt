在ubuntu下安装samba服务器

一. samba的安装:

sudo apt-get install samba

二. 创建共享目录:

mkdir /home/yangang(用户名)/share
sudo chmod 777 /home/user(用户名)/share

三. 创建Samba配置文件:

1. 保存现有的配置文件

sudo cp /etc/samba/smb.conf /etc/samba/smb.conf.bak

2. 修改现配置文件

sudo gedit /etc/samba/smb.conf

在smb.conf最后添加

[share]
      path = /home/user(用户)/share     //上面创建的samba分享路径
      available = yes
      browsealbe = yes
      public = yes
      writable = yes

 
四. 重启samba服务器
sudo /etc/init.d/samba restart

六，使用

可以到windows下输入ip使用了，在文件夹处输入 "\\" + "Ubuntu机器的ip
示例: 192.168.136.129