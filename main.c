#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
struct member {
   int CIN;
   char name[15];
   char password[15];
   char Email[20];
   int NumberPhone;
};
struct computer{
    int code;
    char name[10];
    char memory[10];
    char model[10];
    char status[10];
};
struct session {
    int CIN;
    int code;
    time_t login;
    time_t logout;
    float charges;

};
/ Define the person structure
typedef struct {
    char name[50];
    int coffees_demanded;
    double credit_balance;
} Person;

// Queue element structure
typedef struct _queue_element {
    void *content;
    struct _queue_element *next;
} queue_element;

// Queue structure
typedef struct {
    queue_element *head, *tail;
    unsigned nb_values;
} queue;

// Function to add to the queue
int queue_send(queue *q, void *p) {
    queue_element *e = malloc(sizeof(queue_element));
    if (!e)
        return -1;
    e->content = p;
    e->next = NULL;
    if (q->tail)
        q->tail->next = e;
    else
        q->head = e;
    q->tail = e;
    q->nb_values++;
    return 0;
}
void *queue_receive(queue *q) {
    queue_element *e;
    void *p;
    if (!(q->head))
        return NULL;
    e = q->head;
    p = e->content;
    q->head = e->next;
    if (!--(q->nb_values))
        q->tail = NULL;
    free(e);
    return p;
}
int coffee_stock = 0;
void prepareCoffee(int count) {
    coffee_stock += count;
    printf("%d coffee(s) prepared. Total coffee stock: %d\n", count, coffee_stock);
}
int test(int a);
void addMember();
void updateMember ();
void DeleteMember();
void SearchMember();
void SearchComputer();
void show_all_member ();
void updatePc ();
void show_all_pc();
void addPc();
void Deletepc();
void ComputerEntry ();
void MenuMemberEntry ();
void charges();
int searchpc(int code);
void MemberLogIn();
void booking();
void MenuCafeManagment();
void affichageMenu();
void MemberLogIn ();

