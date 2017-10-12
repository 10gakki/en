#include "window.h"

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QObject> 
#include <QDebug>
#include <QFileDialog> 
#include <QPainter> 


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("Main Window"));

	openAction = new QAction(QIcon(":/images/file.png"), tr("&Open..."),
		this);
	//    openAction = new QAction(QIcon("E:/QTwork/qe/we/file.png"), tr("&Open..."),
	//this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an existing file"));

	saveAction = new QAction(QIcon(":/images/save"), tr("&Save"), this);
	saveAction->setShortcut(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save a new file"));
	connect(openAction, &QAction::triggered, this, &MainWindow::open);
	connect(saveAction, &QAction::triggered, this, &MainWindow::save);
	

	QMenu *file = menuBar()->addMenu(tr("&File"));
	file->addAction(openAction);
	file->addAction(saveAction);

	QToolBar *toolBar = addToolBar(tr("&File"));
	toolBar->addAction(openAction);
	toolBar->addAction(saveAction);

	textEdit = new QTextEdit(this);
	setCentralWidget(textEdit);
	connect(textEdit, &QTextEdit::textChanged, [=]() 
		{this->setWindowModified(true); });
	setWindowTitle("TextPad [*]");

#if 0

	QStatusBar *statusBar = new QStatusBar();
	statusBar->addAction(openAction);
#endif
}

MainWindow::~MainWindow()
{


}

void MainWindow::closeEvent(QCloseEvent * event)
{
	if (isWindowModified())
	{
		bool exit=QMessageBox::question(this,
			tr("Quit"),tr("Are you sure to quit this application?"),
			QMessageBox::Yes|QMessageBox::No,
			QMessageBox::No) == QMessageBox::Yes;
		if (exit)
		{
			event->accept();
		}
		else
		{
			event->ignore();
		}
	}
	else
	{
		event->accept();
	}
}


