//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GlobalParameter.h"
#include "BigWalletForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGraphics"
#pragma link "cxGroupBox"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
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
#pragma link "cxButtons"
#pragma link "cxTextEdit"
#pragma resource "*.dfm"
TBigWalletFrm *BigWalletFrm;
//---------------------------------------------------------------------------
__fastcall TBigWalletFrm::TBigWalletFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBigWalletFrm::cxButton1Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TBigWalletFrm::cxTextEdit1KeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮�������!");
	}
}
//---------------------------------------------------------------------------

void __fastcall TBigWalletFrm::cxButton2Click(TObject *Sender)
{
	if(!cxTextEdit5->Text.IsEmpty()&&(!cxTextEdit1->Text.IsEmpty()||!cxTextEdit2->Text.IsEmpty()))
	{
		String Addsqlstr;
		String subaddsqlstr;
		if(!cxTextEdit1->Text.IsEmpty()&&!cxTextEdit2->Text.IsEmpty())
		{
			int bh = StrToInt(cxTextEdit2->Text);
			AnsiString BHstr;
			BHstr.sprintf("%010d",bh);
			int kh = StrToInt(cxTextEdit1->Text);
			Addsqlstr = "CARD.BH='";
			Addsqlstr += BHstr;
			Addsqlstr += "' and CARD.KH=";
			Addsqlstr += kh;
			subaddsqlstr += "BH='";
			subaddsqlstr += BHstr;
			subaddsqlstr += "' and KH=";
			subaddsqlstr += kh;
		}
		else if(!cxTextEdit1->Text.IsEmpty()&&cxTextEdit2->Text.IsEmpty())
		{
			int kh = StrToInt(cxTextEdit1->Text);
			Addsqlstr = "CARD.KH=";
			Addsqlstr += kh;
			subaddsqlstr = "KH=";
			subaddsqlstr += kh;
		}
		else if(cxTextEdit1->Text.IsEmpty()&&!cxTextEdit2->Text.IsEmpty())
		{
			int bh = StrToInt(cxTextEdit2->Text);
			AnsiString BHstr;
			BHstr.sprintf("%010d",bh);
			Addsqlstr = "CARD.BH='";
			Addsqlstr += BHstr;
			Addsqlstr += "'";
			subaddsqlstr = "BH='";
			subaddsqlstr += BHstr;
			subaddsqlstr += "'";
		}

		String sqlstr = "select * from CARD join Wallet on CARD.BH=Wallet.BH and CARD.KH=Wallet.KH where ";
		sqlstr += Addsqlstr;
		ShowMessage(sqlstr);
		ADOQuery1->Close();
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add(sqlstr);
		ADOQuery1->Open();
		if(!ADOQuery1->IsEmpty())
		{
			//���г�ֵ
			int chargemoney = StrToInt(cxTextEdit5->Text);
			String chargesqlstr = "select * from Wallet where ";
			chargesqlstr += subaddsqlstr;
			ADOQuery1->Close();
			ADOQuery1->SQL->Clear();
			ADOQuery1->SQL->Add(chargesqlstr);
			ADOQuery1->Open();
			if(!ADOQuery1->IsEmpty())
			{
				chargemoney += ADOQuery1->FieldByName("SF_YE")->AsInteger;
				ADOQuery1->Edit();
				ADOQuery1->FieldByName("SF_YE")->AsInteger = chargemoney;
				ADOQuery1->Post();


				//��Ǯ����ֵ��⣬OperationList��
				String opsqlstr = "insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add(opsqlstr);
				int bh = StrToInt(cxTextEdit2->Text);
				AnsiString BHstr;
				BHstr.sprintf("%010d",bh);
				ADOQuery1->Parameters->ParamByName("BH")->Value = BHstr;
				ADOQuery1->Parameters->ParamByName("KH")->Value = StrToInt(cxTextEdit1->Text);
				ADOQuery1->Parameters->ParamByName("JE")->Value = StrToInt(cxTextEdit5->Text);
				ADOQuery1->Parameters->ParamByName("YE")->Value = chargemoney;
				ADOQuery1->Parameters->ParamByName("LX")->Value = "Ǯ����ֵ";
				ADOQuery1->Parameters->ParamByName("Operator")->Value = OperatorName;
				SYSTEMTIME tmpsystime;
				GetLocalTime(&tmpsystime);
				ADOQuery1->Parameters->ParamByName("DateTime")->Value = DateTimeToStr(SystemTimeToDateTime(tmpsystime));
				ADOQuery1->ExecSQL();
				ADOQuery1->Close();

				String outstr = "��Ǯ����ֵ��ϣ���ֵ���Ϊ��";
				outstr += StrToInt(cxTextEdit5->Text);
				outstr += "����Ǯ�����Ϊ��";
				outstr += chargemoney;
				ShowMessage(outstr);
			}
			else
			{
				ShowMessage("û�и���Ϣ�Ĵ�Ǯ����¼!");
			}
			ADOQuery1->Close();
		}
		else
		{
			//��Ӵ�Ǯ�����ݿ��¼����������
			String checksqlstr = "select * from CARD where ";
			checksqlstr += subaddsqlstr;
			ADOQuery1->Close();
			ADOQuery1->SQL->Clear();
			ADOQuery1->SQL->Add(checksqlstr);
			ADOQuery1->Open();
			if(!ADOQuery1->IsEmpty())
			{
				ShowMessage("���ֵǰ���øÿ�Ƭ�Ĵ�Ǯ������!");
				cxButton3->Enabled = true;
				cxTextEdit3->Enabled = true;
				cxTextEdit4->Enabled = true;
			}
			else
				ShowMessage("ϵͳ��û�иÿ�Ƭ��Ϣ���޷���ֵ!");
		}
	}
	else
	{
		ShowMessage("������д��ֵ������д���Ż���!");
	}
}
//---------------------------------------------------------------------------

