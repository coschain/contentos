#!/bin/sh


ninja_path=`which ninja`
if [ ! -f "$ninja_path" ]; then
  brew install ninja
  ninja_path=`which ninja`
  if [ ! -f "$ninja_path" ]; then
    echo "install ninja error"
    exit -1
  fi
fi

ccache_path=`which ccache`
if [ ! -f "$ccache_path" ]; then
  brew install ccache
  ccache_path=`which ccache`
  if [ ! -f "$ccache_path" ]; then
    echo "install ccache error"
    exit -1
  fi
  ccache --set-config=run_second_cpp=false
fi


distcc_path=`brew --prefix distcc`
if [ ! -d "$distcc_path" ]; then
    brew install distcc

    distcc_path=`brew --prefix distcc`
    if [ ! -d "$distcc_path" ]; then
        echo 'error when install distcc'
        exit -1
    fi
    rm -rf $distcc_path/sbin/*
    rm $distcc_path/etc/distcc/hosts
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
        ccache distcc $*
    else
        ccache clang $*
    fi
    ' > $quickcc_dir/quickc.sh

    chmod +x $quickcc_dir/quickc.sh

    echo '#!/bin/sh

    eval last=\${$#}
    if [[ $last == *".cpp" ]]
    then
        ccache distcc $*
    else
        ccache clang++ $*
    fi
    ' > $quickcc_dir/quickcc.sh

    chmod +x $quickcc_dir/quickcc.sh
fi

