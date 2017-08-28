#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "chess_board.h"

class QAction;
class QMenu;

class MainWindow : public QMainWindow {

	Q_OBJECT

public:
	MainWindow();

protected:
	void closeEvent(QCloseEvent* event);

/*private slots:
	void start_new();
	void load();
	bool save();
	void undo();
	void about();

private:
	
	void create_actions();
	void create_menus();
	void start_new_game();
	void load_game(const QString& file_name);
	bool save_game(const QString& file_name);
*/
	ChessBoard* chess_board;
/*	QMenu* file_menu;
	QMenu* edit_menu;
	QMenu* help_menu;

	QAction* new_act;
	QAction* load_act;
	QAction* save_act;
	QAction* undo_act;
	QAction* about_act; 
	*/
};

#endif
