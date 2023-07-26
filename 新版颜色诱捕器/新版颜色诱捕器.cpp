/*
*	本程序名称：EasyX 绘图库硬核实现，颜色诱捕器 ColorPicker 1.0（鼠标移动获取电脑像素点各颜色值）。
*	
*	编译环镜：Microsoft Visual Studio Community 2019 或 2022 版本 16.10.0
*	绘图库：EasyX_20230719(Beta 版)
*	电脑系统：Win10 1809
*	作者：随波逐流 2734596919@qq.com
*
*	程序起始时间：2022 年 7 月 10 日
*	程序最后结束修改时间：2023 年 7 月 20 日：18：53
*
*	地址：
*	目的：实现用 EasyX 绘图库做一个简单的获取桌面各种图像的颜色值，给需要编写 GUI 程序按钮等，有配色的需求的小伙伴们一个硬核参考。
*	历史：本是一个为输入框和按钮协同作战例子，改为一个猎取桌面颜色的小程序。
*
*	编译调试建议：无。
*
*/
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include <graphics.h>				// 绘图库头文件
#include <conio.h>					// 基本头文件
#include<algorithm>					// 针对设置该进程不受系统 DPI 设置影响 的头文件
#include <ShellScalingApi.h>		// 引用头文件
#pragma comment(lib, "Shcore.lib")	// 链接库文件

int WIDTH = 217;			// 程序宽。
int HEIGHT = 308;			// 程序高。

// 程序由以下 24 个核心函数构成缺一不可的逻辑性。代码函数定义位置顺序排列如下：
/* 把程序获取的数据拷备到电脑的粘贴板里复制使用。*/
void setdatatoclip(LPCTSTR color_strdata);

/* 设置获取的颜色数据转换并拷入颜色字符数据里用于颜色框输出。*/
void setcolordatacopy(struct colorpicker_data* color_data1);

/* 设置获取的颜色数据转换并拷入颜色字符数据里用于颜色框输出。*/
void setcolordatacopy1(struct colorpicker_data* color_data1, int* r, int* g, int* b, bool bl, COLORREF clr1);

// 将诱捕的颜色值转为 CMYK 色值数据函数
void RGBtoCMYK(COLORREF rgb, double* c, double* m, double* y, double* k);

/* 捕捉并缩放输出鼠标移动的四块图像至软件里的函数 */
void CaptureImagb(struct colorpicker_data* color_data1, int* r, int* g, int* b, IMAGE* img1, IMAGE* img2, IMAGE* img3, IMAGE* img4, int x1, int y1, int x2, int y2, int w, int h, bool bl);

/* 捕捉颜色被填充到矩形里，时实颜色监控 */
void RGBfillrec(int r, int g, int b, int x1, int y1, int x2, int y2);

/* 画时实监控填充颜色里的锁，和下边的那些文字提示。*/
void text_lock(int x1, int y1, int x2, int y2, bool IMAGE_STATE);

/* 设置字体大小的函数 */
void settextzise(int zise);

/* 输出各种颜色值的函数。*/
void putcolorvalue(struct colorpicker_data* color_data1, int* r, int* g, int* b, int x1, int y1, int x2, int y2);

/* 输出各种颜色值的输出框参数函数。*/
int putcolortextboxparm(int mouse_x, int mouse_y, struct colorpicker_data* textbox_xy, int click, int click_1, bool IMAGE_STATE);

/* 输出鼠标获取的各种颜色值的文体输出框。*/
TCHAR* putcolortextbox(TCHAR* STRING1, TCHAR* STRING0, int x1, int y1, int x2, int y2, int mouse_x, int mouse_y, int textsize1, int click_1, bool IMAGE_STATE);

/* 锁按钮。*/
int button_lock(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1, BOOL* IMAGE_STATE);

/* 输出图像缩放大小值的按钮。*/
int button_zoom(int x1, int y1, int x2, int y2, int mouse_x, int mouse_y, int textsize1, int textsize2, LPCTSTR button_string1, LPCTSTR button_string2, int click_1);

/* 标题栏上的关闭的按钮。*/
int button_x(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1);

/* 标题栏上的信息的按钮。*/
int button_i(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1);

/* 标题栏上的最小化按钮。*/
int button_mini(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, HWND h1, int click_1);

/* 捕捉图像操作栏上的缩放缩大按钮。*/
int button_add(int x111, int y111, int mouse_x, int mouse_y, int click_1);

/* 捕捉图像操作栏上的缩放缩小按钮。*/
int button_addminus(int x111, int y111, int mouse_x, int mouse_y, int click_1);

/* 捕捉图像操作栏上的三角变换状态按钮。*/
int button_triangle(struct colorpicker_data* color_data1, int x111, int y111, int mouse_x, int mouse_y, int click_1);

/* 颜色锁定模式下鼠标移动点击捕捉的图像位置精准采色函数 */
void o(struct colorpicker_data* color_data1, int* r, int* g, int* b, int x1, int y1, int x2, int y2, int w, int h, bool bl);

/* 绘制锁定颜色后鼠标点击获取捕捉图像区域的颜色并跟随鼠标移动的蓝十字圆圈 */
void button_colorcrossring(struct colorpicker_data* color_data1, int mouse_x, int mouse_y, int click_1, BOOL IMAGE_STATE, int w, int h, int r, int g, int b);

/* 绘制标题标 */
void inigra(int i);

/* 初始化函数 */
void initial_drawing();

/* 初始化函数 1，设置程序圆角和去原始标题栏 */
void initial_drawing1(int a);

struct colorpicker_data		// 存放颜色等各种数据结构体。
{
	bool rec = true;
	// 跟随鼠标指针获取的 RGB 的颜色。
	int r2 = 0, g2 = 0, b2 = 0;

	// HSV 颜色
	float h1 = 0, s1 = 0, v1 = 0;

	double h11 = 0, s11 = 0, v11 = 0;

	// CMYK 颜色
	double cc, mm, yy, kk;

	// 用于存放各颜色最终拼接好的值转换后的字符型数据，用函数输出到颜色框里。
	TCHAR color_strdata[8][40 * 5] = { 0 };

	// 用于存放 RGB 值转换后的字符型数据。
	TCHAR R1[50 * 2] = { 0 };
	TCHAR B1[20] = { 0 };
	TCHAR G1[20] = { 0 };

	// 用于存放 RGB 值转换后的字符型数据。
	TCHAR H2[100] = { 0 };
	TCHAR S2[100] = { 0 };
	TCHAR V2[100] = { 0 };

	// 用于存放 RGB 转 16 进制值转换后的字符型数据。
	TCHAR RX[20] = { 0 };
	TCHAR GX[20] = { 0 };
	TCHAR BX[20] = { 0 };

	// 用于存放 CMYK 值转换后的字符型数据。
	TCHAR CC[20] = { 0 };
	TCHAR MM[20] = { 0 };
	TCHAR YY[20] = { 0 };
	TCHAR KK[20] = { 0 };

	// 获取桌面的四个 DC，用于捕捉四块图像，然后拼成一个整的图像，目的是让捕捉颜色中心对齐。
	HDC srcDC1 = GetDC(NULL);
	HDC srcDC2 = GetDC(NULL);
	HDC srcDC3 = GetDC(NULL);
	HDC srcDC4 = GetDC(NULL);

	// 处理桌面的四个 DC 用于缩放四块图像，然后拼成一个整的图像，然后存入图片对象输出。
	HDC dstDC1;
	HDC dstDC2;
	HDC dstDC3;
	HDC dstDC4;

	// 获取桌面颜色的 dc。
	HDC color_dc = GetDC(NULL);
	// 获取全局鼠标坐标，用于获取软件外的颜色值和坐标。
	POINT pt;

	// 捕捉的图像缩放值，分别为长向高。
	int zoom_data[11][3] =
	{
		{3, 1},
		{7, 4},
		{15, 8},
		{26, 14},
		{38, 20},
		{48, 20},
		{54, 28},

		{54 + 6, 28 + 8},
		{54 + 6 + 6, 28 + 8 + 8},
		{54 + 6 + 6 + 6, 28 + 8 + 8 + 8},
		{54 + 6 + 6 + 6 + 6, 28 + 8 + 8 + 8 },
	};

	// 捕捉的图像大小缩放值的初始值，分别为长向高。
	int zoom_x = 54, zoom_y = 29;

	// 按钮三角的状态，奇数代表三角是正三角，偶数是倒三角。
	int button_triangle_state = 0;

	// 三维数组的巧妙应用于，颜色输出框的名字。
	TCHAR textbox_stringchar1[7][8][15] =
	{
		{ _T("X_Y") },
		{ _T("RGB") },
		{ _T("HSV")},
		{ _T("HEX1") },
		{ _T("HEX2") },
		{ _T("CMYK") },
	};

	// 颜色输出框坐标微调。
	int xk0 = 1, xk1 = 1, yg1 = 2, yg2 = 3;
	// 二维数组的巧妙应用于，获取的颜色输出框坐标。
	int textbox_int[7][15] =
	{
		{4 + xk0, 5 + 38 - yg1, 134 + 10 + 4 - xk1 , 25 + 38 - yg2, 11},
		{4 + xk0, 25 + 38 - yg1, 134 + 10 + 4 - xk1 , 45 + 38 - yg2, 11},
		{4 + xk0, 45 + 38 - yg1, 134 + 10 + 4 - xk1 , 65 + 38 - yg2, 11},
		{4 + xk0, 65 + 38 - yg1, 134 + 10 + 4 - xk1, 85 + 38 - yg2, 11},
		{4 + xk0, 85 + 38 - yg1, 134 + 10 + 4 - xk1 , 105 + 38 - yg2, 11},
		{4 + xk0, 105 + 38 - yg1, 134 + 10 + 4 - xk1, 125 + 38 - yg2, 11},
	};
};

