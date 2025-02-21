# EndField FPS Unlocker

## 简介

EndField FPS Unlocker 是一个用于解锁《明日方舟：终末地》游戏帧数上限的工具。针对游戏的 `UnityPlayer.dll` 模块进行修改，偏移量为 `0x1B32E44`。

### **警告**：该程序仅在 [ArkFieldPS 项目](https://github.com/SuikoAkari/ArkFieldPS) 下经过测试，未在实际的官方服务器环境中进行过验证。使用此工具可能会面临封号的风险，请谨慎使用。

## 功能

- 解锁《明日方舟：终末地》游戏帧数上限。
- 支持自定义设置帧率上限。

## 使用说明

### 构建

```
g++ -o EndfieldFpsUnlocker.exe unlocker.cpp -lgdi32 -lpsapi -mconsole
```

### 参数说明

```bash
Usage: EndFieldFPSUnlocker.exe -CN/-OS -fps <frame rate>
-CN：选择中文版游戏进程（Endfield_TBeta.exe）。
-OS：选择国际版游戏进程（Endfield_TBeta_OS.exe）。
-fps <frame rate>：设置目标上限帧率。
-v 或 --version：显示程序版本。

示例

EndFieldFPSUnlocker.exe -CN -fps 144
```

### 注意事项
该工具仅在 ArkFieldPS 项目中经过测试。
程序会在运行时寻找指定进程（Endfield_TBeta.exe 或 Endfield_TBeta_OS.exe），并修改内存中的帧率限制值。

### 警告
使用此程序可能会对游戏账号造成风险，官方未授权此类修改行为。请用户自行承担风险。