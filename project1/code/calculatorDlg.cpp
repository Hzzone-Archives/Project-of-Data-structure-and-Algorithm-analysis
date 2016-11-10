// calculatorDlg.cpp : implementation file
// author : Fangtao
// date : 2016/10/12
//*****************************************//

#include "stdafx.h"
#include "calculator.h"
#include "calculatorDlg.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

template <typename E> class Link{
	private:
	public  :
		E element;
		Link *next;
		Link(E ele, Link *nex)
		{
			element = ele;
			next = nex;
		}
};
template <typename E> class SList{
	private:
		Link<E> *top;
		int size;
	public:
		SList(){
			top = NULL;
			size = 0;
		}

		void clear(){
			while(top != NULL){
				Link<E>* temp = top;
				top = top-> next;
				delete temp;
			}
			size = 0;
		}

		void push(E it){
			top = new Link<E>(it,top);
			size++;
		}

		E pop(){
			if(top ==NULL){
				printf("Error! --- Is empty!");
				return 0;
			}
			Link<E>* temp;
			E it = top->element;
			temp = top->next;
			delete top;
			top = temp;
			size--;
			return it;
		}

		E topValue(){
			if(top ==NULL)
			{
				return 0;
			}
			return top->element;
		}

		int length(){
			return size;
		}
};
int type;
void display(char *str);
int factorial(int num);
int hexToDecimal(char *array);
int binaryToDecimal(char *array);
int priority(char op) ;
void pushNum(SList<char> *numS,SList<double> *num);
double calculate(char *out , int maxNum);
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalculatorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalculatorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	//{{AFX_MSG_MAP(CCalculatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(EDIT, OnChangeEDIT)
	ON_BN_CLICKED(OUTPUT, OnOUTPUT)
	ON_BN_CLICKED(CALCU, OnCALCU)
	ON_BN_CLICKED(B1, OnB1)
	ON_BN_CLICKED(B2, OnB2)
	ON_BN_CLICKED(B3, OnB3)
	ON_BN_CLICKED(B4, OnB4)
	ON_BN_CLICKED(B5, OnB5)
	ON_BN_CLICKED(B6, OnB6)
	ON_BN_CLICKED(B7, OnB7)
	ON_BN_CLICKED(B8, OnB8)
	ON_BN_CLICKED(B9, OnB9)
	ON_BN_CLICKED(B11, OnB11)
	ON_BN_CLICKED(B10, OnB10)
	ON_BN_CLICKED(B16, OnB16)
	ON_BN_CLICKED(B12, OnB12)
	ON_BN_CLICKED(B13, OnB13)
	ON_BN_CLICKED(B14, OnB14)
	ON_BN_CLICKED(B15, OnB15)
	ON_BN_CLICKED(B17, OnB17)
	ON_BN_CLICKED(B18, OnB18)
	ON_BN_CLICKED(JINZHI1, OnJINZHI1)
	ON_BN_CLICKED(JINZHI2, OnJINZHI2)
	ON_BN_CLICKED(B19, OnB19)
	ON_BN_CLICKED(B20, OnB20)
	ON_BN_CLICKED(JINZHI3, OnJINZHI3)
	ON_BN_CLICKED(B21, OnB21)
	ON_BN_CLICKED(B22, OnB22)
	ON_BN_CLICKED(B23, OnB23)
	ON_BN_CLICKED(B24, OnB24)
	ON_BN_CLICKED(B25, OnB25)
	ON_BN_CLICKED(B26, OnB26)
	ON_BN_CLICKED(B27, OnB27)
	ON_BN_CLICKED(B28, OnB28)
	ON_BN_CLICKED(B29, OnB29)
	ON_BN_CLICKED(B30, OnB30)
	ON_BN_CLICKED(B31, OnB31)
	ON_BN_CLICKED(B32, OnB32)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
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
	type = 1;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalculatorDlg::OnChangeEDIT() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CCalculatorDlg::OnOUTPUT() 
{
	// TODO: Add your control notification handler code here
	
}

