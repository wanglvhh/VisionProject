#pragma once
#include "HardWareData.h"
#include "halconcpp.h"
using namespace HalconCpp;

inline void disp_message (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem,
	HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)
{
	// Local iconic variables

	// Local control variables
	HTuple  hv_GenParamName, hv_GenParamValue;

	//This procedure displays text in a graphics window.
	//
	//Input parameters:
	//WindowHandle: The WindowHandle of the graphics window, where
	//   the message should be displayed
	//String: A tuple of strings containing the text message to be displayed
	//CoordSystem: If set to 'window', the text position is given
	//   with respect to the window coordinate system.
	//   If set to 'image', image coordinates are used.
	//   (This may be useful in zoomed images.)
	//Row: The row coordinate of the desired text position
	//   A tuple of values is allowed to display text at different
	//   positions.
	//Column: The column coordinate of the desired text position
	//   A tuple of values is allowed to display text at different
	//   positions.
	//Color: defines the color of the text as string.
	//   If set to [], '' or 'auto' the currently set color is used.
	//   If a tuple of strings is passed, the colors are used cyclically...
	//   - if |Row| == |Column| == 1: for each new textline
	//   = else for each text position.
	//Box: If Box[0] is set to 'true', the text is written within an orange box.
	//     If set to' false', no box is displayed.
	//     If set to a color string (e.g. 'white', '#FF00CC', etc.),
	//       the text is written in a box of that color.
	//     An optional second value for Box (Box[1]) controls if a shadow is displayed:
	//       'true' -> display a shadow in a default color
	//       'false' -> display no shadow
	//       otherwise -> use given string as color string for the shadow color
	//
	//It is possible to display multiple text strings in a single call.
	//In this case, some restrictions apply:
	//- Multiple text positions can be defined by specifying a tuple
	//  with multiple Row and/or Column coordinates, i.e.:
	//  - |Row| == n, |Column| == n
	//  - |Row| == n, |Column| == 1
	//  - |Row| == 1, |Column| == n
	//- If |Row| == |Column| == 1,
	//  each element of String is display in a new textline.
	//- If multiple positions or specified, the number of Strings
	//  must match the number of positions, i.e.:
	//  - Either |String| == n (each string is displayed at the
	//                          corresponding position),
	//  - or     |String| == 1 (The string is displayed n times).
	//
	//
	//Convert the parameters for disp_text.
	if (0 != (HTuple(hv_Row==HTuple()).TupleOr(hv_Column==HTuple())))
	{
		return;
	}
	if (0 != (hv_Row==-1))
	{
		hv_Row = 12;
	}
	if (0 != (hv_Column==-1))
	{
		hv_Column = 12;
	}
	//
	//Convert the parameter Box to generic parameters.
	hv_GenParamName = HTuple();
	hv_GenParamValue = HTuple();
	if (0 != ((hv_Box.TupleLength())>0))
	{
		if (0 != (HTuple(hv_Box[0])==HTuple("false")))
		{
			//Display no box
			hv_GenParamName = hv_GenParamName.TupleConcat("box");
			hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
		}
		else if (0 != (HTuple(hv_Box[0])!=HTuple("true")))
		{
			//Set a color other than the default.
			hv_GenParamName = hv_GenParamName.TupleConcat("box_color");
			hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[0]));
		}
	}
	if (0 != ((hv_Box.TupleLength())>1))
	{
		if (0 != (HTuple(hv_Box[1])==HTuple("false")))
		{
			//Display no shadow.
			hv_GenParamName = hv_GenParamName.TupleConcat("shadow");
			hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
		}
		else if (0 != (HTuple(hv_Box[1])!=HTuple("true")))
		{
			//Set a shadow color other than the default.
			hv_GenParamName = hv_GenParamName.TupleConcat("shadow_color");
			hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[1]));
		}
	}
	//Restore default CoordSystem behavior.
	if (0 != (hv_CoordSystem!=HTuple("window")))
	{
		hv_CoordSystem = "image";
	}
	//
	if (0 != (hv_Color==HTuple("")))
	{
		//disp_text does not accept an empty string for Color.
		hv_Color = HTuple();
	}
	//
	DispText(hv_WindowHandle, hv_String, hv_CoordSystem, hv_Row, hv_Column, hv_Color,
		hv_GenParamName, hv_GenParamValue);
	return;
}

inline void dev_resize_window_fit_size (HTuple hv_Row, HTuple hv_Column, HTuple hv_Width,
	HTuple hv_Height, HTuple hv_WidthLimit, HTuple hv_HeightLimit)
{
	// Local iconic variables

	// Local control variables
	HTuple  hv_MinWidth, hv_MaxWidth, hv_MinHeight;
	HTuple  hv_MaxHeight, hv_ResizeFactor, hv_TempWidth, hv_TempHeight;
	HTuple  hv_WindowWidth, hv_WindowHeight;

	//This procedure adjusts the size of the current window
	//such that it fits into the limits specified by WidthLimit
	//and HeightLimit, but also maintains the correct aspect ratio
	//given by Width and Height.
	//
	//If it is impossible to match the minimum and maximum extent requirements
	//at the same time (f.e. if the image is very long but narrow),
	//the maximum value gets a higher priority.
	//
	//Parse input tuple WidthLimit
	if (0 != (HTuple((hv_WidthLimit.TupleLength())==0).TupleOr(hv_WidthLimit<0)))
	{
		hv_MinWidth = 500;
		hv_MaxWidth = 800;
	}
	else if (0 != ((hv_WidthLimit.TupleLength())==1))
	{
		hv_MinWidth = 0;
		hv_MaxWidth = hv_WidthLimit;
	}
	else
	{
		hv_MinWidth = ((const HTuple&)hv_WidthLimit)[0];
		hv_MaxWidth = ((const HTuple&)hv_WidthLimit)[1];
	}
	//Parse input tuple HeightLimit
	if (0 != (HTuple((hv_HeightLimit.TupleLength())==0).TupleOr(hv_HeightLimit<0)))
	{
		hv_MinHeight = 400;
		hv_MaxHeight = 600;
	}
	else if (0 != ((hv_HeightLimit.TupleLength())==1))
	{
		hv_MinHeight = 0;
		hv_MaxHeight = hv_HeightLimit;
	}
	else
	{
		hv_MinHeight = ((const HTuple&)hv_HeightLimit)[0];
		hv_MaxHeight = ((const HTuple&)hv_HeightLimit)[1];
	}
	//
	//Test, if window size has to be changed.
	hv_ResizeFactor = 1;
	//First, expand window to the minimum extents (if necessary).
	if (0 != (HTuple(hv_MinWidth>hv_Width).TupleOr(hv_MinHeight>hv_Height)))
	{
		hv_ResizeFactor = (((hv_MinWidth.TupleReal())/hv_Width).TupleConcat((hv_MinHeight.TupleReal())/hv_Height)).TupleMax();
	}
	hv_TempWidth = hv_Width*hv_ResizeFactor;
	hv_TempHeight = hv_Height*hv_ResizeFactor;
	//Then, shrink window to maximum extents (if necessary).
	if (0 != (HTuple(hv_MaxWidth<hv_TempWidth).TupleOr(hv_MaxHeight<hv_TempHeight)))
	{
		hv_ResizeFactor = hv_ResizeFactor*((((hv_MaxWidth.TupleReal())/hv_TempWidth).TupleConcat((hv_MaxHeight.TupleReal())/hv_TempHeight)).TupleMin());
	}
	hv_WindowWidth = hv_Width*hv_ResizeFactor;
	hv_WindowHeight = hv_Height*hv_ResizeFactor;
	//Resize window
	if (HDevWindowStack::IsOpen())
		SetWindowExtents(HDevWindowStack::GetActive(),hv_Row, hv_Column, hv_WindowWidth,
		hv_WindowHeight);
	if (HDevWindowStack::IsOpen())
		SetPart(HDevWindowStack::GetActive(),0, 0, hv_Height-1, hv_Width-1);
	return;
}

inline void DispCrossLineInWindow(HTuple hInWindowID,CAMERA_ROTATE eRotateType,int nInImageWidth,int nInImageHeight,double dbRatioWh)
{
	try
	{
		SetColor(hInWindowID,"green") ;

		double dbImgOffset ;
		if ((double)nInImageWidth/(double)nInImageHeight > dbRatioWh)
		{
			dbImgOffset = (double)nInImageWidth / dbRatioWh / 2 - (double)nInImageHeight / 2;

			DispLine(hInWindowID,(nInImageHeight-1)/2 ,0,(nInImageHeight-1)/2 ,nInImageWidth - 1) ;
			DispLine(hInWindowID,0,(nInImageWidth - 1)/2,nInImageHeight-1,(nInImageWidth - 1)/2) ;
		}
		else
		{
			dbImgOffset = (double)nInImageHeight * dbRatioWh / 2 - (double)nInImageWidth / 2;

			DispLine(hInWindowID,(nInImageHeight-1)/2 ,0,(nInImageHeight-1)/2 ,nInImageWidth - 1) ;
			DispLine(hInWindowID,0,(nInImageWidth - 1)/2,nInImageHeight-1,(nInImageWidth - 1)/2) ;
		}
		/*if (E_CAMERA_ROTATE_90 == eRotateType || E_CAMERA_ROTATE_270 == eRotateType)
		{
		if ((double) nInImageHeight/ (double) nInImageWidth > dbRatioWh)
		{
		dbImgOffset = (double)nInImageHeight / dbRatioWh / 2 - (double)nInImageWidth / 2;

		DispLine(hInWindowID,(nInImageWidth-1)/2 ,0,(nInImageWidth-1)/2 ,nInImageHeight  - 1) ;
		DispLine(hInWindowID,0,(nInImageHeight - 1)/2,nInImageWidth-1,(nInImageHeight - 1)/2) ;
		}
		else
		{
		dbImgOffset = (double)nInImageWidth * dbRatioWh / 2 - (double)nInImageHeight / 2;

		DispLine(hInWindowID,(nInImageWidth-1)/2 ,0,(nInImageWidth-1)/2 ,nInImageHeight - 1) ;
		DispLine(hInWindowID,0,(nInImageHeight - 1)/2,nInImageWidth-1,(nInImageHeight - 1)/2) ;
		}
		}
		else
		{
		if ((double)nInImageWidth/(double)nInImageHeight > dbRatioWh)
		{
		dbImgOffset = (double)nInImageWidth / dbRatioWh / 2 - (double)nInImageHeight / 2;

		DispLine(hInWindowID,(nInImageHeight-1)/2 ,0,(nInImageHeight-1)/2 ,nInImageWidth - 1) ;
		DispLine(hInWindowID,0,(nInImageWidth - 1)/2,nInImageHeight-1,(nInImageWidth - 1)/2) ;
		}
		else
		{
		dbImgOffset = (double)nInImageHeight * dbRatioWh / 2 - (double)nInImageWidth / 2;

		DispLine(hInWindowID,(nInImageHeight-1)/2 ,0,(nInImageHeight-1)/2 ,nInImageWidth - 1) ;
		DispLine(hInWindowID,0,(nInImageWidth - 1)/2,nInImageHeight-1,(nInImageWidth - 1)/2) ;
		}
		}*/
	}
	catch (...)
	{
	}
}

//图像旋转 nRotateType（0-0/1-90/2-180/3-270）
inline void InitStaticView(long lInWindowID,CAMERA_ROTATE eCameraRotateType,int nInCtrlWidth,int nInCtrlHeight,int nInImageWidth,\
	int nInImageHeight,double dbRatioWh,HTuple *hOutWindowID)
{
	try
	{
		SetWindowAttr("background_color","blue");
		SetWindowAttr("border_width",0);
		SetCheck("~father");
		OpenWindow(0,0,(Hlong)nInCtrlWidth,(Hlong)nInCtrlHeight,lInWindowID,"visible","",hOutWindowID);

		SetCheck("father");
		SetCheck ("~give_error");
		///////////////////////////////////////////
		double dbImgOffset ;

		if ((double)nInImageWidth/(double)nInImageHeight > dbRatioWh)
		{
			dbImgOffset = (double)nInImageWidth / dbRatioWh / 2 - (double)nInImageHeight / 2;
			SetPart(*hOutWindowID, -(HTuple)dbImgOffset, 0, nInImageHeight + (HTuple)dbImgOffset - 1, nInImageWidth - 1);
		}
		else
		{
			dbImgOffset = (double)nInImageHeight * dbRatioWh / 2 - (double)nInImageWidth / 2;
			SetPart(*hOutWindowID, 0, -(HTuple)dbImgOffset, nInImageHeight - 1,nInImageWidth + (HTuple)dbImgOffset - 1);
		}
		/*if (E_CAMERA_ROTATE_90 == eCameraRotateType || E_CAMERA_ROTATE_270 == eCameraRotateType)
		{
			if ((double) nInImageHeight/ (double) nInImageWidth > dbRatioWh)
			{
				dbImgOffset = (double)nInImageHeight / dbRatioWh / 2 - (double)nInImageWidth / 2;
				SetPart(*hOutWindowID, -(HTuple)dbImgOffset, 0, nInImageWidth + (HTuple)dbImgOffset - 1, nInImageHeight - 1);
			}
			else
			{
				dbImgOffset = (double)nInImageWidth * dbRatioWh / 2 - (double)nInImageHeight / 2;
				SetPart(*hOutWindowID, 0, -(HTuple)dbImgOffset, nInImageWidth - 1,nInImageHeight + (HTuple)dbImgOffset - 1);
			}
		}
		else
		{
			if ((double)nInImageWidth/(double)nInImageHeight > dbRatioWh)
			{
				dbImgOffset = (double)nInImageWidth / dbRatioWh / 2 - (double)nInImageHeight / 2;
				SetPart(*hOutWindowID, -(HTuple)dbImgOffset, 0, nInImageHeight + (HTuple)dbImgOffset - 1, nInImageWidth - 1);
			}
			else
			{
				dbImgOffset = (double)nInImageHeight * dbRatioWh / 2 - (double)nInImageWidth / 2;
				SetPart(*hOutWindowID, 0, -(HTuple)dbImgOffset, nInImageHeight - 1,nInImageWidth + (HTuple)dbImgOffset - 1);
			}
		}*/

		//SetPart(*hOutWindowID,0,0,nInImageHeight-1,nInImageWidth-1) ;
		///////////////////////////////////////////
		SetColor(*hOutWindowID,"green");
		SetDraw(*hOutWindowID,"margin");
		SetLineWidth(*hOutWindowID,1);

		DispCrossLineInWindow(*hOutWindowID,eCameraRotateType,nInImageWidth,nInImageHeight,dbRatioWh) ;
	}
	catch (...)
	{
	}
}

