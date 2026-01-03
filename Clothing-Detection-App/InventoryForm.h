#pragma once
#include "DetectFashionForm.h"

namespace ClothingDetectionApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class InventoryForm : public System::Windows::Forms::Form
	{
	public:
		System::String^ DirectoryPath;

		InventoryForm(System::String^ path)
		{
			InitializeComponent();
			this->DirectoryPath = path;
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

		   // [?????????] Panel ???????????????????????????
	private: System::Windows::Forms::Panel^ bottomPanel;
	private: System::Windows::Forms::Button^ btnTrash;

	private: System::ComponentModel::Container^ components;
	private: System::Drawing::Point dragStartPoint;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->topPanel = (gcnew System::Windows::Forms::Panel());
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
			   this->flowLayoutPanel1->BackColor = System::Drawing::Color::White;
			   this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->flowLayoutPanel1->Location = System::Drawing::Point(0, 60);
			   this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			   this->flowLayoutPanel1->Padding = System::Windows::Forms::Padding(10);
			   this->flowLayoutPanel1->Size = System::Drawing::Size(800, 460);
			   this->flowLayoutPanel1->TabIndex = 0;
			   // 
			   // topPanel
			   // 
			   this->topPanel->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->topPanel->Controls->Add(this->lblStatus);
			   this->topPanel->Controls->Add(this->btnRefresh);
			   this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			   this->topPanel->Location = System::Drawing::Point(0, 0);
			   this->topPanel->Name = L"topPanel";
			   this->topPanel->Size = System::Drawing::Size(800, 60);
			   this->topPanel->TabIndex = 1;
			   // 
			   // lblStatus
			   // 
			   this->lblStatus->AutoSize = true;
			   this->lblStatus->Location = System::Drawing::Point(130, 20);
			   this->lblStatus->Name = L"lblStatus";
			   this->lblStatus->Size = System::Drawing::Size(65, 16);
			   this->lblStatus->TabIndex = 1;
			   this->lblStatus->Text = L"Loading...";
			   // 
			   // btnRefresh
			   // 
			   this->btnRefresh->Location = System::Drawing::Point(12, 12);
			   this->btnRefresh->Name = L"btnRefresh";
			   this->btnRefresh->Size = System::Drawing::Size(100, 35);
			   this->btnRefresh->TabIndex = 0;
			   this->btnRefresh->Text = L"Refresh";
			   this->btnRefresh->Click += gcnew System::EventHandler(this, &InventoryForm::btnRefresh_Click);
			   // 
			   // bottomPanel
			   // 
			   this->bottomPanel->BackColor = System::Drawing::Color::White;
			   this->bottomPanel->Controls->Add(this->btnTrash);
			   this->bottomPanel->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->bottomPanel->Location = System::Drawing::Point(0, 520);
			   this->bottomPanel->Name = L"bottomPanel";
			   this->bottomPanel->Size = System::Drawing::Size(800, 80);
			   this->bottomPanel->TabIndex = 1;
			   this->bottomPanel->Visible = false;
			   // 
			   // btnTrash
			   // 
			   this->btnTrash->AllowDrop = true;
			   this->btnTrash->BackColor = System::Drawing::Color::MistyRose;
			   this->btnTrash->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->btnTrash->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnTrash->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
			   this->btnTrash->ForeColor = System::Drawing::Color::Red;
			   this->btnTrash->Location = System::Drawing::Point(0, 0);
			   this->btnTrash->Margin = System::Windows::Forms::Padding(0);
			   this->btnTrash->Name = L"btnTrash";
			   this->btnTrash->Size = System::Drawing::Size(800, 80);
			   this->btnTrash->TabIndex = 0;
			   this->btnTrash->Text = L"??? DROP HERE TO DELETE ???";
			   this->btnTrash->UseVisualStyleBackColor = false;
			   this->btnTrash->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &InventoryForm::btnTrash_DragDrop);
			   this->btnTrash->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &InventoryForm::btnTrash_DragEnter);
			   // 
			   // InventoryForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(800, 600);
			   this->Controls->Add(this->flowLayoutPanel1);
			   this->Controls->Add(this->bottomPanel);
			   this->Controls->Add(this->topPanel);
			   this->Name = L"InventoryForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			   this->Text = L"My Gallery";
			   this->topPanel->ResumeLayout(false);
			   this->topPanel->PerformLayout();
			   this->bottomPanel->ResumeLayout(false);
			   this->ResumeLayout(false);

		   }
