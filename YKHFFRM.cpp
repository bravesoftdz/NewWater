//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GlobalParameter.h"
#include "YKHFFRM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TYKHFForm *YKHFForm;
//---------------------------------------------------------------------------
__fastcall TYKHFForm::TYKHFForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TYKHFForm::Button3Click(TObject *Sender)
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

	Delayms = DelaySecond;
	keymode = CARDPasswordEdition;
	secnum = UsingSecNUM;

	key[0] = CARDPassword[0];
	key[1] = CARDPassword[1];
	key[2] = CARDPassword[2];
	key[3] = CARDPassword[3];
	key[4] = CARDPassword[4];
	key[5] = CARDPassword[5];

    Edit1->Text = "";
	Edit3->Text = "";
	Edit4->Text = "";

	if(LoadHModule)
	{
		if(readcardinfo)
		{
			status = readcardinfo(readcomno,keymode,secnum,key,kh,balance,
								dwmm,synum,daytime,cardtype,czmm,Delayms);

			if(status > 99)
			{
				ShowMessage("通讯错误！");
			}
			else if (1 == status)
			{
				ShowMessage("请把卡片放好！");
			}
			else if (2 == status)
			{
				ShowMessage("卡号大于192000或等于0！");
			}
			else if (4 == status)
			{
				ShowMessage("卡片密码不对！");
			}
			else if (5 == status)
			{
				ShowMessage("读写卡不稳定！");
			}
			else if (6 == status)
			{
				ShowMessage("卡结构不对！");
			}
			else if (10 == status)
			{
				ShowMessage("卡结构不对！");
			}
			else if (0 != status)
			{
				ShowMessage("该卡未发行或已退卡！");
			}
			else
			{
				//读FK与HF
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
                sendbuf[2] = 1;//命令字：1为读，2为写
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
                    ShowMessage("读卡第一块出错，换房失败！");
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
                //read fk hf

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

		//		ADOWithDrawQuery->Close();

				String tmpstr;
				tmpkh = (int)kh[1]*256*256+(int)kh[2]*256+(int)kh[3];
				tmpsycs = (int)synum[0]*256+(int)synum[1];
				tmpintye = (double)balance[1]*256*256+(double)balance[2]*256+(double)balance[3];
				tmpye = tmpintye/100;

				ADOWithDrawQuery->Close();
				ADOWithDrawQuery->SQL->Clear();
				tmpstr = "select * from KZT where kh=";
				tmpstr += tmpkh;
				ADOWithDrawQuery->SQL->Add(tmpstr);
				ADOWithDrawQuery->Open();
				if(!ADOWithDrawQuery->IsEmpty())
				{
					if(0 != ADOWithDrawQuery->FieldByName("GS")->AsInteger)
					{
						ShowMessage("此卡已挂失，请没收此卡！");
						ADOWithDrawQuery->Close();
						return;
					}
				}
				else
				{
					ShowMessage("此卡不是本系统发出的卡！");
					ADOWithDrawQuery->Close();
					return;
				}
				ADOWithDrawQuery->Close();

				ADOWithDrawQuery->SQL->Clear();
				tmpstr = "select * from CARD where kh=";
				tmpstr += tmpkh;
				ADOWithDrawQuery->SQL->Add(tmpstr);
				ADOWithDrawQuery->Open();
				if(!ADOWithDrawQuery->IsEmpty())
				{
                	if((FKS == ADOWithDrawQuery->FieldByName("FK")->AsInteger)&&
                    (HFS == ADOWithDrawQuery->FieldByName("HF")->AsInteger))
                    {
                    	Button4->Enabled = true;
                        Edit3->Text = ADOWithDrawQuery->FieldByName("KH")->AsInteger;
                        Edit4->Text = ADOWithDrawQuery->FieldByName("XM")->AsString.Trim();
                        Edit1->Text = ADOWithDrawQuery->FieldByName("HF")->AsInteger;
                    }
                    else
                    {
                        ShowMessage("此卡以作废!");
                        return;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TYKHFForm::Button4Click(TObject *Sender)
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
				ShowMessage("通讯错误！");
			}
			else if (1 == status)
			{
				ShowMessage("请把卡片放好！");
			}
			else if (2 == status)
			{
				ShowMessage("卡号大于192000或等于0！");
			}
			else if (4 == status)
			{
				ShowMessage("卡片密码不对！");
			}
			else if (5 == status)
			{
				ShowMessage("读写卡不稳定！");
			}
			else if (6 == status)
			{
				ShowMessage("卡结构不对！");
			}
			else if (10 == status)
			{
				ShowMessage("卡结构不对！");
			}
			else if (0 != status)
			{
				ShowMessage("该卡未发行或已退卡！");
			}
			else
			{
            	int tmpfks,tmphfs;
				//读FK与HF
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
                sendbuf[2] = 1;//命令字：1为读，2为写
                sendbuf[3] = keymode;
                sendbuf[4] = key[0];
                sendbuf[5] = key[1];
                sendbuf[6] = key[2];
                sendbuf[7] = key[3];
                sendbuf[8] = key[4];
                sendbuf[9] = key[5];

                WORD limitStatus = pacarddllproc(readcomno,sendbuflen,sendbuf,&recbuflen,recbuf,Delayms);

                if((0 != limitStatus)||(0 != recbuf[2]))
                {
                    beepofreaddll(readcomno, '10');
                    ShowMessage("读卡第一块出错，换房失败！");
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
                    	tmpfks = precbuf[0];
                        tmphfs = precbuf[2];
                    }
                }
                //read fk hf

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

		//		ADOWithDrawQuery->Close();

				String tmpstr;
				tmpkh = (int)kh[1]*256*256+(int)kh[2]*256+(int)kh[3];
				tmpsycs = (int)synum[0]*256+(int)synum[1];
				tmpintye = (double)balance[1]*256*256+(double)balance[2]*256+(double)balance[3];
				tmpye = tmpintye/100;

				if((tmpkh == StrToInt(Edit3->Text))&&(FKS==tmpfks)&&(HFS==tmphfs))
                {
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
                    sendbuf[4] = key[0];
                    sendbuf[5] = key[1];
                    sendbuf[6] = key[2];
                    sendbuf[7] = key[3];
                    sendbuf[8] = key[4];
                    sendbuf[9] = key[5];

                    sendbuf[10] = FKS;
                    sendbuf[11] = ~sendbuf[10];
                    sendbuf[12] = HFS+1;
                    sendbuf[13] = ~sendbuf[12];
                    memcpy(createCRC, &sendbuf[10], 16);
                    CRCProc(createCRC, 14, CRC);
                    sendbuf[24] = CRC[0];
                    sendbuf[25] = CRC[1];

                    WORD limitStatus = pacarddllproc(readcomno,sendbuflen,sendbuf,&recbuflen,recbuf,Delayms);

                    if((0 != limitStatus)||(0 != recbuf[2]))
                    {
                        beepofreaddll(readcomno, '10');
                        ShowMessage("写卡第一块出错，换房失败！");
                        return;
                    }
                    //写0值到(n+1)*4+2
                    ZeroMemory(sendbuf,26);
                    ZeroMemory(recbuf, 140);
                    ZeroMemory(createCRC, 16);
                    ZeroMemory(CRC, 2);

                    sendbuf[0] = (secnum+1)*4+2;//扇区×4+块号
                    sendbuf[1] = 0x60;//固定为0x60
                    sendbuf[2] = 2;//命令字：1为读，2为写
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

                    limitStatus = pacarddllproc(readcomno,sendbuflen,sendbuf,&recbuflen,recbuf,Delayms);

                    if((0 != limitStatus)||(0 != recbuf[2]))
                    {
                        beepofreaddll(readcomno, '10');
                        ShowMessage("写卡第二块出错，换房失败！");
                        return;
                    }
                    //end write 0

                    ShowMessage("换房成功!");
                    Edit3->Text = "";
                    Edit4->Text = "";
                    Edit1->Text = "";
                    ADOWithDrawQuery->Close();
                    ADOWithDrawQuery->SQL->Clear();
                    tmpstr = "select * from CARD where kh=";
                    tmpstr += tmpkh;
                    ADOWithDrawQuery->SQL->Add(tmpstr);
                    ADOWithDrawQuery->Open();
                    if(!ADOWithDrawQuery->IsEmpty())
                    {
                        Button4->Enabled = false;
                        ADOWithDrawQuery->Edit();
                        ADOWithDrawQuery->FieldByName("FK")->AsInteger = FKS;
                        ADOWithDrawQuery->FieldByName("HF")->AsInteger = HFS+1;
                        ADOWithDrawQuery->Post();
                    }
                    ADOWithDrawQuery->Close();
                    ADOWithDrawQuery->SQL->Clear();
                    tmpstr = "select * from CARD_F where kh=";
                    tmpstr += tmpkh;
                    ADOWithDrawQuery->SQL->Add(tmpstr);
                    ADOWithDrawQuery->Open();
                    if(!ADOWithDrawQuery->IsEmpty())
                    {
                        Button4->Enabled = false;
                        ADOWithDrawQuery->Edit();
                        ADOWithDrawQuery->FieldByName("FK")->AsInteger = FKS;
                        ADOWithDrawQuery->FieldByName("HF")->AsInteger = HFS+1;
                        ADOWithDrawQuery->Post();
                    }
                    ADOWithDrawQuery->Close();
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TYKHFForm::Button2Click(TObject *Sender)
{
	unsigned char keymode,secnum,Delayms,mode;
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
//写0值到(n+1)*4+2
    ZeroMemory(sendbuf,26);
    ZeroMemory(recbuf, 140);
    ZeroMemory(createCRC, 16);
    ZeroMemory(CRC, 2);

    sendbuf[0] = (secnum+1)*4+2;//扇区×4+块号
    sendbuf[1] = 0x60;//固定为0x60
    sendbuf[2] = 2;//命令字：1为读，2为写
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
        ShowMessage("写卡第二块出错，坏机清卡失败！");
        return;
    }
    //end write 0

    ShowMessage("坏机清卡成功!");
}
//---------------------------------------------------------------------------
void __fastcall TYKHFForm::Button1Click(TObject *Sender)
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
			/*	int NumberOFCard;

				NumberOFCard = (int)kh[1]*256*256+(int)kh[2]*256+(int)kh[3];

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
					ShowMessage("该卡已经被使用，请更换卡!");
					return;
				}       */

                WORD writestatus;
                unsigned char writedaytime[4];
                unsigned char writebalance[4];
                unsigned char writeczmm[3];
                unsigned char writecardtype[1];
                unsigned char writekh[4];
                int writetmpkh = 0;
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

                unsigned char writedwmm[2];
                writedwmm[0] = DWPassword[0];
                writedwmm[1] = DWPassword[1];
                unsigned char writesynum[2];
                writesynum[0] = 0x00;
                writesynum[1] = 0x00;
                unsigned char writemode = 0x00;
                unsigned char writeDelayms = DelaySecond;


     //			writesynum[0] = 0x00;
     //			writesynum[1] = 0x00;

     //			ShowMessage(PrepayTextEdit->Text.t_str());
                int writetmpbalance = 0;//-atoi(DepositTextEdit->Text.t_str());
                writetmpbalance *= 100;
                writebalance[0] = 0x00;
                writebalance[1] = (char)((int)writetmpbalance/65536);
                writetmpbalance = writetmpbalance%65536;
                writebalance[2] = (char)((int)writetmpbalance/256);
                writetmpbalance = writetmpbalance%256;
                writebalance[3] = (char)writetmpbalance;

                unsigned char writetmpczmm[5];
                writetmpczmm[0] = writetmpczmm[0]<<4;
                writetmpczmm[1] = writetmpczmm[1]<<4;
                writetmpczmm[1] = writetmpczmm[1]>>4;
                writeczmm[0] = writetmpczmm[0] + writetmpczmm[1];
                writetmpczmm[2] = writetmpczmm[2]<<4;
                writetmpczmm[3] = writetmpczmm[3]<<4;
                writetmpczmm[3] = writetmpczmm[3]>>4;
                writeczmm[1] = writetmpczmm[2]+writetmpczmm[3];
                writeczmm[2] = 0x00;

                writecardtype[0] = 1;

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
                            ShowMessage("写卡第一块出错，发测试卡失败！");
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
                            ShowMessage("写卡第二块出错，发测试卡失败！");
                            return;
                        }
                        //end write 0

                        //填写操作记录表
                        ADOQuery1->Close();
                        ADOQuery1->SQL->Clear();
                        String sqlstr = "insert into OperationList values(:BH,:KH,:JE,:YE,:LX,:Operator,:DateTime)";
                        ADOQuery1->SQL->Add(sqlstr);
                        ADOQuery1->Parameters->ParamByName("BH")->Value = "";//LaunchNewCardADOQ->FieldByName("BH")->AsString;
                        ADOQuery1->Parameters->ParamByName("KH")->Value = 0;
                        ADOQuery1->Parameters->ParamByName("JE")->Value = 0;
                        ADOQuery1->Parameters->ParamByName("YE")->Value = 0;
                        ADOQuery1->Parameters->ParamByName("LX")->Value = "发0卡";
                        ADOQuery1->Parameters->ParamByName("Operator")->Value = OperatorName;
                        ADOQuery1->Parameters->ParamByName("DateTime")->Value = DateTimeToStr(Now());
                        ADOQuery1->ExecSQL();
                        ADOQuery1->Close();
                        ShowMessage("发测试卡成功!");
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TYKHFForm::FormShow(TObject *Sender)
{
	Edit1->Text = "";
	Edit3->Text = "";
    Edit4->Text = "";
    Button4->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TYKHFForm::Button5Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

