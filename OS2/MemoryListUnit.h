#pragma once
#include "Job.h"

class CMemoryListUnit
{
public:
	enum MemoryState{Occupied,Free};
	CMemoryListUnit(void);//��ʼ����һ���ڴ��Ԫ
	CMemoryListUnit(int iSize,int iAddress);//һ��ĳ�ʼ��
	void ResetRect();//���þ�������
	~CMemoryListUnit(void);
	int BeginAddress;//��ʼ�ĵ�ַ
	int	Size;//��С
	MemoryState State;//״̬��Occupied,Free
	CMemoryListUnit* Next;//ָ����һ���ڴ������Ԫ��ָ��
	CJob* pToJob;//ָ��Job��ָ��
//������
	CRect rect;
	int rect_height;//���θ߶�
	int rect_width;//���ο��
	int top;//��ʼ��topֵ,��ֵ
	int left;//��ʼ��leftֵ����ֵ������rect.left+BeignAddress
};