#pragma endregion

	private:
		// ... (???????? LoadImages ?????????????? ??????????) ...
		void LoadImages() {
			if (System::String::IsNullOrEmpty(this->DirectoryPath) || !Directory::Exists(this->DirectoryPath)) {
				lblStatus->Text = "Path not set or not found!";
				return;
			}
			this->flowLayoutPanel1->Controls->Clear();
			lblStatus->Text = "Loading...";
			this->Update();

			int count = 0;
			array<System::String^>^ files = Directory::GetFiles(this->DirectoryPath);
			for each (System::String ^ file in files) {
				System::String^ ext = Path::GetExtension(file)->ToLower();
				if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp") {
					try {
						Panel^ itemPanel = gcnew Panel();
						itemPanel->Size = System::Drawing::Size(160, 150);
						itemPanel->Margin = System::Windows::Forms::Padding(5);

						PictureBox^ pb = gcnew PictureBox();
						pb->Size = System::Drawing::Size(160, 120);
						pb->Dock = DockStyle::Top;
						pb->SizeMode = PictureBoxSizeMode::Zoom;
						pb->Cursor = Cursors::Hand;
						pb->Tag = file;

						FileStream^ fs = gcnew FileStream(file, FileMode::Open, FileAccess::Read);
						Image^ original = Image::FromStream(fs);
						pb->Image = gcnew Bitmap(original, pb->Width, pb->Height);
						delete original;
						fs->Close();
						delete fs;

						pb->Click += gcnew EventHandler(this, &InventoryForm::OnImageClick);
						pb->MouseDown += gcnew MouseEventHandler(this, &InventoryForm::OnImageMouseDown);
						pb->MouseMove += gcnew MouseEventHandler(this, &InventoryForm::OnImageMouseMove);

						Label^ lbl = gcnew Label();
						lbl->Text = Path::GetFileName(file);
						lbl->Dock = DockStyle::Bottom;
						lbl->TextAlign = ContentAlignment::MiddleCenter;

						itemPanel->Controls->Add(lbl);
						itemPanel->Controls->Add(pb);
						this->flowLayoutPanel1->Controls->Add(itemPanel);
						count++;
					}
					catch (System::Exception^ ex) {}
				}
			}
			lblStatus->Text = "Found " + count + " images.";
		}

		// --- Logic Drag & Drop (???????????) ---

		void OnImageMouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				dragStartPoint = e->Location;
			}
		}

		// *** ???????????: ???????????????????????? ***
		void OnImageMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			if (e->Button == System::Windows::Forms::MouseButtons::Left) {
				int dx = Math::Abs(e->X - dragStartPoint.X);
				int dy = Math::Abs(e->Y - dragStartPoint.Y);

				if (dx > 5 || dy > 5) {
					PictureBox^ pb = safe_cast<PictureBox^>(sender);
					if (pb->Tag != nullptr) {

						// 1. ???????????????????????????!
						this->bottomPanel->Visible = true;

						// 2. ???????? (?????????????????????????????????????)
						pb->DoDragDrop(pb->Tag, DragDropEffects::Move);

						// 3. ??????????????? (??????????????????????) ????????????????
						this->bottomPanel->Visible = false;
					}
				}
			}
		}

		void btnTrash_DragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
			if (e->Data->GetDataPresent(DataFormats::StringFormat)) {
				e->Effect = DragDropEffects::Move;
			}
			else {
				e->Effect = DragDropEffects::None;
			}
		}

		void btnTrash_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e) {
			System::String^ filePath = safe_cast<System::String^>(e->Data->GetData(DataFormats::StringFormat));

			// ????????????????????? ???????????????? (????????? MessageBox ???????????)
			if (MessageBox::Show("Delete this image?", "Trash", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes) {
				try {
					System::IO::File::Delete(filePath);
					LoadImages();
				}
				catch (System::Exception^ ex) {
					MessageBox::Show("Error: " + ex->Message);
				}
			}
		}

		System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) { LoadImages(); }

		void OnImageClick(System::Object^ sender, System::EventArgs^ e) {
			PictureBox^ pb = safe_cast<PictureBox^>(sender);
			if (pb->Tag != nullptr) {
				System::String^ filePath = safe_cast<System::String^>(pb->Tag);
				try { System::Diagnostics::Process::Start(filePath); }
				catch (System::Exception^) {}
			}
		}
	};
}