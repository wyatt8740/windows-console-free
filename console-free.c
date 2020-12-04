/* define UNICODE */
#define _UNICODE
#include <windows.h>
#include <winuser.h> /* MessageBoxW */
#include <stdio.h>
#include <tchar.h>
int _tmain(int argc, TCHAR **argv)
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));
  if(argc != 2)
  {
/*    printf("Usage: %s "[command line]"\n", argv[0]); */
    /* don't even need to check what button user clicks if we just have the
       one. It'll be IDOK. Even if escape is pressed, in this case. */
    MessageBoxW(NULL,
                (LPCTSTR)TEXT("Usage: console-free [command line]\n\nNote that the entire command should be a single argument, so surround it with quotes if the program itself has arguments that need passing."),
                (LPCTSTR)TEXT("Usage Information"),
               MB_OK
      );
    return 1;
  }
  BOOL creationResult=CreateProcess(NULL,
                               argv[1],
                               NULL,
                               NULL,
                               FALSE,
                               CREATE_NO_WINDOW,
                               NULL,
                               NULL,
                               &si,
                               &pi);
  if(!creationResult)
  {
    MessageBox(NULL,
               (LPCTSTR)TEXT("CreateProcess() failed.\n\nTry checking that you typed the program name correctly, and also that you have permissions to run the program."),
               (LPCTSTR)TEXT("Error creating process"),
               MB_OK);
    return 1;
  }
  WaitForSingleObject(pi.hProcess, INFINITE);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  return 0;
}