inline void ReSetPart(HTuple hInWindowID,CAMERA_ROTATE eRotateType,int nInImageWidth,int nInImageHeight,double dbRatioWh)
{
	try
	{
		double dbImgOffset ;
		/*if (E_CAMERA_ROTATE_90 == eRotateType || E_CAMERA_ROTATE_270 == eRotateType)
		{
			if ((double) nInImageHeight/ (double) nInImageWidth > dbRatioWh)
			{
				dbImgOffset = (double)nInImageHeight / dbRatioWh / 2 - (double)nInImageWidth / 2;
				SetPart(hInWindowID, -(HTuple)dbImgOffset, 0, nInImageWidth + (HTuple)dbImgOffset - 1, nInImageHeight - 1);
			}
			else
			{
				dbImgOffset = (double)nInImageWidth * dbRatioWh / 2 - (double)nInImageHeight / 2;
				SetPart(hInWindowID, 0, -(HTuple)dbImgOffset, nInImageWidth - 1,nInImageHeight + (HTuple)dbImgOffset - 1);
			}
		}
		else
		{
			if ((double)nInImageWidth/(double)nInImageHeight > dbRatioWh)
			{
				dbImgOffset = (double)nInImageWidth / dbRatioWh / 2 - (double)nInImageHeight / 2;
				SetPart(hInWindowID, -(HTuple)dbImgOffset, 0, nInImageHeight + (HTuple)dbImgOffset - 1, nInImageWidth - 1);
			}
			else
			{
				dbImgOffset = (double)nInImageHeight * dbRatioWh / 2 - (double)nInImageWidth / 2;
				SetPart(hInWindowID, 0, -(HTuple)dbImgOffset, nInImageHeight - 1,nInImageWidth + (HTuple)dbImgOffset - 1);
			}
		}*/

		if ((double)nInImageWidth/(double)nInImageHeight > dbRatioWh)
		{
			dbImgOffset = (double)nInImageWidth / dbRatioWh / 2 - (double)nInImageHeight / 2;
			SetPart(hInWindowID, -(HTuple)dbImgOffset, 0, nInImageHeight + (HTuple)dbImgOffset - 1, nInImageWidth - 1);
		}
		else
		{
			dbImgOffset = (double)nInImageHeight * dbRatioWh / 2 - (double)nInImageWidth / 2;
			SetPart(hInWindowID, 0, -(HTuple)dbImgOffset, nInImageHeight - 1,nInImageWidth + (HTuple)dbImgOffset - 1);
		}

		DispCrossLineInWindow(hInWindowID,eRotateType,nInImageWidth,nInImageHeight,dbRatioWh) ;
	}
	catch (...)
	{
	}
}

inline void DispImageToView(HTuple hInWindowID,HObject &hImage,CAMERA_ROTATE eRotateType,CAMERA_MIRROR eMirrorType,int nInImageWidth,int nInImageHeight,double dbRatioWh)
{
	try
	{
		//旋转
		switch(eRotateType)
		{
		case E_CAMERA_ROTATE_0:
			{
				RotateImage(hImage,&hImage,0,"constant") ;
				break;
			}
		case E_CAMERA_ROTATE_90:
			{
				RotateImage(hImage,&hImage,90,"constant") ;
				break;
			}
		case E_CAMERA_ROTATE_180:
			{
				RotateImage(hImage,&hImage,180,"constant") ;
				break;
			}
		case E_CAMERA_ROTATE_270:
			{
				RotateImage(hImage,&hImage,270,"constant") ;
				break;
			}
		default:
			break;
		}

		//镜像
		switch(eMirrorType)
		{
		case E_CAMERA_MIRROR_NONE:
			{
				break;
			}
		case E_CAMERA_MIRROR_ROW:
			{
				MirrorImage(hImage,&hImage,"row") ;
				break;
			}
		case E_CAMERA_MIRROR_COLUMN:
			{
				MirrorImage(hImage,&hImage,"column") ;
				break;
			}
		case E_CAMERA_MIRROR_DIAGONAL:
			{
				MirrorImage(hImage,&hImage,"diagonal") ;
				break;
			}
		default:
			break;
		}

		DispObj(hImage,hInWindowID) ;
		DispCrossLineInWindow(hInWindowID,eRotateType,nInImageWidth,nInImageHeight,dbRatioWh) ;
	}
	catch (...)
	{
	}
}

inline void Disp_SearchLine (HObject ho_InImage, HObject *ho_OutCaliperRegions, HTuple hv_InWindowID,
	HTuple hv_InLineRowStart, HTuple hv_InLineColStart, HTuple hv_InLineRowEnd, HTuple hv_InLineColEnd,
	HTuple hv_InColor, HTuple hv_InCaliperNum, HTuple hv_InCaliperWidth, HTuple hv_InCaliperHeight)
{
	// Local iconic variables
	HObject  ho_Rectangle;

	// Local control variables
	HTuple  hv_Width, hv_Height, hv_Angle1, hv_Deg;
	HTuple  hv_Angle, hv_Sin, hv_Cos, hv_Len, hv_RowC, hv_ColC;
	HTuple  hv_RowsEdge, hv_ColsEdge, hv_i, hv_Exception;

	try
	{
		GenEmptyObj(&(*ho_OutCaliperRegions));
		GetImageSize(ho_InImage, &hv_Width, &hv_Height);
		AngleLl(hv_InLineRowStart, hv_InLineColStart, hv_InLineRowStart, hv_Width, hv_InLineRowStart,
			hv_InLineColStart, hv_InLineRowEnd, hv_InLineColEnd, &hv_Angle1);
		TupleDeg(hv_Angle1, &hv_Deg);
		TupleRad(hv_Deg-90, &hv_Angle);

		TupleSin(hv_Angle, &hv_Sin);
		TupleCos(hv_Angle, &hv_Cos);
		if (HDevWindowStack::IsOpen())
			SetDraw(HDevWindowStack::GetActive(),"margin");

		TupleSqrt(((hv_InLineRowStart-hv_InLineRowEnd)*(hv_InLineRowStart-hv_InLineRowEnd))+((hv_InLineColStart-hv_InLineColEnd)*(hv_InLineColStart-hv_InLineColEnd)),
			&hv_Len);
		hv_RowC = 0;
		hv_ColC = 0;
		hv_RowsEdge = HTuple();
		hv_ColsEdge = HTuple();
		{
			HTuple end_val16 = hv_InCaliperNum-1;
			HTuple step_val16 = 1;
			for (hv_i=0; hv_i.Continue(end_val16, step_val16); hv_i += step_val16)
			{
				hv_RowC = hv_InLineRowStart-(((hv_Len/hv_InCaliperNum)*hv_i)*hv_Cos);
				hv_ColC = hv_InLineColStart-(((hv_Len/hv_InCaliperNum)*hv_i)*hv_Sin);
				if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(),hv_InColor);
				try
				{
					GenRectangle2(&ho_Rectangle, hv_RowC, hv_ColC, hv_Angle, hv_InCaliperHeight,
						hv_InCaliperWidth);

					ConcatObj((*ho_OutCaliperRegions), ho_Rectangle, &(*ho_OutCaliperRegions)
						);
				}
				// catch (Exception)
				catch (HException &HDevExpDefaultException)
				{
					HDevExpDefaultException.ToHTuple(&hv_Exception);
				}
			}
		}
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		return;
	}
}

inline void Draw_SearchLine (HObject ho_InImage, HObject *ho_OutCaliperRegions, HTuple hv_InWindowID,
	HTuple hv_InCaliperNum, HTuple hv_InCaliperWidth, HTuple hv_InCaliperHeight,
	HTuple hv_InColor, HTuple *hv_OutLineRowStart, HTuple *hv_OutLineColStart, HTuple *hv_OutLineRowEnd,
	HTuple *hv_OutLineColEnd)
{
	// Local control variables
	HTuple  hv_Width, hv_Height, hv_Exception;

	try
	{
		GetImageSize(ho_InImage, &hv_Width, &hv_Height);
		if (HDevWindowStack::IsOpen())
			SetColor(HDevWindowStack::GetActive(),hv_InColor);

		DrawLine(hv_InWindowID, &(*hv_OutLineRowStart), &(*hv_OutLineColStart), &(*hv_OutLineRowEnd),
			&(*hv_OutLineColEnd));
		DispArrow(hv_InWindowID, (*hv_OutLineRowStart), (*hv_OutLineColStart), (*hv_OutLineRowEnd),
			(*hv_OutLineColEnd), (5*hv_Width)/2448);

		Disp_SearchLine(ho_InImage, &(*ho_OutCaliperRegions), hv_InWindowID, (*hv_OutLineRowStart),
			(*hv_OutLineColStart), (*hv_OutLineRowEnd), (*hv_OutLineColEnd), hv_InColor,
			hv_InCaliperNum, hv_InCaliperWidth, hv_InCaliperHeight);
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		return;
	}
}

