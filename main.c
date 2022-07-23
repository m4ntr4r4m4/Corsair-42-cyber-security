#include "includes/corsair.h"

int main()
{
	unsigned long num =3757650997;


	unsigned long	count = 2;
	unsigned long	i=0;
	t_prime	z;
	
    while(num > 1)
    {
        while(fmod(num ,count) == 0)
        {
			if(i++ == 0)
				z.q = count;
			else
				z.p = count;
            num = num / count;
        }
		count++;

    }

	printf("this P %lu and this Q %lu\n", z.p, z.q);
	return 0;

}
