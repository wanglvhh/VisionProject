#pragma once
#include "resource.h"
#include "VisionData.h"
#include "HardWareData.h"
#include "WorkFlowDlg.h"
#include "ManageCameraDlg.h"
#include "ManageCommunication.h"
#include "ManageModbus.h"
#include "ImageViewDlg.h"
#include "VisionGlobal.h"
#include "SystemIni.h"

class CProjectData
{
public:
	CProjectData()
	{
		m_strRoot = GetExepath() ;
		m_strProjectPath = m_strRoot + _T("Project\\Project.cf") ;
		m_strCameraPath =  m_strRoot + _T("Device\\Camera\\CameraDevice.cf") ;
		m_strLedPath = m_strRoot + _T("Device\\Led\\LedDevice.cf") ;
		m_strCommunicationPath = m_strRoot + _T("Device\\Communication\\Communication.cf") ;
		m_strModbusPath = m_strRoot + _T("Device\\Modbus\\Modbus.cf") ;
		m_mgProject.RemoveAll() ;
		m_mgWorkFlowDlg.workFlowDlgList.RemoveAll() ;
		m_mgImageViewDlg.imageViewDlgList.RemoveAll() ;
		m_mgGobalViarent.gobalViarentList.RemoveAll() ;
		m_mgCamera.cameraNodeList.RemoveAll() ;
		m_mgCommunication.commNodeList.RemoveAll() ;
		m_mgModbus.modbusNodeList.RemoveAll() ;

		LoadIni() ;
	}

	~CProjectData()
	{
		//删除数据
	}

	void LoadIni()
	{
		TCHAR szBuffer[MAX_PATH] ;
		CString strSysParaFile(_T("")) ;

		//SysIni
		strSysParaFile = m_strRoot + _T("IniFile\\System.ini") ;
		_tcscpy ( szBuffer, strSysParaFile ) ;
		g_sysIni.Initialize ( szBuffer ) ;
		g_sysIni.LoadPara() ;
	}

	void LoadDeviceData()
	{
		try
		{
			//加载相机配置
			LoadCameraConfig() ;
		}
		catch (...)
		{
		}
	}

	void SaveDeviceData()
	{
		try
		{
			//保存相机配置
			SaveCameraConfig() ;
		}
		catch (...)
		{
		}
	}

	void LoadProjectData()
	{
		try
		{
			LoadProjectName() ;

			LoadImageViewConfig() ;

			LoadWorkFlowConfig() ;

			LoadGobalViarentConfig() ;

			LoadCommunicationConfig() ;

			LoadModbusConfig() ;
		}
		catch (...)
		{
		}
	}

	void SaveProjectData()
	{
		try
		{
			SaveProjectName() ;

			SaveImageViewConfig() ;

			SaveWorkFlowConfig() ;

			SaveGobalViarentConfig() ;

			SaveCommunicationConfig() ;

			SaveModbusConfig() ;
		}
		catch (...)
		{
		}
	}

