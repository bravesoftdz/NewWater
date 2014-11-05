//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BonusInfoExportFRM.h"
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
TBonusInfoExportForm *BonusInfoExportForm;
//---------------------------------------------------------------------------
__fastcall TBonusInfoExportForm::TBonusInfoExportForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TBonusInfoExportForm::CSBTBTNClick(TObject *Sender)
{
	if(BeginDateEdit->Text.IsEmpty()&&EndDateEdit->Text.IsEmpty())
	{
		MessageBox(this->Handle, "��ѡ���ѯ����ʼ����ֹ���ڣ�", "SQL Error!", MB_OK|MB_ICONERROR);
	}
	else
	{
		BTExportBTN->Enabled = false;
        JBBTBTN->Enabled = false;
		PrintInfoBTN->Enabled = false;
		String SQLstr = "select * from BTCS where DownDate>'";
		SQLstr += BeginDateEdit->Text;
		SQLstr += " 00:00:00' and DownDate<'";
		SQLstr += EndDateEdit->Text;
		SQLstr += " 23:59:59'";
		BTExportADOQuery->Close();
		BTExportADOQuery->SQL->Clear();
		BTExportADOQuery->SQL->Add(SQLstr);
		BTExportADOQuery->Open();
//		ShowMessage(ConsumeExportADOQuery->SQL->Text);

		if((!BTExportADOQuery->IsEmpty())&&(BTExportADOQuery->RecordCount < 65531))
		{
			DataGridDBTV->DataController->DataSource = BTExportDataSource;
			DataGridDBTV->ClearItems();
			DataGridDBTV->OptionsView->ColumnAutoWidth = true;

			TcxGridDBColumn* BHDCol = DataGridDBTV->CreateColumn();
			TcxGridDBColumn* KHCol = DataGridDBTV->CreateColumn();
			TcxGridDBColumn* BonusCol = DataGridDBTV->CreateColumn();
			TcxGridDBColumn* CreateDateCol = DataGridDBTV->CreateColumn();
			TcxGridDBColumn* UserNameCol = DataGridDBTV->CreateColumn();
			TcxGridDBColumn* DownDateCol = DataGridDBTV->CreateColumn();


			BHDCol->Caption = "���";
			BHDCol->DataBinding->FieldName = "BH";

			KHCol->Caption = "����";
			KHCol->DataBinding->FieldName = "KH";

			BonusCol->Caption = "�������";
			BonusCol->DataBinding->FieldName = "Bonus";

			CreateDateCol->Caption = "��������ʱ��";
			CreateDateCol->DataBinding->FieldName = "CreateDate";


			UserNameCol->Caption = "����Ա";
			UserNameCol->DataBinding->FieldName = "UserName";

			DownDateCol->Caption = "�����´�ʱ��";
			DownDateCol->DataBinding->FieldName = "DownDate";

			ActiveTableName = "BTCS";
			BTExportBTN->Enabled = true;
			PrintInfoBTN->Enabled = true;
		}
		else
		{
			MessageBox(this->Handle, "���ݿ�������ز�����Ϣ���������Ϣ�������಻��һ�ε������������������ڣ�", "Data Error!", MB_OK|MB_ICONERROR);
			BTExportADOQuery->Close();
		}
        JBBTBTN->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TBonusInfoExportForm::BTExitBTNClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------


void __fastcall TBonusInfoExportForm::JBBTBTNClick(TObject *Sender)
{
	if(BeginDateEdit->Text.IsEmpty()&&EndDateEdit->Text.IsEmpty())
	{
		MessageBox(this->Handle, "��ѡ���ѯ����ʼ����ֹ���ڣ�", "SQL Error!", MB_OK|MB_ICONERROR);
	}
	else
	{
		BTExportBTN->Enabled = false;
        CSBTBTN->Enabled = false;
		PrintInfoBTN->Enabled = false;
		String SQLstr = "select * from BTJB where DownDate>'";
		SQLstr += BeginDateEdit->Text;
		SQLstr += " 00:00:00' and DownDate<'";
		SQLstr += EndDateEdit->Text;
		SQLstr += " 23:59:59'";
		BTExportADOQuery->Close();
		BTExportADOQuery->SQL->Clear();
		BTExportADOQuery->SQL->Add(SQLstr);
		BTExportADOQuery->Open();
//		ShowMessage(ConsumeExportADOQuery->SQL->Text);

		if((!BTExportADOQuery->IsEmpty())&&(BTExportADOQuery->RecordCount < 65531))
		{
			DataGridDBTV->DataController->DataSource = BTExportDataSource;
			DataGridDBTV->ClearItems();
			DataGridDBTV->OptionsView->ColumnAutoWidth = true;

			TcxGridDBColumn* BHDCol = DataGridDBTV->CreateColumn();
			TcxGridDBColumn* KHCol = DataGridDBTV->CreateColumn();
			TcxGridDBColumn* BonusCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* ZWCol = DataGridDBTV->CreateColumn();
			TcxGridDBColumn* CreateDateCol = DataGridDBTV->CreateColumn();

            TcxGridDBColumn* JanuaryCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* FebruaryCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* MarchCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* AprilCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* MayCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* JuneCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* JulyCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* AugustCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* SeptemberCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* OctoberCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* NovemberCol = DataGridDBTV->CreateColumn();
            TcxGridDBColumn* DecemberCol = DataGridDBTV->CreateColumn();

			TcxGridDBColumn* UserNameCol = DataGridDBTV->CreateColumn();
			TcxGridDBColumn* DownDateCol = DataGridDBTV->CreateColumn();


			BHDCol->Caption = "���";
			BHDCol->DataBinding->FieldName = "BH";

			KHCol->Caption = "����";
			KHCol->DataBinding->FieldName = "KH";

			BonusCol->Caption = "�������";
            BonusCol->DataBinding->FieldName = "Bonus";

            ZWCol->Caption = "ְ��";
            ZWCol->DataBinding->FieldName = "ZW";

			CreateDateCol->Caption = "��������ʱ��";
			CreateDateCol->DataBinding->FieldName = "CreateDate";

            JanuaryCol->Caption = "һ�·�";
            JanuaryCol->DataBinding->FieldName = "January";

            FebruaryCol->Caption = "���·�";
            FebruaryCol->DataBinding->FieldName = "February";

            MarchCol->Caption = "���·�";
            MarchCol->DataBinding->FieldName = "March";

            AprilCol->Caption = "���·�";
            AprilCol->DataBinding->FieldName = "April";

            MayCol->Caption = "���·�";
            MayCol->DataBinding->FieldName = "May";

            JuneCol->Caption = "���·�";
            JuneCol->DataBinding->FieldName = "June";

            JulyCol->Caption = "���·�";
            JulyCol->DataBinding->FieldName = "July";

            AugustCol->Caption = "���·�";
            AugustCol->DataBinding->FieldName = "August";

            SeptemberCol->Caption = "���·�";
            SeptemberCol->DataBinding->FieldName = "September";

            OctoberCol->Caption = "ʮ�·�";
            OctoberCol->DataBinding->FieldName = "October";

            NovemberCol->Caption = "ʮһ�·�";
            NovemberCol->DataBinding->FieldName = "November";

            DecemberCol->Caption = "ʮ���·�";
            DecemberCol->DataBinding->FieldName = "December";


			UserNameCol->Caption = "����Ա";
			UserNameCol->DataBinding->FieldName = "UserName";

			DownDateCol->Caption = "�����´�ʱ��";
			DownDateCol->DataBinding->FieldName = "DownDate";

			ActiveTableName = "BTJB";
			BTExportBTN->Enabled = true;
			PrintInfoBTN->Enabled = true;
		}
		else
		{
			MessageBox(this->Handle, "���ݿ�������ز�����Ϣ���������Ϣ�������಻��һ�ε������������������ڣ�", "Data Error!", MB_OK|MB_ICONERROR);
			BTExportADOQuery->Close();
		}
        CSBTBTN->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TBonusInfoExportForm::BTExportBTNClick(TObject *Sender)
{
	if(!BTExportADOQuery->IsEmpty())
    {
        ADOQInThread->Close();
        ADOQInThread->SQL = BTExportADOQuery->SQL;
        if(SaveDialog->Execute())
		{
			if(FileExists(SaveDialog->FileName))
			{
				throw(Exception("��Ŀ¼�´���ͬ���ļ��������������ļ�����"));
			}
			else
            {
            	String savename = SaveDialog->FileName;
				savename += ".xls";
                TExportToXlsThread* ETXThread = new TExportToXlsThread(true,
                									BTExportProgressBar,
                                                    ADOQInThread,
                                                    BTExportBTN,
                                                    BTExitBTN,
                                                    savename,
                                                    ActiveTableName);
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

void __fastcall TBonusInfoExportForm::PrintInfoBTNClick(TObject *Sender)
{
	String temppath = GlobalPath;
	temppath += "\\PreviewFR3";

    if("BTJB" == ActiveTableName)
    {
    	temppath += "\\BTJBINFO.fr3";
        frxBTReport->LoadFromFile(temppath.t_str(), true);

        ((TfrxMemoView*)frxBTReport->FindObject("BH"))->DataField = "BH";
		((TfrxMemoView*)frxBTReport->FindObject("KH"))->DataField = "KH";
        ((TfrxMemoView*)frxBTReport->FindObject("Bonus"))->DataField = "Bonus";
		((TfrxMemoView*)frxBTReport->FindObject("CreateDate"))->DataField = "CreateDate";
        ((TfrxMemoView*)frxBTReport->FindObject("UserName"))->DataField = "UserName";
		((TfrxMemoView*)frxBTReport->FindObject("DownDate"))->DataField = "DownDate";

        frxBTReport->ShowReport(true);
    }

    if("BTCS" == ActiveTableName)
    {
    	temppath += "\\BTCSINFO.fr3";
        frxBTReport->LoadFromFile(temppath.t_str(), true);

        ((TfrxMemoView*)frxBTReport->FindObject("BH"))->DataField = "BH";
		((TfrxMemoView*)frxBTReport->FindObject("KH"))->DataField = "KH";
        ((TfrxMemoView*)frxBTReport->FindObject("Bonus"))->DataField = "Bonus";
		((TfrxMemoView*)frxBTReport->FindObject("ZW"))->DataField = "ZW";
        ((TfrxMemoView*)frxBTReport->FindObject("CreateDate"))->DataField = "CreateDate";
		((TfrxMemoView*)frxBTReport->FindObject("DownDate"))->DataField = "DownDate";
        ((TfrxMemoView*)frxBTReport->FindObject("January"))->DataField = "January";
		((TfrxMemoView*)frxBTReport->FindObject("February"))->DataField = "February";
        ((TfrxMemoView*)frxBTReport->FindObject("March"))->DataField = "March";
		((TfrxMemoView*)frxBTReport->FindObject("April"))->DataField = "April";
        ((TfrxMemoView*)frxBTReport->FindObject("May"))->DataField = "May";
		((TfrxMemoView*)frxBTReport->FindObject("June"))->DataField = "June";
        ((TfrxMemoView*)frxBTReport->FindObject("July"))->DataField = "July";
		((TfrxMemoView*)frxBTReport->FindObject("August"))->DataField = "August";
        ((TfrxMemoView*)frxBTReport->FindObject("September"))->DataField = "September";
		((TfrxMemoView*)frxBTReport->FindObject("October"))->DataField = "October";
        ((TfrxMemoView*)frxBTReport->FindObject("November"))->DataField = "November";
		((TfrxMemoView*)frxBTReport->FindObject("December"))->DataField = "December";
        ((TfrxMemoView*)frxBTReport->FindObject("UserName"))->DataField = "UserName";
		((TfrxMemoView*)frxBTReport->FindObject("DownDate"))->DataField = "DownDate";

        frxBTReport->ShowReport(true);
    }
}
//---------------------------------------------------------------------------

void __fastcall TBonusInfoExportForm::FormShow(TObject *Sender)
{
	BeginDateEdit->Date = Date();
	EndDateEdit->Date = Date();
}
//---------------------------------------------------------------------------