/* 把程序获取的数据拷备到电脑的粘贴板里复制使用。*/
void setdatatoclip(LPCTSTR color_strdata)
{
	// 初始粘贴板。
	if (!OpenClipboard(NULL) || !EmptyClipboard())return;

	size_t i1;

	// 内存块。
	HGLOBAL Memory_block;

	char color_strdata1[500 * 4] = { 0 };

	// TCHAR 转 char。
	wcstombs_s(&i1, color_strdata1, (size_t)500 * 4, color_strdata, wcslen(color_strdata));
	// 分配全局内存块。
	Memory_block = GlobalAlloc(GMEM_MOVEABLE, ((strlen(color_strdata1) + 1) * sizeof(TCHAR)));

	if (!Memory_block)
	{
		// 关闭粘贴板。
		CloseClipboard();
		return;
	}
	// 锁定内存。
	LPSTR lpStr = (LPSTR)GlobalLock(Memory_block);
	if (lpStr == NULL)return;
	// 复制内存。
	memcpy(lpStr, color_strdata1, ((strlen(color_strdata1)) * sizeof(TCHAR)));
	// 字符结束符。
	lpStr[strlen(color_strdata1)] = (TCHAR)0;
	// 释放锁。
	GlobalUnlock(Memory_block);
	// 把内存里的颜色数据复制到粘贴板里。
	SetClipboardData(CF_TEXT, Memory_block);
	// 关闭粘贴板。
	CloseClipboard();
	// 返回。
	return;
}

/* 设置获取的颜色数据转换并拷入颜色字符数据里用于颜色框输出。*/
void setcolordatacopy(struct colorpicker_data* color_data1)
{
	// 拼接复制重组结构体里的 RGB 颜色数据到结构体里的颜色字符型数据用于字符输出。
	_tcscat_s(color_data1->R1, _T(", "));
	_tcscat_s(color_data1->G1, _T(", "));

	TCHAR RGB11[200] = { 0 };
	_tcscat_s(RGB11, color_data1->R1);
	_tcscat_s(RGB11, color_data1->G1);
	_tcscat_s(RGB11, color_data1->B1);
	_tcscpy_s(color_data1->color_strdata[1], RGB11);

	// 拼接复制重组结构体里的 HSV 颜色数据到结构体里的颜色字符型数据用于字符输出。
	_tcscat_s(color_data1->H2, _T(", "));
	_tcscat_s(color_data1->S2, _T(", "));
	_tcscat_s(color_data1->H2, color_data1->S2);
	_tcscat_s(color_data1->H2, color_data1->V2);
	_tcscpy_s(color_data1->color_strdata[2], color_data1->H2);

	// 拼接复制重组结构体里的 CMYK 颜色数据到结构体里的颜色字符型数据用于字符输出。
	_tcscat_s(color_data1->CC, _T(", "));
	_tcscat_s(color_data1->MM, _T(", "));
	_tcscat_s(color_data1->YY, _T(", "));
	_tcscat_s(color_data1->CC, color_data1->MM);
	_tcscat_s(color_data1->CC, color_data1->YY);
	_tcscat_s(color_data1->CC, color_data1->KK);
	_tcscpy_s(color_data1->color_strdata[5], color_data1->CC);
}
/* 设置获取的颜色数据转换并拷入颜色字符数据里用于颜色框输出。*/
void setcolordatacopy1(struct colorpicker_data* color_data1, int* r, int* g, int* b, bool bl, COLORREF clr1)
{
	*r = GetRValue(clr1);		// 分解出红色值。
	*g = GetGValue(clr1);		// 分解出绿色值。
	*b = GetBValue(clr1);		// 分解出蓝色值。

	color_data1->r2 = *r;		// 把颜色值 R 复制到结构体里。
	color_data1->g2 = *g;		// 把颜色值 G 复制到结构体里。
	color_data1->b2 = *b;		// 把颜色值 B 复制到结构体里。

	TCHAR XY[250] = { 0 };		// 字符型全局鼠标的 X_Y 坐标。

	if (bl == true)swprintf(XY, 50, _T("%d x %d"), color_data1->pt.x, color_data1->pt.y);		// 转换整形鼠标坐标。
	if (bl == true)_tcscpy_s(color_data1->color_strdata[0], XY);								// 复制转换后鼠标坐标至结构体。


	RGBtoHSV(RGB(*r, *g, *b), &color_data1->h1, &color_data1->s1, &color_data1->v1);			// 转换获取的 RGB 颜色为 HSV。

	swprintf_s(color_data1->R1, _T("%d"), color_data1->r2);										// 转换 R 颜色值为字符型。
	swprintf_s(color_data1->G1, _T("%d"), color_data1->g2);										// 转换 G 颜色值为字符型。
	swprintf_s(color_data1->B1, _T("%d"), color_data1->b2);										// 转换 B 颜色值为字符型。

	double hh = 0, ss = 0, vv = 0;																// 临时 HSV 颜色值。
	long ykk = 100;

	color_data1->s11 = color_data1->s1, color_data1->v11 = color_data1->v1;

	if ((hh = (int)color_data1->h1) == color_data1->h1)											 // 转换 H 颜色值为字符型。
	{
		swprintf_s(color_data1->H2, _T("%d"), (int)color_data1->h1);
	}
	else
	{
		swprintf_s(color_data1->H2, _T("%.2f"), color_data1->h1);
	}

	if ((ss = (int)color_data1->s1) == color_data1->s1)											// 转换 S 颜色值为字符型。
	{
		long ss1 = (long)round(color_data1->s11 * ykk);

		swprintf_s(color_data1->S2, _T("%d"), ss1);
	}
	else
	{
		long ss1 = (long)round(color_data1->s11 * ykk);
		swprintf_s(color_data1->S2, _T("%d"), ss1);
	}

	if ((vv = (int)color_data1->v1) == color_data1->v1)											// 转换 V 颜色值为字符型。
	{
		long vv1 = (long)round(color_data1->v11 * ykk);
		swprintf_s(color_data1->V2, _T("%d"), vv1);

	}
	else
	{
		long vv1 = (long)round(color_data1->v11 * ykk);
		swprintf_s(color_data1->V2, _T("%d"), vv1);
	}


	// 下面都是把 RGB 颜色值转为 16 进制的操作，# 是 C++ 使用，0X 是 C 语言使用。
	TCHAR HEX[600] = { _T("#") };
	TCHAR HEX2[600] = { _T("0x") };

	_itow_s(*r, color_data1->RX, 16);								// 转换 R 颜色值为 16 进制。
	_itow_s(*g, color_data1->GX, 16);								// 转换 G 颜色值为 16 进制。
	_itow_s(*b, color_data1->BX, 16);								// 转换 B 颜色值为 16 进制。

	if (wcslen(color_data1->RX) == 1)								// 判断 R 颜色值 16 进制高位是否为空，如果是就高位补零。
	{
		TCHAR RX1[100] = { 0 };										// 暂存 16 进制
		wcsncpy_s(RX1, color_data1->RX, 100);
		wcsncpy_s(color_data1->RX, _T("\0"), 100);					// 变成空的。

		wcsncat_s(color_data1->RX, _T("0"), 100);					// 高位补零。
		wcsncat_s(color_data1->RX, RX1, 100);						// 低位补 16 进制。
	}
	if (wcslen(color_data1->GX) == 1)								// 判断 G 颜色值 16 进制高位是否为空，如果是就高位补零。
	{
		TCHAR GX1[100] = { 0 };										// 暂存 16 进制
		wcsncpy_s(GX1, color_data1->GX, 100);
		wcsncpy_s(color_data1->GX, _T("\0"), 100);					// 变成空的。

		wcsncat_s(color_data1->GX, _T("0"), 100);					// 高位补零。
		wcsncat_s(color_data1->GX, GX1, 100);						// 低位补 16 进制。
	}
	if (wcslen(color_data1->BX) == 1)								// 判断 B 颜色值 16 进制高位是否为空，如果是就高位补零。
	{
		TCHAR BX1[100] = { 0 };										// 暂存 16 进制
		wcsncpy_s(BX1, color_data1->BX, 100);
		wcsncpy_s(color_data1->BX, _T("\0"), 100);					// 变成空的。

		wcsncat_s(color_data1->BX, _T("0"), 100);					// 高位补零。
		wcsncat_s(color_data1->BX, BX1, 100);						// 低位补 16 进制。
	}

	if (bl == true)wcsncat_s(HEX, color_data1->RX, 100);			// 拼接成完整的 16 进制颜色值。
	if (bl == true)wcsncat_s(HEX, color_data1->GX, 100);			// 拼接成完整的 16 进制颜色值。	
	if (bl == true)wcsncat_s(HEX, color_data1->BX, 100);			// 拼接成完整的 16 进制颜色值。	

	if (bl == true)wcsncat_s(HEX2, color_data1->RX, 100);			// 拼接成完整的 16 进制颜色值。
	if (bl == true)wcsncat_s(HEX2, color_data1->GX, 100);			// 拼接成完整的 16 进制颜色值。
	if (bl == true)wcsncat_s(HEX2, color_data1->BX, 100);			// 拼接成完整的 16 进制颜色值。

	if (bl == true)_tcscpy_s(color_data1->color_strdata[3], HEX);	// 拼接成完整的 16 进制颜色值。
	if (bl == true)_tcscpy_s(color_data1->color_strdata[4], HEX2);	// 拼接成完整的 16 进制颜色值。
																	// 转换 CMYK。
	RGBtoCMYK(RGB(*r, *g, *b), &color_data1->cc, &color_data1->mm, &color_data1->yy, &color_data1->kk);
	// 转换成字符型 CMYK 颜色值。
	swprintf_s(color_data1->CC, _T("%d"), (long)color_data1->cc);
	swprintf_s(color_data1->MM, _T("%d"), (long)color_data1->mm);
	swprintf_s(color_data1->YY, _T("%d"), (long)color_data1->yy);
	swprintf_s(color_data1->KK, _T("%d"), (long)color_data1->kk);
}
// 将诱捕的颜色值转为 CMYK 色值数据函数
void RGBtoCMYK(COLORREF rgb, double* c, double* m, double* y, double* k)

