简述:
    VisionProject是一款能够简单配置相机硬件、光源硬件、通讯模块、流程模块的非标视觉系统，致力快速解决交付公司7~8成视觉非标项目。
应用场景:
    激光镭射、平台/机械手点胶、机械手引导、上下料组装、对位贴合、3C行业测量、3C行业检测等其他行业应用。    

开发节点

Date:2020-10-12
Detail:
      1.设计界面及添加界面资源。
      
Date:2020-10-15
Detail:
      1.添加工具箱(使用TabControl控件待解决).
      
Date:2020-10-22
Detail:
      1.添加工具箱(使用CPropertySheet 多页面切换):视觉硬件，视觉标定.
 
      
Date:2020-10-23
Detail:
      1.添加工具箱(使用CPropertySheet 多页面切换):2D视觉,2D视觉逻辑,系统.
      2.添加WorkFlow界面及管理类。
      
Date:2020-10-24
Detail:
      1.添加视觉工具基类定义(CVisionBase)及视觉基础数据类型。
    
Date:2020-10-25
Detail:
      1.添加NewDialog页(可以新建流程名及工程名)。 
      2.修改CPropertySheet 自动适应bug. 
      3.添加列表添加工具.
      
Date:2020-11-04
Detail:
      1.添加WorkFlow节点输入关联对话框(采用TurboDLL 树形控件(支持拖拽功能))。
      2.添加视觉工具模块化库接口定义。
      3.添加VisionDll视觉库工程。(管理视觉工具)
      4.添加VisionShapeModel视觉库工程。(标准形状模板工具)
      5.添加VisionFitLine视觉库工程。(找线工具)
      6.SystemData.h添加工具与工具节点参数关联树形数据结构。
      
Date:2020-11-09
Detail:
     1.规范枚举数据定义。
     2.添加CameraDll视觉库工程。(管理相机工具)
     3.添加HalconCamera相机工程.(Halcon驱动相机SDK)
     4.添加BaslerCamera相机工程.(Basler相机SDK)
     5.添加HardWareData.h数据定义.(管理视觉硬件头文件)
     
Date:2020-11-11
Detail:
     1.添加相机管理界面。
     2.添加新建相机界面。
     3.编写实现HalconCamera相机工程接口。
     4.添加相机触发参数设置。
     5.修复界面显示十字叉bug.
     
Date:2020-11-16
Detail:
     1.添加Halcon修改相机曝光机增益的功能.
     2.修复界面显示及十字叉bug.
     3.添加实时显示才能触发修改曝光及增益参数.
     4.修改视觉工具输入输出接口。
     5.使用Boost::Any实现所有类型数据的扩充(2D视觉数据,3D视觉数据,显示特征数据,
     各类型硬件数据等),无需装箱拆箱操作优化系统执行效率。
     6.实现Vision2DCamera实时采图、单张采图、曝光增益的设计。
     7.序列化及反序列化Vision2DCamera.
     8.添加多视图控件管理。
     
Date:2020-11-21
Detail:
     1.添加Project数据类（ProjectData).
     2.Boost::xml 序列化相机配置及反序列化相机配置。
     3.添加Project序列化与反序列化.
     4.添加Imageview序列化与反序列化.
     
Date:2020-12-04
Detail:
     1.Boost库切换至boost_1_56_0.
     2.添加Lua5.1.5功能。
     3.添加Luabind0.9.1功能。
     4.Boost::Xml序列化管理切换成二进制序列化。
     
Date:2020-12-07
Detail:
     1.添加全局变量管理。
     2.添加全局变量脚本接口。
     3.添加通信基类工程。
     4.添加串口通信工程。
     5.添加网络通信工程。
     
Date:2020-12-23
Detail:
     1.添加ModbusDll工程。
     2.添加ModbusRtuMaster工程。
     3.添加ModbusRtuSlave工程。
     4.添加ModbusTcpMaster工程。
     5.添加ModbusTcpSlave工程。
     
Date:2020-12-29
Detail:
     1.修改Comm232通信。
     2.修改CommTcp通信。
     3.移除通信包工程。
     
Date:2020-12-30
Detail:
     1.修改显示界面最小化,软件崩溃bug.
     2.添加Comm通信脚本接口.
     3.添加WorkFlow新建脚本文件及编辑脚本文件功能.
     
Date:2020-01-05
Detail:
     1.修改通信包。
     2.修改通信管理界面。
     3.修改通信脚本接口。
     
Date:2020-01-09
Detail:
     1.添加VisionCommRead工具。
     2.添加control2类包。
     3.添加VisionCommRead工具NewLabel类替换成LabelEx类。
     4.测试VisionCommRead工具。
     5.添加VisionCommWrite工具。
     6.修改Comm232 发送数据句柄增加bug.
     
Date:2020-01-15
Detail:
     1.修改ImageViewDlg控件NewLabel改为LabelEx。
     2.修改MyStatic移动到control2文件夹。
     3.添加VisionModbusRead工程。
     4.添加VisionModbusWrite工程。