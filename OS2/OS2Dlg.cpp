// OS2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "OS2.h"
#include "OS2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// COS2Dlg dialog


COS2Dlg::COS2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(COS2Dlg::IDD, pParent)
	, memorylist_head(NULL)
	, size_to_apply(L"")
	, ID_to_increase(0)
	, memory_capacity(640)
	, cstr_algorithm(_T(""))
	, memory_to_free(_T(""))
	, m_timer(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COS2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Size, size_to_apply);
	DDX_Text(pDX, IDC_STATIC_Algorithm, cstr_algorithm);
	DDX_Text(pDX, IDC_EDIT_ID, memory_to_free);
}

BEGIN_MESSAGE_MAP(COS2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Auto, &COS2Dlg::OnBnClickedButtonAuto)
	ON_BN_CLICKED(IDC_BUTTON_ChangAlgorithm, &COS2Dlg::OnBnClickedButtonChangalgorithm)
	ON_BN_CLICKED(IDC_BUTTON_Apply, &COS2Dlg::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_Free, &COS2Dlg::OnBnClickedButtonFree)
	ON_EN_CHANGE(IDC_EDIT_Size, &COS2Dlg::OnEnChangeEditSize)
	ON_EN_CHANGE(IDC_EDIT_ID, &COS2Dlg::OnEnChangeEditId)
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_Clear, &COS2Dlg::OnBnClickedButtonClear)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Pause, &COS2Dlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_Over, &COS2Dlg::OnBnClickedButtonOver)
END_MESSAGE_MAP()


// COS2Dlg message handlers

BOOL COS2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MyInit(true);

	InvalidateRect(&rectToDraw,true);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COS2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COS2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		MyPaint();
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COS2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COS2Dlg::OnBnClickedButtonAuto()
{
	SetTimer(1, 1000, NULL);
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Over)->EnableWindow(TRUE);
	//////////////////////////////////////////////////////////////////////////
	GetDlgItem(IDC_BUTTON_Auto)->EnableWindow(FALSE);
	//////////////////////////////////////////////////////////////////////////
	GetDlgItem(IDC_BUTTON_Apply)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Free)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Clear)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ChangAlgorithm)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_Size)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_ID)->EnableWindow(FALSE);
	// TODO: Add your control notification handler code here
}

void COS2Dlg::OnBnClickedButtonChangalgorithm()
{
	//切换算法
	if (algorithm_state==FirstFit)
	{
		//GetDlgItem(IDC_STATIC_Algorithm)->DrawCaption()
		cstr_algorithm=L"当前使用最佳适应算法";
		UpdateData(FALSE);
		algorithm_state=BestFit;
	}
	else
	{
		cstr_algorithm=L"当前使用首次适应算法";
		UpdateData(FALSE);
		algorithm_state=FirstFit;
	}
}

void COS2Dlg::OnBnClickedButtonApply()
{
	UpdateData(true);
	float fSize=CStringToFloat(size_to_apply);
	MyApply(fSize);
}

void COS2Dlg::OnBnClickedButtonFree()
{
	UpdateData(true);
	float fID=CStringToFloat(memory_to_free);
	MyFree(fID);
	
}

void COS2Dlg::MyInit(bool init)//我的初始化程序
{
	if(init==true)//第一次使用该函数
	{
		cstr_algorithm=L"当前使用首次适应算法";
		UpdateData(false);
		algorithm_state=FirstFit;//默认初始算法为首次适应
	}
	ID_to_increase=0;
	memorylist_head=new CMemoryListUnit;
	rectToDraw=memorylist_head->rect;
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Over)->EnableWindow(FALSE);
}

 //我自己的绘图代码
