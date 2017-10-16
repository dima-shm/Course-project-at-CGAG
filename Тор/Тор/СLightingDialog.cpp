#include "СLightingDialog.h"
#include "afxdialogex.h"
#include "afxdisp.h"


IMPLEMENT_DYNAMIC(СLightingDialog, CDialog)
void СLightingDialog::OnFinalRelease()
{
	CDialog::OnFinalRelease();
}


СLightingDialog::СLightingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG3, pParent)
{
	EnableAutomation();
}
void СLightingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, RButton_Diff);
	DDX_Control(pDX, IDC_RADIO2, RButton_Mirr);
	DDX_Radio(pDX, IDC_RADIO1, lightMod); // помечает активный RadioButton
}


BEGIN_MESSAGE_MAP(СLightingDialog, CDialog)
	ON_BN_CLICKED(IDOK, &СLightingDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &СLightingDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &СLightingDialog::OnBnClickedRadio2)
END_MESSAGE_MAP()


// Обработчики сообщений СLightingDialog
void СLightingDialog::OnBnClickedOk()
{
	CDialog::OnOK();
}
void СLightingDialog::OnBnClickedRadio1()
{
	lightMod = 0;
}
void СLightingDialog::OnBnClickedRadio2()
{
	lightMod = 1;
}


int СLightingDialog::GetRButtonStatus()
// Возвращает значение 0, если выбрана диффузионная модель
// 1 — зеркальная модель
{
	return lightMod;
}
void СLightingDialog::SetMod(int mod)
// Устанавливает модель освещения —> помечает активный RadioButton
{
	lightMod = mod;
}