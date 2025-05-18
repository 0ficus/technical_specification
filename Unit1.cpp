//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	InitDatabase();
}

void __fastcall TForm1::InitDatabase()
{
	FDConnection1->Params->Clear();
	FDConnection1->Params->Add("DriverID=FB");
	FDConnection1->Params->Add("Database=C:\\UNIVERSITY.FDB");
	FDConnection1->Params->Add("User_Name=SYSDBA");
	FDConnection1->Params->Add("Password=pswd");

	try {
		FDConnection1->Connected = true;
		ShowMessage("Connection to the database is successful\n");
	} catch (Exception& error) {
		ShowMessage("Connection to the database is not successful: " + error.Message);
	}

	try {
		GenerateTestData();
		InitQuery();
		InitDataSource();
		InitDBGrid();
	} catch (Exception& error) {
		ShowMessage(error.Message);
	}
}

void __fastcall TForm1::InitQuery()
{
    FDQuery1->Connection = FDConnection1;
    FDQuery1->SQL->Clear();
	FDQuery1->SQL->Text = "SELECT * FROM CLASSROOMS";
	FDQuery1->Open();
}

void __fastcall TForm1::InitDataSource()
{
	DataSource1->DataSet = FDQuery1;
}

void __fastcall TForm1::InitDBGrid()
{
	DBGrid1->DataSource = DataSource1;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::DBGrid1DblClick(TObject *Sender)
{
	int classroom_id = FDQuery1->FieldByName("ID")->AsInteger;

	TForm2* form2 = new TForm2(this);
	try {
        form2->Connect(FDConnection1);
        form2->CalculateClassroomInfo(classroom_id);
        form2->ShowModal();
	} catch (Exception& error) {
        ShowMessage("runtime error " + error.Message);
	}
	delete Form2;
}
//---------------------------------------------------------------------------

String __fastcall RandomString(size_t length)
{
	String random_string;
	int random_index;
	const String chars = "qwertyuiopasdfghjklzxcvbnm";
	try {
		for (size_t i = 0; i < length; ++i) {
			random_index = 1 + Random(chars.Length() - 1);
			random_string += chars[random_index];
		}
	} catch (Exception& error) {
		ShowMessage("Random String generation was failed: " + error.Message + " (" + IntToStr(random_index) + ")");
	}
	return random_string;
}

void __fastcall TForm1::GenerateTestData()
{
	FDConnection1->StartTransaction();
	try {
		FDQuery1->SQL->Text = "DELETE FROM LESSONS";
		FDQuery1->ExecSQL();

		FDQuery1->SQL->Text = "DELETE FROM STUDENTS";
		FDQuery1->ExecSQL();

		FDQuery1->SQL->Text = "DELETE FROM CLASSROOMS";
		FDQuery1->ExecSQL();

		const String classroom_numbers[5] = {"101", "202", "303", "404", "505"};
		for (int i = 0; i < 5; ++i) {
			FDQuery1->SQL->Text =
                "INSERT INTO CLASSROOMS (ID, NUMBER, CAPACITY) VALUES (:ID, :NUMBER, :CAPACITY)";
			FDQuery1->ParamByName("ID")->Value = i + 1;
			FDQuery1->ParamByName("NUMBER")->Value = classroom_numbers[i];
			FDQuery1->ParamByName("CAPACITY")->Value = 20 + Random(15);
			FDQuery1->ExecSQL();
		}

		const String groups[3] = {"Group A", "Group B", "Group C"};
		for (int i = 0; i < 15; ++i) {
			FDQuery1->SQL->Text =
				"INSERT INTO STUDENTS (ID, NAME, GROUP_NAME) VALUES (:ID, :NAME, :GROUP)";
			FDQuery1->ParamByName("ID")->Value = i + 1;
			FDQuery1->ParamByName("NAME")->Value = RandomString(5) + " " + RandomString(5);
			FDQuery1->ParamByName("GROUP")->Value = groups[i % 3];
			FDQuery1->ExecSQL();
		}

		const String subjects[5] = {
			"Algebra",
			"C++",
			"Cooking dumplings",
			"Rust",
			"ML"
		};
		TDateTime startDate = StrToDate("01.09.2024");
		for (int i = 0; i < 30; ++i) {
			FDQuery1->SQL->Text =
				"INSERT INTO LESSONS (ID, CLASSROOM_ID, STUDENT_ID, SUBJECT, LESSON_TIME) "
				"VALUES (:ID, :CLASSROOM_ID, :STUDENT_ID, :SUBJECT, :LESSON_TIME)";
			FDQuery1->ParamByName("ID")->Value = i + 1;
			FDQuery1->ParamByName("CLASSROOM_ID")->Value = 1 + Random(5);
			FDQuery1->ParamByName("STUDENT_ID")->Value = 1 + Random(15);
			FDQuery1->ParamByName("SUBJECT")->Value = subjects[Random(5)];

			TDateTime datetime = IncDay(startDate, Random(120));
			datetime = IncHour(datetime, 9 + Random(11));
			FDQuery1->ParamByName("LESSON_TIME")->Value = datetime;
			FDQuery1->ExecSQL();
		}

		FDConnection1->Commit();
	} catch (Exception& error) {
		FDConnection1->Rollback();
        ShowMessage("Generation of test data is failed: " + error.Message);
	}
}