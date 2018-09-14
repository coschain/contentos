
# macos手动步骤操作：
# 1. brew 安装cmake ，确保版本号 >= 3.12 ，brew 安装ninja


# 2. brew 安装ccache，设置ccache的run\_second\_cpp=false配置
# 3. brew 安装distcc，将编译服务器的路径和job number写入配置, 参考如下：
#       echo '\n10.60.80.93/16\n' >> $(brew --prefix distcc)/etc/distcc/hosts
# 4. 写入quickcc脚本

#### 以上参考运行 install-quick-compiler.sh

# 5. 将vscode的工程配置复制到文件中
#### 使用copy\_config\_to\_vscode.sh 复制配置到工程目录
#### 使用copy\_config\_to\_vscode.sh up 复制配置到源码目录准备提交

# 6. 使用cmake生成ninja编译环境
#### 参考运行 gen\_ninja\_proj.sh