inline void Bm_Fit_Line_Pairs (HObject ho_InImage, HObject *ho_OutLine1Xld, HObject *ho_OutLine2Xld,
	HObject *ho_OutLineXld, HObject *ho_OutLine1ROIs, HObject *ho_OutLine2ROIs, HTuple hv_InWindowID,
	HTuple hv_InCaliperNum, HTuple hv_InClipNum, HTuple hv_InCaliperWidth, HTuple hv_InCaliperHeight,
	HTuple hv_InSigma1, HTuple hv_InSigma2, HTuple hv_InThre1, HTuple hv_InThre2,
	HTuple hv_InSelect1, HTuple hv_InSelect2, HTuple hv_InTransition1, HTuple hv_InTransition2,
	HTuple hv_InDrawLineRowStart, HTuple hv_InDrawLineColStart, HTuple hv_InDrawLineRowEnd,
	HTuple hv_InDrawLineColEnd, HTuple *hv_OutRows, HTuple *hv_OutCols, HTuple *hv_OutLine1RowStart,
	HTuple *hv_OutLine1ColStart, HTuple *hv_OutLine1RowEnd, HTuple *hv_OutLine1ColEnd,
	HTuple *hv_OutLine2RowStart, HTuple *hv_OutLine2ColStart, HTuple *hv_OutLine2RowEnd,
	HTuple *hv_OutLine2ColEnd, HTuple *hv_OutLineRowStart, HTuple *hv_OutLineColStart,
	HTuple *hv_OutLineRowEnd, HTuple *hv_OutLineColEnd, HTuple *hv_OutbRet1, HTuple *hv_OutbRet2)
{
	// Local iconic variables
	HObject  ho_Rectangle1, ho_Rectangle2, ho_SmoothedContours1;
	HObject  ho_SmoothedContours2, ho_Fit_line, ho_SmoothedContours;

	// Local control variables
	HTuple  hv_OutRows2, hv_OutCols2, hv_Width, hv_Height;
	HTuple  hv_Angle, hv_Deg, hv_Angle1, hv_Angle2, hv_Sin;
	HTuple  hv_Cos, hv_Len, hv_RowC, hv_ColC, hv_RowsEdge1;
	HTuple  hv_ColsEdge1, hv_RowsEdge2, hv_ColsEdge2, hv_RowsEdge;
	HTuple  hv_ColsEdge, hv_i, hv_MeasureHandle1, hv_RowEdge1;
	HTuple  hv_ColumnEdge1, hv_Amplitude1, hv_Distance1, hv_Exception;
	HTuple  hv_MeasureHandle2, hv_RowEdge2, hv_ColumnEdge2;
	HTuple  hv_Amplitude2, hv_Distance2, hv_Nr, hv_Nc, hv_Dist;
	HTuple  hv_OutPutRowBegin, hv_OutputColBegin, hv_OutPutRowEnd;
	HTuple  hv_OutPutColEnd, hv_RowsDel, hv_ColsDel, hv_Distance;
	HTuple  hv_k, hv_Max, hv_Indices;

	try
	{
		GenEmptyObj(&(*ho_OutLine1Xld));
		GenEmptyObj(&(*ho_OutLine2Xld));
		GenEmptyObj(&(*ho_OutLineXld));
		GenEmptyObj(&(*ho_OutLine1ROIs));
		GenEmptyObj(&(*ho_OutLine2ROIs));

		(*hv_OutRows) = HTuple();
		(*hv_OutCols) = HTuple();
		hv_OutRows2 = HTuple();
		hv_OutCols2 = HTuple();

		(*hv_OutbRet1) = 0;
		(*hv_OutbRet2) = 0;

		GetImageSize(ho_InImage, &hv_Width, &hv_Height);
		AngleLl(hv_InDrawLineRowStart, hv_InDrawLineColStart, hv_InDrawLineRowStart,
			hv_Width, hv_InDrawLineRowStart, hv_InDrawLineColStart, hv_InDrawLineRowEnd,
			hv_InDrawLineColEnd, &hv_Angle);
		TupleDeg(hv_Angle, &hv_Deg);
		TupleRad(hv_Deg-90, &hv_Angle1);

		TupleRad(hv_Deg+90, &hv_Angle2);

		TupleSin(hv_Angle1, &hv_Sin);
		TupleCos(hv_Angle1, &hv_Cos);
		if (HDevWindowStack::IsOpen())
			SetDraw(HDevWindowStack::GetActive(),"margin");

		TupleSqrt(((hv_InDrawLineRowStart-hv_InDrawLineRowEnd)*(hv_InDrawLineRowStart-hv_InDrawLineRowEnd))+((hv_InDrawLineColStart-hv_InDrawLineColEnd)*(hv_InDrawLineColStart-hv_InDrawLineColEnd)),
			&hv_Len);
		hv_RowC = 0;
		hv_ColC = 0;
		hv_RowsEdge1 = HTuple();
		hv_ColsEdge1 = HTuple();
		hv_RowsEdge2 = HTuple();
		hv_ColsEdge2 = HTuple();
		hv_RowsEdge = HTuple();
		hv_ColsEdge = HTuple();
		{
			HTuple end_val37 = hv_InCaliperNum-1;
			HTuple step_val37 = 1;
			for (hv_i=0; hv_i.Continue(end_val37, step_val37); hv_i += step_val37)
			{
				hv_RowC = hv_InDrawLineRowStart-(((hv_Len/hv_InCaliperNum)*hv_i)*hv_Cos);
				hv_ColC = hv_InDrawLineColStart-(((hv_Len/hv_InCaliperNum)*hv_i)*hv_Sin);
				/*if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(),"green");*/
				SetColor(hv_InWindowID,"green") ;
				try
				{
					GenRectangle2(&ho_Rectangle1, hv_RowC, hv_ColC, hv_Angle1, hv_InCaliperHeight,
						hv_InCaliperWidth);
					GenMeasureRectangle2(hv_RowC, hv_ColC, hv_Angle1, hv_InCaliperHeight, hv_InCaliperWidth,
						hv_Width, hv_Height, "nearest_neighbor", &hv_MeasureHandle1);
					MeasurePos(ho_InImage, hv_MeasureHandle1, hv_InSigma1, hv_InThre1, hv_InTransition1,
						hv_InSelect1, &hv_RowEdge1, &hv_ColumnEdge1, &hv_Amplitude1, &hv_Distance1);
					ConcatObj((*ho_OutLine1ROIs), ho_Rectangle1, &(*ho_OutLine1ROIs));
					//disp_cross (InWindowID, RowEdge1, ColumnEdge1, 20, 0)
				}
				// catch (Exception)
				catch (HException &HDevExpDefaultException)
				{
					HDevExpDefaultException.ToHTuple(&hv_Exception);
					CloseMeasure(hv_MeasureHandle1);
					continue;
				}

				try
				{
					GenRectangle2(&ho_Rectangle2, hv_RowC, hv_ColC, hv_Angle2, hv_InCaliperHeight,
						hv_InCaliperWidth);
					GenMeasureRectangle2(hv_RowC, hv_ColC, hv_Angle2, hv_InCaliperHeight, hv_InCaliperWidth,
						hv_Width, hv_Height, "nearest_neighbor", &hv_MeasureHandle2);
					MeasurePos(ho_InImage, hv_MeasureHandle2, hv_InSigma2, hv_InThre2, hv_InTransition2,
						hv_InSelect2, &hv_RowEdge2, &hv_ColumnEdge2, &hv_Amplitude2, &hv_Distance2);
					ConcatObj((*ho_OutLine2ROIs), ho_Rectangle2, &(*ho_OutLine2ROIs));
					//disp_cross (InWindowID, RowEdge2, ColumnEdge2, 20, 0)
				}
				// catch (Exception)
				catch (HException &HDevExpDefaultException)
				{
					HDevExpDefaultException.ToHTuple(&hv_Exception);
					CloseMeasure(hv_MeasureHandle2);
					continue;
				}

				if (0 != (HTuple((hv_RowEdge1.TupleLength())!=1).TupleOr((hv_RowEdge2.TupleLength())!=1)))
				{
					/*if (HDevWindowStack::IsOpen())
						SetColor(HDevWindowStack::GetActive(),"green");*/
					CloseMeasure(hv_MeasureHandle1);
					CloseMeasure(hv_MeasureHandle2);
					continue;
				}

				/*if (HDevWindowStack::IsOpen())
				SetColor(HDevWindowStack::GetActive(),"green");*/
				TupleConcat(hv_RowsEdge1, hv_RowEdge1, &hv_RowsEdge1);
				TupleConcat(hv_ColsEdge1, hv_ColumnEdge1, &hv_ColsEdge1);
				TupleConcat(hv_RowsEdge2, hv_RowEdge2, &hv_RowsEdge2);
				TupleConcat(hv_ColsEdge2, hv_ColumnEdge2, &hv_ColsEdge2);

				/*if (HDevWindowStack::IsOpen())
				SetColor(HDevWindowStack::GetActive(),"red");*/
				SetColor(hv_InWindowID,"green") ;
				DispCross(hv_InWindowID, hv_RowEdge1, hv_ColumnEdge1, 20, 0);
				CloseMeasure(hv_MeasureHandle1);
				DispCross(hv_InWindowID, hv_RowEdge2, hv_ColumnEdge2, 20, 0);
				CloseMeasure(hv_MeasureHandle2);
			}
		}

		if (0 != ((hv_RowsEdge1.TupleLength())!=(hv_RowsEdge2.TupleLength())))
		{
			(*hv_OutbRet1) = 0;
			(*hv_OutbRet2) = 0;
			return;
		}

		{
			HTuple end_val92 = (hv_RowsEdge1.TupleLength())-1;
			HTuple step_val92 = 1;
			for (hv_i=0; hv_i.Continue(end_val92, step_val92); hv_i += step_val92)
			{
				hv_RowsEdge[hv_RowsEdge.TupleLength()] = (HTuple(hv_RowsEdge1[hv_i])+HTuple(hv_RowsEdge2[hv_i]))/2;
				hv_ColsEdge[hv_ColsEdge.TupleLength()] = (HTuple(hv_ColsEdge1[hv_i])+HTuple(hv_ColsEdge2[hv_i]))/2;
				/*if (HDevWindowStack::IsOpen())
				SetColor(HDevWindowStack::GetActive(),"blue");*/
				SetColor(hv_InWindowID,"blue") ;
				DispCross(hv_InWindowID, (HTuple(hv_RowsEdge1[hv_i])+HTuple(hv_RowsEdge2[hv_i]))/2,
					(HTuple(hv_ColsEdge1[hv_i])+HTuple(hv_ColsEdge2[hv_i]))/2, 20, 0);
			}
		}

		//过滤(忽略点)
		//边缘点数过少防呆
		if (0 != ((hv_RowsEdge.TupleLength())<=hv_InClipNum))
		{
			(*hv_OutbRet1) = 0;
			(*hv_OutbRet2) = 0;
			return;
		}
		else if (0 != ((hv_RowsEdge1.TupleLength())<10))
		{
			(*hv_OutbRet1) = 0;
			(*hv_OutbRet2) = 0;
			return;
		}

		if (0 != ((hv_RowsEdge1.TupleLength())<=hv_InClipNum))
		{
			(*hv_OutbRet1) = 0;
			if (0 != ((hv_RowsEdge2.TupleLength())<=hv_InClipNum))
			{
				(*hv_OutbRet2) = 0;
			}
			return;
		}
		else if (0 != ((hv_RowsEdge1.TupleLength())<10))
		{
			(*hv_OutbRet1) = 0;
			if (0 != ((hv_RowsEdge2.TupleLength())<=10))
			{
				(*hv_OutbRet2) = 0;
			}
			return;
		}

		GenContourPolygonXld(&(*ho_OutLine1Xld), hv_RowsEdge1, hv_ColsEdge1);
		SmoothContoursXld((*ho_OutLine1Xld), &ho_SmoothedContours1, 5);
		FitLineContourXld(ho_SmoothedContours1, "drop", -1, hv_InClipNum, 5, 2, &(*hv_OutLine1RowStart),
			&(*hv_OutLine1ColStart), &(*hv_OutLine1RowEnd), &(*hv_OutLine1ColEnd), &hv_Nr,
			&hv_Nc, &hv_Dist);

		GenContourPolygonXld(&(*ho_OutLine2Xld), hv_RowsEdge2, hv_ColsEdge2);
		SmoothContoursXld((*ho_OutLine2Xld), &ho_SmoothedContours2, 5);
		FitLineContourXld(ho_SmoothedContours2, "drop", -1, hv_InClipNum, 5, 2, &(*hv_OutLine2RowStart),
			&(*hv_OutLine2ColStart), &(*hv_OutLine2RowEnd), &(*hv_OutLine2ColEnd), &hv_Nr,
			&hv_Nc, &hv_Dist);

		GenContourPolygonXld(&ho_Fit_line, hv_RowsEdge, hv_ColsEdge);
		SmoothContoursXld(ho_Fit_line, &ho_SmoothedContours, 5);
		FitLineContourXld(ho_SmoothedContours, "drop", -1, hv_InClipNum, 5, 2, &hv_OutPutRowBegin,
			&hv_OutputColBegin, &hv_OutPutRowEnd, &hv_OutPutColEnd, &hv_Nr, &hv_Nc, &hv_Dist);

		hv_RowsDel = HTuple();
		hv_ColsDel = HTuple();
		DistancePl(hv_RowsEdge, hv_ColsEdge, hv_OutPutRowBegin, hv_OutputColBegin, hv_OutPutRowEnd,
			hv_OutPutColEnd, &hv_Distance);
		{
			HTuple end_val142 = hv_InClipNum;
			HTuple step_val142 = 1;
			for (hv_k=1; hv_k.Continue(end_val142, step_val142); hv_k += step_val142)
			{
				TupleMax(hv_Distance, &hv_Max);
				TupleFind(hv_Distance, hv_Max, &hv_Indices);
				TupleConcat(hv_RowsDel, HTuple(hv_RowsEdge[HTuple(hv_Indices[0])]), &hv_RowsDel);
				TupleConcat(hv_ColsDel, HTuple(hv_ColsEdge[HTuple(hv_Indices[0])]), &hv_ColsDel);
				TupleRemove(hv_RowsEdge, HTuple(hv_Indices[0]), &hv_RowsEdge);
				TupleRemove(hv_ColsEdge, HTuple(hv_Indices[0]), &hv_ColsEdge);
				TupleRemove(hv_Distance, HTuple(hv_Indices[0]), &hv_Distance);
			}
		}

		(*hv_OutRows) = hv_RowsEdge;
		(*hv_OutCols) = hv_ColsEdge;

		SetColor(hv_InWindowID,"red") ;
		DispCross(hv_InWindowID, hv_RowsDel, hv_ColsDel, 20, 0);

		GenContourPolygonXld(&(*ho_OutLineXld), hv_RowsEdge, hv_ColsEdge);
		SmoothContoursXld((*ho_OutLineXld), &ho_SmoothedContours, 5);
		FitLineContourXld(ho_SmoothedContours, "drop", -1, 0, 5, 2, &(*hv_OutLineRowStart),
			&(*hv_OutLineColStart), &(*hv_OutLineRowEnd), &(*hv_OutLineColEnd), &hv_Nr,
			&hv_Nc, &hv_Dist);

		(*hv_OutbRet1) = 1;
		(*hv_OutbRet2) = 1;
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		(*hv_OutbRet1) = -1;
		(*hv_OutbRet2) = -1;
	}
}

