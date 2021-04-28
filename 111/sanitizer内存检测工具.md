# 一、sanitizer工具介绍和使用

## 1.1 背景

​        内存泄漏（Memory Leak）是指程序中分配的内存由于某种原因未释放或无法释放，造成系统内存资源的浪费，导致程序运行速度减慢甚至崩溃等严重后果。开发人员进行程序开发的过程难免会遇到内存泄露的问题，这就需要开发人员在写代码时需要严格要求自己，当然也需要工具来进行内存分析检测，确保代码的健壮性。

​        下面介绍一种使用方便、功能强大且运行速度较快的内存检测工具， gcc自带的内存检测工具sanitizer。

## 1.2 Sanitizer的简介

​         Sanitizers是谷歌发起的开源工具集，包括了AddressSanitizer, MemorySanitizer, ThreadSanitizer, LeakSanitizer，UndefinedBehaviorSanitizer。Sanitizers是GCC自带的工具。GCC从4.8版本开始支持AddressSanitizer、MemorySanitizer、ThreadSanitizer，4.9版本开始支持LeakSanitizer和undefined behavior Sanitizer。

​        Sanitizers特点：sanitizer可以在检测到内存泄露第一时间立刻终止进程，并且它可以深入检测（随应用进程一起编译）。与Valgrind 工具相比，Valgrind 会极大的降低程序运行速度，而 Sanitizer 大约只降低2倍，运行速度效率比较高。

### 1.2.1 AddressSanitizer原理

​        AddressSanitizer包含3个部分，插桩(Instrumentation) 、内存映射（memory mapping）、运行时库替换malloc()/free()。

● 插桩

​        在程序自身代码使用的内存（main application memory简写mem）的两端插入加一块区域（RedZone），使RedZone的区域的影子内存（Shadow Memory)设置为不可写，程序运行时除了分配代码自身的内存还要额外分配两端的RedZone内存。并将这两边的内存加锁，设为不能访问状态，这样可以有效的防止buffer overflow。

| RedZone1 | Mem1 | RedZone2 | Mem2 | RedZone3 | Mem3 | RedZone4 |
| :------: | :--: | :------: | :--: | :------: | :--: | :------: |

● 内存映射关系

​        mem中的8字节映射到shadow memory中是1字节。shadow memory中一个字节可能有9种不同的值：8字节都能访问，则值为0；8字节都不能访问，则值为负；前k字节能访问，后面8-k字节不能访问， 则值为k。 不同的数字表示不同的错误。

​        malloc()分配的内存总是8字节的倍数，如果要分配的缓存不是8字节的倍数，则尾部的8个字节状态不同。比如分配13字节，会得到两个8字节。前1个全是可访问，那么k=0,后一个只有前5个字节是可访问，后3个字节是不能访问，那么k=5。

● 动态运行库

​        动态运行库的作用就是将malloc/free函数进行替换，并且提供了输出错误报告的功能。malloc在分配内存时会额外的分配redzone区域的内存，redzone区域对应的影子内存加锁，主要的内存区域对应的影子内存不加锁。

​        free函数将所有分配的内存区域进行加锁，并将内存块放入隔离队列中(保证在一定的时间内不会再被malloc函数分配)。

### 1.2.2 AddressSanitizer用法

​        Address Sanitizer简称ASan，是面向C/C++语言的内存错误检测工具。

​        它主要由两部分组成：

​         ● 编译器插桩模块（编译器instrumentation模块）

​         ● 运行时库（malloc()/free()替代项的运行时库）

​         gcc 4.8 开始，AddressSanitizer 成为 gcc 的一部分，但不支持符号信息，无法显示出问题的函数和行数。从 4.9 开始，gcc 支持 AddressSanitizer 的所有功能，建议gcc使用4.9版本。

​         可以检测如下内存问题：

​         ● Use after free 　释放后使用
​         ● Heap buffer overflow　堆缓冲区溢出
​         ● Stack buffer overflow　栈缓冲区溢出
​         ● Global buffer overflow　全局缓冲区溢出
​         ● Use after return　返回后使用
​         ● Use after scope　作用域后使用
​         ● Initialization order bugs　初始化顺序错误
​         ● Memory leaks　内存泄露

​         下面为使用方法和运行例子：

​          -fsanitize=address选项编译和链接你的程序。

​          -fno-omit-frame-pointer编译，检测到内存错误时打印函数调用栈。

​          CMake环境配置，在CMakeLists添加：

​          cmake_minimum_required(VERSION 3.7)

​          project(Sanitizer)

​          set(CMAKE_CXX_FLAGS "-g -fsanitize=address -fno-omit-frame-pointer")

​          add_executable(${PROJECT_NAME} "main.cpp")

