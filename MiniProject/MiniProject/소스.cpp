#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
/*
0. ���� �������̽� ����
1. �ű� �� ���
2. ����ȸ
3. �ű� ���� ���
4. ���� ��ȸ
5. ���� �뿩
6. ���� �ݳ�
7. ���� ��ü ó��
*/
typedef struct _customer {
	int id; //����ȣ
	char name[20]; //���̸�
	char ssn[14]; //�ֹε�Ϲ�ȣ
	char phone[12]; //��ȭ��ȣ
	char address[50]; //�ּ�
} CUSTOMER; //������ ����ü

typedef struct _video {
	int id; //���� ��ȣ
	char title[20]; //���� ����
	char genre[10]; //�帣
	int charge; //�뿩��
	char regist_date[9]; //�������
	int is_rented; //1: �뿩��, 0: �뿩���� �ƴ�
	int late_fee; //1�� ��ü��
} VIDEO; //�������� ����ü

typedef struct _rent_info {
	int id; //�뿩 ��ȣ
	int video_id; //���� ��ȣ
	int cust_id; //����ȣ
	int rent_date; //�뿩 ����
	int ret_due_date; //�ݳ����� ����
	int ret_date; //�ݳ� ����
	int is_returned; //1: �ݳ��Ϸ�, 0: �뿩��
	int total_late_fee; //�� ��ü��
	int charge; //�뿩��(�뿩�� �����)
} RENT_INFO; //�뿩, �ݳ� ���� ����ü

void input_customer();
void input_video();
void new_customer();
int search_customer();
void new_video();
int search_video();
void rent_video();
void return_video();

CUSTOMER customer_info[200];
int c_idx = 0; //������ ����� ����
VIDEO video_info[200];
int v_idx = 0; //�������� ����� ����
RENT_INFO rent; //�Ѱ��� ������ �뿩/�ݳ�
int rent_id = 1; //�뿩��ȣ

int main(void)
{
	int i, sel = 1, idx;

	input_customer(); //������ �Է�
	input_video(); //�������� �Է�

	while(sel!=0)
	{
		system("cls");
		printf("��������������������������������������������������������\n");
		printf("��<���� �뿩���� ���α׷�>��\n");
		printf("��1. �ű� �� ���         ��\n");
		printf("��2. �� ���� ��ȸ         ��\n");
		printf("��3. ��ü �� ���� ��ȸ    ��\n");
		printf("��4. �ű� ���� ���       ��\n");
		printf("��5. ���� ���� ��ȸ       ��\n");
		printf("��6. ��ü ���� ���� ��ȸ  ��\n");
		printf("��7. �뿩                   ��\n");
		printf("��8. �ݳ�                   ��\n");
		printf("��0. ����                   ��\n");
		printf("��������������������������������������������������������\n");
		printf("���׸��� �����ϼ��� : ");
		scanf("%d", &sel);

		switch (sel)
		{
		case 1:
			system("cls");
			new_customer();
			break;

		case 2:
			system("cls");
			idx = search_customer();
			if (idx == -1)
			{
				printf("��ġ�ϴ� ���� �����ϴ�.\n");
			}		
			else
			{
				printf("%d, %s, %s, %s, %s\n"
					, customer_info[idx].id
					, customer_info[idx].name
					, customer_info[idx].ssn
					, customer_info[idx].phone
					, customer_info[idx].address);
			}
			break;

		case 3:
			system("cls");
			for (i = 0; i < c_idx; i++)
			{
				printf("%d, %s, %s, %s, %s\n"
					, customer_info[i].id
					, customer_info[i].name
					, customer_info[i].ssn
					, customer_info[i].phone
					, customer_info[i].address);
			}
			break;

		case 4:
			system("cls");
			new_video();
			break;

		case 5:
			system("cls");
			idx = search_video();
			if (idx == -1)
			{
				printf("��ġ�ϴ� ������ �����ϴ�.\n");
			}
			else
			{
				printf("%d, %s, %s, %d, %s, %d, %d\n"
					, video_info[idx].id
					, video_info[idx].title
					, video_info[idx].genre
					, video_info[idx].charge
					, video_info[idx].regist_date
					, video_info[idx].is_rented
					, video_info[idx].late_fee);
			}
			break;

		case 6:
			system("cls");
			for (i = 0; i < v_idx; i++)
			{
				printf("%d, %s, %s, %d, %s, %d, %d\n"
					, video_info[i].id
					, video_info[i].title
					, video_info[i].genre
					, video_info[i].charge
					, video_info[i].regist_date
					, video_info[i].is_rented
					, video_info[i].late_fee);
			}
			break;

		case 7:
			rent_video();
			break;
			
		case 8:
			system("cls");
			return_video();
			break;
		case 0:
			exit(1);
		}
		_getch();
	}	
	return 0;
}

