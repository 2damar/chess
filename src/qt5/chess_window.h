#ifndef CHESS_WINDOW
#define CHESS_WINDOW

#include <QWidget>
#include <QPointer>
#include <QPlainTextEdit>
#include <QLCDNumber>
#include "chess_board.h"

class ChessWindow : public QWidget {
	Q_OBJECT

public: 
	ChessWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);

private:
	ChessBoard* chess_board;
	QLCDNumber* white_clock;
	QLCDNumber* black_clock;
	QPlainTextEdit* moves;
};

#endif

