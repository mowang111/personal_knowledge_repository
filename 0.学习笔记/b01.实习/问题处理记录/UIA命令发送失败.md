# UIA命令发送失败

### 原因

一般是provider崩溃

### 排查思路

1. 需要确认是否是provider崩溃

   在报错的指令前后中加入python代码验证provider是否还存在

   ```python
   import psutil
   
   def check_if_process_exists(process_name):
       for proc in psutil.process_iter(['name']):
           try:
               if process_name.lower() == proc.info['name'].lower():
                   return True
           except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
               pass
       return False
   
   # 使用方式：
   if check_if_process_exists('ShadowBot.UIAutomation.Provider.exe'):
       print('ShadowBot.UIAutomation.Provider.exe process is running.')
   else:
       print('ShadowBot.UIAutomation.Provider.exe process is not running.')
   ```

   

2. 确认是provider崩溃之后，使用类似procdump的工具抓dump，便于崩溃分析

   https://learn.microsoft.com/en-us/sysinternals/downloads/procdump

   ```bash
   procdump -e -ma -w "ShadowBot.UIAutomation.Provider.exe" .\
   ```

   另一种抓dump的方式

   ```bat
   @echo off
   echo 设置Dump...
   reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps"
   reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps" /v DumpFolder /t REG_EXPAND_SZ /d "C:\Dumps" /f
   reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps" /v DumpType /t REG_DWORD /d 2 /f
   reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps" /v DumpCount /t REG_DWORD /d 10 /f
   echo Dump已经设置
   pause
   @echo on
   ```

   

3. 抓到dump后，可以使用visual studio或者win32dbg分析

