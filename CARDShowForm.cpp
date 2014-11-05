//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CARDShowForm.h"
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
#include "ChangeCardInfoFRM.h"
TCARDShowFrm *CARDShowFrm;
//---------------------------------------------------------------------------
__fastcall TCARDShowFrm::TCARDShowFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCARDShowFrm::FormShow(TObject *Sender)
{
	CARDADOQuery->Open();
    if(!CARDADOQuery->IsEmpty()&&CARDADOQuery->RecordCount<=65500)
    {
    	DataGridDBTV->DataController->DataSource = CARDDataSource;
        DataGridDBTV->ClearItems();

        TcxGridDBColumn* KHCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* BHCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* XMCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* SFYECol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* XBCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* BMCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* BZCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* ZBCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* ZWCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* ZTCol = DataGridDBTV->CreateColumn();
        TcxGridDBColumn* FKRQCol = DataGridDBTV->CreateColumn();

        KHCol->Caption = "����";
        KHCol->MinWidth = 90;
        KHCol->DataBinding->FieldName = "KH";
        BHCol->Caption = "���";
        BHCol->MinWidth = 90;
        BHCol->DataBinding->FieldName = "BH";
        XMCol->Caption = "����";
        XMCol->MinWidth = 70;
        XMCol->DataBinding->FieldName = "XM";
        SFYECol->Caption = "�����";
        SFYECol->MinWidth = 70;
        SFYECol->DataBinding->FieldName = "SF_YE";
        XBCol->Caption = "�Ա�";
        XBCol->MinWidth = 40;
        XBCol->DataBinding->FieldName = "XB";
        BMCol->Caption = "����";
        BMCol->MinWidth = 80;
        BMCol->DataBinding->FieldName = "BM";
        BZCol->Caption = "���";
        BZCol->MinWidth = 60;
        BZCol->DataBinding->FieldName = "BZ";
        ZBCol->Caption = "���";
        ZBCol->MinWidth = 60;
        ZBCol->DataBinding->FieldName = "ZB";
        ZWCol->Caption = "ְ��";
        ZWCol->MinWidth = 60;
        ZWCol->DataBinding->FieldName = "ZW";
        ZTCol->Caption = "״̬";
        ZTCol->MinWidth = 40;
        ZTCol->DataBinding->FieldName = "ZT";
        FKRQCol->Caption = "��������";
        FKRQCol->MinWidth = 140;
        FKRQCol->DataBinding->FieldName = "RQ";
    }
}
//---------------------------------------------------------------------------
void __fastcall TCARDShowFrm::CARDExitBTNClick(TObject *Sender)
{
	CARDADOQuery->Close();
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TCARDShowFrm::CARDExportBTNClick(TObject *Sender)
{
	if(!CARDADOQuery->IsEmpty())
    {
    	ADOQInThread->Close();
        ADOQInThread->SQL->Clear();
		ADOQInThread->SQL = CARDADOQuery->SQL;
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

                TCARDExportThread* ETXThread = new TCARDExportThread(true,
                													 XFMXExportProgressBar,
                                                                     ADOQInThread,
                                                                     CARDExportBTN,
                                                                     PreviewBTN,
                                                                     CARDExitBTN,
                                                                     savename,
                                                                     KHStr,
                                                                     BHStr,
                                                                     XMStr,
                                                                     BMStr,
                                                                     BBStr,
                                                                     ZBStr,
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
void __fastcall TCARDShowFrm::PreviewBTNClick(TObject *Sender)
{
	String temppath = GlobalPath;
	temppath += "\\PreviewFR3\\CARDPreview.fr3";
    frxCARDReport->LoadFromFile(temppath.t_str(), true);

    ((TfrxMemoView*)frxCARDReport->FindObject("KHMemo"))->Text = KHStr.t_str();
    ((TfrxMemoView*)frxCARDReport->FindObject("BHMemo"))->Text = BHStr.t_str();
    ((TfrxMemoView*)frxCARDReport->FindObject("BMMemo"))->Text = BMStr.t_str();
    ((TfrxMemoView*)frxCARDReport->FindObject("XMMemo"))->Text = XMStr.t_str();
    ((TfrxMemoView*)frxCARDReport->FindObject("BZMemo"))->Text = BBStr.t_str();
    ((TfrxMemoView*)frxCARDReport->FindObject("ZBMemo"))->Text = ZBStr.t_str();
    ((TfrxMemoView*)frxCARDReport->FindObject("CZYMemo"))->Text = CZYStr.t_str();
    ((TfrxMemoView*)frxCARDReport->FindObject("SCRQMemo"))->Text = DateTimeToStr(Now()).t_str();

    ((TfrxMemoView*)frxCARDReport->FindObject("KH"))->DataField = "KH";
    ((TfrxMemoView*)frxCARDReport->FindObject("BH"))->DataField = "BH";
    ((TfrxMemoView*)frxCARDReport->FindObject("XM"))->DataField = "XM";
    ((TfrxMemoView*)frxCARDReport->FindObject("BM"))->DataField = "BM";
    ((TfrxMemoView*)frxCARDReport->FindObject("SFYE"))->DataField = "SF_YE";
    ((TfrxMemoView*)frxCARDReport->FindObject("XB"))->DataField = "XB";
    ((TfrxMemoView*)frxCARDReport->FindObject("BZ"))->DataField = "BZ";
    ((TfrxMemoView*)frxCARDReport->FindObject("ZB"))->DataField = "ZB";
    ((TfrxMemoView*)frxCARDReport->FindObject("ZT"))->DataField = "ZT";
    ((TfrxMemoView*)frxCARDReport->FindObject("ZW"))->DataField = "ZW";
    ((TfrxMemoView*)frxCARDReport->FindObject("RQ"))->DataField = "RQ";

    frxCARDReport->ShowReport(true);
}
//---------------------------------------------------------------------------
void __fastcall TCARDShowFrm::DataGridDBTVCellDblClick(TcxCustomGridTableView *Sender,
          TcxGridTableDataCellViewInfo *ACellViewInfo, TMouseButton AButton,
          TShiftState AShift, bool &AHandled)
{
	String outstr = Sender->Controller->SelectedRecords[0]->Values[1];
    ChangeCardInfoForm->BHStr = outstr;
    ChangeCardInfoForm->GBView = Sender;
    ChangeCardInfoForm->ShowModal();
}
//---------------------------------------------------------------------------

