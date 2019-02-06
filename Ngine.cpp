// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Ngine.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/01/26 22:34:24 by smonroe           #+#    #+#             //
//   Updated: 2019/02/01 17:21:55 by smonroe          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Ngine.hpp"

Ngine::Ngine( void )
  : _map_width(0), _map_height(0), _ents(NULL), _entCount(0), _entCapacity(512),
	_head(0), _tail(0), _wait((struct timespec){.tv_sec = 0, .tv_nsec = 40000000}),
	_player(new Player), _score(0)
{
	srand(time(NULL));
	initscr();
	raw();
	noecho();
	timeout(0);
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	cbreak();
	start_color();

	init_pair(0, COLOR_BLACK, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);
	init_pair(5, COLOR_CYAN, COLOR_CYAN);
	init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(7, COLOR_WHITE, COLOR_WHITE);
	init_pair(8, COLOR_WHITE, COLOR_BLACK);

	this->setScreenSize();
	clear();
	this->update();
}

Ngine::Ngine( Ngine const & cp)
{
	_map_width = cp.getMapWidth();
	_map_height = cp.getMapHeight();
	_ents = cp.getEnts();
	*this = cp;
}

Ngine::~Ngine( void )
{
	if (_head)
	{
		Bullet* tmp = _head;
		while (tmp)
		{
			_head = tmp->next;
			delete tmp;
			tmp = _head;
		}
	}
	if (_ents)
	{
		for (int i = 0; i < _entCount; i++)
			delete _ents[i];
		delete _ents;
	}
	if (_player)
		delete _player;
	endwin();
}

Ngine&	Ngine::operator=( Ngine const &) { return *this; }

int		Ngine::setColor( Color color, int bit )
{
	if (bit)
		return attron(COLOR_PAIR(color));
	return attroff(COLOR_PAIR(color));
}

void	Ngine::setScreenSize( void )
{
	getmaxyx(stdscr, _map_height, _map_width);
}

void	Ngine::update( void ) const
{
	refresh();
	nanosleep(&_wait, (struct timespec *){0});
	erase();
}

int		Ngine::getMapWidth( void ) const { return _map_width; }

int		Ngine::getMapHeight( void ) const { return _map_height; }

Enemy** Ngine::getEnts( void ) const { return _ents; }

void	Ngine::pushBullet( Bullet* bullet )
{
	if (!bullet) return;
	if (!_head && !_tail)
		_head = _tail = bullet;
	else
	{
		_tail->next = bullet;
		bullet->prev = _tail;
		_tail = bullet;
	}
}

void	Ngine::paintBullets( void )
{
	this->setColor(YELLOW, 1);
	Bullet* tmp = _head;
	while (tmp)
	{
		if (tmp->move())
		{
			Bullet* tmptmp = tmp->next;
			if (_head == tmp)
				_head = tmp->next;
			if (_tail == tmp)
				_tail = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			
			tmp->next = tmp->prev = NULL;
			delete tmp;
			tmp = tmptmp;
		}
		else
		{
			mvaddch(tmp->getY(), tmp->getX(), tmp->getShape());
			tmp = tmp->next;
		}
	}
	this->setColor(YELLOW, 0);
}

int		Ngine::pushGameEnt( Enemy* enmy )
{
	if (!enmy) return -1;
	if (!_ents)
		_ents = new Enemy*[_entCapacity];
	if (_entCount >= _entCapacity)
	{
		_entCapacity *= 2;
		Enemy** tmp = new Enemy*[_entCapacity];
		for (int i = 0; i < _entCount; i++)
			tmp[i] = _ents[i];
		delete _ents;
		_ents = tmp;
	}
	_ents[_entCount++] = enmy;
	return 0;
}

