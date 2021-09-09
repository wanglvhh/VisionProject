#pragma once

//判断指针
#define ASSERT_POINT(lp)        {if(NULL == lp){return;}}
//删除指针
#define DELETE_POINT(lp)		{if(lp){delete (lp);(lp)=NULL;}}
//数组大小
#define ARRSIZE(x)              (sizeof(x)/sizeof(x[0]))

//颜色定义
#define SYSTEM_BK_COLOR                   RGB(245, 245, 245)                    //背景颜色
#define BTNST_COLOR_FG_IN_COLOR           RGB(255, 0, 0)                        //按钮选中颜色
#define BTNST_COLOR_FG_OUT_COLOR          RGB(0, 0, 250)                        //按钮不选中颜色
#define SYSTEM_RED                        RGB(255, 0, 0)                        //系统红色
#define SYSTEM_GREEN                      RGB(0, 255, 0)                        //系统绿色
#define SYSTEM_BLUE                       RGB(0, 0, 255)                        //系统蓝色
#define SYSTEM_BLACK                      RGB(0, 0, 0)                          //系统黑色
#define SYSTEM_WHITE                      RGB(255, 255,255)                     //系统白色
#define SYSTEM_FONT_COLOR                 RGB(0, 50, 255)                       //系统字体颜色
