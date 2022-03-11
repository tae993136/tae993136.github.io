/*POSproject.c*/
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>     //getpass()함수 사용을 위한 헤더파일추가
#include <math.h>


void login();           //로그인
void logout();          //로그아웃
void print_menu();      //메뉴
void stock_mng();       //재고 관리
void expir_chk();       //유통기한 확인
void sell();            //계산
void wage();            //매출과 급여
void searching();       //검색
void alert();           //비상벨
void insert_snack();    //제품 추가 삽입
/*제품 정보 입력*/
void add(const char *,const char*, const int,const int,const char *, const char *);
void delete();          //선택한 제품 삭제
/*제품 삽입 메뉴*/
void insert(const char * ,const char *,const char*, const int,const int,const char *, const char *);

int login_time = 0;     //로그인 시간
int logout_time = 0;    //로그아웃 시간
int bank = 100000;      //매출계산을 위한 변수

typedef struct Snack            //상품 구조체 선언
{
    char firm[32];            //회사
    char snack_name[32];      //과자 이름
    int price;                //가격
	int stock;                //재고
    char expir_date[10];      //유통기한
    char make_date[10];       //제조일
    struct Snack * next;      //다음 제품
    unsigned int cnt;         //제품 종류의 개수 저장
}snack;
typedef snack* PTR;           //구조체 포인터
static PTR header = NULL;     //첫 번째 제품
static PTR ptrSnack = NULL;   //이후 제품
int main()
{
    login();        //로그인 함수 호출
    return 0;
}
/*초기 제품정보 입력*/
void add(const char * firm,const char * name,const int price,const int stock,
        const char* ex_date,const char* ma_date)
{
    if(header == NULL) //처음 입력할 때
    {
        PTR ptr_first_snack = (PTR)malloc(sizeof(snack));//첫 번째 제품 구조체 동적할당
        strcpy(ptr_first_snack->firm, firm);             //회사명 저장
        strcpy(ptr_first_snack->snack_name,name);        //제품 이름 저장
        ptr_first_snack->price = price;                  //가격 저장
        ptr_first_snack->stock = stock;                  //재고 저장
        strcpy(ptr_first_snack->expir_date, ex_date);    //유통기한 저장
        strcpy(ptr_first_snack->make_date, ma_date);     //제조일자 저장

        ptr_first_snack -> next = NULL;                  //끝 노드
        header = ptr_first_snack;                        //header에 첫번째 노드 주소 참조 
        header -> cnt =0;                                //제품 개수 초기화
        ptrSnack = ptr_first_snack;                      //다음 제품 추가를 위한 첫번째 주소 참조
        ++header->cnt;                                   //제품 개수 증가
    }
    else
    {
        PTR ptr_new_snack = (PTR)malloc(sizeof(snack));  //두 번째 이후의 제품 구조체 할당
        strcpy(ptr_new_snack->firm, firm);               
        strcpy(ptr_new_snack->snack_name,name);
        ptr_new_snack->price = price;
        ptr_new_snack->stock = stock;
        strcpy(ptr_new_snack->expir_date, ex_date);
        strcpy(ptr_new_snack->make_date, ma_date);

        ptr_new_snack->next = NULL;                       //새 노드를 끝 노드로 설정
        ptrSnack -> next = ptr_new_snack;                 //ptrSnack의 next에 새 노드의 주소 참조
        ++header->cnt;                                    //제품 개수 감소
        ptrSnack = ptrSnack->next;                        //다음 노드 참조
    }

}
/* 중간에 삽입할 제품 구조체 구현 */
void insert(const char* _where,const char * firm, const char* name,
        const int price,const int stock, const char* ex_date, const char* ma_date)
{
    if(header == NULL)                                     
    {
        puts("데이터가 없습니다.");
        return;
    }
    PTR temporary_node =(PTR)malloc(sizeof (snack)); //새 제품 저장 노드
    strcpy(temporary_node->firm, firm);
    strcpy(temporary_node->snack_name,name);
    temporary_node->price = price;
    temporary_node->stock = stock;
    strcpy(temporary_node -> expir_date, ex_date);
    strcpy(temporary_node->make_date, ma_date);

    temporary_node->next = NULL;
    PTR current_node = NULL;                         //삽입 위치
    PTR search = header;

    if(!strcmp(search->snack_name,_where))            //첫 번째 노드 뒤에 삽입
        current_node = search;
    else
    {
        while(strcmp(search->snack_name,_where) !=0) //두 번째이후의 노드 뒤에 삽입
        {
            search = search->next;
            current_node = search;                  //지정한 위치 다음에 삽입
        }
    }
    if(current_node == NULL) return ;               //해당 문자열이 없을때
    temporary_node->next = current_node->next;      //새 제품 뒤에 다음 노드 참조
    current_node->next = NULL;                      //다음 삽입 위치 초기화
    current_node->next = temporary_node;            //다음 위치에 새로운 제품 참조
    ++header->cnt;                                  //개수 증가

}
/*선택한 제품 삭제*/
void delete()                                       
 {
    char name[10]={0,};             //삭제할 제품명
    printf("삭제할 제품 입력: ");
    scanf("%s",name);


    if(header == NULL)
    {
        puts("데이터 노드가 없습니다.");
        return;
    }
    PTR temporary_node = NULL;
    PTR previous_ptr_node = NULL;   //이전 노드
    PTR next_ptr_node = NULL;       //다음 노드
    PTR search = header;            //탐색 노드

    while(strcmp(search->snack_name, name) != 0) //이름이 같으면 실행
        {
            previous_ptr_node = search; // 이전 노드에 탐색노드 참조
            search = search->next;      // 탐색 노드 업데이트
            if(search == NULL) return ; //문자열이 없을때 리턴
        }
    temporary_node = search;            //업데이트된 탐색노드
    next_ptr_node = temporary_node->next; //다음 노드
    temporary_node->next = NULL;
    previous_ptr_node -> next = next_ptr_node; //이전 노드에 다음노드 참조
    free(temporary_node); // heap메모리삭제
    --header->cnt;        //개수 감소
    
}
void login()        //로그인 함수 구현
{
    time_t t = time(NULL);          //time()함수 호출하여 현재 시간, 날짜를 저장
    struct tm tm = *localtime(&t);  //localtime()함수를 호출하여 포맷 변환
    login_time = tm.tm_hour;        //로그인 시간 저장
    char my_id[]="jin";             //입력받은 id와 비교할 id
    char my_pass[]="qwe123";        //입력받은 비밀번호와 비교할 비밀번호
    char input_id[20] = {0,};       //입력받을 id
    char * input_pass = {0,};       //입력받을 비밀번호
    char input_firm[20] = {0,};     //회사명
    char input_snack[20] = {0,};    //제품명
    int input_price = 0;            //가격
    int input_stock = 0;            //재고
    char input_ex_date[10] = {0,};  //유통기한
    char input_ma_date[10] = {0,};  //제조일

    printf("ID입력: ");
    scanf("%s",input_id);           //id입력

    input_pass = getpass("비밀번호 입력 : "); //getpass()함수를 사용하여 비밀번호를 보이지 않게 입력

    if(!strcmp(my_pass, input_pass)&&!strcmp(my_id,input_id))
    {
        printf("출근시간 %d시 %d분\n",login_time,tm.tm_min);//문자열을 비교하여 
        
        for(int i=0; i < 3; i++) // 최초 3개의 제품 입려
        {
            printf("상품의 회사, 이름, 가격, 재고, 유통기한, 제조일자를 입력하세요.\n");
            scanf("%s %s %d %d %s %s",input_firm,input_snack,&input_price,&input_stock,
                    input_ex_date,input_ma_date);
            add(input_firm,input_snack,input_price,input_stock,
                    input_ex_date,input_ma_date);           //add함수 호출
        }
        

        print_menu();                 //일치할 시 출근시간을 출력하고 메뉴 호출
    }
    else
    { 
        printf("ID 또는 비밀번호를 확인하십시오.\n");
        login();        //불일치 시 재 입력을 위해 로그인 재호출
    }
    
    
   }

