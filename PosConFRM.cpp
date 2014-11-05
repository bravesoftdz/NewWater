// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PosConFRM.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGraphics"
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
#pragma link "cxGroupBox"
#pragma link "cxRadioGroup"
#pragma link "cxLabel"
#pragma link "cxDropDownEdit"
#pragma link "cxMaskEdit"
#pragma link "cxButtons"
#pragma link "cxListView"
#pragma link "cxSpinButton"
#pragma link "cxSpinEdit"
#pragma link "cxProgressBar"
#pragma link "cxMemo"
#pragma resource "*.dfm"
TPosConfigFRM *PosConfigFRM;

// ---------------------------------------------------------------------------
__fastcall TPosConfigFRM::TPosConfigFRM(TComponent* Owner) : TForm(Owner)
{
}

// --------------------------------------------------------------------------
void __fastcall TPosConfigFRM::cxButton4Click(TObject *Sender)
{
	if(ScanAllPosThread)
	{
		if(!ScanAllPosThread->Finished)
		{
			ScanAllPosThread->Terminate();
			this->Close();
	   //		SDIAppForm->dxNavBar1->Enabled = true;
		}
		else
		{
			this->Close();
		//	SDIAppForm->dxNavBar1->Enabled = true;
        }
	}
	else
	{
		this->Close();
   //		SDIAppForm->dxNavBar1->Enabled = true;
	}
	PosContag = false;
}
// ---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::FormShow(TObject *Sender)
{
	SCanPosADOQ->Close();
	SCanPosADOQ->SQL->Clear();
	SCanPosADOQ->SQL->Add("select * from STNAME");
	SCanPosADOQ->Open();
	if(!SCanPosADOQ->IsEmpty())
	{
		SCanPosADOQ->First();
		PosPlaceComBox->Properties->Items->Clear();
		while(!SCanPosADOQ->Eof)
		{
			PosPlaceComBox->Properties->Items->Add(SCanPosADOQ->FieldByName("STNAME")->AsAnsiString.Trim());
			SCanPosADOQ->Next();
		}
	}
	else
	{
		MessageBox(this->Handle, "û�����ѵص������Ϣ������ϵ������Ա����������ݿ�!", "DataBase Empty Error", MB_OK|MB_ICONWARNING);
    }
	SCanPosADOQ->Close();

	Panel3->Width = cxGroupBox5->Width/2;
	PosContag = true;
	SetSingleBTN->Enabled = false;
	SetAllBaseBTN->Enabled = false;
	ScanPosBTN->Enabled = true;
	SetAllPosBTN->Enabled = false;
//	PauseBTN->Enabled = false;
	ScanTag = false;
	POSListView->Items->Clear();
	DelOneBTN->Enabled = false;
	AddOneBTN->Enabled = false;
	AddDBTN->Enabled = false;
	SelectAllBTN->Enabled = false;
	CancelSelAllBTN->Enabled = false;
	SCanProBar->Position = 0;
/*	if(!ScanPosInBaseThread)
	{
		ScanPosInBaseThread = new TSCanPosInBaseThread(true,
													   SCanPosADOQ,
													   POSListView,
													   SetSingleBTN,
													   SetAllPosBTN,
													   AddOneBTN,
                                                       AddDBTN,
													   DelOneBTN,
													   cxButton4,
													   ScanPosBTN,
                                                       SelectAllBTN,
													   CancelSelAllBTN,
													   SetAllBaseBTN,
													   &ScanTag,
													   SCanProBar);
		if(ScanPosInBaseThread)
		{
			ScanPosInBaseThread->Resume();
			ScanPosBTN->Enabled = false;
//			PauseBTN->Enabled = false;
		}
	}
	else
	{
		if(ScanPosInBaseThread->Finished)
		{
			ScanPosInBaseThread = new TSCanPosInBaseThread(true,
														   SCanPosADOQ,
														   POSListView,
														   SetSingleBTN,
														   SetAllPosBTN,
														   AddOneBTN,
                                                           AddDBTN,
														   DelOneBTN,
														   cxButton4,
														   ScanPosBTN,
                                                           SelectAllBTN,
														   CancelSelAllBTN,
														   SetAllBaseBTN,
														   &ScanTag,
														   SCanProBar);
			if(ScanPosInBaseThread)
			{
				ScanPosInBaseThread->Resume();
				ScanPosBTN->Enabled = false;
//				PauseBTN->Enabled = false;
			}
        }
	}     */
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::ScanPosBTNClick(TObject *Sender)
{
	SetSingleBTN->Enabled = false;
	DelOneBTN->Enabled = false;
	AddOneBTN->Enabled = false;
	SetAllPosBTN->Enabled = false;
	cxButton4->Enabled = false;
	ScanPosBTN->Enabled = false;

	PauseBTN->Enabled = false;
	ScanTag = false;
	POSListView->Items->Clear();
	if(!ScanPosInBaseThread)
	{
		ScanPosInBaseThread = new TSCanPosInBaseThread(true,
													   SCanPosADOQ,
													   POSListView,
													   SetSingleBTN,
													   SetAllPosBTN,
													   AddOneBTN,
                                                       AddDBTN,
													   DelOneBTN,
													   cxButton4,
													   ScanPosBTN,
                                                       SelectAllBTN,
													   CancelSelAllBTN,
													   SetAllBaseBTN,
													   &ScanTag,
													   SCanProBar);
		if(ScanPosInBaseThread)
		{
			ScanPosInBaseThread->Resume();
			ScanPosBTN->Enabled = false;
			PauseBTN->Enabled = false;
		}
	}
	else
	{
		if(ScanPosInBaseThread->Finished)
		{
			ScanPosInBaseThread = new TSCanPosInBaseThread(true,
														   SCanPosADOQ,
														   POSListView,
														   SetSingleBTN,
														   SetAllPosBTN,
														   AddOneBTN,
                                                           AddDBTN,
														   DelOneBTN,
														   cxButton4,
														   ScanPosBTN,
                                                           SelectAllBTN,
														   CancelSelAllBTN,
														   SetAllBaseBTN,
														   &ScanTag,
														   SCanProBar);
			if(ScanPosInBaseThread)
			{
				ScanPosInBaseThread->Resume();
//				ScanPosBTN->Enabled = false;
				PauseBTN->Enabled = false;
			}
        }
	}
/*	if (getusbcomportdll)
	{
		string ComStr = getusbcomportdll();
//		if (ComStr.empty())
//			MessageBox(NULL, "û��POS���������磬����COM�������Ƿ�������", "NO Pos Connected!", MB_OK | MB_ICONERROR);
//		else
//		{
		if(!ScanAllPosThread)
		{
			ScanAllPosThread = new TScanAllPosThread(true,
													 ComStr,
													 SCanProBar,
													 POSListView,
													 SetSingleBTN,
													 SetAllPosBTN,
													 PauseBTN,
													 ScanPosBTN,
													 cxButton4,
													 &ScanTag,
													 SCanPosADOQ);
			if(ScanAllPosThread)
			{
				ScanAllPosThread->Resume();
				ScanPosBTN->Enabled = false;
				PauseBTN->Enabled = true;
				SetSingleBTN->Enabled = false;
				DelOneBTN->Enabled = false;
				AddOneBTN->Enabled = false;
				SetAllPosBTN->Enabled = false;
				cxButton4->Enabled = false;
			}
		}
		else
		{
			if(ScanAllPosThread->Finished)
			{
				ScanAllPosThread = new TScanAllPosThread(true,
														 ComStr,
														 SCanProBar,
														 POSListView,
														 SetSingleBTN,
														 SetAllPosBTN,
														 PauseBTN,
														 ScanPosBTN,
														 cxButton4,
														 &ScanTag,
														 SCanPosADOQ);
				ScanAllPosThread->Resume();
				ScanPosBTN->Enabled = false;
				PauseBTN->Enabled = true;
				SetSingleBTN->Enabled = false;
				DelOneBTN->Enabled = false;
				AddOneBTN->Enabled = false;
				SetAllPosBTN->Enabled = false;
				cxButton4->Enabled = false;
			}
		}
	//	}
	}   */
}
// ---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::PauseBTNClick(TObject *Sender)
{
/*	if(mrOk == MessageBox(this->Handle, "�Ƿ�ȷ����ֹɨ��POS������", "��ȷ��", MB_OKCANCEL))
	{
		if(ScanAllPosThread)
		{
			if(!ScanAllPosThread->Finished)
				ScanAllPosThread->Terminate();
		}
		SetSingleBTN->Enabled = true;
		DelOneBTN->Enabled = true;
		AddOneBTN->Enabled = true;
		SetAllPosBTN->Enabled = true;
		cxButton4->Enabled = true;
	} */
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::AddOneBTNClick(TObject *Sender)
{
	ADDPOSForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::AddDBTNClick(TObject *Sender)
{
    AddMPOSForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::DelOneBTNClick(TObject *Sender)
{
	if(POSListView->Selected)
	{
		if(mrOk == MessageBox(this->Handle, "��ȷ��Ҫɾ����̨POS�豸��?", "ɾ������", MB_OKCANCEL))
		{
			TListItem* tmpitem = POSListView->Selected;
			POSPARA* para = (POSPARA*)tmpitem->Data;
			TmpADOQ->Close();
			TmpADOQ->SQL->Clear();
			String sqlstr = "select * from SFJPARAM where ";
			sqlstr += "JH=";
			sqlstr += para->posnum;
			sqlstr += " and SFJPORT=";
			sqlstr += para->comnum;
			TmpADOQ->SQL->Add(sqlstr);
			TmpADOQ->Open();
			if(!TmpADOQ->IsEmpty())
				TmpADOQ->Delete();
			TmpADOQ->Close();
			tmpitem->Delete();
			ShowMessage("��ɾ��POS�豸");
		}
	}
	else
	{
		ShowMessage("��ѡ��Ҫɾ����POS�豸!");
    }
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::PassWordEditKeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮�������!");
	}
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::MaxEditKeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮�������!");
	}
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::FormCreate(TObject *Sender)
{
	FOriginalcxListViewWindowProc = POSListView->InnerListView->WindowProc;
  	POSListView->InnerListView->WindowProc = cxListViewWindowProcEx;

	SCanPosADOQ->Close();
	SCanPosADOQ->SQL->Clear();
	SCanPosADOQ->SQL->Add("select * from STNAME");
	SCanPosADOQ->Open();
	if(!SCanPosADOQ->IsEmpty())
	{
		SCanPosADOQ->First();
		PosPlaceComBox->Properties->Items->Clear();
		while(!SCanPosADOQ->Eof)
		{
			PosPlaceComBox->Properties->Items->Add(SCanPosADOQ->FieldByName("STNAME")->AsAnsiString.Trim());
			SCanPosADOQ->Next();
		}
	}
	else
	{
		MessageBox(this->Handle, "û�����ѵص������Ϣ������ϵ������Ա����������ݿ�!", "DataBase Empty Error", MB_OK|MB_ICONWARNING);
    }
	SCanPosADOQ->Close();

}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::cxListViewWindowProcEx(TMessage &message)
{
    if(CN_NOTIFY == message.Msg)
    {
        if(PNMHdr(message.LParam)->code == LVN_ITEMCHANGED)
        {
        	if(PNMListView(message.LParam)->uChanged&&LVIF_STATE)
            {
            	DWORD dw1 = PNMListView(message.LParam)->uOldState;//&&LVIS_STATEIMAGEMASK;
                DWORD dw2 = PNMListView(message.LParam)->uNewState;//&&LVIS_STATEIMAGEMASK;
            	if((dw1!=dw2)&&(dw1 != 0))
                {
                    //ShowMessage("check click");
                    if(8192 == dw2)
                    	POSListView->Items[0].Item[PNMListView(message.LParam)->iItem]->Selected = true;
                    else if(4096 == dw2)
                        POSListView->Items[0].Item[PNMListView(message.LParam)->iItem]->Selected = false;
                }
            }
        }
    }
    FOriginalcxListViewWindowProc(message);
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::PassWordEditExit(TObject *Sender)
{
/*	if(!PassWordEdit->Text.IsEmpty())
	{
		String tmpstr = PassWordEdit->Text;
		if(tmpstr.Length() != 4)
		{
			ShowMessage("��������λ������!");
			PassWordEdit->Text = "";
		}
	} */
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::POSListViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected)
{
	if(!ScanTag)
	{
		TListItem* tmpitem = POSListView->Selected;
		if(tmpitem)
		{
		//	if(2 == ((POSPARA*)(tmpitem->Data))->tag)
			{
				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				String sqlstr = "select * from SFJPARAM where JH=";
				POSPARA* para = (POSPARA*)tmpitem->Data;
				sqlstr += para->posnum;
				sqlstr += " and SFJPORT=";
				sqlstr += para->comnum;
				ADOQuery1->SQL->Add(sqlstr);
				ADOQuery1->Open();
				if(!ADOQuery1->IsEmpty())
				{
					ADOQuery1->First();
					MaxEdit->Text = ADOQuery1->FieldByName("MAXXF")->AsAnsiString.Trim();
					PassWordEdit->Text = ADOQuery1->FieldByName("PASSWORD")->AsString.Trim();
					PosStyleComBox->ItemIndex = ADOQuery1->FieldByName("JX")->AsInteger;
				//	PosPlaceComBox->Text = ADOQuery1->FieldByName("STNAME")->AsAnsiString.Trim();
                    PosPlaceComBox->ItemIndex = ADOQuery1->FieldByName("STID")->AsInteger - 1;
				   	POSNumEdit->Text = ADOQuery1->FieldByName("JH")->AsInteger;
					ComNumEdit->Text = ADOQuery1->FieldByName("SFJPORT")->AsInteger;
                    DMaxEdit->Text = ADOQuery1->FieldByName("MAXZZZE")->AsInteger;
                    CheckBox1->Checked = ADOQuery1->FieldByName("DINGCAN")->AsBoolean;
                    CheckBox2->Checked = ADOQuery1->FieldByName("DELBT")->AsBoolean;
					PosStyleComBox->Text = ADOQuery1->FieldByName("JQLX")->AsString.Trim();

					CheckBox3->Checked = ADOQuery1->FieldByName("MAXCSTAG")->AsBoolean;
					if(CheckBox3->Checked)
					{
						MaxCSEdit->Enabled = true;
						MaxCSEdit->Text = ADOQuery1->FieldByName("MAXCS")->AsInteger;
					}
					else
					{
						MaxCSEdit->Text = "";
						MaxCSEdit->Enabled = false;
					}
				}
				ADOQuery1->Close();
//                if(tmpitem->Checked)
//                	tmpitem->Checked = false;
//                else
                	tmpitem->Checked = true;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::SetSingleBTNClick(TObject *Sender)
{
	if(POSListView->Selected)
	{
    	if(MaxEdit->Text.IsEmpty()||DMaxEdit->Text.IsEmpty()||
        	POSNumEdit->Text.IsEmpty()||ComNumEdit->Text.IsEmpty()||
            (-1 == PosPlaceComBox->ItemIndex))
        {
        	ShowMessage("������������POS��Ϣ!");
            return;
        }

		if(!PassWordEdit->Text.IsEmpty())
		{
			String tmpstr = PassWordEdit->Text;
			if(tmpstr.Length() != 4)
			{
				ShowMessage("��������λ������!");
				PassWordEdit->Text = "";
				return;
			}
		}
		TListItem* tmpitem = POSListView->Selected;
		POSPARA* para = (POSPARA*)tmpitem->Data;
		String sqlstr = "select * from SFJPARAM where JH=";
		sqlstr += para->posnum;
		sqlstr += " and SFJPORT=";
		sqlstr += para->comnum;
		TmpADOQ->Close();
		TmpADOQ->SQL->Clear();
		TmpADOQ->SQL->Add(sqlstr);
		TmpADOQ->Open();
		if(!TmpADOQ->IsEmpty())
		{
			TmpADOQ->Edit();
			TmpADOQ->FieldByName("SFJLX")->AsInteger = PosStyleComBox->ItemIndex;
			TmpADOQ->FieldByName("STID")->AsInteger = PosPlaceComBox->ItemIndex+1;
			TmpADOQ->FieldByName("STNAME")->AsString = PosPlaceComBox->Text;
			TmpADOQ->FieldByName("MAXXF")->AsInteger = StrToInt(MaxEdit->Text);
			TmpADOQ->FieldByName("MAXZZZE")->AsInteger = StrToInt(DMaxEdit->Text);
			TmpADOQ->FieldByName("JH")->AsInteger = StrToInt(POSNumEdit->Text);
			TmpADOQ->FieldByName("SFJPORT")->AsInteger = StrToInt(ComNumEdit->Text);
			TmpADOQ->FieldByName("PASSWORD")->AsString = PassWordEdit->Text;
			TmpADOQ->FieldByName("DINGCAN")->AsBoolean = CheckBox1->Checked;
			TmpADOQ->FieldByName("DELBT")->AsBoolean = CheckBox2->Checked;

			TmpADOQ->FieldByName("MAXCSTAG")->AsBoolean = CheckBox3->Checked;

			if(CheckBox3->Checked)
			{
				if(!MaxCSEdit->Text.IsEmpty())
					TmpADOQ->FieldByName("MAXCS")->AsInteger = StrToInt(MaxCSEdit->Text);
				else
					TmpADOQ->FieldByName("MAXCS")->AsInteger = 0;
			}
			else
			{
				TmpADOQ->FieldByName("MAXCS")->AsInteger = 0;
			}

			TmpADOQ->FieldByName("JQLX")->AsString = PosStyleComBox->Text;
			TmpADOQ->Post();
			String nodestr = StrToInt(POSNumEdit->Text);
			nodestr += "��POS��:COM";
			nodestr += StrToInt(ComNumEdit->Text);
			tmpitem->Caption = nodestr;
			para->posnum = StrToInt(POSNumEdit->Text);
			para->comnum = StrToInt(ComNumEdit->Text);
		}
		TmpADOQ->Close();
        MessageBox(this->Handle, "����POS�����!", "Set POS", MB_OK|MB_ICONWARNING);
	}
	else
	{
		MessageBox(this->Handle, "����ѡ��Ҫ���õ�POS��!", "Select POS", MB_OK|MB_ICONWARNING);
	}
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::SetAllPosBTNClick(TObject *Sender)
{
//�´�����POS������	��Ҫ���߳̽�������
	int tagint = 0;
    for(int i = 0; i < POSListView->Items->Count; i++)
    {
        TListItem* tmpitem = POSListView->Items->Item[i];
        if(tmpitem->Checked)
        {
        	tagint++;
        	break;
        }
    }

    if(!tagint)
    {
        ShowMessage("��ѡ��Ҫ���ز�����POS��!");
        return;
    }

	if(!SetAllPosParamThread)
	{
		SetAllPosParamThread = new TSetAllPosParamThread(true,
														 TmpADOQ,
														 POSListView,
														 SetAllPosBTN,
														 SetSingleBTN,
														 DelOneBTN,
														 AddOneBTN,
														 AddDBTN,
														 ScanPosBTN,
														 PauseBTN,
														 cxButton4,
														 SelectAllBTN,
														 CancelSelAllBTN,
														 SetAllBaseBTN,
														 SCanProBar,
                                                         CheckBox1);
		if(SetAllPosParamThread)
		{
			SetAllPosParamThread->Resume();
		}
	}
	else
	{
		if(SetAllPosParamThread->Finished)
		{
			SetAllPosParamThread = new TSetAllPosParamThread(true,
															 TmpADOQ,
															 POSListView,
															 SetAllPosBTN,
															 SetSingleBTN,
															 DelOneBTN,
															 AddOneBTN,
                                                             AddDBTN,
															 ScanPosBTN,
															 PauseBTN,
															 cxButton4,
                                                             SelectAllBTN,
															 CancelSelAllBTN,
															 SetAllBaseBTN,
															 SCanProBar,
                                                             CheckBox1);
			if(SetAllPosParamThread)
			{
				SetAllPosParamThread->Resume();
			}
        }
    }
}
//---------------------------------------------------------------------------



void __fastcall TPosConfigFRM::SelectAllBTNClick(TObject *Sender)
{
	//POSListView->Items[0].Item[PNMListView(message.LParam)->iItem]->Selected = true;
    int allitem = POSListView->Items->Count;
    for(int i = 0; i < allitem; i++)
    {
    	POSListView->Items[0].Item[i]->Checked = true;
    }
    POSListView->SelectAll();
    POSListView->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::CancelSelAllBTNClick(TObject *Sender)
{
	int allitem = POSListView->Items->Count;
    for(int i = 0; i < allitem; i++)
    {
    	POSListView->Items[0].Item[i]->Checked = false;
        POSListView->Items[0].Item[i]->Selected = false;
    }
    POSListView->SetFocus();
//	POSListView->Checkboxes = true;
}
//---------------------------------------------------------------------------



/*	TListItem* tmpitem = POSListView->Selected;
    POSPARA* para = (POSPARA*)tmpitem->Data;
    String sqlstr = "select * from SFJPARAM where JH=";
    sqlstr += para->posnum;
    sqlstr += " and SFJPORT=";
    sqlstr += para->comnum;
    ShowMessage(sqlstr);  */


/*    TPoint lvCursosPos;
    lvCursosPos = POSListView->ScreenToClient(Mouse->CursorPos);

    THitTests hitest = POSListView->GetHitTestInfoAt(lvCursosPos.x, lvCursosPos.y);

    TListItem* tmpitem = POSListView->GetItemAt(lvCursosPos.x, lvCursosPos.y);

    if(tmpitem)
    {
    	TListItem* tmpitem = POSListView->GetItemAt(lvCursosPos.x, lvCursosPos.y);
        if(tmpitem)
        {
        	tmpitem->Checked = !tmpitem->Checked;
            tmpitem->Selected = true;
        }
    }*/

 /*
void __fastcall TPosConfigFRM::SetAllBTNClick(TObject *Sender)
{
	if((PosStyleComBox->ItemIndex != -1)&&(PosPlaceComBox->ItemIndex != -1)&&(MaxEdit->Text != "")&&(PassWordEdit->Text != ""))
	{
		int poscount = POSListView->Items->Count;
		for(int i = 0; i<poscount-1; i++)
		{
			POSListView->ItemIndex = i;
			TListItem* tmpitem = POSListView->Selected;
			POSPARA* para = (POSPARA*)(tmpitem->Data);
		//	String out = para->posnum;
		//	out += para->comnum;
		//	out += para->tag;
		//	ShowMessage(out);

			if(1 == para->tag)
			{
				unsigned char CMD = 0x32;
				WORD nSendStr = 126;
				WORD status;

				unsigned char SendStr[200] = "";
				unsigned char writeczmm[5] = "";

				TmpADOQ->Close();
				TmpADOQ->SQL->Clear();
				TmpADOQ->SQL->Add("select * from XTSET");
				TmpADOQ->Open();
				strcpy(writeczmm, TmpADOQ->FieldByName("DWMM")->AsAnsiString.c_str());
				TmpADOQ->Close();

				SendStr[0] = UsingSecNUM;//0x01; //������
				SendStr[1] = 0x00; //��������

				writeczmm[0] = writeczmm[0]<<4;
				writeczmm[1] = writeczmm[1]<<4;
				writeczmm[1] = writeczmm[1]>>4;
				SendStr[2] = writeczmm[0] + writeczmm[1];  //��λ����
				writeczmm[2] = writeczmm[2]<<4;
				writeczmm[3] = writeczmm[4]<<4;
				writeczmm[3] = writeczmm[4]>>4;
				SendStr[3] = writeczmm[2] + writeczmm[3];   //��λ����

				SendStr[4] = 0x00;    //����
				SendStr[5] = para->posnum;// 0x00;    //���Ų��ı�����ֵ������


				String Hmm = "0x" + PassWordEdit->Text.SubString(1, 2);
				String Lmm = "0x" + PassWordEdit->Text.SubString(3, 2);
				SendStr[6] = (unsigned char)StrToInt(Hmm);   //��������
				SendStr[7] = (unsigned char)StrToInt(Lmm);   //��������

				for (int i = 8; i <= 37; i++)
				{
					SendStr[i] = 0x00;        //����
				}

				SendStr[38] = CARDPasswordEdition;//0x01; 	//����汾

				SendStr[39] = CARDPassword[0];//0x00;     //MF�����룿����
				SendStr[40] = CARDPassword[1];//0x00;     //MF�����룿����
				SendStr[41] = CARDPassword[2];//0x00;     //MF�����룿����
				SendStr[42] = CARDPassword[3];//0x00;     //MF�����룿����
				SendStr[43] = CARDPassword[4];//0x00;     //MF�����룿����
				SendStr[44] = CARDPassword[5];//0x00;     //MF�����룿����

				int tmpmax = StrToInt(MaxEdit->Text)*100;      //�������
				SendStr[45] = (unsigned char)((int)(tmpmax/65536));
				SendStr[46] = (unsigned char)((int)((tmpmax%65536)/256));
				SendStr[47] = (unsigned char)(tmpmax%256);

				SendStr[48] = 0x00;    //�̶����ѽ��
				SendStr[49] = 0x00;    //�̶����ѽ��
				SendStr[50] = 0x00;    //�̶����ѽ��

				SendStr[51] = 0x00;    //��λ�̶����ѽ��
				SendStr[52] = 0x00;    //��λ�̶����ѽ��
				SendStr[53] = 0x00;    //��λ�̶����ѽ��

				TmpADOQ->Close();
				TmpADOQ->SQL->Clear();
				TmpADOQ->SQL->Add("select * from secnum");
				TmpADOQ->Open();
				if(!TmpADOQ->IsEmpty())
				{
					int Max1 = TmpADOQ->FieldByName("daymaxxf")->AsFloat*100;
					int Max2 = TmpADOQ->FieldByName("daymaxxf1")->AsFloat*100;
					int Max3 = TmpADOQ->FieldByName("daymaxxf2")->AsFloat*100;
					int Max4 = TmpADOQ->FieldByName("daymaxxf3")->AsFloat*100;
					int Max5 = TmpADOQ->FieldByName("daymaxxf4")->AsFloat*100;

					//ÿ���������begin
					SendStr[54] = (unsigned char)((int)(Max1/65536));
					SendStr[55] = (unsigned char)((int)((Max1%65536)/256));
					SendStr[56] = (unsigned char)(Max1%256);
					for (int i = 57; i <= 89; i++)
					{
						SendStr[i] = 0x00;
					}

					SendStr[90] = (unsigned char)((int)(Max2/65536));
					SendStr[91] = (unsigned char)((int)((Max2%65536)/256));
					SendStr[92] = (unsigned char)(Max2%256);

					SendStr[93] = (unsigned char)((int)(Max3/65536));
					SendStr[94] = (unsigned char)((int)((Max3%65536)/256));
					SendStr[95] = (unsigned char)(Max3%256);

					SendStr[96] = (unsigned char)((int)(Max4/65536));
					SendStr[97] = (unsigned char)((int)((Max4%65536)/256));
					SendStr[98] = (unsigned char)(Max4%256);

					SendStr[99] = (unsigned char)((int)(Max5/65536));
					SendStr[100] = (unsigned char)((int)((Max5%65536)/256));
					SendStr[101] = (unsigned char)(Max5%256);
					//ÿ���������end
                }
				TmpADOQ->Close();

				status = SerSendFunc((unsigned char)(para->comnum),
									 WORD(para->posnum),
									 CMD,
									 SendStr,
									 nSendStr,
									 1);
				if(0 == status)
				{
					//����ʱ��
					CMD = 0x31;
					String datestr = DateTimeToStr(Now());
					char* timepstr = datestr.t_str();

					SendStr[0] = (unsigned char)(((int)timepstr[2]-48)*16+(int)timepstr[3]-48);
					SendStr[1] = (unsigned char)(((int)timepstr[5]-48)*16+(int)timepstr[6]-48);
					SendStr[2] = (unsigned char)(((int)timepstr[8]-48)*16+(int)timepstr[9]-48);

					if(19 == datestr.Length())
					{
						SendStr[3] = (unsigned char)(((int)timepstr[11]-48)*16+(int)timepstr[12]-48);
						SendStr[4] = (unsigned char)(((int)timepstr[14]-48)*16+(int)timepstr[15]-48);
						SendStr[5] = (unsigned char)(((int)timepstr[17]-48)*16+(int)timepstr[18]-48);
					}
					else
					{
						SendStr[3] = (unsigned char)((int)timepstr[11]-48);
						SendStr[4] = (unsigned char)(((int)timepstr[13]-48)*16+(int)timepstr[14]-48);
						SendStr[5] = (unsigned char)(((int)timepstr[16]-48)*16+(int)timepstr[17]-48);
					}

					nSendStr = 8;

					status = SerSendFunc((unsigned char)(para->comnum),
										WORD(para->posnum),
										CMD,
										SendStr,
										nSendStr,
										1);

					if(0 == status)
					{
					//	ShowMessage("�´�������ʱ��ɹ�!");
					}
					//������POS��������⣺��SFJPARAM
				}
				else
				{
					tmpitem->ImageIndex = 3;
				//	ShowMessage("�´�����ʧ�ܣ�����ϵרҵ��ʿ���POS��!");
				}
			}

			if(3 == para->tag)
			{
				unsigned char CMD = 0x32;
				WORD nSendStr = 126;
				WORD status;

				unsigned char SendStr[200] = "";
				unsigned char writeczmm[5] = "";

				TmpADOQ->Close();
				TmpADOQ->SQL->Clear();
				TmpADOQ->SQL->Add("select * from XTSET");
				TmpADOQ->Open();
				strcpy(writeczmm, TmpADOQ->FieldByName("DWMM")->AsAnsiString.c_str());
				TmpADOQ->Close();

				SendStr[0] = 0x01; //������
				SendStr[1] = 0x00; //��������

				writeczmm[0] = writeczmm[0]<<4;
				writeczmm[1] = writeczmm[1]<<4;
				writeczmm[1] = writeczmm[1]>>4;
				SendStr[2] = writeczmm[0] + writeczmm[1];  //��λ����
				writeczmm[2] = writeczmm[2]<<4;
				writeczmm[3] = writeczmm[4]<<4;
				writeczmm[3] = writeczmm[4]>>4;
				SendStr[3] = writeczmm[2] + writeczmm[3];   //��λ����

				SendStr[4] = UsingSecNUM;//0x00;    //����
				SendStr[5] = para->posnum;// 0x00;    //���Ų��ı�����ֵ������


				String Hmm = "0x" + PassWordEdit->Text.SubString(1, 2);
				String Lmm = "0x" + PassWordEdit->Text.SubString(3, 2);
				SendStr[6] = (unsigned char)StrToInt(Hmm);   //��������
				SendStr[7] = (unsigned char)StrToInt(Lmm);   //��������

				for (int i = 8; i <= 37; i++)
				{
					SendStr[i] = 0x00;        //����
				}

				SendStr[38] = CARDPasswordEdition;//0x01; 	//����汾

				SendStr[39] = CARDPassword[0];//0x00;     //MF�����룿����
				SendStr[40] = CARDPassword[1];//0x00;     //MF�����룿����
				SendStr[41] = CARDPassword[2];//0x00;     //MF�����룿����
				SendStr[42] = CARDPassword[3];//0x00;     //MF�����룿����
				SendStr[43] = CARDPassword[4];//0x00;     //MF�����룿����
				SendStr[44] = CARDPassword[5];//0x00;     //MF�����룿����

				int tmpmax = StrToInt(MaxEdit->Text)*100;      //�������
				SendStr[45] = (unsigned char)((int)(tmpmax/65536));
				SendStr[46] = (unsigned char)((int)((tmpmax%65536)/256));
				SendStr[47] = (unsigned char)(tmpmax%256);

				SendStr[48] = 0x00;    //�̶����ѽ��
				SendStr[49] = 0x00;    //�̶����ѽ��
				SendStr[50] = 0x00;    //�̶����ѽ��

				SendStr[51] = 0x00;    //��λ�̶����ѽ��
				SendStr[52] = 0x00;    //��λ�̶����ѽ��
				SendStr[53] = 0x00;    //��λ�̶����ѽ��

				TmpADOQ->Close();
				TmpADOQ->SQL->Clear();
				TmpADOQ->SQL->Add("select * from secnum");
				TmpADOQ->Open();
				if(!TmpADOQ->IsEmpty())
				{
					int Max1 = TmpADOQ->FieldByName("daymaxxf")->AsFloat*100;
					int Max2 = TmpADOQ->FieldByName("daymaxxf1")->AsFloat*100;
					int Max3 = TmpADOQ->FieldByName("daymaxxf2")->AsFloat*100;
					int Max4 = TmpADOQ->FieldByName("daymaxxf3")->AsFloat*100;
					int Max5 = TmpADOQ->FieldByName("daymaxxf4")->AsFloat*100;

					//ÿ���������begin
					SendStr[54] = (unsigned char)((int)(Max1/65536));
					SendStr[55] = (unsigned char)((int)((Max1%65536)/256));
					SendStr[56] = (unsigned char)(Max1%256);
					for (int i = 57; i <= 89; i++)
					{
						SendStr[i] = 0x00;
					}

					SendStr[90] = (unsigned char)((int)(Max2/65536));
					SendStr[91] = (unsigned char)((int)((Max2%65536)/256));
					SendStr[92] = (unsigned char)(Max2%256);

					SendStr[93] = (unsigned char)((int)(Max3/65536));
					SendStr[94] = (unsigned char)((int)((Max3%65536)/256));
					SendStr[95] = (unsigned char)(Max3%256);

					SendStr[96] = (unsigned char)((int)(Max4/65536));
					SendStr[97] = (unsigned char)((int)((Max4%65536)/256));
					SendStr[98] = (unsigned char)(Max4%256);

					SendStr[99] = (unsigned char)((int)(Max5/65536));
					SendStr[100] = (unsigned char)((int)((Max5%65536)/256));
					SendStr[101] = (unsigned char)(Max5%256);
					//ÿ���������end
                }
				TmpADOQ->Close();

				status = SerSendFunc((unsigned char)(para->comnum),
									 WORD(para->posnum),
									 CMD,
									 SendStr,
									 nSendStr,
									 1);
				if(0 == status)
				{
					//����ʱ��
					CMD = 0x31;
					String datestr = DateTimeToStr(Now());
					char* timepstr = datestr.t_str();

					SendStr[0] = (unsigned char)(((int)timepstr[2]-48)*16+(int)timepstr[3]-48);
					SendStr[1] = (unsigned char)(((int)timepstr[5]-48)*16+(int)timepstr[6]-48);
					SendStr[2] = (unsigned char)(((int)timepstr[8]-48)*16+(int)timepstr[9]-48);

					if(19 == datestr.Length())
					{
						SendStr[3] = (unsigned char)(((int)timepstr[11]-48)*16+(int)timepstr[12]-48);
						SendStr[4] = (unsigned char)(((int)timepstr[14]-48)*16+(int)timepstr[15]-48);
						SendStr[5] = (unsigned char)(((int)timepstr[17]-48)*16+(int)timepstr[18]-48);
					}
					else
					{
						SendStr[3] = (unsigned char)((int)timepstr[11]-48);
						SendStr[4] = (unsigned char)(((int)timepstr[13]-48)*16+(int)timepstr[14]-48);
						SendStr[5] = (unsigned char)(((int)timepstr[16]-48)*16+(int)timepstr[17]-48);
					}

					nSendStr = 8;

					status = SerSendFunc((unsigned char)(para->comnum),
										WORD(para->posnum),
										CMD,
										SendStr,
										nSendStr,
										1);

					if(0 == status)
					{
					//	ShowMessage("�´�������ʱ��ɹ�!");
					}
					//������POS��������⣺��SFJPARAM
				}
				else
				{
					tmpitem->ImageIndex = 3;
				//	ShowMessage("�´�����ʧ�ܣ�����ϵרҵ��ʿ���POS��!");
				}
			}
		}
	}
	else
	{
		ShowMessage("����ȷ��дPOS������!");
	}
}  */
//---------------------------------------------------------------------------

/*���õ�������
		//POS�������ߣ��޷�����
		if(2 == para->tag)
		{
			ShowMessage("��POS�������ߣ��޷�����!");
		}

		//POS�����ߣ���Ϣ�ڿ�
		if(1 == para->tag)
		{
			if((PosStyleComBox->ItemIndex != -1)&&(PosPlaceComBox->ItemIndex !=1)&&(MaxEdit->Text != "")&&(PassWordEdit->Text != ""))
			{
				unsigned char CMD = 0x32;
				WORD nSendStr = 126;
				WORD status;

				unsigned char SendStr[200] = "";
				unsigned char writeczmm[5] = "";

				TmpADOQ->Close();
				TmpADOQ->SQL->Clear();
				TmpADOQ->SQL->Add("select * from XTSET");
				TmpADOQ->Open();
				strcpy(writeczmm, TmpADOQ->FieldByName("DWMM")->AsAnsiString.c_str());
				TmpADOQ->Close();

				SendStr[0] = UsingSecNUM;//0x01; //������
				SendStr[1] = 0x00; //��������

				writeczmm[0] = writeczmm[0]<<4;
				writeczmm[1] = writeczmm[1]<<4;
				writeczmm[1] = writeczmm[1]>>4;
			//	SendStr[2] = writeczmm[0] + writeczmm[1];  //��λ����
				writeczmm[2] = writeczmm[2]<<4;
				writeczmm[3] = writeczmm[3]<<4;
				writeczmm[3] = writeczmm[3]>>4;
			//	SendStr[3] = writeczmm[2] + writeczmm[3];   //��λ����

				SendStr[2] = DWPassword[0];
				SendStr[3] = DWPassword[1];

				SendStr[4] = 0x00;    //����
				SendStr[5] = para->posnum;//0x00;    //���Ų��ı�����ֵ������


				String Hmm = "0x" + PassWordEdit->Text.SubString(1, 2);
				String Lmm = "0x" + PassWordEdit->Text.SubString(3, 2);
				SendStr[6] = (unsigned char)StrToInt(Hmm);   //��������
				SendStr[7] = (unsigned char)StrToInt(Lmm);   //��������

				for (int i = 8; i <= 37; i++)
				{
					SendStr[i] = 0x00;        //����
				}

				SendStr[38] = CARDPasswordEdition;//0x01; 	//����汾

				SendStr[39] = CARDPassword[0];//0x00;     //MF�����룿����
				SendStr[40] = CARDPassword[1];//0x00;     //MF�����룿����
				SendStr[41] = CARDPassword[2];//0x00;     //MF�����룿����
				SendStr[42] = CARDPassword[3];//0x00;     //MF�����룿����
				SendStr[43] = CARDPassword[4];//0x00;     //MF�����룿����
				SendStr[44] = CARDPassword[5];//0x00;     //MF�����룿����

				int tmpmax = StrToInt(MaxEdit->Text)*100;      //�������
				SendStr[45] = (unsigned char)((int)(tmpmax/65536));
				SendStr[46] = (unsigned char)((int)((tmpmax%65536)/256));
				SendStr[47] = (unsigned char)(tmpmax%256);

				SendStr[48] = 0x00;    //�̶����ѽ��
				SendStr[49] = 0x00;    //�̶����ѽ��
				SendStr[50] = 0x00;    //�̶����ѽ��

				SendStr[51] = 0x00;    //��λ�̶����ѽ��
				SendStr[52] = 0x00;    //��λ�̶����ѽ��
				SendStr[53] = 0x00;    //��λ�̶����ѽ��

				TmpADOQ->Close();
				TmpADOQ->SQL->Clear();
				TmpADOQ->SQL->Add("select * from secnum");
				TmpADOQ->Open();
				if(!TmpADOQ->IsEmpty())
				{
					int Max1 = TmpADOQ->FieldByName("daymaxxf")->AsFloat*100;
					int Max2 = TmpADOQ->FieldByName("daymaxxf1")->AsFloat*100;
					int Max3 = TmpADOQ->FieldByName("daymaxxf2")->AsFloat*100;
					int Max4 = TmpADOQ->FieldByName("daymaxxf3")->AsFloat*100;
					int Max5 = TmpADOQ->FieldByName("daymaxxf4")->AsFloat*100;

					//ÿ���������begin
					SendStr[54] = (unsigned char)((int)(Max1/65536));
					SendStr[55] = (unsigned char)((int)((Max1%65536)/256));
					SendStr[56] = (unsigned char)(Max1%256);
					for (int i = 57; i <= 89; i++)
					{
						SendStr[i] = 0x00;
					}

					SendStr[90] = (unsigned char)((int)(Max2/65536));
					SendStr[91] = (unsigned char)((int)((Max2%65536)/256));
					SendStr[92] = (unsigned char)(Max2%256);

					SendStr[93] = (unsigned char)((int)(Max3/65536));
					SendStr[94] = (unsigned char)((int)((Max3%65536)/256));
					SendStr[95] = (unsigned char)(Max3%256);

					SendStr[96] = (unsigned char)((int)(Max4/65536));
					SendStr[97] = (unsigned char)((int)((Max4%65536)/256));
					SendStr[98] = (unsigned char)(Max4%256);

					SendStr[99] = (unsigned char)((int)(Max5/65536));
					SendStr[100] = (unsigned char)((int)((Max5%65536)/256));
					SendStr[101] = (unsigned char)(Max5%256);
					//ÿ���������end
                }
				TmpADOQ->Close();

				status = SerSendFunc((unsigned char)(para->comnum),
									 WORD(para->posnum),
									 CMD,
									 SendStr,
									 nSendStr,
									 1);
				if(0 == status)
				{
					//����ʱ��
					CMD = 0x31;
					String datestr = DateTimeToStr(Now());
					char* timepstr = datestr.t_str();

					SendStr[0] = (unsigned char)(((int)timepstr[2]-48)*16+(int)timepstr[3]-48);
					SendStr[1] = (unsigned char)(((int)timepstr[5]-48)*16+(int)timepstr[6]-48);
					SendStr[2] = (unsigned char)(((int)timepstr[8]-48)*16+(int)timepstr[9]-48);

					if(19 == datestr.Length())
					{
						SendStr[3] = (unsigned char)(((int)timepstr[11]-48)*16+(int)timepstr[12]-48);
						SendStr[4] = (unsigned char)(((int)timepstr[14]-48)*16+(int)timepstr[15]-48);
						SendStr[5] = (unsigned char)(((int)timepstr[17]-48)*16+(int)timepstr[18]-48);
					}
					else
					{
						SendStr[3] = (unsigned char)((int)timepstr[11]-48);
						SendStr[4] = (unsigned char)(((int)timepstr[13]-48)*16+(int)timepstr[14]-48);
						SendStr[5] = (unsigned char)(((int)timepstr[16]-48)*16+(int)timepstr[17]-48);
					}

					nSendStr = 8;

					status = SerSendFunc((unsigned char)(para->comnum),
										WORD(para->posnum),
										CMD,
										SendStr,
										nSendStr,
										1);
					if(0 == status)
					{
						ShowMessage("�´�������ʱ��ɹ�!");
					}

					//������POS��������⣺��SFJPARAM
				}
				else
				{
					tmpitem->ImageIndex = 3;
					ShowMessage("�´�����ʧ�ܣ�����ϵרҵ��ʿ���POS��!");
				}
			}
			else
				MessageBox(this->Handle, "����дPOS���������Ϣ!", "Info Error", MB_OK|MB_ICONWARNING);
		}

		//POS�����ߣ���Ϣ���ڿ⣬Ϊ�¼��벢��⵽��POS��
		if(3 == para->tag)
		{
			if((PosStyleComBox->ItemIndex != -1)&&(PosPlaceComBox->ItemIndex !=1)&&(MaxEdit->Text != "")&&(PassWordEdit->Text != ""))
			{
				unsigned char CMD = 0x32;
				WORD nSendStr = 126;
				WORD status;

				unsigned char SendStr[200] = "";
				unsigned char writeczmm[5] = "";

				TmpADOQ->Close();
				TmpADOQ->SQL->Clear();
				TmpADOQ->SQL->Add("select * from XTSET");
				TmpADOQ->Open();
				strcpy(writeczmm, TmpADOQ->FieldByName("DWMM")->AsAnsiString.c_str());
				TmpADOQ->Close();

				SendStr[0] = UsingSecNUM;//0x01; //������
				SendStr[1] = 0x00; //��������

				writeczmm[0] = writeczmm[0]<<4;
				writeczmm[1] = writeczmm[1]<<4;
				writeczmm[1] = writeczmm[1]>>4;
				SendStr[2] = writeczmm[0] + writeczmm[1];  //��λ����
				writeczmm[2] = writeczmm[2]<<4;
				writeczmm[3] = writeczmm[4]<<4;
				writeczmm[3] = writeczmm[4]>>4;
				SendStr[3] = writeczmm[2] + writeczmm[3];   //��λ����

				SendStr[4] = 0x00;    //����
				SendStr[5] = para->posnum;//0x00;    //���Ų��ı�����ֵ������


				String Hmm = "0x" + PassWordEdit->Text.SubString(1, 2);
				String Lmm = "0x" + PassWordEdit->Text.SubString(3, 2);
				SendStr[6] = (unsigned char)StrToInt(Hmm);   //��������
				SendStr[7] = (unsigned char)StrToInt(Lmm);   //��������

				for (int i = 8; i <= 37; i++)
				{
					SendStr[i] = 0x00;        //����
				}

				SendStr[38] = CARDPasswordEdition;//0x01; 	//����汾

				SendStr[39] = CARDPassword[0];//0x00;     //MF�����룿����
				SendStr[40] = CARDPassword[1];//0x00;     //MF�����룿����
				SendStr[41] = CARDPassword[2];//0x00;     //MF�����룿����
				SendStr[42] = CARDPassword[3];//0x00;     //MF�����룿����
				SendStr[43] = CARDPassword[4];//0x00;     //MF�����룿����
				SendStr[44] = CARDPassword[5];//0x00;     //MF�����룿����

				int tmpmax = StrToInt(MaxEdit->Text)*100;      //�������
				SendStr[45] = (unsigned char)((int)(tmpmax/65536));
				SendStr[46] = (unsigned char)((int)((tmpmax%65536)/256));
				SendStr[47] = (unsigned char)(tmpmax%256);

				SendStr[48] = 0x00;    //�̶����ѽ��
				SendStr[49] = 0x00;    //�̶����ѽ��
				SendStr[50] = 0x00;    //�̶����ѽ��

				SendStr[51] = 0x00;    //��λ�̶����ѽ��
				SendStr[52] = 0x00;    //��λ�̶����ѽ��
				SendStr[53] = 0x00;    //��λ�̶����ѽ��

				TmpADOQ->Close();
				TmpADOQ->SQL->Clear();
				TmpADOQ->SQL->Add("select * from secnum");
				TmpADOQ->Open();
				if(!TmpADOQ->IsEmpty())
				{
					int Max1 = TmpADOQ->FieldByName("daymaxxf")->AsFloat*100;
					int Max2 = TmpADOQ->FieldByName("daymaxxf1")->AsFloat*100;
					int Max3 = TmpADOQ->FieldByName("daymaxxf2")->AsFloat*100;
					int Max4 = TmpADOQ->FieldByName("daymaxxf3")->AsFloat*100;
					int Max5 = TmpADOQ->FieldByName("daymaxxf4")->AsFloat*100;

					//ÿ���������begin
					SendStr[54] = (unsigned char)((int)(Max1/65536));
					SendStr[55] = (unsigned char)((int)((Max1%65536)/256));
					SendStr[56] = (unsigned char)(Max1%256);
					for (int i = 57; i <= 89; i++)
					{
						SendStr[i] = 0x00;
					}

					SendStr[90] = (unsigned char)((int)(Max2/65536));
					SendStr[91] = (unsigned char)((int)((Max2%65536)/256));
					SendStr[92] = (unsigned char)(Max2%256);

					SendStr[93] = (unsigned char)((int)(Max3/65536));
					SendStr[94] = (unsigned char)((int)((Max3%65536)/256));
					SendStr[95] = (unsigned char)(Max3%256);

					SendStr[96] = (unsigned char)((int)(Max4/65536));
					SendStr[97] = (unsigned char)((int)((Max4%65536)/256));
					SendStr[98] = (unsigned char)(Max4%256);

					SendStr[99] = (unsigned char)((int)(Max5/65536));
					SendStr[100] = (unsigned char)((int)((Max5%65536)/256));
					SendStr[101] = (unsigned char)(Max5%256);
					//ÿ���������end
                }
				TmpADOQ->Close();

				status = SerSendFunc((unsigned char)(para->comnum),
									 WORD(para->posnum),
									 CMD,
									 SendStr,
									 nSendStr,
									 1);
				if(0 == status)
				{
					//����ʱ��
					CMD = 0x31;
					String datestr = DateTimeToStr(Now());
					char* timepstr = datestr.t_str();

					SendStr[0] = (unsigned char)(((int)timepstr[2]-48)*16+(int)timepstr[3]-48);
					SendStr[1] = (unsigned char)(((int)timepstr[5]-48)*16+(int)timepstr[6]-48);
					SendStr[2] = (unsigned char)(((int)timepstr[8]-48)*16+(int)timepstr[9]-48);

					if(19 == datestr.Length())
					{
						SendStr[3] = (unsigned char)(((int)timepstr[11]-48)*16+(int)timepstr[12]-48);
						SendStr[4] = (unsigned char)(((int)timepstr[14]-48)*16+(int)timepstr[15]-48);
						SendStr[5] = (unsigned char)(((int)timepstr[17]-48)*16+(int)timepstr[18]-48);
					}
					else
					{
						SendStr[3] = (unsigned char)((int)timepstr[11]-48);
						SendStr[4] = (unsigned char)(((int)timepstr[13]-48)*16+(int)timepstr[14]-48);
						SendStr[5] = (unsigned char)(((int)timepstr[16]-48)*16+(int)timepstr[17]-48);
					}

					nSendStr = 8;

					status = SerSendFunc((unsigned char)(para->comnum),
										WORD(para->posnum),
										CMD,
										SendStr,
										nSendStr,
										1);
					if(0 == status)
					{
						ShowMessage("�´�������ʱ��ɹ�!");
					}
					//������POS��������⣺��SFJPARAM
				}
				else
				{
					tmpitem->ImageIndex = 3;
					ShowMessage("�´�����ʧ�ܣ�����ϵרҵ��ʿ���POS��!");
				}
			}
			else
				MessageBox(this->Handle, "����дPOS���������Ϣ!", "Info Error", MB_OK|MB_ICONWARNING);
		}
*/




void __fastcall TPosConfigFRM::PosStyleComBoxKeyPress(TObject *Sender, wchar_t &Key)
{
	Key = 0;
}
//---------------------------------------------------------------------------


void __fastcall TPosConfigFRM::cxButton1Click(TObject *Sender)
{
/*	String test = "05:03:01";
    String out1 = test.SubString(1, 2);
    ShowMessage(out1);
    String out2 = test.SubString(4, 2);
    ShowMessage(out2);*/
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::CheckBox3Click(TObject *Sender)
{
	if(CheckBox3->Checked)
		MaxCSEdit->Enabled = true;
	else
		MaxCSEdit->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TPosConfigFRM::SetAllBaseBTNClick(TObject *Sender)
{
//��������򣬽����ݿ�������POS������Ϊ��ͬ������ֵ������ͨ�õ�7������
	if(ComNumEdit->Text.IsEmpty())
	{
		ShowMessage("������дͨѶ�˿�!");
		return;
	}
	if(MaxEdit->Text.IsEmpty())
	{
		ShowMessage("������дÿ���������!");
		return;
	}
	if(DMaxEdit->Text.IsEmpty())
	{
		ShowMessage("������дÿ���������!");
		return;
	}
	if(PassWordEdit->Text.IsEmpty())
	{
		ShowMessage("������дPOS����!");
		return;
	}
	if(CheckBox3->Checked)
	{
		if(MaxCSEdit->Text.IsEmpty())
		{
			ShowMessage("������дÿ��/��������Ѵ���!");
			return;
        }
    }
	//��ʼ�����߳�
	int comn = StrToInt(ComNumEdit->Text);
	int max = StrToInt(MaxEdit->Text);
	int dmax = StrToInt(DMaxEdit->Text);
	String pw = PassWordEdit->Text;
	bool dinc = CheckBox1->Checked;
	bool qkbt = CheckBox2->Checked;
	bool mmax = CheckBox3->Checked;
	int mmaxcs;
	if(mmax)
		mmaxcs = StrToInt(MaxCSEdit->Text);
	else
		mmaxcs = 0;

	if(!SetAllPosBaseThread)
	{
		SetAllPosBaseThread = new TSetAllPOSBaseThread(true,
													   comn,
													   max,
													   dmax,
													   pw,
													   dinc,
													   qkbt,
													   mmax,
													   mmaxcs,
													   TmpADOQ,
													   SetAllPosBTN,
													   SetSingleBTN,
													   DelOneBTN,
													   AddOneBTN,
													   AddDBTN,
													   ScanPosBTN,
													   PauseBTN,
													   cxButton4,
													   SelectAllBTN,
													   CancelSelAllBTN,
													   SetAllBaseBTN,
													   SCanProBar,
													   POSListView);
		if(SetAllPosBaseThread)
			SetAllPosBaseThread->Resume();
	}
	else
	{
		if(SetAllPosBaseThread->Finished)
		{
			SetAllPosBaseThread = new TSetAllPOSBaseThread(true,
														   comn,
														   max,
														   dmax,
														   pw,
														   dinc,
														   qkbt,
														   mmax,
														   mmaxcs,
														   TmpADOQ,
														   SetAllPosBTN,
														   SetSingleBTN,
														   DelOneBTN,
														   AddOneBTN,
														   AddDBTN,
														   ScanPosBTN,
														   PauseBTN,
														   cxButton4,
														   SelectAllBTN,
														   CancelSelAllBTN,
														   SetAllBaseBTN,
														   SCanProBar,
														   POSListView);
			if(SetAllPosBaseThread)
				SetAllPosBaseThread->Resume();
        }
	}
}
//---------------------------------------------------------------------------

