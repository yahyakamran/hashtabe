#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define TABLE_LEN 10
#define NAME_MAX 256

typedef struct student{
    char name[NAME_MAX];
    int roll_no;
    struct student * next;
} student;

student * hashtable[TABLE_LEN];

int hash(char *str){
    int sum = 0;
    for(int i = 0; str[i] != '\0' ; ++i){
        sum += str[i];
    }
    return sum % TABLE_LEN;
}

void print_table(){
    for(int i = 0 ; i < TABLE_LEN ; ++i){
        if(hashtable[i] == NULL){
            printf("%d \t ------\n",i);
        }else{
            student * tmp = hashtable[i];
            while (tmp != NULL) {
                printf("%d \t Name : %s   Roll Number : %d\n",
                        i,
                        tmp->name ,
                        tmp->roll_no
                        );
                tmp = tmp->next;
            }
        }
    }
}

int add_in_hashtable(student * p){
    if(!p) return 1;
    int index = hash(p->name);
    p->next = hashtable[index];
    hashtable[index] = p;
    return 0;
}

student * find_in_hashtable(char * name){
    int index = hash(name);
    student * tmp = hashtable[index];
    while(tmp != NULL &&
            strncmp(tmp->name, name ,NAME_MAX) != 0){
                tmp = tmp->next;
    }
    return  tmp;
}

student * delete_from_hashtable(char * name){
    int index = hash(name);
    student * temp = hashtable[index];
    student * prev = NULL;
    while (temp && strcmp(temp->name,name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL) return NULL;
    if(prev == NULL){
        hashtable[index] = temp->next;
    }else {
        prev->next = temp->next;
    }
    return temp;
}
int main (void){
    for(int i = 0 ; i < TABLE_LEN ; ++i){
        hashtable[i] = NULL;
    }
    student ali = {.name = "ali" , .roll_no = 10};
    student yahya = {.name = "yahya" , .roll_no = 12};
    student ahmed = {.name = "ahmed" , .roll_no = 11};
    student farah = {.name = "farah" , .roll_no = 13};
    add_in_hashtable(&ali);
    add_in_hashtable(&yahya);
    add_in_hashtable(&ahmed);
    add_in_hashtable(&farah);
    print_table();
    student * tmp = find_in_hashtable("farah");
    if(tmp == NULL){
        printf("Not Found\n");
    }else{
        printf("Found %s\n",tmp->name);
    }
    student * deleted = delete_from_hashtable("ali");
    if(!deleted){
        printf("Not Found\n");
    }else{
        printf("Found and Deleted %s\n",deleted->name);
    }
    print_table();
    return 0;
}
