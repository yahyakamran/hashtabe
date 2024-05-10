#include <stdio.h>
#include <string.h>

#define TABLE_LEN 10
#define NAME_MAX 256

typedef struct{
    char name[NAME_MAX];
    int roll_no;
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
            printf("%d \t Name : %s   Roll Number : %d\n",
                    i,
                    hashtable[i]->name ,
                    hashtable[i]->roll_no
                    );
        }
    }
}

int add_in_hashtable(student * p){
    if(!p) return 1;
    int index = hash(p->name);
    if(hashtable[index] != NULL){
        return 1;
    }
    hashtable[index] = p;
    return 0;
}

student * find_in_hashtable(char * name){
    int index = hash(name);
    if(hashtable[index] != NULL && strcmp(hashtable[index]->name,name) == 0){
        return hashtable[index];
    }
    else {
        return NULL;
    }
}

student * delete_from_hashtable(char * name){
    int index = hash(name);
    if(hashtable[index] != NULL && strcmp(hashtable[index]->name,name) == 0){
        student * tmp = hashtable[index];
        hashtable[index] = NULL;
        return tmp;
    }
    else {
        return NULL;
    }
}

void update_table(student * p){
    int index = hash(p->name);
    hashtable[index] = p;
}

int main (void){
    for(int i = 0 ; i < TABLE_LEN ; ++i){
        hashtable[i] = NULL;
    }
    student ali = {.name = "ali" , .roll_no = 10};
    student ahmed = {.name = "ahmed" , .roll_no = 11};
    student yahya = {.name = "yahya" , .roll_no = 12};
    student farah = {.name = "farah" , .roll_no = 13};
    add_in_hashtable(&yahya);
    add_in_hashtable(&ali);
    add_in_hashtable(&ahmed);
    add_in_hashtable(&farah);
    print_table();
    student * tmp = find_in_hashtable("yahya");
    if(tmp == NULL){
        printf("Not Found\n");
    }else{
        printf("Found %s\n",tmp->name);
    }
    student * deleted = delete_from_hashtable("yahya");
    if(!deleted){
        printf("Not Found\n");
    }else{
        printf("Found and Deleted %s\n",deleted->name);
    }
    print_table();
    update_table(&ali);
    print_table();
    return 0;
}
