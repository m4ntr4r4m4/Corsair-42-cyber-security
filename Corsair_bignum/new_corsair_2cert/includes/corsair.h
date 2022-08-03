/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:39:32 by ahammoud          #+#    #+#             */
/*   Updated: 2022/08/03 15:36:59 by ahammoud         ###   ########.fr       */
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
	BIGNUM*		m;
	BIGNUM*		q;
	BIGNUM*		p;
	BIGNUM*		pubexp;
	BIGNUM*		privexp;
	BIGNUM*		e1;
	BIGNUM*		e2;
	BIGNUM*		coeff;
	BIGNUM*		phi;
}	t_var;

typedef struct s_prim{
	BIGNUM*	p;
	BIGNUM*	q;
}	t_prime;


RSA		*read_publickey(char	*str);
int		write_privatekey(RSA *rsa, char *str);
void	gen_rsa_priv(t_var *var, char *str);
t_prime	 find_primes(const BIGNUM *num);

#endif
