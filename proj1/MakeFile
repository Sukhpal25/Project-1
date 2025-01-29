CXX = g++
CXXFLAGS = -std=c++17 -Wall
OBJDIR = obj
BINDIR = bin
SOURCES = StringUtils.cpp StringUtilsTest.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/teststrutils

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC)

test: $(EXEC)
	./$(EXEC)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
