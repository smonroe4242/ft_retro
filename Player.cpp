#include "Player.hpp"

Player::Player() {}

Player::Player(Player const& cp) { *this = cp; }

Player::~Player() {}

Player&		Player::operator=(Player const& rhs) { (void)rhs; /*FIX THIS SHIT*/ return *this; }

void		Player::setAlive(bool b) {_alive = b;}

bool		Player::getAlive() {return _alive;}

Bullet*		Player::shoot()
{
	Bullet*		ret = new Bullet(_shape);
	ret->setDir(_dir);
	ret->setLoc(_y, _x);
	return ret;
}

void		Player::move(Dir d)
{
	_dir = d;
	switch (d)
	{
		case STILL : break;
		case UP : _y--; break;
		case DOWN : _y++; break;
		case LEFT : _x--; break;
		case RIGHT : _x++; break;
	}
	if (_x < 0)
		_x = 0;
	if (_y < 0)
		_y = 0;
	if (_x >= _map_width - 1)
		_x = _map_width - 1;
	if (_y > _map_height - 1)
		_y = _map_height - 1;

}
