//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DealMistakFRM.h"
#include "GlobalParameter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxGraphics"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGroupBox"
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
#pragma link "cxCalendar"
#pragma link "cxDropDownEdit"
#pragma link "cxMaskEdit"
#pragma link "cxSpinEdit"
#pragma link "cxTextEdit"
#pragma link "cxTimeEdit"
#pragma link "cxClasses"
#pragma link "cxCustomData"
#pragma link "cxData"
#pragma link "cxDataStorage"
#pragma link "cxDBData"
#pragma link "cxFilter"
#pragma link "cxGrid"
#pragma link "cxGridCustomTableView"
#pragma link "cxGridCustomView"
#pragma link "cxGridDBTableView"
#pragma link "cxGridLevel"
#pragma link "cxGridTableView"
#pragma link "cxStyles"
#pragma link "dxSkinscxPCPainter"
#pragma resource "*.dfm"
TDealMistakeForm *DealMistakeForm;
//---------------------------------------------------------------------------
__fastcall TDealMistakeForm::TDealMistakeForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDealMistakeForm::cxButton1Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TDealMistakeForm::FormShow(TObject *Sender)
{
	cxDateEdit1->Date = Date();
	TDateTime ti = Time();
	unsigned short hr;
	unsigned short me;
	unsigned short sd;
	unsigned short md;
	if(hr >= 23);
		hr = 22;
	DecodeTime(ti,hr,me,sd,md);

	cxTimeEdit1->Time = ti;
	hr = (hr+1)%24;
	cxTimeEdit2->Time = EncodeTime(hr,me,sd,md);

	DataGridDBTV->ClearItems();
	TcxGridDBColumn* KHCol = DataGridDBTV->CreateColumn();
	TcxGridDBColumn* BHCol = DataGridDBTV->CreateColumn();
	TcxGridDBColumn* SFYECol = DataGridDBTV->CreateColumn();
	TcxGridDBColumn* SFRQCol = DataGridDBTV->CreateColumn();
	TcxGridDBColumn* JHCol = DataGridDBTV->CreateColumn();

	KHCol->Caption = "����";
//	KHCol->MinWidth = 90;
	KHCol->DataBinding->FieldName = "KH";

	BHCol->Caption = "���";
	BHCol->DataBinding->FieldName = "BH";

	SFYECol->Caption = "���ѽ��";
	SFYECol->DataBinding->FieldName = "SFJE";

	SFRQCol->Caption = "��������";
	SFRQCol->DataBinding->FieldName = "SFRQ";

	JHCol->Caption = "���ѻ���";
	JHCol->DataBinding->FieldName = "JYNO";
}
//---------------------------------------------------------------------------
void __fastcall TDealMistakeForm::cxButton2Click(TObject *Sender)
{
//����ȡ����
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
				String tmpstr;
				tmpkh = (int)kh[1]*256*256+(int)kh[2]*256+(int)kh[3];
				querykh = tmpkh;
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
						return;
					}
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOQuery1->Close();
					return;
				}
				ADOQuery1->Close();

				ADOQuery1->SQL->Clear();
				tmpstr = "select * from CARD where kh=";
				tmpstr += tmpkh;
				ADOQuery1->SQL->Add(tmpstr);
				ADOQuery1->Open();
				if(!ADOQuery1->IsEmpty())
				{
					bhstr = ADOQuery1->FieldByName("BH")->AsString.Trim();
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOQuery1->Close();
					return;
				}
				ADOQuery1->Close();
				cxButton3->Enabled = true;
				cxButton4->Enabled = true;
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

