#include <QPointer>
#include <QString>
#include "chess_board.h"

#include <iostream>
#include <string>

QSize field_size(60,60);

ChessBoard::ChessBoard(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
	QPointer<Field> field;
	board = new Board();
	layout = new QGridLayout;
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

	setLayout(layout);
}

void ChessBoard::start_game()
{
	board->set_pieces();
	display();
}

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

void ChessBoard::field_clicked() 
{	
	static int from = -1;
	QPointer<Field> f = qobject_cast<Field*>(sender());
	if((from == -1) && (board->get_field(f->get_coord()) != EMPTY)) {
		from = f->get_coord();
	} else if(from != -1) {
		move_piece(from, f->get_coord());
		from = -1;
	}
}

bool ChessBoard::move_piece(int from, int to)
{	
	int move = board->make_move(from, to);
	display();

	switch(move) {
		case REGULARMOVE:
			return true;	
		case CHECK:
			return true;
		case MATE:
			return true;
		case DRAW:
			return true;
		case ILLEGALMOVE:
			break;
		default:
			break;
	}
	return false;
}
	
/*int ChessBoard::undo_move()
{
	//board->undo_move();
	display();
	return 0;
}*/

ChessBoard::~ChessBoard()
{
//	delete board;
//	for(int i = ROWS*COLUMNS - 1; i >= 0; i--)
//		delete fields[i];
}




