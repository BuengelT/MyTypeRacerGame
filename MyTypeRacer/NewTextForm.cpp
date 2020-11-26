#include "NewTextForm.h"

System::Void MyTypeRacer::NewTextForm::button_Reset_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->textBox_NameOfText->Text = "";
	this->textBox_TextContent->Text = "";
}

System::Void MyTypeRacer::NewTextForm::button_AddToDatabase_Click(System::Object^ sender, System::EventArgs^ e)
{
	SqlConnection^ connection = gcnew SqlConnection(this->connectionString);
	SqlCommand^ sqlCommand;
	String^ description = "";
	if (String::IsNullOrEmpty(this->textBox_NameOfText->Text))
	{
		MessageBox::Show("Das Feld 'Text Bezeichnung' darf nicht leer Sein!", "Error");
		return System::Void();
	}
	else
	{
		description = this->textBox_NameOfText->Text;
	}

	String^ textInput = "";
	if (String::IsNullOrEmpty(this->textBox_TextContent->Text))
	{
		MessageBox::Show("Das Feld für den Text darf nicht leer Sein!", "Error");
		return System::Void();
	}
	else
	{
		textInput = this->textBox_TextContent->Text;
	}

	try
	{
		connection->Open();
		sqlCommand = gcnew SqlCommand("select count(*) from Text", connection);
		int ID = Convert::ToInt32(sqlCommand->ExecuteScalar());
		ID++;

		sqlCommand = gcnew SqlCommand("insert into Text values(" + ID + ",'" + description + "','" + textInput + "')", connection);
		sqlCommand->ExecuteNonQuery();

	}
	catch (Exception ^ e)
	{
		MessageBox::Show(e->Message, "Error");
	}
	connection->Close();
}

System::Void MyTypeRacer::NewTextForm::button_Close_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Close();
}
