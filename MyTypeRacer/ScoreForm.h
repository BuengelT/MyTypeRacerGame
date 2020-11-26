#pragma once

namespace MyTypeRacer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Data::SqlClient;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Zusammenfassung für ScoreForm
	/// </summary>
	public ref class ScoreForm : public System::Windows::Forms::Form
	{
	public:
		ScoreForm(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			// Datenbank String
			this->filePath = System::IO::Directory::GetCurrentDirectory();
			this->connectionString = "Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename=" + filePath + "\\Database.mdf;Integrated Security=True;Connect Timeout=30";

			fillComboBox();
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~ScoreForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: String^ filePath;
	private: String^ connectionString;
	private: List<int>^ list_textIDs = gcnew List<int>();
	private: System::Windows::Forms::ComboBox^ comboBox_Texts;
	protected:

	protected:

	private: System::Windows::Forms::Button^ button_Close;
	private: System::Windows::Forms::Panel^ panel_Main;
	private: System::Windows::Forms::DataGridView^ dataGridView;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dgv_Rang;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dgv_Name;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dgv_WPM;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dgv_Time;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dgv_Accuracy;

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
			this->comboBox_Texts = (gcnew System::Windows::Forms::ComboBox());
			this->button_Close = (gcnew System::Windows::Forms::Button());
			this->panel_Main = (gcnew System::Windows::Forms::Panel());
			this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->dgv_Rang = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dgv_Name = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dgv_WPM = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dgv_Time = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dgv_Accuracy = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panel_Main->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// comboBox_Texts
			// 
			this->comboBox_Texts->FormattingEnabled = true;
			this->comboBox_Texts->Location = System::Drawing::Point(182, 12);
			this->comboBox_Texts->MaxDropDownItems = 5;
			this->comboBox_Texts->Name = L"comboBox_Texts";
			this->comboBox_Texts->Size = System::Drawing::Size(173, 21);
			this->comboBox_Texts->TabIndex = 0;
			this->comboBox_Texts->SelectedIndexChanged += gcnew System::EventHandler(this, &ScoreForm::comboBox_Texts_SelectedIndexChanged);
			// 
			// button_Close
			// 
			this->button_Close->Location = System::Drawing::Point(12, 12);
			this->button_Close->Name = L"button_Close";
			this->button_Close->Size = System::Drawing::Size(75, 23);
			this->button_Close->TabIndex = 2;
			this->button_Close->Text = L"schließen";
			this->button_Close->UseVisualStyleBackColor = true;
			this->button_Close->Click += gcnew System::EventHandler(this, &ScoreForm::button_Close_Click);
			// 
			// panel_Main
			// 
			this->panel_Main->Controls->Add(this->dataGridView);
			this->panel_Main->Controls->Add(this->comboBox_Texts);
			this->panel_Main->Controls->Add(this->button_Close);
			this->panel_Main->Location = System::Drawing::Point(0, 0);
			this->panel_Main->Name = L"panel_Main";
			this->panel_Main->Size = System::Drawing::Size(368, 198);
			this->panel_Main->TabIndex = 3;
			// 
			// dataGridView
			// 
			this->dataGridView->AllowUserToAddRows = false;
			this->dataGridView->AllowUserToDeleteRows = false;
			this->dataGridView->AllowUserToResizeColumns = false;
			this->dataGridView->AllowUserToResizeRows = false;
			this->dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->dgv_Rang,
					this->dgv_Name, this->dgv_WPM, this->dgv_Time, this->dgv_Accuracy
			});
			this->dataGridView->Location = System::Drawing::Point(12, 39);
			this->dataGridView->Name = L"dataGridView";
			this->dataGridView->ReadOnly = true;
			this->dataGridView->RowHeadersVisible = false;
			this->dataGridView->Size = System::Drawing::Size(343, 150);
			this->dataGridView->TabIndex = 3;
			// 
			// dgv_Rang
			// 
			this->dgv_Rang->HeaderText = L"#";
			this->dgv_Rang->MaxInputLength = 2;
			this->dgv_Rang->MinimumWidth = 20;
			this->dgv_Rang->Name = L"dgv_Rang";
			this->dgv_Rang->ReadOnly = true;
			this->dgv_Rang->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgv_Rang->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dgv_Rang->Width = 20;
			// 
			// dgv_Name
			// 
			this->dgv_Name->HeaderText = L"Name";
			this->dgv_Name->MaxInputLength = 50;
			this->dgv_Name->MinimumWidth = 180;
			this->dgv_Name->Name = L"dgv_Name";
			this->dgv_Name->ReadOnly = true;
			this->dgv_Name->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgv_Name->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dgv_Name->Width = 180;
			// 
			// dgv_WPM
			// 
			this->dgv_WPM->HeaderText = L"WPM";
			this->dgv_WPM->MaxInputLength = 3;
			this->dgv_WPM->MinimumWidth = 40;
			this->dgv_WPM->Name = L"dgv_WPM";
			this->dgv_WPM->ReadOnly = true;
			this->dgv_WPM->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgv_WPM->Width = 40;
			// 
			// dgv_Time
			// 
			this->dgv_Time->HeaderText = L"Time";
			this->dgv_Time->MaxInputLength = 4;
			this->dgv_Time->MinimumWidth = 40;
			this->dgv_Time->Name = L"dgv_Time";
			this->dgv_Time->ReadOnly = true;
			this->dgv_Time->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgv_Time->Width = 40;
			// 
			// dgv_Accuracy
			// 
			this->dgv_Accuracy->HeaderText = L"Accuracy";
			this->dgv_Accuracy->MaxInputLength = 6;
			this->dgv_Accuracy->MinimumWidth = 60;
			this->dgv_Accuracy->Name = L"dgv_Accuracy";
			this->dgv_Accuracy->ReadOnly = true;
			this->dgv_Accuracy->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgv_Accuracy->Width = 60;
			// 
			// ScoreForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(368, 198);
			this->Controls->Add(this->panel_Main);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ScoreForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Highscores";
			this->panel_Main->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_Close_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void comboBox_Texts_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e); 

	private: System::Void fillComboBox(); 
	};
}
