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
	int m_ID;//作业号
	int m_size;//作业所占内存大小
};
