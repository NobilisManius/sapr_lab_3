#include <windows.h>
#include <cmath>

const wchar_t windowClass[] = L"win32app";
const wchar_t windowTitle[] = L"Win32API - Пример окна";

int const step = 20;
HPEN pen;
HPEN old_Pen;
HBRUSH brush;
HBRUSH old_brush;
HPEN zero_oppacity_pen;
int pen_size = 2;

class MainElement

{

protected:
    int x, y;
    bool isSelected;

public:
    MainElement()
    {
        x = 60;
        y = 60;
        isSelected = 0;
    }

    void move_to(int Xn, int Yn)
    {
        x += Xn - x;
        x = x - x % 20;
        y += Yn - y;
        y = y - y % 20;
    }

    void select()
    {
        isSelected = 1;
    }

    void deSelect()
    {
        isSelected = 0;
    }

    bool is_selected()
    {
        return isSelected;
    }

    int get_x()
    {
        return x;
    }

    int get_y()
    {
        return y;
    }

    virtual bool print(HWND hWnd, HDC hdc) = 0;
};

class XOR : public MainElement
{
public:
    bool print(HWND hWnd, HDC hdc) override
    {
        if (isSelected == 0)
        {
            pen_size = 2;
        }
        else
        {
            pen_size = 4;
        }

        zero_oppacity_pen = CreatePen(PS_NULL, pen_size, RGB(0, 0, 0));
        pen = CreatePen(PS_SOLID, pen_size, RGB(255, 0, 0));
        old_Pen = (HPEN)SelectObject(hdc, pen);

        Rectangle(hdc, get_x(), get_y(), get_x() + 4 * step, get_y() + 6 * step);
        Ellipse(hdc, get_x() + 2 * step, get_y() + 0 * step, get_x() + 4 * step, get_y() + 2 * step);

        SelectObject(hdc, zero_oppacity_pen);
        LineTo(hdc, get_x(), get_y() + step);   //Я поздно узнал про PS_NULL
        SelectObject(hdc, pen);
        LineTo(hdc, get_x() - step, get_y() + step);
        LineTo(hdc, get_x(), get_y() + step);

        LineTo(hdc, get_x(), get_y() + 4 * step);
        LineTo(hdc, get_x() - step, get_y() + 4 * step);
        LineTo(hdc, get_x(), get_y() + 4 * step);

        SelectObject(hdc, zero_oppacity_pen);
        LineTo(hdc, get_x(), get_y() + 6 * step);
        LineTo(hdc, get_x() + 4 * step, get_y() + 6 * step);
        LineTo(hdc, get_x() + 4 * step, get_y() + step);
        SelectObject(hdc, pen);

        LineTo(hdc, get_x() + 4 * step, get_y() + step);
        LineTo(hdc, get_x() + 5 * step, get_y() + step);
        LineTo(hdc, get_x() + 4 * step, get_y() + step);


        LineTo(hdc, get_x() + 2 * step, get_y() + step);
        LineTo(hdc, get_x() + 3 * step, get_y() + step);
        LineTo(hdc, get_x() + 3 * step, get_y() + 2 * step);
        LineTo(hdc, get_x() + 3 * step, get_y());
        LineTo(hdc, get_x() + 3 * step, get_y() + step);
        LineTo(hdc, get_x() + 5 * step, get_y() + step);


        SelectObject(hdc, old_Pen);
        return TRUE;
    }
};

class NOT : public MainElement
{
public:

    bool print(HWND hWnd, HDC hdc) override
    {
        if (isSelected == 0)
        {
            pen_size = 2;
        }
        else
        {
            pen_size = 4;
        }

        zero_oppacity_pen = CreatePen(PS_NULL, pen_size, RGB(0, 0, 0));
        pen = CreatePen(PS_SOLID, pen_size, RGB(255, 0, 0));
        old_Pen = (HPEN)SelectObject(hdc, pen);

        Rectangle(hdc, get_x(), get_y(), get_x() + 4 * step, get_y() + 6 * step);
        Ellipse(hdc, get_x() + 3 * step, get_y() + 2 * step, get_x() + 5 * step, get_y() + 4 * step);
        LineTo(hdc, get_x() - step, get_y() + 3 * step);
        LineTo(hdc, get_x(), get_y() + 3 * step);
        SelectObject(hdc, zero_oppacity_pen);
        LineTo(hdc, get_x() + 6 * step, get_y() + 3 * step);
        SelectObject(hdc, pen);
        LineTo(hdc, get_x() + 5 * step, get_y() + 3 * step);

        SelectObject(hdc, old_Pen);

        return TRUE;
    }
};

XOR elem1;
NOT elem2;

void draw_grid(HWND hWnd, HDC hdc)
{
    RECT rect;
    GetClientRect(hWnd, &rect);

    brush = CreateSolidBrush(RGB(133, 133, 133));

    old_brush = (HBRUSH)SelectObject(hdc, brush);
    pen = CreatePen(PS_DOT, pen_size, RGB(0,255, 0));
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    SelectObject(hdc, old_brush);

    for (int i = 0; i < (rect.right - step); i+= step)
    {
        LineTo(hdc, i, rect.bottom);
        LineTo(hdc, i + step, rect.bottom);
        LineTo(hdc, i + step, rect.top);

    }
    for (int i = 0; i < (rect.bottom - step); i += step)
    {
        LineTo(hdc, rect.left, i);
        LineTo(hdc, rect.left, i + step);
        LineTo(hdc, rect.right, i + step);
    }
    old_Pen = (HPEN)SelectObject(hdc, pen);
    SelectObject(hdc, old_Pen);
}

