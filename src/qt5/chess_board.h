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
#include "chess_clock.h"

class ChessBoard : public QWidget {
	Q_OBJECT

public:
	ChessBoard(QWidget* parent = 0, Qt::WindowFlags f = 0);
	void set_clocks(ChessClock* wc, ChessClock* bc);
	void set_history(QPlainTextEdit* mh);
	void set_status(QLabel* s);
	void start_game();
	void stop_game();
//	int undo_move();
	void display();
	~ChessBoard();

private slots:
	void field_clicked();

private:
	
	QVector<QPointer<Field> > fields;
	Board* board;
	int active_player;
	bool game_stopped;
	QPointer<ChessClock> white_clock;
	QPointer<ChessClock> black_clock;
	QPointer<QLabel> status_label;
	QPointer<QPlainTextEdit> moves_record;
	void update_status(int from, int to, char taken, int move);
	void switch_player();
	bool move_piece(int from, int to);
};

#endif
