#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
/*
0. 유저 인터페이스 구현
1. 신규 고객 등록
2. 고객조회
3. 신규 비디오 등록
4. 비디오 조회
5. 비디오 대여
6. 비디오 반납
7. 비디오 연체 처리
*/
typedef struct _customer {
	int id; //고객번호
	char name[20]; //고객이름
	char ssn[14]; //주민등록번호
	char phone[12]; //전화번호
	char address[50]; //주소
} CUSTOMER; //고객정보 구조체

typedef struct _video {
	int id; //비디오 번호
	char title[20]; //비디오 제목
	char genre[10]; //장르
	int charge; //대여료
	char regist_date[9]; //등록일자
	int is_rented; //1: 대여중, 0: 대여중이 아님
	int late_fee; //1일 연체료
} VIDEO; //비디오정보 구조체

typedef struct _rent_info {
	int id; //대여 번호
	int video_id; //비디오 번호
	int cust_id; //고객번호
	int rent_date; //대여 일자
	int ret_due_date; //반납예정 일자
	int ret_date; //반납 일자
	int is_returned; //1: 반납완료, 0: 대여중
	int total_late_fee; //총 연체료
	int charge; //대여료(대여할 당시의)
} RENT_INFO; //대여, 반납 정보 구조체

void input_customer();
void input_video();
void new_customer();
int search_customer();
void new_video();
int search_video();

CUSTOMER customer_info[200];
int c_idx = 0; //고객정보 저장된 개수
VIDEO video_info[200];
int v_idx = 0; //비디오정보 저장된 개수

int main()
{
	int i, idx, sel = 1;

	input_customer(); //고객정보 입력
	input_video(); //비디오정보 입력

	while(sel!=0)
	{
		system("cls");
		printf("<비디오 대여관리 프로그램>\n");
		printf("1. 신규 고객 등록\n");
		printf("2. 고객 정보 조회\n");
		printf("3. 전체 고객 정보 조회\n");
		printf("4. 신규 비디오 등록\n");
		printf("5. 비디오 정보 조회\n");
		printf("6. 전체 비디오 정보 조회\n");
		printf("0. 종료\n");
		printf("---------------------\n");
		printf("항목을 선택하세요 : ");
		scanf("%d", &sel);

		switch (sel)
		{
		case 1:
			new_customer();
			break;

		case 2:
			idx = search_customer();
			if (idx == -1)
			{
				printf("일치하는 고객이 없습니다.\n");
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
			new_video();
			break;

		case 5:
			idx = search_video();
			if (idx == -1)
			{
				printf("일치하는 비디오가 없습니다.\n");
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
		}
		_getch();
	}
	
	for (i = 0; i < c_idx; i++)
	{
		printf("%d, %s, %s, %s, %s\n"
			, customer_info[i].id
			, customer_info[i].name
			, customer_info[i].ssn
			, customer_info[i].phone
			, customer_info[i].address);
	}

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
	return 0;
}

//비디오 제목 검색으로 고객정보를 찾음
int search_video()
{
	int i;
	char title[30];
	printf("제목: ");
	scanf("%s", &title);

	for (i = 0; i < c_idx; i++)
	{
		if (strcmp(title, video_info[i].title) == 0)
			return i;
	}
	return -1;
}

//신규 비디오정보를 입력받아서 파일에 저장
void new_video()
{
	FILE *v_fp = fopen("video_info.txt", "a");

	//구조체 배열에 고객 정보를 입력 받음
	printf("비디오 번호 : ");
	scanf("%d", &video_info[v_idx].id);
	printf("비디오 제목 : ");
	scanf("%s", &video_info[v_idx].title);
	printf("장르 : ");
	scanf("%s", &video_info[v_idx].genre);
	printf("대여료 : ");
	scanf("%d", &video_info[v_idx].charge);
	printf("등록일자 : ");
	scanf("%s", &video_info[v_idx].regist_date);
	video_info[v_idx].is_rented = 0; //디폴트(대여중이 아님, 신규등록이라 매장안에 존재함)
	printf("연체료 : ");
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

//전화번호 검색으로 고객정보를 찾음
int search_customer()
{
	int i;
	char phone[30];
	printf("전화번호: ");
	scanf("%s", &phone);

	for (i = 0; i < c_idx; i++)
	{
		if (strcmp(phone, customer_info[i].phone) == 0)
			return i;			
	}
	return -1;
}

//신규 고객정보를 입력받아서 파일에 저장
void new_customer()
{
	FILE *c_fp = fopen("customer_info.txt", "a");

	//구조체 배열에 고객 정보를 입력 받음
	printf("고객번호 : ");
	scanf("%d", &customer_info[c_idx].id);
	printf("고객이름 : ");
	scanf("%s", &customer_info[c_idx].name);
	printf("주민등록번호 : ");
	scanf("%s", &customer_info[c_idx].ssn);
	printf("전화번호 : ");
	scanf("%s", &customer_info[c_idx].phone);
	printf("주소 : ");
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

//고객정보를 파일에서 입력받는다.
void input_customer()
{
	FILE *c_fp = fopen("customer_info.txt", "r");
	char line[150];
	char *ptr;
	int word_cnt; //콤마 구분으로 단어를 자름

	while (fscanf(c_fp, "%s", line) > 0)
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
				customer_info[c_idx].id = atoi(ptr);
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
		c_idx++;
	}
	fclose(c_fp);
}

//비디오정보를 파일에서 입력받는다.
void input_video()
{
	FILE *v_fp = fopen("video_info.txt", "r");
	char line[150];
	char *ptr;
	int word_cnt; //콤마 구분으로 단어를 자름

	while (fscanf(v_fp, "%s", line) > 0)
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
				video_info[v_idx].id = atoi(ptr); //문자열 숫자로 변환
				break;
			case 2: //char title
				strcpy(video_info[v_idx].title, ptr);
				break;
			case 3: //char genre
				strcpy(video_info[v_idx].genre, ptr);
				break;
			case 4: //int charge
				video_info[v_idx].charge = atoi(ptr); //문자열 숫자로 변환
				break;
			case 5: //char regist_date
				strcpy(video_info[v_idx].regist_date, ptr);
				break;
			}
			//printf("%s\n", ptr);
			ptr = strtok(NULL, ",");
		}
		v_idx++;
	}
	fclose(v_fp);
}