void CCalculatorDlg::OnCALCU() 
{
	//获得用户输入
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);

	//中缀表达式转后缀表达式
	int maxNum;
	char *array = new char[100];
	array = (char *) str.GetBuffer(0);
	char out[100];
	SList<char> temp;
	int i = 0;
	int j = 0;
	while(array[i] != '\0'){
		if((array[i] >= '0' &&array[i] <= '9')||array[i] == '.' ||array[i] == '^'||(array[i] >='a'&&array[i] <='z'||array[i] == '!')){
			out[j] = array[i];
			j++;
		}
		else if(array[i] == '('){
			out[j++] = '(';
			temp.push(array[i]);
		}
		else if(array[i] == ')'){
			//优先输出结果
			while(temp.topValue() != '(')
			{
				out[j++] = temp.pop();
			}
			temp.pop();
		}
		else if(array[i] == '+'||array[i] == '-'||array[i] == '*'||array[i] == '/'||array[i] == '%')
		{
			out[j++] = ' ';
			//按操作符优先级入栈
			while(priority(array[i]) <= priority(temp.topValue()) )
			{
				out[j++] = temp.pop();
			}
			temp.push(array[i]);
		}
		i++;
	}
	//将剩余操作数入栈
	while(temp.length() != 0)
	{
		out[j++] = temp.pop();
	}

	//输出界面后缀表达式
	char *express = new char[j+1];
	for(int t = 0;t < j;t++)
	{
		express[t] = out[t];
		if(out[t] == '(')
		{
			express[t] = ' ';
		}
	}
	express[j] = '\0';

	//十进制后缀表达式求值
	maxNum = j;
	char *buf = new char[50];
	if(type == 1)
	{
		sprintf(buf, "%.3lf\n", calculate(out,maxNum));
		GetDlgItem(OUTPUT)->SetWindowText(buf);
	}
	//二进制后缀表达式求值
	if(type == 2)
	{
		itoa(calculate(out,maxNum), buf , 2);
		GetDlgItem(OUTPUT)->SetWindowText(buf);
	}
	//十六进制表达式求值
	if(type == 3)
	{
		itoa(calculate(out,maxNum), buf , 16);
		GetDlgItem(OUTPUT)->SetWindowText(buf);
	}
	GetDlgItem(expression)->SetWindowText(express);
}

//根据后缀表达式求值，返回求值结果
double calculate(char *out, int maxNum){

	double temp;
	int j =0 ;
	SList<char> numS;
	SList<double> num;
	double x1,x2;
	for(j = 0;j < maxNum;j++)
	{
		//操作数内容直接进栈
		if(out[j] >= '0' && out[j] <='9' || out[j] == '.' ||out[j] =='^'||(out[j] >='a'&&out[j] <='z')||out[j] =='!')
		{
			/*if(num.length() >=2){
				temp = num.pop();
				while(num.length() != 0)
				{
					temp = temp + num.pop();
				}
				num.push(temp);
			}*/
			numS.push(out[j]);
		}
		if(out[j] == '(')
		{
			num.push(999999);
		}
		//空格分开操作数
		if(out[j] == ' ')
		{
			pushNum(&numS,&num);
		}
		if (out[j] == '+')  
        {  
			pushNum(&numS,&num);
			
            x2 = num.pop();  
            x1 = num.pop();  
			if(x1 == 999999){
				x1 = num.pop();
			}
            num.push(x1+x2);   
        }  
		if (out[j] =='-')  
        {  
			pushNum(&numS,&num);
			
            x2 = num.pop();  
            x1 = num.pop();  
            
			if(x1 == 999999)
			{
				num.push((-1)*x2);
			}
			if(x1 != 999999)
			{
				num.push(x1 - x2);
			}
        } 
		if (out[j] =='*')  
        {  
			/*if(num.length() >=2){
				temp = num.pop();
				while(num.length() != 1)
				{
					temp = temp + num.pop();
				}
				num.push(temp);
			}*/
			
			pushNum(&numS,&num);
			
            x2 = num.pop();  
            x1 = num.pop();  
			if(x1 == 999999){
				x1 = num.pop();
			}
            num.push(x1*x2);   
        } 
		if (out[j] =='/')  
        {  
			/*if(num.length() >=2){
				temp = num.pop();
				while(num.length() != 1)
				{
					temp = temp + num.pop();
				}
				num.push(temp);
			}*/
			pushNum(&numS,&num);
            x2 = num.pop();  
            x1 = num.pop(); 
			if(x1 == 999999){
				x1 = num.pop();
			}
            num.push(x1/x2);   
        } 
		//执行求余操作
		if (out[j] =='%')  
        {  
			pushNum(&numS,&num);
            x2 = num.pop();  
            x1 = num.pop(); 
			if(x1 == 999999)
				x1 = num.pop();{
			}
            num.push((int)x1%(int)x2);   
        } 
	}

	if(numS.length() != 0)
	{
		pushNum(&numS,&num);
	}
	/*temp = num.pop();
	while(num.length() != 0)
	{
		temp = temp + num.pop();
	}
	num.push(temp);*/

	return num.pop();
}

