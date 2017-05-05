# freetype_opencv
OpenCV自带的cvInitFont和cvPutText(putText)函数不支持向图像中写入中文，需要使用FreeType库来进行汉字显示。

FreeType(https://www.freetype.org/) 库是开源的、高质量的且可移植的字体引擎，它提供统一的接口来访问多种字体格式文件。

# freeType环境配置（windows下vs2013）
1. 从官网下载好源代码后，进入到 E:\freetype-2.6.2\builds\windows(根据个人存放位置和下载的版本情况有所不同)，由于我电脑使用的是VS2013，而该文件夹下并没有VS2013
的工程文件，直接复制vc2010文件夹，并改为vc2013，用VS2013打开文件夹下面的freetype.sln,系统会提示更新，打开后的工程就是vc2013工程了。

2. 根据你的需要，选择Debug或者Release，win32或者X64，然后编译生成，就会在E:\freetype-2.6.2\objs\vc2010文件夹里生成相应的lib文件。
3. 更改本项目的属性，需要修改的总共有三处：
* VC++目录 ---> 包含目录  ：E:\freetype-2.6.2\include（根据自己文件夹放的位置不同而不同，视情况修改）
* VC++目录 ---> 库目录：E:\freetype-2.6.2\objs\vc2010（就是第2步中lib生成的目录）
* 链接器 ---> 附加依赖项 ：添加freetype22.lib；freetype262d.lib（就是第2步中生成的lib的名称，freetype22.lib为Release模式，freetype22d.lib为Debug模式）

