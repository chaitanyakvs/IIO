#include <stdio.h>
#include <stdlib.h>
int main()

{

	FILE *in_file;
	// To get the details of temperature //
	float temp;
	in_file = fopen("sys/bus/iio/devices/iio:deviceX/temp_input", "r");
	fscanf("in_file, "%f", &air_temp);
	temp = temp/1000;
	
	printf("The temperature is :\n", temp);
	fclose(in_file);

}
