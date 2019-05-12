# rt-ad7746

## 1、介绍

AD7746 是一款 I2C 接口的高精度电容测量芯片，而且自带温度传感器

## 2、项目说明
### 2.1 目录结构

> 说明：目录结构

| 名称 | 说明 |
| ---- | ---- |
| docs  | 文档目录 |
| examples | 例子目录|
| src  | 源代码目录 |

### 2.2 许可证

MIT

### 2.3 项目依赖

> 说明：AD7746 需要开启 I2C

- Using I2C device drivers
- Use GPIO to simulate I2C

## 3、如何使用 AD7746

使用 ad7746 package 需要在 RT-Thread 的包管理器中选择它，具体路径如下：

    RT-Thread online packages
      peripheral libraries and drivers --->
          [*] AD7746: a high resolution, Σ-Δ capacitance-todigital converter (CDC).


然后让 RT-Thread 的包管理器自动更新，或者使用 `pkgs --update` 命令更新包到 BSP 中。

## 4、注意事项

无

## 5、感谢

段斌

## 6、联系方式

* 维护：Wu Han
* 主页：http://wuhanstudio.cc
* 邮箱：wuhanstudio@hust.edu.cn
