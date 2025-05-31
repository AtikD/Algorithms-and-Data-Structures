add_executable(Application main.cpp)
target_link_libraries(Application PRIVATE 
    EasyExample TPair TMassive TCalculator TVector TStack TQueue TList TAlgorithms TMatrix
)
target_compile_definitions(Application PRIVATE STACKEXPERIMENTS)

add_executable(Heap heap.cpp)
target_link_libraries(Heap PRIVATE 
    THeap TMassive
)

add_executable(Hash hash.cpp)
target_link_libraries(Hash PRIVATE 
    THash
)
