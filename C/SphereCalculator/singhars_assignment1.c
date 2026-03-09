/*
Shawn Singharaj
CS374
10/12/2025

Sphere Segment Statistical Calculator
*/

#include <stdio.h>
#include <math.h>


void calculate(float *r, float *ha, float *hb, float *total_area, float *volume){
  // formulas followed as per assignment
  float a = sqrt(((*r) * (*r)) - ((*ha) * (*ha)));
  float b = sqrt(((*r) * (*r)) - ((*hb) * (*hb))); 
  float h = (*ha) - (*hb);
  float top_area = 3.14159265359 * (a * a);
  float bottom_area = 3.14159265359 * (b * b);
  float lat_area = (2 * 3.14159265359) * (*r) * h;

  *total_area = top_area + bottom_area + lat_area;
  *volume = ((1.0 / 6.0) * 3.14159265359 * h) * ((3 * (a * a)) + (3 * (b * b)) + (h * h));

  // area and volume for each segment printed here
  printf("\nTotal Surface Area= ");
  printf("%.2f", *total_area);
  printf("  Volume= ");
  printf("%.2f", *volume);
  printf("\n\n");
};

int main(void)
{
  // initialize vars
  int num_seg;
  float radius, ha, hb, area, volume;
  float avg_area, avg_volume = 0;

  // prompt for num seg
  printf("How many spherical segments do you want to evaluate?[2-10]\n");
  scanf("%d", &num_seg);

  // if messes up
  while(num_seg < 2 || num_seg > 10){
    printf("Invalid input, try again:\n");
    scanf("%d", &num_seg);
  }
 
  int i = 1;
  while(i <= num_seg){
    printf("\nObtaining data for spherical segment ");
    printf("%d", i);

    do{ // obtain data
      printf("\nWhat is the radius of the sphere (R)?");
      scanf("%f", &radius);
      printf("\nWhat is the height of the top area of the spherical segment (ha)?");
      scanf("%f", &ha);
      printf("\nWhat is the height of the bottom area of the spherical segment (hb)?");
      scanf("%f", &hb);
      
      // reread back
      printf("\nEntered data: R= ");
      printf("%.2f", radius);
      printf(" ha= ");
      printf("%.2f", ha);
      printf(" hb= ");
      printf("%.2f", hb);

      // if invalid
      if(radius <= 0 || ha <= 0 || hb <= 0 || ha > radius || hb > ha){
        printf("\nInvalid input(s), try again.\n");
      } 
      
      // call helper function
      else{
        calculate(&radius, &ha, &hb, &area, &volume);
        avg_area += area; // accumulate area and vol
        avg_volume += volume;
      }

    }while(radius <= 0 || ha <= 0 || hb <= 0 || ha > radius || hb > ha);
    i++;
  }

  // find averages
  avg_area /= num_seg;
  avg_volume /= num_seg;

  printf("Total Average Results:\n");
  printf("Average Total Area= ");
  printf("%.2f", avg_area);
  printf("\nAverage Volume= ");
  printf("%.2f", avg_volume);
  printf("\n");

  return 0;
}

