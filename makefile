# Make
CC= gcc

# Kompilerings- och länkningskommandot
CFLAGS= -g -c -Wall

# Flaggor för kompilering
LDFLAGS= -g

# Flaggor för länkning
OBJECTS= db.o db_functions.o print_functions.o # Objektkodsfilerna

main: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o db
print_functions.o: print_functions.c print_functions.h
	$(CC) $(CFLAGS) print_functions.c
db_functions.o: db_functions.c db_functions.h
	$(CC) $(CFLAGS) db_functions.c
db.o: db.c db_functions.h print_functions.h
	$(CC) $(CFLAGS) db.c
