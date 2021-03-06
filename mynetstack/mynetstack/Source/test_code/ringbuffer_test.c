#include "test_main.h"

u8 ______write_buffer_data____get_unread_ptr_____(u32 loop)
{
	u32 i,j,k;
	u8* s1, *s2;
	u32 l,m = 0,n = 0;
	u8* str = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	u8 check;
	ringbuffer ring;
#ifdef ____SHOW__DEBUG____
	printf("%d", strlen(str));
#endif // ____SHOW__DEBUG____
	initial_buffer(&ring, YES, strlen(str));
	while (loop--)
	{
#ifdef ____SHOW__DEBUG____
		printf("缓存总大小：%d \r\n", strlen(str));
		printf("Buffer数据：\r\n");
		for( k =0; k< strlen(str);k++)
			printf("%c", start_ringbuffer_ptr[k]);
		printf("\r\n写入数据：");
#endif // ____SHOW__DEBUG____
		l = rand() % (strlen(str) + 1);
#ifdef ____SHOW__DEBUG____
		for (k = 0; k < l; k++)
			printf("%c", str[k]);
		printf("\r\n");
#endif // ____SHOW__DEBUG____
		write_buffer_data(&ring, str, l);
		get_unread_ptr(&ring, &s1,&s2,&i,&j,NO);
#ifdef ____SHOW__DEBUG____
		printf("读出数据：");
#endif // ____SHOW__DEBUG____
		check = YES;
		for (k = 0; k < i; k++) {
#ifdef ____SHOW__DEBUG____
			printf("%c", s1[k]);
#endif // ____SHOW__DEBUG____
			if (str[k] != s1[k])
				check = NO;
		}
		for (k = 0; k < j; k++) {
#ifdef ____SHOW__DEBUG____
			printf("%c", s2[k]);
#endif // ____SHOW__DEBUG____
			if (str[i+k] != s2[k])
				check = NO;
		}
		if (check == NO)
			m++;
		n++;
#ifdef ____SHOW__DEBUG____
		printf("\r\n");
		printf("读写不同出现次数：%d",m);
		printf("测试总次数：%d", n);
		system("cls");
#endif // ____SHOW__DEBUG____
	}
	if (m == 0)
		return YES;
	return NO;
}


u8 ______write_buffer_len____get_unread_ptr_____(u32 loop)
{
	u32 i, j, k, o;
	u8* s1, *s2;
	u32 l, m = 0, n = 0;
	u8* str = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	u8 check;
	ringbuffer ring;
#ifdef ____SHOW__DEBUG____
	printf("%d", strlen(str));
#endif // ____SHOW__DEBUG____
	initial_buffer(&ring, YES, strlen(str));
	
	while (loop--)
	{
#ifdef ____SHOW__DEBUG____
		printf("缓存总大小：%d \r\n", strlen(str));
		printf("Buffer数据：\r\n");
		for (k = 0; k < strlen(str); k++)
			printf("%c", start_ringbuffer_ptr[k]);
		printf("\r\n写入数据：");
#endif // ____SHOW__DEBUG____
		l = rand() % (strlen(str) + 1);
#ifdef ____SHOW__DEBUG____
		for (k = 0; k < l; k++)
			printf("%c", str[k]);
		printf("\r\n");
#endif // ____SHOW__DEBUG____
		o = 999999;
		for (k = 0; k < l; k++)
		{
			if (&ring.write_location_ptr[k] == ring.end_ringbuffer_ptr)
			{
				o = 0;
			}
			if(o == 999999)
				ring.write_location_ptr[k] = str[k];
			else
				ring.start_ringbuffer_ptr[o++] = str[k];
		}
		write_buffer_len(&ring, l);
		get_unread_ptr(&ring, &s1, &s2, &i, &j, NO);
#ifdef ____SHOW__DEBUG____
		printf("读出数据：");
#endif // ____SHOW__DEBUG____
		check = YES;
		for (k = 0; k < i; k++) {
#ifdef ____SHOW__DEBUG____
			printf("%c", s1[k]);
#endif // ____SHOW__DEBUG____
			if (str[k] != s1[k])
				check = NO;
		}
		for (k = 0; k < j; k++) {
#ifdef ____SHOW__DEBUG____
			printf("%c", s2[k]);
#endif // ____SHOW__DEBUG____
			if (str[i + k] != s2[k])
				check = NO;
		}
		if (check == NO)
			m++;
		n++;
#ifdef ____SHOW__DEBUG____
		printf("\r\n");
		printf("读写不同出现次数：%d", m);
		printf("测试总次数：%d", n);
		system("cls");
#endif // ____SHOW__DEBUG____
	}
	if (m == 0)
		return YES;
	return NO;
}



