ls_executable:
	gcc ls.c -o ls
rm_executable:
	gcc rm.c -o rm
cat_executable:
	gcc cat.c -o cat
date_executable:
	gcc date.c -o date
mkdir_executable:
	gcc mkdir.c -o mkdir
compile_final:
	gcc shell.c -o shell.out
run:
	./shell.out