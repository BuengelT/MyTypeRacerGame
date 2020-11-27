#include "Hauptfenster.h"

//Event Methoden
System::Void MyTypeRacer::Hauptfenster::button_Start_Click(System::Object^ sender, System::EventArgs^ e)
{
	//Countdown Starten
	this->timer_Countdown->Enabled = true;
	//Fokus setzten
	this->textBox_Input->Focus();

	//Button Management
	manageButtons(false, true, false);
}

System::Void MyTypeRacer::Hauptfenster::button_Stop_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->timer_CalcValues->Stop();
	this->timer_Countdown->Stop();
	this->textBox_Input->ReadOnly = true;

	//Button Management
	manageButtons(true, false, true);
}

System::Void MyTypeRacer::Hauptfenster::button_Reset_Click(System::Object^ sender, System::EventArgs^ e)
{
	button_Stop_Click(nullptr, nullptr);
	initializeNewGame(Hauptfenster::InitText::keep);
}

System::Void MyTypeRacer::Hauptfenster::button_ChangeText_Click(System::Object^ sender, System::EventArgs^ e)
{
	button_Stop_Click(nullptr, nullptr);
	initializeNewGame(Hauptfenster::InitText::random);
}

System::Void MyTypeRacer::Hauptfenster::timer_Countdown_Tick(System::Object^ sender, System::EventArgs^ e)
{
	if (this->int_countdownValue > 0)
	{
		this->int_countdownValue--;
		this->label_CountDown->Text = this->int_countdownValue.ToString();
	}
	if (this->int_countdownValue == 0)
	{
		this->timer_CalcValues->Start();
		this->timer_Countdown->Stop();
		this->textBox_Input->ReadOnly = false;
	}
}

System::Void MyTypeRacer::Hauptfenster::timer_CalcValues_Tick(System::Object^ sender, System::EventArgs^ e)
{
	this->int_timeSpentSec++;
	this->label_Time->Text = this->int_timeSpentSec.ToString();

	//Berechnung der WPM
	this->label_WPM->Text = ((this->int_keyStrokes / 5.0) / (this->int_timeSpentSec / 60.0)).ToString("0");

	this->label_Errors->Text = (((float)(this->int_keyStrokes - this->int_Errors) / (float)this->int_keyStrokes) * 100).ToString("0.00");
}

System::Void MyTypeRacer::Hauptfenster::textBox_Input_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	// pruefen ob die TextBoxInput dem currentWord entspricht
	if (this->textBox_Input->Text == this->string_CurrentWord)
	{		
		// Wenn ein Wort voll ist, dann wird der counter inkrementiert
		this->int_wordProgress++;
		this->label_Words->Text = Convert::ToString(this->int_wordProgress);

		if (this->int_wordProgress <= this->array_CurrentText->Length)
		{
			//wenn das letzte Wort erreicht ist, ist wordProgess == fullTextArray->Length
			if (this->int_wordProgress == this->array_CurrentText->Length)
			{
				//textBoxInput leeren, schwaerzen und Readonly
				this->textBox_Input->Text = "";
				this->textBox_Input->ReadOnly = true;
				this->textBox_Input->BackColor = System::Drawing::Color::Green;

				//textBoxOneLine leeren
				this->richTextBox_OneLine->Text = "";
				this->richTextBox_CurrentText->Text = this->string_CurrentText;

				// Das letzte mal den  Fortschrittbalken aktualisieren
				this->progressBar_Progress->PerformStep();

				// TimerCalcValues Stoppen
				this->timer_CalcValues->Stop();

				//Button management
				manageButtons(false, false, true);

				//Highscore hinzufuegen
				addNewHighscore();

				//Zum abbrechen der Bedingung Void zur�ckgeben
				return System::Void();
			}
			// currentWord neu Zuweisen
			this->string_CurrentWord = this->array_CurrentText[int_wordProgress] + " ";
			// TextBoxInput leeren			
			this->textBox_Input->Text = "";
			// Fortschrittbalken aktualisieren
			this->progressBar_Progress->PerformStep();

			manageRichTextBoxOneLine();
			manageRichTextBoxCurrentText();
		}
	}

	// TextBoxInput Rot/Gruen F�rben (wird bei jedem Buchstaben ausgefuehrt, weshalb es au�erhalb der obigen Schleife liegt)
	if (this->string_CurrentWord->StartsWith(this->textBox_Input->Text))
	{

		this->bool_ErrorBit = false;

		//Aendern der Hintergrundfabe von Input-Textbox in Gruen
		this->textBox_Input->BackColor = System::Drawing::Color::GreenYellow;

		//zuruecksetzen der Maskierung
		this->richTextBox_OneLine->SelectAll();
		this->richTextBox_OneLine->SelectionBackColor = richTextBox_OneLine->BackColor;

		// Neue Maskierung				
		this->richTextBox_OneLine->Select(0, this->textBox_Input->Text->Length);
		this->richTextBox_OneLine->SelectionBackColor = System::Drawing::Color::LightGray;
	}
	else
	{
		if (!this->bool_ErrorBit) {
			this->int_Errors++;
			this->bool_ErrorBit = true;
		}
		//Aendern der Hintergrundfabe von Input-Textbox in Rot
		this->textBox_Input->BackColor = System::Drawing::Color::Red;
	}
}

