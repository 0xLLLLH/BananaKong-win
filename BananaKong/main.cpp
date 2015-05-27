/** *********************************
*                                   *
*			�������ļ�				*
*                                   *
********************************* **/
#include <windows.h>
LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , PSTR szCmdLine , int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWindows!");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style          = CS_HREDRAW | CS_VREDRAW;                  //����
	wndclass.lpfnWndProc    = WndProc ;                                 //���ڶ�Ӧ����Ϣ������
	wndclass.cbClsExtra     = 0;                                        //����ռ�
	wndclass.cbWndExtra     = 0;                                        //ͬ��
	wndclass.hInstance      = hInstance;                                //ʵ�����
	wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);          //����ͼ����ʽ
	wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);              //���������ʽ
	wndclass.hbrBackground  = (HBRUSH) GetStockObject(WHITE_BRUSH);     //���ñ���ɫ
	wndclass.lpszMenuName   = NULL;                                     //ָ��������Ĳ˵�
	wndclass.lpszClassName  = szAppName;                                //
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR | MB_OK);
		return 0;
	}
	hwnd = CreateWindow(szAppName ,                         //����������
		TEXT("The Hello Program"),          //���ڱ���
		WS_OVERLAPPEDWINDOW,                //���ڷ��,�򴰿ڸ�ʽ
		CW_USEDEFAULT,                      //��ʼ x ����
		CW_USEDEFAULT,                      //��ʼ y ����
		CW_USEDEFAULT,                      //��ʼ x ����ߴ�
		CW_USEDEFAULT,                      //��ʼ y ����ߴ�
		NULL,                               //�����ھ��
		NULL,                               //���ڲ˵����
		hInstance,                          //����ʵ�����
		NULL                                //��������
		);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch(message)
	{
	case WM_CREATE :
		//PlaySound(TEXT("hellowin.wav"),NULL,SND_FILENAME|SND_ASYNC);
		return 0;
	case WM_PAINT:          //������л�����������Ч����,������ѭ��
		hdc = BeginPaint(hwnd , &ps);
		//==========
		//�ڽ������Ĳ��ֽ��л���
		GetClientRect(hwnd , &rect);
		DrawText(hdc, TEXT("Hello Windows 8.1!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);        //������ͼ���ͷ��豸�������
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);         //���˳���Ϣ������Ϣ�����Խ���ѭ��
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}