#!/bin/sh


# macos手动步骤操作：
# 1. brew 安装cmake ，确保版本号 >= 3.12 ，brew 安装ninja
# 2. brew 安装distcc，将编译服务器的路径和job number写入配置, 参考如下：
#       echo '\n10.60.80.93/16\n' >> $(brew --prefix distcc)/etc/distcc/hosts
# 3. 写入quickcc脚本
# 4. 将vscode的工程配置复制到文件中
# 5. 使用cmake生成ninja编译环境


cmake_path=`which cmake`
if [ ! -f "$cmake_path" ]; then
  echo "please install cmake >= 3.12 "
  exit -1
fi


ninja_path=`which ninja`
if [ ! -f "$ninja_path" ]; then
  brew install ninja
  ninja_path=`which ninja`
  if [ ! -f "$ninja_path" ]; then
    echo "install ninja error"
    exit -1
  fi
fi

distcc_path=`brew --prefix distcc`
if [ ! -d "$distcc_path" ]; then
    brew install distcc

    distcc_path=`brew --prefix distcc`
    if [ ! -d "$distcc_path" ]; then
        echo 'error when install distcc'
        exit -1
    fi
    echo '\n10.60.80.93/16\n' >> $distcc_path/etc/distcc/hosts

    # distcc会破坏环境，安装后需要重新安装jinja2
    pip3 install jinja2
fi

# 生成编译器脚本，distcc在link阶段是有问题的，脚本的作用就是跳过link
quickcc_dir="$HOME/quickcc/"
if [ ! -d $quickcc_dir ]; then
    mkdir $quickcc_dir

    echo '#!/bin/sh

    eval last=\${$#}
    if [[ $last == *".c" ]]
    then
        distcc $*
    else
        clang $*
    fi
    ' > $quickcc_dir/quickc.sh

    chmod +x $quickcc_dir/quickc.sh

    echo '#!/bin/sh

    eval last=\${$#}
    if [[ $last == *".cpp" ]]
    then
        distcc $*
    else
        c++ $*
    fi
    ' > $quickcc_dir/quickcc.sh

    chmod +x $quickcc_dir/quickcc.sh
fi


# copy vscode 的配置文件方便debug和build
mkdir .vscode
cp -f ./vscode_build_json/c_cpp_properties.json .vscode/
cp -f ./vscode_build_json/launch.json .vscode/
cp -f ./vscode_build_json/settings.json .vscode/
cp -f ./vscode_build_json/tasks.json .vscode/


# 生成build目录，最好是不要和代码放在一个目录，全局查找代码的时候会有问题
cd ..
mkdir bninja
cd bninja

export OPENSSL_ROOT_DIR=/usr/local/opt/openssl/
cmake -G Ninja -DBOOST_ROOT="/usr/local/Cellar/boost/1.67.0_1" -DCMAKE_BUILD_TYPE=Debug -DBUILD_CONTENTOS_TESTNET=ON -DCMAKE_CXX_COMPILER="$quickcc_dir/quickcc.sh" -DCMAKE_C_COMPILER="$quickcc_dir/quickc.sh"  ../contentos/
cd ../contentos/
