// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/01/26 23:49:31 by smonroe           #+#    #+#             //
//   Updated: 2019/01/27 22:53:17 by smonroe          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Ngine.hpp"

int main(void)
{
	Ngine* ng = new Ngine();
	int ret = 0;
	if ((ret = ng->gameLoop()))
	{
		mvprintw(ng->getMapHeight() / 2, (ng->getMapWidth() / 2) - 5, "You lose.");
		mvprintw((ng->getMapHeight() / 2) + 1, (ng->getMapWidth() / 2) - 5, "Score : %d", (ret == 1) ? 0 : ret);
	}
	else
		mvprintw(ng->getMapHeight() / 2, (ng->getMapWidth() / 2) - 4, "You Win!");
	mvprintw(0, 0, "(Press 'q' to leave)");
	while (getch() != 'q');
	delete ng;
	return 0;
}
