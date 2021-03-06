#include "gridsettingswidget.h"
#include "ui_gridsettingswidget.h"

#include <QtWidgets/QColorDialog>

GridSettingsWidget::GridSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GridSettingsWidget)
{
	ui->setupUi(this);

	// offset
	connect(ui->offsetInput, SIGNAL(xChanged(int)),
	        this, SLOT(offsetUpdate()));
	connect(ui->offsetInput, SIGNAL(yChanged(int)),
	        this, SLOT(offsetUpdate()));

	// grid
	connect(ui->gridSizeInput, SIGNAL(xChanged(int)),
	        this, SLOT(gridUpdate()));
	connect(ui->gridSizeInput, SIGNAL(yChanged(int)),
	        this, SLOT(gridUpdate()));

	// spacing
	connect(ui->spacingInput, SIGNAL(xChanged(int)),
	        this, SLOT(spacingUpdate()));
	connect(ui->spacingInput, SIGNAL(yChanged(int)),
	        this, SLOT(spacingUpdate()));

	// color
	connect(ui->colorChooseButton, SIGNAL(clicked()),
	        this, SLOT(chooseColor()));

	// scale
	connect(ui->scaleInput, SIGNAL(xChanged(double)),
	        this, SLOT(scaleUpdate()));
	connect(ui->scaleInput, SIGNAL(yChanged(double)),
	        this, SLOT(scaleUpdate()));
}

GridSettingsWidget::~GridSettingsWidget()
{
	delete ui;
}

void GridSettingsWidget::setOffset(const QPoint &pos)
{
	ui->offsetInput->setPos(pos);
}

void GridSettingsWidget::setGrid(const QSize &size)
{
	ui->gridSizeInput->setPos(size.width(), size.height());
}

void GridSettingsWidget::setSpacing(const QSize &spacing)
{
	ui->spacingInput->setPos(spacing.width(), spacing.height());
}

void GridSettingsWidget::setColor(const QColor &color)
{
	ui->colorBox->setAutoFillBackground(true);
	ui->colorBox->setPalette(QPalette(color));
}

void GridSettingsWidget::setScale(const QPointF &scale)
{
	ui->scaleInput->setPos(scale);
}

void GridSettingsWidget::offsetUpdate()
{
	emit offsetChanged( ui->offsetInput->pos() );
}

void GridSettingsWidget::gridUpdate()
{
	QPoint pos = ui->gridSizeInput->pos();
	emit gridChanged( QSize(pos.x(), pos.y()) );
}

void GridSettingsWidget::spacingUpdate()
{
	QPoint pos = ui->spacingInput->pos();
	emit spacingChanged( QSize(pos.x(), pos.y()) );
}

void GridSettingsWidget::scaleUpdate()
{
	emit scaleChanged( ui->scaleInput->pos() );
}

void GridSettingsWidget::chooseColor()
{
	const QColor color = QColorDialog::getColor(ui->colorBox->palette().color(QPalette::Window),
	                                            this, "Select Color", QColorDialog::ShowAlphaChannel);

	if (color.isValid())
	{
		setColor(color);
		emit colorChanged(color);
	}
}
