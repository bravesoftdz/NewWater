//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PXFXMQery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxCalendar"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxDropDownEdit"
#pragma link "cxEdit"
#pragma link "cxGraphics"
#pragma link "cxGroupBox"
#pragma link "cxLabel"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxMaskEdit"
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
#pragma link "dxSkinsDefaultPainters"
#pragma link "dxSkinSeven"
#pragma link "dxSkinSharp"
#pragma link "dxSkinSilver"
#pragma link "dxSkinSpringTime"
#pragma link "dxSkinStardust"
#pragma link "dxSkinSummer2008"
#pragma link "dxSkinValentine"
#pragma link "dxSkinXmas2008Blue"
#pragma resource "*.dfm"
TPXFXMForm *PXFXMForm;
//---------------------------------------------------------------------------
__fastcall TPXFXMForm::TPXFXMForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPXFXMForm::ReadCardInfoBTNClick(TObject *Sender)
{
	WORD status;
	int tmpbalance;
	int tmpkh,tmpsycs;
	double tmpintye;
	double tmpye;
	unsigned char keymode,secnum,Delayms,mode;
	unsigned char key[6];
	unsigned char dwmm[6];
	unsigned char daytime[4];
	unsigned char kh[4];
	unsigned char balance[4];
	unsigned char cardtype[1];
	unsigned char czmm[3];
	unsigned char synum[3];
//	unsigned char readcomno[5] = "";

	Delayms = 0x00;
	keymode = CARDPasswordEdition;//0x03;
	secnum = UsingSecNUM;//0x01;

	key[0] = CARDPassword[0];
	key[1] = CARDPassword[1];
	key[2] = CARDPassword[2];
	key[3] = CARDPassword[3];
	key[4] = CARDPassword[4];
	key[5] = CARDPassword[5];

	if(LoadHModule)
	{
		beepofreaddll(readcomno, '10');
		if(readcardinfo)
		{
			status = readcardinfo(readcomno,keymode,secnum,key,kh,balance,
								dwmm,synum,daytime,cardtype,czmm,Delayms);

			if(status > 99)
			{
				ShowMessage("ͨѶ����");
			}
			else if (1 == status)
			{
				ShowMessage("��ѿ�Ƭ�źã�");
			}
			else if (2 == status)
			{
				ShowMessage("���Ŵ���192000�����0��");
			}
			else if (4 == status)
			{
				ShowMessage("��Ƭ���벻�ԣ�");
			}
			else if (5 == status)
			{
				ShowMessage("��д�����ȶ���");
			}
			else if (6 == status)
			{
				ShowMessage("���ṹ���ԣ�");
			}
			else if (10 == status)
			{
				ShowMessage("���ṹ���ԣ�");
			}
			else if (0 != status)
			{
				ShowMessage("�ÿ�δ���л����˿���");
			}
			else
			{
				String tmpstr;
				tmpkh = (int)kh[1]*256*256+(int)kh[2]*256+(int)kh[3];
				tmpsycs = (int)synum[0]*256+(int)synum[1];
				tmpintye = (double)balance[1]*256*256+(double)balance[2]*256+(double)balance[3];
				tmpye = tmpintye/100;

				XFADOQ->Close();
				XFADOQ->SQL->Clear();
				tmpstr = "select * from KZT where kh=";
				tmpstr += tmpkh;
				XFADOQ->SQL->Add(tmpstr);
				XFADOQ->Open();
				if(!XFADOQ->IsEmpty())
				{
					if(0 != XFADOQ->FieldByName("GS")->AsInteger)
					{
						ShowMessage("�˿��ѹ�ʧ����û�մ˿���");
						XFADOQ->Close();
					}
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					XFADOQ->Close();
				}
				XFADOQ->Close();

				XFADOQ->SQL->Clear();
				tmpstr = "select * from CARD where kh=";
				tmpstr += tmpkh;
				XFADOQ->SQL->Add(tmpstr);
				XFADOQ->Open();
				if(!XFADOQ->IsEmpty())
				{
					XFXMTextEdit->Text = "";
					XFKHTextEdit->Text = tmpkh;
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					XFADOQ->Close();
				}
			}
		}
		else
		{
            ShowMessage("������������ʧ�ܣ�");
		}
	}
	else
		ShowMessage("���ض�д����̬���ӿ�ʧ�ܣ�");
}
//---------------------------------------------------------------------------
void __fastcall TPXFXMForm::QueryBTNClick(TObject *Sender)
{
	if(XFKHTextEdit->Text.IsEmpty()&&XFXMTextEdit->Text.IsEmpty())
	{
		ShowMessage("��������д�����뿨���е�һ��!");
		return;
	}

	if(!XFBeginDateEdit->Text.IsEmpty()&&!XFEndDateEdit->Text.IsEmpty())
	{
		String sumsqlstr = "select SUM(case when SFLX='X' then MXBAK.SFJE else 0 end) as XFZE,SUM(case when SFLX='X' then 1 else 0 end) as XFZCS,SUM(case when (SFLX='I' or SFLX='A') then MXBAK.SFJE when SFLX='K' then MXBAK.SF_YE else 0 end) as CZZE,SUM(case when (SFLX='I' or SFLX='A') then 1 when SFLX='K' then 1 else 0 end) as CZZCS,SUM(case when (SFLX='D' or SFLX='Q' or SFLX='R') then MXBAK.SFJE else 0 end) as QKZE,SUM(case when (SFLX='D' or SFLX='Q' or SFLX='R') then 1 else 0 end) as QKZCS from MXBAK join CARD_F on CARD_F.BH=MXBAK.BH where ";
		String mxsqlstr = "select MXBAK.KH,MXBAK.BH,CARD_F.XM,CARD_F.BM,CARD_F.ZW,MXBAK.SF_YE,MXBAK.SFJE,MXBAK.SYCS,MXBAK.JYNO,MXBAK.SFLX,MXBAK.SFRQ from MXBAK  join CARD_F on CARD_F.BH=MXBAK.BH where SFLX in ('X','I','A','K','D','Q', 'R') and ";
		String addsqlstr = "";
		if(!XFKHTextEdit->Text.IsEmpty())
		{
			addsqlstr = "MXBAK.KH='";
			addsqlstr += XFKHTextEdit->Text;
			addsqlstr += "' and ";
		}
		if(!XFXMTextEdit->Text.IsEmpty())
		{
			if(addsqlstr.IsEmpty())
			{
				addsqlstr = "CARD_F.XM='";
				addsqlstr += XFXMTextEdit->Text;
				addsqlstr += "' and ";
			}
			else
			{
				addsqlstr += "CARD_F.XM='";
				addsqlstr += XFXMTextEdit->Text;
				addsqlstr += "' and ";
			}
		}

		addsqlstr += "SFRQ>'";
		addsqlstr += XFBeginDateEdit->Text;
		addsqlstr += " 00:00:00' and SFRQ<'";
		addsqlstr += XFEndDateEdit->Text;
		addsqlstr += " 23:59:59'";
		sumsqlstr += addsqlstr;
		mxsqlstr += addsqlstr;

		XFADOQ->Close();
        XFADOQ->SQL->Clear();
		XFADOQ->SQL->Add(mxsqlstr);
		XFADOQ->Open();
		if(!XFADOQ->IsEmpty())
		{
			XFADOQ->Close();
            XFADOQ->SQL->Clear();
            XFADOQ->SQL->Add(sumsqlstr);
			XFADOQ->Open();
			PXFMXShowFrm->AllXFTextEdit->Text = XFADOQ->FieldByName("XFZE")->AsString;
			PXFMXShowFrm->AllCSTextEdit->Text = XFADOQ->FieldByName("XFZCS")->AsString;
			PXFMXShowFrm->cxTextEdit2->Text = XFADOQ->FieldByName("CZZE")->AsString;
			PXFMXShowFrm->cxTextEdit1->Text = XFADOQ->FieldByName("CZZCS")->AsString;
			PXFMXShowFrm->cxTextEdit4->Text = XFADOQ->FieldByName("QKZE")->AsString;
			PXFMXShowFrm->cxTextEdit3->Text = XFADOQ->FieldByName("QKZCS")->AsString;
			XFADOQ->Close();

			PXFMXShowFrm->BeginDateTimeStr = XFBeginDateEdit->Text + " 00:00:00";
			PXFMXShowFrm->EndDateTimeStr = XFEndDateEdit->Text + " 23:59:59";
			PXFMXShowFrm->KHStr = XFKHTextEdit->Text;
			PXFMXShowFrm->XMStr = XFXMTextEdit->Text;
			PXFMXShowFrm->CZYStr = OperatorName;
			PXFMXShowFrm->XFMXExportProgressBar->Position = 0;

			PXFMXShowFrm->allsqlstr = mxsqlstr;
			PXFMXShowFrm->XFMXADOQuery->Close();
			PXFMXShowFrm->XFMXADOQuery->SQL->Clear();
			PXFMXShowFrm->XFMXADOQuery->SQL->Add(mxsqlstr);
			PXFMXShowFrm->ShowModal();
		}
		else
        	ShowMessage("���ϸò�ѯ�����ļ�¼����Ϊ0!");
	}
	else
	{
        ShowMessage("������д��ѯ��ֹ����!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TPXFXMForm::FormShow(TObject *Sender)
{
	XFBeginDateEdit->Date = Date();
	XFEndDateEdit->Date = Date();
}
//---------------------------------------------------------------------------

