#pragma once
#include "CameraForm.h"
namespace ClothingDetectionApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SelectDirectoryForm
	/// </summary>
	public ref class SelectDirectoryForm : public System::Windows::Forms::Form
	{
	public:
		// Global variable to store selected directory path
		System::String^ SelectedDirectoryPath;

		SelectDirectoryForm(void)
		{
			InitializeComponent();
			SelectedDirectoryPath = "";
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SelectDirectoryForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::Button^ PathName;
	private: System::Windows::Forms::Button^ EnterAppButton;


	private: System::Windows::Forms::Label^ label1;
	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->PathName = (gcnew System::Windows::Forms::Button());
			this->EnterAppButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// PathName
			// 
			this->PathName->Location = System::Drawing::Point(12, 76);
			this->PathName->Name = L"PathName";
			this->PathName->Size = System::Drawing::Size(345, 23);
			this->PathName->TabIndex = 0;
			this->PathName->Text = L"/..";
			this->PathName->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->PathName->UseVisualStyleBackColor = true;
			this->PathName->Click += gcnew System::EventHandler(this, &SelectDirectoryForm::button1_Click);
			// 
			// EnterAppButton
			// 
			this->EnterAppButton->Location = System::Drawing::Point(282, 105);
			this->EnterAppButton->Name = L"EnterAppButton";
			this->EnterAppButton->Size = System::Drawing::Size(75, 23);
			this->EnterAppButton->TabIndex = 1;
			this->EnterAppButton->Text = L"ตกลง";
			this->EnterAppButton->UseVisualStyleBackColor = true;
			this->EnterAppButton->Click += gcnew System::EventHandler(this, &SelectDirectoryForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(112, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(136, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"โปลดเลือกโฟลเดอร์เก็บข้อมูล";
			this->label1->Click += gcnew System::EventHandler(this, &SelectDirectoryForm::label1_Click);
			// 
			// SelectDirectoryForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(372, 150);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->EnterAppButton);
			this->Controls->Add(this->PathName);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MaximizeBox = false;
			this->Name = L"SelectDirectoryForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SelectDirectoryForm";
			this->UseWaitCursor = true;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			System::String^ selectedPath = folderBrowserDialog1->SelectedPath;
			// Save to global variable
			SelectedDirectoryPath = selectedPath;
			PathName->Text = selectedPath;

		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedDirectoryPath == "") {
			MessageBox::Show("please select a folder", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		CameraForm^ cameraForm = gcnew CameraForm();
		// You can pass the selected path to CameraForm if needed
		// cameraForm->DirectoryPath = SelectedDirectoryPath;
		cameraForm->ShowDialog();
		SelectDirectoryForm::Close();
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
