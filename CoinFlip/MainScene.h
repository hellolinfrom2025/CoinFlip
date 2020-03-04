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
	//选择关卡场景
	ChoseLevelScene *m_pChoseLevelScene;
	//开始按钮
	MyPushButton *m_pStartBtn;
};
