//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FixLimitTimeFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxCalendar"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxDropDownEdit"
#pragma link "cxEdit"
#pragma link "cxGraphics"
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
TFixLimitTimeForm *FixLimitTimeForm;
//---------------------------------------------------------------------------
__fastcall TFixLimitTimeForm::TFixLimitTimeForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFixLimitTimeForm::FormShow(TObject *Sender)
{
	cxButton1->Enabled = true;
	cxButton2->Enabled = false;
	UseDateEdit->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFixLimitTimeForm::cxButton3Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFixLimitTimeForm::cxButton1Click(TObject *Sender)
{
	if(!pacarddllproc)
	{
		ShowMessage("��������ʱ�亯������ʧ��!");
		return;
	}

	WORD Status;
	int tmpbalance;
	int tmpkh,tmpsycs;
	int oldks,cardks;
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
    unsigned char createCRC[16];
	unsigned char CRC[2];
//	unsigned char readcomno[5] = "";

	Delayms = DelaySecond;
	keymode = CARDPasswordEdition;
	secnum = UsingSecNUM;

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
			WORD status = readcardinfo(readcomno,keymode,secnum,key,kh,balance,
								dwmm,synum,daytime,cardtype,czmm,Delayms);

			if(status > 99)
			{
				ShowMessage("ͨѶ����");
				return;
			}
			else if (1 == status)
			{
				ShowMessage("��ѿ�Ƭ�źã�");
				return;
			}
			else if (2 == status)
			{
				ShowMessage("���Ŵ���192000�����0��");
				return;
			}
			else if (4 == status)
			{
				ShowMessage("��Ƭ���벻�ԣ�");
				return;
			}
			else if (5 == status)
			{
				ShowMessage("��д�����ȶ���");
				return;
			}
			else if (6 == status)
			{
				ShowMessage("���ṹ���ԣ�");
				return;
			}
			else if (10 == status)
			{
				ShowMessage("���ṹ���ԣ�");
				return;
			}
			else if (0 != status)
			{
				ShowMessage("�ÿ�δ���л����˿���");
				return;
			}
			else
			{
				ADOCardInfoQuery->Close();
				ADOCardInfoQuery->SQL->Clear();
				ADOCardInfoQuery->SQL->Add("select * from XTSET");
				String mmstr = "";

				unsigned char tmpchar;
				tmpchar = dwmm[0];
				tmpchar = tmpchar>>4;
				mmstr += (int)tmpchar;

				tmpchar = dwmm[0];
				tmpchar = tmpchar<<4;
				tmpchar = tmpchar>>4;
				mmstr += (int)tmpchar;

				tmpchar = dwmm[1];
				tmpchar = tmpchar>>4;
				mmstr += (int)tmpchar;

				tmpchar = dwmm[1];
				tmpchar = tmpchar<<4;
				tmpchar = tmpchar>>4;
				mmstr += (int)tmpchar;

				ADOCardInfoQuery->Close();

				String tmpstr;
				tmpkh = (int)kh[1]*256*256+(int)kh[2]*256+(int)kh[3];
				tmpsycs = (int)synum[0]*256+(int)synum[1];
				tmpintye = (double)balance[1]*256*256+(double)balance[2]*256+(double)balance[3];
				tmpye = tmpintye/100;

				ADOCardInfoQuery->Close();
				ADOCardInfoQuery->SQL->Clear();
				tmpstr = "select * from KZT where kh=";
				tmpstr += tmpkh;
				ADOCardInfoQuery->SQL->Add(tmpstr);
				ADOCardInfoQuery->Open();
				if(!ADOCardInfoQuery->IsEmpty())
				{
					if(0 != ADOCardInfoQuery->FieldByName("GS")->AsInteger)
					{
						ShowMessage("�˿��ѹ�ʧ����û�մ˿���");
						ADOCardInfoQuery->Close();
						return;
					}
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOCardInfoQuery->Close();
					return;
				}
				ADOCardInfoQuery->Close();

				ADOCardInfoQuery->SQL->Clear();
				tmpstr = "select * from CARD where kh=";
				tmpstr += tmpkh;
				ADOCardInfoQuery->SQL->Add(tmpstr);
				ADOCardInfoQuery->Open();
				if(ADOCardInfoQuery->IsEmpty())
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOCardInfoQuery->Close();
					return;
				}
			}
		}
		else
		{
			ShowMessage("������������ʧ�ܣ�");
			return;
		}
	}
	else
	{
		ShowMessage("���ض�д����̬���ӿ�ʧ�ܣ�");
		return;
	}

	unsigned char sendbuf[26];
	unsigned char sendbuflen = 26;
	unsigned char senddelay = Delayms;
	unsigned char recbuf[140];
	unsigned char recbuflen;
	unsigned char pblock = (secnum+1)*4+2;
	unsigned char pmimamode = 0x60;
	unsigned char pcommand = 0x01;
	unsigned char pkeymode = CARDPasswordEdition;
	unsigned char pkey[6];
	memcpy(pkey,CARDPassword,6);

	ZeroMemory(sendbuf,26);
	sendbuf[0] = pblock;//������4+���
	sendbuf[1] = pmimamode;//�̶�Ϊ0x60
	sendbuf[2] = pcommand;//�����֣�1Ϊ����2Ϊд
	sendbuf[3] = pkeymode;
	sendbuf[4] = pkey[0];
	sendbuf[5] = pkey[1];
	sendbuf[6] = pkey[2];
	sendbuf[7] = pkey[3];
	sendbuf[8] = pkey[4];
	sendbuf[9] = pkey[5];
	Status = pacarddllproc(readcomno,sendbuflen,sendbuf,&recbuflen,recbuf,senddelay);
	if((0 == Status)&&(0 == recbuf[2]))
	{
		//�����ɹ�
		unsigned char tyear;
		unsigned char tmonth;
		unsigned char tday;
		String datestr = "20";
		tyear = recbuf[23];
		tmonth = recbuf[24];
		tday = recbuf[25];

		datestr += (int)(tyear>>4&0x0f);
		datestr += (int)(tyear&0x0f);
		datestr += "-";
		datestr += (int)(tmonth>>4&0x0f);
		datestr += (int)(tmonth&0x0f);
		datestr += "-";
		datestr += (int)(tday>>4&0x0f);
		datestr += (int)(tday&0x0f);

		UseDateEdit->Text = datestr;
		cxButton2->Enabled = true;
	}
	else
	{
		ShowMessage("��������ʱ��ʧ��!");
		return;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFixLimitTimeForm::cxButton2Click(TObject *Sender)
{
	if(!pacarddllproc)
	{
		ShowMessage("д������ʱ�亯������ʧ��!");
		return;
	}

	WORD Status;
	int tmpbalance;
	int tmpkh,tmpsycs;
	int oldks,cardks;
	double tmpintye;
	double tmpye;
	unsigned char keymode,secnum,Delayms,mode;
	unsigned char dwmm[6];
	unsigned char daytime[4];
	unsigned char kh[4];
	unsigned char balance[4];
	unsigned char cardtype[1];
	unsigned char czmm[3];
	unsigned char synum[3];
    unsigned char createCRC[16];
	unsigned char CRC[2];
//	unsigned char readcomno[5] = "";

	Delayms = DelaySecond;
	keymode = CARDPasswordEdition;
	secnum = UsingSecNUM;

	unsigned char sendbuf[26];
	unsigned char sendbuflen = 26;
	unsigned char senddelay = Delayms;
	unsigned char recbuf[140];
	unsigned char recbuflen;
	ZeroMemory(recbuf, 140);
	unsigned char pblock = (secnum+1)*4+2;
	unsigned char pmimamode = 0x60;
	unsigned char pcommand = 0x02;
	unsigned char pkeymode = CARDPasswordEdition;
	unsigned char pkey[6];
	memcpy(pkey,CARDPassword,6);

	ZeroMemory(sendbuf,26);

	unsigned char limitwritedaytime[4];
	String limitwritetmpstr = DateToStr(UseDateEdit->Date);
	char* limitwritetmpdatestr = limitwritetmpstr.t_str();
	limitwritedaytime[0] = char(((int)limitwritetmpdatestr[2]-48)*16+((int)limitwritetmpdatestr[3]-48));
	limitwritedaytime[1] = char(((int)limitwritetmpdatestr[5]-48)*16+((int)limitwritetmpdatestr[6]-48));
	limitwritedaytime[2] = char(((int)limitwritetmpdatestr[8]-48)*16+((int)limitwritetmpdatestr[9]-48));
	limitwritedaytime[3] = 0x00;

	sendbuf[0] = pblock;//������4+���
	sendbuf[1] = pmimamode;//�̶�Ϊ0x60
	sendbuf[2] = pcommand;//�����֣�1Ϊ����2Ϊд
	sendbuf[3] = pkeymode;
	sendbuf[4] = pkey[0];
	sendbuf[5] = pkey[1];
	sendbuf[6] = pkey[2];
	sendbuf[7] = pkey[3];
	sendbuf[8] = pkey[4];
	sendbuf[9] = pkey[5];

	sendbuf[23] = limitwritedaytime[0];
	sendbuf[24] = limitwritedaytime[1];
	sendbuf[25] = limitwritedaytime[2];


	Status = pacarddllproc(readcomno,sendbuflen,sendbuf,&recbuflen,recbuf,senddelay);
	if((0 == Status)&&(0 == recbuf[2]))
	{
		//д���ɹ�
		beepofreaddll(readcomno, '10');
		ShowMessage("д������ʱ��ɹ�!");
		return;
	}
	else
	{
		ShowMessage("д������ʱ��ʧ��!");
		return;
	}
}
//---------------------------------------------------------------------------
