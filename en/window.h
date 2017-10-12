#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QWidget>
#include <QObject> 
#include <QTextEdit>
#include <QDebug> 
#include <QLabel>
#include <QMouseEvent> 
#include <QPushButton>
#include "ui_window.h"

#if 1

class CustomTextEdit :public QTextEdit
{
public:

	bool event(QEvent* e);

private:

};

#endif



class window : public QWidget
{
	Q_OBJECT

public:
	window(QWidget *parent = 0);
	~window();

private:
	Ui::windowClass ui;
};

#include <QMainWindow>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void MainWindow::closeEvent(QCloseEvent *event);

private:
	void open();
	void save();

	QAction *openAction;
	QAction *saveAction;
	QTextEdit* textEdit;
};

class Newspaper : public QObject
{
	Q_OBJECT
public:
	Newspaper(const QString & name) :
		m_name(name)
	{
	}

	void send()
	{
		emit newPaper(m_name);
	}

signals:
	void newPaper(const QString &name);
	void newPaper(const QString &name, const QDate &date);

private:
	QString m_name;
};

class Reader : public QObject
{
	Q_OBJECT
public:
	Reader() {}

	void receiveNewspaper(const QString & name)
	{
		qDebug() << "Receives Newspaper: " << name;
	}
};

class EventLabel:public QLabel
{
protected:
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

};

class CustomButton : public QPushButton
{
	Q_OBJECT
public:
	CustomButton(QWidget *parent = 0);
private:
	void onButtonCliecked();
protected:
	void mousePressEvent(QMouseEvent *e);
};

class CustomWidget : public QWidget
{
	Q_OBJECT

public:
	CustomWidget(QWidget *parent = 0);
	~CustomWidget();
	bool event(QEvent* e);
};


class myWindow:public QMainWindow
{
public:
	myWindow();
protected:
	bool eventFilter(QObject *watched, QEvent *event);
private:	
	QTextEdit* textEdit;
};

class Label :public QWidget
{
public:
	Label()
	{
		installEventFilter(this);
	}
	bool eventFilter(QObject *watched, QEvent *event)
	{
		if (watched==this)
		{
			if (event->type()==QEvent::MouseButtonPress)
			{
				qDebug() << "eventFilter";
			}
		}
		return false;
	}
protected:
	void mousePressEvent(QMouseEvent *event)
	{
		qDebug() << "mousePressEvent";
	}
	bool event(QEvent* e)
	{
		if (e->type()==QEvent::MouseButtonPress)
		{
			qDebug() << "event";
		}
		return QWidget::event(e);
	}
};

class EventFilter:public QObject
{
public:
	EventFilter(QObject* watched, QObject* parent = 0) :
		QObject(parent),
		m_watched(watched)
	{

	}
	bool eventFilter(QObject *watched, QEvent *event)
	{
		if (watched== m_watched)
		{
			if (event->type()==QEvent::MouseButtonPress)
			{
				qDebug() << "QApplication::eventFilter";
			}
		}
		return false;
	}

private:
	QObject* m_watched;
};

class PaintedWidget:public QWidget
{
	Q_OBJECT
public:
	PaintedWidget(QWidget* parent = 0);
protected:
	void paintEvent(QPaintEvent*);
private:
};

#endif // WINDOW_H
