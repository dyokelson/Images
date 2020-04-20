SRC=main3H.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C logging.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3H

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj3H
