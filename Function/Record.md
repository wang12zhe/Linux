# 电路板和Ubuntu通过NFS 共享文件

## mount -t nfs -o nolock,nfsvers=3 192.168.11.119:/home/owen/nfs /mnt/nfs/

# 配置ARM Linux GCC

## 最好在每个用户资格的.bashrc文件里配置，这样开机后自动生效

# 更新Uboot的方法

## 待完善

# 更新Kernl和dtb的方法

## tftp 80800000 zImage 

## tftp 83000000 imx6ull-14x14-evk.dtb 

## bootz 80800000 - 83000000

# 更新rootfs的方法

## 待完善

# Uboot 设置网络参数

## setenv ipaddr 192.168.11.57

## setenv ethaddr 00:04:9f:04:d2:35

## setenv gatewayip 192.168.11.1

## setenv netmask 255.255.255.0

## setenv serverip 192.168.11.119

## saveenv

# 加载模块方法

## insmode ***.ko,  这中加载方式不会加载相应的依赖文件，模块文件名需要带上完整扩展名。

## 将xxx.ko文件拷贝到lib/modules/4.1.15/ 目录，执行depmod 然后执行modprobe xxx,注意这里的顺序，而且modprobe xxx 不能有扩展名

# 安装opkg包管理软件

## wget  http://pkg.entware.net/binaries/armv7/installer/entware_install.sh

## 然后执行脚本entware_install.sh，默认安装在/opt目录，设置环境变量在/etc/profile新增 export PATH=$PATH:/opt/bin   export PATH=$PATH:/opt/sbin,然后执行source /etc/profile

## okpg update,重启后就可以安装命令，例如opkg install tree

# 程序开机自启动

## 将带起的的程序加入/etc/rc.local文件即可，必须设置程序在后台运行，否则将导致无法机内终端，

# 查看某个设备的主次设备号

## ls -l /dev/设备节点,cat /proc/devices可以查看当前有哪些设备

# 在Uboot中更新Uboot(uboot常用命令里mmc write命令章节)

## mmc dev 1:0

## tftp 80800000 u-boot.imx

## mmc write 80800000 2 346    # 346 = u-boot.imx文件大小除以512 得到的16进制mm 

## mmc partconf 1 1 0 0

## 环境变量里的panel 必须和 struct display_info_t const displays[]里的.name 字段相同

# 设置Uboot环境参数

## 新增环境变量setnetpar 

## setenv setnetpar "setenv ipaddr 192.168.11.5;setenv ethaddr 00:04:9f:04:d2:35;setenv gatewayip 192.168.11.1;setenv netmask 255.255.255.0;setenv serverip 192.168.11.119;saveenv;ping 192.168.11.119"

## saveenv，运行方法run setnetpar

# 设置不同的终端

## 设置串口终端:setenv mmcargs "setenv bootargs console=${console},${baudrate} root=${mmcroot}"

## 设置LCD为终端setenv mmcargs "setenv bootargs console=tty1 root=${mmcroot}"

## 设置LCD 和串口作为终端 setenv mmcargs "setenv bootargs console=tty1 console=${console},${baudrate} root=${mmcroot}"

### ALIENTEK 设置静态IP

## 在/etc/rc.local文件的开头加入 sleep 5  ifconfig eth0 192.168.11.57

# 安装模块多指定目录

## make modules_install INSTALL_MOD_PATH=/home/owen/nfs

# vscode 远程连接开发板进行调试需要安装的软件：libpython2.7-dev

## 