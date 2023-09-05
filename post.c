#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
    // my code:
    printf("%s:\n",t.name);
    for (int i=0; i<t.offices_count;i++) {
        printf("\t%d:\n",i);
        for (int j=0; j<t.offices[i].packages_count;j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    // my code:
    town s = *source;
    town t = *target;
    package* rejected=malloc(sizeof(package)*s.offices[source_office_index].packages_count);
    package* accepted=malloc(sizeof(package)*s.offices[source_office_index].packages_count);
    int accepted_count=0,rejected_count=0;
    while (accepted_count+rejected_count<((s.offices)[source_office_index]).packages_count) {
        if ((((s.offices)[source_office_index]).packages)[accepted_count+rejected_count].weight >= ((t.offices)[target_office_index]).min_weight && (((s.offices)[source_office_index]).packages)[accepted_count+rejected_count].weight <= ((t.offices)[target_office_index]).max_weight) {
            accepted[accepted_count]=(((s.offices)[source_office_index]).packages)[accepted_count+rejected_count];
            ++accepted_count;
        } else {
            rejected[rejected_count]=(((s.offices)[source_office_index]).packages)[accepted_count+rejected_count];
            ++rejected_count;
        }
    }
    int original_count=t.offices[target_office_index].packages_count;
    t.offices[target_office_index].packages_count = t.offices[target_office_index].packages_count + accepted_count;
    for (int i=0;i<accepted_count;i++) {
        t.offices[target_office_index].packages=realloc(t.offices[target_office_index].packages, sizeof(package)*t.offices[target_office_index].packages_count);
        for (int k = original_count; k < t.offices[target_office_index].packages_count; k++) {
                t.offices[target_office_index].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                t.offices[target_office_index].packages[k].weight=accepted[k-original_count].weight;
                strcpy(t.offices[target_office_index].packages[k].id,accepted[k-original_count].id);
            }
    }
    for (int i=0;i<rejected_count;i++) {
        s.offices[source_office_index].packages[i]=rejected[i];
        s.offices[source_office_index].packages_count = rejected_count;
    }
}

// my code:
int count_packages_in_town(town t){
    int sum=0;
    for (int i=0;i<t.offices_count;i++) {
        sum += (t.offices[i]).packages_count;
    }
    return sum;
}

town town_with_most_packages(town* towns, int towns_count) {
    // my code:
    town most_town=towns[0];
    for (int i=0;i<towns_count;i++) {
        if (count_packages_in_town(towns[i])>count_packages_in_town(most_town)) {
            most_town=towns[i];
        }
    }
    return most_town;
}

town* find_town(town* towns, int towns_count, char* name) {
    // my code:
    for (int i=0;i<towns_count;i++) {
        if (strcmp(towns[i].name, name)==0) {
            return &towns[i];
        }
    }
    printf("problem");
    return &towns[0];
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}
