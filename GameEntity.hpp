#ifndef GAMEENTITY_HPP
# define GAMEENTITY_HPP
# include <string>
# define PLAYER_CHAR '*'
# define ENEMY_CHAR '!'

class GameEntity {

public:

	enum Dir {
		STILL = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};

	GameEntity( void );
	GameEntity( int, int );
	GameEntity( Dir, int, int );
	GameEntity( GameEntity const & cp );
	~GameEntity( void );
	GameEntity& operator=( GameEntity const & );

	void		setType( std::string );
	void		setX(int x);
	void		setY(int y);
	void		setLoc(int y, int x);
	void		setDir(Dir dir);
	void		setShape( char );
	Dir			getDir() const;
	std::string getType( void ) const;
	int			getX( void ) const;
	int			getY( void ) const;
	char		getShape( void ) const;

	void		checkPos( void );
	void		move( void );

protected:
	static int _map_height;
	static int _map_width;
	Dir		_dir;
	char	_shape;
	std::string	_type;
	int		_x;
	int		_y;

};

#endif