{
	BYTE R = GetRValue(rgb);

	BYTE G = GetGValue(rgb);

	BYTE B = GetBValue(rgb);

	*k = (int)(min(min(255 - R, 255 - G), 255 - B) / 2.55);

	double MyR = R / 2.55;

	double Div = 100 - *k;

	if (Div == 0)Div = 1;

	*c = ((100 - MyR - *k) / Div) * 100;

	int MyG = (int)(G / 2.55);

	*m = ((100 - (double)MyG - (double)*k) / Div) * 100;

	int MyB = (int)(B / 2.55);

	*y = ((100 - (double)MyB - (double)*k) / Div) * 100;

}

/* 捕捉并缩放输出鼠标移动的四块图像至软件里的函数 */
void CaptureImagb(struct colorpicker_data* color_data1, int* r, int* g, int* b, IMAGE* img1, IMAGE* img2, IMAGE* img3, IMAGE* img4, int x1, int y1, int x2, int y2, int w, int h, bool bl)
{
	// 微调。
	int Width1 = 3;
	int temp = y2, ra = 10, rb = 10, rc = 8, rd = 8;
	// 转换全局鼠标。
	GetCursorPos(&color_data1->pt);

	// 获取当前鼠标点像素值
	COLORREF clr1 = GetPixel(color_data1->color_dc, color_data1->pt.x, color_data1->pt.y);

	// 颜色数据转换并拷入颜色字符数据。
	setcolordatacopy1(color_data1, r, g, b, bl, clr1);

	int r1 = GetRValue(clr1);	// 分解出红色值
	int g1 = GetGValue(clr1);	// 分解出绿色值
	int b1 = GetBValue(clr1);	// 分解出蓝色值

	if (color_data1->rec == false)
	{
		ra = 15; rb = 15; rc = 14; rd = 14;
		y2 = y1 + 25;

	}
	else if (color_data1->rec == true)
	{
		ra = 10; rb = 10; rc = 8; rd = 8;
		y2 = temp;
	}

	// 画捕捉部分外框。
	setfillcolor(RGB(53, 53, 53));
	setlinecolor(RGB(61, 68, 89));
	roundrect(x1, y1 - Width1, x2, y2, ra, rb);

	// 画捕捉部分外框。
	setfillcolor(RGB(53, 53, 53));
	fillroundrect(x1 + 1, y1 + 1 - Width1, x2 - 1, y2 - 1, ra, rb);

	// 画捕捉部分外框。
	setfillcolor(RGB(53, 53, 53));
	fillroundrect(x1 + 1, y1 + 1 - Width1, x2 - 1, y2 - 1, rc, rd);

	// 拼接鼠标移动捕捉的图像。
	putimage(x1 + 2, y1 + 25 - 0, img1);
	putimage(x1 + 106 + 1 + 1, y1 + 25 - 0, img2);
	putimage(x1 + 2, y1 + 25 + 55, img3);
	putimage(x1 + 106 + 1 + 1, y1 + 25 + 55, img4);

	// 画捕捉部分外框。
	roundrect(x1 + 1, y1 + 1 - Width1, x2 - 1, y2 - 1, 10, 10);
	roundrect(x1 + 1, y1 + 1 - Width1, x2 - 1, y2 - 1, 8, 8);

	// 画捕捉部分操作栏下边的分界线。
	setlinecolor(RGB(61, 68, 89));
	line(x1 + 2, y1 + 25 - 2, x2 - 2, y1 + 25 - 2);
	line(x1 + 2, y1 + 25 - 1, x2 - 2, y1 + 25 - 1);

	// 画捕捉部分，中心的红十字。
	setlinecolor(RED);
	line(x1 + 108, y1 + 80 - 2, x1 + 108, y1 + 80 - 5);
	line(x1 + 108 + 2, y1 + 80, x1 + 108 + 5, y1 + 80);
	line(x1 + 108, y1 + 80 + 2, x1 + 108, y1 + 80 + 5);
	line(x1 + 108 - 2, y1 + 80, x1 + 108 - 5, y1 + 80);

	// 画捕捉部分，锁定后的中心点和圆。
	if (bl == false)
	{
		setlinecolor(RGB(74, 111, 153));
		circle(x1 + 108, y1 + 80, 8);
		setlinecolor(RGB(74, 111, 153));
		line(x1 + 108 - 6, y1 + 80, x1 + 108 - 12, y1 + 80);
		line(x1 + 108 + 6, y1 + 80, x1 + 108 + 12, y1 + 80);
		line(x1 + 108, y1 + 80 - 6, x1 + 108, y1 + 80 - 12);
		line(x1 + 108, y1 + 80 + 6, x1 + 108, y1 + 80 + 12);
	}

	// 画捕捉部分，中心点的 X 和圆，会随着捕捉颜色变化而变化。
	if (bl == true)setlinecolor(RGB(r1, g1, b1));
	if (bl == true)line(x1 + 108, y1 + 80, x1 + 108 + 20, y1 + 80 - 20);
	if (bl == true)line(x1 + 108, y1 + 80, x1 + 108 + 20, y1 + 80 + 20);
	if (bl == true)line(x1 + 108, y1 + 80, x1 + 108 - 20, y1 + 80 + 20);
	if (bl == true)line(x1 + 108, y1 + 80, x1 + 108 - 20, y1 + 80 - 20);
	if (bl == true)circle(x1 + 108, y1 + 80, 15);

	// 把缩放后的 DC 图像保存到图片对象里。
	if (bl == true)
	{
		color_data1->dstDC1 = GetImageHDC(img1);
		color_data1->dstDC2 = GetImageHDC(img2);
		color_data1->dstDC3 = GetImageHDC(img3);
		color_data1->dstDC4 = GetImageHDC(img4);
	}

	// 核心缩放函数，捉取鼠标移动的图像缩放至 DC 里。
	if (bl == true)
	{
		StretchBlt(color_data1->dstDC1, 0, 0, w, h, color_data1->srcDC1, color_data1->pt.x - color_data1->zoom_x, color_data1->pt.y - color_data1->zoom_y, color_data1->zoom_x, +color_data1->zoom_y, SRCCOPY);
		StretchBlt(color_data1->dstDC2, 0, 0, w, h, color_data1->srcDC2, color_data1->pt.x, color_data1->pt.y - color_data1->zoom_y, +color_data1->zoom_x, +color_data1->zoom_y, SRCCOPY);
		StretchBlt(color_data1->dstDC3, 0, 0, w, h, color_data1->srcDC3, color_data1->pt.x - color_data1->zoom_x, color_data1->pt.y, +color_data1->zoom_x, +color_data1->zoom_y, SRCCOPY);
		StretchBlt(color_data1->dstDC4, 0, 0, w, h, color_data1->srcDC4, color_data1->pt.x, color_data1->pt.y, color_data1->zoom_x, color_data1->zoom_y, SRCCOPY);
	}

	settextcolor(RGB(109, 160, 160));

	// 输出两种不同状态的文字提示，按字符键锁定颜色程序。
	if (bl == true)
	{
		settextzise(10);
		outtextxy(0 + 14, 131 + 38 + 5 - 7 + 2, _T("Press any key"));
		outtextxy(0 + 3, 131 + 38 + 5 - 7 + 2 + 2 + 8, _T("to lock the color"));
	}
	// 输出两种不同状态的文字提示，点击鼠标获取复制颜色值。
	else if (bl == false)
	{
		settextzise(10);
		outtextxy(0 + 10, 131 + 38 + 5 - 7 + 2, _T("Click the cross"));
		outtextxy(0 + 3, 131 + 38 + 5 - 7 + 2 + 2 + 8, _T("to get the color"));
	}
}

