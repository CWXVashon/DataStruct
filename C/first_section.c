//
//  first_section.c
//  data_struct
//
//  Created by mac on 2020/5/18.
//  Copyright © 2020 mingxi. All rights reserved.
//  数据结构第一章练习题

#include<math.h>
#include<stdio.h>

// 实验 1.1
// 判断一个数是否素数
int primeNumber(int n)
{
    int i;
    for(i = 2; i <= (int)sqrt(n); i++)
        if(n % i == 0)
            return 0;
    
    return 1;
}

void practice1_1(void)
{
    int n, i, j = 0;
    printf("请输入需要输出的素数范围：");
    scanf("%d", &n);
    printf("小于等于：%d 的素数为：\n", n);
    
    if(n > 2)
    {
        printf("%4d", 2);
        j++;
    }
    
    for(i = 3; i <= n; i += 2)
    {
        if(primeNumber(i))
        {
            printf("%4d", i);
            if(j != 0 && ++j % 10 == 0)
                printf("\n");
        }
    }
    
    printf("\n");
}

// 实验 1.2
void practice1_2(void)
{
    int num, temp, sum = 0;
    printf("请输入任意的正整数：");
    scanf("%d", &num);
    temp = num;
    
    while(temp)
    {
        sum += temp % 10;
        temp /= 10;
    }
    
    printf("正整数：%d，每位的累加和为：%d\n", num, sum);
}

// 实验 1.3
void practice1_3(void)
{
    char str[100];
    int strLen = 0, start = 0, end = 0;
    
    printf("请输入一个字符串：");
    scanf("%s", str);
    
    while(str[strLen] != '\0')
        strLen++;
    // 去除最后一个结束标记：'\0'
    end = strLen - 1;
    while(end > start)
    {
        if(str[start] != str[end])
        {
            printf("字符串：%s，不是回文字符串\n", str);
            return;
        }
        start++;
        end--;
    }
    printf("字符串：%s，是回文字符串\n", str);
}
