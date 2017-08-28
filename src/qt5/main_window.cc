#include <QtWidgets>
#include "main_window.h"


MainWindow::MainWindow()
{
	//QSize max(480, 480);
	chess_board = new ChessBoard();
	//chess_board->setMaximumSize(max);
	chess_board->start_game();
	setCentralWidget(chess_board);
//	create_actions();
//	create_menus();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	// maybe save
//	event->accept();
}

/**
 * Starts completely new game
 */
/* void MainWindow::start_new() 
{
	// maybe save
	chess_board->start_game();
}*/

/**
 * Loads game from file
 */
/*void MainWindow::load() 
{
	// maybe save
	QString file_name = QFileDialog::getOpenFileName(this);
	if(!file_name.isEmpty())
		load_game(file_name);
}*/

/**
 * Save the current game to a file
 */
/*bool MainWindow::save()
{
	QString file_name = QFileDialog::getSaveFileName(this);
	if(file_name.isEmpty()) 
		return false;
	
	return save_game(file_name);
}

void MainWindow::undo()
{
	chess_board->undo_move();
}

void MainWindow::about() 
{
	QMessageBox::about(this, tr("About Chess"),
		tr("<b>Chess</b> game of chess"));
}

void MainWindow::create_actions()
{
	new_act = new QAction(tr("&New game"), this);
	new_act->setShortcuts(QKeySequence::New);
	connect(new_act, SIGNAL(triggered()), this, SLOT(start_new()));

	load_act = new QAction(tr("&Load game"), this);
	load_act->setShortcuts(QKeySequence::Open);
	connect(load_act, SIGNAL(triggered()), this, SLOT(load()));

	save_act = new QAction(tr("&Save game"), this);
	save_act->setShortcuts(QKeySequence::Save);
	connect(save_act, SIGNAL(triggered()), this, SLOT(save()));

	undo_act = new QAction(tr("&Undo"), this);
	undo_act->setShortcuts(QKeySequence::Undo);
	connect(undo_act, SIGNAL(triggered()), this, SLOT(undo()));

	about_act = new QAction(tr("&About"), this);
	connect(about_act, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::create_menus()
{
	file_menu = menuBar()->addMenu(tr("&File"));
	file_menu->addAction(new_act);
	file_menu->addAction(load_act);
	file_menu->addAction(save_act);
	
	edit_menu = menuBar()->addMenu(tr("&Edit"));
	edit_menu->addAction(undo_act);
	
	menuBar()->addSeparator();

	help_menu = menuBar()->addMenu(tr("&Help"));
	help_menu->addAction(about_act);
}

void MainWindow::load_game(const QString& file_name)
{
	QFile file(file_name);
	if(!file.open(QFile::ReadOnly | QFile::Text))
		return;
	
	// etc.
}

bool MainWindow::save_game(const QString& file_name)
{
	// etc.
	return false;
}*/
