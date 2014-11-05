//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EMXQForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxCalendar"
#pragma link "cxClasses"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxCustomData"
#pragma link "cxData"
#pragma link "cxDataStorage"
#pragma link "cxDBData"
#pragma link "cxDropDownEdit"
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
#pragma link "cxLabel"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxMaskEdit"
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
TEMXQFrm *EMXQFrm;
//---------------------------------------------------------------------------
__fastcall TEMXQFrm::TEMXQFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEMXQFrm::EMXExitBTNClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TEMXQFrm::FormShow(TObject *Sender)
{
//	EMXBeginDateEdit->Text = "";
//    EMXEndDateEdit->Text = "";

	EMXBeginDateEdit->Date = Date();
	EMXEndDateEdit->Date = Date();

    QueryBTN->Enabled = true;
    EMXExportBTN->Enabled = false;
    PreviewBTN->Enabled = false;
    EMXExitBTN->Enabled = true;
    EMXExportProgressBar->Position = 0;
    EMXADOQuery->Close();

    DataGridDBTV->DataController->DataSource = NULL;
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
    SFJECol->Caption = "���ѽ��";
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
//---------------------------------------------------------------------------
void __fastcall TEMXQFrm::QueryBTNClick(TObject *Sender)
{
	if(!EMXBeginDateEdit->Text.IsEmpty()&&!EMXEndDateEdit->Text.IsEmpty())
    {
    	String sqlstr = "select * from MXBAK where KH is NULL and SFLX='x' and SFRQ<='";
        sqlstr += EMXEndDateEdit->Text;
        sqlstr += " 23:59:59' and SFRQ>='";
        sqlstr += EMXBeginDateEdit->Text;
        sqlstr += " 00:00:00'";

        DataGridDBTV->DataController->DataSource = NULL;
        EMXADOQuery->Close();
        EMXADOQuery->SQL->Clear();
        EMXADOQuery->SQL->Add(sqlstr);
        EMXADOQuery->Open();
        if(!EMXADOQuery->IsEmpty())
        {
        	if(EMXADOQuery->RecordCount>65500)
            {
                ShowMessage("���ϸò�ѯ�����ļ�¼��������65500�����޷�������ʾ�뵼�������޸Ĳ�ѯ����!");
                return;
            }
            DataGridDBTV->DataController->DataSource = EMXDataSource;
            BeginStr = EMXBeginDateEdit->Text + " 00:00:00";
            EndStr = EMXEndDateEdit->Text + " 23:59:59";
            CZYStr = OperatorName;
            EMXExportBTN->Enabled = true;
            PreviewBTN->Enabled = true;
        }
        else
        	ShowMessage("�޷��ϲ�ѯ�����ļ�¼!");
    }
    else
    {
        ShowMessage("������д��ѯ��ʼ�ڽ���ʱ��!");
    }
}
//---------------------------------------------------------------------------
void __fastcall TEMXQFrm::EMXExportBTNClick(TObject *Sender)
{
	if(!EMXADOQuery->IsEmpty())
    {
    	ADOQInThread->Close();
        ADOQInThread->SQL->Clear();
		ADOQInThread->SQL = EMXADOQuery->SQL;
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
                TEMXExportThread* EXThread = new TEMXExportThread(true,
                												 EMXExportProgressBar,
                                                                 ADOQInThread,
                                                                 EMXExportBTN,
                                                                 PreviewBTN,
                                                                 EMXExitBTN,
                                                                 QueryBTN,
                                                                 savename,
                                                                 BeginStr,
                                                                 EndStr,
                                                                 CZYStr);
                if(EXThread)
                {
                	EXThread->Resume();
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
void __fastcall TEMXQFrm::PreviewBTNClick(TObject *Sender)
{
	String temppath = GlobalPath;
	temppath += "\\PreviewFR3\\EMXPreview.fr3";
    frxEMXReport->LoadFromFile(temppath.t_str(), true);

    ((TfrxMemoView*)frxEMXReport->FindObject("BBCZYMemo"))->Text = CZYStr.t_str();
    ((TfrxMemoView*)frxEMXReport->FindObject("QSRQMemo"))->Text = BeginStr.t_str();
    ((TfrxMemoView*)frxEMXReport->FindObject("JZRQMemo"))->Text = EndStr.t_str();
    ((TfrxMemoView*)frxEMXReport->FindObject("SCRQMemo"))->Text = DateTimeToStr(Now()).t_str();

    ((TfrxMemoView*)frxEMXReport->FindObject("KH"))->DataField = "KH";
    ((TfrxMemoView*)frxEMXReport->FindObject("BH"))->DataField = "BH";
    ((TfrxMemoView*)frxEMXReport->FindObject("XM"))->DataField = "UNAME";
    ((TfrxMemoView*)frxEMXReport->FindObject("BM"))->DataField = "BUMEN";
    ((TfrxMemoView*)frxEMXReport->FindObject("SFYE"))->DataField = "SF_YE";
    ((TfrxMemoView*)frxEMXReport->FindObject("SFJE"))->DataField = "SFJE";
    ((TfrxMemoView*)frxEMXReport->FindObject("SYCS"))->DataField = "SYCS";
    ((TfrxMemoView*)frxEMXReport->FindObject("JYNO"))->DataField = "JYNO";
    ((TfrxMemoView*)frxEMXReport->FindObject("CT"))->DataField = "CTNAME";
    ((TfrxMemoView*)frxEMXReport->FindObject("SFLX"))->DataField = "SFLX";
    ((TfrxMemoView*)frxEMXReport->FindObject("SFRQ"))->DataField = "SFRQ";

    frxEMXReport->ShowReport(true);
}
//---------------------------------------------------------------------------