int testcode(int a){
    char str[20];
    sprintf(str, "%d", a);
    if (strlen(str) != 4) {
        printf(" incorrect\n");
        return 0;
    }
    for (int i = 0 ; i < 4; i++) {
        if (!isdigit(str[i])) {
            printf(" incorrect\n");
            return 0;
        }
    }
    return 1;
}
int test(int a){
    char str[20];
    sprintf(str, "%d", a);
    if (strlen(str) != 8) {
        printf(" incorrect\n");
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        if (!isdigit(str[i])) {
            printf(" incorrect\n");
            return 0;
        }
    }
    return 1;
}
void addMember() {
    printf("\n              ================== Enter New Member =====================\n");
    char conf[15];
    int s;
    struct member mem;
    struct member newMember;
    FILE *fp;
    fp = fopen("member.txt", "a+");
    if (fp == NULL) {
        printf("Error: Could not open member.txt. Make sure the file exists.\n");
        return;
    }
    do {
        printf("                                                *CIN : ");
        scanf("%d", &newMember.CIN);
        getchar();
    } while (test(newMember.CIN) == 0);
    rewind(fp);

    int cinExists = 0;
    while (fscanf(fp, "%d     %s     %s     %s     %d", &mem.CIN, mem.name, mem.password, mem.Email, &mem.NumberPhone) != EOF) {
        if (mem.CIN == newMember.CIN) {
            printf("This CIN already exists for %s.\n", mem.name);
            cinExists = 1;
            break;
        }
    }

    if (cinExists) {
        fclose(fp);
        return;
    }
    printf("                                            *Name : ");
    fgets(newMember.name, sizeof(newMember.name), stdin);
    newMember.name[strcspn(newMember.name, "\n")] = '\0';
    printf("                                            *Password : ");
    gets(newMember.password);
    s = 0;

    do {
        printf("                                         *Confirm Password : ");
        gets(conf);
        if (strcmp(conf, newMember.password) == 0)
            s = 1;
        else
            printf("Passwords do not match.\n");
    } while (s == 0);
    do {
            printf("                                      *Number Phone : ");
            scanf("%d",&newMember.NumberPhone);
            getchar();
    } while (test(newMember.NumberPhone) == 0);
    printf("                                              *Email : ");
    gets(newMember.Email);
    fprintf(fp, "%d     %s     %s     %s     %d  \n", newMember.CIN, newMember.name, newMember.password, newMember.Email, newMember.NumberPhone);
    fclose(fp);

    printf("Successfully added a new member!\n");
}
void updateMember() {
    struct member mem;
    char name[15], Email[30], Num[15], password[15], conf[15];
    FILE *fp, *fm;
    int CIN ;
    int found = 0;
    fm = fopen("member.txt", "r");
    if (fm == NULL) {
        printf("Error: Could not open member.txt. Make sure the file exists.\n");
        return;
    }
    fp = fopen("user.txt", "w");
    if (fp == NULL) {
        printf("Error: Could not create user.txt.\n");
        fclose(fm);
        return;
    }
    printf("                *Enter the member CIN to update: ");
    scanf("%d", &CIN);
    while (fscanf(fm, "%d     %s     %s     %s     %d ", &mem.CIN, mem.name, mem.password, mem.Email, &mem.NumberPhone) != EOF) {
        if (mem.CIN == CIN) {
            found = 1;
            int choice, valid = 0;

            do {
                printf("                                              what do you want to update ?   \n");
                printf("                                       ____________________________________\n ");
                printf("                                      |          *1-Name.                  |\n");
                printf("                                       |          *2-Password .             |\n");
                printf("                                       |          *3-Email.                 |\n");
                printf("                                       |          *4-Number Phone.          |\n");
                printf("                                       |          *5-back.                  |_n");
                printf("                                        |____________________________________|\n");
                printf("                                         *Select your choice: ");
                scanf("%d", &choice);
                getchar();
                switch (choice) {
                case 1:
                    printf("New name: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    fprintf(fp, "%d     %s     %s     %s     %d\n", mem.CIN, name, mem.password, mem.Email, mem.NumberPhone);
                    break;
                case 2:
                    printf("New password: ");
                    fgets(password, sizeof(password), stdin);
                    password[strcspn(password, "\n")] = '\0';
                    do {
                        printf("Confirm password: ");
                        fgets(conf, sizeof(conf), stdin);
                        conf[strcspn(conf, "\n")] = '\0';
                        if (strcmp(conf, password) == 0) {
                            valid = 1;
                            fprintf(fp, "%d     %s     %s     %s     %d\n", mem.CIN, mem.name, password, mem.Email, mem.NumberPhone);
                        } else {
                            printf("Passwords do not match. Try again.\n");
                        }
                    } while (!valid);
                    break;
                case 3:
                    printf("New email: ");
                    fgets(Email, sizeof(Email), stdin);
                    Email[strcspn(Email, "\n")] = '\0';
                    fprintf(fp, "%d     %s     %s     %s     %d\n", mem.CIN, mem.name, mem.password, Email, mem.NumberPhone);
                    break;
                case 4:
                    do {
                        printf("New phone number: ");
                        scanf("%d",&Num);
                    } while (test(Num) == 0);
                    fprintf(fp, "%d     %s     %s    %s     %d \n", mem.CIN, mem.name, mem.password, mem.Email, Num);
                    break;
                case 5:
                    break;
                default:
                    printf("Invalid choice. Try again.\n");
                }
            } while (choice != 5);
        } else {
            fprintf(fp, "%d     %s     %s     %s     %d\n", mem.CIN, mem.name, mem.password, mem.Email, mem.NumberPhone);
        }
    }

    fclose(fm);
    fclose(fp);
    remove("member.txt");
    rename("user.txt", "member.txt");
    if (found) {
        printf("The information has been successfully updated.\n");
    } else {
        printf("Error: CIN '%d' not found.\n", CIN);
    }
}
void DeleteMember(){
    struct member mem ;
    int CIN ;
    FILE *fp , *fm;
    fm=fopen("member.txt","r");
    fp=fopen("user.txt","w");
    if (fp == NULL || fm == NULL){
        printf("Error: Could not open member.txt. Make sure the file exists.\n");
        if (fm) fclose(fm);
        if (fp) fclose(fp);
        return ;
    }
    do{
            printf(" \n Enter the member CIN to delete : ");
            scanf("%d",&CIN);
            getchar();
    } while (test(CIN) == 0);
    int found = 0 ;
    char r ;
    do {
        printf(" \n Are you sur you want to delete (Y/N)? \n ");
        scanf("%c",&r);
    }while ((toupper(r) != 'Y') && (toupper(r) != 'N') );
    if ( toupper(r) == 'Y'){
            while ((fscanf(fm,"%d     %s     %s     %s     %d ",&mem.CIN , mem.name , mem.password , mem.Email , &mem.NumberPhone))!= EOF) {
                if (CIN == mem.CIN) {
                    found = 1;
                }
                else
                    fprintf(fp ,"%d     %s     %s     %s     %d \n",mem.CIN , mem.name , mem.password , mem.Email , mem.NumberPhone);
            }
            fclose(fm);
            fclose(fp);
            remove("member.txt");
            rename("user.txt", "member.txt");
            if (found == 1){
                    printf(" Record deleted deleted successfully\n ");
            }
            else {
                    printf("user not found . \n ");
                    return ;
            }
    }
    else {
        return;
    }
}
void SearchMember(){
    struct member mem ;
    FILE *fp ;
    fp = fopen ("member.txt","r");
    if (fp == NULL){
        printf("Error: Could not open member.txt. Make sure the file exists.\n");
        return ;
    }
    int CIN;
    int found = 0 ;
    do {
            printf("Enter the CIN of member to search :  ");
            scanf("%d",&CIN);
    } while (test(CIN) == 0);
    while (fscanf(fp,"%d     %s     %s     %s     %d ",&mem.CIN ,mem.name ,mem.password, mem.Email ,&mem.NumberPhone) != EOF ){
        if (CIN == mem.CIN){
            printf("CIN : %d \n Name : %s \n Email: %s \n NumberPhone : %d \n",&mem.CIN , mem.name , mem.Email , &mem.NumberPhone);
            found = 1 ;
            break;
        }
    }
     if (!found) {
        printf("No member found with CIN: %s\n", CIN);
     }
     fclose(fp);
    return;
}
void SearchComputer(){
    struct computer pc ;
    FILE *fp ;
    fp = fopen ("computer.txt","r");
    if (fp == NULL){
        printf("Error: Could not open computer.txt. Make sure the file exists.\n");
        return ;
    }
    int code;
    do{
            printf("Enter the code of computer to search :  ");
            scanf("%d",&code);
    } while (testcode(code) == 0);
    int found = 0 ;
    while (fscanf(fp,"%d     %s     %s     %s     %s ",&pc.code , pc.name , pc.memory , pc.model , pc.status)!= EOF){
        if (code == pc.code){
            printf("code : %d \n Name : %s \n memory : %s \n model : %s \n status : %s \n",pc.code , pc.name , pc.memory , pc.model , pc.status);
            found = 1 ;
            return ;
        }
    }
    if (!found){
        printf("there is no computer with this code ");
    }
    fclose(fp);
    return;
}
void show_all_member (){
    struct member mem ;
    FILE *fp ;
    fp=fopen("member.txt","r");
    if (fp == NULL){
        printf("Error: Could not open member.txt. Make sure the file exists.\n");
        return ;
    }
    printf("\n CIN     Member Name     Email     Phone Number           \n");
    printf("_________________________________________________________________________________________________ \n");
    while ((fscanf(fp,"%d     %s     %s     %s     %d ",&mem.CIN ,mem.name ,mem.password, mem.Email , &mem.NumberPhone))!= EOF){
        printf("%d     %s     %s     %d \n", mem.CIN , mem.name , mem.Email , mem.NumberPhone);
    }
    fclose(fp);
}
void updatePc (){
    struct computer p ;
    char name[15] , memory[10] ,model[8] ;
    FILE *fp , *fm ;
    int code ;
    fm=fopen("computer.txt" , "r");
    fp=fopen("pc.txt" , "w");
    if ((fp == NULL) || (fm == NULL) ){
        printf("Error: Could not open computer.txt. Make sure the file exists.\n");
        return ;
    }
    do {
            printf("Enter the computer code to Update  : ");
            scanf("%d",&code);
            getchar();
    } while ( testcode(code) == 0);
    int found = 0;
    while (fscanf(fm,"%d     %s     %s     %s     %s ", &p.code , p.name , p.memory , p.model , p.status ) != EOF ) {
        if (p.code == code){
            int c ,s ;
             found = 0 ;
            do {
                    printf("                                              what do you want to  modify ?            \n");
                    printf("                                       ____________________________________\n ");
                    printf("                                      |          *1-Name.                  |\n");
                    printf("                                       |          *2-Memory.                |\n");
                    printf("                                       |          *3-Model.                 |\n");
                    printf("                                       |          *4-Back.                  |\n");
                    printf("                                        |____________________________________|\n");
                    printf("\n                                      select your choice :            ");
                    scanf("%d",&c);
                    getchar();
                    switch (c)
                    {
                        case 1 :{
                            printf(" \n New Name :  ");
                            fgets(name, sizeof(name), stdin);
                            name[strcspn(name, "\n")] = '\0';
                            fprintf(fp,"%d     %s     %s     %s     %s \n",p.code , name , p.memory , p.model ,p.status );
                            break ;
                         }
                         case 2 :{
                            printf("/n new memory :   ");
                            fgets(memory, sizeof(memory), stdin);
                            memory[strcspn(memory, "\n")] = '\0';

                            s=0;
                            fprintf(fp, "%d     %s     %s     %s     %s \n",p.code , p.name , memory , p.model ,p.status);

                         }
                         case 3:{
                             printf(" \n New model : ");
                             fgets(model,sizeof(model), stdin);
                             model[strcspn(model, "\n")] = '\0';
                             fprintf(fp, "%d     %s     %s     %s     %s \n",p.code , p.name , p.memory , model , p.status );
                         }
                         case 4: MenuMemberEntry();
                         default : printf("invalid choice ! try again ");
                    }
            } while (c != 4 );
        }
        else
            fprintf(fp, "%d     %s     %s     %s     %s \n",p.code , p.name , p.memory , p.model ,p.status);
    }
    fclose("computer.txt");
    fclose("pc.txt");
    remove("computer.txt");
    rename("pc.txt","computer.txt");
    if (found == 1){
        printf(" the information are modified successfully");
    }
    else
        printf("error , CIN not found .\n ");
}
void show_all_pc(){
    struct computer p;
    FILE *fp ;
    fp=fopen("Computer.txt","r");
    if (fp == NULL){
        printf("Error: Could not open computer.txt Make sure the file exists.\n");
        return ;

    }
    printf("\n Code     Computer Name     Memory     Model     Status \n");
    printf("____________________________________________________________________________________________\n");
    while ((fscanf(fp,"%d     %s     %s     %s     %s ",&p.code , p.name , p.memory , p.model, p.status))!= EOF){
        printf("%d     %s     %s     %s     %s \n",p.code , p.name , p.memory , p.model, p.status);
    }
    fclose(fp);
}
void addPc(){
    printf("\n                             ===================== Enter New Computer =====================\n ");
    struct computer p;
    struct computer newPc ;
    FILE *fp ;
    fp=fopen("computer.txt","a");
    if (fp==NULL){
        printf("Error: Could not open computer.txt. Make sure the file exists.\n");
        return ;
    }
    FILE *f = fopen("computer.txt", "r");
    int found = 0;
    do{
            printf("                                  *Code : ");
            scanf("%d",&newPc.code);
            getchar();
        } while ( testcode(newPc.code) == 0 );
    while (fscanf(f, "%d     %s     %s     %s     %s ", &p.code, p.name, p.memory ,p.model, p.status ) != EOF) {
            if (p.code == newPc.code) {
                found = 1 ;
                break ;
            }

    }
    if(!found){
            printf ("\n                                       *name :  ");
            fgets(newPc.name,sizeof(newPc),stdin);
            newPc.name[strcspn(newPc.name, "\n")] = '\0';
            printf("\n                                        *memory :   ");
            fgets(newPc.memory,sizeof(newPc.memory),stdin);
            newPc.memory[strcspn(newPc.memory, "\n")] = '\0';
            printf("\n                                        *model :  ");
            fgets(newPc.model,sizeof(newPc.model),stdin);
            newPc.model[strcspn(newPc.model, "\n")] = '\0';
            strcpy(newPc.status,"free");
            fprintf(fp,"%d     %s     %s     %s     %s \n",newPc.code , newPc.name , newPc.memory , newPc.model , newPc.status  );
            fclose(fp);
            printf("successfully added a new computer \n");
    }
    else {
        printf("This code already exist ! .\n" );
    }
}
void Deletepc(){
    struct computer p ;
    int code ;
    FILE *fp , *fm;
    fm=fopen("computer.txt","r");
    fp=fopen("pc.txt","w");
    if (fp == NULL || fm == NULL){
        printf("Error: Could not open computer.txt. Make sure the file exists.\n");
        return ;
    }
    do{
            printf(" \n Enter the code of computer to delete : ");
            scanf("%d",&code);
    } while (testcode(code) == 0);
    int found = 0 ;
    char r ;
    do {
        printf(" \n Are you sur you want to delete (Y/N)? \n ");
        scanf(" %c",&r);
    }while ((toupper(r) != 'N' )&& (toupper(r) != 'Y'));
    if ( toupper(r) == 'Y'){
            while ((fscanf(fm,"%d     %s     %s     %s     %s",&p.code , p.name , p.memory , p.model , p.status))!= EOF) {
                if (code == p.code) {
                    found = 1;
                }
                else
                    fprintf(fp ,"%d     %s     %s     %s     %s \n",p.code , p.name , p.memory , p.model ,p.status);
            }
            fclose(fm);
            fclose(fp);
            remove("computer.txt");
            rename("pc.txt", "computer.txt");
            if (found == 1){
                    printf(" Record deleted successfully\n ");
            }
            else
                printf("user not found . \n ");
    }
    else {
        ComputerEntry();
        return;
    }
}
int searchpc(int code){
    struct computer p;
    FILE *fp ;
    fp= fopen ("computer.txt","r");
    if (fp == NULL){
        printf("Error: Could not open computer.txt. Make sure the file exists.\n");
        return ;
    }
    int found = 0 ;
    while ((fscanf(fp,"%d     %s     %s     %s     %s ",&p.code , p.name , p.memory , p.model, p.status))!= EOF){
            if (code == p.code ){
                if (strcmp(p.status,"free") == 0){
                    found = 1 ;
                    break ;
                }
                else {
                    found = 2 ;
                    break ;
                }
            }
    }
    if (found == 1){
        printf("                                    Computer you want to use found ! \n");
    }
    else if (found == 2){
        printf("                                  Computer already in use ");
    }
    else
         printf("                                             There is no computer with this code. \n ");
    return(found);
}
void MemberLogIn(){
    char  pass[15];
    int CIN , code;
    struct member mem;
    struct session s ;
    struct computer p ;
    int a ;
    char c , r = 'N' ;
    show_all_pc();
    do {
            do{
                printf("\n                    Enter the code of computer to search : ");
                scanf(" %d",&code);
                getchar();
            }while ( testcode(code) == 0);
            a=searchpc(code);
            if (a != 1){
                    do{
                            printf("wanna Retry (Y/N)? \n");
                            scanf(" %c",&r);
                    } while((toupper(r) != 'Y') && (toupper(r) != 'N' )) ;
                    if ((toupper(r) == 'N')){
                            booking();
                            return;
                    }
            }
    } while (toupper(r) == 'Y' );
    FILE *fm , *fs, *fpc , *fc;
    fc = fopen("computer.txt","r");
    fpc = fopen("pc.txt","w");
    fs = fopen("session.txt","a");
    fm = fopen("member.txt","r");
    if ((fm == NULL) || (fc == NULL) || (fs == NULL) || (fpc == NULL)) {
            printf("Error: Could not open required files. Make sure the files exist.\n");
            return;
    }
    int found = 0 ;
    do {
            printf(" \n                                          * Enter the User CIN :  ");
            scanf("%d",&CIN);
            getchar();
            printf(" \n                                          * Enter password : ");
            fgets(pass, sizeof(pass), stdin);
            pass[strcspn(pass, "\n")] = '\0';
            while (fscanf(fm,"%d     %s     %s     %s     %d ", &mem.CIN ,mem.name ,mem.password , mem.Email , &mem.NumberPhone)!= EOF){
                    if ((CIN == mem.CIN ) && (strcmp(mem.password , pass ) == 0)){
                        found = 1 ;
                        break ;
                    }
            }
            fclose(fm);
            if (found == 0){
                printf ("user name or password incorrect ! Retry ");
            }
            else {
                s.CIN = CIN ;
                s.code = code ;
                s.login = time (NULL);
                s.logout = 0 ;
                s.charges = 0 ;
                fprintf(fs,"%d     %d     %ld     %ld     %3.f \n",  s.CIN ,s.code, s.login , s.logout , s.charges);
                printf("successfully loged in ");
                while ((fscanf(fc,"%d     %s     %s     %s     %s",&p.code , p.name , p.memory , p.model , p.status))!= EOF) {
                        if (code == p.code) {
                            strcpy(p.status,"in use");
                        }
                        fprintf(fpc ,"%d     %s     %s     %s     %s \n",p.code , p.name , p.memory , p.model , p.status);
                }
                fclose(fc);
                fclose(fpc);
                remove("computer.txt");
                rename("pc.txt", "computer.txt");
            }
    } while ( found == 0 );
}
void MemberLogOut() {

    FILE *session, *sessiontemp , *fpctemp , *fc , *fm ;
    char  pass[20];
    int found = 0;
    int CIN ,code ;
    struct session s;
    fm=fopen("member.txt", "r");
    session=fopen("session.txt", "r");
    fc=fopen("computer.txt", "r");
    fpctemp=fopen("pctemp.txt", "w");
    sessiontemp=fopen("sessiontemp.txt", "w");
    struct member mem ;
    struct computer p ;
    if ((fm == NULL) || (session == NULL) || (fc == NULL) || (fpctemp == NULL) || (sessiontemp == NULL)) {
        printf("Error: Could not open required files. Make sure the files exist.\n");
        return;
    }
    printf(" \n                                          * Enter the User CIN :  ");
    scanf("%d",&CIN);
    getchar();
    printf(" \n                                          * Enter password : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    while ((fscanf(fm,"%d     %s     %s     %s     %d",&mem.CIN ,mem.name ,mem.password, mem.Email , &mem.NumberPhone))!= EOF){
            if ((CIN == mem.CIN ) && (strcmp(mem.password , pass )== 0)){
                found = 1 ;
                break ;
            }
    }
    fclose(fm);
    if (found == 0){
        printf ("user name or password incorrect ! Retry ");
    }
    else {
            while(fscanf( session,"%d     %d     %ld     %ld     %3.f ",  &s.CIN , &s.code, &s.login , &s.logout , &s.charges) != EOF){
                if (s.CIN == CIN){
                    s.logout = time(NULL);
                    code = s.code;
                }
                fprintf(sessiontemp,"%d     %d     %ld     %ld     %3.f \n ",  s.CIN , s.code, s.login , s.logout , s.charges);
            }
            fclose(sessiontemp);
            fclose(session);
            remove("session.txt");
            rename("sessiontemp.txt" , "session.txt");
            fc = fopen("computer.txt", "r");  // Reopen computer file for reading


            while ((fscanf(fc,"%d     %s     %s     %s     %s", &p.code , p.name , p.memory , p.model , p.status))!= EOF) {
                    if (code == p.code) {
                        strcpy(p.status,"free");
                    }
                    fprintf(fpctemp ,"%d     %s     %s     %s     %s \n",p.code , p.name , p.memory , p.model , p.status);
            }
            fclose(fpctemp);
            fclose(fc);
            remove("computer.txt");
            rename("pctemp.txt", "computer.txt");
            printf("Successfully logged out.\n");
        }
}
void LoggedInMembers() {
    FILE *session ;
    struct session s ;
    int count = 0;
    session = fopen("session.txt", "r");
    if (!session) {
        printf("Error: Could not open computer.txt or member.txt or session.txt. Make sure the file exists.\n");
        return;
    }
    printf("List of Logged-in Members:\n");
    printf("-------------------------------------------------------------------\n");
    printf("|   CIN              |  Code             | Time logIn       \n");
    printf("-----------------------------------------------------------------\n");
    while (fscanf(session,"%d     %d     %ld     %ld     %3.f ",  &s.CIN , &s.code, &s.login , &s.logout , &s.charges ) != EOF ) {
            if (s.logout == 0){
                    printf("|   %d               |  %d               | %ld       \n",  s.CIN , s.code, s.login );
                    count++;
            }
    }
    printf("---------------------------------------------------------------------\n");

    fclose(session);

    if (count == 0) {
        printf("No members are currently logged in.\n");
    }
    fclose(session);
}

void WhichMembersUsedSystems() {
    FILE *session;
    struct session s ;
    int count = 0;
    session = fopen("session", "r");
    if (session == NULL) {
        perror("Error: Could not open session.txt. Make sure the file exists.\n");
        return;}

    printf("List of Members Who Used the Systems:\n");
    printf("--------------------------------------------------------------------------\n");
    printf("|   CIN       |  Code      |   Time Login|   Time Logout |\n");
    printf("--------------------------------------------------------------------------\n");

    while (fscanf(session,"%d          %d          %ld          %ld          %3.f ",  &s.CIN , &s.code, &s.login , &s.logout , &s.charges) != EOF) {
        if (s.logout != 0){
                printf("|%d           | %d         |  %ld        | %ld        \n", s.CIN, s.code, s.login, s.logout);
                count++;
        }
    }
    printf("--------------------------------------------------------------------------\n");

    fclose(session);

    if (count == 0) {
        printf("No members have used the systems yet.\n");
    }
}

void calculateCharges() {
    FILE *session, *sessiontemp;
    int CIN;
    struct session s;
    int found = 0;
    float chargeRate , charges ;
    double duration;

    printf("Enter your CIN: ");
    scanf("%d", &CIN);

    session = fopen("session.txt", "r");
    if (session == NULL){
        printf("Error: Could not open session.txt. Make sure the file exists.\n");
        return ;
    }
    while(fscanf( session,"%d     %d     %ld     %ld     %3.f ",  &s.CIN , &s.code, &s.login , &s.logout , &s.charges) != EOF){

            if (CIN == s.CIN) {
                found = 1;
                break;
            }
    }
    if (found == 1) {
            if (s.logout!=0) {
                    printf("Enter the charge rate per minute: ");
                    scanf("%f", &chargeRate);

                    duration = difftime(s.logout, s.login)/60;
                    charges = duration * chargeRate;
                    printf("Total Charges: $%.2f\n", charges);

                    sessiontemp = fopen("sessiontemp.txt", "w");

                    while(fscanf( session,"%d     %d     %ld     %ld     %3.f ",  &s.CIN , &s.code, s.login , s.logout , s.charges) != EOF){
                            if (s.CIN == CIN){
                                s.charges = charges ;
                                fprintf(sessiontemp,"%d     %d    %ld     %ld     %3.f \n ",  s.CIN , s.code, s.login , s.logout , s.charges);
                            }
                            fprintf(sessiontemp,"%d     %s     %ld     %ld     %3.f \n ",  s.CIN, s.code, s.login , s.logout , s.charges);
                    }
                    printf("successfully charge stored ");

                    fclose(sessiontemp);
                    fclose(session);
                    remove("session.txt");
                    rename("sessiontemp.txt", "session.txt");
            }
            else  {
                    printf("You're still logged in, but the charges so far are:\n");
                    time_t now ;
                    now=time(NULL);
                    duration = difftime(now, s.login)/60;
                    printf("Enter the charge rate per minute: ");
                    scanf("%lf", &chargeRate);
                    charges = duration * chargeRate;
                    printf("Charges So Far: $%.2f\n", charges);
            }
    }
    else {
            printf("CIN not found in session.txt.\n");
    }
}
void show_all_charges() {
    FILE *session;
    double charges;
    struct session s;
    int count = 0;
    session = fopen("session.txt", "r");
    if (!session) {
        printf("Error opening session.txt");
        return;
    }

    printf("List of All Charges:\n");
    printf("-------------------------------\n");
    printf("|    CIN    |    Charges ($)  |\n");
    printf("-------------------------------\n");


    while(fscanf( session,"%d     %d     %ld     %ld     %3.f ",  &s.CIN , &s.code, &s.login , &s.logout , &s.charges) != EOF){
            if (s.charges !=0) {
                printf("| %s        | %3.f        |\n", s.CIN, s.charges);
                count++;
            }
    }

    printf("-------------------------------\n");

    fclose(session);

    if (count == 0) {
        printf("No charges recorded in session.txt.\n");
    }
}
void prepareCoffee(int count) {
    coffee_stock += count;
    printf("%d coffee(s) prepared. Total coffee stock: %d\n", count, coffee_stock);
}
void displayQueue(queue *coffee_queue) {
    queue_element *current = coffee_queue->head;
    int total_coffees = 0;

    if (!current) {
        printf("The queue is empty.\n");
        return;
    }

    printf("People in the queue:\n");
    while (current) {
        Person *person = (Person *)current->content;
        printf("- %s wants %d coffee(s).\n", person->name, person->coffees_demanded);
        total_coffees += person->coffees_demanded;
        current = current->next;
    }

    printf("Total coffees demanded: %d\n", total_coffees);
}

// Function to serve coffee
void serveCoffee(queue *coffee_queue) {
    if (!coffee_queue->nb_values) {
        printf("The queue is empty. No one to serve.\n");
        return;
    }

    Person *person = (Person *)coffee_queue->head->content;
    int total_cost = person->coffees_demanded * 3;

    if (person->coffees_demanded > coffee_stock) {
        printf("Not enough coffee for %s. Please prepare more coffee.\n", person->name);
        return;
    }

    if (person->credit_balance >= total_cost) {
        coffee_stock -= person->coffees_demanded;
        person->credit_balance -= total_cost;
        printf("%s served %d coffee(s). Remaining credit: %.2f dinars. Remaining stock: %d.\n",
               person->name, person->coffees_demanded, person->credit_balance, coffee_stock);

        free(queue_receive(coffee_queue));
    } else {
        printf("%s does not have enough credit. Skipping...\n", person->name);
        free(queue_receive(coffee_queue));
    }
}
void coffee_service() {
    queue coffee_queue = {NULL, NULL, 0};
    int choice;
    do {
        printf("\nCoffee Service System\n");
        printf("1. Add Person to Queue\n");
        printf("2. Prepare Coffee\n");
        printf("3. Serve Coffee\n");
        printf("4. Display Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                Person *new_person = (Person *)malloc(sizeof(Person));
                if (!new_person) {
                    printf("Memory allocation failed.\n");
                    break;
                }
                printf("Enter name: ");
                scanf("%s", new_person->name);
                printf("Enter number of coffees: ");
                scanf("%d", &new_person->coffees_demanded);
                printf("Enter credit balance: ");
                scanf("%lf", &new_person->credit_balance);

                if (queue_send(&coffee_queue, new_person) == 0)
                    printf("%s has been added to the queue for %d coffee(s).\n",
                           new_person->name, new_person->coffees_demanded);
                else {
                    printf("Failed to add %s to the queue.\n", new_person->name);
                    free(new_person);
                }
                break;
            }
            case 2: {
                int count;
                printf("Enter number of coffees to prepare: ");
                scanf("%d", &count);
                prepareCoffee(count);
                break;
            }
            case 3:
                serveCoffee(&coffee_queue);
                break;
            case 4:
                displayQueue(&coffee_queue);
                break;
            case 5:
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    while (coffee_queue.nb_values > 0) {
        free(queue_receive(&coffee_queue));
    }
    return 0;
}
void ComputerEntry (){
    int a ;
    do {
            printf(" \n                                  MENU/Master Entry/Computer Entry \n ");
            printf("                                   ________________________________ \n ");
            printf("                                  |                                | \n");
            printf("                                   |   * 1-Add Computer.            | \n");
            printf("                                   |   * 2-Show Computer.           | \n");
            printf("                                   |   * 3-Search Computer.         | \n");
            printf("                                   |   * 4-Delete Computer.         | \n");
            printf("                                   |   * 5-Update Computer.         | \n");
            printf("                                   |   * 6-Back.                    | \n");
            printf ("                                   |________________________________| \n");
            printf ("\n                                      Select Your Choice :  ");
            scanf("%d",&a);
            switch (a){
                case 1:{
                    addPc(); break;
                }
                case 2:{
                    show_all_pc(); break;
                }
                case 3:{
                    SearchComputer(); break ;
                }
                case 4:{
                    Deletepc(); break ;
                }
                case 5:{
                    updatePc() ; break ;
                }
                case 6:{
                    MenuMasterEntry();break;
                }
                default : printf("invalid choice!");

            }
    } while (a != 6 );

}
void MenuMemberEntry (){
    int a ;
    do {
            printf(" \n                                  MENU/Master Entry/Member Entry \n ");
            printf("                                   ________________________________ \n ");
            printf("                                  |                                | \n");
            printf("                                   |   * 1-Add Member.              | \n");
            printf("                                   |   * 2-Show Members.            | \n");
            printf("                                   |   * 3-Search Member by CIN.    | \n");
            printf("                                   |   * 4-Delete Member.           | \n");
            printf("                                   |   * 5-Update Member.           | \n");
            printf("                                   |   * 6-Back.                    | \n");
            printf ("                                   |________________________________| \n");
            printf ("\n                                      Select Your Choice :  ");
            scanf("%d",&a);
            switch (a){
                case 1:{
                    addMember(); break;
                }
                case 2:{
                    show_all_member(); break;
                }
                case 3:{
                    SearchMember(); break ;
                }
                case 4:{
                    DeleteMember(); break ;
                }
                case 5:{
                    updateMember() ; break ;
                }
                case 6:{
                    MenuMasterEntry() ;
                    break ;
                }
                default : printf("invalid choice! ");

            }
    } while (a != 6 );
}
void MenuMasterEntry(){
    int a ;
    printf(" \n                                         MENU/Master Entry \n ");
    printf("                                   ________________________________ \n ");
    printf("                                  |                                | \n");
    printf("                                   |   * 1-Member Entry.            | \n");
    printf("                                   |   * 2-Computer Entry.          | \n");
    printf("                                   |   * 3-Back.                    | \n");
    printf ("                                   |________________________________| \n");
    do {
            printf ("\n                                      Select Your Choice :  ");
            scanf("%d",&a);
            switch (a){
                case 1: {
                    MenuMemberEntry();
                    break;
                }
                case 2: {
                    ComputerEntry();
                    break ;
                }
                case 3: Menu() ; break ;
                default: printf("invalid choice");
            }
    }while (a != 3);
}
void charges(){
     int a;
    do{
            printf("                                         Menu/CafeMangment/Charges    \n");
            printf("                             ___________________________________________________ \n ");
            printf("                            |                                                   | \n");
            printf("                            |   * 1-calculate Charges for a particular member.  | \n");
            printf("                            |   * 2-Show all charges.                           | \n");
            printf("                            |   * 3-Back.                                       | \n");
            printf("                           |___________________________________________________| \n");
            printf("\n                                      Select Your Choice :  ");
            scanf("%d",&a);
            switch(a){
                case 1: calculateCharges() ; break;
                case 2: show_all_charges() ; break;
                case 3: MenuCafeManagment() ; break;
                default : printf("Invalid choice ! Try again . \n"); break;
            }
    } while (a == 3);
}
void booking(){
    int a;
    do{
            printf("                                         Menu/CafeMangment/Booking    \n");
            printf("                                   __________________________________ \n ");
            printf("                                  |                                  | \n");
            printf("                                   |   * 1-Member login.              | \n");
            printf("                                   |   * 2-Member logout.             | \n");
            printf("                                   |   * 3-Logged members.            | \n");
            printf("                                   |   * 4-Which members used systems?| \n");
            printf("                                   |   * 5-Back.                      | \n");
            printf("                                   |__________________________________| \n");
            printf ("\n                                      Select Your Choice :  ");
            scanf("%d",&a);
            switch(a){
                case 1: MemberLogIn();break ;
                case 2: MemberLogOut(); break;
                case 3: LoggedInMembers(); break;
                case 4: WhichMembersUsedSystems (); break ;
                case 5: MenuCafeManagment();break;
                default : printf("Invalid choice ! Try again .");break;
            }
    } while(a != 5);
}
void MenuCafeManagment(){
    int a;
    do {
            printf("                                           MENU/Cafe Managment \n");
            printf("                                   ________________________________ \n ");
            printf("                                  |                                | \n");
            printf("                                   |   * 1-Booking.                 | \n");
            printf("                                   |   * 2-Charges.                 | \n");
            printf("                                   |   * 3-Back.                    | \n");
            printf("                                   |________________________________| \n");
            printf("\n                                      Select Your Choice :  ");
            scanf("%d",&a);
            switch (a) {
                case 1: booking();break;
                case 2: charges();break;
                case 3: Menu();break;
                default:printf("Invalid choice . Please try again !");
            }
    } while( a != 3);
}
void Menu(){
    int c ;
    printf(" \n                                               MENU \n ");
    printf("                                   ________________________________ \n ");
    printf("                                  |                                | \n");
    printf("                                   |   * 1-Master Entry.            | \n");
    printf("                                   |   * 2-Cafe Managment.          | \n");
    printf("                                   |   * 3-Coffee  Service          | \n ")
    printf("                                   |   * 3-Exit.                    | \n");
    printf("                                   |________________________________| \n");
    do{
            printf ("\n                                      Select Your Choice :  ");
            scanf("%d",&c);
            switch(c) {
                case 1:{
                MenuMasterEntry(); break;
                }
                case 2: MenuCafeManagment(); break;
                case 3: coffee_service(); break ;
                case 4: exit(1);break;
                default: printf("meeech mawjoud ");
            }
    } while ((c != 1) || (c != 2) || (c !=3) || (c !=4));
}
int main() {
    char name[15], n[15];
    char pass[15], p[15];
    int found ;

    printf("\n                                                  =========== LOG IN =============\n\n");
    printf("                                            ____________________________________________\n");

    do {
            printf("\n                                           * Enter the User name: ");
            scanf("%s", name);
            printf("\n                                           * Enter password: ");
            scanf("%s", pass);

            FILE *fp = fopen("admin.txt", "r");
            if (fp == NULL) {
                    printf("Error: Could not open admin.txt. Make sure the file exists.\n");
                    return 1;
            }

            found = 0;

            while (fscanf(fp, "%s %s", n, p) != EOF) {
                    if ((strcmp(name, n) == 0) && (strcmp(pass, p) == 0)) {
                        found = 1;
                        break;
                    }
            }

            fclose(fp);

            if (found == 0) {
                    printf("\n User name or password incorrect! Please try again.\n");
            } else {
                printf("\n Successfully logged in.\n");
            }
    } while (found == 0);
    Menu();
    return 0;
}

