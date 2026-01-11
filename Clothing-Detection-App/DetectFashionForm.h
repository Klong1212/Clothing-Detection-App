#pragma once

namespace ClothingDetectionApp {
	using namespace System::Drawing::Drawing2D;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Net::Http;
	using namespace System::Threading::Tasks;
	using System::String;
	using System::Exception;

	public ref class DetectFashionForm : public System::Windows::Forms::Form
	{
	private:
		String^ currentFilePath;
	public:
		DetectFashionForm(System::String^ imagePath)
		{
			InitializeComponent();
			this->currentFilePath = imagePath;
			ApplyModernStyling();
			
			if (System::IO::File::Exists(imagePath)) {
				this->pbOriginal->Image = Image::FromFile(imagePath);
			}
		}

	protected:
		~DetectFashionForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ btnUpload;
	private: System::Windows::Forms::PictureBox^ pbOriginal;
	private: System::Windows::Forms::PictureBox^ pbResult;
	private: System::Windows::Forms::Panel^ headerPanel;
	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Label^ lblOriginal;
	private: System::Windows::Forms::Label^ lblResult;
	private: System::Windows::Forms::Label^ lblStatus;
	private: System::Windows::Forms::Panel^ leftPanel;
	private: System::Windows::Forms::Panel^ rightPanel;
	private: System::Windows::Forms::Panel^ mainPanel;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::ComponentModel::Container^ components;
	private: literal String^ ApiUrl = "http://127.0.0.1:8000/segment";

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->btnUpload = (gcnew System::Windows::Forms::Button());
			   this->pbOriginal = (gcnew System::Windows::Forms::PictureBox());
			   this->pbResult = (gcnew System::Windows::Forms::PictureBox());
			   this->headerPanel = (gcnew System::Windows::Forms::Panel());
			   this->lblStatus = (gcnew System::Windows::Forms::Label());
			   this->lblTitle = (gcnew System::Windows::Forms::Label());
			   this->leftPanel = (gcnew System::Windows::Forms::Panel());
			   this->lblOriginal = (gcnew System::Windows::Forms::Label());
			   this->rightPanel = (gcnew System::Windows::Forms::Panel());
			   this->lblResult = (gcnew System::Windows::Forms::Label());
			   this->mainPanel = (gcnew System::Windows::Forms::Panel());
			   this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			   this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbOriginal))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbResult))->BeginInit();
			   this->headerPanel->SuspendLayout();
			   this->leftPanel->SuspendLayout();
			   this->rightPanel->SuspendLayout();
			   this->mainPanel->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // btnUpload
			   // 
			   this->btnUpload->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			   this->btnUpload->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(122)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			   this->btnUpload->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->btnUpload->FlatAppearance->BorderSize = 0;
			   this->btnUpload->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnUpload->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			   this->btnUpload->ForeColor = System::Drawing::Color::White;
			   this->btnUpload->Location = System::Drawing::Point(450, 720);
			   this->btnUpload->Name = L"btnUpload";
			   this->btnUpload->Size = System::Drawing::Size(250, 55);
			   this->btnUpload->TabIndex = 0;
			   this->btnUpload->Text = L"🤖 Process Image";
			   this->btnUpload->UseVisualStyleBackColor = false;
			   this->btnUpload->Click += gcnew System::EventHandler(this, &DetectFashionForm::btnUpload_Click);
			   this->btnUpload->MouseEnter += gcnew System::EventHandler(this, &DetectFashionForm::btnUpload_MouseEnter);
			   this->btnUpload->MouseLeave += gcnew System::EventHandler(this, &DetectFashionForm::btnUpload_MouseLeave);
			   // 
			   // pbOriginal
			   // 
			   this->pbOriginal->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)));
			   this->pbOriginal->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pbOriginal->Location = System::Drawing::Point(15, 50);
			   this->pbOriginal->Name = L"pbOriginal";
			   this->pbOriginal->Size = System::Drawing::Size(515, 585);
			   this->pbOriginal->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->pbOriginal->TabIndex = 1;
			   this->pbOriginal->TabStop = false;
			   // 
			   // pbResult
			   // 
			   this->pbResult->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)));
			   this->pbResult->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->pbResult->Location = System::Drawing::Point(15, 50);
			   this->pbResult->Name = L"pbResult";
			   this->pbResult->Size = System::Drawing::Size(515, 585);
			   this->pbResult->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->pbResult->TabIndex = 2;
			   this->pbResult->TabStop = false;
			   // 
			   // headerPanel
			   // 
			   this->headerPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)));
			   this->headerPanel->Controls->Add(this->lblStatus);
			   this->headerPanel->Controls->Add(this->lblTitle);
			   this->headerPanel->Dock = System::Windows::Forms::DockStyle::Top;
			   this->headerPanel->Location = System::Drawing::Point(0, 0);
			   this->headerPanel->Name = L"headerPanel";
			   this->headerPanel->Size = System::Drawing::Size(1150, 80);
			   this->headerPanel->TabIndex = 3;
			   // 
			   // lblStatus
			   // 
			   this->lblStatus->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->lblStatus->AutoSize = true;
			   this->lblStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			   this->lblStatus->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->lblStatus->Location = System::Drawing::Point(920, 30);
			   this->lblStatus->Name = L"lblStatus";
			   this->lblStatus->Size = System::Drawing::Size(200, 23);
			   this->lblStatus->TabIndex = 1;
			   this->lblStatus->Text = L"Ready to process";
			   // 
			   // lblTitle
			   // 
			   this->lblTitle->AutoSize = true;
			   this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
			   this->lblTitle->ForeColor = System::Drawing::Color::White;
			   this->lblTitle->Location = System::Drawing::Point(25, 22);
			   this->lblTitle->Name = L"lblTitle";
			   this->lblTitle->Size = System::Drawing::Size(380, 41);
			   this->lblTitle->TabIndex = 0;
			   this->lblTitle->Text = L"🔍 Fashion Detection AI";
			   // 
			   // leftPanel
			   // 
			   this->leftPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			   this->leftPanel->Controls->Add(this->pbOriginal);
			   this->leftPanel->Controls->Add(this->lblOriginal);
			   this->leftPanel->Location = System::Drawing::Point(20, 20);
			   this->leftPanel->Name = L"leftPanel";
			   this->leftPanel->Padding = System::Windows::Forms::Padding(15, 50, 15, 15);
			   this->leftPanel->Size = System::Drawing::Size(545, 650);
			   this->leftPanel->TabIndex = 4;
			   // 
			   // lblOriginal
			   // 
			   this->lblOriginal->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(122)), static_cast<System::Int32>(static_cast<System::Byte>(204)));
			   this->lblOriginal->Dock = System::Windows::Forms::DockStyle::Top;
			   this->lblOriginal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			   this->lblOriginal->ForeColor = System::Drawing::Color::White;
			   this->lblOriginal->Location = System::Drawing::Point(15, 0);
			   this->lblOriginal->Name = L"lblOriginal";
			   this->lblOriginal->Size = System::Drawing::Size(515, 50);
			   this->lblOriginal->TabIndex = 0;
			   this->lblOriginal->Text = L"📷 Original Image";
			   this->lblOriginal->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // rightPanel
			   // 
			   this->rightPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(48)));
			   this->rightPanel->Controls->Add(this->pbResult);
			   this->rightPanel->Controls->Add(this->lblResult);
			   this->rightPanel->Location = System::Drawing::Point(585, 20);
			   this->rightPanel->Name = L"rightPanel";
			   this->rightPanel->Padding = System::Windows::Forms::Padding(15, 50, 15, 15);
			   this->rightPanel->Size = System::Drawing::Size(545, 650);
			   this->rightPanel->TabIndex = 5;
			   // 
			   // lblResult
			   // 
			   this->lblResult->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(46)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(204)), static_cast<System::Int32>(static_cast<System::Byte>(113)));
			   this->lblResult->Dock = System::Windows::Forms::DockStyle::Top;
			   this->lblResult->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			   this->lblResult->ForeColor = System::Drawing::Color::White;
			   this->lblResult->Location = System::Drawing::Point(15, 0);
			   this->lblResult->Name = L"lblResult";
			   this->lblResult->Size = System::Drawing::Size(515, 50);
			   this->lblResult->TabIndex = 0;
			   this->lblResult->Text = L"✨ Processed Result";
			   this->lblResult->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // mainPanel
			   // 
			   this->mainPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(37)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(37)), static_cast<System::Int32>(static_cast<System::Byte>(38)));
			   this->mainPanel->Controls->Add(this->leftPanel);
			   this->mainPanel->Controls->Add(this->rightPanel);
			   this->mainPanel->Controls->Add(this->btnUpload);
			   this->mainPanel->Controls->Add(this->progressBar1);
			   this->mainPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->mainPanel->Location = System::Drawing::Point(0, 80);
			   this->mainPanel->Name = L"mainPanel";
			   this->mainPanel->Size = System::Drawing::Size(1150, 820);
			   this->mainPanel->TabIndex = 6;
			   // 
			   // progressBar1
			   // 
			   this->progressBar1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			   this->progressBar1->Location = System::Drawing::Point(350, 795);
			   this->progressBar1->Name = L"progressBar1";
			   this->progressBar1->Size = System::Drawing::Size(450, 10);
			   this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			   this->progressBar1->TabIndex = 1;
			   this->progressBar1->Visible = false;
			   // 
			   // backgroundWorker1
			   // 
			   this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &DetectFashionForm::backgroundWorker1_DoWork);
			   this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &DetectFashionForm::backgroundWorker1_RunWorkerCompleted);
			   // 
			   // DetectFashionForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), 
				   static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)));
			   this->ClientSize = System::Drawing::Size(1150, 900);
			   this->Controls->Add(this->mainPanel);
			   this->Controls->Add(this->headerPanel);
			   this->MinimumSize = System::Drawing::Size(1000, 700);
			   this->Name = L"DetectFashionForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Fashion Detection - AI Processing";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbOriginal))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbResult))->EndInit();
			   this->headerPanel->ResumeLayout(false);
			   this->headerPanel->PerformLayout();
			   this->leftPanel->ResumeLayout(false);
			   this->rightPanel->ResumeLayout(false);
			   this->mainPanel->ResumeLayout(false);
			   this->ResumeLayout(false);
		   }
