<<<<<<< HEAD
// calculatorDlg.h : header file
//

#if !defined(AFX_CALCULATORDLG_H__808B247F_F942_4FE7_A1CF_FB7DD36B8745__INCLUDED_)
#define AFX_CALCULATORDLG_H__808B247F_F942_4FE7_A1CF_FB7DD36B8745__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

class CCalculatorDlg : public CDialog
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCalculatorDlg)
	enum { IDD = IDD_CALCULATOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalculatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEDIT();
	afx_msg void OnOUTPUT();
	afx_msg void OnCALCU();
	afx_msg void OnB1();
	afx_msg void OnB2();
	afx_msg void OnB3();
	afx_msg void OnB4();
	afx_msg void OnB5();
	afx_msg void OnB6();
	afx_msg void OnB7();
	afx_msg void OnB8();
	afx_msg void OnB9();
	afx_msg void OnB11();
	afx_msg void OnB10();
	afx_msg void OnB16();
	afx_msg void OnB12();
	afx_msg void OnB13();
	afx_msg void OnB14();
	afx_msg void OnB15();
	afx_msg void OnB17();
	afx_msg void OnB18();
	afx_msg void OnJINZHI1();
	afx_msg void OnJINZHI2();
	afx_msg void OnB19();
	afx_msg void OnB20();
	afx_msg void OnJINZHI3();
	afx_msg void OnB21();
	afx_msg void OnB22();
	afx_msg void OnB23();
	afx_msg void OnB24();
	afx_msg void OnB25();
	afx_msg void OnB26();
	afx_msg void OnB27();
	afx_msg void OnB28();
	afx_msg void OnB29();
	afx_msg void OnB30();
	afx_msg void OnB31();
	afx_msg void OnB32();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATORDLG_H__808B247F_F942_4FE7_A1CF_FB7DD36B8745__INCLUDED_)
=======
// calculatorDlg.h : header file
//

#if !defined(AFX_CALCULATORDLG_H__808B247F_F942_4FE7_A1CF_FB7DD36B8745__INCLUDED_)
#define AFX_CALCULATORDLG_H__808B247F_F942_4FE7_A1CF_FB7DD36B8745__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

class CCalculatorDlg : public CDialog
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCalculatorDlg)
	enum { IDD = IDD_CALCULATOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalculatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEDIT();
	afx_msg void OnOUTPUT();
	afx_msg void OnCALCU();
	afx_msg void OnB1();
	afx_msg void OnB2();
	afx_msg void OnB3();
	afx_msg void OnB4();
	afx_msg void OnB5();
	afx_msg void OnB6();
	afx_msg void OnB7();
	afx_msg void OnB8();
	afx_msg void OnB9();
	afx_msg void OnB11();
	afx_msg void OnB10();
	afx_msg void OnB16();
	afx_msg void OnB12();
	afx_msg void OnB13();
	afx_msg void OnB14();
	afx_msg void OnB15();
	afx_msg void OnB17();
	afx_msg void OnB18();
	afx_msg void OnJINZHI1();
	afx_msg void OnJINZHI2();
	afx_msg void OnB19();
	afx_msg void OnB20();
	afx_msg void OnJINZHI3();
	afx_msg void OnB21();
	afx_msg void OnB22();
	afx_msg void OnB23();
	afx_msg void OnB24();
	afx_msg void OnB25();
	afx_msg void OnB26();
	afx_msg void OnB27();
	afx_msg void OnB28();
	afx_msg void OnB29();
	afx_msg void OnB30();
	afx_msg void OnB31();
	afx_msg void OnB32();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATORDLG_H__808B247F_F942_4FE7_A1CF_FB7DD36B8745__INCLUDED_)
>>>>>>> c8e53e6cebb25bd81c804c3626305eefe06d7f69
