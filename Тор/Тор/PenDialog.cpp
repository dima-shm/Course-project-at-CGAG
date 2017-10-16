// PenDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "PenDialog.h"
#include "afxdialogex.h"


// диалоговое окно CPenDialog

IMPLEMENT_DYNAMIC(CPenDialog, CDialog)

CPenDialog::CPenDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CPenDialog::~CPenDialog()
{
}

void CPenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, R);
}


BEGIN_MESSAGE_MAP(CPenDialog, CDialog)
END_MESSAGE_MAP()


// обработчики сообщений CPenDialog
