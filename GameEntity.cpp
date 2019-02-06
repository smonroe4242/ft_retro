#include "GameEntity.hpp"

int GameEntity::_map_height = 0;
int GameEntity::_map_width = 0;

GameEntity::GameEntity() : _dir(STILL), _shape('!'), _type(""), _x(0), _y(0) {}
//GameEntity::GameEntity( int y, int x ) : _dir(STILL), _shape('^'), _type(0), _x(x), _y(y) {}
//GameEntity::GameEntity( Dir dir, int y, int x ) : _dir(dir), _shape('*'), _type(0), _x(x), _y(y) {}
GameEntity::GameEntity(GameEntity const& cp) { *this = cp; }

GameEntity::~GameEntity()
{
	_dir = STILL;
	_shape = 0;
	_type = "";
	_x = 0;
	_y = 0;
}

GameEntity&		GameEntity::operator=(GameEntity const& rhs)
{
	this->_x = rhs._x;
	this->_y = rhs._y;
	this->_type = rhs.getType();
	return *this;
}

void			GameEntity::setType( std::string type ) { _type = type; }
void			GameEntity::setX( int x ) { _x = x; }
void			GameEntity::setY( int y ) { _y = y; }
void			GameEntity::setLoc( int y, int x ) { _y = y; _x = x; }
void			GameEntity::setDir( Dir dir ) {_dir = dir;}
void			GameEntity::setShape( char shape ) { _shape = shape; }

std::string		GameEntity::getType( void ) const { return _type; }
int				GameEntity::getX( void ) const { return _x; }
int				GameEntity::getY( void ) const { return _y; }
char			GameEntity::getShape( void ) const { return _shape; }
GameEntity::Dir	GameEntity::getDir( void ) const { return _dir; }

void			GameEntity::checkPos( void )
{
	if (_x < 0)
		_x = 0;
	if (_y < 0)
		_y = 0;
	if (_x >= _map_width - 1)
		_x = _map_width - 1;
	if (_y > _map_height - 1)
		_y = _map_height - 1;
}

void		GameEntity::move( void )
{
	static int n;
	if (std::rand() % 10 == 0)
		_dir = (Dir[]){LEFT, RIGHT, UP, DOWN}[++n % 4];
	switch (_dir)
	{
		case STILL : break;
		case UP : _y--; break;
		case DOWN : _y++; break;
		case LEFT : _x--; break;
		case RIGHT : _x++; break;
	}
}
