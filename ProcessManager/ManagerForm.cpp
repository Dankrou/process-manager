#include "ManagerForm.h"                 // подключаем заголовочный файл
#include <string>                        // подключаем библиотеки
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

using namespace System;                     //подключаем пространство имен
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(cli::array<System::String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    ProcessManager::ManagerForm form;
    Application::Run(% form);

    //задаем аттрибуты для формы проекта через общеязыковую структуру

}



System::Void 
ProcessManager::ManagerForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{

        if (listBox1->Text) {
            listBox1->Items->Clear();    //очищение листбоксов от уже полученных данных, нажатием кнопки сканирования. Это выполняет функцию "обновления" данных и позволяет реализовать цикл.
            listBox2->Items->Clear();
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            PrintProcessList(hStdOut); //распечатывание системных процессов
            std::string lineString = "check";        //проверка места записи о заполнении данных
            std::ifstream in("ProcessList.txt");
            if (in.is_open())
            {
                while (getline(in, lineString))
                {
                    String^ line = msclr::interop::marshal_as<String^>(lineString); // убирание конфликта системного char с обычным char и системным стрингом путем маршалинга( происходит преобразование). Это связано с передачей текста между записанным текстом в форму, где он меняется на системный и ему нужен преобразователь.

                    listBox1->Items->Add(line); //добавление строки с данными
                }
            }
            in.close();
            std::ifstream in2("ProcessListBack.txt");
            if (in2.is_open())
            {
                while (getline(in2, lineString))
                {
                    String^ line = msclr::interop::marshal_as<String^>(lineString); // убирание конфликта системного char с обычным char и системным стрингом путем маршалинга( происходит преобразование). Это связано с передачей текста между записанным текстом в форму, где он меняется на системный и ему нужен преобразователь.

                    listBox2->Items->Add(line); //добавление строки с данными
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
                    String^ line = msclr::interop::marshal_as<String^>(lineString); //преобразователь системного char

                    listBox1->Items->Add(line);
                }
            }
            in.close();
            std::ifstream in2("ProcessListBack.txt");
            if (in2.is_open())
            {
                while (getline(in2, lineString))
                {
                    String^ line = msclr::interop::marshal_as<String^>(lineString); //преобразователь системного char

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
    listBox2->SelectedIndex = listBox1->SelectedIndex; //синхронизация видимого листбокса с теневым

}
    
System::Void ProcessManager::ManagerForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
   PROCESSENTRY32 entry;
   entry.dwSize = sizeof(PROCESSENTRY32);
   String^ curItem = listBox2->SelectedItem->ToString();
   std::wstring line = msclr::interop::marshal_as<std::wstring>(curItem);//преобразование системного стринга
   String^ curItem2 = msclr::interop::marshal_as<String^>(line); //преобразование системного стринга
       const wchar_t* cstr = line.c_str();
   HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL); //снапшот всех системных процессов

   if (Process32First(snapshot, &entry) == TRUE)
   {
       while (Process32Next(snapshot, &entry) == TRUE)
       {
           if (_tcsicmp(entry.szExeFile, cstr) == 0)
           {
               HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID); //получение прав на вмешательство в процесс
               TerminateProcess(hProcess, 0); //заврешение работы процесса


               CloseHandle(hProcess); //отупскание процесса
               
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

        PROCESSENTRY32 pe; // отвечает за описание процессов, когда сделан снимок
        HANDLE hSnapshot = CreateToolhelp32Snapshot(              //снапшот системных процессов
            TH32CS_SNAPPROCESS, 0);
        int countProc = 0;                              //приравнивание счетчика к 0
        std::ofstream out; //ввод класса для работы с файлами
        std::ofstream out2; //ввод класса для работы с файлами
        pe.dwSize = sizeof(PROCESSENTRY32);
        out.open("ProcessList.txt");                       //открытие видимого списка процессов
        out2.open("ProcessListBack.txt");                  //открытие невидимого, но основного списка процессов
        if (Process32First(hSnapshot, &pe))
        {
            do
            {
                if (!pe.th32ProcessID) continue;    // Пропуск [System process], которые не прочлись
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                    PROCESS_VM_READ,      //получение прав на чтение памяти
                    FALSE, pe.th32ProcessID);
                CloseHandle(hProcess);
                countProc++; //цикл счета процессов
                std::wstring ws(pe.szExeFile); //выдергивание из описание процесса нужную информацию и соединение с pid
                std::string str(ws.begin(), ws.end());
                out << countProc << "  ----  *" << str << "*  Pid = " << pe.th32ProcessID << "" << std::endl; //соединение в видимом листбоксе название процесса, его pid и текстовых символов путем записи в файл информации
                out2 << str << std::endl; //закрытие файла с основным списком процессов
                textBox1->Text = " Число процессов = "+Convert::ToString(countProc);              //вывод количества процессов в отдельный текстбокс
            }
            while (Process32Next(hSnapshot, &pe));              //перехват управления на себя хука системы Process32First для цикла
        }
        CloseHandle(hSnapshot);
        out2.close();
        out.close();
   
    return INT();
}

System::Void ProcessManager::ManagerForm::listBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
    listBox2->SelectedIndex = listBox1->SelectedIndex; //синхронизация теневого листбокса с видимым
    return System::Void();
}
