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
	setWindowTitle("�����");

	//�˵��˳�
	connect(ui.actionQuit, &QAction::triggered, [=]() {close(); });

	//ѡ��ؿ�����
	m_pChoseLevelScene = new ChoseLevelScene;

	//��ʼ��ť��Ч
	QSound	*startSound = new QSound(":/Resources/TapButtonSound.wav", this);

	//������ʼ��Ϸ��ť
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

	//����ѡ��ؿ������ķ��ذ�ť
	connect(m_pChoseLevelScene, &ChoseLevelScene::ChoseLevelSceneBack, [=]() {
		setGeometry(m_pChoseLevelScene->geometry());
		show();
	});

	
}

void MainScene::paintEvent(QPaintEvent *event)
{
	//���Ʊ���ͼ
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/Resources/PlayLevelSceneBg.png");
	painter.drawPixmap(0, 0, width(), height(), pix);
	//�������Ͻ�����ͼƬ
	pix.load(":/Resources/Title.png");
	pix.scaled(pix.width()*0.5, pix.height()*0.5);
	painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