/* 捕捉颜色被填充到矩形里，时实颜色监控 */
void RGBfillrec(int r, int g, int b, int x1, int y1, int x2, int y2)
{
	// 画时实捕捉颜色的外框体。
	setlinecolor(RGB(61, 61, 61));
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 11, 11);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 10, 10);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 9, 9);
	setlinecolor(RGB(85, 85, 85));

	// 画时实捕捉的颜色。
	setfillcolor(RGB(r, g, b));
	fillroundrect(x1 + 3, y1 + 3, x2 - 3, y2 - 3, 11, 11);
	fillroundrect(x1 + 3, y1 + 3, x2 - 3, y2 - 3, 10, 10);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
}
/* 画时实监控填充颜色里的锁，和下边的那些文字提示。*/
void text_lock(int x1, int y1, int x2, int y2, bool IMAGE_STATE)
{
	// 画框体
	setfillcolor(RGB(61, 68, 89));
	setlinecolor(RGB(61, 61, 61));
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 11, 11);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 10, 10);
	roundrect(x1 + 1, y1 + 1, x2 - 1, y2 - 1, 9, 9);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	setlinecolor(RGB(85, 85, 85));
	fillroundrect(x1 + 3, y1 + 3, x2 - 3, y2 - 3, 11, 11);
	fillroundrect(x1 + 3, y1 + 3, x2 - 3, y2 - 3, 10, 10);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	// 画分界线
	line(x1 + 3, y1 + 19, x2 - 3, y1 + 19);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	// 画点击复制颜色值的文字提示。
	settextzise(12);
	settextcolor(RGB(131, 143, 165));
	outtextxy(154, 88 + 38 - 1, _T(" click to"));
	outtextxy(153, 98 + 38 - 1, _T(" copy the"));
	outtextxy(165, 111 + 38 - 1, _T(" colo"));

	setfillcolor(RGB(61, 68, 89));
	setlinecolor(RGB(85, 85, 85));

	// false 为按键按下的锁定状态，画锁上的锁。
	if (IMAGE_STATE == false)
	{	// false 为按键按下的锁定状态。
		settextzise(11);
		settextcolor(RGB(244, 82, 82));
		outtextxy(164, 73 + 38 - 1, _T("Locked"));
	}
	// true 为按键按下的解锁状态，画解锁的锁。
	if (IMAGE_STATE == true)
	{	// true 为按键按下的解锁状态。
		settextzise(11);
		settextcolor(RGB(183, 80, 80));
		outtextxy(158, 73 + 38 - 1, _T("Unlocked"));
	}
}
/* 设置字体大小的函数 */
void settextzise(int zise)
{
	LOGFONT f;
	gettextstyle(&f);									// 获取当前字体设置。
	f.lfHeight = zise;									// 设置字体高度为 48。

	_tcscpy_s(f.lfFaceName, _T("宋体"));
	f.lfQuality = ANTIALIASED_QUALITY;					// 设置输出效果为抗锯齿。

	settextstyle(&f);
	setbkmode(TRANSPARENT);								// 设置透明的背景。
}

