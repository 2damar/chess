#include <QPointer>
#include <QString>
#include "chess_board.h"

#include <iostream>
#include <string>

QSize field_size(60,60);

/**
 * Initializes empty board
 */
ChessBoard::ChessBoard(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
	QPointer<Field> field;
	board = new Board();
	QGridLayout* layout = new QGridLayout;
	layout->setSpacing(0);
	
	for(int i = 0; i < ROWS; i++)
		for(int j = 0; j < COLUMNS; j++) {
			field = new Field(8*i + j);
			connect(field, SIGNAL(clicked()), this, SLOT(field_clicked()));
			fields.push_back(field);
			field->setFixedSize(field_size);
			if(((i % 2 == 0) && (j % 2 == 0)) ||
				((i % 2 == 1) && (j % 2 == 1))) {
				field->setStyleSheet("QLabel { background-color : white; } ");
			} else {
				field->setStyleSheet("QLabel { background-color : darkGray; } ");
			} 

			layout->addWidget(field, i, j);
		 
		}
	game_stopped = false;
	setLayout(layout);
}


/**
 * Sets clocks for both players
 */
void ChessBoard::set_clocks(ChessClock* wc, ChessClock* bc)
{
	white_clock = wc;
	black_clock = bc;
}

/**
 * Sets textfield for writing the moves
 */
void ChessBoard::set_history(QPlainTextEdit* mh)
{
	moves_record = mh;
}

/**
 * Sets status label for current game status
 */
void ChessBoard::set_status(QLabel* s)
{
	status_label = s;
}

/**
 * Puts pieces on the board and starts the game
 */
void ChessBoard::start_game()
{
	board->set_pieces();
	prev_moves.push_back(board->get_board_features());
	active_player = WHITE;
	display();
}

/**
 * Displays the board, needs to be called after any change to the board.
 */
void ChessBoard::display()
{
	QPixmap piece_pic(field_size);
	QString s;
	for(int i = 0; i < ROWS*COLUMNS; i++) {
		s = board->get_field(i);
		fields[i]->clear();
		if(s != "0") {
			s = ":/png/" + s + ".png";
			piece_pic.load(s);
			fields[i]->setPixmap(piece_pic);
		}	
	}
}

/**
 * Evaluates the field that was clicked.
 * And potentially makes the move.
 */
void ChessBoard::field_clicked() 
{
	if(game_stopped)
		return;
	static int from = -1;
	QPointer<Field> f = qobject_cast<Field*>(sender());
	if((from == -1) && (board->get_field(f->get_coord()) != EMPTY)) {
		from = f->get_coord();
//		f->setStyleSheet("QLabel { background-color : green; }");
	} else if(from != -1) {
		move_piece(from, f->get_coord());
		from = -1;
	}
}

/**
 * Switches the active player after succesfull move
 */
void ChessBoard::switch_player()
{
	if(active_player == WHITE) {
		black_clock->start();
		white_clock->stop();
		active_player = BLACK; 
	} else {
		white_clock->start();
		black_clock->stop();
		active_player = WHITE;
	}
}

/**
 * Moves piece on the board, updates the status,
 * records the move and switches the player
 *
 * @param from current position
 * @param to destination
 * @return flag for game status
 */
bool ChessBoard::move_piece(int from, int to)
{
	int move = ILLEGALMOVE;
	char piece_taken = board->get_field(to);
	if(board->get_color(from) == active_player) 
		move = board->make_move(from, to);

	if(move == ILLEGALMOVE)
		return false;


	update_status(from, to, piece_taken, move);
	switch_player();

	// record move
	board_features_t bf = board->get_board_features();
	bf.ap = active_player;
	prev_moves.push_back(bf);

	display();
	
	if((move == MATE) || (move == DRAW))
		stop_game();

	return true;
}

void ChessBoard::update_status(int from, int to, char taken, int move)
{
	QString s;
	s = board->get_field(to);
	s = s + tr(" from ") + QString::number(from) + tr(" moves to ") + QString::number(to);
	if(taken != '0') 
		s = s + tr(" and takes ") + taken;
	moves_record->appendPlainText(s);
	if(move == MATE)
		s = tr("MATE");
	else if(move == CHECK)
		s = tr("CHECK");
	else if(move == DRAW)
		s = tr("DRAW");
	else
		s = (active_player == WHITE) ? tr("Black's turn") : tr("White's turn");
	
	status_label->setText(s);

}

int ChessBoard::undo_move()
{
	if(prev_moves.empty())
		return -1;
	prev_moves.pop_back();
	if(prev_moves.empty())
		return -1;
	
	board_features_t pb = prev_moves.back();
	board->set_pieces(pb.board, pb.cf, pb.ep);
	active_player = pb.ap;	
	//start the right clock
	switch_player();
	switch_player();

	display();
	return 1;
}

void ChessBoard::stop_game()
{
	white_clock->stop();
	black_clock->stop();
	game_stopped = true;
}
	
ChessBoard::~ChessBoard()
{
	delete board;
}