inline void Bm_Fit_Line (HObject ho_Image, HObject *ho_LineXld, HObject *ho_CaliperROIs,
	HTuple hv_WindowID, HTuple hv_CaliperNum, HTuple hv_CaliperWidth, HTuple hv_CaliperHeight,
	HTuple hv_Sigma, HTuple hv_Thre, HTuple hv_Select, HTuple hv_Transition, HTuple hv_ClipNum,
	HTuple hv_DrawLineRowStart, HTuple hv_DrawLineColStart, HTuple hv_DrawLineRowEnd,
	HTuple hv_DrawLineColEnd, HTuple *hv_OutRows, HTuple *hv_OutCols, HTuple *hv_OutLineRowStart,
	HTuple *hv_OutLineColStart, HTuple *hv_OutLineRowEnd, HTuple *hv_OutLineColEnd,
	HTuple *hv_bSuccess)
{
	// Local iconic variables
	HObject  ho_Rectangle, ho_Fit_line, ho_SmoothedContours1;
	HObject  ho_SmoothedContours;

	// Local control variables
	HTuple  hv_Width, hv_Height, hv_Angle1, hv_Deg;
	HTuple  hv_Angle, hv_Sin, hv_Cos, hv_Len, hv_RowC, hv_ColC;
	HTuple  hv_RowsEdge, hv_ColsEdge, hv_i, hv_MeasureHandle;
	HTuple  hv_RowEdge, hv_ColumnEdge, hv_Amplitude, hv_Distance;
	HTuple  hv_Exception, hv_OutPutRowBegin, hv_OutputColBegin;
	HTuple  hv_OutPutRowEnd, hv_OutPutColEnd, hv_Nr, hv_Nc;
	HTuple  hv_Dist, hv_RowsDel, hv_ColsDel, hv_k, hv_Max, hv_Indices;

	try
	{
		GenEmptyObj(&(*ho_LineXld));
		GenEmptyObj(&(*ho_CaliperROIs));

		(*hv_OutRows) = HTuple();
		(*hv_OutCols) = HTuple();

		GetImageSize(ho_Image, &hv_Width, &hv_Height);
		AngleLl(hv_DrawLineRowStart, hv_DrawLineColStart, hv_DrawLineRowStart, hv_Width,
			hv_DrawLineRowStart, hv_DrawLineColStart, hv_DrawLineRowEnd, hv_DrawLineColEnd,
			&hv_Angle1);
		TupleDeg(hv_Angle1, &hv_Deg);
		TupleRad(hv_Deg-90, &hv_Angle);

		TupleSin(hv_Angle, &hv_Sin);
		TupleCos(hv_Angle, &hv_Cos);
		if (HDevWindowStack::IsOpen())
			SetDraw(HDevWindowStack::GetActive(),"margin");

		TupleSqrt(((hv_DrawLineRowStart-hv_DrawLineRowEnd)*(hv_DrawLineRowStart-hv_DrawLineRowEnd))+((hv_DrawLineColStart-hv_DrawLineColEnd)*(hv_DrawLineColStart-hv_DrawLineColEnd)),
			&hv_Len);
		hv_RowC = 0;
		hv_ColC = 0;
		hv_RowsEdge = HTuple();
		hv_ColsEdge = HTuple();
		{
			HTuple end_val21 = hv_CaliperNum-1;
			HTuple step_val21 = 1;
			for (hv_i=0; hv_i.Continue(end_val21, step_val21); hv_i += step_val21)
			{
				hv_RowC = hv_DrawLineRowStart-(((hv_Len/hv_CaliperNum)*hv_i)*hv_Cos);
				hv_ColC = hv_DrawLineColStart-(((hv_Len/hv_CaliperNum)*hv_i)*hv_Sin);
				if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(),"green");
				try
				{
					GenRectangle2(&ho_Rectangle, hv_RowC, hv_ColC, hv_Angle, hv_CaliperHeight,
						hv_CaliperWidth);
					GenMeasureRectangle2(hv_RowC, hv_ColC, hv_Angle, hv_CaliperHeight, hv_CaliperWidth,
						hv_Width, hv_Height, "nearest_neighbor", &hv_MeasureHandle);
					MeasurePos(ho_Image, hv_MeasureHandle, hv_Sigma, hv_Thre, hv_Transition,
						hv_Select, &hv_RowEdge, &hv_ColumnEdge, &hv_Amplitude, &hv_Distance);
					ConcatObj((*ho_CaliperROIs), ho_Rectangle, &(*ho_CaliperROIs));
				}
				// catch (Exception)
				catch (HException &HDevExpDefaultException)
				{
					HDevExpDefaultException.ToHTuple(&hv_Exception);
					CloseMeasure(hv_MeasureHandle);
					continue;
				}

				if (0 != ((hv_RowEdge.TupleLength())!=1))
				{
					if (HDevWindowStack::IsOpen())
						SetColor(HDevWindowStack::GetActive(),"green");
					CloseMeasure(hv_MeasureHandle);
					continue;
				}

				if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(),"green");
				TupleConcat(hv_RowsEdge, hv_RowEdge, &hv_RowsEdge);
				TupleConcat(hv_ColsEdge, hv_ColumnEdge, &hv_ColsEdge);

				if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(),"red");
				//DispCross(hv_WindowID, hv_RowEdge, hv_ColumnEdge, 20, 0);
				CloseMeasure(hv_MeasureHandle);
			}
		}

		//过滤(忽略点)

		//边缘点数过少防呆

		if (0 != ((hv_RowsEdge.TupleLength())<=hv_ClipNum))
		{
			(*hv_bSuccess) = 0;
			return;
		}
		else if (0 != ((hv_RowsEdge.TupleLength())<10))
		{
			(*hv_bSuccess) = 0;
			return;
		}

		GenContourPolygonXld(&ho_Fit_line, hv_RowsEdge, hv_ColsEdge);
		SmoothContoursXld(ho_Fit_line, &ho_SmoothedContours1, 5);
		FitLineContourXld(ho_SmoothedContours1, "drop", -1, hv_ClipNum, 5, 2, &hv_OutPutRowBegin,
			&hv_OutputColBegin, &hv_OutPutRowEnd, &hv_OutPutColEnd, &hv_Nr, &hv_Nc, &hv_Dist);

		hv_RowsDel = HTuple();
		hv_ColsDel = HTuple();
		DistancePl(hv_RowsEdge, hv_ColsEdge, hv_OutPutRowBegin, hv_OutputColBegin, hv_OutPutRowEnd,
			hv_OutPutColEnd, &hv_Distance);
		{
			HTuple end_val71 = hv_ClipNum;
			HTuple step_val71 = 1;
			for (hv_k=1; hv_k.Continue(end_val71, step_val71); hv_k += step_val71)
			{
				TupleMax(hv_Distance, &hv_Max);
				TupleFind(hv_Distance, hv_Max, &hv_Indices);
				TupleConcat(hv_RowsDel, HTuple(hv_RowsEdge[HTuple(hv_Indices[0])]), &hv_RowsDel);
				TupleConcat(hv_ColsDel, HTuple(hv_ColsEdge[HTuple(hv_Indices[0])]), &hv_ColsDel);
				TupleRemove(hv_RowsEdge, HTuple(hv_Indices[0]), &hv_RowsEdge);
				TupleRemove(hv_ColsEdge, HTuple(hv_Indices[0]), &hv_ColsEdge);
				TupleRemove(hv_Distance, HTuple(hv_Indices[0]), &hv_Distance);
			}
		}

		(*hv_OutRows) = hv_RowsEdge;
		(*hv_OutCols) = hv_ColsEdge;

		GenContourPolygonXld(&(*ho_LineXld), hv_RowsEdge, hv_ColsEdge);
		SmoothContoursXld((*ho_LineXld), &ho_SmoothedContours, 5);
		FitLineContourXld(ho_SmoothedContours, "drop", -1, 0, 5, 2, &(*hv_OutLineRowStart),
			&(*hv_OutLineColStart), &(*hv_OutLineRowEnd), &(*hv_OutLineColEnd), &hv_Nr,
			&hv_Nc, &hv_Dist);

		(*hv_bSuccess) = 1;
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		(*hv_bSuccess) = -1;
		return;
	}
}

inline void Halcon_DispLine (HTuple hv_hInWindowID, HTuple hv_hInLineStartRow, HTuple hv_hInLineStartCol,
	HTuple hv_hInLineEndRow, HTuple hv_hInLineEndCol, HTuple hv_hInImageWidth, HTuple hv_hInImageHeight,
	HTuple hv_hInLineColor)
{
	// Local control variables
	HTuple  hv_LeftCrossRow, hv_LeftCrossCol, hv_IsParallelLeft;
	HTuple  hv_RightCrossRow, hv_RightCrossCol, hv_IsParallelRight;
	HTuple  hv_UpCrossRow, hv_UpCrossCol, hv_IsParallelUp, hv_DownCrossRow;
	HTuple  hv_DownCrossCol, hv_IsParallelDown, hv_Exception;

	try
	{
		IntersectionLl(hv_hInLineStartRow, hv_hInLineStartCol, hv_hInLineEndRow, hv_hInLineEndCol,
			0, 0, hv_hInImageHeight, 0, &hv_LeftCrossRow, &hv_LeftCrossCol, &hv_IsParallelLeft);
		IntersectionLl(hv_hInLineStartRow, hv_hInLineStartCol, hv_hInLineEndRow, hv_hInLineEndCol,
			0, hv_hInImageWidth, hv_hInImageHeight, hv_hInImageWidth, &hv_RightCrossRow,
			&hv_RightCrossCol, &hv_IsParallelRight);

		IntersectionLl(hv_hInLineStartRow, hv_hInLineStartCol, hv_hInLineEndRow, hv_hInLineEndCol,
			0, 0, 0, hv_hInImageWidth, &hv_UpCrossRow, &hv_UpCrossCol, &hv_IsParallelUp);
		IntersectionLl(hv_hInLineStartRow, hv_hInLineStartCol, hv_hInLineEndRow, hv_hInLineEndCol,
			hv_hInImageHeight, 0, hv_hInImageHeight, hv_hInImageWidth, &hv_DownCrossRow,
			&hv_DownCrossCol, &hv_IsParallelDown);

		if (HDevWindowStack::IsOpen())
			SetColor(HDevWindowStack::GetActive(),hv_hInLineColor);
		if (0 != (HTuple(HTuple(HTuple(HTuple(HTuple(HTuple(HTuple(hv_LeftCrossRow>=0).TupleAnd(hv_LeftCrossRow<=hv_hInImageHeight)).TupleAnd(hv_LeftCrossCol>=0)).TupleAnd(hv_LeftCrossCol<=hv_hInImageWidth)).TupleAnd(hv_RightCrossRow>=0)).TupleAnd(hv_RightCrossRow<=hv_hInImageHeight)).TupleAnd(hv_RightCrossCol>=0)).TupleAnd(hv_RightCrossCol<=hv_hInImageWidth)))
		{
			DispLine(hv_hInWindowID, hv_LeftCrossRow, hv_LeftCrossCol, hv_RightCrossRow,
				hv_RightCrossCol);
		}
		else
		{
			DispLine(hv_hInWindowID, hv_UpCrossRow, hv_UpCrossCol, hv_DownCrossRow, hv_DownCrossCol);
		}

		return;
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		return;
	}
}

inline void Arc_Pos_Sort (HTuple hv_InputRows, HTuple hv_InputCols, HTuple hv_SortType,
	HTuple *hv_OutputRows, HTuple *hv_OutputCols)
{
	// Local iconic variables
	HObject  ho_Contour;

	// Local control variables
	HTuple  hv_PI, hv_RowCenter, hv_ColCenter, hv_Radius;
	HTuple  hv_StartPhi, hv_EndPhi, hv_PointOrder, hv_LineAngles;
	HTuple  hv_Angle1, hv_i, hv_Angle, hv_Max, hv_Indices, hv_LineAnglesSorted;
	HTuple  hv_FindIndex, hv_Deg, hv_Abs, hv_Min, hv_Exception;

	try
	{
		//SortType = 0 逆时针排序 反之顺时针排序
		TupleRad(180, &hv_PI);
		GenContourPolygonXld(&ho_Contour, hv_InputRows, hv_InputCols);
		FitCircleContourXld(ho_Contour, "algebraic", -1, 0, 0, 3, 2, &hv_RowCenter, &hv_ColCenter,
			&hv_Radius, &hv_StartPhi, &hv_EndPhi, &hv_PointOrder);
		//
		(*hv_OutputRows) = HTuple();
		(*hv_OutputCols) = HTuple();
		hv_LineAngles = HTuple();
		//
		//
		//
		if (0 != (hv_SortType==0))
		{
			//先判断数据是否按逆时针
			AngleLl(hv_RowCenter, hv_ColCenter, HTuple(hv_InputRows[0]), HTuple(hv_InputCols[0]),
				hv_RowCenter, hv_ColCenter, HTuple(hv_InputRows[1]), HTuple(hv_InputCols[1]),
				&hv_Angle1);
			if (0 != (hv_Angle1<0))
			{
				TupleInverse(hv_InputRows, &hv_InputRows);
				TupleInverse(hv_InputCols, &hv_InputCols);
			}
			//
			{
				HTuple end_val20 = (hv_InputRows.TupleLength())-1;
				HTuple step_val20 = 1;
				for (hv_i=0; hv_i.Continue(end_val20, step_val20); hv_i += step_val20)
				{
					//disp_arrow (3600, RowCenter, ColCenter, InputRows[i], InputCols[i], 2)
					hv_Angle = HTuple();
					AngleLl(hv_RowCenter, hv_ColCenter, hv_RowCenter, 9999, hv_RowCenter, hv_ColCenter,
						HTuple(hv_InputRows[hv_i]), HTuple(hv_InputCols[hv_i]), &hv_Angle);
					//
					if (0 != (hv_Angle<0))
					{
						hv_Angle = (2*hv_PI)+hv_Angle;
						//
					}
					//
					TupleConcat(hv_LineAngles, hv_Angle, &hv_LineAngles);
				}
			}
			//
			TupleMax(hv_LineAngles, &hv_Max);
			TupleFind(hv_LineAngles, hv_Max, &hv_Indices);
			{
				HTuple end_val35 = (hv_LineAngles.TupleLength())-1;
				HTuple step_val35 = 1;
				for (hv_i=HTuple(hv_Indices[0])+1; hv_i.Continue(end_val35, step_val35); hv_i += step_val35)
				{
					hv_LineAngles[hv_i] = HTuple(hv_LineAngles[hv_i])+(2*hv_PI);
				}
			}
			//
			TupleSort(hv_LineAngles, &hv_LineAnglesSorted);
			//
			//逆时针链接数据
			{
				HTuple end_val42 = (hv_LineAnglesSorted.TupleLength())-1;
				HTuple step_val42 = 1;
				for (hv_i=0; hv_i.Continue(end_val42, step_val42); hv_i += step_val42)
				{
					TupleFind(hv_LineAngles, HTuple(hv_LineAnglesSorted[hv_i]), &hv_FindIndex);
					TupleConcat((*hv_OutputRows), HTuple(hv_InputRows[hv_FindIndex]), &(*hv_OutputRows));
					TupleConcat((*hv_OutputCols), HTuple(hv_InputCols[hv_FindIndex]), &(*hv_OutputCols));
				}
			}
			//
			//
		}
		else if (0 != (hv_SortType==1))
		{
			//先判断数据是否按顺时针
			AngleLl(hv_RowCenter, hv_ColCenter, HTuple(hv_InputRows[0]), HTuple(hv_InputCols[0]),
				hv_RowCenter, hv_ColCenter, HTuple(hv_InputRows[1]), HTuple(hv_InputCols[1]),
				&hv_Angle1);
			if (0 != (hv_Angle1>0))
			{
				TupleInverse(hv_InputRows, &hv_InputRows);
				TupleInverse(hv_InputCols, &hv_InputCols);
			}
			{
				HTuple end_val56 = (hv_InputRows.TupleLength())-1;
				HTuple step_val56 = 1;
				for (hv_i=0; hv_i.Continue(end_val56, step_val56); hv_i += step_val56)
				{
					//disp_arrow (3600, RowCenter, ColCenter, InputRows[i], InputCols[i], 2)
					hv_Angle = HTuple();
					AngleLl(hv_RowCenter, hv_ColCenter, HTuple(hv_InputRows[hv_i]), HTuple(hv_InputCols[hv_i]),
						hv_RowCenter, hv_ColCenter, hv_RowCenter, 9999, &hv_Angle);
					TupleDeg(hv_Angle, &hv_Deg);
					if (0 != (hv_Angle>0))
					{
						hv_Angle = (-2*hv_PI)+hv_Angle;
					}
					TupleAbs(hv_Angle, &hv_Abs);
					TupleConcat(hv_LineAngles, hv_Angle, &hv_LineAngles);
				}
			}
			//
			TupleMin(hv_LineAngles, &hv_Min);
			TupleFind(hv_LineAngles, hv_Min, &hv_Indices);
			{
				HTuple end_val70 = (hv_LineAngles.TupleLength())-1;
				HTuple step_val70 = 1;
				for (hv_i=hv_Indices+1; hv_i.Continue(end_val70, step_val70); hv_i += step_val70)
				{
					hv_LineAngles[hv_i] = HTuple(hv_LineAngles[hv_i])-(2*hv_PI);
				}
			}
			//
			TupleSort(hv_LineAngles, &hv_LineAnglesSorted);
			//
			//顺时针链接数据
			{
				HTuple end_val77 = (hv_LineAnglesSorted.TupleLength())-1;
				HTuple step_val77 = 1;
				for (hv_i=0; hv_i.Continue(end_val77, step_val77); hv_i += step_val77)
				{
					TupleFind(hv_LineAngles, HTuple(hv_LineAnglesSorted[hv_i]), &hv_FindIndex);
					TupleConcat((*hv_OutputRows), HTuple(hv_InputRows[hv_FindIndex]), &(*hv_OutputRows));
					TupleConcat((*hv_OutputCols), HTuple(hv_InputCols[hv_FindIndex]), &(*hv_OutputCols));
				}
			}
		}
		//
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		return;
	}
}

