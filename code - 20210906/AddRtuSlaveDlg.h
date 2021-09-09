#pragma once

// CAddRtuSlaveDlg �Ի���

class CAddRtuSlaveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddRtuSlaveDlg)
public:
	CWinXPButtonST m_btnOk;
	CWinXPButtonST m_btnCancel;
	CSkinComboBox m_comboPort;
	CSkinComboBox m_comboBaudRate;
	CSkinComboBox m_comboParity;
	CSkinComboBox m_comboBitsize;
	CSkinComboBox m_comboStopBits;
	UINT          m_uSlaveID;

	RTUSLAVENODE  m_rtuSlaveNode ;
private:
	void InitAllControl() ;
	void InitBtnControl() ;
	void InitComboControl() ;
	void UpdateAllControl() ;
public:
	CAddRtuSlaveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddRtuSlaveDlg();

// �Ի�������
	enum { IDD = IDD_ADD_MODBUS_RTUSLAVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
