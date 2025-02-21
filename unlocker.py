import pymem
import pymem.process
import time
import sys
import argparse

# 语言配置
LANG = {
    'CN': {
        'process_not_found': "[-] 未找到进程: {}",
        'success': "[+] 成功将 {} 地址的值修改为 {}",
        'error': "[-] 发生错误: {}",
        'usage': "用法: {} -CN/-OS -fps <帧数>",
        'missing_args': "[-] 缺少必要参数",
        'running': "Endfield FPS 解锁工具运行中...",
    },
    'OS': {
        'process_not_found': "[-] Process not found: {}",
        'success': "[+] Successfully changed value at {} to {}",
        'error': "[-] Error occurred: {}",
        'usage': "Usage: {} -CN/-OS -fps <frame rate>",
        'missing_args': "[-] Missing required arguments",
        'running': "Endfield FPS Unlocker is running...",
    }
}

def unlock_fps(process_name, desired_value, lang):
    dll_name = "UnityPlayer.dll"
    offset = 0x1B32E44

    try:
        pm = pymem.Pymem(process_name)
        
        unity_dll = pymem.process.module_from_name(
            pm.process_handle,
            dll_name
        )
        if not unity_dll:
            raise Exception(f"{dll_name} not found")

        base_address = unity_dll.lpBaseOfDll
        target_address = base_address + offset

        pm.write_int(target_address, desired_value)
        
        print(LANG[lang]['success'].format(hex(target_address), desired_value))
        
    except pymem.exception.ProcessNotFound:
        print(LANG[lang]['process_not_found'].format(process_name))
    except Exception as e:
        print(LANG[lang]['error'].format(str(e)))
    finally:
        if 'pm' in locals():
            pm.close_process()

def main():
    parser = argparse.ArgumentParser(description="Endfield FPS Unlocker By:RoyZ")
    parser.add_argument('-CN', action='store_true', help="使用国服客户端")
    parser.add_argument('-OS', action='store_true', help="Use overseas client")
    parser.add_argument('-fps', type=int, required=True, help="目标帧率")
    
    if len(sys.argv) < 2:
        parser.print_help()
        print(LANG['CN']['missing_args'])
        sys.exit(1)

    args = parser.parse_args()

    if args.CN:
        process_name = "Endfield_TBeta.exe"
        lang = 'CN'
    elif args.OS:
        process_name = "Endfield_TBeta_OS.exe"
        lang = 'OS'
    else:
        print(LANG['CN']['usage'].format(sys.argv[0]))
        sys.exit(1)

    print(LANG[lang]['running'])
    while True:
        unlock_fps(process_name, args.fps, lang)
        time.sleep(2)

if __name__ == "__main__":
    main()