// TP_Projekt_4.cpp: Okreœla punkt wejœcia dla aplikacji.
//

#include "stdafx.h"
#include "TP_Projekt_4.h"
#include "ctime"
#include "cstdlib"

#define MAX_LOADSTRING 100



//pozycja liny dzwigu(do zmian)
struct position 
{
	int x = 292;
	int y = 350;
};
struct chest
{
	int x;
	int y = 370;
	bool CheckTheHook = false;
	int waga=100;
};
position rope;
chest object;

	


// Zmienne globalne:
HINSTANCE hInst;                                // bie¿¹ce wyst¹pienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytu³u
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna g³ównego

// Przeka¿ dalej deklaracje funkcji do³¹czonych w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND losujwage;


void DrawTheRope(HWND);
void ClearTheRope(HWND);
void GetImage(HDC, HWND);
void DrawTheObject(HWND);
void ClearTheObject(HWND);


void GetImage(HDC hdc, HWND hwnd) 
{
	HBITMAP hbmObraz;
	BITMAP bmInfo;
	hbmObraz = (HBITMAP) LoadImage(NULL, L"dzwig.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HDC hdcNowy = CreateCompatibleDC(NULL);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcNowy, hbmObraz);
	GetObject(hbmObraz, sizeof(bmInfo), &bmInfo);
	hdc = GetDC(hwnd);
	BitBlt(hdc, 50, 50, bmInfo.bmWidth, bmInfo.bmHeight, hdcNowy, 0, 0, SRCCOPY);
	ReleaseDC(hwnd, hdc);

	DeleteObject(hbmObraz); // kasowanie bitmapy
	SelectObject(hdcNowy, hbmOld);
	DeleteDC(hdcNowy);
}




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	//Inicjalizacja GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // TODO: W tym miejscu umieœæ kod.
	srand(time(NULL));

    // Zainicjuj ci¹gi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TP_PROJEKT_4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjacje aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TP_PROJEKT_4));
    MSG msg;

	

    // G³ówna pêtla wiadomoœci:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	GdiplusShutdown(gdiplusToken);
    return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  CEL: Rejestruje klasê okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TP_PROJEKT_4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TP_PROJEKT_4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   CEL: Zapisuje dojœcie wyst¹pienia i tworzy okno g³ówne
//
//   KOMENTARZE:
//
//        W tej funkcji dojœcie wyst¹pienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyœwietlane okno g³ówne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Przechowuj dojœcie wyst¹pienia w zmiennej globalnej
   
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 900, 550, nullptr, nullptr, hInstance, nullptr);
 
   losujwage = CreateWindowEx(0, L"BUTTON", L"LOSUJ WAGE", WS_CHILD | WS_VISIBLE, 740, 100, 100, 30, hWnd, NULL, hInstance, NULL);
  


   
   object.x =  292 +rand()%(700-292+1);
   

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  CEL: Przetwarza wiadomoœci dla okna g³ównego.
//
//  WM_COMMAND — przetwarzaj menu aplikacji
//  WM_PAINT — pomaluj okno g³ówne
//  WM_DESTROY — opublikuj komunikat o rezygnacji i wróæ
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
		case WM_KEYDOWN:
		{
			switch ((int)wParam)
			{
			case VK_RIGHT:
				if (rope.x <= 710) {
					ClearTheRope(hWnd);
					rope.x += 1;
					DrawTheRope(hWnd);
					if (object.CheckTheHook)
					{
						ClearTheObject(hWnd);
						object.x += 1;
						DrawTheObject(hWnd);
					}
				
			}
		break;
		case VK_LEFT:
			if (rope.x >= 292) {
				ClearTheRope(hWnd);
				rope.x -= 1;
				DrawTheRope(hWnd);
				if (object.CheckTheHook)
				{
					ClearTheObject(hWnd);
					object.x -= 1;
					DrawTheObject(hWnd);
				}
			}
			
			break;
		case VK_UP:
			if (rope.y >= 148) {
				ClearTheRope(hWnd);
				rope.y -= 2;
				DrawTheRope(hWnd);
				if (object.CheckTheHook)
				{
					ClearTheObject(hWnd);
					object.y -= 2;
					DrawTheObject(hWnd);
				}
			}
			break;
		case VK_DOWN:
			if (rope.y < 370) {
				ClearTheRope(hWnd);
				rope.y += 2;
				DrawTheRope(hWnd);
				if (object.CheckTheHook)
				{
					ClearTheObject(hWnd);
					object.y += 2;
					DrawTheObject(hWnd);
				}
			}
			break;
		case VK_SPACE:
			
			
			if ((rope.x == object.x) && (rope.y == object.y)) {
				if (object.waga >= 300) {
					MessageBox(hWnd, L"Nie uda³o sie podniesc, za gruby sprzet...", L"Komp nie daje rady ;/", MB_OK);
				}
				else object.CheckTheHook = true;
			}
			break;
		case 0x5A:
			if ((rope.x == object.x) && (rope.y == object.y))
			{
				object.CheckTheHook = false;
				while (object.y < 370) {
					ClearTheObject(hWnd);
					object.y += 1;
					DrawTheObject(hWnd);
					Sleep(1);
				}
				
				
			}
			break;
		}
		}
		break;
    case WM_COMMAND:
        {
			HDC hdcWindow = GetDC(hWnd);
            int wmId = LOWORD(wParam);
 
			if ((HWND)lParam == losujwage) {	
				object.waga = 1+ rand() % (400); 
				wchar_t buffer[256];
				wsprintfW(buffer, L"%d", object.waga);
				//MessageBoxW(nullptr, buffer, buffer, MB_OK);
				MessageBox(hWnd, buffer, L"Zmieniasz wage.", MB_OK);
			
			}
			
			

            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
			ReleaseDC(hWnd, hdcWindow);
			}
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			GetImage(hdc, hWnd);
			DrawTheRope(hWnd);
			DrawTheObject(hWnd);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void DrawTheRope(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 0));
	graphics.DrawLine(&pen, rope.x, 127, rope.x, rope.y);
	ReleaseDC(hWnd, hdc);
}

