// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GlobalParameter.h"
#include "CardRechargeFRM.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGraphics"
#pragma link "cxGroupBox"
#pragma link "cxLabel"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
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

#include "CZnoticeFRM.h"
#include "ReChargeERRFRM.h"
TCardRechargeMoneyFRM *CardRechargeMoneyFRM;

// ---------------------------------------------------------------------------
__fastcall TCardRechargeMoneyFRM::TCardRechargeMoneyFRM(TComponent* Owner)
: TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TCardRechargeMoneyFRM::ExitBTNClick(TObject *Sender) {
	// this->Release();
	this->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReadCardBTNClick(TObject *Sender) {
	WORD status;
	int tmpbalance;
	int tmpkh, tmpsycs;
	double tmpintye;
	double tmpye;
	unsigned char keymode, secnum, Delayms, mode;
	unsigned char key[6];
	unsigned char dwmm[6];
	unsigned char daytime[4];
	unsigned char kh[4];
	unsigned char balance[4];
	unsigned char cardtype[1];
	unsigned char czmm[3];
	unsigned char synum[3];

	Delayms = DelaySecond;
	keymode = CARDPasswordEdition;
	secnum = UsingSecNUM;

	key[0] = CARDPassword[0];
	key[1] = CARDPassword[1];
	key[2] = CARDPassword[2];
	key[3] = CARDPassword[3];
	key[4] = CARDPassword[4];
	key[5] = CARDPassword[5];

	cxTextEdit1->Text = "";
	cxTextEdit2->Text = "";
	cxTextEdit3->Text = "";
	cxTextEdit4->Text = "";
	cxTextEdit5->Text = "";
	cxTextEdit6->Text = "";
	cxTextEdit7->Text = "";
	cxTextEdit8->Text = "";
	cxTextEdit9->Text = "";
	cxTextEdit10->Text = "";
	cxTextEdit11->Text = "";
	cxTextEdit12->Text = "";
	cxTextEdit15->Text = "";
	cxTextEdit16->Text = "";
	cxTextEdit17->Text = "";
	cxTextEdit18->Text = "";

	if (LoadHModule) {
		if (readcardinfo) {
			status = readcardinfo(readcomno, keymode, secnum, key, kh, balance,
				dwmm, synum, daytime, cardtype, czmm, Delayms);

			if (status > 99) {
				ShowMessage("ͨѶ����");
			}
			else if (1 == status) {
				ShowMessage("��ѿ�Ƭ�źã�");
			}
			else if (2 == status) {
				ShowMessage("���Ŵ���192000�����0��");
			}
			else if (4 == status) {
				ShowMessage("��Ƭ���벻�ԣ�");
			}
			else if (5 == status) {
				ShowMessage("��д�����ȶ���");
			}
			else if (6 == status) {
				ShowMessage("���ṹ���ԣ�");
			}
			else if (10 == status) {
				ShowMessage("���ṹ���ԣ�");
			}
			else if (0 != status) {
				ShowMessage("�ÿ�δ���л����˿���");
			}
			else {
				ADOReChargeQuery->Close();
				ADOReChargeQuery->SQL->Clear();
				ADOReChargeQuery->SQL->Add("select * from XTSET");
				String mmstr = "";

				unsigned char tmpchar;
				tmpchar = dwmm[0];
				tmpchar = tmpchar >> 4;
				mmstr += (int)tmpchar;

				tmpchar = dwmm[0];
				tmpchar = tmpchar << 4;
				tmpchar = tmpchar >> 4;
				mmstr += (int)tmpchar;

				tmpchar = dwmm[1];
				tmpchar = tmpchar >> 4;
				mmstr += (int)tmpchar;

				tmpchar = dwmm[1];
				tmpchar = tmpchar << 4;
				tmpchar = tmpchar >> 4;
				mmstr += (int)tmpchar;

				ADOReChargeQuery->Close();

				String tmpstr;
				tmpkh = (int)kh[1] * 256 * 256 + (int)kh[2] * 256 + (int)kh[3];
				tmpsycs = (int)synum[0] * 256 + (int)synum[1];
				tmpintye = (double)balance[1] * 256 * 256 + (double)
				balance[2] * 256 + (double)balance[3];
				tmpye = tmpintye / 100;


                //check FK and HF
                int FKS,HFS;
                unsigned char sendbuflen = 26;
                unsigned char sendbuf[26];
                ZeroMemory(sendbuf,26);
                unsigned char recbuf[140];
                unsigned char recbuflen;
                ZeroMemory(recbuf, 140);
                unsigned char createCRC[16];
                unsigned char CRC[2];
                ZeroMemory(createCRC, 16);
                ZeroMemory(CRC, 2);

                sendbuf[0] = (secnum+1)*4+1;//������4+���
                sendbuf[1] = 0x60;//�̶�Ϊ0x60
                sendbuf[2] = 1;//�����֣�1Ϊ����2Ϊд
                sendbuf[3] = keymode;
                sendbuf[4] = key[0];
                sendbuf[5] = key[1];
                sendbuf[6] = key[2];
                sendbuf[7] = key[3];
                sendbuf[8] = key[4];
                sendbuf[9] = key[5];

                memcpy(createCRC, &sendbuf[10], 16);
                CRCProc(createCRC, 14, CRC);
                sendbuf[24] = CRC[0];
                sendbuf[25] = CRC[1];

                WORD limitStatus = pacarddllproc(readcomno,sendbuflen,sendbuf,&recbuflen,recbuf,Delayms);

                if((0 != limitStatus)||(0 != recbuf[2]))
                {
                    beepofreaddll(readcomno, '10');
                    ShowMessage("������һ���������ʧ�ܣ�");
                    return;
                }
                else if((0 == limitStatus)||(0 == recbuf[2]))
                {
                 	//here confirm fk and hf
                 	unsigned char precbuf[16];
					ZeroMemory(precbuf, 16);
					memcpy(precbuf, &recbuf[10], 16);
			   //		if((0x55 == precbuf[14])&&(0xaa == precbuf[15]))
					{
                    	FKS = precbuf[0];
                        HFS = precbuf[2];
                    }
                }
                //end check

				ADOReChargeQuery->Close();
				ADOReChargeQuery->SQL->Clear();
				tmpstr = "select * from KZT where kh=";
				tmpstr += tmpkh;
				ADOReChargeQuery->SQL->Add(tmpstr);
				ADOReChargeQuery->Open();
				if (!ADOReChargeQuery->IsEmpty()) {
					if (0 != ADOReChargeQuery->FieldByName("GS")->AsInteger) {
						ShowMessage("�˿��ѹ�ʧ����û�մ˿���");
						ADOReChargeQuery->Close();
						return;
					}
				}
				else {
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOReChargeQuery->Close();
					return;
				}
				ADOReChargeQuery->Close();

				ADOReChargeQuery->SQL->Clear();
				tmpstr = "select * from CARD where kh=";
				tmpstr += tmpkh;
				ADOReChargeQuery->SQL->Add(tmpstr);
				ADOReChargeQuery->Open();
				if (!ADOReChargeQuery->IsEmpty()) {
					cxTextEdit7->Text = ADOReChargeQuery->FieldByName("BH")
					->AsString;
					cxTextEdit2->Text = ADOReChargeQuery->FieldByName("XM")
					->AsString;
					cxTextEdit11->Text = ADOReChargeQuery->FieldByName("SFZH")
					->AsString;
					cxTextEdit12->Text = ADOReChargeQuery->FieldByName("GRMM")
					->AsString;
					cxTextEdit17->Text = ADOReChargeQuery->FieldByName("YJ")
					->AsString;
					cxTextEdit3->Text = ADOReChargeQuery->FieldByName("BM")
					->AsString;
					cxTextEdit15->Text = ADOReChargeQuery->FieldByName("SF_FL")
					->AsString;
					cxTextEdit4->Text = ADOReChargeQuery->FieldByName("ZW")
					->AsString;
					cxTextEdit10->Text = ADOReChargeQuery->FieldByName("ZB")
					->AsString;
					cxTextEdit9->Text = ADOReChargeQuery->FieldByName("BZ")
					->AsString;
					cxTextEdit8->Text = ADOReChargeQuery->FieldByName("XB")
					->AsString;

                    if((FKS == ADOReChargeQuery->FieldByName("FK")->AsInteger)&&(HFS == ADOReChargeQuery->FieldByName("HF")->AsInteger))
                    {
                        cxTextEdit1->Text = tmpkh;
                        // cxTextEdit16->Text = tmpsycs;
                        cxTextEdit18->Text = tmpye;
                        cxTextEdit6->Text = cardtype[0]; // ??
                        cxTextEdit5->Text = cardtype[0];
                        ReChargeBTN->Enabled = true;
                        ReCharge5BTN->Enabled = true;
                        ReCharge10BTN->Enabled = true;
                        ReCharge20BTN->Enabled = true;
                        ReCharge30BTN->Enabled = true;
                        ReCharge40BTN->Enabled = true;
                        ReCharge50BTN->Enabled = true;
                        ReCharge60BTN->Enabled = true;
                        ReCharge70BTN->Enabled = true;
                        ReCharge80BTN->Enabled = true;
                        ReCharge90BTN->Enabled = true;
                        ReCharge100BTN->Enabled = true;
                        ReCharge150BTN->Enabled = true;
                        ReCharge200BTN->Enabled = true;
                        ReCharge500BTN->Enabled = true;
                        ReCharge1000BTN->Enabled = true;
                        cxButton1->Enabled = true;
                        cxButton2->Enabled = true;
                        cxButton3->Enabled = true;
                        cxButton4->Enabled = true;
                        cxButton5->Enabled = true;
                        beepofreaddll(readcomno, '10');
                        cxTextEdit16->SetFocus();
                    }
                    else
                    {
                        ShowMessage("���ѹ�ʧ!");
                        return;
                    }
                    ADOReChargeQuery->Close();
					// ReadCardBTN->Enabled = false;
				}
				else {
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOReChargeQuery->Close();
				}
			}
		}
	}
	else
		ShowMessage("���ض�д����̬���ӿ�ʧ�ܣ�");
}
// ---------------------------------------------------------------------------

// -----------------��ֵ����begin---------------------/
void __fastcall TCardRechargeMoneyFRM::Function_ReCharge(double ReChargeMoney) {
	// ShowMessage("��ֵ��ʼ!");
	// String Moutstr = "��ȷ�϶Ըÿ���ֵ";
	// Moutstr += ReChargeMoney;
	// Moutstr += "Ԫ��?";
	// if(mrOk != MessageBox(this->Handle, Moutstr.t_str(), "ȷ�ϳ�ֵ���", MB_OKCANCEL))
	// return;

	Panel1->Caption = "��ʼ��ֵ����!";
	WORD status;
	WORD WriteStatus;
	int tmpbalance;
	int tmpkh, tmpsycs;
	double tmpintye;
	double tmpye;
	unsigned char keymode, secnum, Delayms, mode;
	unsigned char key[6];
	unsigned char dwmm[6];
	unsigned char daytime[4];
	unsigned char kh[4];
	unsigned char balance[4];
	unsigned char cardtype[1];
	unsigned char czmm[3];
	unsigned char synum[3];

	Delayms = DelaySecond; // 0x00;
	keymode = CARDPasswordEdition;
	mode = 0x01;
	secnum = UsingSecNUM;

	key[0] = CARDPassword[0];
	key[1] = CARDPassword[1];
	key[2] = CARDPassword[2];
	key[3] = CARDPassword[3];
	key[4] = CARDPassword[4];
	key[5] = CARDPassword[5];

	if (LoadHModule)
	{
		if (readcardinfo)
		{
			// ShowMessage("begin read card!");
			status = readcardinfo(readcomno, keymode, secnum, key, kh, balance,
				dwmm, synum, daytime, cardtype, czmm, Delayms);

			if (status > 99)
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
			else if (5 == status) {
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
				tmpkh = (int)kh[1] * 256 * 256 + (int)kh[2] * 256 + (int)kh[3];
                int chkkh = StrToInt(cxTextEdit1->Text);
                if(chkkh != tmpkh)
                {
                    ShowMessage("������������Ų�ƥ�䣬�벻Ҫ������Ƭ!");
        			ReChargeBTN->Enabled = false;
                    ReCharge5BTN->Enabled = false;
                    ReCharge10BTN->Enabled = false;
                    ReCharge20BTN->Enabled = false;
                    ReCharge30BTN->Enabled = false;
                    ReCharge40BTN->Enabled = false;
                    ReCharge50BTN->Enabled = false;
                    ReCharge60BTN->Enabled = false;
                    ReCharge70BTN->Enabled = false;
                    ReCharge80BTN->Enabled = false;
                    ReCharge90BTN->Enabled = false;
                    ReCharge100BTN->Enabled = false;
                    ReCharge150BTN->Enabled = false;
                    ReCharge200BTN->Enabled = false;
                    ReCharge500BTN->Enabled = false;
                    ReCharge1000BTN->Enabled = false;
                    cxButton1->Enabled = false;
                    cxButton2->Enabled = false;
                    cxButton3->Enabled = false;
                    cxButton4->Enabled = false;
                    cxButton5->Enabled = false;
                    ReadCardBTN->Enabled = true;
                    return;
                }

				//ʹ��pacarddll��ȡ������Ѽ�¼
				unsigned char sendbuf[26];
				unsigned char sendbuflen = 26;
				unsigned char senddelay = Delayms;
				unsigned char recbuf[140];
				unsigned char recbuflen;
				unsigned char pblock = (secnum+2)*4+0;
				unsigned char pmimamode = 0x60;
				unsigned char pcommand = 0x01;
				unsigned char pkeymode = 0x03;
				unsigned char pkey[6];
				memcpy(pkey,CARDPassword,6);
				unsigned char comno[5];
				memcpy(comno,readcomno,5);

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

				WORD pstatus;
				pstatus = pacarddllproc(comno,sendbuflen,sendbuf,&recbuflen,recbuf,senddelay);
				if((0 == pstatus)&&(0 == recbuf[2]))
				{
					//���
					unsigned char precbuf[16];
					ZeroMemory(precbuf, 16);
					memcpy(precbuf, &recbuf[10], 16);
					if((0x55 == precbuf[14])&&(0xaa == precbuf[15]))
					{
						double xf1;
						double xf2;
						int jqh;
						int cjkh;
						xf1 = ((double)precbuf[0]+(double)precbuf[1]*256+
								(double)precbuf[2]*256*256+(double)precbuf[3]*256*256*256)/100;
						xf2 = ((double)(precbuf[4]^0xff)+(double)(precbuf[5]^0xff)*256+
								(double)(precbuf[6]^0xff)*256*256+(double)(precbuf[7]^0xff)*256*256*256)/100;
						if(xf1 == xf2)
						{
							jqh = (int)precbuf[8]*256+(int)precbuf[9];
							cjkh = (int)precbuf[10]*256*256*256+(int)precbuf[11]*256*256+
									(int)precbuf[12]*256+(int)precbuf[13];
							//������
							ADOReChargeQuery->Close();
							String tjsqlstr = "insert into WTJ values(:JH,:CJKH,:XFZE,:SCSJ)";
							ADOReChargeQuery->SQL->Clear();
							ADOReChargeQuery->SQL->Add(tjsqlstr);
							ADOReChargeQuery->Parameters->ParamByName("JH")->Value = jqh;
							ADOReChargeQuery->Parameters->ParamByName("CJKH")->Value = cjkh;
							ADOReChargeQuery->Parameters->ParamByName("XFZE")->Value = xf1;
							ADOReChargeQuery->Parameters->ParamByName("SCSJ")->Value = DateTimeToStr(Now());
							ADOReChargeQuery->ExecSQL();
						}
					}
				}
				//end of pacarddll

				tmpsycs = (int)synum[0] * 256 + (int)synum[1];
				tmpsycs++;
				unsigned char writesynum[2];
				writesynum[0] = (char)(tmpsycs / 256);
				writesynum[1] = (char)(tmpsycs % 256);

				tmpintye = (double)balance[1] * 256 * 256 + (double)
					balance[2] * 256 + (double)balance[3];
				// tmpye = tmpintye/100+ReChargeMoney;
				tmpye = tmpintye / 100 + ReChargeMoney;

				unsigned char writebalance[4];
				double writetmpbalance = ReChargeMoney;
				writetmpbalance *= 100;
				writebalance[0] = 0x00;
				writebalance[1] = (unsigned char)((int)writetmpbalance / 65536);
				writetmpbalance = (int)writetmpbalance % 65536;
				writebalance[2] = (unsigned char)((int)writetmpbalance / 256);
				writetmpbalance = (int)writetmpbalance % 256;
				writebalance[3] = (unsigned char)writetmpbalance;

				if (LaunchNewCard)
				{
					// ShowMessage("begin write card");
					String DateofLaunchCard;
					SYSTEMTIME tmpsystime;
					GetLocalTime(&tmpsystime);
					DateofLaunchCard = DateTimeToStr
						(SystemTimeToDateTime(tmpsystime));

					ADOTable1->TableName = "HJL";
					ADOTable1->Active = true;
					ADOTable1->InsertRecord
						(ARRAYOFCONST((cxTextEdit7->Text, tmpkh, tmpye,
								ReChargeMoney, tmpsycs, "a", OperatorName,
								DateofLaunchCard)));
					/* String hjlsqlstr = "insert into HJL values(:BH,:KH,:YE,:JE,:SFLX,:CZY,:OPTIME)";
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
					HJLADOQ->ExecSQL(); */

					WriteStatus = LaunchNewCard(readcomno, keymode, secnum,
						key, kh, writebalance, dwmm, writesynum, daytime,
						cardtype, czmm, mode, Delayms);
					if (WriteStatus)
					{
						WORD chkstatus;
						WORD chkWriteStatus;
						int chktmpbalance;
						int chktmpkh, chktmpsycs;
						double chktmpintye;
						double chktmpye;
						unsigned char chkkeymode, chksecnum, chkDelayms,
						chkmode;
						unsigned char chkkey[6];
						unsigned char chkdwmm[6];
						unsigned char chkdaytime[4];
						unsigned char chkkh[4];
						unsigned char chkbalance[4];
						unsigned char chkcardtype[1];
						unsigned char chkczmm[3];
						unsigned char chksynum[3];

						chkDelayms = DelaySecond; // 0x00;
						chkkeymode = CARDPasswordEdition;
						chkmode = 0x01;
						chksecnum = UsingSecNUM;

						chkkey[0] = CARDPassword[0];
						chkkey[1] = CARDPassword[1];
						chkkey[2] = CARDPassword[2];
						chkkey[3] = CARDPassword[3];
						chkkey[4] = CARDPassword[4];
						chkkey[5] = CARDPassword[5];

						chkstatus = readcardinfo(readcomno, chkkeymode,
							chksecnum, chkkey, chkkh, chkbalance, chkdwmm,
							chksynum, chkdaytime, chkcardtype, chkczmm,
							chkDelayms);
						if (chkstatus > 99)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (1 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (2 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (4 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (5 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (6 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (10 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (0 != chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else
						{
							double chktmpintye =
								((double)chkbalance[1] * 256 * 256 + (double)
								chkbalance[2] * 256 + (double)chkbalance[3])
								/ 100;
							if (tmpye == chktmpintye)
							{
								// ����MX��
								ADOReChargeQuery->Close();
								ADOReChargeQuery->SQL->Clear();
								String sqlstr =
									"insert into MX values(:BH,:KH,:SF_YE,";
								sqlstr = sqlstr + ":SFJE,:SYCS,:SFRQ,:JYNO,";
								sqlstr = sqlstr + ":GZZID,:SFLX,:CZY,:SCRQ)";
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Parameters->ParamByName("BH")->Value = cxTextEdit7->Text;
								ADOReChargeQuery->Parameters->ParamByName("KH")->Value = tmpkh;
								ADOReChargeQuery->Parameters->ParamByName("SF_YE")->Value = tmpye;
								ADOReChargeQuery->Parameters->ParamByName("SFJE")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("SYCS")->Value = tmpsycs;
								ADOReChargeQuery->Parameters->ParamByName("SFRQ")->Value = DateofLaunchCard;
								ADOReChargeQuery->Parameters->ParamByName("JYNO")->Value = 1001;
								ADOReChargeQuery->Parameters->ParamByName("GZZID")->Value = 1;
								ADOReChargeQuery->Parameters->ParamByName("SFLX")->Value = "a";
								ADOReChargeQuery->Parameters->ParamByName("CZY")->Value = OperatorName;
								ADOReChargeQuery->Parameters->ParamByName("SCRQ")->Value = DateofLaunchCard;
								ADOReChargeQuery->ExecSQL();
								ADOReChargeQuery->Close();

								// ����CK��
								ADOReChargeQuery->SQL->Clear();
								sqlstr =
									"insert into CK values(:kh,:bh,:sf_ye,:sf_fl,:ckxj,";
								sqlstr +=
									":glf,:ckje,:lqbt,:xkje,:sycs,:sfrq,:jyno,:gzzid,:sflx,:CZY)";
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Parameters->ParamByName("kh")->Value = tmpkh;
								ADOReChargeQuery->Parameters->ParamByName("bh")->Value = cxTextEdit7->Text;
								ADOReChargeQuery->Parameters->ParamByName("sf_ye")->Value = tmpye;
								ADOReChargeQuery->Parameters->ParamByName("sf_fl")->Value = 1;
								ADOReChargeQuery->Parameters->ParamByName("ckxj")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("glf")->Value = 0;
								ADOReChargeQuery->Parameters->ParamByName("ckje")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("lqbt")->Value = 0;
								ADOReChargeQuery->Parameters->ParamByName("xkje")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("sycs")->Value = tmpsycs;
								ADOReChargeQuery->Parameters->ParamByName("sfrq")->Value = DateofLaunchCard;
								ADOReChargeQuery->Parameters->ParamByName("jyno")->Value = 1001;
								ADOReChargeQuery->Parameters->ParamByName("gzzid")->Value = 1;
								ADOReChargeQuery->Parameters->ParamByName("sflx")->Value = "a";
								ADOReChargeQuery->Parameters->ParamByName("CZY")->Value = OperatorName;
								ADOReChargeQuery->ExecSQL();
								ADOReChargeQuery->Close();

								// ��д������¼��
								sqlstr =
									"insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
								ADOReChargeQuery->SQL->Clear();
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Parameters->ParamByName("BH")->Value = cxTextEdit7->Text;
								ADOReChargeQuery->Parameters->ParamByName("KH")->Value = tmpkh;
								ADOReChargeQuery->Parameters->ParamByName("JE")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("YE")->Value = tmpye;
								ADOReChargeQuery->Parameters->ParamByName("LX")->Value = "��ֵ";
								ADOReChargeQuery->Parameters->ParamByName("Operator")->Value = OperatorName;
								ADOReChargeQuery->Parameters->ParamByName("DateTime")->Value = DateofLaunchCard;
								ADOReChargeQuery->ExecSQL();
								ADOReChargeQuery->Close();

								// ����CARD��CARD_F��

								sqlstr = "select * from CARD where BH='";
								sqlstr = sqlstr + cxTextEdit7->Text + "'";
								ADOReChargeQuery->SQL->Clear();
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Open();
								if (!ADOReChargeQuery->IsEmpty())
								{
									ADOReChargeQuery->Edit();
									ADOReChargeQuery->FieldByName("SF_YE")->AsFloat = tmpye;
									ADOReChargeQuery->FieldByName("SFYEDT")->AsDateTime = StrToDateTime(DateofLaunchCard);
									ADOReChargeQuery->FieldByName("SYCS")->AsInteger = tmpsycs;
									ADOReChargeQuery->Post();
								}

								ADOReChargeQuery->Close();
								sqlstr = "select * from CARD_F where BH='";
								sqlstr = sqlstr + cxTextEdit7->Text + "'";
								ADOReChargeQuery->SQL->Clear();
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Open();
								if (!ADOReChargeQuery->IsEmpty())
								{
									ADOReChargeQuery->Edit();
									ADOReChargeQuery->FieldByName("SF_YE")->AsFloat = tmpye;
									ADOReChargeQuery->FieldByName("SFYEDT")->AsDateTime = StrToDateTime(DateofLaunchCard);
									ADOReChargeQuery->FieldByName("SYCS")->AsInteger = tmpsycs;
									ADOReChargeQuery->Post();
								}

								ADOReChargeQuery->Close();

								ADOTable1->Delete();
								CQKLogStream << "CK," << tmpkh << "," <<
									ReChargeMoney << "," <<
									DateofLaunchCard.t_str()
									<< "," << OperatorName.t_str() << endl;
								String ReChargeOutstr = "��ֵ�ɹ�!�����Ϊ��";
								ReChargeOutstr += tmpye;
								Panel1->Caption = ReChargeOutstr;
								// CZNoticForm->Panel1->Caption = ReChargeOutstr;
								// CZNoticForm->ShowModal();
								beepofreaddll(readcomno, '10');
								// ShowMessage(ReChargeOutstr);
							}
							else
							{
								ShowMessage("д�����󣬳�ֵʧ�ܣ�������!");
								ReChargeERRForm->ShowModal();
							}
						}
					}
					else
					{
						WORD chkstatus;
						WORD chkWriteStatus;
						int chktmpbalance;
						int chktmpkh, chktmpsycs;
						double chktmpintye;
						double chktmpye;
						unsigned char chkkeymode, chksecnum, chkDelayms,
						chkmode;
						unsigned char chkkey[6];
						unsigned char chkdwmm[6];
						unsigned char chkdaytime[4];
						unsigned char chkkh[4];
						unsigned char chkbalance[4];
						unsigned char chkcardtype[1];
						unsigned char chkczmm[3];
						unsigned char chksynum[3];

						chkDelayms = DelaySecond; // 0x00;
						chkkeymode = CARDPasswordEdition;
						chkmode = 0x01;
						chksecnum = UsingSecNUM;

						chkkey[0] = CARDPassword[0];
						chkkey[1] = CARDPassword[1];
						chkkey[2] = CARDPassword[2];
						chkkey[3] = CARDPassword[3];
						chkkey[4] = CARDPassword[4];
						chkkey[5] = CARDPassword[5];

						chkstatus = readcardinfo(readcomno, chkkeymode,
							chksecnum, chkkey, chkkh, chkbalance, chkdwmm,
							chksynum, chkdaytime, chkcardtype, chkczmm,
							chkDelayms);
						if (chkstatus > 99)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (1 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (2 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (4 == chkstatus)
						 {
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (5 == chkstatus)
						 {
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (6 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (10 == chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else if (0 != chkstatus)
						{
							ShowMessage("��ֵ��������������!");
							ReChargeERRForm->ShowModal();
						}
						else {
							double chktmpintye =
								((double)chkbalance[1] * 256 * 256 + (double)
								chkbalance[2] * 256 + (double)chkbalance[3])
								/ 100;
							if (tmpye == chktmpintye)
							{
								// ����MX��
								ADOReChargeQuery->Close();
								ADOReChargeQuery->SQL->Clear();
								String sqlstr =
									"insert into MX values(:BH,:KH,:SF_YE,";
								sqlstr = sqlstr + ":SFJE,:SYCS,:SFRQ,:JYNO,";
								sqlstr = sqlstr + ":GZZID,:SFLX,:CZY,:SCRQ)";
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Parameters->ParamByName("BH")->Value = cxTextEdit7->Text;
								ADOReChargeQuery->Parameters->ParamByName("KH")->Value = tmpkh;
								ADOReChargeQuery->Parameters->ParamByName("SF_YE")->Value = tmpye;
								ADOReChargeQuery->Parameters->ParamByName("SFJE")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("SYCS")->Value = tmpsycs;
								ADOReChargeQuery->Parameters->ParamByName("SFRQ")->Value = DateofLaunchCard;
								ADOReChargeQuery->Parameters->ParamByName("JYNO")->Value = 1001;
								ADOReChargeQuery->Parameters->ParamByName("GZZID")->Value = 1;
								ADOReChargeQuery->Parameters->ParamByName("SFLX")->Value = "a";
								ADOReChargeQuery->Parameters->ParamByName("CZY")->Value = OperatorName;
								ADOReChargeQuery->Parameters->ParamByName("SCRQ")->Value = DateofLaunchCard;
								ADOReChargeQuery->ExecSQL();
								ADOReChargeQuery->Close();

								// ����CK��
								ADOReChargeQuery->SQL->Clear();
								sqlstr =
									"insert into CK values(:kh,:bh,:sf_ye,:sf_fl,:ckxj,";
								sqlstr +=
									":glf,:ckje,:lqbt,:xkje,:sycs,:sfrq,:jyno,:gzzid,:sflx,:CZY)";
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Parameters->ParamByName("kh")->Value = tmpkh;
								ADOReChargeQuery->Parameters->ParamByName("bh")->Value = cxTextEdit7->Text;
								ADOReChargeQuery->Parameters->ParamByName("sf_ye")->Value = tmpye;
								ADOReChargeQuery->Parameters->ParamByName("sf_fl")->Value = 1;
								ADOReChargeQuery->Parameters->ParamByName("ckxj")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("glf")->Value = 0;
								ADOReChargeQuery->Parameters->ParamByName("ckje")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("lqbt")->Value = 0;
								ADOReChargeQuery->Parameters->ParamByName("xkje")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("sycs")->Value = tmpsycs;
								ADOReChargeQuery->Parameters->ParamByName("sfrq")->Value = DateofLaunchCard;
								ADOReChargeQuery->Parameters->ParamByName("jyno")->Value = 1001;
								ADOReChargeQuery->Parameters->ParamByName("gzzid")->Value = 1;
								ADOReChargeQuery->Parameters->ParamByName("sflx")->Value = "a";
								ADOReChargeQuery->Parameters->ParamByName("CZY")->Value = OperatorName;
								ADOReChargeQuery->ExecSQL();
								ADOReChargeQuery->Close();

								// ��д������¼��
								sqlstr =
									"insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
								ADOReChargeQuery->SQL->Clear();
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Parameters->ParamByName("BH")->Value = cxTextEdit7->Text;
								ADOReChargeQuery->Parameters->ParamByName("KH")->Value = tmpkh;
								ADOReChargeQuery->Parameters->ParamByName("JE")->Value = ReChargeMoney;
								ADOReChargeQuery->Parameters->ParamByName("YE")->Value = tmpye;
								ADOReChargeQuery->Parameters->ParamByName("LX")->Value = "��ֵ";
								ADOReChargeQuery->Parameters->ParamByName("Operator")->Value = OperatorName;
								ADOReChargeQuery->Parameters->ParamByName("DateTime")->Value = DateofLaunchCard;
								ADOReChargeQuery->ExecSQL();
								ADOReChargeQuery->Close();

								// ����CARD��CARD_F��

								sqlstr = "select * from CARD where BH='";
								sqlstr = sqlstr + cxTextEdit7->Text + "'";
								ADOReChargeQuery->SQL->Clear();
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Open();
								if (!ADOReChargeQuery->IsEmpty())
								{
									ADOReChargeQuery->Edit();
									ADOReChargeQuery->FieldByName("SF_YE")->AsFloat = tmpye;
									ADOReChargeQuery->FieldByName("SFYEDT")->AsDateTime = StrToDateTime(DateofLaunchCard);
									ADOReChargeQuery->FieldByName("SYCS")->AsInteger = tmpsycs;
									ADOReChargeQuery->Post();
								}

								ADOReChargeQuery->Close();
								sqlstr = "select * from CARD_F where BH='";
								sqlstr = sqlstr + cxTextEdit7->Text + "'";
								ADOReChargeQuery->SQL->Clear();
								ADOReChargeQuery->SQL->Add(sqlstr);
								ADOReChargeQuery->Open();
								if (!ADOReChargeQuery->IsEmpty())
								{
									ADOReChargeQuery->Edit();
									ADOReChargeQuery->FieldByName("SF_YE")->AsFloat = tmpye;
									ADOReChargeQuery->FieldByName("SFYEDT")->AsDateTime = StrToDateTime(DateofLaunchCard);
									ADOReChargeQuery->FieldByName("SYCS")->AsInteger = tmpsycs;
									ADOReChargeQuery->Post();
								}

								ADOReChargeQuery->Close();

								// д���ܹ���ֵ�ܶ�
                                if(DOGChk)
                                {
                                    unsigned char tempbuf[8];
                                    SFK_ZE += ReChargeMoney;
                                    UpZETable->FieldByName("SFKZE")->AsFloat += ReChargeMoney;
                                     memcpy(tempbuf,&SFK_ZE,8);
                                    unsigned char hightempchar1;
                                    unsigned char lowtempchar1;
                                    for(int t = 0; t < 8; t++)
                                    {
                                    hightempchar1 = tempbuf[t]&0xf0;
                                    lowtempchar1 = tempbuf[t]&0x0f;

                                    hightempchar1 = hightempchar1>>4;
                                    hightempchar1 = hightempchar1&0x0f;

                                    lowtempchar1 = lowtempchar1<<4;
                                    lowtempchar1 = lowtempchar1&0xf0;

                                    tempbuf[t] = hightempchar1|lowtempchar1;
                                    }
                                    int dogoffset = 0x0034;
                                    int doglen = 8;
                                    RY3_Write(doghandle,dogoffset,tempbuf,doglen);
                                }
								// д���ܹ����

								ADOTable1->Delete();
								CQKLogStream << "CK," << tmpkh << "," <<
									ReChargeMoney << "," <<
									DateofLaunchCard.t_str()
									<< "," << OperatorName.t_str() << endl;
								String ReChargeOutstr = "��ֵ�ɹ�!�����Ϊ��";
								ReChargeOutstr += tmpye;
								Panel1->Caption = ReChargeOutstr;
								// CZNoticForm->Panel1->Caption = ReChargeOutstr;
								// CZNoticForm->ShowModal();
								beepofreaddll(readcomno, '10');
								// ShowMessage(ReChargeOutstr);
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

	// ShowMessage("��ֵ������");
	ReChargeBTN->Enabled = false;
	ReCharge5BTN->Enabled = false;
	ReCharge10BTN->Enabled = false;
	ReCharge20BTN->Enabled = false;
	ReCharge30BTN->Enabled = false;
	ReCharge40BTN->Enabled = false;
	ReCharge50BTN->Enabled = false;
	ReCharge60BTN->Enabled = false;
	ReCharge70BTN->Enabled = false;
	ReCharge80BTN->Enabled = false;
	ReCharge90BTN->Enabled = false;
	ReCharge100BTN->Enabled = false;
	ReCharge150BTN->Enabled = false;
	ReCharge200BTN->Enabled = false;
	ReCharge500BTN->Enabled = false;
	ReCharge1000BTN->Enabled = false;
	cxButton1->Enabled = false;
	cxButton2->Enabled = false;
	cxButton3->Enabled = false;
	cxButton4->Enabled = false;
	cxButton5->Enabled = false;
	ReadCardBTN->Enabled = true;

	/* cxTextEdit1->Text = "";
	cxTextEdit2->Text = "";
	cxTextEdit3->Text = "";
	cxTextEdit4->Text = "";
	cxTextEdit5->Text = "";
	cxTextEdit6->Text = "";
	cxTextEdit7->Text = "";
	cxTextEdit8->Text = "";
	cxTextEdit9->Text = "";
	cxTextEdit10->Text = "";
	cxTextEdit11->Text = "";
	cxTextEdit12->Text = "";
	cxTextEdit15->Text = "";
	cxTextEdit16->Text = "";
	cxTextEdit17->Text = "";
	cxTextEdit18->Text = ""; */
	cxTextEdit18->Text = tmpye;
	return;
}
// -----------------��ֵ����end---------------------/

// --------------------------------------------------------------------
void __fastcall TCardRechargeMoneyFRM::cxTextEdit16KeyPress(TObject *Sender,
	wchar_t &Key)
{
	if ((Key < '0' || Key > '9') && Key != '\b' && Key != VK_RETURN)
	{
    	Key = 0;
    	ShowMessage("������0��9֮�������!");
	}
    else
    {
        if (Key == VK_RETURN)
			ReChargeBTN->Click();
    }
/*	if ((Key < '0' || Key > '9') && Key != '\b' && Key != VK_RETURN)
	{
		if (Key != '.' && Key != VK_RETURN)
		{
			Key = 0;
			ShowMessage("������0��9֮�������!");
		}

		if (Key == VK_RETURN)
			ReChargeBTN->Click();
	}
    else
    {
        ShowMessage("������0��9֮�������!");
    }     */
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReChargeBTNClick(TObject *Sender)
{
	if (cxTextEdit16->Text.Length() > 0)
	{
		double ReChargeMoney = StrToFloat(cxTextEdit16->Text);
		if (ReChargeMoney == 0)
		{
			ShowMessage("��ֵ����Ϊ0");
			cxTextEdit16->Text = "";
		}
		/* else if(ReChargeMoney > 5000)
		{
		ShowMessage("��ֵ���ܴ���5000");
		cxTextEdit16->Text = "";
		} */
		else
		{
			Function_ReCharge(ReChargeMoney);
		}
	}
	else {
		ShowMessage("�������ֵ��");
	}
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge5BTNClick(TObject *Sender)
{
	Function_ReCharge(5);

}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge10BTNClick(TObject *Sender)
{
	Function_ReCharge(10);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge20BTNClick(TObject *Sender)
{
	Function_ReCharge(20);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge30BTNClick(TObject *Sender)
{
	Function_ReCharge(30);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge40BTNClick(TObject *Sender)
{
	Function_ReCharge(40);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge50BTNClick(TObject *Sender)
{
	Function_ReCharge(50);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge60BTNClick(TObject *Sender)
{
	Function_ReCharge(60);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge70BTNClick(TObject *Sender)
{
	Function_ReCharge(70);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge80BTNClick(TObject *Sender)
{
	Function_ReCharge(80);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge90BTNClick(TObject *Sender)
{
	Function_ReCharge(90);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge100BTNClick(TObject *Sender)
{
	Function_ReCharge(100);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge150BTNClick(TObject *Sender)
{
	Function_ReCharge(150);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge200BTNClick(TObject *Sender)
{
	Function_ReCharge(200);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge500BTNClick(TObject *Sender)
{
	Function_ReCharge(300);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::ReCharge1000BTNClick(TObject *Sender)
{
	Function_ReCharge(350);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::cxTextEdit16Exit(TObject *Sender)
{
	if (!cxTextEdit16->Text.IsEmpty() && !cxTextEdit18->Text.IsEmpty())
	{
		double trydouble;
		try
		{
			trydouble = StrToFloat(cxTextEdit16->Text);
		}
		catch(...)
		{
			ShowMessage("������ĳ�ֵ��������⣬����������!");
			cxTextEdit16->Text = "";
			return;
		}

		if ((StrToFloat(cxTextEdit16->Text) + StrToFloat(cxTextEdit18->Text))
			>= 100000)
		{
			ShowMessage("��ֵ��������ע���ֵ�������ܴ���100000������������!");
			cxTextEdit16->Text = "";
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::cxButton1Click(TObject *Sender)
{
	Function_ReCharge(400);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::cxButton2Click(TObject *Sender)
{
	Function_ReCharge(450);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::cxButton3Click(TObject *Sender)
{
	Function_ReCharge(500);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::cxButton4Click(TObject *Sender)
{
	Function_ReCharge(550);
}
// ---------------------------------------------------------------------------

void __fastcall TCardRechargeMoneyFRM::cxButton5Click(TObject *Sender)
{
	Function_ReCharge(600);
}
// ---------------------------------------------------------------------------
