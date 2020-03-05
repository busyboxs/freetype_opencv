# OpenCV 在图像中显示中文

## 本机环境

* Windows 10
* Visual Studio Community 2017 (version 15.9.17)
* OpenCV 4.1.2
* freetype 2.10.1

## Visual Studio 下 OpenCV 环境配置

Visual Studio 下 OpenCV 环境配置可以参见我的另外一篇博客：[Visual Studio Opencv 环境配置 - 手动配置](https://github.com/busyboxs/freetype_opencv/blob/master/opencv_visual_studio.md)

## freetype 环境配置

首先下载 freetype 文件。下载地址：[FreeType Downloads](https://www.freetype.org/download.html)

然后将文件解压，我这里解压到 D 盘

![文件解压](images/freetypevs001.png)

然后找到 `~\build\windows\vs2010` 路径，鼠标右键 `freetype.sln`，用 Visual Studio 打开。

![](images/freetypevs002.png)

然后鼠标右键项目名 `freetype`，选择 “重定向项目”。

![](images/freetypevs003.png)

然后点击 “确定”。

![](images/freetypevs004.png)

然后查看项目的属性，可以看到链接文件的输出路径

![](images/freetypevs005.png)

这里可以选择不同的配置（Debug & Release）和平台（Win32 & x64），然后运行项目就可以生成对应配置和平台的链接文件。

![](images/freetypevs006.png)

最终我们需要的是 `freetype.lib` 文件，为了方便我把该文件复制到了 `D:\freetype-2.10.1\lib\X64\Debug\`

![](images/freetypevs007.png)

## Visual Studio 配置

Visual Studio 中需要配置包含目录，库目录和链接器输入的附加依赖库。

* 包含目录为： `D:\freetype-2.10.1\include`
* 库目录为：   `D:\freetype-2.10.1\lib\X64\Debug`
* 附加依赖库： `freetype.lib`

如何配置可以参见我的另外一篇博客：[Visual Studio Opencv 环境配置 - 手动配置](https://github.com/busyboxs/freetype_opencv/blob/master/opencv_visual_studio.md)。

## 测试代码

源码地址：[freetype_opencv](https://github.com/busyboxs/freetype_opencv)

运行结果图

![](images/result.png)

![](images/result4.png)
