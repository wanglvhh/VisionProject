#pragma once

//系统头文件
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "halconcpp.h"
using namespace HalconCpp;

#include <iostream>
#include <stdlib.h>
#include <type_traits>
using namespace std;

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

#include "..\Tools\TurboDLL\xTurboDLL.h"

#include "..\inc\common\vFunc.h"

#include "..\inc\common\EasySize.h"

#include "..\inc\common\CVisionFunctionClass.h"

#include "..\inc\common\BaseIni.h"

#include "..\inc\control\BtnST.h"

#include "..\inc\control\WinXPButtonST.h"

#include "..\inc\control\ListBoxST.h"

#include "..\inc\control\NewLabel.h"

#include "..\inc\control\Led.h"

#include "..\inc\control\MyTab.h"

#include "..\inc\control\ListCtrlCl.h"

#include "..\inc\control\ProSliderCtrl.h"

#include "..\inc\control\SkinClass.h"

#include "..\inc\control\SkinRadio.h"

#include "..\inc\control\BitmapCtrl.h"

#include "..\inc\control2\LabelEx.h"

#include "..\inc\control2\MyStatic.h"

#include "..\inc\vision\VisionBase.h"

#include "..\inc\vision\VisionDefine.h"

#include "..\inc\vision\HardWareData.h"

#include "..\inc\vision\SystemFunction.h"

#include "..\inc\vision\CommunicationData.h"

#include "..\inc\vision\CommunicationNode.h"

#include "VisionEnum.h"

#include "VisionGlobal.h"

#include "SystemData.h"

#include "ProjectData.h"