//定义并返回操作数优先级
int priority(char op)  
{  
    switch(op)  
    {  
    case '(':  
        return 0;  
    case '+':  
    case '-':  
        return 1;  
    case '*':  
    case '/':  
	case '%':
        return 2;  
    default :  
        return -1;  
    }  
}  

//将压入栈numS中的字符转换为操作数压入栈num中
void pushNum(SList<char> *numS,SList<double> *num)
{
	int k = 0;
	double tempnum = 0;
	double downnum = 0;
	bool isMul = false;
	bool isFactorial = false;
	bool isSin = false;
	bool isCos = false;
	bool isTan = false;
	bool isLn = false;
	bool isLog = false;
	while((*numS).length() != 0)
	{
		if((*numS).topValue() == '.')
		{
			tempnum = tempnum / pow(10,k);		//遇到小数点则将原数除以位数
			k = 0;
			(*numS).pop();
		}
		else if((*numS).topValue() == '^'){		//指数
			downnum = tempnum;					
			tempnum = 0;
			k = 0;
			(*numS).pop();
			isMul = true;
		}
		else if((*numS).topValue() == '!'){		//阶乘
			isFactorial = true;
			(*numS).pop();
		}
		else if((*numS).topValue() == 'n'){		
			(*numS).pop();
			if((*numS).topValue() == 'i')
			{
				(*numS).pop();
				if((*numS).topValue() == 's'){		//判断是否为求sin
					(*numS).pop();
					isSin = true;
				}
			}
			else if((*numS).topValue() == 'a')
			{
				(*numS).pop();
				if((*numS).topValue() == 't'){		//判断是否为求tan
					(*numS).pop();
					isTan = true;
				}
			}
			else if((*numS).topValue() == 'l'){		//判断是否为求ln
					(*numS).pop();
					isLn = true;
			}
		}
		else if((*numS).topValue() == 's'){
			(*numS).pop();
			if((*numS).topValue() == 'o')
			{
				(*numS).pop();
				if((*numS).topValue() == 'c'){		//判断是否为求cos
					(*numS).pop();
					isCos = true;
				}
			}
		}
		else if((*numS).topValue() == 'g'){
			(*numS).pop();
				if((*numS).topValue() == 'l'){		//判断是否为求lg
					(*numS).pop();
					isLog = true;
				}
		}
		else{										//根据不同进制计算
			if(type == 1){
				tempnum += ((*numS).pop() - '0') * pow(10,k);
				k++;
			}
			else if(type == 2)
			{
				tempnum += ((*numS).pop() - '0') * pow(2,k);
				k++;
			}
			else if(type == 3)
			{
				if((*numS).topValue() >='0' && (*numS).topValue() <='9'){
				tempnum += ((*numS).pop() - '0') * pow(16,k);
				}
				else
				{
					tempnum += ((*numS).pop() - 'a' + 10) * pow(16,k);
				}
				k++;
			}
		}
	}
	//计算指数
	if(isMul)		
	{
		tempnum = pow(tempnum,downnum);
	}
	//计算阶乘
	if(isFactorial)
	{
	tempnum = factorial(tempnum);
	}
	//三角函数
	if(isSin){
		tempnum = sin(tempnum);
	}
	if(isTan)
	{
		tempnum = tan(tempnum);
	}
	if(isCos){
		tempnum = cos(tempnum);
	}
	if(isLn){
		tempnum = log(tempnum);
	}
	if(isLog){
		tempnum = log10(tempnum);
	}
	//结果入栈
	if(tempnum != 0){
		(*num).push(tempnum);
	}
}

