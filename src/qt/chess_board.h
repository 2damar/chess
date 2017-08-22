#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <QFrame>
#include <QWidget>
#include "../game_logic/types.h"
#include "../game_logic/board_controller.h"
#include "field.h"

//extern char board[ROWS*COLUMNS];

class ChessBoard : public QWidget {
	Q_OBJECT


public:
	ChessBoard(QWidget* parent = 0, Qt::WindowFlags f = 0);
	void set_pieces();

private slots:
	void field_clicked();

private:
	QVector<Field*> fields;
	BoardController board_controller;
	bool move_piece(int from, int to);
	int click;
};

#endif
