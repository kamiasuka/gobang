#pragma once
#define LENTH 15
#define WIDTH 40
enum Qizi{
	EMPTY,
	WHITE,
	BLACK
};
enum RESULT_STEP//���Ӻ�ķ���״̬
{
	NEXT_STEP,//���Խ�����
	CANNOT,//�������ӣ��ظ����ӣ�
	WIN//Ӯ��
};
class Wuziqi
{
public:
	Wuziqi(void);
	~Wuziqi(void);
	void init(void);
	void Draw(HDC hdc);


private:
	void DrawQipan(HDC hdc);
	void DrawQizi(HDC hdc);
public:
	HWND m_hWnd;
private:
	Qizi m_qizi[LENTH][LENTH];
	Qizi m_currentQizi;
	static HBRUSH m_whiteBrush;
	static HBRUSH m_blackBrush;
	int leftTop;
public:
	RESULT_STEP OneStep(int x, int y);
	bool CanLuozi(int row, int col);
private:
	int GetRowOrCol(int position);
public:
	void DrawOneQizi(int row, int col);
	bool ifWin(int row, int col);
};

