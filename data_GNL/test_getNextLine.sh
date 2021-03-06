echo '[test] BUFFER_SIZE=8 check'
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=8 main_get_next_line.c get_next_line.c get_next_line_utils.c
./a.out data_GNL/data.txt > result_8.txt
diff data_GNL/data.txt result_8.txt
echo '[test] BUFFER_SIZE=1 check'
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 main_get_next_line.c get_next_line.c get_next_line_utils.c
./a.out data_GNL/data.txt > result_1.txt
diff data_GNL/data.txt result_1.txt
echo '[test] BUFFER_SIZE=1024 check'
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 main_get_next_line.c get_next_line.c get_next_line_utils.c
./a.out data_GNL/data.txt > result_1024.txt
diff data_GNL/data.txt result_1024.txt
echo '[test] BUFFER_SIZE=9999 check'
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 main_get_next_line.c get_next_line.c get_next_line_utils.c
./a.out data_GNL/data.txt > result_9999.txt
diff data_GNL/data.txt result_9999.txt
echo '[test] BUFFER_SIZE=10000000 check'
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=10000000 main_get_next_line.c get_next_line.c get_next_line_utils.c
./a.out data_GNL/data.txt > result_10000000.txt
diff data_GNL/data.txt result_10000000.txt
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 main_get_next_line.c get_next_line.c get_next_line_utils.c
echo '[test] STDIN check'
./a.out < data_GNL/data.txt > result_stdin.txt
diff data_GNL/data.txt result_stdin.txt
echo '[test] Empty file check'
./a.out < data_GNL/data_empty.txt > result_empty.txt
diff data_GNL/data_empty.txt result_empty.txt
rm -f result*.txt
echo '[test] Bonus multiple files read'
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=128 main_get_next_line_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
./a.out data_GNL/data_abc.txt data_GNL/data_123.txt data_GNL/data_ZYX.txt
