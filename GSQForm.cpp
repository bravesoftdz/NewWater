//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GSQForm.h"
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
#pragma link "cxLabel"
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
#pragma link "cxCalendar"
#pragma link "cxDropDownEdit"
#pragma link "cxMaskEdit"
#pragma resource "*.dfm"
TGSQFrm *GSQFrm;
//---------------------------------------------------------------------------
__fastcall TGSQFrm::TGSQFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGSQFrm::GSExitBTNClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TGSQFrm::FormShow(TObject *Sender)
{
	GSExportProgressBar->Position = 0;
    KHTextEdit->Text = "";
    BHTextEdit->Text = "";
    XMTextEdit->Text = "";
    QueryBTN->Enabled = true;
    GSExportBTN->Enabled = false;
    PreviewBTN->Enabled = false;
    GSExitBTN->Enabled = true;

    GSADOQuery->Close();
	DataGridDBTV->ClearItems();

    TcxGridDBColumn* KHCol = DataGridDBTV->CreateColumn();
    TcxGridDBColumn* BHCol = DataGridDBTV->CreateColumn();
    TcxGridDBColumn* XMCol = DataGridDBTV->CreateColumn();
    TcxGridDBColumn* XBCol = DataGridDBTV->CreateColumn();
    TcxGridDBColumn* BMCol = DataGridDBTV->CreateColumn();
    TcxGridDBColumn* BZCol = DataGridDBTV->CreateColumn();
    TcxGridDBColumn* ZWCol = DataGridDBTV->CreateColumn();
    TcxGridDBColumn* GSCZYCol = DataGridDBTV->CreateColumn();
    TcxGridDBColumn* GSRQCol = DataGridDBTV->CreateColumn();

    KHCol->Caption = "����";
    KHCol->MinWidth = 90;
    KHCol->DataBinding->FieldName = "KH";
    BHCol->Caption = "���";
    BHCol->MinWidth = 90;
    BHCol->DataBinding->FieldName = "BH";
    XMCol->Caption = "����";
    XMCol->MinWidth = 70;
    XMCol->DataBinding->FieldName = "XM";
    XBCol->Caption = "�Ա�";
    XBCol->MinWidth = 40;
    XBCol->DataBinding->FieldName = "XB";
    BMCol->Caption = "����";
    BMCol->MinWidth = 100;
    BMCol->DataBinding->FieldName = "BM";
    BZCol->Caption = "�༶";
    BZCol->MinWidth = 80;
    BZCol->DataBinding->FieldName = "BZ";
    ZWCol->Caption = "ְ��";
    ZWCol->MinWidth = 60;
    ZWCol->DataBinding->FieldName = "ZW";
    GSCZYCol->Caption = "����Ա";
    GSCZYCol->MinWidth = 60;
    GSCZYCol->DataBinding->FieldName = "USERNAME";
    GSRQCol->Caption = "��ʧ����";
    GSRQCol->MinWidth = 140;
    GSRQCol->DataBinding->FieldName = "GSRQ";
}
//---------------------------------------------------------------------------
void __fastcall TGSQFrm::KHTextEditKeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9')&& Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮�������!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TGSQFrm::QueryBTNClick(TObject *Sender)
{
	if(GSBeginDateEdit->Text.IsEmpty()||GSEndDateEdit->Text.IsEmpty())
	{
		ShowMessage("����������д��ѯ��������!");
		return;
	}

	String sqlstr = "select *,GS.USERNAME as gsuser from GS join CARD_F on CARD_F.BH=GS.BH and CARD_F.KH=GS.KH where CARD_F.ZT='��ʧ'";
    String addstr = "";
    if(!KHTextEdit->Text.IsEmpty())
    {
		addstr = " and GS.KH=";
        addstr += KHTextEdit->Text;
    }

    if(!BHTextEdit->Text.IsEmpty())
    {
        if(addstr.IsEmpty())
        {
			addstr = " and GS.BH='";
            addstr += BHTextEdit->Text;
            addstr += "'";
        }
        else
        {
            addstr += " and GS.BH='";
            addstr += BHTextEdit->Text;
            addstr += "'";
        }
    }

    if(!XMTextEdit->Text.IsEmpty())
    {
        if(addstr.IsEmpty())
        {
			addstr = " and CARD_F.XM='";
            addstr += XMTextEdit->Text;
            addstr += "'";
        }
        else
        {
            addstr += " and CARD_F.XM='";
            addstr += XMTextEdit->Text;
            addstr += "'";
        }
	}

	sqlstr += addstr;

	sqlstr += " and GS.GSRQ>='";
	sqlstr += GSBeginDateEdit->Text;
	sqlstr += " 00:00:00' and GS.GSRQ<='";
	sqlstr += GSEndDateEdit->Text;
	sqlstr += " 23:59:59'";

	DataGridDBTV->DataController->DataSource = NULL;
    GSADOQuery->Close();
    GSADOQuery->SQL->Clear();
    GSADOQuery->SQL->Add(sqlstr);
    GSADOQuery->Open();
    if(!GSADOQuery->IsEmpty())
    {
    	if(GSADOQuery->RecordCount>65500)
        {
            ShowMessage("���ϸò�ѯ�����ļ�¼��������65500�����޷�������ʾ�뵼�������޸Ĳ�ѯ����!");
            return;
        }
        DataGridDBTV->DataController->DataSource = GSDataSource;
        KHStr = KHTextEdit->Text;
        BHStr = BHTextEdit->Text;
        XMStr = XMTextEdit->Text;
        CZYStr = OperatorName;
        GSExportBTN->Enabled = true;
        PreviewBTN->Enabled = true;
    }
    else
    	ShowMessage("�޷��ϲ�ѯ�����ļ�¼!");
}
//---------------------------------------------------------------------------
void __fastcall TGSQFrm::GSExportBTNClick(TObject *Sender)
{
	if(!GSADOQuery->IsEmpty())
    {
    	ADOQInThread->Close();
        ADOQInThread->SQL->Clear();
		ADOQInThread->SQL = GSADOQuery->SQL;
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

                TGSExportThread* EXThread = new TGSExportThread(true,
                												GSExportProgressBar,
                                                                ADOQInThread,
                                                                GSExportBTN,
                                                                PreviewBTN,
                                                                GSExitBTN,
                                                                QueryBTN,
                                                                savename,
                                                                KHStr,
                                                                BHStr,
                                                                XMStr,
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
void __fastcall TGSQFrm::PreviewBTNClick(TObject *Sender)
{
	String temppath = GlobalPath;
	temppath += "\\PreviewFR3\\GSMXPreview.fr3";
    frxGSReport->LoadFromFile(temppath.t_str(), true);

    ((TfrxMemoView*)frxGSReport->FindObject("KHMemo"))->Text = KHStr.t_str();
    ((TfrxMemoView*)frxGSReport->FindObject("BHMemo"))->Text = BHStr.t_str();
    ((TfrxMemoView*)frxGSReport->FindObject("XMMemo"))->Text = XMStr.t_str();
    ((TfrxMemoView*)frxGSReport->FindObject("CZYMemo"))->Text = OperatorName.t_str();
    ((TfrxMemoView*)frxGSReport->FindObject("SCRQMemo"))->Text = DateTimeToStr(Now()).t_str();

    ((TfrxMemoView*)frxGSReport->FindObject("KH"))->DataField = "KH";
    ((TfrxMemoView*)frxGSReport->FindObject("BH"))->DataField = "BH";
    ((TfrxMemoView*)frxGSReport->FindObject("XM"))->DataField = "XM";
    ((TfrxMemoView*)frxGSReport->FindObject("XB"))->DataField = "XB";
    ((TfrxMemoView*)frxGSReport->FindObject("BM"))->DataField = "BM";
    ((TfrxMemoView*)frxGSReport->FindObject("BZ"))->DataField = "BZ";
    ((TfrxMemoView*)frxGSReport->FindObject("ZW"))->DataField = "ZW";
    ((TfrxMemoView*)frxGSReport->FindObject("GSCZY"))->DataField = "gsuser";
    ((TfrxMemoView*)frxGSReport->FindObject("GSRQM"))->DataField = "GSRQ";

    frxGSReport->ShowReport(true);
}
//---------------------------------------------------------------------------
