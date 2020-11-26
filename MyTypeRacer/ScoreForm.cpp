#include "ScoreForm.h"


// Auslesen der Datenbank zu dem entsprechenden Text

System::Void MyTypeRacer::ScoreForm::button_Close_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Close();
}

System::Void MyTypeRacer::ScoreForm::comboBox_Texts_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{	
	// Feld Leeren
	for (int i = 0; i < this->dataGridView->Rows->Count ; i++)
	{
		this->dataGridView->Rows->RemoveAt(i);
		i--;
		while (this->dataGridView->Rows->Count == 0)
			break;
	}

	SqlConnection^ connection = gcnew SqlConnection(this->connectionString);
	SqlCommand^ sqlCommand;

	int index = this->comboBox_Texts->SelectedIndex;
	try
	{
		connection->Open();
		sqlCommand = gcnew SqlCommand("select top 10 * from Score where TextID = " + this->list_textIDs[index] + " order by WPM desc", connection);
		SqlDataReader^ dataReader = sqlCommand->ExecuteReader();
		int count = 1;
		while (dataReader->Read())
		{
			this->dataGridView->Rows->Add(count, dataReader["Name"], dataReader["WPM"], dataReader["Time"], dataReader["Errors"]);
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

System::Void MyTypeRacer::ScoreForm::fillComboBox()
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
			this->list_textIDs->Add(Convert::ToInt32(dataReader["TextID"]));
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
