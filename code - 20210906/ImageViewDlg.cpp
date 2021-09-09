// ImageViewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VisionProject.h"
#include "ImageViewDlg.h"
#include "afxdialogex.h"

// CImageViewDlg 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CImageViewDlg, CDialogEx)

CImageViewDlg::CImageViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageViewDlg::IDD, pParent)
{
	m_bMoveState = false;
	m_bDraw = false;
	m_bScale = true ;
	m_bMoveImg = true ;
	m_eRotateType = E_CAMERA_ROTATE_0 ;
	m_eMirrorType = E_CAMERA_MIRROR_NONE ;
}

CImageViewDlg::~CImageViewDlg()
{
	HalconCpp::CloseWindow(m_lWindowID) ;
}

void CImageViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_ctlImageView);
	DDX_Control(pDX, IDC_STATIC_ROW, m_labelRow);
	DDX_Control(pDX, IDC_STATIC_COL, m_labelCol);
	DDX_Control(pDX, IDC_STATIC_GRAY, m_labelGray);
}

BEGIN_MESSAGE_MAP(CImageViewDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_CONTEXTMENU()
	ON_MESSAGE(WM_LBTNDOWN,OnLBtnDown)
	ON_MESSAGE(WM_LBTNUP,OnLBtnUp)
	ON_COMMAND(ID_IMAGEFIT, &CImageViewDlg::OnImagefit)
	ON_COMMAND(ID_IMAGEMOVE, &CImageViewDlg::OnImagemove)
	ON_WM_SIZING()
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CImageViewDlg)
	/*
	left、top、right、bottom分别指的是该控件左、上、右、下方的控件的ID，也可以为以下特殊值：
	ES_BORDER：保持与边框距离不变
	ES_KEEPSIZE：保持大小不变
	所放位置：
	left -- 表示和right指定的控件右对齐
	right -- 表示和left指定的控件左对齐
	top -- 表示和bottom指定的控件上对齐
	bottom -- 表示和top指定的控件下对齐
	options可指定为0，也可指定为以下值：
	ES_HCENTER：保持宽度不变，水平位置在left和right指定的控件正中间
	ES_VCENTER：保持高度不变，垂直位置在left和right指定的控件正中间
	*/
	EASYSIZE(IDC_STATIC_VIEW,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_STATIC_ROW,ES_BORDER,IDC_STATIC_VIEW,IDC_STATIC_COL,ES_BORDER,0)
	EASYSIZE(IDC_STATIC_COL,IDC_STATIC_ROW,IDC_STATIC_VIEW,IDC_STATIC_GRAY,ES_BORDER,0)
	EASYSIZE(IDC_STATIC_GRAY,IDC_STATIC_COL,IDC_STATIC_VIEW,ES_BORDER,ES_BORDER,0)

END_EASYSIZE_MAP
// CImageViewDlg 消息处理程序

BOOL CImageViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	INIT_EASYSIZE;

	InitLabelControl() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CImageViewDlg::InitViewControl(int nImageWidth,int nImageHeight)
{
	try
	{
		long lWindowID=0;
		CRect Rect;
		int nCtrlWidth,nCtrlHeight ;

		m_ctlImageView.GetClientRect(Rect);
		if(Rect.IsRectEmpty()) return ;
		nCtrlWidth =Rect.Width();
		nCtrlHeight=Rect.Height();
		m_dbRatioWh = (double)nCtrlWidth/(double)nCtrlHeight ;
		m_nImageWidth = nImageWidth ;
		m_nImageHeight = nImageHeight ;
		lWindowID = (long)m_ctlImageView.GetSafeHwnd();
		InitStaticView(lWindowID,m_eRotateType,nCtrlWidth,nCtrlHeight,nImageWidth,nImageHeight,m_dbRatioWh,&m_lWindowID) ;
	}
	catch (...)
	{
	}
}

void CImageViewDlg::InitLabelControl()
{
	try
	{
		m_labelRow.SetWindowText(_T("Row:0")) ;
		m_labelCol.SetWindowText(_T("Col:0")) ;
		m_labelGray.SetWindowText(_T("Gray:0")) ;
		/*m_labelRow.SetAlignTextCM();
		m_labelRow.SetColorBkg(255,0,0,0);
		m_labelRow.SetColorBorder(255,0,0,0);
		m_labelRow.SetColorText(255,RGB(0,255,0)) ;
		m_labelRow.SetSizeText(10) ;
		m_labelRow.SetText(_T("Row:0")) ;

		m_labelCol.SetAlignTextCM();
		m_labelCol.SetColorBkg(255,0,0,0);
		m_labelCol.SetColorBorder(255,0,0,0);
		m_labelCol.SetColorText(255,RGB(0,255,0)) ;
		m_labelCol.SetSizeText(10) ;
		m_labelCol.SetText(_T("Col:0")) ;

		m_labelGray.SetAlignTextCM();
		m_labelGray.SetColorBkg(255,0,0,0);
		m_labelGray.SetColorBorder(255,0,0,0);
		m_labelGray.SetColorText(255,RGB(0,255,0)) ;
		m_labelGray.SetSizeText(10) ;
		m_labelGray.SetText(_T("Gray:0")) ;*/
	}
	catch (...)
	{
	}
}

