#include "corsair.h"

void	 get_primes(long	double num)
{
	long	double	count = 2;
	long	double	i=0;
	long double x = num;
	printf("casted to double %Lf\n", x);
	
    while(num > 1)
    {
        while(fmodl(num ,count) == 0)
        {
			printf("this is pime %Lf\n",count );
            num = num / count;
        }
		count++;

    }
}


int	main()
{
	long	double num;
  printf("Enter any number to print Prime factors: ");
    scanf("%Lf", &num);
	get_primes(num);


}
