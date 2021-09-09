#pragma once

// CPara1Dlg �Ի���

class CPara1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPara1Dlg)
public:
	CProSliderCtrl      m_sliderExposureTime;
	CProSliderCtrl      m_sliderGain;
	long                m_lMinExposureTime ;
	long                m_lMaxExposureTime ;
	long                m_lMinGain ;
	long                m_lMaxGain ;
	long                m_lExposureTime ;
	long                m_lGain ;
protected:
	CBrush              m_brush;

private:
	void InitAllControl() ;
	void InitSliderControl() ;

public:
	void UpdateAllControl() ;

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	CPara1Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPara1Dlg();

// �Ի�������
	enum { IDD = IDD_PARA1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