void MainWindow::open()
{
#if 0
	QMessageBox::information(this, tr("Information"), tr("Open file"));

#endif

#if 0
	//    QDialog dialog(this);
	QDialog *dialog = new QDialog();
	dialog->setWindowTitle(tr("hello,dialog!"));
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	dialog->setWindowTitle(tr("hello world,heha"));
	//    dialog.exec();
	//    dialog.show();
	dialog->open();
#endif

	QDialog dialog(this);
	dialog.setWindowTitle(tr("Hello, dialog!"));

#if 0
	if (QMessageBox::Yes == QMessageBox::question(this,
		tr("Question"),
		tr("Are you OK?"),
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::Yes)) {
		QMessageBox::information(this, tr("Hmmm..."), tr("I'm glad to hear that!"));
	}
	else {
		QMessageBox::information(this, tr("Hmmm..."), tr("I'm sorry!"));
	}
#endif

#if 0

	QMessageBox msgBox;
	msgBox.setText(tr("The document has been modified."));
	msgBox.setInformativeText(tr("Do you want to save your changes?"));
	msgBox.setDetailedText(tr("Differences here..."));
	msgBox.setStandardButtons(QMessageBox::Save
		| QMessageBox::Discard
		| QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();
	switch (ret) {
	case QMessageBox::Save:
		qDebug() << "Save document!";
		break;
	case QMessageBox::Discard:
		qDebug() << "Discard changes!";
		break;
	case QMessageBox::Cancel:
		qDebug() << "Close document!";
		break;
	}

	dialog.exec();
	qDebug() << dialog.result();

#endif

#if 1

	QString path = QFileDialog::getOpenFileName(this, tr("Open File"),
		".", tr("Text File(*.txt)"));
	if (!path.isEmpty())
	{
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
		{
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream in(&file);
		textEdit->setText(in.readAll());
		file.close();
	}
	else
	{
		QMessageBox::warning(this, tr("Path"), 
			tr("You did not select any file."));
	}

#endif

}

void MainWindow::save()
{
	QString path = QFileDialog::getSaveFileName(this,
		tr("Open File"),
		".",
		tr("Text Files(*.txt)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Write File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream out(&file);
		out << textEdit->toPlainText();
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}


window::window(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

window::~window()
{

}



void EventLabel::mouseMoveEvent(QMouseEvent * event)
{
	this->setText(QString("<center><h1>Move:(%1,%2)</h1></center>").arg
		(QString::number(event->x()), QString::number(event->y())));
}

void EventLabel::mousePressEvent(QMouseEvent * event)
{
	this->setText(QString("<center><h1>Press:(%1,%2)</h1></center>").arg
		(QString::number(event->x()), QString::number(event->y())));
}

void EventLabel::mouseReleaseEvent(QMouseEvent * event)
{
	QString msg;
	msg.sprintf("<centor><h1>Resease: (%d,%d)</h1></center>",
		event->x(), event->y());
	this->setText(msg);
}

void CustomButton::onButtonCliecked()
{
	qDebug() << "You clicked this!";
}

void CustomButton::mousePressEvent(QMouseEvent * e)
{
	if (e->button()==Qt::LeftButton)
	{
		qDebug() << "left";
	}
	else
	{
		QPushButton::mousePressEvent(e);
	}
}

CustomButton::CustomButton(QWidget *parent) :QPushButton(parent)
{
	connect(this, &CustomButton::clicked,
		this, &CustomButton::onButtonCliecked);
}

bool CustomWidget::event(QEvent * e)
{
	if (e->type()==QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(e);
		if (keyEvent->key()==Qt::Key_Tab)
		{
			qDebug() << "You press tab.";
			return true;
		}
	}
	return QWidget::event(e);
}

#if 1

bool CustomTextEdit::event(QEvent * e)
{
	if (e->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(e);
		if (keyEvent->key() == Qt::Key_Alt)
		{
			qDebug() << "You press Alt.";
			return true;
		}
	}
	return false;
}


#endif

myWindow::myWindow()
{
	textEdit = new QTextEdit;
	setCentralWidget(textEdit);
	textEdit->installEventFilter(this);
}

bool myWindow::eventFilter(QObject * watched, QEvent * event)
{
	if (watched==textEdit)
	{
		if (event->type()==QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			qDebug() << "Ate key press" << keyEvent->key();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return QMainWindow::eventFilter(watched, event);
	}
}

PaintedWidget::PaintedWidget(QWidget* parent /*= 0*/)
{
	resize(800, 600);
	setWindowTitle(tr("Paint Demo"));
}

void PaintedWidget::paintEvent(QPaintEvent*)
{
#if 0

	QPainter painter(this);
	painter.drawLine(80, 100, 650, 500);
	painter.setPen(Qt::red);
	painter.drawRect(10, 10, 100, 400);
	painter.setPen(QPen(Qt::green, 5));
	painter.setBrush(Qt::blue);
	painter.drawEllipse(50, 150, 400, 200);

#endif

#if 0

	QPainter painter(this);
	painter.setPen(QPen(Qt::black, 5, Qt::DashDotLine, Qt::RoundCap));
	painter.setBrush(Qt::yellow);
	painter.drawEllipse(50, 150, 200, 150);

	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(Qt::black, 5, Qt::DashDotLine, Qt::RoundCap));
	painter.setBrush(Qt::yellow);
	painter.drawEllipse(300, 150, 200, 150);

#endif

#if 0

	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing, true);
	QLinearGradient linearGradient(60, 50, 200, 200);
	linearGradient.setColorAt(0.2, Qt::white);
	linearGradient.setColorAt(0.6, Qt::green);
	linearGradient.setColorAt(1.0, Qt::black);
	painter.setBrush(QBrush(linearGradient));
	painter.drawEllipse(50, 50, 200, 150);

#endif

#if 0

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	const int r = 150;
	QConicalGradient conicalGradient(r, r, 0);

	conicalGradient.setColorAt(0.0, Qt::red);
	conicalGradient.setColorAt(60.0 / 360.0, Qt::yellow);
	conicalGradient.setColorAt(120.0 / 360.0, Qt::green);
	conicalGradient.setColorAt(180.0 / 360.0, Qt::cyan);
	conicalGradient.setColorAt(240.0 / 360.0, Qt::blue);
	conicalGradient.setColorAt(300.0 / 360.0, Qt::magenta);
	conicalGradient.setColorAt(1.0, Qt::red);

	QBrush brush(conicalGradient);
	painter.setPen(Qt::NoPen);
	painter.setBrush(brush);
	painter.drawEllipse(QPoint(r, r), r, r);

#endif

#if 1

	QPainter painter(this);
	painter.fillRect(10, 10, 50, 100, Qt::red);
	painter.save();
	painter.translate(100, 0); // 向右平移 100px 
	painter.fillRect(10, 10, 50, 100, Qt::yellow);
	painter.restore();
	painter.save();
	painter.translate(300, 0); // 向右平移 300px 
	painter.rotate(30); // 顺时针旋转 30 度 
	painter.fillRect(10, 10, 50, 100, Qt::green);
	painter.restore();
	painter.save();
	painter.translate(400, 0); // 向右平移 400px 
	painter.scale(2, 3); // 横坐标单位放大 2 倍，纵坐标放大 3 倍 
	painter.fillRect(10, 10, 50, 100, Qt::blue);
	painter.restore();
	painter.save();
	painter.translate(600, 0); // 向右平移 600px 
	painter.shear(0, 1); // 横向不变，纵向扭曲 1 倍 
	painter.fillRect(10, 10, 50, 100, Qt::cyan);
	painter.restore();

#endif
}
