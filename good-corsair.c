/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:47:20 by ahammoud          #+#    #+#             */
/*   Updated: 2022/07/25 18:27:45 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"


int		write_privatekey(RSA *rsa, BIO *keybio)
{

	BIO *bio_private;

	bio_private = BIO_new_file("private_new.pem", "w+");
	PEM_write_bio_RSAPrivateKey(bio_private, rsa, 0, 0, 0, 0, 0);
    return 0;
}


RSA		*read_publickey(char	*str)
{

	RSA *rsa = RSA_new();
    BIO *keybio = NULL;
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

t_prime get_primes(long	double num)
{
	long	double	count = 2;
	long	double	i=0;
	t_prime	z;
	long double x = num;
	printf("casted to double %Lf\n", x);
	
    while(num > 1)
    {
        while(fmodl(num ,count) == 0)
        {
			if(i++ == 0)
				z.q = count;
			else
				z.p = count;
            num = num / count;
        }
		count++;

    }
		printf("this P %Lf and this Q %Lf\n", z.p, z.q);
	return (z);
}

long	double phi(t_prime z)
{
	long	double  phi;

	phi = (z.p - 1) * (z.q - 1);

	return phi;
}

// Recursive C program to compute modular power

long double exponentMod(long double A, long double  B, long double C)
{
    // Base cases
    if (A == 0)
        return 0;
    if (B == 0)
        return 1;

    // If B is even
    long double y;
    if (fmodl(B , 2) == 0) {
        y = exponentMod(A, B / 2, C);
        y = fmodl((y * y) ,  C);
    }

    // If B is odd
    else {
        y = fmodl(A , C);
        y = fmodl((y * fmodl(exponentMod(A, B - 1, C) , C)) , C);
    }

    return (fmodl((y + C) , C));
}


t_var	get_rest(t_var	var, t_prime z)
{
	var.e1 = fmodl(var.privexp , (z.p - 1));
	var.e2 = fmodl(var.privexp ,(z.q - 1));
 	printf("this is P  %Lf Q %Lf \n",z.p, z.q);
//	var.coeff = fmodl(powl(z.q, (z.p - 2)) , z.p);
//	var.coeff = fmodl(powl(fmodl(z.q, z.p), (z.p - 2)) , z.p);

	var.coeff = exponentMod(z.q, z.p - 2, z.p);
	printf("coeff %Lf\n", var.coeff);
//	exit (0);
	return (var);
}

t_var	get_privexp(t_var	var)
{
	long	double	d = 0;
	long	double	x;
	printf("i am here inside prive exp %Lf %Lf  \n", var.phi, var.pubexp);
	while(d < (var.phi))
	{
		x = d * var.pubexp;
		if (fmodl(x, var.phi) == 1)
			var.privexp = d;
		d++;
	}
	return (var);
}

t_var	calculation(RSA *rsa, t_prime z)
{
	t_var	var;
	char	*ptr;
	
	var.phi = phi(z); 
	var.m = z.p * z.q;
	var.pubexp = strtold(BN_bn2dec(RSA_get0_e(rsa)), &ptr);
	var = get_privexp(var);
	var	= get_rest(var, z);
	return (var);
}

int	gen_rsa_priv(t_var var, t_prime z)
{
	RSA *rsa;
	char	str[1000];

	BIGNUM	*n = NULL;
	BIGNUM	*e = NULL;
	BIGNUM	*d = NULL;
	BIGNUM	*p = NULL;
	BIGNUM	*q = NULL;
	BIGNUM	*e1 = NULL;
	BIGNUM	*e2 = NULL;
	BIGNUM	*coeff = NULL;



snprintf( str , 1000   , "%Lf",var.m);
	if(!BN_dec2bn(&n, str))
		printf("error bignum n\n");
snprintf(str , 1000   , "%Lf", var.pubexp);
	if(!BN_dec2bn(&e, str))
		printf("error bignum e\n");
snprintf(str , 1000   , "%Lf",var.privexp);
	if(!BN_dec2bn(&d, str))
		printf("error bignum d\n");
snprintf(str , 1000   , "%Lf", z.p);
	if(!BN_dec2bn(&p, str))
		printf("error bignum p\n");
snprintf(str , 1000   , "%Lf", z.q);
	if(!BN_dec2bn(&q, str))
		printf("error bignum q\n");
snprintf( str , 1000   , "%Lf", var.e1);
	if(!BN_dec2bn(&e1, str))
		printf("error bignum e1\n");
snprintf( str , 1000   , "%Lf", var.e2);
	if(!BN_dec2bn(&e2, str))
		printf("error bignum e2\n");
snprintf(str , 1000   , "%Lf", var.coeff);
	if(!BN_dec2bn(&coeff, str))
		printf("error bignum coeff\n");

	rsa = RSA_new();
	if(!RSA_set0_key(rsa, n, e, d))
		printf("\nerror keyGen\n");
	if(!RSA_set0_factors(rsa, p, q))
		printf("\nerror key factors\n");
	if(!RSA_set0_crt_params(rsa, e1, e2, coeff))
		printf("\nerror key crt params\n");

	BIO	*keybio=NULL;
	keybio = BIO_new(BIO_s_mem());

	if(!PEM_write_bio_RSAPrivateKey(keybio, rsa, 0,0,0,0,0))
		printf("\nerror BIO write\n");
	
	RSA	*rs1 = RSA_new();
    rs1 = PEM_read_bio_RSAPrivateKey(keybio, &rs1 , 0, 0);

	printf("\nthis is modulus from last keybio %s\n", BN_bn2dec((RSA_get0_n(rs1))));

	write_privatekey(rsa, keybio);
	return (0);
}


void	begin(char *str)
{
	RSA	*rsa = read_publickey(str);	
	const BIGNUM	*n = NULL;
	const BIGNUM	*e = NULL;
	t_prime	z;
	t_var	var;
	char *ptr;

	n = RSA_get0_n(rsa);
	e = RSA_get0_e(rsa);
	char *s = BN_bn2dec(n);
	printf("this is modulus %s\n", s);
	z = get_primes(strtold(s, &ptr));
	printf("\nthis is primes p %Lf q%Lf\n", z.p, z.q);
	var = calculation(rsa, z);
	gen_rsa_priv(var, z);
}

void	check(char	*str)
{

	char	buff[10000];
	int	fd = open(str, O_RDONLY);
	read(fd, buff, 10000);
	if (!strstr(buff, "BEGIN PUBLIC KEY"))
	{
		printf("\nError: please Enter a vaid public key in PEM format\n");
		exit(0);
	}

}


int	main(int ac, char **av)
{

	if (ac > 1)
	{

		check(av[ac - 1]);
		begin(av[ac - 1]);
	}
	else
		printf("Please enter the path of the public.key in PEM Format\n");
	return (0);
}