void ClearTheRope(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	Graphics graphics(hdc);
	Pen pen(Color(255, 255, 255, 255));
	graphics.DrawLine(&pen, rope.x, 127, rope.x, rope.y);
	ReleaseDC(hWnd, hdc);
}

void DrawTheObject(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 0));
	graphics.DrawLine(&pen, object.x - 15, object.y, object.x + 15, object.y);
	graphics.DrawLine(&pen, object.x - 15, object.y, object.x - 15, object.y + 60);
	graphics.DrawLine(&pen, object.x + 15, object.y, object.x + 15, object.y + 60);
	graphics.DrawLine(&pen, object.x - 15, object.y + 60, object.x + 15, object.y + 60);
	graphics.DrawLine(&pen, object.x - 15, object.y, object.x + 15, object.y + 60);
	graphics.DrawLine(&pen, object.x + 15, object.y, object.x - 15, object.y + 60);

	ReleaseDC(hWnd, hdc);
}

void ClearTheObject(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	Graphics graphics(hdc);
	Pen pen(Color(255, 255, 255, 255));
	graphics.DrawLine(&pen, object.x - 15, object.y, object.x + 15, object.y);
	graphics.DrawLine(&pen, object.x - 15, object.y, object.x - 15, object.y + 60);
	graphics.DrawLine(&pen, object.x + 15, object.y, object.x + 15, object.y + 60);
	graphics.DrawLine(&pen, object.x - 15, object.y + 60, object.x + 15, object.y + 60);
	graphics.DrawLine(&pen, object.x - 15, object.y, object.x + 15, object.y + 60);
	graphics.DrawLine(&pen, object.x + 15, object.y, object.x - 15, object.y + 60);

	ReleaseDC(hWnd, hdc);
}