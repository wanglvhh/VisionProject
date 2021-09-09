#include "stdafx.h"
#include "CsvManage.h"

CsvManage::CsvManage()
{
	m_header.clear() ;

	m_pParser = NULL ;
	m_nRowNum = -1 ;
}

CsvManage::~CsvManage()
{
	m_header.clear() ;
	if (NULL != m_pParser)
	{
		delete m_pParser ;
		m_pParser = NULL ;
	}

	m_nRowNum = -1 ;
}

bool CsvManage::CsvCreate(unsigned int nCamID)
{
	try
	{
		m_nCamID = nCamID ;
		if (0 == nCamID)
		{
			m_header.clear() ;
			m_header.push_back(_T("Time")) ;
			m_header.push_back(_T("ID")) ;
			m_header.push_back(_T("SnCode")) ;
			m_header.push_back(_T("Station")) ;
			m_header.push_back(_T("Status")) ;
			m_header.push_back(_T("X1")) ;
			m_header.push_back(_T("Y1")) ;
			m_header.push_back(_T("U1")) ;
			m_header.push_back(_T("X2")) ;
			m_header.push_back(_T("Y2")) ;
			m_header.push_back(_T("U2")) ;
		}
		else if (1 == nCamID)
		{
		}
		else if (2 == nCamID)
		{
		}
		else
			return false ;

		m_strCsvPath = GetCsvFilePath() ;
		CString strCsvPath(m_strCsvPath.c_str()) ;
		if (!vFileIsExist(strCsvPath))
		{
			//新建一个文件
			HANDLE hFile = CreateFile(strCsvPath, GENERIC_READ | GENERIC_WRITE, (DWORD) 0,\
				NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL);
			if(hFile == INVALID_HANDLE_VALUE)
			{
				return false ;
			}
			CloseHandle(hFile);

			//写入头文件
			vector<string> vecHeader ;
			VectorCStringToString(m_header,vecHeader) ;
			m_pParser =  new Parser(m_strCsvPath,vecHeader);
			m_pParser->setOriginalFile(vecHeader) ;
			//m_pParser->parseHeader() ;
			m_pParser->parseContent() ;
			m_nRowNum = 0 ;
		}
		else
		{
			m_pParser = new Parser(m_strCsvPath) ;
			m_nRowNum = CsvRowCount();
		}

		return true ;
	}
	catch (...)
	{
		return false ;
	}
}

void CsvManage::ReCsvCreate()
{
	try
	{
		m_strCsvPath = GetCsvFilePath() ;
		CString strCsvPath(m_strCsvPath.c_str()) ;
		if (!vFileIsExist(strCsvPath))
		{
			//更新日期重新新建csv
			if (NULL != m_pParser)
			{
				delete m_pParser ;
				m_pParser = NULL ;
			}

			//新建一个文件
			HANDLE hFile = CreateFile(strCsvPath, GENERIC_READ | GENERIC_WRITE, (DWORD) 0,\
				NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL);
			if(hFile == INVALID_HANDLE_VALUE)
			{
				return  ;
			}
			CloseHandle(hFile);

			//写入头文件
			vector<string> vecHeader ;
			VectorCStringToString(m_header,vecHeader) ;
			m_pParser =  new Parser(m_strCsvPath,vecHeader);
			m_pParser->setOriginalFile(vecHeader) ;
			//m_pParser->parseHeader() ;
			m_pParser->parseContent() ;
			m_nRowNum = 0 ;
		}
	}
	catch (...)
	{
	}
}

string CsvManage::GetCsvFilePath()
{
	SYSTEMTIME tm;
	memset(&tm,0,sizeof(tm));
	::GetLocalTime(&tm);
	CString strCsvPath,strDay,strCamFolder ;
	DWORD dwYear,dwMonth,dwDay ;
	DWORD dwHour,dwMinute ,dwSecond;
	dwYear = tm.wYear ;
	dwMonth = tm.wMonth ;
	dwDay = tm.wDay ;
	dwHour = tm.wHour ;
	dwMinute = tm.wMinute ;
	dwSecond = tm.wSecond ;
	strDay.Format(_T("Cam%d------%d-%d-%d.csv"),m_nCamID+1,dwYear,dwMonth,dwDay) ;

	strCsvPath = GetExepath() + _T("CsvLog\\");
	if (!vPathIsExist(strCsvPath))
	{
		CreateDirectory ( strCsvPath, NULL );
	}

	strCamFolder.Format(_T("Cam%d\\"),m_nCamID+1) ;
	strCsvPath += strCamFolder ;
	if (!vPathIsExist(strCsvPath))
	{
		CreateDirectory ( strCsvPath, NULL );
	}

	strCsvPath += strDay ;
	string strPath = CT2A(strCsvPath.GetBuffer()) ;
	return strPath;
}

void CsvManage::VectorCStringToString(const vector<CString> InVec,vector<string> &OutVec)
{
	try
	{
		OutVec.clear() ;

		for (int i = 0 ;i < InVec.size();i++)
		{
			string strConvert = CT2A(InVec.at(i).GetString()) ;
			OutVec.push_back(strConvert) ;
		}
	}
	catch (...)
	{
	}
}

Row &CsvManage::CsvReadRow(unsigned int row)
{
	try
	{
		ReCsvCreate() ;

		/*if (row <= m_nRowNum)
		{
		}*/
		////更新所有信息
		//if (NULL != m_pParser)
		//{
		//	delete m_pParser ;
		//	m_pParser = NULL ;
		//}
		//CsvCreate(m_nCamID) ;
	}
	catch (...)
	{
	}

	return m_pParser->getRow(row) ;
}

void CsvManage::CsvWriteRow(vector<CString> &vecWrite)
{
	try
	{
		ReCsvCreate() ;

		////更新所有信息
		//if (NULL != m_pParser)
		//{
		//	delete m_pParser ;
		//	m_pParser = NULL ;
		//}
		//CsvCreate(m_nCamID) ;
		m_nRowNum = CsvRowCount() ;

		vector<string> vecConvert ;
		VectorCStringToString(vecWrite,vecConvert) ;
		m_pParser->addRow(m_nRowNum,vecConvert) ;
		m_pParser->sync() ;
	}
	catch (...)
	{
	}
}

bool CsvManage::CsvDeleteRow(unsigned int pos)
{
	try
	{
		ReCsvCreate() ;

		return m_pParser->deleteRow(pos) ;
	}
	catch (...)
	{
		return false ;
	}
}

unsigned int CsvManage::CsvRowCount(void)
{
	ReCsvCreate() ;

	if (m_pParser)
	{
		return m_pParser->rowCount() ;
	}
	return 0 ;
}

unsigned int CsvManage::CsvColumnCount(void)
{
	ReCsvCreate() ;

	if (m_pParser)
	{
		return m_pParser->columnCount() ;
	}
	return 0 ;
}