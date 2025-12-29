#pragma once

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
		// ???????????? path ??????? public
		System::String^ DirectoryPath;

		// Constructor ?????? Path
		InventoryForm(System::String^ path)
		{
			InitializeComponent();

			// ?????? path ?????????
			this->DirectoryPath = path;

			// ????????????????
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
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->topPanel = (gcnew System::Windows::Forms::Panel());
			   this->lblStatus = (gcnew System::Windows::Forms::Label());
			   this->btnRefresh = (gcnew System::Windows::Forms::Button());
			   this->topPanel->SuspendLayout();
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
			   this->flowLayoutPanel1->Size = System::Drawing::Size(800, 540);
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
			   this->btnRefresh->UseVisualStyleBackColor = true;
			   this->btnRefresh->Click += gcnew System::EventHandler(this, &InventoryForm::btnRefresh_Click);
			   // 
			   // InventoryForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(800, 600);
			   this->Controls->Add(this->flowLayoutPanel1);
			   this->Controls->Add(this->topPanel);
			   this->Name = L"InventoryForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			   this->Text = L"My Gallery";
			   this->topPanel->ResumeLayout(false);
			   this->topPanel->PerformLayout();
			   this->ResumeLayout(false);

		   }
#pragma endregion

	private:
		void LoadImages() {
			// ??? System:: ?????? String ???????? Error Ambiguous
			if (System::String::IsNullOrEmpty(this->DirectoryPath) || !Directory::Exists(this->DirectoryPath)) {
				lblStatus->Text = "Path not set or not found!";
				return;
			}

			this->flowLayoutPanel1->Controls->Clear();
			lblStatus->Text = "Loading...";
			this->Update();

			int count = 0;
			// ??? System:: ?????? String
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

						Label^ lbl = gcnew Label();
						lbl->Text = Path::GetFileName(file);
						lbl->Dock = DockStyle::Bottom;
						lbl->TextAlign = ContentAlignment::MiddleCenter;
						lbl->Height = 30;

						itemPanel->Controls->Add(lbl);
						itemPanel->Controls->Add(pb);

						this->flowLayoutPanel1->Controls->Add(itemPanel);
						count++;
					}
					// ??? System:: ?????? Exception
					catch (System::Exception^ ex) {
						Console::WriteLine("Error: " + ex->Message);
					}
				}
			}
			lblStatus->Text = "Found " + count + " images.";
		}

		System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
			LoadImages();
		}

		void OnImageClick(System::Object^ sender, System::EventArgs^ e) {
			PictureBox^ pb = safe_cast<PictureBox^>(sender);
			if (pb->Tag != nullptr) {
				System::String^ filePath = safe_cast<System::String^>(pb->Tag);
				try {
					// ??? System::Diagnostics:: ???????? Ambiguous ???????? Process
					System::Diagnostics::Process::Start(filePath);
				}
				catch (System::Exception^ ex) {
					MessageBox::Show("Cannot open image: " + ex->Message);
				}
			}
		}
	};
}