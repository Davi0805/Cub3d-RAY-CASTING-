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

uint8_t     setup_validation(int ac, char **av, t_cub *head)
{
    if (ac != 2)
        return (PARSE_ERROR);
    
    // File type
    if (filetype_checker(av[1])) parseFailed (head, FTYPE_ERROR);
    // File opens
    if (isFileValid(av[1])) parseFailed (head, FINVALID_ERROR);
    // Has contents
    if (isFileEmpty(av[1])) parseFailed (head, FEMPTY_ERROR);
    
    // Heap storing the file contents into a buffer
    if (allocate_file(av, head)) parseFailed (head, PARSE_ERROR);
    // TEXTURES Validation
    if (textureValidator(head)) parseFailed(head, MWRONG_TEXTURE);

    // Read file contents and allocate map
    if (allocateMap(head, head->fcontent, av[1])) parseFailed(head, MWRONG_TEXTURE);
    // MAP Validation
    if (verifyMap(head)) parseFailed (head, MWRONG_TEXTURE);
    
    return (PARSE_SUCCESS);
}

int main(int ac, char **av)
{
    t_cub head;

    // Init everything to 0's
    ft_bzero(&head, sizeof(head));
    // Valid file
    if (setup_validation(ac, av, &head))
        return (1);


    // Resource deallocation
    freeMap(&head);
    freeFile(&head);
    free_textures(&head);
    return (0);
}