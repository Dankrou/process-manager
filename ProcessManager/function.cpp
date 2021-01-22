#include "ManagerForm.h"
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <tchar.h>
#include <psapi.h>
#include <fstream>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
std::string extern lineString = "shit";
void PRO(DWORD processID)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    std::ofstream out;
    out.open("C:\\Users\\271da\\Documents\\Visual Studio Projects\\ProcessManager\\hui.txt");
    int countProc;
    PROCESSENTRY32 Process;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |          //дескриптор, выполняющий хук системы, а именно неопределенного процесса(объекта), инициализирует открытие и подготовку для вытягивания данных. hprocess-функция ReadProcessMemory,Дескриптор процесса с памятью, которая читается.
        PROCESS_VM_READ,                                              //одно из прав безопастности Windows на программном уровне.Требуется для чтения памяти в процессе с использованием ReadProcessMemory.
        FALSE, processID);


    Process.dwSize = sizeof(PROCESSENTRY32);

    hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    countProc = 0;
    if (NULL != hProcess)
    {
        HMODULE hMod;                                              //Дескриптор модуля DLL, который содержит функцию или переменную. Функция LoadLibrary, LoadLibraryEx, LoadPackagedLibrary или GetModuleHandle возвращает этот дескриптор.
        DWORD cbNeeded;                                           //Выделяет и при необходимости инициализирует двойное слово (4 байта) хранилища для каждого инициализатора.

                     /*PrintProcessNameAndID вызывает функцию EnumProcessModules для получения дескрипторов модуля*/
        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),   //контролирует, перечисляет ли 64-разрядное приложение 32-разрядные модули, 64-разрядные модули или оба типа модулей
            &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessName,  //возвращает имя программы
                sizeof(szProcessName) / sizeof(TCHAR));
        }
    }

    Process.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hProcess, &Process))
    {
        if (out.is_open())
        {

            do
            {
                out << szProcessName << "  " << countProc << "  " << ("%s  (PID: %u)") << "  " << processID << std::endl;
                countProc++;
            } while (Process32Next(hProcess, &Process));
        }
        CloseHandle(hProcess);
        out.close();

    }
    std::string lineString = "shit";
    std::ifstream in("C:\\Users\\271da\\Documents\\Visual Studio Projects\\ProcessManager\\hui.txt");
    if (in.is_open())
    {
        while (getline(in, lineString))
        {
          String^ line = msclr::interop::marshal_as<String^>(lineString);
        }
    }
    in.close();

}