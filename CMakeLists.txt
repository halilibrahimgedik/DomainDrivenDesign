cmake_minimum_required(VERSION 3.29)
project(TestConnection)

set(CMAKE_CXX_STANDARD 20)
find_package(mongocxx CONFIG REQUIRED)

add_executable(TestConnection main.cpp
        domain/Contact/contact.hpp
        domain/Contact/contact-service.hpp
        domain/Contact/contact-repository.hpp
        domain/Contact/contact-factory.hpp
        application/contact-application-service.hpp
        domain/MongoDbConnection.hpp
        domain/History/history.hpp
        domain/History/history-repository.hpp
        domain/History/history-factory.hpp
        domain/History/history-service.hpp
)

target_link_libraries(TestConnection PRIVATE
        $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>
        $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>
)