#include "corsair.h"

BIGNUM	*next_prime(BIGNUM *count, BIGNUM *one, BN_CTX *ctx, BIGNUM *tmp, BIGNUM *num)
{
	while (BN_cmp(num , count) > 0)	
	{
		BN_add(tmp, count, one);
		count = BN_copy(count, tmp);

		if (BN_is_prime_ex(count, BN_prime_checks ,ctx, NULL))
		{
			break;
		}
	}
	BN_clear(tmp);
	return (count);
}

void	get_prime(BIGNUM *num, char *str)
{
	if (!strcmp(BN_bn2dec(num), "0"))
		exit (0);
	BN_CTX *ctx=BN_CTX_new();
	BIGNUM*	count = BN_new();
	BN_dec2bn(&count, str);

	BIGNUM*	tmp = BN_new();

	BIGNUM*	i = BN_new();
	BN_dec2bn(&i, "0");

	BIGNUM*	one = BN_new();
	BN_dec2bn(&one, "1");
	BIGNUM*	zero = BN_new();
	BN_dec2bn(&zero, "0");
	BIGNUM*	mod = BN_new();

	while (BN_cmp(num , one) > 0)	
	{
		count = next_prime(count, one, ctx, tmp, num);
		if(!BN_mod(mod, num, count, ctx))
			printf("error mod\n");
		if (BN_cmp(mod, zero) == 0 && BN_cmp(num , one) > 0)
        {
			printf("this is prime %s\n", BN_bn2dec(count));
			BN_div(tmp, NULL, num, count, ctx);
			printf("this is prime 2  %s\n", BN_bn2dec(tmp));
			break;
		}
	}
	BN_CTX_free(ctx);
	BN_free(count);
	BN_free(tmp);
	BN_free(i);
	BN_free(one);
	BN_free(zero);
	BN_free(mod);
}

char	*fill(int	len)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * len / 2);
	if (!str)
		return (NULL);
	str[0] = '1';
	while(++i < (len / 2))
		str[i] = '0';
	return (str);
}

int	main(int	ac, char **av)
{
	int		len = strlen(av[ac - 1]) - 2;
	char	*num = av[ac - 1];
	char	*str = fill(len);
	BIGNUM *a = BN_new();
	BN_dec2bn(&a, num);
	get_prime(a, str);
	BN_clear_free(a);


}
