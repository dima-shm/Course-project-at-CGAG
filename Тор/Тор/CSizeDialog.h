#pragma once
#include "afxwin.h"
#include "resource.h"


class CSizeDialog : public CDialog
{
private:
	DECLARE_DYNAMIC(CSizeDialog)

	CEdit Edit_R, // Больший радиус
		  Edit_r; // Малый радиус
	int Radius,   // Больший радиус
		radius;   // Малый радиус


public:
	enum { IDD = IDD_DIALOG1 };
	virtual void OnFinalRelease();

	CSizeDialog(CWnd* pParent = NULL); // Стандартный конструктор

	int GetR();
	int Getr();

	void OnBnClickedOk();
	void OnEnChangeEdit1();
	void OnEnChangeEdit2();


protected:
	virtual void DoDataExchange(CDataExchange* pDX); // Поддержка DDX/DDV
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};