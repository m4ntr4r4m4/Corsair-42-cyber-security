/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:39:32 by ahammoud          #+#    #+#             */
/*   Updated: 2022/07/23 16:37:05 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORSAIR_H
# define CORSAIR_H

#include<errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "libft.h"

#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>

typedef	struct s_var{
	long	double	m;
	long	double	q;
	long	double	p;
	long	double	pubexp;
	long	double	privexp;
	long	double	e1;
	long	double	e2;
	long	double	coeff;
	long	double	phi;
}	t_var;

typedef struct s_prim{
	long	double	p;
	long	double	q;
}	t_prime;



char				*get_data(char *str);
char				*trim(char *buff);
char				*get_data(char *str);
long	double	get_modulus(char *str);
long	double	ft_fnprime(long	double	nb);
long	double	ft_primefactor(long	double nb);

#endif
