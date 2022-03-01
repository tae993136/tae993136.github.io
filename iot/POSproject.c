/*POSproject.c*/
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>		//비밀번호 보안을 위한 헤더파일


void login();           //로그인
void logout();          //로그아웃
void print_menu();      //메뉴
void stock_mng();       //재고 관리
void expir_chk();       //유통기한 확인
void sell();            //계산
void wage();            //매출과 급여
void searching();       //검색
void alert();           //비상벨

int login_time = 0;     //로그인 시간
int logout_time = 0;    //로그아웃 시간
int bank = 100000;      //매출계산을 위한 변수

struct Snack            //상품 구조체 선언
{
    char firm[32];      //회사
    char snack_name[32];//과자 이름
    int price;          //가격
	int stock;          //재고
    int ex_year;        //유통기한 년
    int ex_mon;         //유통기한 월
    int ex_day;         //유통기한 일
    int ma_year;        //제조 년
    int ma_mon;         //제조 월
    int ma_day;         //제조 일
}snack[7] = {           //모든 함수에서 접근 가능하도록 전역공간에 초기화
        {"농심","새우깡",1000,9,2023,7,30,2021,12,1},
        {"해태","오예스",2000,30,2021,12,31,2021,1,23},
        {"오리온","초코파이",3000,30,2023,1,1,2022,2,3},
        {"크라운","쿠크다스",1500,30,2022,1,31,2021,11,11},
        {"롯데","마가렛트",4000,30,2022,2,26,2022,1,3},
        {"크라운","크라운산도",2500,30,2022,3,3,2021,1,3},
        {"롯데","빼빼로",1500,30,2022,4,30,2022,1,12}
    };


int main()
{
    login();        //로그인 함수 호출
    return 0;
}

void login()        //로그인 함수 구현
{
    time_t t = time(NULL);          		//time()함수 호출하여 현재 시간, 날짜를 저장
    struct tm tm = *localtime(&t);  		//localtime()함수를 호출하여 포맷 변환
    login_time = tm.tm_hour;        		//로그인 시간 저장
    char my_id[]="jin";             		//입력 id와 비교할 id
    char my_pass[]="qwe123";      			//입력 비밀번호와 비교할 비밀번호
    char input_id[20] = {0,};      			//입력받을 id
    char * input_pass = {0,};    			//입력받을 비밀번호
    printf("ID입력: ");
    scanf("%s",input_id);           		//id입력
	input_pass = getpass("P.W입력:");		//getpass()함수 사용,비밀번호 보안	
   
    if(!strncmp(my_pass, input_pass,strlen(input_pass))&&!strcmp(my_id,input_id))
    {
        printf("출근시간 %d시 %d분\n",login_time,tm.tm_min);//문자열을 비교하여 
        print_menu();                				 //일치할 시 출근시간을 출력하고 메뉴 호출
    }
    else
    { 
        printf("ID 또는 비밀번호를 확인하십시오.\n");
        login();       						 //불일치 시 재 입력을 위해 로그인 재호출
    }
    
    
   }

void logout()           //로그아웃 함수 구현
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    logout_time = tm.tm_hour+6;			//현재시간에 6시간을 더한 값을 로그아웃 시간에 저장
    int work_time = logout_time-login_time;		//근로시간 계산
    printf("%d월 %d일 %d시 %d분 로그아웃\n",tm.tm_mon+1,tm.tm_mday,
            tm.tm_hour+6, tm.tm_min);
    printf("%d시간근무, %d원 벌었다!!\n", work_time,work_time*9160);
    exit(0);            //프로그램 종료
}

void print_menu()       //메뉴 출력 구현
{
    int num = 0;
    printf("===메뉴==============================================\n\n");
    printf("1.물품 관리\t2. 물건 계산\t3. 매출과 급여\n\n");
    printf("4.물건 검색\t5. 비상벨\t6. 로그아웃\n\n");
    printf("=====================================================\n");

    printf("메뉴 번호 입력 : ");
    scanf("%d",&num);
    printf("\n");

    switch(num)     //번호입력시해당하는 함수 호출 
    {
        case 1:
            stock_mng();
            break; 
        case 2:
            sell();
            break;
        case 3:
            wage();
            break;
        case 4:
            searching();
            break;
        case 5:
            alert();
            break;
        case 6:
            logout();
            break;
        default:
             print_menu();  //1~6외의 번호 입력시 다시 메뉴호출
    }

}

void stock_mng()        //재고관리 구현
{
    int num = 0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    printf("---1. 물품관리---------------------------------------\n\n");
    printf("1.1 재고확인\n\n");
    printf("1.2 유통기한 확인\n\n");
    printf("1.3 물품 List\n\n");
    printf("0. 이전 메뉴\n\n");
    printf("-----------------------------------------------------\n");

    printf("메뉴 번호 입력 : ");
    scanf("%d",&num);

    switch(num)     
    {
        case 0:         //메뉴호출
            print_menu();
            break; 
        case 1:         //재고 확인
            printf("***재고 확인******************************************\n\n");
            for(int i = 0;i<sizeof(snack)/sizeof(snack[0]);++i)
            {
                printf("%s %d개\n", snack[i].snack_name,snack[i].stock);
            }
            printf("\n");
            stock_mng();        //재고관리 호출
            break;
        case 2:
            expir_chk();        //유통기한 호출
            stock_mng();        //재고관리 호출
            break;
        case 3:                 //물품종류 확인
             
            printf("---물품List------------------------------------------\n\n");
            for(int i = 0;i<7;++i)
            {
                printf("%s ", snack[i].snack_name);
            }
            printf("\n");
            stock_mng();
            break;
        default:
            stock_mng();
    }

}

