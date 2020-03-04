#include <qDebug>
#include "MyCoin.h"

MyCoin::MyCoin(QString strBtnImg)
{
	QPixmap pixmap;
	bool bRet=pixmap.load(strBtnImg);
	if (!bRet)
	{
		qDebug() << "����ͼƬʧ��";
	}
	setFixedSize(pixmap.width(), pixmap.height());
	setStyleSheet("QPushButton{border:0px;}");
	setIcon(pixmap);
	setIconSize(QSize(pixmap.width(),pixmap.height()));

	//������ʱ��
	m_pTimer1 = new QTimer(this);
	m_pTimer2 = new QTimer(this);
	//��ҵ����ҹ���
	connect(m_pTimer1, &QTimer::timeout, [=]() {
		QPixmap pixmap;
		QString strImg = QString(":/Resources/Coin000%1.png").arg(m_nMinIdx++);
		pixmap.load(strImg);
		setFixedSize(pixmap.width(), pixmap.height());
		setStyleSheet("PushButton{border:0px;}");
		setIcon(pixmap);
		setIconSize(QSize(pixmap.width(), pixmap.height()));
		if (m_nMinIdx>m_nMaxIdx)
		{
			m_nMinIdx = 1;
			m_bIsAnimation = false;
			m_pTimer1->stop();
		}
	});
	//���ҵ���ҹ���
	connect(m_pTimer2, &QTimer::timeout, [=]() {
		QPixmap pixmap;
		QString strImg = QString(":/Resources/Coin000%1.png").arg(m_nMaxIdx--);
		pixmap.load(strImg);
		setFixedSize(pixmap.width(), pixmap.height());
		setStyleSheet("PushButton{border:0px;}");
		setIcon(pixmap);
		setIconSize(QSize(pixmap.width(), pixmap.height()));
		if (m_nMaxIdx < m_nMinIdx)
		{
			m_nMaxIdx = 8;
			m_bIsAnimation = false;
			m_pTimer2->stop();
		}
	});
}

MyCoin::~MyCoin()
{
}

void MyCoin::changeFlag()
{
	if (m_bFlag)
	{
		m_pTimer1->start(30);
		m_bIsAnimation = true;
		m_bFlag = false;
	}
	else
	{
		m_pTimer2->start(30);
		m_bIsAnimation = true;
		m_bFlag = true;
	}
}

void MyCoin::mousePressEvent(QMouseEvent *event)
{
	if (m_bIsAnimation||m_bIsWin)
	{
		return;
	}
	else
	{
		return QPushButton::mousePressEvent(event);
	}
}