//���� �ݳ�
void return_video()
{
	time_t timer;
	struct tm * t;
	int ret_sec;
	int late_pay, late_day;

	video_info[rent.video_id - 1].is_rented = 0;  //�ݳ� ǥ��

	rent.video_id;  //���� ��ȣ
	rent.ret_date = timer = time(NULL);  //�ݳ� ����
	rent.is_returned = 1; //1: �ݳ� �Ϸ�, 0: �뿩��

	if (rent.ret_date > rent.ret_due_date)  //�ݳ� �������� �ѱ� ���
	{
		ret_sec = rent.ret_date - rent.ret_due_date;
		late_day = ((ret_sec / 86400) + 1);  //�� ������ ���
		late_pay = late_day * video_info[rent.video_id - 1].late_fee;  //��ü�� ���
		printf("%d�� ��ü�Ǿ����ϴ�. ��ü��� %d�Դϴ�.\n", late_day, late_pay);
	}
	printf("���� �ݳ��� �Ϸ�Ǿ����ϴ�.\n");
}

//���� �뿩
void rent_video()
{
	int i, video_id, cust_id;
	time_t timer;
	struct tm * t;

	for (i = 0; i < v_idx; i++)
	{
		if (video_info[i].is_rented == 0)
			printf("%d, %s, %s, %d, %s, %d, %d\n"
				, video_info[i].id
				, video_info[i].title
				, video_info[i].genre
				, video_info[i].charge
				, video_info[i].regist_date
				, video_info[i].is_rented
				, video_info[i].late_fee);
	}
	printf("�뿩�� ���� ��ȣ�� �Է��ϼ��� : ");
	scanf("%d", &video_id);
	video_info[video_id-1].is_rented = 1; //�뿩 ǥ��

	for (i = 0; i < c_idx; i++)
	{
		printf("%d, %s, %s, %s, %s\n"
			, customer_info[i].id
			, customer_info[i].name
			, customer_info[i].ssn
			, customer_info[i].phone
			, customer_info[i].address);
	}

	printf("�� ��ȣ�� �Է��ϼ��� : ");
	scanf("%d", &cust_id);

	rent.id = rent_id++; //�뿩id
	rent.video_id = video_info[video_id-1].id; //���� ������ ���� ��ȣ
	rent.cust_id = cust_id; //����ȣ
	//rent.rent_date = timer = time(NULL); //�뿩����(���� �������� �ʷ� ȯ���Ͽ� ������ ��Ÿ��)
	rent.rent_date = timer = time(NULL) - 691200; //�뿩����(�׽�Ʈ�� ���� 8�������� �ð��� ������)
	rent.ret_due_date = timer + 604800; //�ݳ� ��������
	rent.is_returned = 0; //1.�ݳ��Ϸ�, 0.�뿩��
	rent.charge = video_info[video_id-1].charge; //�뿩��

	t = localtime(&timer); //�ð����� �Լ�

	system("cls");
	printf("�뿩ID : %d | ���� ��ȣ : %d | ����ȣ : %d | %d-%d-%d | �뿩���� : %d | �뿩�� : %d\n"		
		, rent.id
		, rent.video_id
		, rent.cust_id
		, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday
		, rent.is_returned
		, rent.charge);
}

//���� ���� �˻����� �������� ã��
int search_video()
{
	int i;
	char title[30];
	printf("���� : ");
	scanf("%s", &title);

	for (i = 0; i < c_idx; i++)
	{
		if (strcmp(title, video_info[i].title) == 0)
			return i;
	}
	return -1;
}

//�ű� ���������� �Է¹޾Ƽ� ���Ͽ� ����
void new_video()
{
	FILE *v_fp = fopen("video_info.txt", "a");

	//����ü �迭�� �� ������ �Է� ����
	printf("���� ��ȣ : ");
	scanf("%d", &video_info[v_idx].id);
	printf("���� ���� : ");
	scanf("%s", &video_info[v_idx].title);
	printf("�帣 : ");
	scanf("%s", &video_info[v_idx].genre);
	printf("�뿩�� : ");
	scanf("%d", &video_info[v_idx].charge);
	printf("������� : ");
	scanf("%s", &video_info[v_idx].regist_date);
	video_info[v_idx].is_rented = 0; //����Ʈ(�뿩���� �ƴ�, �űԵ���̶� ����ȿ� ������)
	printf("��ü�� : ");
	scanf("%d", &video_info[v_idx].late_fee);

	fprintf(v_fp, "\n%d, %s, %s, %d, %s, %d, %d"
		, video_info[v_idx].id
		, video_info[v_idx].title
		, video_info[v_idx].genre
		, video_info[v_idx].charge
		, video_info[v_idx].regist_date
		, video_info[v_idx].is_rented
		, video_info[v_idx].late_fee);

	v_idx++;
	fclose(v_fp);
}

