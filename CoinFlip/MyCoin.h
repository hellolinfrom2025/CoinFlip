#pragma once

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
	Q_OBJECT

public:
	MyCoin(QString strBtnImg);
	~MyCoin();
	void changeFlag();
protected:
	virtual void mousePressEvent(QMouseEvent *event) override;

public:
	int m_nPoxX;
	int m_nPoxY;
	//true:��ҡ�false:����
	bool m_bFlag;
	bool m_bIsWin=false;
private:
	QTimer *m_pTimer1;
	QTimer *m_pTimer2;
	int m_nMinIdx = 1;
	int m_nMaxIdx = 8;
	//���ڷ�ת�������
	bool m_bIsAnimation = false;

};
