#ifndef CHESS_CLOCK
#define CHESS_CLOCK

#include <QWidget>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class ChessClock : public QLCDNumber {
	Q_OBJECT

public:
	ChessClock(QWidget* parent = 0);
	void set_time(int m, int s);
	void start();
	void stop();
	
private slots:
	void show_time();

private:
	int min;
	int sec;
	QTimer* timer;
	QTime time;
};

#endif

