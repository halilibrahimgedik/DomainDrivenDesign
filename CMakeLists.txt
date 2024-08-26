cmake_minimum_required(VERSION 3.29)
project(TestConnection)

set(CMAKE_CXX_STANDARD 20)
find_package(mongocxx CONFIG REQUIRED)

add_executable(TestConnection main.cpp
        domain/contact.hpp
        domain/contact-service.hpp
        domain/contact-repository.hpp
        domain/contact-factory.hpp
        application/contact-application-service.hpp
        MongoDbConnection.hpp
)

target_link_libraries(TestConnection PRIVATE
        $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
        $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
)