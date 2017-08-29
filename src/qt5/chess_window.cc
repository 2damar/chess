#include "chess_window.h"

ChessWindow::ChessWindow(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
	chess_board = new ChessBoard();
	white_clock = new ChessClock();
	white_clock->setStyleSheet("QLCDNumber { color : black; background-color : white }");
	black_clock = new ChessClock();
	black_clock->setStyleSheet("QLCDNumber { color : white; background-color : black }");
	chess_board->set_clocks(white_clock, black_clock);
	moves = new QPlainTextEdit();
	moves->setReadOnly(true);
	chess_board->set_history(moves);
	game_status = new QLabel();
	game_status->setMinimumHeight(40);
	game_status->setAlignment(Qt::AlignCenter);
	game_status->setStyleSheet("QLabel { color : brown; background-color : darkGrey}");	
	chess_board->set_status(game_status);

	
	QHBoxLayout* main_layout = new QHBoxLayout();
	main_layout->addWidget(chess_board);

	QVBoxLayout* controls_layout = new QVBoxLayout();
	controls_layout->addWidget(white_clock);
	controls_layout->addWidget(black_clock);
	controls_layout->addWidget(game_status);
	controls_layout->addWidget(moves);
	main_layout->addLayout(controls_layout);

	chess_board->start_game();
	
	setLayout(main_layout);
}


