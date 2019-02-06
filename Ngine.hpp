// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Ngine.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/01/26 22:34:32 by smonroe           #+#    #+#             //
//   Updated: 2019/01/27 22:03:12 by smonroe          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef NGINE_H
# define NGINE_H
# include <string>
# include <stdexcept>
# include <ncurses.h>
# include <iostream>
# include "GameEntity.hpp"
# include "Enemy.hpp"
# include "Player.hpp"
# define STARS 42
class Ngine {

public:

	enum Color {
		BLACK = 0,
		RED = 1,
		YELLOW = 2,
		GREEN = 3,
		CYAN = 4,
		BLUE = 5,
		MAGENTA = 6,
		WHITE = 7,
		TEXT = 8
	};

	struct background {
		int x;
		int y;
	};

	Ngine( void );
	Ngine( Ngine const & cp );
	~Ngine( void );
	Ngine&	operator=( Ngine const & );
	int		setColor( Color, int );
	void	setScreenSize( void );
	void	update( void ) const;
	int		getMapWidth( void ) const;
	int		getMapHeight( void ) const;
	Enemy**	getEnts( void ) const;
	void	pushBullet( Bullet* );
	void	paintBullets( void );
	int		pushGameEnt( Enemy* );
	int		paintGameEnts( void );
	int		paintPlayer( void );
	void	initEnts( int );
	void	paintBackground( void );
	int		gameLoop( void );

private:	
	int _map_width;
	int _map_height;
	Enemy** _ents;
	int	_entCount;
	int	_entCapacity;
	Bullet*	_head;
	Bullet* _tail;
	struct timespec _wait;
	Player* _player;
	unsigned int _score;
};

#endif