void CImageViewDlg::DispImage(HObject hImage)
{
	try
	{
		m_hImage = hImage ;
		DispObj(hImage,m_lWindowID) ;
		DispCrossLineInWindow(m_lWindowID,m_eRotateType,m_nImageWidth,m_nImageHeight,m_dbRatioWh) ;
	}
	catch (...)
	{
	}
}

void CImageViewDlg::SetImage(HObject hImage)
{
	try
	{
		if (hImage.Key() != NULL)
		{
			m_hImage.Clear() ;
			m_hImage = hImage ;
		}
	}
	catch (...)
	{
	}
}

void CImageViewDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	UPDATE_EASYSIZE;
}

void CImageViewDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	//EASYSIZE_MINSIZE(400, 300, fwSide, pRect);
}

void CImageViewDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	try
	{
		if (m_bDraw)
			return ;

		CRect rect;
		GetDlgItem(IDC_STATIC_VIEW)->GetWindowRect( &rect );
		if (point.x> rect.right || point.x<rect.left ||
			point.y<rect.top ||point.y > rect.bottom )
			return ;

		CMenu menu,*pSubMenu;
		menu.LoadMenu(IDR_MENU_IMAGEPOP);
		pSubMenu = menu.GetSubMenu(0);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}
	catch (...)
	{
	}
}

