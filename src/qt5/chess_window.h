#ifndef CHESS_WINDOW
#define CHESS_WINDOW

#include <QWidget>
#include <QPointer>
#include <QPlainTextEdit>

#include "chess_board.h"
#include "chess_clock.h"

class ChessWindow : public QWidget {
	Q_OBJECT

public: 
	ChessWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);

private:
	ChessBoard* chess_board;
	ChessClock* white_clock;
	ChessClock* black_clock;
	QLabel* game_status;
	QPlainTextEdit* moves;
};

#endif

