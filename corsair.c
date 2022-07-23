/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corsair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:47:20 by ahammoud          #+#    #+#             */
/*   Updated: 2022/07/23 14:06:26 by ahammoud         ###   ########.fr       */
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

t_prime get_primes(unsigned long num)
{
	int count = 2;
	int	i=0;
	t_prime	z;
	
    while(num > 1)
    {
        while(num % count == 0)
        {
			if(i++ == 0)
				z.q = count;
			else
				z.p = count;
            num = num / count;
        }
		count++;
    }
	return (z);
}

unsigned long phi(t_prime z)
{
	unsigned long  phi;

	phi = (z.p - 1) * (z.q - 1);
 //	printf("this is P  %lu Q %lu \n",z.p, z.q);
	return phi;
}


t_var	get_rest(t_var	var, t_prime z)
{
	var.e1 = var.privexp % (z.p - 1);
	var.e2 = var.privexp % (z.q - 1);
 	printf("this is P  %lu Q %lu \n",z.p, z.q);
	var.coeff = (unsigned long) pow(z.q, (z.p - 2)) % z.p;
 //	printf("this is P  %lu Q %lu \n",z.p, z.q);
 //	printf("this is P  %lu Q %lu \n",z.p, z.q);
	return (var);
}

t_var	get_privexp(t_var	var)
{
	unsigned long	d = 0;
	while(d < (var.phi))
	{
		if ((d * var.pubexp) % var.phi == 1)
			var.privexp = d;
		d++;
	}
	return (var);
}

t_var	calculation(RSA *rsa, t_prime z)
{
	t_var	var;
	
	var.phi = phi(z); 
	printf("\n this is phi %lu\n", var.phi);
	printf("\nthis is modulus %lu\n", var.m = z.p * z.q);
	var.pubexp = atoi(BN_bn2dec(RSA_get0_e(rsa)));
	printf("this is pubexp %lu \n",var.pubexp);
	var = get_privexp(var);
	var	= get_rest(var, z);
	printf("this is privexp %lu \n",var.privexp);
	printf("this is e1 %lu \n",var.e1);
	printf("this is e2 %lu \n",var.e2);
	printf("this is coeff %lu \n",var.coeff);
	return (var);
}

int	gen_rsa_priv(t_var var, t_prime z)
{
	RSA *rsa;

	BIGNUM	*n = NULL;
	BIGNUM	*e = NULL;
	BIGNUM	*d = NULL;
	BIGNUM	*p = NULL;
	BIGNUM	*q = NULL;
	BIGNUM	*e1 = NULL;
	BIGNUM	*e2 = NULL;
	BIGNUM	*coeff = NULL;

	if(!BN_dec2bn(&n, ft_itoa(var.m)))
		printf("error bignum n\n");
	if(!BN_dec2bn(&e, ft_itoa(var.pubexp)))
		printf("error bignum e\n");
	if(!BN_dec2bn(&d, ft_itoa(var.privexp)))
		printf("error bignum d\n");
	if(!BN_dec2bn(&p, ft_itoa(z.p)))
		printf("error bignum p\n");
	if(!BN_dec2bn(&q, ft_itoa(z.q)))
		printf("error bignum q\n");
	if(!BN_dec2bn(&e1, ft_itoa(var.e1)))
		printf("error bignum e1\n");
	if(!BN_dec2bn(&e2, ft_itoa(var.e2)))
		printf("error bignum e2\n");
	if(!BN_dec2bn(&coeff, ft_itoa(var.coeff)))
		printf("error bignum coeff\n");






	rsa = RSA_new();
	if(!RSA_set0_key(rsa, n, e, d))
		printf("\nerror keyGen\n");
	if(!RSA_set0_factors(rsa, p, q))
		printf("\nerror key factors\n");
	if(!RSA_set0_crt_params(rsa, e1, e2, coeff))
		printf("\nerror key crt params\n");

	int	fd = open("cracked_private.key", O_CREAT | O_RDWR);
	BIO	*keybio=NULL;
	keybio = BIO_new(BIO_s_mem());

	if(!PEM_write_bio_RSAPrivateKey(keybio, rsa, 0,0,0,0,0))
		printf("\nerror BIO write\n");
	
	RSA	*rs1 = RSA_new();
    rs1 = PEM_read_bio_RSAPrivateKey(keybio, &rs1 , 0, 0);

	printf("\nthis is modulus ifromlast keybio %s\n", BN_bn2dec((RSA_get0_n(rs1))));

	write_privatekey(rsa, keybio);

//	FILE *fp;
//	fp = fopen("cracker_private_file", "w");
//	PEM_write_RSAPrivateKey(fp, rsa, 0,0,0,0,0);
//
//	fclose(fp);


	return (0);
}


void	begin(char *str)
{
	RSA	*rsa = read_publickey(str);	
	const BIGNUM	*n = NULL;
	const BIGNUM	*e = NULL;
	t_prime	z;
	t_var	var;

	n = RSA_get0_n(rsa);
	e = RSA_get0_e(rsa);
//	printf("\nthis is modulus  %s\n", BN_bn2dec(n));
//	printf("\n this si exp   %s\n", BN_bn2dec(e));
	z = get_primes(atoi(BN_bn2dec(n)));
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
