#ifndef BULLET_HPP
# define BULLET_HPP

# include "GameEntity.hpp"

class Bullet : public GameEntity {

public:

	Bullet( void );
	Bullet(char shape);
	Bullet( Bullet const & cp );
	~Bullet( void );
	Bullet& operator=( Bullet const & );

	Dir		getDir( void ) const;
	char	getShape( void ) const;

	void	setDir( Dir );
	void	setShape( char );
	Bullet*	next;
	Bullet* prev;
	int		move( void );

private:
	Dir		_dir;
	char	_shape;

};

#endif
