#pragma once

class CJob
{
public:
	CJob(void);
	CJob(int toGenerateID)
	{
		m_ID=toGenerateID+1;
	}
public:
	~CJob(void);
	int m_ID;//��ҵ��
	int m_size;//��ҵ��ռ�ڴ��С
};
