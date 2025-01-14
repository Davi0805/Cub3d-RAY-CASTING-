/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:08:46 by davi              #+#    #+#             */
/*   Updated: 2025/01/10 14:38:19 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"
#include <X11/keysym.h>
#include <X11/X.h>

uint8_t     allocate_map()
{

}

uint8_t     setup_validation(int ac, char **av, t_cub *head)
{
    if (ac != 2)
        return (PARSE_ERROR);
    
    if (isFileValid(av[1])) return (FINVALID_ERROR); //! check
    if (filetype_checker(av[1])) return (FTYPE_ERROR); //! check
    if (isFileEmpty(av[1])) return (FEMPTY_ERROR); //! check
        
    
    // todo ARTUR HERE
    if (allocate_file(av, head)) return (PARSE_ERROR); //! check
    
    if (textureValidator(head)) parseFailed(head, MWRONG_TEXTURE); //!check

    
    // MAP FETCH
    // Read file contents and allocate map
    
    // MAP Validation
    // Is there a map?
    /*
        - Só contem 0/1 , N/S/W/E x1
    */

    // 
    if (isCharInMap(head, '1')) parseFailed(head, MWRONG_FORMAT);
    if (isTherePlayer(head)) parseFailed(head, MNO_PLAYER);
        
    
    getPlayerPos(head);
    
    // TODO FLOOD FILL
    return (0);
}




int main(int ac, char **av)
{
    t_cub head;
    int error;

    ft_bzero(&head, sizeof(head));

    // Valid file
    error = setup_validation(ac, av, &head);
    
    if (error) 
        return (error);

    return (0);
}