#include "ChoseLevelScene.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QSound>
#include "MyPushButton.h"
#include "PlayScene.h"


ChoseLevelScene::ChoseLevelScene(QWidget *parent)
	: QMainWindow(parent)
{
	setFixedSize(320, 588);
	setWindowIcon(QPixmap(":/Resources/Coin0001.png"));
	setWindowTitle("选择关卡");

	//选择关卡按钮音效
	QSound	*choseSound = new QSound(":/Resources/TapButtonSound.wav", this);
	QSound	*backSound = new QSound(":/Resources/BackButtonSound.wav", this);

	//创建菜单栏
	QMenuBar *pBar = menuBar();
	setMenuBar(pBar);
	QMenu *startMenu = pBar->addMenu("开始");
	QAction *pActionQuit= startMenu->addAction("退出");
	connect(pActionQuit, &QAction::triggered, [=]() {
		close();
	});

	//创建返回按钮
	MyPushButton *pBackBtn = new MyPushButton(":/Resources/BackButton.png"
		, ":/Resources/BackButtonSelected.png");
	pBackBtn->setParent(this);
	pBackBtn->move(width() - pBackBtn->width(), height() - pBackBtn->height());
	connect(pBackBtn, &QPushButton::clicked, [=]() {
		backSound->play();
		QTimer::singleShot(500, [=]() {
			hide();
			emit ChoseLevelSceneBack();
		});
	});

	//创建关卡矩阵
	for (int ii=0;ii<20;ii++)
	{
		MyPushButton *menuBtn = new MyPushButton(":/Resources/LevelIcon.png");
		menuBtn->setParent(this);
		menuBtn->move(25+(ii % 4) * 70, 130+(ii / 4) * 70);
		//按钮上的文字
		QLabel *lbl = new QLabel(this);
		lbl->move(25 + (ii % 4) * 70, 130 + (ii / 4) * 70);
		lbl->setFixedSize(menuBtn->width(), menuBtn->height());
		lbl->setText(QString::number(ii + 1));
		lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		//鼠标事件穿透
		lbl->setAttribute(Qt::WA_TransparentForMouseEvents);

		//点击进入翻金币场景
		connect(menuBtn, &QPushButton::clicked, [=]() {
			if (m_pPlayScene==nullptr)
			{
				hide();
				m_pPlayScene = new PlayScene(ii + 1);
				m_pPlayScene->setGeometry(geometry());
				m_pPlayScene->show();
				//响应翻金币场景的返回按钮
				connect(m_pPlayScene, &PlayScene::sceneBack, [=]() {
					setGeometry(m_pPlayScene->geometry());
					show();
					delete m_pPlayScene;
					m_pPlayScene = nullptr;
				});

				choseSound->play();
			}
		});
	}
}

ChoseLevelScene::~ChoseLevelScene()
{
}

void ChoseLevelScene::paintEvent(QPaintEvent *event)
{
	//绘制背景图
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/Resources/OtherSceneBg.png");
	painter.drawPixmap(0, 0, width(), height(), pix);
	//绘制左上角文字图片
	pix.load(":/Resources/Title.png");
	painter.drawPixmap((width()-pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
