#include "Bullet.hpp"

Bullet::Bullet() : next(0), prev(0), _shape(PLAYER_CHAR) {}

Bullet::Bullet(char shape) : next(0), prev(0), _shape(shape) {}

Bullet::Bullet(Bullet const& cp) { *this  = cp; }

Bullet::~Bullet()
{
	next = NULL;
	prev = NULL;
}

Bullet&       Bullet::operator=(Bullet const& rhs) { _shape = rhs.getShape(); return *this; }

Bullet::Dir		Bullet::getDir( void ) const { return _dir; }

char	Bullet::getShape( void ) const { return _shape; }

void	Bullet::setDir( Dir dir ) { _dir = dir; }

void	Bullet::setShape( char shape ) { _shape = shape; }

int		Bullet::move( void )
{
	switch (_dir) {
		case STILL : break;
		case UP : _y--; break;
		case DOWN : _y++; break;
		case LEFT : _x--; break;
		case RIGHT : _x++; break;
	}
	if (_y < 0 || _x < 0 || _y >= _map_height || _x >= _map_width)
		return 1;
	return 0;
}
