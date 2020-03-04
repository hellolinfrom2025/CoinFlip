#pragma once

#include <QObject>
#include <QPushButton>

class MyPushButton : public QPushButton
{
	Q_OBJECT

public:
	MyPushButton(QString strNormalImg, QString strPressImg="");
	~MyPushButton();
	void zoom1();
	void zoom2();

protected:
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
	QString m_strNormalImgPath;
	QString m_strPressImgPath;
};
