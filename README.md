# freetype_opencv

----

更新：2019-11-2

* 使用 OpenCV 4.1
* 使用 freetype 2.10.1
* 支持 竖向文字、旋转文字

配置说明： [OpenCV 在图像中显示中文](https://github.com/busyboxs/freetype_opencv/blob/master/opencv_puttext_zh.md)

> 如果你会使用 Vcpkg，那么配置将会非常方便简单。直接安装 opencv 库和 freetype 库就行。

```
# for win32 compile env
./vcpkg.exe install opencv4
./vcpkg.exe install freetype

# for x64 compile env
./vcpkg.exe install opencv4:x64-windows
./vcpkg.exe install freetype:x64-windows
```

使用说明：直接打开 `opencv_puttext_zh` 文件夹下的解决方案，配置好依赖环境运行即可。`freetype_test` 为原来版本的文件夹，现在已经没用啦。

![](images/freetypevs008.png)
