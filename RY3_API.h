#ifndef  __FT_RY3_HEADER_H
#define  __FT_RY3_HEADER_H

#ifdef __cplusplus
extern "C" {
#endif
typedef void*  RY_HANDLE;

//������
#define   RY3_SUCCESS                       0x00000000          // �����ɹ�
#define   RY3_NOT_FOUND                     0xF0000001          // δ�ҵ�ָ�����豸
#define   RY3_INVALID_PARAMETER			    0xF0000002			// ��������
#define   RY3_COMM_ERROR					0xF0000003			// ͨѶ����
#define   RY3_INSUFFICIENT_BUFFER		    0xF0000004			// �������ռ䲻��
#define   RY3_NO_LIST					    0xF0000005			// û���ҵ��豸�б�
#define   RY3_DEVPIN_NOT_CHECK				0xF0000006			// �����̿���û����֤
#define   RY3_USERPIN_NOT_CHECK			    0xF0000007			// �û�����û����֤
#define	  RY3_RSA_FILE_FORMAT_ERROR	        0xF0000008			// RSA�ļ���ʽ����
#define   RY3_DIR_NOT_FOUND				    0xF0000009			// Ŀ¼û���ҵ�
#define   RY3_ACCESS_DENIED				    0xF000000A			// ���ʱ��ܾ�
#define   RY3_ALREADY_INITIALIZED		    0xF000000B		    // ��Ʒ�Ѿ���ʼ��
#define   RY3_INCORRECT_PIN				    0xF0000C00		    // ���벻��ȷ
#define   RY3_DF_SIZE						0xF000000D		    // ָ����Ŀ¼�ռ��С����
#define   RY3_FILE_EXIST					0xF000000E		    // �ļ��Ѵ���
#define   RY3_UNSUPPORTED					0xF000000F			// ���ܲ�֧�ֻ���δ�����ļ�ϵͳ
#define   RY3_FILE_NOT_FOUND				0xF0000010			// δ�ҵ�ָ�����ļ�
#define	  RY3_ALREADY_OPENED				0xF0000011		    // ���Ѿ�����
#define   RY3_DIRECTORY_EXIST				0xF0000012			// Ŀ¼�Ѵ���
#define   RY3_CODE_RANGE					0xF0000013			// ������ڴ��ַ���
#define   RY3_INVALID_POINTER				0xF0000014			// ����������ָ��
#define   RY3_GENERAL_FILESYSTEM			0xF0000015		    // �����ļ�ϵͳ���� 
#define   RY3_OFFSET_BEYOND				    0xF0000016		    // �ļ�ƫ���������ļ���С
#define   RY3_FILE_TYPE_MISMATCH			0xF0000017		    // �ļ����Ͳ�ƥ��
#define   RY3_PIN_BLOCKED					0xF0000018		    // PIN������
#define   RY3_INVALID_HANDLE				0xF0000019			// ��Ч�ľ��
#define   RY3_ERROR_UNKNOWN				    0xFFFFFFFF			// δ֪�Ĵ���


#define   RY3_C51_SUCCESS				    0x00000000			//	�ɹ�
#define   RY3_C51_UNKNOWN				    0x00000001			//	δ֪����
#define   RY3_C51_INVALID_PARAMETER	        0x00000002			//	��Ч�Ĳ���
#define   RY3_C51_INVALID_ADDRESS		    0x00000003			//	��Ч�ĵ�ַ,�������ַԽ��
#define   RY3_C51_INVALID_SIZE			    0x00000004			//	��Ч�ĳ���
#define   RY3_C51_FILE_NOT_FOUND		    0x00000005			//	�ļ�û�ҵ�
#define   RY3_C51_ACCESS_DENIED		        0x00000006			//	�����ļ�ʧ��
#define   RY3_C51_FILE_SELECT			    0x00000007			//	�ļ��򿪸����Ѵ�����
#define   RY3_C51_INVALID_HANDLE		    0x00000008			//	��Ч���ļ����
#define   RY3_C51_FILE_OUT_OF_RANGE	        0x00000009			//	�ļ���дԽ��
#define   RY3_C51_FILE_TYPE_MISMATCH	    0x0000000A			//	�ļ����ڵ����Ͳ�ƥ��
#define   RY3_C51_FILE_SIZE_MISMATCH	    0x0000000B			//	�ļ����ڵ����Ȳ�ƥ��
#define   RY3_C51_NO_SPACE				    0x0000000C			//	�ļ��пռ䲻��
#define   RY3_C51_FILE_EXIST			    0x0000000D			//	�ļ�����Ŀ¼�Ѵ���
#define   RY3_C51_INVALID_KEY_FORMAT	    0x0000000E			//	��Ч��RSA��Կ�ļ���ʽ
#define   RY3_C51_KEY_LEN_MISMATCH		    0x0000000F			//  �û��������Կ������ʵ�ʳ��Ȳ�ƥ��
#define   RY3_C51_RSA_INVALID_KEY_FILE	    0x00000010			//	�ļ����Ͳ�����Ҫ��
#define   RY3_C51_RSA_ENC_DEC_FAILED	    0x00000011			//	RSA���ܽ���ʧ��
#define   RY3_C51_RSA_SIGN_VERI_FAILED	    0x00000012			//	RSAǩ����֤ʧ��
#define   RY3_C51_SHA1					    0x00000013			//  SHA1�������
#define   RY3_C51_MD5					    0x00000014			//  MD5�������
#define   RY3_C51_INVALID_ADDERSS		    0x00000015			//  ��Ч���ڴ�ָ��
#define   RY3_C51_EEPROM				    0x00000016			//  дEEPROM����


typedef struct
{
	int     m_Item;          //����1���豸��Ŀ
	char    m_VendorID[12];  //8�ֽ��ַ�����ʽ��VendorID
	char    m_HardID[20];    //16�ֽ��ַ�����ʽ��HardID
}RY3_INFO;


//===============================================================================

//����RY3 (����VendorID�ִ�, ����ҵ���RY3��Ŀ)
DWORD WINAPI RY3_Find(char* pVendorID, int* pCount);

//��ָ����Ŀ��RY3 (������Ŀ,����1,������)
DWORD WINAPI RY3_Open(RY_HANDLE* pHandle, int Item);

//�ر�RY3 (IsReset��ʾ�Ƿ�λ������,�����ȫ״̬)
DWORD WINAPI RY3_Close(RY_HANDLE handle, BOOL IsReset);

//����VendorID (�����볤��ӦС��250�ֽ�)
DWORD WINAPI RY3_SetVendorID(RY_HANDLE handle, char* pSeed, int len, char* pOutVendorID);

//��ȡӲ�����к�(���16�ֽڵ��ַ���)
DWORD WINAPI RY3_GetHardID(RY_HANDLE handle, char* pbuf);

//��ȡ�����(lenָ����������������)
DWORD WINAPI RY3_GenRandom(RY_HANDLE handle, int len_need, BYTE* pOutbuf);

//��ȡ���пռ��С
DWORD WINAPI RY3_GetFreeSize(RY_HANDLE handle, int* pSize);

#define RY3_LED_ON                   1 //����
#define RY3_LED_OFF                  2 //����
#define RY3_LED_WINK                 3 //����

//LED����
DWORD WINAPI RY3_LEDControl(RY_HANDLE handle, int flag);

//У�鿪��������
//У��ɹ�ʱ���ص�RemainCount  0
//У��ʧ��ʱ���ص�RemainCount  0:������  1-254:ʣ�����  255:������
DWORD WINAPI RY3_VerifyDevPin(RY_HANDLE handle, char* pInPin, int* pRemainCount);

//���Ŀ���������(TryCountȡֵ��ΧΪ1-255, ����255��ʾ������)
DWORD WINAPI RY3_ChangeDevPin(RY_HANDLE handle, char* pOldPin, char* pNewPin, int TryCount);

//���洢��(0-8191�ֽ�)
DWORD WINAPI RY3_Read(RY_HANDLE handle, int offset, BYTE* pOutbuf, int len);

//д�洢��(0-7167�ֽ�)
DWORD WINAPI RY3_Write(RY_HANDLE handle, int offset, BYTE* pInbuf, int len);

//������д�洢��(0-8191�ֽ�)
DWORD WINAPI RY3_VendorWrite(RY_HANDLE handle, int offset, BYTE* pInbuf, int len);

//���������ڴ���(0-31�ֽ�)
DWORD WINAPI RY3_ReadShare(RY_HANDLE handle, int offset, BYTE* pbuf, int len);

//д�������ڴ���(0-31�ֽ�)
DWORD WINAPI RY3_WriteShare(RY_HANDLE handle, int offset, BYTE* pbuf, int len);

#define FILE_TYPE_EXE				 0		 //��ִ���ļ�
#define FILE_TYPE_DATA			 	 1		 //�����ļ�
#define FILE_TYPE_RSA_PUBLIC		 2		 //RSA ��Կ�ļ�
#define FILE_TYPE_RSA_PRIVATE		 3		 //RSA ˽Կ�ļ�

//�����ļ�
DWORD WINAPI RY3_CreateFile(RY_HANDLE handle, WORD FileID, int Size, int Type);

//д�ļ�
DWORD WINAPI RY3_WriteFile(RY_HANDLE handle, WORD FileID, int offset, BYTE* pbuf, int Size);

//ִ���ļ�
DWORD WINAPI RY3_ExecuteFile(RY_HANDLE handle, WORD FileID, BYTE* pInBuf, int InSize, BYTE* pOutBuf, int* pOutSize);

//ɾ�������ļ�
DWORD WINAPI RY3_EraseAllFile(RY_HANDLE handle);

//����RSA��˽Կ(kidȡֵ��Χ:0-8, ����0��ʾ������˽Կ��, 1-8Ϊ��ͨ��˽Կ��)
//pPubBakup�����140�ֽڵĹ�Կ������
//pPriBakup�����340�ֽڵ�˽Կ������
//pPubBakup��pPriBakupΪNULLʱ��ʾ������
DWORD WINAPI RY3_GenRsaKey(RY_HANDLE handle, int kid, BYTE* pPubBakup, BYTE* pPriBakup);

//����RSA��Կ��512λ
DWORD WINAPI RY3_GenRsaKey512(RY_HANDLE handle, WORD pubID,WORD priID, BYTE* pPubBakup, BYTE* pPriBakup);

//����RSA��Կ��2048λ
DWORD WINAPI RY3_GenRsaKey2048(RY_HANDLE handle, WORD pubID,WORD priID, BYTE* pPubBakup, BYTE* pPriBakup);

//����RSA��˽Կ(kidȡֵ��Χ:0-8, ����0��ʾ������˽Կ��, 1-8Ϊ��ͨ��˽Կ��)
//pPubKey������140�ֽڵĹ�Կ��д��
//pPriKey������340�ֽڵ�˽Կ��д��
//pPubKey��pPriKeyΪNULLʱ��ʾ��д��
DWORD WINAPI RY3_SetRsaKey(RY_HANDLE handle, int kid, BYTE* pPubKey, BYTE* pPriKey);

//��Կ�����㷨(kidȡֵ��Χ:1-8)
//�������ݳ��ȱ�����128��������
DWORD WINAPI RY3_PublicEncrypt(RY_HANDLE handle, int kid, BYTE* pBuf, int len);

//˽Կ�����㷨(kidȡֵ��Χ:1-8)
//�������ݳ��ȱ�����128��������
DWORD WINAPI RY3_PrivateDecrypt(RY_HANDLE handle, int kid, BYTE* pBuf, int len);

//MD5ǩ���㷨
DWORD WINAPI RY3_MD5(RY_HANDLE handle, BYTE* pBuf, int len, BYTE* pMD5);

//SHA1ǩ���㷨
DWORD WINAPI RY3_SHA1(RY_HANDLE handle, BYTE* pBuf, int len, BYTE* pSHA1);

//����3DES�ӽ��ܵ���Կ,��Կ���ȹ̶�Ϊ16�ֽ�, (kidȡֵ��Χ:1-8)
DWORD WINAPI RY3_Set3DESKey(RY_HANDLE handle, int kid, BYTE* pKey);

#define FLAG_ENCODE  0 //����
#define FLAG_DECODE  1 //����

//3DES�ӽ����㷨(kidȡֵ��Χ:1-8)
//�������ݳ��ȱ�����8��������
DWORD WINAPI RY3_3DES(RY_HANDLE handle, int kid, int flag, BYTE* pBuf, int len);


//Զ������������������(pbuf����������Կ���ܵ�UpdateData���ݽṹ, len������128�ֽڵ�������)
DWORD WINAPI RY3_Update(RY_HANDLE handle, BYTE* pbuf, int len);

#define Data_TYPE_PubKey   0   //��Կ����
#define Data_TYPE_PriKey   1   //˽Կ����
#define Data_TYPE_3DesKey  2   //3DES��Կ����
#define Data_TYPE_Memory   3   //8192�ֽ�������

//�����������ݰ�
//pLicSN:     ָ����������������Ӳ�����к�,���pLicSN=NULL��ʾ������Ӳ�����к�
//type:       Ҫ��������������
//kid_offset: Ҫ������������Ŀ��ƫ�Ƶ�ַ(Ϊ��Ŀʱ,ȡֵ��ΧΪ1-8, ��type=Data_TYPE_Memoryʱ,��ʾ8192��������ƫ�Ƶ�ַ)
//pbuf:       Ҫ���������ݵ�ַ
//len:        Ҫ���������ݳ���(ע:len����Ϊ140�ֽ�(��Կ����),340�ֽ�(˽Կ����),16�ֽ�(ES��Կ����))
//pUPubKey:   ָ��������Կ����
//pOutData:   ����������������ݰ�
//pOutLen:    ����������ݰ��ĳ���
DWORD WINAPI RY3_GenUpdatePacket(RY_HANDLE handle, char* pLicSN, int type, int kid_offset, BYTE* pbuf, int len, BYTE* pUPubKey, /*DWORD value,BYTE policy,*/ BYTE* pOutData, int* pOutLen);


#ifdef __cplusplus 
}
#endif

#endif	//__FT_RY3_HEADER_H