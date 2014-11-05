//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GoonPWFRM.h"
#include "GlobalParameter.h"
#include "SDIMAIN.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGoonPWForm *GoonPWForm;
//---------------------------------------------------------------------------
__fastcall TGoonPWForm::TGoonPWForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGoonPWForm::Button1Click(TObject *Sender)
{
//�жϼ���ʹ�����룬д��
	if(!goontag)
	{
		ShowMessage("����ʹ���˼������룬���������ʹ��Ȩ�����뿪��ʹ������!");
		return;
    }
	char tmppw[12];
	memcpy(tmppw, Edit1->Text.t_str(), 12);
	for(int i = 0; i < 12; i++)
	{
		if(tmppw[i] != goonpw[i])
		{
			ShowMessage("����ʹ��������󣬳����˳�!");
			exit(1);
		}
	}
	//write dog
	unsigned char writebuf = 0x00;

	int writeoffset = 0x0044;
	int writelen = 1;
	DWORD writeretcode = RY3_Write(doghandle,writeoffset,&writebuf,writelen);
	if(writeretcode)
	{
		ShowMessage("д���ܹ����󣬳����޷�����!");
		exit(1);
	}
	ShowMessage("����ʹ��������ȷ������������ʹ��һ����!");
}
//---------------------------------------------------------------------------
void __fastcall TGoonPWForm::Button2Click(TObject *Sender)
{
//�ж�����ʹ�����룬д��
	char tmppw[12];
	memcpy(tmppw, Edit2->Text.t_str(), 12);
	for(int i = 0; i < 12; i++)
	{
		if(tmppw[i] != relvpw[i])
		{
			ShowMessage("����ʹ��������󣬳����˳�!");
			exit(1);
		}
	}
	//write dog
	unsigned char writebuf = 0x00;

	int writeoffset = 0x0045;
	int writelen = 1;
	DWORD writeretcode = RY3_Write(doghandle,writeoffset,&writebuf,writelen);
	if(writeretcode)
	{
		ShowMessage("д���ܹ����󣬳����޷�����!");
		exit(1);
	}
	ShowMessage("����ʹ��������ȷ�����ѻ�������ʹ��Ȩ!");
}
//---------------------------------------------------------------------------
void __fastcall TGoonPWForm::Button3Click(TObject *Sender)
{
	exit(1);
}
//---------------------------------------------------------------------------
void __fastcall TGoonPWForm::FormShow(TObject *Sender)
{
	Edit1->Text = "";
	Edit2->Text = "";
}
//---------------------------------------------------------------------------