void __fastcall TDealMistakeForm::cxButton4Click(TObject *Sender)
{
	if(cxDateEdit1->Text.IsEmpty()||cxTimeEdit1->Text.IsEmpty()||cxTimeEdit2->Text.IsEmpty())
	{
		ShowMessage("������������д��ѯʱ������!");
		return;
	}
	if(cxTimeEdit1->Time > cxTimeEdit2->Time)
	{
		ShowMessage("����ʱ�����ޱ�����������ʱ������!");
		return;
	}
	if(cxTextEdit2->Text.IsEmpty())
	{
		ShowMessage("�����������ѻ���!");
		return;
    }

	String sqlstr = "select * from MX where KH=";
	String sqlbakstr = "select * from MXBAK where KH=";
	sqlstr += querykh;
	sqlbakstr += querykh;
	String upstr;
	String downstr;

	upstr = DateTimeToStr(cxDateEdit1->Text+" "+cxTimeEdit1->Text);
	downstr = DateTimeToStr(cxDateEdit1->Text+" "+cxTimeEdit2->Text);
	String addsqlstr = " and JYNO=";
	addsqlstr += cxTextEdit2->Text;
	addsqlstr += " and SFRQ>'";
	addsqlstr += upstr;
	addsqlstr += "' and SFRQ<'";
	addsqlstr += downstr;
	addsqlstr += "'";

	sqlstr += addsqlstr;
	sqlbakstr += addsqlstr;

	ADOQuery1->Close();
	ADOQuery1->SQL->Clear();
	ADOQuery1->SQL->Add(sqlstr);
	ADOQuery1->Open();
	if(!ADOQuery1->IsEmpty())
	{

	}
	else
	{
		ADOQuery1->Close();
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add(sqlbakstr);
		ADOQuery1->Open();
		if(!ADOQuery1->IsEmpty())
		{

		}
		else
		{
			ShowMessage("�ÿ�������һʱ���û�н������ѣ����������ղ���!");
			return;
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TDealMistakeForm::cxTextEdit2KeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
    	if(13 == Key)
		{
        	Key = 0;
        }
        else
        {
			Key=0;
			ShowMessage("������0��9֮������֣�");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TDealMistakeForm::cxTextEdit1KeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b' && Key!='-' && Key!='.')
	{
    	if(13 == Key)
        {
        	Key = 0;
        }
        else
        {
			Key=0;
			ShowMessage("������0��9֮������֣�");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TDealMistakeForm::cxButton3Click(TObject *Sender)
{
//�������
	if(cxTextEdit1->Text.IsEmpty())
	{
		ShowMessage("������д�������!");
		return;
	}

	double mistakemoney = 0;
	try
	{
		mistakemoney = StrToFloat(cxTextEdit1->Text);
	}
	catch(...)
	{
		ShowMessage("��������������Ϊ������ֵ������������!");
		cxTextEdit1->SelectAll();
		return;
	}

	if(0 == mistakemoney)
	{
		ShowMessage("�������Ϊ0�����������!");
		return;
	}
	//�������д��
	//������Ϊ���CARD,CARD_F,MX,Operatorlist,"^"Ϊ��Ǯ��"v"Ϊ��Ǯ��
	String Moutstr = "����ȷ��������������Ϊ����";
	Moutstr += mistakemoney;
	if(mrOk != MessageBox(this->Handle, Moutstr.t_str(), "ȷ���������", MB_OKCANCEL))
		return;

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

				if(querykh != tmpkh)
				{
					ShowMessage("�ÿ����ǸղŲ�ѯ�Ŀ�Ƭ���޷�����!");
					return;
                }

				tmpsycs = (int)synum[0]*256+(int)synum[1];
				tmpsycs++;
				unsigned char writesynum[2];
				writesynum[0] = (char)(tmpsycs/256);
				writesynum[1] = (char)(tmpsycs%256);

				tmpintye = (double)balance[1]*256*256+(double)balance[2]*256+(double)balance[3];
		  //		tmpye = tmpintye/100+ReChargeMoney;
				tmpye = tmpintye/100 + mistakemoney;

				unsigned char writebalance[4];
				double writetmpbalance = mistakemoney;
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

					ADOTable1->TableName = "HJL";
					ADOTable1->Active = true;
					if(mistakemoney>0)
						ADOTable1->InsertRecord(ARRAYOFCONST((bhstr,tmpkh,tmpye,mistakemoney,tmpsycs,"^",OperatorName,DateofLaunchCard)));
					else if(mistakemoney < 0)
						ADOTable1->InsertRecord(ARRAYOFCONST((bhstr,tmpkh,tmpye,mistakemoney,tmpsycs,"v",OperatorName,DateofLaunchCard)));
					/*
					String hjlsqlstr = "insert into HJL values(:BH,:KH,:YE,:JE,:SFLX,:CZY,:OPTIME)";
					HJLADOQ->Close();
					HJLADOQ->SQL->Clear();
					HJLADOQ->SQL->Add(hjlsqlstr);
					HJLADOQ->Parameters->ParamByName("BH")->Value = cxTextEdit7->Text;
					HJLADOQ->Parameters->ParamByName("KH")->Value = tmpkh;
					HJLADOQ->Parameters->ParamByName("YE")->Value = tmpye;
					HJLADOQ->Parameters->ParamByName("JE")->Value = ReChargeMoney;
					HJLADOQ->Parameters->ParamByName("SFLX")->Value = "a";
					HJLADOQ->Parameters->ParamByName("CZY")->Value = OperatorName;
					HJLADOQ->Parameters->ParamByName("OPTIME")->Value = DateofLaunchCard;
					HJLADOQ->ExecSQL();  */

					//����MX��
					ADOQuery1->Close();
					ADOQuery1->SQL->Clear();
					String sqlstr = "insert into MX values(:BH,:KH,:SF_YE,";
					sqlstr = sqlstr + ":SFJE,:SYCS,:SFRQ,:JYNO,";
					sqlstr = sqlstr + ":GZZID,:SFLX,:CZY,:SCRQ)";
					ADOQuery1->SQL->Add(sqlstr);
					ADOQuery1->Parameters->ParamByName("BH")->Value = bhstr;
					ADOQuery1->Parameters->ParamByName("KH")->Value = tmpkh;
					ADOQuery1->Parameters->ParamByName("SF_YE")->Value = tmpye;
					ADOQuery1->Parameters->ParamByName("SFJE")->Value = mistakemoney;
					ADOQuery1->Parameters->ParamByName("SYCS")->Value = tmpsycs;
					ADOQuery1->Parameters->ParamByName("SFRQ")->Value = DateofLaunchCard;
					ADOQuery1->Parameters->ParamByName("JYNO")->Value = 1002;
					ADOQuery1->Parameters->ParamByName("GZZID")->Value = 1;
					if(mistakemoney>0)
						ADOQuery1->Parameters->ParamByName("SFLX")->Value = "^";
					else if(mistakemoney < 0)
						ADOQuery1->Parameters->ParamByName("SFLX")->Value = "v";
					ADOQuery1->Parameters->ParamByName("CZY")->Value = OperatorName;
					ADOQuery1->Parameters->ParamByName("SCRQ")->Value = DateofLaunchCard;
					ADOQuery1->ExecSQL();
					ADOQuery1->Close();

					//����CK��
					ADOQuery1->SQL->Clear();
					sqlstr = "insert into CK values(:kh,:bh,:sf_ye,:sf_fl,:ckxj,";
					sqlstr += ":glf,:ckje,:lqbt,:xkje,:sycs,:sfrq,:jyno,:gzzid,:sflx,:CZY)";
					ADOQuery1->SQL->Add(sqlstr);
					ADOQuery1->Parameters->ParamByName("kh")->Value = tmpkh;
					ADOQuery1->Parameters->ParamByName("bh")->Value = bhstr;
					ADOQuery1->Parameters->ParamByName("sf_ye")->Value = tmpye;
					ADOQuery1->Parameters->ParamByName("sf_fl")->Value = 1;
					ADOQuery1->Parameters->ParamByName("ckxj")->Value = mistakemoney;
					ADOQuery1->Parameters->ParamByName("glf")->Value = 0;
					ADOQuery1->Parameters->ParamByName("ckje")->Value = mistakemoney;
					ADOQuery1->Parameters->ParamByName("lqbt")->Value = 0;
					ADOQuery1->Parameters->ParamByName("xkje")->Value = mistakemoney;
					ADOQuery1->Parameters->ParamByName("sycs")->Value = tmpsycs;
					ADOQuery1->Parameters->ParamByName("sfrq")->Value = DateofLaunchCard;
					ADOQuery1->Parameters->ParamByName("jyno")->Value = 1002;
					ADOQuery1->Parameters->ParamByName("gzzid")->Value = 1;
					if(mistakemoney>0)
						ADOQuery1->Parameters->ParamByName("SFLX")->Value = "^";
					else if(mistakemoney < 0)
						ADOQuery1->Parameters->ParamByName("SFLX")->Value = "v";
					ADOQuery1->Parameters->ParamByName("CZY")->Value = OperatorName;
					ADOQuery1->ExecSQL();
					ADOQuery1->Close();

					//��д������¼��
					sqlstr = "insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
					ADOQuery1->SQL->Clear();
					ADOQuery1->SQL->Add(sqlstr);
					ADOQuery1->Parameters->ParamByName("BH")->Value = bhstr;
					ADOQuery1->Parameters->ParamByName("KH")->Value = tmpkh;
					ADOQuery1->Parameters->ParamByName("JE")->Value = mistakemoney;
					ADOQuery1->Parameters->ParamByName("YE")->Value = tmpye;
					if(mistakemoney>0)
						ADOQuery1->Parameters->ParamByName("LX")->Value = "��ֵ����";
					else if(mistakemoney < 0)
						ADOQuery1->Parameters->ParamByName("LX")->Value = "��������";
					ADOQuery1->Parameters->ParamByName("Operator")->Value = OperatorName;
					ADOQuery1->Parameters->ParamByName("DateTime")->Value = DateofLaunchCard;
					ADOQuery1->ExecSQL();
					ADOQuery1->Close();

					//����CARD��CARD_F��

					sqlstr = "select * from CARD where BH='";
					sqlstr = sqlstr + bhstr + "'";
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
					sqlstr = sqlstr + bhstr + "'";
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
						ShowMessage("д�����󣬳�ֵʧ�ܣ�������!");
					//	ReChargeERRForm->ShowModal();
					}
					else
					{
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
							ShowMessage("��ֵ��������������!");
						//	ReChargeERRForm->ShowModal();
						}
						else if (1 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
						//	ReChargeERRForm->ShowModal();
						}
						else if (2 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
						//	ReChargeERRForm->ShowModal();
						}
						else if (4 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
						//	ReChargeERRForm->ShowModal();
						}
						else if (5 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
						//	ReChargeERRForm->ShowModal();
						}
						else if (6 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
						//	ReChargeERRForm->ShowModal();
						}
						else if (10 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
						//	ReChargeERRForm->ShowModal();
						}
						else if (0 != chkstatus)
						{
							ShowMessage("��ֵ��������������!");
						//	ReChargeERRForm->ShowModal();
						}
						else
						{
							double chktmpintye = ((double)chkbalance[1]*256*256+(double)chkbalance[2]*256+(double)chkbalance[3])/100;
							if(tmpye == chktmpintye)
							{
								ADOTable1->Delete();
								CQKLogStream<<"CK,"<<tmpkh<<","<<mistakemoney<<","<<DateofLaunchCard.t_str()<<","<<OperatorName.t_str()<<endl;
								beepofreaddll(readcomno, '10');
								String ReChargeOutstr = "�����ɹ�!�����Ϊ��";
								ReChargeOutstr += tmpye;
								ShowMessage(ReChargeOutstr);
							//	CZNoticForm->Panel1->Caption = ReChargeOutstr;
							//	CZNoticForm->ShowModal();
							//	ShowMessage(ReChargeOutstr);
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
//---------------------------------------------------------------------------