void expir_chk()            //유통기한 확인
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int today_year = tm.tm_year+1900;   //오늘 날짜저장
    int today_month = tm.tm_mon+1;
    int today_day = tm.tm_mday;

    for(int i = 0; i < 7; i++)
    {
        if(today_year > snack[i].ex_year)   //연도비교
        {
            printf("%s의 유통기한은 : %d년 %d월 %d일! 폐기하세요\n",
					snack[i].snack_name,snack[i].ex_year,snack[i].ex_mon,
					snack[i].ex_day);
        }
        /*연도가 같을 때 월 비교*/
        else if(today_year == snack[i].ex_year&&today_month>snack[i].ex_mon) 
        {  
			printf("%s의 유통기한은 : %d년 %d월 %d일! 폐기하세요\n",
					snack[i].snack_name,snack[i].ex_year,snack[i].ex_mon,
					snack[i].ex_day);
        }
        /*연도와 월이 같을 때 일 비교*/
        else if(today_year ==snack[i].ex_year&&today_month==snack[i].ex_mon&&today_day > snack[i].ex_day)
        {
            printf("%s의 유통기한은 : %d년 %d월 %d일! 폐기하세요\n",
					snack[i].snack_name,snack[i].ex_year,snack[i].ex_mon,snack[i].ex_day);
        }
        else 	//유통기한이 지나지 않은 품목 출력
             printf("%s의 유통기한은 : %d년 %d월 %d일! \n", 
					 snack[i].snack_name,snack[i].ex_year,snack[i].ex_mon,snack[i].ex_day);
        }
    }



void sell()     //물품 계산
{
   
    char buy[10][20]={0,};      //구매 물품을 저장
    int cnt =0;                 //구매 갯수 저장
    int total = 0;              //총 금액 저장
    int pay = 0;                //지불금액 저장
    int n = 0;

    
    srand(time(NULL));          //시드값 지정
    int buy_cnt=rand()%4+4;     //4~7사이의 값 저장

    
    for(int i=0; i<buy_cnt;i++) //4~7회 반복
    {
        printf("구매:");
        scanf("%s",buy[i]);     //구매 물품 입력
        ++cnt;                  //구매 갯수 증가
    }


    printf("손님 A가 %d개 구매 ",cnt);
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(!strncmp(buy[i],snack[j].snack_name,2))	//입력 문자열과 Snack구조체
            {                                         	//이름 비교
                if(snack[j].stock!=0)                 	//재고가 있으면 실행
                {
                    total+=snack[j].price;          	//총금액 계산
                    snack[j].stock=snack[j].stock-1;	//재고 감소
                }               
            }
        }

    }
    pay=total+(rand()%6+5)*100;             //총 금액에 무작위 값을 더해서 지불 
    printf("총 가격:%d\t지불:%d  잔돈: %d\n",total,pay,pay-total);
    
    bank += total;      //매출에 총 금액 더해 줌
    printf("매출 : %d\n",bank);

    printf("1번 : 이전메뉴 2번 : 계산\n");	//메뉴이동
    printf("insert :");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
        print_menu();
        break;
    case 2:
        sell();
        break;
    default:
        print_menu();
    }   

}

void wage() //매출과 급여
{
    printf("\n");
    printf("~~~오늘의 수입~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("매출 : %d \t급여 : %d\n",bank, 4*9160);	//4시간 일했다고 가정
    printf("\n\n");
    print_menu();
}

void searching()        //물품 검색
{
    char search[][20]={0,};	//검색어 저장
    printf("---물품 검색-----------------------------------------\n");

    printf("물품 검색 : ");
    for(int i=0; i<1; i++)
        scanf("%s",search[i]);
    
    for(int i=0; i<10; i++)
        {
            /*검색어와 물품이름 비교하여 일치하는 품목 출력*/
            if(!strncmp(search[0],snack[i].snack_name,2))
            {
                printf("%s %s %d원 재고%d개 \n유통기한 %d년 %d월 %d일  \n제조일자 %d년 %d월 %d일",
						snack[i].firm,snack[i].snack_name,snack[i].price,
                        snack[i].stock,snack[i].ex_year,snack[i].ex_mon,
                        snack[i].ex_day,snack[i].ma_year,snack[i].ma_mon,
                        snack[i].ma_day);

           }
        }
     printf("\n\n");

     print_menu();
        
}

void alert() //비상벨 작동
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("@@@비상벨 작동@@@\a\n");
    printf("작동시간 %d시 %d분\n",tm.tm_hour,tm.tm_min);    //작동시간 출력

    print_menu();
}


