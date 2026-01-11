#pragma once
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <msclr/marshal_cppstd.h>
#include "InventoryForm.h"
namespace ClothingDetectionApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::Drawing::Drawing2D;
	using namespace cv;
	/// <summary>
	/// Summary for CameraForm
	/// </summary>
	public ref class CameraForm : public System::Windows::Forms::Form
	{
	public:
		System::String^ DirectoryPath;
		CameraForm(void)
		{
			InitializeComponent();
			DirectoryPath = "";
			
			// Apply modern styling
			ApplyModernStyling();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CameraForm()
		{
			if (capture != nullptr) {
				capture->release();
				delete capture;
				capture = nullptr;
			}
			if (currentFrame != nullptr) {
				delete currentFrame;
				currentFrame = nullptr;
			}
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ cameraPanel;
	private: System::Windows::Forms::Panel^ controlPanel;
	private: System::Windows::Forms::Button^ btnCapture;
	private: System::Windows::Forms::Button^ btnGallery;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Timer^ countdownTimer;
	private: System::Windows::Forms::Label^ lblStatus;
	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Label^ lblCountdown;
	private: System::Windows::Forms::Label^ lblTimerTitle;
	private: System::Windows::Forms::RadioButton^ rb0sec;
	private: System::Windows::Forms::RadioButton^ rb5sec;
	private: System::Windows::Forms::RadioButton^ rb10sec;
	private: System::Windows::Forms::Panel^ timerPanel;
	private: System::ComponentModel::IContainer^ components;
	private: Bitmap^ bmp;
	private: VideoCapture* capture = nullptr;
	private: Mat* currentFrame = nullptr;
	private: int photoCount = 0;
	private: int countdownSeconds = 0;
	private: int selectedDelay = 0;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->cameraPanel = (gcnew System::Windows::Forms::Panel());
			this->lblCountdown = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->controlPanel = (gcnew System::Windows::Forms::Panel());
			this->timerPanel = (gcnew System::Windows::Forms::Panel());
			this->rb10sec = (gcnew System::Windows::Forms::RadioButton());
			this->rb5sec = (gcnew System::Windows::Forms::RadioButton());
			this->rb0sec = (gcnew System::Windows::Forms::RadioButton());
			this->lblTimerTitle = (gcnew System::Windows::Forms::Label());
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->btnGallery = (gcnew System::Windows::Forms::Button());
			this->btnCapture = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->countdownTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->cameraPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->controlPanel->SuspendLayout();
			this->timerPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// cameraPanel
			// 
			this->cameraPanel->BackColor = System::Drawing::Color::Black;
			this->cameraPanel->Controls->Add(this->lblCountdown);
			this->cameraPanel->Controls->Add(this->pictureBox1);
			this->cameraPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cameraPanel->Location = System::Drawing::Point(0, 0);
			this->cameraPanel->Name = L"cameraPanel";
			this->cameraPanel->Padding = System::Windows::Forms::Padding(10);
			this->cameraPanel->Size = System::Drawing::Size(1200, 700);
			this->cameraPanel->TabIndex = 0;
			// 
			// lblCountdown
			// 
			this->lblCountdown->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblCountdown->AutoSize = true;
			this->lblCountdown->BackColor = System::Drawing::Color::Transparent;
			this->lblCountdown->Font = (gcnew System::Drawing::Font(L"Segoe UI", 72, System::Drawing::FontStyle::Bold));
			this->lblCountdown->ForeColor = System::Drawing::Color::White;
			this->lblCountdown->Location = System::Drawing::Point(530, 280);
			this->lblCountdown->Name = L"lblCountdown";
			this->lblCountdown->Size = System::Drawing::Size(0, 159);
			this->lblCountdown->TabIndex = 1;
			this->lblCountdown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblCountdown->Visible = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(10, 10);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1180, 680);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &CameraForm::pictureBox1_Click);
			// 
			// controlPanel
			// 
			this->controlPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(48)));
			this->controlPanel->Controls->Add(this->timerPanel);
			this->controlPanel->Controls->Add(this->lblTitle);
			this->controlPanel->Controls->Add(this->lblStatus);
			this->controlPanel->Controls->Add(this->btnGallery);
			this->controlPanel->Controls->Add(this->btnCapture);
			this->controlPanel->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->controlPanel->Location = System::Drawing::Point(0, 700);
			this->controlPanel->Name = L"controlPanel";
			this->controlPanel->Size = System::Drawing::Size(1200, 120);
			this->controlPanel->TabIndex = 1;
			// 
			// timerPanel
			// 
			this->timerPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->timerPanel->Controls->Add(this->rb10sec);
			this->timerPanel->Controls->Add(this->rb5sec);
			this->timerPanel->Controls->Add(this->rb0sec);
			this->timerPanel->Controls->Add(this->lblTimerTitle);
			this->timerPanel->Location = System::Drawing::Point(920, 25);
			this->timerPanel->Name = L"timerPanel";
			this->timerPanel->Size = System::Drawing::Size(260, 80);
			this->timerPanel->TabIndex = 4;
			// 
			// rb10sec
			// 
			this->rb10sec->AutoSize = true;
			this->rb10sec->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->rb10sec->ForeColor = System::Drawing::Color::White;
			this->rb10sec->Location = System::Drawing::Point(170, 40);
			this->rb10sec->Name = L"rb10sec";
			this->rb10sec->Size = System::Drawing::Size(78, 27);
			this->rb10sec->TabIndex = 3;
			this->rb10sec->Text = L"10 sec";
			this->rb10sec->UseVisualStyleBackColor = true;
			this->rb10sec->CheckedChanged += gcnew System::EventHandler(this, &CameraForm::rb10sec_CheckedChanged);
			// 
			// rb5sec
			// 
			this->rb5sec->AutoSize = true;
			this->rb5sec->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->rb5sec->ForeColor = System::Drawing::Color::White;
			this->rb5sec->Location = System::Drawing::Point(90, 40);
			this->rb5sec->Name = L"rb5sec";
			this->rb5sec->Size = System::Drawing::Size(69, 27);
			this->rb5sec->TabIndex = 2;
			this->rb5sec->Text = L"5 sec";
			this->rb5sec->UseVisualStyleBackColor = true;
			this->rb5sec->CheckedChanged += gcnew System::EventHandler(this, &CameraForm::rb5sec_CheckedChanged);
			// 
			// rb0sec
			// 
			this->rb0sec->AutoSize = true;
			this->rb0sec->Checked = true;
			this->rb0sec->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
			this->rb0sec->ForeColor = System::Drawing::Color::White;
			this->rb0sec->Location = System::Drawing::Point(10, 40);
			this->rb0sec->Name = L"rb0sec";
			this->rb0sec->Size = System::Drawing::Size(69, 27);
			this->rb0sec->TabIndex = 1;
			this->rb0sec->TabStop = true;
			this->rb0sec->Text = L"0 sec";
			this->rb0sec->UseVisualStyleBackColor = true;
			this->rb0sec->CheckedChanged += gcnew System::EventHandler(this, &CameraForm::rb0sec_CheckedChanged);
			// 
			// lblTimerTitle
			// 
			this->lblTimerTitle->AutoSize = true;
			this->lblTimerTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->lblTimerTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(180)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->lblTimerTitle->Location = System::Drawing::Point(5, 10);
			this->lblTimerTitle->Name = L"lblTimerTitle";
			this->lblTimerTitle->Size = System::Drawing::Size(141, 23);
			this->lblTimerTitle->TabIndex = 0;
			this->lblTimerTitle->Text = L"⏱️ Timer Delay:";
			// 
			// lblTitle
			// 
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = System::Drawing::Color::White;
			this->lblTitle->Location = System::Drawing::Point(20, 15);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(161, 28);
			this->lblTitle->TabIndex = 3;
			this->lblTitle->Text = L"📷 Camera Live";
			// 
			// lblStatus
			// 
			this->lblStatus->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->lblStatus->AutoSize = true;
			this->lblStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->lblStatus->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->lblStatus->Location = System::Drawing::Point(20, 90);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(122, 20);
			this->lblStatus->TabIndex = 2;
			this->lblStatus->Text = L"Ready to capture";
			// 
			// btnGallery
			// 
			this->btnGallery->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->btnGallery->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(70)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->btnGallery->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnGallery->FlatAppearance->BorderSize = 0;
			this->btnGallery->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnGallery->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			this->btnGallery->ForeColor = System::Drawing::Color::White;
			this->btnGallery->Location = System::Drawing::Point(605, 45);
			this->btnGallery->Name = L"btnGallery";
			this->btnGallery->Size = System::Drawing::Size(120, 50);
			this->btnGallery->TabIndex = 1;
			this->btnGallery->Text = L"🖼️ Gallery";
			this->btnGallery->UseVisualStyleBackColor = false;
			this->btnGallery->Click += gcnew System::EventHandler(this, &CameraForm::btnGallery_Click);
			this->btnGallery->MouseEnter += gcnew System::EventHandler(this, &CameraForm::btnGallery_MouseEnter);
			this->btnGallery->MouseLeave += gcnew System::EventHandler(this, &CameraForm::btnGallery_MouseLeave);
			// 
			// btnCapture
			// 
			this->btnCapture->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->btnCapture->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(122)),
				static_cast<System::Int32>(static_cast<System::Byte>(204)));
			this->btnCapture->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnCapture->FlatAppearance->BorderSize = 0;
			this->btnCapture->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnCapture->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			this->btnCapture->ForeColor = System::Drawing::Color::White;
			this->btnCapture->Location = System::Drawing::Point(475, 45);
			this->btnCapture->Name = L"btnCapture";
			this->btnCapture->Size = System::Drawing::Size(120, 50);
			this->btnCapture->TabIndex = 0;
			this->btnCapture->Text = L"📸 Capture";
			this->btnCapture->UseVisualStyleBackColor = false;
			this->btnCapture->Click += gcnew System::EventHandler(this, &CameraForm::btnCapture_Click);
			this->btnCapture->MouseEnter += gcnew System::EventHandler(this, &CameraForm::btnCapture_MouseEnter);
			this->btnCapture->MouseLeave += gcnew System::EventHandler(this, &CameraForm::btnCapture_MouseLeave);
			// 
			// timer1
			// 
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &CameraForm::timer1_Tick);
			// 
			// countdownTimer
			// 
			this->countdownTimer->Interval = 1000;
			this->countdownTimer->Tick += gcnew System::EventHandler(this, &CameraForm::countdownTimer_Tick);
			// 
			// CameraForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(30)));
			this->ClientSize = System::Drawing::Size(1200, 820);
			this->Controls->Add(this->cameraPanel);
			this->Controls->Add(this->controlPanel);
			this->MinimumSize = System::Drawing::Size(800, 600);
			this->Name = L"CameraForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Camera - Clothing Detection";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &CameraForm::CameraForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &CameraForm::CameraForm_Load);
			this->cameraPanel->ResumeLayout(false);
			this->cameraPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->controlPanel->ResumeLayout(false);
			this->controlPanel->PerformLayout();
			this->timerPanel->ResumeLayout(false);
			this->timerPanel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: void ApplyModernStyling() {
		// Apply rounded corners to buttons
		MakeButtonRounded(btnCapture, 10);
		MakeButtonRounded(btnGallery, 10);
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

	private: System::Void CameraForm_Load(System::Object^ sender, System::EventArgs^ e) {
		capture = new VideoCapture(0);
		if (!capture->isOpened()) {
			MessageBox::Show("Failed to open camera!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			this->Close();
			return;
		}
		int capWidth = (int)capture->get(cv::CAP_PROP_FRAME_WIDTH);
		int capHeight = (int)capture->get(cv::CAP_PROP_FRAME_HEIGHT);
		
		bmp = gcnew Bitmap(capWidth, capHeight, PixelFormat::Format24bppRgb);
		timer1->Start();
		
		lblStatus->Text = "Camera is active • Ready to capture";
	}

	private: System::Void CameraForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		timer1->Stop();
		countdownTimer->Stop();
		if (capture != nullptr) {
			capture->release();
			delete capture;
			capture = nullptr;
		}
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (capture == nullptr || !capture->isOpened()) {
			return;
		}

		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height);
		BitmapData^ bmpData = bmp->LockBits(rect, ImageLockMode::WriteOnly, bmp->PixelFormat);
		int stride = bmpData->Stride;
		
		Mat image(bmp->Height, bmp->Width, CV_8UC3, bmpData->Scan0.ToPointer(), stride);
		
		if (!capture->read(image)) {
			bmp->UnlockBits(bmpData);
			return;
		}
		
		cv::flip(image, image, 1);
		
		if (currentFrame != nullptr) {
			delete currentFrame;
		}
		currentFrame = new Mat(image.clone());
		
		bmp->UnlockBits(bmpData);
		pictureBox1->Image = bmp;
	}

	private: System::Void btnCapture_Click(System::Object^ sender, System::EventArgs^ e) {
		if (selectedDelay == 0) {
			// Capture immediately
			CapturePhoto();
		}
		else {
			// Start countdown
			countdownSeconds = selectedDelay;
			lblCountdown->Text = countdownSeconds.ToString();
			lblCountdown->Visible = true;
			lblCountdown->BringToFront();
			btnCapture->Enabled = false;
			countdownTimer->Start();
		}
	}

	private: System::Void countdownTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		countdownSeconds--;
		
		if (countdownSeconds > 0) {
			lblCountdown->Text = countdownSeconds.ToString();
		}
		else {
			countdownTimer->Stop();
			lblCountdown->Visible = false;
			btnCapture->Enabled = true;
			CapturePhoto();
		}
	}

	private: void CapturePhoto() {
		if (currentFrame == nullptr || currentFrame->empty()) {
			MessageBox::Show("No frame to save!", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (System::String::IsNullOrEmpty(DirectoryPath)) {
			MessageBox::Show("Directory path is not set!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		try {
			DateTime now = DateTime::Now;
			System::String^ filename = System::String::Format("IMG_{0:yyyyMMdd_HHmmss}.jpg", now);
			System::String^ fullPath = System::IO::Path::Combine(DirectoryPath, filename);
			
			std::string stdPath = msclr::interop::marshal_as<std::string>(fullPath);
			
			cv::imwrite(stdPath, *currentFrame);
			
			photoCount++;
			lblStatus->Text = System::String::Format("✓ Photo saved! Total: {0} photos", photoCount);
			
			// Flash effect
			btnCapture->BackColor = Color::FromArgb(0, 200, 100);
			System::Threading::Thread::Sleep(100);
			btnCapture->BackColor = Color::FromArgb(0, 122, 204);
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Failed to save image!\n" + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnGallery_Click(System::Object^ sender, System::EventArgs^ e) {
		if (System::String::IsNullOrEmpty(this->DirectoryPath)) {
			MessageBox::Show("Directory Path is not set! Please take a photo first.", "Warning");
			return;
		}

		InventoryForm^ invForm = gcnew InventoryForm(this->DirectoryPath);
		invForm->ShowDialog();
	}

	// Radio button handlers
	private: System::Void rb0sec_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (rb0sec->Checked) selectedDelay = 0;
	}

	private: System::Void rb5sec_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (rb5sec->Checked) selectedDelay = 5;
	}

	private: System::Void rb10sec_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (rb10sec->Checked) selectedDelay = 10;
	}

	// Hover effects
	private: System::Void btnCapture_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btnCapture->BackColor = Color::FromArgb(0, 140, 230);
	}

	private: System::Void btnCapture_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btnCapture->BackColor = Color::FromArgb(0, 122, 204);
	}

	private: System::Void btnGallery_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btnGallery->BackColor = Color::FromArgb(90, 90, 95);
	}

	private: System::Void btnGallery_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btnGallery->BackColor = Color::FromArgb(70, 70, 75);
	}
private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
