#ifndef BUTTON_H

#define BUTTON_H

#define BUTTON_NORM			0x0000
#define BUTTON_PRESSED		0x0001


class Button
{
public:
	Button(HBITMAP hbmp);
	Response();
	~Button();
private:
	HBITMAP m_hbmp;
	int m_status;
}

#endif