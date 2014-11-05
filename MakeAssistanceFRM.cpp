//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MakeAssistanceFRM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxCalendar"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxDropDownEdit"
#pragma link "cxEdit"
#pragma link "cxGraphics"
#pragma link "cxGroupBox"
#pragma link "cxLabel"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxMaskEdit"
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
#pragma link "cxMemo"
#pragma link "cxProgressBar"
#pragma link "cxRadioGroup"
#pragma link "cxCheckGroup"
#pragma resource "*.dfm"
TMakeAssistancedFRM *MakeAssistancedFRM;
//---------------------------------------------------------------------------
__fastcall TMakeAssistancedFRM::TMakeAssistancedFRM(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMakeAssistancedFRM::BTJETextEditKeyPress(TObject *Sender, wchar_t &Key)

{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮�������!");
	}
}
//---------------------------------------------------------------------------

void __fastcall TMakeAssistancedFRM::BTCSUTextEditKeyPress(TObject *Sender, wchar_t &Key)

{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮�������!");
	}
}
//---------------------------------------------------------------------------

void __fastcall TMakeAssistancedFRM::BTJEGTextEditKeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮�������!");
	}
}
//---------------------------------------------------------------------------

void __fastcall TMakeAssistancedFRM::CSBTBTNClick(TObject *Sender)
{
	if(!BeginDateEdit->Text.IsEmpty()&&!EndDateEdit->Text.IsEmpty()
    	&&!BTJETextEdit->Text.IsEmpty()&&!BTCSUTextEdit->Text.IsEmpty())
    {
        SYSTEMTIME beginsystime;
        DateTimeToSystemTime(BeginDateEdit->Date, beginsystime);
        SYSTEMTIME endsystime;
        DateTimeToSystemTime(EndDateEdit->Date, endsystime);

        if(beginsystime.wYear>endsystime.wYear)
        {
            ShowMessage("ʱ����д����!");
            return;
        }

        if(beginsystime.wYear == endsystime.wYear)
        {
            if(endsystime.wMonth<beginsystime.wMonth)
            {
                ShowMessage("ʱ����д����!");
                return;
            }
            if(endsystime.wMonth==beginsystime.wMonth)
            {
                if(endsystime.wDay<beginsystime.wDay)
                {
                    ShowMessage("ʱ����д����!");
                    return;
                }
            }
        }

        String begindatestr = DateToStr(BeginDateEdit->Date);
        begindatestr += " 00:00:00";
        String enddatestr = DateToStr(EndDateEdit->Date);
        enddatestr += " 23:59:59";

        CSBTADOQ->Close();
		CSBTADOQ->SQL->Add("select count(*) as allcards from CARD where ZT='����'");
		CSBTADOQ->Open();
        if(0 == CSBTADOQ->FieldByName("allcards")->AsInteger)
        {
			ShowMessage("ϵͳ��û�п�Ƭ��¼�޷����ɲ���!");
			CSBTADOQ->Close();
			return;
        }
        else if(5040 < CSBTADOQ->FieldByName("allcards")->AsInteger)
        {
            ShowMessage("����ϵͳ�����ÿ�Ƭ��������5040��,���Բ�����������!");
            CSBTADOQ->Close();
            return;
        }
        else
        {
        	//���ɲ������벹���⣺BTTemp1
            if(!CreateCSBTThread||CreateCSBTThread->Finished)
            {
                CreateCSBTThread = new TCreateCSBTThread(true,
                										CSBTBTN,
                                                        JBJEBTN,
                                                        JBBTBTN,
                                                        BTExitBTN,
                                                        CSBTProgressBar,
                                                        CSBTADOQ,
                                                        CSBTinBaseADOQ,
                                                        begindatestr,
                                                        enddatestr,
                                                        StrToInt(BTJETextEdit->Text),
                                                        StrToInt(BTCSUTextEdit->Text));
                if(CreateCSBTThread)
                {
                    CreateCSBTThread->Resume();
                }

            }
        }
        CSBTADOQ->Close();
    }
    else
    {
        ShowMessage("����ȷ��д����!");
    }
}
//---------------------------------------------------------------------------

