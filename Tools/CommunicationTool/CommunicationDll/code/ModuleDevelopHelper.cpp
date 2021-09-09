#include "stdafx.h"
#include "ModuleDevelopHelper.h"
#include "vMacro.h"
#include "Communication232Interface.h"
#include "CommunicationSocketInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) DWORD __stdcall DllGetVerInfo(DLL_VER_INFO& dllVerInfo)
{
	//�ⲿ�����߲�ѯģ���֧�ֵ�ʵ�ʰ汾�ṹ���ڴ��ֽڴ�С
	if( 0==dllVerInfo._dwByteSize ){
		dllVerInfo._dwByteSize = sizeof(DLL_VER_INFO);
		return 0x00;
	}
	else if( dllVerInfo._dwByteSize<sizeof(DLL_VER_INFO) ){
		return vMAKE_RLT(FALSE, 0x00, 0x000008);
	}
	else{
		DLL_VER_INFO di;
		memset(&di, 0, sizeof(DLL_VER_INFO));
		////�˴�����ģ���֧�ֵ�DLL_VER_INFO���°汾�ṹ���ֽڴ�С
		di._dwByteSize = sizeof(DLL_VER_INFO);

		////�˴�����ģ���֧�ֵ�DLL_VER_INFO�����°汾
		di._dwVerInfo = 1;//tagDLL_VER_INFO��ǰ�ṹ��汾

		////�˴��޶�ģ���汾��Ϣ
		di._dwVerMain = 3;//��̬�⵱ǰ���汾��
		di._dwVerSubMain = 0;//��̬�⵱ǰ�����汾��
		di._dwVerSubSub = 1;//��̬�⵱ǰ�δΰ汾��

		////�˴��޶�ģ���֧�ֵĽӿ���Ϣ
		di._dwInterfaceNo = 1000;//��̬�⵱ǰ֧�ֵ����ӿں�

		////�˴����ģ���������Ϣ
		strcpy(di._szLibType, "{3F025B4F-936A-45d3-B4BF-BAE6ACA81FA5}");//��ģ�������

		////����ģ���UNICODE��־
#ifdef	_UNICODE
		di._cbFlagUnicode = 1;
#else
		di._cbFlagUnicode = 0;
#endif

		////�˴��޶�ģ���֧�ֵ��ַ�������ĸ���
		di._cbCmdCount = 0;

		////�˴�������Ϣ�����_cbExtraInfo
		//::_tcscpy((TCHAR*) di._cbExtraInfo, TEXT("������Ϣ"));

		////
		memcpy(&dllVerInfo, &di, sizeof(DLL_VER_INFO));
		return 0x00;
	}
}

extern "C" __declspec(dllexport) DWORD __stdcall DllCreateInterface(long nInterfaceNo,void** ppInterface)
{
	DLL_VER_INFO di;
	di._dwByteSize = sizeof(DLL_VER_INFO);
	::DllGetVerInfo(di);
	if( NULL==ppInterface ){
		return vMAKE_RLT(FALSE, 0, 0x000002);
	}
	*ppInterface = NULL;
	////
	if( nInterfaceNo>(long) di._dwInterfaceNo || nInterfaceNo<1 ){
		return vMAKE_RLT(FALSE, 0, 0x000003);
	}
	////
	switch( nInterfaceNo ){
	case (int)E_TOOL_COMMUNICATION_COMM232 :
		{
			CCommunication232Interface * pVision = new CCommunication232Interface();
			*ppInterface = (void*) ((CCommunicationBase*) pVision);
		}
		break;
	case (int)E_TOOL_COMMUNICATION_TCPIP :
		{
			CCommunicationSocketInterface * pVision = new CCommunicationSocketInterface();
			*ppInterface = (void*) ((CCommunicationBase*) pVision);
		}
	}
	////
	return 0x00;
}

extern "C" __declspec(dllexport) DWORD __stdcall DllGetCmdInfo(long& nCmdIndex, DLL_CMD_INFO* pDllCmdInfo)
{
	////�ж��Ƿ�֧���ַ�������
	BOOL bCmd = FALSE;
	////�˴��޶��Ƿ�֧���ַ��������־
	//bCmd = TRUE;

	if( !bCmd ){//ģ�鲻֧���ַ�������
		return vMAKE_RLT(FALSE, 0, 0x000009);
	}

	////
	long nCmdCount = 0;
	////�˴����֧���ַ����������
	//nCmdCount = 1;

	////
	if( nCmdIndex<0 ){//�ͻ���ѯģ��֧�ֵ��ַ�������ĸ���
		nCmdIndex = nCmdCount;
		return 0x00;
	}
	else{
		if( nCmdIndex>=nCmdCount ){
			return vMAKE_RLT(FALSE, 0, 0x000009);
		}
		else{
			////
			if( NULL==pDllCmdInfo ){
				return vMAKE_RLT(FALSE, 0, 0x000002);
			}
			////
			if( 0==pDllCmdInfo->_dwByteSize ){
				pDllCmdInfo->_dwByteSize = sizeof(DLL_CMD_INFO);
				return 0x00;
			}
			else if( pDllCmdInfo->_dwByteSize<sizeof(DLL_CMD_INFO) ){
				return vMAKE_RLT(FALSE, 0x00, 0x000008);
			}
			else{
				DLL_CMD_INFO ci;
				memset(&ci, 0, sizeof(DLL_VER_INFO));
				////�˴�����ģ���֧�ֵ�DLL_CMD_INFO���°汾�ṹ���ֽڴ�С
				ci._dwByteSize = sizeof(DLL_CMD_INFO);

				////�˴�����ģ���֧�ֵ�DLL_CMD_INFO�����°汾
				ci._dwVerInfo = 1;//tagDLL_CMD_INFO��ǰ�ṹ��汾

				////�˴��޶�����������ַ�������
				//::strcpy(ci._szCmd, "C_G_SZ_FRESH_RES");

				////�˴��޶�������ַ���������Ӧ����
				//ci._ptrFunc = (DWORD) funcOnFreshRes;

				////
				memcpy(pDllCmdInfo, &ci, sizeof(DLL_CMD_INFO));
				return 0x00;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////