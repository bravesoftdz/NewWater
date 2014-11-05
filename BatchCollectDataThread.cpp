//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BatchCollectDataThread.h"
#include "SDIMAIN.h"
#pragma package(smart_init)
#include "BatchCollectDataFRM.h"
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TBatchCollectThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TBatchCollectDataThread::TBatchCollectDataThread(bool CreateSuspended,
															bool* collecttag,
															TTreeView* OnLinePosTreeList,
															TcxListView* DataListView,
															int* PosNum,
                                                            TcxProgressBar* CProgressBar,
															TADOQuery* updateQuery,
															TPanel* InfoPanel,
															TcxButton* StoreBtn,
															TcxButton* EBTN,
															TcxButton* SBTN) : TThread(CreateSuspended)
{
	validcollecttag = collecttag;
	ValidDisplayListView = DataListView;
	ValidPosTreeList = OnLinePosTreeList;
	ONLinePosNum = PosNum;
	UpdateDataBaseQuery = updateQuery;
	ValidInfoPanel = InfoPanel;
	ValidStoreBtn = StoreBtn;
	ValidEBTN = EBTN;
	ValidSBTN = SBTN;
    ValidCProgressBar = CProgressBar;
}
//---------------------------------------------------------------------------

void __fastcall TBatchCollectDataThread::Execute()
{
	//---- Place thread code here ----
	ValidSBTN->Enabled = false;
	if(SerReceiveFunc&&SendAckFunc)
	{
/*		String filepathstr = GlobalPath+"\\StroeBatchDataFile.dat";
		hStoreToFile = CreateFile(filepathstr.t_str(),
								  GENERIC_READ | GENERIC_WRITE,
								  0,
								  NULL,
								  CREATE_ALWAYS,
								  FILE_ATTRIBUTE_NORMAL,
								  NULL);
		if(hStoreToFile)
		{      */
			errortag = false;
			*validcollecttag = true;
			ValidEBTN->Enabled = true;
			ModeOFCollect = 2;
			String CollectTime = "*CollectTime* ";
			CollectTime += Date();
			CollectTime += " ";
			CollectTime += Time();

			BatchDataSaveToFileStream<<endl<<CollectTime.t_str()<<endl;
			nodecount = ValidPosTreeList->Items->Count;
			currentcount = 0;

			ValidCProgressBar->Position = 0;
			TTreeNode* tmpnode = ValidPosTreeList->Items->GetFirstNode();
			while(tmpnode)
			{
            	errortag = false;
				poscollectedrecordcount = 0;
				if(!Terminated)
				{
					tmpnode->Data;
					POSPARA* tmppospara = (POSPARA*)(tmpnode->Data);
					if(4 == tmppospara->tag)
					{
						WORD ReceiveStatus = -1;
						WORD SynchroStatus = -1;
						char temp[10] = "";
						unsigned char como = (unsigned char)(tmppospara->comnum);
						PosNumber = tmppospara->posnum;
						WORD PosNO = (WORD)(tmppospara->posnum);
						unsigned char ReceiveCMD = 0x23;
						unsigned char SynchroCMD = 0x54;
						ZeroMemory(receivebuf, 2048);
						int receivelen = 2048;
						unsigned char* dir = "E:\\RAD\\2010-9-26\\Recieve";
						int dirlen = strlen(dir);

						UpdateDataBaseQuery->Close();
						UpdateDataBaseQuery->SQL->Clear();
						String tmpsql = "select * from SFJPARAM where JH=";
						tmpsql += tmppospara->posnum;
				   //		tmpsql += "'";
						UpdateDataBaseQuery->SQL->Add(tmpsql);
						UpdateDataBaseQuery->Open();
						Place = UpdateDataBaseQuery->FieldByName("STNAME")->AsAnsiString.Trim();
						UpdateDataBaseQuery->Close();

						int recordinpos = 0;
						WORD posstatus = -1;
						WORD poscomo = como;
						unsigned char statusCMD = 0x43;
						unsigned char statusbuf[16];
						ZeroMemory(statusbuf,16);
						int statuslen = 16;
						posstatus = SerReceiveFunc(poscomo, PosNO, statusCMD, statusbuf, statuslen, 1, dir, dirlen);
						if(0 == posstatus)
						{
							int lowptr = 256*(int)statusbuf[0] + (int)statusbuf[1];
							int highptr = 256*(int)statusbuf[2] + (int)statusbuf[3];
							if(highptr >= lowptr)
							{
								recordinpos = highptr - lowptr;
							}
							else
							{
								recordinpos = highptr + 6576 - lowptr;
							}
							posallrecordcount = recordinpos;
						}
						else
						{
							tmpnode->Text = "POS���쳣";
							tmpnode = tmpnode->GetNext();
							currentcount++;
							continue;
						}

						tmpcaptionstr = "���ڲɼ�";
						tmpcaptionstr += tmppospara->posnum;
						tmpcaptionstr += "�Ż���λ�ڣ�";
						tmpcaptionstr += Place;
						tmpcaptionstr += "����POS���������Ѽ�¼";
						tmpcaptionstr += recordinpos;
						tmpcaptionstr += "����";
						ValidInfoPanel->Caption = tmpcaptionstr;
						bool continued = true;
						DisplayCollectingFunc();
						while(continued)
						{
							if(!Terminated)
							{
								ReceiveStatus = SerReceiveFunc(como, PosNO, ReceiveCMD, receivebuf, receivelen, 1, dir, dirlen);
								if(0 == ReceiveStatus)
								{
									SynchroStatus = SendAckFunc(como, SynchroCMD);
									if(0 == SynchroStatus)
									{
									//	for(int i = 0; i < 2048; i++)
									//		BatchDataSaveToFileStream<<receivebuf[i];
										if((0x00 == receivebuf[10])&&(0x00 == receivebuf[11]))
											continued = false;
										if(0x00 != receivebuf[8])
										{
											Synchronize(AnalyzeDataFunc);
										}
										CollectOverStautsStr = "������������ݲɼ�!";
									}
								//	else
								//	{
								//		MessageBox(SDIAppForm->Handle, "Sysc error", "error", MB_OK|MB_ICONERROR);
								//	}
								}
								else
								{
									continued = false;
									CollectOverStautsStr = "POS��ͨ���쳣���ɼ����ݲ�����!";
									errortag = true;
								}
								Sleep(100);
							}
							else
							{
								continued = false;
								*validcollecttag = false;
								ModeOFCollect = 0;
								CloseHandle(hStoreToFile);
						  //		ValidStoreBtn->Enabled = true;
								ValidEBTN->Enabled = true;
						  //		if(BatchDataSaveToFileStream)
						  //			BatchDataSaveToFileStream.close();
								BatchCollectFRM->Close();
								ValidSBTN->Enabled = true;
								return;
							}
						}
						DisplayEndCollectFunc();
					}
				}
				else
				{
					*validcollecttag = false;
					ModeOFCollect = 0;
			   //		CloseHandle(hStoreToFile);
			   //		ValidStoreBtn->Enabled = true;
					ValidEBTN->Enabled = true;
			   //		if(BatchDataSaveToFileStream)
			   //			BatchDataSaveToFileStream.close();
					BatchCollectFRM->Close();
					ValidSBTN->Enabled = true;
					return;
				}
				tmpnode = tmpnode->GetNext();
				currentcount++;
				ValidCProgressBar->Position = currentcount*100/nodecount;
			}
			*validcollecttag = false;
	   //		CloseHandle(hStoreToFile);
	   //		ValidStoreBtn->Enabled = true;
			ValidEBTN->Enabled = true;
	   //		if(BatchDataSaveToFileStream)
	   //			BatchDataSaveToFileStream.close();
	   		ValidCProgressBar->Position = 100;
			if(!errortag)
			{
				ValidInfoPanel->Caption = "���ݲɼ����!";
				MessageBox(SDIAppForm->Handle, "���ݲɼ����!", "�ɼ����", MB_OK);
			}
			else
			{
				ValidInfoPanel->Caption = "���ݲɼ������г���ͨ���쳣���������ݲɼ����ɹ�������ͨ�����²ɼ��޲�!";
				MessageBox(SDIAppForm->Handle, "���ݲɼ������г���ͨ���쳣���������ݲɼ����ɹ�������ͨ�����²ɼ��޲�!", "�ɼ�������", MB_OK|MB_ICONERROR);
			}

	   /*		if(mrOk == MessageBox(SDIAppForm->Handle, "���ݲɼ���ϣ��Ƿ�����������?", "�ɼ����", MB_OKCANCEL|MB_ICONQUESTION))
            	ValidStoreBtn->Click();
            else
            {
                ValidCProgressBar->Properties->Marquee = false;
			}         */

/*		}
		else
		{
			MessageBox(SDIAppForm->Handle, "�޷��������ݴ洢�ļ�������ϵ������Ա!", "Error", MB_OK|MB_ICONERROR);
	   //		if(BatchDataSaveToFileStream)
	   //			BatchDataSaveToFileStream.close();
			*validcollecttag = false;
			ModeOFCollect = 0;
			return;
		}         */
	}
	else
	{
		*validcollecttag = false;
		ModeOFCollect = 0;
		if(BatchDataSaveToFileStream)
			BatchDataSaveToFileStream.close();
		MessageBox(SDIAppForm->Handle, "Error in Load SerReceiveFunc Or SendAckFunc!", "Error", MB_OK|MB_ICONERROR);
	}
	ValidSBTN->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TBatchCollectDataThread::AnalyzeDataFunc()
{
	int recordNUM = (int)receivebuf[7]*256+(int)receivebuf[8];
	if((recordNUM<128)&&(recordNUM>0)&&(0x20 == receivebuf[0])&&(0x03 == receivebuf[1])
	  &&(DWPassword[0] == receivebuf[2])&&(DWPassword[1] == receivebuf[3])
	  &&(PosNumber == ((int)receivebuf[12]*256+(int)receivebuf[5]))
	  &&(0x23 == receivebuf[4]))
	{
	//��������
		String insqlstr = "";
        String AddinPosinsqlstr = "";
        String Watersqlstr = "";
        String Errorinsqlstr = "";
		int PosNumber = (int)receivebuf[12]*256+(int)receivebuf[5];

		int RecordIndexPos;
		int tmpKH;
		int tmpXFCS;
		double tmpYE;
		double tmpXFJE;
		String tmpDATESTR;
		String tmpXFLX;
		String tmpSQLSTR;

		unsigned char instr[4];
		unsigned char outstr[6];
		ZeroMemory(instr, 4);
		ZeroMemory(outstr, 6);

		String updatetimestr = DateTimeToStr(Now());

		for (int i = 0; i < (int)receivebuf[8]; i++)
		{
			RecordIndexPos = 14 + i*16;
			tmpKH = (int)receivebuf[RecordIndexPos]*256*256 + (int)receivebuf[RecordIndexPos+1]*256 + (int)receivebuf[RecordIndexPos+2];
			tmpXFCS = (int)receivebuf[RecordIndexPos+3]*256+(int)receivebuf[RecordIndexPos+4];
			tmpYE = ((double)receivebuf[RecordIndexPos+5]*256*256+(double)receivebuf[RecordIndexPos+6]*256+(double)receivebuf[RecordIndexPos+7])/100;
			tmpXFJE = ((double)receivebuf[RecordIndexPos+8]*256*256+(double)receivebuf[RecordIndexPos+9]*256+(double)receivebuf[RecordIndexPos+10])/100;

			instr[0] = receivebuf[RecordIndexPos+11];
			instr[1] = receivebuf[RecordIndexPos+12];
			instr[2] = receivebuf[RecordIndexPos+13];
			instr[3] = receivebuf[RecordIndexPos+14];
			if(GetnormaldateFunc)
			{
			//�������ʱ���ж�
				if(0 != GetnormaldateFunc(instr, outstr))
				{
				/*	outstr[0] = '0';
					outstr[1] = '1';
					outstr[2] = '1';
					outstr[3] = '0';
					outstr[4] = '0';
					outstr[5] = '0';            */
					tmpDATESTR = DateTimeToStr(Now());
				}
				else
				{
					tmpDATESTR = "20"+IntToHex((int)outstr[0], 2)+"-"+
									  IntToHex((int)outstr[1], 2)+"-"+
									  IntToHex((int)outstr[2], 2)+" "+
									  IntToHex((int)outstr[3], 2)+":"+
									  IntToHex((int)outstr[4], 2)+":"+
									  IntToHex((int)outstr[5], 2);
				}
			}
			else
			{
			/*	outstr[0] = '0';
				outstr[1] = '1';
				outstr[2] = '1';
				outstr[3] = '0';
				outstr[4] = '0';
				outstr[5] = '0';
				tmpDATESTR = "20"+IntToHex((int)outstr[0], 2)+"-"+
							 IntToHex((int)outstr[1], 2)+"-"+
							 IntToHex((int)outstr[2], 2)+" "+
							 IntToHex((int)outstr[3], 2)+":"+
							 IntToHex((int)outstr[4], 2)+":"+
							 IntToHex((int)outstr[5], 2);    */
				tmpDATESTR = DateTimeToStr(Now());
			}

			String UpdateTime = updatetimestr;

			try
			{
				StrToDateTime(tmpDATESTR);
			}
			catch(...)
			{
				tmpDATESTR = DateTimeToStr(Now());
			}

			if(StrToDateTime(tmpDATESTR)>Now())
			{
				tmpDATESTR = DateTimeToStr(Now());
			}
			else
			{
				TDateTime tmpdt = StrToDateTime(tmpDATESTR);
				tmpdt = IncYear(tmpdt, 1);
				if(tmpdt<Now())
				{
					tmpDATESTR = DateTimeToStr(Now());
				}
			}

			if(0 == receivebuf[RecordIndexPos+15])
				tmpXFLX = "X";
			else if(1 == receivebuf[RecordIndexPos+15])
				tmpXFLX = "Y";
			else if(2 == receivebuf[RecordIndexPos+15])
				tmpXFLX = "B";
			else if(3 == receivebuf[RecordIndexPos+15])
				tmpXFLX = "I";
			else if(4 == receivebuf[RecordIndexPos+15])
				tmpXFLX = "L";
			else if(5 == receivebuf[RecordIndexPos+15])
				tmpXFLX = "M";
			else if(6 == receivebuf[RecordIndexPos+15])
				tmpXFLX = "O";
			else if(7 == receivebuf[RecordIndexPos+15])
				tmpXFLX = "P";
			else if(250 == receivebuf[RecordIndexPos+15])
				tmpXFLX = "Z";
			else if(65 == receivebuf[RecordIndexPos+15]) //breakfast
                tmpXFLX = "S";
			else if(66 == receivebuf[RecordIndexPos+15]) //lunch
                tmpXFLX = "D";
			else if(67 == receivebuf[RecordIndexPos+15]) //supper
				tmpXFLX = "F";
			else if(68 == receivebuf[RecordIndexPos+15]) //night
                tmpXFLX = "G";
            else if(249 == receivebuf[RecordIndexPos+15])
            	tmpXFLX = "W";
			else tmpXFLX = "E";

            if("W" == tmpXFLX)
            {
                //analyze water data;
                int jqh;
                int waterkh;
                double xf1;
                double xf2;
                xf1 = ((double)receivebuf[RecordIndexPos+0]+(double)receivebuf[RecordIndexPos+1]*256+
                        (double)receivebuf[RecordIndexPos+2]*256*256+(double)receivebuf[RecordIndexPos+3]*256*256*256)/100;
                xf2 = ((double)(receivebuf[RecordIndexPos+4]^0xff)+(double)(receivebuf[RecordIndexPos+5]^0xff)*256+
                        (double)(receivebuf[RecordIndexPos+6]^0xff)*256*256+(double)(receivebuf[RecordIndexPos+7]^0xff)*256*256*256)/100;
                if(xf1 == xf2)
                {
                    jqh = (int)receivebuf[RecordIndexPos+8]*256+(int)receivebuf[RecordIndexPos+9];
                    waterkh = (int)receivebuf[RecordIndexPos+10]*256*256*256+
                    		(int)receivebuf[RecordIndexPos+11]*256*256+(int)receivebuf[12]*256+
                            (int)receivebuf[RecordIndexPos+13];
                //    String tjsqlstr = "insert into WTJ values(:JH,:CJKH,:XFZE,:SCSJ)";
                    String watertmpsqlstr = "insert into WTJ values(";
                    watertmpsqlstr += jqh;
                    watertmpsqlstr += ",";
                    watertmpsqlstr += waterkh;
                    watertmpsqlstr += ",";
                    watertmpsqlstr += xf1;
                    watertmpsqlstr += ",'";
					watertmpsqlstr += DateTimeToStr(Now());
                    watertmpsqlstr += "')";
					Watersqlstr += watertmpsqlstr;
				//	MessageBox(SDIAppForm->Handle, watertmpsqlstr.t_str(), "WTJstr", MB_OK|MB_ICONERROR);
				}

				//end analyze;
            }
            else
            {
                String F_bhstr;
                bool errortag = false;
                UpdateDataBaseQuery->Close();
                tmpSQLSTR = "select * from CARD_F where KH = '";
                tmpSQLSTR += tmpKH;
                tmpSQLSTR += "'";
                UpdateDataBaseQuery->SQL->Clear();
                UpdateDataBaseQuery->SQL->Add(tmpSQLSTR);
                UpdateDataBaseQuery->Open();
                if(!UpdateDataBaseQuery->IsEmpty())
                {
                 //	SerialNum = UpdateDataBaseQuery->FieldByName("BH")->AsAnsiString.Trim();

                    String tmpsqlstr = "insert into MX Values('";
                    tmpsqlstr += UpdateDataBaseQuery->FieldByName("BH")->AsAnsiString.Trim();
                    tmpsqlstr += "',";
                    tmpsqlstr += tmpKH;
                    tmpsqlstr += ",";
                    tmpsqlstr += tmpYE;
                    tmpsqlstr += ",";
                    tmpsqlstr += tmpXFJE;
                    tmpsqlstr += ",";
                    tmpsqlstr += tmpXFCS;
                    tmpsqlstr += ",'";
                    tmpsqlstr += tmpDATESTR;
                    tmpsqlstr += "',";
                    tmpsqlstr += PosNumber;
                    tmpsqlstr += ",0,'";
                    tmpsqlstr += tmpXFLX;
                    tmpsqlstr += "','";
                    tmpsqlstr += OperatorName;
                    tmpsqlstr += "','";
                    tmpsqlstr += updatetimestr;
                    tmpsqlstr += "')";
                    insqlstr += tmpsqlstr;

                    if("I" == tmpXFLX)
                    {
                        String tempaddinpossqlstr = "insert into CK Values(";
                        tempaddinpossqlstr += tmpKH;
                        tempaddinpossqlstr += ",'";
                        tempaddinpossqlstr += UpdateDataBaseQuery->FieldByName("BH")->AsAnsiString.Trim();
                        tempaddinpossqlstr += "',";
                        tempaddinpossqlstr += tmpYE;
                        tempaddinpossqlstr += ",1,";
                        tempaddinpossqlstr += tmpXFJE;//PosNumber;
                        tempaddinpossqlstr += ",0,";
                        tempaddinpossqlstr += tmpXFJE;//tmpXFLX;
                        tempaddinpossqlstr += ",0,";
                        tempaddinpossqlstr += tmpXFJE;
                        tempaddinpossqlstr += ",";
                        tempaddinpossqlstr += tmpXFCS;
                        tempaddinpossqlstr += ",'";
                        tempaddinpossqlstr += tmpDATESTR;
                        tempaddinpossqlstr += "',";
                        tempaddinpossqlstr += PosNumber;
                        tempaddinpossqlstr += ",1,'I','";
                        tempaddinpossqlstr += OperatorName;
                        tempaddinpossqlstr += "')";
                        AddinPosinsqlstr += tempaddinpossqlstr;
                    }
                /*
                    if("E" == tempXFLX)
                    {
                        String tmperrorsqlstr = "insert into MX Values('";
                        tmperrorsqlstr += UpdateDataBaseQuery->FieldByName("BH")->AsAnsiString.Trim();
                        tmperrorsqlstr += "',";
                        tmperrorsqlstr += tmpKH;
                        tmperrorsqlstr += ",";
                        tmperrorsqlstr += tmpYE;
                        tmperrorsqlstr += ",";
                        tmperrorsqlstr += tmpXFJE;
                        tmperrorsqlstr += ",";
                        tmperrorsqlstr += tmpXFCS;
                        tmperrorsqlstr += ",'";
                        tmperrorsqlstr += tmpDATESTR;
                        tmperrorsqlstr += "',";
                        tmperrorsqlstr += PosNumber;
                        tmperrorsqlstr += ",0,'";
                        tmperrorsqlstr += tmpXFLX;
                        tmperrorsqlstr += "','";
                        tmperrorsqlstr += OperatorName;
                        tmperrorsqlstr += "','";
                        tmperrorsqlstr += updatetimestr;
                        tmperrorsqlstr += "')";
                        Errorinsqlstr += tmperrorsqlstr;
                    }          */

                    if("E"!=tmpXFLX)
        			{
                        if(UpdateDataBaseQuery->FieldByName("SYCS")->AsInteger < tmpXFCS)
                        {
                            UpdateDataBaseQuery->Edit();
                            UpdateDataBaseQuery->FieldByName("SYCS")->AsInteger = tmpXFCS;
                            UpdateDataBaseQuery->FieldByName("SF_YE")->AsFloat = tmpYE;
                            UpdateDataBaseQuery->FieldByName("SFYEDT")->AsString = tmpDATESTR;
                            UpdateDataBaseQuery->Post();
                        }
                    }
                    F_bhstr = UpdateDataBaseQuery->FieldByName("BH")->AsString;
                }
                else
                    errortag = true;
                UpdateDataBaseQuery->Close();

                if("E"!=tmpXFLX)
                {
                    tmpSQLSTR = "select * from CARD_F where KH = '";
                    tmpSQLSTR += tmpKH;
                    tmpSQLSTR += "' and BH='";
                    tmpSQLSTR += F_bhstr;
                    tmpSQLSTR += "'";
                    UpdateDataBaseQuery->SQL->Clear();
                    UpdateDataBaseQuery->SQL->Add(tmpSQLSTR);
                    UpdateDataBaseQuery->Open();
                    if(!UpdateDataBaseQuery->IsEmpty())
                    {
                        if(UpdateDataBaseQuery->FieldByName("SYCS")->AsInteger < tmpXFCS)
                        {
                            UpdateDataBaseQuery->Edit();
                            UpdateDataBaseQuery->FieldByName("SYCS")->AsInteger = tmpXFCS;
                            UpdateDataBaseQuery->FieldByName("SF_YE")->AsFloat = tmpYE;
                            UpdateDataBaseQuery->FieldByName("SFYEDT")->AsString = tmpDATESTR;
                            UpdateDataBaseQuery->Post();
                        }
                    }
                    else
						errortag = true;
					UpdateDataBaseQuery->Close();

					tmpSQLSTR = "select * from CARD where KH = '";
                    tmpSQLSTR += tmpKH;
                    tmpSQLSTR += "' and BH='";
                    tmpSQLSTR += F_bhstr;
                    tmpSQLSTR += "'";
                    UpdateDataBaseQuery->SQL->Clear();
                    UpdateDataBaseQuery->SQL->Add(tmpSQLSTR);
                    UpdateDataBaseQuery->Open();
                    if(!UpdateDataBaseQuery->IsEmpty())
                    {
                        if(UpdateDataBaseQuery->FieldByName("SYCS")->AsInteger < tmpXFCS)
                        {
                            UpdateDataBaseQuery->Edit();
                            UpdateDataBaseQuery->FieldByName("SYCS")->AsInteger = tmpXFCS;
                            UpdateDataBaseQuery->FieldByName("SF_YE")->AsFloat = tmpYE;
                            UpdateDataBaseQuery->FieldByName("SFYEDT")->AsString = tmpDATESTR;
                            UpdateDataBaseQuery->Post();
                        }
                    }
                    else
						errortag = true;
					UpdateDataBaseQuery->Close();
                }

                //������ʾ
                poscollectedrecordcount++;// += recordNUM;
                ValidCProgressBar->Position = currentcount/nodecount*100+(100/nodecount*poscollectedrecordcount/posallrecordcount);
            }

		}
		//�������

		Sleep(100);
//		MessageBox(SDIAppForm->Handle, insqlstr.t_str(), "Error", MB_OK|MB_ICONERROR);
//		MessageBox(SDIAppForm->Handle, IntToStr(insqlstr.Length()).t_str(), "Error", MB_OK|MB_ICONERROR);
        if(insqlstr.Length()>0)
        {
            UpdateDataBaseQuery->Close();
            UpdateDataBaseQuery->SQL->Clear();
            UpdateDataBaseQuery->SQL->Add(insqlstr);
            UpdateDataBaseQuery->ExecSQL();
            UpdateDataBaseQuery->Close();
        }

        Sleep(100);
        if(AddinPosinsqlstr.Length()>0)
        {
			UpdateDataBaseQuery->Close();
            UpdateDataBaseQuery->SQL->Clear();
            UpdateDataBaseQuery->SQL->Add(AddinPosinsqlstr);
            UpdateDataBaseQuery->ExecSQL();
            UpdateDataBaseQuery->Close();
        }

        Sleep(100);
        if(Watersqlstr.Length()>0)
        {
			UpdateDataBaseQuery->Close();
            UpdateDataBaseQuery->SQL->Clear();
            UpdateDataBaseQuery->SQL->Add(Watersqlstr);
            UpdateDataBaseQuery->ExecSQL();
            UpdateDataBaseQuery->Close();
        }

		String prooutstr = tmpcaptionstr;
		prooutstr += "�Ѳɼ����";
		prooutstr += poscollectedrecordcount;
		prooutstr += "��";
		ValidInfoPanel->Caption = prooutstr;
/*		DWORD writelen;
		WriteFile(hStoreToFile, receivebuf, 2048, &writelen, NULL);     */
	//	BatchDataSaveToFileStream<<receivebuf<<endl;
		for(int i = 0; i < 2048; i++)
			BatchDataSaveToFileStream<<receivebuf[i];
	}
}
//---------------------------------------------------------------------------

void __fastcall TBatchCollectDataThread::DisplayCollectingFunc()
{
	TListItem* tmp = ValidDisplayListView->Items->Add();
	String posstr = PosNumber;
	posstr += "Pos��";
	tmp->Caption = posstr;
	tmp->SubItems->Add(Place);
	tmp->SubItems->Add("���ڽ����������ݲɼ�......");
//	tmp->SubItems->Add(DataStatusStr);

	tmp->Selected = true;
	ValidDisplayListView->SetFocus();
	ValidDisplayListView->Selected->MakeVisible(true);
	return;
}
//---------------------------------------------------------------------------

void __fastcall TBatchCollectDataThread::DisplayEndCollectFunc()
{
	int count = ValidDisplayListView->Items->Count;
	TListItem* tmp = ValidDisplayListView->Items->Item[count-1];
	tmp->SubItems->Strings[1] = CollectOverStautsStr;
//	tmp->SubItems->Strings[1]= "������������ݲɼ�!";

	return;
}

/*
void __fastcall TBatchCollectDataThread::AnalyzeDataFunc()
{
	int recordNUM = (int)receivebuf[7]*256+(int)receivebuf[8];
	if((recordNUM<128)&&(recordNUM>0)&&(0x20 == receivebuf[0])&&(0x03 == receivebuf[1])
	  &&(DWPassword[0] == receivebuf[2])&&(DWPassword[1] == receivebuf[3])
	  &&(PosNumber == ((int)receivebuf[12]*256+(int)receivebuf[5]))
	  &&(0x23 == receivebuf[4]))
	{
		ofstream TmpSaveInsertRecordFile("WaitForInsertToMX.dat");

		OrignalDataStr = "";
		int RecordIndexPos = 14;
		int tmpKH;
		int tmpXFCS;
		double tmpYE;
		double tmpXFJE;
		String tmpDATESTR;
		String tmpXFLX;
		String tmpSQLSTR;

		unsigned char instr[4];
		unsigned char outstr[6];
		ZeroMemory(instr, 4);
		ZeroMemory(outstr, 6);

		for (int t; t < 14; t++)
			OrignalDataStr = OrignalDataStr + (IntToHex((byte)receivebuf[t], 2));

		for (int i = 0; i < (int)receivebuf[8]; i++)
		{
			RecordIndexPos += i*16;

			for (int p; p < 16; p++)
			{
				OrignalDataStr += OrignalDataStr + (IntToHex((byte)receivebuf[RecordIndexPos + p], 2));
			}

			tmpKH = (int)receivebuf[RecordIndexPos]*256*256 + (int)receivebuf[RecordIndexPos+1]*256 + (int)receivebuf[RecordIndexPos+2];
			tmpXFCS = (int)receivebuf[RecordIndexPos+3]*256+(int)receivebuf[RecordIndexPos+4];
			tmpYE = ((double)receivebuf[RecordIndexPos+5]*256*256+(double)receivebuf[RecordIndexPos+6]*256+(double)receivebuf[RecordIndexPos+7])/100;
			tmpXFJE = ((double)receivebuf[RecordIndexPos+8]*256*256+(double)receivebuf[RecordIndexPos+9]*256+(double)receivebuf[RecordIndexPos+10])/100;

			if(GetnormaldateFunc)
			{
				if(0 != GetnormaldateFunc(instr, outstr))
				{
					outstr[0] = '0';
					outstr[1] = '1';
					outstr[2] = '1';
					outstr[3] = '0';
					outstr[4] = '0';
					outstr[5] = '0';
				}
				tmpDATESTR = "20"+IntToHex((int)outstr[0], 2)+"-"+
								  IntToHex((int)outstr[1], 2)+"-"+
								  IntToHex((int)outstr[2], 2)+" "+
								  IntToHex((int)outstr[3], 2)+":"+
								  IntToHex((int)outstr[4], 2)+":"+
								  IntToHex((int)outstr[5], 2);
			}
			else
			{
				outstr[0] = '0';
				outstr[1] = '1';
				outstr[2] = '1';
				outstr[3] = '0';
				outstr[4] = '0';
				outstr[5] = '0';
				tmpDATESTR = "20"+IntToHex((int)outstr[0], 2)+"-"+
							 IntToHex((int)outstr[1], 2)+"-"+
							 IntToHex((int)outstr[2], 2)+" "+
							 IntToHex((int)outstr[3], 2)+":"+
							 IntToHex((int)outstr[4], 2)+":"+
						 	 IntToHex((int)outstr[5], 2);
			}

			if('0' == receivebuf[15])
				tmpXFLX = "X";
			if('1' == receivebuf[15])
				tmpXFLX = "Y";
			if('2' == receivebuf[15])
				tmpXFLX = "B";
			if('3' == receivebuf[15])
				tmpXFLX = "A";
			if('4' == receivebuf[15])
				tmpXFLX = "L";
			if('5' == receivebuf[15])
				tmpXFLX = "M";
			if('6' == receivebuf[15])
				tmpXFLX = "O";
			if('7' == receivebuf[15])
				tmpXFLX = "P";
			if('250' == receivebuf[15])
				tmpXFLX = "Z";

			UpdateDataBaseQuery->Close();
			tmpSQLSTR = "select * from CARD where KH = '";
			tmpSQLSTR += tmpKH;
			tmpSQLSTR += "'";
			UpdateDataBaseQuery->SQL->Clear();
			UpdateDataBaseQuery->SQL->Add(tmpSQLSTR);
			UpdateDataBaseQuery->Open();
			if(!UpdateDataBaseQuery->IsEmpty())
			{
				SerialNum = UpdateDataBaseQuery->FieldByName("BH")->AsAnsiString;
				if(UpdateDataBaseQuery->FieldByName("SYCS")->AsInteger < tmpXFCS)
				{
					UpdateDataBaseQuery->Edit();
					UpdateDataBaseQuery->FieldByName("SYCS")->AsInteger = tmpXFCS;
					UpdateDataBaseQuery->FieldByName("SF_YE")->AsFloat = tmpYE;
					UpdateDataBaseQuery->Post();
				}
			}
			UpdateDataBaseQuery->Close();

			tmpSQLSTR = "select * from CARD_F where KH = '";
			tmpSQLSTR += tmpKH;
			tmpSQLSTR += "'";
			UpdateDataBaseQuery->SQL->Clear();
			UpdateDataBaseQuery->SQL->Add(tmpSQLSTR);
			UpdateDataBaseQuery->Open();
			if(!UpdateDataBaseQuery->IsEmpty())
			{
				UpdateDataBaseQuery->Edit();
				UpdateDataBaseQuery->FieldByName("SYCS")->AsInteger = tmpXFCS;
				UpdateDataBaseQuery->FieldByName("SF_YE")->AsFloat = tmpYE;
				UpdateDataBaseQuery->Post();
			}
			UpdateDataBaseQuery->Close();

			String UpdateTime;
			SYSTEMTIME tmpsystime;
			GetLocalTime(&tmpsystime);
			UpdateTime = DateTimeToStr(SystemTimeToDateTime(tmpsystime));

			TmpSaveInsertRecordFile<<SerialNum.t_str()<<","<<tmpKH<<","<<tmpYE<<","<<tmpXFJE<<",";
			TmpSaveInsertRecordFile<<tmpXFCS<<","<<tmpDATESTR.t_str()<<","<<PosNumber<<","<<"0";
			TmpSaveInsertRecordFile<<tmpXFLX.t_str()<<","<<OperatorName.t_str()<<","<<UpdateTime.t_str()<<endl;
		}

		tmpSQLSTR = "bulk insert MX from 'WaitForInsertToMX.dat' with (fieldterminator=',',rowterminator='\n')";
		UpdateDataBaseQuery->SQL->Clear();
		UpdateDataBaseQuery->SQL->Add(tmpSQLSTR);
		UpdateDataBaseQuery->ExecSQL();
		UpdateDataBaseQuery->Close();

		tmpSQLSTR = "bulk insert MXBAK from 'WaitForInsertToMX.dat' with (fieldterminator=',',rowterminator='\n')";
		UpdateDataBaseQuery->SQL->Clear();
		UpdateDataBaseQuery->SQL->Add(tmpSQLSTR);
		UpdateDataBaseQuery->ExecSQL();
		UpdateDataBaseQuery->Close();

		TmpSaveInsertRecordFile.close();

		DeleteFileA("WaitForInsertToMX.dat");
    }
}
//---------------------------------------------------------------------------

void __fastcall TBatchCollectDataThread::DisplayDataFunc()
{
	String tmphead = PosNumber;
	tmphead += "��POS�����ݣ�";
	DisplayRichEditView->Lines->Add(tmphead);
	DisplayRichEditView->Lines->Add(OrignalDataStr);
	DisplayRichEditView->Lines->Add("\n");
}
//---------------------------------------------------------------------------

void __fastcall TBatchCollectDataThread::SaveDataToFileFunc()
{
	BatchDataSaveToFileStream<<PosNumber<<"��POS�����ݣ�"<<endl;
	BatchDataSaveToFileStream<<OrignalDataStr.t_str()<<endl;
}
//---------------------------------------------------------------------------












/*	String CollectTime = "*CollectTime* "; //ԭʼ�����ɼ�����
	CollectTime += Date();
	CollectTime += " ";
	CollectTime += Time();

	BatchDataSaveToFileStream<<CollectTime.t_str()<<endl;

	WORD ReceiveStatus = -1;
	WORD SynchroStatus = -1;
	char temp[10] = "";
	unsigned char como = 0x00;
	WORD NO1 = 1;
	unsigned char ReceiveCMD = 0x23;
	unsigned char SynchroCMD = 0x54;
	ZeroMemory(receivebuf, 2048);
	int receivelen = 2048;
	unsigned char* dir = "E:\\RAD\\2010-9-26\\Recieve";
	int dirlen = strlen(dir);

	unsigned char* SynchroTagbuf = new unsigned char[300];
	ZeroMemory(SynchroTagbuf, *ONLinePosNum);

	String comparestr = "FFFFFFFFFFFFFFFFFFFF";

	if(*ONLinePosNum > 0)
	{
		if(getusbcomportdll)
		{
			strcpy(temp, getusbcomportdll());
			String tt = temp;
			int tempcom = StrToInt(tt.SubString(4, tt.Length()-3).c_str());
			if(tempcom>255)
			{
				MessageBox(SDIAppForm->Handle, "POS�����ӵ�COM�ڲ��ܴ���255��", "Collect Error!", MB_OK);
			}
			else
			{
				IntToChar(tempcom, &como);
				ValidPauseBTN->Enabled = true;
				while(true)
				{
					if(!Terminated)
					{
						PosNumber = -1;
						OrignalDataStr = "";
						for(WORD PosNO = 1; PosNO<=300; PosNO++)
						{
							if(!Terminated)
							{
								if((0x00 == SynchroTagbuf[PosNO-1])&&(0x01 == PosInUseTag[PosNO-1]))
								{
									ReceiveStatus = SerReceiveFunc(como, PosNO, ReceiveCMD, receivebuf, receivelen, 1, dir, dirlen);
									if(0 == ReceiveStatus)
									{
										SynchroStatus = SendAckFunc(como, SynchroCMD);
										if(0 == SynchroStatus)
										{
											if(0x00 == receivebuf[8])
											{
												SynchroTagbuf[PosNO-1] = 0x01;//˵��û�вɼ�����¼
											}
											else
											{
												Synchronize(AnalyzeDataFunc);
												Synchronize(SaveDataToFileFunc);
												Synchronize(DisplayDataFunc);
											}
										}
										else
										{
											//��POS�޷������ɼ����ݣ���listviewͼ����кڰ׻�
											ValidPosTreeList->Items[0]->Items[PosNO-1]->ImageIndex = 2;
											ValidPosTreeList->Items[0]->Items[PosNO-1]->Texts[0] = "����POS��";
											SynchroTagbuf[PosNO-1] = 0x01;
										}
									}
									else
									{
										//��POS�޷������ɼ����ݣ���listviewͼ����кڰ׻�
										ValidPosTreeList->Items[0]->Items[PosNO-1]->ImageIndex = 2;
										ValidPosTreeList->Items[0]->Items[PosNO-1]->Texts[0] = "����POS��";
										SynchroTagbuf[PosNO-1] = 0x01;
									}
								}
							}
							else
								return;
						}
					}
					else
						return;
                }
			}
		}
	}    */

/*  ��ԭʼ���̴߳���
	if(SerReceiveFunc&&SendAckFunc)
	{
		*validcollecttag = true;
		ModeOFCollect = 2;
		String CollectTime = "*CollectTime* ";
		CollectTime += Date();
		CollectTime += " ";
		CollectTime += Time();

		BatchDataSaveToFileStream<<endl<<CollectTime.t_str()<<endl;

		TTreeNode* tmpnode = ValidPosTreeList->Items->GetFirstNode();
		while(tmpnode)
		{
			if(!Terminated)
			{
				tmpnode->Data;
				POSPARA* tmppospara = (POSPARA*)(tmpnode->Data);
				if(4 == tmppospara->tag)
				{
					WORD ReceiveStatus = -1;
					WORD SynchroStatus = -1;
					char temp[10] = "";
					unsigned char como = (unsigned char)(tmppospara->comnum);
					PosNumber = tmppospara->posnum;
					WORD PosNO = (WORD)(tmppospara->posnum);
					unsigned char ReceiveCMD = 0x23;
					unsigned char SynchroCMD = 0x54;
					ZeroMemory(receivebuf, 2048);
					int receivelen = 2048;
					unsigned char* dir = "E:\\RAD\\2010-9-26\\Recieve";
					int dirlen = strlen(dir);

					UpdateDataBaseQuery->Close();
					UpdateDataBaseQuery->SQL->Clear();
					String tmpsql = "select * from SFJPARAM where JH='";
					tmpsql += tmppospara->posnum;
					tmpsql += "'";
					UpdateDataBaseQuery->SQL->Add(tmpsql);
					UpdateDataBaseQuery->Open();
					Place = UpdateDataBaseQuery->FieldByName("STNAME")->AsAnsiString;
					UpdateDataBaseQuery->Close();

					if(!Terminated)
					{
						ReceiveStatus = SerReceiveFunc(como, PosNO, ReceiveCMD, receivebuf, receivelen, 1, dir, dirlen);
						if(0 == ReceiveStatus)
						{
							SynchroStatus = SendAckFunc(como, SynchroCMD);
							if(0 == SynchroStatus)
							{
								if(0x00 != receivebuf[8])
								{
									Synchronize(AnalyzeDataFunc);
									Synchronize(SaveDataToFileFunc);
									Synchronize(DisplayDataFunc);
								}
							}
						}
					}
				}
			}
			else
			{
				*validcollecttag = false;
				ModeOFCollect = 0;
				return;
			}
			tmpnode = tmpnode->GetNext();
			if(!tmpnode)
				tmpnode = ValidPosTreeList->Items->GetFirstNode();
		}
	}
	else
	{
		*validcollecttag = false;
		ModeOFCollect = 0;
		MessageBox(SDIAppForm->Handle, "Error in Load SerReceiveFunc Or SendAckFunc!", "Error", MB_OK);
	}
*/
