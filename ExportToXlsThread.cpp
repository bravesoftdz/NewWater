//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ExportToXlsThread.h"
#include "GlobalParameter.h"
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
//      void __fastcall TExportToXlsThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TExportToXlsThread::TExportToXlsThread(bool CreateSuspended,
												  TcxProgressBar* progress,
												  TADOQuery* Query,
												  TcxButton* BTN,
												  TcxButton* EBTN,
												  String filename,
												  String Tagname) : TThread(CreateSuspended)
{
	ExportProgress = progress;
	ExportQuery = Query;
	ExportBTN = BTN;
	ExitBTN = EBTN;
	ExportFileName = filename;
	TableName = Tagname;
}
//---------------------------------------------------------------------------

void __fastcall TExportToXlsThread::Execute()
{
	//---- Place thread code here ----
	ExitBTN->Enabled = false;
	ExportQuery->Open();

	Variant ExcelApp;
	try
	{
		ExcelApp = CreateOleObject("Excel.Application");
	}
	catch(...)
	{
		MessageBox(SDIAppForm->Handle, "��������ϵͳ�п���û�а�װExcel��", "Error in launch Excel!", MB_OK|MB_ICONERROR);
		ExportQuery->Close();
		ExportBTN->Enabled = false;
		ExitBTN->Enabled = true;
		return;
	}

	if(!ExportQuery->IsEmpty())
	{
//		MessageBox(this->Handle, DTX.t_str(), "Data", MB_OK);  �����оͻ������룬����֣�
		String DTX = "";
		String path = GlobalPath;
		String Templatepath;
		//������Ϣ����
		if("Section" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("DM")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BUMEN")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\SectionTemplate.xlt";
	   //		MessageBox(SDIAppForm->Handle, Templatepath.t_str(), "out", MB_OK);

			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//�༶��Ϣ����
		if("Class" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("DM")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BUMEN")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BANBIE")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\ClassTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//�����Ϣ����
		if("Group" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("DM")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BUMEN")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BANBIE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("ZUBIE")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\GroupTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//��Ƭ��Ϣ����
		if("Card" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("BH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("KH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BKH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("XM")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("XB")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFZH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BM")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BZ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("ZB")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("ZW")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("JB")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("RQ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("TKRQ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("YJ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("TYJ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("ZT")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GRMM")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SF_YE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFYEDT")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SYCS")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("FKSK")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SF_FL")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GLF")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("FKJE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("TKJE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SF_KL")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("USERNAME")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("PKEY")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\CardTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//��ȡ����Ϣ����
		if("CK" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("bh")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("kh")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("sf_ye")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("sf_fl")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("ckxj")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("glf")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("ckje")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("sycs")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("sfrq")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("jyno")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("gzzid")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("sflx")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("CZY")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("pkey")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\CKTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//��ʧ��Ϣ����
		if("GS" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("BH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("KH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GSRQ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("USERNAME")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\GSTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//������Ϣ����
		if("FL" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("DM")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("FL")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\SFFLTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//Pos������Ϣ����
		if("POSPARAM" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("JH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("STID")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("STNAME")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GZZID")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GZZMC")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("CONNECT")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFJPORT")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("MAXXF")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("PASSWORD")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFJLX")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("JX")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("MAXZZZE")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\PosParTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//����վ��Ϣ����
		if("Station" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("GZZID")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GZZMC")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SY")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\StationTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//ʳ����Ϣ����
		if("ST" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("STID")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("STNAME")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\STNameTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//ϵͳ������Ϣ����
		if("XTSET" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("SYSID")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("INITDATE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("INIT")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("ICTYPE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("FKYJ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("TKYJ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("DWMC")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("DWMM")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("MAXKH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BFPATH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("BFRQ")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\SysSetTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//ϵͳ�û���Ϣ����
		if("SYSUSER" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("USERID")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("USERNAME")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("PASSWORD")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GROUPID")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GROUPNAME")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\SysUserTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

		//������ϸ��Ϣ����
		if("MX" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("BH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("KH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SF_YE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFJE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SYCS")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFRQ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("JYNO")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GZZID")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFLX")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("CZY")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SCRQ")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\MXTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
		}

        //������Ϣ����
		if("ERRDATA" == TableName)
		{
			ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
				DTX += ExportQuery->FieldByName("BH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("KH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SF_YE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFJE")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SYCS")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFRQ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("JYNO")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("GZZID")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SFLX")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("ERRMSG")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("SCRQ")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("PKEY")->AsAnsiString.Trim();
				DTX += "\n";
				ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
					break;
			}
			Templatepath = path + "\\ExportTemplate\\ERRDATATemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
        }

        //��������Ϣ����
        if("BTJB" == TableName)
        {
        	ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
            	DTX += ExportQuery->FieldByName("BH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("KH")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("Bonus")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("CreateDate")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("UserName")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("DownDate")->AsAnsiString.Trim();
				DTX += "\n";
            	ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
                	break;
            }
            Templatepath = path + "\\ExportXLSTemplate\\BTJBTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
        }

        //���Ѵ���������Ϣ����
        if("BTCS" == TableName)
        {
        	ExportQuery->First();
			int allrecord = ExportQuery->RecordCount;
			for(int i = 0; i < 65530; i++)
			{
            	DTX += ExportQuery->FieldByName("BH")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("KH")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("Bonus")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("ZW")->AsAnsiString.Trim();
				DTX += "\t";
				DTX += ExportQuery->FieldByName("CreateDate")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("February")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("March")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("April")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("May")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("June")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("July")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("August")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("September")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("October")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("November")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("December")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("UserName")->AsAnsiString.Trim();
				DTX += "\t";
                DTX += ExportQuery->FieldByName("DownDate")->AsAnsiString.Trim();
				DTX += "\n";
            	ExportProgress->Position = i*100/allrecord;
				ExportQuery->Next();
				if(ExportQuery->Eof)
                	break;
            }
            Templatepath = path + "\\ExportXLSTemplate\\BTCSTemplate.xlt";
			ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
        }

		Variant WB = ExcelApp.OlePropertyGet("ActiveWorkBook");

		Variant ST = WB.OlePropertyGet("Sheets", 1);

		Variant RE = ST.OlePropertyGet("Range", "A2").OleFunction("Select");

		Clipboard()->Clear();
		Clipboard()->SetTextBuf(DTX.c_str());
		ST.OleFunction("Paste");
		Clipboard()->Clear();

		ExcelApp.OlePropertyGet("Columns").OleFunction("AutoFit");

		WB.OleFunction("SaveAs", ExportFileName.t_str());

		ExcelApp.OleFunction("Quit");

		ExcelApp = Unassigned;

		ExportQuery->Close();

        ExportProgress->Position = 100;
		MessageBox(SDIAppForm->Handle, "��������ɵ�����", "Successfully!", MB_OK|MB_ICONINFORMATION);
		ExportProgress->Position = 0;
		ExportBTN->Enabled = false;
		ExitBTN->Enabled = true;
		return;
	}
	else
	{
		MessageBox(SDIAppForm->Handle, "����û�з��ϲ�ѯ���������ϣ�", "Error in Query!", MB_OK|MB_ICONERROR);
		ExcelApp.OleFunction("Quit");
		ExcelApp = Unassigned;
		ExportQuery->Close();
		ExportBTN->Enabled = false;
		ExitBTN->Enabled = true;
		return;
	}
}
//---------------------------------------------------------------------------
