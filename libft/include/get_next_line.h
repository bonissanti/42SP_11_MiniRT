/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:15:58 by brunrodr          #+#    #+#             */
/*   Updated: 2024/04/25 11:40:33 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

//####################  GNL ###################

char	*get_next_line(int fd);

//##################  UTILS  ##################

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(char *s);

#endif
