#pragma once
#include "afxwin.h"
#include "resource.h"


class СLightingDialog : public CDialog
{
private:
	DECLARE_DYNAMIC(СLightingDialog)
	CButton RButton_Diff, // Диффузионная модель
		RButton_Mirr; // Зеркальная модель
	int lightMod;		  // Флаг модели освещения (0 — диффузионная; 1 — зеркальная)


public:
	enum { IDD = IDD_DIALOG3 };
	virtual void OnFinalRelease();

	СLightingDialog(CWnd* pParent = NULL); // Стандартный конструктор

	int GetRButtonStatus();
	void SetMod(int);

	void OnBnClickedOk();
	void OnBnClickedRadio1();
	void OnBnClickedRadio2();


protected:
	virtual void DoDataExchange(CDataExchange* pDX); // Поддержка DDX/DDV
	DECLARE_MESSAGE_MAP()
};