void __fastcall TBigWalletFrm::cxButton3Click(TObject *Sender)
{
	if(!cxTextEdit3->Text.IsEmpty()&&!cxTextEdit4->Text.IsEmpty())
	{
		if(cxTextEdit3->Text != cxTextEdit4->Text)
		{
			ShowMessage("���뼰ȷ�����벻ƥ�䣬����������!");
			cxTextEdit3->Text = "";
			cxTextEdit4->Text = "";
			return;
        }
	}
	else
	{
		ShowMessage("������д���뼰ȷ������!");
		return;
	}

	if(!cxTextEdit1->Text.IsEmpty()||!cxTextEdit2->Text.IsEmpty())
	{
		String subaddsqlstr;
		if(!cxTextEdit1->Text.IsEmpty()&&!cxTextEdit2->Text.IsEmpty())
		{
			int bh = StrToInt(cxTextEdit2->Text);
			AnsiString BHstr;
			BHstr.sprintf("%010d",bh);
			int kh = StrToInt(cxTextEdit1->Text);
			subaddsqlstr = "BH='";
			subaddsqlstr += BHstr;
			subaddsqlstr += "' and KH=";
			subaddsqlstr += kh;
		}
		else if(!cxTextEdit1->Text.IsEmpty()&&cxTextEdit2->Text.IsEmpty())
		{
			int kh = StrToInt(cxTextEdit1->Text);
			subaddsqlstr = "KH=";
			subaddsqlstr += kh;
		}
		else if(cxTextEdit1->Text.IsEmpty()&&!cxTextEdit2->Text.IsEmpty())
		{
			int bh = StrToInt(cxTextEdit2->Text);
			AnsiString BHstr;
			BHstr.sprintf("%010d",bh);
			subaddsqlstr = "BH='";
			subaddsqlstr += BHstr;
			subaddsqlstr += "'";
		}
		String sqlstr = "select * from CARD where ";
		sqlstr += subaddsqlstr;
		ADOQuery1->Close();
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add(sqlstr);
		ADOQuery1->Open();
		if(!ADOQuery1->IsEmpty())
		{
			String insertsqlstr = "insert into Wallet values(:BH,:KH,:SF_YE,:CZY,:PASSWORD)";
			int kh = ADOQuery1->FieldByName("KH")->AsInteger;
			String bh = ADOQuery1->FieldByName("BH")->AsAnsiString;
			String czy = OperatorName;
			String pw = cxTextEdit3->Text;
			ADOQuery1->Close();
			ADOQuery1->SQL->Clear();
			ADOQuery1->SQL->Add(insertsqlstr);
			ADOQuery1->Parameters->ParamByName("BH")->Value = bh;
			ADOQuery1->Parameters->ParamByName("KH")->Value = kh;
			ADOQuery1->Parameters->ParamByName("SF_YE")->Value = 0;
			ADOQuery1->Parameters->ParamByName("CZY")->Value = czy;
			ADOQuery1->Parameters->ParamByName("PASSWORD")->Value = pw;
			ADOQuery1->ExecSQL();
			ADOQuery1->Close();
			ShowMessage("�ÿ�Ƭ��Ǯ���������óɹ������Խ��г�ֵ!");
			cxTextEdit3->Text = "";
			cxTextEdit4->Text = "";
			cxTextEdit3->Enabled = false;
			cxTextEdit4->Enabled = false;
			cxButton3->Enabled = false;
		}
		else
		{
            ShowMessage("ϵͳ���޸ÿ�Ƭ�ļ�¼!");
		}
		ADOQuery1->Close();
	}
	else
	{
		ShowMessage("������д���Ż���!");
    }
}
//---------------------------------------------------------------------------

