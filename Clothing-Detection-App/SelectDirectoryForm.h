#pragma once
#include "CameraForm.h"
namespace ClothingDetectionApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

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
			
			// Apply modern styling
			ApplyModernStyling();
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
	private: System::Windows::Forms::Button^ btnBrowse;
	private: System::Windows::Forms::Button^ btnConfirm;
	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::TextBox^ txtFolderName;
	private: System::Windows::Forms::Label^ lblFolderName;
	private: System::Windows::Forms::Label^ lblSelectedPath;
	private: System::Windows::Forms::Panel^ mainPanel;
	private: System::Windows::Forms::Panel^ headerPanel;
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
			this->btnBrowse = (gcnew System::Windows::Forms::Button());
			this->btnConfirm = (gcnew System::Windows::Forms::Button());
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->txtFolderName = (gcnew System::Windows::Forms::TextBox());
			this->lblFolderName = (gcnew System::Windows::Forms::Label());
			this->lblSelectedPath = (gcnew System::Windows::Forms::Label());
			this->mainPanel = (gcnew System::Windows::Forms::Panel());
			this->headerPanel = (gcnew System::Windows::Forms::Panel());
			this->mainPanel->SuspendLayout();
			this->headerPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnBrowse
			// 
			this->btnBrowse->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->btnBrowse->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnBrowse->FlatAppearance->BorderSize = 0;
			this->btnBrowse->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnBrowse->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->btnBrowse->ForeColor = System::Drawing::Color::White;
			this->btnBrowse->Location = System::Drawing::Point(40, 140);
			this->btnBrowse->Name = L"btnBrowse";
			this->btnBrowse->Size = System::Drawing::Size(420, 45);
			this->btnBrowse->TabIndex = 0;
			this->btnBrowse->Text = L"\?\? Browse Folder";
			this->btnBrowse->UseVisualStyleBackColor = false;
			this->btnBrowse->Click += gcnew System::EventHandler(this, &SelectDirectoryForm::btnBrowse_Click);
			this->btnBrowse->MouseEnter += gcnew System::EventHandler(this, &SelectDirectoryForm::btnBrowse_MouseEnter);
			this->btnBrowse->MouseLeave += gcnew System::EventHandler(this, &SelectDirectoryForm::btnBrowse_MouseLeave);
			// 
			// btnConfirm
			// 
			this->btnConfirm->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->btnConfirm->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnConfirm->FlatAppearance->BorderSize = 0;
			this->btnConfirm->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnConfirm->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			this->btnConfirm->ForeColor = System::Drawing::Color::White;
			this->btnConfirm->Location = System::Drawing::Point(160, 300);
			this->btnConfirm->Name = L"btnConfirm";
			this->btnConfirm->Size = System::Drawing::Size(180, 50);
			this->btnConfirm->TabIndex = 1;
			this->btnConfirm->Text = L"\? Start Camera";
			this->btnConfirm->UseVisualStyleBackColor = false;
			this->btnConfirm->Click += gcnew System::EventHandler(this, &SelectDirectoryForm::btnConfirm_Click);
			this->btnConfirm->MouseEnter += gcnew System::EventHandler(this, &SelectDirectoryForm::btnConfirm_MouseEnter);
			this->btnConfirm->MouseLeave += gcnew System::EventHandler(this, &SelectDirectoryForm::btnConfirm_MouseLeave);
			// 
			// lblTitle
			// 
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = System::Drawing::Color::White;
			this->lblTitle->Location = System::Drawing::Point(90, 20);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(309, 37);
			this->lblTitle->TabIndex = 2;
			this->lblTitle->Text = L"\?\? Setup Photo Session";
			this->lblTitle->Click += gcnew System::EventHandler(this, &SelectDirectoryForm::lblTitle_Click);
			// 
			// txtFolderName
			// 
			this->txtFolderName->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(65)));
			this->txtFolderName->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtFolderName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
			this->txtFolderName->ForeColor = System::Drawing::Color::White;
			this->txtFolderName->Location = System::Drawing::Point(40, 235);
			this->txtFolderName->Name = L"txtFolderName";
			this->txtFolderName->Size = System::Drawing::Size(420, 27);
			this->txtFolderName->TabIndex = 3;
			this->txtFolderName->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// lblFolderName
			// 
			this->lblFolderName->AutoSize = true;
			this->lblFolderName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->lblFolderName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->lblFolderName->Location = System::Drawing::Point(36, 200);
			this->lblFolderName->Name = L"lblFolderName";
			this->lblFolderName->Size = System::Drawing::Size(225, 23);
			this->lblFolderName->TabIndex = 4;
			this->lblFolderName->Text = L"\?\? Enter New Folder Name:";
			// 
			// lblSelectedPath
			// 
			this->lblSelectedPath->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->lblSelectedPath->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->lblSelectedPath->Location = System::Drawing::Point(40, 95);
			this->lblSelectedPath->Name = L"lblSelectedPath";
			this->lblSelectedPath->Size = System::Drawing::Size(420, 35);
			this->lblSelectedPath->TabIndex = 5;
			this->lblSelectedPath->Text = L"No folder selected";
			this->lblSelectedPath->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// mainPanel
			// 
			this->mainPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->mainPanel->Controls->Add(this->lblSelectedPath);
			this->mainPanel->Controls->Add(this->lblFolderName);
			this->mainPanel->Controls->Add(this->txtFolderName);
			this->mainPanel->Controls->Add(this->btnConfirm);
			this->mainPanel->Controls->Add(this->btnBrowse);
			this->mainPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->mainPanel->Location = System::Drawing::Point(0, 80);
			this->mainPanel->Name = L"mainPanel";
			this->mainPanel->Padding = System::Windows::Forms::Padding(20);
			this->mainPanel->Size = System::Drawing::Size(500, 380);
			this->mainPanel->TabIndex = 6;
			// 
			// headerPanel
			// 
			this->headerPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->headerPanel->Controls->Add(this->lblTitle);
			this->headerPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->headerPanel->Location = System::Drawing::Point(0, 0);
			this->headerPanel->Name = L"headerPanel";
			this->headerPanel->Size = System::Drawing::Size(500, 80);
			this->headerPanel->TabIndex = 7;
			// 
			// SelectDirectoryForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->ClientSize = System::Drawing::Size(500, 460);
			this->Controls->Add(this->mainPanel);
			this->Controls->Add(this->headerPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"SelectDirectoryForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Setup - Clothing Detection";
			this->mainPanel->ResumeLayout(false);
			this->mainPanel->PerformLayout();
			this->headerPanel->ResumeLayout(false);
			this->headerPanel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: void ApplyModernStyling() {
		// Apply rounded corners to buttons and textbox
		MakeButtonRounded(btnBrowse, 10);
		MakeButtonRounded(btnConfirm, 15);
		MakeTextBoxRounded(txtFolderName, 8);
	}

	private: void MakeButtonRounded(Button^ button, int radius) {
		GraphicsPath^ path = gcnew GraphicsPath();
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, button->Width, button->Height);
		
		int diameter = radius * 2;
		System::Drawing::Size size = System::Drawing::Size(diameter, diameter);
		System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, size);
		
		path->AddArc(arc, 180, 90);
		arc.X = rect.Right - diameter;
		path->AddArc(arc, 270, 90);
		arc.Y = rect.Bottom - diameter;
		path->AddArc(arc, 0, 90);
		arc.X = rect.Left;
		path->AddArc(arc, 90, 90);
		
		path->CloseFigure();
		button->Region = gcnew System::Drawing::Region(path);
	}

	private: void MakeTextBoxRounded(TextBox^ textbox, int radius) {
		GraphicsPath^ path = gcnew GraphicsPath();
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, textbox->Width + 20, textbox->Height + 16);
		
		int diameter = radius * 2;
		System::Drawing::Size size = System::Drawing::Size(diameter, diameter);
		System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, size);
		
		path->AddArc(arc, 180, 90);
		arc.X = rect.Right - diameter;
		path->AddArc(arc, 270, 90);
		arc.Y = rect.Bottom - diameter;
		path->AddArc(arc, 0, 90);
		arc.X = rect.Left;
		path->AddArc(arc, 90, 90);
		
		path->CloseFigure();
		
		// Create a panel wrapper for rounded effect
		Panel^ wrapper = gcnew Panel();
		wrapper->Size = System::Drawing::Size(textbox->Width + 20, textbox->Height + 16);
		wrapper->Location = System::Drawing::Point(textbox->Location.X - 10, textbox->Location.Y - 8);
		wrapper->BackColor = Color::FromArgb(60, 60, 65);
		wrapper->Region = gcnew System::Drawing::Region(path);
		
		textbox->Parent->Controls->Add(wrapper);
		wrapper->BringToFront();
		textbox->BringToFront();
	}

	private: System::Void btnBrowse_Click(System::Object^ sender, System::EventArgs^ e) {
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			System::String^ selectedPath = folderBrowserDialog1->SelectedPath;
			SelectedDirectoryPath = selectedPath;
			lblSelectedPath->Text = "?? " + selectedPath;
			lblSelectedPath->ForeColor = Color::FromArgb(100, 200, 100);
		}
	}

	private: System::Void btnConfirm_Click(System::Object^ sender, System::EventArgs^ e) {
		if (SelectedDirectoryPath == "") {
			MessageBox::Show("Please select a folder first!", "?? Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		
		if (System::String::IsNullOrWhiteSpace(txtFolderName->Text)) {
			MessageBox::Show("Please enter a folder name!", "?? Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		
		try {
			System::String^ newFolderPath = System::IO::Path::Combine(SelectedDirectoryPath, txtFolderName->Text);
			
			// Create directory if it doesn't exist
			if (!System::IO::Directory::Exists(newFolderPath)) {
				System::IO::Directory::CreateDirectory(newFolderPath);
			}
			
			CameraForm^ cameraForm = gcnew CameraForm();
			cameraForm->DirectoryPath = newFolderPath;
			this->Hide();
			cameraForm->ShowDialog();
			this->Close();
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Failed to create directory!\n" + ex->Message, "? Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	// Hover effects
	private: System::Void btnBrowse_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btnBrowse->BackColor = Color::FromArgb(90, 90, 95);
	}

	private: System::Void btnBrowse_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btnBrowse->BackColor = Color::FromArgb(70, 70, 75);
	}

	private: System::Void btnConfirm_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btnConfirm->BackColor = Color::FromArgb(0, 140, 230);
	}

	private: System::Void btnConfirm_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btnConfirm->BackColor = Color::FromArgb(0, 122, 204);
	}
private: System::Void lblTitle_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