​          QMake环境配置，在pro文件中添加：

​          QMAKE_CXXFLAGS+="-g -fsanitize=address -fno-omit-frame-pointer"

#### 1.2.2.1 heap-use-after-free

代码如下：

1. int main(int argc,  char *argv[]) { 

2. char *array = new char[5]; 

3. delete []array; 

4. printf("%s\n", array); 

5. return 0; 

6. } 

执行结果如下：

![image-a](/home/yaphetshl/Desktop/git/111/img/image-a.png)

第一部分（ERROR）指出错误类型是heap-use-after-free；

第二部分（READ）, 指出线程名thread T0，操作为READ，发生的位置是main.cpp:13:5。 该heapk块之前已经在main.cpp:11:5被释放了；

该heap块是在main.cpp:9:19分配

第三部分 (SUMMARY) 前面输出的概要说明。

#### 1.2.2.2 detected memory leaks

代码如下：

1. int main(int argc, char *argv[]) { 

2. char *array = new char[5]; 

3. return 0; 

4. }

执行结果如下：

![image-b](/home/yaphetshl/Desktop/git/111/img/image-b.png)

错误类型是detected memory leaks，array对象在程序退出时未释放，有5个字节泄露。

#### 1.2.2.3 heap-buffer-overflow

​        代码如下：

​        1. int main(int argc, char *argv[]) { 

​        2. char *ret = new char[4]; 

​        3. qDebug() << ret[9]; 

​        4. return 0; 

​        5. } 

​        执行结果如下：

![image-c](/home/yaphetshl/Desktop/git/111/img/image-c.png) 

​        错误类型是heap-use-after-free堆缓冲区溢出，发生的位置是main.cpp:13:17。

### 1.2.3 Memory Sanitizer用法

​        Memory Sanitizer简称（MSan），是C/C++程序中未初始化内存读取的检测器。

​        当堆栈或堆分配的内存在写入之前被读取时，会出现未初始化的值。MSan检测这样的值影响程序执行的情况。它跟踪位字段中未初始化的位。它将允许复制未初始化的内存，以及简单的逻辑和算术运算。通常，MSan会静默地跟踪内存中未初始化数据的传播，并根据未初始化的值在执行（或未执行）代码分支时报告警告。

​        下面为使用方法和运行例子：

​        -fsanitize=memory -fPIE -pie选项编译和链接你的程序。

​        -fno-omit-frame-pointer编译，检测到内存错误时打印函数调用栈。

​        CMake环境配置，在CMakeLists添加：

​        cmake_minimum_required(VERSION 3.7)

​        project(Sanitizer)

​        set(CMAKE_CXX_FLAGS "-g -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer")

​        add_executable(${PROJECT_NAME} "main.cpp")

​        QMake环境配置，在pro文件中添加：

​        QMAKE_CXXFLAGS+="-g -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer"

​       代码如下：

​       1. int main(int argc, char *argv[]) { 

​       2. char *a = new char[10]; 

​       3. a[5] = '2'; 

​       4. if (a[0] == '2') 

​       5. printf("saniter\n"); 

​       6. return 0; 

​       7. } 

​      执行结果如下：

![image-d](/home/yaphetshl/Desktop/git/111/img/image-d.png) 

​       错误类型为use-of-uninitialized-value使用未初始化的值，产生原因：变量申请内存后未赋初始化值，发生的位置main.cpp:13:9。

### 1.2.4 Thread Sanitizer用法

​        Thread Sanitizer简称（TSan），是一种检测数据争用（data race）的工具。它由编译器指令插入模块和运行时库组成。Thread Sanitizer会降低程序运行速度约为5x-15x。

​        下面为使用方法和运行例子：

​         -fsanizize=thread选项编译和链接你的程序。

​         -fno-omit-frame-pointer编译，检测到内存错误时打印函数调用栈。

​         CMake环境配置，在CMakeLists添加：

​         cmake_minimum_required(VERSION 3.7)

​         project(Sanitizer)

​         set(CMAKE_CXX_FLAGS "-g -fsanizize=thread -fno-omit-frame-pointer")

​         add_executable(${PROJECT_NAME} "main.cpp")

​         QMake环境配置，在pro文件中添加：

​         QMAKE_CXXFLAGS+="-g -fsanizize=thread -fno-omit-frame-pointer"

​         代码如下：

​         1. int Global = 0; 

​         2. void Thread1(void *x) { 

​         3. Global++; 

​         4. return NULL; 

​         5. } 

​         6. void Thread2(void *x) { 

​         7. Global--; 

​         8. return NULL; 

​         9. } 

