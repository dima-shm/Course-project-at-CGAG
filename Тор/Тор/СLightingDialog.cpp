#include "�LightingDialog.h"
#include "afxdialogex.h"
#include "afxdisp.h"


IMPLEMENT_DYNAMIC(�LightingDialog, CDialog)
void �LightingDialog::OnFinalRelease()
{
	CDialog::OnFinalRelease();
}


�LightingDialog::�LightingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG3, pParent)
{
	EnableAutomation();
}
void �LightingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, RButton_Diff);
	DDX_Control(pDX, IDC_RADIO2, RButton_Mirr);
	DDX_Radio(pDX, IDC_RADIO1, lightMod); // �������� �������� RadioButton
}


BEGIN_MESSAGE_MAP(�LightingDialog, CDialog)
	ON_BN_CLICKED(IDOK, &�LightingDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &�LightingDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &�LightingDialog::OnBnClickedRadio2)
END_MESSAGE_MAP()


// ����������� ��������� �LightingDialog
void �LightingDialog::OnBnClickedOk()
{
	CDialog::OnOK();
}
void �LightingDialog::OnBnClickedRadio1()
{
	lightMod = 0;
}
void �LightingDialog::OnBnClickedRadio2()
{
	lightMod = 1;
}


int �LightingDialog::GetRButtonStatus()
// ���������� �������� 0, ���� ������� ������������ ������
// 1 � ���������� ������
{
	return lightMod;
}
void �LightingDialog::SetMod(int mod)
// ������������� ������ ��������� �> �������� �������� RadioButton
{
	lightMod = mod;
}