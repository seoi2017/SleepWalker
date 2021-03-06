# About Storage.SleepWalker

## General

- 一个自用的基于WSL+VSCode+Git的OI\CPC代码管理方案
- 个人的刷题代码存储仓库

## Why "SleepWalker" ?

SleepWalker是本人在OI阶段为一套题目拟定的一组背景故事，有兴趣的话可以去我的其他仓库看看

或许以后我也会搬运一份过来？说不定呢。

## Management Solution?

代码管理方案主要基于`SleepWalker/.vscode`文件夹中的配置文件，要想配置该方案，您需要：

1. 使用支持WSL功能的Windows 10系统，并打开WSL功能
2. 安装基于Ubuntu的WSL
3. 安装`g++`与`gdb`软件包，使用`sudo apt install`命令
4. 【可选】若要支持Java，请安装JDK，推荐最新版本的`openjdk`或者`default-jdk`，后者基于Java8，当指令`javac`和`java`均能够正确识别时即为安装成功
5. 不必额外安装Python，WSL中自带高版本Python3，通过`python3`命令调用；默认的`python`命令是Python2的执行命令
6. 【可选】若要支持其他编程语言，可以自行搜索配置方法

完成以上前置步骤后，您需要在VSCode下继续执行如下配置：

1. 请注意您的VSCode应安装在Windows中而非WSL中，并安装`remote-wsl`插件
2. 点击左下角状态栏中的绿色图标，进入WSL环境下的VSCode
3. 通过文件夹建立您的工作目录，如有必要可以设置Git同步
4. 将本仓库中的`.vscode`文件夹复制到您的工作目录下
5. 在您的工作目录下新建`IO`文件夹，并在其下建立`in.io`和`out.io`两个空文件

完成如上全部工作后，您的配置已完成，现在您可以实现如下功能：

1. 通过在新建的C++文件中键入`main`以快速输入注释头\基础头文件\文件IO\主函数体等内容，减少重复的工作时间
2. 本地全部采用文件IO方式读写（`IO/in.io`&`IO/out.io`），可直接复制代码到OJ而无需删除文件IO部分内容
3. F5一键编译运行C++文件时，不会生成过多的可执行文件占用空间，支持GDB调试

对于以上的内容，您也可以通过修改配置文件进行自定义，这里不再赘述。

## To Learn


C++ cin\cout 的格式控制


CMAKE


OpenMP


SSE\AVX


智能指针


Node* a和Node *&a的区别


仿函数


属性(C++11及更新)


用户代码片段中的多光标同时修改


内存对齐与#pragma pack()


const关键字的用法


覆写与重载


CMake


类模版成员函数不可分离编译


类模版友元函数不可类外实现


在包含智能指针类的构造函数中对智能指针的初始化一定要用其构造函数而不能直接调用其reset方法！


## TODO


DSAA LAB4 D 对顶堆BUG


格式化所有代码文档


删除 DSAA LAB4 及以后的代码中重复的头文件引用


C++ Assignment 2 BUG修正与文档撰述


DSAA Lab7 代码整理