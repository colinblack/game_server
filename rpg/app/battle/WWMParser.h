#ifndef _WWM_PARSER_H_
#define _WWM_PARSER_H_

#include <string>
#include <map>
#include <vector>

using namespace std;

class WWMParser {
public:
	static WWMParser* getInstance(const string& path);

private:
	WWMParser();
	bool parse(const string& path);

public:
	uint32_t getWidth() const {
		return width;
	}
	uint32_t getHeight() const {
		return height;
	}
	uint32_t getGridWidth() const {
		return grid_width;
	}
	uint32_t getGridHeight() const {
		return grid_height;
	}
	bool isMoveable(uint32_t x, uint32_t y);

private:
	static map<string, WWMParser*> wwmParsers;

private:
	uint32_t width;
	uint32_t height;
	uint32_t grid_width;	//格子大小
	uint32_t grid_height;
	vector<byte> cells;

public:
	class MapReader {
	public:
		MapReader(const char *ptr, uint32_t len) {
			ptr_ = ptr;
			len_ = len;
			pos_ = 0;
		}
		bool GetInt32(uint32_t &v) {
			if (pos_ + 4 > len_) {
				return false;
			}
			memcpy(&v, ptr_ + pos_, 4);
			pos_ += 4;
			return true;
		}
		bool GetByte(byte &v) {
			if (pos_ + 1 > len_) {
				return false;
			}
			v = static_cast<unsigned char>(*(ptr_ + pos_));
			pos_ += 1;
			return true;

		}
		bool GetSize(uint32_t &v) {
			byte len = 0;
			if (!GetByte(len)) {
				return false;
			}
			if (len < 255) {
				v = len;
				return true;
			}
			return GetInt32(v);
		}
		bool SetPos(uint32_t p) {
			if (p > len_) {
				return false;
			}
			pos_ = p;
			return true;
		}
		uint32_t GetPos() {
			return pos_;
		}
	private:
		uint32_t pos_;
		uint32_t len_;
		const char *ptr_;
	};
};

#endif