//按钮单级响应事件
void CCalculatorDlg::OnB1() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "1";
	GetDlgItem(EDIT)->SetWindowText(str);
}

void CCalculatorDlg::OnB2() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "2";
	GetDlgItem(EDIT)->SetWindowText(str);
	
}

void CCalculatorDlg::OnB3() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "3";
	GetDlgItem(EDIT)->SetWindowText(str);	
}

void CCalculatorDlg::OnB4() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "4";
	GetDlgItem(EDIT)->SetWindowText(str);	
}

void CCalculatorDlg::OnB5() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "5";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB6() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "6";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB7() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "7";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB8() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "8";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB9() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "9";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB11() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += ".";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB10() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "0";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB16() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str = "";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB12() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "+";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB13() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "-";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB14() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "*";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB15() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "/";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB17() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "(";
	GetDlgItem(EDIT)->SetWindowText(str);	
	
}

void CCalculatorDlg::OnB19() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "^";
	GetDlgItem(EDIT)->SetWindowText(str);	
}

void CCalculatorDlg::OnB20() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "%";
	GetDlgItem(EDIT)->SetWindowText(str);	
	
}
void CCalculatorDlg::OnB18() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += ")";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB21() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "a";
	GetDlgItem(EDIT)->SetWindowText(str);	
}

void CCalculatorDlg::OnB22() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "b";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB23() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "c";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB24() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "d";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB25() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "e";
	GetDlgItem(EDIT)->SetWindowText(str);		
}

void CCalculatorDlg::OnB26() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "f";
	GetDlgItem(EDIT)->SetWindowText(str);		
}


