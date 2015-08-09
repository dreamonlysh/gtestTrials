# 概述
>   本文主要描述如何在vs环境下，搭建可执行的gmock(gtest)运行环境。

# 环境搭建
## 编译gmock(以VS2013为例)
1.选择Win32 Project，修改工程名
2.选择Static library，Additional options全部不勾选
3.拷贝gmock文件到工程路径下：
``` file stru
\-- gmock-1.7.0
    \-- include
        |-- gmock
    |-- src
    \-- gtest
        \-- include
            |-- gtest
        |-- src
```
4.将gmock-1.7.0/src/gmock-all.cc以及gmoc-1.7.0/gtest/src/gtest-all.cc添加进工程
5.设置工程属性(C/C++ -> General -> Additional Include Directory)
```
$(ROOT_PATH)/gmock-1.7.0
$(ROOT_PATH)/gmock-1.7.0/include
$(ROOT_PATH)/gmock-1.7.0/gtest
$(ROOT_PATH)/gmock-1.7.0/gtest/include
```
6.使用UltraEdit将gmock-1.7.0/src/gmock-matchers.cc由UTF-8转为ASCII
7.编译工程生成lib文件

## 创建测试工程
1.选择Win32 Console Application，修改工程名
2.选择Console Application，Additional options只勾选Empty project
3.将gmock-1.7.0/src/gmock_main.cc添加进工程(图省事)
4.设置工程属性
```
- C/C++ -> General -> Additional Include Directory
    + $(ROOT_PATH)/gmock-1.7.0/include
    + $(ROOT_PATH)/gmock-1.7.0/gtest/include
- Linker -> General -> Additional Library Directories
    + 添加gmock lib文件所在路径
- Linker -> Input -> Additional Dependencies
    + 添加gmoc lib文件(ex: gmock.lib)
```
5.右键Set As StartUp Project
6.运行工程，可见0测试控制台界面