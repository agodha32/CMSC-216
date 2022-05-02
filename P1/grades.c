#define MAX 50

#include <stdio.h>
#include <math.h>

/* Calculate the mean  */

float calculate_mean(int score_array[MAX], int number_of_assns) {

  int assn_number = 0, total_score = 0;
  float to_return = 0;

  for(assn_number = 0; assn_number < number_of_assns; assn_number++) {
			
    total_score = total_score + score_array[assn_number];

  }

  to_return = (float) total_score / number_of_assns;

  return to_return; 

}

/* Calculate the Standard Deviation */

float calculate_std_dev(int score_array[MAX], int number_of_assns) {

  float mean_score = calculate_mean(score_array, number_of_assns);
 
  int std_dev_squared[MAX] = {0};	

  int assn_num = 0, num_square = 0;

  float variance = 0, std_dev = 0;

  for(assn_num = 0; assn_num < number_of_assns; assn_num++) {

    num_square = (score_array[assn_num] - mean_score);
    std_dev_squared[assn_num] = (num_square * num_square);	

  }

  variance = calculate_mean(std_dev_squared, number_of_assns);
  std_dev = sqrt(variance);

  return std_dev;

}

/* Calculate the Numeric Score */

  float calculate_numeric_score(int score_array[MAX], 
	int weight_array[MAX], int num_assign) {

  float numeric_score = 0;
  int assn_number = 0, total_weight_score = 0, total_weight = 0;

  for(assn_number = 0; assn_number < num_assign; assn_number++) {

    numeric_score = (score_array[assn_number] * weight_array[assn_number]);	
    total_weight_score += numeric_score;	
    total_weight += weight_array[assn_number];

  }

  numeric_score = (float) total_weight_score / total_weight;

  return numeric_score;

}

int main() {

/* Variable Initalization */

  int num_assns = 0, points_penalty_per_day_late = 0;
  int assn_number = 0, num_assns_to_drop = 0;
  char statistical_info = 0;
	
  int read_assn = 0, read_score = 0, read_weight = 0, read_late = 0;

  int assn_score[MAX] = {0};
  int assn_weight[MAX] = {0};
  int days_late[MAX] = {0};
  int real_score[MAX] = {0};
  int adj_score[MAX] = {0};

  int total_weight = 0, adj_num_assns = 0;
  int assn_removed = 0, lowest_score = 0, score_adj = 0;	
  float mean = 0, std_dev = 0, n_score = 0;

/* Get Input */

  scanf(" %d%d %c", &points_penalty_per_day_late, 
		&num_assns_to_drop, &statistical_info);
  scanf("%d", &num_assns);
		
  adj_num_assns = num_assns;

  for(assn_number = 0; assn_number < num_assns; assn_number++) {
	
    scanf("%d, %d, %d, %d", &read_assn, &read_score, &read_weight, &read_late);
		
    assn_score[read_assn - 1] = read_score;	
    assn_weight[read_assn - 1] = read_weight;
    days_late[read_assn - 1] = read_late;
    real_score[read_assn - 1] = read_score;				

    total_weight += read_weight;
		
  }

/* Check if weight is correct */

  if(total_weight != 100) {

    printf("ERROR: Invalid values provided\n");
		
    return 0;

  }

/* Assigning late score */

  for(assn_number = 0; assn_number < num_assns; assn_number++) {

    score_adj = (assn_score[assn_number]  - (days_late[assn_number]
		 * points_penalty_per_day_late)); 

    assn_score[assn_number] = score_adj;
		adj_score[assn_number] = score_adj;

  }

/* Dropping Assignments */

  assn_removed = 0;

  while(assn_removed != num_assns_to_drop) {
		
    assn_removed++;		
    lowest_score = 0;

    for(assn_number = 0; assn_number < num_assns; assn_number++) {

      if(adj_score[lowest_score] > adj_score[assn_number]) {

	lowest_score = assn_number;

      } 
		
    }

    for(assn_number = lowest_score; assn_number < num_assns; assn_number++) {
		                   
      adj_score[assn_number] = adj_score[assn_number + 1];

    }

    adj_num_assns--;		

  }

  n_score =  calculate_numeric_score(adj_score, assn_weight, adj_num_assns);

/* Printing Basic Information */

  printf("Numeric Score: %5.4f\n", n_score);
  printf("Points Penalty Per Day Late: %d\n", points_penalty_per_day_late);
  printf("Number of Assignments Dropped: %d\n", num_assns_to_drop);
  printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");

  for(assn_number = 0; assn_number < num_assns; assn_number++) {

    printf("%d, %d, ", (assn_number + 1), real_score[assn_number]);
    printf("%d, %d\n",assn_weight[assn_number], days_late[assn_number]);

  }

/* Printing Statistical Inforrmantion */

  if(statistical_info == 'y' || statistical_info == 'Y') {

    mean = calculate_mean(assn_score, num_assns);
    std_dev = calculate_std_dev(assn_score, num_assns);

    printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean, std_dev);

  }	


  return 1;

}
