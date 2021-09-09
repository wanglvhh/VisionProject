#ifndef    _CSVMANAGE_CPP_
#define    _CSVMANAGE_CPP_

#pragma once

#include "CSVparser.hpp"
using namespace csv ;
# include <vector>
using namespace std ;
#include "vFunc.h"

class CsvManage
{
public:
	CsvManage() ;
	~CsvManage() ;

	//��ʱ���Զ�����csv
	bool CsvCreate(unsigned int nCamID = 0) ;
	//���ж�ȡcsv
	Row &CsvReadRow(unsigned int row);
	//����д��csv,д�뵽���һ��
	void CsvWriteRow(vector<CString> &) ;
	//����ɾ��csv
	bool CsvDeleteRow(unsigned int pos);
	//ͳ���и���
	unsigned int CsvRowCount(void);
	//ͳ���и���
	unsigned int CsvColumnCount(void);

private:
	string GetCsvFilePath() ;
	void VectorCStringToString(const vector<CString>,vector<string> &) ;
	void ReCsvCreate() ;

private:
	//csv ͷ
	vector<CString> m_header;
    string m_strCsvPath ;
    Parser *m_pParser ;
	unsigned int m_nCamID;
	unsigned int m_nRowNum ;
};

#endif