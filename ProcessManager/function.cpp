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
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |          //����������, ����������� ��� �������, � ������ ��������������� ��������(�������), �������������� �������� � ���������� ��� ����������� ������. hprocess-������� ReadProcessMemory,���������� �������� � �������, ������� ��������.
        PROCESS_VM_READ,                                              //���� �� ���� ������������� Windows �� ����������� ������.��������� ��� ������ ������ � �������� � �������������� ReadProcessMemory.
        FALSE, processID);


    Process.dwSize = sizeof(PROCESSENTRY32);

    hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    countProc = 0;
    if (NULL != hProcess)
    {
        HMODULE hMod;                                              //���������� ������ DLL, ������� �������� ������� ��� ����������. ������� LoadLibrary, LoadLibraryEx, LoadPackagedLibrary ��� GetModuleHandle ���������� ���� ����������.
        DWORD cbNeeded;                                           //�������� � ��� ������������� �������������� ������� ����� (4 �����) ��������� ��� ������� ��������������.

                     /*PrintProcessNameAndID �������� ������� EnumProcessModules ��� ��������� ������������ ������*/
        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),   //������������, ����������� �� 64-��������� ���������� 32-��������� ������, 64-��������� ������ ��� ��� ���� �������
            &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessName,  //���������� ��� ���������
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