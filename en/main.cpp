#include "window.h"
#include <QtWidgets/QApplication>
#include <QCoreApplication> 
#include <QWidget> 
#include <QSpinBox> 
#include <QSlider> 
#include <QHBoxLayout> 
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
#if 0

	QWidget window;
	window.setWindowTitle("Enter your age");

	QSpinBox *spinBox = new QSpinBox(&window);
	QSlider *slider = new QSlider(Qt::Horizontal, &window);
	spinBox->setRange(0, 130);
	slider->setRange(0, 130);

	QObject::connect(slider, &QSlider::valueChanged, spinBox,
		&QSpinBox::setValue);
	void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
	QObject::connect(spinBox, spinBoxSignal, slider, &QSlider::setValue);
	spinBox->setValue(35);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(spinBox);
	layout->addWidget(slider);
	window.setLayout(layout);

	window.show();

#endif

#if 0

	MainWindow w;
	w.show();

#endif

#if 0

	Newspaper newspaper("Newspaper A");
	Reader reader;
	void (Newspaper:: *newPaperNameDate)(const QString &, const QDate &) =
		&Newspaper::newPaper;
	QObject::connect(&newspaper, newPaperNameDate,
		&reader, &Reader::receiveNewspaper);
	newspaper.send();

#endif

#if 0

	EventLabel* label = new EventLabel;
	label->setWindowTitle("MouseEvent Demo");
	label->resize(300, 200);
	//label->setMouseTracking(true);//ÉèÖÃÊó±ê×·×Ù
	label->show();

#endif

#if 0

	CustomButton btn;
	btn.setText("This is a Button!");
	btn.show();

#endif

#if 0
	CustomTextEdit* textEdit = new CustomTextEdit();
	textEdit->setWindowTitle("event ²âÊÔ");
	textEdit->resize(300, 200);
	textEdit->show();

#endif

#if 0

	Label label;
	a.installEventFilter(new EventFilter(&label, &label));
	label.show();

#endif

#if 1

	PaintedWidget* paint = new PaintedWidget;
	paint->show();

#endif


	return a.exec();
}
