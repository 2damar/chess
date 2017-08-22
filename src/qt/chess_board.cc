#include <QGridLayout>
#include "chess_board.h"

QSize field_size(60,60);

ChessBoard::ChessBoard(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
	Field *field;
	BoardController board_controller;
	QGridLayout *layout = new QGridLayout;
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
	
void ChessBoard::set_pieces()
{
	QPixmap piece_pic(field_size);
	std::string s;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++) {
			s = board_controller.get_field(i*8 + j);
			if(s != "0") {
				s = ":/png/" + s + ".png";
				piece_pic.load(s.c_str());
				fields[i*8 + j]->setPixmap(piece_pic);
			}
				
		}
}

void ChessBoard::field_clicked() 
{	
	static int from = -1;
	Field* f = qobject_cast<Field*>(sender());
	if((from == -1) && (board_controller.get_field(f->get_coord()) != EMPTY)) {
		from = f->get_coord();
	} else if(from != -1) {
		move_piece(from, f->get_coord());
		from = -1;
	}
}

bool ChessBoard::move_piece(int from, int to)
{	
	QPixmap piece_pic(field_size);
	std::string p;

	if(board_controller.make_move(from, to)) {
		fields[from]->clear();
		p = board_controller.get_field(to);
		p = ":/png/" + p + ".png";
		piece_pic.load(p.c_str());
		fields[to]->setPixmap(piece_pic);
		return true;
	}
	
	return false;
}
	