​         10. int main() { 

​         11. pthread_t t[2]; 

​         12. pthread_create(&t[0], NULL, Thread1, NULL); 

​         13. pthread_create(&t[1], NULL, Thread2, NULL); 

​         14. pthread_join(t[0], NULL); 

​         15. pthread_join(t[1], NULL); 

​         16. } 

​         执行结果如下：         ![image-e](/home/yaphetshl/Desktop/git/111/img/image-e.png) 

​         错误类型为data race数据争用，产生原因：两个线程同时修改全局变量Global的值，导致数据发生争用，thread T2发生的位置main.cpp:18:9，thread T1发生的位置main.cpp:13:9。

### 1.2.5 Leak Sanitizer用法

​        Leak Sanitizer简称（LSan），是一个运行时内存泄漏检测器。LSan几乎不增加任何性能开销，直到进程的最后，这时有一个额外的泄漏检测阶段。在独立模式下使用，使用-fsanitize=leak标志链接您的程序。大部分情况下Leak Sanitizer与AddressSanitizer结合使用来获得内存错误和泄漏检测。

### 1.2.6 Undefined Behavior Sanitizer用法

​        Undefined Behavior Sanitizer简称（UBSan），是一种快速的未定义行为检测器。UBSan在编译时修改程序，以捕获程序执行期间的各种未定义行为，例如：

​        ● 使用未对齐或空指针 

​        ● 有符号整数溢出

​        ● 浮点类型之间进行转换，目标溢出

​        下面为使用方法和运行例子：

​        -fsanitize=undefined选项编译和链接你的程序。

​        -fno-omit-frame-pointer编译，检测到内存错误时打印函数调用栈。

​        CMake环境配置，在CMakeLists添加：

​        cmake_minimum_required(VERSION 3.7)

​        project(Sanitizer)

​        set(CMAKE_CXX_FLAGS "-g -fsanitize=undefined -fno-omit-frame-pointer")

​        add_executable(${PROJECT_NAME} "main.cpp")

​        QMake环境配置，在pro文件中添加：

​        QMAKE_CXXFLAGS+="-g -fsanitize=undefined -fno-omit-frame-pointer"

​        代码如下：

​        1. int main(int argc, char *argv) { 

​        2. int k = 0x7fffffff; 

​        3. k += argc; 

​        4. return 0; 

​        5. } 

​        执行结果如下：![image-f](/home/yaphetshl/Desktop/git/111/img/image-f.png) 

​        错误类型是有符号整数溢出，2147483647 + 1会导致超出int数据范围。

## 1.3 Sanitizer平台兼容性

​        该工具适用于x86、ARM、MIPS（所有体系结构的32位和64位版本）。支持的操作系统有Linux、Darwin（OS X和IOS Simulator）、Android。

| OS            | X86  | X86-64 | ARM  | ARM-64 | MIPS | MIPS-64 |
| ------------- | ---- | ------ | ---- | ------ | ---- | ------- |
| Linux         | yes  | yes    | yes  | yes    |      |         |
| OS X          | yes  | yes    |      |        |      |         |
| IOS Simulator | yes  | yes    |      |        |      |         |
| Android       | yes  | yes    | yes  | yes    |      |         |

## 1.4 小结

1. 为了尽可能排除内存泄露、访问越界、堆栈溢出等错误，可以使用此三种工具同时进行检查（ASAN、LSan、UBSan）。建议在每次提交代码之前，开启此三项检查，可以排除大部分常见错误。set(CMAKE_CXX_FLAGS "-fsanitize=undefined,address,leak -fno-omit-frame-pointer")。

2. 线程检测工具Thread Sanitizer，由于改工具会和其他工具组合使用会冲突，建议在新增线程或者线程中可能出现data trace的情况下使用。例如：出现多线程的线程安全问题，可以开启此工具检查。 

3. sanitizer在debug模式下能够定位到错误代码行数(第三方库还是定位为地址,除非提供源代码)。

4. 在正常的项目开发中，会有存有大量的日志信息输出到应用程序输出里，这样会加大查找错误信息的难度，因此建议在将sanitizer错误信息输出到日志里。
   \#include <sanitizer/asan_interface.h>
   __sanitizer_set_report_path("asan.log");
   在指定的目录会生成一个asan.log.pid(进程号)的文件。

5. 可以使用宏开关进行控制，在代码编译的时候是否开启内存检查。

​       set(CMAKE_SANITIZER "${CMAKE_SANITIZER_ARG}")

​       if(CMAKE_SANITIZER STREQUAL "CMAKE_SANITIZER_ARG_ON")

​       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined,address,leak -fno-omit-frame-          pointer")

​       set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,address,leak -fno-omit-frame-pointer")

​       endif()

​       编译的时候添加参数：

​       cmake -DCMAKE_SANITIZER_ARG="CMAKE_SANITIZER_ARG_ON"