System::Void MyTypeRacer::Hauptfenster::textBox_Input_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	//Tastenanschl�ge z�hlen, aber nur wenn keine Fehler vorliegt
	if (Char::IsLetter(e->KeyChar) && !this->bool_ErrorBit) {
		this->int_keyStrokes++;
	}
}

System::Void MyTypeRacer::Hauptfenster::tsmi_Exit_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Close();
}

System::Void MyTypeRacer::Hauptfenster::tsmi_AddNewText_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!this->wForm_NewText->IsDisposed)
	{
		this->wForm_NewText->ShowDialog();
		this->wForm_NewText->Focus();
	}
	else
	{
		this->wForm_NewText = gcnew NewTextForm;
		this->wForm_NewText->ShowDialog();
		this->wForm_NewText->Focus();
	}
}

System::Void MyTypeRacer::Hauptfenster::tsmi_ShowHighscore_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!this->wForm_Score->IsDisposed)
	{
		this->wForm_Score->ShowDialog();
		this->wForm_Score->Focus();
	}
	else
	{
		this->wForm_Score = gcnew ScoreForm;
		this->wForm_Score->ShowDialog();
		this->wForm_Score->Focus();
	}
}

System::Void MyTypeRacer::Hauptfenster::tsmi_Help_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!this->wForm_Help->IsDisposed)
	{
		this->wForm_Help->ShowDialog();
		this->wForm_Help->Focus();
	}
	else
	{
		this->wForm_Help = gcnew HelpForm(this->string_Welcome);
		this->wForm_Help->ShowDialog();
		this->wForm_Help->Focus();
	}

}

System::Void MyTypeRacer::Hauptfenster::tsmi_Info_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Author: Timm B�ngel" + Environment::NewLine + Environment::NewLine
		+ "erstellt w�hrend" + Environment::NewLine
		+ "alfatraining-Kurs C++", "Info");
}

System::Void MyTypeRacer::Hauptfenster::comboBox_Texts_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{	
	initializeNewGame(Hauptfenster::InitText::select); // Select Text
}


