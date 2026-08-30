#include<easyx.h>
#include"grassland.h"
#include"plant_registry.h"
#include"tool.h"

void grassland::planting(int row, int col,Planttype t) {
	if (row < 5 && col < 9) {
		printf("%d", t);
		land[row][col].emplace(t);
	}
	else {
		printf("%d  %d\n", row,col);
	}
}
void grassland::remove(int row, int col) {
	land[row][col] = std::nullopt;
}
void grassland::update() {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (land[i][j].has_value()&&land[i][j].value().gethp() <= 0)land[i][j] = std::nullopt;
			if (land[i][j].has_value())
				putimagePNG(170+j*80,90+i*100, &plant_registry::instance().get_plant_info(land[i][j].value().gettype()).plantimg);
		}
	}
	
}