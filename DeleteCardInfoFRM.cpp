//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GlobalParameter.h"
#include "DeleteCardInfoFRM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGraphics"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxMemo"
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
TDeleteCardInfoFrom *DeleteCardInfoFrom;
//---------------------------------------------------------------------------
__fastcall TDeleteCardInfoFrom::TDeleteCardInfoFrom(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDeleteCardInfoFrom::DeleteCardInfoBTNClick(TObject *Sender)
{
	WORD status;
	unsigned char keymode,secnum,Delayms;
	keymode = CARDPasswordEdition;//0x03;//CARDPasswordEdition;//0x03;
	secnum = UsingSecNUM;//0x01;
	Delayms = DelaySecond;

	unsigned char key[6];
	key[0] = CARDPassword[0];
	key[1] = CARDPassword[1];
	key[2] = CARDPassword[2];
	key[3] = CARDPassword[3];
	key[4] = CARDPassword[4];
	key[5] = CARDPassword[5];

	if(LoadHModule)
	{
		if(ClearCardInfoProc)
		{
			status = ClearCardInfoProc(readcomno, keymode, secnum, key, Delayms);
			if(0 == status)
			{
            	unsigned char mode;
                unsigned char dwmm[6];
                unsigned char daytime[4];
                unsigned char kh[4];
                unsigned char balance[4];
                unsigned char cardtype[1];
                unsigned char czmm[3];
                unsigned char synum[3];

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
            //写0值到(n+1)*4+1
                ZeroMemory(sendbuf,26);
                ZeroMemory(recbuf, 140);
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

                memcpy(createCRC, &sendbuf[10], 16);
                CRCProc(createCRC, 14, CRC);
                sendbuf[24] = CRC[0];
                sendbuf[25] = CRC[1];

                WORD limitStatus = pacarddllproc(readcomno,sendbuflen,sendbuf,&recbuflen,recbuf,Delayms);

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

                //(n+2)*4+0
                ZeroMemory(sendbuf,26);
                ZeroMemory(recbuf, 140);
                ZeroMemory(createCRC, 16);
                ZeroMemory(CRC, 2);

                sendbuf[0] = (secnum+2)*4+0;//扇区×4+块号
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

				beepofreaddll(readcomno, '10');
				DeleteCardInfoMemo->Lines->Add("清卡信息成功！");
			}
			else
			{
                DeleteCardInfoMemo->Lines->Add("清卡信息失败！");
            }
		}
		else
		{
			ShowMessage("清卡函数加载失败！");
        }
	}
	else
		ShowMessage("加载读写动态链接库失败！");
}
//---------------------------------------------------------------------------

void __fastcall TDeleteCardInfoFrom::ExitDeleteCardInfoBTNClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
