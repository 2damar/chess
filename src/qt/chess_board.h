#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <QFrame>
#include <QWidget>
#include "../game_logic/types.h"

class QLabel;
extern char board[][8];

class ChessBoard : public QWidget {
	Q_OBJECT

	QVector<QLabel*> fields;

public:
	ChessBoard();
	void set_pieces();
};

#endif
