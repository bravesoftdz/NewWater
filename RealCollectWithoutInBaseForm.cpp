//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GlobalParameter.h"
#include "RealCollectWithoutInBaseForm.h"
#include "SDIMAIN.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxCheckBox"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGraphics"
#pragma link "cxGroupBox"
#pragma link "cxListView"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxMemo"
#pragma link "cxProgressBar"
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
TRealCollectWOIBFrm *RealCollectWOIBFrm;
//---------------------------------------------------------------------------
__fastcall TRealCollectWOIBFrm::TRealCollectWOIBFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TRealCollectWOIBFrm::FormShow(TObject *Sender)
{
	if(!Collecting&&!Scanning)
	{
		Panel7->Caption = "���ڽ��С�ɨ������POS����������";
		OnlinePosNum = 0;
   		ModeOFCollect = 5;

		DataDisplayView->Items->Clear();
		ScallProgressBar->Visible = true;
		ScallProgressBar->Position = 0;
		CollectProgressBar->Visible = false;
		RealCollectBTN->Enabled = false;
        InBaseBTN->Enabled = false;
		ExitBTN->Enabled = true;

		if(!ScallPosThread)
		{
			ScallPosThread = new TScallPosThread(true,
												 &Scanning,
												 ScallProgressBar,
												 TreeView1,
												 RealCollectBTN,
												 ExitBTN,
												 cxButton1,
												 Panel7,
												 &OnlinePosNum,
												 CollectDataADOQuery);
			if(ScallPosThread)
			{
				ScallPosThread->Resume();
			}
		}
		else
		{
			if(ScallPosThread->Finished)
			{
				ScallPosThread = new TScallPosThread(true,
				                                     &Scanning,
													 ScallProgressBar,
													 TreeView1,
													 RealCollectBTN,
													 ExitBTN,
													 cxButton1,
													 Panel7,
													 &OnlinePosNum,
													 CollectDataADOQuery);
			}
			if(ScallPosThread)
				ScallPosThread->Resume();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TRealCollectWOIBFrm::FormCreate(TObject *Sender)
{
	OnlinePosNum = 0;

	ScallProgressBar->Visible = true;
	ScallProgressBar->Position = 0;
	CollectProgressBar->Visible = false;
	RealCollectBTN->Enabled = false;
	ExitBTN->Enabled = true;

	Collecting = false;
	Scanning = false;
}
//---------------------------------------------------------------------------
void __fastcall TRealCollectWOIBFrm::ExitBTNClick(TObject *Sender)
{
	if(mrOk == MessageBox(this->Handle, "�Ƿ�ȷ���˳�ʵʱ���ݲɼ�����", "��ȷ��", MB_OKCANCEL|MB_ICONQUESTION))
	{
		if(ScallPosThread)
		{
			if(!ScallPosThread->Finished)
				ScallPosThread->Terminate();
		}

		if(CollectDataWOThread)
		{
			if(!CollectDataWOThread->Finished)
            {
				CollectDataWOThread->Terminate();
                this->Close();
            }
			if(CollectDataWOThread->Finished)
			{
				ModeOFCollect = 0;
				this->Close();
			}
		}

		if(!CollectDataWOThread)
		{
			this->Close();
		}

		ModeOFCollect = 0;

    	if(ReportClick)
        	SDIAppForm->dxNavBar1Group8Click(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TRealCollectWOIBFrm::RealCollectBTNClick(TObject *Sender)
{
	if(true == FileExists(GlobalPath+"\\StoreRealCWOIBData.dat"))
	{
		ShowMessage("�����ϴΡ������ɼ��������ݻ�δ��⣬���Ƚ��С�������⡱!");
		InBaseBTN->Enabled = true;
        return;
	}

	String SaveFileName = GlobalPath;
	SaveFileName += "\\RealWOIBData\\";
	SaveFileName += DateToStr(Date());
	SaveFileName += "_";
	SYSTEMTIME st;
	GetSystemTime(&st);
	SaveFileName += (st.wHour+8)%24;
	SaveFileName += "#";
	SaveFileName += st.wMinute;
	SaveFileName += "#";
	SaveFileName += st.wSecond;
	SaveFileName += ".bak";

//	ShowMessage(SaveFileName.c_str());

	if(DataWOSaveToFileStream.is_open())
		DataWOSaveToFileStream.close();

	DataWOSaveToFileStream.open(SaveFileName.t_str(), ios::app|ios::out, 0);


	if(DataWOSaveToFileStream.is_open())
	{
		if (!CollectDataWOThread)
		{
			CollectDataWOThread = new TCollectDataWOThread(true,
													   &Collecting,
													   cxCheckBox1->Checked,
													   DataDisplayView,
													   TreeView1,
													   &OnlinePosNum,
                                                       CollectProgressBar,
													   CollectDataADOQuery,
													   GSADOT);

			if (CollectDataWOThread)
			{
				Panel7->Caption = "���ڽ��С�ʵʱ���ݲɼ�������";
				ScallProgressBar->Visible = false;
				CollectProgressBar->Visible = true;
				RealCollectBTN->Enabled = false;
				CollectDataWOThread->Resume();
			}
			else
				ShowMessage("CollectdataThread No Exist!");
		}
		else
		{
			if (CollectDataWOThread->Suspended)
			{
				Panel7->Caption = "���ڽ��С�ʵʱ���ݲɼ�������";
				ScallProgressBar->Visible = false;
				CollectProgressBar->Visible = true;
				CollectDataWOThread->Resume();
				RealCollectBTN->Enabled = false;
			//	PauseThreadBTN->Enabled = true;
			}
			else if(CollectDataWOThread->Finished)
			{
				CollectDataWOThread = new TCollectDataWOThread(true,
														   &Collecting,
														   cxCheckBox1->Checked,
														   DataDisplayView,
														   TreeView1,
														   &OnlinePosNum,
                                                           CollectProgressBar,
														   CollectDataADOQuery,
														   GSADOT);
				if (CollectDataWOThread)
				{
					Panel7->Caption = "���ڽ��С�ʵʱ���ݲɼ�������";
					ScallProgressBar->Visible = false;
					CollectProgressBar->Visible = true;
					CollectDataWOThread->Resume();
					RealCollectBTN->Enabled = false;
				}
			}
		}
	}
	else
	{
		ShowMessage("��ʵʱ�ɼ����ݱ����ĵ�ʧ�ܣ�����ϵ��ؼ�����Ա��");
	}
}
//---------------------------------------------------------------------------

void __fastcall TRealCollectWOIBFrm::InBaseBTNClick(TObject *Sender)
{
	if(!RealDataInBaseThread)
	{
		ScallProgressBar->Visible = true;
		CollectProgressBar->Visible = false;
		RealDataInBaseThread = new TRealDataInBaseThread(true,
														   InBaseBTN,
														   RealCollectBTN,
														   ExitBTN,
														   ScallProgressBar,
														   InBaseADOQuery,
														   Panel7);
		if(RealDataInBaseThread)
		{
			Panel7->Caption = "���ڽ��С�����������⡱����!";
			RealDataInBaseThread->Resume();
		}
		else
			ShowMessage("BatchDataInBaseThread No Exist!");
	}
	else
	{
		if(RealDataInBaseThread->Finished)
		{
			ScallProgressBar->Visible = true;
			CollectProgressBar->Visible = false;
			RealDataInBaseThread = new TRealDataInBaseThread(true,
															   InBaseBTN,
															   RealCollectBTN,
															   ExitBTN,
															   ScallProgressBar,
															   InBaseADOQuery,
															   Panel7);
			if(RealDataInBaseThread)
			{
				Panel7->Caption = "���ڽ��С�����������⡱����!";
				RealDataInBaseThread->Resume();
			}
			else
				ShowMessage("BatchDataInBaseThread No Exist!");
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TRealCollectWOIBFrm::cxButton1Click(TObject *Sender)
{
	if(mrOk == MessageBox(this->Handle, "�Ƿ�ȷ��ֹͣʵʱ���ݲɼ���", "��ȷ��", MB_OKCANCEL|MB_ICONQUESTION))
	{
		if(ScallPosThread)
		{
			if(!ScallPosThread->Finished)
				ScallPosThread->Terminate();
		}

		if(CollectDataWOThread)
		{
			if(!CollectDataWOThread->Finished)
            {
				CollectDataWOThread->Terminate();
            }
		}
        if(CollectDataWOThread->Finished)
        	MessageBox(this->Handle, "������������⡱��ť����������⣿", "��ȷ��", MB_OKCANCEL|MB_ICONQUESTION);
    }
}
//---------------------------------------------------------------------------

