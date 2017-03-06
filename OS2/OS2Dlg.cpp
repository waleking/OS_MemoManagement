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
	//�л��㷨
	if (algorithm_state==FirstFit)
	{
		//GetDlgItem(IDC_STATIC_Algorithm)->DrawCaption()
		cstr_algorithm=L"��ǰʹ�������Ӧ�㷨";
		UpdateData(FALSE);
		algorithm_state=BestFit;
	}
	else
	{
		cstr_algorithm=L"��ǰʹ���״���Ӧ�㷨";
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

void COS2Dlg::MyInit(bool init)//�ҵĳ�ʼ������
{
	if(init==true)//��һ��ʹ�øú���
	{
		cstr_algorithm=L"��ǰʹ���״���Ӧ�㷨";
		UpdateData(false);
		algorithm_state=FirstFit;//Ĭ�ϳ�ʼ�㷨Ϊ�״���Ӧ
	}
	ID_to_increase=0;
	memorylist_head=new CMemoryListUnit;
	rectToDraw=memorylist_head->rect;
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Over)->EnableWindow(FALSE);
}

 //���Լ��Ļ�ͼ����
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

			//��ʾ����
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
			//��ʾ��ҵ��
			CString stringID;
			stringID.Format(L"#%d",pTemp->pToJob->m_ID);
			dc.SetTextColor(RGB(255,0,0));
			dc.DrawText(stringID,&(pTemp->rect),DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		}
		pTemp=pTemp->Next;
	}
}

// �ڴ�������һ����ҵ
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

// �ҵĹرպ���������delete��new�����Ķ���
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

// ��CStringתΪfloat
float COS2Dlg::CStringToFloat(CString cstr)
{
	//step1,��CStringת��wchar_t
	wchar_t* pwchar=cstr.GetBuffer(cstr.GetLength());
	cstr.ReleaseBuffer();
	//::OutputDebugStringW(pwchar);

	//step2,��wchar_t��char
	int i=0;
	char pCh[128];
	for(;*(pwchar+i)!='\0';i++)
		*(pCh+i)=(char)*(pwchar+i);//ǿ������ת������wchar_t��char
	int length=i;
	*(pCh+length)='\0';

	//step3,��char��string
	std::stringstream stream(pCh);   
	//step4����string��float
	float   a;
	stream>>a;
	stream.clear();
	OutputDebugStringA(pCh);
	return a;
}


// �״���Ӧ�㷨
bool COS2Dlg::FirstFitAlgorithm(int iSize)
{
	CMemoryListUnit* pTemp=memorylist_head;
	//���ȶ�λ�����ڴ�
	while(pTemp!=NULL)
	{

		if(pTemp->State==CMemoryListUnit::Free)
		{
			if((pTemp->Size)>=iSize)
				break;
		}
		pTemp=pTemp->Next;
	}
	//�ӿ����ڴ���л���һ���ָ�Job
	return SplitMemoryListUnit(pTemp,iSize);
}

bool COS2Dlg::BestFitAlgorithm(int iSize)
{
	CMemoryListUnit* pTemp=memorylist_head;
	//���ȶ�λ��С��Ӧ�Ŀ����ڴ�
	int min=memory_capacity+1;//��¼��С��Ӧ��ֵ
	CMemoryListUnit* pToRecord=NULL;//��¼��С��С��Ӧ�Ŀ����ڴ浥Ԫ��ָ��
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
	//�ӿ����ڴ���л���һ���ָ�Job
	return SplitMemoryListUnit(pToRecord,iSize);
}

