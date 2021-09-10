#pragma once

// CImageViewDlg 对话框

class CImageViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageViewDlg)
	DECLARE_EASYSIZE
public:
	HTuple                m_lWindowID ;
	HObject              m_hImage ;
	CMyStatic           m_ctlImageView;
	CLabelEx              m_labelRow;
	CLabelEx              m_labelCol;
	CLabelEx              m_labelGray;
	double                m_dbRatioWh ;
	int                      m_nImageWidth ;
	int                    m_nImageHeight ;

	bool                  m_bDraw;
	HTuple                m_hRowB ;
	HTuple                m_hColB ;
	HTuple                m_hRowE ;
	HTuple                m_hColE;
	BOOL                  m_bScale ;
	BOOL                  m_bMoveImg ;
	bool                  m_bMoveState;
	CAMERA_ROTATE         m_eRotateType ;
	CAMERA_MIRROR         m_eMirrorType ;

public:
	void InitViewControl(int nImageWidth = 2592,int nImageHeight = 1944) ;
	void InitLabelControl() ;
	void DispImage(HObject hImage) ;
	void SetImage(HObject hImage) ;
private:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	LRESULT OnLBtnDown(WPARAM   wParam,   LPARAM   lParam) ;
	LRESULT OnLBtnUp(WPARAM   wParam,   LPARAM   lParam) ;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	CImageViewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CImageViewDlg();

// 对话框数据
	enum { IDD = IDD_IMAGEVIEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnImagefit();
	afx_msg void OnImagemove();
};

//ImageViewDlg对话框元素
class CInterfaceImageViewDlg:public CObject
{
public:
	CInterfaceImageViewDlg()
	{
		nImageViewDlgID           = -1 ;
		strImageViewDlgName       = _T("") ;
		strConnectWorkFlowName    = _T("") ;
		pImageViewDlg             = NULL ;
	}

	virtual ~CInterfaceImageViewDlg()
	{
		nImageViewDlgID           = -1 ;
		strImageViewDlgName       = _T("") ;
		strConnectWorkFlowName    = _T("") ;
		pImageViewDlg             = NULL ;
	}

	CInterfaceImageViewDlg & operator=(const CInterfaceImageViewDlg &src)
	{
		if ( this == &src )
			return *this;

		nImageViewDlgID           = src.nImageViewDlgID ;
		strImageViewDlgName       = src.strImageViewDlgName ;
		strConnectWorkFlowName    = src.strConnectWorkFlowName ;
		pImageViewDlg             = src.pImageViewDlg ;

		return *this;
	}

public:
	int              nImageViewDlgID ;
	CString          strImageViewDlgName ;
	CString          strConnectWorkFlowName ;
	CImageViewDlg    *pImageViewDlg ;
};

//对外接口ImageViewDlg数据链表
typedef CTypedPtrList<CObList, CInterfaceImageViewDlg *> InterfaceImageViewDlgList;

//管理ImageViewDlg
class CManageImageViewDlg
{
public:
	CManageImageViewDlg()
	{
		imageViewDlgList.RemoveAll() ;
	}

	~CManageImageViewDlg()
	{
		imageViewDlgList.RemoveAll() ;
	}

	int GetImageViewDlgListSize()
	{
		return (int)imageViewDlgList.GetSize() ;
	}

	void AddTail(CInterfaceImageViewDlg *pNewImageViewDlg)
	{
		imageViewDlgList.AddTail(pNewImageViewDlg) ;
	}

	void RemoveAtByName(CString strImageViewDlgName)
	{
		if (GetImageViewDlgListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = imageViewDlgList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CInterfaceImageViewDlg *pImageDlg = imageViewDlgList.GetNext(pos) ;
			if (strImageViewDlgName == pImageDlg->strImageViewDlgName)
			{
				imageViewDlgList.RemoveAt(prev) ;
				DELETE_POINT(pImageDlg) ;

				break;
			}
		}
	}

	void RemoveAtById(int nImageViewDlgID)
	{
		if (GetImageViewDlgListSize() <= 0)
		{
			return  ;
		}

		POSITION prev;
		POSITION pos = imageViewDlgList.GetHeadPosition() ;
		while(pos)
		{
			prev = pos ;
			CInterfaceImageViewDlg *pImageDlg = imageViewDlgList.GetNext(pos) ;
			if (nImageViewDlgID == pImageDlg->nImageViewDlgID)
			{
				imageViewDlgList.RemoveAt(prev) ;
				DELETE_POINT(pImageDlg->pImageViewDlg) ;
				DELETE_POINT(pImageDlg) ;

				break;
			}
		}
	}

	void RemoveAll()
	{
		imageViewDlgList.RemoveAll() ;
	}

	void ReSortById()
	{
		if (GetImageViewDlgListSize() <= 0)
		{
			return  ;
		}

		int nIndex = 0 ;
		POSITION pos = imageViewDlgList.GetHeadPosition() ;
		while(pos)
		{
			CInterfaceImageViewDlg *pImageDlg = imageViewDlgList.GetNext(pos) ;
			pImageDlg->nImageViewDlgID = nIndex++ ;
		}
	}

	CInterfaceImageViewDlg* GetImageViewDlgByName(CString strImageViewDlgName)
	{
		if (GetImageViewDlgListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = imageViewDlgList.GetHeadPosition() ;
		while(pos)
		{
			CInterfaceImageViewDlg *pImageDlg = imageViewDlgList.GetNext(pos) ;
			if (strImageViewDlgName == pImageDlg->strImageViewDlgName)
			{
				return pImageDlg ;
				//break;
			}
		}

		return NULL ;
	}

	CInterfaceImageViewDlg* GetImageViewDlgById(int nImageViewDlgID)
	{
		if (GetImageViewDlgListSize() <= 0)
		{
			return NULL ;
		}

		POSITION pos = imageViewDlgList.GetHeadPosition() ;
		while(pos)
		{
			CInterfaceImageViewDlg *pImageDlg = imageViewDlgList.GetNext(pos) ;
			if (nImageViewDlgID == pImageDlg->nImageViewDlgID)
			{
				return pImageDlg ;
			}
		}

		return NULL ;
	}

public:
	InterfaceImageViewDlgList imageViewDlgList ;
};