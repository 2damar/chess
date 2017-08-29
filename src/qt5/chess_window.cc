#include "chess_window.h"

ChessWindow::ChessWindow(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
	chess_board = new ChessBoard();
	chess_board->start_game();
	QHBoxLayout* main_layout = new QHBoxLayout();
	main_layout->addWidget(chess_board);

	QVBoxLayout* controls_layout = new QVBoxLayout();
	white_clock = new QLCDNumber();
	black_clock = new QLCDNumber();
	moves = new QPlainTextEdit();
	controls_layout->addWidget(white_clock);
	controls_layout->addWidget(black_clock);
	controls_layout->addWidget(moves);
	main_layout->addLayout(controls_layout);
	setLayout(main_layout);
}


