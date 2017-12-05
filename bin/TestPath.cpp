#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Minions.h"
#include "XMLParser.h"
#include "Larry.h"
#include "TextureManager.h"
#include "TerrainManager.h"
#include "util.h"
#include "math.h"

std::vector<sf::Vector2f> expand_polygon(std::vector<sf::Vector2f> source_polygon, double expand_size)
{
	double x_offset, y_offset;
	double x_size, y_size;
	double x_ratio, y_ratio;

	x_offset = source_polygon[0].x;
	y_offset = source_polygon[0].y;
	x_size = source_polygon[0].x;
	y_size = source_polygon[0].y;

	for (int i = 1; i < source_polygon.size(); i++)
	{
		if ( source_polygon[i].x < x_offset )
			x_offset = source_polygon[i].x;

		if (source_polygon[i].y < y_offset)
			y_offset = source_polygon[i].y;

		if (source_polygon[i].x > x_size)
			x_size = source_polygon[i].x;

		if (source_polygon[i].y > y_size)
			y_size = source_polygon[i].y;
	}

	std::vector<sf::Vector2f> output_polygon;
	for (int i = 0; i < source_polygon.size(); i++)
	{

		output_polygon.push_back(sf::Vector2f(source_polygon[i].x - x_offset, source_polygon[i].y - y_offset));
	}

	x_size -= x_offset;
	y_size -= y_offset;

	x_ratio = (x_size + 2 * expand_size) / x_size;
	y_ratio = (y_size + 2 * expand_size) / y_size;

	for (int i = 0; i < output_polygon.size(); i++)
	{
		output_polygon[i].x = output_polygon[i].x * x_ratio;
		output_polygon[i].y = output_polygon[i].y * y_ratio;
	}

	for (int i = 0; i < output_polygon.size(); i++)
	{
		output_polygon[i].x = output_polygon[i].x + x_offset - expand_size;
		output_polygon[i].y = output_polygon[i].y + y_offset - expand_size;
	}

	return output_polygon;
}


sf::Vector2f line_intersection(sf::Vector2f line1_start_point, sf::Vector2f line1_end_point, sf::Vector2f line2_start_point, sf::Vector2f line2_end_point)
{
	sf::Vector2f intersection_point(-10000, -10000);

	double dy1 = line1_end_point.y - line1_start_point.y;
	double dx1 = line1_end_point.x - line1_start_point.x;
	double dy2 = line2_end_point.y - line2_start_point.y;
	double dx2 = line2_end_point.x - line2_start_point.x;

	if (dy1 * dx2 != dy2 * dx1)
	{
		double x, y;

		x = ((line2_start_point.y - line1_start_point.y) * dx1 * dx2 + dy1 * dx2 * line1_start_point.x - dy2 * dx1 * line2_start_point.x) / (dy1 * dx2 - dy2 * dx1);
		if (dx1 != 0)
			y = line1_start_point.y + (dy1 / dx1) * (x - line1_start_point.x);
		else
			y = line2_start_point.y + (dy2 / dx2) * (x - line2_start_point.x);

		intersection_point.x = x;
		intersection_point.y = y;
	}

	return intersection_point;
}