#pragma endregion

	private: void ApplyModernStyling() {
		MakeButtonRounded(btnUpload, 12);
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

	private: System::Void btnUpload_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrEmpty(this->currentFilePath) || !File::Exists(this->currentFilePath)) {
			MessageBox::Show("No image received from Inventory!", "❌ Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		pbResult->Image = nullptr;
		btnUpload->Enabled = false;
		btnUpload->Text = L"⏳ Processing...";
		progressBar1->Visible = true;
		lblStatus->Text = L"Processing image...";
		lblStatus->ForeColor = Color::FromArgb(255, 193, 7);

		backgroundWorker1->RunWorkerAsync(this->currentFilePath);
	}

	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
		String^ filePath = safe_cast<String^>(e->Argument);

		try {
			HttpClient^ client = gcnew HttpClient();
			MultipartFormDataContent^ form = gcnew MultipartFormDataContent();
			FileStream^ fs = File::OpenRead(filePath);
			StreamContent^ fileContent = gcnew StreamContent(fs);

			form->Add(fileContent, "file", Path::GetFileName(filePath));

			HttpResponseMessage^ response = client->PostAsync("http://127.0.0.1:8000/segment", form)->Result;
			response->EnsureSuccessStatusCode();

			Stream^ returnStream = response->Content->ReadAsStreamAsync()->Result;
			e->Result = Image::FromStream(returnStream);

			fs->Close();
		}
		catch (Exception^ ex) {
			e->Result = ex;
		}
	}

	private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
		progressBar1->Visible = false;
		
		if (e->Result->GetType() == Exception::typeid) {
			Exception^ ex = safe_cast<Exception^>(e->Result);
			MessageBox::Show("Error: " + ex->Message, "❌ Processing Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
			lblStatus->Text = L"❌ Processing failed";
			lblStatus->ForeColor = Color::FromArgb(231, 76, 60);
		}
		else {
			Image^ processedImage = safe_cast<Image^>(e->Result);
			pbResult->Image = processedImage;
			lblStatus->Text = L"✅ Processing completed successfully!";
			lblStatus->ForeColor = Color::FromArgb(46, 204, 113);
		}

		btnUpload->Enabled = true;
		btnUpload->Text = L"🤖 Process Image";
	}

	private: System::Void btnUpload_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btnUpload->BackColor = Color::FromArgb(0, 140, 230);
	}

	private: System::Void btnUpload_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btnUpload->BackColor = Color::FromArgb(0, 122, 204);
	}
	};
}