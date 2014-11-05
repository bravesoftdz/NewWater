//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CreateJBBTThread.h"
#include "SDIMAIN.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TCreatJBBTThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TCreateJBBTThread::TCreateJBBTThread(bool CreateSuspended,
												TcxButton* CSBTN,
                                                TcxButton* JEBTN,
                                                TcxButton* JBBTN,
                                                TcxButton* EBTN,
                                                TcxComboBox *JBComboBox,
                                                TcxCheckGroup *JBCheckGroup,
                                                TcxProgressBar* JBProBar,
                                                TADOQuery* JBADOQ,
                                				TADOQuery* JBInADOQ) : TThread(CreateSuspended)
{
	ValidCSBTN =CSBTN;
    ValidJEBTN = JEBTN;
    ValidJBBTN = JBBTN;
    ValidEBTN = EBTN;
    ValidJBComboBox = JBComboBox;
    ValidJBCheckGroup = JBCheckGroup;
    ValidJBProBar = JBProBar;
    ValidJBADOQ = JBADOQ;
    ValidJBInADOQ = JBInADOQ;
}
//---------------------------------------------------------------------------
void __fastcall TCreateJBBTThread::Execute()
{
	//---- Place thread code here ----
	ValidCSBTN->Enabled = false;
    ValidJEBTN->Enabled = false;
    ValidJBBTN->Enabled = false;
    ValidEBTN->Enabled = false;

    String checksqlstr = "select count(*) as testcns from BTTemp2";
    ValidJBADOQ->Close();
    ValidJBADOQ->SQL->Clear();
    ValidJBADOQ->SQL->Add(checksqlstr);
    ValidJBADOQ->Open();
    if(ValidJBADOQ->FieldByName("testcns")->AsInteger>0)
    {
        if(IDOK == MessageBox(SDIAppForm->Handle, "ϵͳ�д����ϴ�������δ�´��Ĳ���,��������ɽ�ɾ���ϴ����ɵĲ���!", "Error",
        						MB_OKCANCEL|MB_ICONERROR))
        {
        	String delsqlstr = "delete from BTTemp2";
            ValidJBADOQ->Close();
            ValidJBADOQ->SQL->Clear();
            ValidJBADOQ->SQL->Add(delsqlstr);
            ValidJBADOQ->ExecSQL();
            ValidJBADOQ->Close();
            ValidJBADOQ->SQL->Clear();
            ValidJBADOQ->SQL->Add("select * from BTTemp2");
            if(!ValidJBADOQ->IsEmpty())
            {
            	MessageBox(SDIAppForm->Handle, "�޷�ɾ��һ��������δ�´��Ĳ������޷��������ɲ���!",
                			"Error", MB_OK|MB_ICONERROR);
                ValidCSBTN->Enabled = true;
                ValidJEBTN->Enabled = true;
                ValidJBBTN->Enabled = true;
                ValidEBTN->Enabled = true;
                ValidJBADOQ->Close();
                return;
            }
            ValidJBADOQ->Close();
        }
        else
        {
            ValidJBADOQ->Close();
            ValidCSBTN->Enabled = true;
            ValidJEBTN->Enabled = true;
            ValidJBBTN->Enabled = true;
            ValidEBTN->Enabled = true;
            return;
        }
    }

    String allcardsqlstr = "select * from CARD where ZT='����' order by KH asc";
    ValidJBADOQ->Close();
    ValidJBADOQ->SQL->Clear();
    ValidJBADOQ->SQL->Add(allcardsqlstr);
    ValidJBADOQ->Open();
    if(!ValidJBADOQ->IsEmpty())
    {
		insertsqlstr = "insert into BTTemp2 values(:BH,:KH,:Bonus,:ZW,:CreateDate,:January,:February,:March,:April,:May,:June,:July,:August,:September,:October,:November,:December,:UserName)";  //:January,:February,:March,:April,:May,:June,:July,:August,:September,:October,:November,:December,
/*        for (int i = 0; i < BTGmonthArraylen; i++)
        {
        	insertsqlstr += BTGmonthArray[i];
            if(i != (BTGmonthArraylen-1))
            	insertsqlstr += ",:";
        }
        insertsqlstr += ")";      */
        BTCreatetimestr = DateTimeToStr(Now());

        int allrec = ValidJBADOQ->RecordCount;
        int currentrec = 0;

        ValidJBADOQ->First();
        ValidJBProBar->Position = 0;
        while(!ValidJBADOQ->Eof)
        {
        	Synchronize(CreateOneBonusFunc);
            currentrec++;
            ValidJBProBar->Position = currentrec*100/allrec;
            ValidJBADOQ->Next();
        }
    }
    else
    {
        MessageBox(SDIAppForm->Handle, "ϵͳû�п�Ƭ���ã������޷�����ְ����!", "Error", MB_OK|MB_ICONERROR);
    }
    ValidJBADOQ->Close();

    MessageBox(SDIAppForm->Handle, "����ְ�����ɹ�!", "Successfully", MB_OK|MB_ICONINFORMATION);

    ValidCSBTN->Enabled = true;
    ValidJEBTN->Enabled = true;
    ValidJBBTN->Enabled = true;
    ValidEBTN->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TCreateJBBTThread::CreateOneBonusFunc()
{
	int Bonus = 0;
	String BHstr = ValidJBADOQ->FieldByName("BH")->AsAnsiString.Trim();
	int KH = ValidJBADOQ->FieldByName("KH")->AsInteger;
	String ZWstr = ValidJBADOQ->FieldByName("ZW")->AsAnsiString.Trim();
	String tmpzwstr = ZWstr;
	String opnamestr = OperatorName;

    int bonustag = -1;
    for(int i = 0; i < JBNameArraylen; i++)
	{
		tmpzwstr = ZWstr;
		if(0 == strcmp(JBNameArray[i], tmpzwstr.t_str()))
			bonustag = i;
    }

	if(bonustag != -1)
    {
    	Bonus = BTGArray[bonustag]*BTGmonthArraylen;
        ValidJBInADOQ->Close();
        ValidJBInADOQ->SQL->Clear();
		ValidJBInADOQ->SQL->Add(insertsqlstr);
        ValidJBInADOQ->Parameters->ParamByName("BH")->Value = BHstr;
        ValidJBInADOQ->Parameters->ParamByName("KH")->Value = KH;
        ValidJBInADOQ->Parameters->ParamByName("Bonus")->Value = Bonus;
		ValidJBInADOQ->Parameters->ParamByName("ZW")->Value = ZWstr;
        ValidJBInADOQ->Parameters->ParamByName("CreateDate")->Value = BTCreatetimestr;


		ValidJBInADOQ->Parameters->ParamByName("January")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("February")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("March")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("April")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("May")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("June")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("July")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("August")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("September")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("October")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("November")->Value = 0;
        ValidJBInADOQ->Parameters->ParamByName("December")->Value = 0;

		for (int i = 0; i < BTGmonthArraylen; i++)
        {
        	ValidJBInADOQ->Parameters->ParamByName(BTGmonthArray[i])->Value = 1;
		}
		ValidJBInADOQ->Parameters->ParamByName("UserName")->Value = opnamestr;

		ValidJBInADOQ->ExecSQL();
    }
    return;
}
