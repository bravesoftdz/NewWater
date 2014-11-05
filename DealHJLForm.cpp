//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GlobalParameter.h"
#include "DealHJLForm.h"
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
#pragma link "cxMemo"
#pragma link "cxProgressBar"
#pragma link "cxTextEdit"
#pragma resource "*.dfm"
TDealHJLFRM *DealHJLFRM;
//---------------------------------------------------------------------------
__fastcall TDealHJLFRM::TDealHJLFRM(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDealHJLFRM::cxButton1Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TDealHJLFRM::FormShow(TObject *Sender)
{
	cxMemo1->Text = "";
	cxMemo1->Lines->Clear();
	cxProgressBar1->Position = 0;
}
//---------------------------------------------------------------------------

void __fastcall TDealHJLFRM::cxButton2Click(TObject *Sender)
{
	cxButton2->Enabled = false;
	cxMemo1->Lines->Clear();
	cxMemo1->Text = "";

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
//		beepofreaddll(readcomno, '10');
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
					}
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOCardInfoQuery->Close();
				}
				ADOCardInfoQuery->Close();

				ADOCardInfoQuery->SQL->Clear();
				tmpstr = "select * from CARD where kh=";
				tmpstr += tmpkh;
				ADOCardInfoQuery->SQL->Add(tmpstr);
				ADOCardInfoQuery->Open();
				if(!ADOCardInfoQuery->IsEmpty())
				{
					String BHstr = ADOCardInfoQuery->FieldByName("BH")->AsString.Trim();
					String hjlsqlstr = "select * from HJL where KH=";//SUM(JE) as AHJLJE
					hjlsqlstr += tmpkh;
					hjlsqlstr += " and BH='";
					hjlsqlstr += BHstr;
					hjlsqlstr += "'";
					DHJLADOQuery->Close();
					DHJLADOQuery->SQL->Clear();
					DHJLADOQuery->SQL->Add(hjlsqlstr);
					DHJLADOQuery->Open();
					if(!DHJLADOQuery->IsEmpty())
					{

						DHJLADOQuery->Last();
						int hjlsycs = tmpsycs;//DHJLADOQuery->FieldByName("SYCS")->AsInteger;
						double hjlye = tmpye;//DHJLADOQuery->FieldByName("YE")->AsFloat;
						int hjlje = DHJLADOQuery->FieldByName("JE")->AsInteger;//("AHJLJE")->AsInteger;
						if(hjlje == 0)
						{
							MessageBox(this->Handle,"�ÿ��޻Ҽ�¼!","ע��!",MB_ICONINFORMATION|MB_OK);
							cxButton2->Enabled = true;
							return;
						}

						cxMemo1->Lines->Add("�ÿ��ĳ�ֵ/ȡ����δ�뿨��ϵͳ���Զ����½��г�ֵ/ȡ��!");


						DWORD WriteStatus;
						unsigned char writebalance[4];
						double writetmpbalance;
						int ReChargeMoney = hjlje;
						if(DHJLADOQuery->FieldByName("SFLX")->AsString == "a")
						{
							mode = 0x01;
							writetmpbalance = hjlje;
							tmpye += hjlje;
						}
						else if(DHJLADOQuery->FieldByName("SFLX")->AsString == "d")
						{
							mode = 0x02;
							writetmpbalance = hjlje;
							tmpye -= hjlje;
						}

						writetmpbalance *= 100;
						writebalance[0] = 0x00;
						writebalance[1] = (unsigned char)((int)writetmpbalance/65536);
						writetmpbalance = (int)writetmpbalance%65536;
						writebalance[2] = (unsigned char)((int)writetmpbalance/256);
						writetmpbalance = (int)writetmpbalance%256;
						writebalance[3] = (unsigned char)writetmpbalance;

						unsigned char writesynum[2];
						writesynum[0] = (char)(hjlsycs/256);
						writesynum[1] = (
						char)(hjlsycs%256);

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
						if(!WriteStatus)
						{
							status = readcardinfo(readcomno,keymode,secnum,key,kh,balance,
													dwmm,synum,daytime,cardtype,czmm,Delayms);

							double aftertmpintye;
							double aftertmpye;
							if(status == 0)
							{
								aftertmpintye = (double)balance[1]*256*256+(double)balance[2]*256+(double)balance[3];
								aftertmpye = tmpintye/100;
							}
							if(hjlye == aftertmpye)
							{
								beepofreaddll(readcomno, '10');
							//	ShowMessage(outstr);
								DHJLADOQuery->Last();
								DHJLADOQuery->Delete();
								DHJLADOQuery->Close();

								String DateofLaunchCard;
								SYSTEMTIME tmpsystime;
								GetLocalTime(&tmpsystime);
								DateofLaunchCard = DateTimeToStr(SystemTimeToDateTime(tmpsystime));

								//�Ҽ�¼��ֵȡ������빷

								if(0x01 == mode)
								{
									//��ֵ��⡢�빷��ʼ
									ADOReChargeQuery->Close();
									ADOReChargeQuery->SQL->Clear();
									String sqlstr = "insert into MX values(:BH,:KH,:SF_YE,";
									sqlstr = sqlstr + ":SFJE,:SYCS,:SFRQ,:JYNO,";
									sqlstr = sqlstr + ":GZZID,:SFLX,:CZY,:SCRQ)";
									ADOReChargeQuery->SQL->Add(sqlstr);
									ADOReChargeQuery->Parameters->ParamByName("BH")->Value = BHstr;
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

									//����CK��
									ADOReChargeQuery->SQL->Clear();
									sqlstr = "insert into CK values(:kh,:bh,:sf_ye,:sf_fl,:ckxj,";
									sqlstr += ":glf,:ckje,:lqbt,:xkje,:sycs,:sfrq,:jyno,:gzzid,:sflx,:CZY)";
									ADOReChargeQuery->SQL->Add(sqlstr);
									ADOReChargeQuery->Parameters->ParamByName("kh")->Value = tmpkh;
									ADOReChargeQuery->Parameters->ParamByName("bh")->Value = BHstr;
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

									//��д������¼��
									sqlstr = "insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
									ADOReChargeQuery->SQL->Clear();
									ADOReChargeQuery->SQL->Add(sqlstr);
									ADOReChargeQuery->Parameters->ParamByName("BH")->Value = BHstr;
									ADOReChargeQuery->Parameters->ParamByName("KH")->Value = tmpkh;
									ADOReChargeQuery->Parameters->ParamByName("JE")->Value = ReChargeMoney;
									ADOReChargeQuery->Parameters->ParamByName("YE")->Value = tmpye;
									ADOReChargeQuery->Parameters->ParamByName("LX")->Value = "��ֵ";
									ADOReChargeQuery->Parameters->ParamByName("Operator")->Value = OperatorName;
									ADOReChargeQuery->Parameters->ParamByName("DateTime")->Value = DateofLaunchCard;
									ADOReChargeQuery->ExecSQL();
									ADOReChargeQuery->Close();

									//����CARD��CARD_F��

									sqlstr = "select * from CARD where BH='";
									sqlstr = sqlstr + BHstr + "'";
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
									sqlstr = sqlstr + BHstr + "'";
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
									//д���ܹ����
									//��ֵ��⡢�빷����
								}
								else if(0x02 == mode)
								{
									//ȡ����⡢�빷��ʼ
									ADOReChargeQuery->Close();
									ADOReChargeQuery->SQL->Clear();
									String sqlstr = "insert into MX values(:BH,:KH,:SF_YE,";
									sqlstr = sqlstr + ":SFJE,:SYCS,:SFRQ,:JYNO,";
									sqlstr = sqlstr + ":GZZID,:SFLX,:CZY,:SCRQ)";
									ADOReChargeQuery->SQL->Add(sqlstr);
									ADOReChargeQuery->Parameters->ParamByName("BH")->Value = BHstr;
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
									ADOReChargeQuery->Parameters->ParamByName("bh")->Value = BHstr;
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
									ADOReChargeQuery->Parameters->ParamByName("BH")->Value = BHstr;
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
									sqlstr = sqlstr + BHstr + "'";
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
									sqlstr = sqlstr + BHstr + "'";
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
								}
								//д���ܹ����
								//ȡ����⡢�빷����
								//����빷����

								String outstr = "ϵͳ�Զ���ֵ/ȡ��ɹ�!�����󿨽��Ϊ��";
								outstr += hjlye;
								outstr += "!";
								MessageBox(this->Handle,outstr.t_str(),"�ɹ�!",MB_ICONINFORMATION|MB_OK);
							/*
								String hjldelstr1 = "delete from HJL where KH=";
								hjldelstr1 += tmpkh;
								hjldelstr1 += " and BH='";
								hjldelstr1 += BHstr;
								hjldelstr1 += "' and SYCS=";
								hjldelstr1 += tmpsycs;

								DHJLADOQuery->Close();
								DHJLADOQuery->SQL->Clear();
								DHJLADOQuery->SQL->Add(hjldelstr1);
								DHJLADOQuery->ExecSQL();
								DHJLADOQuery->Close();   */
							}
							else
							{
								MessageBox(this->Handle,"�Ҽ�¼����ʧ�ܣ������¼����������ٽ��лҼ�¼����!","����!",MB_ICONERROR|MB_OK);
							//	ShowMessage("�Ҽ�¼����ʧ�ܣ������¼����������ٽ��лҼ�¼����!");
							}

						}
						else
						{
							MessageBox(this->Handle,"�Ҽ�¼����ʧ�ܣ������¼����������ٽ��лҼ�¼����!","����!",MB_ICONERROR|MB_OK);
							//ShowMessage("ϵͳ�Զ���ֵʧ�ܣ������´���!");
						}
				  //		}
				  //		}
				  //		else
				  // 		{
				  //          ShowMessage("�ÿ���ֵ���Ѿ����������ѣ�����ɼ������ݲ��ܽ��лҼ�¼����!");
				  //      }
					}
					DHJLADOQuery->Close();
				}
				else
				{
					ShowMessage("�˿����Ǳ�ϵͳ�����Ŀ���");
					ADOCardInfoQuery->Close();
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

	cxButton2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TDealHJLFRM::cxButton3Click(TObject *Sender)
{
	if(!DHJLThread)
	{
		DHJLThread = new TDealHJLThread(true,cxButton1,cxProgressBar1,Query1,Query2);
		if(DHJLThread)
			DHJLThread->Resume();
	}
	else
	{
		if(DHJLThread->Finished)
		{
			DHJLThread = new TDealHJLThread(true,cxButton1,cxProgressBar1,Query1,Query2);
			if(DHJLThread)
				DHJLThread->Resume();
        }
    }
}
//---------------------------------------------------------------------------

