// OS2Dlg.h : header file
//

#pragma once
#include "MemoryListUnit.h"
#include <sstream>
#include <string>
#include <cstring>
#include "atltypes.h"

// COS2Dlg dialog
class COS2Dlg : public CDialog
{
// Construction
public:
	COS2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_OS2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnEnChangeEdit2();
public:
	afx_msg void OnBnClickedButton6();
public:
	afx_msg void OnBnClickedButtonAuto();
public:
	afx_msg void OnBnClickedButtonChangalgorithm();
public:
	afx_msg void OnBnClickedButtonApply();
public:
	afx_msg void OnBnClickedButtonFree();
public:
	CMemoryListUnit* memorylist_head;
public:
	void MyInit(bool init);
public:
	// //���Լ��Ļ�ͼ����
	void MyPaint(void);
public:
	// �ڴ�������һ����ҵ
	bool AddJob(void);
public:
	afx_msg void OnEnChangeEditSize();
public:
	afx_msg void OnEnChangeEditId();
public:
	afx_msg void OnDestroy();
public:
	// �ҵĹرպ���������delete��new�����Ķ���
	void MyClose(void);
public:
	CString size_to_apply;
public:
	int ID_to_increase;
public:
	// ��CStringתΪfloat
	float CStringToFloat(CString cstr);
	enum AlgorithmState{FirstFit,BestFit};
public:
	AlgorithmState algorithm_state;
public:
	// ��ʾ��ǰ�㷨
	CString cstr_algorithm;
public:
	afx_msg void OnStnClickedStaticAlgorithm();
public:
	// �״���Ӧ�㷨
	bool FirstFitAlgorithm(int iSize);
public:
	bool BestFitAlgorithm(int iSize);
public:
	bool FreeMemory(int iJobID);
public:
	// ��Edit_free��Ӧ
	CString memory_to_free;
public:
	// �ӿ����ڴ���л���һ���ָ�Job
	bool SplitMemoryListUnit(CMemoryListUnit* pTemp,int iSize);
	int memory_capacity;//�ڴ���������ʼ��Ϊ640
	enum OperationState{Apply,Free};//����״̬��ö�٣�Ϊ�Զ���ʾ��׼��
public:
	// //��װ�����뺯�����ɹ�BUTTONApply���Զ���ʾ����
	void MyApply(float fSize);
public:
	// //��װ��Free������������ButtonFree���Զ���ʾ�ĵ���
	void MyFree(float fID);
public:
	afx_msg void OnBnClickedButtonClear();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	int m_timer;
public:
	afx_msg void OnBnClickedButtonPause();
public:
	afx_msg void OnBnClickedButtonOver();
public:
	// Ҫ��ͼ�ľ�������
	CRect rectToDraw;
};
