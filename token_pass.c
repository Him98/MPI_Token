#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char** argv) {

	int token,total,curr_id,tmp_id,fl = 0;
	// Initializing
	MPI_Init(&argc,&argv);
	// printf("%s\n", argv[1]);
	// Finding rank(or id), size
	// MPI_COMM_WORLD acts as a communicator. Using this common communicator all MPI processes can communicate
	MPI_Comm_rank(MPI_COMM_WORLD,&curr_id);
	MPI_Comm_size(MPI_COMM_WORLD,&total);
	// Setting the token's value for process 0
	if(!curr_id)
		token = atoi(argv[1]);
	else
	{
		// Receive from the lower process and send to the higher process.
		tmp_id = curr_id - 1;
		MPI_Recv(&token,!fl,MPI_INT,tmp_id,fl,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Process %d received token %d from process %d\n",curr_id,token,tmp_id);
	}
	tmp_id = (curr_id + 1) % total;
	MPI_Send(&token,!fl,MPI_INT,tmp_id,fl,MPI_COMM_WORLD);
	// For the last process to pass token to process 0. Thus, one more MPI_Recv required.
	if (!curr_id)
	{
		MPI_Recv(&token,!fl,MPI_INT,total - 1,fl,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Process %d received token %d from process %d\n",curr_id,token,total - 1);
	}
	MPI_Finalize();
}