//进制转化单选框响应事件
//转二进制
void CCalculatorDlg::OnJINZHI1() 
{
	CString space = "";
	GetDlgItem(EDIT)->SetWindowText(space);
	
	CString str;
	GetDlgItem(OUTPUT)->GetWindowText(str);
	GetDlgItem(B2)->EnableWindow(FALSE);
	GetDlgItem(B3)->EnableWindow(FALSE);
	GetDlgItem(B4)->EnableWindow(FALSE);
	GetDlgItem(B5)->EnableWindow(FALSE);
	GetDlgItem(B6)->EnableWindow(FALSE);
	GetDlgItem(B7)->EnableWindow(FALSE);
	GetDlgItem(B8)->EnableWindow(FALSE);
	GetDlgItem(B9)->EnableWindow(FALSE);
	GetDlgItem(B11)->EnableWindow(FALSE);
	//处理十进制
	if(type == 1)
	{
		int i = _ttoi(str);
		char out[100] = {0};
		itoa(i, out,2);

		GetDlgItem(OUTPUT)->SetWindowText(out);
	}

	//处理十六进制
	if(type == 3)
	{
		char out[100];
		char *array = new char[100];
		array = (char *) str.GetBuffer(0);

		int tempnum = hexToDecimal(array);

		itoa(tempnum,out,2);
		GetDlgItem(OUTPUT)->SetWindowText(out);

	}
	type = 2;
}
//转十进制
void CCalculatorDlg::OnJINZHI2() 
{
	CString space = "";
	GetDlgItem(EDIT)->SetWindowText(space);

	CString str;
	GetDlgItem(OUTPUT)->GetWindowText(str);
	//处理二进制
	if(type == 2)
	{
		GetDlgItem(B2)->EnableWindow(TRUE);
		GetDlgItem(B3)->EnableWindow(TRUE);
		GetDlgItem(B4)->EnableWindow(TRUE);
		GetDlgItem(B5)->EnableWindow(TRUE);
		GetDlgItem(B6)->EnableWindow(TRUE);
		GetDlgItem(B7)->EnableWindow(TRUE);
		GetDlgItem(B8)->EnableWindow(TRUE);
		GetDlgItem(B9)->EnableWindow(TRUE);
		GetDlgItem(B11)->EnableWindow(TRUE);
		
		char out[100];
		char *array = new char[100];
		array = (char *) str.GetBuffer(0);

		int tempnum = binaryToDecimal(array);

		itoa(tempnum,out,10);
		GetDlgItem(OUTPUT)->SetWindowText(out);	
	}
	//处理十六进制
	if(type == 3)
	{
		char out[100];
		char *array = new char[100];
		array = (char *) str.GetBuffer(0);

		int tempnum = hexToDecimal(array);

		itoa(tempnum,out,10);
		GetDlgItem(OUTPUT)->SetWindowText(out);	

	}
	type = 1;
}
//二进制转十进制
int binaryToDecimal(char *array){
		SList<char> stack;
		int i = 0;
		while(array[i] != '\0'){
			stack.push(array[i]);
			i++;
		}
		int k = 0;
		int tempnum = 0;
		while(stack.length() != 0)
		{
			tempnum += (stack.pop() - '0') * pow(2,k);
			k++;	
		}
		return tempnum;
}
//16进制转十进制
int hexToDecimal(char *array)
{
	SList<char> stack;
	int i = 0;
	while(array[i] != '\0'){
		stack.push(array[i]);
		i++;
	}
	int k = 0;
	int tempnum = 0;
	while(stack.length() != 0)
	{
		if(stack.topValue() >='0' && stack.topValue() <='9'){
		tempnum += (stack.pop() - '0') * pow(16,k);
		}
		else{
			tempnum += (stack.pop() - 'a' + 10) * pow(16,k);
		}
		k++;	
	}
	return tempnum;
}
//16进制单选框
void CCalculatorDlg::OnJINZHI3() 
{
	CString space = "";
	GetDlgItem(EDIT)->SetWindowText(space);

	CString str;
	GetDlgItem(OUTPUT)->GetWindowText(str);
	//处理十进制
	if(type == 1)
	{
		int i = _ttoi(str);
		char out[100] = {0};
		itoa(i, out,16);
		
		GetDlgItem(OUTPUT)->SetWindowText(out);
	}

	//处理二进制
	if(type == 2)
	{
		char *array = new char[100];
		array = (char *) str.GetBuffer(0);
		int i ;
		i =	binaryToDecimal(array);
		char out[100] = {0};
		itoa(i, out,16);
		GetDlgItem(OUTPUT)->SetWindowText(out);
	}
	type = 3;
}
//阶乘计算
int factorial(int num){
	int i;
	int temp = 1;
	for(i = 1; i <= num;i++)
	{
		temp = temp * i;
	}
	return temp;
}

void CCalculatorDlg::OnB27() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "!";
	GetDlgItem(EDIT)->SetWindowText(str);
}

void CCalculatorDlg::OnB28() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "sin";
	GetDlgItem(EDIT)->SetWindowText(str);
}

void CCalculatorDlg::OnB29() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "cos";
	GetDlgItem(EDIT)->SetWindowText(str);	
}

void CCalculatorDlg::OnB30() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "tan";
	GetDlgItem(EDIT)->SetWindowText(str);	
}
void display(char *str){
	CString str2;
//	GetDlgItem(EDIT)->GetWindowText(str2);
	str2 += str;
//	GetDlgItem(EDIT)->SetWindowText(str2);
}

void CCalculatorDlg::OnB31() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "ln";
	GetDlgItem(EDIT)->SetWindowText(str);
}

void CCalculatorDlg::OnB32() 
{
	CString str;
	GetDlgItem(EDIT)->GetWindowText(str);
	str += "lg";
	GetDlgItem(EDIT)->SetWindowText(str);	
}
