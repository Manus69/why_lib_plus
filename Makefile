compiler = g++
flags = -g -Wall -Wextra
headers = $(wildcard *.h)
source_files = data_item.cpp polynomial.cpp support.cpp
run_file = test_run.cpp
object_dir = object_files/
run_file_object = $(subst .cpp,.o,$(addprefix $(object_dir),$(run_file)))
object_files = $(subst .cpp,.o,$(addprefix $(object_dir),$(source_files)))
binary_name = test_run

all: create test_run

$(object_dir)%.o : %.cpp $(headers)
	$(compiler) $(flags) -I. -c -o $@ $<

test_run: $(object_files) $(run_file_object) $(headers)
	$(compiler) $(flags) -I. -o $(binary_name) $(object_files) $(run_file_object)

clean:
	rm -f $(object_files) $(run_file_object)
	rm -f $(binary_name)

move:
	mv $(wildcard *.o) $(object_dir)

create:
	mkdir -p $(object_dir)

re:
	make clean
	make all
