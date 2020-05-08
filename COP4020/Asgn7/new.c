#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <gmp.h>
#include <stdbool.h>


int power_of_2(int number)
{
        int count = 0;

        if (number == 0)
                return 0;

        while(number > 0)
        {
                if (number & 1 == 1)
                        count++;
                number = number >> 1;
        }

	if (count == 1)
                return 1;
	else
		return 0;
}


/*
	Table sucks up a lot of memory and all entries < x are never used again
*/
void pollard_table(mpz_t *table, int size, mpz_t *x, mpz_t *n)
{
	mpz_t one;
	mpz_init(one);
	mpz_set_str(one, "1", 10);
	int i;

	for(i = 0; i < size; i++)
	{
		//table[i] = (x * x + 1) % n
		mpz_mul(table[i], *x, *x);
		mpz_add(table[i], table[i], one);
		mpz_fdiv_r(table[i], table[i], *n);
		mpz_set(*x, table[i]);
	}
}

void print_table(mpz_t *table, int size)
{
	int i;

	if (size < 1000)
	{
		for(i = 0; i < size; i++)
		{
			printf("%d\t%s\n", i, mpz_get_str(NULL, 10, table[i]));
		}
	}
}

/*
	All this really does is subtract two big ints in table
*/
void pollard_rho(mpz_t *table, int i, int j, mpz_t *test_factor)
{
/*
	printf("debug test_factor = %s - %s\n", mpz_get_str(NULL, 10, table[i-1]),
		mpz_get_str(NULL, 10, table[j-1])
		);
*/

	mpz_t temp;
	mpz_init(temp);

	mpz_sub(temp, table[i], table[j]);
	mpz_abs(*test_factor, temp);
}

int main(int argc, char *argv[])
{
	mpz_t n;
	mpz_t r, test_factor;
	mpz_t *table;
	mpz_t seed;
	int i;
	int x = 0;
	int last_x = 0;
	int table_size;

        if (argc != 4)
	{
		printf("Usage: factor <seed> <table_size> <big number>\n");
		printf("Warning: table_size * 16 cannot exceed 32 bit memory limit\n");
		return 0;
	}


	table_size = strtoll(argv[2], NULL, 10);

	printf("Initializing table\n");
	table = (mpz_t *)malloc(table_size * sizeof(mpz_t));
	if (table == NULL)
	{
		perror("Unable to allocate memory for table");
		return 0;
	}

	for(i = 0; i < table_size; i++)
	{
		mpz_init(table[i]);
	}

	mpz_init(n);
	mpz_init(r);
	mpz_init(test_factor);
	mpz_init(seed);

	mpz_set_str(seed, argv[1], 10);
	// mpz_set_str(var, "big number", base);
	mpz_set_str(n, argv[3], 10);

	// Divide n by d, forming a quotient q and remainder r
	// f means floor rounding
	// mpz_fdiv_qr(q,r,n,d);
	
	printf("Generating table\n");
	pollard_table(table, table_size, &seed, &n);
	print_table(table, table_size);

	while (1)
	{
		x = last_x;

		for(i = 1; x + i < table_size; i++)
		{
			int y = x + i;
	
			mpz_t one, zero;
			mpz_init(one);
			mpz_init(zero);
			mpz_set_str(one, "1", 10);
			mpz_set_str(zero, "0", 10);
	
			pollard_rho(table, x, y, &test_factor );
			printf("Testing factor %u-%u length %u %s\n", x, y, y-x,  mpz_get_str(NULL, 10, test_factor) );
			mpz_gcd(r, n, test_factor);
			printf("gcd %s\n", mpz_get_str(NULL, 10, r));
			if ( mpz_cmp(r, one) > 0 && mpz_cmp(r, zero) != 0)
			{
				printf("Found factor %s\n", mpz_get_str(NULL, 10, r));
				return 0;
			}
	
			if ( power_of_2(y))
			{
				int j;
	
				x = y - 1;
				for(j = last_x; j < x; j++)
				{
					mpz_clear(table[j]);
					mpz_init(table[j]);
				}
				last_x = x;
			}
		}

		last_x = x;
		printf("Table is empty... making a new one\n");
		mpz_set(seed, table[last_x]);
		pollard_table(table, table_size, &seed, &n);
	}

	printf("Failed: index %d exceeded table size\n", x + i);
	return 0;
}
