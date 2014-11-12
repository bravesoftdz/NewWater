//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GlobalParameter.h"
#include "launchNewCardFRM.h"
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
#pragma link "cxLabel"
#pragma link "cxTextEdit"
#pragma link "cxDropDownEdit"
#pragma link "cxMaskEdit"
#pragma link "cxCheckBox"
#pragma link "cxButtons"
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
#pragma link "cxPropertiesStore"
#pragma link "cxHeader"
#pragma link "cxSpinEdit"
#pragma link "cxTimeEdit"
#pragma link "cxCalendar"
#pragma resource "*.dfm"
TLaunchNewUserCardFRM *LaunchNewUserCardFRM;
//---------------------------------------------------------------------------
__fastcall TLaunchNewUserCardFRM::TLaunchNewUserCardFRM(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLaunchNewUserCardFRM::LaunchNewCardExitBTNClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::LaunchNewCardBTNClick(TObject *Sender)
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

	Delayms = DelaySecond;
	keymode = CARDPasswordEdition;
	secnum = UsingSecNUM;

	key[0] = CARDPassword[0];
	key[1] = CARDPassword[1];
	key[2] = CARDPassword[2];
	key[3] = CARDPassword[3];
	key[4] = CARDPassword[4];
	key[5] = CARDPassword[5];
/*    //show card mm
    String chkmmrstr = "";
    for(int i = 0; i < 6; i++)
    {
        chkmmrstr += IntToHex(Byte(key[i]),2);
    }
    ShowMessage(chkmmrstr);
    //show end

    //show pwedition secnum
    chkmmrstr = "pwedition:";
    chkmmrstr += IntToHex(Byte(keymode),2);
    chkmmrstr += "  secnum:";
    chkmmrstr += IntToHex(Byte(UsingSecNUM),2);
    ShowMessage(chkmmrstr);
    //end show   */

	if(LoadHModule)
	{
		if(readcardinfo)
		{
			status = readcardinfo(readcomno,keymode,secnum,key,kh,balance,dwmm,synum,daytime,cardtype,czmm,Delayms);
			if(status > 99)
			{
				ShowMessage("通讯错误！请进行“检测读写器”操作！");
				return;
			}
			else if (1 == status)
			{
				ShowMessage("请把卡片放好！");
				return;
			}
			else if (2 == status)
			{
				ShowMessage("卡号大于200000或等于0！");
				return;
			}
			else if (4 == status)
			{
				ShowMessage("卡片密码不对！");
				return;
			}
			else if (5 == status)
			{
				ShowMessage("读写卡不稳定！");
				return;
			}
			else if (0 == status)
			{
				ShowMessage("此卡不能做为新卡发行，请更换新卡！");
				return;
			}
			else
			{
				int NumberOFCard;
				AnsiString SerialNumOFCard = SerialOFCardTextEdit->Text;

				NumberOFCard = StrToInt(NumberOFCardTextEdit->Text);

				LaunchNewCardADOQ->Close();
				LaunchNewCardADOQ->SQL->Clear();
				String checksqlstr = "select * from KZT where KH=";
				checksqlstr += NumberOFCard;
				checksqlstr += " and GS='0' and SY='N'";
	  //			ShowMessage(checksqlstr);
				LaunchNewCardADOQ->SQL->Add(checksqlstr);
				LaunchNewCardADOQ->Open();
				if(LaunchNewCardADOQ->IsEmpty())
				{
					ShowMessage("该卡号已经被使用，请更换卡号!");
					return;
				}

/*				//读取卡片序列号作为编号
				WORD readserialstatus;
				unsigned char readserialdelayms;
				unsigned char readserial[4];
				ZeroMemory(readserial, 4);
				readserialdelayms = 0x01;
				readserialstatus = readserialfun(readcomno, readserial);
				if(readserialstatus)
				{
					ShowMessage("无法获取该卡片的序列号，请更换卡片!");
					return;
				}
				else
				{
					unsigned int serialnum = readserial[3]*256*256*256
											 + readserial[2]*256*256
											 + readserial[1]*256
											 + readserial[0];

					SerialNumOFCard.sprintf("%010u", serialnum);
					SerialOFCardTextEdit->Text = SerialNumOFCard;

				//	SerialNumOFCard = SerialOFCardTextEdit->Text;
				}          */




				LaunchNewCardADOQ->Close();
				LaunchNewCardADOQ->SQL->Clear();
				checksqlstr = "select * from BHUSED where BH='";
				checksqlstr += SerialNumOFCard;
				checksqlstr += "'";
		//		ShowMessage(checksqlstr);
				LaunchNewCardADOQ->SQL->Add(checksqlstr);
				LaunchNewCardADOQ->Open();
				if(!LaunchNewCardADOQ->IsEmpty())
				{
					ShowMessage("该编号已经被使用，请更换编号!");
					return;
                }
				//(-1 != ClassNameComboBox->ItemIndex)&&(!IdentityIDTextEdit->Text.IsEmpty())
				//&&(!PerPassWordTextEdit->Text.IsEmpty())&&(-1 != SectionNameComboBox->ItemIndex)&&
				//(-1 != DegreeComboBox->ItemIndex)&&(-1 != DegreeComboBox->ItemIndex)
				if((!UserNameTextEdit->Text.IsEmpty())&&(-1 != UserSexComboBox->ItemIndex)&&
					(!DepositTextEdit->Text.IsEmpty())&&(!PrepayTextEdit->Text.IsEmpty())&&
					(-1 != ConsumeRateComboBox->ItemIndex)&&(!DegreeTextEdit->Text.IsEmpty()))
				{
					WORD writestatus;
					unsigned char writedaytime[4];
					unsigned char writebalance[4];
					unsigned char writeczmm[3];
					unsigned char writecardtype[1];
					unsigned char writekh[4];
					int writetmpkh = atoi(NumberOFCardTextEdit->Text.t_str());
					writekh[0] = (char)(writetmpkh/256/256/256);
					writekh[1] = (char)((writetmpkh%(256*256*256))/256/256);
					writekh[2] = (char)((writetmpkh%(256*256))/256);
					writekh[3] = (char)writetmpkh;

					unsigned char writereadcomno[5] = readcomno;
					unsigned char writekeymode = keymode;
					unsigned char writesecnum = secnum;

					unsigned char writekey[6];// = key;
					writekey[0] = CARDPassword[0];
					writekey[1] = CARDPassword[1];
					writekey[2] = CARDPassword[2];
					writekey[3] = CARDPassword[3];
					writekey[4] = CARDPassword[4];
					writekey[5] = CARDPassword[5];

            /*        //show card mm
                    String chkmmstr = "";
                    for(int i = 0; i < 6; i++)
                    {
                        chkmmstr += IntToHex(Byte(writekey[i]),2);
                    }
                    ShowMessage(chkmmstr);
                    //show end        */

					unsigned char writedwmm[2];
					writedwmm[0] = DWPassword[0];
					writedwmm[1] = DWPassword[1];
					unsigned char writesynum[2];
					writesynum[0] = 0x00;
					writesynum[1] = 0x00;
					unsigned char writemode = 0x00;
					unsigned char writeDelayms = DelaySecond;

					String writetmpstr = DateToStr(UseDateEdit->Date);
					char* writetmpdatestr = writetmpstr.t_str();
					writedaytime[0] = char(((int)writetmpdatestr[2]-48)*16+((int)writetmpdatestr[3]-48));
					writedaytime[1] = char(((int)writetmpdatestr[5]-48)*16+((int)writetmpdatestr[6]-48));
					writedaytime[2] = char(((int)writetmpdatestr[8]-48)*16+((int)writetmpdatestr[9]-48));
					writedaytime[3] = 0x00;

		 //			writesynum[0] = 0x00;
		 //			writesynum[1] = 0x00;

		 //			ShowMessage(PrepayTextEdit->Text.t_str());
					int writetmpbalance = atoi(PrepayTextEdit->Text.t_str());//-atoi(DepositTextEdit->Text.t_str());
					writetmpbalance *= 100;
					writebalance[0] = 0x00;
					writebalance[1] = (char)((int)writetmpbalance/65536);
					writetmpbalance = writetmpbalance%65536;
					writebalance[2] = (char)((int)writetmpbalance/256);
					writetmpbalance = writetmpbalance%256;
					writebalance[3] = (char)writetmpbalance;

					unsigned char writetmpczmm[5];
					strcpy(writetmpczmm, PerPassWordTextEdit->Text.t_str());
					writetmpczmm[0] = writetmpczmm[0]<<4;
					writetmpczmm[1] = writetmpczmm[1]<<4;
					writetmpczmm[1] = writetmpczmm[1]>>4;
					writeczmm[0] = writetmpczmm[0] + writetmpczmm[1];
					writetmpczmm[2] = writetmpczmm[2]<<4;
					writetmpczmm[3] = writetmpczmm[3]<<4;
					writetmpczmm[3] = writetmpczmm[3]>>4;
					writeczmm[1] = writetmpczmm[2]+writetmpczmm[3];
					writeczmm[2] = 0x00;

					writecardtype[0] = atoi(DegreeTextEdit->Text.t_str());

					if(LaunchNewCard)
					{
						writestatus = LaunchNewCard(writereadcomno,
													writekeymode,
													writesecnum,
													writekey,
													writekh,
													writebalance,
													writedwmm,
													writesynum,
													writedaytime,
													writecardtype,
													writeczmm,
													writemode,
													writeDelayms);
						if(writestatus)
						{
							ShowMessage("写卡失败！");
							return;
						}
						else
						{
							//判短时间限制并写卡
							if(DateCheckBox->Checked)
							{
							/*	if(!pacarddllproc)
								{
									ClearCardInfoProc(writereadcomno,
													  writekeymode,
													  writesecnum,
													  writekey,
													  writeDelayms);
									beepofreaddll(readcomno, '10');
									ShowMessage("写卡时间限制函数加载失败!");
									return;
								}

								unsigned char limitwritedaytime[4];
								String limitwritetmpstr = DateToStr(UseDateEdit->Date);
								char* limitwritetmpdatestr = limitwritetmpstr.t_str();
								limitwritedaytime[0] = char(((int)limitwritetmpdatestr[2]-48)*16+((int)limitwritetmpdatestr[3]-48));
								limitwritedaytime[1] = char(((int)limitwritetmpdatestr[5]-48)*16+((int)limitwritetmpdatestr[6]-48));
								limitwritedaytime[2] = char(((int)limitwritetmpdatestr[8]-48)*16+((int)limitwritetmpdatestr[9]-48));
								limitwritedaytime[3] = 0x00;

								unsigned char sendbuflen = 26;
								unsigned char sendbuf[26];
								ZeroMemory(sendbuf,26);
								unsigned char recbuf[140];
								unsigned char recbuflen;
								ZeroMemory(recbuf, 140);

								sendbuf[0] = (secnum+3)*4+0;//扇区×4+块号
								sendbuf[1] = 0x60;//固定为0x60
								sendbuf[2] = 2;//命令字：1为读，2为写
								sendbuf[3] = keymode;
								sendbuf[4] = writekey[0];
								sendbuf[5] = writekey[1];
								sendbuf[6] = writekey[2];
								sendbuf[7] = writekey[3];
								sendbuf[8] = writekey[4];
								sendbuf[9] = writekey[5];

								sendbuf[23] = limitwritedaytime[0];
								sendbuf[24] = limitwritedaytime[1];
								sendbuf[25] = limitwritedaytime[2];

								WORD limitStatus = pacarddllproc(writereadcomno,sendbuflen,sendbuf,&recbuflen,recbuf,writeDelayms);

								if((0 != limitStatus)||(0 != recbuf[2]))
								{
                                	ClearCardInfoProc(writereadcomno,
													  writekeymode,
													  writesecnum,
													  writekey,
													  writeDelayms);
									beepofreaddll(readcomno, '10');
									ShowMessage("写卡时间限制失败!");
									return;
                                }  */
							}

                            if(WriteNameChk)
                            {
                                //写姓名
                            /*    if(!UserNameTextEdit->Text.IsEmpty())
                                {
                                    if(!pacarddllproc)
                                    {
                                        ClearCardInfoProc(writereadcomno,
                                                          writekeymode,
                                                          writesecnum,
                                                          writekey,
                                                          writeDelayms);
                                        beepofreaddll(readcomno, '10');
                                        ShowMessage("写姓名函数加载失败!");
                                        return;
                                    }

                                    unsigned char writename[16];
                                    memset(writename, 0xA1, 16);
                                    String writenamestr = UserNameTextEdit->Text;
                                    char* writenametmpstr = writenamestr.t_str();

                                    for(int j = 0; j <writenamestr.Length(); j++)
                                    {
                                        writename[j] = writenametmpstr[j];
                                    }

                                    unsigned char sendbuflen = 26;
                                    unsigned char sendbuf[26];
                                    ZeroMemory(sendbuf,26);
                                    unsigned char recbuf[140];
                                    unsigned char recbuflen;
                                    ZeroMemory(recbuf, 140);

                                    sendbuf[0] = secnum*4+1;//扇区×4+块号
                                    sendbuf[1] = 0x60;//固定为0x60
                                    sendbuf[2] = 2;//命令字：1为读，2为写
                                    sendbuf[3] = keymode;
                                    sendbuf[4] = writekey[0];
                                    sendbuf[5] = writekey[1];
                                    sendbuf[6] = writekey[2];
                                    sendbuf[7] = writekey[3];
                                    sendbuf[8] = writekey[4];
                                    sendbuf[9] = writekey[5];

                                    for(int n = 10; n < 26; n++)
                                    {
                                        sendbuf[n] = writename[n - 10];
                                    }

                                    WORD limitStatus = pacarddllproc(writereadcomno,sendbuflen,sendbuf,&recbuflen,recbuf,writeDelayms);

                                    if((0 != limitStatus)||(0 != recbuf[2]))
                                    {
                                        ClearCardInfoProc(writereadcomno,
                                                          writekeymode,
                                                          writesecnum,
                                                          writekey,
                                                          writeDelayms);
                                        beepofreaddll(readcomno, '10');
                                        ShowMessage("写姓名失败!");
                                        return;
                                    }
                                }
                                //写电话号码
                                if(!cxTextEdit1->Text.IsEmpty())
                                {
                                    if(!pacarddllproc)
                                    {
                                        ClearCardInfoProc(writereadcomno,
                                                          writekeymode,
                                                          writesecnum,
                                                          writekey,
                                                          writeDelayms);
                                        beepofreaddll(readcomno, '10');
                                        ShowMessage("写电话函数加载失败!");
                                        return;
                                    }

                                    unsigned char writephone[16];
                                    memset(writephone, 0x20, 16);
                                    String writephonestr = cxTextEdit1->Text;
                                    char* writephonetmpstr = writephonestr.t_str();

                                    for(int j = 0; j <writephonestr.Length(); j++)
                                    {
                                        writephone[j] = writephonetmpstr[j];
                                    }

                                    unsigned char sendbuflen = 26;
                                    unsigned char sendbuf[26];
                                    ZeroMemory(sendbuf,26);
                                    unsigned char recbuf[140];
                                    unsigned char recbuflen;
                                    ZeroMemory(recbuf, 140);

                                    sendbuf[0] = secnum*4+2;//扇区×4+块号
                                    sendbuf[1] = 0x60;//固定为0x60
                                    sendbuf[2] = 2;//命令字：1为读，2为写
                                    sendbuf[3] = keymode;
                                    sendbuf[4] = writekey[0];
                                    sendbuf[5] = writekey[1];
                                    sendbuf[6] = writekey[2];
                                    sendbuf[7] = writekey[3];
                                    sendbuf[8] = writekey[4];
                                    sendbuf[9] = writekey[5];

                                    for(int n = 10; n < 26; n++)
                                    {
                                        sendbuf[n] = writephone[n - 10];
                                    }

                                    WORD limitStatus = pacarddllproc(writereadcomno,sendbuflen,sendbuf,&recbuflen,recbuf,writeDelayms);

                                    if((0 != limitStatus)||(0 != recbuf[2]))
                                    {
                                        ClearCardInfoProc(writereadcomno,
                                                          writekeymode,
                                                          writesecnum,
                                                          writekey,
                                                          writeDelayms);
                                        beepofreaddll(readcomno, '10');
                                        ShowMessage("写电话失败!");
                                        return;
                                    }
                                }      */
                            }

                            //写FK与HF到(n+1)*4+1
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

                            sendbuf[0] = (secnum+1)*4+1;//扇区×4+块号
                            sendbuf[1] = 0x60;//固定为0x60
                            sendbuf[2] = 2;//命令字：1为读，2为写
                            sendbuf[3] = keymode;
                            sendbuf[4] = writekey[0];
                            sendbuf[5] = writekey[1];
                            sendbuf[6] = writekey[2];
                            sendbuf[7] = writekey[3];
                            sendbuf[8] = writekey[4];
                            sendbuf[9] = writekey[5];

                            sendbuf[10] = 0x00;
                            sendbuf[11] = 0xff;
                            sendbuf[12] = 0x00;
                            sendbuf[13] = 0xff;
                            memcpy(createCRC, &sendbuf[10], 16);
                            CRCProc(createCRC, 14, CRC);
                            sendbuf[24] = CRC[0];
                            sendbuf[25] = CRC[1];

                            WORD limitStatus = pacarddllproc(writereadcomno,sendbuflen,sendbuf,&recbuflen,recbuf,writeDelayms);

                            if((0 != limitStatus)||(0 != recbuf[2]))
                            {
                                ClearCardInfoProc(writereadcomno,
                                                  writekeymode,
                                                  writesecnum,
                                                  writekey,
                                                  writeDelayms);
                                beepofreaddll(readcomno, '10');
                                ShowMessage("写卡第一块出错，发卡失败！");
                                return;
                            }
                            //end write fk hf

                            //写0值到(n+1)*4+2
                            ZeroMemory(sendbuf,26);
                            ZeroMemory(recbuf, 140);
                            ZeroMemory(createCRC, 16);
							ZeroMemory(CRC, 2);

                            sendbuf[0] = (secnum+1)*4+2;//扇区×4+块号
                            sendbuf[1] = 0x60;//固定为0x60
                            sendbuf[2] = 2;//命令字：1为读，2为写
                            sendbuf[3] = keymode;
                            sendbuf[4] = writekey[0];
                            sendbuf[5] = writekey[1];
                            sendbuf[6] = writekey[2];
                            sendbuf[7] = writekey[3];
                            sendbuf[8] = writekey[4];
                            sendbuf[9] = writekey[5];

                            memcpy(createCRC, &sendbuf[10], 16);
                            CRCProc(createCRC, 14, CRC);
                            sendbuf[24] = CRC[0];
                            sendbuf[25] = CRC[1];

                            limitStatus = pacarddllproc(writereadcomno,sendbuflen,sendbuf,&recbuflen,recbuf,writeDelayms);

                            if((0 != limitStatus)||(0 != recbuf[2]))
                            {
                                ClearCardInfoProc(writereadcomno,
                                                  writekeymode,
                                                  writesecnum,
                                                  writekey,
                                                  writeDelayms);
                                beepofreaddll(readcomno, '10');
                                ShowMessage("写卡第二块出错，发卡失败！");
                                return;
                            }
                            //end write 0

							String DateofLaunchCard;
							SYSTEMTIME tmpsystime;
							GetLocalTime(&tmpsystime);
							DateofLaunchCard = DateTimeToStr(SystemTimeToDateTime(tmpsystime));
				  //			ShowMessage(DateofLaunchCard);

							int tmpdeposit = atoi(DepositTextEdit->Text.t_str());
							int tmpPrePay = atoi(PrepayTextEdit->Text.t_str());
							int moneyincard = tmpPrePay;//-tmpdeposit;

							//填写CARD表
							String tmpstr = SerialNumOFCard;
							ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							String sqlstr = "insert into CARD values(:BH,:KH,:BKH,:XM,:XB,";
							sqlstr = sqlstr+":SFZH,:BM,:BZ,:ZB,:ZW,:JB,:RQ,:TKRQ,:YJ,:TYJ,"+
											":ZT,:GRMM,:BTBZ,:BT_YE,:BTYEDT,:BTSYCS,:SF_YE,"+
											":SFYEDT,:SYCS,:FKSK,:SF_FL,:GLF,:FKJE,:TKJE,:TKBT,"+
											":SF_KL,:USERNAME,:FK,:HF)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;
							ADOQuery1->Parameters->ParamByName("KH")->Value = NumberOFCard;
							//ADOQuery1->Parameters->ParamByName("BKH")->Value = NULL;
							ADOQuery1->Parameters->ParamByName("XM")->Value = UserNameTextEdit->Text;
							ADOQuery1->Parameters->ParamByName("XB")->Value = UserSexComboBox->Text;
							ADOQuery1->Parameters->ParamByName("SFZH")->Value = IdentityIDTextEdit->Text;
							ADOQuery1->Parameters->ParamByName("BM")->Value = SectionNameComboBox->Text;
							ADOQuery1->Parameters->ParamByName("BZ")->Value = ClassNameComboBox->Text;
							if(-1 != GroupNameComboBox->ItemIndex)
							{
								ADOQuery1->Parameters->ParamByName("ZB")->Value = GroupNameComboBox->Text;
							}
							ADOQuery1->Parameters->ParamByName("ZW")->Value = DegreeComboBox->Text;
							ADOQuery1->Parameters->ParamByName("JB")->Value = DegreeTextEdit->Text;
							ADOQuery1->Parameters->ParamByName("RQ")->Value = DateofLaunchCard;
							//ADOQuery1->Parameters->ParamByName("TKRQ")->Value = NULL;
							ADOQuery1->Parameters->ParamByName("YJ")->Value = tmpdeposit;
							ADOQuery1->Parameters->ParamByName("TYJ")->Value = tmpdeposit;
							ADOQuery1->Parameters->ParamByName("ZT")->Value = "发卡";
							ADOQuery1->Parameters->ParamByName("GRMM")->Value = PerPassWordTextEdit->Text;
							ADOQuery1->Parameters->ParamByName("BTBZ")->Value = 1;
							ADOQuery1->Parameters->ParamByName("BT_YE")->Value = 0;
							//ADOQuery1->Parameters->ParamByName("BTYEDT")->Value = NULL;
							ADOQuery1->Parameters->ParamByName("BTSYCS")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SF_YE")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("SFYEDT")->Value = DateofLaunchCard;
							ADOQuery1->Parameters->ParamByName("SYCS")->Value = 0;
							ADOQuery1->Parameters->ParamByName("FKSK")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("SF_FL")->Value = ConsumeRateComboBox->ItemIndex+1;
							ADOQuery1->Parameters->ParamByName("GLF")->Value = 0;
							ADOQuery1->Parameters->ParamByName("FKJE")->Value = moneyincard;
							//ADOQuery1->Parameters->ParamByName("TKJE")->Value = NULL;
							//ADOQuery1->Parameters->ParamByName("TKBT")->Value = NULL;
							ADOQuery1->Parameters->ParamByName("SF_KL")->Value = 1;
							ADOQuery1->Parameters->ParamByName("USERNAME")->Value = OperatorName;
                            ADOQuery1->Parameters->ParamByName("FK")->Value = 0;
                            ADOQuery1->Parameters->ParamByName("HF")->Value = 0;
							ADOQuery1->ExecSQL();

							//填写CARD_F表
							ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							sqlstr = "insert into CARD_F values(:BH,:KH,:BKH,:XM,:XB,";
							sqlstr = sqlstr+":SFZH,:BM,:BZ,:ZB,:ZW,:JB,:RQ,:TKRQ,:YJ,:TYJ,"+
							":ZT,:GRMM,:BTBZ,:BT_YE,:BTYEDT,:BTSYCS,:SF_YE,"+
							":SFYEDT,:SYCS,:FKSK,:SF_FL,:GLF,:FKJE,:TKJE,:TKBT,"+
							":SF_KL,:USERNAME,:FK,:HF)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;
							ADOQuery1->Parameters->ParamByName("KH")->Value = (NumberOFCard);
							//ADOQuery1->Parameters->ParamByName("BKH")->Value = NULL;
							ADOQuery1->Parameters->ParamByName("XM")->Value = UserNameTextEdit->Text;
							ADOQuery1->Parameters->ParamByName("XB")->Value = UserSexComboBox->Text;
							ADOQuery1->Parameters->ParamByName("SFZH")->Value = IdentityIDTextEdit->Text;
							ADOQuery1->Parameters->ParamByName("BM")->Value = SectionNameComboBox->Text;
							ADOQuery1->Parameters->ParamByName("BZ")->Value = ClassNameComboBox->Text;
							if(-1 != GroupNameComboBox->ItemIndex)
							{
								ADOQuery1->Parameters->ParamByName("ZB")->Value = GroupNameComboBox->Text;
							}
							ADOQuery1->Parameters->ParamByName("ZW")->Value = DegreeComboBox->Text;
							ADOQuery1->Parameters->ParamByName("JB")->Value = DegreeTextEdit->Text;
							ADOQuery1->Parameters->ParamByName("RQ")->Value = DateofLaunchCard;
							//ADOQuery1->Parameters->ParamByName("TKRQ")->Value = NULL;
							ADOQuery1->Parameters->ParamByName("YJ")->Value = tmpdeposit;
							ADOQuery1->Parameters->ParamByName("TYJ")->Value = tmpdeposit;
							ADOQuery1->Parameters->ParamByName("ZT")->Value = "发卡";
							ADOQuery1->Parameters->ParamByName("GRMM")->Value = PerPassWordTextEdit->Text;
							ADOQuery1->Parameters->ParamByName("BTBZ")->Value = 1;
							ADOQuery1->Parameters->ParamByName("BT_YE")->Value = 0;
							//ADOQuery1->Parameters->ParamByName("BTYEDT")->Value = NULL;
							ADOQuery1->Parameters->ParamByName("BTSYCS")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SF_YE")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("SFYEDT")->Value = DateofLaunchCard;
							ADOQuery1->Parameters->ParamByName("SYCS")->Value = 0;
							ADOQuery1->Parameters->ParamByName("FKSK")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("SF_FL")->Value = ConsumeRateComboBox->ItemIndex+1;
							ADOQuery1->Parameters->ParamByName("GLF")->Value = 0;
							ADOQuery1->Parameters->ParamByName("FKJE")->Value = moneyincard;
							//ADOQuery1->Parameters->ParamByName("TKJE")->Value = NULL;
							//ADOQuery1->Parameters->ParamByName("TKBT")->Value = NULL;
							ADOQuery1->Parameters->ParamByName("SF_KL")->Value = 1;
							ADOQuery1->Parameters->ParamByName("USERNAME")->Value = OperatorName;
                            ADOQuery1->Parameters->ParamByName("FK")->Value = 0;
                            ADOQuery1->Parameters->ParamByName("HF")->Value = 0;
							ADOQuery1->ExecSQL();

							//填写操作记录表
							ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							sqlstr = "insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;//LaunchNewCardADOQ->FieldByName("BH")->AsString;
							ADOQuery1->Parameters->ParamByName("KH")->Value = NumberOFCard;
							ADOQuery1->Parameters->ParamByName("JE")->Value = 0;
							ADOQuery1->Parameters->ParamByName("YE")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("LX")->Value = "发卡";
							ADOQuery1->Parameters->ParamByName("Operator")->Value = OperatorName;
							ADOQuery1->Parameters->ParamByName("DateTime")->Value = DateofLaunchCard;
							ADOQuery1->ExecSQL();
                			ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							sqlstr = "insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;//LaunchNewCardADOQ->FieldByName("BH")->AsString;
							ADOQuery1->Parameters->ParamByName("KH")->Value = NumberOFCard;
							ADOQuery1->Parameters->ParamByName("JE")->Value = tmpdeposit;
							ADOQuery1->Parameters->ParamByName("YE")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("LX")->Value = "收押金";
							ADOQuery1->Parameters->ParamByName("Operator")->Value = OperatorName;
							ADOQuery1->Parameters->ParamByName("DateTime")->Value = DateofLaunchCard;
							ADOQuery1->ExecSQL();

							//填写MX,MXBAK表
							ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							sqlstr = "insert into MX values(:BH,:KH,:SF_YE,:SFJE,:SYCS,:SFRQ,:JYNO,:GZZID,:SFLX,:CZY,:SCRQ)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;//LaunchNewCardADOQ->FieldByName("BH")->AsString;
							ADOQuery1->Parameters->ParamByName("KH")->Value = NumberOFCard;//LaunchNewCardADOQ->FieldByName("KH")->AsInteger;
							ADOQuery1->Parameters->ParamByName("SF_YE")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("SFJE")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SYCS")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SFRQ")->Value = DateofLaunchCard;
							ADOQuery1->Parameters->ParamByName("JYNO")->Value = 0;
							ADOQuery1->Parameters->ParamByName("GZZID")->Value = 1;
							ADOQuery1->Parameters->ParamByName("SFLX")->Value = "K";
							ADOQuery1->Parameters->ParamByName("CZY")->Value = OperatorName;
							ADOQuery1->Parameters->ParamByName("SCRQ")->Value = DateofLaunchCard;
							ADOQuery1->ExecSQL();
							ADOQuery1->Close();

							//添加扣押金记录
							ADOQuery1->SQL->Clear();
							sqlstr = "insert into MX values(:BH,:KH,:SF_YE,:SFJE,:SYCS,:SFRQ,:JYNO,:GZZID,:SFLX,:CZY,:SCRQ)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;//LaunchNewCardADOQ->FieldByName("BH")->AsString;
							ADOQuery1->Parameters->ParamByName("KH")->Value = NumberOFCard;//LaunchNewCardADOQ->FieldByName("KH")->AsInteger;
							ADOQuery1->Parameters->ParamByName("SF_YE")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SFJE")->Value = tmpdeposit;
							ADOQuery1->Parameters->ParamByName("SYCS")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SFRQ")->Value = DateofLaunchCard;
							ADOQuery1->Parameters->ParamByName("JYNO")->Value = 0;
							ADOQuery1->Parameters->ParamByName("GZZID")->Value = 1;
							ADOQuery1->Parameters->ParamByName("SFLX")->Value = "W";
							ADOQuery1->Parameters->ParamByName("CZY")->Value = OperatorName;
							ADOQuery1->Parameters->ParamByName("SCRQ")->Value = DateofLaunchCard;
							ADOQuery1->ExecSQL();

							//添加扣押金记录
/*							ADOQuery1->SQL->Clear();
							sqlstr = "insert into MXBAK values(:BH,:KH,:SF_YE,:SFJE,:SYCS,:SFRQ,:JYNO,:GZZID,:SFLX,:CZY,:SCRQ)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;//LaunchNewCardADOQ->FieldByName("BH")->AsString;
							ADOQuery1->Parameters->ParamByName("KH")->Value = NumberOFCard;//LaunchNewCardADOQ->FieldByName("KH")->AsInteger;
							ADOQuery1->Parameters->ParamByName("SF_YE")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SFJE")->Value = tmpdeposit;
							ADOQuery1->Parameters->ParamByName("SYCS")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SFRQ")->Value = DateofLaunchCard;
							ADOQuery1->Parameters->ParamByName("JYNO")->Value = 0;
							ADOQuery1->Parameters->ParamByName("GZZID")->Value = 1;
							ADOQuery1->Parameters->ParamByName("SFLX")->Value = "W";
							ADOQuery1->Parameters->ParamByName("CZY")->Value = OperatorName;
							ADOQuery1->Parameters->ParamByName("SCRQ")->Value = DateofLaunchCard;
							ADOQuery1->ExecSQL();

							ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							sqlstr = "insert into MXBAK values(:BH,:KH,:SF_YE,:SFJE,:SYCS,:SFRQ,:JYNO,:GZZID,:SFLX,:CZY,:SCRQ)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;//LaunchNewCardADOQ->FieldByName("BH")->AsString;
							ADOQuery1->Parameters->ParamByName("KH")->Value = NumberOFCard;//LaunchNewCardADOQ->FieldByName("KH")->AsInteger;
							ADOQuery1->Parameters->ParamByName("SF_YE")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("SFJE")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SYCS")->Value = 0;
							ADOQuery1->Parameters->ParamByName("SFRQ")->Value = DateofLaunchCard;
							ADOQuery1->Parameters->ParamByName("JYNO")->Value = 0;
							ADOQuery1->Parameters->ParamByName("GZZID")->Value = 1;
							ADOQuery1->Parameters->ParamByName("SFLX")->Value = "K";
							ADOQuery1->Parameters->ParamByName("CZY")->Value = OperatorName;
							ADOQuery1->Parameters->ParamByName("SCRQ")->Value = DateofLaunchCard;
							ADOQuery1->ExecSQL();    */

							ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							sqlstr = "insert into CK values(:kh,:bh,:sf_ye,:sf_fl,:ckxj,";
							sqlstr += ":glf,:ckje,:lqbt,:xkje,:sycs,:sfrq,:jyno,:gzzid,:sflx,:CZY)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("kh")->Value = NumberOFCard;
							ADOQuery1->Parameters->ParamByName("bh")->Value = SerialNumOFCard;
							ADOQuery1->Parameters->ParamByName("sf_ye")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("sf_fl")->Value = 1;
							ADOQuery1->Parameters->ParamByName("ckxj")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("glf")->Value = 0;
							ADOQuery1->Parameters->ParamByName("ckje")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("lqbt")->Value = 0;
							ADOQuery1->Parameters->ParamByName("xkje")->Value = moneyincard;
							ADOQuery1->Parameters->ParamByName("sycs")->Value = 0;
							ADOQuery1->Parameters->ParamByName("sfrq")->Value = DateofLaunchCard;
							ADOQuery1->Parameters->ParamByName("jyno")->Value = 0;
							ADOQuery1->Parameters->ParamByName("gzzid")->Value = 1;
							ADOQuery1->Parameters->ParamByName("sflx")->Value = "K";
							ADOQuery1->Parameters->ParamByName("CZY")->Value = OperatorName;
							ADOQuery1->ExecSQL();
							ADOQuery1->Close();


							//填写KZT表

					   /*	ADOQuery1->SQL->Clear();
							ADOQuery1->SQL->Add("insert into KZT values(:KH,:BH,:GS,:SY,:FKRQ,:TKRQ,:WITHCARDTK)");
							ADOQuery1->Parameters->ParamByName("KH")->Value = NumberOFCard;
							ADOQuery1->Parameters->ParamByName("BH")->Value = tmpstr;
							ADOQuery1->Parameters->ParamByName("GS")->Value = "0";
							ADOQuery1->Parameters->ParamByName("SY")->Value = "1";
							ADOQuery1->Parameters->ParamByName("FKRQ")->Value = DateofLaunchCard;
							//ADOQuery1->Parameters->ParamByName("TKRQ")->Value = NULL;
							//ADOQuery1->Parameters->ParamByName("WITHCARDTK")->Value = NULL;
							ADOQuery1->ExecSQL();     */

					/*		LaunchNewCardADOQ->Edit();
							LaunchNewCardADOQ->FieldByName("SY")->AsString = "Y";
							LaunchNewCardADOQ->FieldByName("FKRQ")->AsString = DateofLaunchCard;
							LaunchNewCardADOQ->Post();   */
							ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							String kztsqlstr = "select * from KZT where KH=";
							kztsqlstr += NumberOFCard;
							ADOQuery1->SQL->Add(kztsqlstr);
							ADOQuery1->Open();
							if(!ADOQuery1->IsEmpty())
							{
								ADOQuery1->Edit();
								ADOQuery1->FieldByName("BH")->AsAnsiString = SerialNumOFCard;
								ADOQuery1->FieldByName("SY")->AsAnsiString = 'Y';
								ADOQuery1->FieldByName("FKRQ")->AsAnsiString = DateofLaunchCard;
                                ADOQuery1->FieldByName("GS")->AsAnsiString = '0';
                                ADOQuery1->FieldByName("TKRQ")->AsAnsiString = "";
                                ADOQuery1->FieldByName("WITHCARDTK")->AsAnsiString = "";
								ADOQuery1->Post();
                            }

							cxLabel20->Caption = IntToStr(moneyincard);

                            ADOQuery1->Close();
							ADOQuery1->SQL->Clear();
							sqlstr = "insert into BHUSED values(:BH)";
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;
							ADOQuery1->ExecSQL();
							ADOQuery1->Close();


							//检查入库情况
							ADOQuery1->SQL->Clear();
							sqlstr = "select * from CARD where KH=";
							sqlstr += NumberOFCard;
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Open();
							if(!ADOQuery1->IsEmpty())
							{
								int chkkh = ADOQuery1->FieldByName("KH")->AsInteger;
								AnsiString chkbh = ADOQuery1->FieldByName("BH")->AsAnsiString.Trim();
								String chkname = ADOQuery1->FieldByName("XM")->AsString.Trim();
								double chkje = ADOQuery1->FieldByName("SF_YE")->AsFloat;

								if(chkkh != NumberOFCard)
								{
									ADOQuery1->Edit();
									ADOQuery1->FieldByName("KH")->AsInteger = NumberOFCard;
									ADOQuery1->Post();
								}

								if(chkbh != SerialNumOFCard)
								{
									ADOQuery1->Edit();
									ADOQuery1->FieldByName("BH")->AsAnsiString = SerialNumOFCard;
									ADOQuery1->Post();
                                }

								if(chkname != UserNameTextEdit->Text)
								{
                                    ADOQuery1->Edit();
									ADOQuery1->FieldByName("XM")->AsString = UserNameTextEdit->Text;
									ADOQuery1->Post();
								}

								if(chkje != moneyincard)
								{
									ADOQuery1->Edit();
									ADOQuery1->FieldByName("SF_YE")->AsFloat = moneyincard;
									ADOQuery1->FieldByName("FKJE")->AsFloat = moneyincard;
									ADOQuery1->Post();
								}
							}
							ADOQuery1->Close();

							ADOQuery1->SQL->Clear();
							sqlstr = "select * from CARD_F where KH=";
							sqlstr += NumberOFCard;
							ADOQuery1->SQL->Add(sqlstr);
							ADOQuery1->Open();
							if(!ADOQuery1->IsEmpty())
							{
								int chkkh = ADOQuery1->FieldByName("KH")->AsInteger;
								AnsiString chkbh = ADOQuery1->FieldByName("BH")->AsAnsiString.Trim();
								String chkname = ADOQuery1->FieldByName("XM")->AsString.Trim();
								double chkje = ADOQuery1->FieldByName("SF_YE")->AsFloat;


								if(chkkh != NumberOFCard)
								{
									ADOQuery1->Edit();
									ADOQuery1->FieldByName("KH")->AsInteger = NumberOFCard;
									ADOQuery1->Post();
								}

								if(chkbh != SerialNumOFCard)
								{
									ADOQuery1->Edit();
									ADOQuery1->FieldByName("BH")->AsAnsiString = SerialNumOFCard;
									ADOQuery1->Post();
                                }

								if(chkname != UserNameTextEdit->Text)
								{
                                    ADOQuery1->Edit();
									ADOQuery1->FieldByName("XM")->AsString = UserNameTextEdit->Text;
									ADOQuery1->Post();
								}

								if(chkje != moneyincard)
								{
									ADOQuery1->Edit();
									ADOQuery1->FieldByName("SF_YE")->AsFloat = moneyincard;
									ADOQuery1->FieldByName("FKJE")->AsFloat = moneyincard;
									ADOQuery1->Post();
								}
							}
							ADOQuery1->Close();

                            //写加密狗充值总额
                            if(DOGChk)
                            {
                            	SFK_ZE += moneyincard;
                                unsigned char tempbuf[8];
			 	               	UpZETable->FieldByName("SFKZE")->AsFloat += moneyincard;
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
							//写加密狗完毕

							beepofreaddll(readcomno, '10');
							ShowMessage("发卡成功！");
                      //      ADOTable1->Active = false;
                      //      ADOTable1->Active = true;

                            LaunchProcessPanel->Caption = "开始发卡......";
							LaunchNewCardADOQ->Close();
							LaunchNewCardADOQ->SQL->Clear();
						  //	LaunchNewCardADOQ->SQL->Add("select min(KH) as minkh from KZT where (SY='N' or SY='T') and GS='0' and KH>0");
						  	LaunchNewCardADOQ->SQL->Add("select min(KH) as minkh from KZT where SY='N' and GS='0' and KH>0");
							LaunchNewCardADOQ->Open();
							if(!LaunchNewCardADOQ->IsEmpty())
							{
								NumberOFCard = LaunchNewCardADOQ->FieldByName("minkh")->AsInteger;
								NumberOFCardTextEdit->Text = NumberOFCard;
								SerialOFCardTextEdit->Text = "";
								SerialNumOFCard.sprintf("%010d", NumberOFCard);

								LaunchNewCardADOQ->Close();
								LaunchNewCardADOQ->SQL->Clear();

								String tmpsqlstr = "select * from BHUSED where BH='";
								tmpsqlstr += SerialNumOFCard;
								tmpsqlstr += "'";
								LaunchNewCardADOQ->SQL->Add(tmpsqlstr);
								LaunchNewCardADOQ->Open();

								if(LaunchNewCardADOQ->IsEmpty())
								{
									SerialOFCardTextEdit->Text = SerialNumOFCard;
								}
								else
								{
                                    srand((unsigned)time(NULL));
                                    int tmpint = rand()%10000000000;
                                    while(1)
                                    {
                                        SerialNumOFCard = "";
                                        SerialNumOFCard.sprintf("%010d", tmpint);

                                        tmpsqlstr = "select * from BHUSED where BH='";
                                        tmpsqlstr += SerialNumOFCard;
                                        tmpsqlstr += "'";

                                        LaunchNewCardADOQ->Close();
                                        LaunchNewCardADOQ->SQL->Clear();
                                        LaunchNewCardADOQ->SQL->Add(tmpsqlstr);
                                        LaunchNewCardADOQ->Open();
                                        if(LaunchNewCardADOQ->IsEmpty())
                                        {
                                            SerialOFCardTextEdit->Text = SerialNumOFCard;
                                            break;
                                        }
                                        else
                                        {
                                            tmpint = rand()%10000000000;
                                        }
                                    }
								}
							}
                            else
                            {
								ShowMessage("系统中已无可用卡号，请联系技术人员！");
                                LaunchNewCardADOQ->Close();
                                UserNameTextEdit->Text = "";
                                UserSexComboBox->ItemIndex = 0;
                                SectionNameComboBox->ItemIndex = -1;
                                ClassNameComboBox->ItemIndex = -1;
                                DegreeComboBox->ItemIndex = -1;
                                GroupNameComboBox->ItemIndex = -1;
                                cxTextEdit4->Text = 1;
                                IdentityIDTextEdit->Text = "";
                                DegreeTextEdit->Text = 1;
								PerPassWordTextEdit->Text = "0000";
                                DepositTextEdit->Text = IntToStr(GlobalFKYJ);
                                if(!cxCheckBox3->Checked)
                                	PrepayTextEdit->Text = "";
                                ConsumeRateComboBox->ItemIndex = 0;
                                UseDateEdit->Text = "2016-07-31";
                                LaunchNewCardBTN->Enabled = false;
                                return;
                            }
							LaunchNewCardADOQ->Close();
							UserNameTextEdit->Text = "";
							UserSexComboBox->ItemIndex = 0;
							SectionNameComboBox->ItemIndex = -1;
							ClassNameComboBox->ItemIndex = -1;
							DegreeComboBox->ItemIndex = -1;
							GroupNameComboBox->ItemIndex = -1;
							cxTextEdit4->Text = 1;
							IdentityIDTextEdit->Text = "";
							DegreeTextEdit->Text = 1;
							PerPassWordTextEdit->Text = "0000";
							DepositTextEdit->Text = IntToStr(GlobalFKYJ);
                            if(!cxCheckBox3->Checked)
								PrepayTextEdit->Text = "";
							ConsumeRateComboBox->ItemIndex = 0;
							UseDateEdit->Text = "2016-07-31";
						}
					}
					else
					{
						ShowMessage("写卡函数加载失败！");
					}
				}
				else
					ShowMessage("卡信息填写不完整，请填写完整！");

				LaunchNewCardADOQ->Close();
			}
		}
		else
		{
			ShowMessage("读卡函数加载失败！");
		}
	}
	else
	{
		ShowMessage("加载读写卡动态链接库失败！");
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::FormCreate(TObject *Sender)
{
/*	LaunchNewCardADOQ->Close();
	LaunchNewCardADOQ->SQL->Clear();
	LaunchNewCardADOQ->SQL->Add("select * from BUMEN");
	LaunchNewCardADOQ->Open();
	SectionNameComboBox->Properties->Items->Clear();
	while(!LaunchNewCardADOQ->Eof)
	{
		SectionNameComboBox->Properties->Items->Add(LaunchNewCardADOQ->FieldByName("BUMEN")->AsAnsiString);
		LaunchNewCardADOQ->Next();
	}
	SectionNameComboBox->ItemIndex = -1;
	LaunchNewCardADOQ->Close();

	LaunchNewCardADOQ->SQL->Clear();
	LaunchNewCardADOQ->SQL->Add("select * from SFZW");
	LaunchNewCardADOQ->Open();
	DegreeComboBox->Properties->Items->Clear();
	while(!LaunchNewCardADOQ->Eof)
	{
		DegreeComboBox->Properties->Items->Add(LaunchNewCardADOQ->FieldByName("ZW")->AsAnsiString);
		LaunchNewCardADOQ->Next();
	}
	DegreeComboBox->ItemIndex = -1;
	LaunchNewCardADOQ->Close();  */

	LaunchNewCardADOQ->SQL->Clear();
	LaunchNewCardADOQ->SQL->Add("select * from SFFL");
	LaunchNewCardADOQ->Open();
	ConsumeRateComboBox->Properties->Items->Clear();
	while(!LaunchNewCardADOQ->Eof)
	{
		ConsumeRateComboBox->Properties->Items->Add(LaunchNewCardADOQ->FieldByName("FL")->AsAnsiString.Trim());
		LaunchNewCardADOQ->Next();
	}
	ConsumeRateComboBox->ItemIndex = 1;
	LaunchNewCardADOQ->Close();
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::SectionNameComboBoxPropertiesChange(TObject *Sender)
{
	LaunchNewCardADOQ->Close();
	LaunchNewCardADOQ->SQL->Clear();
	LaunchNewCardADOQ->SQL->Add("select * from BANBIE where BUMEN='"+
								(SectionNameComboBox->Text)+"'");
	LaunchNewCardADOQ->Open();
	ClassNameComboBox->Properties->Items->Clear();
	while(!LaunchNewCardADOQ->Eof)
	{
		ClassNameComboBox->Properties->Items->Add(LaunchNewCardADOQ->FieldByName("BANBIE")->AsAnsiString.Trim());
		LaunchNewCardADOQ->Next();
	}
	ClassNameComboBox->ItemIndex = -1;
	LaunchNewCardADOQ->Close();
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::ClassNameComboBoxPropertiesChange(TObject *Sender)
{
	LaunchNewCardADOQ->Close();
	LaunchNewCardADOQ->SQL->Clear();
	LaunchNewCardADOQ->SQL->Add("select * from ZUBIE where BUMEN = '"+
								(SectionNameComboBox->Text)+"'"+"and "+
								"BANBIE = '"+(ClassNameComboBox->Text)+"'");
	LaunchNewCardADOQ->Open();
	GroupNameComboBox->Properties->Items->Clear();
	while(!LaunchNewCardADOQ->Eof)
	{
		GroupNameComboBox->Properties->Items->Add(LaunchNewCardADOQ->FieldByName("ZUBIE")->AsAnsiString.Trim());
		LaunchNewCardADOQ->Next();
	}
	GroupNameComboBox->ItemIndex = -1;
	LaunchNewCardADOQ->Close();
}
//---------------------------------------------------------------------------


void __fastcall TLaunchNewUserCardFRM::UserNameTextEditExit(TObject *Sender)
{
/*	String tmpstr = UserNameTextEdit->Text;
	if((tmpstr.Length()==0)||(tmpstr.Length()>=10))
	{
		ShowMessage("您输入的姓名长度不能为0，同时不能大与5的字！");
		UserNameTextEdit->Text = "";
    }  */
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::UserSexComboBoxExit(TObject *Sender)
{
	if(-1 == UserSexComboBox->ItemIndex)
	{
		ShowMessage("请选择用户性别！");
		UserSexComboBox->Text = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::SectionNameComboBoxExit(TObject *Sender)
{
/*	if(-1 == SectionNameComboBox->ItemIndex)
	{
		ShowMessage("请选择用户所在部门！");
		SectionNameComboBox->Text = "";
	}  */
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::DegreeComboBoxExit(TObject *Sender)
{
/*	if(-1 == DegreeComboBox->ItemIndex)
	{
		ShowMessage("请选择用户身份！");
		DegreeComboBox->Text = "";
	}     */
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::IdentityIDTextEditExit(TObject *Sender)
{
	String tmpstr = IdentityIDTextEdit->Text;
	if(tmpstr.Length()>18)
	{
		ShowMessage("输入的身份证号位数应该大于0，小于19，请重新输入");
		IdentityIDTextEdit->Text = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::PerPassWordTextEditExit(TObject *Sender)
{
	String tmpstr = PerPassWordTextEdit->Text;
	if(tmpstr.Length() != 4)
	{
		ShowMessage("请输入四位的个人密码！");
		PerPassWordTextEdit->Text = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::DegreeTextEditExit(TObject *Sender)
{
	String tmpstr = DegreeTextEdit->Text;
	if((tmpstr.Length() > 1)||(tmpstr.Length() == 0))
	{
		ShowMessage("卡级别必须为一位数字!");
		DegreeTextEdit->Text = "1";
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::IdentityIDTextEditKeyPress(TObject *Sender,
          wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
    	if(13 == Key)
        {
        	DegreeTextEdit->SetFocus();
        	Key = 0;
        }
        else
        {
			Key=0;
			ShowMessage("请输入0到9之间的数字！");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::PerPassWordTextEditKeyPress(TObject *Sender,
          wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
    	if(13 == Key)
        {
        	Key = 0;
            DepositTextEdit->SetFocus();
        }
        else
        {
			Key=0;
			ShowMessage("请输入0到9之间的数字！");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::PrepayTextEditKeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
    	if(13 == Key)
        {
            Key = 0;
            ConsumeRateComboBox->SetFocus();
        }
        else
        {
            Key=0;
            ShowMessage("请输入0到9之间的数字！");
        }
	}
}
//---------------------------------------------------------------------------


void __fastcall TLaunchNewUserCardFRM::FormShow(TObject *Sender)
{
//	ShowMessage("Launch Show!");
	UseDateEdit->Date = IncYear(Date(), 3);
	DepositTextEdit->Text = IntToStr(GlobalFKYJ);
//	ADOTable1->Active = true;
	GetNumADOQ->Close();
	GetNumADOQ->SQL->Clear();
	int NumberOFCard;
//				char SerialNumOFCard[10]="";
	AnsiString SerialNumOFCard;

	LaunchProcessPanel->Caption = "开始发卡......";
	LaunchNewCardADOQ->Close();
	LaunchNewCardADOQ->SQL->Clear();
    LaunchNewCardADOQ->SQL->Add("select min(KH) as minkh from KZT where SY='N' and GS='0' and KH>0");
 //	LaunchNewCardADOQ->SQL->Add("select min(KH) as minkh from KZT where (SY='N' or SY='T') and GS='0' and KH>0");
	LaunchNewCardADOQ->Open();
	if(!LaunchNewCardADOQ->IsEmpty())
	{
    	LaunchNewCardBTN->Enabled = true;
		NumberOFCard = LaunchNewCardADOQ->FieldByName("minkh")->AsInteger;
		NumberOFCardTextEdit->Text = NumberOFCard;
		SerialNumOFCard.sprintf("%010d", NumberOFCard);

		LaunchNewCardADOQ->Close();
		LaunchNewCardADOQ->SQL->Clear();
		String tmpsqlstr = "select * from BHUSED where BH='";
		tmpsqlstr += SerialNumOFCard;
		tmpsqlstr += "'";
		LaunchNewCardADOQ->SQL->Add(tmpsqlstr);
		LaunchNewCardADOQ->Open();

		if(LaunchNewCardADOQ->IsEmpty())
		{
			SerialOFCardTextEdit->Text = SerialNumOFCard;
        }
		else
		{
			srand((unsigned)time(NULL));
            int tmpint = rand()%10000000000;
            while(1)
            {
                SerialNumOFCard = "";
                SerialNumOFCard.sprintf("%010d", tmpint);

                tmpsqlstr = "select * from BHUSED where BH='";
                tmpsqlstr += SerialNumOFCard;
                tmpsqlstr += "'";

                LaunchNewCardADOQ->Close();
                LaunchNewCardADOQ->SQL->Clear();
                LaunchNewCardADOQ->SQL->Add(tmpsqlstr);
                LaunchNewCardADOQ->Open();
                if(LaunchNewCardADOQ->IsEmpty())
                {
                    SerialOFCardTextEdit->Text = SerialNumOFCard;
                    break;
                }
                else
                {
                    tmpint = rand()%10000000000;
                }
            }
            LaunchNewCardADOQ->Close();
		}
	}
    else
    {
        ShowMessage("系统已无可用卡号，请联系技术人员！");
        UserNameTextEdit->Text = "";
		UserSexComboBox->ItemIndex = 0;
        SectionNameComboBox->ItemIndex = -1;
        ClassNameComboBox->ItemIndex = -1;
        DegreeComboBox->ItemIndex = -1;
        GroupNameComboBox->ItemIndex = -1;
        cxTextEdit4->Text = 1;
        IdentityIDTextEdit->Text = "";
        DegreeTextEdit->Text = 1;
        PerPassWordTextEdit->Text = "0000";
        DepositTextEdit->Text = IntToStr(GlobalFKYJ);
        PrepayTextEdit->Text = "";
		ConsumeRateComboBox->ItemIndex = 0;
		cxTextEdit1->Text = "";
//		UseDateEdit->Date = IncYear(Now(), 3);
//		UseDateEdit->Text = "2016-07-31";
		LaunchNewCardBTN->Enabled = false;
        return;
    }
	LaunchNewCardADOQ->Close();

	UserNameTextEdit->Text = "";
	UserSexComboBox->ItemIndex = 0;
	SectionNameComboBox->ItemIndex = -1;
	ClassNameComboBox->ItemIndex = -1;
	DegreeComboBox->ItemIndex = -1;
	GroupNameComboBox->ItemIndex = -1;
	cxTextEdit4->Text = 1;
	IdentityIDTextEdit->Text = "";
	DegreeTextEdit->Text = 1;
	PerPassWordTextEdit->Text = "0000";
	DepositTextEdit->Text = IntToStr(GlobalFKYJ);
	PrepayTextEdit->Text = "";
	ConsumeRateComboBox->ItemIndex = 0;
	cxTextEdit1->Text = "";
//	UseDateEdit->Date = IncYear(Now(), 3);
//	UseDateEdit->Text = "2016-07-31";
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::NumberOFCardTextEditKeyPress(TObject *Sender,
		  wchar_t &Key)
{
	if((Key<'0'||Key>'9'||(127 == Key)||(8 == Key)) && Key!='\b')
	{
    	if(13 == Key)
        {
        	SerialOFCardTextEdit->SetFocus();
        }
        else
        {
			Key=0;
			ShowMessage("请输入0到9之间的数字！");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::NumberOFCardTextEditExit(TObject *Sender)
{
	String tmpstr = NumberOFCardTextEdit->Text;
	if(tmpstr.Length()>0)
	{
		int cardno = StrToInt(tmpstr);

		if(cardno > 200000)
		{
			ShowMessage("卡号不能大于200000，请重新输入!");
			NumberOFCardTextEdit->Text = "";
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TLaunchNewUserCardFRM::SerialOFCardTextEditKeyPress(TObject *Sender,
		  wchar_t &Key)
{
	if((Key<'0'||Key>'9'||(127 == Key)||(8 == Key)) && Key!='\b')
	{
    	if(13 == Key)
        {
			UserNameTextEdit->SetFocus();
        }
        else
        {
			Key=0;
			ShowMessage("请输入0到9之间的数字！");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::SerialOFCardTextEditExit(TObject *Sender)
{
	String tmpstr = SerialOFCardTextEdit->Text;
	if(10 != tmpstr.Length())
	{
		ShowMessage("编号长度必须为10位!");
		SerialOFCardTextEdit->Text = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::SectionNameComboBoxEnter(TObject *Sender)
{
	LaunchNewCardADOQ->Close();
	LaunchNewCardADOQ->SQL->Clear();
	LaunchNewCardADOQ->SQL->Add("select * from BUMEN");
	LaunchNewCardADOQ->Open();
	SectionNameComboBox->Properties->Items->Clear();
	while(!LaunchNewCardADOQ->Eof)
	{
		SectionNameComboBox->Properties->Items->Add(LaunchNewCardADOQ->FieldByName("BUMEN")->AsAnsiString.Trim());
		LaunchNewCardADOQ->Next();
	}
	SectionNameComboBox->ItemIndex = -1;
	LaunchNewCardADOQ->Close();
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::DegreeComboBoxEnter(TObject *Sender)
{
	LaunchNewCardADOQ->SQL->Clear();
	LaunchNewCardADOQ->SQL->Add("select * from SFZW");
	LaunchNewCardADOQ->Open();
	DegreeComboBox->Properties->Items->Clear();
	while(!LaunchNewCardADOQ->Eof)
	{
		DegreeComboBox->Properties->Items->Add(LaunchNewCardADOQ->FieldByName("ZW")->AsAnsiString.Trim());
		LaunchNewCardADOQ->Next();
	}
	DegreeComboBox->ItemIndex = -1;
	LaunchNewCardADOQ->Close();
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::PrepayTextEditExit(TObject *Sender)
{
	if(!PrepayTextEdit->Text.IsEmpty())
	{
		if(StrToInt(PrepayTextEdit->Text) >= 100000)
		{
			ShowMessage("发卡金额不能超过100000，请重新输入!");
			PrepayTextEdit->Text = "";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::GroupNameComboBoxExit(TObject *Sender)
{
/*	if(-1 == GroupNameComboBox->ItemIndex)
	{
		ShowMessage("请选择用户所在组别！");
		GroupNameComboBox->Text = "";
	}      */
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::ClassNameComboBoxExit(TObject *Sender)
{
/*	if(-1 == ClassNameComboBox->ItemIndex)
	{
		ShowMessage("请选择用户所在班别！");
		ClassNameComboBox->Text = "";
	}*/
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::SectionNameComboBoxKeyPress(TObject *Sender,
          wchar_t &Key)
{
    if(13 == Key)
    	ClassNameComboBox->SetFocus();
	Key = 0;
}
//---------------------------------------------------------------------------
/*								UpdateInfoADOTable->TableName = "CARD";
								UpdateInfoADOTable->Active = true;
								TVarRec InsRecord[32];
								InsRecord[0] = tmpstr;
								InsRecord[1] = NumberOFCard;
								InsRecord[2] = NULL;
								InsRecord[3] = UserNameTextEdit->Text;
								InsRecord[4] = UserSexComboBox->Text;
								InsRecord[5] = IdentityIDTextEdit->Text;
								InsRecord[6] = SectionNameComboBox->Text;
								InsRecord[7] = ClassNameComboBox->Text;
								InsRecord[8] = GroupNameComboBox->Text;
								InsRecord[9] = DegreeComboBox->Text;
								InsRecord[10] = DegreeTextEdit->Text;
								InsRecord[11] = DateofLaunchCard;
								InsRecord[12] = NULL;
								InsRecord[13] = DepositTextEdit->Text;
								InsRecord[14] = 0;
								InsRecord[15] = "发卡";
								InsRecord[16] = PerPassWordTextEdit->Text;
								InsRecord[17] = 1;
								InsRecord[18] = 0;
								InsRecord[19] = DateofLaunchCard;
								InsRecord[20] = 0;
								InsRecord[21] = moneyincard;
								InsRecord[22] = DateofLaunchCard;
								InsRecord[23] = 0;
								InsRecord[24] = moneyincard;
								InsRecord[25] = ConsumeRateComboBox->ItemIndex+1;
								InsRecord[26] = 0;
								InsRecord[27] = moneyincard;
								InsRecord[28] = NULL;
								InsRecord[29] = NULL;
								InsRecord[30] = writecardtype;
								InsRecord[31] = "SuperVisor";

								UpdateInfoADOTable->InsertRecord(InsRecord, 32); */

/*CARD
								ADOCommand1->CommandText = "insert into CARD values('"+tmpstr+"',"+
															IntToStr(NumberOFCard)+",NULL,'"+
															UserNameTextEdit->Text+"','"+
															UserSexComboBox->Text+"','"+
															IdentityIDTextEdit->Text+"','"+
															SectionNameComboBox->Text+"','"+
															ClassNameComboBox->Text+"','"+
															GroupNameComboBox->Text+"','"+
															DegreeComboBox->Text+"','"+
															DegreeTextEdit->Text+"','"+
															DateofLaunchCard+"',NULL,"+
															tmpPrePay+",0,'发卡','"+
															PerPassWordTextEdit->Text+
															"',1,0,'"+DateofLaunchCard+
															"',0,"+moneyincard+",'"+
															DateofLaunchCard+"',0,"+moneyincard+
															",'"+(ConsumeRateComboBox->ItemIndex+1)+
															"',0,"+moneyincard+",NULL,NULL,'1','SuperVisor')";
								ADOCommand1->Execute();
*/

/*CARD_F
								ADOCommand1->CommandText = "";
								ADOCommand1->CommandText = "insert into CARD_F values('"+tmpstr+"',"+
															IntToStr(NumberOFCard)+",NULL,'"+
															UserNameTextEdit->Text+"','"+
															UserSexComboBox->Text+"','"+
															IdentityIDTextEdit->Text+"','"+
															SectionNameComboBox->Text+"','"+
															ClassNameComboBox->Text+"','"+
															GroupNameComboBox->Text+"','"+
															DegreeComboBox->Text+"','"+
															DegreeTextEdit->Text+"','"+
															DateofLaunchCard+"',NULL,"+
															tmpPrePay+",0,'发卡','"+
															PerPassWordTextEdit->Text+
															"',1,0,'"+DateofLaunchCard+
															"',0,"+moneyincard+",'"+
															DateofLaunchCard+"',0,"+moneyincard+
															",'"+(ConsumeRateComboBox->ItemIndex+1)+
															"',0,"+moneyincard+",NULL,NULL,'1','SuperVisor')";
								ADOCommand1->Execute();
*/

/*
					//此时系统没有发行新卡，数据库为空
					NumberOFCard = 1;
					SerialNumOFCard.sprintf("%010d", NumberOFCard);
					NumberOFCardTextEdit->Text = NumberOFCard;
					SerialOFCardTextEdit->Text = SerialNumOFCard;

					NumberOFCardTextEdit->Text = NumberOFCard;
					SerialOFCardTextEdit->Text = SerialNumOFCard;

					if((!UserNameTextEdit->Text.IsEmpty())&&(-1 != UserSexComboBox->ItemIndex)&&
						(-1 != SectionNameComboBox->ItemIndex)&&(-1 != ClassNameComboBox->ItemIndex)&&
						(-1 != DegreeComboBox->ItemIndex)&&(!IdentityIDTextEdit->Text.IsEmpty())&&
						(!PerPassWordTextEdit->Text.IsEmpty())&&(!DepositTextEdit->Text.IsEmpty())&&
						(!PrepayTextEdit->Text.IsEmpty())&&(-1 != ConsumeRateComboBox->ItemIndex))
					{
						WORD writestatus;
						unsigned char writedaytime[4];
						unsigned char writebalance[4];
						unsigned char writeczmm[3];
						unsigned char writecardtype[1];
						unsigned char writekh[4];
						int writetmpkh = atoi(NumberOFCardTextEdit->Text.t_str());
						writekh[0] = (char)(writetmpkh/256/256/256);
						writekh[1] = (char)((writetmpkh%(256*256*256))/256/256);
						writekh[2] = (char)((writetmpkh%(256*256))/256);
						writekh[3] = (char)writetmpkh;

						unsigned char writereadcomno[5] = readcomno;
						unsigned char writekeymode = keymode;
						unsigned char writesecnum = secnum;
						unsigned char writekey[6] = key;
						unsigned char writedwmm[2];
						writedwmm[0] = DWPassword[0];
						writedwmm[1] = DWPassword[1];
						unsigned char writesynum[2];
						writesynum[0] = 0x00;
						writesynum[1] = 0x00;
						unsigned char writemode = 0x00;
						unsigned char writeDelayms = DelaySecond;

						String writetmpstr = DateToStr(UseDateEdit->Date);
						char* writetmpdatestr = writetmpstr.t_str();
						writedaytime[0] = char(((int)writetmpdatestr[2]-48)*16+((int)writetmpdatestr[3]-48));
						writedaytime[1] = char(((int)writetmpdatestr[5]-48)*16+((int)writetmpdatestr[6]-48));
						writedaytime[2] = char(((int)writetmpdatestr[8]-48)*16+((int)writetmpdatestr[9]-48));
						writedaytime[3] = 0x00;

						writesynum[0] = 0x00;
						writesynum[1] = 0x00;

						ShowMessage(PrepayTextEdit->Text.t_str());
						int writetmpbalance = atoi(PrepayTextEdit->Text.t_str())-atoi(DepositTextEdit->Text.t_str());
						writetmpbalance *= 100;
						writebalance[0] = 0x00;
						writebalance[1] = (char)((int)writetmpbalance/65536);
						writetmpbalance = writetmpbalance%65536;
						writebalance[2] = (char)((int)writetmpbalance/256);
						writetmpbalance = writetmpbalance%256;
						writebalance[3] = (char)writetmpbalance;

						unsigned char writetmpczmm[5];
						strcpy(writetmpczmm, PerPassWordTextEdit->Text.t_str());
						writetmpczmm[0] = writetmpczmm[0]<<4;
						writetmpczmm[1] = writetmpczmm[1]<<4;
						writetmpczmm[1] = writetmpczmm[1]>>4;
						writeczmm[0] = writetmpczmm[0] + writetmpczmm[1];
						writetmpczmm[2] = writetmpczmm[2]<<4;
						writetmpczmm[3] = writetmpczmm[3]<<4;
						writetmpczmm[3] = writetmpczmm[3]>>4;
						writeczmm[1] = writetmpczmm[2]+writetmpczmm[3];
						writeczmm[2] = 0x00;

						writecardtype[0] = atoi(DegreeTextEdit->Text.t_str());

						if(LaunchNewCard)
						{
							writestatus = LaunchNewCard(writereadcomno,
														writekeymode,
														writesecnum,
														writekey,
														writekh,
														writebalance,
														writedwmm,
														writesynum,
														writedaytime,
														writecardtype,
														writeczmm,
														writemode,
														writeDelayms);
							if(writestatus)
							{
								ShowMessage("写卡失败！");
							}
							else
							{
								String DateofLaunchCard;
								SYSTEMTIME tmpsystime;
								GetLocalTime(&tmpsystime);
								DateofLaunchCard = DateTimeToStr(SystemTimeToDateTime(tmpsystime));

								int tmpdeposit = atoi(DepositTextEdit->Text.t_str());
								int tmpPrePay = atoi(PrepayTextEdit->Text.t_str());
								int moneyincard = tmpPrePay-tmpdeposit;

								//填写CARD表
								String tmpstr = SerialNumOFCard;
								ADOQuery1->Close();
								ADOQuery1->SQL->Clear();
								String sqlstr = "insert into CARD values(:BH,:KH,:BKH,:XM,:XB,";
								sqlstr = sqlstr+":SFZH,:BM,:BZ,:ZB,:ZW,:JB,:RQ,:TKRQ,:YJ,:TYJ,"+
												":ZT,:GRMM,:BTBZ,:BT_YE,:BTYEDT,:BTSYCS,:SF_YE,"+
												":SFYEDT,:SYCS,:FKSK,:SF_FL,:GLF,:FKJE,:TKJE,:TKBT,"+
												":SF_KL,:USERNAME)";
								ADOQuery1->SQL->Add(sqlstr);
								ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;
								ADOQuery1->Parameters->ParamByName("KH")->Value = (NumberOFCard);
								//ADOQuery1->Parameters->ParamByName("BKH")->Value = NULL;
								ADOQuery1->Parameters->ParamByName("XM")->Value = UserNameTextEdit->Text;
								ADOQuery1->Parameters->ParamByName("XB")->Value = UserSexComboBox->Text;
								ADOQuery1->Parameters->ParamByName("SFZH")->Value = IdentityIDTextEdit->Text;
								ADOQuery1->Parameters->ParamByName("BM")->Value = SectionNameComboBox->Text;
								ADOQuery1->Parameters->ParamByName("BZ")->Value = ClassNameComboBox->Text;
								if(-1 != GroupNameComboBox->ItemIndex)
								{
									ADOQuery1->Parameters->ParamByName("ZB")->Value = GroupNameComboBox->Text;
								}
								ADOQuery1->Parameters->ParamByName("ZW")->Value = DegreeComboBox->Text;
								ADOQuery1->Parameters->ParamByName("JB")->Value = DegreeTextEdit->Text;
								ADOQuery1->Parameters->ParamByName("RQ")->Value = DateofLaunchCard;
								//ADOQuery1->Parameters->ParamByName("TKRQ")->Value = NULL;
								ADOQuery1->Parameters->ParamByName("YJ")->Value = tmpdeposit;
								ADOQuery1->Parameters->ParamByName("TYJ")->Value = 0;
								ADOQuery1->Parameters->ParamByName("ZT")->Value = "发卡";
								ADOQuery1->Parameters->ParamByName("GRMM")->Value = PerPassWordTextEdit->Text;
								ADOQuery1->Parameters->ParamByName("BTBZ")->Value = 1;
								ADOQuery1->Parameters->ParamByName("BT_YE")->Value = 0;
								//ADOQuery1->Parameters->ParamByName("BTYEDT")->Value = NULL;
								ADOQuery1->Parameters->ParamByName("BTSYCS")->Value = 0;
								ADOQuery1->Parameters->ParamByName("SF_YE")->Value = moneyincard;
								ADOQuery1->Parameters->ParamByName("SFYEDT")->Value = DateofLaunchCard;
								ADOQuery1->Parameters->ParamByName("SYCS")->Value = 0;
								ADOQuery1->Parameters->ParamByName("FKSK")->Value = moneyincard;
								ADOQuery1->Parameters->ParamByName("SF_FL")->Value = ConsumeRateComboBox->ItemIndex+1;
								ADOQuery1->Parameters->ParamByName("GLF")->Value = 0;
								ADOQuery1->Parameters->ParamByName("FKJE")->Value = moneyincard;
								//ADOQuery1->Parameters->ParamByName("TKJE")->Value = NULL;
								//ADOQuery1->Parameters->ParamByName("TKBT")->Value = NULL;
								ADOQuery1->Parameters->ParamByName("SF_KL")->Value = 1;
								ADOQuery1->Parameters->ParamByName("USERNAME")->Value = OperatorName;
								ADOQuery1->ExecSQL();

								//填写CARD_F表
								ADOQuery1->SQL->Clear();
								sqlstr = "insert into CARD_F values(:BH,:KH,:BKH,:XM,:XB,";
								sqlstr = sqlstr+":SFZH,:BM,:BZ,:ZB,:ZW,:JB,:RQ,:TKRQ,:YJ,:TYJ,"+
								":ZT,:GRMM,:BTBZ,:BT_YE,:BTYEDT,:BTSYCS,:SF_YE,"+
								":SFYEDT,:SYCS,:FKSK,:SF_FL,:GLF,:FKJE,:TKJE,:TKBT,"+
								":SF_KL,:USERNAME)";
								ADOQuery1->SQL->Add(sqlstr);
								ADOQuery1->Parameters->ParamByName("BH")->Value = SerialNumOFCard;
								ADOQuery1->Parameters->ParamByName("KH")->Value = (NumberOFCard);
								//ADOQuery1->Parameters->ParamByName("BKH")->Value = NULL;
								ADOQuery1->Parameters->ParamByName("XM")->Value = UserNameTextEdit->Text;
								ADOQuery1->Parameters->ParamByName("XB")->Value = UserSexComboBox->Text;
								ADOQuery1->Parameters->ParamByName("SFZH")->Value = IdentityIDTextEdit->Text;
								ADOQuery1->Parameters->ParamByName("BM")->Value = SectionNameComboBox->Text;
								ADOQuery1->Parameters->ParamByName("BZ")->Value = ClassNameComboBox->Text;
								if(-1 != GroupNameComboBox->ItemIndex)
								{
									ADOQuery1->Parameters->ParamByName("ZB")->Value = GroupNameComboBox->Text;
								}
								ADOQuery1->Parameters->ParamByName("ZW")->Value = DegreeComboBox->Text;
								ADOQuery1->Parameters->ParamByName("JB")->Value = DegreeTextEdit->Text;
								ADOQuery1->Parameters->ParamByName("RQ")->Value = DateofLaunchCard;
								//ADOQuery1->Parameters->ParamByName("TKRQ")->Value = NULL;
								ADOQuery1->Parameters->ParamByName("YJ")->Value = tmpdeposit;
								ADOQuery1->Parameters->ParamByName("TYJ")->Value = 0;
								ADOQuery1->Parameters->ParamByName("ZT")->Value = "发卡";
								ADOQuery1->Parameters->ParamByName("GRMM")->Value = PerPassWordTextEdit->Text;
								ADOQuery1->Parameters->ParamByName("BTBZ")->Value = 1;
								ADOQuery1->Parameters->ParamByName("BT_YE")->Value = 0;
								//ADOQuery1->Parameters->ParamByName("BTYEDT")->Value = NULL;
								ADOQuery1->Parameters->ParamByName("BTSYCS")->Value = 0;
								ADOQuery1->Parameters->ParamByName("SF_YE")->Value = moneyincard;
								ADOQuery1->Parameters->ParamByName("SFYEDT")->Value = DateofLaunchCard;
								ADOQuery1->Parameters->ParamByName("SYCS")->Value = 0;
								ADOQuery1->Parameters->ParamByName("FKSK")->Value = moneyincard;
								ADOQuery1->Parameters->ParamByName("SF_FL")->Value = ConsumeRateComboBox->ItemIndex+1;
								ADOQuery1->Parameters->ParamByName("GLF")->Value = 0;
								ADOQuery1->Parameters->ParamByName("FKJE")->Value = moneyincard;
								//ADOQuery1->Parameters->ParamByName("TKJE")->Value = NULL;
								//ADOQuery1->Parameters->ParamByName("TKBT")->Value = NULL;
								ADOQuery1->Parameters->ParamByName("SF_KL")->Value = 1;
								ADOQuery1->Parameters->ParamByName("USERNAME")->Value = OperatorName;
								ADOQuery1->ExecSQL();

								//填写MX,MXBAK表
								ADOQuery1->SQL->Clear();
								sqlstr = "insert into MX values(:BH,:KH,:SF_YE,:SFJE,:SYCS,:SFRQ,:JYNO,:GZZID,:SFLX,:CZY,:SCRQ)";
								ADOQuery1->Parameters->ParamByName("BH")->Value = LaunchNewCardADOQ->FieldByName("BH")->AsString;

								//填写KZT表
								LaunchNewCardADOQ->Edit();
								LaunchNewCardADOQ->FieldByName("SY")->AsString = "Y";
								LaunchNewCardADOQ->FieldByName("FKRQ")->AsString = DateofLaunchCard;
								LaunchNewCardADOQ->Post();

								cxLabel20->Caption = IntToStr(moneyincard);
								ShowMessage("发卡成功！");
								beepofreaddll(readcomno, '10');
							}
						}
						else
						{
							ShowMessage("写卡函数加载失败！");
						}
					}
					else
						ShowMessage("卡信息填写不完整，请填写完整！");*/
















void __fastcall TLaunchNewUserCardFRM::UserNameTextEditKeyPress(TObject *Sender, wchar_t &Key)
{
	if(13 == Key)
    	UserSexComboBox->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::UserSexComboBoxKeyPress(TObject *Sender, wchar_t &Key)
{
	if(13 == Key)
    	SectionNameComboBox->SetFocus();
    Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::ClassNameComboBoxKeyPress(TObject *Sender,
          wchar_t &Key)
{
	if(13 == Key)
    	DegreeComboBox->SetFocus();
    Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::DegreeComboBoxKeyPress(TObject *Sender, wchar_t &Key)
{
	if(13 == Key)
    	GroupNameComboBox->SetFocus();
    Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::GroupNameComboBoxKeyPress(TObject *Sender,
          wchar_t &Key)
{
	if(13 == Key)
    	cxTextEdit4->SetFocus();
    Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::cxTextEdit4KeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<='0'||Key>'9'||(127 == Key)||(8 == Key)) && Key!='\b')
	{
    	if(13 == Key)
        {
            Key = 0;
        	IdentityIDTextEdit->SetFocus();
        }
        else
        {
			Key=0;
			ShowMessage("请输入1到9之间的数字！");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::DegreeTextEditKeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<='0'||Key>'9'||(127 == Key)||(8 == Key)) && Key!='\b')
	{
    	if(13 == Key)
        {
            Key = 0;
        	PerPassWordTextEdit->SetFocus();
        }
        else
        {
			Key=0;
			ShowMessage("请输入1到9之间的数字！");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::DepositTextEditKeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<='0'||Key>'9'||(127 == Key)||(8 == Key)) && Key!='\b')
	{
    	if(13 == Key)
        {
            Key = 0;
        	PrepayTextEdit->SetFocus();
        }
        else
        {
			Key=0;
			ShowMessage("请输入1到9之间的数字！");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TLaunchNewUserCardFRM::ConsumeRateComboBoxKeyPress(TObject *Sender,
          wchar_t &Key)
{
	if(13 == Key)
    	LaunchNewCardBTN->Focused();
    Key = 0;
}
//---------------------------------------------------------------------------


void __fastcall TLaunchNewUserCardFRM::Button1Click(TObject *Sender)
{
	unsigned char test[4];
	test[0] = 0xff;
	test[1] = 0xff;
	test[2] = 0xff;
	test[3] = 0xff;

	unsigned int testint = (unsigned int)test[0]*256*256*256+
							(unsigned int)test[1]*256*256+
							(unsigned int)test[2]*256+
							(unsigned int)test[3];


	AnsiString SerialNumOFCard;
	SerialNumOFCard.sprintf("%010u", testint);
	ShowMessage(SerialNumOFCard);
}
//---------------------------------------------------------------------------


void __fastcall TLaunchNewUserCardFRM::cxButton1Click(TObject *Sender)
{
	//读取卡片序列号作为编号
	WORD readserialstatus;
	unsigned char readserialdelayms;
	unsigned char readserial[4];
	ZeroMemory(readserial, 4);
	readserialdelayms = 0x01;
	readserialstatus = readserialfun(readcomno, readserial);
	if(readserialstatus)
	{
		ShowMessage("无法获取该卡片的序列号，请更换卡片!");
		return;
	}
	else
	{
		unsigned int serialnum = readserial[3]*256*256*256
								 + readserial[2]*256*256
								 + readserial[1]*256
								 + readserial[0];

		AnsiString SerialNumOFCard;

		SerialNumOFCard.sprintf("%010u", serialnum);
		SerialOFCardTextEdit->Text = SerialNumOFCard;

	//	SerialNumOFCard = SerialOFCardTextEdit->Text;
	}
}
//---------------------------------------------------------------------------


