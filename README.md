# freetype_opencv

----

更新：2020-3-3

* 重构代码
* 添加下划线
* 测试了其他字体（包括日语和 Segoe UI)

----

更新：2019-11-2

* 使用 OpenCV 4.1
* 使用 freetype 2.10.1
* 支持 竖向文字、旋转文字

----

## 配置

配置说明： [OpenCV 在图像中显示中文](https://github.com/busyboxs/freetype_opencv/blob/master/opencv_puttext_zh.md)

> 如果你会使用 Vcpkg，那么配置将会非常方便简单。直接安装 opencv 库和 freetype 库就行。

```bash
# for win32 compile env
./vcpkg.exe install opencv4
./vcpkg.exe install freetype

# for x64 compile env
./vcpkg.exe install opencv4:x64-windows
./vcpkg.exe install freetype:x64-windows
```

## 说明

使用说明：如果使用 Visual Studio，直接打开 `opencv_puttext_zh` 文件夹下的解决方案，配置好依赖环境运行即可。

如果使用其他的环境，复制代码即可，主要代码文件如下：

* `CvxText.cpp`
* `CvxText.h`
* `main.cpp`

字体可以直接从 windows 系统（c:\windows\fonts）里复制过来，然后放到 font 文件夹下。

## 运行效果

![](images/result.png)