inline void Bm_Fit_Arc (HObject ho_InImage, HObject *ho_OutCaliperRegions, HObject *ho_OutCircleXld,
	HTuple hv_InWindowID, HTuple hv_InRowCenter, HTuple hv_InColCenter, HTuple hv_InRadius,
	HTuple hv_InCaliperNum, HTuple hv_InCaliperWidth, HTuple hv_InCaliperHeight,
	HTuple hv_InSigma, HTuple hv_InThre, HTuple hv_InSelect, HTuple hv_InTransition,
	HTuple hv_InStartAngle, HTuple hv_InEndAngle, HTuple *hv_OutRowCenter, HTuple *hv_OutColCenter,
	HTuple *hv_OutRadius, HTuple *hv_OutRows, HTuple *hv_OutCols, HTuple *hv_OutbRet)
{
	// Local iconic variables

	// Local control variables
	HTuple  hv_Width, hv_Height, hv_MetrologyHandle;
	HTuple  hv_MetrologyCircleIndices, hv_CircleParameter, hv_Exception;

	try
	{
		(*hv_OutbRet) = 0;
		(*hv_OutRows) = HTuple();
		(*hv_OutCols) = HTuple();
		(*hv_OutRowCenter) = HTuple();
		(*hv_OutColCenter) = HTuple();
		(*hv_OutRadius) = HTuple();

		GenEmptyObj(&(*ho_OutCaliperRegions));
		GenEmptyObj(&(*ho_OutCircleXld));
		GetImageSize(ho_InImage, &hv_Width, &hv_Height);

		CreateMetrologyModel(&hv_MetrologyHandle);
		SetMetrologyModelImageSize(hv_MetrologyHandle, hv_Width, hv_Height);
		AddMetrologyObjectGeneric(hv_MetrologyHandle, "circle", (hv_InRowCenter.TupleConcat(hv_InColCenter)).TupleConcat(hv_InRadius),
			hv_InCaliperHeight, hv_InCaliperWidth, hv_InSigma, hv_InThre, (HTuple("start_phi").Append("end_phi")),
			(hv_InStartAngle.TupleRad()).TupleConcat(hv_InEndAngle.TupleRad()), &hv_MetrologyCircleIndices);
		SetMetrologyObjectParam(hv_MetrologyHandle, hv_MetrologyCircleIndices, "num_measures",
			hv_InCaliperNum);
		SetMetrologyObjectParam(hv_MetrologyHandle, hv_MetrologyCircleIndices, "measure_transition",
			hv_InTransition);
		//
		ApplyMetrologyModel(ho_InImage, hv_MetrologyHandle);
		GetMetrologyObjectResult(hv_MetrologyHandle, hv_MetrologyCircleIndices, "all",
			"result_type", "all_param", &hv_CircleParameter);
		if (0 != (((hv_CircleParameter.TupleLength())/3)!=1))
		{
			ClearMetrologyModel(hv_MetrologyHandle);
			(*hv_OutbRet) = 0;
			return;
		}
		GetMetrologyObjectResultContour(&(*ho_OutCircleXld), hv_MetrologyHandle, "all",
			"all", 1.5);
		GetMetrologyObjectMeasures(&(*ho_OutCaliperRegions), hv_MetrologyHandle, "all",
			"all", &(*hv_OutRows), &(*hv_OutCols));
		//gen_cross_contour_xld (Cross, Row1, Column1, 6, 0.785398)
		ClearMetrologyModel(hv_MetrologyHandle);
		//
		//
		//
		TupleConcat((*hv_OutRowCenter), HTuple(hv_CircleParameter[0]), &(*hv_OutRowCenter));
		TupleConcat((*hv_OutColCenter), HTuple(hv_CircleParameter[1]), &(*hv_OutColCenter));
		TupleConcat((*hv_OutRadius), HTuple(hv_CircleParameter[2]), &(*hv_OutRadius));
		//
		(*hv_OutbRet) = 1;
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		(*hv_OutbRet) = -1;
	}
}

inline void Halcon_Disp_Arc(HObject ho_InImage, HObject ho_InputArcContour, HObject *ho_OutCaliperRegions,
	HTuple hv_InWindowID, HTuple hv_InCaliperNum, HTuple hv_InCaliperWidth, HTuple hv_InCaliperHeight,
	HTuple hv_InColor, HTuple hv_InputArcRow, HTuple hv_InputArcCol, HTuple hv_InputArcRadius,
	HTuple hv_InputArcStartAngle, HTuple hv_InputArcEndAngle)
{
	// Local iconic variables
	HObject  ho_Rectangle;

	// Local control variables
	HTuple  hv_Width, hv_Height, hv_RowArr, hv_ColArr;
	HTuple  hv_AngleStep, hv_CaliperRows, hv_CaliperCols, hv_i;
	HTuple  hv_HomMat2DIdentity, hv_HomMat2DRotate, hv_RowInter;
	HTuple  hv_ColInter, hv_k, hv_Angle, hv_Exception;

	try
	{
		GenEmptyObj(&(*ho_OutCaliperRegions));
		GetImageSize(ho_InImage, &hv_Width, &hv_Height);
		GetContourXld(ho_InputArcContour, &hv_RowArr, &hv_ColArr);

		hv_AngleStep = ((hv_InputArcEndAngle-hv_InputArcStartAngle)*1.0)/(hv_InCaliperNum-1);

		TupleAbs(hv_AngleStep, &hv_AngleStep);

		hv_CaliperRows = HTuple();
		hv_CaliperCols = HTuple();

		{
			HTuple end_val15 = hv_InCaliperNum-1;
			HTuple step_val15 = 1;
			for (hv_i=0; hv_i.Continue(end_val15, step_val15); hv_i += step_val15)
			{
				if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(),"green");
				HomMat2dIdentity(&hv_HomMat2DIdentity);
				HomMat2dRotate(hv_HomMat2DIdentity, (hv_i*hv_AngleStep).TupleRad(), hv_InputArcRow,
					hv_InputArcCol, &hv_HomMat2DRotate);
				AffineTransPoint2d(hv_HomMat2DRotate, HTuple(hv_RowArr[0]), HTuple(hv_ColArr[0]),
					&hv_RowInter, &hv_ColInter);
				//
				TupleConcat(hv_CaliperRows, hv_RowInter, &hv_CaliperRows);
				TupleConcat(hv_CaliperCols, hv_ColInter, &hv_CaliperCols);
			}
		}

		{
			HTuple end_val25 = (hv_CaliperRows.TupleLength())-1;
			HTuple step_val25 = 1;
			for (hv_k=0; hv_k.Continue(end_val25, step_val25); hv_k += step_val25)
			{
				AngleLl(hv_InputArcRow, hv_InputArcCol, hv_InputArcRow, 9999, hv_InputArcRow,
					hv_InputArcCol, HTuple(hv_CaliperRows[hv_k]), HTuple(hv_CaliperCols[hv_k]),
					&hv_Angle);
				GenRectangle2(&ho_Rectangle, HTuple(hv_CaliperRows[hv_k]), HTuple(hv_CaliperCols[hv_k]),
					hv_Angle, hv_InCaliperHeight, hv_InCaliperWidth);

				ConcatObj((*ho_OutCaliperRegions), ho_Rectangle, &(*ho_OutCaliperRegions));
			}
		}
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		return;
	}
}

