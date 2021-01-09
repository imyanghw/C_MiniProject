#include<stdio.h>

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
	char regist_data[9]; //등록일자
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

int main()
{
	return 0;
}