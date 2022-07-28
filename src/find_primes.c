#include "corsair.h" 

void	 get_primes(BIGNUM *num)
{
	if (!strcmp(BN_bn2dec(num), "0"))
		exit (0);
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
		if(!BN_mod(mod, num, count, ctx))
			printf("error mod\n");
        while(BN_cmp(mod, zero) == 0 && BN_cmp(num , one) > 0)
        {
			printf("this is prime %s\n", BN_bn2dec(count));

            BN_div(tmp, NULL, num, count, ctx);
			num = BN_copy(num, tmp);
			printf("this is prime 2  %s\n", BN_bn2dec(num));
			BN_clear(tmp);
			return ;
			if(!BN_mod(mod, num, count, ctx))
				printf("error mod\n");
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
}


int	main(int	ac, char **av)
{
	char* num = av[ac - 1];
	BIGNUM *a = BN_new();
	BN_dec2bn(&a, num);
	get_primes(a);
	BN_clear_free(a);


}
