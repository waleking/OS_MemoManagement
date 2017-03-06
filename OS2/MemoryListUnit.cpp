#include "StdAfx.h"
#include "MemoryListUnit.h"

CMemoryListUnit::CMemoryListUnit(void)//��ʼ����һ���ڴ��Ԫ
{
	Size=640;//�ڴ�����
	BeginAddress=0;//��ʼ��ַ
	State=Free;
	pToJob=NULL;
	Next=NULL;

	//������Ψһ��Ӳ���룬���ڿ���Ҫ��ʾ��Rect��λ��
	left=25;
	top=70;
	rect_height=90;

	rect.SetRect(CPoint(left+BeginAddress,top),CPoint(left+BeginAddress+Size,top+rect_height));
}

CMemoryListUnit::CMemoryListUnit(int iSize,int iAddress)//һ��ĳ�ʼ��
{
	Size=iSize;//�ڴ�����
	BeginAddress=iAddress;//��ʼ��ַ
	State=Free;
	pToJob=NULL;//���޸�
	Next=NULL;

	//������Ψһ��Ӳ���룬���ڿ���Ҫ��ʾ��Rect��λ��
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
