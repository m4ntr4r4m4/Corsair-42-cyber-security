/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:54:59 by ahammoud          #+#    #+#             */
/*   Updated: 2022/07/28 18:57:27 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "corsair.h"

void	gen_rsa_priv(t_var *var, t_prime *z, RSA *rsa)
{
	RSA *p;

	p = RSA_new();
	if(!p)
		return;
	printf("%p\n", p);
	if(!RSA_set0_key(p, var->m, var->pubexp, var->privexp))
		printf("\nerror keyGen\n");
	if(!RSA_set0_factors(p, z->p, z->q))
		printf("\nerror key factors\n");
	if(!RSA_set0_crt_params(p, var->e1, var->e2, var->coeff))
		printf("\nerror key crt params\n");


	
	char *s;
	printf("this  priv exp %s\n", s = BN_bn2dec(var->privexp));
	free(s);

	printf("this  pub exp %s\n", s = BN_bn2dec(var->pubexp));
	free(s);

	printf("this  modulus %s\n", s = BN_bn2dec(var->m));
	free(s);

	printf("this  e1 %s\n", s = BN_bn2dec(var->e1));
	free(s);

	printf("this  e2 %s\n", s = BN_bn2dec(var->e2));
	free(s);
	printf("this  coeff %s\n", s = BN_bn2dec(var->coeff));
	free(s);


	printf("%p\n", p);
	write_privatekey(p);
	RSA_free(p);
//	BN_free(z->p);
//	BN_free(z->q);
//	BN_free(var->e1);
//	BN_free(var->e2);
//	BN_free(var->coeff);
//	BN_free(var->privexp);
	
//	RSA_free(rsa);

}
