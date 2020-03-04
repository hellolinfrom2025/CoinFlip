#include <QPainter>
#include <QTimer>
#include <QSound>
#include "MainScene.h"
#include "ChoseLevelScene.h"
#include "MyPushButton.h"

MainScene::MainScene(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(320, 588);
	setWindowIcon(QIcon(":/Resources/Coin0001.png"));
	setWindowTitle("翻金币");

	//菜单退出
	connect(ui.actionQuit, &QAction::triggered, [=]() {close(); });

	//选择关卡场景
	m_pChoseLevelScene = new ChoseLevelScene;

	//开始按钮音效
	QSound	*startSound = new QSound(":/Resources/TapButtonSound.wav", this);

	//创建开始游戏按钮
	m_pStartBtn = new MyPushButton(":/Resources/MenuSceneStartButton.png");
	m_pStartBtn->setParent(this);
	m_pStartBtn->move(width()*0.5 - m_pStartBtn->width()*0.5, height()*0.7);
	connect(m_pStartBtn, &MyPushButton::clicked, [=]() {
		startSound->play();
		m_pStartBtn->zoom1();
		m_pStartBtn->zoom2();
		QTimer::singleShot(500, [=]() {
			hide();
			m_pChoseLevelScene->setGeometry(geometry());
			m_pChoseLevelScene->show();
		});
	});

	//监听选择关卡场景的返回按钮
	connect(m_pChoseLevelScene, &ChoseLevelScene::ChoseLevelSceneBack, [=]() {
		setGeometry(m_pChoseLevelScene->geometry());
		show();
	});

	
}

void MainScene::paintEvent(QPaintEvent *event)
{
	//绘制背景图
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/Resources/PlayLevelSceneBg.png");
	painter.drawPixmap(0, 0, width(), height(), pix);
	//绘制左上角文字图片
	pix.load(":/Resources/Title.png");
	pix.scaled(pix.width()*0.5, pix.height()*0.5);
	painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
