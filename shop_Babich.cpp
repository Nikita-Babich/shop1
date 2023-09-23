#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define n printf("\n")

errno_t err;

const char filename[] = "data.txt";
const char check[] = "check.txt";
//char buffer[100];
int start_money;
int final_money;
int database_size;

//---

struct PRODUCT {
    int ID;
    char name[20];
    char manufacturer[20];
    int amount;
    int price;
};
struct PRODUCT* database;
void print_product(struct PRODUCT* instance){
	printf("ID=%d, \t %s \t %s \n", instance->ID, instance->name, instance->manufacturer);
	return;
}
void print_product2(struct PRODUCT* instance){
	printf("ID=%d, \t %s \t %s \n", instance->ID, instance->name, instance->manufacturer);
	printf("Amount = %d, \t Price = %d \n", instance->amount, instance->price);
	return;
}
struct PRODUCT* read_file(){ 
	FILE* textFileInput;
	err = fopen_s(&textFileInput, "data.txt", "r");
	fscanf(textFileInput, "%d", &database_size);
	struct PRODUCT* new_database = (struct PRODUCT*) malloc (sizeof(struct PRODUCT) * database_size);
	for(int i = 0; i < database_size; i++){
		fscanf(textFileInput, "%d %s %s %d %d", 
			&new_database[i].ID,
			new_database[i].name,
			new_database[i].manufacturer,
			&new_database[i].amount,
			&new_database[i].price
		);
	}
	fclose(textFileInput);
	return new_database; 
}

//---

struct ZAKAZNIK {
    char name[20];
    char surname[20];
    int budget;
    int deals;
    struct PRODUCT goods[50];
};
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

//---
int string_equal(char first[20], char second[20]){
	for (int i = 0; i < 20; i++){
		if (first[i] != second[i]){
			return 0;
		} else if (first[i] == '\0'){
			return 1;
		}
	}
	return 1;
}
void search_by_name(char input[20]){
	for( int i = 0; i < database_size; i++){
		if (string_equal(database[i].name, input)){
			print_product(&database[i]);
		}
	}
	return;
}
void search_by_manufacturer(char input[20]){
	for( int i = 0; i < database_size; i++){
		if (string_equal(database[i].manufacturer, input)){
			print_product(&database[i]);
		}
	}
	return;
}
int find_dataset_pos_by_id(int id){
	int position;
	for( int i = 0; i < database_size; i++){
		if (id == database[i].ID){
			position = i;
			break;
		}
	}
	return position;
}
void search(){
	char choice = '0';
	char searchtext[20];
	int choice2 = -1;
	int dataset_pos = -1;
	int finish_flag = 0;
	while(true){
		printf("1 - search by name, \t 2 - search by manufacturer, \t 3 - finish shopping \n");
		scanf("%s", &choice); //read_char(&choice); //choice = getchar();
		getchar();
		switch(choice) {
			case '1':
				printf("input the name: \n");
				scanf("%s", &searchtext);
				getchar();
				search_by_name(searchtext);
				break;
			case '2':
				printf("input the manufacturer: \n");
				scanf("%s", &searchtext);
				getchar();
				search_by_manufacturer(searchtext);
			default: ;
		}
		
		if (choice != '3'){
			printf("Choose id to get further info\n");
			scanf("%d", &choice2);
			//getchar();
			printf("Here is the info about the product:\n");
			dataset_pos = find_dataset_pos_by_id(choice2);
			print_product2(&database[dataset_pos]);
			printf("Will you buy the product? A - yes, N - no\n");
			scanf("%s", &choice); 
			//getchar();
			if (choice == 'A'){
				user.budget -= database[dataset_pos].price;
				user.goods[user.deals] = database[dataset_pos]; // a[b] = *(a+b*struct_size)
				user.deals++;
				//update report
			}
		} else {
			printf("Thank you for choosing us \n");
			break;
		}
	}
	return;
}

//---

void report(){
	final_money = start_money - user.budget;
	printf("Total cost: %d \n", final_money);
	for(int i = 0; i < user.deals; i++){
		print_product(&user.goods[i]);
	}
	FILE* textFileInput;
	err = fopen_s(&textFileInput, check, "w");
	fprintf(textFileInput,"%s, %s\n", user.name, user.surname);
	for(int i = 0; i < user.deals; i++){
		fprintf(textFileInput,"%s, %s, price=%d\n", user.goods[i].name, user.goods[i].manufacturer, user.goods[i].price);
	}
	fprintf(textFileInput,"Total: %d\n");
}

int main(){
	user = get_user_info();
	database = (struct PRODUCT*) read_file();
    search();
    report();
    return 0;
}
