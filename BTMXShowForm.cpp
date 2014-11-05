//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BTMXShowForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxClasses"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxCustomData"
#pragma link "cxData"
#pragma link "cxDataStorage"
#pragma link "cxDBData"
#pragma link "cxEdit"
#pragma link "cxFilter"
#pragma link "cxGraphics"
#pragma link "cxGrid"
#pragma link "cxGridCustomTableView"
#pragma link "cxGridCustomView"
#pragma link "cxGridDBTableView"
#pragma link "cxGridLevel"
#pragma link "cxGridTableView"
#pragma link "cxGroupBox"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxProgressBar"
#pragma link "cxStyles"
#pragma link "cxTextEdit"
#pragma link "dxSkinBlack"
#pragma link "dxSkinBlue"
#pragma link "dxSkinCaramel"
#pragma link "dxSkinCoffee"
#pragma link "dxSkinDarkRoom"
#pragma link "dxSkinDarkSide"
#pragma link "dxSkinFoggy"
#pragma link "dxSkinGlassOceans"
#pragma link "dxSkiniMaginary"
#pragma link "dxSkinLilian"
#pragma link "dxSkinLiquidSky"
#pragma link "dxSkinLondonLiquidSky"
#pragma link "dxSkinMcSkin"
#pragma link "dxSkinMoneyTwins"
#pragma link "dxSkinOffice2007Black"
#pragma link "dxSkinOffice2007Blue"
#pragma link "dxSkinOffice2007Green"
#pragma link "dxSkinOffice2007Pink"
#pragma link "dxSkinOffice2007Silver"
#pragma link "dxSkinPumpkin"
#pragma link "dxSkinsCore"
#pragma link "dxSkinscxPCPainter"
#pragma link "dxSkinsDefaultPainters"
#pragma link "dxSkinSeven"
#pragma link "dxSkinSharp"
#pragma link "dxSkinSilver"
#pragma link "dxSkinSpringTime"
#pragma link "dxSkinStardust"
#pragma link "dxSkinSummer2008"
#pragma link "dxSkinValentine"
#pragma link "dxSkinXmas2008Blue"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
TBTMXShowFRM *BTMXShowFRM;
//---------------------------------------------------------------------------
__fastcall TBTMXShowFRM::TBTMXShowFRM(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBTMXShowFRM::FormShow(TObject *Sender)
{
	XFMXADOQuery->Open();
    if(!XFMXADOQuery->IsEmpty()&&XFMXADOQuery->RecordCount<=65500)
    {
    	DataGridDBTV->DataController->DataSource = XFMXDataSource;
        DataGridDBTV->ClearItems();

        TcxGridDBColumn* KHCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* BHCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* XMCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* BMCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* ZWCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* SFYECol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* SFJECol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* SYCSCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* JYNOCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* CTNAMECol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* SFLXCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* SFRQCol = DataGridDBTV->CreateColumn();

        KHCol->Caption = "����";
        KHCol->MinWidth = 90;
        KHCol->DataBinding->FieldName = "KH";
        BHCol->Caption = "���";
        BHCol->MinWidth = 90;
        BHCol->DataBinding->FieldName = "BH";
        XMCol->Caption = "����";
        XMCol->MinWidth = 70;
        XMCol->DataBinding->FieldName = "UName";
        BMCol->Caption = "����";
        BMCol->MinWidth = 80;
        BMCol->DataBinding->FieldName = "BUMEN";
        ZWCol->Caption = "ְ��";
        ZWCol->MinWidth = 80;
        ZWCol->DataBinding->FieldName = "ZW";
        SFYECol->Caption = "�����";
        SFYECol->MinWidth = 70;
        SFYECol->DataBinding->FieldName = "SF_YE";
		SFJECol->Caption = "�������";
		SFJECol->MinWidth = 60;
        SFJECol->DataBinding->FieldName = "SFJE";
        SYCSCol->Caption = "ʹ�ô���";
        SYCSCol->MinWidth = 60;
        SYCSCol->DataBinding->FieldName = "SYCS";
        JYNOCol->Caption = "����";
        JYNOCol->MinWidth = 50;
        JYNOCol->DataBinding->FieldName = "JYNO";
        CTNAMECol->Caption = "����";
        CTNAMECol->MinWidth = 100;
        CTNAMECol->DataBinding->FieldName = "CTNAME";
        SFLXCol->Caption = "��������";
        SFLXCol->MinWidth = 60;
        SFLXCol->DataBinding->FieldName = "SFLX";
        SFRQCol->Caption = "��������";
        SFRQCol->MinWidth = 140;
        SFRQCol->DataBinding->FieldName = "SFRQ";
	}
}
//---------------------------------------------------------------------------
void __fastcall TBTMXShowFRM::XFMXExportBTNClick(TObject *Sender)
{
	if(!XFMXADOQuery->IsEmpty())
    {
    	ADOQInThread->Close();
        ADOQInThread->SQL->Clear();
//		ADOQInThread->SQL = XFMXADOQuery->SQL;
		ADOQInThread->SQL->Add(allsqlstr);
		if(SaveDialog->Execute())
		{
			if(FileExists(SaveDialog->FileName+".xls"))
			{
				throw(Exception("��Ŀ¼�´���ͬ���ļ��������������ļ�����"));
                return;
			}
			else
			{
				String savename = SaveDialog->FileName;
				savename += ".xls";
				TBTMXInfoExportThread* ETXThread = new TBTMXInfoExportThread(true,
                															 XFMXExportProgressBar,
                                                                             ADOQInThread,
                                                                             XFMXExportBTN,
                                                                             PreviewBTN,
                                                                             XFMXExitBTN,
                                                                             savename,
                                                                             BeginDateTimeStr,
																			 EndDateTimeStr,
																			 AllXFTextEdit->Text,
																			 AllCSTextEdit->Text,
                                                                             tag,
                                                                             CZYStr);
            	if(ETXThread)
				{
                	ETXThread->Resume();
				}
            }
        }
    }
	else
	{
		MessageBox(this->Handle, "û�пɵ�����Ϣ��", "No Record Error!", MB_OK|MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall TBTMXShowFRM::PreviewBTNClick(TObject *Sender)
{
	RePortADOQuery->Close();
	RePortADOQuery->SQL->Clear();
	RePortADOQuery->SQL->Add(allsqlstr);
	RePortADOQuery->Open();

	String temppath = GlobalPath;
	if(1 == tag)
	{
		temppath += "\\PreviewFR3\\BTDMXPreview.fr3";
	}
	if(0 == tag)
	{
		temppath += "\\PreviewFR3\\BTXMXPreview.fr3";
    }
    frxXFMXReport->LoadFromFile(temppath.t_str(), true);

    ((TfrxMemoView*)frxXFMXReport->FindObject("BBCZYMemo"))->Text = CZYStr.t_str();
	((TfrxMemoView*)frxXFMXReport->FindObject("XFZEMemo"))->Text = "��" + AllXFTextEdit->Text;
	((TfrxMemoView*)frxXFMXReport->FindObject("XFZCSMemo"))->Text = AllCSTextEdit->Text.t_str();
    ((TfrxMemoView*)frxXFMXReport->FindObject("QSRQMemo"))->Text = BeginDateTimeStr.t_str();
    ((TfrxMemoView*)frxXFMXReport->FindObject("JZRQMemo"))->Text = EndDateTimeStr.t_str();
    ((TfrxMemoView*)frxXFMXReport->FindObject("SCRQMemo"))->Text = DateTimeToStr(Now()).t_str();

    ((TfrxMemoView*)frxXFMXReport->FindObject("KH"))->DataField = "KH";
    ((TfrxMemoView*)frxXFMXReport->FindObject("BH"))->DataField = "BH";
    ((TfrxMemoView*)frxXFMXReport->FindObject("XM"))->DataField = "UNAME";
    ((TfrxMemoView*)frxXFMXReport->FindObject("BM"))->DataField = "BUMEN";
    ((TfrxMemoView*)frxXFMXReport->FindObject("SFYE"))->DataField = "SF_YE";
    ((TfrxMemoView*)frxXFMXReport->FindObject("SFJE"))->DataField = "SFJE";
    ((TfrxMemoView*)frxXFMXReport->FindObject("SYCS"))->DataField = "SYCS";
    ((TfrxMemoView*)frxXFMXReport->FindObject("JYNO"))->DataField = "JYNO";
    ((TfrxMemoView*)frxXFMXReport->FindObject("CT"))->DataField = "CTNAME";
    ((TfrxMemoView*)frxXFMXReport->FindObject("SFLX"))->DataField = "SFLX";
    ((TfrxMemoView*)frxXFMXReport->FindObject("SFRQ"))->DataField = "SFRQ";

	frxXFMXReport->ShowReport(true);
}
//---------------------------------------------------------------------------
void __fastcall TBTMXShowFRM::XFMXExitBTNClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

