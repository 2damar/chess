#include "chess_clock.h"
#include <QString>

ChessClock::ChessClock(QWidget* parent) : QLCDNumber(parent)
{
	min = 20;
	sec = 0;
	setMinimumHeight(60);
	setSegmentStyle(QLCDNumber::Filled);
	timer = new QTimer(this);
//	time = new QTime();
	connect(timer, SIGNAL(timeout()), this, SLOT(show_time()));
//	timer->start(1000);
	time.setHMS(0, min, sec);
	show_time();
}

void ChessClock::set_time(int m, int s)
{
	timer->stop();
	min = m;
	sec = s;
	time.setHMS(0, min, sec);
	show_time();
}
	
void ChessClock::start()
{
	timer->start(1000);
	show_time();
}

void ChessClock::stop()
{
	timer->stop();
}

void ChessClock::show_time()
{
	QString text = time.toString("mm:ss");
	time = time.addSecs(-1);
	display(text);
}
	


