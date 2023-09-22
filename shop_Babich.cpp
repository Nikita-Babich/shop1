#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define n printf("\n")

errno_t err;

const char filename[] = "data.txt";
char buffer[100];
int start_money = 100;
int final_money;
int database_size;

//---

struct PRODUCT {
    int ID;
    char name[20];
    char manufacturer[20];
    int amount;
    int price;
}
struct PRODUCT* database;
struct PRODUCT goods[50];
int print_product(struct PRODUCT* instance){
	printf("ID=%d, \t %s \t %s", instance->ID, instance->name, instance->manufacturer);
}
struct PRODUCT* read_file(){ //returns the pointer to dataset
	struct PRODUCT* new_database = (struct PRODUCT*) malloc ()
	int size = 0;
	FILE* textFileInput;
	err = fopen_s(&textFileInput, "data.txt", "r");
	struct PRODUCT* new_database = (struct PRODUCT*) malloc (sizeof(struct PRODUCT) * database_size);
	for(int i = 0; i < database_size; i++){
		fscanf(textFileInput, "%d %s %s %d %d", 
			&new_database[i]->ID,
			new_database[i]->name,
			new_database[i]->manufacturer,
			&new_database[i]->amount,
			&new_database[i]->price,
		)
	}
	fclose(textFileInput);
	return size; //?
}

//---

struct ZAKAZNIK {
    char name[20];
    char surname[20];
    int budget;
    int deals;
}
struct ZAKAZNIK user;
struct ZAKAZNIK get_user_info(){
	struct ZAKAZNIK new_user;
	printf("Input your name and surname\n");
	scanf("%s %s", &(new_user.name), &(new_user.surname));
	printf("Input your budget\n");
	scanf("%d", &(new_user.budget));
	new_user.deals = 0;
	return new_user;
}

int search_by_name(){
	
}

int search_by_manufacturer(){
	
}

int search(){
	char choice = '0';
	int finish_flag = 0;
	while(true){
		printf("1 - search by name, \t 2 - search by manufacturer, \t 3 - finish shopping \n");
		read_char(&choice);
		switch(choice) {
			case '1':
				printf("input the name: \n");
				search_by_name();
				break;
			case '2':
				printf("input the manufacturer: \n");
				search_by_manufacturer();
			default:
		}
		
		if (choice != '3'){
			//choose id to get further info
			//print the id
			//will you buy?
			//update report
		} else {
			printf("Thank you for choosing us \n");
			break
		}
	}
}

int report(){
	printf("Total cost: %d \n", )
}

int main(){
	user = get_user_info();
	database = (struct PRODUCT*) read_file();
	
    search();
    report();
    return 0;
}
