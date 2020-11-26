#pragma once

namespace MyTypeRacer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für HelpForm
	/// </summary>
	public ref class HelpForm : public System::Windows::Forms::Form
	{
	public:
		HelpForm(void)
		{			
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//			
		}

		HelpForm(String^ str)
		{			
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			this->label_Text->Text = str;			
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~HelpForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel_Main;
	protected:

	private: System::Windows::Forms::Button^ button_Okay;
	private: System::Windows::Forms::Label^ label_Text;



	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel_Main = (gcnew System::Windows::Forms::Panel());
			this->label_Text = (gcnew System::Windows::Forms::Label());
			this->button_Okay = (gcnew System::Windows::Forms::Button());
			this->panel_Main->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel_Main
			// 
			this->panel_Main->Controls->Add(this->label_Text);
			this->panel_Main->Controls->Add(this->button_Okay);
			this->panel_Main->Location = System::Drawing::Point(0, 0);
			this->panel_Main->Name = L"panel_Main";
			this->panel_Main->Size = System::Drawing::Size(286, 182);
			this->panel_Main->TabIndex = 0;
			// 
			// label_Text
			// 
			this->label_Text->AutoSize = true;
			this->label_Text->Location = System::Drawing::Point(3, 3);
			this->label_Text->MaximumSize = System::Drawing::Size(280, 150);
			this->label_Text->Name = L"label_Text";
			this->label_Text->Size = System::Drawing::Size(37, 13);
			this->label_Text->TabIndex = 13;
			this->label_Text->Text = L"<filler>";
			// 
			// button_Okay
			// 
			this->button_Okay->Location = System::Drawing::Point(206, 156);
			this->button_Okay->Name = L"button_Okay";
			this->button_Okay->Size = System::Drawing::Size(75, 23);
			this->button_Okay->TabIndex = 0;
			this->button_Okay->Text = L"Ok";
			this->button_Okay->UseVisualStyleBackColor = true;
			this->button_Okay->Click += gcnew System::EventHandler(this, &HelpForm::button_Okay_Click);
			// 
			// HelpForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(286, 182);
			this->Controls->Add(this->panel_Main);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"HelpForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Help";
			this->panel_Main->ResumeLayout(false);
			this->panel_Main->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_Okay_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}		  

	
	};


}
