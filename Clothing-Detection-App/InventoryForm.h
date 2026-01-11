#pragma once
#include "DetectFashionForm.h"

namespace ClothingDetectionApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::IO;

	public ref class InventoryForm : public System::Windows::Forms::Form
	{
	public:
		System::String^ DirectoryPath;

		InventoryForm(System::String^ path)
		{
			InitializeComponent();
			this->DirectoryPath = path;
			ApplyModernStyling();
			LoadImages();
		}

	protected:
		~InventoryForm()
		{
			if (components) delete components;
		}

	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Panel^ topPanel;
	private: System::Windows::Forms::Button^ btnRefresh;
	private: System::Windows::Forms::Label^ lblStatus;
	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Panel^ bottomPanel;
	private: System::Windows::Forms::Button^ btnTrash;

	private: System::ComponentModel::Container^ components;
	private: System::Drawing::Point dragStartPoint;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->topPanel = (gcnew System::Windows::Forms::Panel());
			   this->lblTitle = (gcnew System::Windows::Forms::Label());
			   this->lblStatus = (gcnew System::Windows::Forms::Label());
			   this->btnRefresh = (gcnew System::Windows::Forms::Button());
			   this->bottomPanel = (gcnew System::Windows::Forms::Panel());
			   this->btnTrash = (gcnew System::Windows::Forms::Button());
			   this->topPanel->SuspendLayout();
			   this->bottomPanel->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // flowLayoutPanel1
			   // 
			   this->flowLayoutPanel1->AutoScroll = true;
			   this->flowLayoutPanel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(37)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(37)), static_cast<System::Int32>(static_cast<System::Byte>(38)));
			   this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->flowLayoutPanel1->Location = System::Drawing::Point(0, 80);
			   this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			   this->flowLayoutPanel1->Padding = System::Windows::Forms::Padding(20);
			   this->flowLayoutPanel1->Size = System::Drawing::Size(1200, 540);
			   this->flowLayoutPanel1->TabIndex = 0;
			   // 
			   // topPanel
			   // 
			   this->topPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)));
			   this->topPanel->Controls->Add(this->lblTitle);
			   this->topPanel->Controls->Add(this->lblStatus);
			   this->topPanel->Controls->Add(this->btnRefresh);
			   this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			   this->topPanel->Location = System::Drawing::Point(0, 0);
			   this->topPanel->Name = L"topPanel";
			   this->topPanel->Size = System::Drawing::Size(1200, 80);
			   this->topPanel->TabIndex = 1;
			   // 
			   // lblTitle
			   // 
			   this->lblTitle->AutoSize = true;
			   this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
			   this->lblTitle->ForeColor = System::Drawing::Color::White;
			   this->lblTitle->Location = System::Drawing::Point(25, 20);
			   this->lblTitle->Name = L"lblTitle";
			   this->lblTitle->Size = System::Drawing::Size(190, 41);
			   this->lblTitle->TabIndex = 2;
			   this->lblTitle->Text = L"🖼️ Gallery";
			   // 
			   // lblStatus
			   // 
			   this->lblStatus->AutoSize = true;
			   this->lblStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11));
			   this->lblStatus->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->lblStatus->Location = System::Drawing::Point(230, 30);
			   this->lblStatus->Name = L"lblStatus";
			   this->lblStatus->Size = System::Drawing::Size(90, 25);
			   this->lblStatus->TabIndex = 1;
			   this->lblStatus->Text = L"Loading...";
			   // 
			   // btnRefresh
			   // 
			   this->btnRefresh->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->btnRefresh->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(122)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			   this->btnRefresh->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->btnRefresh->FlatAppearance->BorderSize = 0;
			   this->btnRefresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			   this->btnRefresh->ForeColor = System::Drawing::Color::White;
			   this->btnRefresh->Location = System::Drawing::Point(1040, 18);
			   this->btnRefresh->Name = L"btnRefresh";
			   this->btnRefresh->Size = System::Drawing::Size(140, 45);
			   this->btnRefresh->TabIndex = 0;
			   this->btnRefresh->Text = L"🔄 Refresh";
			   this->btnRefresh->UseVisualStyleBackColor = false;
			   this->btnRefresh->Click += gcnew System::EventHandler(this, &InventoryForm::btnRefresh_Click);
			   this->btnRefresh->MouseEnter += gcnew System::EventHandler(this, &InventoryForm::btnRefresh_MouseEnter);
			   this->btnRefresh->MouseLeave += gcnew System::EventHandler(this, &InventoryForm::btnRefresh_MouseLeave);
			   // 
			   // bottomPanel
			   // 
			   this->bottomPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)));
			   this->bottomPanel->Controls->Add(this->btnTrash);
			   this->bottomPanel->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->bottomPanel->Location = System::Drawing::Point(0, 520);
			   this->bottomPanel->Name = L"bottomPanel";
			   this->bottomPanel->Size = System::Drawing::Size(1200, 100);
			   this->bottomPanel->TabIndex = 1;
			   this->bottomPanel->Visible = false;
			   // 
			   // btnTrash
			   // 
			   this->btnTrash->AllowDrop = true;
			   this->btnTrash->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(57)), static_cast<System::Int32>(static_cast<System::Byte>(43)));
			   this->btnTrash->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->btnTrash->FlatAppearance->BorderSize = 0;
			   this->btnTrash->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnTrash->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
			   this->btnTrash->ForeColor = System::Drawing::Color::White;
			   this->btnTrash->Location = System::Drawing::Point(0, 0);
			   this->btnTrash->Margin = System::Windows::Forms::Padding(0);
			   this->btnTrash->Name = L"btnTrash";
			   this->btnTrash->Size = System::Drawing::Size(1200, 100);
			   this->btnTrash->TabIndex = 0;
			   this->btnTrash->Text = L"🗑️ DROP HERE TO DELETE";
			   this->btnTrash->UseVisualStyleBackColor = false;
			   this->btnTrash->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &InventoryForm::btnTrash_DragDrop);
			   this->btnTrash->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &InventoryForm::btnTrash_DragEnter);
			   this->btnTrash->DragLeave += gcnew System::EventHandler(this, &InventoryForm::btnTrash_DragLeave);
			   // 
			   // InventoryForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1200, 620);
			   this->Controls->Add(this->flowLayoutPanel1);
			   this->Controls->Add(this->bottomPanel);
			   this->Controls->Add(this->topPanel);
			   this->MinimumSize = System::Drawing::Size(1000, 600);
			   this->Name = L"InventoryForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			   this->Text = L"Gallery - Clothing Detection";
			   this->topPanel->ResumeLayout(false);
			   this->topPanel->PerformLayout();
			   this->bottomPanel->ResumeLayout(false);
			   this->ResumeLayout(false);

		   }