//Methoden mit ausgelagerten Funktionalit�ten
System::Void MyTypeRacer::Hauptfenster::initializeNewGame(InitText value)
{
	this->int_Errors = 0;
	this->bool_ErrorBit = true;

	//Buttons Initialisieren
	manageButtons(true, false, false);

	// Initialisieren von allgemeingueltigen Variablen
	this->int_keyStrokes = 0;
	this->int_wordProgress = 0;

	// Initialisiere Timer Variables
	this->int_timeSpentSec = 0;

	// Reset Countdown
	this->int_countdownValue = 5;
	this->label_CountDown->Text = this->int_countdownValue.ToString();

	// Zuweisen des aktuellen Textes und arrayCurrentText initialisieren
	getCurrentText(value);

	this->array_CurrentText = this->string_CurrentText->Split(' ');

	// TextBoxCurrentText initialisieren mit CurrentText
	this->richTextBox_CurrentText->Text = this->string_CurrentText;

	// currentWord initialisieren mit arrayCurrentText Element	
	this->string_CurrentWord = this->array_CurrentText[int_wordProgress] + " ";

	// TextBoxInput Initialisieren
	this->textBox_Input->Text = "";
	this->textBox_Input->BackColor = System::Drawing::Color::White;

	// Fortschrittsbalken Initialisieren
	this->progressBar_Progress->Visible = true;
	this->progressBar_Progress->Minimum = 0;
	this->progressBar_Progress->Maximum = this->array_CurrentText->Length;
	this->progressBar_Progress->Value = 0;

	//CalcValues auf Null setzen;
	this->label_Time->Text = this->int_timeSpentSec.ToString();
	this->label_Words->Text = this->int_wordProgress.ToString();
	this->label_WPM->Text = "0";
	this->label_Errors->Text = "0,00";

	// Funktionaliteat zum F�rben der Textboxen Initialisieren
	manageRichTextBoxOneLine();
	manageRichTextBoxCurrentText();
}

System::Void MyTypeRacer::Hauptfenster::getCurrentText(InitText value)
{
	SqlConnection^ connection = gcnew SqlConnection(this->connectionString);
	SqlCommand^ sqlCommand;
	Random^ rand = gcnew Random();

	try
	{
		connection->Open();
		int index = 0;
		
		if (value == Hauptfenster::InitText::random) {
			index = rand->Next(this->list_TextIDs->Count);
		}
		else if (value == Hauptfenster::InitText::select) 		
		{
			index = this->comboBox_Texts->SelectedIndex;
		}
		else  if (value == Hauptfenster::InitText::keep)
		{
			// ich muss den index von this->list_TextIDs herausfinden, welcher this->intTextID besitzt um den aktuellen Text zu ermitteln
			// oder ich vreche einfach die Funktion mit return System::Void(); ab und mache somit auch keine DB-Abfrage
			// ich kann den Reset knopf nur dr�cken wenn bereits ein Text in der Maske ist
			return System::Void();			
		}
		this->int_TextID = Convert::ToInt32(this->list_TextIDs[index]);
	
		sqlCommand = gcnew SqlCommand("select * from Text where TextID = " + this->list_TextIDs[index], connection);
		SqlDataReader^ dataReader = sqlCommand->ExecuteReader();
		while (dataReader->Read())
		{
			this->comboBox_Texts->Text = Convert::ToString(dataReader["Description"]);
			this->string_TextDescription = Convert::ToString(dataReader["Description"]);
			this->string_CurrentText = Convert::ToString(dataReader["Text"]);
		}
		dataReader->Close();
	}
	catch (Exception ^ e)
	{
		MessageBox::Show(e->Message, "ErrorTest");
	}
	connection->Close();
}

System::Void MyTypeRacer::Hauptfenster::manageRichTextBoxOneLine()
{
	//RichTextBox verwalten
	String^ tempString = "";
	// Schleife die festlegt wie viele W�rter in der TextBox_OneLine angezeigt werden
	for (int i = this->int_wordProgress; i < (this->int_wordProgress + this->int_textBoxOneLineWords) && i < this->array_CurrentText->Length; i++)
	{
		tempString += array_CurrentText[i] + " ";
	}
	this->richTextBox_OneLine->Text = tempString;

	// Da es immer das erste Wort ist, veraendert sich die 0 nicht, lediglich die laenge des Wortes
	this->richTextBox_OneLine->Select(0, this->string_CurrentWord->Length);
	this->richTextBox_OneLine->SelectionFont = gcnew System::Drawing::Font(this->richTextBox_OneLine->Font, FontStyle::Bold);
}

