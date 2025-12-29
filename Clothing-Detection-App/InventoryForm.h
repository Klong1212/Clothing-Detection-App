#pragma once

namespace ClothingDetectionApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for InventoryForm
	/// </summary>
	public ref class InventoryForm : public System::Windows::Forms::Form
	{
	public:
		System::String^ DirectoryPath;
		InventoryForm(void)
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
		~InventoryForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Panel^ topPanel;
	private: System::Windows::Forms::Label^ Status;
	private: System::Windows::Forms::Button^ Refresh;



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
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->topPanel = (gcnew System::Windows::Forms::Panel());
			this->Refresh = (gcnew System::Windows::Forms::Button());
			this->Status = (gcnew System::Windows::Forms::Label());
			this->topPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->AutoScroll = true;
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(638, 472);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// topPanel
			// 
			this->topPanel->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->topPanel->Controls->Add(this->Status);
			this->topPanel->Controls->Add(this->Refresh);
			this->topPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->topPanel->Location = System::Drawing::Point(0, 0);
			this->topPanel->Name = L"topPanel";
			this->topPanel->Size = System::Drawing::Size(638, 28);
			this->topPanel->TabIndex = 0;
			this->topPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &InventoryForm::panel1_Paint);
			// 
			// Refresh
			// 
			this->Refresh->Location = System::Drawing::Point(245, 0);
			this->Refresh->Name = L"Refresh";
			this->Refresh->Size = System::Drawing::Size(75, 23);
			this->Refresh->TabIndex = 0;
			this->Refresh->Text = L"button1";
			this->Refresh->UseVisualStyleBackColor = true;
			// 
			// Status
			// 
			this->Status->AutoSize = true;
			this->Status->Location = System::Drawing::Point(464, 9);
			this->Status->Name = L"Status";
			this->Status->Size = System::Drawing::Size(44, 16);
			this->Status->TabIndex = 1;
			this->Status->Text = L"label1";
			// 
			// InventoryForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(638, 472);
			this->Controls->Add(this->topPanel);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Name = L"InventoryForm";
			this->Text = L"InventoryForm";
			this->topPanel->ResumeLayout(false);
			this->topPanel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	};
}
