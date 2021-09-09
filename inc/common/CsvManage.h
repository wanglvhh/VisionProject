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

	//按时间自动创建csv
	bool CsvCreate(unsigned int nCamID = 0) ;
	//按行读取csv
	Row &CsvReadRow(unsigned int row);
	//按行写入csv,写入到最后一行
	void CsvWriteRow(vector<CString> &) ;
	//按行删除csv
	bool CsvDeleteRow(unsigned int pos);
	//统计行个数
	unsigned int CsvRowCount(void);
	//统计列个数
	unsigned int CsvColumnCount(void);

private:
	string GetCsvFilePath() ;
	void VectorCStringToString(const vector<CString>,vector<string> &) ;
	void ReCsvCreate() ;

private:
	//csv 头
	vector<CString> m_header;
    string m_strCsvPath ;
    Parser *m_pParser ;
	unsigned int m_nCamID;
	unsigned int m_nRowNum ;
};

#endif