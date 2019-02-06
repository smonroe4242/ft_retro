#include "Enemy.hpp"

Enemy::Enemy() : _alive(true) { }

Enemy::Enemy(Enemy const& cp) : _alive(true) { *this = cp; }

Enemy::~Enemy() { _alive = false; }

Enemy&		Enemy::operator=(Enemy const& rhs) { _x = rhs.getX(); _y = rhs.getY();/*FIX THIS SHIT*/ return *this; }

void	Enemy::setYX( int y, int x ) { _map_height = y; _map_width = x; }

bool	Enemy::getAlive( void ) const { return _alive; }

void	Enemy::setAlive( bool alive ) { _alive = alive; }

void	Enemy::tick( void )
{
	this->move();
	this->checkPos();
}
