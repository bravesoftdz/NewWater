//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WithDrawERRFRM.h"
//---------------------------------------------------------------------------
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
TWithDrawERRForm *WithDrawERRForm;
#include "CardWithDrawFRM.h"
#include "GlobalParameter.h"
//---------------------------------------------------------------------------
__fastcall TWithDrawERRForm::TWithDrawERRForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWithDrawERRForm::FormShow(TObject *Sender)
{
	cxTextEdit1->Text = CardWithDrawMoneyFRM->cxTextEdit1->Text;
	cxTextEdit2->Text = CardWithDrawMoneyFRM->cxTextEdit2->Text;
	cxTextEdit3->Text = CardWithDrawMoneyFRM->cxTextEdit3->Text;
	cxTextEdit4->Text = CardWithDrawMoneyFRM->cxTextEdit4->Text;
	cxTextEdit5->Text = CardWithDrawMoneyFRM->cxTextEdit5->Text;
	cxTextEdit6->Text = CardWithDrawMoneyFRM->cxTextEdit6->Text;
	cxTextEdit7->Text = CardWithDrawMoneyFRM->cxTextEdit7->Text;
	cxTextEdit8->Text = CardWithDrawMoneyFRM->cxTextEdit8->Text;
	cxTextEdit9->Text = CardWithDrawMoneyFRM->cxTextEdit9->Text;
	cxTextEdit10->Text = CardWithDrawMoneyFRM->cxTextEdit10->Text;
	cxTextEdit11->Text = CardWithDrawMoneyFRM->cxTextEdit11->Text;
	cxTextEdit12->Text = CardWithDrawMoneyFRM->cxTextEdit12->Text;
	cxTextEdit15->Text = CardWithDrawMoneyFRM->cxTextEdit15->Text;
	cxTextEdit16->Text = "";
	cxTextEdit17->Text = CardWithDrawMoneyFRM->cxTextEdit17->Text;
	cxTextEdit18->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TWithDrawERRForm::cxButton2Click(TObject *Sender)
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

	mode = 0x02;
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
				ADOReChargeQuery->Close();
				ADOReChargeQuery->SQL->Clear();
				ADOReChargeQuery->SQL->Add("select * from XTSET");
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

				ADOReChargeQuery->Close();

				String tmpstr;
				tmpkh = (int)kh[1]*256*256+(int)kh[2]*256+(int)kh[3];
				tmpsycs = (int)synum[0]*256+(int)synum[1];
				tmpintye = (double)balance[1]*256*256+(double)balance[2]*256+(double)balance[3];
				tmpye = tmpintye/100;

				ADOReChargeQuery->Close();
				ADOReChargeQuery->SQL->Clear();
				tmpstr = "select * from KZT where kh=";
				tmpstr += tmpkh;
				ADOReChargeQuery->SQL->Add(tmpstr);
				ADOReChargeQuery->Open();
				if(!ADOReChargeQuery->IsEmpty())
				{
					if(0 != ADOReChargeQuery->FieldByName("GS")->AsInteger)
					{
						ShowMessage("�˿��ѹ�ʧ����û�մ˿���");
						ADOReChargeQuery->Close();
						return;
					}
				}
				else
				{
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
				if(!ADOReChargeQuery->IsEmpty())
				{
					ADOReChargeQuery->Close();
					beepofreaddll(readcomno, '10');
					int oldkh = StrToInt(cxTextEdit1->Text.Trim());
					if(oldkh == tmpkh)
					{
						cxTextEdit18->Text = tmpye;
						ADOReChargeQuery->SQL->Clear();
						String Chksqlstr = "select * from HJL where KH=";
						Chksqlstr += tmpkh;
						Chksqlstr += " order by OPTIME asc";
						ADOReChargeQuery->SQL->Add(Chksqlstr);
						ADOReChargeQuery->Open();
						if(ADOReChargeQuery->IsEmpty())
						{
							beepofreaddll(readcomno, '10');
							String ReChargeOutstr = "ȡ��ɹ�!�����Ϊ��";
							ReChargeOutstr += tmpye;
							ShowMessage(ReChargeOutstr);
							this->Close();
						}
						else
						{
							if(tmpye == ADOReChargeQuery->FieldByName("YE")->AsFloat)
							{
								beepofreaddll(readcomno, '10');
								String ReChargeOutstr = "ȡ��ɹ�!�����Ϊ��";
								ReChargeOutstr += tmpye;
								ShowMessage(ReChargeOutstr);
								ADOReChargeQuery->Close();
								this->Close();
							}
							else
							{
								//д��ֵ���
								if(!LaunchNewCard)
								{
									ShowMessage("д����������ʧ��");
									return;
								}

								tmpsycs = (int)synum[0]*256+(int)synum[1];
								tmpsycs++;
								unsigned char writesynum[2];
								writesynum[0] = (char)(tmpsycs/256);
								writesynum[1] = (char)(tmpsycs%256);
								unsigned char writebalance[4];
								ADOReChargeQuery->Last();
								int ReChargeMoney = ADOReChargeQuery->FieldByName("JE")->AsInteger;
								double writetmpbalance = ADOReChargeQuery->FieldByName("JE")->AsFloat;
								tmpye -= writetmpbalance;
								writetmpbalance *= 100;
								writebalance[0] = 0x00;
								writebalance[1] = (unsigned char)((int)writetmpbalance/65536);
								writetmpbalance = (int)writetmpbalance%65536;
								writebalance[2] = (unsigned char)((int)writetmpbalance/256);
								writetmpbalance = (int)writetmpbalance%256;
								writebalance[3] = (unsigned char)writetmpbalance;
								WORD WriteStatus;

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
									ShowMessage("����ʧ�ܣ�������!");
									ADOReChargeQuery->Close();
									return;
								}
								else
								{
									//ȡ����⡢�빷��ʼ
									ADOReChargeQuery->Close();
									ADOReChargeQuery->SQL->Clear();
									String sqlstr = "insert into MX values(:BH,:KH,:SF_YE,";
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
									ADOReChargeQuery->Parameters->ParamByName("SFLX")->Value = "d";
									ADOReChargeQuery->Parameters->ParamByName("CZY")->Value = OperatorName;
									ADOReChargeQuery->Parameters->ParamByName("SCRQ")->Value = DateofLaunchCard;
									ADOReChargeQuery->ExecSQL();
									ADOReChargeQuery->Close();

									//����CK��
									ADOReChargeQuery->SQL->Clear();
									sqlstr = "insert into CK values(:kh,:bh,:sf_ye,:sf_fl,:ckxj,";
									sqlstr += ":glf,:ckje,:lqbt,:xkje,:sycs,:sfrq,:jyno,:gzzid,:sflx,:CZY)";
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
									ADOReChargeQuery->Parameters->ParamByName("sflx")->Value = "d";
									ADOReChargeQuery->Parameters->ParamByName("CZY")->Value = OperatorName;
									ADOReChargeQuery->ExecSQL();
									ADOReChargeQuery->Close();

									//��д������¼��
									sqlstr = "insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
									ADOReChargeQuery->SQL->Clear();
									ADOReChargeQuery->SQL->Add(sqlstr);
									ADOReChargeQuery->Parameters->ParamByName("BH")->Value = cxTextEdit7->Text;
									ADOReChargeQuery->Parameters->ParamByName("KH")->Value = tmpkh;
									ADOReChargeQuery->Parameters->ParamByName("JE")->Value = ReChargeMoney;
									ADOReChargeQuery->Parameters->ParamByName("YE")->Value = tmpye;
									ADOReChargeQuery->Parameters->ParamByName("LX")->Value = "ȡ��";
									ADOReChargeQuery->Parameters->ParamByName("Operator")->Value = OperatorName;
									ADOReChargeQuery->Parameters->ParamByName("DateTime")->Value = DateofLaunchCard;
									ADOReChargeQuery->ExecSQL();
									ADOReChargeQuery->Close();

									//����CARD��CARD_F��

									sqlstr = "select * from CARD where BH='";
									sqlstr = sqlstr + cxTextEdit7->Text + "'";
									ADOReChargeQuery->SQL->Clear();
									ADOReChargeQuery->SQL->Add(sqlstr);
									ADOReChargeQuery->Open();
									if(!ADOReChargeQuery->IsEmpty())
									{
										ADOReChargeQuery->Edit();
										ADOReChargeQuery->FieldByName("SF_YE")->AsFloat = tmpye;
										ADOReChargeQuery->FieldByName("SFYEDT")->AsDateTime = StrToDateTime(DateofLaunchCard);
										ADOReChargeQuery->FieldByName("SYCS")->AsInteger = tmpsycs;
										ADOReChargeQuery->Post();
									}

									sqlstr = "select * from CARD_F where BH='";
									sqlstr = sqlstr + cxTextEdit7->Text + "'";
									ADOReChargeQuery->SQL->Clear();
									ADOReChargeQuery->SQL->Add(sqlstr);
									ADOReChargeQuery->Open();
									if(!ADOReChargeQuery->IsEmpty())
									{
										ADOReChargeQuery->Edit();
										ADOReChargeQuery->FieldByName("SF_YE")->AsFloat = tmpye;
										ADOReChargeQuery->FieldByName("SFYEDT")->AsDateTime = StrToDateTime(DateofLaunchCard);
										ADOReChargeQuery->FieldByName("SYCS")->AsInteger = tmpsycs;
										ADOReChargeQuery->Post();
									}

									ADOReChargeQuery->Close();

									//д���ܹ���ֵ�ܶ�
                                    if(DOGChk)
                                    {
                                        unsigned char tempbuf[8];
                                        SFK_ZE -= ReChargeMoney;
                                        UpZETable->FieldByName("SFKZE")->AsFloat -= ReChargeMoney;
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
									//д���ܹ����
									//ȡ����⡢�빷����
									beepofreaddll(readcomno, '10');
									String ReChargeOutstr = "ȡ��ɹ�!�����Ϊ��";
								//	ReChargeOutstr += tmpye;
									ReChargeOutstr += tmpye;
									ShowMessage(ReChargeOutstr);
									ADOReChargeQuery->Last();
									ADOReChargeQuery->Delete();
									ADOReChargeQuery->Close();
									this->Close();
                                }
                            }
						}
					}
					else
					{
						beepofreaddll(readcomno, '10');
						ShowMessage("�˿����ǳ�ֵ����Ŀ�Ƭ�������!");
                    }

				//	ReadCardBTN->Enabled = false;
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOReChargeQuery->Close();
				}
			}
		}
	}
	else
		ShowMessage("���ض�д����̬���ӿ�ʧ�ܣ�");
}
//---------------------------------------------------------------------------
