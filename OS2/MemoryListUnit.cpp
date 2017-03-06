#include "StdAfx.h"
#include "MemoryListUnit.h"

CMemoryListUnit::CMemoryListUnit(void)//初始化第一个内存表单元
{
	Size=640;//内存容量
	BeginAddress=0;//起始地址
	State=Free;
	pToJob=NULL;
	Next=NULL;

	//程序中唯一的硬编码，用于控制要显示的Rect的位置
	left=25;
	top=70;
	rect_height=90;

	rect.SetRect(CPoint(left+BeginAddress,top),CPoint(left+BeginAddress+Size,top+rect_height));
}

CMemoryListUnit::CMemoryListUnit(int iSize,int iAddress)//一般的初始化
{
	Size=iSize;//内存容量
	BeginAddress=iAddress;//起始地址
	State=Free;
	pToJob=NULL;//待修改
	Next=NULL;

	//程序中唯一的硬编码，用于控制要显示的Rect的位置
	left=25;
	top=70;
	rect_height=90;

	rect.SetRect(CPoint(left+BeginAddress,top),CPoint(left+BeginAddress+Size,top+rect_height));
}

void CMemoryListUnit::ResetRect()
{
	rect.SetRect(CPoint(left+BeginAddress,top),CPoint(left+BeginAddress+Size,top+rect_height));
}

CMemoryListUnit::~CMemoryListUnit(void)
{
}
