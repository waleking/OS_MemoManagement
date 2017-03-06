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
	// //我自己的绘图代码
	void MyPaint(void);
public:
	// 内存中增加一个作业
	bool AddJob(void);
public:
	afx_msg void OnEnChangeEditSize();
public:
	afx_msg void OnEnChangeEditId();
public:
	afx_msg void OnDestroy();
public:
	// 我的关闭函数，用于delete掉new出来的对象
	void MyClose(void);
public:
	CString size_to_apply;
public:
	int ID_to_increase;
public:
	// 将CString转为float
	float CStringToFloat(CString cstr);
	enum AlgorithmState{FirstFit,BestFit};
public:
	AlgorithmState algorithm_state;
public:
	// 显示当前算法
	CString cstr_algorithm;
public:
	afx_msg void OnStnClickedStaticAlgorithm();
public:
	// 首次适应算法
	bool FirstFitAlgorithm(int iSize);
public:
	bool BestFitAlgorithm(int iSize);
public:
	bool FreeMemory(int iJobID);
public:
	// 与Edit_free对应
	CString memory_to_free;
public:
	// 从空闲内存块中划出一部分给Job
	bool SplitMemoryListUnit(CMemoryListUnit* pTemp,int iSize);
	int memory_capacity;//内存容量，初始化为640
	enum OperationState{Apply,Free};//操作状态的枚举，为自动演示而准备
public:
	// //封装的申请函数，可供BUTTONApply和自动演示调用
	void MyApply(float fSize);
public:
	// //封装的Free函数，用于让ButtonFree和自动演示的调用
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
	// 要绘图的矩形区域
	CRect rectToDraw;
};
