#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>

int license_get = 0;

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
    time_t time_login;
    struct tm *p;
    time(&time_login);
    p = gmtime(&time_login);

    printf("================================================================================");
    printf("                                                                                ");
    printf("                                                                                ");
    printf("                                                                                ");
    printf("                           ��ӭʹ��ͼ�����ϵͳv1.2                             ");
    printf("                                   ����ԭ��                                     ");
    printf("                      ����ʱ�䣺%d��%d��%d�� %d:%d:%d\n", 1900 + p->tm_year, p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
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
    printf("                  �������µ��˺ţ����س�����\n");
    printf("�˺ŵĳ���Ϊ");
    scanf("%s", su.username);
    printf("\n");
    printf("                  �������µ����룬���س�����\n");
    printf("         ����ĳ���Ϊ8λ��������ʹ��Ӣ���ַ������֣�������ո�");
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
    struct book *head;
    head = (struct book *)malloc(sizeof(struct book));
    head->next = NULL;
    FILE *fp;
    fp = fopen("library.txt", "r+");
    if (fp == NULL)
        fp = fopen("library.txt", "w+");
    if (check_void_file() == 0)
    {
        //printf("ͼ�����ݿ�Ϊ�գ�");
        return head;
    }
    struct book *p;
    p = head;
    char ch;
    while(!feof(fp))
    {
        struct book *new_book_init;
        new_book_init = (struct book *)malloc(sizeof(struct book));
        fscanf(fp, "%d", &new_book_init->number);
        ch = fgetc(fp);
        fscanf(fp, "%[^\n]%*c", new_book_init->name);
        fscanf(fp, "%[^\n]%*c", new_book_init->category);
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
        fprintf(fp, "%s\n", p->name);
        fprintf(fp, "%s\n", p->category);
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
    if (p == NULL)
        return NULL;
    while(p -> next != NULL)
    {
        if (p -> number == number)
            return p;
        p = p->next;
    }
    //return NULL;
}

//�������ֲ���
//���Գɹ�����Ҫ�޸ģ�
struct book *search_by_name(struct book *head, char *name)
{
    struct book *p;
    p = head->next;
    if (p == NULL)
        return NULL;
    while(p != NULL)
    {
        if (strcmp(name, p->name) == 0)
            return p;
        p = p->next;
    }
    //return NULL;
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

void print_booklist_title()
{
    printf("�����ҵ���������ǣ�\n");
    printf("���                ����                          ����        ���ʱ��       \n");
}

void print_booknode(struct book *t)
{

    if(t != NULL)
    {
        printf("%-20d%-30s%-10s",t->number, t->name, t->category);
        if(t->lent == 1)
        {
            printf("  %d��%d��%d��\n",t->year,t->month,t->day);
        }
        else printf("  �ڿ�\n");
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
    printf("���棡�ò������ɻָ���\n");
    printf("�Ƿ������\n");
    printf("y����  ���������\n");
    printf("�������Ӧѡ����س�������");
    char ch;
    scanf("%c", &ch);
    if (ch == 'y')
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
    else
        return head;

}

//�����µ���
//����ͨ������Ҫ�޸�
int input_new_book()
{
    FILE *fp;
    struct book newbook;
input_loop:
    fp = fopen("library.txt", "a+");
    system("ClS");
    printf("����������ı�ţ�");
    scanf("%d",&newbook.number);
    printf("��������������֣�");
    fflush(stdin);
    scanf("%[^'\n']",newbook.name);
    fflush(stdin);
    printf("����������ķ��ࣺ");
    scanf("%[^'\n']",newbook.category);
    newbook.lent = 0;
    newbook.year = 0;
    newbook.month = 0;
    newbook.day = 0;
    newbook.next = NULL;
    fprintf(fp,"%d ",newbook.number);
    fprintf(fp,"%s\n",newbook.name);
    fprintf(fp,"%s\n",newbook.category);
    fprintf(fp,"%d %d %d %d\n",newbook.lent,newbook.year,newbook.month,newbook.day);
    fclose(fp);
    printf("¼��ɹ���\n");
    printf("�Ƿ����¼�룿\n");
    printf("y����  n����\n");
    fflush(stdin);
    char ch;
    scanf("%c", &ch);
    if (ch == 'y')
        goto input_loop;
    else
    {
        printf("������3��󷵻����˵�...");
        Sleep(3000);
        return 1;
    }
}

//���������
//���Գɹ���
int print_all_book(struct book *head)
{
    system("CLS");
    char ch;
    struct book *p;
    p = head->next;
    if (p == NULL)
    {
        printf("���ݿ���û���鱾��\n");
        printf("                  ��������������˵�...");
        ch = getch();
        return 0;
    }
    print_booklist_title();
    do
    {
        print_booknode(p);
        p = p->next;
    }
    while(p->next != NULL);
    printf("                  ��������������˵�...");
    ch = getch();
    return 1;
}

int give_license()
{
    char license[54];
    strcpy(license, "9ad3eb1a654e073ba4369d25701de71b4cbf5d23bc98222531114");
    char user_license[54];
    int i;
    for(i = 0; i < 54; i++)
        user_license[i] == '\0';
    printf("�����뼤���룬���س�������\n");
    fflush(stdin);
    gets(user_license);
    int check = 1;
    check = strcmp(license, user_license);
    if (check == 0){
        license_get = 1;
        return 1;
    }
    else return 0;
}

//������
int main()
{

    //��¼
    char login_temp;
loop:
    print_main_title();
    printf("\n\n");
    printf("                        1��ע�����û�\n");
    printf("                        2����¼\n");
    printf("                        3������/������¼\n");
    printf("                        4���˳�\n");
    printf("\n\n");
    printf("                      ������ѡ��ǰ�ı�ţ����س���������");
    scanf("%c",&login_temp);
    int login_check_temp = 1;
    char login_exit_temp;
    switch(login_temp)
    {
    case '1':
        create_user();
        goto loop;
    case '2':
        login_check_temp = login();
        if(login_check_temp == 0)goto loop;
        break;
    case '3':
        break;
    case '4':
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
    default:
        system("CLS");
        goto loop;
    }
    //�ɹ���¼�����ִ�г���

    struct book *head;
    int search_select, admin_select, borrow_select, back_select, modify_select, admin_delete_select;
    char menu_select;
    char ch;
    char str_tmp[100];
    while(1)
    {
        head = make_linklist();
main_loop:
        system("CLS");
        print_main_title();
        printf("\n\n");
        printf("                        1������\n");
        printf("                        2������\n");
        printf("                        3������\n");
        printf("                        4����ʾ�����鱾\n");
        printf("                        5������Աѡ��\n");
        printf("                        6���˳�\n");
        //printf("                        7����Ȩ\n");
        printf("\n");
        printf("                   ������Ҫʹ�ù��ܵı�ţ����س����룺");

        scanf("%c", &menu_select);

        struct book *t;
        int i;
        int temp = 0;
        char name_temp[30];
        for(i = 0; i < 30; i++) name_temp[i] = 0;
        char category_temp[10];
        for(i = 0; i < 10; i++) category_temp[i] = 0;

        time_t timep;
        struct tm *time_p;
        time(&timep);
        time_p = gmtime(&timep);

        switch(menu_select)
        {
        case '1'://����
        borrow_loop:
            system("CLS");
            print_main_title();
            printf("\n\n");
            printf("                        1���������ֲ���\n\n");
            printf("                        2�����ݱ�Ų���\n\n");
            printf("                        3������\n\n");
            printf("                        �������Ӧ���ܵı�ţ����س����룺");
            scanf("%d", &borrow_select);
            switch(borrow_select)
            {
            case 1:
                printf("������Ҫ���ҵ�����,���س�������");
                scanf("%s", name_temp);
                t = search_by_name(head, name_temp);
                //time_t timep;

                if (t != NULL)
                {
                    system("CLS");
                    print_booklist_title();
                    print_booknode(t);
                    if(t->lent == 0)
                    {
                        printf("��ȷ��Ҫ���Ȿ����1���� 2����");
                        scanf("%d", &temp);
                        if(temp == 1)
                        {
                            t->lent = 1;
                            t->year = 1900 + time_p->tm_year;
                            t->month = time_p->tm_mon;
                            t->day = time_p->tm_mday;
                            //print_booknode(t);
                            printf("����ɹ���");
                            override_to_file(head);
                        }
                    }
                    //else break;
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
            case 2:
                printf("������Ҫ���ҵı�ţ����س�������");
                scanf("%d", &temp);
                t = search_by_number(head, temp);
                //time_t timep;

                if (t != NULL)
                {
                    print_booknode(t);
                    if(t->lent == 0)
                    {
                        printf("��ȷ��Ҫ���Ȿ����1���� 2����");
                        scanf("%d", &temp);
                        if(temp == 1)
                        {
                            t->lent = 1;
                            t->year = 1900 + time_p->tm_year;
                            t->month = time_p->tm_mon;
                            t->day = time_p->tm_mday;
                            print_booknode(t);
                            printf("����ɹ���");
                            override_to_file(head);
                        }
                    }
                    //else break;
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
            case 3:
                break;
            default:
                gets(str_tmp);
                goto borrow_loop;
            }
            break;
        case '2'://����
            system("CLS");
            /*
            if (license_get == 0){
            printf("�Բ��𣬸ù�����δ����!\n\n");
            printf("�װ����û���ã�������ʹ�õ�����Ѱ汾����������ȫ��Ĳ��ֹ��ܡ�\n�ù�����Ҫ��������Ȩ�Լ���ʹ�ã�������Ϊ10Ԫ��\n");

            printf("��ѽ��ת�˵�֧�����˺�1057703657@qq.com�У������յ�ת�˻��Զ��������ͼ����룬�����յ���������˵�����Ȩѡ����뼤���룬���ɽ���ȫ�����ܣ�\n");
            printf("һ�ν�����������ѣ�\n");
            printf("����֧���ǿ�����Ī��Ķ�����\n");
            system("PAUSE");
            }

            else
            {
                printf("ƭ��Ĺ�����������\nby Ҷ����\n");
                system("PAUSE");
            }
            */
            system("CLS");
            printf("�ù��ܻ��ڵ�����......\n\n\n\n");

            printf("ϵͳ��Ҫ��λ��Ҫ�����飺\n");
            printf("1��������������\n");
            printf("2�����ݱ�Ų���\n");
            printf("3��������һ��\n");
            printf("�������Ӧ����ǰ�ı�ţ����س�������");

            scanf("%d", &back_select);

            switch(back_select)
            {
            case 1://����
                break;
            case 2://���
                break;
            default:
                break;
            }

            break;
        case '3'://����

            system("CLS");
            print_main_title();
            printf("\n\n");
            printf("                        1���������ֲ���\n");
            printf("                        2�����ݱ�Ų���\n");
            printf("                        3�����ݷ������\n");
            printf("                        4�����ݽ��ʱ�����\n");
            printf("                        5������\n");
            printf("\n\n");
            printf("                        �������Ӧ���ܵı�ţ����س����룺");
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

        case '4':
            print_all_book(head);
            break;
        case '5'://����Ա
            system("CLS");
            print_main_title();
            printf("\n\n");
            printf("                        1��¼�����鵽���ݿ�\n");
            printf("                        2���޸����е��������\n");
            printf("                        3�������ݿ���ɾ����\n");
            printf("                        4��������һ��\n");
            printf("\n\n");
            printf("                        �������Ӧ���ܵı�ţ����س����룺");
            scanf("%d", &admin_select);
            switch(admin_select)
            {
            case 1://¼��
                input_new_book();
                break;
            case 2://�޸�
                system("CLS");
                print_main_title();
                printf("\n\n");
                printf("�������������޸����ݿ�����ı�š����ơ�����ͽ��ʱ��\n");
                printf("ϵͳ�趨λ��Ҫ�޸����ݵ��飺\n");
                printf("1���������Ʋ���\n");
                printf("2�������Ų���\n");
                printf("3������\n");
                printf("�������Ӧ����ǰ�ı�ţ����س�������");
                scanf("%d", &modify_select);
                switch(modify_select)
                {
                case 1://��������
                    printf("������Ҫ���ҵ���ı��,���س�������");
                    scanf("%d", &temp);
                    t = search_by_number(head, temp);
                    if (t == NULL)
                    {
                        printf("û���ҵ����飡��˶Ժ�����������\n");
                        printf("��������������˵�...\n");
                        getch();
                        break;
                    }
                    else
                    {
                        printf("��������������ƣ�");
                        printf("��������30���ַ����ڣ�һ������Ϊ�����ַ�\n");
                        gets(name_temp);
                        strcpy(t->name, name_temp);
                        override_to_file(head);
                        printf("�޸ĳɹ���");
                        print_booklist_title();
                        print_booknode(t);
                    }
                    break;
                case 2://������
                    break;
                default:
                    break;
                }

            //��t�����޸�

            case 3://ɾ��
                system("CLS");
                print_main_title();
                printf("\n                           ���棡�ò������ɻָ���\n\n");
                printf("                        ϵͳ�趨λ��Ҫɾ�����飺\n\n");
                printf("                        1���������Ʋ���\n\n");
                printf("                        2�����ݱ�Ų���\n\n");
                printf("                        3������\n\n");
                printf("                        �������Ӧѡ��ı�ţ����س�������");
                scanf("%d", &admin_delete_select);
                switch(admin_delete_select)
                {
                case 1://������ɾ��
                    system("CLS");
                    printf("                           ���棡�ò������ɻָ���\n\n");
                    printf("                        WARNING!THIS CAN'T BE UNDONE!!\n\n");
                    printf("���践����һ���������������ڵġ�@���ַ��󰴻س�����\n\n");
                    printf("������Ҫɾ����������ƣ����س�������");
                    scanf("%s", name_temp);
                    if (name_temp[0] == '@')
                    {
                        printf("\n\n�����������˵�\n");
                        system("PAUSE");
                        break;
                    }
                    t = search_by_name(head, name_temp);
                    if (t != NULL)
                    {
                        head = delete_book(head, t);
                        override_to_file(head);
                    }
                    else
                    {
                        printf("û���ҵ����飡\n");
                        system("PAUSE");
                    }
                    break;
                case 2://�����ɾ��
                    system("CLS");
                    printf("                           ���棡�ò������ɻָ���\n\n");
                    printf("                        WARNING!THIS CAN'T BE UNDONE!!\n\n");
                    printf("���践����һ���������������ڵġ�@���ַ��󰴻س�����\n\n");
                    printf("������Ҫɾ����������ƣ����س�������");
                    scanf("%s", name_temp);
                    if (name_temp[0] == '@')
                    {
                        printf("\n\n�����������˵�\n");
                        system("PAUSE");
                        break;
                    }
                    scanf("%d", &temp);
                    t = search_by_number(head, temp);
                    if (t != NULL)
                    {
                        head = delete_book(head, t);
                        override_to_file(head);
                    }
                    else
                    {
                        printf("û���ҵ����飡\n");
                        system("PAUSE");
                    }
                    break;
                case 3:
                    break;
                }
                default:
                    break;
            }
            break;
        case '6'://�˳�
            {
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

        case '7':
            {
                system("CLS");
                int check;
                give_license();
                if (license_get == 1)
                    printf("��Ȩ�ɹ����뾡��ʹ�ø������\n");
                else
                    printf("��Ȩ������˶Լ������Ƿ���ȷ����������\n");
                system("PAUSE");
            }

        default:
            goto main_loop;
        }
    }
}


/*

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


*/
