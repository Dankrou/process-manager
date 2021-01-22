#include "ManagerForm.h"                 // ���������� ������������ ����
#include <string>                        // ���������� ����������
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <tchar.h>
#include <psapi.h>
#include <fstream>
#include <msclr\marshal_cppstd.h>
#include <regex> 

using namespace System;                     //���������� ������������ ����
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(cli::array<System::String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    ProcessManager::ManagerForm form;
    Application::Run(% form);

    //������ ��������� ��� ����� ������� ����� ������������ ���������

}



System::Void 
ProcessManager::ManagerForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{

        if (listBox1->Text) {
            listBox1->Items->Clear();    //�������� ���������� �� ��� ���������� ������, �������� ������ ������������. ��� ��������� ������� "����������" ������ � ��������� ����������� ����.
            listBox2->Items->Clear();
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            PrintProcessList(hStdOut); //�������������� ��������� ���������
            std::string lineString = "check";        //�������� ����� ������ � ���������� ������
            std::ifstream in("ProcessList.txt");
            if (in.is_open())
            {
                while (getline(in, lineString))
                {
                    String^ line = msclr::interop::marshal_as<String^>(lineString); // �������� ��������� ���������� char � ������� char � ��������� �������� ����� ����������( ���������� ��������������). ��� ������� � ��������� ������ ����� ���������� ������� � �����, ��� �� �������� �� ��������� � ��� ����� ���������������.

                    listBox1->Items->Add(line); //���������� ������ � �������
                }
            }
            in.close();
            std::ifstream in2("ProcessListBack.txt");
            if (in2.is_open())
            {
                while (getline(in2, lineString))
                {
                    String^ line = msclr::interop::marshal_as<String^>(lineString); // �������� ��������� ���������� char � ������� char � ��������� �������� ����� ����������( ���������� ��������������). ��� ������� � ��������� ������ ����� ���������� ������� � �����, ��� �� �������� �� ��������� � ��� ����� ���������������.

                    listBox2->Items->Add(line); //���������� ������ � �������
                }
            }
            in2.close();

        }
        else {
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            PrintProcessList(hStdOut);
            std::string lineString = "check";
            std::ifstream in("ProcessList.txt");
            if (in.is_open())
            {
                while (getline(in, lineString))
                {
                    String^ line = msclr::interop::marshal_as<String^>(lineString); //��������������� ���������� char

                    listBox1->Items->Add(line);
                }
            }
            in.close();
            std::ifstream in2("ProcessListBack.txt");
            if (in2.is_open())
            {
                while (getline(in2, lineString))
                {
                    String^ line = msclr::interop::marshal_as<String^>(lineString); //��������������� ���������� char

                    listBox2->Items->Add(line);
                }
            }
            in2.close();
        }
    }


System::Void ProcessManager::ManagerForm::textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    
    return System::Void();
}

System::Void ProcessManager::ManagerForm::listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
    listBox2->SelectedIndex = listBox1->SelectedIndex; //������������� �������� ��������� � �������

}
    
System::Void ProcessManager::ManagerForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
   PROCESSENTRY32 entry;
   entry.dwSize = sizeof(PROCESSENTRY32);
   String^ curItem = listBox2->SelectedItem->ToString();
   std::wstring line = msclr::interop::marshal_as<std::wstring>(curItem);//�������������� ���������� �������
   String^ curItem2 = msclr::interop::marshal_as<String^>(line); //�������������� ���������� �������
       const wchar_t* cstr = line.c_str();
   HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL); //������� ���� ��������� ���������

   if (Process32First(snapshot, &entry) == TRUE)
   {
       while (Process32Next(snapshot, &entry) == TRUE)
       {
           if (_tcsicmp(entry.szExeFile, cstr) == 0)
           {
               HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID); //��������� ���� �� ������������� � �������
               TerminateProcess(hProcess, 0); //���������� ������ ��������


               CloseHandle(hProcess); //���������� ��������
               
           }
       }
   }
   
   CloseHandle(snapshot);
   Sleep(200);
   button1->PerformClick();
    return;
}

System::Void ProcessManager::ManagerForm::dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
    return System::Void();
}

System::Void ProcessManager::ManagerForm::richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    return System::Void();
}

INT ProcessManager::ManagerForm::PrintProcessList(HANDLE hStdOut)
{

        PROCESSENTRY32 pe; // �������� �� �������� ���������, ����� ������ ������
        HANDLE hSnapshot = CreateToolhelp32Snapshot(              //������� ��������� ���������
            TH32CS_SNAPPROCESS, 0);
        int countProc = 0;                              //������������� �������� � 0
        std::ofstream out; //���� ������ ��� ������ � �������
        std::ofstream out2; //���� ������ ��� ������ � �������
        pe.dwSize = sizeof(PROCESSENTRY32);
        out.open("ProcessList.txt");                       //�������� �������� ������ ���������
        out2.open("ProcessListBack.txt");                  //�������� ����������, �� ��������� ������ ���������
        if (Process32First(hSnapshot, &pe))
        {
            do
            {
                if (!pe.th32ProcessID) continue;    // ������� [System process], ������� �� ��������
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                    PROCESS_VM_READ,      //��������� ���� �� ������ ������
                    FALSE, pe.th32ProcessID);
                CloseHandle(hProcess);
                countProc++; //���� ����� ���������
                std::wstring ws(pe.szExeFile); //������������ �� �������� �������� ������ ���������� � ���������� � pid
                std::string str(ws.begin(), ws.end());
                out << countProc << "  ----  *" << str << "*  Pid = " << pe.th32ProcessID << "" << std::endl; //���������� � ������� ��������� �������� ��������, ��� pid � ��������� �������� ����� ������ � ���� ����������
                out2 << str << std::endl; //�������� ����� � �������� ������� ���������
                textBox1->Text = " ����� ��������� = "+Convert::ToString(countProc);              //����� ���������� ��������� � ��������� ���������
            }
            while (Process32Next(hSnapshot, &pe));              //�������� ���������� �� ���� ���� ������� Process32First ��� �����
        }
        CloseHandle(hSnapshot);
        out2.close();
        out.close();
   
    return INT();
}

System::Void ProcessManager::ManagerForm::listBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
    listBox2->SelectedIndex = listBox1->SelectedIndex; //������������� �������� ��������� � �������
    return System::Void();
}
