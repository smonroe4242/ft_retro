#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "GameEntity.hpp"
# include "Bullet.hpp"

class Enemy : public GameEntity {

public:

	Enemy( void );
	Enemy( Enemy const & cp );
	~Enemy( void );
	Enemy&	operator=( Enemy const & );
	void	setYX( int, int );
	bool	getAlive( void ) const;
	void	setAlive( bool );
	void	tick( void );

private:
	bool _alive;
};

#endif
