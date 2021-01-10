#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

CUSTOMER customer_info[200];
int c_idx = 0; //고객정보 저장된 개수
VIDEO video_info[200];
int v_idx = 0; //비디오정보 저장된 개수


int main()
{
	int i;

	input_customer(); //고객정보 입력
	input_video(); //비디오정보 입력

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