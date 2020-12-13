#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    // create an input file stream using ifstream here called "is"
    // "is" is initialized using the"path" and two oftions binary and ate
    // binary means read data as a binary data
    // ate means standfor "at the end", which is seeking to the end of inputstream
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    // tellg method tells the size of inputstream
    auto size = is.tellg();
    // then create byte vector named "contents" initialized to that size
    std::vector<std::byte> contents(size);    
    
    // seek back to the begining 
    is.seekg(0);
    // read all of the inputstream into "contents" vector.
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    
    // retuen "contents" vector with std::move()
    return std::move(contents);
}

int main(int argc, const char **argv)
{   
    // code below pass a command line arguments 
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            // "-f" allows you to specify osm datafile that you want to use
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    // if ypu don't specify osm datafile, it will use map.osm
    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm";
    }
    
    // vector of byte called osm_data
    std::vector<std::byte> osm_data;
    
    // use ReadFile to read osm_data_file into vector osm_data
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    // TODO 1: Declare floats `start_x`, `start_y`, `end_x`, and `end_y` and get
    // user input for these values using std::cin. Pass the user input to the
    // RoutePlanner object below in place of 10, 10, 90, 90.
    float start_x, start_y, end_x, end_y;
    std::cout << "Enter start x:" << "\n";
    std::cin >> start_x;
    std::cout << "Enter start y:" << "\n";
    std::cin >> start_y;
    std::cout << "Enter end x:" << "\n";
    std::cin >> end_x;
    std::cout << "Enter end y:" << "\n";
    std::cin >> end_y;

    
    // Build Model.
    // create RouteModel object using osm_data called "model"
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search using model and the coordinates.
    RoutePlanner route_planner{model, start_x, start_y, end_x, end_y};
    // starting AstarSearch
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search has been created using model.
    Render render{model};

    // io2d code for display
    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
