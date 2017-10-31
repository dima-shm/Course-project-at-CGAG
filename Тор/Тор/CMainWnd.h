#pragma once
#include "resource.h"
#include "CMatrix.h"
#include "Lib.h"
#include "Toroid.h"
#include "CSizeDialog.h"
#include "�LightingDialog.h"


class CMainWnd : public CFrameWnd
{
private:
	CRect WinRect;  // ������� � ����
	CMatrix PView,  // ���������� ����� ����������
			PLight; // ���������� ��������� �����
	CMenu menu;		// ������ ���� �� ����� ��������
	Toroid* toroid; // ������ �������
	COLORREF color; // ���� �������
	int lightMod;   // ���� ��� ��������� ������ ��������� (0 � ������������; 1 � ����������)


public:
	CMainWnd::CMainWnd()
	{
		Create(NULL, L"���", WS_OVERLAPPEDWINDOW, CRect(10, 10, 600, 600), NULL, NULL);

		lightMod = 0;									// ��������� ������������ ������ ���������

		PView.RedimMatrix(3);
		PView(0) = 450; PView(1) = 0; PView(2) = 45;    // ��������� �������� ����� ����������

		PLight.RedimMatrix(3);
		PLight(0) = 450; PLight(1) = 90; PLight(2) = 45; // ��������� ��������� ��������� �����

		toroid = new Toroid();							 // ������������� ������� Toroid
		color = COLORREF(RGB(0, 0, 255));                // ��������� �����
	}

	void setColor();					  // ��������� ����� ������� ����� ������
	void setSize();						  // ��������� ������� ������� ����� ������
	void writeScreenshot();				  // �������� ����������� ���� � ����
	int ClientToBmp(HWND, RECT, LPCWSTR); // ������� ������ �����������
	void setLighting();					  // ��������� ������ ���������
	void Exit();						  // ����� �� ����������


protected:
	DECLARE_MESSAGE_MAP()
	int OnCreate(LPCREATESTRUCT);
	void OnSize(UINT nType, int cx, int cy);
	void OnKeyDown(UINT nChar, UINT nRepCount, UINT nFlags);
	void OnPaint();
};


BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_SET_COLOR, setColor)
	ON_COMMAND(ID_SET_SIZE, setSize)
	ON_COMMAND(ID_WRITE_SCREENSHOT, writeScreenshot)
	ON_COMMAND(ID_SET_LIGHTING, setLighting)
	ON_COMMAND(ID_EXIT, Exit)
END_MESSAGE_MAP()
int  CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	menu.LoadMenu(IDR_MENU1); // ��������� ���� �� ����� �������
	SetMenu(&menu);			  // ���������� ����
	return 0;
}
void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	WinRect.SetRect(0, 0, cx, cy);
}
void CMainWnd::OnKeyDown(UINT nChar, UINT nRepCount, UINT nFlags)
{
	// ����������� ��������� ����� ���������� ��� ������ �������
	if (nChar == 37)      // ������� �����
	{
		PView(1) += 10;
		if (PView(1) >= 360)
			PView(1) -= 360;
	}
	else if (nChar == 39) // ������� ������ 
	{
		PView(1) -= 10;
		if (PView(1) < 0)
			PView(1) += 360;
	}
	else if (nChar == 38) // ������� ����� 
	{
		PView(2) += 10;
		if (PView(2) >= 360)
			PView(2) -= 360;
	}
	else if (nChar == 40) // ������� ����
	{
		PView(2) -= 10;
		if (PView(2) < 0)
			PView(2) += 360;
	}
	// ����������� ��������� ��������� ����� ��� ������ ������ WASD
	else if (nChar == 65) // ������� A
	{
		PLight(1) -= 10;
		if (PLight(1) >= 360)
			PLight(1) -= 360;
	}
	else if (nChar == 68) // ������� D
	{
		PLight(1) += 10;
		if (PLight(1) < 0)
			PLight(1) += 360;
	}
	else if (nChar == 87) // ������� W
	{
		PLight(2) -= 10;
		if (PLight(2) < 0)
			PLight(2) += 360;
	}
	else if (nChar == 83) // ������� S
	{
		PLight(2) += 10;
		if (PLight(2) >= 360)
			PLight(2) -= 360;
	}
	Invalidate();
}
void CMainWnd::OnPaint()
{
	CPaintDC dc(this);
	toroid->Draw(dc, PView, PLight, WinRect, color, lightMod);
}