int polygon_intersect_line(sf::Vector2f line_start_point, sf::Vector2f line_end_point, std::vector<sf::Vector2f> polygon) 
{
	sf::Vector2f current_point, next_point;
	sf::Vector2f intersect_point;

	double line_min_x, line_max_x, line_min_y, line_max_y;
	int rc = 0;

	if (line_start_point.x < line_end_point.x)
	{
		line_min_x = line_start_point.x;
		line_max_x = line_end_point.x;
	}
	else
	{
		line_min_x = line_end_point.x;
		line_max_x = line_start_point.x;
	}
	if (line_start_point.y < line_end_point.y)
	{
		line_min_y = line_start_point.y;
		line_max_y = line_end_point.y;
	}
	else
	{
		line_min_y = line_end_point.y;
		line_max_y = line_start_point.y;
	}
	for (int i = 0; i < polygon.size(); i++)
	{
		current_point = polygon[i];
		if (i < polygon.size() - 1)
			next_point = polygon[i + 1];
		else
			next_point = polygon[0];

		if ((current_point.x <= line_min_x) && (next_point.x <= line_min_x))
			continue;

		if ((current_point.x >= line_max_x) && (next_point.x >= line_max_x))
			continue;

		if ((current_point.y <= line_min_y) && (next_point.y <= line_min_y))
			continue;

		if ((current_point.y >= line_max_y) && (next_point.y >= line_max_y))
			continue;

		intersect_point = line_intersection(line_start_point, line_end_point, current_point, next_point);
		if (intersect_point.x > -10000)
		{
			if (line_min_x != line_max_x)
			{
				if ((intersect_point.x > line_min_x) && (intersect_point.x < line_max_x))
				{
					rc = 1;
					break;
				}
			}
			else
			{
				if ((intersect_point.y > line_min_y) && (intersect_point.y < line_max_y))
				{
					rc = 1;
					break;
				}
			}
		}
	}
	return rc;
}
sf::Vector2f getPath(sf::Vector2f target_point, sf::Vector2f source_point, std::vector<std::vector<sf::Vector2f>> polygons) {
	sf::Vector2f output_point;
	sf::Vector2f new_point;

	double current_distance, source_distance, target_distance;
	int vertex_index;
	int rc;

	output_point.x = target_point.x;
	output_point.y = target_point.y;
	source_distance = sqrt((source_point.x - target_point.x) * (source_point.x - target_point.x) + (source_point.y - target_point.y) * (source_point.y - target_point.y));
	target_distance = 2048;

	for (auto const& polygon : polygons)
	{
		rc = polygon_intersect_line(source_point, target_point, polygon);
		if (rc == 1)
		{	
			for (auto const& vertex : polygon)
			{
				for (auto const& polygon1 : polygons) {

					rc = polygon_intersect_line(source_point, vertex, polygon1);
					if(rc==1)
						break;

				}
				if ( rc == 0 )
				{
					current_distance = sqrt((target_point.x - vertex.x) * (target_point.x - vertex.x) + (target_point.y - vertex.y) * (target_point.y - vertex.y));
					current_distance += sqrt((source_point.x - vertex.x) * (source_point.x - vertex.x) + (source_point.y - vertex.y) * (source_point.y - vertex.y));
					if (current_distance > 0)
					{
						if (current_distance < target_distance)
						{
							target_distance = current_distance;
							output_point.x = vertex.x;
							output_point.y = vertex.y;
						}
					}
				}
			}
		}
	}

	return output_point;
}

int main(int argc, char** argv)
{
	// Resource Managers
	TextureManager textures;
	XMLParser parser;
	TerrainManager terrain;

	// Fish
	sf::Vertex line[2];
	Minions minion(sf::Vector2f(700,200));
	Larry larry;

	// create main window
	sf::RenderWindow App(sf::VideoMode(1024,768,32), "Path - SFML",sf::Style::Titlebar|sf::Style::Close);

	// add textures
	parser.loadXML("../data/xml/TestXML.xml");
	parser.loadTexture(textures, "fish");

	minion.setTexture(textures.get("fish").texture);
	minion.setTextureAreas(textures.get("fish").areas);
	larry.setTexture(textures.get("fish").texture);
	larry.setTextureAreas(textures.get("fish").areas);

	minion.init();
	larry.init();

	// create terrain with verticies
	std::vector<std::vector<sf::Vector2f>> test;
	std::vector<std::vector<sf::Vector2f>> expand_test;
	std::vector<sf::Vector2f> shape1;
	shape1.push_back(sf::Vector2f(10,10));
	shape1.push_back(sf::Vector2f(200,30));
	shape1.push_back(sf::Vector2f(50,150));
	test.push_back(shape1);
	expand_test.push_back(expand_polygon(shape1,minion.getHeadDistance()));

	std::vector<sf::Vector2f> shape2;
	shape2.push_back(sf::Vector2f(500,600));
	shape2.push_back(sf::Vector2f(400,300));
	shape2.push_back(sf::Vector2f(600,400));
	test.push_back(shape2);
	expand_test.push_back(expand_polygon(shape2,minion.getHeadDistance()));
	
	std::vector<sf::Vector2f> shape3;
	shape3.push_back(sf::Vector2f(700,60));
	shape3.push_back(sf::Vector2f(770,60));
	shape3.push_back(sf::Vector2f(850,100));
	shape3.push_back(sf::Vector2f(650,100));
	test.push_back(shape3);
	expand_test.push_back(expand_polygon(shape3,minion.getHeadDistance()));
	terrain.load(test);

    // start main loop
	sf::Clock clock;
	while(App.isOpen())
	{
    // process events
		sf::Event event;
		while (App.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
				App.close();
				break;
				default:
				break;
			}
		}
    	// clear screen and fill with blue
		App.clear(sf::Color::Blue);
		
		sf::Vector2i mousePos=sf::Mouse::getPosition(App);
		larry.swimTo(sf::Vector2f(mousePos.x,mousePos.y));
		larry.update(0);
		minion.update(0);

		//show path to take between fish
		line[0] = minion.getKnot(0).getPosition();
		line[1] = getPath(larry.getKnot(0).getPosition(),minion.getKnot(0).getPosition(),expand_test);

		App.draw(terrain);
		App.draw(larry);
		App.draw(minion);
		App.draw(line, 2, sf::Lines);
		App.display();
	}

  // Done.
	return 0;

}

