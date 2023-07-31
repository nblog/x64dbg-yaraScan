#pragma once

namespace x64dbgYaraScan {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// frmMain 摘要
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::ComboBox^ CBBOXMod;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ BTNScan;

	private: System::Windows::Forms::TextBox^ TXTBase;
	private: System::Windows::Forms::TextBox^ TXTSize;





	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::CheckedListBox^ CHKBOXRules;
	private: System::Windows::Forms::TreeView^ TREEResult;
	private: System::Windows::Forms::CheckBox^ CHKAll;
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::ComponentModel::IContainer^ components;


	protected:

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TXTSize = (gcnew System::Windows::Forms::TextBox());
			this->CBBOXMod = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->BTNScan = (gcnew System::Windows::Forms::Button());
			this->TXTBase = (gcnew System::Windows::Forms::TextBox());
			this->CHKBOXRules = (gcnew System::Windows::Forms::CheckedListBox());
			this->TREEResult = (gcnew System::Windows::Forms::TreeView());
			this->CHKAll = (gcnew System::Windows::Forms::CheckBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->TXTSize);
			this->groupBox1->Controls->Add(this->CBBOXMod);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->BTNScan);
			this->groupBox1->Controls->Add(this->TXTBase);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(428, 154);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Scan Mode";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(200, 86);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 18);
			this->label3->TabIndex = 13;
			this->label3->Text = L"Size:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 86);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 18);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Base:";
			// 
			// TXTSize
			// 
			this->TXTSize->Location = System::Drawing::Point(202, 116);
			this->TXTSize->Name = L"TXTSize";
			this->TXTSize->Size = System::Drawing::Size(120, 28);
			this->TXTSize->TabIndex = 9;
			this->TXTSize->Text = L"0";
			this->TXTSize->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &frmMain::TXTSize_Validating);
			// 
			// CBBOXMod
			// 
			this->CBBOXMod->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->CBBOXMod->FormattingEnabled = true;
			this->CBBOXMod->Location = System::Drawing::Point(6, 45);
			this->CBBOXMod->Name = L"CBBOXMod";
			this->CBBOXMod->Size = System::Drawing::Size(415, 26);
			this->CBBOXMod->TabIndex = 7;
			this->CBBOXMod->SelectedIndexChanged += gcnew System::EventHandler(this, &frmMain::CBBOXMod_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(80, 18);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Module: ";
			// 
			// BTNScan
			// 
			this->BTNScan->Location = System::Drawing::Point(328, 99);
			this->BTNScan->Name = L"BTNScan";
			this->BTNScan->Size = System::Drawing::Size(93, 50);
			this->BTNScan->TabIndex = 3;
			this->BTNScan->Text = L"Scan";
			this->BTNScan->UseVisualStyleBackColor = true;
			this->BTNScan->Click += gcnew System::EventHandler(this, &frmMain::btnScan_Click);
			// 
			// TXTBase
			// 
			this->TXTBase->Location = System::Drawing::Point(9, 116);
			this->TXTBase->Name = L"TXTBase";
			this->TXTBase->Size = System::Drawing::Size(187, 28);
			this->TXTBase->TabIndex = 2;
			this->TXTBase->Text = L"0";
			this->TXTBase->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &frmMain::TXTBase_Validating);
			// 
			// CHKBOXRules
			// 
			this->CHKBOXRules->FormattingEnabled = true;
			this->CHKBOXRules->Location = System::Drawing::Point(12, 177);
			this->CHKBOXRules->Name = L"CHKBOXRules";
			this->CHKBOXRules->Size = System::Drawing::Size(426, 354);
			this->CHKBOXRules->TabIndex = 3;
			// 
			// TREEResult
			// 
			this->TREEResult->Location = System::Drawing::Point(446, 12);
			this->TREEResult->Name = L"TREEResult";
			this->TREEResult->Size = System::Drawing::Size(482, 519);
			this->TREEResult->TabIndex = 4;
			this->TREEResult->NodeMouseDoubleClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &frmMain::TREEResult_NodeMouseDoubleClick);
			// 
			// CHKAll
			// 
			this->CHKAll->Appearance = System::Windows::Forms::Appearance::Button;
			this->CHKAll->AutoSize = true;
			this->CHKAll->Location = System::Drawing::Point(376, 489);
			this->CHKAll->Name = L"CHKAll";
			this->CHKAll->Size = System::Drawing::Size(45, 28);
			this->CHKAll->TabIndex = 7;
			this->CHKAll->Text = L"ALL";
			this->CHKAll->UseVisualStyleBackColor = true;
			this->CHKAll->CheckedChanged += gcnew System::EventHandler(this, &frmMain::CHKAll_CheckedChanged);
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(939, 546);
			this->Controls->Add(this->CHKAll);
			this->Controls->Add(this->TREEResult);
			this->Controls->Add(this->CHKBOXRules);
			this->Controls->Add(this->groupBox1);
			this->MaximizeBox = false;
			this->Name = L"frmMain";
			this->Text = L"x64dbg YARA Scan";
			this->Load += gcnew System::EventHandler(this, &frmMain::frmMain_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void frmMain_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnScan_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void CHKAll_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void CBBOXMod_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void TREEResult_NodeMouseDoubleClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e);
	private: System::Void TXTBase_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
	private: System::Void TXTSize_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
};
}
