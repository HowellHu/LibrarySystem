#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

//����ϵͳ�û���Ϣ�ṹ
struct sysuser
{
    char username[20];
    char password[8];
};

//����ͼ����Ϣ�ṹ
struct book
{
    int number;     //���
    char name[30];  //����
    char category[10];  //���
    int lent;       //�Ƿ������ѽ�Ϊ1��δ��Ϊ0��
    int year;       //���ʱ�䡪����
    int month;      //���ʱ�䡪����
    int day;        //���ʱ�䡪����
    struct book *next;
};

struct time
{
    int year;
    int month;
    int day;
};

int login();
int checkUserValid(struct sysuser *user);
void save_to_file(FILE *fp, struct book *head);
struct book *search_by_number(struct book *head, int number);
int search_by_category(struct book *head, char *category);

//������
//���Գɹ�
void print_main_title()
{
    printf("================================================================================");
    printf("                                                                                ");
    printf("                                                                                ");
    printf("                                                                                ");
    printf("                           ��ӭʹ��ͼ�����ϵͳv0.1                             ");
    printf("                                   ����ԭ��                                     ");
    printf("                                                                                ");
    printf("                                                                                ");
    printf("================================================================================");
}

struct book *insert_list(struct book *head, struct book *element)
{
    struct book *p;
    p = head;
    while(p -> next != NULL)
        p = p -> next;
    p -> next = element;
    element -> next = NULL;
    return head;
};

//ע���˺�
//����ͨ������Ҫ�޸�
int create_user()
{
    struct sysuser su;
    FILE *fp;
create_loop:
    fp = fopen("user.txt", "a");
    if (fp == NULL) fopen("user.txt", "w");
    system("CLS");
    print_main_title();
    printf("\n\n");
    printf("                  �������µ��˺ţ����س�������");
    scanf("%s", su.username);
    printf("\n");
    printf("                  �������µ����룬���س�����\n");
    printf("         ����ĳ���Ϊ8λ��������ʹ��Ӣ���ַ������֣��Ҳ�����ʾ����Ļ�ϣ�");
    //scanf("%s", su.password);
    int i=0;
    while(i < 8&&(su.password[i]=getch())!='\r')
    {
        if(su.password[i]=='\b')
        {
            i--;
        }
        else
        {
            i++;
        }
    }
    su.password[i]='\0';
    fprintf(fp, "%s %s", su.username, su.password);
    fprintf(fp,"\n");
    fclose(fp);
    printf("                  ע��ɹ���\n\n");
    printf("                  ����������ص�¼�˵�...");
    char ch;
    ch = getch();
    system("cls");
    return 1;
}

//�����¼
//����ͨ������Ҫ�޸�
int login()
{
    struct sysuser su;
    char ch;
    int check = 0;
    system("CLS");
    print_main_title();
    printf("\n\n");
    printf("                       �������˺ţ����س���������");
    scanf("%s", su.username);
    printf("\n");
    printf("                       ���������룬���س���������\n");
    printf("                       �����벻����ʾ����Ļ��:");
    //scanf("%s", su.password);
    int i=0;
    while(i < 8&&(su.password[i]=getch())!='\r')
    {
        if(su.password[i]=='\b')
        {
            i--;
        }
        else
        {
            i++;
        }
    }
    su.password[i]='\0';
    //printf("\n���������:%s",su.password);


    if(checkUserValid(&su) == 1)
    {
        check = 1;
        printf("\n\n\n");
        printf("                       ��¼�ɹ���\n");
        printf("\n");
        printf("                       ��������������˵�...");
        ch = getch();
        system("cls");
    }

    else
    {
        printf("\n\n\n");
        printf("                       ���û������ڣ���˶Ժ����������ע�ᣡ\n");
        printf("                       ����������������Ա��ϵ\n");
        printf("                       ��������������˵�...");
        ch = getch();
        system("cls");
    }

    return check;
}

//�������û��Ϸ���
//����ͨ������Ҫ�޸�
int checkUserValid(struct sysuser *user)
{

    //�򿪴洢�û��˺�������ļ�
    FILE *user_file_p;

    user_file_p = fopen("user.txt","r");
    if (user_file_p == NULL) user_file_p = fopen("user.txt","w");

    char usr[30], usr_f[30], pwd[10];

    int check = 0;

    //��������׼�����ļ�У����û������ַ���
    strcpy(usr, user -> username);
    strcpy(pwd, user -> password);

    //���û����ո����롢\n�������ַ���usr���������ļ��м��ƥ��
    strcat(usr, " ");
    strcat(usr, pwd);
    strcat(usr, "\n");

    //���ļ��ж����û���Ϣ���ݣ������ж��Ƿ����
    while(feof(user_file_p) == 0)
    {
        fgets(usr_f, 30, user_file_p);
        if(strcmp(usr, usr_f) == 0)
        {
            check = 1;
            break;
        }
    }

    //�ر��ļ�
    if(fclose(user_file_p))
    {
        printf("Can not close the file!\n");
        exit(0);
    }

    return check;
}