void logout()           //로그아웃 함수 구현
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    logout_time = tm.tm_hour+6;//현재시간에 6시간을 더한 값을 로그아웃 시간에 저장
    int work_time = logout_time-login_time;//근로시간 계산
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
    scanf("%d",&num);//switch case사용을 위해 숫자를 입력
    printf("\n");

    switch(num)     //숫자입력시해당하는 함수 호출 
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
    int header_cnt = header->cnt; //물품 개수 저장
    
    printf("---1. 물품관리---------------------------------------\n\n");
    printf("1.1 재고확인\n\n");
    printf("1.2 유통기한 확인\n\n");
    printf("1.3 물품 List\n\n");
    printf("1.4 물품 추가\n\n");
    printf("1.5 물품 삭제\n\n");
    printf("0. 이전 메뉴\n\n");
    printf("-----------------------------------------------------\n");
    printf("메뉴 번호 입력 : ");
    scanf("%d",&num);
    
    PTR mole = NULL;
    mole = header;  //탐색
    switch(num)     
    {
        case 0:         //메뉴호출
            print_menu();
            break; 
        case 1:         //재고 확인
            printf("***재고 확인******************************************\n\n");
            for(int i = 0;i<header_cnt;++i) //물품 개수만큼 반복
            {
                printf("%s %d개\n", mole->snack_name,mole->stock);    //과자의 이름과 재고 출력
                mole = mole -> next;
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
            for(int i = 0;i<header_cnt;++i)
            {
                printf("%s ", mole->snack_name);

                mole = mole -> next;
            }
            printf("\n");
            stock_mng();
            break;
        case 4:
            insert_snack();
            stock_mng();
            break;
        case 5:
            delete();
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
    int today_year = tm.tm_year-100;   //오늘 날짜저장
    int today_month = tm.tm_mon+1;
    int today_day = tm.tm_mday;
    int today = (today_year*10000)+(today_month*100)+today_day;//현재 날짜를 6자리로 변환
    int header_cnt = header->cnt;
    int i = 0;
    
    printf("%d %d\n",today, atoi(header->expir_date)); //today와 유통기한 비교 
    PTR mole = NULL;
    mole = header;
    for(int i = 0; i < header_cnt; i++)
    {
        if(today > atoi(mole->expir_date))   //연도비교
        {
            printf("%s의 유통기한은 : %c%c년 %c%c월 %c%c일! 폐기하세요\n",mole->snack_name,
                    mole->expir_date[0],mole->expir_date[1],
                    mole->expir_date[2],mole->expir_date[3],
                    mole->expir_date[4],mole->expir_date[5]
                  );
        }
        else //유통기한이 지나지 않은 품목 출력
        {        
            printf("%s의 유통기한은 : %c%c년 %c%c월 %c%c일!\n",mole->snack_name,
                    mole->expir_date[0],mole->expir_date[1],
                    mole->expir_date[2],mole->expir_date[3],
                    mole->expir_date[4],mole->expir_date[5]
                  );
        }
        mole = mole -> next;
    }
}

void insert_snack()
{   
     
    char input_where[20] = {0,};
    char input_firm[20] = {0,};
    char input_snack[20] = {0,};
    int input_price = 0;
    int input_stock = 0;
    char input_ex_date[10] = {0,};
    char input_ma_date[10] = {0,};

    printf("삽입할 제품의 정보를 입력하세요.\n");
    scanf("%s %s %d %d %s %s",input_firm,input_snack,&input_price,&input_stock,
          input_ex_date,input_ma_date);
    printf("삽입할 위치를 입력하세요.\n");
    scanf("%s",input_where);
    insert(input_where,input_firm,input_snack,input_price,input_stock,
                    input_ex_date,input_ma_date);
    int header_cnt = header->cnt;
    header_cnt;
    PTR mole = NULL;
    mole = header;
    for(int i = 0;i<header_cnt;++i)
        {
            printf("%d번 제품%s ",i+1, mole->snack_name);

            mole = mole -> next;
        }
    printf("\n");

}

void sell()     //물품 계산
{
   
    char buy[10][20]={0,};      //구매 물품을 저장
    int cnt =0;                 //구매 갯수 저장
    int total = 0;              //총 금액 저장
    int pay = 0;                //지불금액 저장
    int n = 0;
    int header_cnt = header->cnt;
    
    srand(time(NULL));          //시드값 지정
    int buy_cnt=rand()%4+4;     //4~7사이의 값 저장

    
    for(int i=0; i<buy_cnt;i++) //4~7회 반복
    {
        printf("구매:");
        scanf("%s",buy[i]);     //구매 물품 입력
        ++cnt;                  //구매 갯수 증가
    }


    printf("손님 A가 %d개 구매 ",cnt); //구매한 갯수출력

    PTR search = NULL;
    for(int i=0; i<7; i++)
    {
        search = header;

        for(int j=0; j<header_cnt; j++)
        {
            if(!strcmp(buy[i],search->snack_name))//입력 문자열과 Snack구조체
            {                                      //이름 비교
                if(search->stock!=0)                 //재고가 있으면 실행
                {
                    total+=search->price;            //총금액 계산
                    search->stock=search->stock-1;     //재고 감소
                }
                
            }
            search=search->next;
        }
    }

    search = header;
    for(int i = 0;i < header_cnt ;i++) 
    {
        if(search->stock==0)
            printf("\n%s의 재고가 부족합니다.\n",search -> snack_name);
        search = search -> next;
    }
     
    pay=total+(rand()%6+5)*100;             //총 금액에 무작위 값을 더해서 지불 
    printf("총 가격:%d\t지불:%d  잔돈: %d\n",total,pay,pay-total);
    
    bank += total;      //매출에 총 금액 더해 줌
    printf("매출 : %d\n",bank);

    printf("1번 : 이전메뉴 2번 : 계산\n");//메뉴이동
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
    printf("~~~오늘의 수입~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("매출 : %d \t급여 : %d\n",bank, 4*9160);//4시간 일했다고 가정
    printf("\n\n");
    print_menu();
}

void searching()        //물품 검색
{
    char search[][20]={0,};//검색어 저장
    int header_cnt = header->cnt;
    PTR mole = NULL;
    mole = header;

    printf("---물품 검색---------------------------------- \n");

    printf("물품 검색 : ");
    for(int i=0; i<1; i++)
        scanf("%s",search[i]);
    
    for(int i=0; i<header_cnt; i++)
        {
           /*검색어와 물품이름 비교하여 일치하는 품목 출력*/
            if(!strcmp(search[0],mole->snack_name))
            {
                printf("%s %s %d원 재고%d개 \n유통기한 %c%c년 %c%c월 %c%c일  \n제조일자 %c%c년 %c%c월 %c%c일",
                               mole->firm,
                               mole->snack_name,mole->price,
                               mole->stock,
                               mole->expir_date[0],mole->expir_date[1],
                               mole->expir_date[2],mole->expir_date[3],
                               mole->expir_date[4],mole->expir_date[5],
                               mole->make_date[0],mole->make_date[1],
                               mole->make_date[2],mole->make_date[3],
                               mole->make_date[4],mole->make_date[5]
                      );                
           }
            mole = mole -> next;
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