inline void Halcon_Draw_Arc (HObject ho_InputImage, HObject *ho_OutputArcCaliperRegions,
	HObject *ho_OutputArcContour, HTuple hv_WindowID, HTuple hv_InputStartAngle,
	HTuple hv_InputEndAngle, HTuple hv_InputColor, HTuple hv_InputCaliperNum, HTuple hv_InputCaliperWidth,
	HTuple hv_InputCaliperHeight, HTuple *hv_OutputStartAngle, HTuple *hv_OutputEndAngle,
	HTuple *hv_OutputRowCenter, HTuple *hv_OutputColCenter, HTuple *hv_OutputRadius,
	HTuple *hv_bArcLength)
{
	// Local iconic variables
	HObject  ho_ContCircle;

	// Local control variables
	HTuple  hv_dbTmpAngle, hv_Row, hv_Column, hv_Radius;
	HTuple  hv_RowCenter, hv_ColCenter, hv_RadiusCenter, hv_StartPhi;
	HTuple  hv_EndPhi, hv_PointOrder, hv_RowCircles, hv_ColCircles;
	HTuple  hv_OutputRows, hv_OutputCols, hv_StartAngle, hv_AbsStep;
	HTuple  hv_Exception;

	try
	{
		/*if (HDevWindowStack::IsOpen())
			DispObj(ho_InputImage, HDevWindowStack::GetActive());
		if (HDevWindowStack::IsOpen())
			SetDraw(HDevWindowStack::GetActive(),"margin");
		if (HDevWindowStack::IsOpen())
			SetColor(HDevWindowStack::GetActive(),"green");
		if (HDevWindowStack::IsOpen())
			SetLineWidth(HDevWindowStack::GetActive(),1);
		GenEmptyObj(&(*ho_OutputArcContour));
		GenEmptyObj(&(*ho_OutputArcCaliperRegions));
		disp_message(hv_WindowID, "鼠标左键绘制，右键结束", "window", -1, -1, "red",
			"false");
*/
		double dbStartAngle = (int)hv_InputStartAngle[0].D()%360 ;
		double dbEndAngle = (int)hv_InputEndAngle[0].D()%360 ;

		(*hv_OutputStartAngle) = dbStartAngle ;
		(*hv_OutputEndAngle) = dbEndAngle ;

		/*(*hv_OutputStartAngle) = hv_InputStartAngle%360;
		(*hv_OutputEndAngle) = hv_InputEndAngle%360;*/

		if (0 != ((*hv_OutputEndAngle)==(*hv_OutputStartAngle)))
		{
			(*hv_OutputEndAngle) = (*hv_OutputStartAngle)+360;
		}

		//if (OutputEndAngle = 0)
		//OutputEndAngle := 360
		//endif

		if (0 != ((*hv_OutputStartAngle)>(*hv_OutputEndAngle)))
		{
			hv_dbTmpAngle = (*hv_OutputEndAngle);
			(*hv_OutputEndAngle) = (*hv_OutputStartAngle);
			(*hv_OutputStartAngle) = hv_dbTmpAngle;
		}

		if (0 != (((*hv_OutputEndAngle)-(*hv_OutputStartAngle))<180))
		{
			(*hv_bArcLength) = 0;
		}
		else
		{
			(*hv_bArcLength) = 1;
		}
		DrawCircle(hv_WindowID, &hv_Row, &hv_Column, &hv_Radius);
		GenCircleContourXld(&ho_ContCircle, hv_Row, hv_Column, hv_Radius, (*hv_OutputStartAngle).TupleRad(),
			(*hv_OutputEndAngle).TupleRad(), "positive", 1);
		DrawXldMod(ho_ContCircle, &(*ho_OutputArcContour), hv_WindowID, "true", "true",
			"true", "true", "true");
		/*if (HDevWindowStack::IsOpen())
			DispObj(ho_InputImage, HDevWindowStack::GetActive());
		if (HDevWindowStack::IsOpen())
			DispObj((*ho_OutputArcContour), HDevWindowStack::GetActive());*/
		FitCircleContourXld((*ho_OutputArcContour), "algebraic", -1, 0, 0, 3, 2, &hv_RowCenter,
			&hv_ColCenter, &hv_RadiusCenter, &hv_StartPhi, &hv_EndPhi, &hv_PointOrder);
		GetContourXld((*ho_OutputArcContour), &hv_RowCircles, &hv_ColCircles);
		Arc_Pos_Sort(hv_RowCircles, hv_ColCircles, 0, &hv_OutputRows, &hv_OutputCols);
		//gen_cross_contour_xld (Cross1, OutputRows[0], OutputCols[0], 60, rad(45))
		//gen_cross_contour_xld (Cross1, OutputRows[|OutputRows|-1], OutputCols[|OutputCols|-1], 60, rad(45))

		AngleLl(hv_RowCenter, hv_ColCenter, hv_RowCenter, 9999, hv_RowCenter, hv_ColCenter,
			HTuple(hv_OutputRows[0]), HTuple(hv_OutputCols[0]), &hv_StartAngle);
		TupleAbs((*hv_OutputEndAngle)-(*hv_OutputStartAngle), &hv_AbsStep);
		TupleDeg(hv_StartAngle, &(*hv_OutputStartAngle));
		(*hv_OutputEndAngle) = (*hv_OutputStartAngle)+hv_AbsStep;
		//angle_ll (RowCenter, ColCenter, RowCenter, 9999, RowCenter, ColCenter, OutputRows[|OutputRows|-1], OutputCols[|OutputCols|-1], EndAngle)

		//tuple_deg (EndAngle, OutputEndAngle)
		(*hv_OutputRowCenter) = hv_RowCenter;
		(*hv_OutputColCenter) = hv_ColCenter;
		(*hv_OutputRadius) = hv_Radius;

		Halcon_Disp_Arc(ho_InputImage, (*ho_OutputArcContour), &(*ho_OutputArcCaliperRegions),
			hv_WindowID, hv_InputCaliperNum, hv_InputCaliperWidth, hv_InputCaliperHeight,
			hv_InputColor, (*hv_OutputRowCenter), (*hv_OutputColCenter), (*hv_OutputRadius),
			(*hv_OutputStartAngle), (*hv_OutputEndAngle));

		//dev_set_line_width (1)
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		if (HDevWindowStack::IsOpen())
			DispObj(ho_InputImage, HDevWindowStack::GetActive());
		if (HDevWindowStack::IsOpen())
			SetLineWidth(HDevWindowStack::GetActive(),1);
		disp_message(hv_WindowID, "Halcon_Draw_Arc err ", "window", 12, 12, "red", "false");
		return;
	}
}
inline void Halcon_Draw_Arc2 (HObject ho_InputImage, HObject *ho_OutputArcCaliperRegions,
	HObject *ho_OutputArcContour, HTuple hv_WindowID, HTuple hv_InputStartAngle,
	HTuple hv_InputEndAngle, HTuple hv_InputColor, HTuple hv_InputCaliperNum, HTuple hv_InputCaliperWidth,
	HTuple hv_InputCaliperHeight, HTuple *hv_OutputStartAngle, HTuple *hv_OutputEndAngle,
	HTuple *hv_OutputRowCenter, HTuple *hv_OutputColCenter, HTuple *hv_OutputRadius,
	HTuple *hv_bArcLength)
{
	// Local iconic variables
	HObject  ho_ContCircle;

	// Local control variables
	HTuple  hv_dbTmpAngle, hv_Row, hv_Column, hv_Radius;
	HTuple  hv_RowCenter, hv_ColCenter, hv_RadiusCenter, hv_StartPhi;
	HTuple  hv_EndPhi, hv_PointOrder, hv_RowCircles, hv_ColCircles;
	HTuple  hv_OutputRows, hv_OutputCols, hv_StartAngle, hv_EndAngle;
	HTuple  hv_Exception;

	try
	{
		/*if (HDevWindowStack::IsOpen())
		DispObj(ho_InputImage, HDevWindowStack::GetActive());
		if (HDevWindowStack::IsOpen())
		SetDraw(HDevWindowStack::GetActive(),"margin");
		if (HDevWindowStack::IsOpen())
		SetColor(HDevWindowStack::GetActive(),"green");
		if (HDevWindowStack::IsOpen())
		SetLineWidth(HDevWindowStack::GetActive(),2);
		GenEmptyObj(&(*ho_OutputArcContour));
		GenEmptyObj(&(*ho_OutputArcCaliperRegions));
		disp_message(hv_WindowID, "鼠标左键绘制，右键结束", "window", -1, -1, "red",
		"false");*/

		double dbStartAngle = (int)hv_InputStartAngle[0].D()%360 ;
		double dbEndAngle = (int)hv_InputEndAngle[0].D()%360 ;

		(*hv_OutputStartAngle) = dbStartAngle ;
		(*hv_OutputEndAngle) = dbEndAngle ;
		/*(*hv_OutputStartAngle) = hv_InputStartAngle*1.0%360.0;
		(*hv_OutputEndAngle) = hv_InputEndAngle*1.0%360.0;*/

		if (0 != ((*hv_OutputEndAngle)==(*hv_OutputStartAngle)))
		{
			(*hv_OutputEndAngle) = (*hv_OutputStartAngle)+360;
		}

		if (0 != ((*hv_OutputEndAngle)==0))
		{
			(*hv_OutputEndAngle) = 360;
		}

		if (0 != ((*hv_OutputStartAngle)>(*hv_OutputEndAngle)))
		{
			hv_dbTmpAngle = (*hv_OutputEndAngle);
			(*hv_OutputEndAngle) = (*hv_OutputStartAngle);
			(*hv_OutputStartAngle) = hv_dbTmpAngle;
		}

		if (0 != (((*hv_OutputEndAngle)-(*hv_OutputStartAngle))<180))
		{
			(*hv_bArcLength) = 0;
		}
		else
		{
			(*hv_bArcLength) = 1;
		}
		DrawCircle(hv_WindowID, &hv_Row, &hv_Column, &hv_Radius);
		GenCircleContourXld(&ho_ContCircle, hv_Row, hv_Column, hv_Radius, (*hv_OutputStartAngle).TupleRad(),
			(*hv_OutputEndAngle).TupleRad(), "positive", 1);
		DrawXldMod(ho_ContCircle, &(*ho_OutputArcContour), hv_WindowID, "true", "true",
			"true", "true", "true");
		if (HDevWindowStack::IsOpen())
			DispObj(ho_InputImage, HDevWindowStack::GetActive());
		if (HDevWindowStack::IsOpen())
			DispObj((*ho_OutputArcContour), HDevWindowStack::GetActive());
		FitCircleContourXld((*ho_OutputArcContour), "algebraic", -1, 0, 0, 3, 2, &hv_RowCenter,
			&hv_ColCenter, &hv_RadiusCenter, &hv_StartPhi, &hv_EndPhi, &hv_PointOrder);
		GetContourXld((*ho_OutputArcContour), &hv_RowCircles, &hv_ColCircles);
		Arc_Pos_Sort(hv_RowCircles, hv_ColCircles, 0, &hv_OutputRows, &hv_OutputCols);

		AngleLl(hv_RowCenter, hv_ColCenter, hv_RowCenter, 9999, hv_RowCenter, hv_ColCenter,
			HTuple(hv_OutputRows[0]), HTuple(hv_OutputCols[0]), &hv_StartAngle);
		AngleLl(hv_RowCenter, hv_ColCenter, hv_RowCenter, 9999, hv_RowCenter, hv_ColCenter,
			HTuple(hv_OutputRows[(hv_OutputRows.TupleLength())-1]), HTuple(hv_OutputCols[(hv_OutputCols.TupleLength())-1]),
			&hv_EndAngle);

		TupleDeg(hv_StartAngle, &(*hv_OutputStartAngle));
		TupleDeg(hv_EndAngle, &(*hv_OutputEndAngle));
		(*hv_OutputRowCenter) = hv_RowCenter;
		(*hv_OutputColCenter) = hv_ColCenter;
		(*hv_OutputRadius) = hv_Radius;

		Halcon_Disp_Arc(ho_InputImage, (*ho_OutputArcContour), &(*ho_OutputArcCaliperRegions),
			hv_WindowID, hv_InputCaliperNum, hv_InputCaliperWidth, hv_InputCaliperHeight,
			hv_InputColor, (*hv_OutputRowCenter), (*hv_OutputColCenter), (*hv_OutputRadius),
			(*hv_OutputStartAngle), (*hv_OutputEndAngle));

		if (HDevWindowStack::IsOpen())
			SetLineWidth(HDevWindowStack::GetActive(),1);
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		if (HDevWindowStack::IsOpen())
			DispObj(ho_InputImage, HDevWindowStack::GetActive());
		if (HDevWindowStack::IsOpen())
			SetLineWidth(HDevWindowStack::GetActive(),1);
		disp_message(hv_WindowID, "Halcon_Draw_Arc err ", "window", 12, 12, "red", "false");
		return;
	}
}

inline void fit_circle (HTuple hv_Row, HTuple hv_Column, HTuple hv_IterMax, HTuple *hv_RowOut,
		HTuple *hv_ColumnOut, HTuple *hv_Radius)
	{
		// Local iconic variables

		// Local control variables
		HTuple  hv_Mxx, hv_Myy, hv_Mxy, hv_Mxz, hv_Myz;
		HTuple  hv_Mzz, hv_N, hv_Center_Row, hv_Center_Column, hv_i;
		HTuple  hv_Xi, hv_Yi, hv_Zi, hv_Mz, hv_Cov_xy, hv_A3, hv_A2;
		HTuple  hv_A1, hv_A0, hv_A22, hv_A33, hv_xnew, hv_ynew;
		HTuple  hv_epsilon, hv_iter, hv_yold, hv_Dy, hv_xold, hv_DET;
		HTuple  hv_Center, hv_RadiusOut, hv_Exception;

		try
		{
			hv_Mxx = 0;
			hv_Myy = 0;
			hv_Mxy = 0;
			hv_Mxz = 0;
			hv_Myz = 0;
			hv_Mzz = 0;

			hv_N = hv_Row.TupleLength();
			hv_Center_Row = hv_Row.TupleMean();
			hv_Center_Column = hv_Column.TupleMean();

			{
				HTuple end_val12 = hv_N-1;
				HTuple step_val12 = 1;
				for (hv_i=0; hv_i.Continue(end_val12, step_val12); hv_i += step_val12)
				{
					hv_Xi = HTuple(hv_Column[hv_i])-hv_Center_Column;
					hv_Yi = HTuple(hv_Row[hv_i])-hv_Center_Row;
					hv_Zi = (hv_Xi*hv_Xi)+(hv_Yi*hv_Yi);
					hv_Mxy += hv_Xi*hv_Yi;
					hv_Mxx += hv_Xi*hv_Xi;
					hv_Myy += hv_Yi*hv_Yi;
					hv_Mxz += hv_Xi*hv_Zi;
					hv_Myz += hv_Yi*hv_Zi;
					hv_Mzz += hv_Zi*hv_Zi;
				}
			}

			hv_Mxx = hv_Mxx/hv_N;
			hv_Myy = hv_Myy/hv_N;
			hv_Mxy = hv_Mxy/hv_N;
			hv_Mxz = hv_Mxz/hv_N;
			hv_Myz = hv_Myz/hv_N;
			hv_Mzz = hv_Mzz/hv_N;

			hv_Mz = hv_Mxx+hv_Myy;
			hv_Cov_xy = (hv_Mxx*hv_Myy)-(hv_Mxy*hv_Mxy);
			hv_A3 = 4*hv_Mz;
			hv_A2 = ((-3*hv_Mz)*hv_Mz)-hv_Mzz;
			hv_A1 = ((((hv_Mzz*hv_Mz)+((4*hv_Cov_xy)*hv_Mz))-(hv_Mxz*hv_Mxz))-(hv_Myz*hv_Myz))-((hv_Mz*hv_Mz)*hv_Mz);
			hv_A0 = (((((hv_Mxz*hv_Mxz)*hv_Myy)+((hv_Myz*hv_Myz)*hv_Mxx))-(hv_Mzz*hv_Cov_xy))-(((2*hv_Mxz)*hv_Myz)*hv_Mxy))+((hv_Mz*hv_Mz)*hv_Cov_xy);
			hv_A22 = hv_A2+hv_A2;
			hv_A33 = (hv_A3+hv_A3)+hv_A3;

			hv_xnew = 0;
			hv_ynew = 1e+20;
			hv_epsilon = 1e-12;

			{
				HTuple end_val44 = hv_IterMax;
				HTuple step_val44 = 1;
				for (hv_iter=1; hv_iter.Continue(end_val44, step_val44); hv_iter += step_val44)
				{
					hv_yold = hv_ynew;
					hv_ynew = hv_A0+(hv_xnew*(hv_A1+(hv_xnew*(hv_A2+(hv_xnew*hv_A3)))));

					if (0 != ((hv_ynew.TupleAbs())>(hv_yold.TupleAbs())))
					{
						hv_xnew = 0;
						break;
					}

					hv_Dy = hv_A1+(hv_xnew*(hv_A22+(hv_xnew*hv_A33)));
					hv_xold = hv_xnew;
					hv_xnew = hv_xold-(hv_ynew/hv_Dy);

					if (0 != (HTuple((((hv_xnew-hv_xold).TupleAbs())/(hv_xnew+hv_epsilon))<hv_epsilon).TupleAnd(hv_xnew!=0)))
					{
						break;
					}

					if (0 != (hv_iter>=hv_IterMax))
					{
						hv_xnew = 0;
					}
					if (0 != (hv_xnew<0.))
					{
						hv_xnew = 0;
					}
				}
			}

			hv_DET = ((hv_xnew*hv_xnew)-(hv_xnew*hv_Mz))+hv_Cov_xy;
			hv_Center = 0;
			hv_Center[1] = (((hv_Mxz*(hv_Myy-hv_xnew))-(hv_Myz*hv_Mxy))/hv_DET)/2;
			hv_Center[0] = (((hv_Myz*(hv_Mxx-hv_xnew))-(hv_Mxz*hv_Mxy))/hv_DET)/2;

			(*hv_RowOut) = 0;
			(*hv_ColumnOut) = 0;
			hv_RadiusOut = 0;

			(*hv_Radius) = (((HTuple(hv_Center[0])*HTuple(hv_Center[0]))+(HTuple(hv_Center[1])*HTuple(hv_Center[1])))+hv_Mz).TupleSqrt();
			(*hv_RowOut) = HTuple(hv_Center[0])+hv_Center_Row;
			(*hv_ColumnOut) = HTuple(hv_Center[1])+hv_Center_Column;
		}
		// catch (Exception)
		catch (HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			return;
		}
	}

