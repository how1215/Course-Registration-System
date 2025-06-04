# Makefile for Course Register System
# 編譯器設定
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -pthread
TARGET = system
SOURCE = system.cpp

# 預設目標
all: $(TARGET)

# 編譯規則
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# 執行程式
run: $(TARGET)
	./$(TARGET)

# 清理編譯產生的檔案
clean:
	rm -f $(TARGET)

# 重新編譯
rebuild: clean all

# 除錯版本
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# 宣告偽目標
.PHONY: all run clean rebuild debug

# 顯示幫助資訊
help:
	@echo "可用的目標："
	@echo "  all     - 編譯程式（預設）"
	@echo "  run     - 編譯並執行程式"
	@echo "  clean   - 清理編譯產生的檔案"
	@echo "  rebuild - 清理後重新編譯"
	@echo "  debug   - 編譯除錯版本"
	@echo "  help    - 顯示此幫助資訊" 