BOOL  CImageViewDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (m_bDraw)
		return -1;

	try
	{
		if (m_bScale)
		{
			if (zDelta > 0)
			{
				HTuple Zoom,ZoomOrg, ZoomTrans, Row, Col , RowShif, ColShif;
				HTuple  Row0, Column0, Row00, Column00, Ht, Wt, r1, c1;
				HTuple  r2, c2,Button;
				Zoom = 1.0;
				ZoomOrg = 1.0;
				ZoomTrans = 1.0;

				try
				{
					SetCheck("~give_error");
					GetMposition(m_lWindowID, &Row, &Col, &Button);
					if (Row.Length() < 1)
						return CDialog::OnMouseWheel(nFlags, zDelta, pt);

					if (0 != (Zoom>=32.0))
					{
						Zoom = 32.0;
					}
					else
					{
						Zoom = 1.0+Zoom;
					}

					ZoomTrans = Zoom/ZoomOrg;
					ZoomOrg = Zoom;
					RowShif = 0;
					ColShif = 0;
					GetPart(m_lWindowID, &Row0, &Column0, &Row00, &Column00);
					Ht = Row00-Row0;
					Wt = Column00-Column0;
					r1 = (Row0+((1-(1.0/ZoomTrans))*(Row-Row0)))-(RowShif/ZoomTrans);
					c1 = (Column0+((1-(1.0/ZoomTrans))*(Col-Column0)))-(ColShif/ZoomTrans);
					r2 = r1+(Ht/ZoomTrans);
					c2 = c1+(Wt/ZoomTrans);
					SetPart(m_lWindowID, r1, c1, r2, c2);
					ClearWindow(m_lWindowID) ;

					if (m_hImage.Key() != NULL)
					{
						DispImage(m_hImage) ;
						//DispObj(m_hImage,m_lWindowID);
					}

					//DispCrossLineInWindow(m_lWindowID,m_nImageWidth,m_nImageHeight,m_eRotateType) ;

					WaitSeconds(0.3) ;
				}
				catch (...)
				{
				}
			}
			else if (zDelta < 0)
			{
				HTuple Zoom,ZoomOrg, ZoomTrans, Row, Col , RowShif, ColShif;
				HTuple  Row0, Column0, Row00, Column00, Ht, Wt, r1, c1;
				HTuple  r2, c2,Button;
				Zoom = 1.0;
				ZoomOrg = 1.0;
				ZoomTrans = 1.0;

				try
				{
					SetCheck("~give_error");
					GetMposition(m_lWindowID, &Row, &Col, &Button);

					if (Row.Length() < 1)
						return CDialog::OnMouseWheel(nFlags, zDelta, pt);

					if (0 != (Zoom<=(1.0/16)))
					{
						Zoom = 1.0/16;
					}
					else
					{
						Zoom = Zoom/2;
					}

					ZoomTrans = Zoom/ZoomOrg;
					ZoomOrg = Zoom;
					RowShif = 0;
					ColShif = 0;
					GetPart(m_lWindowID, &Row0, &Column0, &Row00, &Column00);
					Ht = Row00-Row0;
					Wt = Column00-Column0;
					r1 = (Row0+((1-(1.0/ZoomTrans))*(Row-Row0)))-(RowShif/ZoomTrans);
					c1 = (Column0+((1-(1.0/ZoomTrans))*(Col-Column0)))-(ColShif/ZoomTrans);
					r2 = r1+(Ht/ZoomTrans);
					c2 = c1+(Wt/ZoomTrans);
					SetPart(m_lWindowID, r1, c1, r2, c2);
					ClearWindow(m_lWindowID);

					if (m_hImage.Key() != NULL)
					{
						DispImage(m_hImage) ;
						//DispObj(m_hImage,m_lWindowID);
					}

					//DispCrossLineInWindow(m_lWindowID,m_nImageWidth,m_nImageHeight) ;

					WaitSeconds(0.3);
				}
				catch (...)
				{
				}
			}
		}
	}
	catch (...)
	{
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

LRESULT  CImageViewDlg::OnLBtnDown(WPARAM   wParam,   LPARAM   lParam)
{
	try
	{
		if (m_bDraw)
			return -1;

		if (m_bMoveImg)
		{
			CPoint point;
			GetCursorPos(&point);
			ScreenToClient(&point);
			CWnd *hControlWnd = (CWnd *)ChildWindowFromPoint(point);
			long nID = hControlWnd->GetDlgCtrlID();

			HTuple Button ;
			try
			{
				SetCheck("~give_error");
				GetMposition(m_lWindowID, &m_hRowB, &m_hColB, &Button);
			}
			catch(...)
			{
			}
		}
	}
	catch (...)
	{
	}

	return 0L ;
}

LRESULT  CImageViewDlg::OnLBtnUp(WPARAM   wParam,   LPARAM   lParam)
{
	try
	{
		if (m_bDraw)
			return -1;

		if (m_bMoveImg)
		{
			CPoint point;
			GetCursorPos(&point);
			ScreenToClient(&point);
			CWnd *hControlWnd = (CWnd *)ChildWindowFromPoint(point);
			long nID = hControlWnd->GetDlgCtrlID();

			HTuple Button ;
			HTuple row1,col1,row2,col2 ;
			try
			{
				SetCheck("~give_error");
				GetMposition(m_lWindowID, &m_hRowE, &m_hColE, &Button);

				if (m_hRowE.Length() < 1)
					return 0L ;

				if (m_hRowB.Length() < 1)
					return 0L ;

				double dbRowMove,dbColMove ;
				double dbRowB,dbColB,dbRowE,dbColE ;
				dbRowB = m_hRowB[0].D() ;
				dbRowE = m_hRowE[0].D() ;
				dbColB = m_hColB[0].D() ;
				dbColE = m_hColE[0].D() ;
				dbRowMove = -dbRowE + dbRowB ;
				dbColMove = -dbColE + dbColB ;

				GetPart(m_lWindowID,&row1,&col1,&row2,&col2) ;
				SetPart(m_lWindowID,row1+dbRowMove,col1+dbColMove,row2+dbRowMove,col2+dbColMove) ;
				ClearWindow(m_lWindowID) ;

				if (m_hImage.Key() != NULL)
				{
					DispImage(m_hImage) ;
					//DispObj(m_hImage,m_lWindowID);
				}

				//DispCrossLineInWindow(m_lWindowID,m_nImageWidth,m_nImageHeight,m_eRotateType) ;

				WaitSeconds(0.3);
			}
			catch(HException &except)
			{
			}
		}
	}
	catch (...)
	{
	}

	return 0L ;
}

void CImageViewDlg::OnImagefit()
{
	if (m_bDraw)
		return ;
	try
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);
		CWnd *hControlWnd = (CWnd *)ChildWindowFromPoint(point);
		long nID = hControlWnd->GetDlgCtrlID();

		m_bMoveImg = false ;

		//SetPart(m_lWindowID,0,0,m_nImageHeight - 1,m_nImageWidth - 1) ;
		ReSetPart(m_lWindowID,m_eRotateType,m_nImageWidth,m_nImageHeight,m_dbRatioWh) ;
		ClearWindow(m_lWindowID) ;

		if (m_hImage.Key() != NULL)
		{
			DispImage(m_hImage) ;
			//DispObj(m_hImage,m_lWindowID);
		}
		//DispCrossLineInWindow(m_lWindowID,m_nImageWidth,m_nImageHeight,m_eRotateType) ;

		m_bScale = true ;
	}
	catch (...)
	{
	}
}

void CImageViewDlg::OnImagemove()
{
	if (m_bDraw)
		return ;
	try
	{
		m_bMoveImg = true ;
	}
	catch (...)
	{
	}
}