/* 输出各种颜色值的函数。*/
void putcolorvalue(struct colorpicker_data* color_data1, int* r, int* g, int* b, int x1, int y1, int x2, int y2)
{
	// 画输出各种颜色值框体的函数
	setlinecolor(RGB(61, 61, 61));
	setfillcolor(RGB(53, 53, 53));
	fillrectangle(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
	// 设置获取的颜色数据转换并拷入颜色字符数据里用于颜色框输出。
	setcolordatacopy(color_data1);
}
/* 输出各种颜色值的输出框参数函数。*/
int putcolortextboxparm(int mouse_x, int mouse_y, struct colorpicker_data* textbox_xy, int click, int click_1, bool IMAGE_STATE)
{
	for (int i = 0; i < 6; i++)
	{
		// 输出鼠标获取的各种颜色值的文体输出框。
		putcolortextbox(textbox_xy->color_strdata[i], textbox_xy->textbox_stringchar1[i][0], textbox_xy->textbox_int[i][0], textbox_xy->textbox_int[i][1], textbox_xy->textbox_int[i][2], textbox_xy->textbox_int[i][3], mouse_x, mouse_y, textbox_xy->textbox_int[i][4], click_1, IMAGE_STATE);
	}
	return 0;
}
/* 输出鼠标获取的各种颜色值的文体输出框。*/
TCHAR* putcolortextbox(TCHAR* STRING1, TCHAR* STRING0, int x1, int y1, int x2, int y2, int mouse_x, int mouse_y, int textsize1, int click_1, bool IMAGE_STATE)
{
	if (STRING1 == NULL) { return NULL; };	// 判断传进来的指针数组是否为空。

	setlinecolor(DARKGRAY);					// 绘制低亮边框
	roundrect(x1, y1, x2, y2, 5, 5);
	int chenwidth = 1;						// 中英文输入框字符宽边变换变量				

	settextzise(textsize1);					// 设置字体大小函数。
	TCHAR charwidth[4][55] = { {_T("奈")}, {'N'}, {'n'}, {'0'} };

	// 画颜色的名字框
	setlinecolor(DARKGRAY);
	roundrect(x1, y1, (textwidth(charwidth[0]) * 5) - 4, y2, 5, 5);
	line((textwidth(charwidth[0]) * 5) - 4, y1 + 2, (textwidth(charwidth[0]) * 5) - 4, y2 - 2);

	// 这里等于 0 代表鼠标移动中。
	if (click_1 == 0)
	{
		// 画鼠标移动到名字框里就画高亮边框颜色。
		if (mouse_x > x1 && mouse_y > y1 && mouse_x < x2 && mouse_y < y2)
		{
			setlinecolor(RGB(63, 62, 67));
			roundrect(x1, y1, (textwidth(charwidth[0]) * 5) - 4, y2, 5, 5);
			line((textwidth(charwidth[0]) * 5) - 4, y1 + 2, (textwidth(charwidth[0]) * 5) - 4, y2 - 2);
		}
		if (mouse_x > x1 && mouse_y > y1 && mouse_x < (textwidth(charwidth[0]) * 5) - 4 && mouse_y < y2)
		{
			setlinecolor(RGB(187, 148, 170));
			roundrect(x1, y1, (textwidth(charwidth[0]) * 5) - 4, y2, 5, 5);
			line((textwidth(charwidth[0]) * 5) - 4, y1 + 2, (textwidth(charwidth[0]) * 5) - 4, y2 - 2);
		}
	}

	// 这里等于 1 代表鼠标点击了颜色框里的名字框，就启动复制颜色值和颜色名字到粘贴板里。
	if (click_1 == 1)
	{
		// 颜色框里名字范围。
		if (mouse_x > x1 && mouse_y > y1 && mouse_x < (textwidth(charwidth[0]) * 5) - 4 && mouse_y < y2)
		{
			// 加上颜色名称至颜色数据里。
			TCHAR colordata0[200] = { 0 };
			if (!wcscmp(STRING0, _T("HSV")))
			{
				wcscpy_s(colordata0, _T("HSVtoRGB"));
			}
			else
			{
				wcscpy_s(colordata0, STRING0);
			}
			_tcscat_s(colordata0, _T("("));
			_tcscat_s(colordata0, STRING1);
			_tcscat_s(colordata0, _T(")"));
			// 把 colordata0 里颜色值加名称数据拷备到电脑的粘贴板里复制使用。
			setdatatoclip(colordata0);
		}
	}
	// 输出颜色框的名字。
	settextzise(15);
	settextcolor(RGB(132, 132, 132));
	outtextxy((((((textwidth(charwidth[0]) * 4) + 5) - x1) / 2)) - (textwidth(STRING0) / 2), (((y2 - y1) / 2) + y1) - (textheight(STRING0[0]) / 2), STRING0);

	// 暂存值。
	float temp = textwidth(charwidth[0]) * (float)3.5;
	long temp1 = (long)temp;
	x1 = temp1;
	// 设置字体大小。
	settextzise(textsize1);

	// 当鼠标移动颜色输出框就启动移动相关的
	if (click_1 == 0)
	{
		int cursor_xy = x1 + 5;
		int strlen = 0;

		// 画颜色输出框框体。
		setfillcolor(RGB(63, 62, 67));
		solidroundrect(x1, y1, x2, y2, 5, 5);
		setlinecolor(DARKGRAY);
		roundrect(x1, y1, x2, y2, 5, 5);

		// 画鼠标移动到颜色输出上时边框的颜色。
		if (click_1 == 0)
		{
			if (mouse_x > x1 && mouse_y > y1 && mouse_x < x2 && mouse_y < y2)
			{	// 画鼠标移动框框颜色。
				setlinecolor(RGB(93, 138, 154));
				roundrect(x1, y1, x2, y2, 5, 5);
			}
		}
		// 灵活设置颜色输出框里的字体大小。
		if (wcslen(STRING1) != 0)
		{
			if (wcslen(STRING1) > 14 && wcslen(STRING1) <= 18)
			{
				settextzise(9);
			}

			// 输出获取的各种颜色值数据。
			for (size_t i = 0; i < wcslen(STRING1); i++)
			{
				settextcolor(RGB(175, 172, 191));
				outtextxy((((x2 - x1) / 2) + x1) - (textwidth(STRING1) / 2), (((y2 - y1) / 2) + y1) - (textheight(charwidth[chenwidth]) / 2), STRING1);
			}
		}
	}
	// 框判断大小
	if (x1 == 0 || x2 == 0 || y1 == 0 || y2 == 0)
	{
		x1 = 10; x2 = 10; y1 = 30; y2 = 40;
	}
	if (x1 != 0 && x2 != 0 && y1 != 0 && y2 != 0)
	{
		if ((x2 - x1) < 40)x2 = x2 + (40 - (x2 - x1));
		if ((y2 - y1) < 15)	y2 = y2 + (15 - (y2 - y1));
	}

	if (textheight(charwidth[0]) > (y2 - y1))
	{
		settextzise((y2 - y1) - 4);
		textsize1 = (y2 - y1) - 4;
	}

	// 鼠标点击这个颜色输出就得到这个颜色框的颜色数据到剪切板里。
	if (click_1 == 1)
	{	// 框范围判断。
		if (mouse_x > x1 && mouse_y > y1 && mouse_x < x2 && mouse_y < y2)
		{
			if (IMAGE_STATE == false)FlushBatchDraw();
			// 鼠标点击颜色框的特效。
			setlinecolor(RGB(187, 148, 170));
			roundrect(x1 + 2, y1 + 2, x2 - 2, y2 - 2, 5, 5);
			// 保存绘图内容到当前程序下。
			saveimage(_T("color.bmp"));
			// 把鼠标选中的颜色值，复制到，剪切板中，复制使用。
			setdatatoclip(STRING1);

			Sleep(200);
		}
	}
	// 返回 1 说明，鼠标点到了该输入框，可以通过 if 函数来判断返回值 1 要干什么。
	return NULL;
}

/* 锁按钮。*/
int button_lock(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1, BOOL* IMAGE_STATE)
{
	// 画时实填充获取颜色框里头的锁。锁上的状态和解锁的状态。
	// false 为按键按下的锁定状态，画锁上的锁。
	if (*IMAGE_STATE == false)
	{
		// 画两种颜色透明上锁的锁体。
		setlinecolor(RGB(61, 61, 61));
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		roundrect(192, 87, 207, 98, 5, 3);
		roundrect(192, 87, 207, 98, 6, 4);
		setlinecolor(RGB(85, 85, 85));
		roundrect(192 + 1, 87 + 1, 207 - 1, 98 - 1, 4, 4);
		setlinecolor(RGB(85, 85, 85));
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

		// 画两种颜色透明上锁的锁环。
		setlinecolor(RGB(61, 61, 61));
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		arc(194, 79, 205, 95, 0, 40.62);
		setlinecolor(RGB(85, 85, 85));
		arc(194 + 1, 79 + 2, 205 - 1, 95 - 2, 0, 40.5);
		setlinestyle(PS_ENDCAP_SQUARE, 1);
		setlinecolor(RGB(61, 61, 61));

		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		roundrect(192, 87, 207, 98, 5, 3);
		roundrect(192, 87, 207, 98, 6, 4);
	}
	// 画时实填充获取颜色框里头的锁。锁上的状态和解锁的状态。
	// true 为按键按下的解锁状态，画解锁的锁。
	if (*IMAGE_STATE == TRUE)
	{
		// 画两种颜色透明解锁的锁体。
		setlinecolor(RGB(61, 61, 61));
		setfillcolor(RGB(61, 68, 89));
		roundrect(192, 87, 207, 98, 5, 3);
		roundrect(192, 87, 207, 98, 6, 4);
		setlinecolor(RGB(85, 85, 85));
		roundrect(192 + 1, 87 + 1, 207 - 1, 98 - 1, 4, 4);

		// 画两种颜色透明解锁的锁环。
		setlinecolor(RGB(61, 61, 61));
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		arc(197 - 10, 79, 197, 95, 0, 41.1);
		setlinecolor(RGB(85, 85, 85));
		arc(197 - 9, 79 + 1, 197 - 1, 95 - 2, 0, 41.1);
		setlinestyle(PS_ENDCAP_SQUARE, 1);
	}
	if (mouse_x > x111 && mouse_y > y111 && mouse_x < x222 && mouse_y < y222)						// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
	{
		if (*IMAGE_STATE == false)
		{
			// 画两种颜色透明上锁的锁体。
			setlinecolor(RGB(61, 61, 61));
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
			roundrect(192, 87, 207, 98, 5, 3);
			roundrect(192, 87, 207, 98, 6, 4);
			setlinecolor(RGB(41, 219, 112));
			roundrect(192 + 1, 87 + 1, 207 - 1, 98 - 1, 4, 4);
			setlinecolor(RGB(85, 85, 85));
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

			// 画两种颜色透明上锁的锁环。
			setlinecolor(RGB(61, 61, 61));
			setlinestyle(PS_ENDCAP_SQUARE, 2);
			arc(194, 79, 205, 95, 0, 40.62);
			setlinecolor(RGB(41, 219, 112));
			arc(194 + 1, 79 + 2, 205 - 1, 95 - 2, 0, 40.5);
			setlinestyle(PS_ENDCAP_SQUARE, 1);
			setlinecolor(RGB(61, 61, 61));

			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
			roundrect(192, 87, 207, 98, 5, 3);
			roundrect(192, 87, 207, 98, 6, 4);

		}
		// 画时实填充获取颜色框里头的锁。锁上的状态和解锁的状态。
		// true 为按键按下的解锁状态，画解锁的锁。
		if (*IMAGE_STATE == TRUE)
		{
			// 画两种颜色透明解锁的锁体。
			setlinecolor(RGB(61, 61, 61));
			setfillcolor(RGB(61, 68, 89));
			roundrect(192, 87, 207, 98, 5, 3);
			roundrect(192, 87, 207, 98, 6, 4);
			setlinecolor(RGB(41, 219, 112));
			roundrect(192 + 1, 87 + 1, 207 - 1, 98 - 1, 4, 4);

			// 画两种颜色透明解锁的锁环。
			setlinecolor(RGB(61, 61, 61));
			setlinestyle(PS_ENDCAP_SQUARE, 2);
			arc(197 - 10, 79, 197, 95, 0, 41.1);
			setlinecolor(RGB(41, 219, 112));
			arc(197 - 9, 79 + 1, 197 - 1, 95 - 2, 0, 41.1);
			setlinestyle(PS_ENDCAP_SQUARE, 1);
		}
		if (click_1 == 1)																// 如果点击等于 1 就启动点击按钮特效。
		{
			*IMAGE_STATE = true;
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}
/* 输出图像缩放大小值的按钮。*/
int button_zoom(int x1, int y1, int x2, int y2, int mouse_x, int mouse_y, int textsize1, int textsize2, LPCTSTR button_string1, LPCTSTR button_string2, int click_1)
{
	settextzise(textsize1);																// 设置字体大小函数。
	setlinecolor(RGB(83, 99, 105));														// 设置按钮颜色的外框线体函数。
	settextcolor(RGB(207, 143, 143));													// 设置按钮白色的字体函数。
	setfillcolor(RGB(83, 99, 105));														// 使用修改颜色的 RGB 数组，可改变数组从而来自由改变颜色。
	fillroundrect(x1, y1, x2, y2, 10, 10);												// 画按钮矩形，有圆角 20，对接按钮的前四个坐标数组。																						// 设置居中显示按钮的文字。
	outtextxy((((x2 - x1) / 2) + x1) - (textwidth(button_string1) / 2), (((y2 - y1) / 2) + y1) - (textheight(button_string1) / 2), button_string1);
	// 特制按钮，字体居中算法，不知是否比自带的效率高？但失去了一些强大的功能。

	if (mouse_x > x1 && mouse_y > y1 && mouse_x < x2 && mouse_y < y2)					// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
	{
		//	setlinestyle(PS_ENDCAP_FLAT);
		setlinecolor(RGB(72, 105, 93));													// 选中按钮后把线条变颜色。
		settextcolor(RGB(255, 153, 164));												// 选中按钮后，把文字变成白色。
		setfillcolor(RGB(134, 152, 163));												// 使用修改颜色的 RGB 数组，可改变数组从而来自由改变颜色。
		setbkmode(TRANSPARENT);															// 把文字背景设置成透明的。
		fillroundrect(x1, y1, x2, y2, 10, 10);											// 填充的矩形，画选中的，按钮的意思。
		outtextxy((((x2 - x1) / 2) + x1) - (textwidth(button_string2) / 2), (((y2 - y1) / 2) + y1) - (textheight(button_string2) / 2), button_string2);
		// 特制按钮，字体居中算法：按钮长度减按钮起点除一半得没有起点的一半，再加上起点得按钮宽度中心点减字符串宽度的一半得居左右中字体
		if (click_1 == 1) {}															// 如果点击等于 1 就启动点击按钮特效。
		return 1;																		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	return 0;																			// 如果按钮没有被鼠标选中就返回 0。
}

/* 标题栏上的关闭的按钮。*/
int button_x(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1)
{
	int x = x111 + 11, y = y111 + 11, x11 = 5, y11 = 5;
	// 画叉矩形外框
	setlinecolor(RGB(36, 39, 50));
	setfillcolor(RGB(171, 69, 76));
	fillroundrect(x111, y111, x222, y222, 10, 10);
	fillroundrect(x111, y111, x222, y222, 8, 8);
	fillroundrect(x111, y111, x222, y222, 9, 9);
	// 画黑叉
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
	setlinecolor(RGB(36, 39, 50));
	line(x, y, x - x11, y - y11);
	line(x, y, x + x11, y - y11);
	line(x, y, x + x11, y + y11);
	line(x, y, x - x11, y + y11);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	// 鼠标移动到叉上的样子
	if (mouse_x > x111 && mouse_y > y111 && mouse_x < x222 && mouse_y < y222)						// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
	{
		// 画叉矩形外框
		setfillcolor(RGB(153, 80, 85));
		fillroundrect(x111, y111, x222, y222, 10, 10);
		fillroundrect(x111, y111, x222, y222, 8, 8);
		fillroundrect(x111, y111, x222, y222, 9, 9);
		setlinecolor(RGB(129, 42, 48));
		// 鼠标选中的红叉
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
		line(x, y, x - x11, y - y11);
		line(x, y, x + x11, y - y11);
		line(x, y, x + x11, y + y11);
		line(x, y, x - x11, y + y11);
		line(x - 1, y - 1, x - x11 - 1, y - y11 - 1);
		line(x + 1, y - 1, x + x11 + 1, y - y11 - 1);
		line(x + 1, y + 1, x + x11 + 1, y + y11 + 1);
		line(x - 1, y + 1, x - x11 - 1, y + y11 + 1);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

		if (click_1 == 1)																			// 如果点击等于 1 就启动点击按钮特效。
		{
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}
/* 标题栏上的信息的按钮。*/
int button_i(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, int click_1)
{
	int x = 200, y = 15, x11 = 5, y11 = 5;
	// 画框体。
	setlinecolor(RGB(36, 39, 50));
	setfillcolor(RGB(80, 138, 80));
	fillroundrect(x111, y111, x222, y222, 10, 10);
	fillroundrect(x111, y111, x222, y222, 8, 8);
	fillroundrect(x111, y111, x222, y222, 9, 9);
	// 画感叹号。
	setfillcolor(RGB(71, 111, 71));
	setlinecolor(RGB(71, 111, 71));
	solidrectangle((x111 + ((x222 - x111) / 2)) - 1, y111 + 2 + 1, (x111 + ((x222 - x111) / 2)) + 1, y111 + 2 + 4);
	solidrectangle((x111 + ((x222 - x111) / 2)) - 1, y111 + 2 + 4 + 2, (x111 + ((x222 - x111) / 2)) + 1, y111 + 2 + 4 + 2 + 10);

	if (mouse_x > x111 && mouse_y > y111 && mouse_x < x222 && mouse_y < y222)						// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
	{
		// 画框体。
		setlinecolor(RGB(36, 39, 50));
		setfillcolor(RGB(70, 110, 70));
		fillroundrect(x111, y111, x222, y222, 10, 10);
		fillroundrect(x111, y111, x222, y222, 8, 8);
		fillroundrect(x111, y111, x222, y222, 9, 9);
		// 鼠标选中的画感叹号。
		setfillcolor(RGB(48, 75, 48));
		setlinecolor(RGB(48, 75, 48));
		solidrectangle((x111 + ((x222 - x111) / 2)) - 1, y111 + 2 + 1, (x111 + ((x222 - x111) / 2)) + 1, y111 + 2 + 4);
		solidrectangle((x111 + ((x222 - x111) / 2)) - 1, y111 + 2 + 4 + 2, (x111 + ((x222 - x111) / 2)) + 1, y111 + 2 + 4 + 2 + 10);

		// 鼠标点击信息按钮后要干的事。
		if (click_1 == 1)																			// 如果点击等于 1 就启动点击按钮特效。
		{
			// setfillcolor(RGB(145, 109, 140));
			// solidroundrect(3, 38, 212, 126 + 38 - 1, 10, 10);
			ShellExecuteW(NULL, _T("open"), _T("IEXPLORE"), _T("https://codebus.cn/naynjin/ra/colorpicker1"), NULL, SW_SHOWMAXIMIZED);
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}
/* 标题栏上的最小化按钮。*/
int button_mini(int x111, int y111, int x222, int y222, int mouse_x, int mouse_y, HWND h1, int click_1)
{
	// 画最小化按钮外框。
	setlinecolor(RGB(36, 39, 50));
	setfillcolor(RGB(82, 104, 141));
	fillroundrect(x111, y111, x222, y222, 10, 10);
	fillroundrect(x111, y111, x222, y222, 8, 8);
	fillroundrect(x111, y111, x222, y222, 9, 9);
	// 画杠。
	setlinecolor(RGB(68, 73, 90));
	line(x111 + 3, y222 - 4, x222 - 3, y222 - 4);
	line(x111 + 3, y222 - 5, x222 - 3, y222 - 5);
	line(x111 + 3, y222 - 6, x222 - 3, y222 - 6);

	if (mouse_x > x111 && mouse_y > y111 && mouse_x < x222 && mouse_y < y222)						// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
	{
		// 画鼠标选中的最小化按钮外框。
		setlinecolor(RGB(36, 39, 50));
		setfillcolor(RGB(71, 91, 123));
		fillroundrect(x111, y111, x222, y222, 10, 10);
		fillroundrect(x111, y111, x222, y222, 8, 8);
		fillroundrect(x111, y111, x222, y222, 9, 9);
		setlinecolor(RGB(51, 55, 69));
		// 画鼠标选中的最小化框。
		line(x111 + 3, y222 - 4, x222 - 3, y222 - 4);
		line(x111 + 3, y222 - 5, x222 - 3, y222 - 5);
		line(x111 + 3, y222 - 6, x222 - 3, y222 - 6);

		if (click_1 == 1)																			// 如果点击等于 1 就启动点击按钮特效。
		{
			// 鼠标点击，启动最小化命令。
			ShowWindow(h1, SW_SHOWMINIMIZED);
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}
/* 捕捉图像操作栏上的缩放缩大按钮。*/
int button_add(int x111, int y111, int mouse_x, int mouse_y, int click_1)
{
	// 画外圆
	setlinecolor(RGB(102, 108, 143));
	setfillcolor(RGB(102, 108, 143));
	fillcircle(x111, y111, 9);

	setlinestyle(PS_ENDCAP_SQUARE, 2);			 // 设置 2 的粗
	setlinecolor(RGB(36, 39, 50));
	/* 以圆中心 x_y 轴 向东南西北分别绘制并组成十字 */
	line(x111, y111, x111 - 7, y111);
	line(x111, y111, x111, y111 - 7);
	line(x111, y111, x111 + 7, y111);
	line(x111, y111, x111, y111 + 7);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);	// 返原 1 的粗

	if (mouse_x > x111 - 9 && mouse_y > y111 - 9 && mouse_x < x111 + 9 && mouse_y < y111 + 9)						// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
	{	// 画外圆
		setfillcolor(RGB(73, 76, 101));
		setlinecolor(RGB(73, 76, 101));
		fillcircle(x111, y111, 9);

		setlinecolor(RGB(52, 54, 72));
		/* 画鼠标选中后以圆中心 x y 轴 向东南西北分别绘制并组成十字 */
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		line(x111, y111, x111 - 5, y111);
		line(x111, y111, x111, y111 - 5);
		line(x111, y111, x111 + 5, y111);
		line(x111, y111, x111, y111 + 5);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

		if (click_1 == 1)																	// 如果点击等于 1 就启动点击按钮特效。
		{
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}
/* 捕捉图像操作栏上的缩放缩小按钮。*/
int button_addminus(int x111, int y111, int mouse_x, int mouse_y, int click_1)
{
	// 画外圆
	setlinecolor(RGB(102, 108, 143));
	setfillcolor(RGB(102, 108, 143));
	fillcircle(x111, y111, 9);
	// 画减号
	setlinestyle(PS_ENDCAP_SQUARE, 2);
	setlinecolor(RGB(36, 39, 50));
	line(x111, y111, x111 - 7, y111);
	line(x111, y111, x111 + 7, y111);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	if (mouse_x > x111 - 9 && mouse_y > y111 - 9 && mouse_x < x111 + 9 && mouse_y < y111 + 9)						// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
	{	// 画外圆
		setfillcolor(RGB(73, 76, 101));
		setlinecolor(RGB(73, 76, 101));
		fillcircle(x111, y111, 9);

		setlinecolor(RGB(52, 54, 72));
		// 画鼠标选中的减号
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		line(x111, y111, x111 - 5, y111);
		line(x111, y111, x111 + 5, y111);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
		if (click_1 == 1)																	// 如果点击等于 1 就启动点击按钮特效。
		{
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}
/* 捕捉图像操作栏上的三角变换状态按钮。*/
int button_triangle(struct colorpicker_data* color_data1, int x111, int y111, int mouse_x, int mouse_y, int click_1)
{
	// 多边形坐标
	int pts1[7] = { x111 - 5, y111 + 4, x111, y111 - 6, x111 + 5, y111 + 4 };
	int pts[7] = { x111 - 5, y111 - 4, x111, y111 + 6, x111 + 5, y111 - 4 };

	// 画外圆
	setlinecolor(RGB(102, 108, 143));
	setpolyfillmode(WINDING);
	setfillcolor(RGB(102, 108, 143));
	fillcircle(x111, y111, 9);

	setlinestyle(PS_ENDCAP_SQUARE, 2);
	setlinecolor(RGB(36, 39, 50));
	setpolyfillmode(WINDING);
	setfillcolor(RGB(36, 39, 50));

	// 如果状态等于偶数那就画负三角。
	if ((color_data1->button_triangle_state % 2) == 0)
	{
		solidpolygon((POINT*)pts, 3);
	}
	// 如果状态等于奇数那就画正三角。
	else if ((color_data1->button_triangle_state % 2) != 0)
	{
		solidpolygon((POINT*)pts1, 3);
	}
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	if (mouse_x > x111 - 9 && mouse_y > y111 - 9 && mouse_x < x111 + 9 && mouse_y < y111 + 9)						// 判断鼠标是否在按钮内部，如果是就执行高亮按钮代码。
	{
		// 画外圆
		setfillcolor(RGB(73, 76, 101));
		setlinecolor(RGB(73, 76, 101));
		fillcircle(x111, y111, 9);

		setlinecolor(RGB(52, 54, 72));
		// 红底
		setlinestyle(PS_ENDCAP_SQUARE, 2);
		setpolyfillmode(WINDING);
		setfillcolor(RGB(52, 54, 72));

		// 如果状态等于偶数那就画鼠标选中的负三角。
		if ((color_data1->button_triangle_state % 2) == 0)
		{
			solidpolygon((POINT*)pts, 3);
		}
		// 如果状态等于奇数那就画鼠标选中的正三角。
		else if ((color_data1->button_triangle_state % 2) != 0)
		{
			solidpolygon((POINT*)pts1, 3);
		}
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

		if (click_1 == 2)				// 如果点击等于 1 就启动点击按钮特效。
		{
			// 鼠标点击的外圆
			setfillcolor(RGB(73, 76, 101));
			setlinecolor(RGB(73, 76, 101));
			fillcircle(x111, y111, 9);

			setlinecolor(RGB(52, 54, 72));
			setlinestyle(PS_ENDCAP_SQUARE, 2);
			setpolyfillmode(WINDING);
			setfillcolor(RGB(52, 54, 72));

			// 如果状态等于偶数那就画鼠标点击的负三角。
			if ((color_data1->button_triangle_state % 2) == 0)
			{
				solidpolygon((POINT*)pts, 3);
				color_data1->button_triangle_state++;
			}
			// 如果状态等于奇数那就画鼠标点击的正三角。
			else if ((color_data1->button_triangle_state % 2) != 0)
			{
				solidpolygon((POINT*)pts1, 3);
				color_data1->button_triangle_state++;
			}
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
			return 1;
		}
		// 返回 1 说明，鼠标点到了该按钮，可以通过 if 函数来判断返回值 1 要干什么。
	}
	// 如果按钮没有被鼠标选中就返回 0。
	return 0;
}

/* 颜色锁定模式下鼠标移动点击捕捉的图像位置精准采色函数 */
void o(struct colorpicker_data* color_data1, int* r, int* g, int* b, int x1, int y1, int x2, int y2, int w, int h, bool bl)
{
	// 获取点颜色
	GetCursorPos(&color_data1->pt);
	COLORREF clr1 = GetPixel(color_data1->color_dc, color_data1->pt.x, color_data1->pt.y);
	// 画红十字。
	setlinecolor(RED);
	line(x1 + 108, y1 + 80 - 2, x1 + 108, y1 + 80 - 5);
	line(x1 + 108 + 2, y1 + 80, x1 + 108 + 5, y1 + 80);
	line(x1 + 108, y1 + 80 + 2, x1 + 108, y1 + 80 + 5);
	line(x1 + 108 - 2, y1 + 80, x1 + 108 - 5, y1 + 80);

	// 设置获取的颜色数据转换并拷入颜色字符数据里用于颜色框输出。
	setcolordatacopy1(color_data1, r, g, b, bl, clr1);
	setcolordatacopy(color_data1);
}
/* 绘制锁定颜色后鼠标点击获取捕捉图像区域的颜色并跟随鼠标移动的蓝十字圆圈 */
void button_colorcrossring(struct colorpicker_data* color_data1, int mouse_x, int mouse_y, int click_1, BOOL IMAGE_STATE, int w, int h, int r, int g, int b)
{
	if (IMAGE_STATE == false)
	{
		// 捕捉图像区域
		if (mouse_x > 2 && mouse_y > 192 && mouse_x < 213 && mouse_y < 301)
		{
			// 绘制鼠标跟随的蓝十字圈。
			setlinecolor(RGB(74, 111, 153));
			circle(mouse_x, mouse_y, 8);
			setlinecolor(RGB(74, 111, 153));
			line(mouse_x - 6, mouse_y, mouse_x - 12, mouse_y);
			line(mouse_x + 6, mouse_y, mouse_x + 12, mouse_y);
			line(mouse_x, mouse_y - 6, mouse_x, mouse_y - 12);
			line(mouse_x, mouse_y + 6, mouse_x, mouse_y + 12);
		}
	}
	if (IMAGE_STATE == false)
	{	// 鼠标点击获取颜色值。
		if (click_1 == 0)
		{
			// 捕捉图像区域
			if (mouse_x > 2 && mouse_y > 192 && mouse_x < 213 && mouse_y < 301)
			{
				// 获取颜色值。
				o(color_data1, &r, &g, &b, 0, 167, 215, 267 + 38 + 5 - 7, w, h, true);
				// 填充获取的颜色值至矩形。
				RGBfillrec(r, g, b, 150, 38 + 1, 212, 80 + 38 - 15);
				// 防闪
				text_lock(150, 81 + 38 - 15, 212, 126 + 38 - 1, IMAGE_STATE);
				// 复制颜色值。
				setdatatoclip(color_data1->color_strdata[1]);
				// 绘制鼠标点击跟随的蓝十字圈。
				setlinecolor(RGB(133, 197, 255));
				circle(mouse_x, mouse_y, 8);
				setlinecolor(RGB(133, 197, 255));
				line(mouse_x - 4, mouse_y, mouse_x - 8, mouse_y);
				line(mouse_x + 4, mouse_y, mouse_x + 8, mouse_y);
				line(mouse_x, mouse_y - 4, mouse_x, mouse_y - 8);
				line(mouse_x, mouse_y + 4, mouse_x, mouse_y + 8);
			}
		}
	}
}
/* 绘制标题标 */
void inigra(int i)
{	// 绘制标题栏所需的坐标数据。
	int x = 200, y = 15, d = 2, x11 = 5, y11 = 5;
	int x1 = 0, y1 = 0, x2 = 228, y2 = 30;
	// 设置字体大小。
	settextzise(16);

	// 状态 0：当鼠标没有在界面上标题栏就会变深色。
	if (i == 0)
	{
		setfillcolor(RGB(53, 58, 71));
		solidrectangle(0, 0, 228, 30);
	}
	// 状态 1：当鼠标在界面上标题栏就会变成和背景一样的颜色。
	if (i == 1)
	{
		setfillcolor(RGB(61, 68, 89));
		solidrectangle(0, 0, 228, 30);
	}
	// 绘制分界线。
	setlinecolor(RGB(36, 39, 50));
	line(x1, y2, x2, y2);
	line(x1, y2 + 1, x2, y2 + 1);
	line(x1, y2 + 2, x2, y2 + 2);
	// 输出标题名称。
	settextcolor(RGB(145, 109, 140));
	outtextxy(10, 10, _T("ColorPicker 1.0"));
	setfillcolor(RGB(197, 85, 89));
	// 移动标题栏时加上关闭按钮和信息按钮还有最小化按钮不会闪。
	button_x(189, 4, 211, 26, 0, 0, 1);
	button_i(165, 4, 187, 26, 0, 0, 1);
	button_mini(141, 4, 163, 26, 0, 0, NULL, 2);
}
/* 初始化函数 */
void initial_drawing()
{
	// 设置该进程不受系统 DPI 设置影响
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	// 初始大小。
	initgraph(WIDTH, HEIGHT);

	// 设置背景颜色。
	setbkmode(RGB(61, 68, 89));
	cleardevice();

	setbkcolor(RGB(61, 68, 89));

	cleardevice();
	settextcolor(RGB(0, 132, 132));
}
/* 初始化函数 1，设置程序圆角和去原始标题栏 */
void initial_drawing1(int a)
{
	HWND hWnd = GetHWnd();

	// 去掉原始标题栏。
	SetWindowLong
	(
		hWnd,
		GWL_STYLE,
		GetWindowLong(hWnd, GWL_STYLE)
		& ~
		(WS_CAPTION | WS_DLGFRAME | WS_BORDER)
	);

	SetWindowLong
	(
		hWnd, GWL_EXSTYLE,
		GetWindowLong(hWnd, GWL_EXSTYLE) &
		~(WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME));
	// 设置去年标题栏。
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED
	);

	// 设置程序圆角。
	HRGN rgn = CreateRoundRectRgn(0, 0, WIDTH, HEIGHT - 3 - a, 15, 15);
	SetWindowRgn(hWnd, rgn, true);
	// 显示自绘标题栏。
	inigra(1);
}

// int main()（如果项目是控制台程序使用这个经典主函数。）

// int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)（如果项目是 win32 程序使用这主函数。）

// 主函数
int main(int argc, char* argv[])
{
	// 初始化函数。
	initial_drawing();
	// 设置程序圆角和去原始标题栏。
	initial_drawing1(0);
	// 绘制标题标。
	inigra(1);

	HWND h1;
	h1 = GetHWnd();

	// 定义主函数各种数据值的结构体。
	struct colorpicker_data color_data;
	// 定义主函数各种数据值的结构体指针。
	struct colorpicker_data* color_data1 = &color_data;
	// 捕捉鼠标移动图像四块中其一的大小宽高数值。
	int w = 106, h = 55;
	// 控制标题栏的变量，用于判断鼠标是否在当前软件上，使其标题栏变色。
	int inigra_variable0 = 1;
	// 控制标题栏的变量，用于判断状态，是否在软件上，偶数在，奇数不在。
	int inigra_variable01 = 2;
	// 前者用于缩放按钮缩放的次数和增减量选择缩放值，后者用于打印当前缩放量显示。
	int button_zoom_variable0 = 5, button_zoom_variable1 = 5;
	// 前者用于三角按钮，正三角捕捉图像缩起和倒三角捕捉图像展开的状态判定，偶数倒，奇数正，后者用于判定，按键锁定颜色值，偶数解锁颜色，奇数锁定颜色。
	int triangle_state = 2, key_colorstate = 2;


	// 存放捕捉图像的缩放值的字符型。
	TCHAR ZOOM[200] = { 0 };
	// 主体循环函数的中断条件。
	BOOL TURE1 = true;
	BOOL TURE2 = true;
	// 按键锁定颜色值，锁定捕捉图像的真假判定，真为，不锁定颜色，假锁定颜色。
	BOOL IMAGE_STATE = true;

	// 捕捉鼠标移动的四块图像。
	IMAGE img1;
	IMAGE img2;
	IMAGE img3;
	IMAGE img4;

	// 修改捕捉鼠标移动的四块图像大小。不可用于循环，否则运行到一定时间会因为这个函数，塴掉程序。
	Resize(&img1, w, h);
	Resize(&img2, w, h);
	Resize(&img3, w, h);
	Resize(&img4, w, h);

	// 准备出颜色输出框。
	putcolortextboxparm(NULL, NULL, color_data1, 33, 3, NULL);

	// 定义消息函数。
	ExMessage m;

	// 开启双缓冲。
	BeginBatchDraw();
	// 主程序循环。
	while (TURE2 && TURE1)
	{
		// RGB 颜色值。
		int r = 0, g = 0, b = 0;

		// 系统鼠标。
		POINT pt11;

		// 系统鼠标转为窗口坐标。
		GetCursorPos(&pt11);
		ScreenToClient(h1, &pt11);

		setbkcolor(RGB(61, 68, 89));

		// 界面主体。
		if (IMAGE_STATE)
		{
			// 刷新清屏
			cleardevice();
			// 捕捉鼠标移动的图像和颜色值。
			CaptureImagb(color_data1, &r, &g, &b, &img1, &img2, &img3, &img4, 0, 167, 215, 267 + 38 + 5 - 7, w, h, true);
			// 时实填充鼠标移动捕捉的颜色值至矩形。
			RGBfillrec(r, g, b, 150, 38 + 1, 212, 80 + 38 - 15);
			// 时实输出鼠标移动捕捉的颜色值数据。
			putcolorvalue(color_data1, 0, 0, 0, 3, 38, 149, 126 + 38 - 1);

			setlinecolor(RGB(53, 53, 53));
		}
		else
		{
			// 按键按下锁定颜色后的捕捉鼠标移动的图像和颜色值。
			CaptureImagb(color_data1, &r, &g, &b, &img1, &img2, &img3, &img4, 0, 167, 215, 267 + 38 + 5 - 7, w, h, false);
		}

		// 获取窗口消息，获取按键 ESC 消息，获取按键按下消息。
		if (peekmessage(&m, EX_KEY | EX_CHAR | EX_WINDOW, true))
		{
			// 判断标题栏的，用于判断鼠标是否在当前软件上，不在使其标题栏变色，在使恢复颜色。
			if (m.message == WM_ACTIVATE)
			{
				if ((inigra_variable01 % 2) == 0)
				{
					inigra_variable0 = 1;
					++inigra_variable01;
					flushmessage(-1);
				}
				else if ((inigra_variable01 % 2) != 0)
				{
					inigra_variable0 = 0;
					++inigra_variable01;
					flushmessage(-1);
				}
			}
			// 获取按键 ESC 消息弹出提示框。
			else if (m.message == WM_KEYDOWN)
			{
				if (m.vkcode == VK_ESCAPE)
				{
					if (MessageBox(h1, _T("是否退出软件颜色诱捕器？\n"), _T("颜色诱捕器-询问"), MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						flushmessage(-1);
						TURE2 = false;
						TURE1 = false;
					}
					else
					{
						flushmessage(-1);
						continue;
					}
				}
			}
			// 获取按键按下消息，偶数解锁颜色值与图像状态，奇数锁定图像颜色状态，每次按下数值都会增加。
			if (peekmessage(&m, EX_KEY | EX_CHAR, true))
			{
				if ((key_colorstate % 2) == 0)
				{
					++key_colorstate;
					IMAGE_STATE = false;
					setdatatoclip(color_data1->color_strdata[1]);
					flushmessage(-1);
				}
				else if ((key_colorstate % 2) != 0)
				{
					IMAGE_STATE = true;
					++key_colorstate;
					flushmessage(-1);
				}
			}
			flushmessage(-1);
		}

			// 鼠标移动至标题栏。
			inigra(inigra_variable0);
			swprintf(ZOOM, 200, _T("ZOOM:%d"), button_zoom_variable1 * 10);
			// 鼠标移动至信息提示框。
			text_lock(150, 81 + 38 - 15, 212, 126 + 38 - 1, IMAGE_STATE);
			// 鼠标移动至时实输出缩放值框。
			button_zoom(90, 168, 143, 187, pt11.x, pt11.y, 12, 13, ZOOM, ZOOM, 0);
			// 鼠标移动至标题栏关闭按钮。
			button_x(189, 4, 211, 26, pt11.x, pt11.y, 1);
			// 鼠标移动至标题栏信息按钮上。
			button_i(165, 4, 187, 26, pt11.x, pt11.y, 2);
			// 鼠标移动至标题栏最小化按钮上。
			button_mini(141, 4, 163, 26, pt11.x, pt11.y, h1, 2);
			// 鼠标移动至图像操作栏三角变换状态按钮上。
			button_triangle(color_data1, 200, 178, pt11.x, pt11.y, 1);
			// 鼠标移动至图像操作栏缩放缩大状态按钮上。
			button_add(178, 178, pt11.x, pt11.y, 1);
			// 鼠标移动至图像操作栏缩放缩小状态按钮上。
			button_addminus(156, 178, pt11.x, pt11.y, 1);

		// 鼠标移动输入框中的高亮边框绘制与鼠标离开输入框的恢复低亮边框。
		putcolortextboxparm(pt11.x, pt11.y, color_data1, 33, 0, IMAGE_STATE);
		// 绘制锁定颜色后鼠标点击获取捕捉图像区域的颜色并跟随鼠标移动的蓝十字圆圈。
		button_colorcrossring(color_data1, pt11.x, pt11.y, 1, IMAGE_STATE, w, h, r, g, b);
		button_lock(192, 79, 207, 98, pt11.x, pt11.y, 0, &IMAGE_STATE);
		// 鼠标点击判定。
		if ((GetAsyncKeyState(VK_LBUTTON)) && TURE1)
		{
			button_lock(192, 79, 207, 98, pt11.x, pt11.y, 1, &IMAGE_STATE);
			// 判定鼠标是否点击标题栏信息按钮。
			button_i(165, 4, 187, 26, pt11.x, pt11.y, 1);
			// 判定鼠标是否点击标题栏最小化按钮。
			button_mini(141, 4, 163, 26, pt11.x, pt11.y, h1, 1);
			// 判定鼠标是否点击操作栏缩放值按钮。
			button_zoom(90, 168, 143, 187, pt11.x, pt11.y, 12, 13, ZOOM, ZOOM, 0);
			// 绘制锁定颜色后鼠标点击获取捕捉图像区域的颜色并跟随点击鼠标移动的蓝十字圆圈。
			button_colorcrossring(color_data1, pt11.x, pt11.y, 0, IMAGE_STATE, w, h, r, g, b);
			// 判定鼠标是否点击标题栏关闭按钮。
			if (button_x(189, 4, 211, 26, pt11.x, pt11.y, 1) == 1)
			{
				TURE2 = false;
				TURE1 = false;
			};

			// 判定鼠标是否点击图像操作栏缩放缩大状态按钮上。
			if (button_add(178, 178, pt11.x, pt11.y, 1) == 1)
			{
				if (button_zoom_variable0 == 0 || button_zoom_variable1 == 0) { continue; }
				if (color_data1->zoom_x != 0 || color_data1->zoom_y != 0)
				{
					if (color_data1->zoom_x > 0 || color_data1->zoom_y > 0)
					{
						button_zoom_variable0 -= 1;
						button_zoom_variable1 -= 1;
						color_data1->zoom_x = color_data1->zoom_data[button_zoom_variable0][0];
						color_data1->zoom_y = color_data1->zoom_data[button_zoom_variable0][1];
					}
					Sleep(40);
				}
			}
			// 判定鼠标是否点击图像操作栏缩放缩小状态按钮上。
			if (button_addminus(156, 178, pt11.x, pt11.y, 1) == 1)
			{
				if (button_zoom_variable0 == 10 || button_zoom_variable1 == 10) { continue; }
				if (abs(color_data1->zoom_x) != 0 || abs(color_data1->zoom_y) != 0)
				{
					button_zoom_variable0 += 1;
					button_zoom_variable1 += 1;
					color_data1->zoom_x = color_data1->zoom_data[button_zoom_variable0][0];
					color_data1->zoom_y = color_data1->zoom_data[button_zoom_variable0][1];
					Sleep(40);
				}
			}

			// 判定鼠标是否点击标图像操作栏三角变换状态按钮上。
			if (button_triangle(color_data1, 200, 178, pt11.x, pt11.y, 2) == 1)
			{
				if ((triangle_state % 2) == 0)
				{
					// 移动标题栏防闪。
					text_lock(150, 81 + 38 - 15, 212, 126 + 38 - 1, IMAGE_STATE);
					button_zoom(90, 168, 143, 187, pt11.x, pt11.y, 12, 13, ZOOM, ZOOM, 1);
					// 修改绘图区大小
					initial_drawing1(114 - 2);
					Resize(NULL, WIDTH, HEIGHT - 118);
					color_data1->rec = false;
					triangle_state++;
					Sleep(100);
				}
				else if ((triangle_state % 2) != 0)
				{
					// 移动标题栏防闪。
					text_lock(150, 81 + 38 - 15, 212, 126 + 38 - 1, IMAGE_STATE);
					button_zoom(90, 168, 143, 187, pt11.x, pt11.y, 12, 13, ZOOM, ZOOM, 1);
					// 修改绘图区大小
					initial_drawing1(0);
					Resize(NULL, WIDTH, HEIGHT);
					color_data1->rec = true;
					triangle_state++;
					Sleep(100);
				}
			}

			// 输出颜色值的颜色框，鼠标点击模式关。
			putcolortextboxparm(pt11.x, pt11.y, color_data1, 33, 1, IMAGE_STATE);

			// 鼠标点击标题栏范围。
			if ((pt11.x > 0 && pt11.y > 0 && pt11.x < 140 && pt11.y < 30))
			{
				// 鼠标左键点击。
				while ((GetAsyncKeyState(VK_LBUTTON)))
				{
					// 防闪标题栏。
					inigra(1);
					// 声明定义全局鼠标。
					POINT pt2;
					GetCursorPos(&pt2);
					// 全局移动程序。
					MoveWindow(h1, pt2.x - pt11.x, pt2.y - pt11.y, 245, 340, true);
				}
			}
		}
		// 显示双缓冲内容。
		FlushBatchDraw();
	}
	// 结束双缓冲。
	EndBatchDraw();
	// 关闭绘图库。
	closegraph();
	// 返回。
	return 0;
}