int		Ngine::paintGameEnts( void )
{
	int alive = 1;
	this->setColor(RED, 1);
	for (int i = 0; i < _entCount; i++)
	{
		int x = _ents[i]->getX();
		int y = _ents[i]->getY();
		if (_ents[i]->getAlive() == true && 
			((mvinch(y, x) & A_CHARTEXT) == PLAYER_CHAR
			|| (mvinch(y + 1, x) & A_CHARTEXT) == PLAYER_CHAR
			|| (mvinch(y - 1, x) & A_CHARTEXT) == PLAYER_CHAR
			|| (mvinch(y, x + 1) & A_CHARTEXT) == PLAYER_CHAR
			 || (mvinch(y, x - 1) & A_CHARTEXT) == PLAYER_CHAR))
		{
			_ents[i]->setAlive(false);
			_score += 5;
		}
		if (_ents[i]->getAlive() == true)
		{
			mvaddch(y, x, _ents[i]->getShape());
			alive = 0;
		}
	}
	this->setColor(RED, 0);
	return alive;
}

int		Ngine::paintPlayer( void )
{
	int x = _player->getX();
	int y = _player->getY();
	if ((mvinch(y, x) & A_CHARTEXT) == ENEMY_CHAR
		|| (mvinch(y + 1, x) & A_CHARTEXT) == ENEMY_CHAR
		|| (mvinch(y - 1, x) & A_CHARTEXT) == ENEMY_CHAR
		|| (mvinch(y, x + 1) & A_CHARTEXT) == ENEMY_CHAR
		|| (mvinch(y, x - 1) & A_CHARTEXT) == ENEMY_CHAR)
		return 1;
	this->setColor(GREEN, 1);
	mvaddch(y, x, _player->getShape());
	this->setColor(GREEN, 0);
	return 0;
}

void	Ngine::initEnts( int nbr ) {
	if (_ents)
	{
		for (int i = 0; i < _entCount; i++)
			delete _ents[i];
		delete _ents;
		_ents = NULL;
		_entCount = 0;
	}
	for (int i = 0; i < nbr; i++)
	{
		Enemy* tmp = new Enemy();
		tmp->setY(std::rand() % _map_height);
		tmp->setX(std::rand() % _map_width);
		this->pushGameEnt(tmp);
	}
}

void	Ngine::paintBackground( void )
{
	static struct background bc[STARS];
	static int flag;

	if (!flag)
	{
		for (int i = 0; i < STARS; i++)
		{
			bc[i].y = std::rand() % _map_height;
			bc[i].x = std::rand() % _map_width;
		}
		flag = 1;
	}

	for (int i = 0; i < STARS; i++)
	{
		mvaddch(++(bc[i].y), bc[i].x, '`');
		if (bc[i].y > _map_height)
			bc[i].y = 0;
	}

}

int		Ngine::gameLoop( void )
{
	_player->setLoc(_map_height / 2, 3);
	_player->setShape(PLAYER_CHAR);
	_player->setDir(GameEntity::RIGHT);
	int enemyCount = 2;
	this->initEnts(enemyCount);
	while (1)
	{
		this->paintBackground();
		mvprintw(0, 0, "Player Score: %d", _score);
		this->setScreenSize();
		if (_ents && _ents[0])
			_ents[0]->setYX(_map_height, _map_width);
		for (int i = 0; i < _entCount; i++)
			_ents[i]->tick();
		this->paintBullets();
		if (this->paintGameEnts())
		{
			_score += 100;
			enemyCount *= 2;
			this->initEnts(enemyCount);
		}
		switch (getch()) {
		case 'w' : _player->move(GameEntity::UP); break;
		case 'a' : _player->move(GameEntity::LEFT); break;
		case 's' : _player->move(GameEntity::DOWN); break;
		case 'd' : _player->move(GameEntity::RIGHT); break;
		case ' ' : pushBullet(_player->shoot()); break;
		case 'q' : return 1; break;
		}
		if (this->paintPlayer())
			return _score;
		this->update();
	}
	return 0;
}
