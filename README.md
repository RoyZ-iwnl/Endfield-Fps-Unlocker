# EndField FPS Unlocker
## Introduction
EndField FPS Unlocker is a tool designed to unlock the frame rate limit for the game Arknights: Endfield. By modifying a specific value in the game’s memory, the user can bypass the frame rate cap. This tool targets the UnityPlayer.dll module of the game, with an offset of 0x1B32E44.

### Warning: This tool has only been tested within the [ArkFieldPS Project](https://github.com/SuikoAkari/ArkFieldPS) and has not been verified on the official servers. Using this tool may pose a risk of account suspension, so proceed with caution.

## Features
- Unlocks the frame rate limit for Arknights: Endfield.
- Allows setting a custom frame rate limit.

## Usage Instructions
### Build

```
g++ -o EndfieldFpsUnlocker.exe unlocker.cpp -lgdi32 -lpsapi -mconsole
```
### Arguments

```
Usage: EndFieldFPSUnlocker.exe -CN/-OS -fps <frame rate>

-CN: Choose the Chinese version game process (Endfield_TBeta.exe).
-OS: Choose the international version game process (Endfield_TBeta_OS.exe).
-fps <frame rate>: Set the target frame rate limit.
-v or --version: Display the program version.

Example

EndFieldFPSUnlocker.exe -OS -fps 144
```

## Notes

This tool has been tested only within the [ArkFieldPS Project](https://github.com/SuikoAkari/ArkFieldPS).

The program will search for the specified process (Endfield_TBeta.exe or Endfield_TBeta_OS.exe) and modify the frame rate limit in memory.

### Warning

Using this program may result in account suspension, as this kind of modification is not authorized by the game’s official servers. Please use it at your own risk.

This program is intended for personal research and educational purposes. Do not use it in online environments.
