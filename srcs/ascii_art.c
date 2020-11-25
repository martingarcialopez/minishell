/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_art.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarcia- <mgarcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:58:51 by mgarcia-          #+#    #+#             */
/*   Updated: 2020/11/25 19:12:53 by mgarcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tree.h"

void		display_ascii_art(void)
{
	ft_printf(
	"***************************************************************\n");
	ft_printf(
	"*                                                             *\n");
	ft_printf(
	"*                                             _ _       \\ \\   *\n");
	ft_printf(
"*      --    MINISHELL v%d.%d  --    .-\"\"\"\"\"-. / \\_> /\\    |/   *\n",
						MAJOR_VERSION, MINOR_VERSION);
	ft_printf(
	"*                                 /         \\.'`  `',.--//    *\n");
	ft_printf(
	"*                               -(           I      I  @@\\    *\n");
	ft_printf(
	"*   The only bug in our code ->   \\         /'.____.'\\___|    *\n");
	ft_printf(
	"*                                  '-.....-' __/ | \\   (`)    *\n");
	ft_printf(
	"*                                           /   /  /          *\n");
	ft_printf(
	"*      by mgarcia- & daprovin                    \\  \\         *\n");
	ft_printf(
	"*                                                             *\n");
	ft_printf(
	"***************************************************************\n");
}
