#include <iostream>
#include <QtGui>

#include "chess_board.h"

static const QSize field_size(60,60);

ChessBoard::ChessBoard()
{
	QLabel* lbl;
	QPixmap field(field_size);
	std::string s;
	QGridLayout* layout = new QGridLayout;
	layout->setSpacing(0);
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++) {
			s = board[i][j];
			lbl = new QLabel();
			fields.push_back(lbl);
			lbl->setFixedSize(field_size);
			if(((i % 2 == 0) && (j % 2 == 0)) ||
				((i % 2 == 1) && (j % 2 == 1))) {
				lbl->setStyleSheet("QLabel { background-color : white; } ");
				field.fill(Qt::white);
			} else {
				lbl->setStyleSheet("QLabel { background-color : darkGray; } ");
				field.fill(Qt::darkGray);
			} 

			lbl->setPixmap(field);
			layout->addWidget(lbl, i, j);
		 
		}

	setLayout(layout);
}
	
void ChessBoard::set_pieces()
{
	QPixmap field(field_size);
	std::string s;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++) {
			s = board[i][j];
			if(s != "0") {
				s = ":/png/" + s + ".png";
				field.load(s.c_str());
				fields[i*8 + j]->setPixmap(field);
			}
				
		}
}
