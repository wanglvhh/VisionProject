#pragma once
// CTypeModbusDlg 对话框

class CTypeModbusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTypeModbusDlg)
public:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	int            m_nModbusType;
	CString        m_strModbusName;
private:
	void InitAllControl() ;
	void InitBtnControl() ;

public:
	CTypeModbusDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTypeModbusDlg();

// 对话框数据
	enum { IDD = IDD_TYPE_MODBUS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioClicked(UINT uRadioId) ;
	afx_msg void OnEnChangeEditModbusname();
};
