~/.openmpi/bin/mpicc token_pass.c -o token_pass
~/.openmpi/bin/mpirun -np $2 ./token_pass $1