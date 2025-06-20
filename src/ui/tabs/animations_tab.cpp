#include "animations_tab.hpp"
#include "animations_model.hpp"
#include "ui_animations_tab.h"
#include "images.hpp"

#include <QTimer>

AnimationView::AnimationView(QWidget *parent): QGraphicsView(parent)
{
	QRect gameRect(-408, -312, 816, 624);
	scene = new QGraphicsScene(this);
	scene->setSceneRect(gameRect.x() - 20, gameRect.y() - 20, gameRect.width() + 40, gameRect.height() + 40);
	scale(0.75f, 0.75f);
	setScene(scene);
	setBackgroundBrush(QBrush(QColorConstants::DarkGray));
}

void AnimationView::prepare(Animation *anim)
{
	scene->clear();
	cells.clear();

	if (anim->frames.empty())
	{
		qDebug() << "Animation frames is empty";
		return;
	}

	if (!anim->animation1Name.isEmpty())
		stripes[0] = Images::Get()->animation(anim->animation1Name);

	if (!anim->animation2Name.isEmpty())
		stripes[1] = Images::Get()->animation(anim->animation2Name);

	for (auto &frameData: anim->frames)
	{
		//for (auto &cellData: frameData)
		for (size_t i = 0; i < frameData.size(); i++)
		{
			AnimationCell *cell = new AnimationCell();
			cell->setTransformOriginPoint(cell->boundingRect().center());
			cell->hide();
			scene->addItem(cell);
			cells.push_back(cell);
		}
	}

	QRect gameRect(-408, -312, 816, 624);
	QGraphicsRectItem *rectItem = new QGraphicsRectItem(gameRect);
	QPen pen(QColorConstants::White);
	pen.setCosmetic(true);
	rectItem->setPen(pen);
	scene->addItem(rectItem);

	currentAnim = anim;
	currentFrame = 0;
}

void AnimationView::doFrame(int frame)
{
	if (currentAnim->frames[frame].empty())
		return;

	setUpdatesEnabled(false);

	for (auto cell: cells)
		cell->hide();

	int index = 0;
	for (auto &frameData: currentAnim->frames[frame])
	{
		int pattern = int(frameData[0]);
		int stripIndex = 0;

		if (pattern >= 100)
		{
			pattern -= 100;
			stripIndex = 1;
		}

		int x = pattern % 5;
		int y = pattern / 5;

		cells[index]->updateCell(stripes[stripIndex], x, y);
		cells[index]->setPos(frameData[1], frameData[2]);
		cells[index]->setScale(frameData[3] * 0.01f);
		cells[index]->show();

		++index;
	}

	setUpdatesEnabled(true);
	viewport()->update();
}

AnimationsTab::AnimationsTab(QWidget *parent)
	: QWidget(parent), ui(new Ui::AnimationsTab)
{
	ui->setupUi(this);
	timer = new QTimer(this);
	animationView = new AnimationView(this);
	ui->framesBox->layout()->addWidget(animationView);

	connect(ui->tableView, &BaseTable::rowSelected, this, &AnimationsTab::rowSelected);
	connect(ui->playButton, &QPushButton::clicked, this, &AnimationsTab::playButtonClicked);
	connect(timer, &QTimer::timeout, this, &AnimationsTab::doFrame);
}

AnimationsTab::~AnimationsTab()
{
	delete ui;
}

void AnimationsTab::init()
{
	model = new AnimationsModel(ui->tableView);
	ui->tableView->setModel2(model);
}

void AnimationsTab::rowSelected(int row)
{
	currentAnim = Database::Get()->animation(row);
	if (!currentAnim)
		return;
}

void AnimationsTab::playButtonClicked()
{
	currentFrame = 0;
	animationView->prepare(currentAnim);
	timer->start(16.66666f * 4);
}

void AnimationsTab::doFrame()
{
	if (currentFrame == std::ssize(currentAnim->frames))
	{
		timer->stop();
		return;
	}

	animationView->doFrame(currentFrame);

	++currentFrame;
}


