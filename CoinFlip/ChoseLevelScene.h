#pragma once

#include <QMainWindow>
class PlayScene;
class ChoseLevelScene : public QMainWindow
{
	Q_OBJECT

public:
	ChoseLevelScene(QWidget *parent = Q_NULLPTR);
	~ChoseLevelScene();
protected:
	virtual void paintEvent(QPaintEvent *event) override;
signals:
	void ChoseLevelSceneBack();
private:
	PlayScene *m_pPlayScene = nullptr;
};
