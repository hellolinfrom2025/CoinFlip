#include <qDebug>
#include <QPropertyAnimation>
#include "MyPushButton.h"

MyPushButton::MyPushButton(QString strNormalImg, QString strPressImg /*= ""*/)
{
	m_strNormalImgPath = strNormalImg;
	m_strPressImgPath = strPressImg;
	QPixmap pixmap;
	bool ret=pixmap.load(m_strNormalImgPath);
	if (!ret)
	{
		qDebug() << strNormalImg << "����ͼƬʧ��";
	}
	setFixedSize(pixmap.width(), pixmap.height());
	//���ò�������ʽ��
	setStyleSheet("QPushButton{border:0px;}");
	setIcon(pixmap);
	setIconSize(QSize(pixmap.width(), pixmap.height()));
}

MyPushButton::~MyPushButton()
{
}

void MyPushButton::zoom1()
{
	QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "geometry");
	pAnimation->setDuration(200);
	pAnimation->setStartValue(QRect(x(), y(), width(), height()));
	pAnimation->setEndValue(QRect(x(),y()+10,width(),height()));
	//���û������ߣ�QEasingCurve::OutBounce����Ч��
	pAnimation->setEasingCurve(QEasingCurve::OutBounce);
	pAnimation->start();
}

void MyPushButton::zoom2()
{
	QPropertyAnimation *pAnimation = new QPropertyAnimation(this, "geometry");
	pAnimation->setDuration(200);
	pAnimation->setStartValue(QRect(x(), y() + 10, width(), height()));
	pAnimation->setEndValue(QRect(x(), y(), width(), height()));
	pAnimation->setEasingCurve(QEasingCurve::OutBounce);
	pAnimation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *event)
{
	if (m_strPressImgPath!="")
	{
		QPixmap pixmap;
		bool ret=pixmap.load(m_strPressImgPath);
		if (!ret)
		{
			qDebug() << m_strPressImgPath << "����ͼƬʧ�ܣ�";
		}
		setFixedSize(pixmap.width(), pixmap.height());
		setStyleSheet("QPushButton{border:0px;}");
		setIcon(pixmap);
		setIconSize(QSize(pixmap.width(), pixmap.height()));
	}
	return QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_strNormalImgPath != "")
	{
		QPixmap pixmap;
		bool ret = pixmap.load(m_strNormalImgPath);
		if (!ret)
		{
			qDebug() << m_strNormalImgPath << "����ͼƬʧ�ܣ�";
		}
		setFixedSize(pixmap.width(), pixmap.height());
		setStyleSheet("QPushButton{border:0px;}");
		setIcon(pixmap);
		setIconSize(QSize(pixmap.width(), pixmap.height()));
	}
	return QPushButton::mouseReleaseEvent(event);
}