void draw_elems(HWND hWnd, HDC hdc)
{
    elem1.print(hWnd, hdc);
    elem2.print(hWnd, hdc);
}

void draw_plot(HWND hWnd, HDC hdc, RECT rectangle)
{
    zero_oppacity_pen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
    pen = CreatePen(PS_SOLID, 2, RGB(50, 166, 50));
    old_Pen = (HPEN)SelectObject(hdc, pen);
    brush = CreateSolidBrush(RGB(50, 166, 50));
    old_brush = (HBRUSH)SelectObject(hdc, brush);

    Rectangle(hdc, rectangle.right - rectangle.right * 2 / 3, 2 * rectangle.bottom / 3, rectangle.right - rectangle.right * 1/3, rectangle.bottom);
    SelectObject(hdc, old_Pen);
    SelectObject(hdc, old_brush);


    double period = 4, axisX = rectangle.bottom / 6, func, stepX, stepY;

    for (double i = 0; i <= 2 * period * 3.14; i += 0.001)
    {
        func = axisX * cos(i);
        stepX = i * rectangle.right / 3 / (2 * period * 3.14);
        SetPixel(hdc, rectangle.right - rectangle.right * 6 / 9 + stepX, rectangle.bottom - axisX - func, RGB(0, 0, 255));
    }


    //ВАХ I = I0*(e^(U/фT)-1)
    //φт = kT/q — температурный потенциал (при 20°C равен 26 мВ);
    
    //double fT = 26 * 0.3;
   //double fT = 0.5;
   //
   //for (double i = 0; i <= 1; i += 0.001)
   //
   //{
   //
   //    func = axisX * 2 * (pow(2.7182, i / fT) - 1);
   //
   //    stepX = i * rectangle.right / 3;
   //
   //    if (rectangle.bottom - axisX - func >= 6 * rectangle.bottom / 9)
   //
   //    {
   //        SetPixel(hdc, rectangle.right - rectangle.right * 6 / 9 + stepX, rectangle.bottom - axisX - func, RGB(0, 0, 255));
   //    }
   //    SetPixel(hdc, rectangle.right - rectangle.right * 6 / 9 + stepX, rectangle.bottom - axisX, RGB(0, 0, 0));
   //}
    

    pen = (HPEN)SelectObject(hdc, zero_oppacity_pen);
    LineTo(hdc, rectangle.right/3, 6 * rectangle.bottom/9);
    pen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
    pen = (HPEN)SelectObject(hdc, pen);
    LineTo(hdc, rectangle.right / 3, 3 * rectangle.bottom / 3);

}

void selection(int test_x, int test_y, WPARAM msg, RECT r)
{
    if (msg & MK_CONTROL)
    {

        if ((elem1.get_x() <= test_x) && (elem1.get_y() <= test_y) && (elem1.get_x() + 4 * step >= test_x) && (elem1.get_y() + 6 * step >= test_y)) //Узнать почему просто с lowword не работает 
        {
            if (elem1.is_selected() != 0)
            {
                elem1.deSelect();
            }
            else
            {
                elem1.select();
            }

        }

        if ((elem2.get_x() <= test_x) && (elem2.get_y() <= test_y) && (elem2.get_x() + 4 * step >= test_x) && (elem2.get_x() + 6 * step >= test_y))
        {
            if (elem2.is_selected() != 0)
            {
                elem2.deSelect();
            }
            else
            {
                elem2.select();
            }

        }

    }
    else
    {
        if (elem1.is_selected())
        {
            if (!((test_x > r.right - r.right * 2 / 3) && (test_x < r.right - r.right * 1 / 3) && (test_y > 2 * r.bottom / 3)))
            {
                elem1.move_to(test_x, test_y);
            }
            elem1.deSelect();
        }

        if (elem2.is_selected())
        {
            if (!((test_x > r.right - r.right * 2 / 3) && (test_x < r.right - r.right * 1 / 3) && (test_y > 2 * r.bottom / 3)))
            {
                elem2.move_to(test_x, test_y);
            }
            elem2.deSelect();
        }
    }
}

void moving(int test_x, int test_y, WPARAM msg, RECT r)
{
    if (!((test_x > r.right - r.right * 2 / 3) && (test_x < r.right - r.right * 1 / 3) && (test_y > 2 * r.bottom / 3)))
    {
        if (elem1.is_selected() || elem2.is_selected())
        {
            elem1.deSelect();
            elem2.deSelect();
        }
        else
        {
            elem2.move_to(test_x, test_y);
        }
    }
}

long __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    PAINTSTRUCT ps;
    HDC hdc;
    RECT r;
    int x_main = 0;
    int y_main = 0;
    GetClientRect(hWnd, &r);

    switch (message) {

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        draw_grid(hWnd, hdc);
        draw_plot(hWnd, hdc, r);
        draw_elems(hWnd, hdc);
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:
        x_main = LOWORD(lParam);
        y_main = HIWORD(lParam);
        selection(x_main, y_main, wParam, r);
        InvalidateRect(hWnd, NULL, true);
        break;

    case WM_RBUTTONDOWN:
        x_main = LOWORD(lParam);
        y_main = HIWORD(lParam);
        moving(x_main, y_main, wParam, r);
        InvalidateRect(hWnd, NULL, true);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = windowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, L"Can’t register window class!", L"Win32 API Test", NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(windowClass, windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, L"Can’t create window!", L"Win32 API Test", NULL);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

