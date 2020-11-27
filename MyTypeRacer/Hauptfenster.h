#pragma once
#include "HelpForm.h"
#include "NewTextForm.h"
#include "ScoreForm.h"

namespace MyTypeRacer {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Data::SqlClient;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Zusammenfassung für Hauptfenster
	/// </summary>
	public ref class Hauptfenster : public System::Windows::Forms::Form
	{
	public:
		Hauptfenster(void)
		{

			////////////////////////////////////////////////////////////////////////
			// Hinzufuegen neuer Funktionalitäten
			// - Den Timer mit Millisekunden anzeigen
			// - Date zu den Highscore-DB hinzufuegen
			// - Anzahl der Tippfehler zur Highscore-DB hinzufuegen
			////////////////////////////////////////////////////////////////////////

			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//		
			// Datenbank String
			this->filePath = System::IO::Directory::GetCurrentDirectory();
			this->connectionString = "Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename=" + filePath + "\\Database.mdf;Integrated Security=True;Connect Timeout=30";

			fillComboBox();
			// Alle Werte bei neuer Runde zuruecksetzen
			//initializeNewGame(true); // starten mit Zufallstext
			initializeNewGame(Hauptfenster::InitText::random);
			
			manageButtons(false, false, false);
			

			this->string_Welcome = "Willkommen zu TypeRacer," + Environment::NewLine
				+ "ein Programm bei dem Sie Ihre Tippgeschwindigkeit ermitteln können!" + Environment::NewLine + Environment::NewLine
				+ "ø Words/Min = Ermittelt die durchschnittliche getippte Anzahl der Wörter in der Minute nach der Formel, dass ein Wort durchschnittlich aus 5 Zeichen besteht." + Environment::NewLine + Environment::NewLine
				+ "Starten mit der Wahl eines Textes!";

			// Variablen die nur zu Beginn des Programmstarts gesetzt werden			
			this->richTextBox_CurrentText->Text = this->string_Welcome;
			this->richTextBox_OneLine->Text = "";
			this->comboBox_Texts->Text = "";

			// Variable die festlegt wie viele Wörter in der TextBoxOneLine angezeigt werden
			this->int_textBoxOneLineWords = 4;

			// Forms das erste mal Initialisieren
			this->wForm_NewText = gcnew NewTextForm;
			this->wForm_Help = gcnew HelpForm(this->string_Welcome);
			this->wForm_Score = gcnew ScoreForm;	
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Hauptfenster()
		{
			if (components)
			{
				delete components;
			}
		}
	public: enum class InitText{random, select, keep};
	private: int int_TextID; // TextID aus der Datenbank
	private: String^ string_TextDescription; // Description aus der Datenbank
	private: int int_textBoxOneLineWords; // Anzahl der Woerter die in richTextBoxOneLineWord angezeigt werden
	private: int int_countdownValue; // Integer zum Zaehlen des Countdowns
	private: int int_wordProgress; // Integer zum Zaehlen des Wortfortschrittes
	private: int int_timeSpentSec; // Integer zum Zaehlen der gebrauchten Zeit
	private: int int_keyStrokes; // Ermittelt die Anzahl der Tastenanschlaege pro Minute
	private: bool bool_ErrorBit; // Prueft ob Fehler aufgetreten ist und wird bereinigt wenn kein Fehler mehr vorliegt
	private: int int_Errors; // Integer zum Zaehlen der eingegebenen Fehler
	private: String^ string_CurrentText;  // Der gesamte aktuelle Text
	private: String^ string_CurrentWord; // Das aktuelle Wort
	private: String^ string_Welcome; // Willkommenstext
	private: array<String^>^ array_CurrentText; // Der aktuelle Text in ein Array unterteilt, um die Woerter zu erkennen	
	private: String^ filePath; // Datenbank Speicherort
	private: String^ connectionString; // Datenbank connection String
	private: List<int>^ list_TextIDs = gcnew List<int>();
	private: HelpForm^ wForm_Help;
	private: NewTextForm^ wForm_NewText;
	private: ScoreForm^ wForm_Score;

	private: System::Windows::Forms::Panel^ panel_Main;
	private: System::Windows::Forms::Label^ label_Words;
	private: System::Windows::Forms::Label^ label_WPM;
	private: System::Windows::Forms::Label^ label_Time;
	private: System::Windows::Forms::TextBox^ textBox_Input;
	private: System::Windows::Forms::ProgressBar^ progressBar_Progress;
	private: System::Windows::Forms::Button^ button_Reset;
	private: System::Windows::Forms::Button^ button_Stop;
	private: System::Windows::Forms::Button^ button_Start;
	private: System::Windows::Forms::Panel^ panel_Control;
	private: System::Windows::Forms::Button^ button_ChangeText;
	private: System::Windows::Forms::Label^ label_CountDown;
	private: System::Windows::Forms::Timer^ timer_Countdown;
	private: System::Windows::Forms::Timer^ timer_CalcValues;
	private: System::Windows::Forms::Label^ label_WordsTag;
	private: System::Windows::Forms::Label^ label_WPMTag;
	private: System::Windows::Forms::Label^ label_TimeTag;
	private: System::Windows::Forms::RichTextBox^ richTextBox_OneLine;
	private: System::Windows::Forms::RichTextBox^ richTextBox_CurrentText;
	private: System::Windows::Forms::Label^ label_Errors;
	private: System::Windows::Forms::Label^ label_ErrorLabel;
	private: System::Windows::Forms::Panel^ panel_View;
	private: System::Windows::Forms::MenuStrip^ menuStrip_Auswahl;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_MainMenu;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_Questionmark;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_AddNewText;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_ShowHighscore;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_Exit;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_Help;
	private: System::Windows::Forms::ToolStripMenuItem^ tsmi_Info;
	private: System::Windows::Forms::TextBox^ textBox_NameInput;
	private: System::Windows::Forms::ComboBox^ comboBox_Texts;
	private: System::Windows::Forms::Panel^ panel1;

	private: System::ComponentModel::IContainer^ components;

	protected:

	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel_Main = (gcnew System::Windows::Forms::Panel());
			this->panel_View = (gcnew System::Windows::Forms::Panel());
			this->richTextBox_OneLine = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox_Input = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox_CurrentText = (gcnew System::Windows::Forms::RichTextBox());
			this->progressBar_Progress = (gcnew System::Windows::Forms::ProgressBar());
			this->panel_Control = (gcnew System::Windows::Forms::Panel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label_TimeTag = (gcnew System::Windows::Forms::Label());
			this->label_Time = (gcnew System::Windows::Forms::Label());
			this->label_WordsTag = (gcnew System::Windows::Forms::Label());
			this->label_Errors = (gcnew System::Windows::Forms::Label());
			this->label_Words = (gcnew System::Windows::Forms::Label());
			this->label_ErrorLabel = (gcnew System::Windows::Forms::Label());
			this->label_WPMTag = (gcnew System::Windows::Forms::Label());
			this->label_WPM = (gcnew System::Windows::Forms::Label());
			this->comboBox_Texts = (gcnew System::Windows::Forms::ComboBox());
			this->textBox_NameInput = (gcnew System::Windows::Forms::TextBox());
			this->button_ChangeText = (gcnew System::Windows::Forms::Button());
			this->label_CountDown = (gcnew System::Windows::Forms::Label());
			this->button_Reset = (gcnew System::Windows::Forms::Button());
			this->button_Stop = (gcnew System::Windows::Forms::Button());
			this->button_Start = (gcnew System::Windows::Forms::Button());
			this->timer_Countdown = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer_CalcValues = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip_Auswahl = (gcnew System::Windows::Forms::MenuStrip());
			this->tsmi_MainMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmi_AddNewText = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmi_ShowHighscore = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmi_Exit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmi_Questionmark = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmi_Help = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tsmi_Info = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel_Main->SuspendLayout();
			this->panel_View->SuspendLayout();
			this->panel_Control->SuspendLayout();
			this->panel1->SuspendLayout();
			this->menuStrip_Auswahl->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel_Main
			// 
			this->panel_Main->Controls->Add(this->panel_View);
			this->panel_Main->Controls->Add(this->panel_Control);
			this->panel_Main->Location = System::Drawing::Point(0, 27);
			this->panel_Main->Name = L"panel_Main";
			this->panel_Main->Size = System::Drawing::Size(630, 293);
			this->panel_Main->TabIndex = 0;
			// 
			// panel_View
			// 
			this->panel_View->Controls->Add(this->richTextBox_OneLine);
			this->panel_View->Controls->Add(this->textBox_Input);
			this->panel_View->Controls->Add(this->richTextBox_CurrentText);
			this->panel_View->Controls->Add(this->progressBar_Progress);
			this->panel_View->Location = System::Drawing::Point(3, 3);
			this->panel_View->Name = L"panel_View";
			this->panel_View->Size = System::Drawing::Size(466, 287);
			this->panel_View->TabIndex = 2;
			// 
			// richTextBox_OneLine
			// 
			this->richTextBox_OneLine->BackColor = System::Drawing::Color::Bisque;
			this->richTextBox_OneLine->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox_OneLine->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox_OneLine->Location = System::Drawing::Point(3, 217);
			this->richTextBox_OneLine->Multiline = false;
			this->richTextBox_OneLine->Name = L"richTextBox_OneLine";
			this->richTextBox_OneLine->ReadOnly = true;
			this->richTextBox_OneLine->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->richTextBox_OneLine->Size = System::Drawing::Size(460, 30);
			this->richTextBox_OneLine->TabIndex = 10;
			this->richTextBox_OneLine->Text = L"";
			// 
			// textBox_Input
			// 
			this->textBox_Input->BackColor = System::Drawing::SystemColors::Window;
			this->textBox_Input->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox_Input->Location = System::Drawing::Point(3, 254);
			this->textBox_Input->Multiline = true;
			this->textBox_Input->Name = L"textBox_Input";
			this->textBox_Input->ReadOnly = true;
			this->textBox_Input->Size = System::Drawing::Size(460, 30);
			this->textBox_Input->TabIndex = 0;
			this->textBox_Input->TextChanged += gcnew System::EventHandler(this, &Hauptfenster::textBox_Input_TextChanged);
			this->textBox_Input->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Hauptfenster::textBox_Input_KeyPress);
			// 
			// richTextBox_CurrentText
			// 
			this->richTextBox_CurrentText->BackColor = System::Drawing::Color::Beige;
			this->richTextBox_CurrentText->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox_CurrentText->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->richTextBox_CurrentText->Location = System::Drawing::Point(3, 3);
			this->richTextBox_CurrentText->Name = L"richTextBox_CurrentText";
			this->richTextBox_CurrentText->ReadOnly = true;
			this->richTextBox_CurrentText->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->richTextBox_CurrentText->Size = System::Drawing::Size(460, 190);
			this->richTextBox_CurrentText->TabIndex = 11;
			this->richTextBox_CurrentText->Text = L"";
			// 
			// progressBar_Progress
			// 
			this->progressBar_Progress->Location = System::Drawing::Point(3, 200);
			this->progressBar_Progress->Name = L"progressBar_Progress";
			this->progressBar_Progress->Size = System::Drawing::Size(460, 10);
			this->progressBar_Progress->Step = 1;
			this->progressBar_Progress->TabIndex = 9;
			// 
			// panel_Control
			// 
			this->panel_Control->Controls->Add(this->panel1);
			this->panel_Control->Controls->Add(this->comboBox_Texts);
			this->panel_Control->Controls->Add(this->textBox_NameInput);
			this->panel_Control->Controls->Add(this->button_ChangeText);
			this->panel_Control->Controls->Add(this->label_CountDown);
			this->panel_Control->Controls->Add(this->button_Reset);
			this->panel_Control->Controls->Add(this->button_Stop);
			this->panel_Control->Controls->Add(this->button_Start);
			this->panel_Control->Location = System::Drawing::Point(472, 3);
			this->panel_Control->Name = L"panel_Control";
			this->panel_Control->Size = System::Drawing::Size(155, 287);
			this->panel_Control->TabIndex = 1;
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->label_TimeTag);
			this->panel1->Controls->Add(this->label_Time);
			this->panel1->Controls->Add(this->label_WordsTag);
			this->panel1->Controls->Add(this->label_Errors);
			this->panel1->Controls->Add(this->label_Words);
			this->panel1->Controls->Add(this->label_ErrorLabel);
			this->panel1->Controls->Add(this->label_WPMTag);
			this->panel1->Controls->Add(this->label_WPM);
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(150, 96);
			this->panel1->TabIndex = 19;
			// 
			// label_TimeTag
			// 
			this->label_TimeTag->AutoSize = true;
			this->label_TimeTag->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_TimeTag->Location = System::Drawing::Point(3, 8);
			this->label_TimeTag->Name = L"label_TimeTag";
			this->label_TimeTag->Size = System::Drawing::Size(47, 20);
			this->label_TimeTag->TabIndex = 13;
			this->label_TimeTag->Text = L"Time:";
			// 
			// label_Time
			// 
			this->label_Time->AutoSize = true;
			this->label_Time->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_Time->Location = System::Drawing::Point(115, 8);
			this->label_Time->Name = L"label_Time";
			this->label_Time->Size = System::Drawing::Size(18, 20);
			this->label_Time->TabIndex = 3;
			this->label_Time->Text = L"0";
			this->label_Time->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_WordsTag
			// 
			this->label_WordsTag->AutoSize = true;
			this->label_WordsTag->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_WordsTag->Location = System::Drawing::Point(3, 28);
			this->label_WordsTag->Name = L"label_WordsTag";
			this->label_WordsTag->Size = System::Drawing::Size(106, 20);
			this->label_WordsTag->TabIndex = 5;
			this->label_WordsTag->Text = L"Typed Words:";
			// 
			// label_Errors
			// 
			this->label_Errors->AutoSize = true;
			this->label_Errors->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_Errors->Location = System::Drawing::Point(94, 68);
			this->label_Errors->Name = L"label_Errors";
			this->label_Errors->Size = System::Drawing::Size(18, 20);
			this->label_Errors->TabIndex = 15;
			this->label_Errors->Text = L"0";
			this->label_Errors->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_Words
			// 
			this->label_Words->AutoSize = true;
			this->label_Words->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_Words->Location = System::Drawing::Point(115, 28);
			this->label_Words->Name = L"label_Words";
			this->label_Words->Size = System::Drawing::Size(18, 20);
			this->label_Words->TabIndex = 14;
			this->label_Words->Text = L"0";
			this->label_Words->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_ErrorLabel
			// 
			this->label_ErrorLabel->AutoSize = true;
			this->label_ErrorLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_ErrorLabel->Location = System::Drawing::Point(3, 68);
			this->label_ErrorLabel->Name = L"label_ErrorLabel";
			this->label_ErrorLabel->Size = System::Drawing::Size(99, 20);
			this->label_ErrorLabel->TabIndex = 16;
			this->label_ErrorLabel->Text = L"Genauigkeit:";
			// 
			// label_WPMTag
			// 
			this->label_WPMTag->AutoSize = true;
			this->label_WPMTag->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_WPMTag->Location = System::Drawing::Point(3, 48);
			this->label_WPMTag->Name = L"label_WPMTag";
			this->label_WPMTag->Size = System::Drawing::Size(101, 20);
			this->label_WPMTag->TabIndex = 12;
			this->label_WPMTag->Text = L"ø Words/Min:";
			// 
			// label_WPM
			// 
			this->label_WPM->AutoSize = true;
			this->label_WPM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_WPM->Location = System::Drawing::Point(115, 48);
			this->label_WPM->Name = L"label_WPM";
			this->label_WPM->Size = System::Drawing::Size(18, 20);
			this->label_WPM->TabIndex = 4;
			this->label_WPM->Text = L"0";
			this->label_WPM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// comboBox_Texts
			// 
			this->comboBox_Texts->FormattingEnabled = true;
			this->comboBox_Texts->Location = System::Drawing::Point(7, 131);
			this->comboBox_Texts->Name = L"comboBox_Texts";
			this->comboBox_Texts->Size = System::Drawing::Size(143, 21);
			this->comboBox_Texts->TabIndex = 18;
			this->comboBox_Texts->SelectedIndexChanged += gcnew System::EventHandler(this, &Hauptfenster::comboBox_Texts_SelectedIndexChanged);
			// 
			// textBox_NameInput
			// 
			this->textBox_NameInput->Location = System::Drawing::Point(7, 105);
			this->textBox_NameInput->Name = L"textBox_NameInput";
			this->textBox_NameInput->Size = System::Drawing::Size(143, 20);
			this->textBox_NameInput->TabIndex = 17;
			this->textBox_NameInput->Tag = L"";
			this->textBox_NameInput->Text = L"<Ihr Name>";
			this->textBox_NameInput->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button_ChangeText
			// 
			this->button_ChangeText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_ChangeText->Location = System::Drawing::Point(5, 254);
			this->button_ChangeText->Name = L"button_ChangeText";
			this->button_ChangeText->Size = System::Drawing::Size(70, 30);
			this->button_ChangeText->TabIndex = 11;
			this->button_ChangeText->Text = L"RND";
			this->button_ChangeText->UseVisualStyleBackColor = true;
			this->button_ChangeText->Click += gcnew System::EventHandler(this, &Hauptfenster::button_ChangeText_Click);
			// 
			// label_CountDown
			// 
			this->label_CountDown->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label_CountDown->AutoSize = true;
			this->label_CountDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_CountDown->Location = System::Drawing::Point(53, 155);
			this->label_CountDown->Name = L"label_CountDown";
			this->label_CountDown->Size = System::Drawing::Size(51, 55);
			this->label_CountDown->TabIndex = 10;
			this->label_CountDown->Text = L"5";
			this->label_CountDown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button_Reset
			// 
			this->button_Reset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_Reset->Location = System::Drawing::Point(80, 254);
			this->button_Reset->Name = L"button_Reset";
			this->button_Reset->Size = System::Drawing::Size(70, 30);
			this->button_Reset->TabIndex = 8;
			this->button_Reset->Text = L"Reset";
			this->button_Reset->UseVisualStyleBackColor = true;
			this->button_Reset->Click += gcnew System::EventHandler(this, &Hauptfenster::button_Reset_Click);
			// 
			// button_Stop
			// 
			this->button_Stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_Stop->Location = System::Drawing::Point(80, 218);
			this->button_Stop->Name = L"button_Stop";
			this->button_Stop->Size = System::Drawing::Size(70, 30);
			this->button_Stop->TabIndex = 7;
			this->button_Stop->Text = L"Stop";
			this->button_Stop->UseVisualStyleBackColor = true;
			this->button_Stop->Click += gcnew System::EventHandler(this, &Hauptfenster::button_Stop_Click);
			// 
			// button_Start
			// 
			this->button_Start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_Start->Location = System::Drawing::Point(5, 218);
			this->button_Start->Name = L"button_Start";
			this->button_Start->Size = System::Drawing::Size(70, 30);
			this->button_Start->TabIndex = 6;
			this->button_Start->Text = L"Start";
			this->button_Start->UseVisualStyleBackColor = true;
			this->button_Start->Click += gcnew System::EventHandler(this, &Hauptfenster::button_Start_Click);
			// 
			// timer_Countdown
			// 
			this->timer_Countdown->Interval = 1000;
			this->timer_Countdown->Tick += gcnew System::EventHandler(this, &Hauptfenster::timer_Countdown_Tick);
			// 
			// timer_CalcValues
			// 
			this->timer_CalcValues->Interval = 1000;
			this->timer_CalcValues->Tick += gcnew System::EventHandler(this, &Hauptfenster::timer_CalcValues_Tick);
			// 
			// menuStrip_Auswahl
			// 
			this->menuStrip_Auswahl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->menuStrip_Auswahl->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->tsmi_MainMenu,
					this->tsmi_Questionmark
			});
			this->menuStrip_Auswahl->Location = System::Drawing::Point(0, 0);
			this->menuStrip_Auswahl->Name = L"menuStrip_Auswahl";
			this->menuStrip_Auswahl->Size = System::Drawing::Size(631, 24);
			this->menuStrip_Auswahl->TabIndex = 1;
			this->menuStrip_Auswahl->Text = L"menuStrip1";
			// 
			// tsmi_MainMenu
			// 
			this->tsmi_MainMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->tsmi_AddNewText,
					this->tsmi_ShowHighscore, this->tsmi_Exit
			});
			this->tsmi_MainMenu->Name = L"tsmi_MainMenu";
			this->tsmi_MainMenu->Size = System::Drawing::Size(50, 20);
			this->tsmi_MainMenu->Text = L"Menü";
			// 
			// tsmi_AddNewText
			// 
			this->tsmi_AddNewText->Name = L"tsmi_AddNewText";
			this->tsmi_AddNewText->Size = System::Drawing::Size(167, 22);
			this->tsmi_AddNewText->Text = L"Text Hinzufuegen";
			this->tsmi_AddNewText->Click += gcnew System::EventHandler(this, &Hauptfenster::tsmi_AddNewText_Click);
			// 
			// tsmi_ShowHighscore
			// 
			this->tsmi_ShowHighscore->Name = L"tsmi_ShowHighscore";
			this->tsmi_ShowHighscore->Size = System::Drawing::Size(167, 22);
			this->tsmi_ShowHighscore->Text = L"Highscore";
			this->tsmi_ShowHighscore->Click += gcnew System::EventHandler(this, &Hauptfenster::tsmi_ShowHighscore_Click);
			// 
			// tsmi_Exit
			// 
			this->tsmi_Exit->Name = L"tsmi_Exit";
			this->tsmi_Exit->Size = System::Drawing::Size(167, 22);
			this->tsmi_Exit->Text = L"Beenden";
			this->tsmi_Exit->Click += gcnew System::EventHandler(this, &Hauptfenster::tsmi_Exit_Click);
			// 
			// tsmi_Questionmark
			// 
			this->tsmi_Questionmark->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->tsmi_Help,
					this->tsmi_Info
			});
			this->tsmi_Questionmark->Name = L"tsmi_Questionmark";
			this->tsmi_Questionmark->Size = System::Drawing::Size(24, 20);
			this->tsmi_Questionmark->Text = L"\?";
			// 
			// tsmi_Help
			// 
			this->tsmi_Help->Name = L"tsmi_Help";
			this->tsmi_Help->Size = System::Drawing::Size(99, 22);
			this->tsmi_Help->Text = L"Hilfe";
			this->tsmi_Help->Click += gcnew System::EventHandler(this, &Hauptfenster::tsmi_Help_Click);
			// 
			// tsmi_Info
			// 
			this->tsmi_Info->Name = L"tsmi_Info";
			this->tsmi_Info->Size = System::Drawing::Size(99, 22);
			this->tsmi_Info->Text = L"Info";
			this->tsmi_Info->Click += gcnew System::EventHandler(this, &Hauptfenster::tsmi_Info_Click);
			// 
			// Hauptfenster
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(631, 321);
			this->Controls->Add(this->menuStrip_Auswahl);
			this->Controls->Add(this->panel_Main);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip_Auswahl;
			this->MaximizeBox = false;
			this->Name = L"Hauptfenster";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"TypeRacer";
			this->panel_Main->ResumeLayout(false);
			this->panel_View->ResumeLayout(false);
			this->panel_View->PerformLayout();
			this->panel_Control->ResumeLayout(false);
			this->panel_Control->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->menuStrip_Auswahl->ResumeLayout(false);
			this->menuStrip_Auswahl->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// Event Methoden
	private: System::Void button_Start_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void button_Stop_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void button_Reset_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void button_ChangeText_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void timer_Countdown_Tick(System::Object^ sender, System::EventArgs^ e);

	private: System::Void timer_CalcValues_Tick(System::Object^ sender, System::EventArgs^ e);

	private: System::Void textBox_Input_TextChanged(System::Object^ sender, System::EventArgs^ e);

	private: System::Void textBox_Input_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);

		   //tsmi = toolStripMenuItem
	private: System::Void tsmi_Exit_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void tsmi_AddNewText_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void tsmi_ShowHighscore_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void tsmi_Help_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void tsmi_Info_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void comboBox_Texts_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);

		   //Methoden mit ausgelagerten Funktionalitäten
	private: System::Void initializeNewGame(InitText value);

	private: System::Void getCurrentText(InitText value);

	private: System::Void manageRichTextBoxOneLine();

	private: System::Void manageRichTextBoxCurrentText();

	private: System::Void manageButtons(bool bStart, bool bStop, bool bReset);

	private: System::Void addNewHighscore();

	private: System::Void fillComboBox();
};
}
