//---------------------------------------------------------------------------

#ifndef YKHFFRMH
#define YKHFFRMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TYKHFForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox4;
	TButton *Button2;
	TADOQuery *ADOWithDrawQuery;
	TGroupBox *GroupBox2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit3;
	TEdit *Edit4;
	TButton *Button3;
	TButton *Button4;
	TGroupBox *GroupBox3;
	TButton *Button1;
	TADOQuery *ADOQuery1;
	TADOQuery *LaunchNewCardADOQ;
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Button5;
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TYKHFForm(TComponent* Owner);
    int FKS;
    int HFS;
};
//---------------------------------------------------------------------------
extern PACKAGE TYKHFForm *YKHFForm;
//---------------------------------------------------------------------------
#endif
