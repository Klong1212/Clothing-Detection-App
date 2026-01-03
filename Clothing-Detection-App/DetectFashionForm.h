#pragma once

namespace ClothingDetectionApp {

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

	/// <summary>
	/// Summary for DetectFashionForm
	/// </summary>
	public ref class DetectFashionForm : public System::Windows::Forms::Form
	{
	public:
		DetectFashionForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DetectFashionForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnUpload;
	protected:
	private: System::Windows::Forms::PictureBox^ pbOriginal;
	private: System::Windows::Forms::PictureBox^ pbResult;

	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

	private: literal String^ ApiUrl = "http://127.0.0.1:8000/segment";

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->btnUpload = (gcnew System::Windows::Forms::Button());
			   this->pbOriginal = (gcnew System::Windows::Forms::PictureBox());
			   this->pbResult = (gcnew System::Windows::Forms::PictureBox());
			   this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbOriginal))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbResult))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // btnUpload
			   // 
			   this->btnUpload->Location = System::Drawing::Point(473, 56);
			   this->btnUpload->Name = L"btnUpload";
			   this->btnUpload->Size = System::Drawing::Size(192, 37);
			   this->btnUpload->TabIndex = 0;
			   this->btnUpload->Text = L"Upload & Process";
			   this->btnUpload->UseVisualStyleBackColor = true;
			   this->btnUpload->Click += gcnew System::EventHandler(this, &DetectFashionForm::btnUpload_Click);
			   // 
			   // pbOriginal
			   // 
			   this->pbOriginal->Location = System::Drawing::Point(53, 123);
			   this->pbOriginal->Name = L"pbOriginal";
			   this->pbOriginal->Size = System::Drawing::Size(478, 451);
			   this->pbOriginal->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->pbOriginal->TabIndex = 1;
			   this->pbOriginal->TabStop = false;
			   this->pbOriginal->Click += gcnew System::EventHandler(this, &DetectFashionForm::pbOriginal_Click);
			   // 
			   // pbResult
			   // 
			   this->pbResult->Location = System::Drawing::Point(596, 123);
			   this->pbResult->Name = L"pbResult";
			   this->pbResult->Size = System::Drawing::Size(465, 451);
			   this->pbResult->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->pbResult->TabIndex = 2;
			   this->pbResult->TabStop = false;
			   this->pbResult->Click += gcnew System::EventHandler(this, &DetectFashionForm::pbResult_Click);
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
			   this->ClientSize = System::Drawing::Size(1110, 627);
			   this->Controls->Add(this->pbResult);
			   this->Controls->Add(this->pbOriginal);
			   this->Controls->Add(this->btnUpload);
			   this->Name = L"DetectFashionForm";
			   this->Text = L"DetectFashionForm";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbOriginal))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbResult))->EndInit();
			   this->ResumeLayout(false);

		   }
#pragma endregion
		   // 1. ปุ่มกด Upload: แค่สั่งให้ Worker เริ่มทำงาน
	private: System::Void btnUpload_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "Image Files|*.jpg;*.jpeg;*.png;";

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filePath = openFileDialog->FileName;

			// โชว์รูปต้นฉบับ
			pbOriginal->Image = Image::FromFile(filePath);
			pbResult->Image = nullptr;

			// ปรับปุ่ม
			btnUpload->Enabled = false;
			btnUpload->Text = "Processing...";

			// เริ่มทำงานเบื้องหลัง (ส่ง filePath ไปด้วย)
			backgroundWorker1->RunWorkerAsync(filePath);
		}
	}
	private: System::Void pbOriginal_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pbResult_Click(System::Object^ sender, System::EventArgs^ e) {
	}
		   // 2. DoWork: ทำงานหนักๆ (เชื่อมต่อ Server) ตรงนี้ *ห้ามแตะ UI*
	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
		// รับ filePath ที่ส่งมา
		String^ filePath = safe_cast<String^>(e->Argument);

		try {
			HttpClient^ client = gcnew HttpClient();
			// เพิ่ม Reference System.Net.Http ก่อนนะครับ ถึงจะใช้บรรทัดนี้ได้

			MultipartFormDataContent^ form = gcnew MultipartFormDataContent();
			FileStream^ fs = File::OpenRead(filePath);
			StreamContent^ fileContent = gcnew StreamContent(fs);

			form->Add(fileContent, "file", Path::GetFileName(filePath));

			// ส่งข้อมูล (Synchronous ได้เลยเพราะอยู่ใน BackgroundWorker แล้ว)
			HttpResponseMessage^ response = client->PostAsync("http://127.0.0.1:8000/segment", form)->Result;
			response->EnsureSuccessStatusCode();

			// อ่านผลลัพธ์
			Stream^ returnStream = response->Content->ReadAsStreamAsync()->Result;

			// ส่งผลลัพธ์ (รูปภาพ) ไปให้ฟังก์ชันจบ
			e->Result = Image::FromStream(returnStream);

			// ปิดไฟล์
			fs->Close();
		}
		catch (Exception^ ex) {
			// ถ้า error ให้ส่ง error message ไปแทน
			e->Result = ex;
		}
	}
		   // 3. RunWorkerCompleted: งานเสร็จแล้ว อัปเดตหน้าจอตรงนี้
	private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {
		// ตรวจสอบว่าผลลัพธ์เป็น Error หรือ รูปภาพ
		if (e->Result->GetType() == Exception::typeid) {
			Exception^ ex = safe_cast<Exception^>(e->Result);
			MessageBox::Show("Error: " + ex->Message);
		}
		else {
			// เอารูปมาแสดง
			Image^ processedImage = safe_cast<Image^>(e->Result);
			pbResult->Image = processedImage;
		}

		// คืนค่าปุ่ม
		btnUpload->Enabled = true;
		btnUpload->Text = "Upload & Process";
	}
	};
}