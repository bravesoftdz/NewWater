//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ChangePasswordFRM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxButtons"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGraphics"
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
TChangePasswordFrom *ChangePasswordFrom;

//#include "SDIMAIN.h"
#include <string.h>
#include "GlobalParameter.h"
//---------------------------------------------------------------------------
__fastcall TChangePasswordFrom::TChangePasswordFrom(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TChangePasswordFrom::cxButton1Click(TObject *Sender)
{
	String Oldpwstr = TEOldPassword->Text;
	String Newpwstr1 = TENewPassword1->Text;
	String Newpwstr2 = TENewPassword2->Text;

	if("" != Oldpwstr)
	{
		if(("" != Newpwstr1)&&("" != Newpwstr2))
		{
			if(Newpwstr1 == Newpwstr2)
			{
				ADOQuery1->Close();
				ADOQuery1->SQL->Clear();
				ADOQuery1->SQL->Add("Select * from XTSET");
				ADOQuery1->Open();
				String tmpstr = ADOQuery1->FieldByName("DWMM")->AsString;
				//ShowMessage(tmpstr);
				if(tmpstr == Oldpwstr)
				{
					if(Newpwstr1 == Newpwstr2)
					{
						if(4 == Newpwstr1.Length())
						{
							ADOQuery1->Edit();
							ADOQuery1->FieldByName("DWMM")->AsString = Newpwstr1;
							ADOQuery1->Post();

							String tmpDWPassword = ADOQuery1->FieldByName("DWMM")->AsAnsiString.Trim();
							for(int t=0; t < 2; t++)
							{
								int tmpint = StrToInt("0x"+tmpDWPassword.SubString(t*2+1, 2));
								IntToUChar(tmpint, &DWPassword[t]);
							}

							MessageBox(this->Handle, "�����޸ĳɹ�!", "�ɹ�", MB_OK|MB_ICONEXCLAMATION);
							this->Close();
						}
						else
							MessageBox(this->Handle, "�������Ϊ4λ!", "����", MB_OK|MB_ICONERROR);
					}
					else
						MessageBox(this->Handle, "������������ͬ��������!", "����", MB_OK|MB_ICONERROR);
				}
				else
				{
					MessageBox(this->Handle, "���������!", "����", MB_OK|MB_ICONERROR);
				}
				ADOQuery1->Close();
			}
			else
			{
			//	ShowMessage("������������벻һ�£�");
				MessageBox(this->Handle, "������������벻һ�£�", "����", MB_OK|MB_ICONERROR);
            }
        }
	}
	else
		MessageBox(this->Handle, "�����벻Ϊ�գ�", "����", MB_OK|MB_ICONERROR);
}
//---------------------------------------------------------------------------

void __fastcall TChangePasswordFrom::cxButton2Click(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TChangePasswordFrom::TEOldPasswordKeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮������֣�");
	}
}
//---------------------------------------------------------------------------

void __fastcall TChangePasswordFrom::TENewPassword1KeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮������֣�");
	}
}
//---------------------------------------------------------------------------

void __fastcall TChangePasswordFrom::TENewPassword2KeyPress(TObject *Sender, wchar_t &Key)
{
	if((Key<'0'||Key>'9') && Key!='\b')
	{
		Key=0;
		ShowMessage("������0��9֮������֣�");
	}
}
//---------------------------------------------------------------------------


