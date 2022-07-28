#include "corsair.h" 

t_prime	 find_primes(const BIGNUM *num)
{
	t_prime	z;

	z.p = BN_new();
	z.q = BN_new();
	BN_CTX *ctx=BN_CTX_new();
	BIGNUM*	count = BN_new();
	BN_dec2bn(&count, "2");

	BIGNUM*	tmp = BN_new();

	BIGNUM*	i = BN_new();
	BN_dec2bn(&i, "0");

	BIGNUM*	one = BN_new();
	BN_dec2bn(&one, "1");
	BIGNUM*	zero = BN_new();
	BN_dec2bn(&zero, "0");
	BIGNUM*	mod = BN_new();

    while(BN_cmp(num, one) > 0)
    {
		if	(!BN_mod(mod, num, count, ctx))
			printf("error mod\n");
       	if	(BN_cmp(mod, zero) == 0 && BN_cmp(num , one) > 0)
        {
			z.q = BN_copy(z.q, count);

	//		printf("this is prime %s\n", BN_bn2dec(z.p));

            BN_div(tmp, NULL, num, count, ctx);
			z.p = BN_copy(z.p, tmp);

	//		printf("this is prime 2  %s\n", BN_bn2dec(z.q));
			BN_clear(tmp);
			break ;	
        }
		BN_add(tmp, count, one);
		count = BN_copy(count, tmp);
		BN_clear(tmp);
    }
	BN_CTX_free(ctx);
	BN_free(count);
	BN_free(tmp);
	BN_free(i);
	BN_free(one);
	BN_free(zero);
	BN_free(mod);
	return(z);
}

