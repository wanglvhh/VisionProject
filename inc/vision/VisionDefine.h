#pragma once

//�ж�ָ��
#define ASSERT_POINT(lp)        {if(NULL == lp){return;}}
//ɾ��ָ��
#define DELETE_POINT(lp)		{if(lp){delete (lp);(lp)=NULL;}}
//�����С
#define ARRSIZE(x)              (sizeof(x)/sizeof(x[0]))

//��ɫ����
#define SYSTEM_BK_COLOR                   RGB(245, 245, 245)                    //������ɫ
#define BTNST_COLOR_FG_IN_COLOR           RGB(255, 0, 0)                        //��ťѡ����ɫ
#define BTNST_COLOR_FG_OUT_COLOR          RGB(0, 0, 250)                        //��ť��ѡ����ɫ
#define SYSTEM_RED                        RGB(255, 0, 0)                        //ϵͳ��ɫ
#define SYSTEM_GREEN                      RGB(0, 255, 0)                        //ϵͳ��ɫ
#define SYSTEM_BLUE                       RGB(0, 0, 255)                        //ϵͳ��ɫ
#define SYSTEM_BLACK                      RGB(0, 0, 0)                          //ϵͳ��ɫ
#define SYSTEM_WHITE                      RGB(255, 255,255)                     //ϵͳ��ɫ
#define SYSTEM_FONT_COLOR                 RGB(0, 50, 255)                       //ϵͳ������ɫ