System::Void MyTypeRacer::Hauptfenster::manageRichTextBoxCurrentText()
{
	// Auf Standard setzen um vorheriges Wort zu demaskieren
	this->richTextBox_CurrentText->Text = this->string_CurrentText;

	// mit dem .Net 5.0 funktioert die Select-Funktion der rtb nicht korrekt
	// das jeweilige Wort hervorheben
	//this->richTextBox_CurrentText->SelectionStart = this->int_keyStrokes + this->int_wordProgress;	
	//this->richTextBox_CurrentText->Select(this->richTextBox_CurrentText->SelectionStart, this->array_CurrentText[this->int_wordProgress]->Length); //anfang und l�nge des aktuellen wortes	
	//this->richTextBox_CurrentText->ScrollToCaret();
	//this->richTextBox_CurrentText->SelectionBackColor = System::Drawing::Color::Yellow;
}

System::Void MyTypeRacer::Hauptfenster::manageButtons(bool bStart, bool bStop, bool bReset)
{
	this->button_Start->Enabled = bStart;
	this->button_Stop->Enabled = bStop;
	this->button_Reset->Enabled = bReset;
}

System::Void MyTypeRacer::Hauptfenster::addNewHighscore()
{
	SqlConnection^ connection = gcnew SqlConnection(this->connectionString);
	SqlCommand^ sqlCommand;

	// Festlegen der SQL Parameter
	String^ name = "";
	if (this->textBox_NameInput->Text->Contains("<Ihr Name>"))
		name = "Mr. Nobody";
	else if (String::IsNullOrEmpty(this->textBox_NameInput->Text))
		name = "Mr. Nobody";
	else name = this->textBox_NameInput->Text;

	int wpm = Convert::ToInt32(this->label_WPM->Text);
	int time = this->int_timeSpentSec;
	String^ errors = this->label_Errors->Text;
	int textID = this->int_TextID;
	try
	{
		connection->Open();
		sqlCommand = gcnew SqlCommand("select max(ScoreID) from Score", connection);

		int id = 0;
		// Wenn noch keine ID vorliegt, SQL- Fehler abfangen
		if (!String::IsNullOrEmpty(sqlCommand->ExecuteScalar()->ToString()))
			id = Convert::ToInt32(sqlCommand->ExecuteScalar());
		id++;

		sqlCommand = gcnew SqlCommand("insert into Score values(" + id + ",'" + name + "'," + wpm + "," + time + ",'" + errors + "'," + textID + ")", connection);
		sqlCommand->ExecuteNonQuery();
	}
	catch (Exception ^ e)
	{
		MessageBox::Show(e->Message, "SQL-Error");
	}
	connection->Close();
}

System::Void MyTypeRacer::Hauptfenster::fillComboBox()
{
	SqlConnection^ connection = gcnew SqlConnection(this->connectionString);
	SqlCommand^ sqlCommand;

	try
	{
		connection->Open();

		sqlCommand = gcnew SqlCommand("select TextID, Description from Text order by Description asc", connection);
		SqlDataReader^ dataReader = sqlCommand->ExecuteReader();

		int count = 1;
		while (dataReader->Read())
		{
			this->list_TextIDs->Add(Convert::ToInt32(dataReader["TextID"]));
			this->comboBox_Texts->Items->Add(count + ". " + Convert::ToString(dataReader["Description"]));
			count++;
		}
		dataReader->Close();
	}
	catch (Exception ^ e)
	{
		MessageBox::Show(e->Message, "SQL-Error");
	}
	connection->Close();
}