#pragma endregion

	private:
		void ApplyModernStyling() {
			this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
			MakeButtonRounded(btnRefresh, 10);
		}

		void MakeButtonRounded(Button^ button, int radius) {
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

		void LoadImages() {
			if (System::String::IsNullOrEmpty(this->DirectoryPath) || !Directory::Exists(this->DirectoryPath)) {
				lblStatus->Text = "❌ Path not found";
				lblStatus->ForeColor = Color::FromArgb(231, 76, 60);
				return;
			}
			this->flowLayoutPanel1->Controls->Clear();
			lblStatus->Text = "⏳ Loading...";
			lblStatus->ForeColor = Color::FromArgb(255, 193, 7);
			this->Update();

			int count = 0;
			array<System::String^>^ files = Directory::GetFiles(this->DirectoryPath);
			for each (System::String ^ file in files) {
				System::String^ ext = Path::GetExtension(file)->ToLower();
				if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp") {
					try {
						Panel^ cardPanel = gcnew Panel();
						cardPanel->Size = System::Drawing::Size(220, 250);
						cardPanel->Margin = System::Windows::Forms::Padding(15);
						cardPanel->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
						cardPanel->Tag = file;

						PictureBox^ pb = gcnew PictureBox();
						pb->Size = System::Drawing::Size(220, 180);
						pb->Dock = DockStyle::Top;
						pb->SizeMode = PictureBoxSizeMode::Zoom;
						pb->Cursor = Cursors::Hand;
						pb->Tag = file;
						pb->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);

						FileStream^ fs = gcnew FileStream(file, FileMode::Open, FileAccess::Read);
						Image^ original = Image::FromStream(fs);
						pb->Image = gcnew Bitmap(original, pb->Width, pb->Height);
						delete original;
						fs->Close();
						delete fs;

						pb->DoubleClick += gcnew EventHandler(this, &InventoryForm::OnImageDoubleClick);
						pb->MouseDown += gcnew MouseEventHandler(this, &InventoryForm::OnImageMouseDown);
						pb->MouseMove += gcnew MouseEventHandler(this, &InventoryForm::OnImageMouseMove);
						pb->MouseEnter += gcnew EventHandler(this, &InventoryForm::OnImageMouseEnter);
						pb->MouseLeave += gcnew EventHandler(this, &InventoryForm::OnImageMouseLeave);

						Label^ lbl = gcnew Label();
						lbl->Text = Path::GetFileNameWithoutExtension(file);
						lbl->Dock = DockStyle::Bottom;
						lbl->Height = 60;
						lbl->TextAlign = ContentAlignment::MiddleCenter;
						lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Regular);
						lbl->ForeColor = System::Drawing::Color::FromArgb(200, 200, 200);
						lbl->Padding = System::Windows::Forms::Padding(5);

						Label^ hintLabel = gcnew Label();
						hintLabel->Text = L"🔍 Double-click to process";
						hintLabel->Dock = DockStyle::Bottom;
						hintLabel->Height = 10;
						hintLabel->TextAlign = ContentAlignment::MiddleCenter;
						hintLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 7);
						hintLabel->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);

						cardPanel->Controls->Add(hintLabel);
						cardPanel->Controls->Add(lbl);
						cardPanel->Controls->Add(pb);
						
						this->flowLayoutPanel1->Controls->Add(cardPanel);
						count++;
					}
					catch (System::Exception^ ex) {}
				}
			}
			lblStatus->Text = "✅ " + count + " images loaded";
			lblStatus->ForeColor = Color::FromArgb(46, 204, 113);
		}

		void OnImageDoubleClick(System::Object^ sender, System::EventArgs^ e) {
			PictureBox^ pb = safe_cast<PictureBox^>(sender);
			if (pb->Tag != nullptr) {
				System::String^ filePath = safe_cast<System::String^>(pb->Tag);
				DetectFashionForm^ detectForm = gcnew DetectFashionForm(filePath);
				detectForm->ShowDialog();
			}
		}

		void OnImageMouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				dragStartPoint = e->Location;
			}
		}

		void OnImageMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				int dx = Math::Abs(e->X - dragStartPoint.X);
				int dy = Math::Abs(e->Y - dragStartPoint.Y);

				if (dx > 5 || dy > 5) {
					PictureBox^ pb = safe_cast<PictureBox^>(sender);
					if (pb->Tag != nullptr) {
						this->bottomPanel->Visible = true;
						pb->DoDragDrop(pb->Tag, DragDropEffects::Move);
						this->bottomPanel->Visible = false;
					}
				}
			}
		}

		void OnImageMouseEnter(System::Object^ sender, System::EventArgs^ e) {
			PictureBox^ pb = safe_cast<PictureBox^>(sender);
			Panel^ parent = safe_cast<Panel^>(pb->Parent);
			parent->BackColor = System::Drawing::Color::FromArgb(60, 60, 65);
			pb->BackColor = System::Drawing::Color::FromArgb(40, 40, 45);
		}

		void OnImageMouseLeave(System::Object^ sender, System::EventArgs^ e) {
			PictureBox^ pb = safe_cast<PictureBox^>(sender);
			Panel^ parent = safe_cast<Panel^>(pb->Parent);
			parent->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
			pb->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
		}

		void btnTrash_DragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
			if (e->Data->GetDataPresent(DataFormats::StringFormat)) {
				e->Effect = DragDropEffects::Move;
				btnTrash->BackColor = System::Drawing::Color::FromArgb(231, 76, 60);
				btnTrash->Text = L"🗑️ RELEASE TO DELETE!";
			}
			else {
				e->Effect = DragDropEffects::None;
			}
		}

		void btnTrash_DragLeave(System::Object^ sender, System::EventArgs^ e) {
			btnTrash->BackColor = System::Drawing::Color::FromArgb(192, 57, 43);
			btnTrash->Text = L"🗑️ DROP HERE TO DELETE";
		}

		void btnTrash_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
			System::String^ filePath = safe_cast<System::String^>(e->Data->GetData(DataFormats::StringFormat));

			if (MessageBox::Show("Delete this image permanently?", "🗑️ Confirm Delete", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes) {
				try {
					System::IO::File::Delete(filePath);
					LoadImages();
					MessageBox::Show("✅ Image deleted successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				catch (System::Exception^ ex) {
					MessageBox::Show("❌ Error: " + ex->Message, "Delete Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}

			btnTrash->BackColor = System::Drawing::Color::FromArgb(192, 57, 43);
			btnTrash->Text = L"🗑️ DROP HERE TO DELETE";
		}

		System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) { 
			LoadImages(); 
		}

		void btnRefresh_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
			btnRefresh->BackColor = System::Drawing::Color::FromArgb(0, 140, 230);
		}

		void btnRefresh_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
			btnRefresh->BackColor = System::Drawing::Color::FromArgb(0, 122, 204);
		}
	};
}