void CMainWnd::setColor()
{
	CColorDialog cColorDlg;
	if (cColorDlg.DoModal() == IDOK)
	{
		color = cColorDlg.GetColor();
		Invalidate();
	}
}
void CMainWnd::setSize()
{
	CSizeDialog cSizeDlg; // ������ ����������� ����
	if (cSizeDlg.DoModal() == IDOK)
	{
		int R = cSizeDlg.GetR(), r = cSizeDlg.Getr();
		delete toroid;
		toroid = new Toroid(R, r);
		Invalidate();
	}
}
void CMainWnd::writeScreenshot()
{
	if (ClientToBmp(m_hWnd, WinRect, L"������.bmp") == 0)
		MessageBox(L"���� ��������� ���� ��� ������� ������ � �������� ��� \"������.bmp\"");
	else
		MessageBox(L"�� ������� �������� �������� ����");
}
int CMainWnd::ClientToBmp(HWND hWnd, RECT rect, LPCWSTR Name)
{
	BITMAPFILEHEADER bmfHdr; // ���, ������ � ����� ����� � ������� DIB
	BITMAPINFOHEADER bi;
	int BitToPixel = 16;	 // ������������� �������� ������� 16 ���
	HDC hdc = ::GetDC(hWnd);
	HDC hdcMem = CreateCompatibleDC(hdc);

	HBITMAP BitMap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(hdcMem, BitMap);
	BitBlt(hdcMem, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdc, rect.left, rect.top, SRCCOPY);
	BitMap = (HBITMAP)SelectObject(hdcMem, OldBitmap);

	ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = rect.right - rect.left;
	bi.biHeight = rect.bottom - rect.top;
	bi.biPlanes = 1;
	bi.biBitCount = BitToPixel;
	bi.biSizeImage = (rect.right * BitToPixel + 31) / 32 * 4 * rect.bottom;
	DWORD dwWritten; // ���������� ���������� ������

					 // ��������� ����
	HANDLE fh = CreateFile((LPCWSTR)Name, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return 2;
	bmfHdr.bfType = ('M' << 8) | 'B'; // ��������� �������� ���������
	bmfHdr.bfSize = bi.biSizeImage + sizeof(bmfHdr) + bi.biSize; // ������ �����
	bmfHdr.bfReserved1 = bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = sizeof(bmfHdr) + bi.biSize; // �������� �� ������ ������

												   // ������ ��������� � ����										   
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(bmfHdr), &dwWritten, NULL);

	// ������ � ���� ������������ ���������
	WriteFile(fh, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);

	// �������� ����� � ������ ��� ����,����� ������� GetDIBits()���������
	// ���� ���� ����� � DIB-�������.
	char *lp = (char *)GlobalAlloc(GMEM_FIXED, bi.biSizeImage);

	// �� ����� BitMap ������ � ������� �� bi.biHeight ������� ����������
	// � ������ lp �� ������� bi ( ������������� ������)
	int err = GetDIBits(hdc, BitMap, 0, (UINT)rect.bottom, lp, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

	// ������ ����������� �� ����
	WriteFile(fh, lp, bi.biSizeImage, &dwWritten, NULL);

	// ������������ ������ � �������� �����
	GlobalFree(GlobalHandle(lp));
	CloseHandle(fh);
	::ReleaseDC(hWnd, hdc);
	DeleteDC(hdcMem);

	if (dwWritten == 0)
		return 2;

	return 0;
}
void CMainWnd::setLighting()
{
	�LightingDialog �LightingDlg;
	�LightingDlg.SetMod(lightMod);
	if (�LightingDlg.DoModal() == IDOK)
	{
		lightMod = �LightingDlg.GetRButtonStatus();
		Invalidate();
	}
}
void CMainWnd::Exit()
{
	DestroyWindow();
}