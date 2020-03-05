# Vcpkg 配置 freetype 和 OpenCV

## 本机环境

* Windows 10 专业版
* Visual Studio Community 2017  (版本 15.9.7)

## Windows 安装 Vcpkg

Vcpkg 是适用于 Windows，Linux 和 MacOS 的 C++ 库管理器，使用它可以方便地管理 C++ 的依赖库。

Vcpkg 的下载地址和使用说明： [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg)

首先从 github 克隆源码，然后进入到文件夹。windows shell 执行 `.\bootstrap-vcpkg.bat`，git bash 执行 `./bootstrap-vcpkg.sh`。然后会在文件夹中生成可执行文件 `vcpkg.exe`。

```bash
git clone https://github.com/Microsoft/vcpkg.git

cd vcpkg

PS> .\bootstrap-vcpkg.bat
Linux:~/$ ./bootstrap-vcpkg.sh
```

vcpkg 安装库也很简单，首先使用 `vcpkg search lib-name` 搜索某个库是否存在以及对应的版本信息，然后使用 `vcpkg install lib-name` 安装指定的库。

如果不指定安装的架构，vcpkg 默认把开源库编译成 x86 的 Windows 版本的库。可以使用以下代码查询对应的架构：

```bash
$ .\vcpkg.exe help triplet

Available architecture triplets:
  arm-uwp
  arm-windows
  arm64-uwp
  arm64-windows
  x64-linux
  x64-osx
  x64-uwp
  x64-windows
  x64-windows-static
  x86-uwp
  x86-windows
  x86-windows-static
```

我这里编译的版本为 x64，因此使用 x64-window。

执行以下代码进行安装库，有些库可能会安装附加依赖库，需要你添加 `--recurse`。

```bash
> cd d:\vcpkg # 根据你的目录进行修改
> ./vcpkg.exe install opencv:x64-windows
> ./vcpkg.exe install freetype:x64-windows
```

安装完后可以执行命令 `vcpkg list` 查看库

## 配置 Visual Studio 使用 Vcpkg 安装的库

### 集成到全局

Vcpkg 提供了一套机制，可以全自动的适配目录，而开发者不需要关心已安装的库的目录在哪里，也不需要设置。

```bash
$ ./vcpkg.exe integrate install
Applied user-wide integration for this vcpkg root.

All MSBuild C++ projects can now #include any installed libraries.
Linking will be handled automatically.
Installing new libraries will make them instantly available.

CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

当出现 “Applied user-wide integration for this vcpkg root.” 字样的时候，说明已经集成成功。这时候可以在任意的工程中使用安装好的第三方库。CMake 项目则需要添加后面那句指令。

如果不需要集成了，可以移除全局集成，执行下面指令即可

```bash
./vcpkg.exe integrate remove
```

### 集成到工程

"集成到工程”需要利用 Visual Studio 中的 nuget 插件来实现。

#### 生成配置

执行命令

```bash
$ ./vcpkg.exe integrate project
Created nupkg: D:\vcpkg\scripts\buildsystems\vcpkg.D.vcpkg.1.0.0.nupkg

With a project open, go to Tools->NuGet Package Manager->Package Manager Console and paste:
    Install-Package vcpkg.D.vcpkg -Source "D:\vcpkg\scripts\buildsystems"

```

执行命令成功后会在 `“\scripts\buildsystems”` 目录下，生成 nuget 配置文件.

#### NuGet配置

在 Visual Studio 中，点击菜单 “工具->选项”, 选择"NuGet包管理器->程序包源".

添加新的可用程序包源, 选择 vcpkg 目录下的 `“scripts\buildsystems”` 目录，然后点击右侧的 “更新” 按钮。

点击 “确定” 按钮，关闭对话框。

到此，全局性的设置已经完成。

![img](https://cdn.jsdelivr.net/gh/busyboxs/CDN@latest/blog/cpp/baiduAI/vcpkg_01.png)

#### 工程配置

用 Visual Studio 打开一个工程或解决方案。右键点击需要设置的工程弹出菜单，选择“管理 NuGet 程序包”。

![工程配置](https://cdn.jsdelivr.net/gh/busyboxs/CDN@latest/blog/cpp/baiduAI/vcpkg_02.png)

在右上角的 “程序包源” 中选择刚刚设置的 “vcpkg”。这样在 “浏览” 选项卡中就可以看到 “vcpkg.D.vcpkg”。点击最右侧的 “安装”。这样就可以集成到某个工程了。

![img](https://cdn.jsdelivr.net/gh/busyboxs/CDN@latest/blog/cpp/baiduAI/vcpkg_03.png)