inline void Disp_SearchCircle (HObject ho_InImage, HObject *ho_OutCaliperRegions, HTuple hv_InWindowID,
		HTuple hv_InCaliperNum, HTuple hv_InCaliperWidth, HTuple hv_InCaliperHeight,
		HTuple hv_InColor, HTuple hv_InCircleRow, HTuple hv_InCircleCol, HTuple hv_InCircleRadius)
	{
		// Local iconic variables
		HObject  ho_ContCircle, ho_Rectangle;

		// Local control variables
		HTuple  hv_CaliperRows, hv_CaliperCols, hv_Width;
		HTuple  hv_Height, hv_RowArr, hv_ColArr, hv_i, hv_HomMat2DIdentity;
		HTuple  hv_HomMat2DRotate, hv_RowInter, hv_ColInter, hv_Angle;
		HTuple  hv_Exception;

		try
		{
			hv_CaliperRows = HTuple();
			hv_CaliperCols = HTuple();
			GenEmptyObj(&(*ho_OutCaliperRegions));

			GetImageSize(ho_InImage, &hv_Width, &hv_Height);
			GenCircleContourXld(&ho_ContCircle, hv_InCircleRow, hv_InCircleCol, hv_InCircleRadius,
				0, 6.28318, "positive", 1);
			GetContourXld(ho_ContCircle, &hv_RowArr, &hv_ColArr);

			{
				HTuple end_val9 = hv_InCaliperNum-1;
				HTuple step_val9 = 1;
				for (hv_i=0; hv_i.Continue(end_val9, step_val9); hv_i += step_val9)
				{
					if (HDevWindowStack::IsOpen())
						SetColor(HDevWindowStack::GetActive(),hv_InColor);
					HomMat2dIdentity(&hv_HomMat2DIdentity);
					HomMat2dRotate(hv_HomMat2DIdentity, ((hv_i*360.0)/(hv_InCaliperNum-1)).TupleRad(),
						hv_InCircleRow, hv_InCircleCol, &hv_HomMat2DRotate);
					AffineTransPoint2d(hv_HomMat2DRotate, HTuple(hv_RowArr[0]), HTuple(hv_ColArr[0]),
						&hv_RowInter, &hv_ColInter);
					//
					TupleConcat(hv_CaliperRows, hv_RowInter, &hv_CaliperRows);
					TupleConcat(hv_CaliperCols, hv_ColInter, &hv_CaliperCols);
					//
					AngleLl(hv_InCircleRow, hv_InCircleCol, hv_InCircleRow, 9999, hv_InCircleRow,
						hv_InCircleCol, hv_RowInter, hv_ColInter, &hv_Angle);
					GenRectangle2(&ho_Rectangle, hv_RowInter, hv_ColInter, hv_Angle, hv_InCaliperHeight,
						hv_InCaliperWidth);
					ConcatObj((*ho_OutCaliperRegions), ho_Rectangle, &(*ho_OutCaliperRegions));
				}
			}
		}
		// catch (Exception)
		catch (HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			return;
		}
	}

inline void Draw_SearchCircle (HObject ho_InImage, HObject *ho_OutCaliperRegions, HTuple hv_InWindowID,
		HTuple hv_InCaliperNum, HTuple hv_InCaliperWidth, HTuple hv_InCaliperHeight,
		HTuple hv_InColor, HTuple *hv_OutCircleRow, HTuple *hv_OutCircleCol, HTuple *hv_OutCircleRadius)
	{
		// Local control variables
		HTuple  hv_Exception;

		try
		{
			if (HDevWindowStack::IsOpen())
				SetColor(HDevWindowStack::GetActive(),hv_InColor);
			DrawCircle(hv_InWindowID, &(*hv_OutCircleRow), &(*hv_OutCircleCol), &(*hv_OutCircleRadius));
			DispCircle(hv_InWindowID, (*hv_OutCircleRow), (*hv_OutCircleCol), (*hv_OutCircleRadius));

			Disp_SearchCircle(ho_InImage, &(*ho_OutCaliperRegions), hv_InWindowID, hv_InCaliperNum,
				hv_InCaliperWidth, hv_InCaliperHeight, hv_InColor, (*hv_OutCircleRow), (*hv_OutCircleCol),
				(*hv_OutCircleRadius));
		}
		// catch (Exception)
		catch (HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			return;
		}
	}

inline void Halcon_Fit_Arc (HObject ho_InputImage, HObject ho_InputContour, HObject *ho_OutputCircleContour,
	HObject *ho_OutputCaliperOkRegions, HObject *ho_OutputCaliperNgRegions, HTuple hv_WindowID,
	HTuple hv_CaliperNum, HTuple hv_Sigma, HTuple hv_Thre, HTuple hv_Transition,
	HTuple hv_Select, HTuple hv_RoiWidth, HTuple hv_RoiHeight, HTuple hv_ifArcLength,
	HTuple hv_StartAngle, HTuple hv_EndAngle, HTuple *hv_RowCircle, HTuple *hv_ColCircle,
	HTuple *hv_Radius, HTuple *hv_OutRows, HTuple *hv_OutCols)
{
	// Local iconic variables
	HObject  ho_CaliperRegions, ho_RegionLineStart;
	HObject  ho_Rectangle, ho_TmpRegion;

	// Local control variables
	HTuple  hv_RowCenter, hv_ColCenter, hv_RadiusCenter;
	HTuple  hv_RowArr, hv_ColArr, hv_AngleRangle, hv_AngleStep;
	HTuple  hv_CaliperRows, hv_CaliperCols, hv_i, hv_HomMat2DIdentity;
	HTuple  hv_HomMat2DRotate, hv_RowInter, hv_ColInter, hv_Width;
	HTuple  hv_Height, hv_k, hv_Angle, hv_MeasureHandle, hv_RowEdge;
	HTuple  hv_ColumnEdge, hv_Amplitude, hv_Distance, hv_TmpRows;
	HTuple  hv_TmpCols, hv_m, hv_Sqrt, hv_Abs, hv_Exception;

	try
	{
		GenEmptyObj(&(*ho_OutputCircleContour));
		GenEmptyObj(&(*ho_OutputCaliperOkRegions));
		GenEmptyObj(&(*ho_OutputCaliperNgRegions));
		GenEmptyObj(&ho_CaliperRegions);
		SmallestCircleXld(ho_InputContour, &hv_RowCenter, &hv_ColCenter, &hv_RadiusCenter);
		//fit_circle_contour_xld (InputContour, 'algebraic', -1, 0, 0, 3, 2, RowCenter, ColCenter, RadiusCenter, StartPhi, EndPhi, PointOrder)
		GetContourXld(ho_InputContour, &hv_RowArr, &hv_ColArr);
		//gen_circle_contour_xld (ContCircle, RowCenter, ColCenter, RadiusCenter, 0, 6.28318, 'positive', 1)
		//
		//gen_region_contour_xld (ContCircle, InputCircleRegion, 'filled')
		//erosion_circle (InputCircleRegion, RegionErosion, 5)
		//gen_contour_region_xld (RegionErosion, Contours, 'border')
		//gen_region_contour_xld (Contours, InputCircleRegion1, 'margin')
		GenRegionLine(&ho_RegionLineStart, hv_RowCenter, hv_ColCenter, HTuple(hv_RowArr[0]),
			HTuple(hv_ColArr[0]));
		hv_AngleRangle = hv_EndAngle-hv_StartAngle;
		hv_AngleStep = (hv_AngleRangle*1.0)/(hv_CaliperNum-1);
		TupleAbs(hv_AngleStep, &hv_AngleStep);
		//
		hv_CaliperRows = HTuple();
		hv_CaliperCols = HTuple();
		(*hv_OutRows) = HTuple();
		(*hv_OutCols) = HTuple();
		//
		//
		{
			HTuple end_val25 = hv_CaliperNum-1;
			HTuple step_val25 = 1;
			for (hv_i=0; hv_i.Continue(end_val25, step_val25); hv_i += step_val25)
			{
				if (HDevWindowStack::IsOpen())
					SetColor(HDevWindowStack::GetActive(),"green");
				HomMat2dIdentity(&hv_HomMat2DIdentity);
				HomMat2dRotate(hv_HomMat2DIdentity, (hv_i*hv_AngleStep).TupleRad(), hv_RowCenter,
					hv_ColCenter, &hv_HomMat2DRotate);
				AffineTransPoint2d(hv_HomMat2DRotate, HTuple(hv_RowArr[0]), HTuple(hv_ColArr[0]),
					&hv_RowInter, &hv_ColInter);
				//
				TupleConcat(hv_CaliperRows, hv_RowInter, &hv_CaliperRows);
				TupleConcat(hv_CaliperCols, hv_ColInter, &hv_CaliperCols);
				//
				//dev_set_color ('blue')
				//disp_cross (WindowID, RowInter, ColInter, 6, 0)
			}
		}
		//
		if (0 != ((hv_CaliperRows.TupleLength())<3))
		{
			return;
		}
		//
		GetImageSize(ho_InputImage, &hv_Width, &hv_Height);
		//angle_ll (RowCenter, ColCenter, RowCenter, 5000, RowCenter, ColCenter, CaliperRows[0], CaliperCols[0], StartPhi)
		//
		{
			HTuple end_val45 = (hv_CaliperRows.TupleLength())-1;
			HTuple step_val45 = 1;
			for (hv_k=0; hv_k.Continue(end_val45, step_val45); hv_k += step_val45)
			{
				AngleLl(hv_RowCenter, hv_ColCenter, hv_RowCenter, 9999, hv_RowCenter, hv_ColCenter,
					HTuple(hv_CaliperRows[hv_k]), HTuple(hv_CaliperCols[hv_k]), &hv_Angle);
				GenRectangle2(&ho_Rectangle, HTuple(hv_CaliperRows[hv_k]), HTuple(hv_CaliperCols[hv_k]),
					hv_Angle, hv_RoiHeight, hv_RoiWidth);
				GenMeasureRectangle2(HTuple(hv_CaliperRows[hv_k]), HTuple(hv_CaliperCols[hv_k]),
					hv_Angle, hv_RoiHeight, hv_RoiWidth, hv_Width, hv_Height, "nearest_neighbor",
					&hv_MeasureHandle);
				MeasurePos(ho_InputImage, hv_MeasureHandle, hv_Sigma, hv_Thre, hv_Transition,
					hv_Select, &hv_RowEdge, &hv_ColumnEdge, &hv_Amplitude, &hv_Distance);
				if (0 != ((hv_RowEdge.TupleLength())<=0))
				{
					//
					CloseMeasure(hv_MeasureHandle);
					continue;
				}
				//
				TupleConcat((*hv_OutRows), hv_RowEdge, &(*hv_OutRows));
				TupleConcat((*hv_OutCols), hv_ColumnEdge, &(*hv_OutCols));
				ConcatObj(ho_CaliperRegions, ho_Rectangle, &ho_CaliperRegions);
				CloseMeasure(hv_MeasureHandle);
			}
		}
		//
		if (0 != (((*hv_OutRows).TupleLength())<3))
		{
			return;
		}
		//
		fit_circle((*hv_OutRows), (*hv_OutCols), 1, &(*hv_RowCircle), &(*hv_ColCircle),
			&(*hv_Radius));
		GenCircleContourXld(&(*ho_OutputCircleContour), (*hv_RowCircle), (*hv_ColCircle),
			(*hv_Radius), hv_StartAngle.TupleRad(), hv_EndAngle.TupleRad(), "positive",
			1);
		//
		hv_TmpRows = HTuple();
		hv_TmpCols = HTuple();
		hv_TmpRows = (*hv_OutRows);
		hv_TmpCols = (*hv_OutCols);
		(*hv_OutRows) = HTuple();
		(*hv_OutCols) = HTuple();
		//
		{
			HTuple end_val76 = (hv_TmpRows.TupleLength())-1;
			HTuple step_val76 = 1;
			for (hv_m=0; hv_m.Continue(end_val76, step_val76); hv_m += step_val76)
			{
				TupleSqrt((((*hv_RowCircle)-HTuple(hv_TmpRows[hv_m]))*((*hv_RowCircle)-HTuple(hv_TmpRows[hv_m])))+(((*hv_ColCircle)-HTuple(hv_TmpCols[hv_m]))*((*hv_ColCircle)-HTuple(hv_TmpCols[hv_m]))),
					&hv_Sqrt);
				TupleAbs(hv_Sqrt-(*hv_Radius), &hv_Abs);
				SelectObj(ho_CaliperRegions, &ho_TmpRegion, hv_m+1);
				if (0 != (hv_Abs<10))
				{
					TupleConcat((*hv_OutRows), HTuple(hv_TmpRows[hv_m]), &(*hv_OutRows));
					TupleConcat((*hv_OutCols), HTuple(hv_TmpCols[hv_m]), &(*hv_OutCols));
					ConcatObj((*ho_OutputCaliperOkRegions), ho_TmpRegion, &(*ho_OutputCaliperOkRegions)
						);
					continue;
				}
				ConcatObj((*ho_OutputCaliperNgRegions), ho_TmpRegion, &(*ho_OutputCaliperNgRegions)
					);
			}
		}
		if (0 != (((*hv_OutRows).TupleLength())<3))
		{
			return;
		}
		//
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		//if (|MeasureHandle|>0)
		//close_measure (MeasureHandle)
		//endif
		if (HDevWindowStack::IsOpen())
			DispObj(ho_InputImage, HDevWindowStack::GetActive());
		disp_message(hv_WindowID, "Halcon_Fit_Arc Throw err", "window", -1, -1, "red",
			"false");
		return;
		//
	}
}

