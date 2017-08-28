#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <QFrame>
#include <QWidget>
#include <QGridLayout>
#include <QPointer>
#include "../board/types.h"
#include "../board/board.h"
#include "field.h"

//extern char board[ROWS*COLUMNS];

class ChessBoard : public QWidget {
	Q_OBJECT


public:
	ChessBoard(QWidget* parent = 0, Qt::WindowFlags f = 0);
	void start_game();
//	int undo_move();
	void display();
	~ChessBoard();

private slots:
	void field_clicked();

private:
	QVector<QPointer<Field> > fields;
	Board* board;
	QGridLayout* layout;
	bool move_piece(int from, int to);
	int click;
};

#endif
