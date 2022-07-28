/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:47:20 by ahammoud          #+#    #+#             */
/*   Updated: 2022/07/28 18:55:26 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"


int		write_privatekey(RSA *rsa)
{

	BIO *bio_private;

	bio_private = BIO_new_file("private_new.pem", "w+");
	if(!PEM_write_bio_RSAPrivateKey(bio_private, rsa, 0, 0, 0, 0, 0))
		return(0);
	BIO_free_all(bio_private);
    return 1;
}


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

BIGNUM	*phi(t_prime z)
{
	BIGNUM*	phi = BN_new();
	BIGNUM*	one = BN_new();
	BIGNUM*	tmp1 = BN_new();
	BIGNUM*	tmp2 = BN_new();
	BN_CTX *ctx=BN_CTX_new();
	BN_dec2bn(&one, "1");
	BN_sub(tmp1, z.p , one);
	BN_sub(tmp2, z.q , one);
	BN_mul(phi, tmp1, tmp2, ctx);
	BN_free(one);
	BN_free(tmp1);
	BN_free(tmp2);
	BN_CTX_free(ctx);
	return phi;
}

void	get_rest(t_var	*var, t_prime *z)
{
	BIGNUM* tmp;//
	BIGNUM* tmp1;//
	var->e1 = BN_new(); ////
	var->e2 = BN_new(); ///
	var->coeff = BN_new(); ///
	BIGNUM* one = BN_new(); ////
	BIGNUM* two = BN_new(); ////
	BN_CTX *ctx=BN_CTX_new(); ////
	tmp = BN_new();
	tmp1 = BN_new();
	BN_dec2bn(&one, "1");
	BN_dec2bn(&two, "2");
	BN_sub(tmp, z->p, one);
	BN_mod(var->e1, var->privexp, tmp, ctx);
	BN_clear(tmp);
	BN_sub(tmp, z->q, one);
	BN_mod(var->e2, var->privexp, tmp, ctx);

	BN_sub(tmp1, z->p,  two);
	BN_mod_exp(var->coeff, z->q, tmp1 , z->p, ctx);
	
	BN_CTX_free(ctx);
	BN_free(tmp);
	BN_free(tmp1);
	BN_free(one);
	BN_free(two);
}

BIGNUM	*get_privexp(t_var	var)
{
//	char	*s1;
	BIGNUM*	d = BN_new();
	BIGNUM*	tmp = BN_new();
	BIGNUM*	mod = BN_new();
	BIGNUM*	one = BN_new();
	BIGNUM*	x = BN_new();
	BN_CTX *ctx=BN_CTX_new();
	BIGNUM* privexp;
	BN_dec2bn(&d, "0");
	BN_dec2bn(&one, "1");
//	printf("i am here inside prive exp %s %s  \n", BN_bn2dec(var.phi), BN_bn2dec(var.pubexp));
	while(BN_cmp(d ,(var.phi)) == -1)
	{
		BN_mul(x, d , var.pubexp, ctx);
		BN_mod(mod, x ,var.phi, ctx);

		if (BN_is_one(mod) == 1)
			privexp = BN_dup( d);
		BN_add(tmp, d, one);

		d = BN_copy(d, tmp);
		BN_clear(tmp);
	}
//	printf("this is  var exp: %s\n", s1 =  BN_bn2dec(var.privexp));

	BN_free(d);
	BN_free(tmp);
	BN_free(mod);
	BN_free(one);
	BN_free(x);
	BN_CTX_free(ctx);
//	free(s1);
	return (privexp);
}

t_var	calculation(RSA *rsa, t_prime z)
{
	t_var	var;
	
	var.phi = phi(z); 
	var.m = BN_dup((BIGNUM *)RSA_get0_n(rsa));
	var.pubexp = BN_dup((BIGNUM *)RSA_get0_e(rsa));
	var.privexp = get_privexp(var);
//	var = get_privexp(var);
	get_rest(&var, &z);
	return (var);
}

void	begin(char *str)
{
	RSA	*rsa = read_publickey(str);	
	BIGNUM	*n;
	t_prime	z;
	t_var	var;
	char *s1, *s2;

	n = BN_dup((BIGNUM *)RSA_get0_n(rsa));
	char *s = BN_bn2dec(n);
	printf("this is modulus %s\n", s);
	free(s);
	z = find_primes(n);
	printf("\nthis is primes p %s q %s\n", s1 = BN_bn2dec(z.p), s2 = BN_bn2dec(z.q));
	var = calculation(rsa, z);
	RSA_free(rsa);

	gen_rsa_priv(&var, &z, NULL);
	BN_free(n);

	BN_free(var.phi);

//	BN_free(z.q);
//	BN_free(z.p);
//
//	BN_free(var.m);
//	BN_free(var.pubexp);
//	BN_free(var.privexp);
//	BN_free(var.e1);
//	BN_free(var.e2);
//	BN_free(var.coeff);



	free(s1);
	free(s2);
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

	atexit(leaks);
	if (ac > 1)
	{

		check(av[ac - 1]);
		begin(av[ac - 1]);
	}
	else
		printf("Please enter the path of the public.key in PEM Format\n");
	return (0);
}
