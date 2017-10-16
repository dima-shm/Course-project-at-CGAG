#pragma once
#include "afxwin.h"
#include "resource.h"


class �LightingDialog : public CDialog
{
private:
	DECLARE_DYNAMIC(�LightingDialog)
	CButton RButton_Diff, // ������������ ������
		RButton_Mirr; // ���������� ������
	int lightMod;		  // ���� ������ ��������� (0 � ������������; 1 � ����������)


public:
	enum { IDD = IDD_DIALOG3 };
	virtual void OnFinalRelease();

	�LightingDialog(CWnd* pParent = NULL); // ����������� �����������

	int GetRButtonStatus();
	void SetMod(int);

	void OnBnClickedOk();
	void OnBnClickedRadio1();
	void OnBnClickedRadio2();


protected:
	virtual void DoDataExchange(CDataExchange* pDX); // ��������� DDX/DDV
	DECLARE_MESSAGE_MAP()
};