#include "CSizeDialog.h"
#include "afxdialogex.h"
#include "afxdisp.h"


IMPLEMENT_DYNAMIC(CSizeDialog, CDialog)
void CSizeDialog::OnFinalRelease()
{
	CDialog::OnFinalRelease();
}


CSizeDialog::CSizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{
	EnableAutomation();
}
void CSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Edit_R);
	DDX_Control(pDX, IDC_EDIT2, Edit_r);
}


BEGIN_MESSAGE_MAP(CSizeDialog, CDialog)
	ON_BN_CLICKED(IDOK,		&CSizeDialog::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CSizeDialog::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CSizeDialog::OnEnChangeEdit2)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSizeDialog, CDialog)
END_DISPATCH_MAP()

static const IID IID_CSizeDialog =
{ 0x140C0F47, 0x65E4, 0x4C40, {0x9F, 0x5E, 0x2B, 0x44, 0x45, 0x3B, 0x39, 0x70 }}; // {140C0F47-65E4-4C40-9F5E-2B44453B3970}
BEGIN_INTERFACE_MAP(CSizeDialog, CDialog)
	INTERFACE_PART(CSizeDialog, IID_CSizeDialog, Dispatch)
END_INTERFACE_MAP()


// Обработчики сообщений CSizeDialog
void CSizeDialog::OnBnClickedOk()
{
	CDialog::OnOK();
}
void CSizeDialog::OnEnChangeEdit1()
{
	CString str;
	Edit_R.GetWindowText(str);
	Radius = _wtoi(str.GetString());
}
void CSizeDialog::OnEnChangeEdit2()
{
	CString str;
	Edit_r.GetWindowText(str);
	radius = _wtoi(str.GetString());
}


int CSizeDialog::GetR() 
{
	return Radius;
}
int CSizeDialog::Getr() 
{
	return radius;
}