	void LoadProjectName()
	{
		USES_CONVERSION ;
		try
		{
			m_mgProject.RemoveAll() ;

			if (!vFileIsExist(m_strProjectPath))
				return ;

			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hReadTuple ;
			OpenFile(W2A(m_strProjectPath),"input_binary",&hFileHandle) ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;

			if ("Project Config" != hReadTuple) return ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			int nRead = hReadTuple ;

			for (int i = 0 ;i < nRead;i++)
			{
				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				m_mgProject.Add((CString)hReadTuple[0].S()) ;
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void SaveProjectName()
	{
		USES_CONVERSION ;
		try
		{
			//开始序列化
			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hSaveTuple;
			OpenFile(W2A(m_strProjectPath),"output_binary",&hFileHandle) ;

			hSaveTuple = "Project Config" ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			hSaveTuple = (int)m_mgProject.GetSize() ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			for (int i = 0 ;i < (int)m_mgProject.GetSize();i++)
			{
				CString strSave = m_mgProject.GetAt(i) ;
				hSaveTuple = W2A(m_mgProject.GetAt(i)) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void LoadCameraConfig()
	{
		USES_CONVERSION ;
		try
		{
			m_mgCamera.cameraNodeList.RemoveAll() ;

			if (!vFileIsExist(m_strCameraPath))
				return ;

			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hReadTuple ;
			OpenFile(W2A(m_strCameraPath),"input_binary",&hFileHandle) ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			if ("Camera Config" != hReadTuple) return ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			int nRead = hReadTuple ;

			for (int i = 0 ;i < nRead ;i++)
			{
				CCameraNode *pCameraNode = new CCameraNode() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->nCameraId = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->strCameraSn = hReadTuple[0].S() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->strCameraTipInfo = hReadTuple[0].S() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->eCameraType = (VISION_TOOLTYPE)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->eCameraConnectType = (CAMERA_CONNECTTYPE)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->eCameraColorType = (CAMERA_COLORTYPE)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->eCameraRotateType = (CAMERA_ROTATE)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->eCameraMirrorType = (CAMERA_MIRROR)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->nImageWidth = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->nImageHeight = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->nSourceImageWidth = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->nSourceImageHeight = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->lExposureTime = (long)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->lGain = (long)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->triggerMode.bTriggerMode = (bool)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->triggerMode.triggerPara.eAcquisitionMode = (CAMERA_ACQUISITION_MODE)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->triggerMode.triggerPara.eTriggerActive = (CAMERA_TRIGGER_ACTIVE)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->triggerMode.triggerPara.eTriggerSource = (CAMERA_TRIGGER_SOURCE)(int)hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCameraNode->triggerMode.triggerPara.lTriggerDelayTime = (long)(int)hReadTuple ;

				switch((int)pCameraNode->eCameraType)
				{
				case E_TOOL_CAMERA_HALCON:
					{
						pCameraNode->mgrDllCameraBaseIm.DllCreateInterface((long)E_TOOL_CAMERA_HALCON,(void **)&pCameraNode->pCameraBase) ;
						break;
					}
				case E_TOOL_CAMERA_BASLER:
					{
						pCameraNode->mgrDllCameraBaseIm.DllCreateInterface((long)E_TOOL_CAMERA_BASLER,(void **)&pCameraNode->pCameraBase) ;
						break;
					}

				default:
					break;
				}

				if (NULL == pCameraNode->pCameraBase)
				{
					AfxMessageBox(_T("加载相机DLL失败")) ;
					//DELETE_POINT(pCameraNode) ;
					//continue ;
				}

				if (E_CAMERA_OK != pCameraNode->pCameraBase->Camera_Init(pCameraNode->strCameraSn,pCameraNode->eCameraConnectType,pCameraNode->eCameraColorType) ||\
					E_CAMERA_OK != pCameraNode->pCameraBase->Camera_GetImageSize(pCameraNode->nSourceImageWidth,pCameraNode->nSourceImageHeight) ||\
					E_CAMERA_OK != pCameraNode->pCameraBase->Camera_SetTriggerMode(pCameraNode->triggerMode))
				{
					AfxMessageBox(_T("相机加载失败")) ;
				}
				else
				{
					pCameraNode->nImageWidth = pCameraNode->nSourceImageWidth ;
					pCameraNode->nImageHeight = pCameraNode->nSourceImageHeight ;
				}

				//添加相机
				m_mgCamera.AddTail(pCameraNode) ;
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void SaveCameraConfig()
	{
		USES_CONVERSION ;
		try
		{
			//开始序列化
			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hSaveTuple;
			OpenFile(W2A(m_strCameraPath),"output_binary",&hFileHandle) ;

			hSaveTuple = "Camera Config" ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			hSaveTuple = m_mgCamera.GetCameraNodeListSize() ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			for (int i = 0 ;i < m_mgCamera.GetCameraNodeListSize();i++)
			{
				CCameraNode *pCameraNode = m_mgCamera.GetCameraNodeById(i) ;

				hSaveTuple = pCameraNode->nCameraId ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = W2A((CString)pCameraNode->strCameraSn.c_str()) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = W2A((CString)pCameraNode->strCameraTipInfo.c_str()) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = (int)pCameraNode->eCameraType ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = (int)pCameraNode->eCameraConnectType ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = (int)pCameraNode->eCameraColorType ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = (int)pCameraNode->eCameraRotateType ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = (int)pCameraNode->eCameraMirrorType ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pCameraNode->nImageWidth ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pCameraNode->nImageHeight ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pCameraNode->nSourceImageWidth ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pCameraNode->nSourceImageHeight ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pCameraNode->lExposureTime ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pCameraNode->lGain ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = (int)pCameraNode->triggerMode.bTriggerMode ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = (int)pCameraNode->triggerMode.triggerPara.eAcquisitionMode ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = (int)pCameraNode->triggerMode.triggerPara.eTriggerActive ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = (int)pCameraNode->triggerMode.triggerPara.eTriggerSource ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pCameraNode->triggerMode.triggerPara.lTriggerDelayTime ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void LoadImageViewConfig()
	{
		USES_CONVERSION ;
		try
		{
			m_mgImageViewDlg.RemoveAll() ;

			CString strImageViewPath = g_sysIni.m_strProjectPath + _T("\\ImageView.cf") ;
			if (!vFileIsExist(strImageViewPath))
				return ;

			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hReadTuple ;
			OpenFile(W2A(strImageViewPath),"input_binary",&hFileHandle) ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			if ("ImageView Config" != hReadTuple) return ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			int nRead = hReadTuple ;

			for (int i = 0 ;i < nRead ;i++)
			{
				CInterfaceImageViewDlg *pInterfaceImageViewDlg = new CInterfaceImageViewDlg() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pInterfaceImageViewDlg->nImageViewDlgID = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pInterfaceImageViewDlg->strImageViewDlgName = hReadTuple[0].S() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pInterfaceImageViewDlg->strConnectWorkFlowName = hReadTuple[0].S() ;

				m_mgImageViewDlg.AddTail(pInterfaceImageViewDlg) ;
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void SaveImageViewConfig()
	{
		USES_CONVERSION ;
		try
		{
			CString strImageViewPath = g_sysIni.m_strProjectPath + _T("\\ImageView.cf") ;

			//开始序列化
			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hSaveTuple;
			OpenFile(W2A(strImageViewPath),"output_binary",&hFileHandle) ;

			hSaveTuple = "ImageView Config" ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			hSaveTuple = m_mgImageViewDlg.GetImageViewDlgListSize() ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			for (int i = 0 ;i < m_mgImageViewDlg.GetImageViewDlgListSize();i++)
			{
				CInterfaceImageViewDlg *pInterfaceImageViewDlg = m_mgImageViewDlg.GetImageViewDlgById(i) ;

				hSaveTuple = pInterfaceImageViewDlg->nImageViewDlgID ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = W2A(pInterfaceImageViewDlg->strImageViewDlgName) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = W2A(pInterfaceImageViewDlg->strConnectWorkFlowName) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void LoadWorkFlowConfig()
	{
		USES_CONVERSION ;
		try
		{
			m_mgWorkFlowDlg.RemoveAll() ;

			CString strWorkFlowPath = g_sysIni.m_strProjectPath + _T("\\WorkFlow.cf") ;
			if (!vFileIsExist(strWorkFlowPath))
				return ;

			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hReadTuple ;
			OpenFile(W2A(strWorkFlowPath),"input_binary",&hFileHandle) ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			if ("WorkFlow Config" != hReadTuple) return ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			int nRead1 = hReadTuple ;

			for (int i = 0 ;i < nRead1 ;i++)
			{
				CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg  = new CInterfaceWorkFlowDlg() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pInterfaceWorkFlowDlg->nWorkFlowDlgID = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pInterfaceWorkFlowDlg->strWorkFlowDlgName = hReadTuple[0].S() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				int nRead2 = hReadTuple ;

				pInterfaceWorkFlowDlg->pWorkFlowDlg          = new CWorkFlowDlg() ;
				pInterfaceWorkFlowDlg->pWorkFlowDlg->m_strWorkFlowDlgName = pInterfaceWorkFlowDlg->strWorkFlowDlgName  ;
				pInterfaceWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.RemoveAll() ;

				for (int j = 0 ;j < nRead2 ;j++)
				{
					CFlowNode *pFlowNode = new CFlowNode() ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					pFlowNode->nFlowNodeID = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					pFlowNode->eFlowNodeType = (VISION_TOOLTYPE)(int)hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					int nRead3 = hReadTuple ;

					for (int k = 0;k < nRead3 ;k++)
					{
						CNodeIn* pNodeIn = new CNodeIn() ;

						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						pNodeIn->eNodeInType = (VISION_DATATYPE)(int)hReadTuple ;

						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						pNodeIn->NodeInLog.nParentTreeNodeID = hReadTuple ;

						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						pNodeIn->NodeInLog.nParentTreeNodeOutID = hReadTuple ;

						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						pNodeIn->NodeInLog.strParentTreeNodeOutName = hReadTuple[0].S() ;

						pFlowNode->treeNode.AddTail(pNodeIn) ;
					}
					pInterfaceWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.AddTail(pFlowNode) ;
				}
				m_mgWorkFlowDlg.AddTail(pInterfaceWorkFlowDlg) ;
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void SaveWorkFlowConfig()
	{
		USES_CONVERSION ;
		try
		{
			CString strWorkFlowPath = g_sysIni.m_strProjectPath + _T("\\WorkFlow.cf") ;

			//开始序列化
			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hSaveTuple;
			OpenFile(W2A(strWorkFlowPath),"output_binary",&hFileHandle) ;

			hSaveTuple = "WorkFlow Config" ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			hSaveTuple = m_mgWorkFlowDlg.GetWorkFlowDlgListSize();
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			for (int i = 0 ;i < m_mgWorkFlowDlg.GetWorkFlowDlgListSize();i++)
			{
				CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg = m_mgWorkFlowDlg.GetWorkFlowDlgById(i) ;

				hSaveTuple = pInterfaceWorkFlowDlg->nWorkFlowDlgID ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = W2A(pInterfaceWorkFlowDlg->strWorkFlowDlgName) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pInterfaceWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeListSize() ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				for (int j = 0 ;j < pInterfaceWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeListSize() ;j++)
				{
					CFlowNode *pFlowNode = pInterfaceWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeById(j) ;

					hSaveTuple = pFlowNode->nFlowNodeID ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = (int)pFlowNode->eFlowNodeType ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = (int)pFlowNode->treeNode.GetSize() ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					for (int k = 0 ;k < (int)pFlowNode->treeNode.GetSize() ;k++)
					{
						CNodeIn* pNodeIn = pFlowNode->treeNode.GetAt(pFlowNode->treeNode.FindIndex(k)) ;

						hSaveTuple = (int)pNodeIn->eNodeInType ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

						hSaveTuple = pNodeIn->NodeInLog.nParentTreeNodeID ; ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

						hSaveTuple = pNodeIn->NodeInLog.nParentTreeNodeOutID ; ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

						hSaveTuple = W2A((CString)pNodeIn->NodeInLog.strParentTreeNodeOutName.c_str()) ; ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
					}
				}
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void LoadGobalViarentConfig()
	{
		USES_CONVERSION ;
		try
		{
			m_mgGobalViarent.RemoveAll() ;

			CString strGobalViarentPath = g_sysIni.m_strProjectPath + _T("\\GobalViarent.cf") ;
			if (!vFileIsExist(strGobalViarentPath))
				return ;

			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hReadTuple ;
			OpenFile(W2A(strGobalViarentPath),"input_binary",&hFileHandle) ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			if ("GobalViarent Config" != hReadTuple) return ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			int nRead = hReadTuple ;

			for (int i = 0 ;i < nRead ;i++)
			{
				CGOBALVIARENT *pGobalViarent = new CGOBALVIARENT() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pGobalViarent->nViarentID = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pGobalViarent->nViarentType = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pGobalViarent->strViarentName = hReadTuple[0].S() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pGobalViarent->strViarentValue = hReadTuple[0].S() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pGobalViarent->strViarentTipInfo = hReadTuple[0].S() ;

				//int;double;string;bool;matrix;2dpos;3dpos;
				switch(pGobalViarent->nViarentType)
				{
				case 0:
					{
						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						pGobalViarent->aViarentValue = (int)hReadTuple ;
						break ;
					}
				case 1:
					{
						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						pGobalViarent->aViarentValue = (double)hReadTuple ;
						break ;
					}
				case 2:
					{
						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						pGobalViarent->aViarentValue = (CString)hReadTuple[0].S() ;
						break ;
					}
				case 3:
					{
						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						pGobalViarent->aViarentValue = (bool)(int)hReadTuple ;
						break ;
					}
				case 4:
					{
						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						pGobalViarent->aViarentValue = (HTuple)hReadTuple ;
						break ;
					}
				case 5:
					{
						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						V2DPoint point2D ;
						point2D.dbX = hReadTuple[0] ;
						point2D.dbY = hReadTuple[1] ;
						pGobalViarent->aViarentValue = (V2DPoint)point2D ;
						break ;
					}
				case 6:
					{
						FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
						DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
						V3DPoint point3D ;
						point3D.dbX = hReadTuple[0] ;
						point3D.dbY = hReadTuple[1] ;
						point3D.dbZ = hReadTuple[2] ;
						pGobalViarent->aViarentValue = (V3DPoint)point3D ;
						break ;
					}
				default:
					break;
				}

				m_mgGobalViarent.AddTail(pGobalViarent) ;
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void SaveGobalViarentConfig()
	{
		USES_CONVERSION ;
		try
		{
			CString strGobalViarentPath = g_sysIni.m_strProjectPath + _T("\\GobalViarent.cf") ;

			//开始序列化
			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hSaveTuple;
			OpenFile(W2A(strGobalViarentPath),"output_binary",&hFileHandle) ;

			hSaveTuple = "GobalViarent Config" ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			hSaveTuple = m_mgGobalViarent.GetGobalViarentListSize();
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			for (int i = 0 ;i < m_mgGobalViarent.GetGobalViarentListSize();i++)
			{
				CGOBALVIARENT *pGobalViarent = m_mgGobalViarent.GetGobalViarentById(i) ;

				hSaveTuple = pGobalViarent->nViarentID ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pGobalViarent->nViarentType ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = W2A(pGobalViarent->strViarentName) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = W2A(pGobalViarent->strViarentValue) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = W2A(pGobalViarent->strViarentTipInfo) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				//int;double;string;bool;matrix;2dpos;3dpos;
				switch(pGobalViarent->nViarentType)
				{
				case 0:
					{
						hSaveTuple = any_cast<int>(pGobalViarent->aViarentValue) ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
						break ;
					}
				case 1:
					{
						hSaveTuple = any_cast<double>(pGobalViarent->aViarentValue) ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
						break ;
					}
				case 2:
					{
						hSaveTuple = W2A(any_cast<CString>(pGobalViarent->aViarentValue)) ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
						break ;
					}
				case 3:
					{
						hSaveTuple = any_cast<bool>(pGobalViarent->aViarentValue) ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
						break ;
					}
				case 4:
					{
						hSaveTuple = any_cast<HTuple>(pGobalViarent->aViarentValue) ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
						break ;
					}
				case 5:
					{
					    V2DPoint point2D = any_cast<V2DPoint>(pGobalViarent->aViarentValue) ;
						hSaveTuple = HTuple() ;
						hSaveTuple[0] = point2D.dbX ;
						hSaveTuple[1] = point2D.dbY ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
						break ;
					}
				case 6:
					{
						V3DPoint point3D = any_cast<V3DPoint>(pGobalViarent->aViarentValue) ;
						hSaveTuple = HTuple() ;
						hSaveTuple[0] = point3D.dbX ;
						hSaveTuple[1] = point3D.dbY ;
						hSaveTuple[2] = point3D.dbZ ;
						SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
						FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
						break ;
					}
				default:
					break;
				}
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void LoadCommunicationConfig()
	{
		USES_CONVERSION ;
		try
		{
			m_mgCommunication.RemoveAll() ;

			if (!vFileIsExist(m_strCommunicationPath))
				return ;

			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hReadTuple ;
			OpenFile(W2A(m_strCommunicationPath),"input_binary",&hFileHandle) ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			if ("Communication Config" != hReadTuple) return ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			int nRead = hReadTuple ;

			for (int i = 0 ;i < nRead ;i++)
			{
				CCommunicationNode *pCommNode = new CCommunicationNode() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCommNode->nCommId = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pCommNode->nCommType = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				CString strCommName(hReadTuple[0].S()) ;
				pCommNode->strCommName = W2A(strCommName) ;

				if (0 == pCommNode->nCommType)
				{
					//串口通信
					COMM232NODE comm232Node ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					CString strPortName(hReadTuple[0].S()) ;
					comm232Node.strPortName = W2A(strPortName) ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					comm232Node.nBaudRate = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					comm232Node.nParity = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					comm232Node.nDataBits = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					comm232Node.nStop = hReadTuple ;

					pCommNode->aCommValue = comm232Node ;

					//初始化Dll
					pCommNode->mgrDllCommuncitionBaseIm.DllCreateInterface((long)E_TOOL_COMMUNICATION_COMM232,(void **)&pCommNode->pCommunicationBase) ;
					if (NULL == pCommNode->pCommunicationBase)
					{
						AfxMessageBox(_T("加载Comm232Dll失败")) ;
					}

					string strComm232Info = m_mgCommunication.GetCommInfo(pCommNode) ;
					if (E_COMM_OK != pCommNode->pCommunicationBase->Comm_Init(strComm232Info))
					{
						AfxMessageBox(_T("Comm232 Init Fail")) ;
					}
				}
				else if (1 == pCommNode->nCommType)
				{
					//网络通信
					COMMSOCKETNODE socketNode ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					socketNode.nSocketType = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					CString strIpAddress(hReadTuple[0].S()) ;
					socketNode.strIpAddress = W2A(strIpAddress) ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					socketNode.uIpPort = (UINT)(int)hReadTuple ;

					pCommNode->aCommValue = socketNode ;

					//初始化Dll
					pCommNode->mgrDllCommuncitionBaseIm.DllCreateInterface((long)E_TOOL_COMMUNICATION_TCPIP,(void **)&pCommNode->pCommunicationBase) ;
					if (NULL == pCommNode->pCommunicationBase)
					{
						AfxMessageBox(_T("加载CommSocketDll失败")) ;
					}

					string strCommSocketInfo = m_mgCommunication.GetCommInfo(pCommNode) ;
					if (E_COMM_OK != pCommNode->pCommunicationBase->Comm_Init(strCommSocketInfo))
					{
						AfxMessageBox(_T("CommSocketDll Init Fail")) ;
					}
				}

				m_mgCommunication.AddTail(pCommNode) ;
			}
			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void SaveCommunicationConfig()
	{
		USES_CONVERSION ;
		try
		{
			//开始序列化
			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hSaveTuple;
			OpenFile(W2A(m_strCommunicationPath),"output_binary",&hFileHandle) ;

			hSaveTuple = "Communication Config" ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			hSaveTuple = m_mgCommunication.GetCommNodeListSize();
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			for (int i = 0 ;i < m_mgCommunication.GetCommNodeListSize();i++)
			{
				CCommunicationNode *pCommNode = m_mgCommunication.GetCommNodeById(i) ;

				hSaveTuple = pCommNode->nCommId ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pCommNode->nCommType ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				CString strCommName(pCommNode->strCommName.c_str()) ;
				hSaveTuple = W2A(strCommName) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				if (0 == pCommNode->nCommType)
				{
					//串口通信
					COMM232NODE comm232Node = any_cast<COMM232NODE>(pCommNode->aCommValue) ;

					CString strPortName(comm232Node.strPortName.c_str()) ;
					hSaveTuple = W2A(strPortName) ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = comm232Node.nBaudRate ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = comm232Node.nParity ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = comm232Node.nDataBits ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = comm232Node.nStop ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
				}
				else if (1 == pCommNode->nCommType)
				{
					//网络通信
					COMMSOCKETNODE commSocketNode = any_cast<COMMSOCKETNODE>(pCommNode->aCommValue) ;

					hSaveTuple = commSocketNode.nSocketType ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					CString strIpAddress(commSocketNode.strIpAddress.c_str()) ;
					hSaveTuple = W2A(strIpAddress) ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = (int)commSocketNode.uIpPort ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
				}
			}

			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void LoadModbusConfig()
	{
		USES_CONVERSION ;
		try
		{
			m_mgModbus.RemoveAll() ;

			if (!vFileIsExist(m_strModbusPath))
				return ;

			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hReadTuple ;
			OpenFile(W2A(m_strModbusPath),"input_binary",&hFileHandle) ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			if ("Modbus Config" != hReadTuple) return ;

			FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
			DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
			int nRead = hReadTuple ;

			for (int i = 0 ;i < nRead ;i++)
			{
				CModbusNode* pModbusNode = new CModbusNode() ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pModbusNode->nModbusID = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				pModbusNode->nModbusType = hReadTuple ;

				FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
				DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
				CString strModbusName(hReadTuple[0].S()) ;
				pModbusNode->strModbusName = W2A(strModbusName) ;

				if (0 == pModbusNode->nModbusType)
				{
					//RtuMaster
					RTUMASTERNODE rtuMasterNode ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuMasterNode.nSlaveID = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					CString strPortName(hReadTuple[0].S()) ;
					rtuMasterNode.strPortName = W2A(strPortName) ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuMasterNode.nBaudRate = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuMasterNode.nParity = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuMasterNode.nDataBits = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuMasterNode.nStop = hReadTuple ;

					pModbusNode->aModbusValue = rtuMasterNode ;

					//初始化Dll
					pModbusNode->mgrDllModbusBaseDllIm.DllCreateInterface((long)E_TOOL_MODBUS_RTUMASTER,(void **)&pModbusNode->pModbusBase) ;
					if (NULL == pModbusNode->pModbusBase)
					{
						AfxMessageBox(_T("加载RtuMasterDll失败")) ;
					}

					string strModbusInfo = m_mgModbus.GetModbusInfo(pModbusNode) ;
					if (E_MODBUS_OK != pModbusNode->pModbusBase->Modbus_Init(strModbusInfo))
					{
						AfxMessageBox(_T("RtuMaster Modbus Init Fail")) ;
					}
				}
				else if (1 == pModbusNode->nModbusType)
				{
					//RtuSlave
					RTUSLAVENODE rtuSlaveNode ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuSlaveNode.nSlaveID = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					CString strPortName(hReadTuple[0].S()) ;
					rtuSlaveNode.strPortName = W2A(strPortName) ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuSlaveNode.nBaudRate = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuSlaveNode.nParity = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuSlaveNode.nDataBits = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					rtuSlaveNode.nStop = hReadTuple ;

					pModbusNode->aModbusValue = rtuSlaveNode ;

					//初始化Dll
					pModbusNode->mgrDllModbusBaseDllIm.DllCreateInterface((long)E_TOOL_MODBUS_RTUSLAVE,(void **)&pModbusNode->pModbusBase) ;
					if (NULL == pModbusNode->pModbusBase)
					{
						AfxMessageBox(_T("加载RtuSlaveDll失败")) ;
					}

					string strModbusInfo = m_mgModbus.GetModbusInfo(pModbusNode) ;
					if (E_MODBUS_OK != pModbusNode->pModbusBase->Modbus_Init(strModbusInfo))
					{
						AfxMessageBox(_T("RtuSlave Modbus Init Fail")) ;
					}
				}
				else if (2 == pModbusNode->nModbusType)
				{
					//TcpMaster
					TCPMASTERNODE tcpMasterNode ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					tcpMasterNode.nSlaveID = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					CString strIpAddress(hReadTuple[0].S()) ;
					tcpMasterNode.strIpAddress = W2A(strIpAddress) ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					tcpMasterNode.uIpPort = (UINT)(int)hReadTuple ;

					pModbusNode->aModbusValue = tcpMasterNode ;

					//初始化Dll
					pModbusNode->mgrDllModbusBaseDllIm.DllCreateInterface((long)E_TOOL_MODBUS_TCPMASTER,(void **)&pModbusNode->pModbusBase) ;
					if (NULL == pModbusNode->pModbusBase)
					{
						AfxMessageBox(_T("加载TcpMasterDll失败")) ;
					}

					string strModbusInfo = m_mgModbus.GetModbusInfo(pModbusNode) ;
					if (E_MODBUS_OK != pModbusNode->pModbusBase->Modbus_Init(strModbusInfo))
					{
						AfxMessageBox(_T("TcpMaster Modbus Init Fail")) ;
					}
				}
				else if (3 == pModbusNode->nModbusType)
				{
					//TcpSlave
					TCPSLAVENODE tcpSlaveNode ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					tcpSlaveNode.nSlaveID = hReadTuple ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					CString strIpAddress(hReadTuple[0].S()) ;
					tcpSlaveNode.strIpAddress = W2A(strIpAddress) ;

					FreadSerializedItem(hFileHandle,&hSerializedItemHandle) ;
					DeserializeTuple(hSerializedItemHandle,&hReadTuple) ;
					tcpSlaveNode.uIpPort = (UINT)(int)hReadTuple ;

					pModbusNode->aModbusValue = tcpSlaveNode ;

					//初始化Dll
					pModbusNode->mgrDllModbusBaseDllIm.DllCreateInterface((long)E_TOOL_MODBUS_TCPSLAVE,(void **)&pModbusNode->pModbusBase) ;
					if (NULL == pModbusNode->pModbusBase)
					{
						AfxMessageBox(_T("加载TcpSlaveDll失败")) ;
					}

					string strModbusInfo = m_mgModbus.GetModbusInfo(pModbusNode) ;
					if (E_MODBUS_OK != pModbusNode->pModbusBase->Modbus_Init(strModbusInfo))
					{
						AfxMessageBox(_T("TcpSlave Modbus Init Fail")) ;
					}
				}

				m_mgModbus.AddTail(pModbusNode) ;
			}
			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	void SaveModbusConfig()
	{
		USES_CONVERSION ;
		try
		{
			//开始序列化
			HTuple hFileHandle,hSerializedItemHandle ;
			HTuple hSaveTuple;
			OpenFile(W2A(m_strModbusPath),"output_binary",&hFileHandle) ;

			hSaveTuple = "Modbus Config" ;
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			hSaveTuple = m_mgModbus.GetModbusNodeListSize();
			SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
			FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

			for (int i = 0 ;i < m_mgModbus.GetModbusNodeListSize();i++)
			{
				CModbusNode *pModbusNode = m_mgModbus.GetModbusNodeById(i) ;

				hSaveTuple = pModbusNode->nModbusID ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				hSaveTuple = pModbusNode->nModbusType ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				CString strModbusName(pModbusNode->strModbusName.c_str()) ;
				hSaveTuple = W2A(strModbusName) ;
				SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
				FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

				if (0 == pModbusNode->nModbusType)
				{
					//RtuMaster
					RTUMASTERNODE rtuMasterNode = any_cast<RTUMASTERNODE>(pModbusNode->aModbusValue) ;

					hSaveTuple = rtuMasterNode.nSlaveID ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					CString strPortName(rtuMasterNode.strPortName.c_str()) ;
					hSaveTuple = W2A(strPortName) ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = rtuMasterNode.nBaudRate ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = rtuMasterNode.nParity ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = rtuMasterNode.nDataBits ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = rtuMasterNode.nStop ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
				}
				else if (1 == pModbusNode->nModbusType)
				{
					//RtuSlave
					RTUSLAVENODE rtuSlaveNode = any_cast<RTUSLAVENODE>(pModbusNode->aModbusValue) ;

					hSaveTuple = rtuSlaveNode.nSlaveID ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					CString strPortName(rtuSlaveNode.strPortName.c_str()) ;
					hSaveTuple = W2A(strPortName) ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = rtuSlaveNode.nBaudRate ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = rtuSlaveNode.nParity ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = rtuSlaveNode.nDataBits ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = rtuSlaveNode.nStop ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
				}
				else if (2 == pModbusNode->nModbusType)
				{
					//TcpMaster
					TCPMASTERNODE tcpMasterNode = any_cast<TCPMASTERNODE>(pModbusNode->aModbusValue) ;

					hSaveTuple = tcpMasterNode.nSlaveID ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					CString strIpAddress(tcpMasterNode.strIpAddress.c_str()) ;
					hSaveTuple = W2A(strIpAddress) ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = (int)tcpMasterNode.uIpPort ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
				}
				else if (3 == pModbusNode->nModbusType)
				{
					//TcpSlave
					TCPSLAVENODE tcpSlaveNode = any_cast<TCPSLAVENODE>(pModbusNode->aModbusValue) ;

					hSaveTuple = tcpSlaveNode.nSlaveID ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					CString strIpAddress(tcpSlaveNode.strIpAddress.c_str()) ;
					hSaveTuple = W2A(strIpAddress) ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;

					hSaveTuple = (int)tcpSlaveNode.uIpPort ;
					SerializeTuple(hSaveTuple,&hSerializedItemHandle) ;
					FwriteSerializedItem(hFileHandle,hSerializedItemHandle) ;
				}
			}
			CloseFile(hFileHandle) ;
		}
		catch (...)
		{
		}
	}

	bool GetInputPara(CFlowNode *pNode,vector<any> &vecInput)
	{
		USES_CONVERSION ;
		try
		{
			if (NULL == pNode)
				return false ;

			vecInput.clear() ;

			int nTreeNodeCount = (int)pNode->treeNode.GetSize() ;
			if (nTreeNodeCount <= 0)
				return false ;

			CNodeIn *pNodeIn ;
			switch((int)pNode->eFlowNodeType)
			{
			case (int)E_TOOL_2DVISION_CAMERA:
				{
					pNodeIn = pNode->treeNode.GetAt(pNode->treeNode.FindIndex(0)) ;
					if(E_VDATA_CAMERA != pNodeIn->eNodeInType)
						return false ;

					int nFind1,nFind2 ;
					string strParentTreeNodeOutName(pNodeIn->NodeInLog.strParentTreeNodeOutName) ;
					nFind1 = (int)strParentTreeNodeOutName.find('D') ;
					nFind2 = (int)strParentTreeNodeOutName.find(':') ;
					if (nFind1 < 0 || nFind2 < 0)
						return false ;

					string strId = strParentTreeNodeOutName.substr(nFind1 + 1,nFind2 - nFind1 - 1) ;
					long lExposureTime,lGain ;
					CCameraNode *pCameraNode = m_mgCamera.GetCameraNodeById(atoi(strId.c_str())) ;

					if (NULL == pCameraNode) return false ;
					pCameraNode->pCameraBase->Camera_GetExposureTime(lExposureTime) ;
					pCameraNode->pCameraBase->Camera_GetGain(lGain) ;

					VString vStrCameraName ;
					vStrCameraName.vStr = pNodeIn->NodeInLog.strParentTreeNodeOutName ;
					vecInput.push_back(vStrCameraName) ;
					vecInput.push_back(lExposureTime) ;
					vecInput.push_back(lGain) ;
					vecInput.push_back(pCameraNode) ;

					break;
				}
			case (int)E_TOOL_2DVISION_SHAPEMODEL:
				{
					break;
				}
			case (int)E_TOOL_2DVISION_FITLINE:
				{
					break;
				}
			case (int)E_TOOL_VISIONSYSTEM_COMMREAD:
				{
					pNodeIn = pNode->treeNode.GetAt(pNode->treeNode.FindIndex(0)) ;
					if(E_VDATA_COMMUNICATION != pNodeIn->eNodeInType)
						return false ;

					int nFind1,nFind2 ;
					string strParentTreeNodeOutName(pNodeIn->NodeInLog.strParentTreeNodeOutName) ;
					nFind1 = (int)strParentTreeNodeOutName.find('D') ;
					nFind2 = (int)strParentTreeNodeOutName.find(':') ;
					if (nFind1 < 0 || nFind2 < 0)
						return false ;

					string strId = strParentTreeNodeOutName.substr(nFind1 + 1,nFind2 - nFind1 - 1) ;
					CCommunicationNode *pCommNode = m_mgCommunication.GetCommNodeById(atoi(strId.c_str())) ;

					if (NULL == pCommNode) return false ;

					VString vStrCommName ;
					vStrCommName.vStr = pNodeIn->NodeInLog.strParentTreeNodeOutName ;
					vecInput.push_back(vStrCommName) ;
					vecInput.push_back(pCommNode) ;

					break ;
				}
			case (int)E_TOOL_VISIONSYSTEM_COMMWRITE:
				{
					pNodeIn = pNode->treeNode.GetAt(pNode->treeNode.FindIndex(0)) ;
					if(E_VDATA_COMMUNICATION != pNodeIn->eNodeInType)
						return false ;

					int nFind1,nFind2 ;
					string strParentTreeNodeOutName(pNodeIn->NodeInLog.strParentTreeNodeOutName) ;
					nFind1 = (int)strParentTreeNodeOutName.find('D') ;
					nFind2 = (int)strParentTreeNodeOutName.find(':') ;
					if (nFind1 < 0 || nFind2 < 0)
						return false ;

					string strId = strParentTreeNodeOutName.substr(nFind1 + 1,nFind2 - nFind1 - 1) ;
					CCommunicationNode *pCommNode = m_mgCommunication.GetCommNodeById(atoi(strId.c_str())) ;

					if (NULL == pCommNode) return false ;

					VString vStrCommName ;
					vStrCommName.vStr = pNodeIn->NodeInLog.strParentTreeNodeOutName ;
					vecInput.push_back(vStrCommName) ;
					vecInput.push_back(pCommNode) ;

					break ;
				}
			default:
				break;
			}
		}
		catch (...)
		{
			return false ;
		}

		return true ;
	}

	bool GetConfigPath(CString strWorkFlowDlgName,CFlowNode *pNode,CString &strPath)
	{
		try
		{
			if (NULL == pNode)
				return false ;

			CString strFolder(_T("")),strName(_T("")) ;
			switch((int)pNode->eFlowNodeType)
			{
			case (int)E_TOOL_2DVISION_CAMERA:
				{
					strName.Format(_T("(ID%d)2D相机"),pNode->nFlowNodeID) ;
					strFolder = g_sysIni.m_strProjectPath  + _T("\\") + strWorkFlowDlgName + _T("\\") + strName + _T("\\2DCamera.vDat") ;
					break;
				}
			case (int)E_TOOL_2DVISION_SHAPEMODEL:
				{
					strName.Format(_T("(ID%d)标准形状模板"),pNode->nFlowNodeID) ;
					strFolder = g_sysIni.m_strProjectPath  + _T("\\") + strWorkFlowDlgName + _T("\\") + strName + _T("\\ShapeModel.vDat") ;
					break;
				}
			case (int)E_TOOL_2DVISION_FITLINE:
				{
					strName.Format(_T("(ID%d)找线"),pNode->nFlowNodeID) ;
					strFolder = g_sysIni.m_strProjectPath  + _T("\\") + strWorkFlowDlgName + _T("\\") + strName + _T("\\FitLine.vDat") ;
					break;
				}
			case (int)E_TOOL_VISIONSYSTEM_COMMREAD:
				{
					strName.Format(_T("(ID%d)通信接收"),pNode->nFlowNodeID) ;
					strFolder = g_sysIni.m_strProjectPath  + _T("\\") + strWorkFlowDlgName + _T("\\") + strName + _T("\\CommRead.vDat") ;
					break;
				}
			case (int)E_TOOL_VISIONSYSTEM_COMMWRITE:
				{
					strName.Format(_T("(ID%d)通信发送"),pNode->nFlowNodeID) ;
					strFolder = g_sysIni.m_strProjectPath  + _T("\\") + strWorkFlowDlgName + _T("\\") + strName + _T("\\CommWrite.vDat") ;
					break;
				}
			default:
				break;
			}

			strPath = strFolder ;
		}
		catch (...)
		{
			return false ;
		}

		return true ;
	}

	void ReleaseProjectData()
	{
		try
		{
			//释放imageViewPage
			int i = 0 ;
			while(m_mgImageViewDlg.GetImageViewDlgListSize() > 0)
			{
				CInterfaceImageViewDlg *pInterfaceImageViewDlg = m_mgImageViewDlg.GetImageViewDlgById(i) ;

				m_mgImageViewDlg.RemoveAtById(i++) ;
			}

			//释放WorkFlowDlg
			i = 0 ;
			while(m_mgWorkFlowDlg.GetWorkFlowDlgListSize() > 0)
			{
				CInterfaceWorkFlowDlg *pInterfaceWorkFlowDlg = m_mgWorkFlowDlg.GetWorkFlowDlgById(i) ;

				//释放
				for (int j = 0 ;j < pInterfaceWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeListSize();j++)
				{
					CFlowNode *pFlowNode = pInterfaceWorkFlowDlg->pWorkFlowDlg->m_ManageFlowNode.GetFlowNodeById(j) ;
					//释放工具包
					if (NULL != pFlowNode->pVisionBase)
					{
						pFlowNode->pVisionBase->Vision_Release() ;

						delete pFlowNode->pVisionBase ;
						pFlowNode->pVisionBase = NULL ;
					}

					//释放关联节点
					for (int k = 0 ;k < pFlowNode->treeNode.GetSize();k++)
					{
						CNodeIn *pNodeIn = pFlowNode->treeNode.GetAt(pFlowNode->treeNode.FindIndex(k)) ;
						if (NULL ==pNodeIn)
						{
							delete pNodeIn ;
							pNodeIn = NULL ;
						}
					}
					pFlowNode->treeNode.RemoveAll() ;

					if (NULL != pFlowNode)
					{
						delete pFlowNode ;
						pFlowNode = NULL ;
					}
				}

				m_mgWorkFlowDlg.RemoveAtById(i++) ;
			}

			//释放GobalViarent
			i = 0 ;
			while(m_mgGobalViarent.GetGobalViarentListSize() > 0)
			{
				CGOBALVIARENT *pGobalViarent = m_mgGobalViarent.GetGobalViarentById(i) ;
				m_mgGobalViarent.RemoveAtById(i++) ;
			}
		}
		catch (...)
		{
		}
	}

	void ReleaseDeviceData()
	{
		try
		{
			ReleaseCameraData() ;

			ReleaseLedData() ;
		}
		catch (...)
		{
		}
	}

	void ReleaseCameraData()
	{
		try
		{
			for (int i = 0 ;i < m_mgCamera.GetCameraNodeListSize();i++)
			{
				CCameraNode *pCameraNode = m_mgCamera.GetCameraNodeById(i) ;

				if (NULL != pCameraNode)
				{
					delete pCameraNode ;
					pCameraNode = NULL ;
				}
			}
		}
		catch (...)
		{
		}
	}

	void ReleaseLedData()
	{
		try
		{
		}
		catch (...)
		{
		}
	}

public:
	//系统根目录
	CString                   m_strRoot ;
	//工程配置目录
	CString                   m_strProjectPath ;
	//相机配置目录
	CString                   m_strCameraPath ;
	//Led配置目录
	CString                   m_strLedPath ;
	//Comm配置目录
	CString                   m_strCommunicationPath ;
	//Modbus配置目录
	CString                   m_strModbusPath ;
	//管理工程
	CStringArray              m_mgProject ;
	//管理workFlowPage
	CManageWorkFlowDlg        m_mgWorkFlowDlg ;
	//管理imageViewPage
	CManageImageViewDlg       m_mgImageViewDlg ;
	//管理GobalViarent
	CManageGobalViarent       m_mgGobalViarent ;
	//管理相机硬件
	CManageCamera             m_mgCamera ;
	//管理通信
	CManageCommunication      m_mgCommunication ;
	//管理Modbus
	CManageModbus             m_mgModbus ;
};

inline bool CheckProjectName(CStringArray &mgProject,CString strProjectName)
{
	try
	{
		int nProjectCount = (int)mgProject.GetSize() ;
		if (nProjectCount <= 0)
			return true ;

		for (int i = 0 ;i < nProjectCount ;i++)
		{
			if (strProjectName == mgProject.GetAt(i))
				return false ;
		}
	}
	catch (...)
	{
		return false ;
	}
	return true ;
}

inline bool CheckImageViewName(CManageImageViewDlg &mgImageViewDlg,CString strName)
{
	try
	{
		int nImageViewCount = mgImageViewDlg.GetImageViewDlgListSize() ;
		if (nImageViewCount <= 0)
			return true ;

		for (int i = 0 ;i < nImageViewCount ;i++)
		{
			if (strName == mgImageViewDlg.GetImageViewDlgById(i)->strImageViewDlgName)
				return false ;
		}
	}
	catch (...)
	{
		return false ;
	}
	return true ;
}

inline bool CheckWorkFlowName(CManageWorkFlowDlg &mgWorkFlowDlg,CString strName)
{
	try
	{
		int nWorkFlowCount = mgWorkFlowDlg.GetWorkFlowDlgListSize() ;
		if (nWorkFlowCount <= 0)
			return true ;

		for (int i = 0 ;i < nWorkFlowCount ;i++)
		{
			if (strName == mgWorkFlowDlg.GetWorkFlowDlgById(i)->strWorkFlowDlgName)
				return false ;
		}
	}
	catch (...)
	{
		return false ;
	}
	return true ;
}