#pragma once

//枚举头文件
//图像旋转
enum IMG_ROTATE
{
	//原图
	IMG_R0 = 0,
	//旋转90
	IMG_R90,
	//旋转180
	IMG_R180,
	//旋转270
	IMG_R270,
};

//图像镜像
enum IMG_MIRROR
{
	//原图
	IMG_NORMAL = 0,
	//水平镜像
	IMG_MIRROR_H,
	//竖直镜像
	IMG_MIRROR_V,
};