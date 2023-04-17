#include "StdAfx.h"
#include "Wuziqi.h"

HBRUSH Wuziqi::m_whiteBrush = CreateSolidBrush(RGB(255,255,255));
HBRUSH Wuziqi::m_blackBrush = CreateSolidBrush(RGB(0,0,0));
Wuziqi::Wuziqi(void)
{
	init();
}


Wuziqi::~Wuziqi(void)
{
}


void Wuziqi::init(void)
{
	for (int row = 0;row<LENTH;row++)
	{
	    leftTop = WIDTH + WIDTH/2;
		for (int col = 0;col<LENTH;col++)
		{
			m_qizi[row][col]=EMPTY;
		}
	}
	m_currentQizi = BLACK;
	InvalidateRect(m_hWnd,NULL,TRUE);
}


void Wuziqi::Draw(HDC hdc)
{
	DrawQipan(hdc);
	DrawQizi(hdc);
}


void Wuziqi::DrawQipan(HDC hdc)
{
	//������
	for (int row = 1;row<=LENTH + 2;row++)
	{
		MoveToEx(hdc,WIDTH,row * WIDTH,NULL);
		LineTo(hdc,(LENTH + 2) * WIDTH,row * WIDTH);
	}
	//������
	for (int col = 1 ; col<= LENTH+2;col++)
	{
		MoveToEx(hdc,col * WIDTH,WIDTH,NULL);
		LineTo(hdc,col* WIDTH,(LENTH + 2)*WIDTH);
	}
}


void Wuziqi::DrawQizi(HDC hdc)
{
	int rightBottom = 2 * WIDTH + WIDTH/2;
	HBRUSH oldBrush;
	for (int row = 0;row<LENTH;row++)
	{
		for (int col = 0;col<LENTH;col++)
		{
			switch(m_qizi[row][col])
			{
			case WHITE:
				{
					oldBrush=(HBRUSH)SelectObject(hdc,m_whiteBrush);
					break;
				}
			case BLACK:
				{
					oldBrush=(HBRUSH)SelectObject(hdc,m_blackBrush);
					break;
				}
			}
			if(m_qizi[row][col]!=EMPTY)
			{
				Ellipse(hdc,leftTop + col  * WIDTH,
					leftTop + row * WIDTH,
					rightBottom + col * WIDTH,
					rightBottom + row * WIDTH);
				SelectObject(hdc,oldBrush);
			}
		}
	}
}


RESULT_STEP Wuziqi::OneStep(int x, int y)
{
	RESULT_STEP resultStep = NEXT_STEP;
		/*�õ��������λ�������������е��±�*/
	int row = GetRowOrCol(y);
	int col = GetRowOrCol(x);

	if (!CanLuozi(row,col))
	{
		return CANNOT;
	}
	m_qizi[row][col]=m_currentQizi;
	DrawOneQizi(row,col);
	if (ifWin(row,col))
	{
		{
			if (BLACK == m_currentQizi)
			{
				MessageBox(m_hWnd,"����ʤ","Ӯ��",MB_OK);
			}else{
                MessageBox(m_hWnd,"����ʤ","Ӯ��",MB_OK);
			}
		}
		return WIN;
	}
	m_currentQizi = (m_currentQizi == BLACK?WHITE:BLACK);
	return resultStep;
}


bool Wuziqi::CanLuozi(int row, int col)
{
	if (row<0||col<0||row>=LENTH||col>=LENTH||m_qizi[row][col]!=EMPTY)
	{
	    return false;
	}
	return true;
}


int Wuziqi::GetRowOrCol(int position)
{
	
	position = (position - leftTop);
	return ((position%WIDTH)>(WIDTH/2))?(position/(WIDTH+1)):(position/(WIDTH+1));
}


void Wuziqi::DrawOneQizi(int row, int col)
{
	HDC hdc;
	hdc = GetDC(m_hWnd);
	HBRUSH hOldBrush;
	if(m_qizi[row][col]==BLACK)
	{
		hOldBrush = (HBRUSH)SelectObject(hdc,m_blackBrush);
	}
	else
	{
		hOldBrush = (HBRUSH)SelectObject(hdc,m_whiteBrush);
	}
	Ellipse(hdc,leftTop + col * WIDTH,
		leftTop + row * WIDTH,
		leftTop + (col+1) * WIDTH,
		leftTop + (row+1) * WIDTH);
	SelectObject(hdc,hOldBrush);
	ReleaseDC(m_hWnd,hdc);
}


bool Wuziqi::ifWin(int row, int col)
{
	int m_iMax = 1;
	//ͳ�Ƶ�ǰ���Ӻ�������������
	int i;
	for(int i=0;i<5&&m_qizi[row][col+i+1]==m_currentQizi;i++)
	{
		m_iMax++;
	}

	for(int i=0;i<5&&m_qizi[row][col-i-1]==m_currentQizi;i++)
	{
		m_iMax++;
	}
	if (m_iMax>=5)
	{
		return true;
	}
	//ͳ�Ƶ�ǰ������������������
	m_iMax = 1;
	for(int i=0;i<5&&m_qizi[row+i+1][col]==m_currentQizi;i++)
	{
		m_iMax++;
	}
	for(int i=0;i<5&&m_qizi[row-i-1][col]==m_currentQizi;i++)
	{
		m_iMax++;
	}
	if (m_iMax>=5)
	{
		return true;
	}
   //ͳ�Ƶ�ǰ���ӵ�һ���޵�������б45�ȵ����������
	m_iMax = 1;
	for(int i=0;i<5&&m_qizi[row+i+1][col+i+1]==m_currentQizi;i++)
	{
		m_iMax++;
	}
	for(int i=0;i<5&&m_qizi[row-i-1][col-i-1]==m_currentQizi;i++)
	{
		m_iMax++;
	}
	if (m_iMax>=5)
	{
		return true;
	}
	 //ͳ�Ƶ�ǰ���ӵڶ����޵�������б45�ȵ����������
	m_iMax = 1;
	for(int i=0;i<5&&m_qizi[row-i-1][col+i+1]==m_currentQizi;i++)
	{
		m_iMax++;
	}
	for(int i=0;i<5&&m_qizi[row+i+1][col-i-1]==m_currentQizi;i++)
	{
		m_iMax++;
	}
	if (m_iMax>=5)
	{
		return true;
	}
	return false;
}