inline void Halcon_Fit_Arc2 (HObject ho_InImage, HObject ho_InArcContour, HObject *ho_OutArcContour,
	HObject *ho_OutCaliperRegions, HTuple hv_InWindowID, HTuple hv_InCaliperNum,
	HTuple hv_InCaliperWidth, HTuple hv_InCaliperHeight, HTuple hv_InSigma, HTuple hv_InThre,
	HTuple hv_InTranstion, HTuple hv_InSelect, HTuple hv_InStartAngle, HTuple hv_InEndAngle,
	HTuple *hv_OutArcRow, HTuple *hv_OutArcCol, HTuple *hv_OutArcRadius, HTuple *hv_OutArcRows,
	HTuple *hv_OutArcCols, HTuple *hv_OutRet)
{
	// Local iconic variables

	// Local control variables
	HTuple  hv_InStartRad, hv_InEndRad, hv_Width;
	HTuple  hv_Height, hv_RowCenter, hv_ColCenter, hv_RadiusCenter;
	HTuple  hv_StartPhi, hv_EndPhi, hv_PointOrder, hv_MetrologyHandle;
	HTuple  hv_MetrologyCircleIndices, hv_CircleParameter, hv_Exception;

	try
	{
		GenEmptyObj(&(*ho_OutArcContour));
		GenEmptyObj(&(*ho_OutCaliperRegions));

		(*hv_OutArcRows) = HTuple();
		(*hv_OutArcCols) = HTuple();
		(*hv_OutArcRow) = HTuple();
		(*hv_OutArcCol) = HTuple();
		(*hv_OutArcRadius) = HTuple();
		TupleRad(hv_InStartAngle, &hv_InStartRad);
		TupleRad(hv_InEndAngle, &hv_InEndRad);
		GetImageSize(ho_InImage, &hv_Width, &hv_Height);
		FitCircleContourXld(ho_InArcContour, "algebraic", -1, 0, 0, 3, 2, &hv_RowCenter,
			&hv_ColCenter, &hv_RadiusCenter, &hv_StartPhi, &hv_EndPhi, &hv_PointOrder);
		//DispCircle(200000, hv_RowCenter, hv_ColCenter, hv_RadiusCenter);

		CreateMetrologyModel(&hv_MetrologyHandle);
		SetMetrologyModelImageSize(hv_MetrologyHandle, hv_Width, hv_Height);
		AddMetrologyObjectGeneric(hv_MetrologyHandle, "circle", (hv_RowCenter.TupleConcat(hv_ColCenter)).TupleConcat(hv_RadiusCenter),
			hv_InCaliperHeight, hv_InCaliperWidth, hv_InSigma, hv_InThre, (HTuple("start_phi").Append("end_phi")),
			hv_InStartRad.TupleConcat(hv_InEndRad), &hv_MetrologyCircleIndices);
		SetMetrologyObjectParam(hv_MetrologyHandle, hv_MetrologyCircleIndices, "num_measures",
			hv_InCaliperNum);
		SetMetrologyObjectParam(hv_MetrologyHandle, hv_MetrologyCircleIndices, "measure_transition",
			hv_InTranstion);
		SetMetrologyObjectParam(hv_MetrologyHandle, hv_MetrologyCircleIndices, "measure_select",
			hv_InSelect);
		SetMetrologyObjectParam(hv_MetrologyHandle, hv_MetrologyCircleIndices, "min_score",
			0.3);
		//
		ApplyMetrologyModel(ho_InImage, hv_MetrologyHandle);
		GetMetrologyObjectResult(hv_MetrologyHandle, hv_MetrologyCircleIndices, "all",
			"result_type", "all_param", &hv_CircleParameter);
		if (0 != (((hv_CircleParameter.TupleLength())/3)!=1))
		{
			ClearMetrologyModel(hv_MetrologyHandle);
			(*hv_OutRet) = 0;
			return;
		}
		GetMetrologyObjectResultContour(&(*ho_OutArcContour), hv_MetrologyHandle, "all",
			"all", 1.5);
		GetMetrologyObjectMeasures(&(*ho_OutCaliperRegions), hv_MetrologyHandle, "all",
			"all", &(*hv_OutArcRows), &(*hv_OutArcCols));
		//gen_cross_contour_xld (Cross, Row1, Column1, 6, 0.785398)
		ClearMetrologyModel(hv_MetrologyHandle);
		//
		//
		//
		TupleConcat((*hv_OutArcRow), HTuple(hv_CircleParameter[0]), &(*hv_OutArcRow));
		TupleConcat((*hv_OutArcCol), HTuple(hv_CircleParameter[1]), &(*hv_OutArcCol));
		TupleConcat((*hv_OutArcRadius), HTuple(hv_CircleParameter[2]), &(*hv_OutArcRadius));

		(*hv_OutRet) = 1;
	}
	// catch (Exception)
	catch (HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&hv_Exception);
		(*hv_OutRet) = -1;
		return;
	}
}

inline void SaveOkDumpWindowLog(HTuple hWindowID,int nCamID ,CString strExternInfo = _T(""))
{
	CString strRootPath = _T("D:\\ImageLog\\") ;
	if(!vPathIsExist(strRootPath))
	{
		if(!::CreateDirectory(strRootPath,NULL))
		{
			strRootPath = _T("");
		}
	}

	CString strSecondPath = strRootPath + _T("DumpOk\\") ;
	if(!vPathIsExist(strSecondPath))
	{
		if(!::CreateDirectory(strSecondPath,NULL))
		{
			strSecondPath = _T("");
		}
	}

	SYSTEMTIME tm;
	memset(&tm,0,sizeof(tm));
	::GetLocalTime(&tm);
	CString strTextFile ;
	CString strTime ;
	DWORD dwYear,dwMonth,dwDay ;
	DWORD dwHour,dwMinute ,dwSecond;
	dwYear = tm.wYear ;
	dwMonth = tm.wMonth ;
	dwDay = tm.wDay ;
	dwHour = tm.wHour ;
	dwMinute = tm.wMinute ;
	dwSecond = tm.wSecond ;
	strTextFile.Format(_T("%d_%d_%d\\"),dwYear,dwMonth,dwDay) ;
	strTime.Format(_T("%d(时)_%d(分)_%d(秒).jpg"),dwHour,dwMinute,dwSecond) ;

	try
	{
		USES_CONVERSION;

		CString strThirdPath = strSecondPath + strTextFile ;
		if(!vPathIsExist(strThirdPath))
		{
			if(!::CreateDirectory(strThirdPath,NULL))
			{
				strThirdPath = _T("");
			}
		}

		CString strChildFolder(_T("")) ;
		strChildFolder.Format(_T("Cam%d\\"),nCamID+1) ;
		CString strFouthPath = strThirdPath + strChildFolder ;
		if(!vPathIsExist(strFouthPath))
		{
			if(!::CreateDirectory(strFouthPath,NULL))
			{
				strFouthPath = _T("");
			}
		}

		CString strSavePath = strFouthPath + strExternInfo + _T("_") +  strTime;
		HObject hDumpImage ;
		DumpWindowImage(&hDumpImage,hWindowID) ;
		WriteImage(hDumpImage,"jpg",0,W2A(strSavePath)) ;
	}
	catch (...)
	{
	}

    return  ;
}

inline void SaveNgDumpWindowLog(HTuple hWindowID,int nCamID ,CString strExternInfo = _T(""))
{
	CString strRootPath = _T("D:\\ImageLog\\") ;
	if(!vPathIsExist(strRootPath))
	{
		if(!::CreateDirectory(strRootPath,NULL))
		{
			strRootPath = _T("");
		}
	}

	CString strSecondPath = strRootPath + _T("DumpNg\\") ;
	if(!vPathIsExist(strSecondPath))
	{
		if(!::CreateDirectory(strSecondPath,NULL))
		{
			strSecondPath = _T("");
		}
	}

	SYSTEMTIME tm;
	memset(&tm,0,sizeof(tm));
	::GetLocalTime(&tm);
	CString strTextFile ;
	CString strTime ;
	DWORD dwYear,dwMonth,dwDay ;
	DWORD dwHour,dwMinute ,dwSecond;
	dwYear = tm.wYear ;
	dwMonth = tm.wMonth ;
	dwDay = tm.wDay ;
	dwHour = tm.wHour ;
	dwMinute = tm.wMinute ;
	dwSecond = tm.wSecond ;
	strTextFile.Format(_T("%d_%d_%d\\"),dwYear,dwMonth,dwDay) ;
	strTime.Format(_T("%d(时)_%d(分)_%d(秒).jpg"),dwHour,dwMinute,dwSecond) ;

	try
	{
		USES_CONVERSION;

		CString strThirdPath = strSecondPath + strTextFile ;
		if(!vPathIsExist(strThirdPath))
		{
			if(!::CreateDirectory(strThirdPath,NULL))
			{
				strThirdPath = _T("");
			}
		}

		CString strChildFolder(_T("")) ;
		strChildFolder.Format(_T("Cam%d\\"),nCamID+1) ;
		CString strFouthPath = strThirdPath + strChildFolder ;
		if(!vPathIsExist(strFouthPath))
		{
			if(!::CreateDirectory(strFouthPath,NULL))
			{
				strFouthPath = _T("");
			}
		}

		CString strSavePath = strFouthPath + strExternInfo + _T("_") +  strTime;
		HObject hDumpImage ;
		DumpWindowImage(&hDumpImage,hWindowID) ;
		WriteImage(hDumpImage,"jpg",0,W2A(strSavePath)) ;
	}
	catch (...)
	{
	}

	return  ;
}

inline void SaveOkBmpWindowLog(HObject hImage,int nCamID ,CString strExternInfo = _T(""))
{
	CString strRootPath = _T("D:\\ImageLog\\") ;
	if(!vPathIsExist(strRootPath))
	{
		if(!::CreateDirectory(strRootPath,NULL))
		{
			strRootPath = _T("");
		}
	}

	CString strSecondPath = strRootPath + _T("BmpOk\\") ;
	if(!vPathIsExist(strSecondPath))
	{
		if(!::CreateDirectory(strSecondPath,NULL))
		{
			strSecondPath = _T("");
		}
	}

	SYSTEMTIME tm;
	memset(&tm,0,sizeof(tm));
	::GetLocalTime(&tm);
	CString strTextFile ;
	CString strTime ;
	DWORD dwYear,dwMonth,dwDay ;
	DWORD dwHour,dwMinute ,dwSecond;
	dwYear = tm.wYear ;
	dwMonth = tm.wMonth ;
	dwDay = tm.wDay ;
	dwHour = tm.wHour ;
	dwMinute = tm.wMinute ;
	dwSecond = tm.wSecond ;
	strTextFile.Format(_T("%d_%d_%d\\"),dwYear,dwMonth,dwDay) ;
	strTime.Format(_T("%d(时)_%d(分)_%d(秒).bmp"),dwHour,dwMinute,dwSecond) ;

	try
	{
		USES_CONVERSION;

		CString strThirdPath = strSecondPath + strTextFile ;
		if(!vPathIsExist(strThirdPath))
		{
			if(!::CreateDirectory(strThirdPath,NULL))
			{
				strThirdPath = _T("");
			}
		}

		CString strChildFolder(_T("")) ;
		strChildFolder.Format(_T("Cam%d\\"),nCamID+1) ;
		CString strFouthPath = strThirdPath + strChildFolder ;
		if(!vPathIsExist(strFouthPath))
		{
			if(!::CreateDirectory(strFouthPath,NULL))
			{
				strFouthPath = _T("");
			}
		}

		CString strSavePath = strFouthPath + strExternInfo + _T("_") +  strTime;
		WriteImage(hImage,"bmp",0,W2A(strSavePath)) ;
	}
	catch (...)
	{
	}

	return  ;
}

inline void SaveNgBmpWindowLog(HObject hImage,int nCamID ,CString strExternInfo = _T(""))
{
	CString strRootPath = _T("D:\\ImageLog\\") ;
	if(!vPathIsExist(strRootPath))
	{
		if(!::CreateDirectory(strRootPath,NULL))
		{
			strRootPath = _T("");
		}
	}

	CString strSecondPath = strRootPath + _T("BmpNg\\") ;
	if(!vPathIsExist(strSecondPath))
	{
		if(!::CreateDirectory(strSecondPath,NULL))
		{
			strSecondPath = _T("");
		}
	}

	SYSTEMTIME tm;
	memset(&tm,0,sizeof(tm));
	::GetLocalTime(&tm);
	CString strTextFile ;
	CString strTime ;
	DWORD dwYear,dwMonth,dwDay ;
	DWORD dwHour,dwMinute ,dwSecond;
	dwYear = tm.wYear ;
	dwMonth = tm.wMonth ;
	dwDay = tm.wDay ;
	dwHour = tm.wHour ;
	dwMinute = tm.wMinute ;
	dwSecond = tm.wSecond ;
	strTextFile.Format(_T("%d_%d_%d\\"),dwYear,dwMonth,dwDay) ;
	strTime.Format(_T("%d(时)_%d(分)_%d(秒).bmp"),dwHour,dwMinute,dwSecond) ;

	try
	{
		USES_CONVERSION;

		CString strThirdPath = strSecondPath + strTextFile ;
		if(!vPathIsExist(strThirdPath))
		{
			if(!::CreateDirectory(strThirdPath,NULL))
			{
				strThirdPath = _T("");
			}
		}

		CString strChildFolder(_T("")) ;
		strChildFolder.Format(_T("Cam%d\\"),nCamID+1) ;
		CString strFouthPath = strThirdPath + strChildFolder ;
		if(!vPathIsExist(strFouthPath))
		{
			if(!::CreateDirectory(strFouthPath,NULL))
			{
				strFouthPath = _T("");
			}
		}

		CString strSavePath = strFouthPath + strExternInfo +  _T("_") + strTime;
		WriteImage(hImage,"bmp",0,W2A(strSavePath)) ;
	}
	catch (...)
	{
	}

	return  ;
}