#include "Kernel.h"
#include "WWMParser.h"

map<string, WWMParser*> WWMParser::wwmParsers;

WWMParser::WWMParser() {
	width = 0;
	height = 0;
	grid_width = 0;
	grid_height = 0;
	cells.clear();
}

WWMParser* WWMParser::getInstance(const string& path) {
	if (wwmParsers.find(path) != wwmParsers.end()) {
		return wwmParsers[path];
	}
	WWMParser* theParser = new WWMParser();
	if (!theParser->parse(path)) {
		delete theParser;
		return NULL;
	}
	wwmParsers[path] = theParser;
	return theParser;
}

bool WWMParser::isMoveable(uint32_t x, uint32_t y) {
	x /= grid_width;
	y /= grid_height;
	if (x > width || y > height) {
		return false;
	}
	return cells[y * width + x] >= 1;
}

bool WWMParser::parse(const string& path) {
	string content;
	if (File::Read(path, content) != 0) {
		error_log("open file %s failed", path.c_str());
		return false;
	}
	MapReader reader(content.c_str(), content.length());
	uint32_t map_id = 0, mapWidth = 0, mapHeight = 0, ySize = 0, xSize = 0;
	if (!reader.GetInt32(map_id)) {
		error_log("get map id error");
		return false;
	}
	if (!reader.GetInt32(grid_width)) {
		error_log("get grid width error");
		return false;
	}
	if (!reader.GetInt32(grid_height)) {
		error_log("get grid height error");
		return false;
	}
	if (!reader.GetInt32(width)) {
		error_log("get grid x error");
		return false;
	}
	if (!reader.GetInt32(height)) {
		error_log("get grid y error");
		return false;
	}
	if (!reader.GetInt32(mapWidth)) {
		error_log("get map width error");
		return false;
	}
	if (!reader.GetInt32(mapHeight)) {
		error_log("get map height error");
		return false;
	}
	if (!reader.GetSize(ySize)) {
		error_log("get y size error");
		return false;
	}
	if (grid_width == 0 || grid_height == 0) {
		error_log("grid_width or grid_height error %u %u", grid_width, grid_height);
		return false;
	}
	cells.resize(width * height);
	if (ySize > height) {
		ySize = height;
	}
	for (uint32_t y = 0; y < ySize; ++y) {
		if (!reader.GetSize(xSize)) {
			error_log("get x size error y=%u", y);
			return false;
		}
		uint32_t n_pos = reader.GetPos() + xSize;
		if (xSize > width) {
			xSize = width;
		}
		for (uint32_t x = 0; x < xSize; ++x) {
			reader.GetByte(cells[y * width + x]);
		}
		if (!reader.SetPos(n_pos)) {
			error_log("set pos error y=%u", y);
			return false;
		}
	}
	debug_log("wwmap %s,%d,%d,%d,%d,%d,%d,%d",
			path.c_str(), map_id, grid_width, grid_height, width, height, mapWidth, mapHeight);
	return true;
}

