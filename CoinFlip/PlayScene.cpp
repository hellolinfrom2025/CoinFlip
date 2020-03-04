#include <QMenuBar>
#include <qDebug>
#include <QPainter>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QSound>
#include "MyCoin.h"
#include "PlayScene.h"
#include "MyPushButton.h"
#include "dataconfig.h"

PlayScene::PlayScene(int nlevelIdx)
{
	//qDebug() << "select:" << levelIdx;
	m_nLevelIdx = nlevelIdx;
	setFixedSize(320, 588);
	setWindowIcon(QPixmap(":/Resources/Coin0001.png"));
	setWindowTitle("翻金币");

	//音效
	QSound	*pBackSound = new QSound(":/Resources/BackButtonSound.wav", this);
	QSound	*pFlipSound = new QSound(":/Resources/ConFlipSound.wav", this);
	QSound	*pWinSound = new QSound(":/Resources/LevelWinSound.wav", this);

	//创建菜单栏
	QMenuBar *pBar = menuBar();
	setMenuBar(pBar);
	QMenu *pStartMenu = pBar->addMenu("开始");
	QAction *pActionQuit = pStartMenu->addAction("退出");
	connect(pActionQuit, &QAction::triggered, [=]() {
		close();
	});

	//返回按钮
	MyPushButton *pBackBtn = new MyPushButton(":/Resources/BackButton.png"
		, ":/Resources/BackButtonSelected.png");
	pBackBtn->setParent(this);
	pBackBtn->move(width() - pBackBtn->width(), height() - pBackBtn->height());
	connect(pBackBtn, &MyPushButton::clicked, [=]() {
		pBackSound->play();
		QTimer::singleShot(500, [=]() {
			hide();
			emit sceneBack();
		});
	});

	//显示当前关卡名
	QLabel	*pLblTittle = new QLabel(this);
	QFont font ;
	font.setFamily("华文新魏");
	font.setPointSize(20);
	pLblTittle->setFont(font);
	QString str = QString("Level: %1").arg(m_nLevelIdx);
	pLblTittle->setText(str);
	pLblTittle->setGeometry(QRect(30,height()-50,160,50));

	//胜利图片
	QLabel *lblWin = new QLabel(this);
	QPixmap pixmap(":/Resources/LevelCompletedDialogBg.png");
	lblWin->setGeometry(0, 0, pixmap.width(), pixmap.height());
	lblWin->move(width()*0.5 - pixmap.width()*0.5, -pixmap.height());
	lblWin->setPixmap(pixmap);

	//创建金币背景图片
	for (int ii=0;ii<4;ii++)
	{
		for (int jj=0;jj<4;jj++)
		{
			//金币背景
			QLabel *pLbl = new QLabel(this);
			pLbl->setGeometry(0, 0, 50, 50);
			pLbl->move(57 + ii * 50, 200 + jj * 50);
			pLbl->setPixmap(QPixmap(":/Resources/BoardNode.png"));

			//初始化游戏数据
			dataConfig data;
			m_nGameArray[ii][jj] = data.mData[m_nLevelIdx][ii][jj];
			QString strImg;
			if (m_nGameArray[ii][jj]==1)
			{
				strImg = ":/Resources/Coin0001.png";
			}
			else
			{
				strImg = ":/Resources/Coin0008.png";
			}
			//金币对象
			MyCoin *pCoin = new MyCoin(strImg);
			pCoin->setParent(this);
			pCoin->move(59 + ii * 50, 204 + jj * 50);
			pCoin->m_nPoxX = ii;
			pCoin->m_nPoxY = jj;
			pCoin->m_bFlag = m_nGameArray[ii][jj];

			m_arrCoinBtn[ii][jj] = pCoin;
			//监听每个按钮的点击效果
			connect(pCoin, &MyCoin::clicked, [=]() {
				pCoin->changeFlag();
				m_nGameArray[ii][jj] = m_nGameArray[ii][jj] == 0 ? 1: 0;

				//延时翻动周围金币
				QTimer::singleShot(300, [=]() {
					if (pCoin->m_nPoxX + 1 <= 3)
					{
						m_arrCoinBtn[pCoin->m_nPoxX + 1][pCoin->m_nPoxY]->changeFlag();
						m_nGameArray[pCoin->m_nPoxX + 1][pCoin->m_nPoxY] =
							m_nGameArray[pCoin->m_nPoxX + 1][pCoin->m_nPoxY] == 0 ? 1 : 0;
					}
					if (pCoin->m_nPoxX - 1 >= 0)
					{
						m_arrCoinBtn[pCoin->m_nPoxX - 1][pCoin->m_nPoxY]->changeFlag();
						m_nGameArray[pCoin->m_nPoxX - 1][pCoin->m_nPoxY] =
							m_nGameArray[pCoin->m_nPoxX - 1][pCoin->m_nPoxY] == 0 ? 1 : 0;
					}
					if (pCoin->m_nPoxY + 1 <= 3)
					{
						m_arrCoinBtn[pCoin->m_nPoxX][pCoin->m_nPoxY + 1]->changeFlag();
						m_nGameArray[pCoin->m_nPoxX][pCoin->m_nPoxY + 1] =
							m_nGameArray[pCoin->m_nPoxX][pCoin->m_nPoxY + 1] == 0 ? 1 : 0;
					}
					if (pCoin->m_nPoxY - 1 >= 0)
					{
						m_arrCoinBtn[pCoin->m_nPoxX][pCoin->m_nPoxY - 1]->changeFlag();
						m_nGameArray[pCoin->m_nPoxX][pCoin->m_nPoxY - 1] =
							m_nGameArray[pCoin->m_nPoxX][pCoin->m_nPoxY - 1] == 0 ? 1 : 0;
					}

					//判断是否胜利
					m_bIsWin = true;
					for (int ii=0;ii<16;ii++)
					{
						if (!m_arrCoinBtn[ii/4][ii%4]->m_bFlag)
						{
							m_bIsWin = false;
							break;
						}
					}
					if (m_bIsWin)
					{
						//qDebug() << "胜利了";
						QPropertyAnimation*pAnimation = new QPropertyAnimation(lblWin, "geometry");
						pAnimation->setDuration(1000);
						pAnimation->setStartValue(QRect(lblWin->x(), lblWin->y(), lblWin->width(), lblWin->height()));
						pAnimation->setEndValue(QRect(lblWin->x(), lblWin->y()+114, lblWin->width(), lblWin->height()));
						pAnimation->setEasingCurve(QEasingCurve::OutBounce);
						pAnimation->start();

						//禁用金币按钮点击
						for (int ii=0;ii<16;ii++)
						{
							m_arrCoinBtn[ii / 4][ii % 4]->m_bIsWin = true;
						}

						pWinSound->play();
					}
				});

				pFlipSound->play();
			});
			
		}
	}

}

PlayScene::~PlayScene()
{
}

void PlayScene::paintEvent(QPaintEvent *event)
{
	//绘制背景图
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/Resources/PlayLevelSceneBg.png");
	painter.drawPixmap(0, 0, width(), height(), pix);
	//绘制左上角文字图片
	pix.load(":/Resources/Title.png");
	painter.drawPixmap((width() - pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