//��ȭ��ȣ �˻����� �������� ã��
int search_customer()
{
	int i;
	char phone[30];
	printf("��ȭ��ȣ : ");
	scanf("%s", &phone);

	for (i = 0; i < c_idx; i++)
	{
		if (strcmp(phone, customer_info[i].phone) == 0)
			return i;			
	}
	return -1;
}

//�ű� �������� �Է¹޾Ƽ� ���Ͽ� ����
void new_customer()
{
	FILE *c_fp = fopen("customer_info.txt", "a");

	//����ü �迭�� �� ������ �Է� ����
	printf("����ȣ : ");
	scanf("%d", &customer_info[c_idx].id);
	printf("���̸� : ");
	scanf("%s", &customer_info[c_idx].name);
	printf("�ֹε�Ϲ�ȣ : ");
	scanf("%s", &customer_info[c_idx].ssn);
	printf("��ȭ��ȣ : ");
	scanf("%s", &customer_info[c_idx].phone);
	printf("�ּ� : ");
	scanf("%s", &customer_info[c_idx].address);

	fprintf(c_fp, "\n%d, %s, %s, %s, %s"
		, customer_info[c_idx].id
		, customer_info[c_idx].name
		, customer_info[c_idx].ssn
		, customer_info[c_idx].phone
		, customer_info[c_idx].address);

	c_idx++;
	fclose(c_fp);
}

//�������� ���Ͽ��� �Է¹޴´�.
void input_customer()
{
	FILE *c_fp = fopen("customer_info.txt", "r"); //���Ͽ� ���� ������ �о��
	char line[150]; //�� ���ξ� �о��
	char *ptr;
	int word_cnt; //�޸� �������� �ܾ �ڸ�

	while (fscanf(c_fp, "%s", line) > 0) //�о�� �������� ������ int������ return �ϰԵ�
	{
		word_cnt = 0;
		//printf("%s\n", line);
		ptr = strtok(line, ","); //�޸� ������ �����ؼ� �߶�
		while (ptr != NULL)
		{
			word_cnt++; //1.����ȣ 2.���̸� 3.�ֹε�Ϲ�ȣ...(���������� ����)
			switch (word_cnt)
			{
			case 1: //int id
				customer_info[c_idx].id = atoi(ptr); //���ڿ� ���ڷ� ��ȯ
				break;
			case 2: //char name
				strcpy(customer_info[c_idx].name, ptr);
				break;
			case 3: //char ssn
				strcpy(customer_info[c_idx].ssn, ptr);
				break;
			case 4: //char phone
				strcpy(customer_info[c_idx].phone, ptr);
				break;
			case 5: //char address
				strcpy(customer_info[c_idx].address, ptr);
				break;
			}
			//printf("%s\n", ptr);
			ptr = strtok(NULL, ",");
		}
		c_idx++; //������ ����� ���� ����
	}
	fclose(c_fp);
}

//���������� ���Ͽ��� �Է¹޴´�.
void input_video()
{
	FILE *v_fp = fopen("video_info.txt", "r"); //���Ͽ� ���� ������ �о��
	char line[150]; //�� ���ξ� �о��
	char *ptr;
	int word_cnt; //�޸� �������� �ܾ �ڸ�

	while (fscanf(v_fp, "%s", line) > 0) //�о�� �������� ������ int������ return �ϰԵ�
	{
		word_cnt = 0;
		//printf("%s\n", line);
		ptr = strtok(line, ",");
		while (ptr != NULL)
		{
			word_cnt++;
			switch (word_cnt)
			{
			case 1: //int id
				video_info[v_idx].id = atoi(ptr); //���ڿ� ���ڷ� ��ȯ
				break;
			case 2: //char title
				strcpy(video_info[v_idx].title, ptr);
				break;
			case 3: //char genre
				strcpy(video_info[v_idx].genre, ptr);
				break;
			case 4: //int charge
				video_info[v_idx].charge = atoi(ptr); //���ڿ� ���ڷ� ��ȯ
				break;
			case 5: //char regist_date
				strcpy(video_info[v_idx].regist_date, ptr);
				break;
			case 6:  //int is_rented
                video_info[v_idx].is_rented = atoi(ptr);
                break;
            case 7:  //int late_fee
                video_info[v_idx].late_fee = atoi(ptr);
                break;
			}
			//printf("%s\n", ptr);
			ptr = strtok(NULL, ",");
		}
		v_idx++; //�������� ����� ���� ����
	}
	fclose(v_fp);
}