// �ͷ��ڴ��
bool COS2Dlg::FreeMemory(int iJobID)
{
	CMemoryListUnit* pTemp=memorylist_head;
	CMemoryListUnit* pPrevious=pTemp;
	while(pTemp!=NULL)
	{
		if(pTemp->pToJob!=NULL)
		{
			if(pTemp->pToJob->m_ID==iJobID)//�ͷ�
			{
				//���ͷ�
				pTemp->State=CMemoryListUnit::Free;
				delete pTemp->pToJob;
				pTemp->pToJob=NULL;
				if(pTemp!=pPrevious&&pPrevious->State==CMemoryListUnit::Free)//��ǰ���һ���ڵ�ϲ�
				{
					pPrevious->Size=pPrevious->Size+pTemp->Size;
					pPrevious->ResetRect();
					pPrevious->Next=pTemp->Next;
					delete pTemp;
					pTemp=pPrevious;
				}
				if(pTemp->Next!=NULL)//�ͺ����һ���ڵ�ϲ�
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

// �ӿ����ڴ���л���һ���ָ�Job
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

// //��װ�����뺯�����ɹ�BUTTONApply���Զ���ʾ����
void COS2Dlg::MyApply(float fSize)
{
	//�����������
	if((fSize-(int)fSize)!=0 || fSize<=0)
	{
		MessageBox(L"������һ��������");
		GetDlgItem(IDC_EDIT_Size)->SetFocus();
		size_to_apply=L"";
		UpdateData(false);
		return;
	}
	if(algorithm_state==FirstFit)
	{
		if(FirstFitAlgorithm((int)fSize)==false)
		{
			MessageBox(L"�ڴ�ռ䲻�㡣������������ҵ��С�����ͷ�һ����ҵ��");
			GetDlgItem(IDC_EDIT_Size)->SetFocus();
			size_to_apply=L"";
			UpdateData(false);
		}
		else
		{
			CListBox *pCtrl = (CListBox *)GetDlgItem( IDC_LIST1 ) ; 
			//��� 
			CString JobStrInfo;
			JobStrInfo.Format(L"��ҵ#%d ������\n    ��ռ�ڴ��С��%d",ID_to_increase,(int)fSize);
			pCtrl->AddString(JobStrInfo);
			pCtrl->SetCurSel(pCtrl->GetCount()-1);

			InvalidateRect(&rectToDraw,true);
		}
	}
	else
	{
		if(BestFitAlgorithm((int)fSize)==false)
		{
			MessageBox(L"�ڴ�ռ䲻�㡣������������ҵ��С�����ͷ�һ����ҵ��");
			GetDlgItem(IDC_EDIT_Size)->SetFocus();
			size_to_apply=L"";
			UpdateData(false);
		}
		else
		{
			CListBox *pCtrl = (CListBox *)GetDlgItem( IDC_LIST1 ) ; 
			//��ListBox�����
			CString JobStrInfo;
			JobStrInfo.Format(L"��ҵ#%d ������\n    ��ռ�ڴ��С��%d",ID_to_increase,(int)fSize);
			pCtrl->AddString(JobStrInfo);
			pCtrl->SetCurSel(pCtrl->GetCount()-1);
			InvalidateRect(&rectToDraw,true);
		}
	}
}

// //��װ��Free������������ButtonFree���Զ���ʾ�ĵ���
void COS2Dlg::MyFree(float fID)
{
	//�����������
	if((fID-(int)fID)!=0 || fID<=0)
	{
		MessageBox(L"������һ��������");
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
		memory_to_free=L"";
		UpdateData(false);
		return;
	}

	if(FreeMemory((int)fID)==false)
	{
		MessageBox(L"��ǰ�ڴ���û�и���ҵ��");
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
		memory_to_free=L"";
		UpdateData(false);
	}
	else
	{
		CListBox *pCtrl = (CListBox *)GetDlgItem( IDC_LIST1 ) ; 
		//��� 
		CString JobStrInfo;
		JobStrInfo.Format(L"��ҵ#%d ���ͷ�",(int)fID);
		pCtrl->AddString(JobStrInfo);
		pCtrl->SetCurSel(pCtrl->GetCount()-1);
		InvalidateRect(&rectToDraw,true);
	}
}

void COS2Dlg::OnBnClickedButtonClear()
{
	MyClose();
	MyInit(false);//���ǵ�һ��ʹ��MyInit����
	CListBox* pBox=(CListBox *)GetDlgItem( IDC_LIST1 ); 
	pBox->ResetContent();
	pBox->AddString(L"�ڴ汻���");
	pBox->SetCurSel(pBox->GetCount()-1);
	size_to_apply=L"";
	memory_to_free=L"";
	UpdateData(false);
	
	InvalidateRect(&rectToDraw,true);
	// TODO: Add your control notification handler code here
}

void COS2Dlg::OnTimer(UINT_PTR nIDEvent)//�Զ���ʾ
{
	// TODO: Add your message handler code here and/or call default

	OperationState operation[]={Apply,Apply,Apply,Free,Apply,Free,Free,Apply,Apply,Apply,Free};//һ��11�����
	int           apply_size[]={130,  60,   100,  -1,  200,  -1  ,-1,  140,  60,  50,   -1};//-1��ʾû�и������
	int              free_id[]={ -1,  -1,   -1,   2,   -1,   3,   1,   -1,   -1,   -1,   6 };//-1��ʾ�޸������
	if(m_timer<(sizeof(operation)/sizeof(OperationState)))
	{
		if(operation[m_timer]==Apply)
		{
			MyApply((float)apply_size[m_timer]);
		}
		else
			MyFree((float)free_id[m_timer]);
		m_timer++;//ʱ��
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
	//��ͣ
	GetDlgItem(IDC_BUTTON_Auto)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_Pause)->EnableWindow(FALSE);
	KillTimer(1);
	// TODO: Add your control notification handler code here
}

void COS2Dlg::OnBnClickedButtonOver()
{
	MyClose();
	MyInit(false);//���ǵ�һ��ʹ��MyInit����
	CListBox* pBox=(CListBox *)GetDlgItem( IDC_LIST1 ); 
	pBox->ResetContent();
	pBox->AddString(L"�Զ���ʾ����ֹ���ڴ����");
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
