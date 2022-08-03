/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:25:18 by ahammoud          #+#    #+#             */
/*   Updated: 2022/08/03 16:02:29 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

RSA		*read_publickey(char	*str)
{

	RSA *rsa = RSA_new();
    BIO *keybio;
	keybio = BIO_new(BIO_s_file());
	BIO_read_filename(keybio, str) ;
    if (!keybio)
		printf("Failed to create key BIO");
    rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa , 0, 0);
    if(!rsa )
		printf("Failed to create RSA");
    BIO_free(keybio);
    return rsa;
}

void	calculation(t_var *var)
{
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM*	tmp = BN_new();
	BIGNUM*	tmp1 = BN_new();
	BIGNUM*	tmp2 = BN_new();
	BIGNUM*	one = BN_new();
	BIGNUM* two = BN_new();
	var->e1 = BN_new();
	var->e2 = BN_new();
	var->phi = BN_new();
	var->privexp = BN_new();
	var->coeff = BN_new();
	BN_dec2bn(&one, "1");
	BN_dec2bn(&two, "2");
	BN_sub(tmp1, var->p , one);
	BN_sub(tmp2, var->q , one);
	BN_mul(var->phi, tmp1, tmp2, ctx);

	printf("PHi\n");

	var->privexp = BN_mod_inverse(var->privexp, var->pubexp, var->phi, ctx);
	printf("priv exp\n");

	printf("the rest\n");



	BN_sub(tmp, var->p, one);
	BN_mod(var->e1, var->privexp, tmp, ctx);
	BN_clear(tmp);
	BN_sub(tmp, var->q, one);
	BN_mod(var->e2, var->privexp, tmp, ctx);

	BN_sub(tmp1, var->p,  two);
	BN_mod_exp(var->coeff, var->q, tmp1 , var->p, ctx);




	BN_free(one);
	BN_free(two);
	BN_free(tmp);
	BN_free(tmp1);
	BN_free(tmp2);
	BN_CTX_free(ctx);



}

int		write_privatekey(RSA *rsa, char *str)
{

	BIO *bio_private;

	bio_private = BIO_new_file(str, "w+");
	if(!PEM_write_bio_RSAPrivateKey(bio_private, rsa, 0, 0, 0, 0, 0))
		return(0);
	BIO_free_all(bio_private);
    return 1;
}

void	gen_rsa_priv(t_var *var, char *str)
{
	RSA *p;
	char *s;

	p = RSA_new();
	if(!p)
		return;
	if(!RSA_set0_key(p, var->m, var->pubexp, var->privexp))
		printf("\nerror keyGen\n");
	if(!RSA_set0_factors(p, var->p, var->q))
		printf("\nerror key factors\n");
	if(!RSA_set0_crt_params(p, var->e1, var->e2, var->coeff))
		printf("\nerror key crt params\n");
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
	write_privatekey(p, str);
	RSA_free(p);
}

void	free_var(t_var *var)
{
	BN_free(var->phi);




}

void	begin(char *s1, char *s2)
{
	char	*s;
	t_var	var1;
	t_var	var2;
	RSA	*rsa1 = read_publickey(s1);
	RSA	*rsa2 = read_publickey(s2);
	BN_CTX	*ctx = BN_CTX_new();
	BIGNUM	*gcd = BN_new();

	var1.m = BN_dup((BIGNUM *)RSA_get0_n(rsa1));
	var2.m = BN_dup((BIGNUM *)RSA_get0_n(rsa2));
	var1.pubexp = BN_dup((BIGNUM *)RSA_get0_e(rsa1));
	var2.pubexp = BN_dup((BIGNUM *)RSA_get0_e(rsa2));
	BN_gcd(gcd, var1.m, var2.m, ctx);
	if(BN_is_one(gcd))
		exit(0);
	printf("this is gcd: %s\n", s = BN_bn2dec(gcd));	
	free(s);

	var1.p = BN_dup(gcd);
	var2.p = BN_dup(gcd);
	var1.q = BN_new();
	var2.q = BN_new();
	BN_div(var1.q, NULL, var1.m, gcd, ctx);
	BN_div(var2.q, NULL, var2.m, gcd, ctx);
	if (BN_cmp(var1.p, var1.q) < 0)
		ft_swap((int*)&var1.p, (int*)&var1.q);
	if (BN_cmp(var2.p, var2.q) < 0)
		ft_swap((int*)&var2.p, (int*)&var2.q);
	
//	printf("this is p1: %s\n", s = BN_bn2dec(var1.p));	
//	free(s);
//	printf("this is q1: %s\n", s = BN_bn2dec(var1.q));	
//	free(s);
//
//	printf("this is p2: %s\n", s = BN_bn2dec(var2.p));	
//	free(s);
//	printf("this is q2: %s\n", s = BN_bn2dec(var2.q));	
//	free(s);

	calculation(&var1);
	calculation(&var2);
	gen_rsa_priv(&var1, "rsa1-private");
	gen_rsa_priv(&var2, "rsa2-private");

	free_var(&var1);
	free_var(&var2);

	

	RSA_free(rsa1);
	RSA_free(rsa2);
	BN_free(gcd);
	BN_CTX_free(ctx);
}

void	check(char	*str)
{

	char	*buff;
	int n = 10000;
	buff = malloc(sizeof(char) * n);
	if(!buff)
		exit(0);
	int	fd = open(str, O_RDONLY);
	read(fd, buff, n);
	if (!strstr(buff, "BEGIN PUBLIC KEY"))
	{
		printf("\nError: please Enter a vaid public key in PEM format\n");
		exit(0);
	}
	free(buff);
}

void	leaks()
{
	system("leaks corsair");

}

int	main(int ac, char **av)
{

//	atexit(leaks);
	if (ac > 1 && ac < 4)
	{

		check(av[ac - 2]);
		check(av[ac - 1]);
		begin(av[ac - 2], av[ac - 1]);
	}
	else
		printf("Please enter  only the path of the 2 public.key in PEM Format\n");

	return (0);
}