void COS2Dlg::MyPaint(void)
{
	::OutputDebugString(L"MyPaint is called\n");
	CPaintDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	CBrush brushWhite(RGB(255,255,255));
	CBrush brushBlue(RGB(0,0,255));
	CMemoryListUnit* pTemp=memorylist_head;

	while(pTemp!=NULL)
	{
		if(pTemp->State==CMemoryListUnit::Free)
		{
			dc.SelectObject(&brushWhite);
			dc.Rectangle(pTemp->rect);

			//显示文字
			//CFont font1;
			CString stringSize;
			stringSize.Format(L"%dK",pTemp->Size);
			dc.SetTextColor(RGB(192,192,192));
			dc.DrawText(stringSize,&(pTemp->rect),DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}
		else
		{
			dc.SelectObject(&brushBlue);
			dc.Rectangle(pTemp->rect);
			//显示作业号
			CString stringID;
			stringID.Format(L"#%d",pTemp->pToJob->m_ID);
			dc.SetTextColor(RGB(255,0,0));
			dc.DrawText(stringID,&(pTemp->rect),DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		}
		pTemp=pTemp->Next;
	}
}

// 内存中增加一个作业
bool COS2Dlg::AddJob(void)
{
	return false;
}

void COS2Dlg::OnEnChangeEditSize()
{
}

void COS2Dlg::OnEnChangeEditId()
{
}


void COS2Dlg::OnDestroy()
{
	MyClose();
	CDialog::OnDestroy();
}

// 我的关闭函数，用于delete掉new出来的对象
void COS2Dlg::MyClose(void)
{
	CMemoryListUnit* pTemp=memorylist_head;	
	while(memorylist_head!=NULL)
	{
		pTemp=memorylist_head;
		memorylist_head=memorylist_head->Next;
		delete pTemp->pToJob;
		delete pTemp;
	}
}

// 将CString转为float
float COS2Dlg::CStringToFloat(CString cstr)
{
	//step1,从CString转到wchar_t
	wchar_t* pwchar=cstr.GetBuffer(cstr.GetLength());
	cstr.ReleaseBuffer();
	//::OutputDebugStringW(pwchar);

	//step2,从wchar_t到char
	int i=0;
	char pCh[128];
	for(;*(pwchar+i)!='\0';i++)
		*(pCh+i)=(char)*(pwchar+i);//强制类型转换，从wchar_t到char
	int length=i;
	*(pCh+length)='\0';

	//step3,从char到string
	std::stringstream stream(pCh);   
	//step4，从string到float
	float   a;
	stream>>a;
	stream.clear();
	OutputDebugStringA(pCh);
	return a;
}


// 首次适应算法
bool COS2Dlg::FirstFitAlgorithm(int iSize)
{
	CMemoryListUnit* pTemp=memorylist_head;
	//首先定位空闲内存
	while(pTemp!=NULL)
	{

		if(pTemp->State==CMemoryListUnit::Free)
		{
			if((pTemp->Size)>=iSize)
				break;
		}
		pTemp=pTemp->Next;
	}
	//从空闲内存块中划出一部分给Job
	return SplitMemoryListUnit(pTemp,iSize);
}

bool COS2Dlg::BestFitAlgorithm(int iSize)
{
	CMemoryListUnit* pTemp=memorylist_head;
	//首先定位最小适应的空闲内存
	int min=memory_capacity+1;//记录最小适应的值
	CMemoryListUnit* pToRecord=NULL;//记录最小最小适应的空闲内存单元的指针
	while(pTemp!=NULL)
	{
		if(pTemp->State==CMemoryListUnit::Free && (pTemp->Size)>=iSize)
		{
			if((pTemp->Size)<min)
			{
				pToRecord=pTemp;
				min=pTemp->Size;
			}
		}
		pTemp=pTemp->Next;
	}
	//从空闲内存块中划出一部分给Job
	return SplitMemoryListUnit(pToRecord,iSize);
}

// 释放内存块
bool COS2Dlg::FreeMemory(int iJobID)
{
	CMemoryListUnit* pTemp=memorylist_head;
	CMemoryListUnit* pPrevious=pTemp;
	while(pTemp!=NULL)
	{
		if(pTemp->pToJob!=NULL)
		{
			if(pTemp->pToJob->m_ID==iJobID)//释放
			{
				//先释放
				pTemp->State=CMemoryListUnit::Free;
				delete pTemp->pToJob;
				pTemp->pToJob=NULL;
				if(pTemp!=pPrevious&&pPrevious->State==CMemoryListUnit::Free)//和前面的一个节点合并
				{
					pPrevious->Size=pPrevious->Size+pTemp->Size;
					pPrevious->ResetRect();
					pPrevious->Next=pTemp->Next;
					delete pTemp;
					pTemp=pPrevious;
				}
				if(pTemp->Next!=NULL)//和后面的一个节点合并
				{
					if(pTemp->Next->State==CMemoryListUnit::Free)
					{
						pTemp->Size=pTemp->Size+pTemp->Next->Size;
						pTemp->ResetRect();
						CMemoryListUnit* pToDelete=pTemp->Next;
						pTemp->Next=pToDelete->Next;
						delete pToDelete;
					}
				}
				return true;
			}
		}
		pPrevious=pTemp;
		pTemp=pTemp->Next;
	}
	return false;
}

// 从空闲内存块中划出一部分给Job
bool COS2Dlg::SplitMemoryListUnit(CMemoryListUnit* pTemp,int iSize)
{
	if(pTemp!=NULL)
	{
		if(pTemp->Size==iSize)
		{
			pTemp->State=CMemoryListUnit::Occupied;
			CJob* pJob=new CJob(ID_to_increase);
			ID_to_increase+=1;
			pTemp->pToJob=pJob;
			return true;
		}
		else
		{
			CMemoryListUnit* pTempNew=new CMemoryListUnit(pTemp->Size-iSize,iSize+pTemp->BeginAddress);
			pTempNew->Next=pTemp->Next;
			pTemp->State=CMemoryListUnit::Occupied;
			pTemp->Size=iSize;
			pTemp->ResetRect();
			pTemp->Next=pTempNew;
			CJob* pJob=new CJob(ID_to_increase);
			ID_to_increase+=1;
			pTemp->pToJob=pJob;
			return true;
		}
	}
	else
		return false;
}

// //封装的申请函数，可供BUTTONApply和自动演示调用
void COS2Dlg::MyApply(float fSize)
{
	//检查合理的输入
	if((fSize-(int)fSize)!=0 || fSize<=0)
	{
		MessageBox(L"请输入一个正整数");
		GetDlgItem(IDC_EDIT_Size)->SetFocus();
		size_to_apply=L"";
		UpdateData(false);
		return;
	}
	if(algorithm_state==FirstFit)
	{
		if(FirstFitAlgorithm((int)fSize)==false)
		{
			MessageBox(L"内存空间不足。请重新输入作业大小或者释放一个作业。");
			GetDlgItem(IDC_EDIT_Size)->SetFocus();
			size_to_apply=L"";
			UpdateData(false);
		}
		else
		{
			CListBox *pCtrl = (CListBox *)GetDlgItem( IDC_LIST1 ) ; 
			//添加 
			CString JobStrInfo;
			JobStrInfo.Format(L"作业#%d 被创建\n    所占内存大小：%d",ID_to_increase,(int)fSize);
			pCtrl->AddString(JobStrInfo);
			pCtrl->SetCurSel(pCtrl->GetCount()-1);

			InvalidateRect(&rectToDraw,true);
		}
	}
	else
	{
		if(BestFitAlgorithm((int)fSize)==false)
		{
			MessageBox(L"内存空间不足。请重新输入作业大小或者释放一个作业。");
			GetDlgItem(IDC_EDIT_Size)->SetFocus();
			size_to_apply=L"";
			UpdateData(false);
		}
		else
		{
			CListBox *pCtrl = (CListBox *)GetDlgItem( IDC_LIST1 ) ; 
			//向ListBox中添加
			CString JobStrInfo;
			JobStrInfo.Format(L"作业#%d 被创建\n    所占内存大小：%d",ID_to_increase,(int)fSize);
			pCtrl->AddString(JobStrInfo);
			pCtrl->SetCurSel(pCtrl->GetCount()-1);
			InvalidateRect(&rectToDraw,true);
		}
	}
}

// //封装的Free函数，用于让ButtonFree和自动演示的调用
void COS2Dlg::MyFree(float fID)
{
	//检查合理的输入
	if((fID-(int)fID)!=0 || fID<=0)
	{
		MessageBox(L"请输入一个正整数");
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
		memory_to_free=L"";
		UpdateData(false);
		return;
	}

	if(FreeMemory((int)fID)==false)
	{
		MessageBox(L"当前内存中没有该作业号");
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
		memory_to_free=L"";
		UpdateData(false);
	}
	else
	{
		CListBox *pCtrl = (CListBox *)GetDlgItem( IDC_LIST1 ) ; 
		//添加 
		CString JobStrInfo;
		JobStrInfo.Format(L"作业#%d 被释放",(int)fID);
		pCtrl->AddString(JobStrInfo);
		pCtrl->SetCurSel(pCtrl->GetCount()-1);
		InvalidateRect(&rectToDraw,true);
	}
}

void COS2Dlg::OnBnClickedButtonClear()
{
	MyClose();
	MyInit(false);//并非第一次使用MyInit函数
	CListBox* pBox=(CListBox *)GetDlgItem( IDC_LIST1 ); 
	pBox->ResetContent();
	pBox->AddString(L"内存被清空");
	pBox->SetCurSel(pBox->GetCount()-1);
	size_to_apply=L"";
	memory_to_free=L"";
	UpdateData(false);
	
	InvalidateRect(&rectToDraw,true);
	// TODO: Add your control notification handler code here
}

void COS2Dlg::OnTimer(UINT_PTR nIDEvent)//自动演示
{
	// TODO: Add your message handler code here and/or call default

	OperationState operation[]={Apply,Apply,Apply,Free,Apply,Free,Free,Apply,Apply,Apply,Free};//一共11项操作
	int           apply_size[]={130,  60,   100,  -1,  200,  -1  ,-1,  140,  60,  50,   -1};//-1表示没有该项操作
	int              free_id[]={ -1,  -1,   -1,   2,   -1,   3,   1,   -1,   -1,   -1,   6 };//-1表示无该项操作
	if(m_timer<(sizeof(operation)/sizeof(OperationState)))
	{
		if(operation[m_timer]==Apply)
		{
			MyApply((float)apply_size[m_timer]);
		}
		else
			MyFree((float)free_id[m_timer]);
		m_timer++;//时钟
	}
	else
	{
		KillTimer(1);
		m_timer=0;
		GetDlgItem(IDC_BUTTON_Auto)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_Over)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_Apply)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_Free)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_Clear)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ChangAlgorithm)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_Size)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_ID)->EnableWindow(TRUE);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void COS2Dlg::OnBnClickedButtonPause()
{
	//暂停
	GetDlgItem(IDC_BUTTON_Auto)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(FALSE);
	KillTimer(1);
	// TODO: Add your control notification handler code here
}

void COS2Dlg::OnBnClickedButtonOver()
{
	MyClose();
	MyInit(false);//并非第一次使用MyInit函数
	CListBox* pBox=(CListBox *)GetDlgItem( IDC_LIST1 ); 
	pBox->ResetContent();
	pBox->AddString(L"自动演示被中止，内存清空");
	pBox->SetCurSel(pBox->GetCount()-1);
	size_to_apply=L"";
	memory_to_free=L"";
	UpdateData(false);

	InvalidateRect(&rectToDraw,true);

	KillTimer(1);
	m_timer=0;
	GetDlgItem(IDC_BUTTON_Auto)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Over)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_Apply)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Free)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Clear)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ChangAlgorithm)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_Size)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_ID)->EnableWindow(TRUE);
}
