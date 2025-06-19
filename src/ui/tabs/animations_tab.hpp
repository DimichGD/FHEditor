#pragma once

#include <QWidget>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsView>

namespace Ui { class AnimationsTab; }
class AnimationsModel;
class DataMapper;
class QTimer;
class QGraphicsScene;
struct Animation;

class AnimationCell: public QGraphicsItem
{
public:
	explicit AnimationCell(): QGraphicsItem() {}

	void updateCell(QPixmap *pixmap, int x, int y)
	{
		this->pixmap = pixmap;
		this->x = x;
		this->y = y;
	}

	QRectF boundingRect() const override
	{
		return { -96.0f, -96.0f, 192.0f, 192.0f };
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override
	{
		painter->drawPixmap(boundingRect().toRect(), *pixmap, { x * 192, y * 192, 192, 192 });
		QPen pen(QColorConstants::White);
		pen.setCosmetic(true);
		painter->setPen(pen);
		//painter->drawRect(boundingRect());
	}

private:
	QPixmap *pixmap = nullptr;
	int x = 0;
	int y = 0;
};

class AnimationView: public QGraphicsView
{
	Q_OBJECT

public:
	explicit AnimationView(QWidget *parent = nullptr);

public slots:
	void prepare(Animation *anim);
	void doFrame(int frame);

protected:
	//void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
	QGraphicsScene *scene = nullptr;
	Animation *currentAnim = nullptr;
	int currentFrame = 0;
	std::vector<AnimationCell *> cells;
	QPixmap stripes[2];
};

class AnimationsTab: public QWidget
{
	Q_OBJECT

public:
	explicit AnimationsTab(QWidget *parent = nullptr);
	~AnimationsTab();

	void init();

private slots:
	void rowSelected(int row);
	void playButtonClicked();
	void doFrame();

private:
	Ui::AnimationsTab *ui = nullptr;
	AnimationsModel *model = nullptr;
	DataMapper *mapper = nullptr;
	Animation *currentAnim = nullptr;
	AnimationView *animationView = nullptr;
	QTimer *timer = nullptr;
	int currentFrame = 0;
};

