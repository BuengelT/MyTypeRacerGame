#pragma once

namespace MyTypeRacer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Zusammenfassung für NewTextForm
	/// </summary>
	public ref class NewTextForm : public System::Windows::Forms::Form
	{
	public:
		NewTextForm(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			// Datenbank String
			this->filePath = System::IO::Directory::GetCurrentDirectory();
			this->connectionString = "Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename=" + filePath + "\\Database.mdf;Integrated Security=True;Connect Timeout=30";
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~NewTextForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: String^ filePath;
	private: String^ connectionString;
	private: System::Windows::Forms::Panel^ panel_Main;
	protected:
	private: System::Windows::Forms::Button^ button_Reset;
	private: System::Windows::Forms::Button^ button_AddToDatabase;
	private: System::Windows::Forms::Label^ label_TextContent;
	private: System::Windows::Forms::TextBox^ textBox_TextContent;
	private: System::Windows::Forms::Label^ label_NameOfText;
	private: System::Windows::Forms::TextBox^ textBox_NameOfText;
	private: System::Windows::Forms::Button^ button_Close;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel_Main = (gcnew System::Windows::Forms::Panel());
			this->button_Close = (gcnew System::Windows::Forms::Button());
			this->button_Reset = (gcnew System::Windows::Forms::Button());
			this->button_AddToDatabase = (gcnew System::Windows::Forms::Button());
			this->label_TextContent = (gcnew System::Windows::Forms::Label());
			this->textBox_TextContent = (gcnew System::Windows::Forms::TextBox());
			this->label_NameOfText = (gcnew System::Windows::Forms::Label());
			this->textBox_NameOfText = (gcnew System::Windows::Forms::TextBox());
			this->panel_Main->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel_Main
			// 
			this->panel_Main->Controls->Add(this->button_Close);
			this->panel_Main->Controls->Add(this->button_Reset);
			this->panel_Main->Controls->Add(this->button_AddToDatabase);
			this->panel_Main->Controls->Add(this->label_TextContent);
			this->panel_Main->Controls->Add(this->textBox_TextContent);
			this->panel_Main->Controls->Add(this->label_NameOfText);
			this->panel_Main->Controls->Add(this->textBox_NameOfText);
			this->panel_Main->Location = System::Drawing::Point(0, 0);
			this->panel_Main->Name = L"panel_Main";
			this->panel_Main->Size = System::Drawing::Size(519, 317);
			this->panel_Main->TabIndex = 0;
			// 
			// button_Close
			// 
			this->button_Close->Location = System::Drawing::Point(422, 286);
			this->button_Close->Name = L"button_Close";
			this->button_Close->Size = System::Drawing::Size(90, 23);
			this->button_Close->TabIndex = 6;
			this->button_Close->Text = L"schließen";
			this->button_Close->UseVisualStyleBackColor = true;
			this->button_Close->Click += gcnew System::EventHandler(this, &NewTextForm::button_Close_Click);
			// 
			// button_Reset
			// 
			this->button_Reset->Location = System::Drawing::Point(180, 286);
			this->button_Reset->Name = L"button_Reset";
			this->button_Reset->Size = System::Drawing::Size(90, 23);
			this->button_Reset->TabIndex = 5;
			this->button_Reset->Text = L"zurücksetzen";
			this->button_Reset->UseVisualStyleBackColor = true;
			this->button_Reset->Click += gcnew System::EventHandler(this, &NewTextForm::button_Reset_Click);
			// 
			// button_AddToDatabase
			// 
			this->button_AddToDatabase->Location = System::Drawing::Point(12, 286);
			this->button_AddToDatabase->Name = L"button_AddToDatabase";
			this->button_AddToDatabase->Size = System::Drawing::Size(156, 23);
			this->button_AddToDatabase->TabIndex = 4;
			this->button_AddToDatabase->Text = L"Zur Datenbank hinzufügen";
			this->button_AddToDatabase->UseVisualStyleBackColor = true;
			this->button_AddToDatabase->Click += gcnew System::EventHandler(this, &NewTextForm::button_AddToDatabase_Click);
			// 
			// label_TextContent
			// 
			this->label_TextContent->AutoSize = true;
			this->label_TextContent->Location = System::Drawing::Point(9, 64);
			this->label_TextContent->Name = L"label_TextContent";
			this->label_TextContent->Size = System::Drawing::Size(99, 13);
			this->label_TextContent->TabIndex = 3;
			this->label_TextContent->Text = L"Einzugebener Text:";
			// 
			// textBox_TextContent
			// 
			this->textBox_TextContent->Location = System::Drawing::Point(12, 80);
			this->textBox_TextContent->Multiline = true;
			this->textBox_TextContent->Name = L"textBox_TextContent";
			this->textBox_TextContent->Size = System::Drawing::Size(500, 200);
			this->textBox_TextContent->TabIndex = 2;
			// 
			// label_NameOfText
			// 
			this->label_NameOfText->AutoSize = true;
			this->label_NameOfText->Location = System::Drawing::Point(12, 15);
			this->label_NameOfText->Name = L"label_NameOfText";
			this->label_NameOfText->Size = System::Drawing::Size(93, 13);
			this->label_NameOfText->TabIndex = 1;
			this->label_NameOfText->Text = L"Name des Textes:";
			// 
			// textBox_NameOfText
			// 
			this->textBox_NameOfText->Location = System::Drawing::Point(12, 31);
			this->textBox_NameOfText->MaxLength = 50;
			this->textBox_NameOfText->Name = L"textBox_NameOfText";
			this->textBox_NameOfText->Size = System::Drawing::Size(258, 20);
			this->textBox_NameOfText->TabIndex = 0;
			// 
			// NewTextForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(520, 318);
			this->Controls->Add(this->panel_Main);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"NewTextForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Neuen Text hinzufügen";
			this->panel_Main->ResumeLayout(false);
			this->panel_Main->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_Reset_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void button_AddToDatabase_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void button_Close_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
