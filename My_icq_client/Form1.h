#pragma once

#include "TClient.h"

namespace My_icq_client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public: bool ifClientSocketOpened;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::RichTextBox^  richTextBox2;
	private: System::Windows::Forms::Button^  button2;
	public: 
	public: TClient ^client;
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			ifClientSocketOpened = false;
			bgw_busy = false;
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (ifClientSocketOpened) client->Logout();

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  b_Login;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->b_Login = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// b_Login
			// 
			this->b_Login->Location = System::Drawing::Point(12, 65);
			this->b_Login->Name = L"b_Login";
			this->b_Login->Size = System::Drawing::Size(122, 81);
			this->b_Login->TabIndex = 0;
			this->b_Login->Text = L"Login";
			this->b_Login->UseVisualStyleBackColor = true;
			this->b_Login->Click += gcnew System::EventHandler(this, &Form1::b_Login_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(26, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(27, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"id = ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"pass = ";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(59, 6);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(75, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"314";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(59, 39);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(75, 20);
			this->textBox2->TabIndex = 4;
			this->textBox2->Text = L"12345";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::backgroundWorker1_RunWorkerCompleted);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(140, 25);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(114, 147);
			this->listBox1->TabIndex = 5;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(260, 6);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(146, 140);
			this->richTextBox1->TabIndex = 6;
			this->richTextBox1->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(137, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(40, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Online:";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(260, 152);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(146, 23);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Send HELLO";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// richTextBox2
			// 
			this->richTextBox2->Location = System::Drawing::Point(12, 178);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->Size = System::Drawing::Size(242, 27);
			this->richTextBox2->TabIndex = 9;
			this->richTextBox2->Text = L"";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(260, 181);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(146, 23);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Send msg";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(418, 208);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->b_Login);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void b_Login_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 client = gcnew TClient(1234, "127.0.0.1");
				 ifClientSocketOpened = true;
				 if (client->Login(Convert::ToInt32(textBox1->Text), "12345") == 1)
				 {
					 //timer1->Interval = 1000;
					 timer1->Enabled = true;
				 }
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if (!bgw_busy)
				 {
					 bgw_busy = true;
					 backgroundWorker1->RunWorkerAsync();
				 }
				 if (client->isOnline) 
					 b_Login->Visible = false;
				 if (client->isFriendChanged)
				 {
					 listBox1->Items->Clear();
					 CFriend *tmp = client->friends->head;
					 while (tmp != NULL)
					 {
						 //richTextBox1->Text += Convert::ToInt32(tmp->id) + "\n";
						 listBox1->Items->Add(Convert::ToInt32(tmp->id));
						 tmp = tmp->next;
					 }
					 client->isFriendChanged = false;
				 }
				 if (client->isChatChanged)
				 {
					 richTextBox1->Text += client->chat;
					 client->chat = "";
					 client->isChatChanged = false;
				 }
			 }

private: bool bgw_busy;
private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
		 {
			 client->WatchForData();
		 }
private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
		 {
			 bgw_busy = false;
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 try
			 {
				 int id_recv = System::Convert::ToInt32(listBox1->SelectedItem->ToString());
				 client->Send("Message", client->id, id_recv, "HELLO", ':');
			 }
			 catch (Exception^ e) {}
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 try
			 {
				 int id_recv = System::Convert::ToInt32(listBox1->SelectedItem->ToString());
				 char* msg = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(richTextBox2->Text);
				 richTextBox1->Text += richTextBox2->Text + "\n";
				 richTextBox2->Text = "";
				 client->Send("Message", client->id, id_recv, msg, ':');
			 }
			 catch (Exception^ e) {}
		 }
};
}

