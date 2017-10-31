#pragma once
#include "resource.h"
#include "CMatrix.h"
#include "Lib.h"
#include "Toroid.h"
#include "CSizeDialog.h"
#include "СLightingDialog.h"


class CMainWnd : public CFrameWnd
{
private:
	CRect WinRect;  // Область в окне
	CMatrix PView,  // Координаты точки наблюдения
			PLight; // Координаты источника света
	CMenu menu;		// Объект меню из файла ресурсов
	Toroid* toroid; // Объект тороида
	COLORREF color; // Цвет тороида
	int lightMod;   // Флаг для установки модели освещения (0 — диффузионная; 1 — зеркальная)


public:
	CMainWnd::CMainWnd()
	{
		Create(NULL, L"Тор", WS_OVERLAPPEDWINDOW, CRect(10, 10, 600, 600), NULL, NULL);

		lightMod = 0;									// Установка диффузионной модели освещения

		PView.RedimMatrix(3);
		PView(0) = 450; PView(1) = 0; PView(2) = 45;    // Установка коодинат точки наблюдения

		PLight.RedimMatrix(3);
		PLight(0) = 450; PLight(1) = 90; PLight(2) = 45; // Установка координат источника света

		toroid = new Toroid();							 // Инициализация объекта Toroid
		color = COLORREF(RGB(0, 0, 255));                // Установка цвета
	}

	void setColor();					  // Установка цвета тороида через диалог
	void setSize();						  // Установка размера тороида через диалог
	void writeScreenshot();				  // Записать изображение окна в файл
	int ClientToBmp(HWND, RECT, LPCWSTR); // Функция записи изображения
	void setLighting();					  // Установка модели освещения
	void Exit();						  // Выйти из приложения


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
	menu.LoadMenu(IDR_MENU1); // Загрузить меню из файла ресурса
	SetMenu(&menu);			  // Установить меню
	return 0;
}
void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	WinRect.SetRect(0, 0, cx, cy);
}
void CMainWnd::OnKeyDown(UINT nChar, UINT nRepCount, UINT nFlags)
{
	// Перемещение координат точки наблюдения при помощи стрелок
	if (nChar == 37)      // Клавиша влево
	{
		PView(1) += 10;
		if (PView(1) >= 360)
			PView(1) -= 360;
	}
	else if (nChar == 39) // Клавиша вправо 
	{
		PView(1) -= 10;
		if (PView(1) < 0)
			PView(1) += 360;
	}
	else if (nChar == 38) // Клавиша вверх 
	{
		PView(2) += 10;
		if (PView(2) >= 360)
			PView(2) -= 360;
	}
	else if (nChar == 40) // Клавиша вниз
	{
		PView(2) -= 10;
		if (PView(2) < 0)
			PView(2) += 360;
	}
	// Перемещение координат источника света при помощи клавиш WASD
	else if (nChar == 65) // Клавиша A
	{
		PLight(1) -= 10;
		if (PLight(1) >= 360)
			PLight(1) -= 360;
	}
	else if (nChar == 68) // Клавиша D
	{
		PLight(1) += 10;
		if (PLight(1) < 0)
			PLight(1) += 360;
	}
	else if (nChar == 87) // Клавиша W
	{
		PLight(2) -= 10;
		if (PLight(2) < 0)
			PLight(2) += 360;
	}
	else if (nChar == 83) // Клавиша S
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
	CSizeDialog cSizeDlg; // Объект диалогового окна
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
	if (ClientToBmp(m_hWnd, WinRect, L"Тороид.bmp") == 0)
		MessageBox(L"Файл скриншота окна был успешно создан и сохранен как \"Тороид.bmp\"");
	else
		MessageBox(L"Не удалось записать скриншот окна");
}
int CMainWnd::ClientToBmp(HWND hWnd, RECT rect, LPCWSTR Name)
{
	BITMAPFILEHEADER bmfHdr; // Тип, размер и макет файла в формате DIB
	BITMAPINFOHEADER bi;
	int BitToPixel = 16;	 // Устанавливаем цветовую глубину 16 бит
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
	DWORD dwWritten; // Количество записанных файлов

					 // Открываем файл
	HANDLE fh = CreateFile((LPCWSTR)Name, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return 2;
	bmfHdr.bfType = ('M' << 8) | 'B'; // Заполняем дисковый заголовок
	bmfHdr.bfSize = bi.biSizeImage + sizeof(bmfHdr) + bi.biSize; // Размер файла
	bmfHdr.bfReserved1 = bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = sizeof(bmfHdr) + bi.biSize; // Смещение до начала данных

												   // Запись заголовка в файл										   
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(bmfHdr), &dwWritten, NULL);

	// Запись в файл загружаемого заголовка
	WriteFile(fh, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);

	// Выделяем место в памяти для того,чтобы функция GetDIBits()перенесла
	// туда коды цвета в DIB-формате.
	char *lp = (char *)GlobalAlloc(GMEM_FIXED, bi.biSizeImage);

	// Из карты BitMap строки с нулевой по bi.biHeight функция пересылает
	// в массив lp по формату bi ( беспалитровый формат)
	int err = GetDIBits(hdc, BitMap, 0, (UINT)rect.bottom, lp, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);

	// Запись изображения на диск
	WriteFile(fh, lp, bi.biSizeImage, &dwWritten, NULL);

	// Освобождение памяти и закрытие файла
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
	СLightingDialog СLightingDlg;
	СLightingDlg.SetMod(lightMod);
	if (СLightingDlg.DoModal() == IDOK)
	{
		lightMod = СLightingDlg.GetRButtonStatus();
		Invalidate();
	}
}
void CMainWnd::Exit()
{
	DestroyWindow();
}