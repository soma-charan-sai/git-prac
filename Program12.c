#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct record
{
	char name[20];
	int id, flag;
}ht[10];
int hash(int key)
{
	int value, slots = 10;
	value = key % slots;
	return value;
}
void main()
{
	FILE *in, *out;
	int i, j, k, n, id, location;
	char name[20];
	printf("\n enter the number of records less than 10\n");
	scanf("%d", &n);
	in = fopen("input.txt", "r");
	if (n <= 10)
	{
		for (k = 0; k < 10; k++)
			ht[k].flag = 0;
		for (i = 0; i < n; i++)
		{
			fscanf(in, "%d%s", &id, name);
			location = hash(id);
			if (ht[location].flag == 0)
			{
				printf("the address of %d record is %d\n", i + 1, location);
				strcpy(ht[location].name, name);
				ht[location].id = id;
				ht[location].flag = 1;
			}
			else
			{
				printf("Collision detetcted!\n");
				for (j = location + 1; (j % 10) < 10; j++)
				{
					if (!ht[j % 10].flag)
					{
						printf("the address of %d record is %d\n", i + 1, j%10);
						strcpy(ht[j % 10].name, name);
						ht[j % 10].id = id;
						ht[j % 10].flag = 1;
						break;
					}
				}

			}
		}
		fclose(in);
		//display hash table
		printf("The Hash Table contents are\n");
		for (k = 0; k < 10; k++)
		{
			if (ht[k].flag == 0)
				printf("\n##\n");
			else
				printf("%d \t %s \n", ht[k].id, ht[k].name);
			//writing ht contents to file
		}
		out = fopen("output.txt", "w");
		for (k = 0; k < 10; k++)
		{
			if (ht[k].flag == 0)
				fprintf(out, "##\n");
			else
				fprintf(out, "%d %s \n", ht[k].id, ht[k].name);

		}
	}
	fclose(out);
	getch();
}