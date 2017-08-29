#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <QFrame>
#include <QWidget>
#include <QGridLayout>
#include <QPointer>
#include <QLCDNumber>
#include <QPlainTextEdit>
#include "../board/types.h"
#include "../board/board.h"
#include "field.h"

class ChessBoard : public QWidget {
	Q_OBJECT

public:
	ChessBoard(QWidget* parent = 0, Qt::WindowFlags f = 0);
	void set_clocks(QLCDNumber* wc, QLCDNumber* bc);
	void set_history(QPlainTextEdit* mh);
	void start_game();
//	int undo_move();
	void display();
	~ChessBoard();

private slots:
	void field_clicked();

private:
	
	QVector<QPointer<Field> > fields;
	Board* board;
	int active_player;
	int white_player;
	int black_player;
	QPointer<QLCDNumber> white_clock;
	QPointer<QLCDNumber> black_clock;
	QPointer<QPlainTextEdit> moves_history;
	bool move_piece(int from, int to);
	int click;
};

#endif