void __fastcall TMakeAssistancedFRM::JBBTBTNClick(TObject *Sender)
{
	if(0 == BTGComboBox->Properties->Items->Count)
    {
        ShowMessage("ϵͳ���޿�Ƭ�����˵�ְ����Ϣ���޷���ְλ���в�������");
        return;
    }
    else
    {
    	bool jbtag = true;
    	for(int i = 0; i < BTGComboBox->Properties->Items->Count; i++)
        {
        	if(BTGArray[i] < 0)
            {
                jbtag = false;
                break;
            }
        }

        if(!jbtag)
        {
            ShowMessage("�������ÿ��ְ����в���������ò������ɲ���!");
            return;
        }

        if(jbtag)
        {
        	bool Monthtag = false;
            int months = 0;

            for(int i = 0; i < 12; i++)
            {
                if(cbsChecked == JBRQCheckGroup->States[i])
                {
                    months++;
                    Monthtag = true;
                }
            }

            int monthindex = 0;
            if(Monthtag)
            {
                BTGmonthArray = new char*[months];
                for(int i = 0; i < 12; i++)
                {
                    if(cbsChecked == JBRQCheckGroup->States[i])
                    {
                        switch (i)
                        {
                            case 0: BTGmonthArray[monthindex] = "January"; break;
                            case 1: BTGmonthArray[monthindex] = "February"; break;
                            case 2: BTGmonthArray[monthindex] = "March"; break;
                            case 3: BTGmonthArray[monthindex] = "April"; break;
                            case 4: BTGmonthArray[monthindex] = "May"; break;
                            case 5: BTGmonthArray[monthindex] = "June"; break;
                            case 6: BTGmonthArray[monthindex] = "July"; break;
                            case 7: BTGmonthArray[monthindex] = "August"; break;
                            case 8: BTGmonthArray[monthindex] = "September"; break;
                            case 9: BTGmonthArray[monthindex] = "October"; break;
                            case 10: BTGmonthArray[monthindex] = "November"; break;
                            case 11: BTGmonthArray[monthindex] = "December"; break;
                        }
                        monthindex++;
                    }
                }
                BTGmonthArraylen = monthindex;
            }
            else
            {
                ShowMessage("��ѡ��Ҫ���в������·�!");
                return;
            }

            //���ɰ�����Ĳ���
            JBBTADOQ->Close();
            JBBTADOQ->SQL->Clear();
			JBBTADOQ->SQL->Add("select count(*) as allcards from CARD where ZT='����'");
            JBBTADOQ->Open();
            if(0 == JBBTADOQ->FieldByName("allcards")->AsInteger)
            {
                ShowMessage("ϵͳ��û�п�Ƭ��¼�޷����ɲ���!");
                JBBTADOQ->Close();
                return;
            }
            else if(5040 < JBBTADOQ->FieldByName("allcards")->AsInteger)
            {
                ShowMessage("����ϵͳ�����ÿ�Ƭ��������5040��,���Բ�����������!");
                JBBTADOQ->Close();
                return;
            }
            else
            {
                if(!CreateJBBTThread||CreateJBBTThread->Finished)
                {
                    CreateJBBTThread = new TCreateJBBTThread(true,
                                                            CSBTBTN,
                                                            JBJEBTN,
                                                            JBBTBTN,
                                                            BTExitBTN,
                                                            BTGComboBox,
                                                            JBRQCheckGroup,
                                                            JBBTProgressBar,
                                                            JBBTADOQ,
                                                            JBBTinBaseADOQ);
                    if(CreateJBBTThread)
                    {
                        CreateJBBTThread->Resume();
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMakeAssistancedFRM::JBJEBTNClick(TObject *Sender)
{
	if(BTJEGTextEdit->Text.Length() > 0)
	{
		if((BTGComboBox->ItemIndex!=-1)&&(StrToInt(BTJEGTextEdit->Text)>=0))
		{
			BTGArray[BTGComboBox->ItemIndex] = StrToInt(BTJEGTextEdit->Text);
            String outstr = "ְ��\"";
            outstr += BTGComboBox->Text;
            outstr += "\"��Ӧ�Ĳ���Ϊ:";
            outstr += BTJEGTextEdit->Text;
            outstr += "Ԫ";
            ShowMessage(outstr);
		}
		else
		{
			ShowMessage("����ȷѡ��ְ����ȷ��д�������!");
			return;
		}
	}
	else
	{
		ShowMessage("����ȷ��д�������!");
    }
}
//---------------------------------------------------------------------------

void __fastcall TMakeAssistancedFRM::FormShow(TObject *Sender)
{
	CreateBTtag = true;
    CSBTProgressBar->Position = 0;
    JBBTProgressBar->Position = 0;
    BeginDateEdit->Text = "";
    EndDateEdit->Text = "";
    BTJETextEdit->Text = "";
    BTCSUTextEdit->Text = "";
    BTGComboBox->ItemIndex = -1;
    BTJEGTextEdit->Text = "";

    for (int i = 0; i < 12; i++)
    {
    	JBRQCheckGroup->States[i] = cbsUnchecked;
    }

	BTZWADOQ->Close();
    BTZWADOQ->SQL->Clear();
    BTZWADOQ->SQL->Add("select * from SFZW");
    BTZWADOQ->Open();
    BTGComboBox->Properties->Items->Clear();
    BTZWADOQ->First();
    while(!BTZWADOQ->Eof)
    {
    	BTGComboBox->Properties->Items->Add(BTZWADOQ->FieldByName("ZW")->AsAnsiString.Trim());
        BTZWADOQ->Next();
    }
    BTGComboBox->ItemIndex = -1;
    BTZWADOQ->Close();

    if(BTGComboBox->Properties->Items->Count>0)
    {
        BTGArray = new int[BTGComboBox->Properties->Items->Count];
        BTGArraylen = BTGComboBox->Properties->Items->Count;

        JBNameArray = new char*[BTGComboBox->Properties->Items->Count];
        JBNameArraylen = BTGComboBox->Properties->Items->Count;

    	for(int i = 0; i < BTGComboBox->Properties->Items->Count; i++)
        {
        	JBNameArray[i] = new char[strlen(BTGComboBox->Properties->Items->Strings[i].t_str())];
            strcpy(JBNameArray[i], BTGComboBox->Properties->Items->Strings[i].t_str());
//			ShowMessage(BTGComboBox->Properties->Items->Strings[i]);
        	BTGArray[i] = -1;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TMakeAssistancedFRM::BTExitBTNClick(TObject *Sender)
{
	CreateBTtag = false;
    if(BTGArray)
    {
    	delete BTGArray;
        BTGArraylen = 0;
    }
    if(BTGmonthArray)
    {
        delete BTGmonthArray;
        BTGmonthArraylen = 0;
    }
    if(JBNameArray)
    {
        delete JBNameArray;
        JBNameArraylen = 0;
    }

	this->Close();
}
//---------------------------------------------------------------------------

