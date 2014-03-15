#pragma once
#include "ThreadedServer.h"

namespace My_icq_server {


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
	public: ThreadedServer *server;
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			server = new ThreadedServer(1234);
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  b_Start_Stop;
	protected: 
	private: System::Windows::Forms::ListBox^  lB_OnlineUsers;

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->b_Start_Stop = (gcnew System::Windows::Forms::Button());
			this->lB_OnlineUsers = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// b_Start_Stop
			// 
			this->b_Start_Stop->Location = System::Drawing::Point(12, 12);
			this->b_Start_Stop->Name = L"b_Start_Stop";
			this->b_Start_Stop->Size = System::Drawing::Size(75, 23);
			this->b_Start_Stop->TabIndex = 0;
			this->b_Start_Stop->Text = L"Start";
			this->b_Start_Stop->UseVisualStyleBackColor = true;
			this->b_Start_Stop->Click += gcnew System::EventHandler(this, &Form1::b_Start_Stop_Click);
			// 
			// lB_OnlineUsers
			// 
			this->lB_OnlineUsers->FormattingEnabled = true;
			this->lB_OnlineUsers->Location = System::Drawing::Point(12, 41);
			this->lB_OnlineUsers->Name = L"lB_OnlineUsers";
			this->lB_OnlineUsers->Size = System::Drawing::Size(260, 199);
			this->lB_OnlineUsers->TabIndex = 1;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 251);
			this->Controls->Add(this->lB_OnlineUsers);
			this->Controls->Add(this->b_Start_Stop);
			this->Name = L"Form1";
			this->Text = L"Server";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void b_Start_Stop_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 server->Start();
			 }
	};
}