//����ļ��Ƿ�Ϊ��
//�շ���0���ǿշ���1
//����ͨ������Ҫ�޸�
int check_void_file()
{
    FILE *fp;
    fp = fopen("library.txt", "r+");
    char ch;
    ch = fgetc(fp);
    fclose(fp);
    if (ch == EOF) return 0;
    return 1;
}

//���ļ��ж�ȡ����������
//����ͨ������Ҫ�޸�
struct book *make_linklist()
{
    FILE *fp;
    fp = fopen("library.txt", "r+");
    if (fp == NULL) printf("û��ͼ�飡");
    if (check_void_file() == 0)
    {
        printf("ͼ�����ݿ�Ϊ�գ�");
        return 0;
    }
    struct book *head;
    head = (struct book *)malloc(sizeof(struct book));
    head->next = NULL;
    struct book *p;
    p = head;
    char ch;
    while(!feof(fp))
    {
        struct book *new_book_init;
        new_book_init = (struct book *)malloc(sizeof(struct book));
        fscanf(fp, "%d", &new_book_init->number);
        ch = fgetc(fp);
        fscanf(fp, "%s", new_book_init->name);
        ch = fgetc(fp);
        fscanf(fp, "%s", new_book_init->category);
        ch = fgetc(fp);
        fscanf(fp, "%d", &new_book_init->lent);
        ch = fgetc(fp);
        fscanf(fp, "%d", &new_book_init->year);
        ch = fgetc(fp);
        fscanf(fp, "%d", &new_book_init->month);
        ch = fgetc(fp);
        fscanf(fp, "%d", &new_book_init->day);
        ch = fgetc(fp);
        new_book_init->next = NULL;

        p->next = new_book_init;
        p = p->next;
    }
    fclose(fp);
    return head;
}


//���������ļ��������ԭ�ļ�������
void override_to_file(struct book *head)
{
    FILE *fp;
    fp = fopen("library.txt", "w");
    struct book *p;
    p = head->next;
    while(p->next != NULL)
    {
        fprintf(fp, "%d ", p->number);
        fprintf(fp, "%s ", p->name);
        fprintf(fp, "%s ", p->category);
        fprintf(fp, "%d ", p->lent);
        fprintf(fp, "%d ", p->year);
        fprintf(fp, "%d ", p->month);
        fprintf(fp, "%d", p->day);
        fprintf(fp, "\n");
        p = p->next;
    }
    fclose(fp);
}


//ͨ����Ų���
//����ͨ������Ҫ�޸ģ�
struct book *search_by_number(struct book *head, int number)
{
    struct book *p;
    p = head->next;
    while(p -> next != NULL)
    {
        if (p -> number == number)
            return p;
        p = p->next;
    }
    return NULL;
}

