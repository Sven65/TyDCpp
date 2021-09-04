include_directories(Nodes)
add_library (TyDCPP
	TydCPP.cpp TydCPP.hpp
	TydParser.hpp
	TydConstants.hpp
	Nodes/TydNode.hpp
	Nodes/TydCollection.hpp
	Nodes/TydDocument.hpp
	Nodes/TydList.hpp
	Nodes/TydString.hpp
	Nodes/TydTable.hpp
)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (TyDCPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})