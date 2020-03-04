#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainScene.h"
class ChoseLevelScene;
class MyPushButton;

class MainScene : public QMainWindow
{
	Q_OBJECT

public:
	MainScene(QWidget *parent = Q_NULLPTR);
protected:
	virtual void paintEvent(QPaintEvent *event) override;
private:
	Ui::MainSceneClass ui;
	//ѡ��ؿ�����
	ChoseLevelScene *m_pChoseLevelScene;
	//��ʼ��ť
	MyPushButton *m_pStartBtn;
};
