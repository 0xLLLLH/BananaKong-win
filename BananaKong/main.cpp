/** *********************************
*                                   *
*			�������ļ�				*
*                                   *
********************************* **/

#include <windows.h>
#include "container.h"

//ȫ�ֱ���
Container box;

//���ڳ�ʼ����Դ������
void InitResource(HWND hwnd);

//���ڶ�Ӧ����Ϣ��Ӧ����
LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , PSTR szCmdLine , int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Banana Kong");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style          = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS;                  //����
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
	InitResource(hwnd);
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
	if (box.DispatchMSG(hwnd,message,wParam,lParam))
	{
		//����Ϣ��ͼ����Ӧ

	}
	else
	{
		//�������Ĭ�ϵĴ��ڴ�����
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

void InitResource(HWND hwnd)
{
	//TODO:��ʼ����Դ������
	box.SetHandle(hwnd);
}