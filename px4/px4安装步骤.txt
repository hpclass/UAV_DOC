--------------------------------------------------------------------
PX4安装步骤
--------------------------------------------------------------------

1. 
sudo usermod -a -G dialout $USER

2. 
sudo add-apt-repository ppa:george-edison55/cmake-3.x -y
sudo apt-get update
sudo apt-get install python-argparse git-core wget zip \
    python-empy qtcreator cmake build-essential genromfs -y
	
3. 
sudo apt-get remove modemmanager

4. 
sudo apt-get install python-serial openocd \
    flex bison libncurses5-dev autoconf texinfo build-essential \
    libftdi-dev libtool zlib1g-dev \
    python-empy  -y
	
5. 
sudo apt-get remove gcc-arm-none-eabi gdb-arm-none-eabi binutils-arm-none-eabi gcc-arm-embedded
sudo add-apt-repository --remove ppa:team-gcc-arm-embedded/ppa

6.
cat > $HOME/rule.tmp <<_EOF
# All 3D Robotics (includes PX4) devices
SUBSYSTEM=="usb", ATTR{idVendor}=="26AC", GROUP="plugdev"
# FTDI (and Black Magic Probe) Devices
SUBSYSTEM=="usb", ATTR{idVendor}=="0483", GROUP="plugdev"
# Olimex Devices
SUBSYSTEM=="usb",  ATTR{idVendor}=="15ba", GROUP="plugdev"
_EOF
sudo mv $HOME/rule.tmp /etc/udev/rules.d/10-px4.rules
sudo /etc/init.d/udev restart

7. 
sudo usermod -a -G plugdev $USER

8. 
sudo yum install glibc.i686 ncurses-libs.i686

9.
sudo usermod -a -G uucp $USER

10.
pushd .
cd ~
wget https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q2-update/+download/gcc-arm-none-eabi-5_4-2016q2-20160622-linux.tar.bz2
tar -jxf gcc-arm-none-eabi-5_4-2016q2-20160622-linux.tar.bz2
exportline="export PATH=$HOME/gcc-arm-none-eabi-5_4-2016q2/bin:\$PATH"
if grep -Fxq "$exportline" ~/.profile; then echo nothing to do ; else echo $exportline >> ~/.profile; fi
. ~/.profile
popd

11. 
sudo dpkg --add-architecture i386
sudo apt-get update

sudo apt-get install libc6:i386 libgcc1:i386 libstdc++5:i386 libstdc++6:i386
sudo apt-get install gcc-4.6-base:i386

12
arm-none-eabi-gcc --version
cmake -version

ubunut17:
make -C /home/yangang/work/px4/theone-mc/build_theone -j4 --no-print-directory 
Scanning dependencies of target git_genmsg
Scanning dependencies of target __nuttx_patch_px4io-v2
Scanning dependencies of target git_gencpp
[  0%] Built target __nuttx_patch_px4io-v2
[  1%] Generating git_init_Tools_genmsg.stamp
[  0%] Generating git_init_Tools_gencpp.stamp
[  1%] Built target git_gencpp


