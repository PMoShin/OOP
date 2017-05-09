#pragma once
#pragma once
#include"Container.h"
#include"iostream"
#include"algorithm"
#include"math.h"
#include"Base.h"

const double Pi = 3.14159;
int Counter = 0;

class Shape : public Printable
{
public:
	Shape()
	{
		Counter++;
	}

	Shape(const Shape& shape)
	{
		Counter++;
	}

	static int GetCount()
	{
		return Counter;
	}

	std::string Print() const { return "Shape"; }

	~Shape()
	{
		Counter--;
	}
};

class Point : public Shape, public Named
{
public:
	double x, y;

	Point() : Named("Point")
	{
		x = 0;
		y = 0;
	}

	Point(const double& new_x, const double& new_y) :Named("Point:")
	{
		x = new_x;
		y = new_y;
	}

	std::string Print() const
	{
		return "\n" + this->GetName() + "\nx:" + std::to_string(this->x) + "\ny:" + std::to_string(this->y) + "\n";
	}

	friend std::ostream& operator<<(std::ostream& os, Point& point)
	{
		return os << point.Print();
	}
};

class Circle : public Shape, public Named
{
public:
	double x, y, radius;

	Circle() :Named("Circle")
	{
		x = 0;
		y = 0;
		radius = 0;
	}

	Circle(const double& new_x, const double& new_y, const double& r) :Named("Circle")
	{
		x = new_x;
		y = new_y;
		radius = r;
	}

	std::string Print() const
	{
		return "\n" + this->GetName() + "\nCenter Ox:" + std::to_string(this->x) + "\nCenter Oy:" + std::to_string(this->y)
			+ "\nRadius:" + std::to_string(this->radius) + "\nArea of Circle:" + std::to_string(this->radius * this->radius * Pi) + "\n";
	}

	friend std::ostream& operator<<(std::ostream& Os, Circle& circle)
	{
		return Os << circle.Print();
	}
};

class Rectangle : public Shape, public Named
{
public:
	Point Point1, Point2;

	Rectangle() : Named("Rectangle")
	{
		Point1 = Point();
		Point2 = Point();
	}

	Rectangle(const double& LeftX, const double& LeftY, const double& RightX, const double& RightY) : Named("Rectangle")
	{
		Point1 = Point(LeftX, LeftY);
		Point2 = Point(RightX, RightY);
	}

	std::string Print() const
	{
		return "\n" + this->GetName()
			+ "\nbig side length:" + std::to_string(std::max(fabs(this->Point1.x - this->Point2.x), fabs(this->Point1.y - this->Point2.y)))
			+ "\nsmall side length:" + std::to_string(std::min(fabs(this->Point1.x - this->Point2.x), fabs(this->Point1.y - this->Point2.y)))
			+ "\narea:" + std::to_string(fabs(this->Point1.x - this->Point2.x)*fabs(this->Point1.y - this->Point2.y)) + "\n";
	}

	friend std::ostream& operator<<(std::ostream& Os, Rectangle& rectangle)
	{
		return Os << Rectangle.Print();
	}
};

class Square : public Shape, public Named
{
public:
	Point LeftPoint;
	double Length;
	Square() : Named("Square")
	{
		LeftPoint = Point();
		Length = 0;
	}

	Square(const double& LeftX, const double& LeftY, const double& length) : Named("Square")
	{
		LeftPoint = Point(LeftX, LeftY);
		Length = length;
	}

	std::string Print() const
	{
		return "\n" + this->GetName() + "\nside length:" + std::to_string(this->Length) + "\narea:" + std::to_string(pow(this->Length, 2)) + "\n";
	}

	friend std::ostream& operator<<(std::ostream& Os, Square& square)
	{
		return Os << square.Print();
	}
};

class Polyline : public Shape, public Named
{
public:
	Container<Point> Points;
	double Length;

	Polyline() : Named("Polyline")
	{
		Points.AddFirst(Point());
		Length = 0;
	}

	Polyline(Container<Point>& dots, const int& size) : Named("Polyline")
	{
		Length = 0;
		dots.MoveToFirst();
		AddPoint(dots.GetFirst());
		for (int i = 1; i < size; i++)
		{
			AddPoint(dots.GoOver());
		}
	}

	void AddPoint(const Point& point)
	{
		if (this->Points.IsEmpty())
		{
			this->Points.AddLast(point);
			return;
		}
		else
		{
			double dotX = this->Points.GetLast().x;
			double dotY = this->Points.GetLast().y;
			this->Points.AddLast(point);
			this->Length += sqrt(pow(dotX - point.x, 2) + pow(dotY - point.y, 2));
		}
	}

	std::string Print() const
	{
		return "\n" + this->GetName() + "\nlength:" + std::to_string(this->Length) + "\n";
	}

	friend std::ostream& operator<<(std::ostream& Os, Polyline& Line)
	{
		return Os << Line.Print();
	}
};

class Polygone : public Shape, public Named
{
public:
	Container<Point> Points;
	double Length;

	Polygone() : Named("Polygone")
	{
		Points.AddFirst(Point());
		Length = 0;
	}

	Polygone(Container<Point>& dots, const int& size) : Named("Polygone")
	{
		Length = sqrt(pow(dots.GetFirst().x - dots.GetLast().x, 2) +
			pow(dots.GetFirst().y - dots.GetLast().y, 2));
		dots.MoveToFirst();
		AddPoint(dots.GetFirst());
		for (int i = 1; i < size; i++)
		{
			AddPoint(dots.GoOver());
		}
	}

	void AddPoint(const Point& point)
	{
		if (this->Points.IsEmpty())
		{
			this->Points.AddLast(point);
			return;
		}
		else
		{
			double dotX = this->Points.GetLast().x;
			double dotY = this->Points.GetLast().y;
			this->Points.AddLast(point);
			this->Length += sqrt(pow(dotX - point.x, 2) + pow(dotY - point.y, 2));
		}
	}

	std::string Print() const
	{
		return "\n" + this->GetName() + "\nperimeter:" + std::to_string(this->Length) + "\n";
	}

	friend std::ostream& operator<<(std::ostream& Os, Polygone& Ngon)
	{
		return Os << Ngon.Print();
	}
};