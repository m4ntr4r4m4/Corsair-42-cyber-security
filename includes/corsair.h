/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:39:32 by ahammoud          #+#    #+#             */
/*   Updated: 2022/07/22 23:11:01 by ahammoud         ###   ########.fr       */
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
	unsigned	long	m;
	unsigned	long	q;
	unsigned	long	p;
	unsigned	long	pubexp;
	unsigned	long	privexp;
	unsigned	long	e1;
	unsigned	long	e2;
	unsigned	long	coeff;
	unsigned	long	phi;
}	t_var;

typedef struct s_prim{
	unsigned	long	p;
	unsigned	long	q;
}	t_prime;



char				*get_data(char *str);
char				*trim(char *buff);
char				*get_data(char *str);
unsigned	long	get_modulus(char *str);
unsigned	long	ft_fnprime(unsigned	long	nb);
unsigned	long	ft_primefactor(unsigned	long nb);

#endif
