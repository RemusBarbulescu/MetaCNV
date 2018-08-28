#variable declaration

CC = g++
CFLAGS = -c -Wall 
GTKFLAGS = $(shell pkg-config --cflags --libs gtk+-3.0)

all: MetaCNV

MetaCNV: main.o new_segments.o new_segmentsF.o normalize.o normalizeF.o combine.o combineF.o \
	compress.o compressF.o normalize_XY.o combine_XY.o compress_XY.o match_to_ref.o \
	cnvnator.o cnvnatorsplit.o cnvnator_female.o mcnvgui.o
	$(CC) ./obj/main.o ./obj/new_segments.o ./obj/new_segmentsF.o ./obj/normalize.o ./obj/normalizeF.o \
	./obj/combine.o ./obj/combineF.o ./obj/compress.o ./obj/compressF.o ./obj/normalize_XY.o \
	./obj/combine_XY.o ./obj/compress_XY.o ./obj/match_to_ref.o ./obj/cnvnator.o ./obj/cnvnatorsplit.o \
	./obj/cnvnator_female.o ./obj/mcnvgui.o $(GTKFLAGS) -o ./bin/MetaCNV

main.o: ./src/main.cpp ./src/libraries.h ./src/structures.h ./src/new_segments/new_segments.h ./src/new_segments/new_segmentsF.h \
	./src/cnvnator/cnvnator.h ./src/cnvnator/cnvnator_female.h ./src/Interface/mcnvgui.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/main.cpp -o obj/$@

new_segments.o: ./src/new_segments/new_segments.cpp ./src/new_segments/new_segments.h \
	./src/combine/crunch.h ./src/normalize/normalize.h ./src/normalize/normalize_XY.h ./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/new_segments/new_segments.cpp -o obj/$@

new_segmentsF.o: ./src/new_segments/new_segmentsF.cpp ./src/new_segments/new_segmentsF.h \
	./src/combine/crunchF.h ./src/normalize/normalizeF.h ./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/new_segments/new_segmentsF.cpp -o obj/$@

normalize.o: ./src/normalize/normalize.cpp ./src/normalize/normalize.h ./src/combine/combine.h \
	./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/normalize/normalize.cpp -o obj/$@

normalizeF.o: ./src/normalize/normalizeF.cpp ./src/normalize/normalizeF.h ./src/combine/combineF.h \
	./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/normalize/normalizeF.cpp -o obj/$@

normalize_XY.o: ./src/normalize/normalize_XY.cpp ./src/normalize/normalize_XY.h ./src/combine/combine_XY.h \
	./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/normalize/normalize_XY.cpp -o obj/$@

combine.o: ./src/combine/combine.cpp ./src/combine/combine.h ./src/compress/compress.h ./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/combine/combine.cpp -o obj/$@

combineF.o: ./src/combine/combineF.cpp ./src/combine/combineF.h ./src/compress/compressF.h ./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/combine/combineF.cpp -o obj/$@

combine_XY.o: ./src/combine/combine_XY.cpp ./src/combine/combine_XY.h ./src/compress/compress_XY.h ./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/combine/combine_XY.cpp -o obj/$@

compress.o: ./src/compress/compress.cpp ./src/compress/compress.h ./src/match_to_ref/match_to_ref.h \
	./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/compress/compress.cpp -o obj/$@

compressF.o: ./src/compress/compressF.cpp ./src/compress/compressF.h ./src/match_to_ref/match_to_ref.h \
	./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/compress/compressF.cpp -o obj/$@

compress_XY.o: ./src/compress/compress_XY.cpp ./src/compress/compress_XY.h ./src/match_to_ref/match_to_ref.h \
	./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/compress/compress_XY.cpp -o obj/$@

match_to_ref.o: ./src/match_to_ref/match_to_ref.cpp ./src/match_to_ref/match_to_ref.h ./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/match_to_ref/match_to_ref.cpp -o obj/$@

cnvnator.o: ./src/cnvnator/cnvnator.cpp ./src/cnvnator/cnvnator.h ./src/cnvnator/cnvnatorsplit.h \
	./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/cnvnator/cnvnator.cpp -o obj/$@

cnvnatorsplit.o: ./src/cnvnator/cnvnatorsplit.cpp ./src/cnvnator/cnvnatorsplit.h ./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/cnvnator/cnvnatorsplit.cpp -o obj/$@

cnvnator_female.o: ./src/cnvnator/cnvnator_female.cpp ./src/cnvnator/cnvnator_female.h ./src/libraries.h ./src/structures.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/cnvnator/cnvnator_female.cpp -o obj/$@

mcnvgui.o: ./src/Interface/mcnvgui.cpp ./src/Interface/mcnvgui.h
	$(CC) $(CFLAGS) $(GTKFLAGS) ./src/Interface/mcnvgui.cpp -o obj/$@