//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GSExportThread.h"
#include "GSQForm.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TGSExportThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TGSExportThread::TGSExportThread(bool CreateSuspended,
											TcxProgressBar* progress,
                                            TADOQuery* Query,
                                            TcxButton* EXBTN,
                                            TcxButton* PreBTN,
                                            TcxButton* EBTN,
                                            TcxButton* QBTN,
                                            String savepath,
                                            String KHstr,
                                            String BHstr,
                                            String XMstr,
                                            String CZYstr) : TThread(CreateSuspended)
{
	Validprogress = progress;
    ValidQuery = Query;
    ValidEXBTN = EXBTN;
    ValidPreBTN = PreBTN;
    ValidEBTN = EBTN;
    ValidQBTN = QBTN;
    Validsavepath = savepath;
    ValidKHstr = KHstr;
    ValidBHstr = BHstr;
    ValidXMstr = XMstr;
    ValidCZYstr = CZYstr;
}
//---------------------------------------------------------------------------
void __fastcall TGSExportThread::Execute()
{
	//---- Place thread code here ----
    ValidEBTN->Enabled = false;
    ValidPreBTN->Enabled = false;
    ValidEBTN->Enabled = false;
    ValidQBTN->Enabled = false;

    Variant ExcelApp;
	try
	{
		ExcelApp = CreateOleObject("Excel.Application");
	}
	catch(...)
	{
		MessageBox(GSQFrm->Handle, "��������ϵͳ�п���û�а�װExcel��", "Error in launch Excel!", MB_OK|MB_ICONERROR);
        ValidEXBTN->Enabled = true;
        ValidPreBTN->Enabled = true;
        ValidEBTN->Enabled = true;
		return;
	}

    ValidQuery->Open();
    String DTX = "";
    String path = GlobalPath;
    String Templatepath;
    ValidQuery->First();
    int allrecord = ValidQuery->RecordCount;
    for(int i = 0; i <65531; i++)
    {
        DTX += ValidQuery->FieldByName("KH")->AsAnsiString.Trim();
        DTX += "\t";
        DTX += ValidQuery->FieldByName("BH")->AsAnsiString.Trim();
        DTX += "\t";
        DTX += ValidQuery->FieldByName("XM")->AsAnsiString.Trim();
        DTX += "\t";
        DTX += ValidQuery->FieldByName("XB")->AsAnsiString.Trim();
        DTX += "\t";
        DTX += ValidQuery->FieldByName("BM")->AsAnsiString.Trim();
        DTX += "\t";
        DTX += ValidQuery->FieldByName("BZ")->AsAnsiString.Trim();
        DTX += "\t";
        DTX += ValidQuery->FieldByName("ZW")->AsAnsiString.Trim();
        DTX += "\t";
        DTX += ValidQuery->FieldByName("gsuser")->AsAnsiString.Trim();
        DTX += "\t";
        DTX += ValidQuery->FieldByName("GSRQ")->AsAnsiString.Trim();
        DTX += "\n";
        Validprogress->Position = i*100/allrecord;
        ValidQuery->Next();
        if(ValidQuery->Eof)
            break;
    }

    Templatepath = path + "\\ExportXLSTemplate\\GSTemplate.xlt";
    ExcelApp.OlePropertyGet("workbooks").OleFunction("Open", Templatepath.t_str());
    Variant WB = ExcelApp.OlePropertyGet("ActiveWorkBook");
    Variant ST = WB.OlePropertyGet("Sheets", 1);

    //���ñ�ͷ��Ϣ
    String tmpoutstr = "";
    ST.OlePropertyGet("Cells",2,2).OlePropertySet("Value", ValidKHstr.t_str());
    ST.OlePropertyGet("Cells",2,5).OlePropertySet("Value", ValidXMstr.t_str());
    ST.OlePropertyGet("Cells",2,8).OlePropertySet("Value", DateTimeToStr(Now()).t_str());

    ST.OlePropertyGet("Cells",3,2).OlePropertySet("Value", ValidBHstr.t_str());
    ST.OlePropertyGet("Cells",3,5).OlePropertySet("Value", ValidCZYstr.t_str());


    Variant RE = ST.OlePropertyGet("Range", "A6").OleFunction("Select");
    Clipboard()->Clear();
    Clipboard()->SetTextBuf(DTX.c_str());
    ST.OleFunction("Paste");
    Clipboard()->Clear();

    ExcelApp.OlePropertyGet("Columns").OleFunction("AutoFit");
    WB.OleFunction("SaveAs", Validsavepath.t_str());
    ExcelApp.OleFunction("Quit");
    ExcelApp = Unassigned;
    Validprogress->Position = 100;
    MessageBox(GSQFrm->Handle, "��������ɵ�����", "Successfully!", MB_OK|MB_ICONINFORMATION);

    ValidEBTN->Enabled = true;
    ValidPreBTN->Enabled = true;
    ValidEBTN->Enabled = true;
    ValidQBTN->Enabled = true;
}
//---------------------------------------------------------------------------
