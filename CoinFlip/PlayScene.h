#pragma once

#include <QMainWindow>
class MyCoin;

class PlayScene : public QMainWindow
{
	Q_OBJECT

public:
	PlayScene(int levelIdx);
	~PlayScene();
protected:
	virtual void paintEvent(QPaintEvent *event) override;
signals:
	void sceneBack();
private:
	int m_nLevelIdx;
	int m_nGameArray[4][4];
	MyCoin* m_arrCoinBtn[4][4];
	bool m_bIsWin;
};
