#ifndef PLAYER_HPP
# define PLAYER_HPP
# include "GameEntity.hpp"
# include "Bullet.hpp"

class Player : public GameEntity {

public:

	Player( void );
	Player( Player const & cp );
	~Player( void );
	Player& operator=( Player const & );

	void	setAlive(bool);
	bool	getAlive();

	Bullet*	shoot();
	void	move(Dir d);

private:

	bool	_alive;

};

#endif
