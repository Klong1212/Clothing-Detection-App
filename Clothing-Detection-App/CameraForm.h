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
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	private: Bitmap^ bmp;
	private: VideoCapture* capture = nullptr;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: Mat* currentFrame = nullptr;
	protected:

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
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button3 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->pictureBox1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->button3);
			this->splitContainer1->Panel2->Controls->Add(this->button2);
			this->splitContainer1->Panel2->Controls->Add(this->button1);
			this->splitContainer1->Size = System::Drawing::Size(1194, 519);
			this->splitContainer1->SplitterDistance = 815;
			this->splitContainer1->TabIndex = 0;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(815, 519);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &CameraForm::pictureBox1_Click);
			// 
			// button2
			// 
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->button2->Location = System::Drawing::Point(99, 329);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(192, 138);
			this->button2->TabIndex = 1;
			this->button2->Text = L"IMAGE";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &CameraForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(148, 213);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(114, 91);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Save Image";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &CameraForm::button1_Click_1);
			// 
			// timer1
			// 
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &CameraForm::timer1_Tick);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(148, 56);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(114, 66);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Test Detect";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &CameraForm::button3_Click);
			// 
			// CameraForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(1194, 519);
			this->Controls->Add(this->splitContainer1);
			this->MaximizeBox = false;
			this->Name = L"CameraForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CameraForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &CameraForm::CameraForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &CameraForm::CameraForm_Load);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
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
	}

	private: System::Void CameraForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		timer1->Stop();
		if (capture != nullptr) {
			capture->release();
			delete capture;
			capture = nullptr;
		}
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
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

	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
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
			
			MessageBox::Show("Image saved successfully!\n" + fullPath, "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Failed to save image!\n" + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (System::String::IsNullOrEmpty(this->DirectoryPath)) {
		MessageBox::Show("Directory Path is not set! Please take a photo first.", "Warning");
		return;
	}

	InventoryForm^ invForm = gcnew InventoryForm(this->DirectoryPath);

	// timer1->Stop(); //  ถ้าต้องการหยุดกล้อง
	invForm->ShowDialog();
	// timer1->Start(); // ถ้าต้องการเริ่มกล้องใหม่
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	DetectFashionForm^ DeForm = gcnew DetectFashionForm();
	DeForm->ShowDialog();
}
};
}
