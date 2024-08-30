#!/bin/bash

file_to_edit="src/fractol.c"

check_if_modified()
{
		mod_executable=$(stat -c %Y fractol)
		mod_file_to_edit=$(stat -c %Y "$file_to_edit")
		[[ "$mod_executable" < "$mod_file_to_edit" ]] && make_and_compile
}

make_and_compile()
{
		clear
		make
		echo -e "\n--start--\n"
		./fractol M
}

make_and_compile
while true; do
	sleep 1
	check_if_modified
done
