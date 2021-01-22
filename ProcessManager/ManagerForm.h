#pragma once
#include <windows.h>
namespace ProcessManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ManagerForm
	/// </summary>
	public ref class ManagerForm : public System::Windows::Forms::Form 
	{
	public:
		ManagerForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ManagerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::ListBox^ listBox2;




	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(366, 38);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(115, 175);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Сканирование";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ManagerForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(161, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L" Число процессов =";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &ManagerForm::textBox1_TextChanged);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(12, 38);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(337, 355);
			this->listBox1->TabIndex = 3;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &ManagerForm::listBox1_SelectedIndexChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(366, 219);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(115, 172);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Завершение процесса";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &ManagerForm::button2_Click);
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Location = System::Drawing::Point(1, 0);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(10, 4);
			this->listBox2->TabIndex = 5;
			this->listBox2->Visible = false;
			this->listBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &ManagerForm::listBox2_SelectedIndexChanged);
			// 
			// ManagerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(493, 403);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->listBox2);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"ManagerForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Process Manager";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
	private:System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e);
private: INT PrintProcessList(HANDLE hStdOut);
private: System::Void listBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
};
}