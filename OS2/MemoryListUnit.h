#pragma once
#include "Job.h"

class CMemoryListUnit
{
public:
	enum MemoryState{Occupied,Free};
	CMemoryListUnit(void);//初始化第一个内存表单元
	CMemoryListUnit(int iSize,int iAddress);//一般的初始化
	void ResetRect();//重置矩形区域
	~CMemoryListUnit(void);
	int BeginAddress;//开始的地址
	int	Size;//大小
	MemoryState State;//状态：Occupied,Free
	CMemoryListUnit* Next;//指向下一个内存分区表单元的指针
	CJob* pToJob;//指向Job的指针
//数据区
	CRect rect;
	int rect_height;//矩形高度
	int rect_width;//矩形宽度
	int top;//初始的top值,定值
	int left;//初始的left值，定值，用于rect.left+BeignAddress
};