void __fastcall TBigWalletFrm::cxButton5Click(TObject *Sender)
{
//������ȡ��Ƭ��Ϣ
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
				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add("select * from XTSET");
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

				ADOQuery1->Close();

				String tmpstr;
				tmpkh = (int)kh[1]*256*256+(int)kh[2]*256+(int)kh[3];
				tmpsycs = (int)synum[0]*256+(int)synum[1];
				tmpintye = (double)balance[1]*256*256+(double)balance[2]*256+(double)balance[3];
				tmpye = tmpintye/100;

				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				tmpstr = "select * from KZT where kh=";
				tmpstr += tmpkh;
				ADOQuery1->SQL->Add(tmpstr);
				ADOQuery1->Open();
				if(!ADOQuery1->IsEmpty())
				{
					if(0 != ADOQuery1->FieldByName("GS")->AsInteger)
					{
						ShowMessage("�˿��ѹ�ʧ����û�մ˿���");
						ADOQuery1->Close();
					}
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOQuery1->Close();
				}
				ADOQuery1->Close();

				ADOQuery1->SQL->Clear();
				tmpstr = "select * from CARD where kh=";
				tmpstr += tmpkh;
				ADOQuery1->SQL->Add(tmpstr);
				ADOQuery1->Open();
				if(!ADOQuery1->IsEmpty())
				{
					cxTextEdit6->Text = tmpkh;
					cxTextEdit7->Text = ADOQuery1->FieldByName("BH")->AsAnsiString;
					ADOQuery1->Close();
					String wsqlstr = "select * from Wallet where BH='";
					wsqlstr += cxTextEdit7->Text;
					wsqlstr += "' and KH=";
					wsqlstr += cxTextEdit6->Text;
					ADOQuery1->SQL->Clear();
					ADOQuery1->SQL->Add(wsqlstr);
					ADOQuery1->Open();
					if(!ADOQuery1->IsEmpty())
					{
						cxTextEdit8->Enabled = true;
						cxTextEdit9->Enabled = true;
						cxButton4->Enabled = true;
					}
					else
					{
                        ShowMessage("�ÿ�Ƭû�д�Ǯ����¼�����ܴӴ�Ǯ���н���ת��!");
                    }
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOQuery1->Close();
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

void __fastcall TBigWalletFrm::FormShow(TObject *Sender)
{
	cxTextEdit1->Text = "";
	cxTextEdit2->Text = "";
	cxTextEdit3->Text = "";
	cxTextEdit4->Text = "";
	cxTextEdit5->Text = "";
	cxTextEdit6->Text = "";
	cxTextEdit7->Text = "";
	cxTextEdit8->Text = "";
	cxTextEdit9->Text = "";
	cxButton3->Enabled = false;
	cxButton4->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TBigWalletFrm::cxButton4Click(TObject *Sender)
{
//ת��
	if(!cxTextEdit8->Text.IsEmpty()&&!cxTextEdit9->Text.IsEmpty())
	{
		String pw = "";
		int ye = 0;
		String zcsqlstr = "select * from Wallet where KH=";
		zcsqlstr += cxTextEdit6->Text;
		zcsqlstr += " and BH='";
		zcsqlstr += cxTextEdit7->Text;
		zcsqlstr += "'";
		ADOQuery1->Close();
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add(zcsqlstr);
		ADOQuery1->Open();
		if(!ADOQuery1->IsEmpty())
		{
			pw = ADOQuery1->FieldByName("PASSWORD")->AsAnsiString;
			ye = ADOQuery1->FieldByName("SF_YE")->AsInteger;
		}
		ADOQuery1->Close();
		if(pw != cxTextEdit9->Text)
		{
			ShowMessage("��Ǯ���������!");
			return;
		}
		if(ye < StrToInt(cxTextEdit9->Text))
		{
			ShowMessage("��Ǯ������!");
			return;
		}

		//��ֵ����⣬MX��
		int czsfye = StrToInt(cxTextEdit9->Text)-ye;
		WORD status;
		WORD WriteStatus;
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

		Delayms = DelaySecond;//0x00;
		keymode = CARDPasswordEdition;
		mode = 0x01;
		secnum = UsingSecNUM;

		key[0] = CARDPassword[0];
		key[1] = CARDPassword[1];
		key[2] = CARDPassword[2];
		key[3] = CARDPassword[3];
		key[4] = CARDPassword[4];
		key[5] = CARDPassword[5];

		if(LoadHModule)
		{
			if(readcardinfo)
			{
	 //			ShowMessage("begin read card!");
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
					tmpkh = (int)kh[1]*256*256+(int)kh[2]*256+(int)kh[3];

					tmpsycs = (int)synum[0]*256+(int)synum[1];
					tmpsycs++;
					unsigned char writesynum[2];
					writesynum[0] = (char)(tmpsycs/256);
					writesynum[1] = (char)(tmpsycs%256);

					tmpintye = (double)balance[1]*256*256+(double)balance[2]*256+(double)balance[3];
			  //		tmpye = tmpintye/100+ReChargeMoney;
					tmpye = tmpintye/100 + StrToInt(cxTextEdit9->Text);

					unsigned char writebalance[4];
					double writetmpbalance = StrToInt(cxTextEdit8->Text);
					writetmpbalance *= 100;
					writebalance[0] = 0x00;
					writebalance[1] = (unsigned char)((int)writetmpbalance/65536);
					writetmpbalance = (int)writetmpbalance%65536;
					writebalance[2] = (unsigned char)((int)writetmpbalance/256);
					writetmpbalance = (int)writetmpbalance%256;
					writebalance[3] = (unsigned char)writetmpbalance;

					if(LaunchNewCard)
					{
						String DateofLaunchCard;
						SYSTEMTIME tmpsystime;
						GetLocalTime(&tmpsystime);
						DateofLaunchCard = DateTimeToStr(SystemTimeToDateTime(tmpsystime));

						WriteStatus = LaunchNewCard(readcomno,
													keymode,
													secnum,
													key,
													kh,
													writebalance,
													dwmm,
													writesynum,
													daytime,
													cardtype,
													czmm,
													mode,
													Delayms);
						if(WriteStatus)
						{
							ShowMessage("д��ʧ��!��ֵʧ��!");
						}
						else
						{

							//����MX��
							ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							String sqlstr = "insert into MX values(:BH,:KH,:SF_YE,";
							sqlstr = sqlstr + ":SFJE,:SYCS,:SFRQ,:JYNO,";
							sqlstr = sqlstr + ":GZZID,:SFLX,:CZY,:SCRQ)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = cxTextEdit7->Text;
							ADOQuery1->Parameters->ParamByName("KH")->Value = tmpkh;
							ADOQuery1->Parameters->ParamByName("SF_YE")->Value = tmpye;
							ADOQuery1->Parameters->ParamByName("SFJE")->Value = StrToInt(cxTextEdit8->Text);;
							ADOQuery1->Parameters->ParamByName("SYCS")->Value = tmpsycs;
							ADOQuery1->Parameters->ParamByName("SFRQ")->Value = DateofLaunchCard;
							ADOQuery1->Parameters->ParamByName("JYNO")->Value = 1001;
							ADOQuery1->Parameters->ParamByName("GZZID")->Value = 1;
							ADOQuery1->Parameters->ParamByName("SFLX")->Value = "C";
							ADOQuery1->Parameters->ParamByName("CZY")->Value = OperatorName;
							ADOQuery1->Parameters->ParamByName("SCRQ")->Value = DateofLaunchCard;
							ADOQuery1->ExecSQL();
							ADOQuery1->Close();


							//��д������¼��
							sqlstr = "insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
							ADOQuery1->SQL->Clear();
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = cxTextEdit7->Text;
							ADOQuery1->Parameters->ParamByName("KH")->Value = tmpkh;
							ADOQuery1->Parameters->ParamByName("JE")->Value = StrToInt(cxTextEdit8->Text);;
							ADOQuery1->Parameters->ParamByName("YE")->Value = tmpye;
							ADOQuery1->Parameters->ParamByName("LX")->Value = "Ǯ��ת��";
							ADOQuery1->Parameters->ParamByName("Operator")->Value = OperatorName;
							ADOQuery1->Parameters->ParamByName("DateTime")->Value = DateofLaunchCard;
							ADOQuery1->ExecSQL();
							ADOQuery1->Close();

							//����CARD��CARD_F��

							sqlstr = "select * from CARD where BH='";
							sqlstr = sqlstr + cxTextEdit7->Text + "'";
							ADOQuery1->SQL->Clear();
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->ExecSQL();
							ADOQuery1->Active = true;
							ADOQuery1->Edit();
							ADOQuery1->FieldByName("SF_YE")->AsFloat = tmpye;
							ADOQuery1->FieldByName("SFYEDT")->AsDateTime = StrToDateTime(DateofLaunchCard);
							ADOQuery1->FieldByName("SYCS")->AsInteger = tmpsycs;
							ADOQuery1->Post();

							sqlstr = "select * from CARD_F where BH='";
							sqlstr = sqlstr + cxTextEdit7->Text + "'";
							ADOQuery1->SQL->Clear();
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->ExecSQL();
							ADOQuery1->Active = true;
							ADOQuery1->Edit();
							ADOQuery1->FieldByName("SF_YE")->AsFloat = tmpye;
							ADOQuery1->FieldByName("SFYEDT")->AsDateTime = StrToDateTime(DateofLaunchCard);
							ADOQuery1->FieldByName("SYCS")->AsInteger = tmpsycs;
							ADOQuery1->Post();

							ADOQuery1->Close();

							WORD chkstatus;
							WORD chkWriteStatus;
							int chktmpbalance;
							int chktmpkh,chktmpsycs;
							double chktmpintye;
							double chktmpye;
							unsigned char chkkeymode,chksecnum,chkDelayms,chkmode;
							unsigned char chkkey[6];
							unsigned char chkdwmm[6];
							unsigned char chkdaytime[4];
							unsigned char chkkh[4];
							unsigned char chkbalance[4];
							unsigned char chkcardtype[1];
							unsigned char chkczmm[3];
							unsigned char chksynum[3];

							chkDelayms = DelaySecond;//0x00;
							chkkeymode = CARDPasswordEdition;
							chkmode = 0x01;
							chksecnum = UsingSecNUM;

							chkkey[0] = CARDPassword[0];
							chkkey[1] = CARDPassword[1];
							chkkey[2] = CARDPassword[2];
							chkkey[3] = CARDPassword[3];
							chkkey[4] = CARDPassword[4];
							chkkey[5] = CARDPassword[5];

							chkstatus = readcardinfo(readcomno,chkkeymode,chksecnum,chkkey,chkkh,chkbalance,
									chkdwmm,chksynum,chkdaytime,chkcardtype,chkczmm,chkDelayms);
							if(chkstatus > 99)
							{
								ShowMessage("��ֵ��������!");
							}
							else if (1 == chkstatus)
							{
								ShowMessage("��ֵ��������!");
							}
							else if (2 == chkstatus)
							{
								ShowMessage("��ֵ��������!");
							}
							else if (4 == chkstatus)
							{
								ShowMessage("��ֵ��������!");
							}
							else if (5 == chkstatus)
							{
								ShowMessage("��ֵ��������!");
							}
							else if (6 == chkstatus)
							{
								ShowMessage("��ֵ��������!");
							}
							else if (10 == chkstatus)
							{
								ShowMessage("��ֵ��������!");
							}
							else if (0 != chkstatus)
							{
								ShowMessage("��ֵ��������!");
							}
							else
							{
								double chktmpintye = ((double)chkbalance[1]*256*256+(double)chkbalance[2]*256+(double)chkbalance[3])/100;
								if(tmpye == chktmpintye)
								{
									beepofreaddll(readcomno, '10');
									ADOQuery1->Close();
									ADOQuery1->SQL->Clear();
									ADOQuery1->SQL->Add(zcsqlstr);
									ADOQuery1->Open();
									if(!ADOQuery1->IsEmpty())
									{
										ADOQuery1->Edit();
										ADOQuery1->FieldByName("SF_YE")->AsInteger = czsfye;
										ADOQuery1->Post();
									}
									ADOQuery1->Close();
									String ReChargeOutstr = "��ֵ�ɹ�!�����Ϊ����";
									ReChargeOutstr += tmpye;
									ReChargeOutstr += "�����Ĵ�Ǯ�����Ϊ����";
									ReChargeOutstr += czsfye;
									ShowMessage(ReChargeOutstr);
								}
							}
						}
					}
					else
					{
						ShowMessage("д����������ʧ�ܣ�");
					}
				}
			}
		}
	}
	else
	{
		ShowMessage("�������Ǯ�����뼰ת����!");
    }
}
//---------------------------------------------------------------------------

