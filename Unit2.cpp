//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Connect(TFDConnection* connection)
{
	FDQuery2->Connection = connection;
	DataSource2->DataSet = FDQuery2;
	DBGrid2->DataSource = DataSource2;
}

void __fastcall TForm2::CalculateClassroomInfo(int classroom_id)
{
	FDQuery2->SQL->Text =
		"SELECT STUDENTS.NAME, LESSONS.SUBJECT, LESSONS.LESSON_TIME "
		"FROM LESSONS "
		"INNER JOIN STUDENTS ON LESSONS.STUDENT_ID = STUDENTS.ID "
		"WHERE LESSONS.CLASSROOM_ID = :ID "
		"ORDER BY LESSONS.LESSON_TIME";
	FDQuery2->ParamByName("ID")->Value = classroom_id;
	FDQuery2->Open();
}
