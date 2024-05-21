SRCCODE_DIR = ./src/code
BIN_DIR = ./src/bin
DATA_DIR = ./src/data
IMAGES_DIR = ./src/images

ITM = ${BIN_DIR}/itm   # ITM needs to be build
PLOTTER = ${SRCCODE_DIR}/plotter.py

output:
	tectonic -X build

all: itm data imgs output

itm: ${SRCCODE_DIR}/integral_triangle_method.c
	mkdir -p ${BIN_DIR}
	gcc $< -fopenmp -lm -o ${ITM}

data:
	mkdir -p ${DATA_DIR}
	${ITM} > ${DATA_DIR}/data.csv

imgs:
	mkdir -p ${IMAGES_DIR}
	${PLOTTER} ${DATA_DIR}/data.csv ${IMAGES_DIR}/comparacion_speedup.png 0 3
	${PLOTTER} ${DATA_DIR}/data.csv ${IMAGES_DIR}/comparacion_efficiency.png 0 4

clean:
	rm -rf ${BIN_DIR}

.PHONY: clean