/*Umgestellt auf DB
System::String^ MyTypeRacer::Hauptfenster::getCurrentText()
{
	Random^ rand = gcnew Random();
	array<String^>^ allTexts =
	{
		"Die Story funktioniert, dachte Mustermann, aber dann kam die Ern�chterung. Kaum Klicks, kaum Likes, kaum Feedback. Doch das lag nicht an der Geschichte. Es lag daran, wie Mustermann sie aufgeschrieben hatte.",
		"Dies hier ist ein Beispieltext �ber f�nfzig W�rter. Es dient zur Anschauung von Textl�ngen. Denn nicht jeder Shopbetreiber oder Entwickler hat eine genaue Vorstellung davon, wie ein Textumfang auf einer Anwendung wirkt. Textl�ngen mit bis zu f�nfzig W�rtern dienen meist als Kurzbeschreibung oder als Teaser-Text, der neugierig auf mehr macht.",
		"Oft ist es besser, ein Adjektiv durch ein anderes zu ersetzen, um die Aussage zu verst�rken, statt lediglich 'sehr' davor zu schreiben. Auf dem Flughafen in Kampala war es sehr warm.",
		"Ein h�ssliches Verb und au�erdem ungenau. Beamte lieben es. Seien Sie pr�ziser! Mein afrikanischer Gesch�ftspartner war gerade dabei, eine Inventur durchzuf�hren.",
		"Zu allgemein und unausgegoren. Je pr�ziser ein Satz formuliert wird, desto informativer ist er. Irgendwie h�tte ich auch mal Lust, irgendwann nach Botswana zu fahren.",
		"Das Wort Beute wurde im 8. Jahrhundert zuerst f�r ein Backbrett oder einen Backtrog und sp�ter f�r den Waldbienenstock benutzt. Trotz der fr�hen Bezeugung ist weder die Herkunft noch die Geschichte ausreichend klar. Bezeugt ist das mittelhochdeutsche Wort 'biuta' als Bienenstock und das althochdeutsche 'biutte' oder 'biot' als Backtrog oder Bienenkorb.",
		"Heidekr�uter sind immergr�ne, niederliegende Str�ucher und B�ume, die bis zu 10 Meter gro� werden k�nnen. Das Mark ist gleichm��ig, die Knospenschuppen k�nnen fehlen. Trag- und Vorbl�tter sind selten mit dem Achselspross verwachsen (recauleszent). Die Bl�tter stehen in Wirteln, selten gegenst�ndig oder verstreut.",
		"Der Menhir ist aus grauem Granit vermutlich lokalen Ursprungs, wie man durch die N�he eines Steinbruchs vermuten kann. Sein Gewicht wird auf bis zu 160 Tonnen gesch�tzt. Eine Seite wurde bearbeitet, um sie fast plan zu machen. Seine flache viereckige Basis steht auf einer Granitplattform.",
		"Auerswald entstammte einem alten Mei�ener Adelsgeschlecht mit gleichnamigem Stammhaus Auerswalde (heute ein Ortsteil von Lichtenau im Landkreis Mittelsachsen), das im Jahr 1263 urkundlich zuerst genannt wird.",
		"In Deutschland ist die Popularklage nur in Ausnahmef�llen zugelassen; normalerweise ist die Geltendmachung einer Verletzung eigener Rechte unter dem Begriff Klagebefugnis eine Voraussetzung f�r die Zul�ssigkeit einer Klage.",
		"Die Hansa war ein 1899 in Dienst gestelltes Passagierschiff der schwedischen Reederei Angfartygs AB Gotland, das 45 Jahre lang Passagiere und Fracht in einem regelm��igen Linienverkehr zwischen Stockholm und Visby auf der schwedischen Ostseeinsel Gotland bef�rderte.",
		"Das Theater der Kl�nge ist ein Musik- und Tanztheater, das am 10. Mai 1987 in D�sseldorf gegr�ndet wurde. Dieses Theater versteht sich als Ensemblekollektiv verschiedener in Gemeinschaft kreierender K�nstler.",
		"Ein G�rtel ist ein um die K�rpermitte getragenes Band oder Geflecht. Er kann dem Zusammenhalt und besseren Sitz der Kleidung, reinen Schmuck-Zwecken oder der Befestigung von Gegenst�nden dienen. In manchen F�llen dienen G�rtel Schutzzwecken oder sollen nur die Taille einengen.",
		"Die Annan Old Parish Church ist ein Kirchengeb�ude der presbyterianischen Church of Scotland in der schottischen Kleinstadt Annan in der Council Area Dumfries and Galloway. 1971 wurde das Bauwerk in die schottischen Denkmallisten in der h�chsten Denkmalkategorie A aufgenommen.",
		"Wenn Fliegen hinter Fliegen fliegen fliegen Fliegen hinter Fliegen her.",
		"Fischers Fritz fischt frische Fische.",
		"Brautkleid ist Brautkleid und Blaukraut ist Blaukraut.",
		"Als wir noch in der Wiege lagen, gab's noch keine Liegewagen. Jetzt kann man in den Wagen liegen und sich in allen Lagen wiegen. Als wir noch in der Wiege lagen, gab's noch keine Liegewagen. Jetzt kann man in den Wagen liegen und sich in allen Lagen wiegen.",
		"Am Zehnten Zehnten zehn Uhr zehn zogen zehn zahme Ziegen zehn Zentner Zucker zum Zoo.",
		"Auf den sieben Robbenklippen sitzen sieben Robbensippen, die sich in die Rippen stippen, bis sie von den Klippen kippen.",
		"Der Metzger wetzt das Metzgermesser mit des Metzgers Wetzstein. Mit des Metzgers Wetzstein wetzt der Metzger sein Metzgermesser.",
		"Der d�nne Diener tr�gt die dicke Dame durch den dicken Dreck, da dankt die dicke Dame dem d�nnen Diener, dass der d�nne Diener die dicke Dame durch den dicken Dreck getragen hat.",
		"Als Klappentext wird urspr�nglich der Text bezeichnet, der auf der zweiten Au�enseite des Schutzumschlages eines Buches steht. Bei B�chern ohne Schutzumschlag ist dieser identisch mit dem Text auf der Umschlagr�ckseite. Diese Ausf�hrung �ber Ihr Buch dient als werbender Text, der den Buchinhalt kurz umfasst, und im besten Fall zum Lesen (und zum Kauf des Buches) anregt. Meist ist dieser im heutigen Verlagswesen auch mit dem Waschzettel eines Buches identisch, der als Kurztext die Presse �ber das Buch informiert. Sie sollten auf jeden Fall gen�gend Zeit f�r diesen Text aufwenden, denn erst nachdem dieser Ihre Leser von Ihrem Buch �berzeugt hat, entscheiden sie sich im besten Fall f�r den Kauf Ihres Buches. Scheitern Ihre potentiellen Leser jedoch an einem langweiligen, schlecht geschriebenen oder irref�hrenden Klappentext, dann werden selbst Ihre Fans oder die idealen Leser Ihr Buch gar nicht erst aufschlagen. Also, selbst wenn Sie nach dem Fertigstellen Ihres Manuskripts Ihr Buch nur noch so schnell wie m�glich ver�ffentlichen wollen, �bereilen Sie diesen wichtigen letzten Schritt nicht! Ein guter Klappentext ist ebenso wichtig wie die vielf�ltigste Werbung.",
		"Der Klappentext beinhaltet meist eine Kurzzusammenfassung des Buchinhalts und eine Autorenvita, aber nat�rlich k�nnen Sie hier auch kreativ werden. Bei einem Sachbuch zum Beispiel kann man auch eine kleine Spiegelstrich-Liste einbauen, was das Buch zu bieten hat, etc. Ihrer Fantasie sind hier keine Grenzen gesetzt. Sie k�nnen diesen Klappentext als eine Art Werbebotschaft an Ihre Leser sehen, die Ihr Buch in aller K�rze von der sch�nsten Seite pr�sentiert. Sie sollten aber gleichzeitig keine falschen Versprechungen machen oder Illusionen streuen. Wenn der Klappentext mehr verspricht, als das eigentlich Buch einzuhalten imstande ist, hagelt es im Anschluss negative Rezensionen - schlechte Werbung f�r Ihr Buch. Denken Sie daran: Der Klappentext soll zuallererst die Neugier eines potenziellen Lesers entfachen, diesen zum Kauf des Buches, zum Lesen und zu m�glichen Weiterempfehlungen anregen. Der Klappentext dient daher nicht dazu, den Inhalt Ihres Buches in aller Ausf�hrlichkeit wiederzugeben. Oberstes Ziel eines guten Klappentextes ist in einem kurzen und leicht verdaulichen Text auf kurzem Raum zu zeigen, worum es in Ihrem Buch geht, welche Ziele Ihr Buch verfolgt und was das Buch f�r den Leser bereith�lt. Diese drei Schl�sselfragen sollten Sie sich auch beim Verfassen stellen: Wird aus dem Klappentext ersichtlich, worum es in meinem Buch geht? Im besten Fall erkennt der Leser auch, in welchem Stil das Buch verfasst ist. Welche Ziele verfolgt mein Buch, was soll dem Leser vermittelt werden, welche Geschichte erz�hlt werden? Und last but not least, welchen Erkenntnisgewinn hat der Leser nach der Lekt�re meines Buches? Habe ich dies bereits im Klappentext erkenntlich gemacht?",
		"Die immer als erstes aufgef�hrte Inhaltsangabe umrei�t kurz den Inhalt des Buches, zeigt die Haupthandlung in einem Roman oder stellt die wichtigsten Themenaspekte in einem Sach- oder Fachbuch vor. Dabei geht es hier nicht darum, alle Handlungsstr�nge oder Thesen in aller Detailgenauigkeit vorzustellen. Die Inhaltsangabe skizziert ein Buchprojekt lediglich kurz und verpackt diesen Inhalt in einen Neugier weckenden Kurztext. Dieser Text sollte unter keinen Umst�nden lang oder sogar langwierig werden! Verraten Sie in dieser Zusammenfassung auch nicht alle Handlungsstr�nge oder gar das Ende. Verstehen Sie diesen Text als eine Art Teaser oder Trailer zum Buch, wie dieser im Kino f�r den n�chsten Kassenrei�er eingesetzt wird. Erst durch diesen wird der Leser wirklich neugierig auf Ihr Buch und dazu angeregt, sofort mit der Lekt�re zu beginnen. Wenn Sie ihren Lesern aber an dieser Stelle schon die komplette Handlung verraten haben, wird der Buchkauf �berfl�ssig.",
		"Ein guter Klappentext ist wie ein guter Wein, er sollte gut bek�mmlich sein, sofort gute Stimmung verbreiten und Emotionen wecken. Arbeiten Sie mit ausdrucksstarken, aber nicht �bertriebenen Adjektiven. Vermeiden Sie abgegriffene Redewendungen. Idealerweise weckt der Text beim Leser Neugierde und Spannung, so dass der Griff zum Buch eine wahrscheinliche Option f�r den Leser oder die Leserin wird. Bei einem Fach- oder Sachbuch sollte das Buch die wichtigsten Thesen und Theorien des Buches zusammenfassen, �ber die der Leser im Idealfall gleich mehr wissen m�chte. Nat�rlich sollte ein Klappentext nie alles verraten, sondern Neugier sch�ren und durch eine spannende Dramatugie des Textes zur Lekt�re des ganzen Buches animieren. Das funktioniert am Besten, wenn beim Lesen des Klappentextes Gef�hle und eine Verbindung zum Leser aufgebaut wird."

	};

	int textIndex = rand->Next(allTexts->Length);
	return allTexts[textIndex];
}
*/