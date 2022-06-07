/* define UNICODE */
/* Wyatt Ward, 2020-2022 */
/* compile with:
   gcc -Wall -municode -mwindows -Wl,--subsystem,windows runner.c -o runner.exe
*/

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
  if(argc < 2)
  {
    MessageBoxW(NULL,
                (LPCTSTR)TEXT("Usage: console-free [command line]\n\nNote that the entire command should be a single argument, so surround it with quotes if the program itself has arguments that need passing."),
                (LPCTSTR)TEXT("Usage Information"),
                MB_OK
      );
    return 1;
  }
  size_t command_arg_length = 0;
  int i=1;
  while(i < argc) {
    command_arg_length += _tcslen(argv[i]);
    i++;
  }
  TCHAR *all_args = malloc(sizeof(TCHAR) * ((argc * 3) + command_arg_length + 1));
/* argc*3 is number of separating spaces between args, plus open and
 * close quotes.
 * Note: i think there's a one-char overhead here (first arg has no space
 * before it), so we can probably remove the +1 meant for the null
 * terminator.
 */
  TCHAR *quot=TEXT("\"");
  i=1;
  while(i<argc) {
    if(i==1) {
      all_args = _tcscpy(all_args, quot);
    }
    else {
      all_args = _tcscat(all_args, TEXT(" "));
      all_args = _tcscat(all_args, quot);
    }
    all_args = _tcscat(all_args, argv[i]);
    all_args = _tcscat(all_args, quot);
    i++;
  }


  BOOL creationResult = FALSE;
  if(_tcslen(all_args) != 0) {
    creationResult=CreateProcess(NULL,
                                 all_args,
                                 NULL,
                                 NULL,
                                 FALSE,
                                 CREATE_NO_WINDOW,
                                 NULL,
                                 NULL,
                                 &si,
                                 &pi);
  }
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
  free(all_args);
  return 0;
}