//�������ֲ���
//���Գɹ�����Ҫ�޸ģ�
struct book *search_by_name(struct book *head, char *name)
{
    struct book *p;
    p = head->next;
    while(p -> next != NULL)
    {
        if (strcmp(name, p->name) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

//ͨ��������࣬����÷������е���
//���Գɹ���
int search_by_category(struct book *head, char *category)
{
    struct book *p;
    p = head->next;
    int flag = 0;
    while(p -> next != NULL)
    {
        if (strcmp(category, p->category) == 0)
        {
            print_booknode(p);
            flag = 1;
        }
        p = p->next;
    }
    if(flag == 0)
    {
        printf("û���ҵ��÷�����飡\n");
        printf("��������������˵�...\n");
        getch();
        return 0;
    }
    printf("��������������˵�...\n");
    getch();
    return 0;

}

//��������������Ϣ
//���Գɹ���
void print_booknode(struct book *t)
{
    if(t != NULL)
    {
        printf("�����ҵ���������ǣ�\n");
        printf("������%s\n", t->name);
        printf("��ţ�%d\n", t->number);
        printf("���ࣺ%s\n", t->category);
        printf("�Ƿ��ѽ裺");
        if(t->lent == 1)
        {
            printf("��\n");
            printf("������ڣ�%d��%d��%d��",t->year,t->month,t->day);
        }
        else printf("��\n");
    }
    else
    {
        printf("û���ҵ����飡\n");
        printf("��������������˵�...\n");
        getch();
    }
}


//delete book
//���Գɹ���
struct book *delete_book(struct book *head, struct book *p)
{
    struct book *q;
    q = head;
    while(q->next != p)
    {
        q = q->next;
    }
    q->next = p->next;
    free(p);
    return head;
}

//�����µ���
//����ͨ������Ҫ�޸�
int input_new_book()
{
    FILE *fp;
    fp = fopen("library.txt", "a+");
    struct book newbook;
    printf("����������ı�ţ�");
    scanf("%d",&newbook.number);
    printf("��������������֣�");
    scanf("%s",newbook.name);
    printf("����������ķ��ࣺ");
    scanf("%s",newbook.category);
    newbook.lent = 0;
    newbook.year = 0;
    newbook.month = 0;
    newbook.day = 0;
    newbook.next = NULL;
    fprintf(fp,"%d ",newbook.number);
    fprintf(fp,"%s ",newbook.name);
    fprintf(fp,"%s ",newbook.category);
    fprintf(fp,"%d %d %d %d\n",newbook.lent,newbook.year,newbook.month,newbook.day);
    fclose(fp);
    printf("¼��ɹ��������������˵�...\n");
    return 1;
}

//���������
//���Գɹ���
void print_all_book(struct book *head)
{
    struct book *p;
    p = head->next;
    while(p->next != NULL)
    {
        print_booknode(p);
        p = p->next;
    }
}

//������
int main()
{

    //��¼
    int login_temp;
loop:
    print_main_title();
    printf("\n\n");
    printf("                        1��ע�����û�\n");
    printf("                        2����¼\n");
    printf("                        3������/������¼\n");
    printf("                        4���˳�\n");
    printf("\n\n");
    printf("                      ������ѡ����س���������");
    scanf("%d",&login_temp);
    int login_check_temp = 1;
    char login_exit_temp;
    switch(login_temp)
    {
    case 1:
        create_user();
        goto loop;
    case 2:
        login_check_temp = login();
        if(login_check_temp == 0)goto loop;
        break;
    case 3:
        break;
    case 4:
        printf("\n");
        printf("                      ��ȷ��Ҫ�˳���\n");
        printf("                      ��������˳�����n����\n");
        login_exit_temp = getch();
        if(login_exit_temp == 'n')
        {
            system("CLS");
            goto loop;
        }
        else exit(0);
    }
    //�ɹ���¼�����ִ�г���

    struct book *head;
    int menu_select, search_select, admin_select, borrow_select, modify_select, admin_delete_select;
    while(1)
    {
        head = make_linklist();
main_loop:
        system("CLS");
        printf("================================================================================");
        printf("                                                                                ");
        printf("                                                                                ");
        printf("                                                                                ");
        printf("                           ��ӭʹ��ͼ�����ϵͳv1.0                             ");
        printf("                                                                                ");
        printf("                                                                                ");
        printf("                                                                                ");
        printf("================================================================================");
        printf("\n\n");
        printf("1������\n2������\n3������\n4����ʾ�����鱾\n5������Աѡ��\n6���˳�\n");


        time_t timep;
        struct tm *p;
        time(&timep);
        p = gmtime(&timep);
        //p =localltime(&timep);
        printf("Year:  %d\n", 1900+p->tm_year);
        printf("Month:  %d\n", 1+p->tm_mon);
        printf("Day:  %d\n", p->tm_mday);
        printf("Hour:  %d\n", 8 + p->tm_hour);
        printf("Minute:  %d\n", p->tm_min);
        printf("Second:  %d\n",  p->tm_sec);
        printf("Weekday:  %d\n", p->tm_wday);
        printf("Days:  %d\n", p->tm_yday);
        printf("Isdst:  %d\n", p->tm_isdst);


        scanf("%d", &menu_select);
        struct book *t;
        int i;
        int temp = 0;
        char name_temp[30];
        for(i = 0; i < 30; i++) name_temp[i] = 0;
        char category_temp[10];
        for(i = 0; i < 10; i++) name_temp[i] = 0;

        switch(menu_select)
        {
        case 1://����
            printf("1������2�����3������4������");
            scanf("%d", &borrow_select);
            switch(borrow_select)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                goto main_loop;
            }
            break;
        case 2://����
            break;
        case 3://����
            printf("1������2�����3������4�����ʱ��5������");
            scanf("%d", &search_select);
            switch(search_select)
            {
            case 1://��������
                printf("������Ҫ���ҵ�����,���س�������");
                scanf("%s", name_temp);
                t = search_by_name(head, name_temp);
                if (t != NULL)
                {
                    print_booknode(t);
                    printf("��������������˵�...\n");
                    getch();
                    break;
                }
                else
                {
                    printf("û���ҵ����飡\n");
                    printf("��������������˵�...\n");
                    getch();
                    break;
                }
                break;
            case 2://���ݱ��
                //���Գɹ�����Ҫ�޸ģ�
                printf("������Ҫ���ҵ���ı��,���س�������");
                scanf("%d", &temp);
                t = search_by_number(head, temp);
                if (t != NULL)
                {
                    print_booknode(t);
                    printf("��������������˵�...\n");
                    getch();
                    break;
                }
                else
                {
                    printf("û���ҵ����飡\n");
                    printf("��������������˵�...\n");
                    getch();
                    break;
                }
                break;
            case 3://���ݷ���
                printf("������Ҫ���ҵķ���,���س�������");
                scanf("%s", category_temp);
                search_by_category(head, category_temp);
                break;
            case 4://���ݽ��ʱ��
                break;
            default://������һ��
                break;
            }
            break;

        case 5://����Ա
            switch(admin_select)
            {
            case 1://¼��
                input_new_book();
                break;
            case 2://�޸�
                printf("ϵͳ�趨λ��Ҫ�޸����ݵ��飺\n");
                printf("1���������Ʋ���2�������Ų���");
                scanf("%d", &modify_select);
                switch(modify_select)
                {
                case 1://��������
                    printf("������Ҫ���ҵ���ı��,���س�������");
                scanf("%d", &temp);
                t = search_by_number(head, temp);
                if (t == NULL)
                {
                    printf("û���ҵ����飡\n");
                    printf("��������������˵�...\n");
                    getch();
                    break;
                }
                case 2://������
                    break;
                }

                //��t�����޸�

            case 3://ɾ��
                printf("1������2�����3������\n");
                scanf("%d", admin_delete_select);
                switch(admin_delete_select)
                {
                case 1://������ɾ��
                    printf("������Ҫɾ����������ƣ����س�������");
                    scanf("%s", name_temp);
                    t = search_by_name(head, name_temp);
                    head = delete_book(head, t);
                    override_to_file(head);
                case 2://�����ɾ��
                    printf("������Ҫɾ������ı�ţ����س�������");
                    scanf("%d", &temp);
                    t = search_by_number(head, temp);
                    head = delete_book(head, t);
                    override_to_file(head);
                    break;
                case 3:
                    break;
                }
                break;
            }
            break;
        case 6://�˳�
            printf("\n");
            printf("                      ��ȷ��Ҫ�˳���\n");
            printf("                      ��������˳�����n����\n");
            login_exit_temp = getch();
            if(login_exit_temp == 'n')
            {
                system("CLS");
                goto main_loop;
            }
            else return 1;
        }
    }
}


/*

{
    head = make_linklist();
    system("CLS");

    //����˵�


    scanf("%d", &menu_select);
    int y;
    int m;
    int d;

    struct book *t;
    int i;
    int temp = 0;
    char name_temp[30];
    for(i = 0; i < 30; i++) name_temp[i] = 0;
    char category_temp[10];
    for(i = 0; i < 10; i++) name_temp[i] = 0;

    switch(menu_select)
    {
    case 1:
        input_new_book();
        break;
    case 2:
        printf("������������ƣ����س�������");
        scanf("%s", name_temp);
        t = search_by_name(head, name_temp);
        t->lent = 1;
        //printf("")
        break;
    case 3:
        printf("ע�⣡�˲������ɻָ���\n");
        printf("1�����ձ��ɾ��\n2����������ɾ��\n3������\n�����룺");
        scanf("%d", &temp);
        switch(temp)
        {
        case 1:
            printf("������Ҫɾ������ı�ţ����س�������");
            scanf("%d", &temp);
            t = search_by_number(head, temp);
            head = delete_book(head, t);
            override_to_file(head);
            break;
        case 2:
            printf("������Ҫ���ҵ�������ƣ����س�������");
            scanf("%s", name_temp);
            t = search_by_name(head, name_temp);
            head = delete_book(head, t);
            override_to_file(head);
        default:
            break;
        }
        break;
    case 4:
        //���Գɹ���
        printf("������Ҫ���ҵ�����,���س�������");
        scanf("%s", name_temp);
        t = search_by_name(head, name_temp);
        if (t != NULL)
        {
            print_booknode(t);
            printf("��������������˵�...\n");
            getch();
            break;
        }
        break;
    case 5:
        printf("������Ҫ���ҵķ���,���س�������");
        scanf("%s", category_temp);
        search_by_category(head, category_temp);
        break;
    case 6:
        //���Գɹ�����Ҫ�޸ģ�
        printf("������Ҫ���ҵ���ı��,���س�������");
        scanf("%d", &temp);
        t = search_by_number(head, temp);
        print_booknode(t);
        printf("��������������˵�...\n");
        getch();
        break;
    case 7:
        break;
    case 8:
        printf("1���г������鼮\n2�������˳����������ͼ��\n3�����������ļ�\n4����ȡ��ǰ����");
        scanf("%d",&temp);
        switch(temp)
        {
        case 1:
            print_all_book(head);
            break;
        case 3:
            override_to_file(head);
            break;
            //case 4:
            //_getsystime
        }
        break;
    case 9:
        return 1;
    }
}
*/
