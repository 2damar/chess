#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <QFrame>
#include <QWidget>
#include "../game_logic/types.h"
#include "../game_logic/chess_controller.h"
#include "field.h"

extern char board[ROWS*COLUMNS];

class ChessBoard : public QWidget {
	Q_OBJECT


public:
	ChessBoard(QWidget* parent = 0, Qt::WindowFlags f = 0);
	void set_pieces();

private slots:
	void field_clicked();

private:
	QVector<Field*> fields;
	ChessController chess_controller;
	bool move_piece(int from, int to);
	int click;
};

#endif