u8 ______write_buffer_len____get_unread_data_____(u32 loop)
{
	u32 i, k, o;
	u8* s1;
	u32 l, m = 0, n = 0;
	u8* str = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	u8 check;
	ringbuffer ring;
#ifdef ____SHOW__DEBUG____
	printf("%d", strlen(str));
#endif // ____SHOW__DEBUG____
	initial_buffer(&ring, YES, strlen(str));

	while (loop--)
	{
#ifdef ____SHOW__DEBUG____
		printf("缓存总大小：%d \r\n", strlen(str));
		printf("Buffer数据：\r\n");
		for (k = 0; k < strlen(str); k++)
			printf("%c", start_ringbuffer_ptr[k]);
		printf("\r\n写入数据：");
#endif // ____SHOW__DEBUG____
		l = rand() % (strlen(str) + 1);
#ifdef ____SHOW__DEBUG____
		for (k = 0; k < l; k++)
			printf("%c", str[k]);
		printf("\r\n");
#endif // ____SHOW__DEBUG____
		o = 999999;
		for (k = 0; k < l; k++)
		{
			if (&ring.write_location_ptr[k] == ring.end_ringbuffer_ptr)
			{
				o = 0;
			}
			if (o == 999999)
				ring.write_location_ptr[k] = str[k];
			else
				ring.start_ringbuffer_ptr[o++] = str[k];
		}
		if (loop == 999836)
			loop = 999836;
		write_buffer_len(&ring, l);
		s1 = get_unread_data(&ring, &i, NO);
#ifdef ____SHOW__DEBUG____
		printf("读出数据：");
#endif // ____SHOW__DEBUG____
		check = YES;
		for (k = 0; k < i; k++) {
#ifdef ____SHOW__DEBUG____
			printf("%c", s1[k]);
#endif // ____SHOW__DEBUG____
			if (str[k] != s1[k])
				check = NO;
		}
		if (check == NO)
			m++;
		n++;
#ifdef ____SHOW__DEBUG____
		printf("\r\n");
		printf("读写不同出现次数：%d", m);
		printf("测试总次数：%d", n);
		system("cls");
#endif // ____SHOW__DEBUG____
	}
	if (m == 0)
		return YES;
	return NO;
}



u8 ____update_readlocation_len____(u32 loop)
{
	u8* str = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	ringbuffer ring;
	u8* s1, *s2;
	u32 i, j, k, o, u, p;

	initial_buffer(&ring, YES, 10);
	for (i = 0; i < 10; i++)
		ring.start_ringbuffer_ptr[i] = str[i];
	write_buffer_len(&ring, 10);


	get_unread_ptr(&ring, &s1, &s2, &i, &j, YES);
	for (k = 0; k < i; k++)
		printf("%c",s1[k]);
	for (k = 0; k < j; k++)
		printf("%c", s2[k]);
	printf("\r\n");
	update_readlocation_len(&ring, 5);
	get_unread_ptr(&ring, &s1, &s2, &i, &j, YES);
	for (k = 0; k < i; k++)
		printf("%c", s1[k]);
	for (k = 0; k < j; k++)
		printf("%c", s2[k]);
	printf("\r\n");


	write_buffer_len(&ring, 7);
	get_unread_ptr(&ring, &s1, &s2, &i, &j, YES);
	for (k = 0; k < i; k++)
		printf("%c", s1[k]);
	for (k = 0; k < j; k++)
		printf("%c", s2[k]);
	printf("\r\n");

	update_readlocation_len(&ring, 1);
	write_buffer_len(&ring, 7);
	get_unread_ptr(&ring, &s1, &s2, &i, &j, YES);
	for (k = 0; k < i; k++)
		printf("%c", s1[k]);
	for (k = 0; k < j; k++)
		printf("%c", s2[k]);
	printf("\r\n");
}

















u8 ____update_readlocation_len____2(u32 loop)
{
	u32 i, j, k, o,u,p;
	u8* s1, *s2;
	u32 l, m = 0, n = 0;
	u8* str = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	u8 check;
	ringbuffer ring;
	initial_buffer(&ring, YES, strlen(str));
	while (loop--)
	{
		l = rand() % (strlen(str) + 1);
		o = 999999;
		for (k = 0; k < l; k++)
		{
			if (&ring.write_location_ptr[k] == ring.end_ringbuffer_ptr)
			{
				o = 0;
			}
			if (o == 999999)
				ring.write_location_ptr[k] = str[k];
			else
				ring.start_ringbuffer_ptr[o++] = str[k];
		}
		write_buffer_len(&ring, l);





		p = rand() % (strlen(str) + 1);
		get_unread_ptr(&ring, &s1, &s2, &i, &j, YES);
		update_readlocation_len(&ring, p);
		check = YES;
		for (k = 0; k < ((i <= p) ? i : p); k++) {
			if (str[k] != s1[k])
				check = NO;
		}
		for (k = 0; k < ((i <= p) ? j : 0); k++) {
			if (str[i + k] != s2[k])
				check = NO;
		}
		if (check == NO)
			m++;
		n++;
		


	}
	if (m == 0)
		return YES;
	return NO;
}
